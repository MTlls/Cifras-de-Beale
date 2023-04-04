/*
 * TAD pilha
 * Autores:
 *    André Ricardo Abed Gregio
 *    Marcos Alexandre Castilho
 *    Luis Carlos Erpen de Bona
 *    Luiz Carlos Pessoa Albini
 *
 * Versao 1.0.0 de 04/04/2022
*/

#ifndef _LIBlista_t_H
#define _LIBlista_t_H

struct nodo_l {
    int elemento;       /* lista de numeros inteiros */
    struct nodo_l* prox;  /* ponteiro para o proximo   */
};
typedef struct nodo_l nodo_l_t;

struct lista {
    nodo_l_t* ini;      /* ponteiro para o inicio da lista */
    int tamanho;        /* numero de elementos na lista    */
};
typedef struct lista lista_t;


/*   FUNÇOES QUE MANIPULAM ESSAS ESTRUTURAS ESTÃO MAIS ABAIXO */
/*
 * Struct do nodo char, cada nodo contém uma lista de números
 */
struct nchar_l {
	int elemento;         /* lista de numeros inteiros */
	struct lista* lista;  /* ponteiro para a lista de indices*/
	struct nchar_l* prox; /* ponteiro para o proximo caractere */
};
typedef struct nchar_l nchar_l_t;

/**
 * Struct da lista contendo os caracteres
 */
struct list_char {
	nchar_l_t* ini; /* ponteiro para o inicio da lista */
	int tamanho;    /* numero de elementos na lista    */
};
typedef struct list_char lchar_t;


/*
 * Cria uma lista vazia e a retorna, se falhar retorna NULL.
*/
lista_t* lista_cria ();

/*
 * Remove todos os elementos da lista, libera espaco e retorna NULL.
*/
lista_t* lista_destroi (lista_t* l);

/*
 * Retorna 1 se a lista esta vazia e 0 caso contrario.
*/
int lista_vazia (lista_t* l);

/*
 * Retorna o tamanho da lista, isto eh, o numero de elementos presentes nela.
*/
int lista_tamanho (lista_t* l);

/*
 * Insere o elemento no inicio da lista.
 * Retorna 1 se a operacao foi bem sucedida e 0 caso contrario.
*/
int lista_insere_inicio (lista_t* l, int elemento);

/*
 * Insere o elemento no final da lista.
 * Retorna 1 se a operacao foi bem sucedida e 0 caso contrario.
*/
int lista_insere_fim (lista_t* l, int elemento);

/*
 * Insere o elemento na lista garantindo ordenacao em ordem crescente.
 * Retorna 1 se a operacao foi bem sucedida e 0 caso contrario.
*/
int lista_insere_ordenado (lista_t* l, int elemento);

/*
 * Remove o elemento do inicio da lista e o retorna em 'elemento'.
 * Retorna 1 se a operacao foi bem sucedida e 0 caso contrario.
*/
int lista_retira_inicio (lista_t* l, int* elemento);

/*
 * Remove o elemento do final da lista e o retorna em 'elemento'.
 * Retorna 1 se a operacao foi bem sucedida e 0 caso contrario.
*/
int lista_retira_fim (lista_t* l, int* elemento);

/*
 * Remove o elemento 'elemento' caso ele exista na lista.
 * Retorna 1 se a operacao foi bem sucedida e 0 caso contrario.
 * Se o elemento nao for encontrado na lista tambem retorna 0.
*/
int lista_retira_elemento (lista_t *l, int *elemento);

/*
 * Retorna 1 se o elemento existe na lista e 0 caso contrario.
*/
int lista_pertence (lista_t* l, int elemento);

/*
 * Imprime a lista, do inicio ate o fim, este por ultimo, sem espaco no final.
 * Quando a lista estiver vazia, nao imprime nada, nem um \n.
 * Esta funcao eh somente para facilitar teus testes.
 * Normalmente ela nao existe nas implementacoes de um TAD lista.
*/
void lista_imprime (lista_t* l);


/* FUNÇÕES QUE MONTAM/DESMONTAM A LISTA DA CIFRA*/

/*
 * Cria uma lista de caracteres vazia e a retorna, se falhar retorna NULL.
 */
lchar_t* lchar_cria();

/*
 * Remove todos os elementos da lista de caracteres, libera espaco e retorna NULL.
 */
lchar_t* lchar_destroi(lchar_t* l);






/*****************FUNÇÕES PARA LISTA DE CHAVES/CARACTERES*****************/

/*
 * Retorna 1 se a lista de caracteres esta vazia e 0 caso contrario.
 */
int lchar_vazia(lchar_t* l);

/*
 * Retorna o tamanho da lista de caracteres, isto eh, o numero de caracteres presentes nela.
 */
int lchar_tamanho(lchar_t* l);

/*
 * Insere o caractere no inicio da lista.
 * Retorna 1 se a operacao foi bem sucedida e 0 caso contrario.
 */
int lchar_insere_inicio(lchar_t* l, int caractere, int index);

/*
 * Remove o elemento do inicio da lista e o retorna em 'elemento'.
 * Retorna 1 se a operacao foi bem sucedida e 0 caso contrario.
 */

int lchar_retira_inicio(lchar_t* l, int* elemento);

/*
 * Insere o elemento na lista de caracteres garantindo ordenacao em ordem crescente.
 * Retorna 1 se a operacao foi bem sucedida e 0 caso contrario.
 */
int lchar_insere_ordenado(lchar_t* l, int caractere, int index);

/*
 * Retorna 1 se o caractere existe na lista e 0 caso contrario.
 */
int lchar_pertence(lchar_t* l, int caractere);

/**
 * Inclui o índice na chave, retorna 1 se
 * inserido com sucesso, 0 caso contrário
 */
int nchar_insere_indice(lchar_t* l, int caractere, int index);

/*
 * Imprime a lista de caracteres, do inicio ate o fim, este por ultimo, sem espaco no final.
 * Quando a lista de caracteres estiver vazia, nao imprime nada, nem um \n.
 * Esta funcao eh somente para facilitar teus testes.
 * Normalmente ela nao existe nas implementacoes de um TAD lista.
 */
void lchar_imprime(lchar_t* l);

#endif
