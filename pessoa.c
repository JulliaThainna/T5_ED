#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "pessoa.h"

typedef struct {
    char cpf[200];
    char nome[300];
    char sobrenome[300];
    char sexo;
    char dataNascimento[110];
}PessoaStruct;

Pessoa criaPessoa(char* cpf, char* nome, char* sobrenome, char sexo, char* dataNascimento){
    PessoaStruct* pessoa = (PessoaStruct*)malloc(sizeof(PessoaStruct));
    strcpy(pessoa->cpf,cpf);
    strcpy(pessoa->nome,nome);
    strcpy(pessoa->sobrenome,sobrenome);
    pessoa->sexo = sexo;
    strcpy(pessoa->dataNascimento,dataNascimento);
    return pessoa;
}

//Setters
void pessoaSetCpf(Pessoa pessoa, char* cpf){
    PessoaStruct* p = (PessoaStruct*)pessoa;
    strcpy(p->cpf, cpf);

}

void pessoaSetNome(Pessoa pessoa, char* nome){
    PessoaStruct* p = (PessoaStruct*)pessoa;
    strcpy(p->nome, nome);

}

void pessoaSetSobrenome(Pessoa pessoa, char* sobrenome){
    PessoaStruct* p = (PessoaStruct*)pessoa;
    strcpy(p->sobrenome, sobrenome);

}

void pessoaSetSexo(Pessoa pessoa, char sexo){
    PessoaStruct* p = (PessoaStruct*)pessoa;
    p->sexo = sexo;

}

void pessoaSetNascimento(Pessoa pessoa, char* nascimento){
    PessoaStruct* p = (PessoaStruct*)pessoa;
    strcpy(p->dataNascimento, nascimento);

}


//Getters
char* pessoaGetCpf(Pessoa pessoa){
    PessoaStruct* p = (PessoaStruct*)pessoa;
    return p->cpf;
}

char* pessoaGetNome(Pessoa pessoa){
    PessoaStruct* p = (PessoaStruct*)pessoa;
    return p->nome;

}

char* pessoaGetSobrenome(Pessoa pessoa){
    PessoaStruct* p = (PessoaStruct*)pessoa;
    return p->sobrenome;

}

char pessoaGetSexo(Pessoa pessoa){
    PessoaStruct* p = (PessoaStruct*)pessoa;
    return p->sexo;

}

char* pessoaGetNascimento(Pessoa pessoa){
    PessoaStruct* p = (PessoaStruct*)pessoa;
    return p->dataNascimento;

}

int pessoaGetSize(){
    return sizeof(PessoaStruct);
}