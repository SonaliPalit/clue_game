#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdio.h>
#include <stdbool.h>
#include "items.h"
#include "rooms.h"
#include "avatar.h"
#include "character.h"

struct Room *roomsArray;  
int clueCount = 0;

char *roomAnswer;
char *itemAnswer;
char *characterAnswer;

void help(){
    char *commands = "\n"\
                    "help: look up all commands \n"\
                    "list: look up the list of items, rooms and characters in the game \n"\
                    "look: see the room you are in, including items, rooms in each direction and characters in room \n"\
                    "inventory: see the items in your inventory \n"\
                    "go: move to an adjacent room to your north, south, east or west if it exists \n"\
                    "take: take an item in the room you are in and add to your inventory \n"\
                    "drop: drop an item in your inventory \n"\
                    "clue: take a guess about the character who did the murder and item used. You must currently be in the room where the murder occured \n"\
                    "quit: exits game \n";

    printf("\nThese are the commands you can use: %s", commands); 
}

void list(){
    char *items = "candlestick, dagger, pipe, revolver, rope, wrench";
    char *rooms = "kitchen, ballroom, conservatory, dining, billiard, library, lounge, hall, study";
    char *characters = "Mustard, White, Reverend, Peacock, Plum";
    printf("\n");
    printf("Characters: %s\n", characters);
    printf("Items: %s\n", items);
    printf("Rooms: %s\n", rooms);
}

void inventory(struct Avatar **avatar){
    struct ItemNode *current = (*avatar)->inventory;
    if (current == NULL){
        printf("No items in inventory\n");
    }
    else{
        printf("Items in inventory: ");
        while(current != NULL){
            printf("%s ", current->itemName);
            current = current->next;
        }
    }
    printf("\n");
}
void look(struct Avatar *avatar){

    printf("\n");
    //Print rooms in the 4 directions
    if (avatar->currentRoom->North != NULL){
        printf("North: %s\n", avatar->currentRoom->North->name);
    }
    else{
        printf("No room to North\n");
    }

    if (avatar->currentRoom->East != NULL){
        printf("East is: %s\n", avatar->currentRoom->East->name);
    }
    else{
        printf("No room to East\n");
    }

    if (avatar->currentRoom->West != NULL){
        printf("West: %s\n", avatar->currentRoom->West->name);
    }
    else{
        printf("No room to West\n");
    }

    if (avatar->currentRoom->South != NULL){
        printf("South: %s\n", avatar->currentRoom->South->name);
    }
    else{
        printf("No room to South\n");
    }
    printf("\n");


    //Print characters in that room
    struct CharacterNode *curChar = avatar->currentRoom->characterList;
    if (curChar == NULL){
        printf("No characters in this room\n");
    }
    else{
        printf("\nCharacters in this room are: ");
        while(curChar != NULL){
            printf("%s  ", curChar->characterName);
            curChar = curChar->next;
        }
    }
    
    printf("\n");

    //Print items in that room
    struct ItemNode *curItem = avatar->currentRoom->itemList;
    if (curItem == NULL){
        printf("No items in this room\n");
    }
    else{
        printf("Items in this room are: ");
        while(curItem != NULL){
            printf("%s  ", curItem->itemName);
            curItem = curItem->next;
        }
    }
    printf("\n");

}

bool isValidDirection(char *direction){
    char allDirections[4][20] = {"north", "south", "east", "west"};
    for (int i = 0; i < 4; i++){
        if (strcmp(direction, allDirections[i]) == 0){
            return true;
        }
    }
    return false;
}

bool isValidCharacter(char *character){
    char allCharacters[5][30] = {"Mustard", "White", "Reverend", "Peacock", "Plum"};
    for (int i = 0; i < 5; i++){
        if (strcmp(character, allCharacters[i]) == 0){
            return true;
        }
    }
    return false;
}

bool isValidItem(char *item){
    char allItems[6][30] = {"candlestick", "dagger", "pipe", "revolver", "rope", "wrench"};
    for (int i = 0; i < 6; i++){
        if (strcmp(item, allItems[i]) == 0){
            return true;
        }
    }
    return false;
}



