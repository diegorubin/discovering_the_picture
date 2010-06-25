#ifndef BIDICHAT_H_
#define BIDICHAT_H_

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

int setup_client(const char *host, int port);

#endif /* BIDICHAT_H_ */
