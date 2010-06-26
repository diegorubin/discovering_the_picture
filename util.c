/******************************************************************************
 * bidichat - C                                                               *
 * Exemplo de comunicação bidirecional sobre soquetes Internet                *
 ******************************************************************************
 * Autor: Juliano F. Ravasi                                                   *
 * Sistemas Operacionais II - Bacharelado em Ciência da Computação            *
 * Universidade Estadual Paulista, UNESP - Rio Claro                          *
 ******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "util.h"

/**
 * Função para reportar erros de erros, via va_list.
 *
 * @param msg String com formatação estilo printf().
 * @param args Ponteiro para vetor de argumentos.
 */
void
verror(const char *msg, va_list args)
{
	char buffer[8192];
	vsnprintf(buffer, sizeof buffer, msg, args);
	fprintf(stderr, "%s\n", buffer);
}

/**
 * Função para reportar erros de erros genéricos.
 *
 * @param msg String com formatação estilo printf().
 */
void
error(const char *msg, ...)
{
	va_list args;
	va_start(args, msg);
	verror(msg, args);
	va_end(args);
}

/**
 * Função para reportar erros de erros fatais. Termina a execução do programa.
 *
 * @param msg String com formatação estilo printf().
 */
void
fatal(const char *msg, ...)
{
	va_list args;
	va_start(args, msg);
	verror(msg, args);
	va_end(args);
	exit(EXIT_FAILURE);
}

/**
 * Elimina caracteres de espaço no final de uma string.
 *
 * @param str String a ser tratada.
 * @return String tratada.
 */
char *
chop(char *str)
{
	for (int l = strlen(str) - 1; l >= 0 && isspace(str[l]); l--)
		str[l] = 0;
	return str;
}
