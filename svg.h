#ifndef __SVG_H
#define __SVG_H

#include "quadTree.h"
#include "corPadrao.h"

/*
DesenhaSvgGeo o arquivo SVG do GEO
Pré: As listas, as cores dos elementos e o caminho onde será criada as saídas
*/
void desenhaSvgGeo(QuadTree* qt, char* dirSaida);

/*
DesenhaSvgGeo o arquivo SVG do QRY
Pré: As listas, as cores dos elementos e o caminho onde será criada as saídas
*/
void desenhaSvgQry(QuadTree* qt, char* dirSaida);

#endif
