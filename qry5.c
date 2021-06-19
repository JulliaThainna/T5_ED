//Standart Includes
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

//Data Structures
#include "graph.h"
#include "doublyLinkedList.h"
#include "quadTree.h"
#include "hashTable.h"
#include "trataString.h"
#include "utilitario.h"
#include "path.h"


#include "endereco.h"
#include "point.h"
#include "linha.h"
#include "hidrante.h"
#include "semaforo.h"
#include "radioBase.h"
#include "circulo.h"
#include "retangulo.h"
#include "texto.h"
#include "postoSaude.h"
#include "localCasos.h"

enum LISTAS{CIRCULO, RETANGULO, TEXTO, QUADRA, HIDRANTE, SEMAFORO, RADIOBASE, POSTOSAUDE, LINHA, LOCALCASOS, POLIGONO, ESTABELECIMENTO, ENDERECOS};
enum HASHTABLE{CPF_ENDERECO, TIPO_DESCRICAO, CPF_DADOS, CEP_QUADRA};

int indiceRegistrador(char* r){
    char* rAux = malloc((strlen(r) + 1) * sizeof(char));
    rAux = strcpy(rAux, r);
    rAux = rAux + 1;
    int indice = atoi(rAux);
    free(rAux - 1);
    return indice;
}   

void mInt(QuadTree* qt, HashTable* ht, Point* registrador, char* r, char* cpf){
    int indice = indiceRegistrador(r);
    Endereco endereco = getValue(ht[CPF_ENDERECO], cpf);
    setPointX(registrador[indice], getPointX(enderecoGetPoint(endereco)));
    setPointY(registrador[indice], getPointY(enderecoGetPoint(endereco)));
    
    Linha linha = criaLinha(getPointX(registrador[indice]), getPointY(registrador[indice]), getPointX(registrador[indice]), 10, 0, 0, r);
    insereQt(qt[LINHA], linhaGetP1(linha), linha);
}

void eInt(QuadTree* qt, HashTable* ht, Point* registrador, char* r, char* cep, char face, int num){
    int indice = indiceRegistrador(r);
    Quadra quadra = getValue(ht[CEP_QUADRA], cep);
    if(quadra == NULL){
        return;
    }
    //Pega o endereço de CEP/ FACE/ NUM com base numa quadra
    float x = quadraGetX(quadra);
    float y = quadraGetY(quadra);
    float w = quadraGetWidth(quadra);
    float h = quadraGetHeight(quadra);

    switch(toupper(face)){
    case 'N':
        x += num;
        y += h;
        break;
    case 'S':
        x += num;
        break;
    case 'L':
        y += num;
        break;
    case 'O':
        x += w;
        y += num;
        break;
    }
    setPointX(registrador[indice], x);
    setPointY(registrador[indice], y);

    Linha linha = criaLinha(getPointX(registrador[indice]), getPointY(registrador[indice]), getPointX(registrador[indice]), 10, 0, 0, r);
    insereQt(qt[LINHA], linhaGetP1(linha), linha);
}

void gInt(QuadTree* qt, Point* registrador, char* r, char* id){
    int indice = indiceRegistrador(r);
    Hidrante hidrante = getInfoByIdQt(qt[HIDRANTE], id);
    Semaforo semaforo = getInfoByIdQt(qt[SEMAFORO], id);
    RadioBase radioBase = getInfoByIdQt(qt[RADIOBASE], id);
    if(hidrante != NULL){
        setPointX(registrador[indice], getPointX(hidranteGetPoint(hidrante)));
        setPointY(registrador[indice], getPointY(hidranteGetPoint(hidrante)));
    }
    else if(semaforo != NULL){
        setPointX(registrador[indice], getPointX(semaforoGetPoint(semaforo)));
        setPointY(registrador[indice], getPointY(semaforoGetPoint(semaforo)));
    }
    else if(radioBase != NULL){
        setPointX(registrador[indice], getPointX(radioBaseGetPoint(radioBase)));
        setPointY(registrador[indice], getPointY(radioBaseGetPoint(radioBase)));
    }
    else{
        return;
    }

    Linha linha = criaLinha(getPointX(registrador[indice]), getPointY(registrador[indice]), getPointX(registrador[indice]), 10, 0, 0, r);
    insereQt(qt[LINHA], linhaGetP1(linha), linha);
}

