#include <stdio.h>
#include <stdlib.h>

#include "queue.h"

typedef struct node{
    struct node* ant;
    struct node* prox;
    QueueInfo info;
}NodeQueue;

typedef struct{
    NodeQueue* primeiro;
    NodeQueue* ultimo;
    int size;
    int isEmpty;
}QueueStruct;



Queue createQueue(){
    QueueStruct* queue = (QueueStruct*)malloc(sizeof(QueueStruct));
    queue->primeiro = NULL;
    queue->ultimo = NULL;
    queue->size = 0;
    queue->isEmpty = 1;
    return queue;
}


int isQueueEmpty(Queue queue){
    QueueStruct* q = (QueueStruct*)queue;
    return q->isEmpty;
}


int getQueueSize(Queue queue){
    QueueStruct* q = (QueueStruct*)queue;
    return q->size;
}


void enqueue(Queue queue, QueueInfo info){
    QueueStruct* q = (QueueStruct*)queue;
    NodeQueue* nod = (NodeQueue*)malloc(sizeof(NodeQueue));

    nod->prox = NULL;
    nod->info = info;

    if(q->isEmpty == 1){
        nod->ant = NULL;
        q->primeiro = nod;
        q->ultimo = nod;
        q->isEmpty = 0;
        q->size++;
        return;
    }
    q->ultimo->prox = nod;
    nod->ant = q->ultimo;
    q->ultimo = nod;
    q->size++;
}


QueueInfo dequeue(Queue queue){
    QueueStruct* q = (QueueStruct*)queue;
    NodeQueue* aux = q->primeiro;
    if(q->isEmpty == 1){
        return NULL;
    }
    if(q->size > 1){
        q->primeiro = q->primeiro->prox;
    }
    QueueInfo info = aux->info;
    q->size--;
    free(aux);
    if(q->size == 0){
        q->primeiro = NULL;
        q->ultimo = NULL;
        q->isEmpty = 1;
    }
    return info;
}


void deleteQueue(Queue queue){
    QueueStruct* q = (QueueStruct*)queue;
    free(q);
}
