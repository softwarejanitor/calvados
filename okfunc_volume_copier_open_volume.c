#include <gtk/gtk.h>
#include <gdk/gdkkeysyms.h>

#include "calvados.h"

/*
 *
 * okfunc_volume_copier_open_volume()
 *
 * OK Function for volume copier open volume
 *
 * Show that the "OK" button was pressed
 *
 */
void okfunc_volume_copier_open_volume(GtkWidget *widget, gpointer data)
{
  /* --- Display message --- */
  g_print("Volume copier select volume function goes here.\n");

  /* --- Close it. --- */
  gtk_widget_destroy(GTK_WIDGET(data));
}

