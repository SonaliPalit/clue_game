#ifndef CHARACTER_H
#define CHARACTER_H

#include <stdbool.h>

struct CharacterNode
{
    char *characterName;
    struct CharacterNode *next;
};

void addCharacter(struct CharacterNode **head, struct CharacterNode *newCharacter);

bool inCharacterList(struct CharacterNode **head, char *key);

bool deleteCharacter(struct CharacterNode **head, char *key);



#endif