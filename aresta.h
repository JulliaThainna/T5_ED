#ifndef __ARESTA_H
#define __ARESTA_H

typedef void* Aresta;

/*Create
Função responsável para criar Aresta. 
PRE: nome/id, nomeVerticeInicial, nomeVerticeFinal, ldir, lesq, comprimento da aresta, velocidade da aresta
POS: Retorna um pointer instanciado.
*/
Aresta createAresta(char* nome, char* nomeVerticeInicial, char* nomeVerticeFinal, char* ldir, char* lesq, float cmp, float vm);

/*
Getters: Retorna o atributo do título da função
PRE: Objeto
POS: Atributo especificado
*/
char* arestaGetNome(Aresta aresta);
char* arestaGetNomeVerticeInicial(Aresta aresta);
char* arestaGetNomeVerticeFinal(Aresta aresta);
char* arestaGetLdir(Aresta aresta);
char* arestaGetLesq(Aresta aresta);
float arestaGetCmp(Aresta aresta);
float arestaGetVm(Aresta aresta);
float arestaGetTempo(Aresta aresta);

#endif



