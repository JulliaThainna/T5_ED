#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "qry4.h"
#include "quadTree.h"
#include "hashTable.h"
#include "trataString.h"
#include "pessoa.h"
#include "endereco.h"
#include "linha.h"
#include "estabelecimento.h"
#include "circulo.h"
#include "hidrante.h"
#include "semaforo.h"
#include "radioBase.h"
#include "utilitario.h"
#include "graph.h"
#include "aresta.h"
#include "vertice.h"
/*
CHAVE X VALOR
HASHTABLE 0 cpf X endereço:                                                 
HASHTABLE 1 tipo-estabelecimento-comercial X descrição:
HASHTABLE 2 dados de uma pessoa: dado um cpf, retorna os dados pessoais daquela pessoa
HASHTABLE 3 cep X quadra:

*/

enum LISTAS{CIRCULO, RETANGULO, TEXTO, QUADRA, HIDRANTE, SEMAFORO, RADIOBASE, POSTOSAUDE, LINHA, LOCALCASOS, POLIGONO, ESTABELECIMENTO, ENDERECOS};
enum HASHTABLE{CPF_ENDERECO, TIPO_DESCRICAO, CPF_DADOS, CEP_QUADRA};

void m(QuadTree* qt, HashTable* ht, char* cep, FILE* fileTxt){
    fprintf(fileTxt, "\nm? %s\n", cep);
    
    Quadra qAux = getInfoByIdQt(qt[QUADRA], cep);
    if(qAux == NULL){
        return;
    }

    float qX = quadraGetX(qAux);
    float qY = quadraGetY(qAux);
    float qW = quadraGetWidth(qAux);
    float qH = quadraGetHeight(qAux);

    DoublyLinkedList listaNoArvoreEnderecos = nosDentroRetanguloQt(qt[ENDERECOS], qX, qY, qX + qW, qY + qH);
    for(Node aux = getFirst(listaNoArvoreEnderecos); aux != NULL; aux = getNext(aux)){
        Endereco endereco = getInfoQt(qt[ENDERECOS], getInfo(aux));
        Pessoa pessoa = getValue(ht[CPF_DADOS], enderecoGetCpf(endereco));
        //Imprime dados pessoa
        fprintf(fileTxt, "DADOS MORADOR | CPF: %s  NOME: %s  SOBRENOME: %s  SEXO: %c  NASCIMENTO: %s", pessoaGetCpf(pessoa), pessoaGetNome(pessoa), pessoaGetSobrenome(pessoa), pessoaGetSexo(pessoa), pessoaGetNascimento(pessoa));
        //Imprime dados endereço
        fprintf(fileTxt, "  /  ENDEREÇO | CEP: %s  FACE: %c  NUM: %d  COMPLEMENTO: %s\n", enderecoGetCep(endereco), enderecoGetFace(endereco), enderecoGetNum(endereco), enderecoGetComplemento(endereco));
    }
    removeList(listaNoArvoreEnderecos, 0);
}


void dm(QuadTree* qt, HashTable* ht, char* cpf, FILE* fileTxt){
    fprintf(fileTxt, "\ndm? %s\n", cpf);

    Pessoa pessoa  = getValue(ht[CPF_DADOS], cpf);   
    Endereco endereco = getValue(ht[CPF_ENDERECO], cpf);

    if(pessoa != NULL && endereco != NULL){

        fprintf(fileTxt, "PESSOA | CPF: %s  NOME: %s  SOBRENOME: %s  SEXO: %c  NASC: %s", pessoaGetCpf(pessoa), pessoaGetNome(pessoa), pessoaGetSobrenome(pessoa), pessoaGetSexo(pessoa), pessoaGetNascimento(pessoa));
        fprintf(fileTxt, "  /  ENDERECO | CEP: %s  FACE: %c  NUM: %d  COMPLEMENTO: %s\n", enderecoGetCep(endereco), enderecoGetFace(endereco), enderecoGetNum(endereco), enderecoGetComplemento(endereco));

        char infoMorador[200];
        strcpy(infoMorador, cpf);
        strcat(infoMorador, " ");
        strcat(infoMorador, pessoaGetNome(pessoa));
        strcat(infoMorador, " ");
        strcat(infoMorador, enderecoGetCep(endereco));
        strcat(infoMorador, " ");
        char auxString[5];
        sprintf(auxString, "%c", enderecoGetFace(endereco));
        strcat(infoMorador, " ");
        strcat(infoMorador, auxString);
        char auxString2[5];
        sprintf(auxString2, "%d", enderecoGetNum(endereco));
        strcat(infoMorador, auxString2);
        strcat(infoMorador, " ");
        strcat(infoMorador, enderecoGetComplemento(endereco));

        Point point = enderecoGetPoint(endereco);
        Linha linha = criaLinha(getPointX(point), getPointY(point), getPointX(point),  0, 0, 0, infoMorador);
        insereQt(qt[LINHA], linhaGetP1(linha), linha);
    }
}


