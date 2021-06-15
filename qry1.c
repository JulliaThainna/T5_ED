#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "qry1.h"
#include "quadTree.h"
#include "circulo.h"
#include "retangulo.h"
#include "texto.h"
#include "utilitario.h"

enum LISTAS{CIRCULO, RETANGULO, TEXTO, QUADRA, HIDRANTE, SEMAFORO, RADIOBASE, POSTOSAUDE};

//T1
int overlay(QuadTree* qt, char* j, char* k, float* x, float* y, float* w, float* h, FILE* fileTxt){ 
    //Printa a consulta no TXT
    fprintf(fileTxt, "o? %s %s\n", j, k);

    //Inicia o vetor de pontos Xe Y que vão ser desenhados um retangulo pontilhado ou não posteriormente
    float vX[4] = {0, 0, 0, 0};
    float vY[4] = {0, 0, 0, 0};

    //Variaveis para saber as formas (-1 = não iniciado; 0 = circulo e 1 = retangulo)
    int formaJ = -1;
    int formaK = -1;
    //overlay: -1 sem calcular/ impossivel; 0 não sobrepoe; 1 sobrpo
    int overlay = -1;

    //Encontrando Elemento J e vendo se é circulo ou ret (0 ou 1)
    Circulo circuloJ = NULL;
    Retangulo retanguloJ = NULL;
    circuloJ =  getInfoByIdQt(qt[CIRCULO], j);
    retanguloJ = getInfoByIdQt(qt[RETANGULO], j);
    //verifica se o circulo ou retangulo foi encontrado
    if(circuloJ != NULL){
        formaJ = 0;
    }
    else if(retanguloJ != NULL){
        formaJ = 1;
    }

    //Calcula os pontos do retangulo que vai ser desenhado
    //Diferencia de circulo e retangulo para pegar coordenadas certas
    if(formaJ == 0 && circuloJ != NULL){
        vX[0] = circuloGetX(circuloJ) + circuloGetRaio(circuloJ);
        vX[1] = circuloGetX(circuloJ) - circuloGetRaio(circuloJ);
        vY[0] = circuloGetY(circuloJ) + circuloGetRaio(circuloJ);
        vY[1] = circuloGetY(circuloJ) - circuloGetRaio(circuloJ);
    }
    else if(formaJ == 1 && retanguloJ != NULL){
        vX[0] = retanguloGetX(retanguloJ);
        vX[1] = retanguloGetX(retanguloJ) + retanguloGetWidth(retanguloJ);
        vY[0] = retanguloGetY(retanguloJ);
        vY[1] = retanguloGetY(retanguloJ) + retanguloGetHeight(retanguloJ);
    }

    //Encontrando Elemento K e vendo se é circulo ou ret (0 ou 1)
    //Mesma coisa só que para o id K 
    Circulo circuloK = NULL;
    Retangulo retanguloK = NULL;
    circuloK =  getInfoByIdQt(qt[CIRCULO], k);
    retanguloK = getInfoByIdQt(qt[RETANGULO], k);
    if(circuloK != NULL){
        formaK = 0;
    }
    else if(retanguloK!= NULL){
        formaK = 1;
    }

    if(formaK == 0 && circuloK != NULL){
        vX[2] = circuloGetX(circuloK) + circuloGetRaio(circuloK);
        vX[3] = circuloGetX(circuloK) - circuloGetRaio(circuloK);
        vY[2] = circuloGetY(circuloK) + circuloGetRaio(circuloK);
        vY[3] = circuloGetY(circuloK) - circuloGetRaio(circuloK);
    }
    else if(formaK == 1 && retanguloK != NULL){
        vX[2] = retanguloGetX(retanguloK);
        vX[3] = retanguloGetX(retanguloK) + retanguloGetWidth(retanguloK);
        vY[2] = retanguloGetY(retanguloK);
        vY[3] = retanguloGetY(retanguloK) + retanguloGetHeight(retanguloK);
    }

    if(formaJ != -1 && formaK != -1){
        //Escolhe as melhores coordenadas
        *x = minV(vX, 4);
        *y = minV(vY, 4);
        *w = maxV(vX, 4) - *x;
        *h = maxV(vY, 4) - *y;

    }
    //Verifica se as figuras se sobrepõem ou não e retorna o valor, printando no TXT também
    //CIRCULO E CIRCULO
    if(formaJ == 0 && formaK == 0){
        overlay = overlayCirculoCirculo(circuloJ, circuloK);
        fprintf(fileTxt, "CIRCULO E CIRCULO %s\n\n", overlay == 1 ? "SOBREPÕE" : "NÃO SOBREPÕE");
    }
    //CIRCULO E RETANGULO
    else if(formaJ == 0 && formaK == 1){
        overlay = overlayCirculoRetangulo(circuloJ, retanguloK);
        fprintf(fileTxt, "CIRCULO E RETANGULO %s\n\n", overlay == 1 ? "SOBREPÕE" : "NÃO SOBREPÕE");
    }
    //RETANGULO E CIRCULO
    else if(formaJ == 1 && formaK == 0){
        overlay = overlayCirculoRetangulo(circuloK, retanguloJ);
        fprintf(fileTxt, "RETANGULO E CIRCULO %s\n\n", overlay == 1 ? "SOBREPÕE" : "NÃO SOBREPÕE");
    }
    //RETANGULO E RETANGULO
    else if(formaJ == 1 && formaK == 1){
        overlay = overlayRetanguloRetangulo(retanguloJ, retanguloK);
        fprintf(fileTxt, "RETANGULO E RETANGULO %s\n\n", overlay == 1 ? "SOBREPÕE" : "NÃO SOBREPÕE");
    }

    return overlay;
}

