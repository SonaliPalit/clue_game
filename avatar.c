#include <stdbool.h>
#include <stdlib.h>
#include "avatar.h"
#include "rooms.h"
#include "items.h"

//Assign avatar's current room to the direction specified if possible
void go(struct Avatar **avatar, char *direction){
    char *north = "north";
    char *south = "south";
    char *east = "east";
    char *west = "west";

    if (strcmp(direction, north) == 0){
        if ((*avatar)->currentRoom->North != NULL){
            (*avatar)->currentRoom = (*avatar)->currentRoom->North;
            printf("Moved to North\n");
            return;
        }
    }
    if (strcmp(direction, south) == 0){
        if ((*avatar)->currentRoom->South != NULL){
            (*avatar)->currentRoom = (*avatar)->currentRoom->South;
            printf("Moved to South\n");
            return;
        }
    }
    if (strcmp(direction, east) == 0){
        if ((*avatar)->currentRoom->East != NULL){
            (*avatar)->currentRoom = (*avatar)->currentRoom->East;
            printf("Moved to East\n");
            return;
        }
    }
    if (strcmp(direction, west) == 0){
        if ((*avatar)->currentRoom->West != NULL){
            (*avatar)->currentRoom = (*avatar)->currentRoom->West;
            printf("Moved to West\n");
            return;
        }
    }
    printf("Reached end of board, connot move %s \n", direction);
}

//Avatar can pick up item from the room if it exists in room. 
//Item added to avatar's inventory
//Item removed from avatar's current room
//Return True if item not in current room
//If item does not exist in current room, return false 
bool take(struct Avatar *avatar, char *itemName){
    //If item present in currentRoom's itemList, then add to inventory
    if (inItemList(&(avatar->currentRoom->itemList), itemName)){
        struct ItemNode *newItem = (struct ItemNode*) malloc(sizeof(struct ItemNode));
        newItem->itemName = itemName;
        addItem((&(avatar->inventory)), newItem);
        deleteItem((&(avatar->currentRoom->itemList)), itemName);
        return true;
    }
    else{
        return false;
    }
} 

//Drops item from Avatar's inventory and adds to room's itemList
//If item not in inventory, returns false
bool drop(struct Avatar *avatar, char *itemName){
    if (inItemList(&(avatar->inventory), itemName)){
        deleteItem(&(avatar->inventory), itemName);

        struct ItemNode *newItem = (struct ItemNode*) malloc(sizeof(struct ItemNode));
        newItem->itemName = itemName;
        addItem(&(avatar->currentRoom->itemList), newItem);
        return true;
    }
    else{
        return false;
    }
}












