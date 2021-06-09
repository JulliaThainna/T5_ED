#ifndef __VERTICE_H
#define __VERTICE_H

#include "point.h"

typedef void* Vertice;

Vertice createVertice(char* id, float x, float y);

char* verticeGetId(Vertice vertice);

Point verticeGetPoint(Vertice vertice);

float verticeGetX(Vertice vertice);

float verticeGetY(Vertice vertice);

#endif