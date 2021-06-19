#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "leituraQry.h"
#include "quadTree.h"
#include "hashTable.h"
#include "graph.h"
#include "trataString.h"

#include "linha.h"
#include "retangulo.h"
#include "point.h"
#include "qry1.h"
#include "qry2.h"
#include "qry3.h"
#include "qry4.h"
#include "qry5.h"

enum LISTAS{
    CIRCULO,
    RETANGULO,
    TEXTO,
    QUADRA,
    HIDRANTE,
    SEMAFORO,
    RADIOBASE,
    POSTOSAUDE,
    LINHA,
    LOCALCASOS,
    POLIGONO,
    ESTABELECIMENTO,
    ENDERECOS
};

void readQry(QuadTree *qt, HashTable *ht, Graph graph, char *dirQry, char *dirTxt, char *dirSaida, char *nomeGeoSemExtensao, char *nomeQrySemExtensao, char* dirSaidaGeoQry){

    FILE *fileTxt = NULL;
    fileTxt = fopen(dirTxt, "w");
    if(!fileTxt){
        exit(1);
    }
    printf("\nArquivo TXT aberto com sucesso!");

    FILE *fileQry = NULL;
    fileQry = fopen(dirQry, "r");
    if(!fileQry){
        exit(1);
    }
    printf("\nArquivo QRY aberto com sucesso!");

    FILE* fileSvgQry = NULL;
    fileSvgQry = fopen(dirSaidaGeoQry, "w");
    if(!fileSvgQry){
        exit(1);
    }
    printf("\nArquivo SVG-QRY criado com sucesso!");
    fprintf(fileSvgQry, "<svg version=\"1.1\" baseProfile=\"full\" width=\"10000\" height=\"10000\" xmlns=\"http://www.w3.org/2000/svg\" xmlns:xlink=\"http://www.w3.org/1999/xlink\">");

    char* corSombra[6] = {"#FFFF00", "#FF9955", "#FF0000", "#FF00CC", "#6600FF", "#A02C5A"}; //Comando usado para fazer a sombras das quadras no SVG do comando dd (Atualizado para T4)

    fprintf(fileSvgQry, "<defs>");
    for(int i = 0; i < 6; i++){
        fprintf(fileSvgQry, "<filter id=\"shadow%d\">\n\t\t\t<feDropShadow dx=\"4\" dy=\"4\" stdDeviation=\"0.2\" flood-color=\"%s\"/>\n\t\t</filter>", i, corSombra[i]);
    }
    fprintf(fileSvgQry, "</defs>");

    Point registradores[11];
    for(int i = 0; i < 11; i++){
        registradores[i] = criaPoint(-1, -1);
    }
    DoublyLinkedList arqsPInt = create();
    DoublyLinkedList arqsPbInt = create();
    char j[100], k[100], comando[100], cb[100], cp[100], cep[100], face[100], t, sfx[100], cpf[100], cnpj[100], compl[100], tp[100];
    char reg[100], reg1[100], reg2[100], cmc[100], cmr[100], id[100]; 
    int casosCovid = 0, n = 0, num = 0, interno = 0, sobrepoe = 0, max = 0, idPInt = 0, idPbInt = 0;
    float x = 0, y = 0, w = 0, h = 0, r = 0, centroDeMassaX = 0, centroDeMassaY = 0;

    Graph graphCiclovia = NULL;
    Linha linhaAux = NULL;
    Retangulo retanguloAux = NULL;
    
    while(1){
        fscanf(fileQry, "%s", comando);
        if(feof(fileQry)){
            break;
        }

        //T1_ED
        //o?
        if(strcmp(comando, "o?") == 0){
            fscanf(fileQry, "%s %s", j, k);
            sobrepoe = overlay(qt, j, k, &x, &y, &w, &h, fileTxt);
            if(sobrepoe == 0){
                retanguloAux = criaRetangulo("0", 1, x, y, w, h, "black", "none", "2px");
                insereQt(qt[1], retanguloGetPoint(retanguloAux), retanguloAux);
            }
            if(sobrepoe == 1){
                retanguloAux = criaRetangulo("0", 0, x, y, w, h, "black", "none", "2px");
                insereQt(qt[1], retanguloGetPoint(retanguloAux), retanguloAux);
            }
        }
        //i?
        if(strcmp(comando, "i?") == 0){
            fscanf(fileQry, "%s %f %f", j, &x, &y);
            interno = inside(qt, j, x, y, &centroDeMassaX, &centroDeMassaY, fileTxt);
            if(interno == 1){ //Dentro
                linhaAux = criaLinha(x, y, centroDeMassaX, centroDeMassaY, 1, 1, "-1");
                insereQt(qt[8], linhaGetP1(linhaAux), linhaAux);
            }
            else if(interno == 0){ //Fora ou borda
                linhaAux = criaLinha(x, y, centroDeMassaX, centroDeMassaY, 1, 0, "-1");
                insereQt(qt[8], linhaGetP1(linhaAux), linhaAux);
            }
        }
        //pnt
        if(strcmp(comando, "pnt") == 0){
            fscanf(fileQry, "%s %s %s", j, cb, cp);
            pnt(qt, j, cb, cp, fileTxt);
        }
        //pnt*
        if(strcmp(comando, "pnt*") == 0){
            fscanf(fileQry, "%s %s %s %s", j, k, cb, cp);
            pntAst(qt, j, k, cb, cp, fileTxt);
        }
        //delf
        if(strcmp(comando, "delf") == 0){
            fscanf(fileQry, "%s", j);
            delf(qt, j, fileTxt);
        }
        //delf*
        if(strcmp(comando, "delf*") == 0){
            fscanf(fileQry, "%s %s", j, k);
            delfAst(qt, j, k, fileTxt);
        }

        //T2_ED
        //dq
        if(strcmp(comando, "dq") == 0){
            char hashtag = getc(fileQry);
            hashtag = getc(fileQry);
            if(hashtag == '#'){
                fscanf(fileQry, "%s %f", cep, &r);
                dq(qt, cep, r, 1, fileTxt);
            }
            fseek(fileQry, -2, SEEK_CUR);
            fscanf(fileQry, "%s %f", cep, &r);
            dq(qt, cep, r, 0, fileTxt);
        }
        //del
        if(strcmp(comando, "del") == 0){
            fscanf(fileQry, "%s", cep);
            del(qt, cep, fileTxt);
        }
        //cbq
        if(strcmp(comando, "cbq") == 0){
            fscanf(fileQry, "%f %f %f %s", &x, &y, &r, cb);
            cbq(qt, x, y, r, cb, fileTxt);
        }
        //crd?
        if(strcmp(comando, "crd?") == 0){
            fscanf(fileQry, "%s", cep);
            crd(qt, cep, fileTxt);
        }
        //car
        if(strcmp(comando, "car") == 0){
            fscanf(fileQry, "%f %f %f %f", &x, &y, &w, &h);
            car(qt, x, y, w, h, fileTxt);
        }

        //T3_ED
        //cv
        if(strcmp(comando, "cv") == 0){
            fscanf(fileQry, "%d %s %s %d", &n, cep, face, &num);
            cv(qt, n, cep, faceToChar(face), num);
        }
        //soc
        if(strcmp(comando, "soc") == 0){
            fscanf(fileQry, "%d %s %s %d", &casosCovid, cep, face, &num);
            soc(qt, graph, casosCovid, cep, faceToChar(face), num, fileTxt, idPInt, fileSvgQry);
            idPInt += 100;
        }
        //ci
        if(strcmp(comando, "ci") == 0){
            fscanf(fileQry, "%f %f %f", &x, &y, &r);
            ci(qt, x, y, r, fileTxt);
        }

        //T4_ED
        //m?
        if(strcmp(comando, "m?") == 0){
            fscanf(fileQry, "%s", cep);
            m(qt, ht, cep, fileTxt);
        }
        //dm?
        if(strcmp(comando, "dm?") == 0){
            fscanf(fileQry, "%s", cpf);
            dm(qt, ht, cpf, fileTxt);
        }
        //de?
        if(strcmp(comando, "de?") == 0){
            fscanf(fileQry, "%s", cnpj);
            de(qt, ht, cnpj, fileTxt);
        }
        //mud
        if(strcmp(comando, "mud") == 0){
            fscanf(fileQry, "%s %s %s %d %s", cpf, cep, face, &num, compl );
            mud(qt, ht, cpf, cep, faceToChar(face), num, compl, fileTxt);
        }
        //dmprbt
        if(strcmp(comando, "dmprbt") == 0){
            fscanf(fileQry, " %c %s", &t, sfx); //NÃO APAGAR ESPAÇO ANTES DO %C
            dmprbt(qt, t, sfx, dirSaida, nomeGeoSemExtensao, nomeQrySemExtensao);
        }
        //eplg?
        if(strcmp(comando, "eplg?") == 0){
            fscanf(fileQry, "%s %f %f %f %f", tp, &x, &y, &w, &h);
            eplg(qt, ht, tp, x, y, w, h, fileTxt);
        }
        //catac
        if(strcmp(comando, "catac") == 0){
            fscanf(fileQry, "%f %f %f", &x, &y, &r);
            catac(qt, ht, x, y, r, fileTxt);
        }

        //T5_ED
        //@m?
        if(strcmp(comando, "@m?") == 0){
            fscanf(fileQry, "%s %s", reg, cpf);
            mInt(qt, ht, registradores, reg, cpf);
        }
        if(strcmp(comando, "@e?") == 0){
            fscanf(fileQry, "%s %s %s %d", reg, cep, face, &num);
            eInt(qt, ht, registradores, reg, cep, faceToChar(face), num);
        }
        if(strcmp(comando, "@g?") == 0){
            fscanf(fileQry, "%s %s", reg, id);
            gInt(qt, registradores, reg, id);
        }
        if(strcmp(comando, "@xy") == 0){
            fscanf(fileQry, "%s %f %f", reg, &x, &y);
            xy(qt, registradores, reg, x, y);
        }
        if(strcmp(comando, "ccv") == 0){
            fscanf(fileQry, "%s", sfx);
            graphCiclovia = ccv(graph, sfx, dirSaida, nomeGeoSemExtensao, nomeQrySemExtensao);
        }
        if(strcmp(comando, "p?") == 0){
            fscanf(fileQry, "%s %s %s %s %s", sfx, reg1, reg2, cmc, cmr);
            if(strcmp(sfx, "-") != 0){
                char* pathPIntSfx = NULL;
                char* nomeGeoQry = NULL;
                char* nomeGeoQrySfx = NULL;
                concatenaNomeGeoQry(nomeGeoSemExtensao, nomeQrySemExtensao, "", &nomeGeoQry);
                concatenaNomeGeoQry(nomeGeoQry, sfx, ".svg", &nomeGeoQrySfx);
                concatenaCaminhos(dirSaida, nomeGeoQrySfx, &pathPIntSfx);
                insert(arqsPInt, pathPIntSfx);
                pInt(qt, graph, registradores, sfx, reg1, reg2, cmc, cmr, pathPIntSfx, idPInt);
            }
            else{
                pInt(qt, graph, registradores, sfx, reg1, reg2, cmc, cmr, getInfo(getLast(arqsPInt)), idPInt);
            }
            idPInt += 2;
        }
        if(strcmp(comando, "bf") == 0){
            fscanf(fileQry, "%d", &max);
            bf(qt, graph, max, fileTxt);
        }
        if(strcmp(comando, "sp?") == 0){
            fscanf(fileQry, "%s %s %s %s %s", sfx, reg1, reg2, cmc, cmr);
            //TODO: sp?
        }
        if(strcmp(comando, "pb?") == 0){
            fscanf(fileQry, "%s %s %s %s", sfx, reg1, reg2, cmc);
            if(graphCiclovia != NULL){
                if(strcmp(sfx, "-") != 0){
                    char* pathPbIntSfx = NULL;
                    char* nomeGeoQry = NULL;
                    char* nomeGeoQrySfx = NULL;
                    concatenaNomeGeoQry(nomeGeoSemExtensao, nomeQrySemExtensao, "", &nomeGeoQry);
                    concatenaNomeGeoQry(nomeGeoQry, sfx, ".svg", &nomeGeoQrySfx);
                    concatenaCaminhos(dirSaida, nomeGeoQrySfx, &pathPbIntSfx);
                    insert(arqsPInt, pathPbIntSfx);
                    
                    pbInt(qt, graphCiclovia, registradores, sfx, reg1, reg2, cmc, pathPbIntSfx, idPbInt);
                }
                else{
                    pbInt(qt, graphCiclovia, registradores, sfx, reg1, reg2, cmc, getInfo(getLast(arqsPInt)), idPbInt);
                }
                idPbInt += 1;
            }
        }
    }
    
    FILE* fileArqsPInt = NULL;
    for(Node node = getFirst(arqsPInt); node != NULL; node = getNext(node)){
        fileArqsPInt = fopen(getInfo(node), "a");
        if(fileArqsPInt == NULL){
            continue;
        }
        fprintf(fileArqsPInt, "\n</svg>");
        fclose(fileArqsPInt);
    }

    FILE* fileArqsPbInt = NULL;
    for(Node node = getFirst(arqsPbInt); node != NULL; node = getNext(node)){
        fileArqsPbInt = fopen(getInfo(node), "a");
        if(fileArqsPbInt == NULL){
            continue;
        }
        fprintf(fileArqsPbInt, "\n</svg>");
        fclose(fileArqsPbInt);
    }

    removeList(arqsPInt, 1);
    removeList(arqsPbInt, 1);
    fclose(fileTxt);
    fclose(fileQry);
    fclose(fileSvgQry);
}

char faceToChar(char* face){
    int tam = strlen(face);
    return toupper(face[tam-1]);
}