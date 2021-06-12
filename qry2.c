#include <stdio.h>
#include <stdlib.h>

#include "qry2.h"
#include "quadTree.h"
#include "circulo.h"
#include "quadra.h"
#include "hidrante.h"
#include "semaforo.h"
#include "radioBase.h"
#include "linha.h"
#include "utilitario.h"
#include "texto.h"
#include "retangulo.h"
#include "string.h"

enum LISTAS{CIRCULO, RETANGULO, TEXTO, QUADRA, HIDRANTE, SEMAFORO, RADIOBASE, POSTOSAUDE, LINHA};

void dq(QuadTree* qt, char* id, float r, int hashtag, FILE* fileTxt){
     fprintf(fileTxt, "\ndq %s %s %f", hashtag == 1 ? "#" : " ", id, r);
     fflush(stdout);

     float x = 0, y = 0;

     Hidrante hidrante = getInfoByIdQt(qt[HIDRANTE], id);
     if(hidrante != NULL){
          fflush(stdout);
          x = hidranteGetX(hidrante);
          y = hidranteGetY(hidrante);
          fprintf(fileTxt, "HIDRANTE | ID: %s  X: %f  Y: %f", hidranteGetId(hidrante), hidranteGetX(hidrante), hidranteGetY(hidrante));
     }

     Semaforo semaforo = getInfoByIdQt(qt[SEMAFORO], id);
     if(semaforo != NULL){
          fflush(stdout);
          x = semaforoGetX(semaforo);
          y = semaforoGetY(semaforo);
          fprintf(fileTxt, "SEMAFORO | ID: %s  X: %f  Y: %f", semaforoGetId(semaforo), semaforoGetX(semaforo), semaforoGetY(semaforo));
     }

     RadioBase radiobase = getInfoByIdQt(qt[RADIOBASE], id);
     if(radiobase != NULL){
          fflush(stdout);
          x = radioBaseGetX(radiobase);
          y = radioBaseGetY(radiobase);
          fprintf(fileTxt, "RADIOBASE | ID: %s  X: %f  Y: %f", radioBaseGetId(radiobase), radioBaseGetX(radiobase), radioBaseGetY(radiobase));
     }

     DoublyLinkedList lista = nosDentroCirculoQt(qt[QUADRA], x, y, r);
     for(Node aux = getFirst(lista); aux != NULL; aux = getNext(aux)){
          QtNo noArvore = getInfo(aux); //Como é retornada uma lista de nós da árvore, é preciso pegar a info da lista -> nó da qt
          Quadra quadra = getInfoQt(qt[QUADRA], noArvore); //Agora que sabemos qual é o nó da árvore, pegamos a info desse nó (struct da respectiva quadra)

          float qX = quadraGetX(quadra);
          float qY = quadraGetY(quadra);
          float qW = quadraGetWidth(quadra);
          float qH = quadraGetHeight(quadra);

          if(insideCirculo(qX, qY, x, y, r) == 1 && insideCirculo(qX + qW, qY, x, y, r) == 1 && insideCirculo(qX, qY + qH, x, y, r) == 1 && insideCirculo(qX + qW, qY + qH, x, y, r) == 1){
               if(hashtag == 0){
                    removeNoQt(qt[QUADRA], noArvore);
                    fprintf(fileTxt, "QUADRA | CEP: %s", quadraGetCep(quadra));
                    free(quadraGetPoint(quadra));
                    free(quadra);
               }
               else{
                    quadraSetArredondado(quadra, 1);
                    quadraSetCorPreenchimento(quadra, "beige");
                    quadraSetCorBorda(quadra, "olive");
               }
          }
     }
     //anel em volta do equip
     Circulo anel1 = criaCirculo("-1", x, y, 10, "indigo", "none", "8px");
     Circulo anel2 = criaCirculo("-1", x, y, 23, "crimson", "none", "8px");
     insereQt(qt[CIRCULO], circuloGetPoint(anel1), anel1);
     insereQt(qt[CIRCULO], circuloGetPoint(anel2), anel2);

     //circulo raio r região de deleção
     Circulo circulo = criaCirculo("-1", x, y, r, "goldenrod", "none", "8px");
     insereQt(qt[CIRCULO], circuloGetPoint(circulo), circulo);
     
     removeList(lista, 0);
}