void xy(QuadTree* qt, Point* registrador, char* r, float x, float y){
    int indice = indiceRegistrador(r);
    setPointX(registrador[indice], x);
    setPointY(registrador[indice], y);
    Linha linha = criaLinha(getPointX(registrador[indice]), getPointY(registrador[indice]), getPointX(registrador[indice]), 10, 0, 0, r);
    insereQt(qt[LINHA], linhaGetP1(linha), linha);
}

Graph ccv(Graph graphVia, char* sfx, char* dirSaida, char* nomeGeoSemExtensao, char* nomeQrySemExtensao){
    Graph v = removeVerticeDesconexo(graphVia);
    Graph graphCiclovia = primAlgorithm(convertToUndirectedGraph(v));

    char* nomeGeoQry = NULL;
    char* nomeGeoQrySfx = NULL;
    char* pathCcv = NULL;
    concatenaNomeGeoQry(nomeGeoSemExtensao, nomeQrySemExtensao, "", &nomeGeoQry);
    concatenaNomeGeoQry(nomeGeoQry, sfx, ".svg", &nomeGeoQrySfx);
    concatenaCaminhos(dirSaida, nomeGeoQrySfx, &pathCcv);
    
    FILE* fileSvg = fopen(pathCcv, "w");
    if(fileSvg == NULL){
        return NULL;
    }
    printf("\nArquivo SVG-%s aberto com sucesso!", sfx);
        
    fprintf(fileSvg, "\n<svg width=\"10000\" height=\"10000\" xmlns=\"http://www.w3.org/2000/svg\">");

    desenhaGrafoSvg(graphVia, fileSvg, "gray", "gray");
    desenhaGrafoSvg(graphCiclovia, fileSvg, "pink", "gray");

    fprintf(fileSvg, "\n</svg>");

    fclose(fileSvg);
    return graphCiclovia;
}

