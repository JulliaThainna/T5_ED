#ifndef __QRY5_H
#define __QRY5_H

#include "graph.h"
#include "hashTable.h"
#include "point.h"

int indiceRegistrador(char* r);

void mInt(QuadTree* qt, HashTable* ht, Point* registrador, char* r, char* cpf);
void eInt(QuadTree* qt, HashTable* ht, Point* registrador, char* r, char* cep, char face, int num);
void gInt(QuadTree* qt, Point* registrador, char* r, char* id);
void xy(QuadTree* qt, Point* registrador, char* r, float x, float y);
Graph ccv(Graph graphVia, char* sfx, char* dirSaida, char* nomeGeoSemExtensao, char* nomeQrySemExtensao);

#endif