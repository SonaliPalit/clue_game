#ifndef ROOMS_H
#define ROOMS_H


#include <stdio.h>

struct Room  
{
   char *name;
   struct Room *North;
   struct Room *South;
   struct Room *East;
   struct Room *West;
   struct ItemNode *itemList;
   struct CharacterNode *characterList;
};

struct Room * initializeBoard();

void randomize (struct Room *arr, int n );

void printRoom(struct Room *roomsArray);

#endif
