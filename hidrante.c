#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "hidrante.h"
#include "point.h"

typedef struct hidrante{
    char id[200];
    char cp[220], cb[220], sw[220];
    Point point;
}HidranteStruct;


//Create
Hidrante criaHidrante(char* id, float x, float y, char* cp, char* cb, char* sw){
    HidranteStruct* hid = (HidranteStruct*) malloc(sizeof(HidranteStruct));
    Point point = criaPoint(x, y);
    strcpy(hid->id, id);
    strcpy(hid->cp, cp);
    strcpy(hid->cb, cb);
    strcpy(hid->sw, sw);
    hid->point = point;
    return hid;
}

//Setters
void hidranteSetId(Hidrante hidrante, char* id){
    HidranteStruct* hid = (HidranteStruct*) hidrante;
    strcpy(hid->id, id);
}

void hidranteSetX(Hidrante hidrante, float x){
    HidranteStruct* hid = (HidranteStruct*) hidrante;
    setPointX(hid->point, x);
}

void hidranteSetY(Hidrante hidrante, float y){
    HidranteStruct* hid = (HidranteStruct*) hidrante;
    setPointY(hid->point, y);
}

void hidranteSetPoint(Hidrante hidrante, Point point){
    HidranteStruct* hid = (HidranteStruct*) hidrante;
    free(hid->point);
    hid->point = point;
}

void hidranteSetCorPreenchimento(Hidrante hidrante, char* cp){
    HidranteStruct* hid = (HidranteStruct*) hidrante;
    strcpy(hid->cp, cp);
}

void hidranteSetCorBorda(Hidrante hidrante, char* cb){
    HidranteStruct* hid = (HidranteStruct*) hidrante;
    strcpy(hid->cb, cb);
}

void hidranteSetEspessura(Hidrante hidrante, char* sw){
    HidranteStruct* hid = (HidranteStruct*) hidrante;
    strcpy(hid->sw, sw);
}


//Getters
char* hidranteGetId(Hidrante hidrante){
    HidranteStruct* hid = (HidranteStruct*) hidrante;
    return hid->id;
}

float hidranteGetX(Hidrante hidrante){
    HidranteStruct* hid = (HidranteStruct*) hidrante;
    return getPointX(hid->point);
}

float hidranteGetY(Hidrante hidrante){
    HidranteStruct* hid = (HidranteStruct*) hidrante;
    return getPointY(hid->point);
}

Point hidranteGetPoint(Hidrante hidrante){
    HidranteStruct* hid = (HidranteStruct*) hidrante;
    return hid->point;
}

char* hidranteGetCorPreenchimento(Hidrante hidrante){
    HidranteStruct* hid = (HidranteStruct*) hidrante;
    return hid->cp;
}

char* hidranteGetCorBorda(Hidrante hidrante){
    HidranteStruct* hid = (HidranteStruct*) hidrante;
    return hid->cb;
}

char* hidranteGetEspessura(Hidrante hidrante){
    HidranteStruct* hid = (HidranteStruct*) hidrante;
    return hid->sw;
}

void hidranteSwap(Hidrante h1, Hidrante h2){
    HidranteStruct* a = (HidranteStruct*) h1;
    HidranteStruct* b = (HidranteStruct*) h2;
    HidranteStruct temp = *a;
    *a = *b;
    *b = temp;
}

void hidranteDesenhaSvgGeo(Hidrante hidrante, void* fileSvg){
    fprintf((FILE*)fileSvg, "\n\t<circle cx=\"%f\" cy=\"%f\" r=\"3\" style=\"fill:%s;stroke:%s;stroke-widht:%s\"/>", hidranteGetX(hidrante), hidranteGetY(hidrante), hidranteGetCorPreenchimento(hidrante), hidranteGetCorBorda(hidrante), hidranteGetEspessura(hidrante)); //);
}