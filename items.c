//methods to add and remove linked list
//moving items from one list to another and to avatars

#include "items.h"
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

//Pass a pointer to the itemList pointer
//While using this method itemListPointer = &itemList (directy pass to addItem). 
void addItem(struct ItemNode **itemList, struct ItemNode *newItem){
    if (*itemList == NULL){ //itemList is pointing to NULl, list doesn't exist
        *itemList = newItem;
    }
    else{
        //When at end of linked list (since itemList is a double pointer, deference)
        if ((*itemList)->next == NULL){ 
            (*itemList)->next = newItem;
        }
        else{
            addItem(&(*itemList)->next, newItem);
        }
    }
    
}

//Find an item with the same item name
//Takes in pointer to head pointer of list and string key
//Return true or false
//Return false if list is empty


bool inItemList(struct ItemNode **head, char *key){
    struct ItemNode *cur = *head;
    while (cur != NULL){
        if (strcmp(cur->itemName, key) == 0){
            return true; 
        }
        cur = cur->next;
    }
  
    return false;
}


//Takes in head(double pointer) of list and key(string pointer)
//Returns true if node found 
//Returns false if node not found or list is empty

bool deleteItem(struct ItemNode **head, char *key){
    struct ItemNode *cur = *head;
    struct ItemNode *prev;

    //If key in first node
    if (cur != NULL && strcmp(cur->itemName, key) == 0){
        *head = cur->next;
        return true;
    }
    //If not first node
    while (cur != NULL){
        if(strcmp(cur->itemName, key) == 0){
            prev->next = cur->next;
           
            return true;
        }
        else{
            prev = cur;
            cur = cur->next;
        }
    }
    
    return false;
}