void pInt(QuadTree* qt, Graph graph, Point* registradores, char* sfx, char* r1, char* r2, char* cmc, char* cmr, char* pathPIntSfx, int idPInt){
  
    //Pega os pontos
    int indice1 = indiceRegistrador(r1);
    int indice2 = indiceRegistrador(r2);
                                                                                                
    Point pInicial = registradores[indice1];
    Point pFinal = registradores[indice2];

    if(getPointX(pInicial) == -1 || getPointY(pInicial) == -1 || getPointX(pFinal) == -1 || getPointY(pFinal) == -1 ){
        return;
    }

    //Define a menor distancia até agora com a distancia dos pontos com o primeiro vertice
    float menorDistP1 = distanciaEntrePontos(getPointX(pInicial), getPointY(pInicial), verticeGetX(graphGetVertice(getInfo(getFirst(graph)))), verticeGetY(graphGetVertice(getInfo(getFirst(graph)))));
    float menorDistP2 = distanciaEntrePontos(getPointX(pFinal), getPointY(pFinal), verticeGetX(graphGetVertice(getInfo(getFirst(graph)))), verticeGetY(graphGetVertice(getInfo(getFirst(graph)))));
    
    char nomeVI[100];
    char nomeVF[100];

    for(Node node = getFirst(graph); node != NULL; node = getNext(node)){
        AdjascentList al = getInfo(node);
        if(distanciaEntrePontos(getPointX(pInicial), getPointY(pInicial), verticeGetX(graphGetVertice(getInfo(node))), verticeGetY(graphGetVertice(getInfo(node)))) < menorDistP1){
            menorDistP1 = distanciaEntrePontos(getPointX(pInicial), getPointY(pInicial), verticeGetX(graphGetVertice(getInfo(node))), verticeGetY(graphGetVertice(getInfo(node))));
            strcpy(nomeVI, verticeGetNome(graphGetVertice(al)));
        }
        if(distanciaEntrePontos(getPointX(pFinal), getPointY(pFinal), verticeGetX(graphGetVertice(getInfo(node))), verticeGetY(graphGetVertice(getInfo(node)))) < menorDistP2){
            menorDistP2 = distanciaEntrePontos(getPointX(pFinal), getPointY(pFinal), verticeGetX(graphGetVertice(getInfo(node))), verticeGetY(graphGetVertice(getInfo(node))));
            strcpy(nomeVF, verticeGetNome(graphGetVertice(al)));
        }
    }

    float distTotal = 0;
    float velocidadeTotal = 0;

    DoublyLinkedList listCmc = dijkstraAlgorithm(graph, nomeVI, nomeVF, &distTotal, arestaGetCmp);
    DoublyLinkedList listVm = dijkstraAlgorithm(graph, nomeVI, nomeVF, &velocidadeTotal, arestaGetTempo);

    FILE* fileSvgGeo = NULL;

    //Se o p? teve SUFIXO
    if(strcmp(sfx, "-") != 0){
        fileSvgGeo = fopen(pathPIntSfx, "w");
        if(fileSvgGeo == NULL){
            return;
        }
        printf("\nArquivo SVG-%s aberto com sucesso!", sfx);
        //Imprime o geo
        char* corSombra[6] = {"#FFFF00", "#FF9955", "#FF0000", "#FF00CC", "#6600FF", "#A02C5A"}; //Comando usado para fazer a sombras das quadras no SVG do comando dd (Atualizado para T4)

        fprintf(fileSvgGeo, "<svg version=\"1.1\" baseProfile=\"full\" width=\"10000\" height=\"10000\" xmlns=\"http://www.w3.org/2000/svg\"  xmlns:xlink=\"http://www.w3.org/1999/xlink\">");
        fprintf(fileSvgGeo, "<defs>");
        for(int i = 0; i < 6; i++){
            fprintf(fileSvgGeo, "<filter id=\"shadow%d\">\n\t\t\t<feDropShadow dx=\"4\" dy=\"4\" stdDeviation=\"0.2\" flood-color=\"%s\"/>\n\t\t</filter>", i, corSombra[i]);
        }
        fprintf(fileSvgGeo, "</defs>");

        percorreLarguraQt(qt[CIRCULO], circuloDesenhaSvgGeo, fileSvgGeo);
        percorreLarguraQt(qt[RETANGULO], retanguloDesenhaSvgGeo, fileSvgGeo);
        percorreLarguraQt(qt[TEXTO], textoDesenhaSvgGeo, fileSvgGeo);
        percorreLarguraQt(qt[QUADRA], quadraDesenhaSvgGeo, fileSvgGeo);
        percorreLarguraQt(qt[HIDRANTE], hidranteDesenhaSvgGeo, fileSvgGeo);
        percorreLarguraQt(qt[SEMAFORO], semaforoDesenhaSvgGeo, fileSvgGeo);
        percorreLarguraQt(qt[RADIOBASE], radioBaseDesenhaSvgGeo, fileSvgGeo);
        percorreLarguraQt(qt[POSTOSAUDE], postoSaudeDesenhaSvgGeo, fileSvgGeo);
    }
    else{ //Se p? NÃO TEVE SUFIXO
        fileSvgGeo = fopen(pathPIntSfx, "a");
        if(fileSvgGeo == NULL){
            return;
        }
        printf("\nAnexado em arquivo SVG anterior com sucesso!");
    }
    
    Path pathCmc = criaPath(graph, pInicial, pFinal, listCmc, distTotal, 6, cmc, idPInt, 0);
    Path pathCmr = criaPath(graph, pInicial, pFinal, listVm, velocidadeTotal, 6, cmr, idPInt+1, 1);
    desenhaPathSvg(pathCmc, fileSvgGeo);
    desenhaPathSvg(pathCmr, fileSvgGeo);

    fclose(fileSvgGeo);
}


