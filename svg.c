#include <stdio.h>
#include <stdlib.h>

#include "svg.h"
#include "quadTree.h"
#include "circulo.h"
#include "retangulo.h"
#include "texto.h"
#include "quadra.h"
#include "hidrante.h"
#include "semaforo.h"
#include "radioBase.h"
#include "linha.h"
#include "corPadrao.h"
#include "localCasos.h"
#include "postoSaude.h"
#include "poligono.h"


enum LISTAS{CIRCULO, RETANGULO, TEXTO, QUADRA, HIDRANTE, SEMAFORO, RADIOBASE, POSTOSAUDE, LINHA, LOCALCASOS, POLIGONO};

void desenhaSvgGeo(QuadTree* qt, char* dirSaida){

    char* corSombra[6] = {"#FFFF00", "#FF9955", "#FF0000", "#FF00CC", "#6600FF", "#A02C5A"}; //Comando usado para fazer a sombras das quadras no SVG do comando dd (Atualizado para T4)
    FILE* fileSvgGeo = NULL;
    fileSvgGeo = fopen(dirSaida, "w");
    if(!fileSvgGeo){
        exit(1);
    }
    printf("\nArquivo SVG-GEO criado com sucesso!");
    fprintf(fileSvgGeo, "<svg version=\"1.1\" baseProfile=\"full\" width=\"10000\" height=\"10000\" xmlns=\"http://www.w3.org/2000/svg\">");
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

    fprintf(fileSvgGeo, "\n</svg>");
    fclose(fileSvgGeo);
}


void desenhaSvgQry(QuadTree* qt, char* dirSaida){
    //char* corSombra[6] = {"#FFFF00", "#FF9955", "#FF0000", "#FF00CC", "#6600FF", "#A02C5A"}; //Comando usado para fazer a sombras das quadras no SVG do comando dd (Atualizado para T4)
    FILE* fileSvgQry = NULL;
    fileSvgQry = fopen(dirSaida, "a");
    if(!fileSvgQry){
        exit(1);
    }

    percorreLarguraQt(qt[QUADRA], quadraDesenhaSvgQry, fileSvgQry);
    percorreLarguraQt(qt[HIDRANTE], hidranteDesenhaSvgGeo, fileSvgQry);
    percorreLarguraQt(qt[SEMAFORO], semaforoDesenhaSvgGeo, fileSvgQry);
    percorreLarguraQt(qt[RADIOBASE], radioBaseDesenhaSvgGeo, fileSvgQry);
    percorreLarguraQt(qt[POSTOSAUDE], postoSaudeDesenhaSvgGeo, fileSvgQry); 
    percorreLarguraQt(qt[CIRCULO], circuloDesenhaSvgGeo, fileSvgQry);
    percorreLarguraQt(qt[RETANGULO], retanguloDesenhaSvgQry, fileSvgQry);
    percorreLarguraQt(qt[TEXTO], textoDesenhaSvgGeo, fileSvgQry);
    percorreLarguraQt(qt[LINHA], linhaDesenhaSvgQry, fileSvgQry);
    percorreLarguraQt(qt[LOCALCASOS], localCasosDesenhaSvgQry, fileSvgQry);
    percorreLarguraQt(qt[POLIGONO], poligonoDesenhaSvgQry, fileSvgQry);

    fprintf(fileSvgQry, "\n</svg>");
    fclose(fileSvgQry);
}
