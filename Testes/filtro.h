#ifndef __F_AUX__
#define __F_AUX__
#include "estrutura.h"

//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

int vizinhos(int M);

int cmpfunc (const void *a, const void *b);

void seleciona_vizinhos(unsigned *vz, int aux1, int aux2, pgm *img, int M, int n, int disi, int disj);

int med_vizinhos(int aux1, int aux2, pgm *img, int M, int disi, int disj);

void negativa(FILE *arc, pgm *img, char *output);

void rotacao(pgm *img, int ang);

pgm* mediana(pgm *img, int M);

#endif
