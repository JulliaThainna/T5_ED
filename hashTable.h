#ifndef __HASHTABLE_H
#define __HASHTABLE_H

typedef void *HashTable;
typedef void *HashData;
typedef void *InfoHash;

/*
    Cria e aloca uma hash table
    PRE: tamanho da HashTable (Número de listas)
    POS: Estrutura HashTable
*/
HashTable createHashTable(int tamHT);

/*
    Insere um novo par Chave Valor na hash table
    PRE: hashtable, chave e valor
*/
void insertValueHashTable(HashTable ht, char *key, InfoHash value);

/* 
    Verifica se uma determinada chave tem um valor associado na hashtable
    PRE: hashtable e chave
    POS: 0 se não existe valor associado e 1 se existe
*/
int isKeyHashTable(HashTable ht, char *key);

/*
    Retorna um valor referente a uma chave na hashtable
    PRE: Hashtable e chave
    POS: elemento caso e existe e NULL se não existir
*/
InfoHash getValue(HashTable ht, char *key);

/*
    Remove um par chave valor da hashtable
    PRE: hashtable e chave
*/
void removeKey(HashTable ht, char *key);

/*
    Remove todos os elementos da hashTable e desaloca a memória. NÃO DESALOCA AS INFOS. É NECESSÁRIO TER UMA REFERENCIA DELAS EM OUTRO LUGAR!!!
    PRE: hashTable
*/
void removeHashTable(HashTable ht);

/*
    Função que dado uma chave e o tamanho da hashtable retorna o valor hash (ou indice do vetor de listas)
    PRE: chave e tamanho da hashtable
    POS: indice ou valor hash
*/
int hashFunc(char *key, int tamHT);

#endif