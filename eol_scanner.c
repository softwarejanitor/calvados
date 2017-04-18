#include <gtk/gtk.h>
#include <gdk/gdkkeysyms.h>

#include "calvados.h"

/*
 *
 * eol_scanner()
 *
 * eol_scanner Volume from the menu.
 *
 */
void eol_scanner(GtkWidget *widget, gpointer data)
{
  GtkWidget *dialog;
  gint res;
  GtkFileFilter *allFilesFilt;

  /* --- Display message --- */
  /*g_print("eol_scanner function goes here.\n");*/

  allFilesFilt = gtk_file_filter_new();
  gtk_file_filter_set_name(allFilesFilt, "All Files");
  gtk_file_filter_add_pattern(allFilesFilt, "*");

  dialog = gtk_file_chooser_dialog_new("Select file to scan",
                                       NULL,
                                       GTK_FILE_CHOOSER_ACTION_OPEN,
                                       GTK_STOCK_CANCEL,
                                       GTK_RESPONSE_CANCEL,
                                       GTK_STOCK_OPEN,
                                       GTK_RESPONSE_ACCEPT,
                                       NULL);

  gtk_file_chooser_add_filter(GTK_FILE_CHOOSER(dialog), allFilesFilt);

  res = gtk_dialog_run(GTK_DIALOG(dialog));
  if (res == GTK_RESPONSE_ACCEPT) {
    char *filename;
    GtkFileChooser *chooser = GTK_FILE_CHOOSER(dialog);
    filename = gtk_file_chooser_get_filename(chooser);
    do_eol_scan(filename);
    g_free(filename);
  }

  gtk_widget_destroy(dialog);
}

