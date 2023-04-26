#include "cifrador.h"

#include "libListaChar.h"
#include "libRedBlack.h"

int criaChaves(FILE *livroCifra, lchar_t *listaChaves) {
	// Tamanho 1024 devido a alguma palavra estar ligada a outro caractere e poder estourar a memória.
	wchar_t palavra[1024];
	int caractere, i;

	// Lê até encontrar palavra por palavra e captura o primeiro caractere
	for(i = 0; fscanf(livroCifra, "%ls", palavra) != EOF; i++) {
		caractere = palavra[0];
		caractere = towlower(caractere);

		// Insere o caractere e o índice na lista.
		if(lchar_insere(listaChaves, caractere, i) == 0)
			return 0;
	}

	return 1;
}

int trocar(FILE *mensagem, FILE *output, lchar_t *l) {
	srand(time(NULL));
	nchar_l_t *aux;
	wint_t caractere;
	int i = 0, index;

	// Flag que indica se há algum caractere no texto original que não está na lista de chaves
	int nullCharFlag = 0;

	// lê até encontrar ' ', '\t' ou  '\n'
	while((caractere = towlower(fgetwc(mensagem))) != EOF) {
		// Se for quebra de linha, índice = -3
		if((caractere) == '\n')
			index = -3;
		// Se for espaço, índice =-1
		else if(caractere == ' ')
			index = -1;
		else {
			// Itera até achar o caractere na lista.
			for(i = 0, aux = l->ini; ((i < l->tamanho) && (caractere != aux->elemento)); i++) {
				aux = aux->prox;
			}
			// Realiza a busca de um índice aleatório da lista e o retorna, caso contrário retorna -2.
			if(!aux) {
				// Caso o livro cifra não cubra todos os casos de caracteres, se insere um -2 no lugar do caractere.
				index = -2;
				nullCharFlag = 1;
			} else {
				index = lista_busca(aux->lista, rand() % (aux->lista->tamanho));
			}
		}
		// Insere o índice.
		fprintf(output, "%d ", index);
	}

	// Se não há um caractere do livro cifra que represente algum caractere da mensagem, haverá um aviso indicando isso.
	if(nullCharFlag == 1)
		printf("AVISO: Há caracteres no texto original que não foram achados no texto codificado. Há -2 no output.\n");
	return 1;
}

FILE *encode(FILE *livroCifra, FILE *mensagem, FILE *output, FILE *chaves) {
	lchar_t *listaChar = NULL;

	/* Cria a lista necessária para guardar as chaves */
	if(!(listaChar = lchar_cria())) {
		fprintf(stderr, "ERRO: %s", "Falha ao criar lista de chaves.\n");
		return NULL;
	}

	// Insere as chaves na struct lchar
	if(criaChaves(livroCifra, listaChar) == 0) {
		fprintf(stderr, "ERRO: %s", "Falha ao criar lista de chaves.\n");
		return NULL;
	}

	/**
	 * Se existe o arquivo de chaves, a opção -c foi acionada.
	 * A lista de caracteres é escrito no arquivo.
	 */
	if(chaves)
		lchar_escreve(chaves, listaChar);

	// Realiza a codificação.
	trocar(mensagem, output, listaChar);

	lchar_destroi(listaChar);
	return output;
}


FILE *decode(FILE *livroCifra, FILE *input, FILE *output, FILE *chaves) {
	wchar_t palavra[1024];
	nodo_index_t *raiz = NULL;
	int valor;
	int caractere = 0, i = 0;
	int charNullFlag  = 0;

	// A árvore irá usar -3 como \n
	insere_redblack(&raiz, 10, -3);

	// A árvore irá usar -1 como espaço
	insere_redblack(&raiz, 32, -1);

	// Opção -c (Utilziando um Arquivo de Chaves)
	if(chaves) {
		// Captura-se a chave/índice a cada iteração
		while(fscanf(chaves, "%ls", palavra) != EOF) {
			// Captura da chave/caractere:
			if(palavra[1] == ':') {
				caractere = palavra[0];
			}
			// Captura do valor/índice
			else {
				i = wcstol(palavra, 0, 10);
				insere_redblack(&raiz, caractere, i);
			}
		}
	}
	// Opção -b (utilizando um Livro Cifra)
	else {
		// Lê todas as primeiras letras, e insere na árvore. cada iteração aumenta o índice
		for(i = 0; fscanf(livroCifra, "%ls", palavra) != EOF; i++) {
			caractere = palavra[0];
			caractere = iswupper(caractere) ? towlower(caractere) : caractere;
			// Insere o caractere na árvore
			insere_redblack(&raiz, caractere, i);
		}
	}

	// Captura-se os valores do arquivo encriptado e escreve seu respectivo caractere no output a cada iteração.
	while(fscanf(input, "%d", &valor) != EOF){
		if(valor == -2)
			charNullFlag = 1;
		fprintf(output, "%lc", srchIndex(raiz, valor));
	}

	// Avisa se há caracteres que não foram encontrados e substituídos no output
	if(charNullFlag == 1){
		printf("\nAVISO: Há caracteres no texto original que não foram achados no texto codificado. Há '@' no output.\n\n");
	}
	destroi(raiz);

	return output;
}