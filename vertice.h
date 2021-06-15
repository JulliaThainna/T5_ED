#ifndef __VERTICE_H
#define __VERTICE_H

#include "point.h"

typedef void* Vertice;

/*Create
Função responsável para criar vertice. 
PRE: id do vertice; coordenadas x,y;
POS: Retorna um pointer instanciado.
*/
Vertice createVertice(char* id, float x, float y);

/*
Getters: Retorna o atributo do título da função
PRE: Objeto
POS: Atributo especificado
*/
char* verticeGetNome(Vertice vertice);
Point verticeGetPoint(Vertice vertice);
float verticeGetX(Vertice vertice);
float verticeGetY(Vertice vertice);

/*
    Escreve uma tag SVG de circulo e texto no arquivo passado
    PRE: Vertice e arquivo onde irá ser salvo o SVG
*/
void desenhaVerticeSvg(Vertice vertice, char* corVertice, FILE* fileSvg);

#endif