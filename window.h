/*
 * window.h
 *
 *  Created on: Jun 20, 2010
 *      Author: Diego Rubin
 */

#ifndef WINDOW_H_
#define WINDOW_H_

#include <gtk/gtk.h>
#include "common.h"
#include "dialog_connect_server.h"

GtkWidget *window;
GtkWidget *create_main_window();

/* Widgets da Janela */
/* buttons */
GtkWidget *button_connect_server;

GtkWidget *slate;
GtkWidget *label_nickname;

char nickname[100];
int activesocket;

/* separator */
GtkWidget *h_separator;

/* Methods */
void initialize_map(char m[MAX_WIDTH][MAX_HEIGHT]);
void send_point(int x,int y);
void set_last_client(char client[100]);

/* Callbacks */
gboolean program_quit(GtkWidget *widget, GdkEvent *event, gpointer data);
void button_connect_server_clicked(GtkWidget *widget, gpointer data);


#endif /* WINDOW_H_ */
