#ifndef __GRAFO_H
#define __GRAFO_H

#include "doublyLinkedList.h"
#include "aresta.h"
#include "vertice.h"

typedef void* Graph;
typedef void* AdjascentList;


/*
Essa função aloca um novo grafo
PRE: Nada
POS: Variável grafo
*/
Graph createGraph();

/*Essa função retorna o Vertice de uma lista de adjascencia.
Cada lista de adjascencia possui um vertice e uma lista de arestas que saem desse vertice
PRE: uma lista de adjascencia;
POS: retorna o atributo 
*/
Vertice graphGetVertice(AdjascentList adjascentList);

/*

*/
DoublyLinkedList graphGetArestas(AdjascentList adjascentList);

/*
Essa função retorna uma AdjascentList com base no nome do vertice.
PRE: Variável Grafo e o char* nomeVertice do vertice
POS: Lista de adjascencia caso exista o vertice e NULL caso não exista
*/
AdjascentList graphGetAdjascentList(Graph graph, char* id);

/*
Adiciona um novo vertice no grafo. Faz isso através da AdjascentList
PRE: Variável Grafo e um vertice definido
POS: Não há retorno
*/
void adicionaVertice(Graph graph, Vertice vertice);

/*
Essa função adiciona uma nova aresta partindo de um dos vertices. Como o vertice final e o vertice inicial da aresta é definido na aresta, não há necessidade de passa-los
como valores separados para a função. Caso o usuário passe uma aresta NULL a função retornará.
PRE: Variável Grafo e variável Aresta
POS: Não há retorno
*/
void adicionaAresta(Graph graph, Aresta aresta);

/*
Essa função desaloca todas as arestas de uma lista de adjascencia. Em outras palavras ela deleta todas as arestas partindo de determinado vertice. Também desaloca o vertice.
PRE: Lista de adjascencia
POS: Não há retorno
*/
void desalocaAdjascentList(AdjascentList adjascentList);

/*
Essa função desaloca todas as AdjascentList (Vertices) que existirem dentro do grafo.
(ESSA FUNÇÃO NÃO DESALOCA AS ARESTAS. USAR ELA SEM DESALOCAR AS ARESTAS IRÁ CAUSA MEMORY LEAK!!!)
PRE: Variável Grafo
POS: Não há retorno
*/
void desalocaGrafo(Graph graph);

/*
Essa função desenha uma única aresta no SVG.
PRE: Variável Grafo, variável AdjascentList, uma Aresta e o FILE* em que o svg será gerado
POS: Não há retorno
*/
void desenhaArestaSvg(Graph graph, AdjascentList adjascentList, Aresta aresta, char* corAresta, FILE* fileSvg);

/*
Essa função desenha um grafo num FILE com as cores determinadas
PRE: Variável grafo, um FILE*, a cor da aresta e do vertice
POS: Nada
*/
void desenhaGrafoSvg(Graph graph, FILE* fileSvg, char* corAresta, char* corVertice);

/*
Essa função recebe um grafo direcionado e retorna um novo grafo não-direcionado
PRE: Variável grafo direcionado
POS: Variável grafo não-direcionado
*/
Graph convertToUndirectedGraph(Graph directedGraph);

/*
Retira do grafo os vertices que não possuem nenhuma aresta partindo ou indo pra ele. Altera o original.
PRE: Variável grafo
POS: Variável grafo
*/
Graph removeVerticeDesconexo(Graph graph);

/*
O algoritmo de prim faz uma arvore geradora mínima
PRE: Grafo grafo
POS: Grafo arvoreGeradoraMinima
*/
Graph primAlgorithm(Graph graph);

/*
Essa função realiza o algoritmo de Dijkstra e retorna uma lista de ids de vertices entre dois vertices
PRE: Variável grafo, idVerticeInicial, idVerticeFinal, um pointer para salvar a distancia total e a função para pegar o peso de uma aresta
POS: Uma lista de strings com ids dos vertices do ponto final até o ponto inicial 
*/
DoublyLinkedList dijkstraAlgorithm(Graph graph, char* nomeVI, char* nomeVF, float* distTotal, float getPeso(Aresta aresta));

#endif