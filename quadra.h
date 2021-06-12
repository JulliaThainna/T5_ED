#ifndef __QUADRA_H
#define __QUADRA_H

#include "point.h"

typedef void* Quadra;

/*
Função responsável para criar Quuadra. 
PRE: cep da quadra; coordenadas x,y; largura da quadra; altura da quadra; cor da borda; cor do preenchimento; espessura da borda; se as bordas são arrendondas(1) ou não(0)
POS: Retorna um pointer instanciado.
*/
Quadra criaQuadra(char* cep, float x, float y, float w, float h, char* cb, char* cp, char* cstrk, int arredondado);

/*
Setters: Define o atributo do título da função
PRE: Objeto e atributo
*/
void quadraSetCep(Quadra quadra, char* cep);
void quadraSetX(Quadra quadra, float x);
void quadraSetY(Quadra quadra, float y);
void quadraSetWidth(Quadra quadra, float w);
void quadraSetHeight(Quadra quadra, float h);
void quadraSetCorBorda(Quadra quadra, char* cb);
void quadraSetCorPreenchimento(Quadra quadra, char* cp);
void quadraSetArredondado(Quadra quadra, int arredondado);
void quadraSetPoint(Quadra quadra, Point point);
void quadraSetDensidadeDemografica(Quadra quadra, float dd);
void quadraSetEspessura(Quadra quadra, char* sw);
/*
Getters: Retorna o atributo do título da função
PRE: Objeto
POS: Atributo especificado
*/
char* quadraGetCep(Quadra quadra);
float quadraGetX(Quadra quadra);
float quadraGetY(Quadra quadra);
float quadraGetWidth(Quadra quadra);
float quadraGetHeight(Quadra quadra);
char* quadraGetCorBorda(Quadra quadra);
char* quadraGetCorPreenchimento(Quadra quadra);
int quadraGetArredondado(Quadra quadra);
float quadraGetArea(Quadra quadra);
Point quadraGetPoint(Quadra quadra);
float quadraGetDensidadeDemografica(Quadra quadra);
char* quadraGetEspessura(Quadra quadra);

/*
    Troca duas quadras de lugar na memória
    PRE: quadra 1 e quadra 2
*/
void quadraSwap(Quadra q1, Quadra q2);

/*
    Escreve uma tag SVG da quadra no file passado
    PRE: quadra e arquivo onde irá ser salvo o SVG
*/
void quadraDesenhaSvgGeo(Quadra quadra, void* fileSvg);

/*
    Escreve uma tag SVG da quadra no arquivo passado
    PRE: quadra e arquivo onde irá ser salvo o SVG
*/
void quadraDesenhaSvgQry(Quadra quadra, void* fileSvgQry);

#endif
