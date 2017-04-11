#include <gtk/gtk.h>
#include <gdk/gdkkeysyms.h>

#include "calvados.h"

/*
 *
 * acceptfunc_add_files()
 *
 * Accept Function for add files
 *
 * Show that the "Accept" button was pressed
 *
 */
void acceptfunc_add_files(GtkWidget *widget, gpointer data)
{
    /* --- Display message --- */
    g_print("Add function goes here.\n");

    /* --- Close it. --- */
    gtk_widget_destroy(GTK_WIDGET(data));
}

