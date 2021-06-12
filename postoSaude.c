#include <stdio.h>
#include <stdlib.h>

#include "point.h"
#include "postoSaude.h"


typedef struct{
    Point point;
}PostoSaudeStruct;


//Create
PostoSaude criaPostoSaude(float x, float y){
    PostoSaudeStruct* ps = (PostoSaudeStruct*)malloc(sizeof(PostoSaudeStruct));
    Point point = criaPoint(x, y);
    ps->point = point;
    return ps;
}

//Setters
void postoSaudeSetX(PostoSaude posto, float x){
    PostoSaudeStruct* ps = (PostoSaudeStruct*)posto;
    setPointX(ps->point, x);
}

void postoSaudeSetY(PostoSaude posto, float y){
    PostoSaudeStruct* ps = (PostoSaudeStruct*)posto;
    setPointY(ps->point, y);
}

void postoSaudeSetPoint(PostoSaude posto, Point point){
    PostoSaudeStruct* ps = (PostoSaudeStruct*)posto;
    free(ps->point);
    ps->point = point;
}

//Getters
float postoSaudeGetX(PostoSaude posto){
    PostoSaudeStruct* ps = (PostoSaudeStruct*)posto;
    return getPointX(ps->point);
}

float postoSaudeGetY(PostoSaude posto){
    PostoSaudeStruct* ps = (PostoSaudeStruct*)posto;
    return getPointY(ps->point);
}

Point postoSaudeGetPoint(PostoSaude posto){
    PostoSaudeStruct* ps = (PostoSaudeStruct*)posto;
    return ps->point;
}

void postoSaudeSwap(PostoSaude ps1, PostoSaude ps2){
    PostoSaudeStruct* a = (PostoSaudeStruct*) ps1;
    PostoSaudeStruct* b = (PostoSaudeStruct*) ps2;
    PostoSaudeStruct temp = *a;
    *a = *b;
    *b = temp;
}

void postoSaudeAtribuirPonto(PostoSaude posto1, PostoSaude posto2){
    PostoSaudeStruct* ps1 = (PostoSaudeStruct*)posto1;
    PostoSaudeStruct* ps2 = (PostoSaudeStruct*)posto2;

    atribuirPonto(ps1->point, ps2->point);
}

void postoSaudeDesenhaSvgGeo(PostoSaude posto, void* fileSvg){
    fprintf((FILE*)fileSvg, "\n\t<circle cx=\"%f\" cy=\"%f\" r=\"3\" style=\"fill:black;stroke:white;stroke-widht:2\"/>",postoSaudeGetX(posto), postoSaudeGetY(posto));
}