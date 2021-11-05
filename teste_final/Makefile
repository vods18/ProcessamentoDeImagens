CC=gcc

#flags de compilacao
CFLAGS= -g -Wall -lm 

#arquivos-objeto
OBJ = tratamento.o acesso.o filtro.o pgmnega.o  

#regras de compilacao
negativa = pgmnega.o filtro.o acesso.o tratamento.o

rotacao = pgmrotacao.o filtro.o acesso.o tratamento.o

lbp = pgmlbp.o filtro.o acesso.o tratamento.o

%.o: %.c
	$(CC) -c -o $@ $< $(CFLAGS) 

#regra default
all: pgmnega pgmrotacao pgmlbp

#regras de ligacao
pgmnega: $(negativa)

	$(CC) -o $@ $^ $(CFLAGS) 

pgmrotacao: $(rotacao)
	
	$(CC) -o $@ $^ $(CFLAGS)

pgmlbp: $(lbp)

	$(CC) -o $@ $^ $(CFLAGS)

.PHONY:	clean

#remove arquivos temporarios
clean: 

	rm *.o 
#remove tudo o que nao for condifo-fonte original
purge: 

	rm pgmnega pgmrotacao pgmlbp
