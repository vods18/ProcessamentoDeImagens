//GRR20182592
//VINICIUS OLIVEIRA DOS SANTOS

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "filtro.h"

#define pi 3.1415926
#define rad(a) ((a*pi)/180)


/* Nesse arquivo mantenho minhas funcoes de tratamento de imagem */

void imprime (pgm* img, char *output){

	FILE *arc;
	
	if (output == NULL)
		arc = stdout;
	
	else
		arc = fopen(output, "w+");

	/*Cabecalho*/
	
	fprintf(arc, "P%i\n", img->tipo); //Insiro tipo no novo arquivo a ser gerado
	
	fprintf(arc, "%i %i\n", img->col, img->lin); //Insiro linha e coluna maxima no novo arquivo a ser gerado
	
	fprintf(arc, "%i \n", img->pmax); //Insiro pixel maximo no novo arquivo a ser gerado

	if(img->tipo == 2) 	// Eh p2 ou p5?
		
		/*Imagem*/
		for(int i=0; i<(img->lin); i++){
			for(int j=0; j<(img->col); j++) {
				fprintf(arc, "%hhu ", img->m[i][j]); //Insiro atual imagem negativa no novo arquivo a ser gerado
			}
			fprintf(arc, "\n");			
		}
	
	else
		for(int i=0; i<(img->lin); i++) {
			fwrite(img->m[i], sizeof(unsigned char), img->col, arc);
			
	}
	
	fclose(arc);
}

//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void negativa(pgm *img, char *output){ //Poe o filtro negativo na imagem
	
	for(int i=0; i<(img->lin); i++) //Lido com a matriz apenas depois do cabecalho pra fazer a troca de pixel adequada
		for(int j=0; j<(img->col); j++){
			img->m[i][j]= (img->pmax) - img->m[i][j]; //Faco a diferença entre os elementos da matriz e o maior pixel
		}

	imprime(img, output);	

} 

//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
/*Funcoes para rotacao*/

int comparador(const void *a, const void *b) {
	/*Logica utilizada para funcionamento do quick sort*/

	int *pa, *pb;

	pa = (int*)a;
	pb = (int*)b;

	if (*pa > *pb) return 1;  
	if (*pa > *pb) return -1;
	return 0;
}

void dimensao_resultante(pgm *img, float ang, int dim[], int desc[]) {
	int pontosi[4]; //vetor com as coordenadas i dos pontos extremos da imagem resultante
	int pontosj[4]; //vetor com as coordenadas j dos pontos extremos da imagem resultante

	pontosi[0]=0; pontosj[0]=0; //ponto 1
	
	pontosi[1]= ceil((0*cos(ang)) - (img->col*sin(ang))); 
	pontosj[1]= ceil((0*sin(ang)) + (img->col*cos(ang))); //ponto 2

	pontosi[2] = ceil((img->lin*cos(ang)) - (0*sin(ang))); 
	pontosj[2] = ceil((img->lin*sin(ang)) + (0*cos(ang))); //ponto 3	
	
	pontosi[3] = ceil((img->lin*cos(ang)) - (img->col*sin(ang))); 
	pontosj[3] = ceil((img->lin*sin(ang)) + (img->col*cos(ang))); //ponto 4

	qsort(pontosi, sizeof(int), 4, comparador); //ordeno o vetor com os valores
	qsort(pontosj, sizeof(int), 4, comparador);
	
	dim[0] = pontosi[3] - pontosi[0]; //a distancia entre o menor ponto e o maior ponto extremo das coordenadas i sera a dimensao i da resultante
	dim[1] = pontosj[3] - pontosj[0]; //a distancia entre o menor ponto e o maior ponto extremo das coordenadas j sera a dimensao j da resultante

	desc[0] = pontosi[0]; //o valor de deslocamento i da imagem no plano cartesiano se da pelo menor ponto i
	desc[1] = pontosj[0]; //o valor de deslocamento j da imagem no plano cartesiano se da pelo menor ponto j
	
}

void aloca_matriz(pgm *out, pgm *img) {

	//aloca um vetor de lin ponteiros para linhas do tipo unsigned char 
	out->m = malloc(out->lin * sizeof (unsigned char*));

	//aloca a cada uma das linhas um vetor de col colunas do tipo unsigned char
	for(int i=0; i<(out->lin); i++) 
		out->m[i] = malloc(out->col * sizeof (unsigned char));
	
}

