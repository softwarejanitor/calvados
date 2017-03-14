#include <gtk/gtk.h>
#include <gdk/gdkkeysyms.h>

#include "calvados.h"

/*
 *
 * open_file()
 *
 * Open file dialog
 *
 */
void open_file()
{
  GtkWidget *dialog;
  gint res;

  dialog = gtk_file_chooser_dialog_new("Open",
                                       NULL,
                                       GTK_FILE_CHOOSER_ACTION_OPEN,
                                       GTK_STOCK_CANCEL,
                                       GTK_RESPONSE_CANCEL,
                                       GTK_STOCK_OPEN,
                                       GTK_RESPONSE_ACCEPT,
                                       NULL);

  res = gtk_dialog_run(GTK_DIALOG(dialog));
  if (res == GTK_RESPONSE_ACCEPT) {
    char *filename;
    GtkFileChooser *chooser = GTK_FILE_CHOOSER(dialog);
    filename = gtk_file_chooser_get_filename(chooser);
    do_open_file(filename);
    g_free(filename);
  }

  gtk_widget_destroy(dialog);
}

