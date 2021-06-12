#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "quadTree.h"
#include "doublyLinkedList.h"
#include "queue.h"
#include "point.h"

#include "utilitario.h"

enum COORDS {NW, NE, SW, SE};

#define dx 250
#define dy 250

typedef struct nodeQt{
    struct nodeQt* children[4];
    struct nodeQt* parent;
    Point point;
    QtInfo info;
}NodeQtStruct;

typedef struct{
    NodeQtStruct* root;
    char* (*fun)(QtInfo);
}QuadTreeStruct;



QuadTree criaQt(funcGetChave fun){
    QuadTreeStruct* qts = (QuadTreeStruct*)malloc(sizeof(QuadTreeStruct));
    qts->root = NULL;
    qts->fun = fun;
    return qts;
}


void insere(QuadTreeStruct* quadTree, NodeQtStruct* node){
    //Define aux e comparativos
    NodeQtStruct* aux = quadTree->root;
    //Define parent como NULL pois usa na condição
    node->parent = NULL;
    //Define children do elemento alocado para NULL
    for(int i = 0; i < 4; i++){
        node->children[i] = NULL;
    }
    //Se aux == NULL, então é a 1a inserção. Inserte e retorna o node
    if(aux == NULL){
        quadTree->root = node;
        return;
    }

    //Senão, procura até encontrar o lugar apropriado para adicionar
    do{
        //Define auxiliar   
        //Pega o ponto para comparação
        Point pAux = aux->point;

        Point p = node->point;
        //Vê se está a direita ou à esquerda
        if(getPointX(p) >= getPointX(pAux)){
            //Vê se está acima ou a baixo
            if(getPointY(p) >= getPointY(pAux)){
                //Se a posição encontrada estiver NULL, então está vazia. Adiciona o node
                if(aux->children[NE] == NULL){
                    aux->children[NE] = node;
                    node->parent = aux;
                }
                //Senão, atualiza o aux e repete mais uma vez
                else{
                    aux = aux->children[NE];
                }
            }
            else{
                if(aux->children[SE] == NULL){
                    aux->children[SE] = node;
                    node->parent = aux;
                }
                else{
                    aux = aux->children[SE];
                }
            }
        }
        else{
            if(getPointY(p) >= getPointY(pAux)){
                if(aux->children[NW] == NULL){
                    aux->children[NW] = node;
                    node->parent = aux;
                }
                else{
                    aux = aux->children[NW];
                }
            }
            else{
                if(aux->children[SW] == NULL){
                    aux->children[SW] = node;
                    node->parent = aux;
                }
                else{
                    aux = aux->children[SW];
                }
            }
        }
        //A condição do while só é quebrada quando a linha node->parent = aux é executada
    }while(node->parent == NULL);
}


QtNo insereQt(QuadTree qt, Point p, QtInfo pInfo){
    QuadTreeStruct* quadtree = (QuadTreeStruct*) qt;
    NodeQtStruct* node = (NodeQtStruct*)malloc(sizeof(NodeQtStruct));
    node->point = p;
    node->info = pInfo;
    insere(quadtree,node);
    return node;
}

QtInfo removeNoQt(QuadTree qt, QtNo pNo){
    QuadTreeStruct* quadtree = (QuadTreeStruct*) qt;
    NodeQtStruct* node = (NodeQtStruct*) pNo;
    NodeQtStruct* aux;
    int i;
    QtInfo info;

    Queue queue = createQueue();

    if(node->parent == NULL){
        for(i = 0; i < 4; i++){
            if(node->children[i] != NULL){
                enqueue(queue, node->children[i]);
            }
        }
        quadtree->root = NULL;
    }
    else{
        for(i = 0; i < 4; i++){
            if(node->parent->children[i] == node){
                node->parent->children[i] = NULL;
                break;
            }
        }
        for(i = 0; i < 4; i++){
            if(node->children[i] != NULL){
                if(node->parent->children[i] == NULL){
                    node->parent->children[i] = node->children[i];
                    node->children[i]->parent = node->parent;
                }
                else{
                    enqueue(queue, node->children[i]);
                }
            }
        }
    }

    while(getQueueSize(queue) != 0){
        aux = dequeue(queue);
        for(i = 0; i < 4; i++){
            if(aux->children[i] != NULL){
                enqueue(queue, aux->children[i]);
            }
        }
        insere(quadtree, aux);
    }
    info = getInfoQt(quadtree, node);
    free(node);
    deleteQueue(queue);
    return info;
}


