#ifndef __DOUBLYLINKEDLIST_H
#define __DOUBLYLINKEDLIST_H

typedef void* DoublyLinkedList;
typedef void* Info;
typedef void* Node;

/*
Instancia uma nova lista (malloc e retorna o void*)
POS: pointer da lista
*/
DoublyLinkedList create();

/*
Adiciona um novo Node na lista com Info
PRE: DoublyLinkedList lista e Info info
*/
void insert(DoublyLinkedList lista, Info info);

/*
Retorna o numero de nodes da lista
*/
int getSize(DoublyLinkedList lista);

/*
Retorna 1 se a lista estiver vazia e 0 se não estiver
*/
int isEmpty(DoublyLinkedList lista);

/*
Retorna a informação dentro do index i
PRE: lista e int i
POS: informação (NULL se for outofboudaries exception)
*/
Info getInfoByIndex(DoublyLinkedList lista, int i);

/*
Retorna a Info do Node
PRE: Node node
POS: Info info
*/
Info getInfo(Node node);

/*
Retorna o 1º Node da lista
PRE: DoublyLinkedList lista
POS: Node node
*/
Node getFirst(DoublyLinkedList lista);

/*
Retorna o último Node da lista
PRE: DoublyLinkedList lista
POS: Node node
*/
Node getLast(DoublyLinkedList lista);

/*
Retorna o elemento anterior de um Node
PRE: Node node
POS: Node node
*/
Node getPrevious(Node node);

/*
Retorna o próximo elemento de um Node
PRE: Node node
POS: Node node
*/
Node getNext(Node node);

/*
Insere um elemento antes do elemento passado
PRE: DoublyLinkedList lista, Node node, Info info
*/
void insertBefore(DoublyLinkedList lista, Node node, Info info);

/*
Insere um elemento depois do elemento passado
PRE: DoublyLinkedList lista, Node node, Info info
*/
void insertAfter(DoublyLinkedList lista, Node node, Info info);

/*
Remove o Node especificado da lista
PRE: DoublyLinkedList lista, Node node
*/
void removeNode(DoublyLinkedList lista, Node node, int flag);

/*
Remove uma lista
PRE: DoublyLinkedList lista
*/
void removeList(DoublyLinkedList lista, int flag);

#endif