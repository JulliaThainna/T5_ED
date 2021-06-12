#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "leituraGeo.h" 
#include "corPadrao.h"
#include "doublyLinkedList.h"
//T1_ED
#include "circulo.h"
#include "retangulo.h"
#include "texto.h"
#include "linha.h"
//T2_ED
#include "quadra.h"
#include "hidrante.h"
#include "semaforo.h"
#include "radioBase.h"
//T3_ED
#include "postoSaude.h"
#include "densidadeDemografica.h"
//T4_ED
#include "hashTable.h"


enum LISTAS{CIRCULO, RETANGULO, TEXTO, QUADRA, HIDRANTE, SEMAFORO, RADIOBASE, POSTOSAUDE, DENSIDADEDEMOGRAFICA, QUADRAS2};
enum HASHTABLE{CPF_ENDERECO, TIPO_DESCRICAO, CPF_DADOS, CEP_QUADRA};

typedef struct nx{
    int i;
    int nq;
    int nh;
    int ns;
    int nr;
}NxStruct;


void readGeo(DoublyLinkedList* listas, char* dirGeo, CorPadrao cores){
    FILE* fileGeo = NULL;
    fileGeo = fopen(dirGeo, "r");
    if(!fileGeo){
        exit(1);
    }
    printf("Arquivo GEO aberto com sucesso!");

    //Numeros maximos de Elementos em cada lista;
     NxStruct dft;
     dft.i = 1000;
     dft.nq = 1000;
     dft.nh = 1000;
     dft.ns = 1000;
     dft.nr = 1000;

    //Quantidade atual de Elementos em cada lista
     NxStruct atual;
     atual.i = 0;
     atual.nq = 0;
     atual.nh = 0;
     atual.ns = 0;
     atual.nr = 0;

    //Variaveis auxiliares
    char comando[3], cp[22], cb[22], cep[20], sw[22], cw[22], rw[22], cfill[22], cstrk[22], buffer, id[20];
    int bufferSize = 0;
    float r, x, y, w, h, d;
    char* txt = NULL;

    //Variáveis auxiliares para formas
    Circulo auxCirc = NULL;
    Retangulo auxRet = NULL;
    Texto auxTex = NULL;
    Quadra quadraAux = NULL;
    Hidrante hidranteAux = NULL;
    Semaforo semaforoAux = NULL;
    RadioBase radiobaseAux = NULL;
    PostoSaude postoSaudeAux = NULL;
    DensidadeDemografica densidadeDemograficaAux = NULL;

    while(1){
        fscanf(fileGeo, "%s", comando);
        if(feof(fileGeo)){
            break;
        }
        
        //T1_ED
        //Comando: nx
        //nx i(circulos, retangulos ?e textos?) quadras hidrantes semaforos radiobases 
        else if(strcmp(comando, "nx") == 0){
            fscanf(fileGeo, "%d %d %d %d %d", &dft.i, &dft.nq, &dft.nh, &dft.ns, &dft.nr);
        }
        //Comando: c
        else if(strcmp(comando, "c") == 0){
            fscanf(fileGeo, "%s %f %f %f %s %s", id, &r, &x, &y, cb, cp);
            auxCirc = criaCirculo(id, x, y, r, cb, cp, coresPadraoGetEspessuraCirculos(cores));
            insert(listas[CIRCULO], auxCirc);
        }
        //Comando: r
        else if(strcmp(comando, "r") == 0){
            fscanf(fileGeo, "%s %f %f %f %f %s %s", id, &w, &h, &x, &y, cb, cp);
            auxRet = criaRetangulo(id, 0, x, y, w, h, cb, cp, coresPadraoGetEspessuraRetangulos(cores));
            insert(listas[RETANGULO], auxRet);
        }
        //Comando: t
        else if(strcmp(comando, "t") == 0){
            fscanf(fileGeo, "%s %f %f %s %s", id, &x, &y, cb, cp);
            
            buffer = getc(fileGeo);
            while(!feof(fileGeo) && buffer != '\n'){
                buffer = getc(fileGeo);
                bufferSize++;
            }
            bufferSize++;
            fseek(fileGeo, -bufferSize, SEEK_CUR);
            buffer = getc(fileGeo);
            txt = (char*) malloc(sizeof(char) * (bufferSize + 1));
            if(txt == NULL){
                exit(1);
            }
            fscanf(fileGeo, "%[^\n]s", txt);
            auxTex = criaTexto(id, bufferSize, x, y, txt, cb, cp);
            insert(listas[TEXTO], auxTex);
            bufferSize = 0;
            free(txt);
        }

        
        //T2_ED
        //Comando: q
        else if(strcmp(comando, "q") == 0){
            fscanf(fileGeo, "%s %f %f %f %f", cep, &x, &y, &w, &h);
            
            // A struct de quantidades atuais dos eq. urbanos é definida como 0
            // A struct de quantidades default dos eq. urbanos é definida pra 1000
            // Se o comando nx é usado esse valor muda, senão não
            // A condição para criar quadras e adicioná-las na lista, é se a quantidade atual é menor do que o default padrão ou definido pelo nx
            if(atual.nq < dft.nq){
                atual.nq += 1;
                quadraAux = criaQuadra(cep, x, y, w, h, coresPadraoGetBordaQuadras(cores), coresPadraoGetPreenchimentoQuadras(cores), coresPadraoGetEspessuraQuadras(cores), 0);
                insert(listas[QUADRA], quadraAux);
                insert(listas[QUADRAS2], quadraAux);
            }
        }
        //Comando: h
        else if(strcmp(comando, "h") == 0){
            fscanf(fileGeo, "%s %f %f", cep, &x, &y);

            if(atual.nh < dft.nh){
                atual.nh += 1;
                hidranteAux = criaHidrante(cep, x, y, coresPadraoGetPreenchimentoHidrantes(cores), coresPadraoGetBordaHidrantes(cores), coresPadraoGetEspessuraHidrantes(cores));
                insert(listas[HIDRANTE], hidranteAux);
            }
        }
        //Comando: s
        else if(strcmp(comando, "s") == 0){
            fscanf(fileGeo, "%s %f %f", cep, &x, &y);

            if(atual.ns < dft.ns){
                atual.ns += 1;
                semaforoAux = criaSemaforo(cep, x, y, coresPadraoGetPreenchimentoSemaforos(cores), coresPadraoGetBordaSemaforos(cores), coresPadraoGetEspessuraSemaforos(cores));
                insert(listas[SEMAFORO], semaforoAux);
            }
        }
        //Comando: rb
        else if(strcmp(comando, "rb") == 0){
            fscanf(fileGeo, "%s %f %f", cep, &x, &y);

            if(atual.nr < dft.nr){
                atual.nr += 1;
                radiobaseAux = criaRadioBase(cep, x, y, coresPadraoGetPreenchimentoRadioBases(cores), coresPadraoGetBordaRadioBases(cores), coresPadraoGetEspessuraRadioBases(cores));
                insert(listas[RADIOBASE], radiobaseAux);
            }   
        }
        //Comando: cq
        else if(strcmp(comando, "cq") == 0){
            fscanf(fileGeo, "%s %s %s", sw, cfill, cstrk);

            coresPadraoSetPreenchimentoQuadras(cores, cfill);
            coresPadraoSetBordaQuadras(cores, cstrk);
            coresPadraoSetEspessuraQuadras(cores, sw);
        }   
        //Comando: ch
        else if(strcmp(comando, "ch") == 0){
            fscanf(fileGeo, "%s %s %s", sw, cfill, cstrk);

            coresPadraoSetPreenchimentoHidrantes(cores, cfill);
            coresPadraoSetBordaHidrantes(cores, cstrk);
            coresPadraoSetEspessuraHidrantes(cores, sw);
        }
        //Comando: cr
        else if(strcmp(comando, "cr") == 0){
            fscanf(fileGeo, "%s %s %s", sw, cfill, cstrk);

            coresPadraoSetPreenchimentoRadioBases(cores, cfill);
            coresPadraoSetBordaRadioBases(cores, cstrk);
            coresPadraoSetEspessuraRadioBases(cores, sw);
        }
        //Comando: cs
        else if(strcmp(comando, "cs") == 0){
            fscanf(fileGeo, "%s %s %s", sw, cfill, cstrk);

            coresPadraoSetPreenchimentoSemaforos(cores, cfill);
            coresPadraoSetBordaSemaforos(cores, cstrk);
            coresPadraoSetEspessuraSemaforos(cores, sw);
        }
        //Comando: sw
        else if(strcmp(comando, "sw") == 0){
            fscanf(fileGeo, "%s %s", cw, rw);

            coresPadraoSetEspessuraCirculos(cores, cw);
            coresPadraoSetEspessuraRetangulos(cores, rw);
        }


        //T3_ED
        //Comando: ps
        else if(strcmp(comando, "ps") == 0){
            fscanf(fileGeo, "%f %f", &x, &y);

            postoSaudeAux = criaPostoSaude(x, y);
            insert(listas[POSTOSAUDE], postoSaudeAux);
        }
        //Comando: dd
        else if(strcmp(comando, "dd") == 0){
            fscanf(fileGeo, "%f %f %f %f %f", &x, &y, &w, &h, &d);
            
            densidadeDemograficaAux = criaDensidadeDemografica(x, y, w, h, d);
            insert(listas[DENSIDADEDEMOGRAFICA], densidadeDemograficaAux);
        }
    }

    fclose(fileGeo);
}
