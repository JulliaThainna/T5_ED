#ifndef __PESSOA_H_
#define __PESSOA_H_

#include "graph.h"
#include "point.h"
#include "doublyLinkedList.h"

typedef void* Path;

Path criaPath(Graph graph, Point pInicial, Point pFinal, DoublyLinkedList nomesVerticesList, float cmp, float duration, char* cor, int idPInt, int flag);

void desenhaPathSvg(Path path, void* fileSvg);

#endif