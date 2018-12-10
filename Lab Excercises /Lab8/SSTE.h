/*-------------------------------------------------------
# Student's Name: Patricia Zapansa
# Lab Exercise #8
# Lab Section: 201-X02L
# Lab Instructor’s Name: Calin Anton
# CMPUT 201
# Instructor's Name: Calin Anton
*------------------------------------------------------*/
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct client
{
  char cName[20];
  int cID;
  int cBalance;
  int cShare;
  struct client *next;
} CLIENT;

typedef struct orders
{
  int oID;
  int oType;
  int oPrice;
} ORDER;

// typedef struct list
// {
//   CLIENT client;
//   CLIENT *next;
// } sste;

CLIENT *addClient(CLIENT *head, int ID, char name[], int balance, int share);

CLIENT *delClient(CLIENT *head, int ID);

void SSTEMENU();

int choice();

void displayClient(CLIENT *c);

void listClient(CLIENT *head);
