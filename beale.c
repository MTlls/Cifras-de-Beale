#include <getopt.h>
#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "cifrador.h"

int main(int argc, char **argv) {
	int option;
	FILE *livroCifra;
	int e = 0, d = 0;
	char *m = 0;
	char *b = 0;
	char *i = 0;

	opterr = 0;

	setlocale(LC_CTYPE, "");
	// Verifica se há mais de 1 argumento
	if(argc == 1) {
		fprintf(stderr, "ERRO: %s", "é necessário mais argumentos.\n");
		exit(1);
	}

	/*
	 * NOTA: necessario revisar as opções e suas saídas. 
	*/
	while((option = getopt(argc, argv, "edb:m:i:")) != -1) {
		switch(option) {
		// encode flag
		case 'e':
			e = 1;
			break;
		// decode flag
		case 'd':
			d = 1;
			break;
		/*
			NOTA: Se as opções "-m" ou "-b" ou "-i" estiverem sem argumentos
			forçamos a descida dos cases até o caso '?'.
		*/
		// -m recebe a mensagem não codificada
		case 'm':
			if(strncmp(optarg, "-", 1) != 0) {
				m = malloc(sizeof((char *)optarg) + 1);
				m = strcpy(m, optarg);

				break;
			}

		// -b recebe o LivroCifra
		case 'b':
			if(strncmp(optarg, "-", 1) != 0) {
				if(!(livroCifra = fopen(strcat(optarg, ".ascii"), "r"))) {
					fprintf(stderr, "ERRO: %s \"%s\": %s\n", "Nao foi possivel abrir/criar o arquivo", optarg, strerror(errno));
					exit(1);
				}

				b = malloc(sizeof((char *)optarg)+6);
				b = strcpy(b, optarg);
				cifrador(livroCifra);
				fclose(livroCifra);
				break;
			}
		// -i recebe a mensagem codificada
		case 'i':
			if(strncmp(optarg, "-", 1) != 0) {
				i = malloc(sizeof((char *)optarg) + 1);
				i = strcpy(i, optarg);
				break;
			}
		// Argumento inválido
		/*
			MELHORIA: necessário desenvolver uma verificação se
			encontramos um caractere diferente de "-e-d-b-m"
		*/
		case '?':
			fprintf(stderr, "ERRO: %s: -%c\n", "Necessário um argumento para a opção", option == '?' ? optopt : option);
			exit(1);
			break;
		}
	}

	// print dos argumentos
	printf("Resultado dos argumentos:\n");
	printf("arg -m: %s\n", m);
	printf("arg -b: %s\n", b);
	printf("arg -i: %s\n", i);

	printf("arg -e: %d\n", e);
	printf("arg -d: %d\n", d);

	free(b);
	exit(0);
}