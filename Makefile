CC := g++
FLAGS := -Wall -pedantic -g 

all: tp0
	
bignum.o: bignum.cpp bignum.h
	$(CC) $(FLAGS) bignumm.0

tp0: bignum.cpp tp0.cpp
	$(CC) $(FLAGS) $^ -o tp0 

clean:
	rm *.o

gdb: tp0
	gdb ./tp0

valgrind: tp0
	valgrind --leak-check=full ./tp0