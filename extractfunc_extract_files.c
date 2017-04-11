#include <gtk/gtk.h>
#include <gdk/gdkkeysyms.h>

#include "calvados.h"

/*
 *
 * extractunc_extract_files()
 *
 * Extract Function for extract files
 *
 * Show that the "Extract" button was pressed
 *
 */
void extractfunc_extract_files(GtkWidget *widget, gpointer data)
{
  /* --- Display message --- */
  g_print("Extract function goes here.\n");

  /* --- Close it. --- */
  gtk_widget_destroy(GTK_WIDGET(data));
}

