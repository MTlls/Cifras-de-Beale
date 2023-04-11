
#include "libErro.h"

/**
 * Função realizada caso aconteça um erro ao abrir o arquivo.
 * Dispara uma mensagem na saída de erro indicando o mesmo.
 */
void erroArq(char *arq) {
	fprintf(stderr, "ERRO: %s \"%s\": %s\n", "Nao foi possivel abrir/criar o arquivo", arq, strerror(errno));
}

/**
 * Função realizada caso o arquivo esteja vazio.
 * Dispara uma mensagem na saída de erro indicando o mesmo.
 */
void erroArqVazio(char *arq) {
	fprintf(stderr, "ERRO: %s \"%s\"\n", "Arquivo está vazio", arq);
}

/**
 * Função realizada caso aconteça um erro ao codificar.
 * Dispara uma mensagem na saída de erro indicando o mesmo.
 */
void erroEncode() {
	fprintf(stderr, "ERRO: %s\n", "Nao foi possivel codificar o arquivo");
}

/**
 * Função realizada caso aconteça um erro ao decodificar.
 * Dispara uma mensagem na saída de erro indicando o mesmo.
 */
void erroDecode() {
	fprintf(stderr, "ERRO: %s\n", "Nao foi possivel decodificar o arquivo");
	exit(1);
}

/**
 * Função realizada caso falte o argumento na opção
 * Dispara uma mensagem na saída de erro indicando que a opção requer argumento.
 */
void faltaArg(int option) {
	fprintf(stderr, "ERRO: Opção -%c requer um argumento.\n", option);
	exit(1);
}

/**
 * Função realizada caso falte alguma opção para encriptar ou desencriptar
 * Dispara uma mensagem na saída de erro indicando o mesmo.
 */
void faltaOpt(int option) {
	fprintf(stderr, "ERRO: Para essa ação, é necessário especificar a opção %c.\n", option);
	exit(1);
}
/**
 * Função realizada caso -e e -d ou -b e -c (na decodificação) estejam sendo utilizados ao mesmo tempo
 * Dispara uma mensagem na saída de erro indicando o mesmo.
 */
void simultaneo() {
	fprintf(stderr, "ERRO: Operação não aceita. Não é possível satisfazer as duas opções simultaneamente.\n");
	exit(1);
}

/**
 * Função realizada caso seja uma opção exclusiva de encode ou decode
 * Dispara uma mensagem na saída de erro indicando o mesmo.
 */
void optExclusiva(int option) {
	fprintf(stderr, "ERRO: Operação não aceita. Opção -%c exclusiva da opção contrária a escolhida (-e ou -d).\n", option);
	exit(1);
}

/**
 * Função realizada caso seja uma opção inválida
 * Dispara uma mensagem na saída de erro indicando o mesmo.
 */
void optInvalida(int option) {
	fprintf(stderr, "ERRO: Opção inválida. Inserido foi %c\n", option);
	exit(1);
}

/**
 * Função realizada caso não seja indicado a opção de output
 * Dispara uma mensagem na saída de erro indicando o mesmo.
 */
void semOutput() {
	fprintf(stderr, "ERRO: Necessário indicar o output.\n");
	exit(1);
}

/**
 * Função realiza o free() de cada string que possuía o nome de cada arquivo.
 */
void liberarArgumentos(char *output, char *book, char *input, char *mensagem, char *chaves) {
	if(output)
		free(output);
	if(book)
		free(book);
	if(input)
		free(input);
	if(mensagem)
		free(mensagem);
	if(chaves)
		free(chaves);
}

/**
 * Função realiza o free() de cada string que possuía o nome de cada arquivo.
 */
void fechaArquivos(FILE *book, FILE *mensagem, FILE *output, FILE *chaves, FILE *input) {
	if(output)
		fclose(output);
	if(book)
		fclose(book);
	if(input)
		fclose(input);
	if(mensagem)
		fclose(mensagem);
	if(chaves)
		fclose(chaves);
}