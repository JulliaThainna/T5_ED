#ifndef __ENDERECO_H
#define __ENDERECO_H

#include "point.h"
#include "quadra.h"

typedef void* Endereco;

/*Create
Função responsável para criar Endereco. 
PRE: Quadra do qual o endereço fará parte, ou seja, o cep; Cpf do morador; face, número e complemento do endereço
POS: Retorna um pointer instanciado.
*/
Endereco criaEndereco(Quadra quad, char* cpf, char face, int num, char* compl);

/*
Setters: Define o atributo do título da função
PRE: Objeto e atributo
*/
void enderecoSetCpf(Endereco endereco, char* cpf);
void enderecoSetPoint(Endereco endereco, Point p);
void enderecoSetFace(Endereco endereco, char face);
void enderecoSetNum(Endereco endereco, int num);
void enderecoSetComplemento(Endereco endereco, char* compl);

/*
Getters: Retorna o atributo do título da função
PRE: Objeto
POS: Atributo especificado
*/
char* enderecoGetCpf(Endereco endereco);
Point enderecoGetPoint(Endereco endereco);
char enderecoGetFace(Endereco endereco);
int enderecoGetNum(Endereco endereco);
char* enderecoGetComplemento(Endereco endereco);
char* enderecoGetCep(Endereco endereco);

/*
    Troca dois enderecos de lugar na memória
    PRE: endereço 1 e endereço 2
*/
void enderecoSwap(Endereco e1, Endereco e2);

#endif