#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "doublyLinkedList.h"

typedef struct node {
    struct node* ant;
    Info info;
    struct node* prox;
}NodeStruct;

typedef struct{
    NodeStruct* primeiro;
    NodeStruct* ultimo;
    int size;
    int isEmpty;
}ListaStruct;

DoublyLinkedList create(){
    ListaStruct* list = (ListaStruct*)malloc(sizeof(ListaStruct));
    list->primeiro = NULL;
    list->ultimo = NULL;
    list->size = 0;
    list->isEmpty = 1;
    return list;
}

void insert(DoublyLinkedList lista, Info info){ //Pra inserir eu preciso saber qual é a lista e a informação a ser guardada
    ListaStruct* list = (ListaStruct*)lista;
    NodeStruct* node = (NodeStruct*)malloc(sizeof(NodeStruct));
    if(list->primeiro == NULL){
        node->info = info;
        node->ant = NULL;
        node->prox = NULL;
        list->primeiro = node;
        list->ultimo = node;
        list->isEmpty = 0;
    }
    else{
        node->info = info;
        node->prox = NULL;
        node->ant = list->ultimo;
        list->ultimo->prox = node;
        list->ultimo = node;
    }
    list->size++;
}

int getSize(DoublyLinkedList lista){
    ListaStruct* list = (ListaStruct*)lista;
    return list->size;
}

int isEmpty(DoublyLinkedList lista){
    ListaStruct* list = (ListaStruct*)lista;
    return list->isEmpty;
}

Info getInfoByIndex(DoublyLinkedList lista, int i){
    Info info;
    Node node;
    int j = 0;
    node = getFirst(lista);
    if(node == NULL){
        return NULL;
    }
    while (j < i) {
        node = getNext(node);
        j++;
        if(node == NULL){
            return NULL;
        }
    }
    info = getInfo(node);
    return info;
}



Info getInfo(Node node){
    NodeStruct* nod = (NodeStruct*)node;
    return nod->info;
}


Node getFirst(DoublyLinkedList lista){
    ListaStruct* list = (ListaStruct*)lista;
    return list->primeiro;
}


Node getLast(DoublyLinkedList lista){
    ListaStruct* list = (ListaStruct*)lista;
    return list->ultimo;
}


Node getPrevious(Node node){
    NodeStruct* nod = (NodeStruct*)node;
    return nod->ant;
}


Node getNext(Node node){
    NodeStruct* nod = (NodeStruct*)node;
    return nod->prox;
}


void insertBefore(DoublyLinkedList lista, Node node, Info info){
    NodeStruct* nod = (NodeStruct*)node;
    ListaStruct* list = (ListaStruct*)lista;
    NodeStruct* newNode = (NodeStruct*)malloc(sizeof(NodeStruct));
    newNode->info = info;

    nod->ant->prox = newNode; 
    newNode->ant = nod->ant;
    nod->ant = newNode;
    newNode->prox = nod;

    if(nod->ant == NULL){
        list->primeiro = newNode;
    }
    list->size++;
}


void insertAfter(DoublyLinkedList lista, Node node, Info info){
    NodeStruct* nod = (NodeStruct*)node;
    ListaStruct* list = (ListaStruct*)lista;
    NodeStruct* newNode = (NodeStruct*)malloc(sizeof(NodeStruct));
    newNode->info = info;

    newNode->prox = nod->prox;
    nod->prox = newNode;
    newNode->ant = nod;
    newNode->prox->ant = newNode;
    
    if(nod->prox == NULL){
        list->ultimo = newNode;
    }
    list->size++;
}


void removeNode(DoublyLinkedList lista, Node node, int flag){
    NodeStruct* nod = (NodeStruct*)node;
    ListaStruct* list = (ListaStruct*)lista;

    if(nod->prox == NULL && nod->ant == NULL){
        list->primeiro = NULL;
        list->ultimo = NULL;
        if(flag == 1){
            free(nod->info);
        }
        free(nod);
        list->size--;
        list->isEmpty = 1;
        return;
    }
    if(nod->ant == NULL){
        nod->prox->ant = NULL;
        list->primeiro = nod->prox;
        if(flag == 1){
            free(nod->info);
        }
        free(nod);
        list->size--;
        return;
    }
    if(nod->prox == NULL){
        nod->ant->prox = NULL;
        list->ultimo = nod->ant;
        if(flag == 1){
            free(nod->info);
        }   
        free(nod);
        list->size--;
        return;
    }

    nod->ant->prox = nod->prox;
    nod->prox->ant = nod->ant;
    if(flag == 1){
        free(nod->info);
    }
    free(nod);
    list->size--;
}


void removeList(DoublyLinkedList lista, int flag){
    ListaStruct* list = (ListaStruct*) lista;
    NodeStruct* inicio = list->primeiro;

    NodeStruct* aux = NULL;
    while(inicio != NULL){
        aux = inicio;
        inicio = inicio->prox;
        if(flag == 1){
            free(getInfo(aux));
        }
        free(aux);
    }
    free(list);
}