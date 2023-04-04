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
FILE* cifrador(FILE* livroCifra);

/*
 * Insere chaves e atualiza índices se a chave já existir.
 * Retorna 1 se inserido com sucesso, 0 caso contrário.
 */
int setChave(lchar_t* l, int caractere, int indice);

/**
 * Exclui espaços e quebras de linha em sequência, texto todo em minúsculo.
 * Retorna um stream para o arquivo criado.
 */
FILE* normalizaTexto(FILE* texto);

/*
 * Retira os acentos do texto.
 */
void retiraAcento(FILE* livroCifra);

/**
 * Insere as chaves obtidas do texto.
*/
void insereChaves(FILE* livroCifra, lchar_t* listaChaves);

#endif