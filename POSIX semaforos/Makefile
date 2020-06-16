CC=gcc
LINKS=-lpthread

all: posix-sem

posix-sem: posix-sem.o
	$(CC) posix-sem.o -o posix-sem $(LINKS)
    
posix-sem.o: posix-sem.c
	$(CC) -c posix-sem.c 


clean:
	-rm -f *.o
