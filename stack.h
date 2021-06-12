#ifndef __STACK_H
#define __STACK_H

typedef void* Stack;
typedef void* InfoStack;

/*
    Cria uma stack
    POS: retoan a stack
*/
Stack createStack();
/*
    Verifica se a stack está vazia
    PRE: stack
    POS: 0 se não está vazio e 1 se está
*/
int isEmptyStack(Stack stack);

/*
    Retorna o tamanho da stack 
    PRE: stack
    POS: numero de elementos
*/
int sizeStack(Stack stack);

/*
    Retorna o primeiro elemento da stack
    PRE: stack
    POS: elemento
*/
InfoStack topStack(Stack stack);

/*
    Insere um novo elemento na stack
    PRE: stack e elemento
*/
void pushStack(Stack stack, InfoStack info);

/*
    Retira o último elemento da stack
    PRE: stack e flag: 1 = desaloca info e 0 = não desaloca
*/
void popStack(Stack stack, int flag);

/*
    Desaloca stack
    PRE: stack e flag: 1 = desaloca info e 0 = não desaloca
*/
void removeStack(Stack stack, int flag);

#endif