#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "point.h"
#include "quadra.h"

typedef struct quadra{
    char cep[20];
    Point point;
    float w;
    float h;
    float dd;
    char cb[22];
    char cp[22];
    char sw[22];
    int arredondado;
}QuadraStruct;


//Create
Quadra criaQuadra(char* cep, float x, float y, float w, float h, char* cb, char* cp, char* sw, int arredondado){
    QuadraStruct* quad = (QuadraStruct*) malloc(sizeof(QuadraStruct));
    Point point = criaPoint(x, y);
    strcpy(quad->cep, cep);
    quad->point = point;
    quad->w = w;
    quad->h = h;
    quad->dd = 0;
    strcpy(quad->cb, cb);
    strcpy(quad->cp, cp);
    strcpy(quad->sw, sw);
    quad->arredondado = arredondado;
    return quad; 
}

//Setters 
void quadraSetCep(Quadra quadra, char* cep){
    QuadraStruct* quad = (QuadraStruct*) quadra;
    strcpy(quad->cep, cep);
}

void quadraSetX(Quadra quadra, float x){
    QuadraStruct* quad = (QuadraStruct*) quadra;
    setPointX(quad->point, x);
}

void quadraSetY(Quadra quadra, float y){
    QuadraStruct* quad = (QuadraStruct*) quadra;
    setPointY(quad->point, y);
}

void quadraSetWidth(Quadra quadra, float w){
    QuadraStruct* quad = (QuadraStruct*) quadra;
    quad->w = w;
}

void quadraSetHeight(Quadra quadra, float h){
    QuadraStruct* quad = (QuadraStruct*) quadra;
    quad->h = h;
}

void quadraSetCorBorda(Quadra quadra, char* cb){
    QuadraStruct* quad = (QuadraStruct*) quadra;
    strcpy(quad->cb, cb);
}

void quadraSetCorPreenchimento(Quadra quadra, char* cp){
    QuadraStruct* quad = (QuadraStruct*) quadra;
    strcpy(quad->cp, cp);
}

void quadraSetArredondado(Quadra quadra, int arredondado){
    QuadraStruct* quad = (QuadraStruct*) quadra;
    quad->arredondado = arredondado;
}

void quadraSetPoint(Quadra quadra, Point point){
    QuadraStruct* quad = (QuadraStruct*) quadra;
    free(quad->point);
    quad->point = point;
}

void quadraSetDensidadeDemografica(Quadra quadra, float dd){
    QuadraStruct* quad = (QuadraStruct*) quadra;
    quad->dd = dd;
}

void quadraSetEspessura(Quadra quadra, char* sw){
    QuadraStruct* quad = (QuadraStruct*) quadra;
    strcpy(quad->sw, sw);
}

//Getters
char* quadraGetCep(Quadra quadra){
    QuadraStruct* quad = (QuadraStruct*) quadra;
    return quad->cep;
}

float quadraGetX(Quadra quadra){
    QuadraStruct* quad = (QuadraStruct*) quadra;
    return getPointX(quad->point);
}

float quadraGetY(Quadra quadra){
    QuadraStruct* quad = (QuadraStruct*) quadra;
    return getPointY(quad->point);
}

float quadraGetWidth(Quadra quadra){
    QuadraStruct* quad = (QuadraStruct*) quadra;
    return quad->w;
}

float quadraGetHeight(Quadra quadra){
    QuadraStruct* quad = (QuadraStruct*) quadra;
    return quad->h;
}

char* quadraGetCorBorda(Quadra quadra){
    QuadraStruct* quad = (QuadraStruct*) quadra;
    return quad->cb;
}

char* quadraGetCorPreenchimento(Quadra quadra){
    QuadraStruct* quad = (QuadraStruct*) quadra;
    return quad->cp;
}

int quadraGetArredondado(Quadra quadra){
    QuadraStruct* quad = (QuadraStruct*) quadra;
    return quad->arredondado;
}

float quadraGetArea(Quadra quadra){
    QuadraStruct* quad = (QuadraStruct*) quadra;
    return (quad->w * quad->h);
}

Point quadraGetPoint(Quadra quadra){
    QuadraStruct* quad = (QuadraStruct*) quadra;
    return quad->point;
}

float quadraGetDensidadeDemografica(Quadra quadra){
    QuadraStruct* quad = (QuadraStruct*) quadra;
    return quad->dd;
}

