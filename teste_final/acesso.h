//GRR20182592
//VINICIUS OLIVEIRA DOS SANTOS

#ifndef __ACESSO__
#define __ACESSO__

#include <stdio.h>
#include "filtro.h"

void acessa_arquivo (char *input, char *output, int op, float ang);

void confere(FILE *arq);

void comentario(FILE *arq);

void le_cabecalho(FILE *arq, pgm *p);

void le_p2(FILE *arq, pgm *p);

void le_p5(FILE *arq, pgm *p);

#endif
