// cache.c
//   by Derek Chiou
//      March 4, 2007
// 

// for 382N-10

// STUDENTS: YOU MAY NEED TO MODIFY THIS FILE, BUT KEEP YOUR CHANGES TO A MINIMUM.

#include <stdio.h>
#include "types.h"
#include "cache.h"
#include "iu.h"

/**
 * Constructor of cache
 *
 * @param __node Node ID
 * @param __lg_assoc Log2 Associativity
 * @param __lg_num_sets Log2 Sets
 * @param __lg_cache_line_size Log2 CacheLine Size
 */
cache_t::cache_t(int __node, int __lg_assoc, int __lg_num_sets, int __lg_cache_line_size) {
    init(__node, __lg_assoc, __lg_num_sets, __lg_cache_line_size);
}

/**
 * Initialization (Actual constructor)
 *
 * @param __node Node ID
 * @param __lg_assoc Log2 Associativity
 * @param __lg_num_sets Log2 Sets
 * @param __lg_cache_line_size Log2 CacheLine Size
 */
void cache_t::init(int __node, int __lg_assoc, int __lg_num_sets, int __lg_cache_line_size) {
    node = __node;
    lg_assoc = __lg_assoc;
    lg_num_sets = __lg_num_sets;
    lg_cache_line_size = __lg_cache_line_size;

    full_hits = partial_hits = misses = 0;

    // Number of sets
    num_sets = (1 << lg_num_sets);

    // Number of cache blocks per set
    assoc = (1 << lg_assoc);

    // Get the index from address
    set_shift = lg_cache_line_size;
    set_mask = (1 << lg_num_sets) - 1;

    // Tag size start bit
    address_tag_shift = lg_cache_line_size + lg_num_sets;

    // Fetch valid data for one cache line
    cache_line_mask = (1 << lg_cache_line_size) - 1;
    if ((cache_line_mask + 1) != CACHE_LINE_SIZE) {
        ERROR("inconsistent cache_line_size");
    }

    tags = new cache_line_t *[num_sets];

    // Initialization of tag store
    // Invalid and no replacement
    // 0 initialization
    for (int i = 0; i < num_sets; ++i) {
        tags[i] = new cache_line_t[assoc];

        for (int j = 0; j < assoc; ++j) {
            tags[i][j].permit_tag = INVALID;
            tags[i][j].replacement = -1;

            for (int k = 0; k < cache_line_size; ++k) {
                tags[i][j].data[k] = 0;
            }
        }
    }
}

void cache_t::bind(iu_t *i) {
    iu = i;
}

void cache_t::print_stats() {
    printf("------------------------------\n");
    printf("node %d\n", node);
    printf("full_hits      = %d\n", full_hits);
    printf("partial_hits   = %d\n", partial_hits);
    printf("misses         = %d\n", misses);
    printf("total accesses = %d\n", full_hits + partial_hits + misses);
    printf("hit rate = %f\n", hit_rate());
}

double cache_t::hit_rate() {
    return ((double) full_hits / (full_hits + partial_hits + misses));
}

/**
 * Get address tag
 *
 * @param addr Address
 * @return Tag
 */
address_tag_t cache_t::gen_address_tag(address_t addr) {
    return (addr >> address_tag_shift);
}

/**
 * Get block offset
 *
 * @param addr Address
 * @return Block offset
 */
int cache_t::gen_offset(address_t addr) {
    return (addr & cache_line_mask);
}

/**
 * Get set index
 *
 * @param addr Address
 * @return Set index
 */
int cache_t::gen_set(address_t addr) {
    int set = (addr >> set_shift) & set_mask;
    NOTE_ARGS(("addr = %x, set_shift %d, set_mask %x, set %d\n", addr, set_shift, set_mask, set));
    return (set);
}

/**
 * Cache access implementation
 *
 * @param addr Address
 * @param permit Cache coherence bit
 * @param car
 * @return
 */
