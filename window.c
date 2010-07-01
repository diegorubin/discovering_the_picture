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
  int x = event->x;
  int y = event->y;
  if (event->button == 1 && pixmap != NULL){
	  send_point(x,y);
	  draw_brush(slate,x,y);
  }
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
      x = (int) event->x;
      y = (int) event->y;
      state = event->state;
    }

  if (state & GDK_BUTTON1_MASK && pixmap != NULL && x >= 0 && y >= 0 && x <= MAX_WIDTH && y <= MAX_HEIGHT){
	draw_brush(slate,x,y);
	send_point(x,y);
  }

  return TRUE;
}

GtkWidget *create_main_window()
{
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);

	/* configurações da janela */
	gtk_window_set_title(GTK_WINDOW(window), "Discovering The Picture");
	gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER_ALWAYS);
	gtk_window_set_default_size(GTK_WINDOW(window),800,600);
	gtk_window_set_resizable(GTK_WINDOW(window), FALSE);

	/* configurações dos widgets */
	GtkWidget *table = gtk_table_new(5,2, FALSE);

	button_connect_server = gtk_button_new_with_label("Conectar ao Servidor");

	slate = gtk_drawing_area_new();
	gtk_drawing_area_size(GTK_DRAWING_AREA(slate),800,600);

	label_nickname = gtk_label_new("Ultimo ponto feito por:");

	h_separator = gtk_hseparator_new();

	gtk_table_attach(GTK_TABLE(table), button_connect_server, 1, 2, 0, 1,GTK_SHRINK,GTK_SHRINK,0,0);
	gtk_table_attach_defaults(GTK_TABLE(table), slate, 0, 2, 1, 2);
	gtk_table_attach(GTK_TABLE(table), h_separator, 0, 2, 2, 3,GTK_SHRINK,GTK_SHRINK,0,0);
	gtk_table_attach(GTK_TABLE(table), label_nickname, 0, 2, 3, 4, GTK_EXPAND, GTK_SHRINK,0,5);


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

	activesocket = -1;

	return window;
}

void main_poll(){
    while(1){
		while (gtk_events_pending ())
			gtk_main_iteration();
		struct pollfd pfds[2];

		//descritor de um arquivo de buffer que sera alimentado pela interface.
		pfds[0].fd = activesocket;
		pfds[0].events = POLLIN;

		poll(pfds, 1, 5);

		if(pfds[0].revents != 0){
		   char buffer[8192];
		        
            int r = recv(activesocket,buffer, sizeof(buffer),0);
            if(r > 0){
               message_t *received = (message_t*) &buffer ;
               draw_brush(slate,received->x, received->y);
               set_last_client(received->nickname);
		    }
		}

	}
}

void set_last_client(char client[100]){
  
  char label[200] = "Ultimo ponto feito por: \0";
  strcat(label,client);
  
  gtk_label_set_text(GTK_LABEL(label_nickname),label);
}

void send_point(int x, int y)
{
    message_t new;
    new.x = x;
    new.y = y;
    strcpy(new.nickname,nickname);
    send(activesocket, (char *)&new, sizeof(new), 0);
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
	}
}

