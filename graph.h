#ifndef __GRAFO_H
#define __GRAFO_H

#include "doublyLinkedList.h"
#include "aresta.h"
#include "vertice.h"

typedef void *Graph;
typedef void *AdjascentList;

Graph createGraph();
Vertice graphGetVertice(AdjascentList adjascentList);
DoublyLinkedList graphGetArestas(AdjascentList adjascentList);
AdjascentList graphGetAdjascentList(Graph graph, char *id);
void adicionaVertice(Graph graph, Vertice vertice);
void adicionaAresta(Graph graph, Aresta aresta);
void desalocaAdjascentList(AdjascentList adjascentList);
void desalocaGrafo(Graph graph);
void desenhaArestaSvg(Graph graph, AdjascentList adjascentList, Aresta aresta, FILE *fileSvg);
void desenhaGrafoSvg(Graph graph, FILE *fileSvg);
Graph primAlgorithm(Graph graph);

#endif