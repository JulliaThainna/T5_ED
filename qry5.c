//Standart Includes
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

//Data Structures
#include "graph.h"
#include "doublyLinkedList.h"
#include "quadTree.h"
#include "hashTable.h"
#include "trataString.h"

//
#include "endereco.h"
#include "point.h"
#include "linha.h"
#include "hidrante.h"
#include "semaforo.h"
#include "radioBase.h"
 
enum LISTAS{CIRCULO, RETANGULO, TEXTO, QUADRA, HIDRANTE, SEMAFORO, RADIOBASE, POSTOSAUDE, LINHA, LOCALCASOS, POLIGONO, ESTABELECIMENTO, ENDERECOS};
enum HASHTABLE{CPF_ENDERECO, TIPO_DESCRICAO, CPF_DADOS, CEP_QUADRA};

int indiceRegistrador(char* r){
    char* rAux = malloc((strlen(r) + 1) * sizeof(char));
    rAux = strcpy(rAux, r);
    rAux = rAux + 1;
    int indice = atoi(rAux);
    free(rAux - 1);
    return indice;
}   

void mInt(QuadTree* qt, HashTable* ht, Point* registrador, char* r, char* cpf){
    int indice = indiceRegistrador(r);
    Endereco endereco = getValue(ht[CPF_ENDERECO], cpf);
    setPointX(registrador[indice], getPointX(enderecoGetPoint(endereco)));
    setPointY(registrador[indice], getPointY(enderecoGetPoint(endereco)));
    
    Linha linha = criaLinha(getPointX(registrador[indice]), getPointY(registrador[indice]), getPointX(registrador[indice]), 10, 0, 0, r);
    insereQt(qt[LINHA], linhaGetP1(linha), linha);
}

void eInt(QuadTree* qt, HashTable* ht, Point* registrador, char* r, char* cep, char face, int num){
    int indice = indiceRegistrador(r);
    Quadra quadra = getValue(ht[CEP_QUADRA], cep);
    if(quadra == NULL){
        return;
    }
    //Pega o endereço de CEP/ FACE/ NUM com base numa quadra
    float x = quadraGetX(quadra);
    float y = quadraGetY(quadra);
    float w = quadraGetWidth(quadra);
    float h = quadraGetHeight(quadra);

    switch(toupper(face)){
    case 'N':
        x += num;
        y += h;
        break;
    case 'S':
        x += num;
        break;
    case 'L':
        y += num;
        break;
    case 'O':
        x += w;
        y += num;
        break;
    }
    setPointX(registrador[indice], x);
    setPointY(registrador[indice], y);

    Linha linha = criaLinha(getPointX(registrador[indice]), getPointY(registrador[indice]), getPointX(registrador[indice]), 10, 0, 0, r);
    insereQt(qt[LINHA], linhaGetP1(linha), linha);
}

void gInt(QuadTree* qt, Point* registrador, char* r, char* id){
    int indice = indiceRegistrador(r);
    Hidrante hidrante = getInfoByIdQt(qt[HIDRANTE], id);
    Semaforo semaforo = getInfoByIdQt(qt[SEMAFORO], id);
    RadioBase radioBase = getInfoByIdQt(qt[RADIOBASE], id);
    if(hidrante != NULL){
        setPointX(registrador[indice], getPointX(hidranteGetPoint(hidrante)));
        setPointY(registrador[indice], getPointY(hidranteGetPoint(hidrante)));
    }
    else if(semaforo != NULL){
        setPointX(registrador[indice], getPointX(semaforoGetPoint(semaforo)));
        setPointY(registrador[indice], getPointY(semaforoGetPoint(semaforo)));
    }
    else if(radioBase != NULL){
        setPointX(registrador[indice], getPointX(radioBaseGetPoint(radioBase)));
        setPointY(registrador[indice], getPointY(radioBaseGetPoint(radioBase)));
    }
    else{
        return;
    }

    Linha linha = criaLinha(getPointX(registrador[indice]), getPointY(registrador[indice]), getPointX(registrador[indice]), 10, 0, 0, r);
    insereQt(qt[LINHA], linhaGetP1(linha), linha);
}

void xy(QuadTree* qt, Point* registrador, char* r, float x, float y){
    int indice = indiceRegistrador(r);
    setPointX(registrador[indice], x);
    setPointY(registrador[indice], y);
    Linha linha = criaLinha(getPointX(registrador[indice]), getPointY(registrador[indice]), getPointX(registrador[indice]), 10, 0, 0, r);
    insereQt(qt[LINHA], linhaGetP1(linha), linha);
}

Graph ccv(Graph graphVia, char* sfx, char* dirSaida, char* nomeGeoSemExtensao, char* nomeQrySemExtensao){
    Graph v = removeVerticeDesconexo(graphVia);
    Graph graphCiclovia = primAlgorithm(convertToUndirectedGraph(v));

    char* nomeGeoQry = NULL;
    char* nomeGeoQrySfx = NULL;
    char* pathCcv = NULL;
    concatenaNomeGeoQry(nomeGeoSemExtensao, nomeQrySemExtensao, "", &nomeGeoQry);
    concatenaNomeGeoQry(nomeGeoQry, sfx, ".svg", &nomeGeoQrySfx);
    concatenaCaminhos(dirSaida, nomeGeoQrySfx, &pathCcv);
    
    FILE* fileSvg = fopen(pathCcv, "w");
    if(fileSvg == NULL){
        return NULL;
    }
    printf("\nArquivo SVG-%s aberto com sucesso!", sfx);
        
    fprintf(fileSvg, "\n<svg width=\"10000\" height=\"10000\" xmlns=\"http://www.w3.org/2000/svg\">");

    desenhaGrafoSvg(graphVia, fileSvg, "gray", "gray");
    desenhaGrafoSvg(graphCiclovia, fileSvg, "pink", "gray");

    fprintf(fileSvg, "\n</svg>");

    fclose(fileSvg);
    return graphCiclovia;
}

