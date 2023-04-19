# Cifras-de-Beale
Feito como um trabalho para a disciplina Programação II, o Cifras-de-Beale consiste em um programa e criptografa e descriptografa textos com base nas Cifras de Beale

GRR20211774
Matheus Telles Batista

Structs:

Struct args_t 


	struct argumentos {
	int eFlag; /* flag da opt e (encode) */
	int dFlag; /* flag da opt d (decode) */
	int oFlag; /* flag da opt o (MensagemCodificada/MensagemDecodificada) */
	int bFlag; /* flag da opt b (LivroCifra) */
	int cFlag; /* flag da opt c (ArquivoDeChaves) */
	int mFlag; /* flag da opt m (Mensagem) */
	int iFlag; /* flag da opt i (MensagemCodificada) */

	char *strOutput;   /*string do argumento -o */
	char *strBook;     /*string do argumento -b */
	char *strChave;    /*string do argumento -c */
	char *strMensagem; /*string do argumento -m */
	char *strInput;    /*string do argumento -i */

	FILE *output;   /* arquivo output  */
	FILE *book;     /* arquivo book  */
	FILE *chave;    /* arquivo chave  */
	FILE *mensagem; /* arquivo mensagem  */
	FILE *input;    /* arquivo input */

	};
	typedef struct argumentos args_t;

Essa estrutura guarda todos os argumentos e arquivos necessários, é usado para inserção dos arquivos, alteração de flags e criação de streams para os arquivos.


Caso haja erro em alguma execução, seja de qualquer tipo, é limpado da memória todas as flags, argumentos e streams.
O projeto também verifica algumas incosistências em opções, como:

-alguém tentar decodificar e codificar ao mesmo tempo;

-esquecer de inserir a opção i em um decode;

-esquecer de inserir a opção -m em um encode.


Todos os casos listados estão em args.c (comentados a cada if).



Struct nchar_l_t

	struct nchar_l {
		int elemento;         /* lista de numeros inteiros */
		struct lista *lista;  /* ponteiro para a lista de indices*/
		struct nchar_l *prox; /* ponteiro para o proximo caractere */
	};
	typedef struct nchar_l nchar_l_t;


Sobre os componentes/membros:

O elemento é usado para guardar um caractere e a lista para guardar os índices.


O prox aponta para o próximo nchar_l_t, podendo ser um nodo de CARACTERE ou de ÍNDICE


O nodo de CARACTERE (nchar_l_t) é usado na criação do arquivo de chaves, contendo uma lista de ÍNDICES.

Algo como isso:

a: 98 94 72

c: 79 70 

d: 95 92 80 67 64 61 58 56 46 36 33 20 18 7

Cada índice é usado na codificação/decodificação das mensagens.



Struct lchar_t


    /**
     *Struct da lista contendo os caracteres
    */
        struct list_char {
	    nchar_l_t *ini; /* ponteiro para o inicio da lista */
	    int tamanho;    /* numero de elementos na lista    */
    };
    typedef struct list_char lchar_t;

Essa struct lchar_t foi usada para guardar índices ({nodo, nodo, nodo, ...}), uma lista simples ligada;



Struct nodo_l_t

	struct nodo_l {
		int elemento;        /* lista de numeros inteiros */
		struct nodo_l *prox; /* ponteiro para o proximo   */
	};
	typedef struct nodo_l nodo_l_t;


Essa struct nodo_l_t foi usada para os próprios índices, um nodo simples de uma lista simples ligada;




Struct lista_t

	struct lista {
		nodo_l_t *ini; /* ponteiro para o inicio da lista */
		int tamanho;   /* numero de elementos na lista    */
	};
	typedef struct lista lista_t;

Lista básica para concatenar elementos em sequência, sendo o ini o início e o tamanho autoexplicativo.




Struct nodo_index_t

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

Struct do nodo índice (nodo_index_t). Cada nodo contém um índice e um respectivo caractere, além disso, o nodo participa de uma árvore red-black, tendo a cor vermelha(1) ou preta(0). Será usado para criar uma estrutura autobalanceável que facilita a captura do índice com seu respectivo caractere. 


Escolhido pois possui uma complexidade baixa e pior caso = melhor caso, além de ser necessário apenas a inserção do mesmo.

Encoder/Codificador:

    ./beale  -e  -b LivroCifra -m MensagemOriginal -o MensagemCodificada 
	./beale  -e  -b LivroCifra -m MensagemOriginal -o MensagemCodificada -c ArquivoDeChaves 

O funcionamento do decifrador segue o seguinte raciocínio:


Como precisamos do índice de palavras, usamos um iterador dentro do LivroCifra que só é incrementado com um fscanf(), ou seja, apenas após ' ' ou '\n' se é incrementado o i. O caractere será obrigatoriamente minúsculo. É inserido o caractere e seu índice pelas condicionais logo após.

OBS: como foi enviado um arquivo .txt que possuía acentos de exemplo como LivroCifra, o trabalho atual foi optado por trabalhar com wchar, por isso as funções fscanf() que serão apresentadas normalmente recebem  vetores de wchar.

(cifrador.c - Função criaChaves(), linha 6)

	for(i = 0; fscanf(livroCifra, "%ls", palavra) != EOF; i++) {
		caractere = palavra[0];
		caractere = towlower(caractere);

		// Insere o caractere e o índice na lista.
		if(lchar_insere(listaChaves, caractere, i) == 0)
			return 0;
	}


