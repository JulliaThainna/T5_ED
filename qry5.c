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

char* pInt(QuadTree* qt, Graph graph, Point* registradores, char* sfx, char* r1, char* r2, char* cmc, char* cmr, char* nomeGeoSemExtensao, char* nomeQrySemExtensao, char* dirSaida, int idPInt, char* pathPIntHifen){

    if(strcmp(sfx, "-") != 0){
        FILE* confirmaFechaSvg = fopen(pathPIntHifen, "a+");
        fprintf(confirmaFechaSvg, "</svg>");
        fclose(confirmaFechaSvg);
    }

    //Pega os pontos
    int indice1 = indiceRegistrador(r1);
    int indice2 = indiceRegistrador(r2);

    Point pInicial = registradores[indice1];
    Point pFinal = registradores[indice2];

    //TODO: Fazer verificação

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

    // TODO: Fazer verificação se vertice existe pelo amor de deus

    DoublyLinkedList listCmc = dijkstraAlgorithm(graph, nomeVI, nomeVF, &distTotal, arestaGetCmp);
    DoublyLinkedList listVm = dijkstraAlgorithm(graph, nomeVI, nomeVF, &velocidadeTotal, arestaGetVm);


    //Organizar nome do arquivo

    FILE* fileSvgGeo = NULL;

    //Pra retornar o caminho do FILE se p? TEVE SUFIXO
    char* pathPIntSfx = NULL;
    char* nomeGeoQry = NULL;
    char* nomeGeoQrySfx = NULL;
    concatenaNomeGeoQry(nomeGeoSemExtensao, nomeQrySemExtensao, "", &nomeGeoQry);
    concatenaNomeGeoQry(nomeGeoQry, sfx, ".svg", &nomeGeoQrySfx);
    concatenaCaminhos(dirSaida, nomeGeoQrySfx, &pathPIntSfx);

    //Se o p? teve SUFIXO
    if(strcmp(sfx, "-") != 0){
        fileSvgGeo = fopen(pathPIntSfx, "w");
        if(fileSvgGeo == NULL){
            return NULL;
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
         fileSvgGeo = fopen(pathPIntHifen, "a");
         printf("\nAnexado em arquivo SVG anterior com sucesso!");

         fseek(fileSvgGeo, -5, SEEK_CUR);
     }

    Path pathCmc = criaPath(graph, pInicial, pFinal, listCmc, distTotal, 6, cmc, idPInt);
    Path pathCmr = criaPath(graph, pInicial, pFinal, listVm, velocidadeTotal, 6, cmr, idPInt + 1);
    desenhaPathSvg(pathCmc, fileSvgGeo);
    desenhaPathSvg(pathCmr, fileSvgGeo);
    
    fclose(fileSvgGeo);

    if(strcmp(sfx, "-") == 0){
        return pathPIntHifen;
    }
    else{
        return pathPIntSfx;
    }
}


char* pbInt(QuadTree* qt, Graph graph, Point* registradores, char* sfx, char* r1, char* r2, char* cmc, char* nomeGeoSemExtensao, char* nomeQrySemExtensao, char* dirSaida, int idPbInt, char* pathPbIntHifen){

    if(strcmp(sfx, "-") != 0){
        FILE* confirmaFechaSvg = fopen(pathPbIntHifen, "a+");
        fprintf(confirmaFechaSvg, "</svg>");
        fclose(confirmaFechaSvg);
    }

    //Pega os pontos
    int indice1 = indiceRegistrador(r1);
    int indice2 = indiceRegistrador(r2);

    Point pInicial = registradores[indice1];
    Point pFinal = registradores[indice2];

    //TODO: Fazer verificação

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

    // TODO: Fazer verificação se vertice existe pelo amor de deus

    DoublyLinkedList listCmc = dijkstraAlgorithm(graph, nomeVI, nomeVF, &distTotal, arestaGetCmp);

    //Organizar nome do arquivo

    FILE* fileSvgGeo = NULL;

    //Pra retornar o caminho do FILE se p? TEVE SUFIXO
    char* pathPbIntSfx = NULL;
    char* nomeGeoQry = NULL;
    char* nomeGeoQrySfx = NULL;
    concatenaNomeGeoQry(nomeGeoSemExtensao, nomeQrySemExtensao, "", &nomeGeoQry);
    concatenaNomeGeoQry(nomeGeoQry, sfx, ".svg", &nomeGeoQrySfx);
    concatenaCaminhos(dirSaida, nomeGeoQrySfx, &pathPbIntSfx);

    //Se o p? teve SUFIXO
    if(strcmp(sfx, "-") != 0){
        fileSvgGeo = fopen(pathPbIntSfx, "w");
        if(fileSvgGeo == NULL){
            return NULL;
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
         fileSvgGeo = fopen(pathPbIntHifen, "a");
         printf("\nAnexado em arquivo SVG anterior com sucesso!");

         fseek(fileSvgGeo, -5, SEEK_CUR);
     }

    Path pathCmc = criaPath(graph, pInicial, pFinal, listCmc, distTotal, 6, cmc, idPbInt);
    desenhaPathSvg(pathCmc, fileSvgGeo);

    fclose(fileSvgGeo);

    if(strcmp(sfx, "-") == 0){
        return pathPbIntHifen;
    }
    else{
        return pathPbIntSfx;
    }
}