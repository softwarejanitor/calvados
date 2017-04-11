#include <string.h>
#include <gtk/gtk.h>

#include "calvados.h"
 
/* FIXME -- this needs to be thought through and moved to the .h file or somewhere better */
#define SHK 0
#define DSK 1

/*
 *
 * archive_info()
 *
 */
void archive_info()
{
  GtkWidget *dialog;
  GtkWidget *vbox;

  GtkWidget *archiveInfoFrame;
  GtkWidget *archiveInfoHbox;
  GtkWidget *archiveInfoVboxl;
  GtkWidget *archiveInfoVboxr;
  GtkWidget *filenameLabel;
  GtkWidget *formatLabel;
  GtkWidget *recordsLabel;
  GtkWidget *masterVersionLabel;
  GtkWidget *createdLabel;
  GtkWidget *modifiedLabel;
  GtkWidget *junkSkippedLabel;

  GtkWidget *fileCharacteristicsFrame;
  GtkWidget *fileCharacteristicsHbox;
  GtkWidget *fileCharacteristicsVboxl;
  GtkWidget *fileCharacteristicsVboxr;
  GtkWidget *diskCharacteristicsFrame;
  GtkWidget *diskCharacteristicsHbox;
  GtkWidget *diskCharacteristicsInfoVboxl;
  GtkWidget *diskCharacteristicsInfoVboxr;

  GtkWidget *hbox2;
  GtkWidget *helpButton;
  GtkWidget *doneButton;
  int archive_type = 0;
  char dialog_title[256];

  g_print("archive info goes here\n");

  /* FIXME -- need to detect what type of archive we are looking at */
  if (archive_type == SHK) {
     strcpy(dialog_title, "NuFX (ShrinkIt) Archive");
  } else if (archive_type == DSK) {
     strcpy(dialog_title, "Disk Image Info");
  } else {
     strcpy(dialog_title, "Disk Image Info");
  }

  /* --- Create a dialog window --- */
  dialog = gtk_dialog_new();

  /* --- Trap the destroy button --- */
  gtk_signal_connect(GTK_OBJECT(dialog), "destroy",
                     GTK_SIGNAL_FUNC(gtk_widget_destroyed),
                     &dialog);

  /* --- Add a title to the window --- */
  gtk_window_set_title(GTK_WINDOW(dialog), dialog_title);

  /* --- Create a small border --- */
  gtk_container_border_width(GTK_CONTAINER(dialog), 5);

  vbox = gtk_vbox_new(FALSE, 0);
  gtk_box_pack_start(GTK_BOX(GTK_DIALOG(dialog)->vbox), vbox, TRUE, TRUE, 0);
  gtk_widget_show(vbox);

  /* For archive info SHK, etc */
  if (archive_type == SHK) {
    archiveInfoFrame = gtk_frame_new("Archive Info");
    gtk_box_pack_start(GTK_BOX(vbox), archiveInfoFrame, TRUE, TRUE, 0);
    gtk_widget_show(archiveInfoFrame);

    archiveInfoHbox = gtk_hbox_new(FALSE, 0);
    gtk_container_add(GTK_CONTAINER(archiveInfoFrame), archiveInfoHbox);
    gtk_widget_show(archiveInfoHbox);

    archiveInfoVboxl = gtk_vbox_new(FALSE, 0);
    gtk_box_pack_start(GTK_BOX(archiveInfoHbox), archiveInfoVboxl, TRUE, TRUE, 0);
    gtk_widget_show(archiveInfoVboxl);

    archiveInfoVboxr = gtk_vbox_new(FALSE, 0);
    gtk_box_pack_start(GTK_BOX(archiveInfoHbox), archiveInfoVboxr, TRUE, TRUE, 0);
    gtk_widget_show(archiveInfoVboxr);

    filenameLabel = gtk_label_new("Filename:");
    gtk_box_pack_start(GTK_BOX(archiveInfoVboxl), filenameLabel, TRUE, TRUE, 0);
    gtk_widget_show(filenameLabel);
    formatLabel = gtk_label_new("Format:");
    gtk_box_pack_start(GTK_BOX(archiveInfoVboxl), formatLabel, TRUE, TRUE, 0);
    gtk_widget_show(formatLabel);
    recordsLabel = gtk_label_new("Records:");
    gtk_box_pack_start(GTK_BOX(archiveInfoVboxl), recordsLabel, TRUE, TRUE, 0);
    gtk_widget_show(recordsLabel);
    masterVersionLabel = gtk_label_new("Master Version:");
    gtk_box_pack_start(GTK_BOX(archiveInfoVboxl), masterVersionLabel, TRUE, TRUE, 0);
    gtk_widget_show(masterVersionLabel);
    createdLabel = gtk_label_new("Created:");
    gtk_box_pack_start(GTK_BOX(archiveInfoVboxl), createdLabel, TRUE, TRUE, 0);
    gtk_widget_show(createdLabel);
    modifiedLabel = gtk_label_new("Modified:");
    gtk_box_pack_start(GTK_BOX(archiveInfoVboxl), modifiedLabel, TRUE, TRUE, 0);
    gtk_widget_show(modifiedLabel);
    junkSkippedLabel = gtk_label_new("Junk Skipped:");
    gtk_box_pack_start(GTK_BOX(archiveInfoVboxl), junkSkippedLabel, TRUE, TRUE, 0);
    gtk_widget_show(junkSkippedLabel);
  } else {
    /* For disk image info DSK, etc */
    fileCharacteristicsFrame = gtk_frame_new("File Characteristics");
    gtk_box_pack_start(GTK_BOX(vbox), fileCharacteristicsFrame, TRUE, TRUE, 0);
    gtk_widget_show(fileCharacteristicsFrame);

    fileCharacteristicsHbox = gtk_hbox_new(FALSE, 0);
    gtk_container_add(GTK_CONTAINER(fileCharacteristicsFrame), fileCharacteristicsHbox);
    gtk_widget_show(fileCharacteristicsHbox);

    fileCharacteristicsVboxl = gtk_vbox_new(FALSE, 0);
    gtk_box_pack_start(GTK_BOX(fileCharacteristicsHbox), fileCharacteristicsVboxl, TRUE, TRUE, 0);
    gtk_widget_show(fileCharacteristicsVboxl);

    fileCharacteristicsVboxr = gtk_vbox_new(FALSE, 0);
    gtk_box_pack_start(GTK_BOX(fileCharacteristicsHbox), fileCharacteristicsVboxr, TRUE, TRUE, 0);
    gtk_widget_show(fileCharacteristicsVboxr);

    filenameLabel = gtk_label_new("Filename:");
    gtk_box_pack_start(GTK_BOX(fileCharacteristicsVboxl), filenameLabel, TRUE, TRUE, 0);
    gtk_widget_show(filenameLabel);

    diskCharacteristicsFrame = gtk_frame_new("Disk Characteristics");
    gtk_box_pack_start(GTK_BOX(vbox), diskCharacteristicsFrame, TRUE, TRUE, 0);
    gtk_widget_show(diskCharacteristicsFrame);

    diskCharacteristicsHbox = gtk_hbox_new(FALSE, 0);
    gtk_container_add(GTK_CONTAINER(diskCharacteristicsFrame), diskCharacteristicsHbox);
    gtk_widget_show(diskCharacteristicsHbox);

  }

  hbox2 = gtk_hbox_new(FALSE, 0);
  gtk_box_pack_start(GTK_BOX(GTK_DIALOG(dialog)->action_area), hbox2, TRUE, TRUE, 0);
  gtk_widget_show(hbox2);

  /*
   * --- Help button
   */

  /* --- Create the "Help" button --- */
  helpButton = gtk_button_new_with_label("Help");

  gtk_signal_connect(GTK_OBJECT(helpButton), "clicked",
                     GTK_SIGNAL_FUNC(help_func_archive_info),
                     dialog);

  /* --- Add the "Help" button to the dialog --- */
  gtk_box_pack_start(GTK_BOX(hbox2), helpButton, TRUE, TRUE, 0);

  /* --- Make the button visible. --- */
  gtk_widget_show(helpButton);

  /*
   * --- "done" button
   */

  /* --- Create the "done" button --- */
  doneButton = gtk_button_new_with_label("Cancel");

  /* --- Need to close the window if they press "done" --- */
  gtk_signal_connect(GTK_OBJECT(doneButton), "clicked",
                     GTK_SIGNAL_FUNC(close_dialog),
                     dialog);

  /* --- Allow it to be the default button --- */
  GTK_WIDGET_SET_FLAGS(doneButton, GTK_CAN_DEFAULT);

  /* --- Add the button to the dialog --- */
  gtk_box_pack_start(GTK_BOX(hbox2), doneButton, TRUE, TRUE, 0);

  /* --- Make the button the default button --- */
  gtk_widget_grab_default(doneButton);

  /* --- Make the button visible --- */
  gtk_widget_show(doneButton);

  /* --- Need to close the window if they press "done" --- */
  gtk_signal_connect(GTK_OBJECT(doneButton), "clicked",
                     GTK_SIGNAL_FUNC(close_dialog),
                     dialog);

  /* --- Make the dialog visible --- */
  gtk_widget_show(dialog);

  gtk_grab_add(dialog);
}

