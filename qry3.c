#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "qry3.h"
#include "quadTree.h"
#include "quadra.h"
#include "localCasos.h"
#include "linha.h"
#include "postoSaude.h"
#include "retangulo.h"
#include "doublyLinkedList.h"
#include "sorting.h"
#include "convexHull.h"
#include "circulo.h"
#include "utilitario.h"
#include "poligono.h"

enum LISTAS{CIRCULO, RETANGULO, TEXTO, QUADRA, HIDRANTE, SEMAFORO, RADIOBASE, POSTOSAUDE, LINHA, LOCALCASOS, POLIGONO};

void cv(QuadTree* qt, int casosCovid, char* cep, char face, int num){
    float cx = 0, cy = 0;

    convertLocalCasosToPoint(qt[QUADRA], cep, face, num, &cx, &cy);

    LocalCasos casa = criaLocalCasos(casosCovid, num, cep, face, cx, cy);
    insereQt(qt[LOCALCASOS], localCasosGetPoint(casa), casa);
}

void convertLocalCasosToPoint(QuadTree qt, char* cep, char face, int num, float* cx, float* cy){
    float qx, qy, qw, qh;
    Quadra quadra = getInfoByIdQt(qt, cep);
    if(quadra != NULL){
        qx = quadraGetX(quadra);
        qy = quadraGetY(quadra);
        qw = quadraGetWidth(quadra);
        qh = quadraGetHeight(quadra);
    
        if(face == 'S' || face == 's'){
            *cx = qx + num;
            *cy = qy;
        }
        else if(face == 'N' || face == 'n'){
            *cx = qx + num;
            *cy = qy + qh - 20;
        }
        else if(face == 'L' || face == 'l'){
            *cx = qx;
            *cy = qy + num;
        }
        else if(face == 'O' || face == 'o'){
            *cx = qx + qw - 20;
            *cy = qy + num;
        }
    }
}

void soc(QuadTree* qt, int k, char* cep, char face, int num, FILE* fileTxt){
    fprintf(fileTxt, "\nsoc %d %s %c %d", k, cep, face, num);

    float cx, cy;

    DoublyLinkedList lista = create();
    
    //Com um CEP FACE NUM ele calcula a posição X e Y desse endereço
    convertLocalCasosToPoint(qt[QUADRA], cep, face, num, &cx, &cy);

    //Percorre cada um dos nós da arvore da arvore, e para cada nó, inserimos a informação desse nó numa lista criada
    percorreLarguraQt(qt[POSTOSAUDE], convertQtToList, lista);
    //Agora, temos uma lista com todos os postos de saúde
    
    shellSorting(lista, cx, cy);

    //Sempre que a variavel começar no 0 nunca usa o igual
    int i = 0;
    for(Node aux = getFirst(lista); aux != NULL; aux = getNext(aux)){
        if(i < k){
            Linha linha = criaLinha(cx, cy, postoSaudeGetX(getInfo(aux)), postoSaudeGetY(getInfo(aux)), 0, 0, "-1");
            linhaSetTracejada(linha, 1);
            insereQt(qt[LINHA], linhaGetP1(linha), linha);
            i++;
        }
        fprintf(fileTxt, "POSTO DE SAUDE | X: %f  Y: %f", postoSaudeGetX(getInfo(aux)), postoSaudeGetY(getInfo(aux)));
    }

    Retangulo retangulo = criaRetangulo("0", 0, cx, cy, 20, 20, "white", "blue", "3px");
    insereQt(qt[RETANGULO], retanguloGetPoint(retangulo), retangulo);

    removeList(lista, 0);
}

void convertQtToList(Info info, DoublyLinkedList lista){
    insert(lista, info);
}


