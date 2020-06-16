#Compilador a utlizar 
#Referencia de estudio http://profesores.elo.utfsm.cl/~agv/elo320/makefile/makefile.html
CC=gcc
LINKS=-lpthread

all: hilo

hilo: hilo.o
	$(CC) hilo.o -o hilo $(LINKS)
    
hilo.o: hilo.c
	$(CC) -c hilo.c 


clean:
	-rm -f *.o
