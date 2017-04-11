#include <gtk/gtk.h>
#include <gdk/gdkkeysyms.h>

#include "calvados.h"

/*
 *
 * donefunc_file_viewer()
 *
 * Done Function for file viewer
 *
 * Show that the "Done" button was pressed
 *
 */
void donefunc_file_viewer(GtkWidget *widget, gpointer data)
{
  /* --- Display message --- */
  g_print("File viewer done function goes here.\n");

  /* --- Close it. --- */
  gtk_widget_destroy(GTK_WIDGET(data));
}

