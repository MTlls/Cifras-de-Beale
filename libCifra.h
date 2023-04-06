#include <stdio.h>
#include "libLista.h"
#ifndef _LIBCifra_t_H
#define _LIBCifra_t_H

/*Funções/structs que manipulam as estruturas usadas para montar o arquivo de chaves e decodificar as mensagens cifradas (não inclui a struct lista_t e seus nodos)*/

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

/**
 * Struct do nodo índice, cada nodo contém um índice e um respectivo caractere,
 * além disso, o nodo participa de uma árvore red-black, tendo a cor vermelha(1) ou preta(0).
 *
 */
struct nodo_indice {
	int indice;              /* índice do caractere */
	int caractere;           /* qual caractere */
	int cor;                 /* 1: vermelho, 2: preto*/
	struct nodo_indice *pai; /* nó pai*/
	struct nodo_indice *dir; /* nó direito*/
	struct nodo_indice *esq; /* nó esquerdo*/
};
typedef struct nodo_indice nindice_t;

/* FUNÇÕES QUE MONTAM/DESMONTAM A LISTA DA CIFRA*/

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
 * Imprime a lista de caracteres, do inicio ate o fim, este por ultimo, sem espaco no final.
 * Quando a lista de caracteres estiver vazia, nao imprime nada, nem um \n.
 * Esta funcao eh somente para facilitar teus testes.
 * Normalmente ela nao existe nas implementacoes de um TAD lista.
 */
void lchar_imprime(FILE *arq, lchar_t *l);

#endif