#include <stdio.h>
#include <stdlib.h>
#include "filtro.h"


/* Nesse arquivo mantenho minhas funcoes de tratamento de imagem */

//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void negativa(FILE *arc, pgm *img, char *output){ //Poe o filtro negativo na imagem
	
	for(int i=0; i<(img->lin); i++) //Lido com a matriz apenas depois do cabecalho pra fazer a troca de pixel adequada
		for(int j=0; j<(img->col); j++){
			img->m[i][j]= (img->pmax) - img->m[i][j]; //Faco a diferença entre os elementos da matriz e o maior pixel
		}
	

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
/*Funcoes para rotacao*/





