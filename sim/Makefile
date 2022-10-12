all:	sim 

sim:	cache.cpp cache.h helpers.cpp iu.cpp proc.cpp network.cpp main.cpp test.cpp my_fifo.h 
	g++ -g cache.cpp helpers.cpp iu.cpp proc.cpp network.cpp main.cpp test.cpp -o sim

clean:
	rm *~ sim TAGS

ETAGS:	
	etags *.cpp *.h