(libLIstaChar.c - Função int lchar_insere(), linha 269)

    int lchar_insere(lchar_t *l, int caractere, int index) {
    	if(lchar_pertence(l, caractere))
    		return nchar_insere_indice(l, caractere, index);
    	return lchar_insere_ordenado(l, caractere, index);
    }

Essa função realiza o necessário para inserção do caractere na lista de chaves (lchar_t). Segue o seguinte raciocínio:

1: Se o caractere já está inserido, realiza a inserção do indice apenas;

2: Caso não esteja inserido, insere-se ordenadamente o caractere.


A maioria das funções interiores das listas (listaChar, lista) não são tão importantes serem explicadas devido a ser um assunto já abordado na disciplina de Prog I. 

obs: Se foi especificado um arquivo de chaves pela opção -c, será escrito o conteúdo das chaves pela função lchar_escreve(FILE* arq, lchar_t l), que recebe o arquivo que será escrito e a lista;

Após a criação da lista, é feito a leitura letra por letra e uma troca por um índice de seu respectivo caractere escolhido aleatoriamente. A troca é feito pela função trocar().

(cifrador.c - Função trocar(), linha 31)

	
    int trocar(FILE *mensagem, FILE *output, lchar_t *l) {
	    srand(time(NULL));
	    nchar_l_t *aux;
		wint_t caractere;
		int i = 0, index;

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
	    		} else {
	    			index = lista_busca(aux->lista, rand() % (aux->lista->tamanho));
	    		}
	    	}
		    // Insere o índice.
		    fprintf(output, "%d ", index);
    	}
        
	    return 1;
    }


Os casos especiais são -1, -2 e -3: 

-1 - Espaço encontrado;

-2 - Valor não consta no livro cifra (Trocado por @ no encoder);

-3 - Quebra de linha.


O código avança caractere por caractere e, caso não seja nenhum dos três casos especiais, o encontra.
Após encontrado, busca-se um valor aleatório que está contido dentro da lista de índices do caractere achado. Esse valor é inserido na stream output.

Decifrador:

    ./beale -d -i MensagemCodificada -c ArquivoDeChaves -o MensagemDecodificada 
    ./beale -d -i MensagemCodificada -b LivroCifra -o MensagemDecodificada 
    
É possível duas opções de decodificação, ler pelo livro cifra ou pelo arquivo de chaves. Em contrapartida elas montam a mesma árvore red-black (rubro-negra). O que faciltia a utilização de apenas um comando para realizar a troca de caracteres na decodificação.

O tratamento dos casos especiais (-1, -2, -3) é realizado com a inserção dos valores de -1 e -3 em uma  árvore rubro negra.
Como o valor -2 não será achado em srchIndex(raiz, valor), apenas é retornado um '@' quando atingir alguma folha.

Exemplo: A cifra 

"16988 9629 11614 7233 9556 15301 4126 5900 -2 -1" 

decodificada se torna: "sunshine@ "

Pelo livro cifra:


Como é preciso capturar os índices e verificar o seu respectivo caractere, uma solução rápida seria concatenar as listas e procurar o índice, mas para livros cifra com quantidades grandes de palavras isso não é uma opção razoável em termos de processamento. Foi optado no projeto a implementação de uma árvore red-black que possui complexidade O(log n), e é autobalanceável, que facilita a inserção rápida.


Então primeiro monta-se uma árvore rubro negra, criando nodos_index_t a cada passe de palavra, até o final do livro cifra.



A criação da árvore red-black usando o um livro cifra ocorre pelo seguinte algorítmo em C:

função decode(livroCifra, input, output, chaves), linha 118

	for(i = 0; fscanf(livroCifra, "%ls", palavra) != EOF; i++) {
		caractere = palavra[0];
		caractere = iswupper(caractere) ? towlower(caractere) : caractere;
		insere_redblack(&raiz, caractere, i);
	}

	
Cria-se a árvore com todos os índices e caracteres e a partir deste ponto apenas é necessário fazer a busca do índice encontrado no livro.


Pelo arquivo de chaves: 

Nessa situação, o mesmo é necesśario: implementar uma árvore rubro-negra.
    
Para a captura do arquivo chave-valor foi usado um leitor que verifica se o segundo caractere que foi capturado (palavra[1]) é um ':', pois o arquivo mantém os dados nessa lógica "chave: {valor1, valor2, ...}", logo palavra[0] = chave. Caso contrário, é valor.

Após o valor que era wchar* ser convertido para int, é inserido o valor na árvore.

função decode(livroCifra, input, output, chaves), linha 101

	
	if(chaves) {
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
	
Note-se que é necessário que seja inserido no bloco else{} pois é pelos valores/índices que o texto será codificado.

A decodificação é realizada realmente por duas linhas, que itera o arquivo codificado (input) e a cada valor encontrado, insere o caractere correspondente na árvore rubro-negra.

(cifrador.c - função decode(), linha 127)

	while(fscanf(input, "%d", &valor) != EOF)
		fprintf(output, "%lc", srchIndex(raiz, valor));


Caso tenha dúvidas sobre srchIndex, função que busca em uma árvore de busca binário algum valor.

(libRedBlack.c - função srchIndex(), linha 191)


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
