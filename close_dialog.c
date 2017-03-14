#include <gtk/gtk.h>
#include <gdk/gdkkeysyms.h>

/*
 *
 * close_dialog()
 *
 * Called when closing a dialog
 *
 */
void close_dialog(GtkWidget *widget, gpointer data)
{
    /* --- Display message --- */
    /*g_print("Cancel function goes here.\n");*/

    /* --- Close it. --- */
    gtk_widget_destroy(GTK_WIDGET(data));
}

