#ifndef CORPADRAO__H_
#define CORPADRAO__H_

typedef void* CorPadrao;

//Função responsável para criar CoresPadrao. Retorna um pointer instanciado.
CorPadrao criaCorPadrao(char* quadraSw, char* quadraCfill, char* quadraCstrk, char* hidranteSw, char* hidranteCfill, char* hidranteCstrk, char* radioBaseSw, char* radioBaseCfill, char* radioBaseCstrk, char* semaforoSw, char* semaforoCfill, char* semaforoCstrk, char* circuloSw, char* retanguloSw);

/*
Setters: Define o atributo do título da função
PRE: Objeto e atributo
*/
void coresPadraoSetPreenchimentoQuadras(CorPadrao corPadrao, char* cfill);
void coresPadraoSetBordaQuadras(CorPadrao corPadrao, char* cstrk);
void coresPadraoSetEspessuraQuadras(CorPadrao corPadrao, char* sw);

void coresPadraoSetPreenchimentoHidrantes(CorPadrao corPadrao, char* cfill);
void coresPadraoSetBordaHidrantes(CorPadrao corPadrao, char* cstrk);
void coresPadraoSetEspessuraHidrantes(CorPadrao corPadrao, char* sw);

void coresPadraoSetPreenchimentoRadioBases(CorPadrao corPadrao, char* cfill);
void coresPadraoSetBordaRadioBases(CorPadrao corPadrao, char* cstrk);
void coresPadraoSetEspessuraRadioBases(CorPadrao corPadrao, char* sw);

void coresPadraoSetPreenchimentoSemaforos(CorPadrao corPadrao, char* cfill);
void coresPadraoSetBordaSemaforos(CorPadrao corPadrao, char* cstrk);
void coresPadraoSetEspessuraSemaforos(CorPadrao corPadrao, char* sw);

void coresPadraoSetEspessuraCirculos(CorPadrao cores, char* cw);
void coresPadraoSetEspessuraRetangulos(CorPadrao cores, char* rw);

/*
Getters: Retorna o atributo do título da função
PRE: Objeto
POS: Atributo especificado
*/
char* coresPadraoGetPreenchimentoQuadras(CorPadrao corPadrao);
char* coresPadraoGetBordaQuadras(CorPadrao corPadrao);
char* coresPadraoGetEspessuraQuadras(CorPadrao corPadrao);

char* coresPadraoGetPreenchimentoHidrantes(CorPadrao corPadrao);
char* coresPadraoGetBordaHidrantes(CorPadrao corPadrao);
char* coresPadraoGetEspessuraHidrantes(CorPadrao corPadrao);

char* coresPadraoGetPreenchimentoRadioBases(CorPadrao corPadrao);
char* coresPadraoGetBordaRadioBases(CorPadrao corPadrao);
char* coresPadraoGetEspessuraRadioBases(CorPadrao corPadrao);

char* coresPadraoGetPreenchimentoSemaforos(CorPadrao corPadrao);
char* coresPadraoGetBordaSemaforos(CorPadrao corPadrao);
char* coresPadraoGetEspessuraSemaforos(CorPadrao corPadrao);

char* coresPadraoGetEspessuraCirculos(CorPadrao cores);
char* coresPadraoGetEspessuraRetangulos(CorPadrao cores);

#endif
