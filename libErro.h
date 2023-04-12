#ifndef _LIB_erros_H
#define _LIB_erros_H

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * Função realizada caso aconteça um erro ao abrir o arquivo.
 * Dispara uma mensagem na saída de erro indicando o mesmo.
 */
void erroArq(char *arq);

/**
 * Função realizada caso o arquivo esteja vazio.
 * Dispara uma mensagem na saída de erro indicando o mesmo.
 */
void erroArqVazio(char *arq);

/**
 * Função realizada caso aconteça um erro ao codificar.
 * Dispara uma mensagem na saída de erro indicando o mesmo.
 */
void erroEncode();

/**
 * Função realizada caso aconteça um erro ao decodificar.
 * Dispara uma mensagem na saída de erro indicando o mesmo.
 */
void erroDecode();

/**
 * Função realizada caso falte o argumento na opção
 * Dispara uma mensagem na saída de erro indicando o mesmo.
 * */
void faltaArg(int option);

/**
 * Função realizada caso falte alguma opção para encriptar ou desencriptar
 * Dispara uma mensagem na saída de erro indicando o mesmo.
 */
void faltaOpt(int option);

/**
 * Função realizada caso -e e -d estejam sendo utilizados ao mesmo tempo
 * Dispara uma mensagem na saída de erro, indicando o mesmo.
 */
void simultaneo();

/**
 * Função realizada caso seja uma opção exclusiva de encode ou decode
 * Dispara uma mensagem na saída de erro, indicando o mesmo.
 */
void optExclusiva(int option);

/**
 * Função realizada caso seja uma opção inválida
 * Dispara uma mensagem na saída de erro, indicando o mesmo.
 */
void optInvalida(int option);

/**
 * Função realizada caso não seja indicado a opção de output
 * Dispara uma mensagem na saída de erro, indicando o mesmo.
 */
void semOutput();

/**
 * Função realizada caso seja enviado algum arquivo igual ao output.
 */
void argIgual();

#endif