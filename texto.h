#ifndef __TEXTO_H_
#define __TEXTO_H_

#include "point.h"

typedef void* Texto;

//Função responsável para criar Texto. Retorna um pointer instanciado.
Texto criaTexto(char* id, int size, float x, float y, char* txt, char* cb, char* cp);


/*
Setters: Define o atributo do título da função
PRE: Objeto e atributo
*/
void textoSetId(Texto texto, char* id);
void textoSetX(Texto texto, float x);
void textoSetY(Texto texto, float y);
void textoSetTexto(Texto texto, char* txt, int size);
void textoSetCorBorda(Texto texto, char* cb);
void textoSetCorPreenchimento(Texto texto, char* cp);
void textoSetPoint(Texto texto, Point point);

/*
Getters: Retorna o atributo do título da função
PRE: Objeto
POS: Atributo especificado
*/
char* textoGetId(Texto texto);
float textoGetX(Texto texto);
float textoGetY(Texto texto);
char* textoGetTexto(Texto texto);
char* textoGetCorBorda(Texto texto);
char* textoGetCorPreenchimento(Texto texto);
Point textoGetPoint(Texto texto);

//Desaloca o malloc do texto da memória
//Pré: Objeto texto
void textoDeletaTxt(Texto texto);

/*
    Troca dois textos de lugar na memória
    PRE: Texto 1 e texto 2
*/
void textoSwap(Texto t1, Texto t2);

/*
    Escreve uma tag SVG do texto no arquivo passado
    PRE: Texto e arquivo onde irá ser salvo o SVG
*/
void textoDesenhaSvgGeo(Texto texto, void* fileSvg);

#endif