void ci(QuadTree* qt, float x, float y, float r, FILE* fileTxt){
    fprintf(fileTxt, "ci %f %f %f", x, y, r);

    int totalCasos = 0;

    //CONVEX HULL COM LOCAL CASOS
    DoublyLinkedList listaNoArvore = nosDentroCirculoQt(qt[LOCALCASOS], x, y, r);
    DoublyLinkedList listaLocalCasos = create();
    DoublyLinkedList listaCH = NULL;
    
    for(Node aux = getFirst(listaNoArvore); aux != NULL; aux = getNext(aux)){
        QtNo noArvore = getInfo(aux);
        LocalCasos localCasos = getInfoQt(qt[LOCALCASOS], noArvore);
        insert(listaLocalCasos, localCasos);
        fprintf(fileTxt, "\nCOORDENADAS DOS CASOS DENTRO DO CIRCULO | X: %f  Y: %f", localCasosGetX(localCasos), localCasosGetY(localCasos));
        totalCasos += localCasosGetN(localCasos);
    }
    removeList(listaNoArvore, 0);
    fprintf(fileTxt, "  /  NÚMERO TOTAL DE CASOS: %d", totalCasos);
    if(getSize(listaLocalCasos) > 2){
       listaCH = convexHull(listaLocalCasos, localCasosGetPoint, localCasosSwap); 
    }
    if(listaCH == NULL){
        listaCH = listaLocalCasos;
    }
    else{
        removeList(listaLocalCasos, 0);
    }


    //DETERMINA INCIDENCIA RELATIVA DA REGIÃO

    //DETERMINA DENSIDADE DEMOGRAFICA
    DoublyLinkedList listaNoArvoreQuadras = nosDentroCirculoQt(qt[QUADRA], x, y, r);
    DoublyLinkedList listaQuadras = create();

    for(Node aux = getFirst(listaNoArvoreQuadras); aux != NULL; aux = getNext(aux)){
        QtNo noArvore = getInfo(aux);
        Quadra info = getInfoQt(qt[QUADRA], noArvore);
        insert(listaQuadras, info);
    }
    removeList(listaNoArvoreQuadras, 0);
    
    float densidadeDemografica = 0;
    int numQuadras = 0;

    for(Node aux = getFirst(listaQuadras); aux != NULL; aux = getNext(aux)){
        Quadra quadra = getInfo(aux);

        float qX = quadraGetX(quadra);
        float qY = quadraGetY(quadra);
        float qW = quadraGetWidth(quadra);
        float qH = quadraGetHeight(quadra);

        if(insideCirculo(qX, qY, x, y, r) == 1 && insideCirculo(qX + qW, qY, x, y, r) == 1 && insideCirculo(qX, qY + qH, x, y, r) == 1 && insideCirculo(qX + qW, qY + qH, x, y, r) == 1){
            densidadeDemografica =+ quadraGetDensidadeDemografica(quadra);
            numQuadras++;
        }
    }
    //Média das densidades demográficas
    densidadeDemografica /= numQuadras;
    
    //A PARTIR DAQUI CALCULA INCIDENCIA
    char cor[20];
    float areaEnvoltoria = calculaArea(listaCH); 
    fprintf(fileTxt, "  /  ÁREA DA REGIÃO DE INCIDÊNCIA: %f", areaEnvoltoria);
    if(areaEnvoltoria != 0){
        float incidencia = 10 * totalCasos / (densidadeDemografica * areaEnvoltoria); //Calcula a incidencia 

        if(incidencia < 0.1){
            strcpy(cor, "00FFFF");
            fprintf(fileTxt, "  /  CATEGORIA A: LIVRE DE COVID");
        }
        else if(incidencia < 5){
            strcpy(cor, "008080");
            fprintf(fileTxt, "  /  CATEGORIA B: BAIXA INCIDÊNCIA");
        }
        else if(incidencia < 10){
            strcpy(cor, "FFFF00");
            fprintf(fileTxt, "  /  CATEGORIA C: MÉDIA INCIDÊNCIA");
        }
        else if(incidencia < 20){
            strcpy(cor, "FF0000");
            fprintf(fileTxt, "  /  CATEGORIA D: ALTA INCIDÊNCIA");
        }
        else{
            strcpy(cor, "800080");
            fprintf(fileTxt, "  /  CATEGORIA E: CATASTRÓFICO");
            //Verificar se tem um posto de saude na área, se não tiver, insere um no centroide
            DoublyLinkedList pontosPostos = pontosDentroCirculoQt(qt[POSTOSAUDE], x, y, r);
            if(getFirst(pontosPostos) == NULL){
                Point novoPosto = centroide(listaCH, areaEnvoltoria);
                fprintf(fileTxt, "  /  SUGERE-SE UM POSTO DE SAÚDE EM %f,%f\n", getPointX(novoPosto), getPointY(novoPosto));
                free(novoPosto);
            }
            removeList(pontosPostos, 0);
        }
    }
    else{
        fprintf(fileTxt, "  /  NÃO FOI POSSÍVEL DEFINIR REGIÃO DE INCIDÊNCIA!\n");
        if(listaCH != NULL){
            removeList(listaCH, 0);
        }

        //SVG
        Circulo circulo = criaCirculo("-1", x, y, r, "green", "none", "8px");
        insereQt(qt[CIRCULO], circuloGetPoint(circulo), circulo);

        return;
    }

    //SVG
    Circulo circulo = criaCirculo("-1", x, y, r, "green", "none", "8px");
    insereQt(qt[CIRCULO], circuloGetPoint(circulo), circulo);

    Poligono poligono = criaPoligono(listaCH, cor);
    insereQt(qt[POLIGONO], poligonoGetPoint(poligono), poligono);
}
