#ifndef __QRY1_H
#define __QRY1_H

#include "quadTree.h"
#include "circulo.h"
#include "retangulo.h"

/*
    Realiza a função indicada por o?
    PRE: Vetor de quadtrees, indice j e k, float pointer para desenhar retangulo indicando figuras e file para log
    POS: 0 se não for overlay e 1 se for
*/
int overlay(QuadTree* qt, char* j, char* k, float* x, float* y, float* w, float* h, FILE* fileTxt);

/*
    Verifica se um circulo está sobreposto em um circulo
    PRE: c1 e c2
    POS: -1: erro, 0: não se sobrepõe, 1: se sobrepõe
*/
int overlayCirculoCirculo(Circulo c1, Circulo c2);

/*
    Verifica se um circulo está sobreposto em um retangulo
    PRE: circulo e retangulo
    POS: -1: erro, 0: não se sobrepõe, 1: se sobrepõe
*/
int overlayCirculoRetangulo(Circulo c, Retangulo r);

/*
    Verifica se um retangulo está sobreposto em um retangulo
    PRE: r1 e r2
    POS: -1: erro, 0: não se sobrepõe, 1: se sobrepõe
*/
int overlayRetanguloRetangulo(Retangulo r1, Retangulo r2);

/*
    Realiza a função indicada por i?
    PRE: Vetor de quadtrees, indice j, ponto x e y, float pointer para salvar o centro de massa centroMassaX e centroMassaY e file para log
    POS: 0 se não for inside e 1 se for
*/
int inside(QuadTree* qt, char* j, float x, float y, float* centroMassaX, float* centroMassaY, FILE* fileTxt);


/*
    Altera a cor de um circulo, retangulo ou texto com o id J
    PRE: vetor de quadtrees, id J, novas cores de preenchimento e borda (cp, cb) e file para log
*/
void pnt(QuadTree* qt, char* j, char* cb, char* cp, FILE* fileTxt);

/*
    Altera a cor de um circulo, retangulo ou texto, aplicado entre os ids J e K, inclusive
    PRE: vetor de quadtrees, id J, id K, novas cores de preenchimento e borda (cp, cb) e file para log
*/
void pntAst(QuadTree* qt, char* j, char* k, char* cb, char* cp, FILE* fileTxt);

/*
    Remove um circulo, retangulo ou texto com o id J
    PRE: vetor de quadtrees, id J e file para log
*/
void delf(QuadTree* qt, char* j, FILE* fileTxt);

/*
    Remove um circulo, retangulo ou texto entre os ids J e K, inclusive
    PRE: vetor de quadtrees, id J, id K, e file para log
*/
void delfAst(QuadTree* qt, char* j, char* k, FILE* fileTxt);

#endif