char* quadraGetEspessura(Quadra quadra){
    QuadraStruct* quad = (QuadraStruct*) quadra;
    return quad->sw;
}


void quadraSwap(Quadra q1, Quadra q2){
    QuadraStruct* a = (QuadraStruct*) q1;
    QuadraStruct* b = (QuadraStruct*) q2;
    QuadraStruct temp = *a;
    *a = *b;
    *b = temp;
}

void quadraDesenhaSvgGeo(Quadra quadra, void* fileSvg){

    int sombra = -1;
    if(quadraGetDensidadeDemografica(quadra) <= 500){
        sombra = 0;
    }
    else if(quadraGetDensidadeDemografica(quadra) <= 1500){
        sombra = 1;
    }
    else if(quadraGetDensidadeDemografica(quadra) <= 3000){
        sombra = 2;
    }  
    else if(quadraGetDensidadeDemografica(quadra) <= 4500){
        sombra = 3;
    }
    else if(quadraGetDensidadeDemografica(quadra) <= 6000){
        sombra = 4;
    }
    else{
        sombra = 5;
    }
    //<filter id=\"shadow%d\">\n\t\t\t<feDropShadow dx=\"2\" dy=\"2\" stdDeviation=\"0.2\" flood-color=\"%s\"/>\n\t\t</filter>
    fprintf((FILE*)fileSvg, "\n\t<rect x=\"%f\" y=\"%f\" width=\"%f\" height=\"%f\" style=\"stroke:%s;fill:%s;stroke-widht:%s\" filter=\"url(#shadow%d)\"/>", quadraGetX(quadra), quadraGetY(quadra), quadraGetWidth(quadra), quadraGetHeight(quadra), quadraGetCorBorda(quadra), quadraGetCorPreenchimento(quadra), quadraGetEspessura(quadra), sombra); //);
    fprintf((FILE*)fileSvg, "\n\t<text x=\"%f\" y=\"%f\" fill=\"black\" stroke=\"seashell\" stroke-width=\"0.5\" dominant-baseline=\"middle\" text-anchor=\"middle\">%s</text>", quadraGetX(quadra) + (quadraGetWidth(quadra) / 2), quadraGetY(quadra) + (quadraGetHeight(quadra) / 2), quadraGetCep(quadra));
}

void quadraDesenhaSvgQry(Quadra quadra, void* fileSvgQry){
    
    int sombra = -1;
    if(quadraGetDensidadeDemografica(quadra) <= 500){
        sombra = 0;
    }
    else if(quadraGetDensidadeDemografica(quadra) <= 1500){
        sombra = 1;
    }
    else if(quadraGetDensidadeDemografica(quadra) <= 3000){
        sombra = 2;
    }  
    else if(quadraGetDensidadeDemografica(quadra) <= 4500){
        sombra = 3;
    }
    else if(quadraGetDensidadeDemografica(quadra) <= 6000){
        sombra = 4;
    }
    else{
        sombra = 5;
    }

    if(quadraGetArredondado(quadra) == 1){
        fprintf((FILE*)fileSvgQry, "\n\t<rect x=\"%f\" y=\"%f\" width=\"%f\" height=\"%f\" style=\"stroke:%s;fill:%s;stroke-widht:%s\" rx=\"10\" ry=\"10\" />", quadraGetX(quadra), quadraGetY(quadra), quadraGetWidth(quadra), quadraGetHeight(quadra), quadraGetCorBorda(quadra), quadraGetCorPreenchimento(quadra), quadraGetEspessura(quadra));
    }
    else{
        fprintf((FILE*)fileSvgQry, "\n\t<rect x=\"%f\" y=\"%f\" width=\"%f\" height=\"%f\" style=\"stroke:%s;fill:%s;stroke-widht:%s\" filter=\"url(#shadow%d)\"/>", quadraGetX(quadra), quadraGetY(quadra), quadraGetWidth(quadra), quadraGetHeight(quadra), quadraGetCorBorda(quadra), quadraGetCorPreenchimento(quadra), quadraGetEspessura(quadra), sombra); //);
    }
    fprintf((FILE*)fileSvgQry, "\n\t<text x=\"%f\" y=\"%f\" fill=\"black\" stroke=\"seashell\" stroke-width=\"0.5\" dominant-baseline=\"middle\" text-anchor=\"middle\">%s</text>", quadraGetX(quadra) + (quadraGetWidth(quadra) / 2), quadraGetY(quadra) + (quadraGetHeight(quadra) / 2), quadraGetCep(quadra));
}