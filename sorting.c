#include <stdio.h>
#include <stdlib.h>

#include "sorting.h"
#include "doublyLinkedList.h"
#include "localCasos.h"
#include "utilitario.h"
#include "postoSaude.h"
#include "point.h"
#include "convexHull.h"

void shellSorting(DoublyLinkedList lista, float x, float y){
    PostoSaude info1, info2;
    int i, j, h, size = getSize(lista);

    for(h = 1; h < size; h = 3 * h + 1);

    while(h > 0){
        h = (h - 1) / 3;
        for(i = 0; i < size; i++){
            info1 = getInfoByIndex(lista, i);
            PostoSaude aux = criaPostoSaude(postoSaudeGetX(info1), postoSaudeGetY(info1));
            j = i;
            PostoSaude aux2 = getInfoByIndex(lista, j - h);
            while(distanciaEntrePontos(postoSaudeGetX(aux2), postoSaudeGetY(aux2), x, y) > distanciaEntrePontos(postoSaudeGetX(aux), postoSaudeGetY(aux), x, y)){
                info1 = getInfoByIndex(lista, j);
                info2 = getInfoByIndex(lista, j - h);
                postoSaudeAtribuirPonto(info1, info2);
                j -= h;
                if(j < h){
                    break;
                }
            }
            postoSaudeAtribuirPonto(getInfoByIndex(lista, j), aux);
            free(aux); 
        }
    }
}


float obterArea(DoublyLinkedList l){
    float a = 0;
    Info i, j;
    Node node;
    for(node = getFirst(l); getNext(node) != NULL; node = getNext(node)){
        i = getInfo(node);
        j = getInfo(getNext(node));
        a += localCasosGetX(i) * localCasosGetY(j) - localCasosGetY(i) * localCasosGetX(j);
    }
    i = getInfo(node);
    j = getInfo(getFirst(l));
    a += localCasosGetX(i) * localCasosGetY(j) - localCasosGetY(i) * localCasosGetX(j);
    return a / 2;
}


void quickSortDoublyLinkedList(DoublyLinkedList l, Node primeiro, Node ultimo, Point (*getPoint)(Info), void (*swapInfo)(Info, Info)){
    if(ultimo != NULL && primeiro != ultimo && getNext(ultimo) != primeiro){
        Node p = partition(l, primeiro, ultimo, getPoint, swapInfo);
        quickSortDoublyLinkedList(l, primeiro, getPrevious(p), getPoint, swapInfo);
        quickSortDoublyLinkedList(l, getNext(p), ultimo, getPoint, swapInfo);
    }
}


Node partition(DoublyLinkedList l, Node primeiro, Node ultimo, Point (*getPoint)(Info), void (*swapInfo)(Info, Info)){
    Node i = getPrevious(primeiro);
    for(Node j = primeiro; j != ultimo; j = getNext(j)){
        if(comparar(getPoint(getInfo(getFirst(l))), getPoint(getInfo(j)), getPoint(getInfo(ultimo)))){
            i = (i == NULL) ? primeiro : getNext(i);
            swapInfo(getInfo(i), getInfo(j));
        }
    }
    i = (i == NULL) ? primeiro : getNext(i);
    swapInfo(getInfo(i), getInfo(ultimo));
    return i;
}


int comparar(Point a, Point b, Point c){
    int aux = orientacao(a, b, c);
    if(aux == 0){
        return distanciaEntrePontos(getPointX(a), getPointY(a), getPointX(c), getPointY(c)) < distanciaEntrePontos(getPointX(a), getPointY(a), getPointX(b), getPointY(b));
    }
    return aux == 1;
}


int orientacao(Point a, Point b, Point c){
    float area = (getPointX(b) - getPointX(a)) * (getPointY(c) - getPointY(a)) - (getPointY(b) - getPointY(a)) * (getPointX(c) - getPointX(a));
    //Se a área for > 1 significa que o sentido do vetor formado pelos pontos é horário
    if(area < 0){
        return -1;
    }
    //Se a área for < 1 significa que o sentido do vetor formado pelos pontos é anti-horário
    if(area > 0){
        return 1;
    }
    //Se a área for 0, siginifca que os vetores são colineares e paralelos entre sí
    return 0; 
}