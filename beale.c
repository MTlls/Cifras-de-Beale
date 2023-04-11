#include <getopt.h>
#include <locale.h>

#include "cifrador.h"
#include "libErro.h"

#define EXTENSAO ".ascii"

int main(int argc, char **argv) {
	clock_t tInicio, tFim;
	double tDecorrido = 0.0;
	tInicio = clock();
	setlocale(LC_CTYPE, "");
	int option = 0;
	int dFlag = 0, eFlag = 0, iFlag = 0, mFLag = 0, oFLag = 0, cFlag = 0, bFlag = 0;

	// Strings contendo cada argumento que será usado.
	char *strOutput = NULL;
	char *strInput = NULL;
	char *strMensagem = NULL;
	char *strBook = NULL;
	char *strChaves = NULL;

	// Arquivos que serão utilizados.
	FILE *output = NULL;
	FILE *input = NULL;
	FILE *mensagem = NULL;
	FILE *book = NULL;
	FILE *chaves = NULL;

	// Para customizar mensagem de erro
	opterr = 0;
	char optstring[13] = ":edi:m:o:c:b:";

	while((option = getopt(argc, argv, optstring)) != -1) {
		// Opção requer argumento e é seguida de outra opção, um erro que será tratado no caso ':'
		if(optarg && optarg[0] == '-') {
			optopt = option;
			option = ':';
		}
		switch(option) {
		case 'd':
			if(eFlag == 1) {
				liberarArgumentos(strOutput, strBook, strInput, strMensagem, strChaves);
				simultaneo();
			}
			dFlag = 1;
			break;
		case 'e':
			if(dFlag == 1) {
				liberarArgumentos(strOutput, strBook, strInput, strMensagem, strChaves);
				simultaneo();
			}
			eFlag = 1;
			break;
		case 'm':
			if(dFlag == 1 || eFlag == 0) {
				liberarArgumentos(strOutput, strBook, strInput, strMensagem, strChaves);
				optExclusiva(option);
			}
			mFLag = 1;
			strMensagem = (char *)malloc(strlen(optarg) + strlen(EXTENSAO) + 1);
			strcat(strcpy(strMensagem, optarg), EXTENSAO);
			break;
		case 'i':
			if(dFlag == 0 || eFlag == 1) {
				liberarArgumentos(strOutput, strBook, strInput, strMensagem, strChaves);
				optExclusiva(option);
			}
			iFlag = 1;

			// Aloca memória para o argumento + sufixo .ascii
			strInput = (char *)malloc(strlen(optarg) + strlen(EXTENSAO) + 1);
			strcat(strcpy(strInput, optarg), EXTENSAO);
			break;
		case 'b':
			bFlag = 1;

			// Aloca memória para o argumento + sufixo .ascii
			strBook = (char *)malloc(strlen(optarg) + strlen(EXTENSAO) + 1);
			strcat(strcpy(strBook, optarg), EXTENSAO);
			break;
		case 'o':
			oFLag = 1;

			// Aloca memória para o argumento + sufixo .ascii
			strOutput = (char *)malloc(strlen(optarg) + strlen(EXTENSAO) + 1);
			strcat(strcpy(strOutput, optarg), EXTENSAO);
			break;
		case 'c':
			cFlag = 1;
			// Aloca memória para o argumento + sufixo .ascii
			strChaves = (char *)malloc(strlen(optarg) + strlen(EXTENSAO) + 1);
			strcat(strcpy(strChaves, optarg), EXTENSAO);
			break;
		case ':':  // Opção que requer argumento e não o possui:
			liberarArgumentos(strOutput, strBook, strInput, strMensagem, strChaves);
			faltaArg(optopt);
			break;
		case '?':  // Se a opção é inválida:
			liberarArgumentos(strOutput, strBook, strInput, strMensagem, strChaves);
			optInvalida(optopt);
			break;
		}
	}

	// Necessário um output sempre.
	if(oFLag == 0) {
		liberarArgumentos(strOutput, strBook, strInput, strMensagem, strChaves);
		semOutput();
	}
	if(!(output = fopen(strOutput, "w"))) {
		erroArq(strOutput);
		fechaArquivos(book, mensagem, output, chaves, input);
		liberarArgumentos(strOutput, strBook, strInput, strMensagem, strChaves);
		exit(1);
	}

	// Caso a opção seja encode (-e)
	if(eFlag == 1) {
		// É necessária a mensagem original (-m) ou o livro cifra (-b)
		if(mFLag == 0) {
			fechaArquivos(book, mensagem, output, chaves, input);
			liberarArgumentos(strOutput, strBook, strInput, strMensagem, strChaves);
			faltaOpt('m');
		} else if(bFlag == 0) {
			fechaArquivos(book, mensagem, output, chaves, input);
			liberarArgumentos(strOutput, strBook, strInput, strMensagem, strChaves);
			faltaOpt('b');
		}
		// Cria a stream para a mensagem original e o livro cifra.
		if(!(mensagem = fopen(strMensagem, "r"))) {
			erroArq(strMensagem);
			fechaArquivos(book, mensagem, output, chaves, input);
			liberarArgumentos(strOutput, strBook, strInput, strMensagem, strChaves);
			exit(1);
		} else if(!(book = fopen(strBook, "r"))) {
			erroArq(strBook);
			fechaArquivos(book, mensagem, output, chaves, input);
			liberarArgumentos(strOutput, strBook, strInput, strMensagem, strChaves);
			exit(1);
		}

		// Verifica se os arquivos estão vazios.
		fseek(book, 0, SEEK_END);
		if(ftell(book) == 0) {
			liberarArgumentos(strOutput, strBook, strInput, strMensagem, strChaves);
			fechaArquivos(book, mensagem, output, chaves, input);
			erroArqVazio(strBook);
			exit(1);
		}
		rewind(book);

		// Se for escolhido, cria o arquivo de chaves.
		if(cFlag == 1) {
			if(!(chaves = fopen(strChaves, "w"))) {
				erroArq(strChaves);
				fechaArquivos(book, mensagem, output, chaves, input);
				exit(1);
			}
		}

		// Todas as streams setadas, começa o processo de codificação/encode
		if(!(output = encode(book, mensagem, output, chaves))) {
			fechaArquivos(book, mensagem, output, chaves, input);
			liberarArgumentos(strOutput, strBook, strInput, strMensagem, strChaves);
			erroEncode();
		}
	}
	// Decode:
	else {
		// É necessária a mensagem codificada (-i).
		if(iFlag == 0) {
			fechaArquivos(book, mensagem, output, chaves, input);
			liberarArgumentos(strOutput, strBook, strInput, strMensagem, strChaves);
			faltaOpt('i');
		} else if(bFlag == 1 && cFlag == 1) {  // Impossível decodificar por -b e -c simultaneamente
			fechaArquivos(book, mensagem, output, chaves, input);
			liberarArgumentos(strOutput, strBook, strInput, strMensagem, strChaves);
			simultaneo();
		}

		if(bFlag == 1) {
			// Se for escolhido, lê o arquivo cifra.
			if(!(book = fopen(strBook, "r"))) {
				erroArq(strBook);
				fechaArquivos(book, mensagem, output, chaves, input);
				liberarArgumentos(strOutput, strBook, strInput, strMensagem, strChaves);
				exit(1);
			}
		} else if(cFlag == 1) {
			// Se for escolhido, lê o arquivo de chaves.
			if(!(chaves = fopen(strChaves, "r"))) {
				erroArq(strChaves);
				fechaArquivos(book, mensagem, output, chaves, input);
				liberarArgumentos(strOutput, strBook, strInput, strMensagem, strChaves);

				exit(1);
			}
		}
		// Cria a stream para a mensagem codificada.
		if(!(input = fopen(strInput, "r"))) {
			erroArq(strInput);
			fechaArquivos(book, mensagem, output, chaves, input);
			liberarArgumentos(strOutput, strBook, strInput, strMensagem, strChaves);
			exit(1);
		}
		// Todas as streams setadas, começa o processo de codificação/encode
		if(!(output = decode(book, input, output, chaves))) {
			fechaArquivos(book, mensagem, output, chaves, input);
			liberarArgumentos(strOutput, strBook, strInput, strMensagem, strChaves);
			erroDecode();
		}
	}

	// Fechamento das streams e das strings que guardam argumentos.
	fechaArquivos(book, mensagem, output, chaves, input);
	liberarArgumentos(strOutput, strBook, strInput, strMensagem, strChaves);
	tFim = clock();
	tDecorrido = ((double) (tFim - tInicio) / (CLOCKS_PER_SEC));
	fprintf(stdout, "Tempo: %lf s\n", tDecorrido);
	return 0;
}
