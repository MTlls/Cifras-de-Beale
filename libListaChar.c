#include "libListaChar.h"

/*
 * Cria uma lista de caracteres vazia e a retorna, se falhar retorna NULL.
 */
lchar_t *lchar_cria() {
	lchar_t *l;

	/*Testando o malloc*/
	if(!(l = (lchar_t *)malloc(sizeof(lchar_t))))
		return NULL;

	l->tamanho = 0;
	l->ini = NULL;

	return l;
}

/*
 * Remove todos os elementos da lista de caracteres, libera espaco e retorna NULL.
 */
lchar_t *lchar_destroi(lchar_t *l) {
	int elem;

	/* A função retirar do início da free em todos os nodos,
	 * assim, só precisamos
	 * executá-la iterativamente */

	while(lchar_vazia(l) == 0)
		lchar_retira_inicio(l, &elem);

	free(l);
	return NULL;
}

/*
 * Remove o elemento do inicio da lista e o retorna em 'elemento'.
 * Retorna 1 se a operacao foi bem sucedida e 0 caso contrario.
 */

int lchar_retira_inicio(lchar_t *l, int *elemento) {
	nchar_l_t *temp;
	lista_t *lista;
	temp = l->ini;

	if(lchar_vazia(l))
		return 0;

	*elemento = (l->ini)->elemento;

	/* Passando o início para o nodo da frente */
	lista = (temp)->lista;
	l->ini = (l->ini)->prox;
	l->tamanho--;
	temp->elemento = 0;
	temp->lista = lista_destroi(lista);
	temp->prox = NULL;
	free(temp);

	return 1;
}
/*
 * Retorna 1 se a lista de caracteres esta vazia e 0 caso contrario.
 */
int lchar_vazia(lchar_t *l) {
	if(lchar_tamanho(l) != 0)
		return 0;

	return 1;
}

/*
 * Retorna o tamanho da lista de caracteres, isto eh, o numero de caracteres presentes nela.
 */
int lchar_tamanho(lchar_t *l) {
	return l->tamanho;
}

/*
 * Insere o caractere no inicio da lista.
 * Retorna 1 se a operacao foi bem sucedida e 0 caso contrario.
 */
int lchar_insere_inicio(lchar_t *l, int caractere, int index) {
	nchar_l_t *newNodo;
	lista_t *newLista;

	/*Testando o malloc*/
	if(!(newNodo = (nchar_l_t *)malloc(sizeof(nchar_l_t))) ||
	   !(newLista = lista_cria()))
		return 0;

	newNodo->elemento = caractere;

	/* Insere o indice do caractere no inicio da lista do char*/
	if(!(lista_insere_inicio(newLista, index)))
		return 0;

	newNodo->lista = newLista;

	/* Movendo o início para frente */
	newNodo->prox = l->ini;
	l->ini = newNodo;
	l->tamanho++;

	return 1;
}

/*
 * Insere o caractere na lista garantindo ordenacao em ordem crescente.
 * Retorna 1 se a operacao foi bem sucedida e 0 caso contrario.
 */

int lchar_insere_ordenado(lchar_t *l, int caractere, int index) {
	nchar_l_t *aux;
	nchar_l_t *newNodo;
	lista_t *newLista;

	/*Testando o malloc*/
	if(!(newNodo = (nchar_l_t *)malloc(sizeof(nchar_l_t))) ||
	   !(newLista = lista_cria()))
		return 0;

	newNodo->elemento = caractere;
	/* Insere o indice do caractere no inicio da lista do char*/
	if(!(lista_insere_inicio(newLista, index)))
		return 0;

	newNodo->lista = newLista;
	newNodo->prox = NULL;

	aux = l->ini;
	if(lchar_vazia(l) == 1) {
		l->ini = newNodo;
		l->tamanho++;
		return 1;
	} else if(caractere < l->ini->elemento) {
		/*insere no inicio se for o menor valor*/
		l->ini = newNodo;
		l->ini->prox = aux;
	} else {
		/* É iterado até que o próximo do auxiliar seja maior
		 */
		while((aux->prox != NULL) && (caractere > aux->prox->elemento)) {
			aux = aux->prox;
		}

		/* Agora o próximo do novo nodo será o próximo
		 * do auxiliar e o proximo do auxiliar o novo nodo*/
		newNodo->prox = aux->prox;
		aux->prox = newNodo;
	}
	l->tamanho++;
	return 1;
}

