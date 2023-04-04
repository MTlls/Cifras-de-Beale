CFLAGS = -std=c99 -Wall -g
 
objs = cifrador.o liblista.o beale.o
 
# regra default (primeira regra)
all: beale
 
# regras de ligacao
beale: $(objs)
 
# regras de compilação
beale.o: cifrador.h
cifrador.o: cifrador.c liblista.h cifrador.h
cifrador.h: liblista.h
liblista.o: liblista.c liblista.h
 
# remove arquivos temporários
clean:
	-rm -f $(objs) *~  
 
# remove tudo o que não for o código-fonte
purge: clean
	-rm -f beale *.ascii *.txt