bool cache_t::cache_access(address_t addr, permit_tag_t permit, cache_access_response_t *car) {
    int set = gen_set(addr);
    address_tag_t address_tag = gen_address_tag(addr);

    car->set = set;

    for (int a = 0; a < assoc; ++a) {
        if (tags[set][a].address_tag == address_tag) { // found in cache, check permit
            car->address_tag = address_tag;
            car->permit_tag = tags[set][a].permit_tag;
            car->way = a;

            return (car->permit_tag >= permit);

        }
    }

    car->permit_tag = INVALID;
    return (false);
}

/**
 * Modify cache sline state (coherence)
 *
 * @param car Cache request
 * @param permit Coherence bits
 */
void cache_t::modify_permit_tag(cache_access_response_t car, permit_tag_t permit) {
    tags[car.set][car.way].permit_tag = permit;
}

/**
 * Cache line fill implementation
 *
 * @param car Cache request
 * @param data Data (cache line)
 */
void cache_t::cache_fill(cache_access_response_t car, data_t data) {
    tags[car.set][car.way].address_tag = car.address_tag;
    tags[car.set][car.way].permit_tag = car.permit_tag;

    NOTE_ARGS(("set tags[%d][%d].address_tag = %d", car.set, car.way, car.address_tag));
    NOTE_ARGS(("set tags[%d][%d].permit_tag  = %d", car.set, car.way, car.permit_tag));

    touch_replacement(car);

    for (int i = 0; i < CACHE_LINE_SIZE; ++i)
        tags[car.set][car.way].data[i] = data[i];
}

/**
 * Read data from target cache line
 *
 * @param addr Address
 * @param car Cache request
 * @return Data (byte)
 */
int cache_t::read_data(address_t addr, cache_access_response_t car) {
    int offset = gen_offset(addr);

    return (tags[car.set][car.way].data[offset]);
}


/**
 * Write data to target cache line
 *
 * @param addr Address
 * @param car Cache request
 * @param data Data (byte)
 */
void cache_t::write_data(address_t addr, cache_access_response_t car, int data) {
    int offset = gen_offset(addr);

    tags[car.set][car.way].data[offset] = data;
}

cache_access_response_t cache_t::lru_replacement(address_t addr) {
    cache_access_response_t car;

    // already in the cache?
    if (cache_access(addr, INVALID, &car)) {
        return (car);
    }

    bool done_p = false;
    int set = gen_set(addr);

    // find LRU way
    car.address_tag = gen_address_tag(addr);
    car.set = set;

    // see if you can find yourself
    for (int a = 0; a < assoc; ++a) {
        if (tags[set][a].replacement == -1) {
            car.way = a;
            return (car);
        } else if (tags[set][a].replacement == 0) {
            done_p = true;
            car.way = a;
        }
    }

    if (done_p) return (car);

    ERROR("should be a way that is LRU");

}

// perfect LRU
/**
 * Replacement status update
 *
 * For each hit, replacement status should be changed. The hit one should have the highest priority and lower the ones
 * that are less victim than current cache line (Reorder the current one to be the least likely to be evicted)
 *
 * @param car
 */
void cache_t::touch_replacement(cache_access_response_t car) {
    int cur_replacement = tags[car.set][car.way].replacement;
    if (cur_replacement < 0) cur_replacement = 0;

    tags[car.set][car.way].replacement = assoc;

    for (int a = 0; a < assoc; ++a) {
        if (tags[car.set][a].replacement > cur_replacement) // demote
            --tags[car.set][a].replacement;
    }

    // consistency check
    // Least recently used cache line should be only one
    bool found_zero_p = false;
    for (int a = 0; a < assoc; ++a) {
        if (tags[car.set][a].replacement == 0)
            if (found_zero_p) {
                ERROR("touch_replacement: error\n");
            } else
                found_zero_p = true;

        if (tags[car.set][a].replacement > assoc - 1) {
            ERROR("touch_replacement: error: assoc too large\n");
        }
    }
}

