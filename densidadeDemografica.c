#include <stdio.h>
#include <stdlib.h>

#include "point.h"
#include "densidadeDemografica.h"

typedef struct{
    Point point;
    float w, h, d;
}DensidadeDemograficaStruct;


//Create
DensidadeDemografica criaDensidadeDemografica(float x, float y, float w, float h, float d){
    DensidadeDemograficaStruct* dd = (DensidadeDemograficaStruct*)malloc(sizeof(DensidadeDemograficaStruct));
    Point point = criaPoint(x, y);
    dd->point = point;
    dd->w = w;
    dd->h = h;
    dd->d = d;
    return dd;
}

//Setters
void densidadeDemograficaSetX(DensidadeDemografica densidade, float x){
    DensidadeDemograficaStruct* dd = (DensidadeDemograficaStruct*)densidade;
    setPointX(dd->point, x);
}

void densidadeDemograficaSetY(DensidadeDemografica densidade, float y){
    DensidadeDemograficaStruct* dd = (DensidadeDemograficaStruct*)densidade;
    setPointY(dd->point, y);
}

void densidadeDemograficaSetWidth(DensidadeDemografica densidade, float w){
    DensidadeDemograficaStruct* dd = (DensidadeDemograficaStruct*)densidade;
    dd->w = w;
}

void densidadeDemograficaSetHeight(DensidadeDemografica densidade, float h){
    DensidadeDemograficaStruct* dd = (DensidadeDemograficaStruct*)densidade;
    dd->h = h;
}

void densidadeDemograficaSetDensidadeDemografica(DensidadeDemografica densidade, float d){
    DensidadeDemograficaStruct* dd = (DensidadeDemograficaStruct*)densidade;
    dd->d = d;
}

void densidadeDemograficaSetPoint(DensidadeDemografica densidade, Point point){
    DensidadeDemograficaStruct* dd = (DensidadeDemograficaStruct*)densidade;
    free(dd->point);
    dd->point = point;
}

//Getters
float densidadeDemograficaGetX(DensidadeDemografica densidade){
    DensidadeDemograficaStruct* dd = (DensidadeDemograficaStruct*)densidade;
    return getPointX(dd->point);
}

float densidadeDemograficaGetY(DensidadeDemografica densidade){
    DensidadeDemograficaStruct* dd = (DensidadeDemograficaStruct*)densidade;
    return getPointY(dd->point);
}

float densidadeDemograficaGetWidth(DensidadeDemografica densidade){
    DensidadeDemograficaStruct* dd = (DensidadeDemograficaStruct*)densidade;
    return dd->w;
}

float densidadeDemograficaGetHeight(DensidadeDemografica densidade){
    DensidadeDemograficaStruct* dd = (DensidadeDemograficaStruct*)densidade;
    return dd->h;
}

float densidadeDemograficaGetDensidadeDemografica(DensidadeDemografica densidade){
    DensidadeDemograficaStruct* dd = (DensidadeDemograficaStruct*)densidade;
    return dd->d;
}

Point densidadeDemograficaGetPoint(DensidadeDemografica densidade){
    DensidadeDemograficaStruct* dd = (DensidadeDemograficaStruct*)densidade;
    return dd->point;
}