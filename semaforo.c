#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "semaforo.h"
#include "point.h"

typedef struct semaforo{ 
    char id[200];
    char cp[220], cb[220], sw[220];
    Point point;
}SemaforoStruct;


//Create
Semaforo criaSemaforo(char* id, float x, float y, char* cp, char* cb, char* sw){
    SemaforoStruct* sem = (SemaforoStruct*) malloc(sizeof(SemaforoStruct));
    strcpy(sem->id, id);
    strcpy(sem->cp, cp);
    strcpy(sem->cb, cb);
    strcpy(sem->sw, sw);
    Point point = criaPoint(x, y);
    sem->point = point;
    return sem;
}

//Setters
void semaforoSetId(Semaforo semaforo, char* id){
    SemaforoStruct* sem = (SemaforoStruct*) semaforo;
    strcpy(sem->id, id);
}

void semaforoSetX(Semaforo semaforo, float x){
    SemaforoStruct* sem = (SemaforoStruct*) semaforo;
    setPointX(sem->point, x);
}

void semaforoSetY(Semaforo semaforo, float y){
    SemaforoStruct* sem = (SemaforoStruct*) semaforo;
    setPointY(sem->point, y);
}

void semaforoSetPoint(Semaforo semaforo, Point point){
    SemaforoStruct* sem = (SemaforoStruct*) semaforo;
    free(sem->point);
    sem->point = point;
}

void semaforoSetCorPreenchimento(Semaforo semaforo, char* cp){
    SemaforoStruct* sem = (SemaforoStruct*) semaforo;
    strcpy(sem->cp, cp);
}

void semaforoSetCorBorda(Semaforo semaforo, char* cb){
    SemaforoStruct* sem = (SemaforoStruct*) semaforo;
    strcpy(sem->cb, cb);
}

void semaforoSetEspessura(Semaforo semaforo, char* sw){
    SemaforoStruct* sem = (SemaforoStruct*) semaforo;
    strcpy(sem->sw, sw);
}

//Getters
char* semaforoGetId(Semaforo semaforo){
    SemaforoStruct* sem = (SemaforoStruct*) semaforo;
    return sem->id;
}

float semaforoGetX(Semaforo semaforo){
    SemaforoStruct* sem = (SemaforoStruct*) semaforo;
    return getPointX(sem->point);
}

float semaforoGetY(Semaforo semaforo){
    SemaforoStruct* sem = (SemaforoStruct*) semaforo;
    return getPointY(sem->point);
}

Point semaforoGetPoint(Semaforo semaforo){
    SemaforoStruct* sem = (SemaforoStruct*) semaforo;
    return sem->point;
}

char* semaforoGetCorPreenchimento(Semaforo semaforo){
    SemaforoStruct* sem = (SemaforoStruct*) semaforo;
    return sem->cp;
}

char* semaforoGetCorBorda(Semaforo semaforo){
    SemaforoStruct* sem = (SemaforoStruct*) semaforo;
    return sem->cb;
}

char* semaforoGetEspessura(Semaforo semaforo){
    SemaforoStruct* sem = (SemaforoStruct*) semaforo;
    return sem->sw;
}

void semaforoSwap(Semaforo s1, Semaforo s2){
    SemaforoStruct* a = (SemaforoStruct*) s1;
    SemaforoStruct* b = (SemaforoStruct*) s2;
    SemaforoStruct temp = *a;
    *a = *b;
    *b = temp;
}

void semaforoDesenhaSvgGeo(Semaforo semaforo, void* fileSvg){
    fprintf((FILE*)fileSvg, "\n\t<circle cx=\"%f\" cy=\"%f\" r=\"3\" style=\"fill:%s;stroke:%s;stroke-widht:%s\"/>", semaforoGetX(semaforo), semaforoGetY(semaforo), semaforoGetCorPreenchimento(semaforo), semaforoGetCorBorda(semaforo), semaforoGetEspessura(semaforo)); //);
}