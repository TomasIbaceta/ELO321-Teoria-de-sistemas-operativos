FLAGS = -std=c99 -lpthread -Wall
default: main.c
	$(RM) tarea3 *.o
	gcc -o tarea3 main.c queue.c queue.h $(FLAGS)
	./tarea3
run: default
	./tarea3