#ifndef __POSTOSAUDE_H
#define __POSTOSAUDE_H

typedef void* PostoSaude;

/*
Função responsável para criar PostoSaude. 
PRE: Coordenadas x,y do posto de saúde
POS: Retorna um pointer instanciado.
*/
PostoSaude criaPostoSaude(float x, float y);

/*
Setters: Define o atributo do título da função
PRE: Objeto e atributo
*/
void postoSaudeSetX(PostoSaude posto, float x);
void postoSaudeSetY(PostoSaude posto, float y);
void postoSaudeSetPoint(PostoSaude posto, Point point);
/*
Getters: Retorna o atributo do título da função
PRE: Objeto
POS: Atributo especificado
*/
float postoSaudeGetX(PostoSaude posto);
float postoSaudeGetY(PostoSaude posto);
Point postoSaudeGetPoint(PostoSaude posto);

void postoSaudeAtribuirPonto(PostoSaude posto1, PostoSaude posto2);

/*
    Troca dois postoSaude de lugar na memória
    PRE: posto de saude 1 e posto de saude 2
*/
void postoSaudeSwap(PostoSaude ps1, PostoSaude ps2);

/*
    Escreve uma tag SVG do posto no file passado
    PRE: posto de saude e arquivo onde irá ser salvo o SVG
*/
void postoSaudeDesenhaSvgGeo(PostoSaude posto, void* fileSvg);

#endif