//Iterate through rooms to find where character is 
//Return index of room where character is found
//Return NULL if not found
int findCharacter(struct Room *roomsArray, char *name){
   
    int i;
    for (i = 0; i < 9; i++){
        if (inCharacterList(&(roomsArray[i].characterList), name)){
            return i;
        }
    }
    return -1;
}

//Takes in roomsArray, name of character to be moved and avatar
//Moves character from a room to Avatar's room
void moveCharacter(struct Room *roomsArray, char *name, struct Avatar *avatar){

    //int index = 0;
    int index = findCharacter(roomsArray, name);
    if (index != -1){
        //Delete character from room they are in
        deleteCharacter(&(roomsArray[index].characterList), name);
        
        //Add character to Avatar's current room
        struct CharacterNode *addChar = (struct CharacterNode*) malloc(sizeof(struct CharacterNode));
        addChar->characterName = name;
        addCharacter(&(avatar->currentRoom->characterList), addChar);
    }
    else{
        printf("Character not found in rooms\n");
    }
}



//Return ints:
//0 - Lost the game (10 attempts done)
//1 - Did not win, still have atempts remaining
//2 - Won the game!
int checkClue(char *character, char* item, struct Avatar *avatar, struct Room *roomsArray){
    //Move character to avatar's room
    moveCharacter(roomsArray, character, avatar);

    //Tell matching details
    int matches = 0;
    if (strcmp(avatar->currentRoom->name, roomAnswer) == 0){
        printf("Room Match\n");
        matches = matches + 1;
    }
    if (inCharacterList(&(avatar->currentRoom->characterList), character)){
        if (strcmp(character, characterAnswer) == 0){
            printf("Character Match\n");
            matches = matches + 1;
        }
    }
    if (inItemList(&(avatar->currentRoom->itemList), item)){
        printf("Item Match\n");
        matches = matches + 1;
    }

    //Check winning or loosing state
    if (matches == 3){
        printf("Congratulations! You have won the game!\n");
        return 2;
    }
    else{
        clueCount = clueCount + 1;
        if (clueCount >= 10){
            printf("Game Over. You have made your 10th failed attempt. Thanks for playing!\n");
            return 0;
        }
        else{
            printf("Wrong guess. Attempts remaining: %d \n", 10 - clueCount);
            return 1;
        }
    }

}

void generateRandomAnswer(){
     //Get answer Character
    srand(time(0));
    char allCharacters[5][30] = {"Mustard", "White", "Reverend", "Peacock", "Plum"};
    int randNum1 = rand() % 6;
    characterAnswer = allCharacters[randNum1];


    //Get answer Item
    //srand(time(0));
    char allItems[6][30] = {"candlestick", "dagger", "pipe", "revolver", "rope", "wrench"};
    int randNum2 = rand() % 7;
    itemAnswer = allItems[randNum2];

    //Get answer Room
    //srand(time(0));
    char allRooms[9][30] = {"kitchen", "ballroom", "conservatory", "dining", "billiard", "library", "lounge", "hall", "study"};
    int randNum3 = rand() % 10;
    roomAnswer = allRooms[randNum3];
}

