#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "texto.h"
#include "point.h"

typedef struct{
    char id[100];
    int size;
    Point point;
    char* txt;
    char cb[220], cp[220];
}TextoStruct;


//Create
Texto criaTexto(char* id, int size, float x, float y, char* txt, char* cb, char* cp){
    TextoStruct* tex = (TextoStruct*)malloc(sizeof(TextoStruct));
    Point point = criaPoint(x, y);
    tex->point = point;
    strcpy(tex->id, id);
    strcpy(tex->cb, cb);
    strcpy(tex->cp, cp);
    tex->txt = (char*) malloc(sizeof(char) * (size + 1));
    strcpy(tex->txt, txt);
    return tex;
}


//Setters
void textoSetId(Texto texto, char* id){
    TextoStruct* tex = (TextoStruct*)texto;
    strcpy(tex->id, id);
}

void textoSetX(Texto texto, float x){
    TextoStruct* tex = (TextoStruct*)texto;
    setPointX(tex->point, x);
}

void textoSetY(Texto texto, float y){
    TextoStruct* tex = (TextoStruct*)texto;
    setPointY(tex->point, y);
}

void textoSetTexto(Texto texto, char* txt, int size){
    TextoStruct* tex = (TextoStruct*) texto;

    free(tex->txt);
    tex->txt = (char*) malloc(sizeof(char) * size);
    strcpy(tex->txt, txt);
}

void textoSetCorBorda(Texto texto, char* cb){
    TextoStruct* tex = (TextoStruct*)texto;
    strcpy(tex->cb, cb);
}

void textoSetCorPreenchimento(Texto texto, char* cp){
    TextoStruct* tex = (TextoStruct*)texto;
    strcpy(tex->cp, cp);
}

void textoSetPoint(Texto texto, Point point){
    TextoStruct* tex = (TextoStruct*)texto;
    free(tex->point);
    tex->point = point;
}


//Getters
char* textoGetId(Texto texto){
    TextoStruct* tex = (TextoStruct*)texto;
    return tex->id;
}

float textoGetX(Texto texto){
    TextoStruct* tex = (TextoStruct*)texto;
    return getPointX(tex->point);
}

float textoGetY(Texto texto){
    TextoStruct* tex = (TextoStruct*)texto;
    return getPointY(tex->point);
}

char* textoGetTexto(Texto texto){
    TextoStruct* tex = (TextoStruct*)texto;
    return tex->txt;   
}

char* textoGetCorBorda(Texto texto){
    TextoStruct* tex = (TextoStruct*)texto;
    return tex->cb;
}

char* textoGetCorPreenchimento(Texto texto){
    TextoStruct* tex = (TextoStruct*)texto;
    return tex->cp;
}

Point textoGetPoint(Texto texto){
    TextoStruct* tex = (TextoStruct*)texto;
    return tex->point;
}

//Desaloca texto
void textoDeletaTxt(Texto texto){
    TextoStruct* tex = (TextoStruct*)texto;
    free(tex->txt);
}

void textoSwap(Texto t1, Texto t2){
    TextoStruct* a = (TextoStruct*) t1;
    TextoStruct* b = (TextoStruct*) t2;
    TextoStruct temp = *a;
    *a = *b;
    *b = temp;
}

void textoDesenhaSvgGeo(Texto texto, void* fileSvg){
    fprintf((FILE*)fileSvg, "\n\t<text x=\"%f\" y=\"%f\" stroke=\"%s\" fill=\"%s\" stroke-width=\"0.5\">%s</text>", textoGetX(texto), textoGetY(texto), textoGetCorBorda(texto), textoGetCorPreenchimento(texto), textoGetTexto(texto));
    //stroke-width não devia estar em cores padrao?
}