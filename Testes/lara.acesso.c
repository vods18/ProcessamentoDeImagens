#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "struct.h"

/* Função para alocar a matriz para o tipo P2
    Esse jeito facilita o uso da função fread */
unsigned int* aloca_matriz (FILE *arq, imgPGM *imagem){
    unsigned int *mataux ;
    int i, j ;
 
    // aloca um vetor com todos os elementos da matriz
    mataux = malloc (imagem->altura * imagem->largura * sizeof (int)) ;
 
    // percorre a matriz
    for (i=0; i < imagem->altura; i++){
          for (j=0; j < imagem->largura; j++){
            mataux[(i*imagem->largura) + j] = 0 ; // calcula a posição de cada elemento
          }
    }
    //teste
    //printf("estou alocado\n");
    return mataux;   
}

//teste
void imprime(imgPGM *imagem) {
    for(int i=0; i< (imagem->altura); i++){
        for(int j=0; j< (imagem->largura); j++){
            printf("%d ", imagem->matriz[(i*imagem->largura) + j]);
        }
        //printf("\n");
    }
}

unsigned int* recebe_arquivo_P2(FILE* arq, imgPGM *imagem) {
    int i, j;
    for (i=0; i < imagem->altura; i++){
        for (j=0; j < imagem->largura; j++){
            fscanf(arq,"%d", &imagem->matriz[(i*imagem->largura) + j]);
        }
    }
    //printf("arquivo recebido P2 \n");
    fclose(arq);
    return imagem->matriz;
}

unsigned int* recebe_arquivo_P5(FILE *arq, imgPGM *imagem) {
    fread(imagem->matriz, sizeof(unsigned int), (imagem->altura * imagem->largura), arq);

    //printf("arquivo recebido P5 \n");
    fclose(arq);
    return imagem->matriz;
}

/*Função para abrir o arqivo e encerrar caso incompativel */

imgPGM* ler_arquivo(){
    imgPGM *imagem = (imgPGM *) malloc (sizeof(imgPGM));
    FILE* arq = fopen ("lena.pgm", "r+") ;

    if (!arq){
        return NULL;
    }

    fscanf(arq, "%s", imagem->tipo);
    fscanf(arq, "%u %u", &imagem->altura, &imagem->largura);
    fscanf(arq, "%hhu", &imagem->densidade);

    //teste
    printf("%s\n", imagem->tipo);
    printf("%u %u \n", imagem->altura, imagem->largura);
    printf("%hhu\n", imagem->densidade);

    if (strcmp (imagem->tipo, "P5") == 0){    //Caso seja do tipo P5
        //ler matriz como binario
        //aloca a matriz binaria e seta matriz ascii = Null
        imagem->matriz= aloca_matriz(arq, imagem);
        imagem->matriz= recebe_arquivo_P5(arq, imagem);
        imprime(imagem);
    }
    // Caso seja do tipo P2
    else{
        //ler matriz como ascii
        //aloca a matriz ascii e seta matriz binario = Null
        imagem->matriz= aloca_matriz(arq, imagem);
        imagem->matriz= recebe_arquivo_P2(arq, imagem);
        //matriz= recebe_arquivo_P5(arq, imagem, matriz);
    }

    return imagem;
}

