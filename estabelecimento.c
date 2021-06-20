#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "estabelecimento.h"
#include "point.h"
#include "quadra.h"

typedef struct{
    Point ponto;
    char cnpj[200];
    char nome[200];
    char cpf[200];
    char cep[200];
    char codt[100];
    char face;
    int numero;
    float x;
    float y;
}EstabelecimentoStruct;

Estabelecimento criaEstabelecimento(Quadra quad, char* cnpj, char* cpf, char* nome, char* codt, char face, int num){
    EstabelecimentoStruct* estabelecimento = (EstabelecimentoStruct*) malloc(sizeof(EstabelecimentoStruct));
    float x = quadraGetX(quad);
    float y = quadraGetY(quad);
    float h = quadraGetWidth(quad);
    float w = quadraGetHeight(quad);
    switch (face){
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
    strcpy(estabelecimento->cnpj, cnpj);
    strcpy(estabelecimento->cpf, cpf);
    strcpy(estabelecimento->cep, quadraGetCep(quad));
    strcpy(estabelecimento->nome, nome);
    strcpy(estabelecimento->codt, codt);
    estabelecimento->ponto = criaPoint(x,y);
    estabelecimento->x = x;
    estabelecimento->y = y;
    estabelecimento->face = face;
    estabelecimento->numero = num;

    return estabelecimento;
}

char* estabelecimentoGetCep(Estabelecimento estabelecimento){
    EstabelecimentoStruct* e = (EstabelecimentoStruct*)estabelecimento;
    return e->cep;
}

char* estabelecimentoGetCodt(Estabelecimento estabelecimento){
    EstabelecimentoStruct* e = (EstabelecimentoStruct*)estabelecimento;
    return e->codt;
}

char* estabelecimentoGetCpf(Estabelecimento estabelecimento){
    EstabelecimentoStruct* e = (EstabelecimentoStruct*)estabelecimento;
    return e->cpf;
}

char* estabelecimentoGetCnpj(Estabelecimento estabelecimento){
    EstabelecimentoStruct* e = (EstabelecimentoStruct*)estabelecimento;
    return e->cnpj;
}

char* estabelecimentoGetNome(Estabelecimento estabelecimento){
    EstabelecimentoStruct* e = (EstabelecimentoStruct*)estabelecimento;
    return e->nome;
}

Point estabelecimentoGetPoint(Estabelecimento estabelecimento){
    EstabelecimentoStruct* e = (EstabelecimentoStruct*)estabelecimento;
    return e->ponto;
}

char estabelecimentoGetFace(Estabelecimento estabelecimento){
    EstabelecimentoStruct* e = (EstabelecimentoStruct*)estabelecimento;
    return e->face;
}

int estabelecimentoGetNum(Estabelecimento estabelecimento){
    EstabelecimentoStruct* e = (EstabelecimentoStruct*)estabelecimento;
    return e->numero;
}

void estabelecimentoSwap(Estabelecimento e1, Estabelecimento e2){  
    EstabelecimentoStruct* a = (EstabelecimentoStruct*) e1;
    EstabelecimentoStruct* b = (EstabelecimentoStruct*) e2;
    EstabelecimentoStruct temp = *a;  
    *a = *b;  
    *b = temp;  
}

int estabelecimentoGetSize(){
    return sizeof(EstabelecimentoStruct);
}

float estabelecimentoGetX(Estabelecimento estabelecimento){
    EstabelecimentoStruct* e = (EstabelecimentoStruct*) estabelecimento;
    return e->x;
}

float estabelecimentoGetY(Estabelecimento estabelecimento){
    EstabelecimentoStruct* e = (EstabelecimentoStruct*) estabelecimento;
    return e->y;
}


void estabelecimentoSetPoint(Estabelecimento estabelecimento, float x, float y){
    EstabelecimentoStruct* e = (EstabelecimentoStruct*) estabelecimento;
    e->ponto = criaPoint(x,y);
}