#include <gtk/gtk.h>
#include <gdk/gdkkeysyms.h>

#include "calvados.h"

/*
 *
 * help_func_add_files()
 *
 * Help Function for add files
 *
 * Show that the "Help" button was pressed
 *
 */
void help_func_add_files(GtkWidget *widget, gpointer data)
{
  /* --- Display message --- */
  g_print("Help function for add files goes here.\n");

  /* --- Close it. --- */
  gtk_widget_destroy(GTK_WIDGET(data));

  /* Now open the help dialog */
/*FIXME*/
}

