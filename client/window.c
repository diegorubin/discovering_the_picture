/*
 * window.c
 *
 *  Created on: Jun 20, 2010
 *      Author: Diego Rubin
 */

#include "window.h"

extern int activesocket;

GtkWidget *create_main_window()
{
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);

	/* configurações da janela */
	gtk_window_set_title(GTK_WINDOW(window), "gBidiChat");
	gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER_ALWAYS);
	gtk_window_set_default_size(GTK_WINDOW(window),150,400);

	/* configurações dos widgets */
	GtkWidget *table = gtk_table_new(5,2, FALSE);

	button_start_server = gtk_button_new_with_label("Start Server");
	button_connect_server = gtk_button_new_with_label("Conectar ao Servidor");
	button_send_message = gtk_button_new_with_mnemonic("_Enviar Mensagem");

	GtkAdjustment *adjustment = gtk_adjustment_new(0,0,0,0,0,0);
	GtkWidget *scrolled_window = gtk_scrolled_window_new(adjustment,adjustment);

	text_chat = gtk_text_view_new();
	gtk_container_add(GTK_CONTAINER(scrolled_window),text_chat);
	gtk_text_view_set_editable(GTK_TEXT_VIEW(text_chat),FALSE);

	entry_message = gtk_entry_new();
	gtk_entry_set_width_chars(GTK_ENTRY(entry_message),30);
	gtk_entry_buffer_set_max_length(gtk_entry_get_buffer(GTK_ENTRY(entry_message)),254);

	h_separator = gtk_hseparator_new();

	gtk_table_attach(GTK_TABLE(table), button_start_server, 0, 1, 0, 1,GTK_SHRINK,GTK_SHRINK,0,0);
	gtk_table_attach(GTK_TABLE(table), button_connect_server, 1, 2, 0, 1,GTK_SHRINK,GTK_SHRINK,0,0);
	gtk_table_attach_defaults(GTK_TABLE(table), scrolled_window, 0, 2, 1, 2);
	gtk_table_attach(GTK_TABLE(table), h_separator, 0, 2, 2, 3,GTK_SHRINK,GTK_SHRINK,0,0);
	gtk_table_attach(GTK_TABLE(table), entry_message, 0, 2, 3, 4, GTK_EXPAND, GTK_SHRINK,0,5);
	gtk_table_attach(GTK_TABLE(table), button_send_message, 1, 2, 4, 5,GTK_SHRINK,GTK_SHRINK,0,0);


	gtk_container_add(GTK_CONTAINER(window), table);

	/* signals connect */
	g_signal_connect(G_OBJECT(window), "delete_event", G_CALLBACK(program_quit),NULL);
	g_signal_connect(G_OBJECT(button_start_server), "clicked", G_CALLBACK(button_start_server_clicked), NULL);
	g_signal_connect(G_OBJECT(button_connect_server), "clicked", G_CALLBACK(button_connect_server_clicked), NULL);
	g_signal_connect(G_OBJECT(button_send_message), "clicked", G_CALLBACK(button_send_message_clicked), NULL);

	return window;
}

/* Implementacao dos callbacks */

gboolean program_quit(GtkWidget *widget, GdkEvent *event, gpointer data)
{
	gtk_main_quit();
	return TRUE;
}

void button_connect_server_clicked(GtkWidget *widget, gpointer data)
{
	if((activesocket = dialog_connect_server_show(GTK_WINDOW(window))) > 0){
		gtk_widget_hide(button_connect_server);
		gtk_widget_hide(button_start_server);
		chat("Diego");
	}
}

void button_send_message_clicked(GtkWidget *widget, gpointer data)
{
	char message[1024] = "Diego: ";
	strcat(message, gtk_entry_get_text(GTK_ENTRY(entry_message)));
	strcat(message,"\n");
	GtkTextBuffer *buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(text_chat));
	gtk_text_buffer_insert_at_cursor(buffer,message,-1);
}
