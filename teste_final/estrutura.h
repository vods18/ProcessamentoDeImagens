//GRR20182592
//VINICIUS OLIVEIRA DOS SANTOS

#ifndef __ESTRUTURA__
#define __ESTRUTURA__


typedef struct estrutura_pgm {  //Declaro uma base estrutural pra lidar com o cabecalho da matriz de forma mais intuitiva
	int tipo; //Tipo da imagem (2 ou 5)
	int lin, col; //Altura e largura da imagem 
	int pmax; //Maior pixel
	unsigned char **m; //Imagem 
}pgm;

#endif
