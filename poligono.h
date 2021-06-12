#ifndef __POLIGONO_H
#define __POLIGONO_H

#include "point.h"

typedef void* Poligono;

/*Create
Função responsável para criar Poligono. 
PRE: Lista de pontos e cor do poligono de acordo com a área de incidência relativa de casos de covid
POS: Retorna um pointer instanciado.
*/
Poligono criaPoligono(DoublyLinkedList pontos, char cor[]);

/*
Setters: Define o atributo do título da função
PRE: Objeto e atributo
*/
void poligonoSetCor(Poligono poligono, char* cor);
void poligonoSetPoint(Poligono poligono, Point point);
void poligonoSetX(Poligono poligono, float x);
void poligonoSetY(Poligono poligono, float y);

/*
Getters: Retorna o atributo do título da função
PRE: Objeto
POS: Atributo especificado
*/
char* poligonoGetCor(Poligono poligono);
Point poligonoGetPoint(Poligono poligono);
float poligonoGetX(Poligono poligono);
float poligonoGetY(Poligono poligono);


/*
    Escreve uma tag SVG do poligono no file passado
    PRE: poligono e arquivo onde irá ser salvo o SVG
*/
void poligonoDesenhaSvgQry(Poligono poligono, void* fileSvg);

#endif
