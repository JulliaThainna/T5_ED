#include <stdio.h>
#include <stdlib.h>

#include "stack.h"

typedef struct node{
    InfoStack info;
    struct node* ant;
    struct node* prox;
}NodeStruct;

typedef struct{
    NodeStruct* top;
    int size;
    int isEmpty;
}StackStruct;



Stack createStack(){
    StackStruct* stk = (StackStruct*)malloc(sizeof(StackStruct));
    stk->top = NULL;
    stk->isEmpty = 1;
    stk->size = 0;

    return stk;
}
//Quando se cria uma Stack, cria-se um endereço (stk) com o tamanho determinado
//da StackStruct, do qual é convetido para void*, já que o tipo da função
//retorna void* (Stack). Quando tem-se uma função como a isEmpty,
//esse endereço que era um void* (ou seja, sem tipo) é convertido para
//StackStruct* novamente e desta forma, consegue saber o tamanho alocado
//na memória e consequentemente, as suas informações

int isEmptyStack(Stack stack){
    StackStruct* stk = (StackStruct*)stack;
    return stk->isEmpty;
}


int sizeStack(Stack stack){
    StackStruct* stk = (StackStruct*)stack;
    return stk->size;
}


InfoStack topStack(Stack stack){
    StackStruct* stk = (StackStruct*)stack;
    if(stk->top != NULL){
        return stk->top->info;
    }
    return NULL;
}


void pushStack(Stack stack, InfoStack info){
    StackStruct* stk = (StackStruct*)stack;
    NodeStruct* nod = (NodeStruct*)malloc(sizeof(NodeStruct));

    if(stk->isEmpty == 1){ //stk->size == 0
        nod->ant = NULL;
        stk->isEmpty = 0;
    }
    else{
        nod->ant = stk->top;
    }
    nod->prox = NULL;
    nod->info = info;
    stk->top = nod;
    stk->size++;
}


void popStack(Stack stack, int flag){
    StackStruct* stk = (StackStruct*)stack;
    if(stk->isEmpty == 1){
        return;
    }
    NodeStruct* nodAux = stk->top;
    if(stk->size > 1){
        stk->top = nodAux->ant;
    }
    stk->top->prox = NULL;
    if(flag == 1){
        free(nodAux->info);
    }
    free(nodAux);
    stk->size--;
    if(stk->size == 0){
        stk->isEmpty = 1;
    }
}


void removeStack(Stack stack, int flag){
    while(isEmptyStack(stack) == 0){ //stk->isEmpty == 0 || !(stk->isEmpty)
        popStack(stack, flag);
    }
    free(stack);
}
