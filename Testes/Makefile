CC=gcc
CFLAGS= -g -Wall
OBJ = tratamento.o acesso.o filtro.o pgmnega.o  

negativa = pgmnega.o filtro.o acesso.o tratamento.o

rotacao = pgmrotacao.o filtro.o acesso.o tratamento.o

lbp = pgmlbp.o filtro.o acesso.o tratamento.o

%.o: %.c
	$(CC) -c -o $@ $< $(CFLAGS) 

all: pgmnega pgmrotacao pgmlbp

pgmnega: $(negativa)

	$(CC) -o $@ $^ $(CFLAGS) 

pgmrotacao: $(rotacao)
	
	$(CC) -o $@ $^ $(CFLAGS)

pgmlbp: $(lbp)

	$(CC) -o $@ $^ $(CFLAGS)

.PHONY:	clean

clean: 

	rm *.o 

purge: 

	rm pgmnega pgmrotacao pgmlbp
