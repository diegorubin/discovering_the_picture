#ifndef COMMON_H_
#define COMMON_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <poll.h>
#include <gtk/gtk.h>
#include "util.h"

#define MAX_WIDTH 800
#define MAX_HEIGHT 600

typedef struct message message_t;

int setup_client(const char *host, int port);
int setup_server(const struct sockaddr_in *address);

/* Estrutura das mensagens trocadas */
struct message {
    char nickname[100];
	int x;
	int y;
};

#endif /* COMMON_H_ */
