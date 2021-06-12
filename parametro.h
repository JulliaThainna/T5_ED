#ifndef PARAMETROS__H_
#define PARAMETROS__H_

/*
Lê os argumentos passados pelo usuário no siguel e os guarda em variáveis
Pré: char *argv[] - argumentos lidos pelo terminal (ja e um parametro proprio da main na linguagem C)
            int i - contador i do comando de repeticao 'for' na main que acaba quando todos os argumentos 
            do terminal foram lidos
Pós: Retorna um char* referente ao nome do parâmetro inserido
*/
char *buscaParametros(char* argv[], int i);

/*
Verifica se os parâmetros essenciais foram inseridos pelo usuário
Pré: arqGeo - Nome do arquivo GEO (referente ao comando -f no siguel)
     dirSaida - Caminho onde serão gerados os arquivos de saída (referente ao comando -o no siguel)
*/
void verificaExecucao(char* arqGeo, char* dirSaida);

#endif
