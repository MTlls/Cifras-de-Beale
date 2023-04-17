

CFLAGS = -std=c99 -Wall -g
 
objs = beale.o cifrador.o libListaChar.o libRedBlack.o libErro.o libLista.o args.o
 
# regra default (primeira regra)
all: beale
 
# regras de ligacao
beale: $(objs)
 
# regras de compilação

# objeto principal
beale.o: beale.c args.o cifrador.o libErro.o

# objeto responsavel pelo controle das cifras
cifrador.o: cifrador.c cifrador.h libListaChar.o libRedBlack.o

# objeto responsavel pelas listas de caracteres
libListachar.o: libListaChar.c libListaChar.h libLista.o

# objeto responsavel pela arvore red black
libRedBlack.o: libRedBlack.c libRedBlack.h

# objeto responsavel pela biblioteca de erros
libErro.o: libErro.c libErro.h

# objeto responsavel pelas listas para cada caractere
libLista.o: libLista.c libLista.h

# objeto responsavel pelo tratamento dos argumentos
args.o: args.c args.h libErro.o

# remove arquivos temporários
clean:
	@echo "Limpando..."
	-rm -f  *~ $(objs) beale
 
# remove tudo o que não for o código-fonte
purge: clean
	@echo "Limpando tudo que não seja código-fonte..."
	-rm -f beale *.[^c,h]*