/**
 * Load request from processor
 *
 * @param addr Address
 * @param tag Debug info
 * @param data Data (byte)
 * @param retried_p Retry status
 * @return Response to processor
 */
response_t cache_t::load(address_t addr, bus_tag_t tag, int *data, bool retried_p) {
    response_t r;
    cache_access_response_t car;
    int a;

    // Cache hit (No retry, hit status update)
    // Retry hit is not actual hit
    // Tag access and comparison
    if (cache_access(addr, SHARED, &car)) {
        if (!retried_p) ++full_hits;
        r.hit_p = true;
        r.retry_p = false;

        // Data access
        *data = read_data(addr, car);

        NOTE_ARGS(("%d: hit: addr %d, tag %d", node, addr, tag));

        // Update replacement policy
        touch_replacement(car);

    } else {  // miss, service request
        if (!retried_p) {
            ++misses;
            proc_cmd_t proc_cmd = (proc_cmd_t) {READ, addr, tag, SHARED};

            NOTE_ARGS(("%d: miss: addr %d, tag %d", node, addr, tag));

            // issue a read to next level of memory hierarchy.  In this case,
            // it's the IU

            bool iu_retry_p = iu->from_proc(proc_cmd);

            // create a response.  We know that it will take at least one
            // cycle to get a response and we are modeling a blocking cache
            // for now (if there is an outstanding miss, retry all memory
            // operations until that miss is statisfied.)
        }

        r.hit_p = false;
        r.retry_p = true; // blocking cache for now
    }
    return (r);
}

/**
 * Write request from processor
 *
 * @param addr Address
 * @param tag (???)
 * @param data Data (byte)
 * @param retried_p Retry status
 * @return
 */
response_t cache_t::store(address_t addr, bus_tag_t tag, int data, bool retried_p) {
    response_t r;
    cache_access_response_t car;
    int a;

    // First try exclusive/modified cache tag access
    cache_access(addr, EXCLUSIVE, &car);

    switch (car.permit_tag) {
        // Miss in the cache
        case INVALID: {
            if (!retried_p) {
                proc_cmd_t proc_cmd = (proc_cmd_t) {READ, addr, tag, MODIFIED};
                iu->from_proc(proc_cmd);

                ++misses;
            }

            r.hit_p = false;
            r.retry_p = true;
            break;
        }

            // Broadcast ownership through network first
        case SHARED: {
            if (!retried_p) {
                proc_cmd_t proc_cmd = (proc_cmd_t) {READ, addr, tag, MODIFIED};
                iu->from_proc(proc_cmd);

                ++partial_hits;
            }

            r.hit_p = false;
            r.retry_p = true;
            break;
        }

        case EXCLUSIVE:
            if (!retried_p) ++full_hits;

            // Upgrade cache line status
            modify_permit_tag(car, MODIFIED);

            // Update replacement status
            touch_replacement(car);

            // Write data into cache line
            write_data(addr, car, data);

            r.hit_p = true;
            r.retry_p = false;
            break;

        case MODIFIED:
            if (!retried_p) ++full_hits;

            r.hit_p = true;
            r.retry_p = false;
            touch_replacement(car);
            write_data(addr, car, data);
            break;
        default: ERROR("store: illegal permission");
    }

    return (r);
}

/**
 * Fill the cache from Intersection Unit for processor request
 *
 * @param proc_cmd Processor request
 */
void cache_t::reply(proc_cmd_t proc_cmd) {
    // fill cache, return to processor

    cache_access_response_t car = lru_replacement(proc_cmd.addr);

    NOTE_ARGS(("%d: replacing addr_tag %d into set %d, assoc %d", node, car.address_tag, car.set, car.way));

    // TODO: Write back replacement cache line
    car.permit_tag = proc_cmd.permit_tag;
    cache_fill(car, proc_cmd.data);

}

