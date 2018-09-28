CFLAGS = -Wall -g -std=c99
LDLIBS = -lm
CC = gcc  
compile: main.c numArray.c numMod.c
	$(CC) $(CFLAGS) -o lab2 main.c numArray.c numMod.c $(LDLIBS)
main.o: main.c numArray.h numMod.h
	$(CC) $(CFLAGS) -c main.c 
numArray.o: numArray.c numArray.h
	$(CC) $(CFLAGS) -c numArray.c
numMod.o: numMod.c numMod.h
	$(CC) $(CFLAGS) -c numMod.c
testing:
	./lab2 < lab2InTest1 > lab2OutTest1
	diff lab2Correct1 lab2OutTest1

