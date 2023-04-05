#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>

#include "liblista.h"

#ifndef _CIFRADOR_H_
#define _CIFRADOR_H_

/* FUNÇÕES DO CIFRADOR */
/*
    Cria um arquivo com as chaves dadas pelo livroCifra
*/
FILE *cifrador(FILE *livroCifra);

/*
 * Insere chaves e atualiza índices se a chave já existir.
 * Retorna 1 se inserido com sucesso, 0 caso contrário.
 */
int setChave(lchar_t *l, int caractere, int indice);

/**
 * Insere as chaves obtidas do texto. Retorna com sucesso o arquivo ou NULL caso contrário.
 */
FILE* insereChaves(FILE *texto, lchar_t *listaChaves);

#endif