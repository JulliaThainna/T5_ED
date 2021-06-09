#include <stdio.h>
#include <stdlib.h>
#include "point.h"

typedef struct{
    float x, y;
}PointStruct;


//Create
Point criaPoint(float x, float y){
    PointStruct* pnt = (PointStruct*) malloc(sizeof(PointStruct));
    pnt->x = x;
    pnt->y = y;
    return pnt;
}

//Getters
float getPointX(Point point){
    PointStruct* pnt = (PointStruct*)point;
    return pnt->x;
}

float getPointY(Point point){
    PointStruct* pnt = (PointStruct*)point;
    return pnt->y;
}

//Setters
void setPointX(Point point, float x){
    PointStruct* pnt = (PointStruct*)point;
    pnt->x = x;
}

void setPointY(Point point, float y){
    PointStruct* pnt = (PointStruct*)point;
    pnt->y = y;
}

void atribuirPonto(Point p1, Point p2){  
    PointStruct* a = (PointStruct*) p1;
    PointStruct* b = (PointStruct*) p2;
    *a = *b;  
}