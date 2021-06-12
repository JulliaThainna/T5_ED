#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "doublyLinkedList.h"
#include "poligono.h"
#include "point.h"

typedef struct {
    DoublyLinkedList pontos;
    Point point;
    char cor[22];
}PoligonoStruct;


//Create
Poligono criaPoligono(DoublyLinkedList pontos, char cor[]){
    PoligonoStruct* polig = (PoligonoStruct*)malloc(sizeof(PoligonoStruct));
    polig->pontos = pontos;
    
    Node firstNode = getFirst(polig->pontos); //Pega primeiro node da lista
    Point firstPoint = getInfo(firstNode); //Pega a info do promeiro node (que é um ponto)
    polig->point = criaPoint(getPointX(firstPoint), getPointY(firstPoint)); //(Taca o x e y desse ponto no ponto que tem que ter pq a arvore pede)
    strcpy(polig->cor, cor);
    return polig;
}

//Setters
void poligonoSetCor(Poligono poligono, char* cor){
    PoligonoStruct* polig = (PoligonoStruct*)poligono;
    strcpy(polig->cor, cor);
}

void poligonoSetPoint(Poligono poligono, Point point){
    PoligonoStruct* polig = (PoligonoStruct*)poligono;
    free(polig->point);
    polig->point = point;
}

void poligonoSetX(Poligono poligono, float x){
    PoligonoStruct* polig = (PoligonoStruct*)poligono;
    setPointX(polig->point, x);
}

void poligonoSetY(Poligono poligono, float y){
    PoligonoStruct* polig = (PoligonoStruct*)poligono;
    setPointY(polig->point, y);
}

//Getters
char* poligonoGetCor(Poligono poligono){
    PoligonoStruct* polig = (PoligonoStruct*)poligono;
    return polig->cor;
}

Point poligonoGetPoint(Poligono poligono){
    PoligonoStruct* polig = (PoligonoStruct*)poligono;
    return polig->point;
}

float poligonoGetX(Poligono poligono){
    PoligonoStruct* polig = (PoligonoStruct*)poligono;
    return getPointX(polig->point);
}

float poligonoGetY(Poligono poligono){
    PoligonoStruct* polig = (PoligonoStruct*)poligono;
    return getPointY(polig->point);
}       

void poligonoDesenhaSvgQry(Poligono poligono, void* fileSvg){
    PoligonoStruct* polig = (PoligonoStruct*)poligono;
    //Abre tag
    fprintf((FILE*)fileSvg, "<polygon points=\"");
    for(Node aux = getFirst(polig->pontos); aux != NULL; aux = getNext(aux)){
        fprintf((FILE*)fileSvg, " %f,%f ", getPointX(getInfo(aux)), getPointY(getInfo(aux)));
    }    
    //Fecha tag 
    fprintf((FILE*)fileSvg, "\" style=\"fill:#%s; stroke:red; stroke-width: 5px;\" fill-opacity= \"0.2\" />", polig->cor);
}