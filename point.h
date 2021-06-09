#ifndef __POINT_H 
#define __POINT_H

typedef void* Point;

/*Create
Função responsável para criar Point. 
PRE: Coordenadas x,y do ponto
POS: Retorna um pointer instanciado.
*/
Point criaPoint(float x, float y);

/*
Getters: Retorna o atributo do título da função
PRE: Objeto
POS: Atributo especificado
*/
float getPointX(Point point);
float getPointY(Point point);

/*
Setters: Define o atributo do título da função
PRE: Objeto e atributo
*/
void setPointX(Point point, float x);
void setPointY(Point point, float y);

/*
Atribui o valor de um ponto ao outro
PRE: ponto 1 e ponto 2
*/
void atribuirPonto(Point p1, Point p2);

#endif 