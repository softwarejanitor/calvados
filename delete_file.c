#include <gtk/gtk.h>

#include "calvados.h"

/*
 *
 * delete_file()
 *
 * Display yes no question dialog box for file deletion.
 *
 */
void delete_file(GtkWidget *widget, gpointer data)
{
  GtkWidget *dialog;

  /*g_print("Delete file goes here.\n");*/

  dialog = gtk_message_dialog_new(NULL,
                                  GTK_DIALOG_DESTROY_WITH_PARENT,
                                  GTK_MESSAGE_QUESTION,
                                  GTK_BUTTONS_YES_NO,
                                  "Delete 1 file?");

  gtk_window_set_title(GTK_WINDOW(dialog), "Delete?");
  gtk_dialog_run(GTK_DIALOG(dialog));
  gtk_widget_destroy(dialog);
}

