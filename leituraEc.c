#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "leituraEc.h"
#include "quadTree.h"
#include "doublyLinkedList.h"
#include "hashTable.h"
#include "estabelecimento.h"
#include "processaGeo.h"
#include "quadra.h"

/*
CHAVE X VALOR
HASHTABLE 0 cpf X endereço:                                                 
HASHTABLE 1 tipo-estabelecimento-comercial X descrição:
HASHTABLE 2 dados de uma pessoa: dado um cpf, retorna os dados pessoais daquela pessoa
HASHTABLE 3 cep X quadra:

*/

enum LISTAS{CIRCULO, RETANGULO, TEXTO, QUADRA, HIDRANTE, SEMAFORO, RADIOBASE, POSTOSAUDE, LINHA, LOCALCASOS, POLIGONO, ESTABELECIMENTO, ENDERECOS};
enum HASHTABLE{CPF_ENDERECO, TIPO_DESCRICAO, CPF_DADOS, CEP_QUADRA};

void readEc(QuadTree* qt, HashTable* ht, char* dirEc){
    DoublyLinkedList listaEstabelecimentos = create();

    FILE* fileEc = NULL;
    fileEc = fopen(dirEc, "r");
    if(!fileEc){
        exit(1);
    }
    printf("Arquivo EC aberto com sucesso!");

        //Parametros
        char comando[2], codt[30], descricao[30], cnpj[30], cpf[30], cep[20], face, nome[30];
        int num;

    while(1){
        fscanf(fileEc, "%s", comando);
        
        if(feof(fileEc)){
            break;
        }

        else if(strcmp(comando, "t") == 0){
            fscanf(fileEc, "%s %s", codt, descricao);
            char* chave = (char*)malloc(sizeof(char) * (strlen(codt) + 1));
            char* valor = (char*)malloc(sizeof(char) * (strlen(descricao) + 1));
            strcpy(chave, codt);
            strcpy(valor, descricao);
            insertValueHashTable(ht[TIPO_DESCRICAO], chave, valor);
        }
        else if(strcmp(comando, "e") == 0){
            fscanf(fileEc, "%s %s %s %s %c %d %s", cnpj, cpf, codt, cep, &face, &num, nome);
            
            Quadra quadra = getInfoByIdQt(qt[QUADRA], cep);
            if(quadra == NULL){
                removeList(listaEstabelecimentos, 0);
                return;
            }   
            Estabelecimento estabelecimento = criaEstabelecimento(quadra, cnpj, cpf, nome, codt, face, num);
            insert(listaEstabelecimentos, estabelecimento);
        }
    }

    qt[ESTABELECIMENTO] = criaQt(estabelecimentoGetCnpj);
    DoublyLinkedListToQuadTree(listaEstabelecimentos, qt[ESTABELECIMENTO], estabelecimentoGetPoint, estabelecimentoSwap);

    fclose(fileEc);
}
