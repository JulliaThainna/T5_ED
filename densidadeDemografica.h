#ifndef __DENSIDADE_DEMOGRAFICA_H
#define __DENSIDADE_DEMOGRAFICA_H

typedef void* DensidadeDemografica;

/*
Função responsável para criar DensidadeDemografica. 
PRE: Coordenadas x,y; Largura; Altura; Densidade Demográfica da região delimitada por x,y,w,h
POS: Retorna um pointer instanciado.
*/
DensidadeDemografica criaDensidadeDemografica(float x, float y, float w, float h, float d);

/*
Setters: Define o atributo do título da função
PRE: Objeto e atributo
*/
void densidadeDemograficaSetX(DensidadeDemografica densidade, float x);
void densidadeDemograficaSetY(DensidadeDemografica densidade, float y);
void densidadeDemograficaSetWidth(DensidadeDemografica densidade, float w);
void densidadeDemograficaSetHeight(DensidadeDemografica densidade, float h);
void densidadeDemograficaSetDensidadeDemografica(DensidadeDemografica densidade, float d);
void densidadeDemograficaSetPoint(DensidadeDemografica densidade, Point point);

/*
Getters: Retorna o atributo do título da função
PRE: Objeto
POS: Atributo especificado
*/
float densidadeDemograficaGetX(DensidadeDemografica densidade);
float densidadeDemograficaGetY(DensidadeDemografica densidade);
float densidadeDemograficaGetWidth(DensidadeDemografica densidade);
float densidadeDemograficaGetHeight(DensidadeDemografica densidade);
float densidadeDemograficaGetDensidadeDemografica(DensidadeDemografica densidade);
Point densidadeDemograficaGetPoint(DensidadeDemografica densidade);

#endif
