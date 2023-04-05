#include "cifrador.h"

#include <wctype.h>

#include "liblista.h"

/**
 * Exclui espaços e quebras de linha em sequência, texto todo em minúsculo. Retorna um stream para o arquivo criado.
 */
FILE *insereChaves(FILE *texto, lchar_t *listaChaves) {
	// pneumoultramicroscopicossilicovulcanoconiótico possui 46 letras (maior palavra do alfabeto)
	char palavra[46 + 1];
	wint_t c;
	FILE *arq;
	int i;
	char *fileName = "ArquivoDeChaves.ascii";

	if(!(arq = fopen(fileName, "w"))) {
		return NULL;
	}

	// lê até encontrar ' ', '\t' ou  '\n'
	for(i = 0; fscanf(texto, "%s", palavra) != EOF; i++) {
		c = palavra[0];
		c = iswupper(c) ? towlower(c) : c;
		printf("%c-", c);

		if(!(setChave(listaChaves, c, i))) {
			return NULL;
		}
		// atualiza o indice
	};
	printf("\n");

	// escreve toda a lista de caracteres no arquivo e no stdout
	lchar_imprime(arq, listaChaves);

	fclose(arq);

	return fopen(fileName, "r");
}

FILE *cifrador(FILE *livroCifra) {
	FILE *arqChaves;
	lchar_t *listaChar;

	/* Cria a lista necessária para guardar as chaves */
	if(!(listaChar = lchar_cria())) {
		fprintf(stderr, "ERRO: %s", "Falha ao criar lista de chaves.\n");
		exit(1);
	}

	/*Recebe a lista e cria o arquivo de chaves, caso ocorra imprevista realiza o devido tratamento do erro*/
	printf("Lista: \n");
	if(!(arqChaves = insereChaves(livroCifra, listaChar))) {
		fprintf(stderr, "ERRO: %s \"%s\": %s\n", "Nao foi possivel abrir/criar o arquivo", "ArquivoDeChaves.ascii", strerror(errno));
		exit(1);
	}

	lchar_destroi(listaChar);
	fclose(arqChaves);
	return arqChaves;
}