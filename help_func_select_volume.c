#include <gtk/gtk.h>
#include <gdk/gdkkeysyms.h>

#include "calvados.h"

/*
 *
 * help_func_select_volume()
 *
 * Help Function for select volume image
 *
 * Show that the "Help" button was pressed
 *
 */
void help_func_select_volume(GtkWidget *widget, gpointer data)
{
    /* --- Display message --- */
    g_print("Help function goes here.\n");

    /* --- Close it. --- */
    gtk_widget_destroy(GTK_WIDGET(data));

    /* Now open the help dialog */
/*FIXME*/
}

