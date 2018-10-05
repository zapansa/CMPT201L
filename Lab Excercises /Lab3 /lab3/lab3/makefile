# Student's Name: Patricia Zapansa
# Lab Excercise #3, Part (#2def)
# Lab Section: 201-X02L
# Lab Instructor’s Name: Calin Anton
# CMPUT 201
# Instructor's Name: Calin Anton

CFLAGS = -Wall
LDLIBS = -lm
CC = gcc

compile: secondchange.c change.c
	$(CC) $(CFLAGS) -o change secondchange.c change.c $(LDLIBS)
secondchange.o: secondchange.c change.h
	$(CC) $(CFLAGS) -c secondchange.c
change.o: change.c change.h
	$(CC) $(CFLAGS) -c change.c
clean: 
	rm *.o
tar: 
	tar -zcvf lab3.tar.gz firstchange.c change.c change.h secondchange.c makefile
