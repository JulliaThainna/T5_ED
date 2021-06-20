#ifndef __PESSOA_H_
#define __PESSOA_H_

#include "graph.h"
#include "point.h"
#include "doublyLinkedList.h"

typedef void* Path;

/*
    Cria uma variável path para poder desenhar
    o retorno de um dijkstra
*/
Path criaPath(Graph graph, Point pInicial, Point pFinal, DoublyLinkedList nomesVerticesList, float cmp, float duration, char* cor, int idPInt, int flag);

/*
    Desenha o path e um circulo com animação no svg
*/
void desenhaPathSvg(Path path, void* fileSvg);

#endif