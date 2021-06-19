#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "path.h"
#include "doublyLinkedList.h"
#include "vertice.h"
#include "point.h"
#include "graph.h"

typedef struct{
    Graph graphBase;
    Point pInicial;
    Point pFinal;
    DoublyLinkedList vertices;
    float cmp;
    float duration;
    char cor[100];
    int idPInt;
    int flag;
}PathStruct;

Path criaPath(Graph graph, Point pInicial, Point pFinal, DoublyLinkedList nomesVerticesList, float cmp, float duration, char* cor, int idPInt, int flag){
    PathStruct* ps = (PathStruct*) malloc(sizeof(PathStruct));
    ps->graphBase = graph;
    ps->pInicial = criaPoint(getPointX(pInicial), getPointY(pInicial));
    ps->pFinal = criaPoint(getPointX(pFinal), getPointY(pFinal));
    ps->cmp = cmp;
    ps->duration = duration;
    strcpy(ps->cor, cor);
    ps->idPInt = idPInt;
    ps->flag = flag;

    ps->vertices = create();

    for(Node node = getFirst(nomesVerticesList); node != NULL; node = getNext(node)){
        char* id = getInfo(node);
        AdjascentList al = graphGetAdjascentList(graph, id);
        Vertice v = graphGetVertice(al);
        insert(ps->vertices, v);
    }

    return ps;
}

void desenhaPathSvg(Path path, void* fileSvg){
    PathStruct* ps = (PathStruct*) path;
    
    //Fazer ponto inicial e final
    fprintf((FILE*) fileSvg, "\n\t<circle cx=\"%f\" cy=\"%f\" r=\"10\" style=\"stroke:magenta;fill:purple;stroke-width:1\"/>", getPointX(ps->pInicial), getPointY(ps->pInicial));
    fprintf((FILE*) fileSvg, "\n\t<circle cx=\"%f\" cy=\"%f\" r=\"10\" style=\"stroke:magenta;fill:purple;stroke-width:1\"/>", getPointX(ps->pFinal), getPointY(ps->pFinal));
    fprintf((FILE*) fileSvg, "\n\t<text x=\"%f\" y=\"%f\" fill=\"white\" text-anchor=\"middle\" >I</text>", getPointX(ps->pInicial), getPointY(ps->pInicial));
    fprintf((FILE*) fileSvg, "\n\t<text x=\"%f\" y=\"%f\" fill=\"white\" text-anchor=\"middle\" >F</text>", getPointX(ps->pFinal), getPointY(ps->pFinal));
    
    //Fazer a tag do caminho
    int primeiro = 1;
    if(ps->flag == 0 || ps->flag == 1){
        fprintf((FILE*) fileSvg, "\n\t<path style=\"fill:none;stroke:%s;stroke-width:2px;stroke-linecap:butt;stroke-linejoin:miter;stroke-opacity:1\"\n\t d=\" M", ps->cor);
    }
    else{
        fprintf((FILE*) fileSvg, "\n\t<path stroke-dasharray=\"2\" style=\"fill:none;stroke:%s;stroke-width:2px;stroke-linecap:butt;stroke-linejoin:miter;stroke-opacity:1\"\n\t d=\" M", ps->cor);
    }
    for(Node node = getFirst(ps->vertices); node != NULL; node = getNext(node)){
        Vertice v = getInfo(node);
        if(ps->flag == 0 || ps->flag == -1){
            if(primeiro == 1){
                fprintf((FILE*) fileSvg, " %f %f", verticeGetX(v), verticeGetY(v));
                primeiro = 0;
            }
            else{
                fprintf((FILE*) fileSvg, "L %f %f", verticeGetX(v), verticeGetY(v));
            }
        }
        if(ps->flag == 1){
            if(primeiro == 1){
                fprintf((FILE*) fileSvg, " %f %f", verticeGetX(v) + 1, verticeGetY(v) + 1);
                primeiro = 0;
            }
            else{
                fprintf((FILE*) fileSvg, " L %f %f", verticeGetX(v) + 1, verticeGetY(v) + 1);
            }
        }
    }
    fprintf((FILE*) fileSvg, "\" id=\"%d\" />", ps->idPInt);

    // TODO: Fazer uma bolinha mas mudar para o svg de um sapinho UwU depois ><
    fprintf((FILE*) fileSvg, "\n\t<circle cx=\"\" cy=\"\" r=\"5\" fill=\"red\"><animateMotion dur=\"6s\" repeatCount=\"indefinite\"><mpath xlink:href=\"#%d\"/></animateMotion></circle>", ps->idPInt);

}