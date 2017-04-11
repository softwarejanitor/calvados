#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>
#include <gtk/gtk.h>
#include <string.h>

#include "calvados.h"

GtkWidget *extractAllFilesRb;
GtkWidget *convertToNonAppleIIFormatsCb;
GtkWidget *extractDisksAs2MGCb;
GtkWidget *dontConvertTextFilesRb;
GtkWidget *autoDetectConvertFilesWithRb;
GtkWidget *stripHighASCIIFilesCb;
GtkWidget *dataForksCb;
GtkWidget *resourceForksCb;
GtkWidget *diskImagesCb;
GtkWidget *addFileAttributePreservationCb;
GtkWidget *addTypeExtensionCb;

/* FIXME -- need to add a callback to the folder chooser to un-grey extract selected files radio button when there are selections */

void filesToExtractRbCallback(GtkWidget *widget, gpointer *data)
{
  g_print("clicked %s\n", (char *)data);
}


void textConversionRbCallback2(GtkWidget *widget, gpointer *data)
{
  /*g_print("clicked %s\n", (char *)data);*/

  if (strcmp((char *)data, "dontConvertTextFilesRb") == 0) {
    gtk_widget_set_sensitive(stripHighASCIIFilesCb, FALSE);
  } else {
    gtk_widget_set_sensitive(stripHighASCIIFilesCb, TRUE);
  }
}


void configureToPreserveAppleIIFormatsCallback(GtkWidget *widget, gpointer *data)
{
  g_print("clicked %s\n", (char *)data);
  gtk_toggle_button_set_state(GTK_TOGGLE_BUTTON(extractAllFilesRb), TRUE);
  gtk_toggle_button_set_state(GTK_TOGGLE_BUTTON(convertToNonAppleIIFormatsCb), FALSE);
  gtk_toggle_button_set_state(GTK_TOGGLE_BUTTON(extractDisksAs2MGCb), FALSE);
  gtk_toggle_button_set_state(GTK_TOGGLE_BUTTON(dontConvertTextFilesRb), TRUE);
  gtk_toggle_button_set_state(GTK_TOGGLE_BUTTON(autoDetectConvertFilesWithRb), FALSE);
  gtk_toggle_button_set_state(GTK_TOGGLE_BUTTON(stripHighASCIIFilesCb), FALSE);
  gtk_widget_set_sensitive(stripHighASCIIFilesCb, FALSE);
  gtk_toggle_button_set_state(GTK_TOGGLE_BUTTON(dataForksCb), TRUE);
  gtk_toggle_button_set_state(GTK_TOGGLE_BUTTON(resourceForksCb), TRUE);
  gtk_toggle_button_set_state(GTK_TOGGLE_BUTTON(diskImagesCb), TRUE);
  gtk_toggle_button_set_state(GTK_TOGGLE_BUTTON(addFileAttributePreservationCb), TRUE);
  gtk_toggle_button_set_state(GTK_TOGGLE_BUTTON(addTypeExtensionCb), FALSE);
}


void configureForEasyAccessInLinuxCallback(GtkWidget *widget, gpointer *data)
{
  g_print("clicked %s\n", (char *)data);
  gtk_toggle_button_set_state(GTK_TOGGLE_BUTTON(extractAllFilesRb), TRUE);
  gtk_toggle_button_set_state(GTK_TOGGLE_BUTTON(convertToNonAppleIIFormatsCb), TRUE);
  gtk_toggle_button_set_state(GTK_TOGGLE_BUTTON(extractDisksAs2MGCb), TRUE);
  gtk_toggle_button_set_state(GTK_TOGGLE_BUTTON(dontConvertTextFilesRb), FALSE);
  gtk_toggle_button_set_state(GTK_TOGGLE_BUTTON(autoDetectConvertFilesWithRb), TRUE);
  gtk_toggle_button_set_state(GTK_TOGGLE_BUTTON(stripHighASCIIFilesCb), TRUE);
  gtk_widget_set_sensitive(stripHighASCIIFilesCb, TRUE);
  gtk_toggle_button_set_state(GTK_TOGGLE_BUTTON(dataForksCb), TRUE);
  gtk_toggle_button_set_state(GTK_TOGGLE_BUTTON(resourceForksCb), FALSE);
  gtk_toggle_button_set_state(GTK_TOGGLE_BUTTON(diskImagesCb), TRUE);
  gtk_toggle_button_set_state(GTK_TOGGLE_BUTTON(addFileAttributePreservationCb), FALSE);
  gtk_toggle_button_set_state(GTK_TOGGLE_BUTTON(addTypeExtensionCb), TRUE);
}


