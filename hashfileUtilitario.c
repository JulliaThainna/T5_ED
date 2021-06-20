#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "trataString.h"
#include "hashFile.h"
#include "quadTree.h"
#include "hashTable.h"
#include "doublyLinkedList.h"

#include "estabelecimento.h"
#include "pessoa.h"
#include "endereco.h"
#include "item.h"
#include "processaGeo.h"

enum LISTAS{CIRCULO, RETANGULO, TEXTO, QUADRA, HIDRANTE, SEMAFORO, RADIOBASE, POSTOSAUDE, LINHA, LOCALCASOS, POLIGONO, ESTABELECIMENTO, ENDERECOS};
enum HASHTABLE{CPF_ENDERECO, TIPO_DESCRICAO, CPF_DADOS, CEP_QUADRA};

void insertAux(Info f, DoublyLinkedList l){
    insert(l, f);
}

void doublyLinkedListToHashFile(Hashfile hf, DoublyLinkedList l){
    for(Node node = getFirst(l); node != NULL; node = getNext(node)){
        fwriteRec(hf, getInfo(node));
    }
}

void doublyLinkedListToHashTable(HashTable ht, DoublyLinkedList l){
    for(Node node = getFirst(l); node != NULL; node = getNext(node)){
        insertValueHashTable(ht, itemGetKey(getInfo(node)), itemGetValue(getInfo(node)));
    }
}

void generateDatFiles(QuadTree* qt, HashTable* ht, char* arqDatK){

    //Verificações pra ver se or arquivo é null
    if(arqDatK == NULL){
        return;
    }
    char* nomeDat = NULL;
    extraiNome(arqDatK, &nomeDat);
    if(nomeDat == NULL){
        return;
    }

    //Declara os arquivos
    char fileEC[80], fileDes[80], fileP[80], fileEnd[80];

    //Concatena os nomes
    sprintf(fileEC,"%s-ec.dat", nomeDat);
    sprintf(fileDes,"%s-des.dat", nomeDat);
    sprintf(fileP,"%s-pes.dat", nomeDat);
    sprintf(fileEnd,"%s-end.dat", nomeDat);

    //Cria os hashfiles
    Hashfile hf[4];
    hf[0] = fcreateHF(fileEC,107,10,estabelecimentoGetSize(),20);
    hf[1] = fcreateHF(fileEnd,107,10,enderecoGetSize(),20);
    hf[2] = fcreateHF(fileDes,107,10,255,20);
    hf[3] = fcreateHF(fileP,107,10,pessoaGetSize(),20);

    //Cria as listas auxiliares
    DoublyLinkedList lAux[4];
    for(int i = 0; i < 4; i++){
        lAux[i] = create();
    }
    DoublyLinkedList lEst = create();
    DoublyLinkedList lEnd = create();

    percorreLarguraQt(qt[ESTABELECIMENTO], insertAux, lEst);
    for(Node node = getFirst(lEst); node != NULL; node = getNext(node)){
        insert(lAux[0], createItem(estabelecimentoGetCnpj(getInfo(node)), getInfo(node)));
    }

    percorreLarguraQt(qt[ENDERECOS], insertAux, lEst);
    for(Node node = getFirst(lEnd); node != NULL; node = getNext(node)){
        insert(lAux[0], createItem(enderecoGetCpf(getInfo(node)), getInfo(node)));
    }

    for(int i = 2; i < 4; i++){
        percorreHashTable(ht[i - 1], insertAux, lAux[i]);
    }

    fflush(stdin);
    fflush(stdout);
    //doublyLinkedListToHashFile(hf[3], lAux[3]);
    for(int i = 0; i < 4; i++){
        doublyLinkedListToHashFile(hf[i], lAux[i]);
        fcloseHF(hf[i]);
    }

}

void loadDatFiles(QuadTree* qt, HashTable* ht, char* arqDatU){

    //Verificações pra ver se or arquivo é null
    if(arqDatU == NULL){
        return;
    }
    char* nomeDat = NULL;
    extraiNome(arqDatU, &nomeDat);
    if(nomeDat == NULL){
        return;
    }

    //Declara os arquivos
    char fileEC[80], fileDes[80], fileP[80], fileEnd[80];

    //Concatena os nomes
    sprintf(fileEC,"%s-ec.dat", nomeDat);
    sprintf(fileDes,"%s-des.dat", nomeDat);
    sprintf(fileP,"%s-pes.dat", nomeDat);
    sprintf(fileEnd,"%s-end.dat", nomeDat);

    //Cria os hashfiles
    Hashfile hf[4];
    hf[0] = fopenHF(fileEC);
    hf[1] = fopenHF(fileEnd);
    hf[2] = fopenHF(fileDes);
    hf[3] = fopenHF(fileP);

    //Cria as listas auxiliares
    DoublyLinkedList lAux[4];
    for(int i = 0; i < 4; i++){
        lAux[i] = create();
    }

    fflush(stdin);
    fflush(stdout);

    for(int i = 0; i < 4; i++){
        dumpFileHF(hf[i], lAux[i], insertAux);
        fcloseHF(hf[i]);
    }

    DoublyLinkedList end = create();
    DoublyLinkedList est = create();

    for(Node node = getFirst(lAux[0]); node != NULL; node = getNext(node)){
        Estabelecimento e = itemGetValue(getInfo(node));
        estabelecimentoSetPoint(e, estabelecimentoGetX(e), estabelecimentoGetY(e));
        insert(est, e);
    }
    for(Node node = getFirst(lAux[1]); node != NULL; node = getNext(node)){
        Endereco e = itemGetValue(getInfo(node));
        enderecoSetPoint(e, enderecoGetX(e), enderecoGetY(e));
        insert(end, e);
    }
    //QuadTree DoublyLinkedListToQuadTree(DoublyLinkedList l, QuadTree qt, Point (*getPoint)(void*), void (*swapInfo)(void*,void*))
    DoublyLinkedListToQuadTree(est, qt[ESTABELECIMENTO], estabelecimentoGetPoint, estabelecimentoSwap);
    DoublyLinkedListToQuadTree(end, qt[ENDERECOS], enderecoGetPoint, enderecoSwap);
    //enum HASHTABLE{CPF_ENDERECO, TIPO_DESCRICAO, CPF_DADOS, CEP_QUADRA};

    for(int i = 1; i < 4; i++){
        doublyLinkedListToHashTable(ht[i - 1], lAux[i]);
        removeList(lAux[i], 0);
    }

    removeList(est, 0);
    removeList(end, 0);
    removeList(lAux[0], 0);

}
