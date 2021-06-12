#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "radioBase.h"
#include "point.h"

typedef struct radiobase{
    char id[20];
    char cp[22], cb[22], sw[22];
    Point point;
}RadioBaseStruct;


//Create
RadioBase criaRadioBase(char* id, float x, float y, char* cp, char* cb, char* sw){
    RadioBaseStruct* radio = (RadioBaseStruct*) malloc(sizeof(RadioBaseStruct));
    Point point = criaPoint(x, y);
    strcpy(radio->id, id);
    strcpy(radio->cp, cp);
    strcpy(radio->cb, cb);
    strcpy(radio->sw, sw);
    radio->point = point;
    return radio;
}

//Setters
void radioBaseSetId(RadioBase radiobase, char* id){
    RadioBaseStruct* radio = (RadioBaseStruct*) radiobase;
    strcpy(radio->id, id);
}

void radioBaseSetX(RadioBase radiobase, float x){
    RadioBaseStruct* radio = (RadioBaseStruct*) radiobase;
    setPointX(radio->point, x);
}

void radioBaseSetY(RadioBase radiobase, float y){
    RadioBaseStruct* radio = (RadioBaseStruct*) radiobase;
    setPointY(radio->point, y);
}

void radioBaseSetPoint(RadioBase radiobase, Point point){
    RadioBaseStruct* radio = (RadioBaseStruct*) radiobase;
    free(radio->point);
    radio->point = point;
}

void radioBaseSetCorPreenchimento(RadioBase radiobase, char* cp){
    RadioBaseStruct* radio = (RadioBaseStruct*) radiobase;
    strcpy(radio->cp, cp);

}

void radioBaseSetCorBorda(RadioBase radiobase, char* cb){
    RadioBaseStruct* radio = (RadioBaseStruct*) radiobase;
    strcpy(radio->cb, cb);

}

void radioBaseSetEspessura(RadioBase radiobase, char* sw){
    RadioBaseStruct* radio = (RadioBaseStruct*) radiobase;
    strcpy(radio->sw, sw);
}

//Getters 
char* radioBaseGetId(RadioBase radiobase){
    RadioBaseStruct* radio = (RadioBaseStruct*) radiobase;   
    return radio->id;
}

float radioBaseGetX(RadioBase radiobase){
    RadioBaseStruct* radio = (RadioBaseStruct*) radiobase;
    return getPointX(radio->point);
}

float radioBaseGetY(RadioBase radiobase){
    RadioBaseStruct* radio = (RadioBaseStruct*) radiobase; 
    return getPointY(radio->point);
}

Point radioBaseGetPoint(RadioBase radiobase){
    RadioBaseStruct* radio = (RadioBaseStruct*) radiobase;
    return radio->point;
}

char* radioBaseGetCorPreenchimento(RadioBase radiobase){
    RadioBaseStruct* radio = (RadioBaseStruct*) radiobase;
    return radio->cp;

}

char* radioBaseGetCorBorda(RadioBase radiobase){
    RadioBaseStruct* radio = (RadioBaseStruct*) radiobase;
    return radio->cb;

}

char* radioBaseGetEspessura(RadioBase radiobase){
    RadioBaseStruct* radio = (RadioBaseStruct*) radiobase;
    return radio->sw;
}

void radioBaseSwap(RadioBase rb1, RadioBase rb2){
    RadioBaseStruct* a = (RadioBaseStruct*) rb1;
    RadioBaseStruct* b = (RadioBaseStruct*) rb2;
    RadioBaseStruct temp = *a;
    *a = *b;
    *b = temp;
}

void radioBaseDesenhaSvgGeo(RadioBase radiobase, void* fileSvg){
    fprintf((FILE*)fileSvg, "\n\t<circle cx=\"%f\" cy=\"%f\" r=\"3\" style=\"fill:%s;stroke:%s;stroke-widht:%s\"/>", radioBaseGetX(radiobase), radioBaseGetY(radiobase), radioBaseGetCorPreenchimento(radiobase), radioBaseGetCorBorda(radiobase), radioBaseGetEspessura(radiobase)); //);
}
