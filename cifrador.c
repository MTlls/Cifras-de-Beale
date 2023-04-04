#include "cifrador.h"

#include <wctype.h>

#include "liblista.h"

void insereChaves(FILE *livroCifra, lchar_t *listaChaves) {
	wint_t c;
	int i = 0;

	/**
	 * É inserido a primeira chave com o índice i
	 */
	c = fgetwc(livroCifra);
	setChave(listaChaves, c, i);

	while(c != WEOF) {
		/**
		 * Caso seja um espaço ou \n é pego o proximo caractere e inserido na lista de chaves
		 * */
		if(c == ' ' || c == '\n') {
			/*É pego o próximo caracetere depois de ' ' ou '\n'*/
			c = fgetwc(livroCifra);

			/* Caso haja espaço no final do arquivo (não queremos um espaço nas chaves que iremos encriptografar) */
			if(c == WEOF) {
				return;
			} else if(!setChave(listaChaves, c, ++i)) {  // Se ocorrer erro
				fprintf(stderr, "ERRO: %s \"%c\": %s\n", "Nao foi possivel atualizar os indices do caractere ", c, strerror(errno));
				exit(1);
			}
		}
		c = fgetwc(livroCifra);
	}
}

/**
 * Exclui espaços e quebras de linha em sequência, texto todo em minúsculo. Retorna um stream para o arquivo criado.
 */
FILE *normalizaTexto(FILE *texto) {
	wint_t c;
	FILE *arq;
	char *fileName = "formatado.ascii";

	if(!(arq = fopen(fileName, "w"))) {
		fprintf(stderr, "ERRO: %s \"%s\": %s\n", "Nao foi possivel abrir/criar o arquivo", fileName, strerror(errno));
		exit(1);
	}

	c = fgetwc(texto);

	while(c != WEOF) {
		// se for ' ' ou \n
		if(iswspace(c)) {
			fputwc(c, arq);
			c = fgetwc(texto);
			// enquanto houverem espaços ou quebras de linhas em sequencia, avança-se o cursor, cobrindo o caso no qual há linhas extras no final do arquivo
			while(iswspace(c)) {
				c = fgetwc(texto);
			}
			// tramamento caso o espaço seja seguido do fim do arquivo
			if(c == WEOF) {
				fclose(arq);
				return fopen(fileName, "r");
			}
		}

		/* Se o caractere for maísculo, colocamos como minúsculo*/
		if(iswupper(c)) {
			c = towlower(c);
		}

		fputwc(c, arq);
		c = fgetwc(texto);
	}
	fclose(arq);

	rewind(texto);

	return fopen(fileName, "r");
}

/**
 * Retira os acentos do texto.
 */
void retiraAcento(FILE *texto) {
	wchar_t *comAcentos = L"ÄÅÁÂÀÃäáâàãÉÊËÈéêëèÍÎÏÌíîïìÖÓÔÒÕöóôòõÜÚÛüúûùÇç";
	char semAcentos[] = "AAAAAAaaaaaEEEEeeeeIIIIiiiiOOOOOoooooUUUuuuuCc";
	wint_t c;
	int i;

	printf("ftell: %ld\n", ftell(texto));
	fseek(texto, -sizeof(L'\0'), SEEK_END);
	c = fgetwc(texto);

	// mbtowc(&c, fgetc(texto), sizeof(wint_t));
	if(!(c)) {
		fprintf(stderr, "ERRO: %s: %s\n", "Nao foi possivel ler o caractere do arquivo", strerror(errno));
		exit(1);
	}

	while(c != EOF) {
		for(i = 0; i < wcslen(comAcentos); i++) {
			if(c == comAcentos[i]) {
				c = semAcentos[i];
				/* é preciso sair do loop pois será feito a mesma verificação com o proximo caractere*/
				i = wcslen(comAcentos);
			}
		}
		fputwc(c, texto);
		fseek(texto, -sizeof(c), SEEK_CUR);
		c = getwc(texto);
	}

	rewind(texto);
}

FILE *cifrador(FILE *livroCifra) {
	FILE *arqChaves, *flivroCifra;
	lchar_t *listaChar;

	if(!(arqChaves = fopen("ArquivoDeChaves.txt", "w"))) {
		fprintf(stderr, "ERRO: %s \"%s\": %s\n", "Nao foi possivel abrir/criar o arquivo", "ArquivoDeChaves.txt", strerror(errno));
		exit(1);
	}

	if(!(listaChar = lchar_cria())) {
		fprintf(stderr, "ERRO: %s", "Falha ao criar lista de chaves.\n");
		exit(1);
	}

	flivroCifra = normalizaTexto(livroCifra);
	insereChaves(flivroCifra, listaChar);
	printf("Lista: \n");
	lchar_imprime(listaChar);
	printf("------------------------------------------\n");
	lchar_destroi(listaChar);
	fclose(arqChaves);
	fclose(flivroCifra);
	return arqChaves;
}
