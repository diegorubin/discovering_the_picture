/*
 * main.c
 *
 *  Created on: Jun 20, 2010
 *      Author: Diego Rubin
 */

#include <gtk/gtk.h>

#include "window.h"

int main(int argc, char *argv[])
{
	gtk_init(&argc,&argv);
	int i;
	i =1;

	GtkWidget *main_window;
	main_window = create_main_window();

	gtk_widget_show_all(main_window);
	main_poll();
	gtk_main();

	return 0;
}
