#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "estabelecimento.h"
#include "point.h"
#include "quadra.h"

typedef struct{
    Point ponto;
    char cnpj[20];
    char nome[20];
    char cpf[20];
    char cep[20];
    char codt[10];
    char face;
    int numero;
}EstabelecimentoStruct;

Estabelecimento criaEstabelecimento(Quadra quad, char* cnpj, char* cpf, char* nome, char* codt, char face, int num){
    EstabelecimentoStruct* estabelecimento = (EstabelecimentoStruct*) malloc(sizeof(EstabelecimentoStruct));
    float x = quadraGetX(quad);
    float y = quadraGetY(quad);
    float h = quadraGetWidth(quad);
    float w = quadraGetHeight(quad);
    switch (face){
    case 'n':
        x += num;
        y += h;
        break;
    case 's':
        x += num;
        break;
    case 'l':
        y += num;
        break;
    case 'o':
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
