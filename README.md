# clue_game
Welcome to Clue!


Code can be compiled using the command - gcc adventure.c avatar.c rooms.c items.c character.c -o adventure 


The game Board can be visualized as such :

[R0, R1, R2
 R3, R4, R5
 R6, R7, R8]
where R0 - R8 are the 9 Rooms initialized randomly. 

Project specifications:

1. Game has 9 rooms that are connected to each other using pointers (see function initializeRooms() in rooms.c)
The rooms, items and characters are randomly initialized. (see randomize() in rooms.c)

2. Game contains 6 items = "candlestick, dagger, pipe, revolver, rope, wrench"
                 5 characters = "Mustard, White, Reverend, Peacock, Plum"
                 9 rooms = "kitchen, ballroom, conservatory, dining, billiard, library, lounge, hall, study"
    The player/avatar is named "Scarlett" 

3. Randomly generate a room, item and character as Answer (see generateRandomAnswer() in adventure.c)

4. Each Room struct has a linked list of items in room called itemList (see rooms.h)

5. The avatar/player has an inventory of items called inventory (see avatar.h)

6. Commands:
           1. "help" - look up commands (see help() adventure.c)
           2. "list" - list items, characters, rooms  (see list() adventure.c)
           3. "look" - see which room avatar is in, the items and characters in room.  (see look() adventure.c)
           4. "go" - to allow characters to go to adjacent rooms, if they exist. (see go() in avatar.c)
                   - player can retype direction is not valid (see adventure.c)
           5. "take" - allows player to take an item from the room and add to thier inventory (see take() in avatar.c)
                     - can retype itemName if not valid (see adventure.c)

           6. "drop" - to drop item from player's inventory to room (see drop() in avatar.c)
                     - can retype itemName if not valid (see adventure.c)

           7. "inventory" - to look up player's inventory (see inventory() in adventure.c)

           8. "clue" - player can type character name and item name that is thier guess of the answer (see clue() in adventure.c)
                     - Players can retype character name is name entered is not valid (see adventure.c)
                     - Players can retype character name is name entered is not valid (see adventure.c)
                     

           9. Players can retype commands if not one of the above
    
7. After getting "clue" command:
                       - Move character entered to the same room as avatar (see moveCharacter() in adventure.c)
                       - If the item entered is same as the item answer, prints "item match" (see clue in adventure.c)
                       - If the character entered is same as the character answer, prints "item match" see clue() in adventure.c)
                       - If the room avatar is in is same as room answer, prints "room match" see clue() in adventure.c)
                       - If all 3 entered are same answer, game won. (see clue() in adventure.c))
                       - If 10 clue guesses have beem made, game over. (see clue() in adventure.c)

8. There are 5 .c files:
                      1. rooms.c - functions inintialize board 
                      2. items.c - functions to addItem, deleteItem and check if item in list
                      3. character.c - functions to addCharacter, deleteCharacter and check if character in list
                      4. avatar.c - funtions to go, take and drop 
                      5. adventure.c - main driver program to take in user input and call all funtions.

9. There are 4 header files:
                      1. rooms.h - contains Room struct with name, direction pointers, itemList, characterList. Also function definitions
                      2. items.h - contains ItemNode struct with itemName, next pointer. Also function definitions
                      3. character.h - contains CharacterNode struct with characterName, next pointer. Also function definitions
                      4. avatar.h - contains Avatar struct with name, currentRoom, inventory. Also function definitions
