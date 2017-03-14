#include <gtk/gtk.h>
#include <gdk/gdkkeysyms.h>

#include "calvados.h"

enum {
  COL_VOLUME_OR_DEVICE_NAME = 0,
  COL_REMARK,
  NUM_SELECT_VOLUME_COLS
};


/*
 *
 * select_volume()
 *
 * Select volume dialog box
 *
 */
void select_volume()
{
  GtkWidget *dialog_window;
  GtkWidget *ok_button;
  GtkWidget *cancel_button;
  GtkWidget *help_button;
  GtkWidget *showLabel;
  GList *showComboItems = NULL;
  GtkWidget *showCombo;
  GtkWidget *showHbox;
  GtkListStore *store;
  /*GtkTreeIter iter;*/
  GtkCellRenderer *renderer;
  GtkTreeModel *model;
  GtkWidget *view;
  GtkWidget *openAsReadOnlyCB;

  /* --- Create the dialog --- */
  dialog_window = gtk_dialog_new();

  /* --- Trap the window close signal to release the grab --- */
  gtk_signal_connect(GTK_OBJECT(dialog_window), "destroy",
                      GTK_SIGNAL_FUNC(closing_dialog),
                      &dialog_window);

  /* --- Set the title --- */
  gtk_window_set_title(GTK_WINDOW(dialog_window), "Select Volume");

  /* --- Add a small border --- */
  gtk_container_border_width(GTK_CONTAINER(dialog_window), 5);

  showHbox = gtk_hbox_new(FALSE, 0);

  showLabel = gtk_label_new("Show: ");
  gtk_misc_set_alignment(GTK_MISC(showLabel), 0, 0.5);

  /*
   * --- Create a list of the items first
   */
  showComboItems = g_list_append(showComboItems, "Both logical and physical");
  showComboItems = g_list_append(showComboItems, "Logical volumes");
  showComboItems = g_list_append(showComboItems, "Physical disks");

  /* --- Make a combo box. --- */
  showCombo = gtk_combo_new();

  /* --- Create the drop down portion of the combo --- */
  gtk_combo_set_popdown_strings(GTK_COMBO(showCombo), showComboItems);

  /* --- Default the text in the field to a value --- */
  gtk_entry_set_text(GTK_ENTRY(GTK_COMBO(showCombo)->entry), "Both logical and physical");

  /* --- Make the edit portion non-editable.  They can pick a
   *     value from the drop down, they just can't end up with
   *     a value that's not in the drop down.
   */
  gtk_entry_set_editable(GTK_ENTRY(GTK_COMBO(showCombo)->entry), FALSE);

  gtk_box_pack_start(GTK_BOX(showHbox), showLabel, TRUE, TRUE, 0);
  gtk_box_pack_start(GTK_BOX(showHbox), showCombo, TRUE, TRUE, 0);

  gtk_box_pack_start(GTK_BOX(GTK_DIALOG(dialog_window)->vbox), showHbox, TRUE, TRUE, 0);

  gtk_widget_show(showLabel);
  gtk_widget_show(showCombo);
  gtk_widget_show(showHbox);

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
                                              "Remark",
                                              renderer,
                                              "text", COL_REMARK,
                                              NULL);

  model = GTK_TREE_MODEL(store);

  gtk_tree_view_set_model(GTK_TREE_VIEW(view), model);

  /* The tree view has acquired its own reference to the
   *  model, so we can drop ours. That way the model will
   *  be freed automatically when the tree view is destroyed */
  g_object_unref(model);

  gtk_box_pack_start(GTK_BOX(GTK_DIALOG(dialog_window)->vbox), view, TRUE, TRUE, 0);

  gtk_widget_show(view);

  openAsReadOnlyCB = gtk_check_button_new_with_label("Open as read-only (writing to the volume will be disabled)");
  gtk_toggle_button_set_state(GTK_TOGGLE_BUTTON(openAsReadOnlyCB), TRUE);

  gtk_box_pack_start(GTK_BOX(GTK_DIALOG(dialog_window)->vbox), openAsReadOnlyCB, TRUE, TRUE, 0);

  gtk_widget_show(openAsReadOnlyCB);

  /*
   * --- OK button
   */

  /* --- Create the "OK" button --- */
  ok_button = gtk_button_new_with_label("OK");

  gtk_signal_connect(GTK_OBJECT(ok_button), "clicked",
                     GTK_SIGNAL_FUNC(okfunc_select_volume),
                     dialog_window);

  /* --- Allow "Cancel" to be a default --- */
  GTK_WIDGET_SET_FLAGS(ok_button, GTK_CAN_DEFAULT);

  /* --- Add the OK button to the bottom hbox2 --- */
  gtk_box_pack_start(GTK_BOX(GTK_DIALOG(dialog_window)->action_area), ok_button, TRUE, TRUE, 0);

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
                     dialog_window);

  /* --- Allow "Cancel" to be a default --- */
  GTK_WIDGET_SET_FLAGS(cancel_button, GTK_CAN_DEFAULT);

  /* --- Add the "Cancel" button to the dialog --- */
  gtk_box_pack_start(GTK_BOX(GTK_DIALOG(dialog_window)->action_area), cancel_button, TRUE, TRUE, 0);

  /* --- Make the button visible. --- */
  gtk_widget_show(cancel_button);

  /*
   * --- Help button
   */

  /* --- Create the "Help" button --- */
  help_button = gtk_button_new_with_label("Help");

  gtk_signal_connect(GTK_OBJECT(help_button), "clicked",
                     GTK_SIGNAL_FUNC(help_func_select_volume),
                     dialog_window);

  /* --- Add the "Help" button to the dialog --- */
  gtk_box_pack_start(GTK_BOX(GTK_DIALOG(dialog_window)->action_area), help_button, TRUE, TRUE, 0);

  /* --- Make the button visible. --- */
  gtk_widget_show(help_button);

  /* --- Show the dialog --- */
  gtk_widget_show(dialog_window);

  /* --- Only this window can be used for now --- */
  gtk_grab_add(dialog_window);
}

