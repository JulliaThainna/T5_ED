#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "graph.h"
#include "hashTable.h"
#include "doublyLinkedList.h"
#include "aresta.h"
#include "vertice.h"

/*Struct da lista de "vértices". Ex: 1 -> 2 -> 3*/
/*
Essa struct representa cada vertice que é adicionado no grafo.
Cada vertice novo adiciona uma novo AdjascentListStruct na lista, que dentro dela contem
o vertice e a lista de arestas que partem desse vertice
*/
typedef struct
{
    Vertice inicio;           //Objeto de tipo vértice que guarda o ínicio da lista de "arestas"
    DoublyLinkedList arestas; //Lista de arestas
} AdjascentListStruct;

/*Struct dos nodes da lista de "arestas" Ex: 1
                                             |
                                             3                        
typedef struct{
    Aresta aresta; //Objeto de tipo aresta
    char verticeFinal[100]; //Pra onde a aresta vai
}AdjascentNodeStruct;
*/

/*
Cria um grafo. Na verdade cria uma lista que é tratada de forma exclusiva dentro do TAD do grafo. Dessa forma
utilizamos uma lista para a representação do grafo. Cada elemento dessa lista é uma AdjascentListStruct (descrito acima), que representam vertices e listas de arestas */
Graph createGraph()
{
    return create();
}

/*Essa função retorna o Vertice de uma lista de adjascencia.
Cada lista de adjascencia possui um vertice e uma lista de arestas que saem desse vertice
PRE: uma lista de adjascencia;
POS: retorna o atributo 
*/
Vertice graphGetVertice(AdjascentList adjascentList)
{
    AdjascentListStruct *als = (AdjascentListStruct *)adjascentList;
    return als->inicio;
}

/*
Essa função retorna a lista de arestas de uma lista de adjascencia. Semelhante a função anterior.
Cada lista de adjascencia possui uma lista de arestas que partem do vertice descrito em "inicio".
*/
DoublyLinkedList graphGetArestas(AdjascentList adjascentList)
{
    AdjascentListStruct *als = (AdjascentListStruct *)adjascentList;
    return als->arestas;
}

/*Aresta graphGetAresta(AdjascentNode adjascentNode){
    AdjascentNodeStruct* ans = (AdjascentNodeStruct*)adjascentNode;
    return ans->aresta;
}

char* graphGetVerticeFinal(AdjascentNode adjascentNode){
    AdjascentNodeStruct* ans = (AdjascentNodeStruct*)adjascentNode;
    return ans->verticeFinal;
}
*/

/*
Essa função retorna uma AdjascentList com base no nome do vertice.
PRE: Variável Grafo e o char* nomeVertice do vertice
POS: Lista de adjascencia caso exista o vertice e NULL caso não exista
*/
AdjascentList graphGetAdjascentList(Graph graph, char *nomeVertice)
{
    for (Node node = getFirst(graph); node != NULL; node = getNext(node))
    {
        AdjascentListStruct *als = getInfo(node);
        if (strcmp(nomeVertice, verticeGetNome(als->inicio)) == 0)
        {
            return als;
        }
    }
    return NULL;
}

/*
Adiciona um novo vertice no grafo. Faz isso através da AdjascentList
PRE: Variável Grafo e um vertice definido
POS: Não há retorno
*/
void adicionaVertice(Graph graph, Vertice vertice)
{
    AdjascentListStruct *als = (AdjascentListStruct *)malloc(sizeof(AdjascentListStruct));
    als->inicio = vertice;
    als->arestas = create();
    insert(graph, als);
}

/*
Essa função adiciona uma nova aresta partindo de um dos vertices. Como o vertice final e o vertice inicial da aresta é definido na aresta, não há necessidade de passa-los
como valores separados para a função. Caso o usuário passe uma aresta NULL a função retornará.
PRE: Variável Grafo e variável Aresta
POS: Não há retorno
*/
void adicionaAresta(Graph graph, Aresta aresta)
{
    AdjascentListStruct *als = graphGetAdjascentList(graph, arestaGetNomeVerticeInicial(aresta));
    if (als == NULL)
    {
        return;
    }
    insert(als->arestas, aresta);
}

/*
Essa função desaloca todas as arestas de uma lista de adjascencia. Em outras palavras ela deleta todas as arestas partindo de determinado vertice. Também desaloca o vertice.
PRE: Lista de adjascencia
POS: Não há retorno
*/
void desalocaAdjascentList(AdjascentList adjascentList)
{
    AdjascentListStruct *als = (AdjascentListStruct *)adjascentList;
    removeList(als->arestas, 1);
    //desalocaVertice(als->inicio);
    free(adjascentList);
}

/*
Essa função desaloca todas as AdjascentList (Vertices) que existirem dentro do grafo.
(ESSA FUNÇÃO NÃO DESALOCA AS ARESTAS. USAR ELA SEM DESALOCAR AS ARESTAS IRÁ CAUSA MEMORY LEAK!!!)
PRE: Variável Grafo
POS: Não há retorno
*/
void desalocaGrafo(Graph graph)
{
    removeList(graph, 0);
}

