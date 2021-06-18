#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "doublyLinkedList.h"
#include "hashFile.h"
#include "item.h"


typedef struct Hashfile{
    char filename[80];
    int nBaldes;
    int numRPB;
    int tamRec;
    int tamCh;
}HashfileStruct;

typedef struct{
    int nItens;
    Item* itens;
    long int next;
}Balde;

//Funções Auxiliares
int getKey(char *chave, int nbuckets) {
    //Gera uma chave 
    int aux = 0, res;
    int tamanho = strlen(chave);
    for (int i = 0; i < tamanho; i++) {
        aux += chave[i];
    }
    res = aux % nbuckets;
    return res;
}

//Escreve um balde no file
void fwriteBalde(FILE* file, Balde *b, int numRPB, int tamRec, int tamCh){
    fwrite(&b->nItens, sizeof(int), 1, file);
    for(int j = 0; j < numRPB; j++){
        fwrite(itemGetKey(b->itens[j]), sizeof(char),tamCh,file);
        fwrite(itemGetValue(b->itens[j]),tamRec,1,file);
    }
    fwrite(&b->next, sizeof(long int), 1, file);
}

//Lê um balde no file
void freadBalde(FILE* file, Balde *b, int numRPB, int tamRec, int tamCh){
    fread(&b->nItens, sizeof(int), 1, file);
    for(int j = 0; j < numRPB; j++){
        fread(itemGetKey(b->itens[j]), sizeof(char),tamCh,file);
        fread(itemGetValue(b->itens[j]),tamRec,1,file);
    }
    fread(&b->next, sizeof(long int), 1, file);
}

//Inicializa um novo balde
Balde inicializarBalde(int numRPB, int tamRec, int tamCh){
    Balde balde;
    balde.itens = (Item*)malloc(sizeof(Item) * numRPB);
    for(int i = 0; i < numRPB; i++){
        balde.itens[i] = alocarItem(tamCh, tamRec);
    }
    return balde;
}

//Desaloca um balde
void desalocarBalde(Balde balde, int numRPB){
    for(int i = 0; i < numRPB; i++){
        itemDesalocaValue(balde.itens[i]);
    }
    free(balde.itens);
}

//Funções Principais
Hashfile fcreateHF(char *nome,int nbuckets,int numRecPerBkt, int tamRec, int tamCh){
    HashfileStruct* hf = malloc(sizeof(HashfileStruct));
    FILE* file = fopen(nome,"wb");
    strcpy(hf->filename,nome);
    hf->nBaldes = nbuckets;
    hf->numRPB = numRecPerBkt;
    hf->tamRec = tamRec;
    hf->tamCh = tamCh;

    //Cria cabeçalho
    fwrite(nome,sizeof(char),80,file);
    fwrite(&nbuckets,sizeof(int),1,file);
    fwrite(&numRecPerBkt,sizeof(int),1,file);
    fwrite(&tamRec,sizeof(int),1,file);
    fwrite(&tamCh,sizeof(int),1,file);

    //Percorre e escreve chaves e valor
    int nItens = 0;
    long int next = -1;
    for(int i  = 0; i < nbuckets; i++){
        fwrite(&nItens, sizeof(int), 1, file);
        for(int j = 0; j < numRecPerBkt; j++){
            char* chave = "\0";
            char* valor = "\0";
            fwrite(chave,sizeof(char),tamCh,file);
            fwrite(valor,tamRec,1,file);
        }
        fwrite(&next, sizeof(long int), 1, file);
    }

    //Fecha e retorna o pointer
    fclose(file);
    return hf;
}


Hashfile fopenHF(char *nome){

    //Abre o arquivo
    FILE* file = fopen(nome,"rb");
    if(file == NULL){
        return NULL;
    }

    //Lê o cabeçalho
    HashfileStruct* hf = malloc(sizeof(HashfileStruct));
    fread(hf->filename,sizeof(char),80,file);
    fread(&hf->nBaldes,sizeof(int),1,file);
    fread(&hf->numRPB,sizeof(int),1,file);
    fread(&hf->tamRec,sizeof(int),1,file);
    fread(&hf->tamCh,sizeof(int),1,file);
    fclose(file);

    //Retorna pointer
    return hf;
}


