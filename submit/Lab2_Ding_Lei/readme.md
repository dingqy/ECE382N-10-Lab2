## ECE382N.10 Parallel Computer Architecture Lab 2
Qiyang Ding, Mingyu Lei

## Filer organization
1. Two versions of `proc.cpp` and `test.cpp`

   - `proc.cpp` and `test.cpp`: for processor-level test
   - `proc_uarch.cpp` and `test_uarch.cpp`: for uarch-level test, helpful in debugging process

2. Scripts are located in `sim/scipts`

## To run the test
1. Please make sure you substitute your cpp files (`proc.cpp`, `test.cpp`, `proc_uarch.cpp`, `test_uarch.cpp`) as well as the header files (`proc.h`, `test.h`) with ours.
   
2. cd to sim/scipts

       $ cd /sim/scripts

3. run *processor-level* test, where we use load/store to access data, the cache/dir is treated as a blackbox (`26` test cases in total)

       $ ./runme.sh

4. run *uarch-level* test, where dir/cache states are checked (`33` test cases in total)

       $ ./runme_uarch.sh

## To use our tests for others' simulator

1. Please make sure you copy our cpp files (`proc.cpp`, `test.cpp`) as well as the header files (`proc.h`, `test.h`) to others' simulator. `proc.h` is specific so it should also be copied with `proc.cpp`. Otherwise, it cannot be compiled.