CLFAGS = -Wall
CC = gcc

all: demo

demo: SSTE.o
	$(CC) $(CFLAGS) -o demo SSTE.o

SSTE.o: SSTE.h SSTE.c
	$(CC) $(CFLAGS) -c SSTE.c
