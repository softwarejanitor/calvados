#include <gtk/gtk.h>
#include <gdk/gdkkeysyms.h>

#include "calvados.h"

/*
 *
 * help_func_archive_info()
 *
 * Help Function for archive info
 *
 * Show that the "Help" button was pressed
 *
 */
void help_func_archive_info(GtkWidget *widget, gpointer data)
{
  /* --- Display message --- */
  g_print("Help function for archive info goes here.\n");

  /* --- Close it. --- */
  gtk_widget_destroy(GTK_WIDGET(data));

  /* Now open the help dialog */
/*FIXME*/
}

