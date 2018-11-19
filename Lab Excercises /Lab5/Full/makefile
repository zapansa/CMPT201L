# Student's Name: Patricia Zapansa
# Lab Excercise #5, Part (#1)
# Lab Section: 201-X02L
# Lab Instructor’s Name: Calin Anton
# CMPUT 201
# Instructor's Name: Calin Anton

# The -g flag must be set to the compiler
CFLAGS = -g -std=c99
CC = gcc
main: main.c safeStr.c
	$(CC) $(CFLAGS) -o main main.c safeStr.c
ms.o: main.c safeStr.h
	$(CC) $(CFLAGS) -c main.c
ss.o: safeStr.c safeStr.h
	$(CC) $(CFLAGS) -c safeStr.c
tar: 
	tar -zcvf lab5.tar.gz main.c safeStr.c safeStr.h README.txt stringPointers.c makefile

