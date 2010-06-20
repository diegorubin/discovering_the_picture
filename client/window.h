/*
 * window.h
 *
 *  Created on: Jun 20, 2010
 *      Author: Diego Rubin
 */

#ifndef WINDOW_H_
#define WINDOW_H_

#include <gtk/gtk.h>

GtkWidget *window;
GtkWidget *create_main_window();

/* Widgets da Janela */
/* buttons */
GtkWidget *button_connect_server;

/* text view */
GtkWidget *slate;
GtkWidget *entry_message;

/* separator */
GtkWidget *h_separator;

/* Callbacks */
gboolean program_quit(GtkWidget *widget, GdkEvent *event, gpointer data);
void button_connect_server_clicked(GtkWidget *widget, gpointer data);
void button_send_message_clicked(GtkWidget *widget, gpointer data);


#endif /* WINDOW_H_ */
