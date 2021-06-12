#ifndef __SEMAFORO_H
#define __SEMAFORO_H

#include "point.h"

typedef void* Semaforo; //Cria um tipo Semaforo que guarda void*

/*
Função responsável para criar Semaforo.
PRE: Id do semaforo, coordenadas x,y; cor de preenchimento; cor da borda; espessura da borda
POS: Retorna um pointer instanciado.
*/
Semaforo criaSemaforo(char* id, float x, float y, char* cp, char* cb, char* sw); //Cria um novo Semaforo

/*
Setters: Define o atributo do título da função
PRE: Objeto e atributo
*/
void semaforoSetId(Semaforo semaforo, char* id); //Seta um novo valor para o id do Semaforo
void semaforoSetX(Semaforo semaforo, float x);
void semaforoSetY(Semaforo semaforo, float y);
void semaforoSetPoint(Semaforo semaforo, Point point);
void semaforoSetCorPreenchimento(Semaforo semaforo, char* cp);
void semaforoSetCorBorda(Semaforo semaforo, char* cb);
void semaforoSetEspessura(Semaforo semaforo, char* sw);
/*
Getters: Retorna o atributo do título da função
PRE: Objeto
POS: Atributo especificado
*/
char* semaforoGetId(Semaforo semaforo); //Retorna o valor atual do id do Semaforo
float semaforoGetX(Semaforo semaforo);
float semaforoGetY(Semaforo semaforo);
Point semaforoGetPoint(Semaforo semaforo);
char* semaforoGetCorPreenchimento(Semaforo semaforo);
char* semaforoGetCorBorda(Semaforo semaforo);
char* semaforoGetEspessura(Semaforo semaforo);

/*
    Troca dois semaforos de lugar na memória
    PRE: semaforo 1 e semaforo 2
*/
void semaforoSwap(Semaforo s1, Semaforo s2);


/*
    Escreve uma tag SVG do semaforo no arquivo passado
    PRE: Semaforo e arquivo onde irá ser salvo o SVG
*/
void semaforoDesenhaSvgGeo(Semaforo semaforo, void* fileSvg);

#endif
