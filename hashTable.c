#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "hashTable.h"
#include "doublyLinkedList.h"

typedef struct{
    int tamHT;
    DoublyLinkedList* hash;
} HashTableStruct;

typedef struct{
    char key[20];
    InfoHash value;
} HashDataStruct;

HashTable createHashTable(int tamHT){
    HashTableStruct* ht = (HashTableStruct*)malloc(sizeof(HashTableStruct));

    //Associa parâmetro
    ht->tamHT = tamHT;

    //Aloca o vetor de listas
    ht->hash = (DoublyLinkedList*)malloc(sizeof(DoublyLinkedList) * tamHT);

    //Inicia as DoublyLinkedList
    for(int i = 0; i < tamHT; i++){
        ht->hash[i] = create();
    }

    return ht;
}

void insertValueHashTable(HashTable ht, char* key, InfoHash value){
    //Converto o void* da hashtable para a struct
    HashTableStruct* hts = (HashTableStruct *)ht;

    //Crio um novo elemento HashDataStruct
    HashDataStruct* hds = (HashDataStruct *)malloc(sizeof(HashDataStruct));

    //Defino os valores
    strcpy(hds->key, key);
    hds->value = value;

    //Descobre o index que vou adicionar essa nova informação
    int index = hashFunc(key, hts->tamHT);

    //Insere essa nova informação na lista de index definido
    insert(hts->hash[index], hds);
}

int hashFunc(char* key, int tamHT){
    int soma = 0;

    //Percorro a string somando cada caractere ASCII
    for(int i = 0; (unsigned)i < strlen(key); i++){
        soma += key[i];
    }

    //index = soma mod(tamHT)
    int index = soma % tamHT;
    return index;
}

int isKeyHashTable(HashTable ht, char* key){
    /*
    descobrir qual lista a chave está
    percorrer a lista comparando se a chave da info é a chave que eu quero
    retornar 1 ou 0
    */

    //Converte a hashtable
    HashTableStruct* hts = (HashTableStruct*)ht;

    //Vê qual o index em que essa chave pode existir
    int index = hashFunc(key, hts->tamHT);

    //Percorre a lista tentando encontrar uma chave que seja igual
    for(Node aux = getFirst(hts->hash[index]); aux != NULL; aux = getNext(aux)){

        //Pega cada HashData dentro da lista e converte para HashDataStruct
        Info auxinfo = getInfo(aux);
        HashDataStruct* hdsAux = (HashDataStruct*)auxinfo; //

        //Pega a chave armazenada em hdsAux é a chave desejada
        int resultado = strcmp(hdsAux->key, key);
        //Verifica se a chave encontra é a chave desejada
        if(resultado == 0){
            //Caso seja, retorna 1 e encerra a função
            return 1;
        }
    }

    //Caso percorra toda a lista e não encontre a chave desejada, ela não existe, por isso retorna 0
    return 0;
}

InfoHash getValue(HashTable ht, char* key){
    /*
    descobrir qual lista a chave está
    percorrer a lista comparando se a chave da info é a chave que eu quero
    retorna a info
    */

    //Converte a hashtable
    HashTableStruct *hts = (HashTableStruct*)ht;

    //Vê qual o index em que essa chave pode existir
    int index = hashFunc(key, hts->tamHT);

    //Percorre a lista tentando encontrar uma chave que seja igual
    for(Node aux = getFirst(hts->hash[index]); aux != NULL; aux = getNext(aux)){

        //Pega cada HashData dentro da lista e converte para HashDataStruct
        HashDataStruct* hdsAux = (HashDataStruct*)getInfo(aux);

        //salva o resultado da comparação entre a chave armazenada em hdsAux e a chave desejada
        int resultado = strcmp(hdsAux->key, key);
        //Verifica se a chave encontrada é a chave desejada
        if(resultado == 0){
            //Caso seja, retorna a informação
            return hdsAux->value;
        }
    }

    //Se nenhuma chave for encontrada com esse valor retorna NULL
    return NULL;
}

//Nada no for
void removeKey(HashTable ht, char* key){
    /*
    descobrir qual lista a chave está
    percorrer a lista comparando se a chave da info é a chave que eu quero
    remover a info
    */

    //Converte a hashtable
    HashTableStruct* hts = (HashTableStruct*)ht;

    //Vê qual o index em que essa chave pode existir
    int index = hashFunc(key, hts->tamHT);

    //Percorre a lista tentando encontrar uma chave que seja igual
    Node inicio = getFirst(hts->hash[index]);
    while(inicio != NULL){
        Node aux = inicio;
        inicio = getNext(inicio);
        //Pega cada HashData dentro da lista e converte para HashDataStruct
        HashDataStruct* hdsAux = (HashDataStruct*)getInfo(aux);

        //Pega a chave armazenada em hdsAux é a chave desejada
        int resultado = strcmp(hdsAux->key, key);
        //Verifica se a chave encontrada é a chave desejada
        if(resultado == 0){
            //Caso seja, remove o node da lista
            //número 1 é uma flag que adicionamos com o pedro no último trabalho de última hora.
            //Quando flag = 1, a info dentro do node também é desalocada
            //Quando flag = 0, a info dentro do node NÃO é desalocada
            //Talvez a gente remova essa flag nesse trabalho após refatorar o Convex Hull
            removeNode(hts->hash[index], aux, 1);
        }
    }
}

void removeHashTable(HashTable ht){
    HashTableStruct* hts = (HashTableStruct*)ht;
    for(int i = 0; i < hts->tamHT; i++){ //Percorrer o vetor
        Node inicio = getFirst(hts->hash[i]);
        while(inicio != NULL){
            Node aux = inicio;
            inicio = getNext(inicio);
            HashDataStruct* hdsAux = (HashDataStruct*)getInfo(aux);
            free(hdsAux->value);
            removeNode(hts->hash[i], aux, 1);
        }
    }
    for(int i = 0; i < hts->tamHT; i++){
        free(hts->hash[i]);
    }
    free(hts->hash);
    free(hts);
}