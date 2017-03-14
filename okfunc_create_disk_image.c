#include <gtk/gtk.h>
#include <gdk/gdkkeysyms.h>

#include "calvados.h"

/*
 *
 * okfunc_create_disk_image()
 *
 * OK Function for create disk image
 *
 * Show that the "OK" button was pressed
 *
 */
void okfunc_create_disk_image(GtkWidget *widget, gpointer data)
{
    /* --- Display message --- */
    g_print("Create function goes here.\n");

    /* --- Close it. --- */
    gtk_widget_destroy(GTK_WIDGET(data));
}

