#ifndef __CIRCULO_H_
#define __CIRCULO_H_

#include "point.h"

typedef void* Circulo;

/*Create
Função responsável para criar Circulo. 
PRE: id do circulo; coordenadas x,y; raio r; cor da borda; cor do preenchimento; espessura da borda
POS: Retorna um pointer instanciado.
*/
Circulo criaCirculo(char* id, float x, float y, float r, char* cb, char* cp, char* sw);

/*
Setters: Define o atributo do título da função
PRE: Objeto e atributo
*/
void circuloSetId(Circulo circulo, char* id);
void circuloSetX(Circulo circulo, float x);
void circuloSetY(Circulo circulo, float y);
void circuloSetRaio(Circulo circulo, float r);
void circuloSetCorBorda(Circulo circulo, char* cb);
void circuloSetCorPreenchimento(Circulo circulo, char* cp);
void circuloSetPoint(Circulo circulo, Point point);
void circuloSetEspessura(Circulo circulo, char* sw);

/*
Getters: Retorna o atributo do título da função
PRE: Objeto
POS: Atributo especificado
*/
char* circuloGetId(Circulo circulo);
float circuloGetX(Circulo circulo);
float circuloGetY(Circulo circulo);
float circuloGetRaio(Circulo circulo);
char* circuloGetCorBorda(Circulo circulo);
char* circuloGetCorPreenchimento(Circulo circulo);
Point circuloGetPoint(Circulo circulo);
char* circuloGetEspessura(Circulo circulo);

/*
    Troca dois circulos de lugar na memória
    PRE: circulo 1 e circulo 2
*/
void circuloSwap(Circulo c1, Circulo c2);

/*
    Escreve uma tag SVG do circulo no arquivo passado
    PRE: circulo e arquivo onde irá ser salvo o SVG
*/
void circuloDesenhaSvgGeo(Circulo circulo, void* fileSvg);

#endif