void pbInt(QuadTree* qt, Graph graph, Point* registradores, char* sfx, char* r1, char* r2, char* cmc, char* pathPbIntSfx, int idPbInt){
    //Pega os pontos
    int indice1 = indiceRegistrador(r1);
    int indice2 = indiceRegistrador(r2);

    Point pInicial = registradores[indice1];
    Point pFinal = registradores[indice2];

    if(getPointX(pInicial) == -1 || getPointY(pInicial) == -1 || getPointX(pFinal) == -1 || getPointY(pFinal) == -1 ){
        return;
    }

    //Define a menor distancia até agora com a distancia dos pontos com o primeiro vertice
    float menorDistP1 = distanciaEntrePontos(getPointX(pInicial), getPointY(pInicial), verticeGetX(graphGetVertice(getInfo(getFirst(graph)))), verticeGetY(graphGetVertice(getInfo(getFirst(graph)))));
    float menorDistP2 = distanciaEntrePontos(getPointX(pFinal), getPointY(pFinal), verticeGetX(graphGetVertice(getInfo(getFirst(graph)))), verticeGetY(graphGetVertice(getInfo(getFirst(graph)))));
    
    char nomeVI[100];
    char nomeVF[100];

    for(Node node = getFirst(graph); node != NULL; node = getNext(node)){
        AdjascentList al = getInfo(node);
        if(distanciaEntrePontos(getPointX(pInicial), getPointY(pInicial), verticeGetX(graphGetVertice(getInfo(node))), verticeGetY(graphGetVertice(getInfo(node)))) < menorDistP1){
            menorDistP1 = distanciaEntrePontos(getPointX(pInicial), getPointY(pInicial), verticeGetX(graphGetVertice(getInfo(node))), verticeGetY(graphGetVertice(getInfo(node))));
            strcpy(nomeVI, verticeGetNome(graphGetVertice(al)));
        }
        if(distanciaEntrePontos(getPointX(pFinal), getPointY(pFinal), verticeGetX(graphGetVertice(getInfo(node))), verticeGetY(graphGetVertice(getInfo(node)))) < menorDistP2){
            menorDistP2 = distanciaEntrePontos(getPointX(pFinal), getPointY(pFinal), verticeGetX(graphGetVertice(getInfo(node))), verticeGetY(graphGetVertice(getInfo(node))));
            strcpy(nomeVF, verticeGetNome(graphGetVertice(al)));
        }
    }

    float distTotal = 0;

    DoublyLinkedList listCmc = dijkstraAlgorithm(graph, nomeVI, nomeVF, &distTotal, arestaGetCmp);

    FILE* fileSvgGeo = NULL;

    if(strcmp(sfx, "-") != 0){ //Se o p? teve SUFIXO
        fileSvgGeo = fopen(pathPbIntSfx, "w");
        if(fileSvgGeo == NULL){
            return;
        }
        printf("\nArquivo SVG-%s aberto com sucesso!", sfx);
        //Imprime o geo
        char* corSombra[6] = {"#FFFF00", "#FF9955", "#FF0000", "#FF00CC", "#6600FF", "#A02C5A"}; //Comando usado para fazer a sombras das quadras no SVG do comando dd (Atualizado para T4)

        fprintf(fileSvgGeo, "<svg version=\"1.1\" baseProfile=\"full\" width=\"10000\" height=\"10000\" xmlns=\"http://www.w3.org/2000/svg\"  xmlns:xlink=\"http://www.w3.org/1999/xlink\">");
        fprintf(fileSvgGeo, "<defs>");
        for(int i = 0; i < 6; i++){
            fprintf(fileSvgGeo, "<filter id=\"shadow%d\">\n\t\t\t<feDropShadow dx=\"4\" dy=\"4\" stdDeviation=\"0.2\" flood-color=\"%s\"/>\n\t\t</filter>", i, corSombra[i]);
        }
        fprintf(fileSvgGeo, "</defs>");

        percorreLarguraQt(qt[CIRCULO], circuloDesenhaSvgGeo, fileSvgGeo);
        percorreLarguraQt(qt[RETANGULO], retanguloDesenhaSvgGeo, fileSvgGeo);
        percorreLarguraQt(qt[TEXTO], textoDesenhaSvgGeo, fileSvgGeo);
        percorreLarguraQt(qt[QUADRA], quadraDesenhaSvgGeo, fileSvgGeo);
        percorreLarguraQt(qt[HIDRANTE], hidranteDesenhaSvgGeo, fileSvgGeo);
        percorreLarguraQt(qt[SEMAFORO], semaforoDesenhaSvgGeo, fileSvgGeo);
        percorreLarguraQt(qt[RADIOBASE], radioBaseDesenhaSvgGeo, fileSvgGeo);
        percorreLarguraQt(qt[POSTOSAUDE], postoSaudeDesenhaSvgGeo, fileSvgGeo);
    }
    else{ //Se p? NÃO TEVE SUFIXO
        fileSvgGeo = fopen(pathPbIntSfx, "a");
        if(fileSvgGeo == NULL){
            return;
        }
        printf("\nAnexado em arquivo SVG anterior com sucesso!");
     }

    Path pathCmc = criaPath(graph, pInicial, pFinal, listCmc, distTotal, 6, cmc, idPbInt, 0);
    desenhaPathSvg(pathCmc, fileSvgGeo);

    fclose(fileSvgGeo);
}