void de(QuadTree* qt, HashTable* ht, char* cnpj, FILE* fileTxt){
    fprintf(fileTxt, "\nde? %s\n", cnpj);
    Estabelecimento estabelecimento = getInfoByIdQt(qt[ESTABELECIMENTO], cnpj);

    if(estabelecimento != NULL){
        char* descricao = getValue(ht[TIPO_DESCRICAO], estabelecimentoGetCodt(estabelecimento));

        fprintf(fileTxt, "DADOS DO ESTABELECIMENTO | NOME: %s  DESCRIÇÃO: %s  CNPJ: %s  CODT: %s  CEP: %s  FACE: %c  NUM: %d", estabelecimentoGetNome(estabelecimento), descricao ,estabelecimentoGetCnpj(estabelecimento), estabelecimentoGetCodt(estabelecimento), estabelecimentoGetCep(estabelecimento), estabelecimentoGetFace(estabelecimento), estabelecimentoGetNum(estabelecimento));
    
        Pessoa pessoa = getValue(ht[CPF_DADOS], estabelecimentoGetCpf(estabelecimento));
    
        if(pessoa != NULL){             
            fprintf(fileTxt, "  /  DADOS DO PROPRIETÁRIO | CPF: %s  NOME: %s  SOBRENOME: %s  SEXO: %c  NASC: %s\n", pessoaGetCpf(pessoa), pessoaGetNome(pessoa), pessoaGetSobrenome(pessoa), pessoaGetSexo(pessoa), pessoaGetNascimento(pessoa));
        }
    }
}


void mud(QuadTree* qt, HashTable* ht, char* cpf, char* cep, char face, int num, char* compl, FILE* fileTxt){
    fprintf(fileTxt, "\nmud %s %s %c %d %s\n", cpf, cep, face, num, compl);

    Pessoa pessoa = getValue(ht[CPF_DADOS], cpf);

    Endereco enderecoAntigo = getValue(ht[CPF_ENDERECO], cpf);
    fprintf(fileTxt, "DADOS PESSOA | CPF: %s  NOME: %s  SOBRENOME: %s  SEXO: %c  NASCIMENTO: %s", pessoaGetCpf(pessoa), pessoaGetNome(pessoa), pessoaGetSobrenome(pessoa), pessoaGetSexo(pessoa), pessoaGetNascimento(pessoa));
    fprintf(fileTxt, "  /  ENDERECO ANTIGO | CEP: %s  FACE: %c  NUM: %d  COMPLEMENTO: %s", enderecoGetCep(enderecoAntigo), enderecoGetFace(enderecoAntigo), enderecoGetNum(enderecoAntigo), enderecoGetComplemento(enderecoAntigo));

    Endereco enderecoNovo = criaEndereco(getInfoByIdQt(qt[QUADRA], cep), cpf, face, num, compl);
    fprintf(fileTxt, "  /  ENDERECO NOVO | CEP: %s  FACE: %c  NUM: %d  COMPLEMENTO: %s\n", enderecoGetCep(enderecoNovo), enderecoGetFace(enderecoNovo), enderecoGetNum(enderecoNovo), enderecoGetComplemento(enderecoNovo));
    
    //Desenha uma linha do endereço antigo até o endereço antigo com um circulo azul no novo e um vermelho no antigo
    Point pAnt = enderecoGetPoint(enderecoAntigo);
    Circulo cAnt = criaCirculo("-1", getPointX(pAnt), getPointY(pAnt), 5, "white", "red", "4px");
    Point pNovo = enderecoGetPoint(enderecoNovo);
    Circulo cNovo = criaCirculo("-1", getPointX(pNovo), getPointY(pNovo), 5, "white", "blue", "4px");

    insereQt(qt[CIRCULO], circuloGetPoint(cAnt), cAnt);
    insereQt(qt[CIRCULO], circuloGetPoint(cNovo), cNovo);
    Linha lEndereco = criaLinha(getPointX(pAnt), getPointY(pAnt), getPointX(pNovo), getPointY(pNovo), -1, 0, "-1");
    insereQt(qt[LINHA], linhaGetP1(lEndereco), lEndereco);

    QtNo no = getNoQt(qt[ENDERECOS], getPointX(pAnt), getPointY(pAnt));

    if(no != NULL){
        removeNoQt(qt[ENDERECOS], no);
    }
    removeKey(ht[CPF_ENDERECO], cpf);
    
    insertValueHashTable(ht[CPF_ENDERECO], cpf, enderecoNovo);

    insereQt(qt[ENDERECOS], enderecoGetPoint(enderecoNovo), enderecoNovo);
}


