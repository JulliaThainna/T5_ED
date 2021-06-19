#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "circulo.h"
#include "point.h"

typedef struct{
    char id[100];
    float r;
    Point point;
    char cb[220], cp[220], sw[220];
}CirculoStruct;


//Create
Circulo criaCirculo(char* id, float x, float y, float r, char* cb, char* cp, char* sw){
    CirculoStruct* circ = (CirculoStruct*)malloc(sizeof(CirculoStruct));
    Point point = criaPoint(x, y);
    strcpy(circ->id, id);
    circ->point = point;
    circ->r = r;
    strcpy(circ->cb, cb);
    strcpy(circ->cp, cp);
    strcpy(circ->sw, sw);
    return circ;
}

//Setters
void circuloSetId(Circulo circulo, char* id){
    CirculoStruct* circ = (CirculoStruct*)circulo;
    strcpy(circ->id, id);
}

void circuloSetX(Circulo circulo, float x){
    CirculoStruct* circ = (CirculoStruct*)circulo;
    setPointX(circ->point, x);
}

void circuloSetY(Circulo circulo, float y){
    CirculoStruct* circ = (CirculoStruct*)circulo;
    setPointY(circ->point, y);
}

void circuloSetRaio(Circulo circulo, float r){
    CirculoStruct* circ = (CirculoStruct*)circulo;
    circ->r = r;
}

void circuloSetCorBorda(Circulo circulo, char* cb){
    CirculoStruct* circ = (CirculoStruct*)circulo;
    strcpy(circ->cb, cb);
}

void circuloSetCorPreenchimento(Circulo circulo, char* cp){
    CirculoStruct* circ = (CirculoStruct*)circulo;
    strcpy(circ->cp, cp);
}

void circuloSetPoint(Circulo circulo, Point point){
    CirculoStruct* circ = (CirculoStruct*)circulo;
    free(circ->point);
    circ->point = point;
}

void circuloSetEspessura(Circulo circulo, char* sw){
    CirculoStruct* circ = (CirculoStruct*)circulo;
    strcpy(circ->sw, sw);
}

//Getters
char* circuloGetId(Circulo circulo){
    CirculoStruct* circ = (CirculoStruct*)circulo;
    return circ->id;
}

float circuloGetX(Circulo circulo){
    CirculoStruct* circ = (CirculoStruct*)circulo;
    return getPointX(circ->point);
}

float circuloGetY(Circulo circulo){
    CirculoStruct* circ = (CirculoStruct*)circulo;
    return getPointY(circ->point);
}

float circuloGetRaio(Circulo circulo){
    CirculoStruct* circ = (CirculoStruct*)circulo;
    return circ->r;
}

char* circuloGetCorBorda(Circulo circulo){
    CirculoStruct* circ = (CirculoStruct*)circulo;
    return circ->cb;
}

char* circuloGetCorPreenchimento(Circulo circulo){
    CirculoStruct* circ = (CirculoStruct*)circulo;
    return circ->cp;
}

Point circuloGetPoint(Circulo circulo){
    CirculoStruct* circ = (CirculoStruct*)circulo;
    return circ->point;
}

char* circuloGetEspessura(Circulo circulo){
    CirculoStruct* circ = (CirculoStruct*)circulo;
    return circ->sw;
}

void circuloSwap(Circulo c1, Circulo c2){
    CirculoStruct* a = (CirculoStruct*) c1;
    CirculoStruct* b = (CirculoStruct*) c2;
    CirculoStruct temp = *a;
    *a = *b;
    *b = temp;
}

void circuloDesenhaSvgGeo(Circulo circulo, void* fileSvg){
    if(strcmp(circuloGetId(circulo), "-2") == 0){
        fprintf((FILE*)fileSvg, "\n\t<circle cx=\"%f\" cy=\"%f\" r=\"%f\" style=\"stroke:%s;fill:%s;stroke-width:%s\" fill-opacity= \"0.5\"/>", circuloGetX(circulo), circuloGetY(circulo), circuloGetRaio(circulo), circuloGetCorBorda(circulo), circuloGetCorPreenchimento(circulo), circuloGetEspessura(circulo));
        return;
    }
    fprintf((FILE*)fileSvg, "\n\t<circle cx=\"%f\" cy=\"%f\" r=\"%f\" style=\"stroke:%s;fill:%s;stroke-width:%s\"/>", circuloGetX(circulo), circuloGetY(circulo), circuloGetRaio(circulo), circuloGetCorBorda(circulo), circuloGetCorPreenchimento(circulo), circuloGetEspessura(circulo));
}