#include "args.h"

#include <stdio.h>
#include <stdlib.h>

#include "libErro.h"

#define EXTENSAO ".ascii"

args_t *criaArgs() {
	args_t *args;

	if(!(args = (args_t *)malloc(sizeof(args_t))))
		return NULL;

	args->eFlag = 0;
	args->dFlag = 0;
	args->oFlag = 0;
	args->bFlag = 0;
	args->cFlag = 0;
	args->mFlag = 0;
	args->iFlag = 0;

	args->strOutput = NULL;
	args->strBook = NULL;
	args->strChave = NULL;
	args->strMensagem = NULL;
	args->strInput = NULL;

	args->output = NULL;
	args->book = NULL;
	args->chave = NULL;
	args->mensagem = NULL;
	args->input = NULL;

	return args;
}

void liberaArgumentos(args_t *args) {
	if(args->strOutput)
		free(args->strOutput);
	if(args->strBook)
		free(args->strBook);
	if(args->strInput)
		free(args->strInput);
	if(args->strMensagem)
		free(args->strMensagem);
	if(args->strChave)
		free(args->strChave);
}

void fechaArquivos(args_t *args) {
	if(args->output)
		fclose(args->output);
	if(args->book)
		fclose(args->book);
	if(args->input)
		fclose(args->input);
	if(args->mensagem)
		fclose(args->mensagem);
	if(args->chave)
		fclose(args->chave);
}

void liberaFlags(args_t *args) {
	args->eFlag = 0;
	args->dFlag = 0;
	args->oFlag = 0;
	args->bFlag = 0;
	args->cFlag = 0;
	args->mFlag = 0;
	args->iFlag = 0;
}

args_t *destroiArgs(args_t *args) {
	liberaArgumentos(args);

	liberaFlags(args);

	fechaArquivos(args);

	free(args);
	return NULL;
}

void criaNomeArq(args_t *args, char option, char *optarg) {
	switch(option) {
	case 'm':
		args->strMensagem = (char *)malloc(strlen(optarg) + strlen(EXTENSAO) + 1);
		strcat(strcpy(args->strMensagem, optarg), EXTENSAO);
		break;
	case 'i':
		args->strInput = (char *)malloc(strlen(optarg) + strlen(EXTENSAO) + 1);
		strcat(strcpy(args->strInput, optarg), EXTENSAO);
		break;
	case 'b':
		args->strBook = (char *)malloc(strlen(optarg) + strlen(EXTENSAO) + 1);
		strcat(strcpy(args->strBook, optarg), EXTENSAO);
		break;
	case 'o':
		args->strOutput = (char *)malloc(strlen(optarg) + strlen(EXTENSAO) + 1);
		strcat(strcpy(args->strOutput, optarg), EXTENSAO);
		break;
	case 'c':
		args->strChave = (char *)malloc(strlen(optarg) + strlen(EXTENSAO) + 1);
		strcat(strcpy(args->strChave, optarg), EXTENSAO);
		break;
	}
}

char *criaArqEncode(args_t *args) {
	if(!(args->mensagem = fopen(args->strMensagem, "r")))
		return args->strMensagem;

	if(!(args->book = fopen(args->strBook, "r")))
		return args->strBook;

	// Se for escolhido, cria o arquivo de chaves para ESCRITA
	if(args->cFlag == 1) {
		if(!(args->chave = fopen(args->strChave, "w")))
			return args->strChave;
	}

	return NULL;
}

char *criaArqDecode(args_t *args) {
	if(!(args->input = fopen(args->strInput, "r")))
		return args->strInput;

	if(args->bFlag == 1) {  // Se for escolhido, lê o arquivo cifra.
		if(!(args->book = fopen(args->strBook, "r")))
			return args->strBook;
	} else  // Se for escolhido, lê o arquivo de chaves.
		if(!(args->chave = fopen(args->strChave, "r")))
			return args->strChave;

	return NULL;
}

void verificaArgs(args_t *args) {
	// Caso seja encode e decode simultâneo.  XOR.
	if((args->dFlag == 1) && (args->eFlag == 1)) {
		destroiArgs(args);
		simultaneo();
	}

	// Necessário um output sempre.
	if(args->oFlag == 0) {
		destroiArgs(args);
		semOutput();
	}

	// Caso seja uma codificação
	if(args->eFlag == 1) {
		// É necessária a mensagem original (-m) ou o livro cifra (-b)
		if(args->mFlag == 0) {
			destroiArgs(args);
			faltaOpt('m');
		} else if(args->bFlag == 0) {
			destroiArgs(args);
			faltaOpt('b');
		}
		// Mensagem Original e Output não podem ser o mesmo arquivo.
		if(strcmp(args->strMensagem, args->strOutput) == 0)
			argIgual();
	}

	// Caso seja uma decodificação
	if(args->dFlag == 1) {
		// É necessária a mensagem codificada (-i).
		if(args->iFlag == 0) {
			destroiArgs(args);
			faltaOpt('i');
		}
		// Não é necessário a mensagem original (-m)
		else if(args->mFlag == 1) {
			destroiArgs(args);
			optExclusiva('m');
		}

		// Impossível decodificar/não decodificar por -b e -c simultaneamente, basicamente um XOR
		if((args->bFlag == args->cFlag)) {
			destroiArgs(args);
			simultaneo();
		}

		// Input e Output não podem ser o mesmo arquivo.
		if(strcmp(args->strInput, args->strOutput) == 0) {
			destroiArgs(args);
			argIgual();
		}
	}
}