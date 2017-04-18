#include <gtk/gtk.h>

#include "calvados.h"

/*
 *
 * show_error()
 *
 * Show an error message dialog box
 *
 */
void show_error(GtkWidget *widget, gpointer data, char *errmsg)
{
  GtkWidget *dialog;

  /*g_print("Error dialog goes here\n");*/

  dialog = gtk_message_dialog_new(NULL,
            GTK_DIALOG_DESTROY_WITH_PARENT,
            GTK_MESSAGE_ERROR,
            GTK_BUTTONS_OK,
            errmsg);

  gtk_window_set_title(GTK_WINDOW(dialog), "Error");
  gtk_dialog_run(GTK_DIALOG(dialog));
  gtk_widget_destroy(dialog);
}

