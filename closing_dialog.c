#include <gtk/gtk.h>
#include <gdk/gdkkeysyms.h>

/*
 *
 * closing_dialog
 *
 * Calls when window is about to close.  returns FALSE
 * to let it close.
 *
 */
void closing_dialog(GtkWidget *widget, gpointer data)
{
  gtk_grab_remove(GTK_WIDGET(widget));
}

