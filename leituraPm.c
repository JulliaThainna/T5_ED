#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "quadTree.h"
#include "hashTable.h"
#include "leituraPm.h"
#include "pessoa.h"
#include "endereco.h"
#include "processaGeo.h"
/*
CHAVE X VALOR
HASHTABLE 0 cpf X endereço: -M (PM)                                            
HASHTABLE 1 tipo-estabelecimento-comercial X descrição: - T (EC)
HASHTABLE 2 cpf X Pessoa - P (PM)
HASHTABLE 3 cep X quadra: - QUADRA (GEO)

*/
enum LISTAS{CIRCULO, RETANGULO, TEXTO, QUADRA, HIDRANTE, SEMAFORO, RADIOBASE, POSTOSAUDE, LINHA, LOCALCASOS, POLIGONO, ESTABELECIMENTO, ENDERECOS};
enum HASHTABLE{CPF_ENDERECO, TIPO_DESCRICAO, CPF_DADOS, CEP_QUADRA};

void readPm(QuadTree* qt, HashTable* ht, char* dirPm){

    DoublyLinkedList listaEnderecos = create();
    DoublyLinkedList listaEnderecos2 = create();

    FILE* filePm = NULL;
    filePm = fopen(dirPm, "r");
    if(!filePm){
        exit(1);
    }
    printf("Arquivo PM aberto com sucesso!");

    //Parametros
    char comando[200], cpf[300], nome[300], sobrenome[300], sexo, nasc[110], cep[200], face, compl[100];
    int num;

    while(1){
        fscanf(filePm, "%s", comando);

        if(feof(filePm)){
            break;
        }

        else if(strcmp(comando, "p") == 0){
            fscanf(filePm, "%s %s %s %c %s", cpf, nome, sobrenome, &sexo, nasc);
            Pessoa pessoa = criaPessoa(cpf, nome, sobrenome, sexo, nasc);
            char* pessoaCpf = (char*)malloc(sizeof(char) * (strlen(cpf) + 1));
            strcpy(pessoaCpf, cpf);
            insertValueHashTable(ht[CPF_DADOS], pessoaCpf, pessoa);
        }

        else if(strcmp(comando, "m") == 0){
            fscanf(filePm, "%s %s %c %d %s", cpf, cep, &face, &num, compl);
            Quadra qAux = getInfoByIdQt(qt[QUADRA], cep);
            if(qAux == NULL){
                return;
            }
            Endereco endereco = criaEndereco(qAux, cpf, face, num, compl);
            Endereco endereco2 = criaEndereco(qAux, cpf, face, num, compl);
            insert(listaEnderecos, endereco);
            insert(listaEnderecos2, endereco2);
        }
    }

    qt[ENDERECOS] = criaQt(enderecoGetCpf);
    DoublyLinkedListToQuadTree(listaEnderecos2, qt[ENDERECOS], enderecoGetPoint, enderecoSwap);
    for(Node aux = getFirst(listaEnderecos); aux != NULL; aux = getNext(aux)){
        Endereco endereco = getInfo(aux);
        insertValueHashTable(ht[CPF_ENDERECO], enderecoGetCpf(endereco), endereco);
    }

    removeList(listaEnderecos, 0);
    removeList(listaEnderecos2, 0);

    fclose(filePm);
}
