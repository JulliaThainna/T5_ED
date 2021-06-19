#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "retangulo.h"
#include "point.h"

typedef struct{
    int tracejado;
    char id[100];
    Point point;
    float w, h;
    char cb[220], cp[220], sw[220];
}RetanguloStruct;


//Create
Retangulo criaRetangulo(char* id, int tracejado, float x, float y, float w, float h, char* cb, char* cp, char* sw){
    RetanguloStruct* ret = (RetanguloStruct*)malloc(sizeof(RetanguloStruct));
    Point point = criaPoint(x, y);
    ret->point = point;
    strcpy(ret->id, id);
    ret->tracejado = tracejado;
    ret->w = w;
    ret->h = h;
    strcpy(ret->cb, cb);
    strcpy(ret->cp, cp);
    strcpy(ret->sw, sw);
    return ret;
}

//Setters
void retanguloSetId(Retangulo retangulo, char* id){
    RetanguloStruct* ret = (RetanguloStruct*)retangulo;
    strcpy(ret->id, id);
}

void retanguloSetTracejado(Retangulo retangulo, int tracejado){
    RetanguloStruct* ret = (RetanguloStruct*)retangulo;
    ret->tracejado = tracejado;
}

void retanguloSetX(Retangulo retangulo, float x){
    RetanguloStruct* ret = (RetanguloStruct*)retangulo;
    setPointX(ret->point, x);
}

void retanguloSetY(Retangulo retangulo, float y){
    RetanguloStruct* ret = (RetanguloStruct*)retangulo;
    setPointY(ret->point, y);
}

void retanguloSetWidth(Retangulo retangulo, float w){
    RetanguloStruct* ret = (RetanguloStruct*)retangulo;
    ret->w = w;
}

void retanguloSetHeight(Retangulo retangulo, float h){
    RetanguloStruct* ret = (RetanguloStruct*)retangulo;
    ret->h = h;
}

void retanguloSetCorBorda(Retangulo retangulo, char* cb){
    RetanguloStruct* ret = (RetanguloStruct*)retangulo;
    strcpy(ret->cb, cb);
}

void retanguloSetCorPreenchimento(Retangulo retangulo, char* cp){
    RetanguloStruct* ret = (RetanguloStruct*)retangulo;
    strcpy(ret->cp, cp);
}

void retanguloSetPoint(Retangulo retangulo, Point point){
    RetanguloStruct* ret = (RetanguloStruct*)retangulo;
    free(ret->point);
    ret->point = point;
}

void retanguloSetEspessura(Retangulo retangulo, char* sw){
    RetanguloStruct* ret = (RetanguloStruct*)retangulo;
    strcpy(ret->sw, sw);
}

//Getters
char* retanguloGetId(Retangulo retangulo){
    RetanguloStruct* ret = (RetanguloStruct*)retangulo;
    return ret->id;
}

int retanguloGetTracejado(Retangulo retangulo){
    RetanguloStruct* ret = (RetanguloStruct*)retangulo;
    return ret->tracejado;
}

float retanguloGetX(Retangulo retangulo){
    RetanguloStruct* ret = (RetanguloStruct*)retangulo;
    return getPointX(ret->point);
}

float retanguloGetY(Retangulo retangulo){
    RetanguloStruct* ret = (RetanguloStruct*)retangulo;
    return getPointY(ret->point);
}

float retanguloGetWidth(Retangulo retangulo){
    RetanguloStruct* ret = (RetanguloStruct*)retangulo;
    return ret->w;
}

float retanguloGetHeight(Retangulo retangulo){
    RetanguloStruct* ret = (RetanguloStruct*)retangulo;
    return ret->h;
}

char* retanguloGetCorBorda(Retangulo retangulo){
    RetanguloStruct* ret = (RetanguloStruct*)retangulo;
    return ret->cb;
}

char* retanguloGetCorPreenchimento(Retangulo retangulo){
    RetanguloStruct* ret = (RetanguloStruct*)retangulo;
    return ret->cp;
}

Point retanguloGetPoint(Retangulo retangulo){
    RetanguloStruct* ret = (RetanguloStruct*)retangulo;
    return ret->point;
}

char* retanguloGetEspessura(Retangulo retangulo){
    RetanguloStruct* ret = (RetanguloStruct*)retangulo;
    return ret->sw;
}

void retanguloSwap(Retangulo r1, Retangulo r2){
    RetanguloStruct* a = (RetanguloStruct*) r1;
    RetanguloStruct* b = (RetanguloStruct*) r2;
    RetanguloStruct temp = *a;
    *a = *b;
    *b = temp;
}

void retanguloDesenhaSvgGeo(Retangulo retangulo, void* fileSvg){
    fprintf((FILE*)fileSvg, "\n\t<rect x=\"%f\" y=\"%f\" width=\"%f\" height=\"%f\" style=\"stroke:%s;fill:%s;stroke-widht:%s\"/>", retanguloGetX(retangulo), retanguloGetY(retangulo), retanguloGetWidth(retangulo), retanguloGetHeight(retangulo), retanguloGetCorBorda(retangulo), retanguloGetCorPreenchimento(retangulo), retanguloGetEspessura(retangulo)); 
}

void retanguloDesenhaSvgQry(Retangulo retangulo, void* fileSvg){
    if(retanguloGetTracejado(retangulo) == 1){
        fprintf((FILE*)fileSvg, "\n\t<rect x=\"%f\" y=\"%f\" width=\"%f\" height=\"%f\" style=\"stroke:%s;fill:none;stroke-widht:%s; stroke-dasharray: 3 3 3;\" fill-opacity=\"0.0\"/>", retanguloGetX(retangulo), retanguloGetY(retangulo), retanguloGetWidth(retangulo), retanguloGetHeight(retangulo), retanguloGetCorBorda(retangulo), retanguloGetEspessura(retangulo));
    }
    else{
        fprintf((FILE*)fileSvg, "\n\t<rect x=\"%f\" y=\"%f\" width=\"%f\" height=\"%f\" style=\"stroke:%s;fill:%s;stroke-widht:%s\"/>", retanguloGetX(retangulo), retanguloGetY(retangulo), retanguloGetWidth(retangulo), retanguloGetHeight(retangulo), retanguloGetCorBorda(retangulo), retanguloGetCorPreenchimento(retangulo), retanguloGetEspessura(retangulo));
    }
}