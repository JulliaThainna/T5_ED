#ifndef __PESSOA_H_
#define __PESSOA_H_

typedef void* Pessoa; 

/*Create
Função responsável para criar Pessoa. 
PRE: cpf da pessoa, nome e sobrenome, sexo biológico e data de nascimento
POS: Retorna um pointer instanciado.
*/
Pessoa criaPessoa(char* cpf, char* nome, char* sobrenome, char sexo, char* dataNascimento);


/*
Setters: Define o atributo do título da função
PRE: Objeto e atributo
*/
void pessoaSetCpf(Pessoa pessoa, char* cpf);
void pessoaSetNome(Pessoa pessoa, char* nome);
void pessoaSetSobrenome(Pessoa pessoa, char* sobrenome);
void pessoaSetSexo(Pessoa pessoa, char sexo);
void pessoaSetNascimento(Pessoa pessoa, char* nascimento);

/*
Getters: Retorna o atributo do título da função
PRE: Objeto
POS: Atributo especificado
*/
char* pessoaGetCpf(Pessoa pessoa);
char* pessoaGetNome(Pessoa pessoa);
char* pessoaGetSobrenome(Pessoa pessoa);
char pessoaGetSexo(Pessoa pessoa);
char* pessoaGetNascimento(Pessoa pessoa);

#endif