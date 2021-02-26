CC=g++
CFLAGS= -std=c++11 -fopenmp -o prog

%.o: %.cpp
	$(CC) -c -o $@ $< $(CFLAGS) $(DEBUGFLAGS)

ALL: countTwinPrimes.o
	$(CC) countTwinPrimes.cpp $(CFLAGS) $(DEBUGFLAGS)


DEBUG: DEBUGFLAGS = -DDEBUG
DEBUG: ALL

CLEAN:
	rm *.o