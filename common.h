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

int setup_client(const char *host, int port);
int setup_server(const struct sockaddr_in *address);

struct message {
	char map[MAX_WIDTH][MAX_HEIGHT];
};

#endif /* COMMON_H_ */
