#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <wchar.h>
#include <wctype.h>
#include <getopt.h>
#include <locale.h>

#include "libListaChar.h"

#ifndef _CIFRADOR_H_
#define _CIFRADOR_H_

/**
 * Cria um arquivo com as chaves dadas pelo livroCifra
 * Retorna o arquivo cifrado, NULL caso contrário.
 * */
FILE *encode(FILE *livroCifra, FILE *mensagem, FILE *output, FILE *chaves);

/**
 * Função insere as chaves dentro do arquivo de chaves.
 * Modifica o texto para os caracteres serem todos minúsculos.
 * Retorna 1 se conseguir criar com sucesso ou 0 caso contrário.
 */
int criaChaves(FILE *livroCifra, lchar_t *listaChaves);

/**
 * Troca todos os caracteres da mensagem original.
 *	1 se sucesso. 0 caso contrário.
 */
int trocar(FILE *mensagem, FILE *output, lchar_t *l);

/**
 * Decifra a mensagem de acordo com o arquivo de chave inserido. Retorna com sucesso o arquivo.
 *
 * Usa uma árvore rubro-negra para criar uma lista de indices com seus caracteres, todos ordenados pelo índice.
 *
 * OBS: FILE* chaves é uma stream que aponta ou para o arquivo de chaves, ou para um texto cifra.
 */
FILE *decode(FILE *livroCifra, FILE *input, FILE *output, FILE *chaves);

#endif