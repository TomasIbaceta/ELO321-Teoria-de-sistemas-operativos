CC=gcc
LINKS=-lpthread

all: Dining

Dining: Dining.o
	$(CC) Dining.o -o Dining $(LINKS)
    
Dining.o: Dining.c
	$(CC) -c Dining.c 


clean:
	-rm -f *.o
