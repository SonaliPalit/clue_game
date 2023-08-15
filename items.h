#ifndef ITEMS_H
#define ITEMS_H

#include <stdbool.h>
struct ItemNode
{
    char *itemName;
    struct ItemNode *next;
};

void addItem(struct ItemNode **itemList, struct ItemNode *newItem);

bool deleteItem(struct ItemNode **head, char *key);

bool inItemList(struct ItemNode **head, char *key);

#endif