#ifndef AVATAR_H
#define AVATAR_H

#include <stdbool.h>
#include <string.h>


struct Avatar
{
    char *name;
    struct ItemNode *inventory;
    struct Room *currentRoom;
};

void go(struct Avatar **avatar, char *direction);

bool take(struct Avatar *avatar, char *itemName);

bool drop(struct Avatar *avatar, char *itemName);

#endif
