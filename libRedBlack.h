
#include <stdio.h>
#include <stdlib.h>

#ifndef _LIBRedBlack_t_H
#define _LIBRedBlack_t_H

/**
 * Struct do nodo índice, cada nodo contém um índice e um respectivo caractere,
 * além disso, o nodo participa de uma árvore red-black, tendo a cor vermelha(1) ou preta(0).
 *
 */
struct nodo_index {
	int indice;             /* índice do caractere */
	int caractere;          /* qual caractere */
	int cor;                /* 1: vermelho, 2: preto*/
	struct nodo_index *pai; /* nó pai*/
	struct nodo_index *dir; /* nó direito*/
	struct nodo_index *esq; /* nó esquerdo*/
};
typedef struct nodo_index nodo_index_t;

/**
 * Função que verifica se a árvore está vazia.
 * retorna 1 se vazia ou 0 se não.
 */
int arvore_vazia(nodo_index_t *raiz);

/**
 * Função que insere o nó na árvore sem um balanceamento redblack (com excessão da raiz). Retorna o nó inserido.
 */
nodo_index_t *insere_arvore_bst(nodo_index_t *viajante, nodo_index_t *input);

/**
 * Função que retorna o avó do nó inserido no argumento.
 */
nodo_index_t *getAvo(nodo_index_t *no);

/**
 * Função que retorna o tio do nó inserido no argumento.
 */
nodo_index_t *getTio(nodo_index_t *no);

/**
 * Função que equilibra a arvore red-black.
 */
void equilibra_redblack(nodo_index_t **raiz, nodo_index_t *no);

/* Segue casos de balanceamento da árvore red-black */

/**
 * Função que rotaciona o nó na direção esquerda.
 */

void rotacaoEsq(nodo_index_t **raiz, nodo_index_t *no);

/**
 * Função que rotaciona o nó na direção direita.
 */
void rotacaoDir(nodo_index_t **raiz, nodo_index_t *no);

/**
 *  Função para imprimir a arvore e suas cores.
 * */
void inorder(nodo_index_t *no);

/**
 *  Função para procurar o elemento na árvore.
 *  Retorna o caractere do índice ou 64 (@) caso contrário.
 */
int srchIndex(nodo_index_t *viajante, int indice);

/**
 * Função para destruir a arvore, usando recursividade pós-order (esq, dir,
 * raiz)
 */
void destroi(nodo_index_t *no);

/**
 * Função que cria um nó, dado o caractere, e o seu índice.
 * O insere na árvore, garantindo o balanceamento de uma árvore redblack.
 */
void insere_redblack(nodo_index_t **raiz, int caractere, int index);

#endif