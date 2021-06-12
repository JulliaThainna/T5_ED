#include <stdio.h>
#include <stdlib.h>
#include <string.h>



//Refatorar error checking e i++
char* buscaParametros(char* argv[], int i){
        char* parametro = NULL;

        if(strcmp(argv[i], "-e") == 0){     
            i++; 
            if(argv[i] == NULL){
                return NULL;
            }
            printf("\n\t\t> Diretorio de Entrada: %s", argv[i]);
            parametro = (char*) malloc((strlen(argv[i]) + 1) * sizeof(char)); 
            if(parametro == NULL){
                printf("\nErro inesperado! Memoria insuficiente para alocar o nome do diretorio de entrada.");
                exit(1);
            }
            strcpy(parametro, argv[i]); 
        }

        else if(strcmp(argv[i], "-f") == 0){   
            i++;     
            if(argv[i] == NULL){
                return NULL;
            }
            printf("\n\t\t> Arquivo .geo: %s", argv[i]);
            parametro = (char*) malloc((strlen(argv[i]) + 1) * sizeof(char));
            if(parametro == NULL){
                printf("\nErro inesperado! Memoria insuficiente para alocar o nome do arquivo .geo.");
                exit(1);
            }
            strcpy(parametro, argv[i]);
        }

        else if(strcmp(argv[i], "-q") == 0){       
            i++; 
            if(argv[i] == NULL){
                return NULL;
            }
            printf("\n\t\t> Arquivo .qry: %s", argv[i]);
            parametro = (char*) malloc((strlen(argv[i]) + 1) * sizeof(char));
            if(parametro == NULL){
                printf("\nErro inesperado! Memoria insuficiente para alocar o nome do arquivo .qry.");
                exit(1);
            }
            strcpy(parametro, argv[i]);
        }

        else if(strcmp(argv[i], "-o") == 0){  
            i++;    
            if(argv[i] == NULL){
                return NULL;
            }
            printf("\n\t\t> Diretorio de Saida: %s", argv[i]);
            parametro = (char*) malloc((strlen(argv[i]) + 1) * sizeof(char));
            if(parametro == NULL){
                printf("\nErro inesperado! Memoria insuficiente para alocar o nome do diretorio de saida.");
                exit(1);
            }
            strcpy(parametro, argv[i]);
        }

        else if(strcmp(argv[i], "-ec") == 0){  
            i++;    
            if(argv[i] == NULL){
                return NULL;
            }
            printf("\n\t\t> Arquivo .ec: %s", argv[i]);
            parametro = (char*) malloc((strlen(argv[i]) + 1) * sizeof(char));
            if(parametro == NULL){
                printf("\nErro inesperado! Memoria insuficiente para alocar o nome do diretorio de saida.");
                exit(1);
            }
            strcpy(parametro, argv[i]);
        }

        else if(strcmp(argv[i], "-pm") == 0){  
            i++;    
            if(argv[i] == NULL){
                return NULL;
            }
            printf("\n\t\t> Arquivo .pm: %s", argv[i]);
            parametro = (char*) malloc((strlen(argv[i]) + 1) * sizeof(char));
            if(parametro == NULL){
                printf("\nErro inesperado! Memoria insuficiente para alocar o nome do diretorio de saida.");
                exit(1);
            }
            strcpy(parametro, argv[i]);
        }
        
        else if(strcmp(argv[i], "-v") == 0){
            i++;
            if(argv[i] == NULL){
                return NULL;
            }
            printf("\n\t\t> Arquivo .via: %s", argv[i]);
            parametro = (char*) malloc((strlen(argv[i]) + 1) * sizeof(char));
            if(parametro == NULL){
                printf("\nErro inesperado! Memoria insuficiente para alocar o nome do diretorio de saida.");
                exit(1);
            }
            strcpy(parametro, argv[i]);
        }

        else{
            printf("\nComando siguel inexistente!");
            exit(1);           
        }
    return parametro;
}


void verificaExecucao(char* arqGeo, char* dirSaida){
    if(arqGeo == NULL || dirSaida == NULL){
        printf("\n!Erro! Nao existe -f ou -o. Parâmetros essenciais!");
        exit(1);
    }
}