void main(){  
    
    printf("Welcome to Clue!\n");

    //To generate Random Answer
    generateRandomAnswer();

    //Intialize rooms
    roomsArray = initializeBoard(); 

    //Initialize an Avatar
    struct Avatar *avatar = (struct Avatar*) malloc(sizeof(struct Avatar));

    //Name: Mrs. "Scarlet", Avatar starts at first room;
    avatar->name = "Scarlet";
    avatar->currentRoom = &roomsArray[0];

    bool lose = true;
    while (lose){
        char line[25];
        printf("\nPlease enter your command: ");
        scanf("%s", line);
        char *userInput = line;

        //GO
        if (strcmp(userInput, "go") == 0){
            
            while (true){

                //TO DO: REMOVE PRINT STATEMENTS
                printf("Check inside while: %s\n", avatar->inventory->itemName);
                char goLine[25];
                printf("\nPlease enter the direction you would like to go: ");
                scanf("%s", goLine);
                printf("Check inventory after input: %s\n", avatar->inventory->itemName);
                char *goInput = goLine; 

                if (!isValidDirection(goInput)){
                    printf("Did not enter valid direction, please retype direction. \n");
                }
                else{
                    go(&avatar, goInput);
                    break;
                }
            }
        }

        //TAKE
        else if (strcmp(userInput, "take") == 0){
            while (true){
                char takeLine[25];
                printf("\nPlease enter the item you would like to take: ");
                scanf("%s", takeLine);
                char *takeInput = takeLine; 

                //If want to exit the take command
                if (strcmp(takeInput, "exit") == 0){
                    break;
                }
                //If itemList in the room is empty, then ask to type another command
                else if (avatar->currentRoom->itemList == NULL){
                    printf("There are no items in this room, please retype command\n");
                    break;
                }
                else if (!isValidItem(takeInput)){
                    printf("Did not enter valid item, please retype item name or type exit to type another command. \n");
                }
                else{
                    bool itemInRoom = take(avatar, takeInput);
                    if (itemInRoom){
                        printf("Item added to inventory\n");
                        break;
                    }
                    else{
                        printf("Item entered was not in room, please retype item name.\n");
                    }
                }
                
            }
        }

        //DROP
        else if (strcmp(userInput, "drop") == 0){
            while(true){
                char dropLine[25];
                printf("\nPlease enter the item you would like to drop: ");
                scanf("%s", dropLine);
                char *dropInput = dropLine; 

                //If want to exit the take command
                if (strcmp(dropInput, "exit") == 0){
                    break;
                }
                //If itemList in the room is empty, then ask to type another command
                else if (avatar->inventory == NULL){
                    printf("There are no items in player's inventory, please retype command\n");
                    break;
                }
                else if (!isValidItem(dropInput)){
                    printf("Did not enter valid item, please retype item name or type exit to type another command. \n");
                }
                else{
                    bool itemInInventory = drop(avatar, dropInput);
                    if (itemInInventory){
                        printf("Item dropped from inventory\n");
                        break;
                    }
                    else{
                        printf("Item entered was not in inventory, please retype item name.\n");
                    }
                }
            }
        }

        //CLUE
        else if (strcmp(userInput, "clue") == 0){
              while (true){
                char charNameInput[25];
                printf("Enter a character name: ");
                scanf("%s", charNameInput);

                char itemNameInput[25];
                printf("\nEnter an item name: ");
                scanf("%s", itemNameInput);

                //If want to exit the clue command
                if (strcmp(charNameInput, "exit") == 0 || strcmp(itemNameInput, "exit") == 0){
                    break;
                }

                else if (!isValidCharacter(charNameInput)){
                    printf("Did not enter valid character name, please retype character name or type 'exit' to type another command. \n");
                }

                else if (!isValidItem(itemNameInput)){
                    printf("Did not enter valid item name, please retype item name or type 'exit' to type another command");
                }

                //Item not present in room's itemList or inventory
                else if(!inItemList(&(avatar->currentRoom->itemList), itemNameInput) && !inItemList(&(avatar->inventory), itemNameInput)){
                    printf("Item entered not in current room or inventory, please retype command. \n");
                    break;
                }

                else{
                    char *characterName = charNameInput;
                    char *itemName = itemNameInput;
                    int clueResult = checkClue(characterName, itemName, avatar, roomsArray);
                    
                    //Won or lost game, update flag and exit game
                    if (clueResult == 0 || clueResult == 2){
                        lose = false;
                        break;
                    }
                    if (clueResult == 1){
                        break;
                    }
                }
            }
        }
        else if(strcmp(userInput, "help") == 0){
            help();
        }
        else if(strcmp(userInput, "look") == 0){
            look(avatar);
        }
        else if (strcmp(userInput, "list") == 0){
            list();
        }
        else if (strcmp(userInput, "inventory") == 0){
            inventory(&avatar);
        }
        else if(strcmp(userInput, "exit") == 0){
            break;
        }
        else{
            printf("\n Wrong command, please check commands by typing help\n");
        }
    }
}



