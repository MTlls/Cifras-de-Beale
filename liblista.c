#include "liblista.h"

#include <stdio.h>
#include <stdlib.h>

/*
 * Cria uma lista vazia e a retorna, se falhar retorna NULL.
 */

lista_t *lista_cria() {
	lista_t *l;

	/*Testando o malloc*/
	if(!(l = (lista_t*)malloc(sizeof(lista_t))))
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
	nodo_l_t* NewNodo;

	/*Testando o malloc*/
	if(!(NewNodo = (nodo_l_t*)malloc(sizeof(nodo_l_t))))
		return 0;

	NewNodo->elemento = elemento;

	/* Movendo o início para frente */
	NewNodo->prox = l->ini;
	l->ini = NewNodo;
	l->tamanho++;

	return 1;
}

/*
 * Insere o elemento no final da lista.
 * Retorna 1 se a operacao foi bem sucedida e 0 caso contrario.
 */
int lista_insere_fim(lista_t *l, int elemento) {
	nodo_l_t *NodoAtual;
	nodo_l_t *NewNode;

	/*Testando o malloc*/
	if(!(NewNode = (nodo_l_t*)malloc(sizeof(nodo_l_t))))
		return 0;

	NewNode->elemento = elemento;
	NewNode->prox = NULL;

	if(lista_vazia(l) == 1) {
		l->ini = NewNode;
		l->tamanho++;
		return 1;
	} else {
		NodoAtual = l->ini;

		/*Quando NodoAtual->prox for NULL,
		 * estaremos no último elemento da lista */
		while(NodoAtual->prox != NULL)
			NodoAtual = NodoAtual->prox;

		NodoAtual->prox = NewNode;
		l->tamanho++;
	}
	return 1;
}

/* Ordena a lista e retorna a mesma */

lista_t *ordena_lista(lista_t* l) {
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
 * Insere o elemento na lista garantindo ordenacao em ordem crescente.
 * Retorna 1 se a operacao foi bem sucedida e 0 caso contrario.
 */

int lista_insere_ordenado(lista_t *l, int elemento) {
	/* Para garantir isso, podemos simplesmente inserir
	 * no final e ordenar depois */

	lista_insere_fim(l, elemento);
	l = ordena_lista(l);

	return 1;
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
 * Remove o elemento do final da lista e o retorna em 'elemento'.
 * Retorna 1 se a operacao foi bem sucedida e 0 caso contrario.
 */

int lista_retira_fim(lista_t *l, int *elemento) {
	nodo_l_t *NodoAtual;

	if(lista_vazia(l))
		return 0;

	/* Se só tem um elemento na lista, removendo-o */
	if((l->ini)->prox == NULL) {
		*elemento = (l->ini)->elemento;
		l->tamanho--;
		free(l->ini);
		return 1;
	}

	/* Indo para o penúltimo elemento da lista */
	NodoAtual = l->ini;
	while((NodoAtual->prox)->prox != NULL)
		NodoAtual = NodoAtual->prox;

	/*NodoAtual aponta para o penúltimo,
	 * logo podemos remover NodoAtual->prox */
	*elemento = (NodoAtual->prox)->elemento;
	free(NodoAtual->prox);
	NodoAtual->prox = NULL;
	l->tamanho--;

	return 1;
}

/*
 * Remove o elemento 'elemento' caso ele exista na lista.
 * Retorna 1 se a operacao foi bem sucedida e 0 caso contrario.
 * Se o elemento nao for encontrado na lista tambem retorna 0.
 */

int lista_retira_elemento(lista_t *l, int *elemento) {
	nodo_l_t *NodoAtual;
	NodoAtual = l->ini;
	int elem;
	elem = *elemento;

	/* Se o elemento não pertence a lista, retorna 0 */
	if(lista_pertence(l, elem) == 0)
		return 0;
	else {
		if(NodoAtual->elemento == elem)
			lista_retira_inicio(l, &elem);
		else {
			while((NodoAtual->prox)->elemento != elem)
				NodoAtual = NodoAtual->prox;

			/* NodoAtual é o anterior do Nodo que queremos remover
			 * Logo, podemos trabalhar com NodoAtual->prox */
			nodo_l_t* del;

			/* del é o Nodo a ser deletado */
			del = NodoAtual->prox;
			NodoAtual->prox = (NodoAtual->prox)->prox;
			del->elemento = 0;
			del->prox = NULL;
			l->tamanho--;
			free(del);
		}
	}
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
			printf("%d ", NodoAtual->elemento);
			fprintf(arq, "%d ", NodoAtual->elemento);
			NodoAtual = NodoAtual->prox;
		}

		/* Imprimindo o último elemento da lista */
		printf("%d", NodoAtual->elemento);
		fprintf(arq, "%d\n", NodoAtual->elemento);
	}
	printf("\n");
}

/*******************FUNÇÕES DAS LISTAS DE CHAVES/CARACTERES*****************/

/*
 * Insere chaves e atualiza índices se a chave já existir.
 * Retorna 1 se inserido com sucesso, 0 caso contrário.
 */
int setChave(lchar_t *l, int caractere, int index) {
	if(lchar_pertence(l, caractere))
		return nchar_insere_indice(l, caractere, index);
	return lchar_insere_ordenado(l, caractere, index);
}

/*
 * Cria uma lista de caracteres vazia e a retorna, se falhar retorna NULL.
 */
lchar_t *lchar_cria() {
	lchar_t *l;

	/*Testando o malloc*/
	if(!(l = (lchar_t*)malloc(sizeof(lchar_t))))
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
	if(!(newNodo = (nchar_l_t*)malloc(sizeof(nchar_l_t))) ||
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
	if(!(newNodo = (nchar_l_t*)malloc(sizeof(nchar_l_t))) ||
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
		/* Se achar o elemento, sai do laço e retorna 1 */
		if(newNodo->elemento == caractere) {
			return lista_insere_inicio(newNodo->lista, index);
		}
		newNodo = newNodo->prox;
	}

	if(newNodo->elemento == caractere)
		return lista_insere_inicio(newNodo->lista, index);

	/* Se chegou até aqui, é porque não achou */
	return 0;
}

/*
 * Imprime a lista de caracteres, do inicio ate o fim, este por ultimo, sem espaco no final.
 * Quando a lista de caracteres estiver vazia, nao imprime nada, nem um \n.
 * Esta funcao eh somente para facilitar teus testes.
 * Normalmente ela nao existe nas implementacoes de um TAD lista.
 */
void lchar_imprime(FILE *arq, lchar_t *l) {
	nchar_l_t *NodoAtual;

	NodoAtual = l->ini;

	if(lchar_vazia(l) == 0) {
		while(NodoAtual->prox != NULL) {
			printf("%c: ", NodoAtual->elemento);

			// insere no arquivo o caractere e sua respectiva lista
			fprintf(arq, "%lc: ", NodoAtual->elemento);
			lista_imprime(arq, NodoAtual->lista);

			NodoAtual = NodoAtual->prox;
		}

		/* Imprimindo o último elemento da lista */
		printf("%c: ", NodoAtual->elemento);
		fprintf(arq, "%lc: ", NodoAtual->elemento);
		lista_imprime(arq, NodoAtual->lista);
	}
}