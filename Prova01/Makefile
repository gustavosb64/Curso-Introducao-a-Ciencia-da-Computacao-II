all:
	gcc -g -o codigo-alterado codigo-alterado.c

all-runcodes:
	gcc -g -o codigo-alterado codigo-alterado.c -Wall -Wpedantic

run:
	./codigo-alterado

debug:
	valgrind -s --leak-check=full --show-leak-kinds=all --track-origins=yes ./codigo-alterado

