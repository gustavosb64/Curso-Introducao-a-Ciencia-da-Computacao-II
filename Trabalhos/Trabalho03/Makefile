all:
	python autotad.py lista_encadeada.c 
	gcc -Wall -g -o main main.c lista_encadeada.c

c:
	python autotad.py lista_encadeada.c comment-off
	gcc -g -o main main.c lista_encadeada.c

run:
	./main

debug:
	valgrind -s --leak-check=full --show-leak-kinds=all --track-origins=yes ./main
