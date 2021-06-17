#ifndef __ITEM_H
#define __ITEM_H

#include "doublyLinkedList.h"

typedef void* Item;
Item createItem(char chave[], Info valor);
Item alocarItem(int tamCh, int tamRec);
char* itemGetKey(Item item);
Info itemGetValue(Item item);
void itemDesalocaValue(Item item);
void removeItem(Item item);

#endif