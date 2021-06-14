#ifndef __GRAFO_H
#define __GRAFO_H

#include "doublyLinkedList.h"
#include "aresta.h"
#include "vertice.h"

typedef void* Graph;
typedef void* AdjascentList;

Graph createGraph();
Vertice graphGetVertice(AdjascentList adjascentList);
DoublyLinkedList graphGetArestas(AdjascentList adjascentList);
AdjascentList graphGetAdjascentList(Graph graph, char* id);
void adicionaVertice(Graph graph, Vertice vertice);
void adicionaAresta(Graph graph, Aresta aresta);
void desalocaAdjascentList(AdjascentList adjascentList);
void desalocaGrafo(Graph graph);
void desenhaArestaSvg(Graph graph, AdjascentList adjascentList, Aresta aresta, char* corAresta, FILE *fileSvg);
void desenhaGrafoSvg(Graph graph, FILE *fileSvg, char* corAresta, char* corVertice);
Graph convertToUndirectedGraph(Graph directedGraph);
Graph primAlgorithm(Graph graph);
Graph dijkstraAlgorithm(Graph graph, char* nomeVI, char* nomeVF, float* distTotal, float getPeso(Aresta aresta));

#endif