void del(QuadTree* qt, char* id, FILE* fileTxt){
     fprintf(fileTxt, "\ndel %s", id);

     Quadra quadra = getInfoByIdQt(qt[QUADRA], id);
     if(quadra != NULL){
          fprintf(fileTxt, "\nX:%f Y:%f - QUADRA CEP: %s", quadraGetX(quadra), quadraGetY(quadra), quadraGetCep(quadra));
          quadra = removeNoQt(qt[QUADRA], getNoQt(qt[QUADRA], quadraGetX(quadra), quadraGetY(quadra)));
          Linha linha = criaLinha(quadraGetX(quadra) + (quadraGetWidth(quadra) / 2), quadraGetY(quadra) + (quadraGetHeight(quadra) / 2), quadraGetX(quadra) + (quadraGetWidth(quadra) / 2), 0, 0, 0, quadraGetCep(quadra));
          insereQt(qt[LINHA], linhaGetP1(linha), linha);
          free(quadraGetPoint(quadra));
          free(quadra);
          return;
     }
     Hidrante hidrante = getInfoByIdQt(qt[HIDRANTE], id);
     if(hidrante != NULL){
          fprintf(fileTxt, "\nX:%f Y:%f - HIDRANTE CEP: %s", hidranteGetX(hidrante), hidranteGetY(hidrante), hidranteGetId(hidrante));
          hidrante = removeNoQt(qt[HIDRANTE], getNoQt(qt[HIDRANTE], hidranteGetX(hidrante), hidranteGetY(hidrante)));
          Linha linha = criaLinha(hidranteGetX(hidrante), hidranteGetY(hidrante), hidranteGetX(hidrante), 0, 0, 0, hidranteGetId(hidrante));
          insereQt(qt[LINHA], linhaGetP1(linha), linha);
          free(hidranteGetPoint(hidrante));
          free(hidrante);
          return;
     } 
     Semaforo semaforo = getInfoByIdQt(qt[SEMAFORO], id);
     if(semaforo != NULL){
          fprintf(fileTxt, "\nX:%f Y:%f - SEMAFORO CEP: %s", semaforoGetX(semaforo), semaforoGetY(semaforo), semaforoGetId(semaforo));
          semaforo = removeNoQt(qt[SEMAFORO], getNoQt(qt[SEMAFORO], semaforoGetX(semaforo), semaforoGetY(semaforo)));
          Linha linha = criaLinha(semaforoGetX(semaforo), semaforoGetY(semaforo), semaforoGetX(semaforo), 0, 0, 0, semaforoGetId(semaforo));
          insereQt(qt[LINHA], linhaGetP1(linha), linha);
          free(semaforoGetPoint(semaforo));
          free(semaforo);
          return;
     }
     RadioBase radiobase = getInfoByIdQt(qt[RADIOBASE], id);
     if(radiobase != NULL){
          fprintf(fileTxt, "\nX:%f Y:%f - RADIOBASE CEP: %s", radioBaseGetX(radiobase), radioBaseGetY(radiobase), radioBaseGetId(radiobase));
          radiobase = removeNoQt(qt[RADIOBASE], getNoQt(qt[RADIOBASE], radioBaseGetX(radiobase), radioBaseGetY(radiobase)));
          Linha linha = criaLinha(radioBaseGetX(radiobase), radioBaseGetY(radiobase), radioBaseGetX(radiobase), 0, 0, 0, radioBaseGetId(radiobase));
          insereQt(qt[LINHA], linhaGetP1(linha), linha);
          free(radioBaseGetPoint(radiobase));
          free(radiobase);
          return;
     }
}


void cbq(QuadTree* qt, float x, float y, float r, char* cstrk, FILE* fileTxt){
     DoublyLinkedList lista = nosDentroCirculoQt(qt[QUADRA], x, y, r); //Retorna uma lista de nós que estão dentro do circulo x,y com raio r

     fprintf(fileTxt, "\ncbq %f %f %f %s\n", x, y, r, cstrk);
     
     for(Node aux = getFirst(lista); aux != NULL; aux = getNext(aux)){

          //Ao inves de nosDentroCirculo retornar uma lista dos ELEMENTOS da quadtree, ela retorna uma lista de NOS
          //As infos (quadra, circ, ret, hidrante, etc) ficam DENTRO DO NÓ DA QUADTREE!!! Por isso temos que acessar a informação da lista (que é o node da QT) e depois pegar a informação desse node 
          //Além do mais, o parâmetro da arvore é inutil, já que getInfoQt não usa. Dentro dele está qt = qt só para não dar warning de unused. Retorna só no->info;
          QtNo noArvore = getInfo(aux); //Nosso nó da arvore
          Quadra quadra = getInfoQt(qt[QUADRA], noArvore); //Pega a quadra

          float qX = quadraGetX(quadra);
          float qY = quadraGetY(quadra);
          float qW = quadraGetWidth(quadra);
          float qH = quadraGetHeight(quadra);

          if(insideCirculo(qX, qY, x, y, r) == 1 && insideCirculo(qX + qW, qY, x, y, r) == 1 && insideCirculo(qX, qY + qH, x, y, r) == 1 && insideCirculo(qX + qW, qY + qH, x, y, r) == 1){
               quadraSetCorBorda(quadra, cstrk);
               fprintf(fileTxt, "CEP QUADRA: %s\n", quadraGetCep(quadra));
          }
     }
     removeList(lista, 0);
}


