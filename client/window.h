/*
 * window.h
 *
 *  Created on: Jun 20, 2010
 *      Author: Diego Rubin
 */

#ifndef WINDOW_H_
#define WINDOW_H_

#define MAX_WIDTH 800
#define MAX_HEIGHT 600

#include <gtk/gtk.h>
#include "dialog_connect_server.h"

GtkWidget *window;
GtkWidget *create_main_window();

/* Widgets da Janela */
/* buttons */
GtkWidget *button_connect_server;

GtkWidget *slate;
GtkWidget *entry_message;

char map[MAX_WIDTH][MAX_HEIGHT];
static int activesocket;

/* separator */
GtkWidget *h_separator;

/* Methods */
void initialize_map(char m[MAX_WIDTH][MAX_HEIGHT]);
void draw_map(char m[MAX_WIDTH][MAX_HEIGHT]);

/* Callbacks */
gboolean program_quit(GtkWidget *widget, GdkEvent *event, gpointer data);
void button_connect_server_clicked(GtkWidget *widget, gpointer data);
void button_send_message_clicked(GtkWidget *widget, gpointer data);


#endif /* WINDOW_H_ */
