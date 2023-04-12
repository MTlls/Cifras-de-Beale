#include <stdio.h>

#ifndef _ARGS_H_
#define _ARGS_H_

/**
 * Struct responsável por guardar as flags e seus argumentos.
  */
struct argumentos {
	int eFlag; /* flah da opt e (encode) */
	int dFlag; /* flah da opt d (decode) */
	int oFlag; /* flag da opt o (MensagemCodificada/MensagemDecodificada) */
	int bFlag; /* flag da opt b (LivroCifra) */
	int cFlag; /* flag da opt c (ArquivoDeChaves) */
	int mFlag; /* flag da opt m (Mensagem) */
	int iFlag; /* flag da opt i (MensagemCodificada) */

	char *strOutput;   /*string do argumento -o */
	char *strBook;     /*string do argumento -b */
	char *strChave;    /*string do argumento -c */
	char *strMensagem; /*string do argumento -m */
	char *strInput;    /*string do argumento -i */

	FILE *output;   /* arquivo output  */
	FILE *book;     /* arquivo book  */
	FILE *chave;    /* arquivo chave  */
	FILE *mensagem; /* arquivo mensagem  */
	FILE *input;    /* arquivo input */

};
typedef struct argumentos args_t;

/**
 * Função cria uma struct args_t que recebe os argumentos, as flags e os arquivos
 */
args_t *criaArgs();

/**
 * Função que fecha todos os arquivos e destrói todos os argumentos e flags.
 * Usado em caso de erro ou término da execução do programa.
 */
args_t *destroiArgs(args_t *args);

/**
 * Função fecha cada arquivo aberto.
 */
void fechaArquivos(args_t *args);

/**
 * Função realiza o free() de cada string que possuía o nome de cada arquivo.
 */
void liberaArgumentos(args_t *args);

/**
 * Função responsável por inserir o nome dos argumentos,
 * são usados para abrir arquivos.
 */
void criaNomeArq(args_t *args, char option, char *str);

/**
 * Função responsável por criar a stream dos arquivos principais para codificação.
 *  Retorna NULL caso sucesso e o nome do arquivo que ocorreu o erro caso contrário.
 */
char *criaArqEncode(args_t *args);

/**
 * Função responsável por criar a stream dos arquivos principais para
 * decodificação.
 * Retorna NULL caso sucesso e o nome do arquivo que ocorreu o erro caso contrário.
 */
char* criaArqDecode(args_t *args);

/**
 * Função que verifica todas os possíveis erros na entrada de opções/argumentos.
 * Dispara erros e termina a execução ou "codificado"/"decodificado" na saída.
 */
void verificaArgs(args_t *args);

/**
 * Função que verifica se o arquivo está vazio.
 * Retorna 1 se estiver vazio, 0 caso contrário.
*/
int verificaArqVazio(FILE *arq);

#endif