int overlayCirculoCirculo(Circulo c1, Circulo c2){
    if(distanciaQuadrada(circuloGetX(c1), circuloGetY(c1), circuloGetX(c2), circuloGetY(c2)) <= (circuloGetRaio(c1) + circuloGetRaio(c2)) * (circuloGetRaio(c1) + circuloGetRaio(c2))){
        return 1;
    }
    return 0;
}

int overlayCirculoRetangulo(Circulo c, Retangulo r){
    float dX = circuloGetX(c) - maxF(retanguloGetX(r), minF(circuloGetX(c), retanguloGetX(r) + retanguloGetWidth(r)));
    float dY = circuloGetY(c) - maxF(retanguloGetY(r), minF(circuloGetY(c), retanguloGetY(r) + retanguloGetHeight(r)));
    if((dX * dX + dY * dY) <= (circuloGetRaio(c) * circuloGetRaio(c))){
        return 1;
    } 
    return 0;
}

int overlayRetanguloRetangulo(Retangulo r1, Retangulo r2){

    int inside = -1;

    float r1X = retanguloGetX(r1);
    float r1Y = retanguloGetY(r1);
    float r1W = retanguloGetWidth(r1);
    float r1H = retanguloGetHeight(r1);

    float r2X = retanguloGetX(r2);
    float r2Y = retanguloGetY(r2);
    float r2W = retanguloGetWidth(r2);
    float r2H = retanguloGetHeight(r2);

    //Existe algum ponto do r1 contido no r2?
    inside = insideRetangulo(r1X, r1Y, r2X, r2Y, r2W, r2H);
    if(inside == 1 || inside == 2){
        return 1;
    }
    inside = insideRetangulo(r1X + r1W, r1Y, r2X, r2Y, r2W, r2H);
    if(inside == 1 || inside == 2){
        return 1;
    }
    inside = insideRetangulo(r1X, r1Y + r1H, r2X, r2Y, r2W, r2H);
    if(inside == 1 || inside == 2){
        return 1;
    }
    inside = insideRetangulo(r1X + r1W, r1Y + r1H, r2X, r2Y, r2W, r2H);
    if(inside == 1 || inside == 2){
        return 1;
    }

    //Existe algum ponto do r2 contido no r1?
    inside = insideRetangulo(r2X, r2Y, r1X, r1Y, r1W, r1H);
    if(inside == 1 || inside == 2){
        return 1;
    }
    inside = insideRetangulo(r2X + r2W, r2Y, r1X, r1Y, r1W, r1H);
    if(inside == 1 || inside == 2){
        return 1;
    }
    inside = insideRetangulo(r2X, r2Y + r2H, r1X, r1Y, r1W, r1H);
    if(inside == 1 || inside == 2){
        return 1;
    }
    inside = insideRetangulo(r2X + r2W, r2Y + r2H, r1X, r1Y, r1W, r1H);
    if(inside == 1 || inside == 2){
        return 1;
    }
    
    return 0;
}


int inside(QuadTree* qt, char* j, float x, float y, float* centroMassaX, float* centroMassaY, FILE* fileTxt){

    //Acho o j dentro da quadtree de circ ou da quadtree de retangulo ou não encontro(NULL)
    Circulo circulo =  getInfoByIdQt(qt[CIRCULO], j);
    Retangulo retangulo = getInfoByIdQt(qt[RETANGULO], j);

    //Printo a consulta do o? no txt 
    fprintf(fileTxt, "i? %s %f %f\n", j, x, y);

    //
    int isInside = -1;

    //Se o elemento j foi encontrado na quadtree de circulo
    if(circulo != NULL){
        *centroMassaX = circuloGetX(circulo);
        *centroMassaY = circuloGetY(circulo);
        isInside = insideCirculo(x, y, circuloGetX(circulo), circuloGetY(circulo), circuloGetRaio(circulo));
        fprintf(fileTxt, "FIGURA: CIRCULO | X,Y %s \n", isInside == 1 ? "INTERNO" : "EXTERNO");
    }
    
    //Se o elemento j foi incontrado na quadtree de retangulo
    else if(retangulo != NULL){
        *centroMassaX = retanguloGetX(retangulo) + (retanguloGetWidth(retangulo) / 2); //centro de massa é x+(w/2)
        *centroMassaY = retanguloGetY(retangulo) + (retanguloGetHeight(retangulo) / 2); //centro de massa é y+(h/2)
        //Vejo se o ponto x,y está dentro do retangulo, se sim retorna 1, senão retorna 0, ou retorna 2 (na borda)
        isInside = insideRetangulo(x, y, retanguloGetX(retangulo), retanguloGetY(retangulo), retanguloGetWidth(retangulo), retanguloGetHeight(retangulo));
        if(isInside == 2){
            isInside = 0;
        }
        fprintf(fileTxt, "FIGURA: RETANGULO | X,Y %s \n", isInside == 1 ? "INTERNO" : "EXTERNO"); //printo o nome da figura e se o ponto x,y está dentro ou fora
    }

    return isInside;
}