void fundo_branco(pgm *out) {

	//preencho a imagem com pixel maximos para por o fundo branco
	for(int i=0; i<(out->lin); i++)
			for(int j=0; j<(out->col); j++) 
				out->m[i][j] = out->pmax;
}

void calcula_posicoes(pgm *img, pgm *out, float ang, int desc[]){
	
	int k,l; //indices resultantes
	
	for(int i=0; i<(img->lin); i++){
			for(int j=0; j<(img->col); j++){ 
				k = (i*cos(ang)) - (j*sin(ang)) - desc[0]; //calculo indice k
				l = (i*sin(ang)) + (j*cos(ang)) - desc[1]; //calculo indice l
				out->m[k][l] = img->m[i][j]; //ponho na posicao resultante as coordenadas
			}
	}
}				

void rotacao(pgm *img, float ang, char *output){

	pgm *out;  //pgm resultante
	out = malloc(sizeof(pgm)); //aloco o espaço geral
	out->tipo = img->tipo; //pego o tipo
	out->pmax = img->pmax; //pego o pixel maximo

	if ( ang < 0 )
		ang = ang + 360;

	ang = rad(ang); //calculo do radiano

	int desc[2];

	int dim[2]; //vetor com os valores da dimensao da imagem resultante
	dimensao_resultante(img, ang, dim, desc);
	
	out->lin = dim[0]; //recebe linha maxima
	out->col = dim[1]; //recebe coluna maxima
	
	aloca_matriz(out, img); //aloco a partir dos indices maximos recebidos
	fundo_branco(out); //ponho o fundo branco que resultara a partir da rotacao

	calcula_posicoes(img, out, ang, desc); //calculo todas as posicoes resultante

	imprime(out, output);

}


//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
/*Funcoes para lpb*/
void preenche_aux(unsigned char **m, unsigned char *aux, int k, int l){
	int x=0;
	for(int i=k; i<k+3; i++)
		for(int j=l; j<l+3; j++){
			aux[x] = m[i][j]; //vetor vai recebendo valores da matriz original para fazer as continha
			x++;
		}
}

void intensidade(unsigned char *aux){
	for(int i=0; i<9; i++){ 
		if (i != 4) { //se nao for o valor central
			if(aux[i] >= aux[4]) //comparo com valor central 		
				aux[i] = 1; 
			else 
				aux[i] = 0; 
		}
	}
}

void multmasc(unsigned char *aux, unsigned char *masc){
	int x=0;	
	unsigned char LBP=0; //variavel correspondente a soma dos vizinhos alterados	
	for(int i=0; i<9; i++){ //k e l sao o ponto de partida da vizinhança atual
		if (i != 4){ //se nao for o valor central
			aux[i] = aux[i] * masc[x];
			LBP = aux[i] + LBP;
			x++;
		}
	}
	aux[4] = LBP; //valor central recebe a soma
}

void lbp(pgm *img, char *output) {

	unsigned char masc[8] = {1,2,4,8,16,32,64,128}; //valores de mascara
	unsigned char aux[9]; //vetor auxiliar que carregara vizinhança atual da imagem
	pgm *out;  //pgm auxiliar para nao alterar a original
	
	out = malloc(sizeof(pgm));
 
	//out recebe valores da imagem original
	out->tipo = img->tipo; 
	out->lin = img->lin;
	out->col = img->col;
	out->pmax = img->pmax;

	//aloca um vetor de lin ponteiros para linhas do tipo unsigned char
	out->m = calloc(out->lin, sizeof (unsigned char*));

	//aloca a cada uma das linhas um vetor de col colunas do tipo unsigned char
	for(int i=0; i<(out->lin); i++) {
		out->m[i] = calloc(out->col, sizeof (unsigned char));
	}


	for(int i=0; i<img->lin; i++)
		for(int j=0; j<img->col; j++)
			out->m[i][j] = img->m[i][j]; //ponho na matriz de saida os valores da original

	for(int i=0; i<img->lin-2; i++){
		for(int j=0; j<img->col-2; j++){
			preenche_aux(img->m, aux, i, j); //vetor auxiliar recebe vizinhança atual da imagem
			intensidade(aux); //comparo a intensidade dos vizinhos com o valor central
			multmasc(aux, masc); // multiplico os valores da mascara com os vizinhos		
			out->m[i+1][j+1] = aux[4]; // atualizo valor central		
		}
	}
	
	imprime(out, output); //imprimo a matriz resultante
}