/*
 * Retorna 1 se o caractere existe na lista e 0 caso contrario.
 */
int lchar_pertence(lchar_t *l, int caractere) {
	nchar_l_t *NodoAtual;

	if(lchar_vazia(l))
		return 0;

	NodoAtual = l->ini;

	if(lchar_tamanho(l) == 1) {
		if(NodoAtual->elemento == caractere)
			return 1;
	}

	while(NodoAtual->prox != NULL) {
		/* Se achar o elemento, sai do laço e retorna 1 */
		if(NodoAtual->elemento == caractere)
			return 1;
		NodoAtual = NodoAtual->prox;
	}

	if(NodoAtual->elemento == caractere)
		return 1;

	/* Se chegou até aqui, é porque não achou */
	return 0;
}

/**
 * Retorna o nodo do caractere inserido no paramâmetro 'caractere',
 * caso não exista retorna NULL
 */
nchar_l_t *get_nchar(lchar_t *l, int caractere) {
	/* Se não pertencer: */
	if(!lchar_pertence(l, caractere))
		return NULL;

	nchar_l_t *nodoAtual;

	nodoAtual = l->ini;

	/* Se pertencer:*/
	while(nodoAtual->elemento != caractere)
		nodoAtual = nodoAtual->prox;

	return nodoAtual;
}

/**
 * Inclui o índice na lista da chave, retorna 1 se
 * inserido com sucesso, 0 caso contrário.
 */
int nchar_insere_indice(lchar_t *l, int caractere, int index) {
	nchar_l_t *newNodo;

	if(lchar_vazia(l))
		return 0;

	newNodo = l->ini;

	if(lchar_tamanho(l) == 1) {
		if(newNodo->elemento == caractere) {
			return lista_insere_inicio(newNodo->lista, index);
		}
	}

	while(newNodo->prox != NULL) {
		//Se achar o elemento, sai do laço e retorna 1.
		if(newNodo->elemento == caractere) {
			// Insere o índice na lista do caractere
			return lista_insere_inicio(newNodo->lista, index);
		}
		newNodo = newNodo->prox;
	}

	// Último elemento da lista
	if(newNodo->elemento == caractere)
		return lista_insere_inicio(newNodo->lista, index);

	//Se chegou até aqui, é porque não achou.
	return 0;
}

/*
 * Escreve a lista de caracteres no arquivo, do inicio ate o fim.
 */
void lchar_escreve(FILE *arq, lchar_t *l) {
	nchar_l_t *NodoAtual;

	NodoAtual = l->ini;

	if(lchar_vazia(l) == 0) {
		while(NodoAtual->prox != NULL) {

			// insere no arquivo o caractere e sua respectiva lista
			fprintf(arq, "%lc: ", NodoAtual->elemento);
			lista_imprime(arq, NodoAtual->lista);

			NodoAtual = NodoAtual->prox;
		}

		/* Imprimindo o último elemento da lista */
		fprintf(arq, "%lc: ", NodoAtual->elemento);
		lista_imprime(arq, NodoAtual->lista);
	}
}

/*
 * Insere chaves e atualiza índices se a chave já existir.
 * Retorna 1 se inserido com sucesso, 0 caso contrário.
 */
int lchar_insere(lchar_t *l, int caractere, int index) {
	if(lchar_pertence(l, caractere))
		return nchar_insere_indice(l, caractere, index);
	return lchar_insere_ordenado(l, caractere, index);
}