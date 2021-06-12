#ifndef __QUEUE_H
#define __QUEUE_H

typedef void* QueueInfo;
typedef void* Queue;

/*
    Cria uma nova Queue
    POS: retorna queue
*/
Queue createQueue();

/*
    Verifica se a queue está vazia
    PRE: queue
    POS: 0 se não estiver e 1 se estiver
*/
int isQueueEmpty(Queue queue);

/*
    Retorna o tamanho da queue (numero de elementos)
    PRE: queue
    POS: numero de elementos
*/
int getQueueSize(Queue queue);

/*
    Adiciona um novo elemento na queue
    PRE: queue e elemento
*/
void enqueue(Queue queue, QueueInfo info);

/*
    Retira um elemento do topo da queue
    PRE: queue
    POS: elemento
*/
QueueInfo dequeue(Queue queue);

/*
    Desaloca a memória da queue (NÃO DESALOCA INFOS!!! É NECESSÁRIO TER UMA REFERENCIA PARA AS INFOS EM OUTRO LUGAR!!!)
    PRE: queue
*/
void deleteQueue(Queue queue);

#endif
