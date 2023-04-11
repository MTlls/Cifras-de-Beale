#include <stdio.h>
#include <stdlib.h>

#include "libLista.h"
#ifndef _LIBCifra_t_H
#define _LIBCifra_t_H

/**
 * Funções/structs que manipulam as estruturas usadas para as chaves;
 * Também usado para criar o Arquivo de Chaves (a struct lista_t e seus nodos estão no libLista).
 * 
 * */

/*
 * Struct do nodo char, cada nodo contém uma lista de números
 */
struct nchar_l {
	int elemento;         /* lista de numeros inteiros */
	struct lista *lista;  /* ponteiro para a lista de indices*/
	struct nchar_l *prox; /* ponteiro para o proximo caractere */
};
typedef struct nchar_l nchar_l_t;

/**
 *Struct da lista contendo os caracteres
 */
struct list_char {
	nchar_l_t *ini; /* ponteiro para o inicio da lista */
	int tamanho;    /* numero de elementos na lista    */
};
typedef struct list_char lchar_t;

/*
 * Cria uma lista de caracteres vazia e a retorna, se falhar retorna NULL.
 */
lchar_t *lchar_cria();

/*
 * Remove todos os elementos da lista de caracteres, libera espaco e retorna NULL.
 */
lchar_t *lchar_destroi(lchar_t *l);

/*****************FUNÇÕES PARA LISTA DE CHAVES/CARACTERES*****************/

/*
 * Retorna 1 se a lista de caracteres esta vazia e 0 caso contrario.
 */
int lchar_vazia(lchar_t *l);

/*
 * Retorna o tamanho da lista de caracteres, isto eh, o numero de caracteres presentes nela.
 */
int lchar_tamanho(lchar_t *l);

/*
 * Retorna 1 se o caractere existe na lista e 0 caso contrario.
 */
int lchar_pertence(lchar_t *l, int caractere);

/*
 * Insere o caractere no inicio da lista.
 * Retorna 1 se a operacao foi bem sucedida e 0 caso contrario.
 */
int lchar_insere_inicio(lchar_t *l, int caractere, int index);

/*
 * Insere o elemento na lista de caracteres garantindo ordenacao em ordem crescente.
 * Retorna 1 se a operacao foi bem sucedida e 0 caso contrario.
 */
int lchar_insere_ordenado(lchar_t *l, int caractere, int index);

/*
 * Inclui o índice na chave, retorna 1 se
 * inserido com sucesso, 0 caso contrário
 */
int nchar_insere_indice(lchar_t *l, int caractere, int index);

/*
 * Remove o elemento do inicio da lista e o retorna em 'elemento'.
 * Retorna 1 se a operacao foi bem sucedida e 0 caso contrario.
 */

int lchar_retira_inicio(lchar_t *l, int *elemento);

/*
 * Imprime a lista de caracteres, do inicio ate o fim, este por ultimo.
 */
void lchar_escreve(FILE *arq, lchar_t *l);

/*
 * Insere chaves e atualiza índices se a chave já existir.
 * Retorna 1 se inserido com sucesso, 0 caso contrário.
 */
int lchar_insere(lchar_t *l, int caractere, int index);

#endif