void crd(QuadTree* qt, char* id, FILE* fileTxt){
     fprintf(fileTxt, "\ncrd? %s", id);

     Quadra quadra = getInfoByIdQt(qt[QUADRA], id);
     if(quadra != NULL){
          fprintf(fileTxt, "\nX:%f Y:%f - QUADRA CEP: %s", quadraGetX(quadra), quadraGetY(quadra), quadraGetCep(quadra));
          return;
     }
     Hidrante hidrante = getInfoByIdQt(qt[HIDRANTE], id);
     if(hidrante != NULL){
          fprintf(fileTxt, "\nX:%f Y:%f - HIDRANTE CEP: %s", hidranteGetX(hidrante), hidranteGetY(hidrante), hidranteGetId(hidrante));
          return;
     } 
     Semaforo semaforo = getInfoByIdQt(qt[SEMAFORO], id);
     if(semaforo != NULL){
          fprintf(fileTxt, "\nX:%f Y:%f - SEMAFORO CEP: %s", semaforoGetX(semaforo), semaforoGetY(semaforo), semaforoGetId(semaforo));
          return;
     }
     RadioBase radiobase = getInfoByIdQt(qt[RADIOBASE], id);
     if(radiobase != NULL){
          fprintf(fileTxt, "\nX:%f Y:%f - RADIOBASE CEP: %s", radioBaseGetX(radiobase), radioBaseGetY(radiobase), radioBaseGetId(radiobase));
          return;
     }
}


void car(QuadTree* qt, float x, float y, float w, float h, FILE* fileTxt){
     DoublyLinkedList lista = nosDentroRetanguloQt(qt[QUADRA], x, y, x + w, y + h); //Retorna uma lista de nós que estão dentro do retangulo x, y, w, h

     fprintf(fileTxt, "\ncar %f %f %f %f", x, y, w, h);

     float areaTotal = 0;

     for(Node aux = getFirst(lista); aux != NULL; aux = getNext(aux)){
          QtNo noArvore = getInfo(aux); //Nosso nó da arvore
          Quadra q = getInfoQt(qt[QUADRA], noArvore); //Pega a quadra

          float qX = quadraGetX(q);
          float qY = quadraGetY(q);
          float qW = quadraGetWidth(q);
          float qH = quadraGetHeight(q);

          if(insideRetangulo(qX, qY, x, y, w, h) == 1 && insideRetangulo(qX + qW, qY, x, y, w, h) == 1 && insideRetangulo(qX, qY + qH, x, y, w, h) == 1 && insideRetangulo(qX + qW, qY + qH, x, y, w, h) == 1){
               //Tudo que estiver aqui dentro vai ser executado para as quadras que estiverem completamente dentro do retangulo

               //Pegar a area da quadra
               float areaQuadraAtual = quadraGetArea(q);

               //Escrever a area da quadra dentro da quadra (Querendo adicionar um TEXTO para ser desenhado no SVG)
               //Para escrever um texto com um valor que é float, eu tenho que converter pra string
               char areaQuadraAtualString[20];
               sprintf(areaQuadraAtualString, "%f", areaQuadraAtual); //Converte float para string. O 1o parâmetro é sempre a string e o resto é o float
               Texto tAux = criaTexto("-1", strlen(areaQuadraAtualString), qX + (qW / 2), qY + (qH / 2), areaQuadraAtualString, "seashell", "black"); //Crio meu texto com a area que vai ser printada dentro da quadra
               insereQt(qt[TEXTO], textoGetPoint(tAux), tAux); //Adiciono texto na QT
               //Somar a area da quadra com a area total
               areaTotal += areaQuadraAtual;

               //Imprime no TXT a area e as informações da quadra atual
               fprintf(fileTxt, "\nQUADRA CEP: %s - ÁREA: %f", quadraGetCep(q), areaQuadraAtual);
          }
     }

     //Printar o retangulo do comando
     Retangulo rAux = criaRetangulo("-1", 0, x, y, w, h, "pink", "none", "3px");
     insereQt(qt[RETANGULO], retanguloGetPoint(rAux), rAux);

     //Traçar linha do ponto X, Y até o topo com a area total ao lado
     char areaTotalString[10];
     sprintf(areaTotalString, "%f", areaTotal);
     Linha lAux = criaLinha(x, y, x, 0, 0, 0, areaTotalString);
     insereQt(qt[LINHA], linhaGetP1(lAux), lAux);

     //Imprime Área total das quadras
     fprintf(fileTxt, "\n ÁREA TOTAL: %f\n", areaTotal);

     removeList(lista, 0);
}
