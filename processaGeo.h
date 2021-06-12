#ifndef __PROCESSAGEO_H
#define __PROCESSAGEO_H

#include "quadTree.h"
#include "doublyLinkedList.h"
#include "densidadeDemografica.h"
#include "quadra.h"
#include "hashTable.h"
#include "point.h"


void instanciaQts(QuadTree* quadTrees);
//realiza o comando criaQt(getId) para todas as arvores alocadas menos pra postoSaude

void convertToQuadTrees(QuadTree* quadTrees, HashTable* ht, DoublyLinkedList* listas);
//Chama a função DoublyLinkedListsToQuadTrees,, que chama DoublyLinkedListToQuadTree para todas as listas, que chama convexHull para todas as listas "recursivamente"

QuadTree DoublyLinkedListToQuadTree(DoublyLinkedList l, QuadTree qt, Point (*getPoint)(void*), void (*swapInfo)(void*,void*));
//Realizar o convexHull com a lista até sobrar três ou menos elementos
//Colocar elementos numa Stack até chegar nessa condição
//Enquanto stackIsEmpty == 0 insertQt


/*
    Define um valor de DD para cada quadra completamente dentro de uma densidade
  *  PRE: quadtree de quadras e lista de densidades
    POS: dd das quadras alterados
*/
void defineQuadraDensidadeDemografica(QuadTree quadraQt, DoublyLinkedList densidadesDemograficas);

/*
    Define uma densidade para uma unica quadra
    PRE: quadra e lista de densidades
    POS: dd da quadra alterado
*/
void quadraDefineDensidade(Quadra quadra, DoublyLinkedList dds);

/*
    Verifica se a quadra está completamente dentro da densidade demografica em questão, se estiver, altera DD
    PRE: quadra e densidade
    POS: dd do quadra alterado
*/
void verificaDensidade(Quadra q, DensidadeDemografica dd);

#endif