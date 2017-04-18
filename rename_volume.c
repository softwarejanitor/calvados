#include <gtk/gtk.h>

#include "calvados.h"

/*
 *
 * rename_volume()
 *
 * rename_volume Volume from the menu.
 *
 */
void rename_volume(GtkWidget *widget, gpointer data)
{
  GtkWidget *dialog;
  GtkWidget *selectVolumeLabel;
  /*GtkWidget *selectVolumeEntry;*/
  GtkListStore *store;
  /*GtkTreeIter iter;*/
  GtkCellRenderer *renderer;
  GtkTreeModel *model;
  GtkWidget *view;
  GtkWidget *newNameLabel;
  GtkWidget *newNameEntry;
  /*GtkWidget *hbox1;*/
  GtkWidget *ok_button;
  GtkWidget *cancel_button;
  GtkWidget *help_button;

  /* --- Display message --- */
  /*g_print("rename_volume function goes here.\n");*/

  /* --- Create the dialog --- */
  dialog = gtk_dialog_new();

  /* --- Trap the window close signal to release the grab --- */
  gtk_signal_connect(GTK_OBJECT(dialog), "destroy",
                      GTK_SIGNAL_FUNC(closing_dialog),
                      &dialog);

  /* --- Set the title --- */
  gtk_window_set_title(GTK_WINDOW(dialog), "Rename volume");

  /* --- Add a small border --- */
  gtk_container_border_width(GTK_CONTAINER(dialog), 5);

  /*hbox1 = gtk_hbox_new(FALSE, 0);
  gtk_widget_show(hbox1);*/
  selectVolumeLabel = gtk_label_new("Select a volume to rename: ");

  gtk_widget_show(selectVolumeLabel);
  gtk_box_pack_start(GTK_BOX(GTK_DIALOG(dialog)->vbox), selectVolumeLabel, TRUE, TRUE, 0);

  /*selectVolumeEntry = gtk_entry_new();
  gtk_widget_show(selectVolumeEntry);
  gtk_box_pack_start(GTK_BOX(GTK_DIALOG(dialog)->vbox), selectVolumeEntry, TRUE, TRUE, 0);*/

  store = gtk_list_store_new(NUM_SELECT_VOLUME_COLS, G_TYPE_STRING, G_TYPE_UINT);

/*FIXME*/
  /* This needs to be in a loop reading from somewhere */
  /* Append a row and fill in some data */
  /*gtk_list_store_append(store, &iter);
  gtk_list_store_set(store, &iter,
                     COL_VOLUME_OR_DEVICE_NAME, "",
                     COL_REMARK, "",
                     -1);*/

  view = gtk_tree_view_new();
  gtk_widget_set_size_request(view, 320, 256);

  /* --- Column #1 --- */
  renderer = gtk_cell_renderer_text_new();
  gtk_tree_view_insert_column_with_attributes(GTK_TREE_VIEW(view),
                                              -1,
                                              "Volume or Device Name",
                                              renderer,
                                              "text", COL_VOLUME_OR_DEVICE_NAME,
                                              NULL);

  /* --- Column #2 --- */
  renderer = gtk_cell_renderer_text_new();
  gtk_tree_view_insert_column_with_attributes(GTK_TREE_VIEW(view),
                                              -1,
                                              "Remarks",
                                              renderer,
                                              "text", COL_REMARK,
                                              NULL);

  model = GTK_TREE_MODEL(store);

  gtk_tree_view_set_model(GTK_TREE_VIEW(view), model);

  /* The tree view has acquired its own reference to the
   *  model, so we can drop ours. That way the model will
   *  be freed automatically when the tree view is destroyed */
  g_object_unref(model);

  gtk_box_pack_start(GTK_BOX(GTK_DIALOG(dialog)->vbox), view, TRUE, TRUE, 0);

  gtk_widget_show(view);

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