void dmprbt(QuadTree* qt, char t, char* sfx, char* dirSaida, char* nomeGeoSemExtensao, char* nomeQrySemExtensao){
    int i;
    switch (t){
    case 'q':
        i = 3;
        break;
    case 'h':
        i = 4;
        break;
    case 's':
        i = 5;
        break;
    case 't':
        i = 6;
        break;
    case 'e':
        i = 12;
        break;
    default:
        break;
    }

    char* nomeGeoQry = NULL;
    char* nomeGeoQrySfx = NULL;
    char* pathDmprbt = NULL;
    concatenaNomeGeoQry(nomeGeoSemExtensao, nomeQrySemExtensao, "", &nomeGeoQry);
    concatenaNomeGeoQry(nomeGeoQry, sfx, ".svg", &nomeGeoQrySfx);
    concatenaCaminhos(dirSaida, nomeGeoQrySfx, &pathDmprbt);

    //Function para imprimir a arvore
    FILE* fileSvgQT = fopen(pathDmprbt, "w");
    if(fileSvgQT){
        return;
    }
    printf("\nArquivo SVG-DMPRBT aberto com sucesso!");

    desenhaQt(qt[i], fileSvgQT);

    fclose(fileSvgQT);
    free(nomeGeoQry);
    free(nomeGeoQrySfx);
    free(pathDmprbt);
}


void eplg(QuadTree* qt, HashTable* ht, char* tp, float x, float y, float w, float h, FILE* fileTxt){
    fprintf(fileTxt, "\neplg? %s %f %f %f %f\n", tp, x, y, w, h);

    DoublyLinkedList listaNoEstabelecimento = nosDentroRetanguloQt(qt[ESTABELECIMENTO], x, y, x + w, y + h);
    
    for(Node aux = getFirst(listaNoEstabelecimento); aux != NULL; aux = getNext(aux)){
        Estabelecimento estabelecimento = getInfoQt(qt[ESTABELECIMENTO], getInfo(aux));
        Pessoa pessoa = getValue(ht[CPF_DADOS], estabelecimentoGetCpf(estabelecimento));

        if(strcmp(tp, "*") == 0){   //Qualquer tipo
            fprintf(fileTxt, "DADOS ESTABELECIMENTO | NOME: %s  CNPJ: %s  CODT: %s  CEP: %s  FACE: %c  NUM: %d", estabelecimentoGetNome(estabelecimento), estabelecimentoGetCnpj(estabelecimento), estabelecimentoGetCodt(estabelecimento), estabelecimentoGetCep(estabelecimento), estabelecimentoGetFace(estabelecimento), estabelecimentoGetNum(estabelecimento));
            fprintf(fileTxt, "  /  DADOS DO PROPRIETÁRIO |  NOME: %s  CPF: %s\n", pessoaGetNome(pessoa), pessoaGetCpf(pessoa));
            
            Point pontoEstabelecimento = estabelecimentoGetPoint(estabelecimento);
            Circulo cAux = criaCirculo("-1", getPointX(pontoEstabelecimento), getPointY(pontoEstabelecimento), 2, "white", "lightslategray", "1px");
            insereQt(qt[CIRCULO], circuloGetPoint(cAux), cAux);
        }
        else if(strcmp(estabelecimentoGetCodt(estabelecimento), tp) == 0){
            fprintf(fileTxt, "DADOS ESTABELECIMENTO | NOME: %s  CNPJ: %s  CODT: %s  CEP: %s  FACE: %c  NUM: %d", estabelecimentoGetNome(estabelecimento), estabelecimentoGetCnpj(estabelecimento), estabelecimentoGetCodt(estabelecimento), estabelecimentoGetCep(estabelecimento), estabelecimentoGetFace(estabelecimento), estabelecimentoGetNum(estabelecimento));
            fprintf(fileTxt, "  /  DADOS DO PROPRIETÁRIO |  NOME: %s  CPF: %s\n", pessoaGetNome(pessoa), pessoaGetCpf(pessoa));
            
            Point pontoEstabelecimento = estabelecimentoGetPoint(estabelecimento);
            Circulo cAux = criaCirculo("-1", getPointX(pontoEstabelecimento), getPointY(pontoEstabelecimento), 10, "white", "lightslategray", "1px");
            insereQt(qt[CIRCULO], circuloGetPoint(cAux), cAux);
        }
    }

    removeList(listaNoEstabelecimento, 0);
}

