//Standart Headers
#include <stdio.h>
#include <stdlib.h>

#include "graph.h"
#include "doublyLinkedList.h"
#include "vertice.h"
#include "aresta.h"

int main(){
    Graph g = createGraph();
    Vertice v1 = createVertice("juia", 50, 50);
    adicionaVertice(g, v1);
    Vertice v2 = createVertice("rafo", 200, 200);
    adicionaVertice(g, v2);

    Aresta a1 = createAresta("Rua JuiaRafo", "rafo", "juia", "batata", "batata2", 30, 5);
    adicionaAresta(g, a1);
    
    FILE* svg = fopen("teste.svg", "w");
    fprintf(svg, "<svg viewBox=\"0 0 3000 3000\" xmlns=\"http://www.w3.org/2000/svg\">");
    desenhaGrafoSvg(g, svg);
    fprintf(svg, "</svg>");
    fclose(svg);
    return 0;
}
