//GRR20182592
//VINICIUS OLIVEIRA DOS SANTOS

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "tratamento.h"

#define MAX_NOME 30

void tratamento(int argc, char **argv, int op) {
	
	char *input; //nome da imagem input
	input=malloc(MAX_NOME * sizeof(char)); // reservo espaço para um nome de ate 30 letras
	input = NULL;

	char *output; //nome da imagem output
	output=malloc(MAX_NOME * sizeof(char)); // reservo espaço para um nome de ate 30 letras
	output = NULL;

	int option;
	float ang=90.0;

	while ((option = getopt (argc, argv, "a:i:o:")) != -1) {		

			switch(option) { 
				
				case 'a':
					
					ang = atof(optarg); //converto o valor de optarg para integer e pego o angulo 		
				
				break;
				
				case 'i': 
					
					input = optarg; //pego o nome da imagem para leitura

				break;
	
				case 'o':

					output = optarg; //pego o nome da imagem para escrita

				break;
			}
	}
 
	acessa_arquivo(input, output, op, ang);
}	
