#include "character.h"
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>


//To add a character to a room
//Pass a pointer to the characterList head pointer

void addCharacter(struct CharacterNode **head, struct CharacterNode *newCharacter){
    if (*head == NULL){ // list doesn't exist
        *head = newCharacter;
    }
    else{
        //When at end of linked list (since characterList is a double pointer, deference)
        if ((*head)->next == NULL){ 
            (*head)->next = newCharacter;
        }
        else{
            addCharacter(&(*head)->next, newCharacter);
        }
    }
    
}

//Find a character with the same name
//Takes in pointer to head pointer of list and string key
//Return true or false
//Return false if list is empty


bool inCharacterList(struct CharacterNode **head, char *key){
    struct CharacterNode *cur = *head;
    while (cur != NULL){
        if (strcmp(cur->characterName, key) == 0){
            return true; 
        }
        cur = cur->next;
    }
    return false;
}


//Takes in head(double pointer) of list and key(string pointer)
//Returns true if node found 
//Returns false if node not found or list is empty

bool deleteCharacter(struct CharacterNode **head, char *key){
    struct CharacterNode *cur = *head;
    struct CharacterNode *prev;

    //If key in first node
    if (cur != NULL && strcmp(cur->characterName, key) == 0){
        *head = cur->next;
        return true;
    }
    //If not first node
    while (cur != NULL){
        if(strcmp(cur->characterName, key) == 0){
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


