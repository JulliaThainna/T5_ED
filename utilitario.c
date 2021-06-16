#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "doublyLinkedList.h"
#include "point.h"
#include "utilitario.h"


int insideCirculo(float x, float y, float cx, float cy, float r){
    return (distanciaQuadrada(x, y, cx, cy) < r * r ? 1 : 0);
}

int insideRetangulo(float x, float y, float rx, float ry, float rw, float rh){
    if((x == rx || x == rx+rw) || (y == ry || y == ry + rh)){
        return 2;
    }
    return ((x > rx && x < rx + rw) && (y > ry && y < ry + rh) ? 1 : 0);
}

float distanciaQuadrada(float x1, float  y1, float  x2, float  y2){
    return ((x1 - x2) * (x1 - x2)) + ((y1 - y2) * (y1 - y2));
}

float distanciaEntrePontos(float x1, float  y1, float  x2, float  y2){
    double result = sqrt((double) ((x1 - x2) * (x1 - x2)) + ((y1 - y2) * (y1 - y2)));
    return result;
}


int min(int a, int b){
    return ((a < b) ? a : b);
}

int max(int a, int b){
    return ((a > b) ? a : b);
}


float minF(float a, float b){
    return ((a < b) ? a : b);
}

float maxF(float a, float b){
    return ((a > b) ? a : b);
}


float minV(float v[], int tamanho){
    float min = v[0];
    for(int i = 1; i < tamanho; i++){
        if(min > v[i]){
            min = v[i];
        }
    }
    return min;
}

float maxV(float v[], int tamanho){
    float max = v[0];
    for(int i = 1; i < tamanho; i++){
        if(max < v[i]){
            max = v[i];
        }
    }
    return max;
}

float calculaArea(DoublyLinkedList l){
    float a = 0;
    Info i, j;
    Node node;
    for(node = getFirst(l); getNext(node) != NULL; node = getNext(node)){
        i = getInfo(node);
        j = getInfo(getNext(node));
        a += getPointX(i) * getPointY(j) - getPointY(i) * getPointX(j);
    }
    i = getInfo(node);
    j = getInfo(getFirst(l));
    a += getPointX(i) * getPointY(j) - getPointY(i) * getPointX(j);
    return a / 2;
}


Point centroide(DoublyLinkedList l, float area){
    float x = 0, y = 0;
    Info i, j;
    Node node;

    for(node = getFirst(l); getNext(node) != NULL; node = getNext(node)){
        i = getInfo(node);
        j = getInfo(getNext(node));
        x += (getPointX(i) + getPointX(j)) * getPointX(i) * getPointY(j) - getPointY(i) * getPointX(j);
        y += (getPointY(i) + getPointY(j)) * getPointX(i) * getPointY(j) - getPointY(i) * getPointX(j);
    }
    i = getInfo(node);
    j = getInfo(getFirst(l));
    x += (getPointX(i) + getPointX(j)) * getPointX(i) * getPointY(j) - getPointY(i) * getPointX(j);
    y += (getPointY(i) + getPointY(j)) * getPointX(i) * getPointY(j) - getPointY(i) * getPointX(j);
    return criaPoint(x/(6 * area), y/(6 * area));
}

int stringInDoublyLinkedList(DoublyLinkedList list, char* info){
    for(Node node = getFirst(list); node != NULL; node = getNext(node)){
        if(strcmp(getInfo(node), info) == 0){
            return 1;
        }
    }
    return 0;
}

DoublyLinkedList reverseDoublyLinkedList(DoublyLinkedList list){
    DoublyLinkedList reverseList = create();
    for(Node node = getLast(list); node != NULL; node = getPrevious(node)){
        insert(reverseList, getInfo(node));
    }
    return reverseList;
}