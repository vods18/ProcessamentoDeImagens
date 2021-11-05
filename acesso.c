//GRR20182592
//VINICIUS OLIVEIRA DOS SANTOS

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
	
	char lixo [500]; //reservo no maximo 500 caracteres para essa linha de comentario
	while (fgetc(arq) == '#') { //se for comentario
		fseek(arq, -(sizeof(char)), SEEK_CUR); //volto um pq ja li o #
		fgets(lixo, sizeof(lixo), arq); //vou o tamanho da string pra frente
	}
	
	fseek(arq, -(sizeof(char)), SEEK_CUR); //volto um por ja ter lido o #
}

void le_cabecalho (FILE *arq, pgm *img){

	comentario(arq); //essa funcao ira conferir se a posicao atual do ponterio eh comentario	
	fscanf(arq, "P%i\n",&img->tipo); //Leio o tipo

	comentario(arq);	
	fscanf(arq, "%i %i\n", &img->col, &img->lin); //Leio largura e altura
	
	comentario(arq);	
	fscanf(arq, "%i\n", &img->pmax); //Leio o maior pixel

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

void acessa_arquivo (char *input, char *output, int op, float ang){ 
	
	FILE *arq; //Declaro arq para ser meu ponteiro do arquivo
	pgm *img; //Declaro img para ser meu ponteiro que irá apontar pros valores da minha estrutura pgm
	
	img=malloc(sizeof(pgm)); //Faco a alocacao para a imagem

	if (input == NULL)
		arq = stdin; //caso nao tenha sido passado um nome, pegue da entrada padrao
	else
		arq = fopen(input, "r+"); //Abro arquivo

	confere(arq); //Confere se a leitura do arquivo acontece como esperado	
	le_cabecalho(arq, img); //Leio os valores do cabecalho
		
	//aloca um vetor de lin ponteiros para linhas do tipo unsigned char 
	img->m = calloc(img->lin, sizeof (unsigned char*));

	//aloca a cada uma das linhas um vetor de col colunas do tipo unsigned char
	for(int i=0; i<(img->lin); i++) {
		img->m[i] = calloc(img->col, sizeof (unsigned char));
	}

	if(img->tipo == 2) 	// Eh p2 ou p5?
		aloca_p2(arq, img);
	else
		aloca_p5(arq, img);
	
	
	fclose(arq);
	
	if( op == 1) {
			negativa(img, output); //operacao negativa pedida
	}

	else if (op == 2) {

			rotacao(img, ang, output); //operacao rotacao pedida
	}
	else {

			lbp(img, output); //operacao lbp pedida
	}
}
