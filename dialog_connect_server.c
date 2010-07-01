/*
 * dialog_connect_server.c
 *
 *  Created on: May 30, 2010
 *      Author: diego
 *
 *  Implementação do dialogo de conexão com o server.
 *
 */

#include "dialog_connect_server.h"

const char *server_host;
int server_port = 0;

extern char nickname[100];

int dialog_connect_server_show(GtkWindow *parent)
{
	int socket = 0;

	dialog = gtk_dialog_new_with_buttons("Informe a porta",
					parent,
					GTK_DIALOG_DESTROY_WITH_PARENT,
					GTK_STOCK_OK,
					GTK_RESPONSE_ACCEPT,
					NULL);
	GtkWidget *label_nickname = gtk_label_new("Apelido:");
	GtkWidget *label_host = gtk_label_new("Servidor:");
	GtkWidget *label_port = gtk_label_new("Porta:");

	entry_nickname = gtk_entry_new();
	gtk_entry_set_text(GTK_ENTRY(entry_nickname),"anonimo");
	entry_host = gtk_entry_new();
	gtk_entry_set_text(GTK_ENTRY(entry_host),"127.0.0.1");
	entry_port = gtk_entry_new();
	gtk_entry_set_text(GTK_ENTRY(entry_port),"9090");

	GtkWidget *table = gtk_table_new(2,4,FALSE);
	gtk_table_attach_defaults(GTK_TABLE(table),label_host,0,1,0,1);
	gtk_table_attach_defaults(GTK_TABLE(table),entry_host,1,2,0,1);
	gtk_table_attach_defaults(GTK_TABLE(table),label_port,2,3,0,1);
	gtk_table_attach_defaults(GTK_TABLE(table),entry_port,3,4,0,1);
	gtk_table_attach_defaults(GTK_TABLE(table),label_nickname,2,3,1,2);
	gtk_table_attach_defaults(GTK_TABLE(table),entry_nickname,3,4,1,2);

	g_signal_connect(dialog, "response", G_CALLBACK(dialog_connect_server_response), dialog);

	gtk_container_add(GTK_CONTAINER(gtk_dialog_get_content_area(GTK_DIALOG(dialog))),table);

	gtk_widget_show_all(dialog);
	gint result = gtk_dialog_run(GTK_DIALOG(dialog));

	if(result == GTK_RESPONSE_ACCEPT){
		socket = setup_client(server_host, server_port);
	}
	gtk_widget_destroy(dialog);
	return socket;
}

void dialog_connect_server_response(GtkWidget *widet, gpointer data)
{
	server_host = gtk_entry_get_text(GTK_ENTRY(entry_host));
	server_port = atoi(gtk_entry_get_text(GTK_ENTRY(entry_port)));
	strcpy(nickname,gtk_entry_get_text(GTK_ENTRY(entry_nickname)));
	gtk_dialog_set_response_sensitive(GTK_DIALOG(dialog), GTK_RESPONSE_ACCEPT, TRUE);
}