void catac(QuadTree* qt, HashTable* ht, float x, float y, float r, FILE* fileTxt, Graph graph){
    fprintf(fileTxt, "\ncatac %f %f %f\n", x, y, r);

    DoublyLinkedList quadras = nosDentroCirculoQt(qt[QUADRA], x, y, r);
    for(Node aux = getFirst(quadras); aux != NULL; aux = getNext(aux)){
        QtNo noArvore = getInfo(aux); //Nosso nó da arvore
        Quadra quadra = getInfoQt(qt[QUADRA], noArvore); //Pega a quadra

        float qX = quadraGetX(quadra);
        float qY = quadraGetY(quadra);
        float qW = quadraGetWidth(quadra);
        float qH = quadraGetHeight(quadra);

        if(insideCirculo(qX, qY, x, y, r) == 1 && insideCirculo(qX + qW, qY, x, y, r) == 1 && insideCirculo(qX, qY + qH, x, y, r) == 1 && insideCirculo(qX + qW, qY + qH, x, y, r) == 1){
            fprintf(fileTxt, "QUADRA | CEP: %s  X: %f  Y: %f  W: %f  H: %f\n", quadraGetCep(quadra), quadraGetX(quadra), quadraGetY(quadra), quadraGetWidth(quadra), quadraGetHeight(quadra));
            removeKey(ht[CEP_QUADRA], quadraGetCep(quadra));
            Quadra q = removeNoQt(qt[QUADRA], getInfo(aux));
            free(quadraGetPoint(q));
            free(q);
        }
    }
    removeList(quadras, 0);
    
    //DELETA EQUIPAMENTOS URBANOS
    DoublyLinkedList hidrantes = nosDentroCirculoQt(qt[HIDRANTE], x, y, r);
    DoublyLinkedList semaforos = nosDentroCirculoQt(qt[SEMAFORO], x, y, r);
    DoublyLinkedList radiobases = nosDentroCirculoQt(qt[RADIOBASE], x, y, r);

    for(Node aux = getFirst(hidrantes); aux != NULL; aux = getNext(aux)){
        Hidrante hidrante = getInfoQt(qt[HIDRANTE], getInfo(aux));
        fprintf(fileTxt, "HIDRANTE | ID: %s  X: %f  Y: %f\n", hidranteGetId(hidrante), hidranteGetX(hidrante), hidranteGetY(hidrante));
        Hidrante h = removeNoQt(qt[HIDRANTE], getInfo(aux));
        free(hidranteGetPoint(h));
        free(h);
    }
    for(Node aux = getFirst(semaforos); aux != NULL; aux = getNext(aux)){
        Semaforo semaforo = getInfoQt(qt[RADIOBASE], getInfo(aux));
        fprintf(fileTxt, "SEMAFORO | ID: %s  X: %f  Y: %f\n", semaforoGetId(semaforo), semaforoGetX(semaforo), semaforoGetY(semaforo));
        Semaforo s = removeNoQt(qt[SEMAFORO], getInfo(aux));
        free(semaforoGetPoint(s));
        free(s);
    }
    for(Node aux = getFirst(radiobases); aux != NULL; aux = getNext(aux)){
        RadioBase radiobase = getInfoQt(qt[RADIOBASE], getInfo(aux));
        fprintf(fileTxt, "RADIOBASE | ID: %s  X: %f  Y: %f\n", radioBaseGetId(radiobase), radioBaseGetX(radiobase), radioBaseGetY(radiobase));
        RadioBase r = removeNoQt(qt[RADIOBASE], getInfo(aux));
        free(radioBaseGetPoint(r));
        free(r);
    }
    removeList(hidrantes, 0);
    removeList(semaforos, 0);
    removeList(radiobases, 0);

    //DELETA MORADORES E ESTABELECIMENTOS COMERCIAIS
    DoublyLinkedList enderecos = nosDentroCirculoQt(qt[ENDERECOS], x, y, r);
    DoublyLinkedList estabelecimentos = nosDentroCirculoQt(qt[ESTABELECIMENTO], x, y, r);

    for(Node aux = getFirst(enderecos); aux != NULL; aux = getNext(aux)){
        Endereco endereco = getInfoQt(qt[ENDERECOS], getInfo(aux));
        fprintf(fileTxt, "DADOS MORADORES | CPF: %s  CEP: %s  FACE: %c  NUM: %d  COMPLEMENTO: %s\n", enderecoGetCpf(endereco), enderecoGetCep(endereco), enderecoGetFace(endereco), enderecoGetNum(endereco), enderecoGetComplemento(endereco));
        removeKey(ht[CPF_ENDERECO], enderecoGetCpf(endereco));
        Endereco e = removeNoQt(qt[ENDERECOS], getInfo(aux));
        free(enderecoGetPoint(e));
        free(e);
    }
    for(Node aux = getFirst(estabelecimentos); aux != NULL; aux = getNext(aux)){
        Estabelecimento estabelecimento = getInfoQt(qt[ESTABELECIMENTO], getInfo(aux));
        fprintf(fileTxt, "DADOS ESTABELECIMENTOS | NOME: %s  CNPJ: %s  CPF: %s  CODT: %s  CEP: %s  FACE: %c  NUM: %d\n", estabelecimentoGetNome(estabelecimento), estabelecimentoGetCnpj(estabelecimento) ,estabelecimentoGetCpf(estabelecimento), estabelecimentoGetCodt(estabelecimento), estabelecimentoGetCep(estabelecimento), estabelecimentoGetFace(estabelecimento), estabelecimentoGetNum(estabelecimento));
        Estabelecimento e = removeNoQt(qt[ESTABELECIMENTO], getInfo(aux));
        free(estabelecimentoGetPoint(e));
        free(e);
    }

    //Id -2 para ser transparente
    Circulo circulo = criaCirculo("-2", x, y, r, "#6C6753", "#CCFF00,", "2px");
    insereQt(qt[CIRCULO], circuloGetPoint(circulo), circulo);

    if(graph == NULL){
        return;
    }

    //Remove vertices que estão dentro do circulo
    Node node = getFirst(graph);
    while(node != NULL){
        Vertice v = graphGetVertice(getInfo(node));
        if(insideCirculo(verticeGetX(v), verticeGetY(v), x, y, r) == 1){
            Node nodeAux = getNext(node);
            fprintf(fileTxt, "VERTICE | ID: %s X: %f Y: %f\n", verticeGetNome(v), verticeGetX(v), verticeGetY(v));
            removeNode(graph, node, 0);
            node = nodeAux;
            continue;
        }
        node = getNext(node);
    }

    for(Node node = getFirst(graph); node != NULL; node = getNext(node)){
        AdjascentList al = getInfo(node);
        Node nodeA = getFirst(graphGetArestas(al)); 
        while(nodeA != NULL){
            Aresta a = getInfo(nodeA);
            AdjascentList alVI = graphGetAdjascentList(graph, arestaGetNomeVerticeInicial(a));
            AdjascentList alVF = graphGetAdjascentList(graph, arestaGetNomeVerticeFinal(a));
            if(alVI == NULL || alVF == NULL){
                Node nodeAux = getNext(nodeA);
                fprintf(fileTxt, "ARESTA | NOME: %s NOME VERTICE INICIAL: %s NOME VERTICE FINAL: %s LESQ: %s LDIR: %s CMP: %f VM: %f\n", arestaGetNome(a), arestaGetNomeVerticeInicial(a), arestaGetNomeVerticeFinal(a), arestaGetLesq(a), arestaGetLdir(a), arestaGetCmp(a), arestaGetVm(a));
                removeNode(graphGetArestas(al), nodeA, 0);
                nodeA = nodeAux;
                continue;
            }
            nodeA = getNext(nodeA);
        }
    }
}