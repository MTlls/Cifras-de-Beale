CFLAGS = -std=c99 -Wall -g
 
objs = cifrador.o structs.o beale.o
 
# regra default (primeira regra)
all: beale
 
# regras de ligacao
beale: $(objs)
 
# regras de compilação
beale.o: beale.c cifrador.h structs.c libLCifra.h
cifrador.o: cifrador.c cifrador.h structs.c libLCifra.h
libLCifra.h: libLista.h
structs.o: structs.c libLCifra.h
 
# remove arquivos temporários
clean:
	-rm -f $(objs) *~  
 
# remove tudo o que não for o código-fonte
purge: clean
	-rm -f beale *.ascii *.txt
