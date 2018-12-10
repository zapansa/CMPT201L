CC=gcc 
FLAGS=-g
all: Lab9

Lab9_PASSMGMT.o: Lab9_PASSMGMT.h Lab9_PASSMGMT.c
	$(CC) $(FLAGS) -c Lab9_PASSMGMT.c

Lab9: Lab9.c Lab9_PASSMGMT.o
	$(CC) $(FLAGS) -o secMailCreate Lab9.c Lab9_PASSMGMT.o

clean:
	rm *.o

