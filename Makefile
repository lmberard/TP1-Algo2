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

bignum.o: bignum.cpp bignum.h multiply_interface.h
	$(CC) $(FLAGS) bignum.o

tp1.o: tp1.cpp tp1.h
	$(CC) $(FLAGS) tp1.o

karatsuba.o: karatsuba.cpp karatsuba.h
	$(CC) $(FLAGS) shunting.o

standard.o: standard.cpp standard.h
	$(CC) $(FLAGS) shunting.o

shunting.o: shunting.cpp shunting.h
	$(CC) $(FLAGS) shunting.o

tp1: cmdline.cpp bignum.cpp shunting.cpp tp1.cpp karatsuba.cpp standard.cpp
	$(CC) $(FLAGS) $^ -o tp1

clean:
	@echo "$(GREEN)Limpiando ...$(NORMAL)"
	rm -vf *.o $(PROGRAM)
	@echo "$(GREEN)Listo!$(NORMAL)"

gdb: tp1
	gdb ./tp1

valgrind: tp1
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes -s ./tp1
