#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "items.h"
#include "rooms.h"
#include "character.h"
#include "avatar.h"

struct Room * initializeBoard(){
    //dynamically allocate memory for 9 Rooms in an array
    struct Room *roomsArray = (struct Room*) malloc(9 * sizeof(struct Room));
    char allRooms[9][30] = {"kitchen", "ballroom", "conservatory", "dining", "billiard", "library", "lounge", "hall", "study"};
    
    //All characters except the Avatar(Scarlett)
    char allCharacters[5][30] = {"Mustard", "White", "Reverend", "Peacock", "Plum"};
    
    char allItems[6][30] = {"candlestick", "dagger", "pipe", "revolver", "rope", "wrench"};
   
   // Assigning each room struct with name of room and a character
    for (int i = 0; i < 9; i++){
        roomsArray[i].name = strdup(allRooms[i]);
        if (i < 5){
            struct CharacterNode *currChar = (struct CharacterNode*) malloc(sizeof(struct CharacterNode));
            roomsArray[i].characterList = currChar;
            currChar->characterName = strdup(allCharacters[i]);
        }
        if (i < 6){
            struct ItemNode *currItem = (struct ItemNode*) malloc(sizeof(struct ItemNode));
            roomsArray[i].itemList = currItem;
            currItem->itemName = strdup(allItems[i]); //strdup to create a copy and stores in heap
        }
    }
   
    randomize(roomsArray, 9);


    //Assign north, south, east, west pointers for each room in order.
    //Room 0:
    roomsArray[0].North = NULL;
    roomsArray[0].South = &roomsArray[3];
    roomsArray[0].East = &roomsArray[1];
    roomsArray[0].West = NULL;

    // Room 1:
    roomsArray[1].North = NULL;
    roomsArray[1].South = &roomsArray[4];
    roomsArray[1].East = &roomsArray[2];
    roomsArray[1].West = &roomsArray[0];

    // Room 2:
    roomsArray[2].North = NULL;
    roomsArray[2].South = &roomsArray[5];
    roomsArray[2].East = NULL;
    roomsArray[2].West = &roomsArray[1];

    // Room 3:
    roomsArray[3].North = &roomsArray[0];
    roomsArray[3].South = &roomsArray[6];
    roomsArray[3].East = &roomsArray[4];
    roomsArray[3].West = NULL;

    // Room 4:
    roomsArray[4].North = &roomsArray[1];
    roomsArray[4].South = &roomsArray[7];
    roomsArray[4].East = &roomsArray[5];
    roomsArray[4].West = &roomsArray[3];

    // Room 5:
    roomsArray[5].North = &roomsArray[2];
    roomsArray[5].South = &roomsArray[8];
    roomsArray[5].East = NULL;
    roomsArray[5].West = &roomsArray[4];

    // Room 6:
    roomsArray[6].North = &roomsArray[3];
    roomsArray[6].South = NULL;
    roomsArray[6].East = &roomsArray[7];
    roomsArray[6].West = NULL;

    // Room 7:
    roomsArray[7].North = &roomsArray[4];
    roomsArray[7].South = NULL;
    roomsArray[7].East = &roomsArray[8];
    roomsArray[7].West = &roomsArray[6];

    // Room 8:
    roomsArray[8].North = &roomsArray[5];
    roomsArray[8].South = NULL;
    roomsArray[8].East = NULL;
    roomsArray[8].West = &roomsArray[7];
    
    return roomsArray;
}

void printRoom(struct Room *roomsArray){
    for (int i = 0; i < 9; i++){
        printf("Room name: %s\n", roomsArray[i].name);
        if (roomsArray[i].characterList != NULL){
           printf("Character in room: %s\n", roomsArray[i].characterList->characterName);
        }
        if (roomsArray[i].itemList != NULL){
           
           printf("item in room: %s\n", roomsArray[i].itemList->itemName);
        }
        printf("\n");  
    }
    
}
// Fisher yates shuffle
void randomize (struct Room *arr, int n ){
    // Use a different seed value so that we don't get same
    // result each time we run this program
    srand ( time(NULL) );
 
    // Start from the last element and swap one by one. We don't
    // need to run for the first element that's why i > 0
    for (int i = n-1; i > 0; i--)
    {
        // Pick a random index from 0 to i
        int j = rand() % (i+1);
        
        // Swap arr[i] with the element at random index
        struct Room temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
    }
}


