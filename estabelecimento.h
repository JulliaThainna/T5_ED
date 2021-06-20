#ifndef __ESTABELECIMENTO_H
#define __ESTABELECIMENTO_H

#include "quadra.h"
#include "point.h"

typedef void* Estabelecimento;

/*Create
Função responsável para criar Estabelecimento. 
PRE: 
POS: Retorna um pointer instanciado.
*/
Estabelecimento criaEstabelecimento(Quadra quad, char* cnpj, char* cpf, char* nome, char* codt, char face, int num);

/*
Getters: Retorna o atributo do título da função
PRE: Objeto
POS: Atributo especificado
*/
char* estabelecimentoGetCep(Estabelecimento estabelecimento);
char* estabelecimentoGetCodt(Estabelecimento estabelecimento);
char* estabelecimentoGetCpf(Estabelecimento estabelecimento);
char* estabelecimentoGetCnpj(Estabelecimento estabelecimento);
char* estabelecimentoGetNome(Estabelecimento estabelecimento);
Point estabelecimentoGetPoint(Estabelecimento estabelecimento);
char estabelecimentoGetFace(Estabelecimento estabelecimento);
int estabelecimentoGetNum(Estabelecimento estabelecimento);

/*
    Troca dois estabelecimentos de lugar na memória
    PRE: estabelecimento 1 e estabelecimento 2
*/
void estabelecimentoSwap(Estabelecimento e1, Estabelecimento e2);

//Retorna o tamanho do estabelecimento em bytes
int estabelecimentoGetSize();

/*
Retorna o X do estabelecimento (x que não esta dentro do point)
*/
float estabelecimentoGetX(Estabelecimento estabelecimento);
/*
Retorna o Y do estabelecimento (y que não esta dentro do point)
*/
float estabelecimentoGetY(Estabelecimento estabelecimento);
//Define o ponto de um estabelecimento
void estabelecimentoSetPoint(Estabelecimento estabelecimento, float x, float y);
#endif