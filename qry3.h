#ifndef __QRY3_H
#define __QRY3_H

#include "quadTree.h"
#include "graph.h"
/*
Foram detectados n casos de COVID-19 no endereço cep,face,num.
PRE: informações de cep face num, qts, casos de covid
POS: SVG: colocar um pequeno quadrado (cor
laranja) no endereço com o número n
dentro (cor branca).
*/
void cv(QuadTree* qt, int casosCovid, char* cep, char face, int num);

/*
Encapsula insert na lista para percorreLargura qt
PRE: Info e Lista
POS: lista com info inserida
*/
void convertQtToList(Info info, DoublyLinkedList lista);

/*
Converte cep face num para um ponto x e y
PRE: cep face num e pointer para x e y
POS: x e y com pontos corretos de cep face num
*/
void convertLocalCasosToPoint(QuadTree qt, char* cep, char face, int num, float* cx, float* cy);

/*
Morador do endereço cep,face,num precisa
de atendimento. Determine os k postos de
atendimento mais próximos.
PRE: numero k de postos, cep face num do endereço
POS:
SVG: colocar um pequeno quadrado azul
com bordas brancas no endereço. Traçar
um segmento de reta tracejada do endereço
até cada um dos k postos de atendimento.
TXT: escrever as coordenadas dos postos
de atendimento
*/
void soc(QuadTree* qt, Graph graph, int k, char* cep, char face, int num, FILE* fileTxt, int id, FILE* fileSvgQry);

/*
Determinar a região de incidência relativa
aos casos (comando cv) reportados dentro
da região delimitada pela circunferência de
cento em (x,y) e raio r. Determinar a
categoria da região. Se necessário sugerir
um posto de atendimento no centróide da
região.
PRE: Coordenadas de um circulo, qts, e file para log
POS:
SVG: Desenhar o circulo sem
preenchimento e com borda grossa verde.
Desenhar a região de incidência (envoltória
convexa). Usar borda grossa na cor
vermelha e preencher com fundo
transparente na cor relativa à respectiva
categoria.
TXT: coordenadas dos casos selecionados
pelo círculo, o número total de casos, a
área dentro da envoltória convexa e a
categoria de incidência.
*/
void ci(QuadTree* qt, float x, float y, float r, FILE* fileTxt);

#endif