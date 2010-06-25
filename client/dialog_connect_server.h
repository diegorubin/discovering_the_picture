/*
 * dialog_connect_server.h
 *
 *  Created on: May 30, 2010
 *      Author: diego
 */

#ifndef DIALOG_CONNECT_SERVER_H_
#define DIALOG_CONNECT_SERVER_H_

#include <gtk/gtk.h>
#include "common.h"

GtkWidget *dialog;
GtkWidget *entry_host;
GtkWidget *entry_port;

int dialog_start_server_show(GtkWindow *parent);
void dialog_connect_server_response(GtkWidget *widet, gpointer data);

#endif /* DIALOG_CONNECT_SERVER_H_ */
