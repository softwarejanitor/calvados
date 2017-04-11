#include <gtk/gtk.h>
#include <gdk/gdkkeysyms.h>

#include "calvados.h"

/*
 *
 * okfunc_select_volume()
 *
 * OK Function for select volume
 *
 * Show that the "OK" button was pressed
 *
 */
void okfunc_select_volume(GtkWidget *widget, gpointer data)
{
  /* --- Display message --- */
  g_print("Create function goes here.\n");

  /* --- Close it. --- */
  gtk_widget_destroy(GTK_WIDGET(data));
}

