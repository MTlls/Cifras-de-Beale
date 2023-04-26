#include <getopt.h>
#include <locale.h>

#include "args.h"
#include "cifrador.h"
#include "libErro.h"

int main(int argc, char **argv) {
	// strArqErro é usado para tratamento de erro ao abrir arquivo.
	char *strArqErro;
	int option = 0;

	setlocale(LC_CTYPE, "");

	args_t *args = criaArgs();

	// Para customizar mensagem de erro
	opterr = 0;

	while((option = getopt(argc, argv, ":edi:m:o:c:b:")) != -1) {
		// Opção requer argumento
		if(option != 'e' && option != 'd' && optarg) {
			// É seguida de outra opção, um erro que será tratado no caso ':'
			if(optarg[0] == '-') {
				optopt = option;
				option = ':';
			}
			// Guarda o nome do argumento/arquivo
			else {
				criaNomeArq(args, option, optarg);
			}
		}

		switch(option) {
		case 'd':
			args->dFlag = 1;
			break;
		case 'e':
			args->eFlag = 1;
			break;
		case 'm':
			args->mFlag = 1;
			break;
		case 'i':
			args->iFlag = 1;
			break;
		case 'b':
			args->bFlag = 1;
			break;
		case 'o':
			args->oFlag = 1;
			break;
		case 'c':
			args->cFlag = 1;
			break;
		case ':':  // Opção que requer argumento e não o possui:
			destroiArgs(args);
			faltaArg(optopt);
			break;
		case '?':  // Se a opção é inválida:
			liberaArgumentos(args);
			optInvalida(optopt);
			break;
		}
	}

	// Verifica todos os argumentos (se há alguma incongruência nas opções)
	verificaArgs(args);

	// Necessário um output sempre.
	if(!(args->output = fopen(args->strOutput, "w"))) {
		erroArq(args->strOutput);
		destroiArgs(args);
		exit(1);
	}

	// Avisa os casos especiais
	printf("\nAVISO: Os casos especiais são -1, -2 e -3:\n"
			"-1: Espaço encontrado\n"
			"-2: Valor não consta no livro cifra (Trocado por @ na decodificação)\n"
			"-3: Quebra de linha.\n\n");

	// Caso a opção seja encode (-e)
	if(args->eFlag == 1) {
		if((strArqErro = criaArqEncode(args))) {
			erroArq(strArqErro);
			destroiArgs(args);
			exit(1);
		}

		fprintf(stdout, "Começando a codificação...\n");

		// Todas as streams setadas, começa o processo de codificação/encode
		if(!(args->output = encode(args->book, args->mensagem, args->output, args->chave))) {
			destroiArgs(args);
			erroEncode();
		}

		fprintf(stdout, "Codificado com sucesso!\n");
	}
	// Decode:
	else {
		if((strArqErro = criaArqDecode(args))) {
			erroArq(strArqErro);
			destroiArgs(args);
			exit(1);
		}

		fprintf(stdout, "Começando a decodificação...\n");
		// Todas as streams setadas, começa o processo de codificação/encode
		if(!(args->output = decode(args->book, args->input, args->output, args->chave))) {
			destroiArgs(args);
			erroDecode();
		}

		fprintf(stdout, "Decodificado com sucesso!\n");
	}

	// Fechamento das streams e das strings que guardam argumentos.
	destroiArgs(args);
	return 0;
}
