#include <gtk/gtk.h>
#include <gdk/gdkkeysyms.h>

#include "calvados.h"

/*
 *
 * twomg_properties_editor()
 *
 * twomg_properties_editor Volume from the menu.
 *
 */
void twomg_properties_editor(GtkWidget *widget, gpointer data)
{
  GtkWidget *dialog;
  gint res;
  GtkFileFilter *twoMGFilesFilt;
  GtkFileFilter *allFilesFilt;

  /* --- Display message --- */
  /*g_print("twomg_properties_editor function goes here.\n");*/

  twoMGFilesFilt = gtk_file_filter_new();
  gtk_file_filter_set_name(twoMGFilesFilt, "2MG Disk Images (.2mg, .2img)");
  gtk_file_filter_add_pattern(twoMGFilesFilt, "*.2[Mm][Gg]");
  gtk_file_filter_add_pattern(twoMGFilesFilt, "*.2[Ii][Mm][Gg]");

  allFilesFilt = gtk_file_filter_new();
  gtk_file_filter_set_name(allFilesFilt, "All Files");
  gtk_file_filter_add_pattern(allFilesFilt, "*");

  dialog = gtk_file_chooser_dialog_new("Select file to edit",
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
    do_2mg_edit(filename);
    g_free(filename);
  }

  gtk_widget_destroy(dialog);
}

