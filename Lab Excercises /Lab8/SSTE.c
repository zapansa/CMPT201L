/*-------------------------------------------------------
# Student's Name: Patricia Zapansa
# Lab Exercise #8
# Lab Section: 201-X02L
# Lab Instructor’s Name: Calin Anton
# CMPUT 201
# Instructor's Name: Calin Anton
*------------------------------------------------------*/
#include "SSTE.h"

CLIENT *addClient(CLIENT *head, int ID, char name[], int balance, int share)
{
  CLIENT *newClient;

  newClient = (CLIENT*)malloc(sizeof(CLIENT));

  if(newClient == NULL)
  {
    printf("Allocation Failed.\n");
    exit(0);
  }
  else
  {
    newClient->cID = ID;
    strcpy(newClient->cName, name);
    newClient->cBalance = balance;
    newClient->cShare = share;
    newClient->next = head;
    head = newClient;
    return head;
  }
}

CLIENT *delClient(CLIENT *head, int ID)
{
  /* in the beginning */
  CLIENT *ptr;
  CLIENT *behindPtr;

  if(head->cID == ID)
  {
    ptr = head;
    /*deleted*/
    head = head->next;
    free(ptr);
    return head;
  }

  /* not at the beginning */
  for(ptr=head->next, behindPtr=head; ptr!=NULL; ptr=ptr->next, behindPtr=behindPtr->next)
  {
    if(ptr->cID == ID)
    {
      /* delete the node */
      behindPtr->next = ptr->next;
      free(ptr);
      return head;
    }
  }

  /* employee not found show sorry message or something */
  return head;
}

void SSTEMENU()
{
  printf("1. Add a Client\n");
  printf("2. Delete a Client\n");
  printf("3. View all Clients\n");
}

int choice()
{
  SSTEMENU();
  int choice;

  printf("Enter a choice:");
  scanf("%d", &choice);

  return choice;
}

void displayClient(CLIENT *c)
{
  printf("#%10d %15s $%10d - Shares: %d\n", c->cID, c->cName, c->cBalance, c->cShare);
}

void listClient(CLIENT *head)
{
  CLIENT *ptr;
  for(ptr = head; ptr != NULL; ptr = ptr->next)
    displayClient(ptr);
}

int main(void)
{
  CLIENT *list;
  char name[20];
  int ID;
  int balance;
  int share;

  list = NULL;

  int choose = choice();

    switch (choose)
    {
      case 1:
        printf("Enter Client Name: ");
        scanf("%s", name);
        printf("Enter Client Balance: ");
        scanf("%d", &balance);
        printf("Enter Client Shares: ");
        scanf("%d", &share);
        ID = 10+share+balance+10000;
        list = addClient(list, ID, name, balance, share);
        break;
      case 2:
        printf("Enter Client ID to Delete ");
        scanf("%d ", &ID);
        list = delClient(list, ID);
        break;
      case 3:
        if(list == NULL)
        {
          printf("The list is empty.\n");
          break;
        }
        listClient(list);
        break;
      case 4:
        exit(0);
      default:
        break;
    }

  listClient(list);
}
