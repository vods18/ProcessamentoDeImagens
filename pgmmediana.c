#include "acesso.h"
#include "filtro.h"

int main (){
	pgm *q;
	q=acessa_arquivo();
	
	mediana(q,3);
	
	printf("%s\n", q->tipo); //Insiro tipo no novo arquivo a ser gerado
	printf("%u %u\n", q->lin, q->col); //Insiro linha e coluna maxima no novo arquivo a ser gerado
	printf("%u\n", q->pmax); //Insiro pixel maximo no novo arquivo a ser gerado

	for(int i=0; i<(q->lin); i++){
		printf("\n");
		for(int j=0; j<(q->col); j++)
			printf("%u ", q->m[(i*(q->col))+j]); //Insiro atual imagem tratada no novo arquivo a ser gerado 
		}

	return 0;
}
