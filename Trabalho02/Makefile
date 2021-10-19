all:
	gcc -Wall -o main main.c func.c -lm

c:
	gcc -g -lm -o main main.c func.c

run:
	./main

debug:
	valgrind -s --leak-check=full --show-leak-kinds=all --track-origins=yes ./main
