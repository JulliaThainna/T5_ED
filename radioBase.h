#ifndef __RADIOBASE_H
#define __RADIOBASE_H

#include "point.h"

typedef void* RadioBase;

/*
Função responsável para criar RadioBase.
PRE: Id da radiobase; coordenadas x,y; cor de preenchimento; cor da borda; espessura da borda 
POS: Retorna um pointer instanciado.
*/
RadioBase criaRadioBase(char* id, float x, float y, char* cp, char* cb, char* sw);

/*
Setters: Define o atributo do título da função
PRE: Objeto e atributo
*/
void radioBaseSetId(RadioBase radiobase, char* id);
void radioBaseSetX(RadioBase radiobase, float x);
void radioBaseSetY(RadioBase radiobase, float y);
void radioBaseSetPoint(RadioBase radiobase, Point point);
void radioBaseSetCorPreenchimento(RadioBase radiobase, char* cp);
void radioBaseSetCorBorda(RadioBase radiobase, char* cb);
void radioBaseSetEspessura(RadioBase radiobase, char* sw);

/*
Getters: Retorna o atributo do título da função
PRE: Objeto
POS: Atributo especificado
*/
char* radioBaseGetId(RadioBase radiobase);
float radioBaseGetX(RadioBase radiobase);
float radioBaseGetY(RadioBase radiobase);
Point radioBaseGetPoint(RadioBase radiobase);
char* radioBaseGetCorPreenchimento(RadioBase radiobase);
char* radioBaseGetCorBorda(RadioBase radiobase);
char* radioBaseGetEspessura(RadioBase radiobase);

/*
    Troca duas radiobases de lugar na memória
    PRE: radiobase 1 e radiobase 2
*/
void radioBaseSwap(RadioBase rb1, RadioBase rb2);

/*
    Escreve uma tag SVG da radiobase no file passado
    PRE: radiobase e arquivo onde irá ser salvo o SVG
*/
void radioBaseDesenhaSvgGeo(RadioBase radiobase, void* fileSvg);

#endif
