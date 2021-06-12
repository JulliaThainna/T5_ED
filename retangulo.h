#ifndef __RETANGULO_H_
#define __RETANGULO_H_

#include "point.h"

typedef void* Retangulo;

/*
Função responsável para criar Retangulo. 
PRE: id do retangulo; retangulo com bordas tracejadas (1) ou não (0), coordenadas x,y; largura do retangulo; altura do retangulo; cor da borda; cor de preenchimento; espessura da borda
POS: Retorna um pointer instanciado.
*/
Retangulo criaRetangulo(char* id, int tracejado, float x, float y, float w, float h, char* cb, char* cp, char* sw);

/*
Setters: Define o atributo do título da função
PRE: Objeto e atributo
*/
void retanguloSetId(Retangulo retangulo, char* id);
void retanguloSetTracejado(Retangulo retangulo, int tracejado);
void retanguloSetX(Retangulo retangulo, float x);
void retanguloSetY(Retangulo retangulo, float y);
void retanguloSetWidth(Retangulo retangulo, float w);
void retanguloSetHeight(Retangulo retangulo, float h);
void retanguloSetCorBorda(Retangulo retangulo, char* cb);
void retanguloSetCorPreenchimento(Retangulo retangulo, char* cp);
void retanguloSetPoint(Retangulo retangulo, Point point);
void retanguloSetEspessura(Retangulo retangulo, char* sw);

/*
Getters: Retorna o atributo do título da função
PRE: Objeto
POS: Atributo especificado
*/
char* retanguloGetId(Retangulo retangulo);
int retanguloGetTracejado(Retangulo retangulo);
float retanguloGetX(Retangulo retangulo);
float retanguloGetY(Retangulo retangulo);
float retanguloGetWidth(Retangulo retangulo);
float retanguloGetHeight(Retangulo retangulo);
char* retanguloGetCorBorda(Retangulo retangulo);
char* retanguloGetCorPreenchimento(Retangulo retangulo);
Point retanguloGetPoint(Retangulo retangulo);
char* retanguloGetEspessura(Retangulo retangulo);

/*
    Troca dois retangulos de lugar na memória
    PRE: retangulo 1 e retangulo 2
*/
void retanguloSwap(Retangulo r1, Retangulo r2);


/*
    Escreve uma tag SVG do retangulo no arquivo passado
    PRE: retangulo e arquivo onde irá ser salvo o SVG
*/
void retanguloDesenhaSvgGeo(Retangulo retangulo, void* fileSvg);

/*
    Escreve uma tag SVG do retangulo no arquivo passado
    PRE: retangulo e arquivo onde irá ser salvo o SVG
*/
void retanguloDesenhaSvgQry(Retangulo retangulo, void* fileSvg);

#endif
