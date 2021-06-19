#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "localCasos.h"
#include "point.h"

typedef struct{
    int n, num;
    char cep[300], face;
    Point point;
}LocalCasosStruct;


//Create
LocalCasos criaLocalCasos(int n, int num, char* cep, char face, float x, float y){
    LocalCasosStruct* lc = (LocalCasosStruct*) malloc(sizeof(LocalCasosStruct));
    lc->n = n;
    lc->num = num;
    strcpy(lc->cep, cep);
    lc->face = face;
    lc->point = criaPoint(x, y);
    return lc;
}

//Setters
void localCasosSetN(LocalCasos localCasos, int n){
    LocalCasosStruct* lc = (LocalCasosStruct*)localCasos;
    lc->n = n;   
}

void localCasosSetNum(LocalCasos localCasos, int num){
    LocalCasosStruct* lc = (LocalCasosStruct*)localCasos;
    lc->num = num;   
}

void localCasosSetCep(LocalCasos localCasos, char* cep){
    LocalCasosStruct* lc = (LocalCasosStruct*)localCasos;
    strcpy(lc->cep, cep);   
}

void localCasosSetFace(LocalCasos localCasos, char face){
    LocalCasosStruct* lc = (LocalCasosStruct*)localCasos;
    lc->face = face;   
}

void localCasosSetX(LocalCasos localCasos, float x){
    LocalCasosStruct* lc = (LocalCasosStruct*)localCasos;
    setPointX(lc->point, x);
}

void localCasosSetY(LocalCasos localCasos, float y){
    LocalCasosStruct* lc = (LocalCasosStruct*)localCasos;
    setPointX(lc->point, y);
}

void localCasosSetPoint(LocalCasos localCasos, Point point){
    LocalCasosStruct* lc = (LocalCasosStruct*)localCasos;
    free(lc->point);
    lc->point = point;
}

//Getters
int localCasosGetN(LocalCasos localCasos){
    LocalCasosStruct* lc = (LocalCasosStruct*)localCasos;
    return lc->n;   
}

int localCasosGetNum(LocalCasos localCasos){
    LocalCasosStruct* lc = (LocalCasosStruct*)localCasos;
    return lc->num;   
}

char* localCasosGetCep(LocalCasos localCasos){
    LocalCasosStruct* lc = (LocalCasosStruct*)localCasos;
    return lc->cep;   
}

char localCasosGetFace(LocalCasos localCasos){
    LocalCasosStruct* lc = (LocalCasosStruct*)localCasos;
    return lc->face;   
}

float localCasosGetX(LocalCasos localCasos){
    LocalCasosStruct* lc = (LocalCasosStruct*)localCasos;
    return getPointX(lc->point);
}

float localCasosGetY(LocalCasos localCasos){
    LocalCasosStruct* lc = (LocalCasosStruct*)localCasos;
    return getPointY(lc->point);
}

Point localCasosGetPoint(LocalCasos localCasos){
    LocalCasosStruct* lc = (LocalCasosStruct*)localCasos;
    return lc->point; 
}

//Swap
void localCasosSwap(LocalCasos p1, LocalCasos p2){  
    LocalCasosStruct* a = (LocalCasosStruct*) p1;
    LocalCasosStruct* b = (LocalCasosStruct*) p2;
    LocalCasosStruct temp = *a;  
    *a = *b;  
    *b = temp;  
}

void localCasosDesenhaSvgQry(LocalCasos localCasos, void* fileSvg){
    LocalCasosStruct* lc = (LocalCasosStruct*)localCasos;
    fprintf((FILE*)fileSvg, "\n<rect x=\"%f\" y=\"%f\" width=\"20\" height=\"20\" style=\"fill:orange\"/>", localCasosGetX(lc), localCasosGetY(lc));    
    fprintf((FILE*)fileSvg, "\n<text x=\"%f\" y=\"%f\" text-anchor=\"middle\" fill=\"white\">%d</text>", localCasosGetX(lc)+10, localCasosGetY(lc)+15, localCasosGetN(lc));
}
