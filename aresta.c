#include <stdio.h>
#include <stdlib.h>
#include <string.h>      

#include "aresta.h"
#include "graph.h"
#include "vertice.h"

typedef struct{
    char nome[100];
    char nomeVerticeInicial[100];
    char nomeVerticeFinal[100];
    char ldir[100];
    char lesq[100];
    float cmp;
    float vm;
}ArestaStruct;

Aresta createAresta(char* nome, char* nomeVerticeInicial, char* nomeVerticeFinal, char* ldir, char* lesq, float cmp, float vm){
    ArestaStruct* art = (ArestaStruct*) malloc(sizeof(ArestaStruct));
    strcpy(art->nomeVerticeInicial, nomeVerticeInicial);
    strcpy(art->nomeVerticeFinal, nomeVerticeFinal);
    strcpy(art->nome, nome);
    strcpy(art->ldir, ldir);
    strcpy(art->lesq, lesq);
    art->cmp = cmp;
    art->vm = vm;
    return art;
}

char* arestaGetNome(Aresta aresta){
    ArestaStruct* art = (ArestaStruct*) aresta;
    return art->nome;
}

char* arestaGetNomeVerticeInicial(Aresta aresta){
    ArestaStruct* art = (ArestaStruct*) aresta;
    return art->nomeVerticeInicial;
}

char* arestaGetNomeVerticeFinal(Aresta aresta){
    ArestaStruct* art = (ArestaStruct*) aresta;
    return art->nomeVerticeFinal;
}

char* arestaGetLdir(Aresta aresta){
    ArestaStruct* art = (ArestaStruct*) aresta;
    return art->ldir;
}

char* arestaGetLesq(Aresta aresta){
    ArestaStruct* art = (ArestaStruct*) aresta;
    return art->lesq;
} 

float arestaGetCmp(Aresta aresta){
    ArestaStruct* art = (ArestaStruct*) aresta;
    return art->cmp;
}

float arestaGetVm(Aresta aresta){
    ArestaStruct* art = (ArestaStruct*) aresta;
    return art->vm;
}

float arestaGetTempo(Aresta aresta){
    ArestaStruct* art = (ArestaStruct*) aresta;
    return art->cmp / art->vm;
}
