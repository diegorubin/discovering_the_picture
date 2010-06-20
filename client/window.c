/*
 * window.c
 *
 *  Created on: Jun 20, 2010
 *      Author: Diego Rubin
 */

#include "window.h"

/* Backing pixmap for drawing area */
static GdkPixmap *pixmap = NULL;

/* Create a new backing pixmap of the appropriate size */
static gboolean configure_event( GtkWidget         *widget,
                                 GdkEventConfigure *event )
{
  if (pixmap)
    g_object_unref (pixmap);

  pixmap = gdk_pixmap_new (widget->window,
			   widget->allocation.width,
			   widget->allocation.height,
			   -1);
  gdk_draw_rectangle (pixmap,
		      widget->style->white_gc,
		      TRUE,
		      0, 0,
		      widget->allocation.width,
		      widget->allocation.height);

  return TRUE;
}

/* Redraw the screen from the backing pixmap */
static gboolean expose_event( GtkWidget      *widget,
                              GdkEventExpose *event )
{
  gdk_draw_drawable (widget->window,
		     widget->style->fg_gc[gtk_widget_get_state (widget)],
		     pixmap,
		     event->area.x, event->area.y,
		     event->area.x, event->area.y,
		     event->area.width, event->area.height);

  return FALSE;
}

/* Draw a rectangle on the screen */
static void draw_brush( GtkWidget *widget,
                        gdouble    x,
                        gdouble    y)
{
  GdkRectangle update_rect;

  update_rect.x = x - 5;
  update_rect.y = y - 5;
  update_rect.width = 5;
  update_rect.height = 5;
  gdk_draw_rectangle (pixmap,
		      widget->style->black_gc,
		      TRUE,
		      update_rect.x, update_rect.y,
		      update_rect.width, update_rect.height);
  gtk_widget_queue_draw_area (widget,
		              update_rect.x, update_rect.y,
		              update_rect.width, update_rect.height);
}

static gboolean button_press_event( GtkWidget      *widget,
                                    GdkEventButton *event )
{
  if (event->button == 1 && pixmap != NULL)
    draw_brush (widget, event->x, event->y);

  return TRUE;
}

static gboolean motion_notify_event( GtkWidget *widget,
                                     GdkEventMotion *event )
{
  int x, y;
  GdkModifierType state;

  if (event->is_hint)
    gdk_window_get_pointer (event->window, &x, &y, &state);
  else
    {
      x = event->x;
      y = event->y;
      state = event->state;
    }

  if (state & GDK_BUTTON1_MASK && pixmap != NULL)
    draw_brush (widget, x, y);

  return TRUE;
}

GtkWidget *create_main_window()
{
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);

	/* configurações da janela */
	gtk_window_set_title(GTK_WINDOW(window), "Discovering The Picture");
	gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER_ALWAYS);
	gtk_window_set_default_size(GTK_WINDOW(window),900,700);

	/* configurações dos widgets */
	GtkWidget *table = gtk_table_new(5,2, FALSE);

	button_connect_server = gtk_button_new_with_label("Conectar ao Servidor");

	slate = gtk_drawing_area_new();
	gtk_drawing_area_size(GTK_DRAWING_AREA(slate),800,600);

	entry_message = gtk_entry_new();
	gtk_entry_set_width_chars(GTK_ENTRY(entry_message),30);
	gtk_entry_buffer_set_max_length(gtk_entry_get_buffer(GTK_ENTRY(entry_message)),254);

	h_separator = gtk_hseparator_new();

	gtk_table_attach(GTK_TABLE(table), button_connect_server, 1, 2, 0, 1,GTK_SHRINK,GTK_SHRINK,0,0);
	gtk_table_attach_defaults(GTK_TABLE(table), slate, 0, 2, 1, 2);
	gtk_table_attach(GTK_TABLE(table), h_separator, 0, 2, 2, 3,GTK_SHRINK,GTK_SHRINK,0,0);
	gtk_table_attach(GTK_TABLE(table), entry_message, 0, 2, 3, 4, GTK_EXPAND, GTK_SHRINK,0,5);


	gtk_container_add(GTK_CONTAINER(window), table);

	/* Signals used to handle backing pixmap */

	g_signal_connect (slate, "expose-event",
			    G_CALLBACK (expose_event), NULL);
	g_signal_connect (slate,"configure-event",
		    G_CALLBACK (configure_event), NULL);

	/* Event signals */

	g_signal_connect (slate, "motion-notify-event",
			    G_CALLBACK (motion_notify_event), NULL);
	g_signal_connect (slate, "button-press-event",
			    G_CALLBACK (button_press_event), NULL);

	gtk_widget_set_events (slate, GDK_EXPOSURE_MASK
				 | GDK_LEAVE_NOTIFY_MASK
				 | GDK_BUTTON_PRESS_MASK
				 | GDK_POINTER_MOTION_MASK
				 | GDK_POINTER_MOTION_HINT_MASK);

	/* signals connect */
	g_signal_connect(G_OBJECT(window), "delete_event", G_CALLBACK(program_quit),NULL);
	g_signal_connect(G_OBJECT(button_connect_server), "clicked", G_CALLBACK(button_connect_server_clicked), NULL);

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
}

void button_send_message_clicked(GtkWidget *widget, gpointer data)
{
}
