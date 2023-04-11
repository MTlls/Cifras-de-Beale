#include "libLista.h"

/*
 * Cria uma lista vazia e a retorna, se falhar retorna NULL.
 */

lista_t *lista_cria() {
	lista_t *l;

	/*Testando o malloc*/
	if(!(l = (lista_t *)malloc(sizeof(lista_t))))
		return NULL;

	l->tamanho = 0;
	l->ini = NULL;

	return l;
}

/*
 * Remove todos os elementos da lista, libera espaco e retorna NULL.
 */

lista_t *lista_destroi(lista_t *l) {
	int elem;

	/* A função retirar do início da free em todos os nodos,
	 * assim, só precisamos
	 * executá-la iterativamente */

	while(lista_vazia(l) == 0)
		lista_retira_inicio(l, &elem);

	free(l);
	return NULL;
}

/*
 * Retorna 1 se a lista esta vazia e 0 caso contrario.
 */

int lista_vazia(lista_t *l) {
	if(lista_tamanho(l) != 0)
		return 0;

	return 1;
}

/*
 * Retorna o tamanho da lista, isto eh, o numero de elementos presentes nela.
 */

int lista_tamanho(lista_t *l) {
	return l->tamanho;
}

/*
 * Insere o elemento no inicio da lista.
 * Retorna 1 se a operacao foi bem sucedida e 0 caso contrario.
 */
int lista_insere_inicio(lista_t *l, int elemento) {
	nodo_l_t *NewNodo;

	/*Testando o malloc*/
	if(!(NewNodo = (nodo_l_t *)malloc(sizeof(nodo_l_t))))
		return 0;

	NewNodo->elemento = elemento;

	/* Movendo o início para frente */
	NewNodo->prox = l->ini;
	l->ini = NewNodo;
	l->tamanho++;

	return 1;
}

/* Ordena a lista e retorna a mesma */

lista_t *ordena_lista(lista_t *l) {
	nodo_l_t *NodoAtual;
	nodo_l_t *Aux = NULL;
	int temp;

	NodoAtual = l->ini;

	while(NodoAtual != NULL) {
		Aux = NodoAtual->prox;

		while(Aux != NULL) {
			if(NodoAtual->elemento > Aux->elemento) {
				/* Trocando os dois nodos */
				temp = NodoAtual->elemento;
				NodoAtual->elemento = Aux->elemento;
				Aux->elemento = temp;
			}
			Aux = Aux->prox;
		}
		NodoAtual = NodoAtual->prox;
	}

	return l;
}

/*
 * Remove o elemento do inicio da lista e o retorna em 'elemento'.
 * Retorna 1 se a operacao foi bem sucedida e 0 caso contrario.
 */

int lista_retira_inicio(lista_t *l, int *elemento) {
	nodo_l_t *temp;
	temp = l->ini;

	if(lista_vazia(l))
		return 0;

	*elemento = (l->ini)->elemento;

	/* Passando o início para o nodo da frente */
	l->ini = (l->ini)->prox;
	l->tamanho--;
	temp->elemento = 0;
	temp->prox = NULL;
	free(temp);

	return 1;
}

/*
 * Retorna 1 se o elemento existe na lista e 0 caso contrario.
 */
int lista_pertence(lista_t *l, int elemento) {
	nodo_l_t *NodoAtual;

	if(lista_vazia(l))
		return 0;

	NodoAtual = l->ini;

	if(lista_tamanho(l) == 1) {
		if(NodoAtual->elemento == elemento)
			return 1;
	}

	while(NodoAtual->prox != NULL) {
		/* Se achar o elemento, sai do laço e retorna 1 */
		if(NodoAtual->elemento == elemento)
			return 1;
		NodoAtual = NodoAtual->prox;
	}

	if(NodoAtual->elemento == elemento)
		return 1;

	/* Se chegou até aqui, é porque não achou */
	return 0;
}

/*
 * Imprime a lista, do inicio ate o fim, este por ultimo, sem espaco no final.
 * Quando a lista estiver vazia, nao imprime nada, nem um \n.
 * Esta funcao eh somente para facilitar teus testes.
 * Normalmente ela nao existe nas implementacoes de um TAD lista.
 */
void lista_imprime(FILE *arq, lista_t *l) {
	nodo_l_t *NodoAtual;
	NodoAtual = l->ini;

	if(lista_vazia(l) == 0) {
		while(NodoAtual->prox != NULL) {
			fprintf(arq, "%d ", NodoAtual->elemento);
			NodoAtual = NodoAtual->prox;
		}

		/* Imprimindo o último elemento da lista */
		fprintf(arq, "%d\n", NodoAtual->elemento);
	}
}

/**
 * Função realiza a busca do n-ésimo indice da lista e o retorna.
 * Retorna null caso contrário.
 */
int lista_busca(lista_t *n, int index) {
	int i;
	nodo_l_t *aux = n->ini;

	for(i = 0; i < index; i++) {
		aux = aux->prox;
	}
	if(aux == NULL)
		return -2;

	return aux->elemento;
}