all:
	gcc -g -o sort_algorithms sort_algorithms.c

run:
	./sort_algorithms

debug:
	valgrind -s --leak-check=full --show-leak-kinds=all --track-origins=yes ./sort_algorithms
