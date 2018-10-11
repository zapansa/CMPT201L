# student's Name: Patricia Zapansa
# Lab Assignment #1
# Lab Section: 201-X02L
# Lab Instructor’s Name: Calin Anton
# CMPUT 201
# Instructor's Name: Calin Anton

# Main makefile for compiling all the programs

CFLAGS = -Wall -ansi -std=c89
CC = gcc

all: anagram primesdiff printfamday selectline squeeze
anagram: anagram.c
	$(CC) $(CFLAGS) -o anagram anagram.c
primesdiff: primesdiff.c
	$(CC) $(CFLAGS) -o primesdiff primesdiff.c
printfamday: printfamday.c
	$(CC) $(CFLAGS) -o printfamday printfamday.c
selectline: selectline.c
	$(CC) $(CFLAGS) -o selectline selectline.c
squeeze: squeeze.c
	$(CC) $(CFLAGS) -o squeeze squeeze.c
ass1.tar.gz: *.c makefile
	tar -zczf ass1.tar.gz *.c makefile
