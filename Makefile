CFLAGS = -std=c99 -Wall -g
 
objs = beale.o cifrador.o libErro.o libListaChar.o libRedBlack.o libLista.o args.o
 
# regra default (primeira regra)
all: beale
 
# regras de ligacao
beale: $(objs)
 
# regras de compilação
beale.o: beale.c cifrador.o libErro.o
cifrador.o: cifrador.c cifrador.h libListaChar.o libRedBlack.o
libListachar.o: libListaChar.c libListaChar.h libLista.o
libRedBlack.o: libRedBlack.c libRedBlack.h
libErro.o: libErro.c libErro.h
libLista.o: libLista.c libLista.h
args.o: args.c args.h

# remove arquivos temporários
clean:
	-rm -f  *~ $(objs) beale
 
# remove tudo o que não for o código-fonte
purge: clean
	-rm -f beale *.ascii *.txt
