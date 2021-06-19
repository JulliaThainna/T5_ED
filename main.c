//Standart Headers
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Custom Headers para configuração
#include "parametro.h"
#include "trataString.h"
#include "corPadrao.h"
#include "leituraGeo.h"
#include "processaGeo.h"
#include "leituraQry.h"
#include "svg.h"
#include "texto.h"
#include "hashTable.h"
#include "poligono.h"

//Custom Headers para estruturas e organização
#include "doublyLinkedList.h"
#include "quadTree.h"
#include "graph.h"
#include "leituraEc.h"
#include "leituraPm.h"
#include "leituraVia.h"
#include "hashfileUtilitario.h"

//Enumeration para todas as listas utilizadas
enum LISTAS{CIRCULO, RETANGULO, TEXTO, QUADRA, HIDRANTE, SEMAFORO, RADIOBASE, POSTOSAUDE, DENSIDADEDEMOGRAFICA, QUADRA2};

int main(int argc, char *argv[]){
    //Variáveis passadas como parametro para o Path
    char *dirEntrada = NULL, *arqGeo = NULL, *arqQry = NULL, *dirSaida = NULL, *arqPm = NULL, *arqEc = NULL, *arqVia = NULL, *arqDatK = NULL, *arqDatU = NULL;
    //Variaveis criadas para a localização dos arquivos de entrada e de saída
    //Armazena dirEntrada + arqGeo
    char* dirGeo = NULL;
    //Armazena o nome do arquivo .geo
    char* nomeArquivoGeo = NULL;
    //Armazena o path de saida do arquivo .svg + nome do arquivo + extensão
    char* saidaSvgGeo = NULL;
    //Armazena o path de entrada do arquivo qry
    char* dirQry = NULL;
    //Armazena o nome do arquivo .geo sem extensão
    char* nomeGeoSemExtensao = NULL;
    //Armazena o nome do arquivo .qry sem extensão
    char* nomeQrySemExtensao = NULL;
    //Armazena o nome do arquivo geo com o arquivo qry
    char* nomeGeoQry = NULL;
    //Armazena o caminho de saida do SVG do geo+qry
    char* dirSaidaGeoQry = NULL;
    //Armazena o nome do arquivo de Log (TXT)
    char* nomeArquivoLogTxt = NULL;
    //Armazena o path de saida do arquivo de Log
    char* dirTxt = NULL;
    //Diretorio dirEntrada + arqEc
    char* dirEc = NULL;
    //Diretorio dirEntrada + arqPm
    char* dirPm = NULL;
    //Diretorio dirEntrada + arqVia
    char* dirVia = NULL;

    CorPadrao cores = criaCorPadrao("0.5", "coral", "saddlebrown", "0.5", "red", "darkred", "0.5", "deeppink", "mediumvioletred", "0.5", "green", "red", "0.5", "0.5");

    //Realiza a leitura dos parâmetros
    for(int i = 1; argc > i; i++){
        if(strcmp(argv[i], "-e") == 0){
            dirEntrada = buscaParametros(argv, i);
        }
        else if(strcmp(argv[i], "-f") == 0){
            arqGeo = buscaParametros(argv, i);
        }
        else if(strcmp(argv[i], "-q") == 0){
            arqQry = buscaParametros(argv, i);
        }
        else if(strcmp(argv[i], "-o") == 0){
            dirSaida = buscaParametros(argv, i);
        }
        else if(strcmp(argv[i], "-ec") == 0){
            arqEc = buscaParametros(argv, i);
        }
        else if(strcmp(argv[i], "-pm") == 0){
            arqPm = buscaParametros(argv, i);
        }
        else if(strcmp(argv[i], "-v") == 0){
            arqVia = buscaParametros(argv, i);
        }
        else if(strcmp(argv[i], "-k") == 0){
            arqDatK = buscaParametros(argv, i);
        }
        else if(strcmp(argv[i], "-u") == 0){
            arqDatU = buscaParametros(argv, i);
        }
        i++;
    }
    //Verifica se os parâmetros essenciais estão inseridos
    verificaExecucao(arqGeo, dirSaida);
    //Cria Listas
    DoublyLinkedList listas[10];
    for(int i = CIRCULO; i <= QUADRA2; i++){
        listas[i] = create();
    }
    //Define HashTable
    HashTable hashTables[4];
    for(int i = 0; i < 4; i++){
        hashTables[i] = createHashTable(100);
    }
    concatenaCaminhos(dirEntrada, arqGeo, &dirGeo);
    readGeo(listas, dirGeo, cores);
    Graph graph = NULL;
    //Define QuadTrees
    QuadTree quadTrees[14];
    //Instancia quadTrees e suas funções (getId)
    instanciaQts(quadTrees);
    //Converte todas as listas para quadTrees
    convertToQuadTrees(quadTrees, hashTables, listas);
    //me retorna por ex. overlaps-01.svg
    getNomeConcatExtension(arqGeo, ".svg", &nomeArquivoGeo);
    //me retorna pastaSaida/resultados/overlaps-01.svg
    concatenaCaminhos(dirSaida, nomeArquivoGeo, &saidaSvgGeo);
    //Cria o arquivo do SVG e DesenhaSvgGeo a lista dentro dele
    desenhaSvgGeo(quadTrees, saidaSvgGeo);
    if(arqQry != NULL){
        if(arqEc != NULL){
            //Lê os comandos do Ec
            concatenaCaminhos(dirEntrada, arqEc, &dirEc);
            readEc(quadTrees, hashTables, dirEc);
        }
        if(arqPm != NULL){
            //Lê os comandos do Pm
            concatenaCaminhos(dirEntrada, arqPm, &dirPm);
            readPm(quadTrees, hashTables, dirPm);
        }
        if(arqVia != NULL){
            //Lê os comandos do Via
            graph = createGraph();
            concatenaCaminhos(dirEntrada, arqVia, &dirVia);
            readVia(graph, dirVia);
        }
        loadDatFiles(quadTrees, hashTables, arqDatU);
        //Comando para criar o caminho que será utilizado para abrir o .qry
        concatenaCaminhos(dirEntrada, arqQry, &dirQry);
        //Me retorna o nome do arquivo geo sem extensão (utilizado mais tarde no nome do svg)
        extraiNome(arqGeo, &nomeGeoSemExtensao);
        //Me retorna o nome do arquivo qry sem extensão (utilizado mais tarde no nome do svg)
        extraiNome(arqQry, &nomeQrySemExtensao);
        //Me retorna nomeDoArquivoGeo-NomeDoArquivoQry.Extensão (nomeDoArquivoGeo-NomeDoArquivoQry.svg)
        concatenaNomeGeoQry(nomeGeoSemExtensao, nomeQrySemExtensao, ".svg", &nomeGeoQry);
        //Concatena o caminho de saida com o nome gerado no comando acima (saida do SVG)
        concatenaCaminhos(dirSaida, nomeGeoQry, &dirSaidaGeoQry);
        //Me retorna nomeDoArquivoGeo-NomeDoArquivoQry.Extensão (nomeDoArquivoGeo-NomeDoArquivoQry.txt)
        concatenaNomeGeoQry(nomeGeoSemExtensao, nomeQrySemExtensao, ".txt", &nomeArquivoLogTxt);
        //Concatena o caminho de saida com o nome gerado no comando acima (saida do TXT)
        concatenaCaminhos(dirSaida, nomeArquivoLogTxt, &dirTxt);
        //Lê os comandos do QRY
        readQry(quadTrees, hashTables, graph, dirQry, dirTxt, dirSaida, nomeGeoSemExtensao, nomeQrySemExtensao, dirSaidaGeoQry);
        //Desenha o svg do QRY
        desenhaSvgQry(quadTrees, dirSaidaGeoQry);
    }

    // TODO: Aqui ele tem que salvar tudo que precisa nos .dat
    generateDatFiles(quadTrees, hashTables, arqDatK);

    for(int i = 0; i < 8; i++){
        removeList(listas[i], 0);
    }
    // for(int i = 0; i < 13; i++){
    //     desalocaQt(quadTrees[i]);
    // }
    char* variables[13] = {dirEntrada, arqGeo, arqQry, dirSaida, dirGeo, nomeArquivoGeo, saidaSvgGeo, dirQry, nomeGeoSemExtensao, nomeQrySemExtensao, dirSaidaGeoQry, nomeArquivoLogTxt, dirTxt};
    for(int i = 0; i < 13; i++){
        if(variables[i] != NULL){
            free(variables[i]);
        }
    }
    free(cores);
    return 0;
}
