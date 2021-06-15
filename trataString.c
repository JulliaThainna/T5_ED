#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "trataString.h"



void concatenaCaminhos(char e[], char f[], char** result){
    //printf("\ne[] -> %s\n", e);
    //printf("\nf[] -> %s\n", f);

    int tamanhoString = (e == NULL) ? (strlen(f) + 1) : (strlen(e) + strlen(f) + 1);
    if(e == NULL){
        *result = malloc(tamanhoString);
        strcpy(*result, f);
        return;
    }

    int tamE = strlen(e);
    int tamF = strlen(f);

    if(e[tamE - 1] != '/' && (f[0] != '/' && f[0] != '.')){
        tamanhoString++;
        *result = malloc(tamanhoString);
        strcpy(*result, e);
        strcat(*result, "/");
        strcat(*result, f);
    }
    else if((e[tamE - 1] == '/' && (f[0] != '/' && f[0] != '.')) || (e[tamE - 1] != '/' && f[0] == '/')){
        *result = malloc(tamanhoString);
        strcpy(*result, e);
        strcat(*result, f);
    }
    else if(e[tamE - 1] == '/' && f[0] == '/'){
        tamanhoString--;
        *result = malloc(tamanhoString);
        strcpy(*result, e);
        strncat(*result, f + 1, tamF -1);
    }
    else if(e[tamE - 1] == '/' && f[0] == '.'){
        tamanhoString -= 2;
        *result = malloc(tamanhoString);
        strcpy(*result, e);
        strncat(*result, f + 2, tamF -1);
    }
    else{
        printf("\nERRO! O formato que você inseriu no parâmetro -f e -e não se encaixam no contexto.\n Verifique o caminho que você inseriu!\n");
        exit(1);
    }
}


void getNomeConcatExtension(char f[], char ext[], char** result){
    //printf("\nRetirando o nome do arquivo da sentença: \"%s\"\n", f);
    //printf("Concatenando o nome do arquivo com: \"%s\"\n", ext);
    char* aux = NULL;
    int tamF = strlen(f);
    //Encontra pos do último / no f
    if(f[0] == '.'){
        aux = strtok(f + 1, ".");
    }
    aux = strtok(f, ".");
    bool temBarra = false;
    for(int i = 0; i < (tamF - 1); i++){
        if(f[i] == '/'){
            temBarra = true;
        }
    }
    if(temBarra){
        aux = strrchr(f, '/') + 1;
    }
    *result = malloc(strlen(aux) + strlen(ext) + 1);
    strcpy(*result, aux);
    strcat(*result, ext);
}

void extraiNome(char f[], char** result){
    //printf("\nRetirando o nome do arquivo da sentença: \"%s\"\n", f);
    char* aux = NULL;
    int tamF = strlen(f);
    //Encontra pos do último / no f
    if(f[0] == '.'){
        aux = strtok(f + 1, ".");
    }
    aux = strtok(f, ".");
    bool temBarra = false;
    for(int i = 0; i < (tamF - 1); i++){
        if(f[i] == '/'){
            temBarra = true;
        }
    }
    if(temBarra){
        aux = strrchr(f, '/') + 1;
    }
    //printf("\n%s\n", aux);
    *result = malloc(strlen(aux) +  1);
    strcpy(*result, aux);
}

void concatenaNomeGeoQry(char geo[], char qry[], char ext[], char** result){
    int tamanho = strlen(geo) + strlen(qry) + strlen(ext);
    *result = malloc(tamanho + 2);
    strcpy(*result, geo);
    strcat(*result, "-");
    strcat(*result, qry);
    strcat(*result, ext);
}
