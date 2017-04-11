#include <gtk/gtk.h>
#include <gdk/gdkkeysyms.h>

#include "calvados.h"

/*
 *
 * help_func_file_viewer()
 *
 * Help Function for file viewer image
 *
 * Show that the "Help" button was pressed
 *
 */
void help_func_file_viewer(GtkWidget *widget, gpointer data)
{
  /* --- Display message --- */
  g_print("Help function for file viewer goes here.\n");

  /* --- Close it. --- */
  gtk_widget_destroy(GTK_WIDGET(data));

  /* Now open the help dialog */
/*FIXME*/
}

