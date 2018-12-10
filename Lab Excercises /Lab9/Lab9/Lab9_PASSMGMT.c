#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Lab9_PASSMGMT.h"

PASSWORD passTable[IDDTABSIZE]; //password table idexed by uid
int usrCnt=0;


//Takes a password and a user id as prameteres
//returns 1 if password matched table entry for user id
//0 otherwise
int verifyPassword(PASSWORD pass, UIDD uid){
   if (!strcmp(pass,passTable[uid]))
     return 1;
   return 0;
  
}


//Takes a password and a user id as prameteres
//returns 1 if succesfully adds password for user id
//0 otherwise
int passwordAdd(PASSWORD pass,UIDD uid){
  if(usrCnt==IDDTABSIZE) //table is full
    return 0;
  if(!strcmp(passTable[uid],""))      //this is a new password increment userCount
    usrCnt++;
  strcpy(passTable[uid],pass);
  return 1;

}

//Takes user id as prameter
//returns 1 if successfully deleted password entry  for user id
//0 otherwise

int passwordDelete(UIDD uid){
  if ((uid<0) || (uid>IDDTABSIZE)) //wrong uid
    return 0; 
  if(strcmp(passTable[uid],"")) //this is a real delete password decrement userCount
    usrCnt--;
  strcpy(passTable[uid],"");
  return 1;
}