QtNo getNoQt(QuadTree qt, double x, double y){
    //Realiza a mesma coisa que o insert. Porém, procura um ponto que já esteja inserido na quadtree que corresponde com o parâmetro
    //Retorna NULL se não encontrar
    QuadTreeStruct* quad = (QuadTreeStruct*) qt;
    NodeQtStruct* aux = quad->root;
    Point point;

    while(aux != NULL){
        point = aux->point;

        if(x == getPointX(point) && y == getPointY(point)){
            return aux;
        }

        if(x >= getPointX(point)){
            if(y >= getPointY(point)){
                aux = aux->children[NE];
            }
            else{
                aux = aux->children[SE];
            }
        }
        else{
            if(y >= getPointY(point)){
                aux = aux->children[NW];
            }
            else{
                aux = aux->children[SW];
            }
        }
    }
    return NULL;
}


Point getPontoQt(QuadTree qt, QtNo pNo){
    //Retorna um ponto de um Node da quadtree
    qt = qt;
    NodeQtStruct* node = (NodeQtStruct*) pNo;
    return node->point;
}


QtInfo getInfoQt(QuadTree qt, QtNo pNo){
    qt = qt;
    //Retorna a info de um Node da quadtree
    NodeQtStruct* node = (NodeQtStruct*)pNo;
    return node->info;
}


char* getChaveQt(QuadTree qt, QtNo pNo){
    //Converte
    QuadTreeStruct* quad = (QuadTreeStruct*)qt;
    NodeQtStruct* node = (NodeQtStruct*) pNo;
    //Chama a função getInfoQt que retorna a informação de um Node
    QtInfo aux = getInfoQt(qt, node);
    //Retorna a chave, já que fun é a função que retorna a chave de um elemento
    return quad->fun(aux);
}


QtInfo getInfoById(QuadTree qt, QtNo no, char* chave){
    //Converte
    NodeQtStruct* node = (NodeQtStruct*) no;
    QuadTreeStruct* quad = (QuadTreeStruct*)qt;
    //Pega a informação do node (a quadtree nesse parâmetro é completamente INUTIL mas está no TAD)
    QtInfo aux = getInfoQt(qt, node);
    //Se a chave da info do node é igual a chave passada como parâmetro, retorna a info
    if(strcmp(quad->fun(aux), chave) == 0){
        return aux;
    }
    //Senão, percorre os quatro children desse node procurando por uma info dentro de um node que possui uma chave correspondente
    for(int i = 0; i < 4; i++){
        if(node->children[i] != NULL){
            //Chama a função recursivamente
            aux = getInfoById(qt, node->children[i], chave);
            if(aux != NULL){
                //Se o aux não é NULL significa que ele retornou o que corresponde à chave, logo retorna o elemento
                return aux;
            }
        }
    }
    //Se percorreu todos os Node, chegou nas folhas e não encontrou nada que corresponde, não existe a chave na quadtree
    //logo, retorna null
    return NULL;
}


QtInfo getInfoByIdQt(QuadTree qt, char* chave){
    //Passa a quadtree e uma chave como parâmetro e espera o retorno da informação que corresponde com essa chave
    QuadTreeStruct* quad = (QuadTreeStruct*)qt;
    if(quad->root == NULL){
        return NULL;
    }
    //Chama a função getInfoById, que percoore a árvore analisando as informações e vendo qual corresponde
    return getInfoById(qt, quad->root, chave);
}


