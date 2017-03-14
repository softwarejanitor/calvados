#include <gtk/gtk.h>
#include <gdk/gdkkeysyms.h>

#include "calvados.h"

/*
 *
 * new_archive()
 *
 * New archive dialog box.
 *
 */
void new_archive()
{
  GtkWidget *dialog;

  dialog = gtk_file_chooser_dialog_new("New Archive",
                                      NULL,
                                      GTK_FILE_CHOOSER_ACTION_SAVE,
                                      GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL,
                                      GTK_STOCK_SAVE, GTK_RESPONSE_ACCEPT,
                                      NULL);
  gtk_file_chooser_set_do_overwrite_confirmation(GTK_FILE_CHOOSER(dialog), TRUE);

  gtk_file_chooser_set_current_folder(GTK_FILE_CHOOSER(dialog), "Desktop");
  gtk_file_chooser_set_current_name(GTK_FILE_CHOOSER(dialog), "new.shk");


  if (gtk_dialog_run(GTK_DIALOG(dialog)) == GTK_RESPONSE_ACCEPT) {
    char *filename;

    filename = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(dialog));
    save_to_file(filename);
    g_free(filename);
  }

  gtk_widget_destroy(dialog);
}

