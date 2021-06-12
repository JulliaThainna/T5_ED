#ifndef __SORTING_H
#define __SORTING_H

#include "localCasos.h"
#include "doublyLinkedList.h"
#include "point.h"

/*
    Algoritmo shellSorting
    PRE: vetor de elementos InfoSoc para ser ordenado e o tamanho no vetor
    POS: 
*/
void shellSorting(DoublyLinkedList lista, float x, float y);

/*
    Função que calcula a área de um poligono qualquer
    PRE: Lista de vertices do poligono
    POS: Área
*/
float obterArea(DoublyLinkedList l);

/*
    Realiza o algoritmo de ordenação quickSort com uma doublyLinkedList
    PRE: Lista l, primeiro e ultimo node, função para pegar o ponto do elemento, função para trocar dois elementos do mesmo tipo de lugar
    POS: A lista passada como parâmetro é alterada
*/
void quickSortDoublyLinkedList(DoublyLinkedList l, Node primeiro, Node ultimo, Point (*getPoint)(Info), void (*swapInfo)(Info, Info));

/*
    Partição para ver os próximos pontos que farão parte do convexHull
    PRE: lista, primeiro e ultimo note, função para pegar o ponto do elemento, função para trocar dois elementos do mesmo tipo de lugar
    POS: node que será inserido
    
*/
Node partition(DoublyLinkedList l, Node primeiro, Node ultimo, Point (*getpoint)(Info), void (*swapInfo)(Info, Info));

/*
    Compara 3 pontos para ver se etá dentro do poligono ou não
    PRE: pontos
    POS: 0 se não estiver e 1 se estiver
*/
int comparar(Point a, Point b, Point c);

/*
    Calcula a area formada pelos três pontos para ver a orientação
    PRE: pontos
    POS: -1 antihorario 0 linear 1 horário
*/
int orientacao(Point a, Point b, Point c);


#endif
