/*
 * main.c
 *
 *  Created on: Jun 20, 2010
 *      Author: Diego Rubin
 */

#include "common.h"

int clients[9];
int last_client;

void initialize_clients(){
    int i;
    for(i = 0;i <= 9; i++)
        clients[i] = 0;
}

void send_others(int owner, message_t new){
    int i;
    for(i = 0; i <= last_client; i++)
        if(i != owner)
            send(clients[i], (char *)&new, sizeof(new), 0);
    
}

int main(int argc, char **argv){
	
	int i;
	int port = 9090;
    last_client = 0;
    
    initialize_clients();
    
	struct sockaddr_in local = { AF_INET };
	local.sin_addr.s_addr = htonl(INADDR_ANY);
	local.sin_port = htons(port);

	int socket = setup_server(&local);

	if (listen(socket,10) < 0)
		fatal("Erro na escuta do servidor.");

	for (;;) {

		struct pollfd pfds[10];
	

		pfds[0].fd = socket;
		pfds[0].events = POLLIN;
		
		poll(pfds, 10, -1);

	    //nova conexao
		if (pfds[0].revents != 0) {
		    printf("nova conexao de client.\n");
		    clients[last_client] = accept(socket,NULL,NULL);
		    		    
		    pfds[last_client+1].fd = clients[last_client];
		    pfds[last_client+1].events = POLLIN;
		    
		    last_client++;
		}
		
		//recebendo do cliente
		for(i = 1; i <= 10; i++){
		    if (pfds[i].revents != 0) {
		        char buffer[8192];
		        
		        int r = recv(clients[i-1],buffer, sizeof(buffer),0);
		        if(r > 0){
		           message_t *received = (message_t*) &buffer ;
		           printf("recebido informacao de client.\n");
		           send_others(i-1, *received);
		         }
		    }
		}
		
	}

	return 0;
}
