/*
 * dialog_connect_server.h
 *
 *  Created on: Jun 25, 2010
 *      Author: Diego Rubin
 */
#include "common.h"

int setup_client(const char *host, int port)
{
	int clientsock;

	struct sockaddr_in server = { AF_INET };

	if (inet_pton(AF_INET, host, &server.sin_addr) <= 0)
		fatal("Falhou ao interpretar o endereço IP.");

	server.sin_port = htons(port);

	clientsock = socket(PF_INET, SOCK_STREAM, 0);
	if(clientsock < 0 )
		fatal("Erro na criação do socket cliente.");

	if (connect(clientsock,(struct sockaddr*) &server, sizeof(server)) < 0)
		fatal("Erro ao conectar com o servidor");

	printf("*** Conexão estabelecida.\n");
	return clientsock;
}

int setup_server(const struct sockaddr_in *address)
{

	int serversock = socket(PF_INET, SOCK_STREAM, 0);
	if(serversock < 0 )
		fatal("Erro ao criar socket do servidor.");
		
	if (bind(serversock,(struct sockaddr*) address, sizeof(*address)) < 0)
		fatal("Erro na criação da porta.");
	
	return serversock;
}
