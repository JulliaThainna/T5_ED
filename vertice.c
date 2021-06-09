#include <stdio.h>
#include <stdlib.h>

#include "vertice.h"
#include "point.h"


typedef struct{
    char nome[100];
    Point point;
}VerticeStruct;

Vertice createVertice(char* nome, float x, float y){
    VerticeStruct* vert = (VerticeStruct*)malloc(sizeof(VerticeStruct));
    strcpy(vert->nome, nome);
    vert->point = createPoint(x, y);
    return vert;
}

char* verticeGetNome(Vertice vertice){
    VerticeStruct* vert = (VerticeStruct*)vertice;
    return vert->nome;
}

Point verticeGetPoint(Vertice vertice){
    VerticeStruct* vert = (VerticeStruct*)vertice;
    return vert->point;
}

float verticeGetX(Vertice vertice){
    VerticeStruct* vert = (VerticeStruct*)vertice;
    return getPointX(vert->point);
}

float verticeGetY(Vertice vertice){
    VerticeStruct* vert = (VerticeStruct*)vertice;
    return getPointY(vert->point);
}
