#ifndef __ARESTA_H
#define __ARESTA_H

#include "graph.h"

typedef void* Aresta;

Aresta createAresta(char* nome, char* ldir, char* lesq, float cmp, float vm);
char* arestaGetNome(Aresta aresta);
char* arestaGetNomeVerticeInicial(Aresta aresta);
char* arestaGetNomeVerticeFinal(Aresta aresta);
char* arestaGetLdir(Aresta aresta);
char* arestaGetLesq(Aresta aresta);
float arestaGetCmp(Aresta aresta);
float arestaGetVm(Aresta aresta);
float arestaGetTempo(Aresta aresta);

#endif