/*
 *
 * extract_files()
 *
 * Extract files dialog box
 *
 */
void extract_files()
{
  GtkWidget *dialog;
  GtkWidget *chooser_dialog;
  GtkWidget *hbox1;
  GtkWidget *vboxl;
  GtkWidget *vboxr;
  GtkWidget *hbox2;
  GtkWidget *folderLabel;
  GtkWidget *folderFileChooserButton;
  GtkWidget *filesToExtractFrame;
  GtkWidget *filesToExtractVbox;
  GSList *filesToExtractRbGroup = NULL;
  GtkWidget *extractNSelectedFilesRb;
  GtkWidget *formatConversionFrame;
  GtkWidget *formatConversionVbox;
  GtkWidget *textConversionFrame;
  GtkWidget *textConversionVbox;
  GSList *textConversionRbGroup = NULL;
  GtkWidget *convertTextFilesByFileTypeRb;
  GtkWidget *convertAllFilesRb;
  GtkWidget *partsToExtractFrame;
  GtkWidget *partsToExtractVbox;
  GtkWidget *filenamesFrame;
  GtkWidget *filenamesVbox;
  GtkWidget *miscellaneousFrame;
  GtkWidget *miscellaneousVbox;
  GtkWidget *stripFolderNamesCb;
  GtkWidget *overwriteExistingFilesCb;
  GtkWidget *configureToPreserveAppleIIFormatsButton;
  GtkWidget *configureForEasyAccessInLinuxButton;
  GtkWidget *extract_button;
  GtkWidget *cancel_button;
  GtkWidget *help_button;
  /* For getting user's home directory */
  struct passwd *pw;
  const char *homedir;

  /* Get their home directory for use in folder picker */
  if ((homedir = getenv("HOME")) == NULL) {
    pw = getpwuid(getuid());
    homedir = pw->pw_dir;
  }

  g_print("homedir=%s", homedir);

  /* --- Create the dialog --- */
  dialog = gtk_dialog_new();

  /* --- Trap the window close signal to release the grab --- */
  gtk_signal_connect(GTK_OBJECT(dialog), "destroy",
                      GTK_SIGNAL_FUNC(closing_dialog),
                      &dialog);

  /* --- Set the title --- */
  gtk_window_set_title(GTK_WINDOW(dialog), "Extract Files");

  /* --- Add a small border --- */
  gtk_container_border_width(GTK_CONTAINER(dialog), 5);

  /* Create file chooser dialog */
  chooser_dialog = gtk_file_chooser_dialog_new("Select folder",
                                       NULL,
                                       GTK_FILE_CHOOSER_ACTION_SELECT_FOLDER,
                                       GTK_STOCK_CANCEL,
                                       GTK_RESPONSE_CANCEL,
                                       GTK_STOCK_OPEN,
                                       GTK_RESPONSE_ACCEPT,
                                       NULL);

  folderLabel = gtk_label_new("Folder where files will be extracted:");
  gtk_widget_show(folderLabel);
  gtk_box_pack_start(GTK_BOX(GTK_DIALOG(dialog)->vbox), folderLabel, TRUE, TRUE, 0);

  gtk_file_chooser_set_current_folder(GTK_FILE_CHOOSER(chooser_dialog), homedir);

  folderFileChooserButton = gtk_file_chooser_button_new_with_dialog(chooser_dialog);
  gtk_widget_show(folderFileChooserButton);
  gtk_box_pack_start(GTK_BOX(GTK_DIALOG(dialog)->vbox), folderFileChooserButton, TRUE, TRUE, 0);

  hbox1 = gtk_hbox_new(FALSE, 0);
  gtk_widget_show(hbox1);
  gtk_box_pack_start(GTK_BOX(GTK_DIALOG(dialog)->vbox), hbox1, TRUE, TRUE, 0);

  vboxl = gtk_vbox_new(FALSE, 0);
  gtk_widget_show(vboxl);
  gtk_box_pack_start(GTK_BOX(hbox1), vboxl, TRUE, TRUE, 0);

  vboxr = gtk_vbox_new(FALSE, 0);
  gtk_widget_show(vboxr);
  gtk_box_pack_start(GTK_BOX(hbox1), vboxr, TRUE, TRUE, 0);

  filesToExtractFrame = gtk_frame_new("Files to extract");
  gtk_widget_show(filesToExtractFrame);
  gtk_box_pack_start(GTK_BOX(vboxl), filesToExtractFrame, TRUE, TRUE, 0);

  filesToExtractVbox = gtk_vbox_new(FALSE, 0);
  gtk_widget_show(filesToExtractVbox);
  gtk_container_add(GTK_CONTAINER(filesToExtractFrame), filesToExtractVbox);

  extractNSelectedFilesRb = create_radio(filesToExtractVbox, &filesToExtractRbGroup, "Extract N selected files");
  extractAllFilesRb = create_radio(filesToExtractVbox, &filesToExtractRbGroup, "Extract all files");

  /* Set default selected item */
  gtk_toggle_button_set_state(GTK_TOGGLE_BUTTON(extractAllFilesRb), TRUE);

  /* Default grey out extract selected files radio button */
  gtk_widget_set_sensitive(extractNSelectedFilesRb, FALSE);

  /* Set up callbacks for files to extract frame */
  gtk_signal_connect(GTK_OBJECT(extractNSelectedFilesRb), "clicked", GTK_SIGNAL_FUNC(filesToExtractRbCallback), (gpointer)"extractNSelectedFilesRb");
  gtk_signal_connect(GTK_OBJECT(extractAllFilesRb), "clicked", GTK_SIGNAL_FUNC(filesToExtractRbCallback), (gpointer)"extractAllFilesRb");

  formatConversionFrame = gtk_frame_new("Format conversion");
  gtk_widget_show(formatConversionFrame);
  gtk_box_pack_start(GTK_BOX(vboxl), formatConversionFrame, TRUE, TRUE, 0);

  formatConversionVbox = gtk_vbox_new(FALSE, 0);
  gtk_widget_show(formatConversionVbox);
  gtk_container_add(GTK_CONTAINER(formatConversionFrame), formatConversionVbox);

  convertToNonAppleIIFormatsCb = gtk_check_button_new_with_label("Convert to non-Apple II formats");
  gtk_widget_show(convertToNonAppleIIFormatsCb);
  gtk_box_pack_start(GTK_BOX(formatConversionVbox), convertToNonAppleIIFormatsCb, TRUE, TRUE, 0);
  extractDisksAs2MGCb = gtk_check_button_new_with_label("Extract disks as 2MG");
  gtk_widget_show(extractDisksAs2MGCb);
  gtk_box_pack_start(GTK_BOX(formatConversionVbox), extractDisksAs2MGCb, TRUE, TRUE, 0);

  textConversionFrame = gtk_frame_new("Text conversion");
  gtk_widget_show(textConversionFrame);
  gtk_box_pack_start(GTK_BOX(vboxl), textConversionFrame, TRUE, TRUE, 0);

  textConversionVbox = gtk_vbox_new(FALSE, 0);
  gtk_widget_show(textConversionVbox);
  gtk_container_add(GTK_CONTAINER(textConversionFrame), textConversionVbox);

  dontConvertTextFilesRb = create_radio(textConversionVbox, &textConversionRbGroup, "Don't convert text files");
  convertTextFilesByFileTypeRb = create_radio(textConversionVbox, &textConversionRbGroup, "Convert text files by file type");
  autoDetectConvertFilesWithRb = create_radio(textConversionVbox, &textConversionRbGroup, "Auto-detect & convert files with");
  convertAllFilesRb = create_radio(textConversionVbox, &textConversionRbGroup, "Convert All files");
  stripHighASCIIFilesCb = gtk_check_button_new_with_label("Strip \"high ASCII\" files");
  gtk_widget_show(stripHighASCIIFilesCb);
  gtk_box_pack_start(GTK_BOX(textConversionVbox), stripHighASCIIFilesCb, TRUE, TRUE, 0);

  /* Set default active and selected items */
  gtk_toggle_button_set_state(GTK_TOGGLE_BUTTON(dontConvertTextFilesRb), TRUE);
  gtk_toggle_button_set_state(GTK_TOGGLE_BUTTON(stripHighASCIIFilesCb), TRUE);

  /* Default grey out strip high ascii files checkbox */
  gtk_widget_set_sensitive(stripHighASCIIFilesCb, FALSE);

  /* Set up callbacks for text conversion frame */
  gtk_signal_connect(GTK_OBJECT(dontConvertTextFilesRb), "clicked", GTK_SIGNAL_FUNC(textConversionRbCallback2), (gpointer)"dontConvertTextFilesRb");
  gtk_signal_connect(GTK_OBJECT(convertTextFilesByFileTypeRb), "clicked", GTK_SIGNAL_FUNC(textConversionRbCallback2), (gpointer)"convertTextFilesByFileTypeRb");
  gtk_signal_connect(GTK_OBJECT(autoDetectConvertFilesWithRb), "clicked", GTK_SIGNAL_FUNC(textConversionRbCallback2), (gpointer)"autoDetectConvertFilesWithRb");
  gtk_signal_connect(GTK_OBJECT(convertAllFilesRb), "clicked", GTK_SIGNAL_FUNC(textConversionRbCallback2), (gpointer)"convertAllFilesRb");

  partsToExtractFrame = gtk_frame_new("Parts to extract");
  gtk_widget_show(partsToExtractFrame);
  gtk_box_pack_start(GTK_BOX(vboxr), partsToExtractFrame, TRUE, TRUE, 0);

  partsToExtractVbox = gtk_vbox_new(FALSE, 0);
  gtk_widget_show(partsToExtractVbox);
  gtk_container_add(GTK_CONTAINER(partsToExtractFrame), partsToExtractVbox);

  dataForksCb = gtk_check_button_new_with_label("Data forks");
  gtk_widget_show(dataForksCb);
  gtk_box_pack_start(GTK_BOX(partsToExtractVbox), dataForksCb, TRUE, TRUE, 0);
  resourceForksCb = gtk_check_button_new_with_label("Resource forks");
  gtk_widget_show(resourceForksCb);
  gtk_box_pack_start(GTK_BOX(partsToExtractVbox), resourceForksCb, TRUE, TRUE, 0);
  diskImagesCb = gtk_check_button_new_with_label("Disk images");
  gtk_widget_show(diskImagesCb);
  gtk_box_pack_start(GTK_BOX(partsToExtractVbox), diskImagesCb, TRUE, TRUE, 0);

  /* Set default selected items */
  gtk_toggle_button_set_state(GTK_TOGGLE_BUTTON(dataForksCb), TRUE);
  gtk_toggle_button_set_state(GTK_TOGGLE_BUTTON(diskImagesCb), TRUE);

  filenamesFrame = gtk_frame_new("Filenames");
  gtk_widget_show(filenamesFrame);
  gtk_box_pack_start(GTK_BOX(vboxr), filenamesFrame, TRUE, TRUE, 0);

  filenamesVbox = gtk_vbox_new(FALSE, 0);
  gtk_widget_show(filenamesVbox);
  gtk_container_add(GTK_CONTAINER(filenamesFrame), filenamesVbox);

  addFileAttributePreservationCb = gtk_check_button_new_with_label("Add file attribute preservation");
  gtk_widget_show(addFileAttributePreservationCb);
  gtk_box_pack_start(GTK_BOX(filenamesVbox), addFileAttributePreservationCb, TRUE, TRUE, 0);
  addTypeExtensionCb = gtk_check_button_new_with_label("Add type extension");
  gtk_widget_show(addTypeExtensionCb);
  gtk_box_pack_start(GTK_BOX(filenamesVbox), addTypeExtensionCb, TRUE, TRUE, 0);

  /* Set default selected item */
  gtk_toggle_button_set_state(GTK_TOGGLE_BUTTON(addFileAttributePreservationCb), TRUE);

  miscellaneousFrame = gtk_frame_new("Miscellaneous");
  gtk_widget_show(miscellaneousFrame);
  gtk_box_pack_start(GTK_BOX(vboxr), miscellaneousFrame, TRUE, TRUE, 0);

  miscellaneousVbox = gtk_vbox_new(FALSE, 0);
  gtk_widget_show(miscellaneousVbox);
  gtk_container_add(GTK_CONTAINER(miscellaneousFrame), miscellaneousVbox);

  stripFolderNamesCb = gtk_check_button_new_with_label("Strip folder names");
  gtk_widget_show(stripFolderNamesCb);
  gtk_box_pack_start(GTK_BOX(miscellaneousVbox), stripFolderNamesCb, TRUE, TRUE, 0);
  overwriteExistingFilesCb = gtk_check_button_new_with_label("Overwrite existing files");
  gtk_widget_show(overwriteExistingFilesCb);
  gtk_box_pack_start(GTK_BOX(miscellaneousVbox), overwriteExistingFilesCb, TRUE, TRUE, 0);

  hbox2 = gtk_hbox_new(FALSE, 0);
  gtk_widget_show(hbox2);
  gtk_box_pack_start(GTK_BOX(GTK_DIALOG(dialog)->vbox), hbox2, TRUE, TRUE, 0);

  configureToPreserveAppleIIFormatsButton = gtk_button_new_with_label("Configure to preserve Apple II formats");
  gtk_widget_show(configureToPreserveAppleIIFormatsButton);
  gtk_box_pack_start(GTK_BOX(hbox2), configureToPreserveAppleIIFormatsButton, TRUE, TRUE, 0);

  gtk_signal_connect(GTK_OBJECT(configureToPreserveAppleIIFormatsButton), "clicked", GTK_SIGNAL_FUNC(configureToPreserveAppleIIFormatsCallback), (gpointer)"configureToPreserveAppleIIFormatsButton");

  configureForEasyAccessInLinuxButton = gtk_button_new_with_label("Configure for easy access in Linux");
  gtk_widget_show(configureForEasyAccessInLinuxButton);
  gtk_box_pack_start(GTK_BOX(hbox2), configureForEasyAccessInLinuxButton, TRUE, TRUE, 0);

  gtk_signal_connect(GTK_OBJECT(configureForEasyAccessInLinuxButton), "clicked", GTK_SIGNAL_FUNC(configureForEasyAccessInLinuxCallback), (gpointer)"configureForEasyAccessInLinuxButton");

  /*
   * --- Extract button
   */

  /* --- Create the "Extract" button --- */
  extract_button = gtk_button_new_with_label("Extract");

  gtk_signal_connect(GTK_OBJECT(extract_button), "clicked",
                     GTK_SIGNAL_FUNC(extractfunc_extract_files),
                     dialog);

  /* --- Allow "Extract" to be a default --- */
  GTK_WIDGET_SET_FLAGS(extract_button, GTK_CAN_DEFAULT);

  /* --- Add the Extract button to the bottom hbox2 --- */
  gtk_box_pack_start(GTK_BOX(GTK_DIALOG(dialog)->action_area), extract_button, TRUE, TRUE, 0);

  /* --- Make the "Extract" the default --- */
  gtk_widget_grab_default(extract_button);

  /* --- Make the button visible --- */
  gtk_widget_show(extract_button);

  /*
   * --- Cancel button
   */

  /* --- Create the "Cancel" button --- */
  cancel_button = gtk_button_new_with_label("Cancel");

  gtk_signal_connect(GTK_OBJECT(cancel_button), "clicked",
                     GTK_SIGNAL_FUNC(close_dialog),
                     dialog);

  /* --- Allow "Cancel" to be a default --- */
  GTK_WIDGET_SET_FLAGS(cancel_button, GTK_CAN_DEFAULT);

  /* --- Add the "Cancel" button to the dialog --- */
  gtk_box_pack_start(GTK_BOX(GTK_DIALOG(dialog)->action_area), cancel_button, TRUE, TRUE, 0);

  /* --- Make the button visible. --- */
  gtk_widget_show(cancel_button);

  /*
   * --- Help button
   */

  /* --- Create the "Help" button --- */
  help_button = gtk_button_new_with_label("Help");

  gtk_signal_connect(GTK_OBJECT(help_button), "clicked",
                     GTK_SIGNAL_FUNC(help_func_extract_files),
                     dialog);

  /* --- Add the "Help" button to the dialog --- */
  gtk_box_pack_start(GTK_BOX(GTK_DIALOG(dialog)->action_area), help_button, TRUE, TRUE, 0);

  /* --- Make the button visible. --- */
  gtk_widget_show(help_button);

  /* --- Show the dialog --- */
  gtk_widget_show(dialog);

  /* --- Only this window can be used for now --- */
  gtk_grab_add(dialog);
}

