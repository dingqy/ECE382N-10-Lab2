all:	sim

uarch: cache.cpp cache.h helpers.cpp iu.cpp proc_uarch.cpp network.cpp main.cpp test_uarch.cpp my_fifo.h 
	g++ -std=c++11 -g cache.cpp helpers.cpp iu.cpp proc_uarch.cpp network.cpp main.cpp test_uarch.cpp -o sim

sim:	cache.cpp cache.h helpers.cpp iu.cpp proc.cpp network.cpp main.cpp test.cpp my_fifo.h 
	g++ -std=c++11 -g cache.cpp helpers.cpp iu.cpp proc.cpp network.cpp main.cpp test.cpp -o sim

clean:
	rm *~ sim TAGS

ETAGS:	
	etags *.cpp *.h

