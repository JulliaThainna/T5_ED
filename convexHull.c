#include <stdio.h>
#include <stdlib.h>

#include "convexHull.h"
#include "doublyLinkedList.h"
#include "point.h"
#include "sorting.h"

DoublyLinkedList convexHull(DoublyLinkedList l, Point (*getPoint)(Info), void (*swapInfo)(Info, Info)){
    //Verifica se convexHull é possivel
    if(getSize(l) < 3){
        return NULL;
    }

    Node primeiro = getFirst(l);
    Info aux = getInfo(primeiro);
    
    //Pega o menor ponto em Y e usa X como critério de desempate
    for(Node i = getNext(primeiro); i != NULL; i = getNext(i)){
        Point p1 = getPoint(aux);
        Point p2 = getPoint(getInfo(i));
        if(getPointY(p2) < getPointY(p1) || (getPointY(p2) == getPointY(p1) && getPointX(p2) < getPointX(p1))){
            aux = getInfo(i);
        }
    }

    //Troca o primeiro com o minimo encontrado em Y
    Info infoPrimeiro = getInfo(primeiro);
    swapInfo(infoPrimeiro, aux);

    //Faz o quicksort a partir do segundo elemento da lista (pois o primeiro já é o menor em Y)
    quickSortDoublyLinkedList(l, getNext(primeiro), getLast(l), getPoint, swapInfo);

    //Leva em consideração o tamanho da lista na hora de selecionar os pontos e o sentido deles no convexhull
    DoublyLinkedList lAux = create();
    insert(lAux, getInfo(primeiro));

    //Começa do 3º e itera
    for(Node i = getNext(getNext(primeiro)); i != NULL; i = getNext(i)){
        Point p1 = getPoint(getInfo(i));
        Point p2 = getPoint(getInfo(getPrevious(i)));
        //Se a area do vetor formado pelo primeiro, p2 e p1 for 0 (colinear) remove o anterior da lista e diminui o tamanho dela
        if(orientacao(getPoint(getInfo(primeiro)), p2, p1) != 0){
            insert(lAux, getInfo(getPrevious(i)));
        }
    }

    insert(lAux, getInfo(getLast(l)));
    int j = getSize(lAux);
    //Após isso, se o tamanho da lista for menor que três, retorna NULL e encerra o convex hull (Pois os pontos são sómente colineares formando uma reta, sendo impossivel de calcular um poligono)
    if(j < 3){
        //removeList(lAux, 0);
        return NULL;
    }

    //Cria a lista do convex hull
    Node i;
    DoublyLinkedList conHull = create();
    for(i = primeiro, j = 0; j < 3; j++, i = getNext(i)){
        insert(conHull, getPoint(getInfo(i)));
    }

    //Percorre a lista para adicionar no convex hull verificando o sentido anti-horário
    while(i != NULL){
        while(getSize(conHull) > 1 && orientacao(getInfo(getPrevious(getLast(conHull))), getInfo(getLast(conHull)), getPoint(getInfo(i))) != 1){
            removeNode(conHull, getLast(conHull), 0);
        }
        insert(conHull, getPoint(getInfo(i)));
        i = getNext(i);
    }

    removeList(lAux, 0);
    return conHull;
}

int insidePolygon(DoublyLinkedList l, Point p){
    insert(l, getInfo(getFirst(l)));
    for(Node node = getNext(getFirst(l)); node != NULL; node = getNext(node)){
        int flag = orientacao(getInfo(getPrevious(node)), getInfo(node), p);
        if(flag == -1){
            removeNode(l, getLast(l), 0);
            return 0;
        }
    }
    removeNode(l, getLast(l), 0);
    return 1;
}