PROGRAM=tp1
CC := g++
FLAGS := -Wall -pedantic -g
LDLFLAGS=-lm
GREEN= \e[92m
NORMAL= \e[0m

all:
	@echo "$(GREEN)Compilando ...$(NORMAL)"
	$(MAKE) tp1
	@echo "$(GREEN)Terminó$(NORMAL)"

cmdline.o: cmdline.cpp cmdline.h
	$(CC) $(FLAGS) cmdline.o

bignum.o: bignum.cpp bignum.h
	$(CC) $(FLAGS) bignum.o

shunting.o: shunting.cpp bignum.h
	$(CC) $(FLAGS) shunting.o

tp1: cmdline.cpp bignum.cpp tp1.cpp shunting.cpp
	$(CC) $(FLAGS) $^ -o tp1

clean:
	@echo "$(GREEN)Limpiando ...$(NORMAL)"
	rm -vf *.o $(PROGRAM)
	@echo "$(GREEN)Listo!$(NORMAL)"

gdb: tp1
	gdb ./tp1

valgrind: tp1
	valgrind --leak-check=full --show-leak-kinds=all ./tp1
