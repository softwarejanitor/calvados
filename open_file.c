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
  GtkFileFilter *shrinkItArchivesFilt;
  GtkFileFilter *binaryIIArchivesFilt;
  GtkFileFilter *acuArchivesFilt;
  GtkFileFilter *appleSingleFilesFilt;
  GtkFileFilter *diskImagesFilt;
  GtkFileFilter *allFilesFilt;
  GtkWidget *openAsReadOnlyCb;

  shrinkItArchivesFilt = gtk_file_filter_new();
  gtk_file_filter_set_name(shrinkItArchivesFilt, "ShrinkIt Archives");
  gtk_file_filter_add_pattern(shrinkItArchivesFilt, "*.[Ss][Hh][Kk]");
  gtk_file_filter_add_pattern(shrinkItArchivesFilt, "*.[Ss][Dd][Kk]");
  gtk_file_filter_add_pattern(shrinkItArchivesFilt, "*.[Bb][Xx][Yy]");
  gtk_file_filter_add_pattern(shrinkItArchivesFilt, "*.[Ss][Ee][Aa]");
  gtk_file_filter_add_pattern(shrinkItArchivesFilt, "*.[Bb][Ss][Ee]");

  binaryIIArchivesFilt = gtk_file_filter_new();
  gtk_file_filter_set_name(binaryIIArchivesFilt, "Binary II Archives");
  gtk_file_filter_add_pattern(binaryIIArchivesFilt, "*.[Bb][Nn][Yy]");
  gtk_file_filter_add_pattern(binaryIIArchivesFilt, "*.[Bb][Qq][Yy]");
  gtk_file_filter_add_pattern(binaryIIArchivesFilt, "*.[Bb][Xx][Yy]");

  acuArchivesFilt = gtk_file_filter_new();
  gtk_file_filter_set_name(acuArchivesFilt, "ACU Archives");
  gtk_file_filter_add_pattern(acuArchivesFilt, "*.[Aa][Cc][Uu]");

  appleSingleFilesFilt = gtk_file_filter_new();
  gtk_file_filter_set_name(appleSingleFilesFilt, "AppleSingle Files");
  gtk_file_filter_add_pattern(appleSingleFilesFilt, "*.[Aa][Ss]");

  diskImagesFilt = gtk_file_filter_new();
  gtk_file_filter_set_name(diskImagesFilt, "Disk Images");
  gtk_file_filter_add_pattern(diskImagesFilt, "*.[Dd][Ss][Kk]");
  gtk_file_filter_add_pattern(diskImagesFilt, "*.[Ss][Dd][Kk]");
  gtk_file_filter_add_pattern(diskImagesFilt, "*.[Ss][Hh][Kk]");
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

  allFilesFilt = gtk_file_filter_new();
  gtk_file_filter_set_name(allFilesFilt, "All Files");
  gtk_file_filter_add_pattern(allFilesFilt, "*");

  dialog = gtk_file_chooser_dialog_new("Open",
                                       NULL,
                                       GTK_FILE_CHOOSER_ACTION_OPEN,
                                       GTK_STOCK_CANCEL,
                                       GTK_RESPONSE_CANCEL,
                                       GTK_STOCK_OPEN,
                                       GTK_RESPONSE_ACCEPT,
                                       NULL);

  gtk_file_chooser_add_filter(GTK_FILE_CHOOSER(dialog), shrinkItArchivesFilt);
  gtk_file_chooser_add_filter(GTK_FILE_CHOOSER(dialog), binaryIIArchivesFilt);
  gtk_file_chooser_add_filter(GTK_FILE_CHOOSER(dialog), acuArchivesFilt);
  gtk_file_chooser_add_filter(GTK_FILE_CHOOSER(dialog), appleSingleFilesFilt);
  gtk_file_chooser_add_filter(GTK_FILE_CHOOSER(dialog), diskImagesFilt);
  gtk_file_chooser_add_filter(GTK_FILE_CHOOSER(dialog), allFilesFilt);

  gtk_file_chooser_set_filter(GTK_FILE_CHOOSER(dialog), allFilesFilt);

  openAsReadOnlyCb = gtk_check_button_new_with_label("Open as read-only");
  gtk_box_pack_end(GTK_BOX(GTK_DIALOG(dialog)->action_area), openAsReadOnlyCb, TRUE, TRUE, 0);
  gtk_widget_show(openAsReadOnlyCb);

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

