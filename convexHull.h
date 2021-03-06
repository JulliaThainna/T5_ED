#ifndef __CONVEXHULL_H_
#define __CONVEXHULL_H_

    #include "doublyLinkedList.h"
    #include "point.h"

    /*
    Realiza o algoritmo de convex hull para formar o menor poligono convexo que englobe todos os pontos passados
    PRE: Uma lista de elementos l, função para pegar um ponto de um elemento, função para trocar duas informações de lugar
    POS: Uma lista com os pontos que formam o menor poligono convexo 
    */
    DoublyLinkedList convexHull(DoublyLinkedList l, Point (*getPoint)(Info), void (*swapInfo)(Info, Info));

    /*
    Verifica se um point p está dentro de um poligono cujos
    pontos são descritos na lista l
    PRE: Lista de pontos e point
    POS: 0 se estiver fora do poligono e 1 se estiver dentro
    */
    int insidePolygon(DoublyLinkedList l, Point p);
#endif