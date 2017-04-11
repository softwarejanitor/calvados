#include <gtk/gtk.h>

#include "calvados.h"

/*
 *
 * rename_file()
 *
 */
void rename_file(GtkWidget *widget, gpointer data)
{
  GtkWidget *dialog;
  GtkWidget *currentNameLabel;
  GtkWidget *currentNameEntry;
  GtkWidget *newNameLabel;
  GtkWidget *newNameEntry;
  /*GtkWidget *hbox1;*/
  GtkWidget *ok_button;
  GtkWidget *cancel_button;
  GtkWidget *help_button;

  /*g_print("Rename file goes here.\n");*/

  /*g_print("data=%s\n", (char *)data);*/

  /* --- Create the dialog --- */
  dialog = gtk_dialog_new();

  /* --- Trap the window close signal to release the grab --- */
  gtk_signal_connect(GTK_OBJECT(dialog), "destroy",
                      GTK_SIGNAL_FUNC(closing_dialog),
                      &dialog);

  /* --- Set the title --- */
  gtk_window_set_title(GTK_WINDOW(dialog), "Rename");

  /* --- Add a small border --- */
  gtk_container_border_width(GTK_CONTAINER(dialog), 5);

  /*hbox1 = gtk_hbox_new(FALSE, 0);
  gtk_widget_show(hbox1);*/

  currentNameLabel = gtk_label_new("Current name: ");
  gtk_widget_show(currentNameLabel);
  gtk_box_pack_start(GTK_BOX(GTK_DIALOG(dialog)->vbox), currentNameLabel, TRUE, TRUE, 0);

  currentNameEntry = gtk_entry_new();
  gtk_widget_show(currentNameEntry);
  gtk_box_pack_start(GTK_BOX(GTK_DIALOG(dialog)->vbox), currentNameEntry, TRUE, TRUE, 0);

  newNameLabel = gtk_label_new("New name: ");
  gtk_widget_show(newNameLabel);
  gtk_box_pack_start(GTK_BOX(GTK_DIALOG(dialog)->vbox), newNameLabel, TRUE, TRUE, 0);

  newNameEntry = gtk_entry_new();
  gtk_widget_show(newNameEntry);
  gtk_box_pack_start(GTK_BOX(GTK_DIALOG(dialog)->vbox), newNameEntry, TRUE, TRUE, 0);

  /* FIXME -- need to add path separator widgets here */

  /*
   * --- OK button
   */

  /* --- Create the "OK" button --- */
  ok_button = gtk_button_new_with_label("OK");

  gtk_signal_connect(GTK_OBJECT(ok_button), "clicked",
                     GTK_SIGNAL_FUNC(okfunc_select_volume),
                     dialog);

  /* --- Allow "Cancel" to be a default --- */
  GTK_WIDGET_SET_FLAGS(ok_button, GTK_CAN_DEFAULT);

  /* --- Add the OK button to the bottom hbox2 --- */
  gtk_box_pack_start(GTK_BOX(GTK_DIALOG(dialog)->action_area), ok_button, TRUE, TRUE, 0);

  /* --- Make the "OK" the default --- */
  gtk_widget_grab_default(ok_button);

  /* --- Make the button visible --- */
  gtk_widget_show(ok_button);

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
                     GTK_SIGNAL_FUNC(help_func_select_volume),
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

