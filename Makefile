CC := g++
FLAGS := -Wall -pedantic -g 

all: tp0

cmdline.o: cmdline.cpp cmdline.h
	$(CC) $(FLAGS) cmdline.o
	
bignum.o: bignum.cpp bignum.h
	$(CC) $(FLAGS) bignumm.0

tp0: cmdline.cpp bignum.cpp tp0.cpp
	$(CC) $(FLAGS) $^ -o tp0 

clean:
	rm *.o

gdb: tp0
	gdb ./tp0

valgrind: tp0
	valgrind --leak-check=full ./tp0