void desalocaNos(NodeQtStruct* node){
    //Se o node é NULL retorna sem fazer nada
    if(node == NULL){
        return;
    }
    //pega as childdren e realiza o mesmo processo recursivamente
    for(int i = 0; i < 4; i++){
        //Chama recursivamente a função
        desalocaNos(node->children[i]);
    }
    free(node->info);
    free(node->point);
    free(node);
}


void desalocaQt(QuadTree qt){
    QuadTreeStruct* quad = (QuadTreeStruct*)qt;
    desalocaNos(quad->root);
    free(qt);
}


void dentroRetanguloQt(QuadTree qt, NodeQtStruct* node, DoublyLinkedList l, double x1, double y1, double x2, double y2, void* (*fun)(void*, void*)){
    if(node == NULL){
        return;
    }
    if(insideRetangulo(getPointX(node->point), getPointY(node->point), x1, y1, x2-x1, y2-y1)){
        if(fun != NULL){
            insert(l, fun(qt, node));
        }
        else{
            insert(l, node);
        }
    }
    for(int i = 0; i < 4; i++){
        dentroRetanguloQt(qt, node->children[i], l, x1, y1, x2, y2, fun);
    }
}


void dentroCirculoQt(QuadTree qt, NodeQtStruct* node, DoublyLinkedList l, double x, double y, double r, void* (*fun)(void*, void*)){
    if(node == NULL){
        return;
    }
    float pX = getPointX(node->point);
    float pY = getPointY(node->point);
    if(insideCirculo(pX, pY, x, y, r)){
        if(fun != NULL){
            insert(l, fun(qt, node));
        }
        else{
            insert(l, node);
        }
    }
    for(int i = 0; i < 4; i++){
        dentroCirculoQt(qt, node->children[i], l, x, y, r, fun);
    }
}


void percorreProfundidade(QuadTree qt, NodeQtStruct* node, funcVisita f, ExtraInfo ei){
    if(node == NULL){
        return;
    }
    f(getInfoQt(qt, node), ei);
    for(int i = 0; i < 4; i++){
        percorreProfundidade(qt, node->children[i], f, ei);
    }
}


void percorreProfundidadeQt(QuadTree qt, funcVisita f, ExtraInfo ei){
    QuadTreeStruct* quad = (QuadTreeStruct*) qt;
    NodeQtStruct* node = quad->root;
    percorreProfundidade(qt, node, f, ei);
}


void percorreLarguraQt(QuadTree qt, funcVisita f, ExtraInfo ei){
    QuadTreeStruct* quad = (QuadTreeStruct*) qt;
    if(quad->root == NULL){
        return;
    }
    Queue queue = createQueue();
    enqueue(queue, quad->root);
    do{
        NodeQtStruct* aux = dequeue(queue);
        for(int i = 0; i < 4; i++){
            if(aux->children[i] != NULL){
                enqueue(queue, aux->children[i]);
            }
        }
        //O PARÂMETRO QT DESSA FUNÇÃO NÃO SERVE PRA NADA!!!!!
        f(getInfoQt(qt, aux), ei);
    }while(!isQueueEmpty(queue));
    
    deleteQueue(queue);
}


DoublyLinkedList chavesDentroRetanguloQt(QuadTree qt, double x1, double y1, double x2, double y2){
    QuadTreeStruct* quad = (QuadTreeStruct*) qt;
    NodeQtStruct* node = quad->root;
    DoublyLinkedList l = create();
    dentroRetanguloQt(qt, node, l, x1, y1, x2, y2, (void* (*)(void*, void*))getChaveQt);
    return l;
}


DoublyLinkedList chavesDentroCirculoQt(QuadTree qt, double x, double y, double r){ 
    QuadTreeStruct* quad = (QuadTreeStruct*) qt; 
    NodeQtStruct* node = quad->root;
    DoublyLinkedList l = create();
    dentroCirculoQt(qt, node, l, x, y, r, (void*(*)(void*,void*))getChaveQt);
    return l;
}


