#include <gtk/gtk.h>
#include <gdk/gdkkeysyms.h>

#include "calvados.h"

/*
 *
 * disk_image_converter()
 *
 * Disk image converter file dialog
 *
 */
void disk_image_converter(GtkWidget *widget, gpointer data)
{
  GtkWidget *dialog;
  gint res;
  GtkFileFilter *diskImagesFilt;
  GtkFileFilter *allFilesFilt;

  /* Filter for disk images */
  diskImagesFilt = gtk_file_filter_new();
  gtk_file_filter_set_name(diskImagesFilt, "Disk Images");
  gtk_file_filter_add_pattern(diskImagesFilt, "*.[Ss][Hh][Kk]");
  gtk_file_filter_add_pattern(diskImagesFilt, "*.[Ss][Dd][Kk]");
  gtk_file_filter_add_pattern(diskImagesFilt, "*.[Dd][Ss][Kk]");
  gtk_file_filter_add_pattern(diskImagesFilt, "*.[Pp][Oo]");
  gtk_file_filter_add_pattern(diskImagesFilt, "*.[Dd][Oo]");
  gtk_file_filter_add_pattern(diskImagesFilt, "*.[Dd]13");
  gtk_file_filter_add_pattern(diskImagesFilt, "*.2[Mm][Gg]");
  gtk_file_filter_add_pattern(diskImagesFilt, "*.[Ii][Mm][Gg]");
  gtk_file_filter_add_pattern(diskImagesFilt, "*.[Nn][Ii][Bb]");
  gtk_file_filter_add_pattern(diskImagesFilt, "*.[Nn][Bb]2");
  gtk_file_filter_add_pattern(diskImagesFilt, "*.[Rr][Aa][Ww]");
  gtk_file_filter_add_pattern(diskImagesFilt, "*.[Hh][Dd][Vv]");
  gtk_file_filter_add_pattern(diskImagesFilt, "*.[Dd][Cc]");
  gtk_file_filter_add_pattern(diskImagesFilt, "*.[Dd][Cc]6");
  gtk_file_filter_add_pattern(diskImagesFilt, "*.[Dd][Dd][Dd]");
  gtk_file_filter_add_pattern(diskImagesFilt, "*.[Aa][Pp][Pp]");
  gtk_file_filter_add_pattern(diskImagesFilt, "*.[Ff][Dd][Ii]");
  gtk_file_filter_add_pattern(diskImagesFilt, "*.[Ii][Ss][Oo]");
  gtk_file_filter_add_pattern(diskImagesFilt, "*.[Gg][Zz]");
  gtk_file_filter_add_pattern(diskImagesFilt, "*.[Zz][Ii][Pp]");

  /* Filter for all files */
  allFilesFilt = gtk_file_filter_new();
  gtk_file_filter_set_name(allFilesFilt, "All Files");
  gtk_file_filter_add_pattern(allFilesFilt, "*");

  /* Creae the file opener dialog */
  dialog = gtk_file_chooser_dialog_new("Select image to convert",
                                       NULL,
                                       GTK_FILE_CHOOSER_ACTION_OPEN,
                                       GTK_STOCK_CANCEL,
                                       GTK_RESPONSE_CANCEL,
                                       GTK_STOCK_OPEN,
                                       GTK_RESPONSE_ACCEPT,
                                       NULL);

  /* Add the filters */
  gtk_file_chooser_add_filter(GTK_FILE_CHOOSER(dialog), diskImagesFilt);
  gtk_file_chooser_add_filter(GTK_FILE_CHOOSER(dialog), allFilesFilt);

  /* Set disk images filter as default */
  gtk_file_chooser_set_filter(GTK_FILE_CHOOSER(dialog), diskImagesFilt);

  res = gtk_dialog_run(GTK_DIALOG(dialog));
  if (res == GTK_RESPONSE_ACCEPT) {
    char *filename;
    GtkFileChooser *chooser = GTK_FILE_CHOOSER(dialog);
    filename = gtk_file_chooser_get_filename(chooser);
    do_image_converter(filename);
    g_free(filename);
  }

  gtk_widget_destroy(dialog);
}

