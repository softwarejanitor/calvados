#include <gtk/gtk.h>
#include <gdk/gdkkeysyms.h>

#include "calvados.h"

void fileAttributePreservationRbCallback(GtkWidget *widget, gpointer *data)
{
  g_print("clicked %s\n", (char *)data);
}


void textConversionRbCallback(GtkWidget *widget, gpointer *data)
{
  g_print("clicked %s\n", (char *)data);
}


/*
 *
 * add_files()
 *
 * Add Files dialog box.
 *
 */
void add_files()
{
  GtkWidget *dialog;
  GtkWidget *help_button;
  GtkWidget *hbox1;
  GtkWidget *vboxl;
  GtkWidget *vboxr;
  GtkWidget *fileAttributePreservationFrame;
  GtkWidget *miscellaneousFrame;
  GtkWidget *textConversionFrame;
  GtkWidget *fileAttributePreservationVbox;
  GtkWidget *miscellaneousVbox;
  GtkWidget *textConversionVbox;
  GtkWidget *storagePrefixVbox;
  GtkWidget *ignoreFileAttributePreservationTagsRb;
  GtkWidget *useFileAttributePreservationTagsRb;
  GtkWidget *useTagsAndGuessTypeFromExtensionRb;
  GSList *fileAttributePreservationRbGroup = NULL;
  GtkWidget *dontConvertTextFilesRb;
  GtkWidget *convertTextFilesByFileTypeRb;
  GtkWidget *autoDetectConvertFilesByFileTypeRb;
  GtkWidget *convertAllFilesRb;
  GSList *textConversionRbGroup = NULL;
  GtkWidget *includeSubfoldersCb;
  GtkWidget *stripFolderNamesCb;
  GtkWidget *overwriteExistingFilesCb;
  GtkWidget *storagePrefixLabel;
  GtkWidget *storagePrefixEntry;

  /* --- Create the dialog --- */
  dialog = gtk_file_chooser_dialog_new("Add Files...",
                                       NULL,
                                       GTK_FILE_CHOOSER_ACTION_SAVE,
                                       "_Accept",
                                       GTK_RESPONSE_ACCEPT,
                                       GTK_STOCK_CANCEL,
                                       GTK_RESPONSE_CANCEL,
                                       /*GTK_STOCK_HELP,
                                       GTK_RESPONSE_HELP,*/
                                       NULL);
  gtk_file_chooser_set_do_overwrite_confirmation(GTK_FILE_CHOOSER(dialog), FALSE);

  /*
   * --- Help button
   */

  /* --- Create the "Help" button --- */
  help_button = gtk_button_new_with_label("Help");
  gtk_widget_show(help_button);

  gtk_signal_connect(GTK_OBJECT(help_button), "clicked",
                     GTK_SIGNAL_FUNC(help_func_select_volume),
                     dialog);

  /* --- Add the "Help" button to the dialog --- */
  gtk_box_pack_start(GTK_BOX(GTK_DIALOG(dialog)->action_area), help_button, TRUE, TRUE, 0);

  hbox1 = gtk_hbox_new(FALSE, 0);
  gtk_widget_show(hbox1);
  gtk_box_pack_start(GTK_BOX(GTK_DIALOG(dialog)->vbox), hbox1, TRUE, TRUE, 0);

  vboxl = gtk_vbox_new(FALSE, 0);
  gtk_widget_show(vboxl);
  gtk_box_pack_start(GTK_BOX(hbox1), vboxl, TRUE, TRUE, 0);

  vboxr = gtk_vbox_new(FALSE, 0);
  gtk_widget_show(vboxr);
  gtk_box_pack_start(GTK_BOX(hbox1), vboxr, TRUE, TRUE, 0);

  fileAttributePreservationFrame = gtk_frame_new("File attribute preservation");
  gtk_widget_show(fileAttributePreservationFrame);
  gtk_box_pack_start(GTK_BOX(vboxl), fileAttributePreservationFrame, TRUE, TRUE, 0);
  fileAttributePreservationVbox = gtk_vbox_new(FALSE, 0);
  gtk_widget_show(fileAttributePreservationVbox);
  gtk_container_add(GTK_CONTAINER(fileAttributePreservationFrame), fileAttributePreservationVbox);

  textConversionFrame = gtk_frame_new("Text conversion");
  gtk_widget_show(textConversionFrame);
  gtk_box_pack_start(GTK_BOX(vboxl), textConversionFrame, TRUE, TRUE, 0);
  textConversionVbox = gtk_vbox_new(FALSE, 0);
  gtk_widget_show(textConversionVbox);
  gtk_container_add(GTK_CONTAINER(textConversionFrame), textConversionVbox);

  miscellaneousFrame = gtk_frame_new("Miscellaneous");
  gtk_widget_show(miscellaneousFrame);
  gtk_box_pack_start(GTK_BOX(vboxr), miscellaneousFrame, TRUE, TRUE, 0);
  miscellaneousVbox = gtk_vbox_new(FALSE, 0);
  gtk_widget_show(miscellaneousVbox);
  gtk_container_add(GTK_CONTAINER(miscellaneousFrame), miscellaneousVbox);

  storagePrefixVbox = gtk_vbox_new(FALSE, 0);
  gtk_widget_show(storagePrefixVbox);
  gtk_box_pack_start(GTK_BOX(vboxr), storagePrefixVbox, TRUE, TRUE, 0);

  ignoreFileAttributePreservationTagsRb = create_radio(fileAttributePreservationVbox, &fileAttributePreservationRbGroup, "Ignore file attribute preservation tags");
  useFileAttributePreservationTagsRb = create_radio(fileAttributePreservationVbox, &fileAttributePreservationRbGroup, "Use file attribute preservation flags");
  useTagsAndGuessTypeFromExtensionRb = create_radio(fileAttributePreservationVbox, &fileAttributePreservationRbGroup, "Use tags and guess type from extension");

  dontConvertTextFilesRb = create_radio(textConversionVbox, &textConversionRbGroup, "Don't convert text files");
  convertTextFilesByFileTypeRb = create_radio(textConversionVbox, &textConversionRbGroup, "Convert text files by file type");
  autoDetectConvertFilesByFileTypeRb = create_radio(textConversionVbox, &textConversionRbGroup, "Auto-detect & Convert text files by file type with text");
  convertAllFilesRb = create_radio(textConversionVbox, &textConversionRbGroup, "Convert ALL files");

  includeSubfoldersCb = gtk_check_button_new_with_label("Include subfolders");
  gtk_widget_show(includeSubfoldersCb);
  gtk_box_pack_start(GTK_BOX(miscellaneousVbox), includeSubfoldersCb, TRUE, TRUE, 0);
  gtk_toggle_button_set_state(GTK_TOGGLE_BUTTON(includeSubfoldersCb), TRUE);

  stripFolderNamesCb = gtk_check_button_new_with_label("Strip folder names");
  gtk_widget_show(stripFolderNamesCb);
  gtk_box_pack_start(GTK_BOX(miscellaneousVbox), stripFolderNamesCb, TRUE, TRUE, 0);
  gtk_toggle_button_set_state(GTK_TOGGLE_BUTTON(stripFolderNamesCb), TRUE);

  overwriteExistingFilesCb = gtk_check_button_new_with_label("Overwrite existing files");
  gtk_widget_show(overwriteExistingFilesCb);
  gtk_box_pack_start(GTK_BOX(miscellaneousVbox), overwriteExistingFilesCb, TRUE, TRUE, 0);
  gtk_toggle_button_set_state(GTK_TOGGLE_BUTTON(overwriteExistingFilesCb), TRUE);

  storagePrefixLabel = gtk_label_new("Storage prefix");
  gtk_widget_show(storagePrefixLabel);
  gtk_box_pack_start(GTK_BOX(storagePrefixVbox), storagePrefixLabel, TRUE, TRUE, 0);

  storagePrefixEntry = gtk_entry_new();
  gtk_widget_show(storagePrefixEntry);
  gtk_box_pack_start(GTK_BOX(storagePrefixVbox), storagePrefixEntry, TRUE, TRUE, 0);

  gtk_toggle_button_set_state(GTK_TOGGLE_BUTTON(useFileAttributePreservationTagsRb), TRUE);

  /* Set up callbacks for file attribute preservation frame */
  gtk_signal_connect(GTK_OBJECT(ignoreFileAttributePreservationTagsRb), "clicked", GTK_SIGNAL_FUNC(fileAttributePreservationRbCallback), (gpointer)"ignoreFileAttributePreservationTagsRb");
  gtk_signal_connect(GTK_OBJECT(useFileAttributePreservationTagsRb), "clicked", GTK_SIGNAL_FUNC(fileAttributePreservationRbCallback), (gpointer)"useFileAttributePreservationTagsRb");
  gtk_signal_connect(GTK_OBJECT(useTagsAndGuessTypeFromExtensionRb), "clicked", GTK_SIGNAL_FUNC(fileAttributePreservationRbCallback), (gpointer)"useTagsAndGuessTypeFromExtensionRb");

  gtk_toggle_button_set_state(GTK_TOGGLE_BUTTON(convertTextFilesByFileTypeRb), TRUE);

  /* Set up callbacks for text conversion frame */
  gtk_signal_connect(GTK_OBJECT(dontConvertTextFilesRb), "clicked", GTK_SIGNAL_FUNC(textConversionRbCallback), (gpointer)"dontConvertTextFilesRb");
  gtk_signal_connect(GTK_OBJECT(convertTextFilesByFileTypeRb), "clicked", GTK_SIGNAL_FUNC(textConversionRbCallback), (gpointer)"convertTextFilesByFileTypeRb");
  gtk_signal_connect(GTK_OBJECT(autoDetectConvertFilesByFileTypeRb), "clicked", GTK_SIGNAL_FUNC(textConversionRbCallback), (gpointer)"autoDetectConvertFilesByFileTypeRb");
  gtk_signal_connect(GTK_OBJECT(convertAllFilesRb), "clicked", GTK_SIGNAL_FUNC(textConversionRbCallback), (gpointer)"convertAllFilesRb");

/* FIXME -- need to make correct path here */
  gtk_file_chooser_set_current_folder(GTK_FILE_CHOOSER(dialog), "Desktop");

  if (gtk_dialog_run(GTK_DIALOG(dialog)) == GTK_RESPONSE_ACCEPT) {
    char *filename;

    filename = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(dialog));
    do_add_files(filename);
    g_free(filename);
  }

  gtk_widget_destroy(dialog);
}