int fwriteRec(Hashfile hf, Item buf){

    //Abre o arquivo
    HashfileStruct* h = (HashfileStruct*) hf;
    FILE* file = fopen(h->filename,"r+b");
    if(file == NULL){
        return 0;
    }

    //Lê o cabeçalho
    int posicao = getKey(itemGetKey(buf), h->nBaldes);
    int tamHf = 80*sizeof(char) + 4*sizeof(int);
    int tamBalde = sizeof(long int) + sizeof(int) + h->numRPB * (h->tamRec + h->tamCh * sizeof(char));
    fseek(file,tamHf + posicao * tamBalde, SEEK_SET);
    long int posIn = ftell(file);

    //Inicia o balde
    Balde balde = inicializarBalde(h->numRPB, h->tamRec, h->tamCh);
    freadBalde(file, &balde, h->numRPB, h->tamRec, h->tamCh);

    //Percorre até chegar no ponto desejado para escrever
    while (balde.nItens == h->numRPB){
        if(balde.next == -1){
            //Gerencia os baldes
            fseek(file, -tamBalde, SEEK_CUR);
            long int posAnt = ftell(file);
            fseek(file, 0, SEEK_END);
            posIn = ftell(file); 
            balde.next = posIn;
            fseek(file, posAnt, SEEK_SET);
            fwriteBalde(file, &balde, h->numRPB, h->tamRec, h->tamCh);
            balde.nItens = 0;
            balde.next = -1;
        }
        else{
            fseek(file, balde.next, SEEK_SET);
            posIn = ftell(file);
            freadBalde(file, &balde, h->numRPB, h->tamRec, h->tamCh);
        }
    }

    //Escreve nova chave e valor
    strcpy(itemGetKey(balde.itens[balde.nItens]), itemGetKey(buf));
    memcpy(itemGetValue(balde.itens[balde.nItens]), itemGetValue(buf), h->tamRec);
    balde.nItens++;
    fseek(file, posIn, SEEK_SET);
    fwriteBalde(file, &balde, h->numRPB, h->tamRec, h->tamCh);

    //Fecha o arquivo
    fclose(file);
    desalocarBalde(balde, h->numRPB);
    return 1;
}


int freadHF(Hashfile hf, char *ch, Item buf){

    HashfileStruct* h = (HashfileStruct*) hf;
    Item* i = (Item*) buf;
    //Abre o arquivo
    FILE* file = fopen(h->filename,"rb");
    if(file == NULL){
        return 0;
    }

    //Lê cabeçalho
    int posicao = getKey(ch, h->nBaldes);
    int tamHf = 80*sizeof(char) + 4*sizeof(int);
    int tamBalde = sizeof(long int) + sizeof(int) + h->numRPB * (h->tamRec + h->tamCh * sizeof(char));
    fseek(file,tamHf + posicao * tamBalde, SEEK_SET);
    Balde balde = inicializarBalde(h->numRPB, h->tamRec, h->tamCh);

    //Procura a chave desejada
    do{
        freadBalde(file, &balde, h->numRPB, h->tamRec, h->tamCh);
        for(int j = 0; j < balde.nItens; j++){
            //Verifica se essa é a chave certa
            if(strcmp(ch,itemGetKey(balde.itens[j])) == 0){
                Info aux = malloc(h->tamRec);
                memcpy(aux, itemGetValue(balde.itens[j]),h->tamRec);
                //Salva a informação no buf e retorna 1
                *i = createItem(itemGetKey(balde.itens[j]), aux);
                fclose(file);
                desalocarBalde(balde, h->numRPB);
                return 1;
            }
        }
    } while (balde.next != -1);

    //Caso não encontre a chave, fecha o arquivo e retorna 0
    fclose(file);
    desalocarBalde(balde, h->numRPB);
    return 0;
}

void dumpFileHF(Hashfile hf, Info F, PrintRecord p){
    HashfileStruct* h = (HashfileStruct*) hf;

    //Abre o arquivo
    FILE* file = fopen(h->filename,"rb");
    if(file == NULL){
        return;
    }

    //Lê tamanho do cabeçalho
    int tamHf = 80 * sizeof(char) + 4 * sizeof(int);
    fseek(file,tamHf, SEEK_SET);
    Balde balde = inicializarBalde(h->numRPB, h->tamRec, h->tamCh);

    //Percorre todos os baldes escrevendo as "chave: valor"
    for(int i = 0; i < h->nBaldes; i++){
        //Faz o gerenciamento de baldes
        freadBalde(file, &balde, h->numRPB, h->tamRec, h->tamCh);
        long int aux = ftell(file);
        while(1){
            for(int j = 0; j < balde.nItens; j++){
                Item item = alocarItem(h->tamCh, h->tamRec);
                strcpy(itemGetKey(item), itemGetKey(balde.itens[j]));
                memcpy(itemGetValue(item), itemGetValue(balde.itens[j]), h->tamRec);
                p(F, item);
            }
            if(balde.next == -1){
                break;
            }
            fseek(file,balde.next,SEEK_SET);
            freadBalde(file, &balde, h->numRPB, h->tamRec, h->tamCh);
        }
        fseek(file,aux,SEEK_SET);        
    }

    //Desaloca balde e fecha o arquivo
    desalocarBalde(balde, h->numRPB);
    fclose(file);
}
