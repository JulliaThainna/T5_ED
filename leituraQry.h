#ifndef LEITURAQRY__H_
#define LEITURAQRY__H_

#include "graph.h"
#include "hashTable.h"
#include "quadTree.h"
#include "corPadrao.h"

/*
Lê as consultas requisitadas no arquivo QRY
Pré: As listas e o diretório do arquivo QRY
*/
void readQry(QuadTree *qt, HashTable *ht, Graph graph, char *dirQry, char *dirTxt, char *dirSaida, char *nomeGeoSemExtensao, char *nomeQrySemExtensao, char* dirSaidaGeoQry);

/*
Por conta dos casos de testes diferenciados, essa função garante que a face é sempre um caractere ("N", "S", "L", "O")
*/
char faceToChar(char* face);
#endif
