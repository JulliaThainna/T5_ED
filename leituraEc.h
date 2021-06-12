#ifndef __LEITURAEC_H
#define __LEITURAEC_H

#include "quadTree.h"
#include "hashTable.h"

/*
Lê os comando requisitados no arquivo EC
PRE: As QuadTrees, as hashtables e o diretorio do arquivo EC
*/
void readEc(QuadTree* qt, HashTable* ht, char* dirEc);

#endif
