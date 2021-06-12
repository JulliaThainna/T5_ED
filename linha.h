#ifndef LINHA__H_
#define LINHA__H_

#include "point.h"

typedef void* Linha;

// Função responsável para criar Linha. Retorna um pointer instanciado.
Linha criaLinha(float x1, float y1, float x2, float y2, int pntInicial, int interna, char* cep);

/*
Setters: Define o atributo do título da função
PRE: Objeto e atributo
*/
void linhaSetX1(Linha linha, float x1);
void linhaSetY1(Linha linha, float y1);
void linhaSetX2(Linha linha, float x2);
void linhaSetY2(Linha linha, float y2);
void linhaSetPntInicial(Linha linha, int pntInicial);
void linhaSetInterna(Linha linha, int interna);
void linhaSetCep(Linha linha, char* cep);
void linhaSetP1(Linha linha, Point p1);
void linhaSetP2(Linha linha, Point p2);
void linhaSetTracejada(Linha linha, int tracejada);
/*
Getters: Retorna o atributo do título da função
PRE: Objeto
POS: Atributo especificado
*/
float linhaGetX1(Linha linha);
float linhaGetY1(Linha linha);
float linhaGetX2(Linha linha);
float linhaGetY2(Linha linha);
int linhaGetPntInicial(Linha linha);
int linhaGetInterna(Linha linha);
char* linhaGetCep(Linha linha);
Point linhaGetP1(Linha linha);
Point linhaGetP2(Linha linha);
int linhaGetTracejada(Linha linha);

/*
    Escreve uma tag SVG da linha no arquivo passado
    PRE: linha e arquivo onde irá ser salvo o SVG
*/
void linhaDesenhaSvgQry(Linha linha, void* fileSvgQry);

#endif
