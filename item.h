#ifndef __ITEM_H
#define __ITEM_H

#include "doublyLinkedList.h"

typedef void* Item;

/*
Cria um item com chave e valor e retorna o item
*/
Item createItem(char* chave, Info valor);

/*
Aloca os espaços pra chave e valor e retorna o item mas não
coloca nada no conteudo desses campos
*/
Item alocarItem(int tamCh, int tamRec);

/*
    Retorna a chave do item
*/
char* itemGetKey(Item item);

/*
    Retorna o valor do item
*/
Info itemGetValue(Item item);

/*
    Desaloca o valor do item
*/
void itemDesalocaValue(Item item);

/*
    Desaloca o item
*/
void removeItem(Item item);

#endif