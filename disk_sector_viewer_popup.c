#include <gtk/gtk.h>
#include <gdk/gdkkeysyms.h>

#include "calvados.h"

/*
 *
 * disk_sector_viewer_popup()
 *
 * Disk Sector Viewer Popup dialog
 *
 */
void disk_sector_viewer_popup()
{
  GtkWidget *dialog;
  GtkWidget *vbox;
  GtkWidget *openDiskButton;
  GtkWidget *openVolumeButton;
  GtkWidget *openArchiveButton;
  GtkWidget *cancelButton;

  /* --- Create a dialog window --- */
  dialog = gtk_dialog_new();

  /* --- Trap the destroy button --- */
  gtk_signal_connect(GTK_OBJECT(dialog), "destroy",
	             GTK_SIGNAL_FUNC(gtk_widget_destroyed),
	             &dialog);

  /* --- Add a title to the window --- */
  /*gtk_window_set_title(GTK_WINDOW(dialog), "Disk sector viewer");*/
  gtk_window_set_title(GTK_WINDOW(dialog), " ");

  /* --- Create a small border --- */
  gtk_container_border_width(GTK_CONTAINER(dialog), 5);

  vbox = gtk_vbox_new(FALSE, 0);
  gtk_box_pack_start(GTK_BOX(GTK_DIALOG(dialog)->vbox), vbox, TRUE, TRUE, 0);
  gtk_widget_show(vbox);

  /*
   * --- "open disk" button
   */

  /* --- Create the "open disk" button --- */
  openDiskButton = gtk_button_new_with_label("Open disk image file");

  /* --- Need to close the window if they press "ok" --- */
  gtk_signal_connect(GTK_OBJECT(openDiskButton), "clicked",
                     GTK_SIGNAL_FUNC(close_dialog),
                     dialog);

  /* --- Add the button to the dialog --- */
  gtk_box_pack_start(GTK_BOX(vbox), openDiskButton, TRUE, TRUE, 0);

  /* --- Make the button visible --- */
  gtk_widget_show(openDiskButton);

  /*
   * --- "open volume" button
   */

  /* --- Create the "open volume" button --- */
  openVolumeButton = gtk_button_new_with_label("Open logical or physical volume");

  /* --- Need to close the window if they press "ok" --- */
  gtk_signal_connect(GTK_OBJECT(openVolumeButton), "clicked",
                     GTK_SIGNAL_FUNC(close_dialog),
                     dialog);

  /* --- Add the button to the dialog --- */
  gtk_box_pack_start(GTK_BOX(vbox), openVolumeButton, TRUE, TRUE, 0);

  /* --- Make the button visible --- */
  gtk_widget_show(openVolumeButton);

  /*
   * --- "open archive" button
   */

  /* --- Create the "open archive" button --- */
  openArchiveButton = gtk_button_new_with_label("Open current archive");

  /* --- Need to close the window if they press "ok" --- */
  gtk_signal_connect(GTK_OBJECT(openArchiveButton), "clicked",
                     GTK_SIGNAL_FUNC(close_dialog),
                     dialog);

  /* --- Add the button to the dialog --- */
  gtk_box_pack_start(GTK_BOX(vbox), openArchiveButton, TRUE, TRUE, 0);

  /* --- Make the button visible --- */
  gtk_widget_show(openArchiveButton);

  /*
   * --- "cancel" button
   */

  /* --- Create the "cancel" button --- */
  cancelButton = gtk_button_new_with_label("Cancel");

  /* --- Need to close the window if they press "ok" --- */
  gtk_signal_connect(GTK_OBJECT(cancelButton), "clicked",
                     GTK_SIGNAL_FUNC(close_dialog),
                     dialog);

  /* --- Allow it to be the default button --- */
  GTK_WIDGET_SET_FLAGS(cancelButton, GTK_CAN_DEFAULT);

  /* --- Add the button to the dialog --- */
  gtk_box_pack_start(GTK_BOX(vbox), cancelButton, TRUE, TRUE, 0);

  /* --- Make the button the default button --- */
  gtk_widget_grab_default(cancelButton);

  /* --- Make the button visible --- */
  gtk_widget_show(cancelButton);

  /* --- Make the dialog visible --- */
  gtk_widget_show(dialog);

  gtk_grab_add(dialog);
}

