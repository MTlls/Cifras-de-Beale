#include "libRedBlack.h"

int arvore_vazia(nodo_index_t *raiz) {
	if(raiz == NULL)
		return 1;
	return 0;
}

nodo_index_t *insere_arvore_bst(nodo_index_t *viajante, nodo_index_t *input) {
	// caso arvore esteja vazia
	if(viajante == NULL) {
		return input;
	}
	// Menor vai para a esquerda
	if(input->indice < viajante->indice) {
		viajante->esq = insere_arvore_bst(viajante->esq, input);
		viajante->esq->pai = viajante;
	}
	// Maior para a direita
	if(input->indice >= viajante->indice) {
		viajante->dir = insere_arvore_bst(viajante->dir, input);
		viajante->dir->pai = viajante;
	}
	return viajante;
}

/**
 * Função que retorna o avó do nó inserido no argumento.
 */
nodo_index_t *getAvo(nodo_index_t *no) {
	if(!(no->pai->pai))
		return NULL;
	return no->pai->pai;
}

/**
 * Função que retorna o tio do nó inserido no argumento.
 */
nodo_index_t *getTio(nodo_index_t *no) {
	nodo_index_t *avo;

	if(!(avo = getAvo(no)))
		return NULL;  // Se não possui vô, não possui tio.

	// Pai é filho da direita
	if(no->pai == avo->dir)
		return avo->esq;
	// Pai é filho da esquerda
	return avo->dir;
}

/**
 * Função que equilibra a arvore red-black.
 */
void equilibra_redblack(nodo_index_t **raiz, nodo_index_t *no) {
	nodo_index_t *tio = NULL;
	nodo_index_t *avo = NULL;
	nodo_index_t *pai = NULL;
	int corAvo;

	// condições para que seja verificado o balanceamento
	while((no != *raiz) && (no->cor == 1 && no->pai->cor == 1)) {
		// Atualiza os três nós sempre na subida da árvore
		pai = no->pai;
		tio = getTio(no);
		avo = getAvo(no);

		// Verifica se o nó tio é preto (ou se não existe) e se sim, verifica os casos 2 e 3
		if(!tio || tio->cor == 0) {
			// Caso zig-zag
			if((avo->esq == pai && no->pai->dir == no) ||
			   (avo->dir == pai && pai->esq == no)) {
				if(pai == avo->esq)
					rotacaoEsq(raiz, pai);

				else
					rotacaoDir(raiz, pai);

				no = pai;
				pai = no->pai;
			}
			// Caso zig-zig
			if((avo->esq == pai && pai->esq == no) ||
			   (avo->dir == pai && pai->dir == no)) {
				if(pai == avo->esq)
					rotacaoDir(raiz, avo);
				else
					rotacaoEsq(raiz, avo);
			}

			// Recoloração dos nós pai e avô
			corAvo = avo->cor;
			avo->cor = pai->cor;
			pai->cor = corAvo;
			no = pai;
		} else {  // Se o nó tio é vermelho, faz a recoloração do nó tio, avô e pai
			tio->cor = tio->cor == 1 ? 0 : 1;
			avo->cor = avo->cor == 1 ? 0 : 1;
			pai->cor = pai->cor == 1 ? 0 : 1;
			no = avo;
		}
	}
	return;
}

/**
 * Função que rotaciona o nó na direção esquerda.
 */

void rotacaoEsq(nodo_index_t **raiz, nodo_index_t *no) {
	// Salva o ponteiro para o filho à direita do nó que será rotacionado
	nodo_index_t *dir = no->dir;

	// Atualiza o filho à direita do nó que está sendo rotacionado
	no->dir = dir->esq;
	if(no->dir)
		no->dir->pai = no;

	// Atualiza o pai do filho à direita
	dir->pai = no->pai;

	// Atualiza a raiz da árvore, se necessário
	if(!dir->pai)
		*raiz = dir;

	// Atualiza o filho à esquerda ou à direita do pai do nó que foi rotacionado
	else if(no == no->pai->dir)
		no->pai->dir = dir;
	else
		no->pai->esq = dir;

	// Atualiza o filho à esquerda do nó que foi rotacionado
	dir->esq = no;
	// Atualiza o pai do nó que foi rotacionado
	no->pai = dir;
}

/**
 * Função que rotaciona o nó na direção direita.
 */
void rotacaoDir(nodo_index_t **raiz, nodo_index_t *no) {
	// Salva o ponteiro para o filho à esquerda do nó que será rotacionado
	nodo_index_t *esq = no->esq;

	// Atualiza o filho à esquerda do nó que está sendo rotacionado
	no->esq = esq->dir;
	if(no->esq)
		no->esq->pai = no->esq;

	// Atualiza o pai do nó à esquerda
	esq->pai = no->pai;

	// Atualiza a raiz da árvore, se necessário
	if(!no->pai)
		*raiz = esq;

	// Atualiza o filho do pai, se necessário
	else if(no == no->pai->esq) {
		no->pai->esq = esq;
	} else {
		no->pai->dir = esq;
	}

	// Atualiza o filho à direita do nó que está sendo rotacionado
	esq->dir = no;
	// Atualiza o pai do nó que foi rotacionado
	no->pai = esq;
}

// Função para imprimir a arvore e suas cores.
void inorder(nodo_index_t *no) {
	char *cor;
	if(no == NULL)
		return;
	inorder(no->esq);
	printf("índice %d : %s\n", no->indice, cor = no->cor == 0 ? "preto" : "vermelho");
	inorder(no->dir);
}


void destroi(nodo_index_t *no) {
	if(no == NULL)
		return;
	destroi(no->esq);
	destroi(no->dir);
	free(no);
}

int srchIndex(nodo_index_t *viajante, int indice) {
	// Caso base: achamos o elemento.
	// Elemento não foi encontrado. Retorna um @.
	if(viajante == NULL) {
		return 64;
	}
	if(viajante->indice == indice) {
		return viajante->caractere;
	}

	// Elemento está para a esquerda.
	if(indice < viajante->indice) {
		return srchIndex(viajante->esq, indice);
	} 
	// Elemento está para a direita.
	else {
		return srchIndex(viajante->dir, indice);
	}
}

void insere_redblack(nodo_index_t **raiz, int caractere, int index) {
	// Cria-se o novo nó
	nodo_index_t *novoNo = (nodo_index_t *)malloc(sizeof(nodo_index_t));
	novoNo->dir = NULL;
	novoNo->esq = NULL;
	novoNo->pai = NULL;
	novoNo->indice = index;
	novoNo->caractere = caractere;
	novoNo->cor = 1;

	// Insere na árvore rubro-negra
	*raiz = insere_arvore_bst(*raiz, novoNo);

	// Equilibra a árvore rubro-negra
	equilibra_redblack(raiz, novoNo);
	(*raiz)->cor = 0;
}