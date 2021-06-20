#ifndef __HASHFILEUTILITARIO_H
#define __HASHFILEUTILITARIO_H

#include "quadTree.h"
#include "hashTable.h"

/*
Gera os arquivos .dat com as informações do trabalho no estado que estão
PRE: QuadTrees qts, Hashtables hts e o nome base do arquivo
POS: Arquivos .dat
*/
void generateDatFiles(QuadTree* qt, HashTable* ht, char* arqDatK);

/*
Carrega os arquivos .dat com as informações que estão neles
PRE: QuadTrees qts, Hashtables hts e o nome base do arquivo
POS: Conteudo dos arquivos .dat nas hashtables e quadtrees respectivas 
*/
void loadDatFiles(QuadTree* qt, HashTable* ht, char* arqDatK);

#endif