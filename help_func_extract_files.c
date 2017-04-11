#include <gtk/gtk.h>
#include <gdk/gdkkeysyms.h>

#include "calvados.h"

/*
 *
 * help_func_extract_files()
 *
 * Help Function for extract files
 *
 * Show that the "Help" button was pressed
 *
 */
void help_func_extract_files(GtkWidget *widget, gpointer data)
{
  /* --- Display message --- */
  g_print("Help function for extract files goes here.\n");

  /* --- Close it. --- */
  gtk_widget_destroy(GTK_WIDGET(data));

  /* Now open the help dialog */
/* FIXME*/
}

