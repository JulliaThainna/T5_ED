#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "vertice.h"
#include "point.h"

typedef struct{
    char nome[100];
    Point point;
} VerticeStruct;

Vertice createVertice(char* nome, float x, float y){
    VerticeStruct* vert = (VerticeStruct*)malloc(sizeof(VerticeStruct));
    strcpy(vert->nome, nome);
    vert->point = criaPoint(x, y);
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

void desenhaVerticeSvg(Vertice vertice, char* corVertice, FILE* fileSvg){
    fprintf(fileSvg, "\n\t<circle cx=\"%f\" cy=\"%f\" r=\"10\" stroke=\"%s\" fill=\"white\" stroke-width=\"0.5\" />", verticeGetX(vertice), verticeGetY(vertice), corVertice);
    fprintf(fileSvg, "\n\t<text x=\"%f\" y=\"%f\" text-anchor=\"middle\" font-size=\"0.13em\">%s</text>", verticeGetX(vertice), verticeGetY(vertice), verticeGetNome(vertice));
}