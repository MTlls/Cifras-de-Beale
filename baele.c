#include <errno.h>
#include <getopt.h>
#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/*
    Função para utilidade futura: obtém as primeiras letras de cada palavra do arquivo.
*/
void getFirstLetter(char *fileName) {
	FILE *message;
	char c;

	if(!(message = fopen(strcat(fileName, ".txt"), "r"))) {
		/* caso o arquivo não exista */
		fprintf(stderr, "ERRO: %s \"%s\": %s\n", "Nao foi possivel abrir o arquivo", fileName, strerror(errno));
		exit(1);
	}

	c = fgetc(message);

	printf("%c\n", c);
	while(c != EOF) {
		if(c == ' ') {
			printf("%c\n", fgetc(message));
		}
		c = fgetc(message);
	}
	fclose(message);
}

int main(int argc, char **argv) {
	int option;
	char *fileFormatted;
	int e = 0, d = 0;
	char *m, *b, *i;

	opterr = 0;

	setlocale(LC_ALL, "pt_BR.UTF-8");

	// Verifica se há mais de 1 argumento
	if(argc == 1) {
		fprintf(stderr, "ERRO: %s", "é necessário mais argumentos.\n");
		exit(1);
	}

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
				getFirstLetter(m);
				break;
			}
		// -b recebe o LivroCifra
		case 'b':
			if(strncmp(optarg, "-", 1) != 0) {
				b = malloc(sizeof((char *)optarg) + 1);
				b = strcpy(b, optarg);
				getFirstLetter(b);
				break;
			}
		// -i recebe a mensagem codificada
		case 'i':
			if(strncmp(optarg, "-", 1) != 0) {
				i = malloc(sizeof((char *)optarg) + 1);
				i = strcpy(i, optarg);
				getFirstLetter(i);
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
	printf("arg -m: %s\n", m);
	printf("arg -b: %s\n", b);
	printf("arg -i: %s\n", i);

	printf("arg -e: %d\n", e);
	printf("arg -d: %d\n", d);

	exit(0);
}
