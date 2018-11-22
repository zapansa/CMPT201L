/*-------------------------------------------------------
# Student's Name: Patricia Zapansa
# Lab Exercise #7, Part1
# Lab Section: 201-X02L
# Lab Instructor’s Name: Calin Anton
# CMPUT 201
# Instructor's Name: Calin Anton
*------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define GAME_AMT (7)
#define MAX_STR (60)

/* game structure - storing price & title */
typedef struct
  {
 double price;
 char title[60];
  } game;

/* function declarations */

/* This function is used to compare titles of games alphabetically.
   Preconditions: array of games is initialized
   Postconditions: an integer is returned
*/
int compGamesByTitle(game *g1, game *g2);

/* This function is used to compare price of games
   Preconditions: array of games is initialized
   Postconditions: an integer is returned
*/
int compGamesByPrice(game *g1, game * g2);

int main(void)
  {
    /* variables */
    int g;

    /* Array of titles and prices in order !! */
    double pArray[GAME_AMT] = {22.79, 0.01, 7.79, 14.99, 0, 7.79, 64.96};
    char tArray[GAME_AMT][MAX_STR] = {"Opus Magnum", "Minecraft", "TIS-100", "Trainz",
			     "Code Combat", "Lemmings Revolution", "Warcraft"};

   /* array of game structs */
   game gArray[GAME_AMT];

   /* make the structs via loop and add to gArray */
   for(g=0; g<GAME_AMT; g++)
     {
       gArray[g].price = pArray[g];
       strcpy(gArray[g].title, tArray[g]);
     }

   /* uses qsort function to sort games by the title */
   qsort(gArray, GAME_AMT, sizeof(*gArray), (int(*)(const void*,const void*))compGamesByTitle);
   printf("By title\n");

   /* print title sorted gArray */
   for(g=0; g<GAME_AMT; g++)
     {
       printf("%s %.2f\n", gArray[g].title, gArray[g].price);
     }

   /* uses qsort function to sort games by price */
   qsort(gArray, GAME_AMT, sizeof(*gArray), (int(*)(const void*,const void*))compGamesByPrice);
   printf("\nBy price\n");

   /* print privce sorted gArray */
   for(g=0; g<GAME_AMT; g++)
     {
       printf("%s %.2f\n", gArray[g].title, gArray[g].price);
     }

   return 0;
  }

int compGamesByTitle(game *g1, game *g2)
  {
    /* returns comparison of g1 and g2 title
       negative int if g1 appears before g2 in lexico. order
       0 if g1==g2
       postitive if g1 appears after g2 in lexico. order
    */
    return strcmp((const char *)g1->title, (const char*)g2->title);
  }

int compGamesByPrice(game *g1, game *g2)
  {
    /* returns comparison of g1 and g2 price
       negative int if g1<g2
       0 if g1==g2
       postitive if g1>g2
    */
    return(g1->price-g2->price);
  }
