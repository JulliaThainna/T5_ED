#ifndef __QRY5_H
#define __QRY5_H

#include "graph.h"
#include "hashTable.h"
#include "point.h"

int indiceRegistrador(char* r);

/*
Verifica se a curva entre uma aresta e outra é pra esquerda ou direita
É chamado quando a aresta inicial está na horizontal
0 -> Esquerda
1 -> Direita
*/
int descreveCurvaHorizontal(Graph graph, Aresta i, Aresta f);

/*
Verifica se a curva entre uma aresta e outra é pra esquerda ou direita
É chamado quando a aresta inicial está na vertical
0 -> Esquerda
1 -> Direita
*/
int descreveCurvaVertical(Graph graph, Aresta i, Aresta f);

/*
Armazena no registrador r a posição
geográfica da residência do morador de cpf
cpf.
SVG: linha vertical com identificação do
registrador.
*/
void mInt(QuadTree* qt, HashTable* ht, Point* registrador, char* r, char* cpf);

/*
Armazena no registrador r a posição
geográfica do endereço cep/face/num
SVG: linha vertical com identificação do
registrador.
*/
void eInt(QuadTree* qt, HashTable* ht, Point* registrador, char* r, char* cep, char face, int num);

/*
Armazena no registrador r a posição
geográfica do equipamento urbano cujo
identificador é id
SVG: linha vertical com identificação do
registrador.
*/
void gInt(QuadTree* qt, Point* registrador, char* r, char* id);

/*
Armazena no registrador r a posição geográfica (x,y)
*/
void xy(QuadTree* qt, Point* registrador, char* r, float x, float y);

/*
Produza uma árvore geradora mínima que
representa as ciclovias implantadas na
cidade.
SVG (nomearq-sufx.svg): desenhar o grafo,
evidenciando as arestas que compõem a
árvore geradora mínima.
*/
Graph ccv(Graph graphVia, char* sfx, char* dirSaida, char* nomeGeoSemExtensao, char* nomeQrySemExtensao);

/*
Qual o melhor trajeto de carro entre a
origem que está que no registrador r1 e o
destino que está no registrador r2. O
percurso na representação pictórica deve
indicar o trajeto mais curto na cor cmc e o
trajeto mais rápido com a cor cmr.
TXT: descrição textual do percurso
SGV (nomearq-sufx.svg): traçar (linhas) os
percursos com as cores correspondentes.
Cuidado para que uma percurso não
esconda o outro. Indicar o início e o fim do
percurso. Caso sufx for -, continuar usando
o mesmo arquivo de um comando p?
anterior.
*/
void pInt(QuadTree* qt, Graph graph, Point* registradores, char* sfx, char* r1, char* r2, char* cmc, char* cmr, char* pathPIntSfx, int idPInt, char* pathPIntSfxTxt);

/*
Interditar trechos de ruas (face de quadra)
com mais que max casos de covid.
TXT: listar cep e face referente ao trecho
interditado e o número total de casos de
coviid naquela face.
SGV: desenhar um segmento de reta
vermelho e largo ao lado da face da
quadra, mas fora dela.
*/
void bf(QuadTree* qt, Graph graph, int max, FILE* fileTxt);

/*
Igual a p?, mas evita toda a região com
casos de covid. Evitar completamente a
região determinada pela envoltória convexa
dos casos de covid.
TXT: mesma saida de p?
SVG:mesma saida de p?.Também desenhar
a envoltória convexa com borda grossa,
preenchida com amarelo e transparência de
60%
*/

/*
Calcula o percurso por ciclo-
vias.Semelhante a p?, mas o cálculo deve
considerar a árvore geradora mínima.
Como o percurso é por bicicleta, o cálculo deve apenas
otimizar a distância a ser percorrida
*/

void pbInt(QuadTree* qt, Graph graph, Point* registradores, char* sfx, char* r1, char* r2, char* cmc, char* pathPbIntSfx, int idPbInt, char* pathPbIntSfxTxt);


void descreveTrajeto(Graph graph, DoublyLinkedList path, FILE* filetxt);

#endif