void insertAuxQry5(Info info, DoublyLinkedList l){
    insert(l, info);
}

void bf(QuadTree* qt, Graph graph, int max, FILE* fileTxt){
    fprintf(fileTxt, "\nBf max: %d", max);

    //Converte a quadtree de local casos para lista de local casos
    DoublyLinkedList localCasos = create();
    percorreLarguraQt(qt[LOCALCASOS], insertAuxQry5, localCasos);

    for(Node node = getFirst(localCasos); node != NULL; node = getNext(node)){
        int casosNorte = 0;
        int casosSul = 0;
        int casosOeste = 0;
        int casosLeste = 0;
        LocalCasos lc1 = getInfo(node);
        for(Node aux = getFirst(localCasos); aux != NULL; aux = getNext(aux)){
            LocalCasos lc2 = getInfo(aux);
            if(strcmp(localCasosGetCep(lc1), localCasosGetCep(lc2)) == 0){
                if(toupper(localCasosGetFace(lc2)) == 'N'){
                    casosNorte += localCasosGetN(lc2);
                }
                else if(toupper(localCasosGetFace(lc2)) == 'S'){
                    casosSul += localCasosGetN(lc2);
                }
                else if(toupper(localCasosGetFace(lc2)) == 'O'){
                    casosOeste += localCasosGetN(lc2);
                }
                else if(toupper(localCasosGetFace(lc2)) == 'L'){
                    casosLeste += localCasosGetN(lc2);
                }
            }
        }
        if(casosNorte > max){
            fprintf(fileTxt, "\nCEP: %s Face: N Total de Casos: %d", localCasosGetCep(lc1), casosNorte);
            removeArestasBf(qt, graph, localCasosGetCep(lc1), 1, 0);
        }
        else if(casosSul > max){
            fprintf(fileTxt, "\nCEP: %s Face: S Total de Casos: %d", localCasosGetCep(lc1), casosSul);
            removeArestasBf(qt, graph, localCasosGetCep(lc1), 0, 0);
        }
        else if(casosOeste > max){
            fprintf(fileTxt, "\nCEP: %s Face: O Total de Casos: %d", localCasosGetCep(lc1), casosOeste);
            removeArestasBf(qt, graph, localCasosGetCep(lc1), 1, 1);
        }
        else if(casosLeste > max){
            fprintf(fileTxt, "\nCEP: %s Face: L Total de Casos: %d", localCasosGetCep(lc1), casosLeste);
            removeArestasBf(qt, graph, localCasosGetCep(lc1), 0, 1);
        }
    }
}