/*
Essa função desenha uma única aresta no SVG.
PRE: Variável Grafo, variável AdjascentList, uma Aresta e o FILE* em que o svg será gerado
POS: Não há retorno
*/
void desenhaArestaSvg(Graph graph, AdjascentList adjascentList, Aresta aresta, FILE *fileSvg)
{
    //Pra desenhar uma aresta eu preciso de duas listas adjascentes
    //Porque? Porque dentro das listas adjascentes tem a posição (point) dos vertice
    AdjascentListStruct *alsVI = (AdjascentListStruct *)adjascentList;
    AdjascentListStruct *alsVF = (AdjascentListStruct *)graphGetAdjascentList(graph, arestaGetNomeVerticeFinal(aresta));

    float x1 = verticeGetX(alsVI->inicio);
    float y1 = verticeGetY(alsVI->inicio);
    float x2 = verticeGetX(alsVF->inicio);
    float y2 = verticeGetY(alsVF->inicio);

    fprintf(fileSvg, "\n\t<line x1=\"%lf\" y1=\"%lf\" x2=\"%lf\" y2=\"%lf\" style=\"stroke:red;stroke-width:2\"/>\n", x1, y1, x2, y2);
}

void desenhaGrafoSvg(Graph graph, FILE *fileSvg)
{
    //Desenha todas as arestas
    for (Node aux = getFirst(graph); aux != NULL; aux = getNext(aux))
    {
        AdjascentList al = getInfo(aux);
        //Info é AdjascentList
        DoublyLinkedList arestas = graphGetArestas(al);
        //Percorre a lista de arestas imprimindo cada aresta
        for (Node auxArestas = getFirst(arestas); auxArestas != NULL; auxArestas = getNext(auxArestas))
        {
            Aresta aresta = getInfo(auxArestas);
            desenhaArestaSvg(graph, al, aresta, fileSvg);
        }
    }

    //Desenha todos os vertices
    for (Node aux = getFirst(graph); aux != NULL; aux = getNext(aux))
    {
        AdjascentList al = getInfo(aux);
        //Info é AdjascentList
        Vertice vert = graphGetVertice(al);
        desenhaVerticeSvg(vert, fileSvg);
    }
}

Graph primAlgorithm(Graph graph)
{
    HashTable htVisitados = createHashTable(100);
    Graph agm = createGraph();

    char *nomeVI, *nomeVF;
    char visitado[] = "1";

    //Cria uma cópia dos vertices para a arvore geradora minima
    for (Node aux = getFirst(graph); aux != NULL; aux = getNext(aux))
    {
        AdjascentList adl = getInfo(aux);
        Vertice v = graphGetVertice(adl);
        Vertice v2 = createVertice(verticeGetNome(v), verticeGetX(v), verticeGetY(v));
        adicionaVertice(agm, v2);
    }

    //Adiciona o primeiro node na HT de visitados
    Vertice vertice = graphGetVertice(getInfo(getFirst(graph)));
    insertValueHashTable(htVisitados, verticeGetNome(vertice), visitado);

    while (1)
    {
        float menorCmp;
        Aresta aresta;
        int first = 1;

        for (Node i = getFirst(graph); i != NULL; i = getNext(i))
        {
            // TODO: Perguntar pro pedro se há necessidade de pegar novamente o primeiro vertice
            AdjascentListStruct *adl = getInfo(i);
            vertice = adl->inicio;
            if (isKeyHashTable(htVisitados, verticeGetNome(vertice)) != 0)
            {
                for (Node j = getFirst(adl->arestas); j != NULL; j = getNext(j))
                {
                    if (isKeyHashTable(htVisitados, arestaGetNomeVerticeFinal(getInfo(j))) == 0)
                    {
                        if (first != 0)
                        {
                            nomeVI = verticeGetNome(vertice);
                            aresta = getInfo(j);
                            nomeVF = arestaGetNomeVerticeFinal(aresta);
                            menorCmp = arestaGetCmp(aresta);
                            first = 0;
                        }
                        else if (arestaGetCmp(getInfo(j)) > menorCmp)
                        {
                            nomeVI = verticeGetNome(vertice);
                            aresta = getInfo(j);
                            nomeVF = arestaGetNomeVerticeFinal(aresta);
                            menorCmp = arestaGetCmp(aresta);
                        }
                    }
                }
            }
        }
        if (first != 0)
        {
            break;
        }
        Aresta a1 = createAresta(arestaGetNome(aresta), nomeVI, nomeVF, arestaGetLdir(aresta), arestaGetLesq(aresta), arestaGetCmp(aresta), arestaGetVm(aresta));
        Aresta a2 = createAresta(arestaGetNome(aresta), nomeVF, nomeVI, arestaGetLdir(aresta), arestaGetLesq(aresta), arestaGetCmp(aresta), arestaGetVm(aresta));
        adicionaAresta(agm, a1);
        adicionaAresta(agm, a2);
        insertValueHashTable(htVisitados, nomeVF, visitado);
    }
    // TODO: Arrumar algum jeito para não dar double free ou free em coisa invalida quando chamar removeHashTable
    removeHashTable(htVisitados);
    return agm;
}
