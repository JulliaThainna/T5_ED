#ifndef __UTILITARIO_H
#define __UTILITARIO_H


/*
Verifica se um ponto é interno ao circulo
PRE: Coordenadas do Circulo e do ponto
POS: -1: Impossivel/ 0: Externo/ 1: Interno/ 2: Borda
*/
int insideCirculo(float x, float y, float cx, float cy, float r);
/*
Verifica se um ponto é interno ao retangulo
PRE: Coordenadas do Retangulo e do ponto
POS: -1: Impossivel/ 0: Externo/ 1: Interno/ 2: Borda
*/
int insideRetangulo(float x, float y, float rx, float ry, float rw, float rh);
/*
Calcula a distancia quadrada (entre dois pontos)
Pré: As coordenadas dos dois pontos (x1, y1 e x2, y2)
Pós: Retorna um float referente a distância dos dois pontos
*/
float distanciaQuadrada(float x1, float  y1, float  x2, float  y2);

/*
Calcula a distancia entre dois pontos
PRE: Coordenadas dos dois pontos
POS: distancia
*/
float distanciaEntrePontos(float x1, float  y1, float  x2, float  y2);

//Calcula o min de 2 valores;
//a, b - valores especificados;
int min(int a, int b);

//Calcula o max de 2 valores;
//a, b - valores especificados;
int max(int a, int b);

//Calcula o min de 2 valores;
//a, b - valores especificados;
float minF(float a, float b);

//Calcula o max de 2 valores;
//a, b - valores especificados;
float maxF(float a, float b);

//Calcula o min de um vetor;
float minV(float v[], int tamanho);

//Calcula o max de um vetor;
float maxV(float v[], int tamanho);

/*
Calcula a area de uma lista de pontos
PRE: DoublyLinkedList l
POS: float area
*/
float calculaArea(DoublyLinkedList l);

/*
Calcula o centroide de uma lista de pontos e da área
PRE: DoublyLinkedList l e float area
POS: Point centroide
*/
Point centroide(DoublyLinkedList l, float area);

/*
Retorna 1 se existe a string char* info dentro de uma lista de strings e 0 se não existe
PRE: DoublyLinkedList list e char* info
POS: 1 (true)/ 0 (false) 
*/
int stringInDoublyLinkedList(DoublyLinkedList list, char* info);

#endif
