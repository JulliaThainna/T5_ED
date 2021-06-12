#ifndef __QRY2_H
#define __QRY2_H

#include "quadTree.h"

/*
    Função responsável pelo dq (Arredonda as quadras ou remove)
    PRE: qt, id da figura base, raio r, hashtag para ver se arredonda bordas ou deleta
    POS: Quadras com bordas arredondadas e cores diferentes ou removidas da qt
*/
void dq(QuadTree* qt, char* id, float r, int hashtag, FILE* fileTxt);

/*
    Remove uma quadra ou equipamento atraves de id/cep
    PRE: qts, id/cep e file txt para log
    POS: elemento ou quadra removido
*/
void del(QuadTree* qt, char* id, FILE* fileTxt);

/*
    Altera a cor das quadras dentro do circulo x, y e raio r
    PRE: parâmetros necessários para as cores e circulo, qt, fileTxt para log
    POS: cores das quadras alteradas na região
*/
void cbq(QuadTree* qt, float x, float y, float r, char* cstrk, FILE* fileTxt);

/*
    Imprime no arquivo .txt as coordenadas e a
    espécie do equipamento urbano de um
    determinado cep ou com uma determinada
    identificação. 
    PRE: cep ou id, qts e txt
    POS: imprime no txt as informações
*/
void crd(QuadTree* qt, char* id, FILE* fileTxt);

/*
    Calcula a área total das quadras e
    equipamentos urbanos que estiverem
    inteiramente dentro do retângulo (x,y,w,h).
    PRE: qts, pontos de um retangulo, file TXT
    POS:     No arquivo .svg: desenhar o retângulo da
    consulta e traçar uma linha vertical do
    ponto (x,y) até o topo do mapa. No topo do
    mapa, ao lado da linha vertical, escrever a
    área total. No centro de cada quadra
    selecionada, escrever a sua respectiva área.
    No arquivo .txt: escrever os ceps das
    quadras selecionadas e suas respectivas
    áreas. Escrever a área total.
*/
void car(QuadTree* qt, float x, float y, float w, float h, FILE* fileTxt);

#endif