#ifndef __QRY4_H
#define __QRY4_H

#include "quadTree.h"
#include "hashTable.h"

/*
Moradores da quadra cujo cep é cep. Mostra
mensagem de erro se quadra não existir.
PRE: qts, hashtables e cep
POS: TXT: listar todos os dados dos moradores(nome,
endereço,...)
*/
void m(QuadTree* qt, HashTable* ht, char* cep, FILE* fileTxt);

/*
Imprime todos os dados do morador identificado
pelo cpf.
PRE: tipo de estabelecimento, cep, qts, hts, fileTxt
POS: TXT: dados pessoais, seu endereço
SVG: colocar uma linha vertical do endereço do
morador até a margem superior do mapa. Anotar
ao lado da linha o cpf, nome e endereço do
morador
*/
void dm(QuadTree* qt, HashTable* ht, char* cpf, FILE* fileTxt);

/*
Imprime todos os dados do estabelecimento comercial identificado por cnpj.
PRE: qts, hts, cnpj, fileTxt
POS:
TXT: dados do estabelecimento (nome, descrição
do tipo, etc) e dados de seu proprietário.
*/
void de(QuadTree* qt, HashTable* ht, char* cnpj, FILE* fileTxt);

/*
A pessoa identificada por cpf muda-se para o
endereço determinado pelos parâmetros.
PRE: cpf cep face num compl, qts, hts, file para log
POS:
TXT: Mostrar os dados da pessoa (nome, etc), o
endereço antigo e o novo endereço.
Arquivo.
SVG: Uma linha vermelha grossa do endereço
antigo ao endereço novo. Um pequeno círculo
vermelho no endereço antigo, outro círculo azul
no novo endereço. Ambos círculos com borda
branca grossa.
*/
void mud(QuadTree* qt, HashTable* ht, char* cpf, char* cep, char face, int num, char* compl, FILE* fileTxt);

/*
Imprime o estado atual de uma árvore no arquivo arq.svg.
t informa qual das árvores: q: quadras; h: hidrantes; s: semáforos; t: torres;
Cada nó da árvore deve mostrar as coordenadas
do elemento armazenado e alguma informação
relevante sobre tal elemento (p.ex, o cep da
quadra, o identificador do hidrante, etc)
PRE: variaveis necessarias para criar o arquivo, sfx que é anexado ao fim do nome do arquivo
POS: Arvore impressa no arquivo
*/
void dmprbt(QuadTree* qt, char t, char* sfx, char* dirSaida, char* nomeGeoSemExtensao, char* nomeQrySemExtensao);

/*
Estabelecimentos comerciais do tipo tp (ou de
qualquer tipo, caso *) que estão inteiramente
dentro da região retangular especificada.
PRE: tipo de estabelecimento, pontos do retangulo
POS:
TXT: dados sobre os estabelecimentos comerciais,
incluindo o nome de seu proprietário.
SVG: Destacar o estabelecimento comercial
selecionado.

*/
void eplg(QuadTree* qt, HashTable* ht, char* tp, float x, float y, float w, float h, FILE* fileTxt);

/*
Remover as quadras, elementos urbanos,
moradores e estabelecimentos comerciais que
estejam inteiramente contidas na circunferência
de raio r e centro em
PRE: circulo x y de raio r, qts, hts, e file para logs
POS:
TXT: imprimir identificadores e dados associados
de tudo o que foi removido.
SVG: elementos removidos não devem aparecer.
Desenhar sob o mapa o referido circulo com cor
de preenchimento #CCFF00, cor de borda
#6C6753 e com 50% de transparência.
*/
void catac(QuadTree* qt, HashTable* ht, float x, float y, float r, FILE* fileTxt);

#endif