void pnt(QuadTree* qt, char* j, char* cb, char* cp, FILE* fileTxt){
    Circulo circulo = getInfoByIdQt(qt[0], j);
    Retangulo retangulo = getInfoByIdQt(qt[1], j);
    Texto texto = getInfoByIdQt(qt[2], j);

    fprintf(fileTxt, "\npnt %s %s %s\n", j, cb, cp);

    if(circulo != NULL){
        circuloSetCorBorda(circulo, cb);
        circuloSetCorPreenchimento(circulo, cp);
        fprintf(fileTxt, "CIRCULO | X: %f  Y: %f", circuloGetX(circulo), circuloGetY(circulo));
    }
    else if(retangulo != NULL){
        retanguloSetCorBorda(retangulo, cb);
        retanguloSetCorPreenchimento(retangulo, cp);
        fprintf(fileTxt, "RETANGULO | X: %f  Y: %f", retanguloGetX(retangulo), retanguloGetY(retangulo));
    }
    else if(texto != NULL){
        textoSetCorBorda(texto, cb);
        textoSetCorPreenchimento(texto, cp);
        fprintf(fileTxt, "TEXTO | X: %f  Y: %f", textoGetX(texto), textoGetY(texto));
    }
}

void pntAst(QuadTree* qt, char* j, char* k, char* cb, char* cp, FILE* fileTxt){
    int intJ = atoi(j);
    int intK = atoi(k);

    int minJK = min(intJ, intK);
    int maxJK = max(intJ, intK);

    int num = maxJK - minJK + 1;

    for(int i = minJK; i < minJK + num; i++){
        char id[10];
        sprintf(id, "%d", i);
        pnt(qt, id, cb, cp, fileTxt);
    }
}


void delf(QuadTree* qt, char* j, FILE* fileTxt){
    Circulo circulo = getInfoByIdQt(qt[CIRCULO], j);
    Retangulo retangulo = getInfoByIdQt(qt[RETANGULO], j);
    Texto texto = getInfoByIdQt(qt[TEXTO], j);

    fprintf(fileTxt, "delf %s", j);

    if(circulo != NULL){
        fprintf(fileTxt, "CIRCULO | ID: %s  X: %f  Y: %f  R: %f  CB: %s  CP: %s", circuloGetId(circulo), circuloGetX(circulo), circuloGetY(circulo), circuloGetRaio(circulo), circuloGetCorBorda(circulo), circuloGetCorPreenchimento(circulo));
        circulo = removeNoQt(qt, getNoQt(qt, circuloGetX(circulo), circuloGetY(circulo)));
        free(circuloGetPoint(circulo));
        free(circulo);
        
    }
    else if(retangulo != NULL){
        fprintf(fileTxt, "RETANGULO | ID: %s  X: %f  Y: %f  W: %f  H: %f  CB: %s  CP: %s", retanguloGetId(retangulo), retanguloGetX(retangulo), retanguloGetY(retangulo), retanguloGetWidth(retangulo), retanguloGetHeight(retangulo), retanguloGetCorBorda(retangulo), retanguloGetCorPreenchimento(retangulo));
        retangulo = removeNoQt(qt, getNoQt(qt, retanguloGetX(retangulo), retanguloGetY(retangulo)));
        free(retanguloGetPoint(retangulo));
        free(retangulo);
    }
    else if(texto != NULL){
        fprintf(fileTxt, "TEXTO | ID: %s  X: %f  Y: %f  CB: %s  CP: %s  TEXTO: %s", textoGetId(texto), textoGetX(texto), textoGetY(texto), textoGetCorBorda(texto), textoGetCorPreenchimento(texto), textoGetTexto(texto));
        texto = removeNoQt(qt, getNoQt(qt, textoGetX(texto), textoGetY(texto)));
        free(textoGetPoint(texto));
        free(texto);
    }

}

void delfAst(QuadTree* qt, char* j, char* k, FILE* fileTxt){
    int intJ = atoi(j);
    int intK = atoi(k);

    int minJK = min(intJ, intK);
    int maxJK = max(intJ, intK);

    int num = maxJK - minJK + 1;

    for(int i = minJK; i < minJK + num; i++){
        char id[10];
        sprintf(id, "%d", i);
        delf(qt, id, fileTxt);
    }
}
