#ifndef __QRY5_H
#define __QRY5_H

#include "hashTable.h"
#include "point.h"

int indiceRegistrador(char* r);

void mInt(HashTable* ht, Point* registrador, char* r, char* cpf);
void eInt(HashTable* ht, Point* registrador, char* r, char* cep, char face, int num);
void xy(Point* registrador, char* r, float x, float y);

#endif