DoublyLinkedList pontosDentroRetanguloQt(QuadTree qt, double x1, double y1, double x2, double y2){
    QuadTreeStruct* quad = (QuadTreeStruct*) qt;
    NodeQtStruct* node = quad->root;
    DoublyLinkedList l = create();
    dentroRetanguloQt(qt, node, l, x1, y1, x2, y2, (void*(*)(void*,void*))getPontoQt);
    return l;
}


DoublyLinkedList pontosDentroCirculoQt(QuadTree qt, double x, double y, double r){
    QuadTreeStruct* quad = (QuadTreeStruct*) qt;
    NodeQtStruct* node = quad->root;
    DoublyLinkedList l = create();
    dentroCirculoQt(qt, node, l, x, y, r, (void*(*)(void*,void*))getPontoQt);
    return l;
}


DoublyLinkedList nosDentroCirculoQt(QuadTree qt, double x, double y, double r){
    QuadTreeStruct* quad = (QuadTreeStruct*) qt;
    NodeQtStruct* node = quad->root;
    DoublyLinkedList l = create();
    dentroCirculoQt(qt, node, l, x, y, r, NULL);
    return l;
}


DoublyLinkedList nosDentroRetanguloQt(QuadTree qt, double x1, double y1, double x2, double y2){
    QuadTreeStruct* quad = (QuadTreeStruct*) qt;
    NodeQtStruct* node = quad->root;
    DoublyLinkedList l = create();
    dentroRetanguloQt(qt, node, l, x1, y1, x2, y2, NULL);
    return l;
}

void desenhaNosQt(QuadTreeStruct* qt, NodeQtStruct* no, FILE* svg, float* x, float y, DoublyLinkedList ant){
    if(no == NULL){
        return;
    }
    DoublyLinkedList atual = create();
    for(int i = 0; i < 2; i++){
        desenhaNosQt(qt, no->children[i], svg, x, y + dy, atual);
    }
    *x += dx;
    float aux = *x;
    fprintf(svg, "<rect x='%lf' y='%lf' width='240' height='14' fill='none' stroke='tomato' stroke-width=\"3px\" />\n", aux-120, y - 10);
    fprintf(svg, "\t<text x=\"%lf\" y=\"%lf\" text-anchor=\"middle\">%s: %lf,%lf</text>\n",aux, y + 2, qt->fun(getInfoQt(qt, no)), getPointX(no->point), getPointY(no->point));
    if(ant != NULL){
        insert(ant, criaPoint(aux, y - 10));
    }
    else{
        fprintf(svg, "\t<circle cx=\"%lf\" cy=\"%lf\" r=\"5\" fill=\"blue\"/>\n", aux, y - 150);
        fprintf(svg, "\t<line x1=\"%lf\" y1=\"%lf\" x2=\"%lf\" y2=\"%lf\" style=\"stroke: tomato; stroke-width: 3\" />\n", aux, y + 2, aux, y - 150);
    }
    for(int i = 2; i < 4; i++){
        desenhaNosQt(qt, no->children[i], svg, x, y + dy, atual);
    }
    for(Node node = getFirst(atual); node != NULL; node = getNext(node)){
        fprintf(svg, "\t<line x1=\"%lf\" y1=\"%lf\" x2=\"%lf\" y2=\"%lf\" style=\"stroke: tomato; stroke-width: 3\" />\n", aux, y + 2, getPointX(getInfo(node)), getPointY(getInfo(node)));
    }
    removeList(atual, 0);
}

void desenhaQt(QuadTree qt, FILE* svg){
    QuadTreeStruct* quadtree = (QuadTreeStruct*)qt;
    float* x = (float*)malloc(sizeof(float));
    *x = 0;
    fprintf(svg, "<svg  width=\"10000\" height=\"10000\" viewBox=\"0 0 10000 10000\" xmlns=\"http://www.w3.org/2000/svg\">");
    desenhaNosQt(quadtree, quadtree->root, svg, x, dy, NULL);
    fprintf(svg, "</svg>");
    free(x);
}