/*
Password management module which associates passwords with user id
*/
#ifndef PASSMGMT_H
#define PASSMGMT_H

#define PASSLEN 16      //password length
#define IDDTABSIZE 1000   //sized of password table

typedef char PASSWORD[PASSLEN];  //paswords
typedef unsigned int UIDD;       //uid 

int passwordVerify(PASSWORD,UIDD);  //verifies password for UID
int passwordAdd(PASSWORD,UIDD);     //add password for UID
int passwordDelete(UIDD);  //deltes password for uid

#endif
