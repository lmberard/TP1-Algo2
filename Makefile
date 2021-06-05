PROGRAM=tp0
CC := g++
FLAGS := -Wall -pedantic -g
LDLFLAGS=-lm
GREEN= \e[92m
NORMAL= \e[0m 

all: 
	@echo "$(GREEN)Compilando ...$(NORMAL)"
	$(MAKE) tp0
	@echo "$(GREEN)Terminó$(NORMAL)"

cmdline.o: cmdline.cpp cmdline.h
	$(CC) $(FLAGS) cmdline.o
	
bignum.o: bignum.cpp bignum.h
	$(CC) $(FLAGS) bignumm.0

tp0: cmdline.cpp bignum.cpp tp0.cpp
	$(CC) $(FLAGS) $^ -o tp0 

clean:
	@echo "$(GREEN)Limpiando ...$(NORMAL)"
	rm -vf *.o $(PROGRAM)
	@echo "$(GREEN)Listo!$(NORMAL)"

gdb: tp0
	gdb ./tp0

valgrind: tp0
	valgrind --leak-check=full --show-leak-kinds=all ./tp0