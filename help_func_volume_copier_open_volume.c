#include <gtk/gtk.h>
#include <gdk/gdkkeysyms.h>

#include "calvados.h"

/*
 *
 * help_func_volume_copier_open_volume()
 *
 * Help Function for volume copier open volume
 *
 * Show that the "Help" button was pressed
 *
 */
void help_func_volume_copier_open_volume(GtkWidget *widget, gpointer data)
{
  /* --- Display message --- */
  g_print("Help function for volume copier open volume goes here.\n");

  /* --- Close it. --- */
  gtk_widget_destroy(GTK_WIDGET(data));

  /* Now open the help dialog */
/*FIXME*/
}

