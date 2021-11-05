#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "acesso.h"


void confere (FILE *arq) {
	if(!arq) {  //Avisa e interrompe execucao caso o arquivo nao seja lido corretamente
		printf("Erro ao acessar o arquivo\n");
		abort();
	}
}

void comentario(FILE *arq){
	
	char *coment = malloc(256 * sizeof(char));	
	fgets(coment, 256, arq); //leio posicao atual de arq pra conferir se eh comentario 
	//caso tenha eu pulo ele de acordo com o tamanho dele
	if(coment[0] == '#'){ 
		fseek(arq, strlen(coment), SEEK_CUR);
	}
	else
		fseek(arq, -strlen(coment), SEEK_CUR);

}

void le_cabecalho (FILE *arq, pgm *img){

	comentario(arq); //essa funcao ira conferir se a posicao atual do ponterio eh comentario	
	fscanf(arq, "P%i",&img->tipo); //Leio o tipo

	comentario(arq);	
	fscanf(arq, "%i %i", &img->col, &img->lin); //Leio largura e altura
	
	comentario(arq);	
	fscanf(arq, "%i", &img->pmax); //Leio o maior pixel
	
	comentario(arq);

}

void aloca_p2 (FILE *arq, pgm *img){	

	//agora percorro a imagem
	for(int i=0; i<(img->lin); i++){ 
		for(int j=0; j<(img->col); j++){
			fscanf(arq, "%hhu", &img->m[i][j]); //Leio cada elemento da matriz de inteiros seguindo a logica da alocacao dinamica tipo 2
		}
	}
}

void aloca_p5 (FILE *arq, pgm *img){

	for(int i=0; i<(img->lin); i++) {
		fread(img->m[i], sizeof(unsigned char), img->col, arq);
	}
}

void acessa_arquivo (char *input, char *output, int op, int ang){ 
	
	FILE *arq; //Declaro arq para ser meu ponteiro do arquivo
	pgm *img; //Declaro img para ser meu ponteiro que irá apontar pros valores da minha estrutura pgm
	
	img=malloc(sizeof(pgm)); //Faco a alocacao para a imagem
	arq=fopen(input, "r+"); //Abro arquivo

	confere(arq); //Confere se a leitura do arquivo acontece como esperado	
	le_cabecalho(arq, img); //Leio os valores do cabecalho

	
	FILE *arc = fopen(output, "w+");

	/*Cabecalho*/
	fprintf(arc, "P%i\n", img->tipo); //Insiro tipo no novo arquivo a ser gerado
	fprintf(arc, "%i %i\n", img->col, img->lin); //Insiro linha e coluna maxima no novo arquivo a ser gerado
	fprintf(arc, "%i \n", img->pmax); //Insiro pixel maximo no novo arquivo a ser gerado

		
	//aloca um vetor de lin ponteiros para linhas do tipo int
	img->m = calloc(img->lin, sizeof (unsigned char*));

	//aloca a cada uma das linhas um vetor de col colunas do tipo int
	for(int i=0; i<(img->lin); i++) {
		img->m[i] = calloc(img->col, sizeof (unsigned char));
	}

	if(img->tipo == 2) 	// Eh p2 ou p5?
		aloca_p2(arq, img);
	else
		aloca_p5(arq, img);
	
	
	fclose(arq);
		
	switch(op) {
		
		case 1:
			negativa(arc, img, output);

		//case'2':
			//rotacao(img, ang, output);
	}

}
