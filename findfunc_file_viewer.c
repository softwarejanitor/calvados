#include <gtk/gtk.h>
#include <gdk/gdkkeysyms.h>

#include "calvados.h"

/*
 *
 * findfunc_file_viewer()
 *
 * Find Function for file viewer image
 *
 * Show that the "Find" button was pressed
 *
 */
void findfunc_file_viewer(GtkWidget *widget, gpointer data)
{
  /* --- Display message --- */
  g_print("Find function for file viewer goes here.\n");

  /* --- Close it. --- */
  gtk_widget_destroy(GTK_WIDGET(data));

  /* Now open the find dialog */
/*FIXME*/
}

