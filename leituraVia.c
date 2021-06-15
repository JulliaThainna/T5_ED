#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "leituraVia.h"
#include "graph.h"
#include "vertice.h"
#include "aresta.h"

void readVia(Graph graph, char* dirVia){
    FILE* fileVia = NULL;
    fileVia = fopen(dirVia, "r");
    if(fileVia == NULL){
        exit(1);
    }
    printf("\nArquivo VIA aberto com sucesso!");
    
    //Parametros
    char comando[100], id[100], i[100], j[100], ldir[100], lesq[100], nome[100];
    float x, y, cmp, vm;

    while(1){
        fscanf(fileVia, "%s", comando);
        
        if(feof(fileVia)){
            break;
        }

        else if(strcmp(comando, "v") == 0){
            fscanf(fileVia, "%s %f %f", id, &x, &y);
            Vertice vertice = createVertice(id, x, y);
            adicionaVertice(graph, vertice);
        }
        else if(strcmp(comando, "e") == 0){
            fscanf(fileVia, "%s %s %s %s %f %f %s", i, j, ldir, lesq, &cmp, &vm, nome);
            Aresta aresta = createAresta(nome, i, j, ldir, lesq, cmp, vm);
            adicionaAresta(graph, aresta);
        }
    }
    fclose(fileVia);
}
