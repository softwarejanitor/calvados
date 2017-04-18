#include <gtk/gtk.h>

#include "calvados.h"


/*
 *
 * dataForkRbCallback()
 *
 */
void dataForkRbCallback(GtkWidget *widget, gpointer *data)
{
  g_print("clicked %s\n", (char *)data);
}


/*
 *
 * resourceForkRbCallback()
 *
 */
void resourceForkRbCallback(GtkWidget *widget, gpointer *data)
{
  g_print("clicked %s\n", (char *)data);
}


/*
 *
 * commentRbCallback()
 *
 */
void commentRbCallback(GtkWidget *widget, gpointer *data)
{
  g_print("clicked %s\n", (char *)data);
}


/*
 *
 * view_next()
 *
 */
void view_next()
{
  g_print("view_next func goes here\n");
}


/*
 *
 * view_prev()
 *
 */
void view_prev()
{
  g_print("view_prev func goes here\n");
}


/*
 *
 * best()
 *
 */
void best_func()
{
  g_print("Best func goes here\n");
}


/*
 *
 * hex()
 *
 */
void hex_func()
{
  g_print("Hex func goes here\n");
}


/*
 *
 * raw()
 *
 */
void raw_func()
{
  g_print("Raw func goes here\n");
}


/*
 *
 * file_viewer()
 *
 * Display file viewer dialog box
 *
 */
void file_viewer(GtkWidget *widget, gpointer data)
{
  GtkWidget *dialog;
  GtkWidget *scrolled_window;
  GtkWidget *table;
  GtkWidget *hbox1;
  GtkWidget *vbox1;
  GtkWidget *vbox2;
  GtkWidget *vbox3;
  GtkWidget *vbox4;
  GtkWidget *hbox2;
  GtkWidget *hbox3;
  GtkWidget *hbox4;
  GSList *forkRbGroup = NULL;
  GtkWidget *dataForkRb;
  GtkWidget *resourceForkRb;
  GtkWidget *commentRb;
  GList *fileComboItems = NULL;
  GtkWidget *fileCombo;
  GtkWidget *next_button;
  GtkWidget *prev_button;
  GtkWidget *best_button;
  GtkWidget *hex_button;
  GtkWidget *raw_button;
  GtkWidget *find_button;
  GtkWidget *print_button;
  GtkWidget *font_button;
  GtkWidget *done_button;
  GtkWidget *help_button;

  /*g_print("File viewer dialog box goes here\n");*/

  /* --- Create the dialog --- */
  dialog = gtk_dialog_new();

  /* --- Trap the window close signal to release the grab --- */
  gtk_signal_connect(GTK_OBJECT(dialog), "destroy",
                      GTK_SIGNAL_FUNC(closing_dialog),
                      &dialog);

  /* --- Set the title --- */
  gtk_window_set_title(GTK_WINDOW(dialog), "File Viewer");
/* FIXME -- need to put filename in title. */

  /* --- Add a small border --- */
  gtk_container_border_width(GTK_CONTAINER(dialog), 5);

  /* create a new scrolled window. */
  scrolled_window = gtk_scrolled_window_new(NULL, NULL);
    
  gtk_widget_set_size_request(scrolled_window, 512, 256);

  gtk_container_set_border_width(GTK_CONTAINER(scrolled_window), 10);
    
  /* the policy is one of GTK_POLICY AUTOMATIC, or GTK_POLICY_ALWAYS.
   * GTK_POLICY_AUTOMATIC will automatically decide whether you need
   * scrollbars, whereas GTK_POLICY_ALWAYS will always leave the scrollbars
   * there.  The first one is the horizontal scrollbar, the second, 
   * the vertical. */
  gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scrolled_window),
                                 GTK_POLICY_AUTOMATIC, GTK_POLICY_ALWAYS);
  /* The dialog window is created with a vbox packed into it. */								
  gtk_box_pack_start(GTK_BOX(GTK_DIALOG(dialog)->vbox), scrolled_window, TRUE, TRUE, 0);
  gtk_widget_show(scrolled_window);

/* FIXME -- should display the file here */
  /* create a table of 10 by 10 squares. */
  table = gtk_table_new(10, 10, FALSE);
    
  /* set the spacing to 10 on x and 10 on y */
  gtk_table_set_row_spacings(GTK_TABLE(table), 10);
  gtk_table_set_col_spacings(GTK_TABLE(table), 10);
    
  /* pack the table into the scrolled window */
  gtk_scrolled_window_add_with_viewport(GTK_SCROLLED_WINDOW(scrolled_window), table);
  gtk_widget_show(table);

  hbox1 = gtk_hbox_new(FALSE, 0);
  gtk_box_pack_start(GTK_BOX(GTK_DIALOG(dialog)->action_area), hbox1, TRUE, TRUE, 0);
  gtk_widget_show(hbox1);

  vbox1 = gtk_vbox_new(FALSE, 0);
  gtk_box_pack_start(GTK_BOX(hbox1), vbox1, TRUE, TRUE, 0);
  gtk_widget_show(vbox1);
  
  vbox2 = gtk_vbox_new(FALSE, 0);
  gtk_box_pack_start(GTK_BOX(hbox1), vbox2, TRUE, TRUE, 0);
  gtk_widget_show(vbox2);
  
  dataForkRb = create_radio(vbox1, &forkRbGroup, "Data fork");
  resourceForkRb = create_radio(vbox1, &forkRbGroup, "Resource fork");
  commentRb = create_radio(vbox1, &forkRbGroup, "Comment");

  /* Set default selected item */
  gtk_toggle_button_set_state(GTK_TOGGLE_BUTTON(dataForkRb), TRUE);

  /* Default grey out resource fork radio button */
  gtk_widget_set_sensitive(resourceForkRb, FALSE);

  /* Default grey out comment radio button */
  gtk_widget_set_sensitive(commentRb, FALSE);

  /* Set up callbacks for radio buttons */
  gtk_signal_connect(GTK_OBJECT(dataForkRb), "clicked", GTK_SIGNAL_FUNC(dataForkRbCallback), (gpointer)"dataForkRb");
  gtk_signal_connect(GTK_OBJECT(resourceForkRb), "clicked", GTK_SIGNAL_FUNC(resourceForkRbCallback), (gpointer)"resourceForkRb");
  gtk_signal_connect(GTK_OBJECT(commentRb), "clicked", GTK_SIGNAL_FUNC(commentRbCallback), (gpointer)"commentRb");

  /*
   * --- Next button
   */

  /* --- Create the "Next" button --- */
  next_button = gtk_button_new_with_label("Next");

  gtk_signal_connect(GTK_OBJECT(next_button), "clicked",
                     GTK_SIGNAL_FUNC(view_next),
                     dialog);

  /* --- Allow "Next" to be a default --- */
  GTK_WIDGET_SET_FLAGS(next_button, GTK_CAN_DEFAULT);

  /* --- Add the Next button to the bottom right --- */
  gtk_box_pack_start(GTK_BOX(vbox2), next_button, TRUE, TRUE, 0);

  /* --- Make the "Next" the default --- */
  gtk_widget_grab_default(next_button);

  /* --- Make the button visible --- */
  gtk_widget_show(next_button);

  /*
   * --- Prev button
   */

  /* --- Create the "Prev" button --- */
  prev_button = gtk_button_new_with_label("Prev");

  gtk_signal_connect(GTK_OBJECT(prev_button), "clicked",
                     GTK_SIGNAL_FUNC(view_prev),
                     dialog);

  /* --- Allow "Prev" to be a default --- */
  GTK_WIDGET_SET_FLAGS(prev_button, GTK_CAN_DEFAULT);

  /* --- Add the Prev button to the bottom right --- */
  gtk_box_pack_start(GTK_BOX(vbox2), prev_button, TRUE, TRUE, 0);

  /* --- Make the "Prev" the default --- */
  gtk_widget_grab_default(prev_button);

  /* --- Make the button visible --- */
  gtk_widget_show(prev_button);

  vbox3 = gtk_vbox_new(FALSE, 0);
  gtk_box_pack_start(GTK_BOX(hbox1), vbox3, TRUE, TRUE, 0);
  gtk_widget_show(vbox3);
  
  vbox4 = gtk_vbox_new(FALSE, 0);
  gtk_box_pack_start(GTK_BOX(hbox1), vbox4, TRUE, TRUE, 0);
  gtk_widget_show(vbox4);
  
  /*
   * --- Create a list of the items first
   */
  fileComboItems = g_list_append(fileComboItems, "Converted Text");
  fileComboItems = g_list_append(fileComboItems, "Raw");
  fileComboItems = g_list_append(fileComboItems, "Hex Dump");
  fileComboItems = g_list_append(fileComboItems, "//e monitor listing");
  fileComboItems = g_list_append(fileComboItems, "IIgs monitor listing (long regs)");

  /* --- Make a combo box. --- */
  fileCombo = gtk_combo_new();

  /* --- Create the drop down portion of the combo --- */
  gtk_combo_set_popdown_strings(GTK_COMBO(fileCombo), fileComboItems);

  /* --- Default the text in the field to a value --- */
  gtk_entry_set_text(GTK_ENTRY(GTK_COMBO(fileCombo)->entry), "Converted Text");

  /* --- Make the edit portion non-editable.  They can pick a
   *     value from the drop down, they just can't end up with
   *     a value that's not in the drop down.
   */
  gtk_entry_set_editable(GTK_ENTRY(GTK_COMBO(fileCombo)->entry), FALSE);

  gtk_box_pack_start(GTK_BOX(vbox3), fileCombo, TRUE, TRUE, 0);

  gtk_widget_show(fileCombo);

  hbox2 = gtk_hbox_new(FALSE, 0);
  gtk_box_pack_start(GTK_BOX(vbox3), hbox2, TRUE, TRUE, 0);
  gtk_widget_show(hbox2);

  hbox3 = gtk_hbox_new(FALSE, 0);
  gtk_box_pack_start(GTK_BOX(vbox4), hbox3, TRUE, TRUE, 0);
  gtk_widget_show(hbox3);

  hbox4 = gtk_hbox_new(FALSE, 0);
  gtk_box_pack_start(GTK_BOX(vbox4), hbox4, TRUE, TRUE, 0);
  gtk_widget_show(hbox4);

  /*
   * --- Best button
   */

  /* --- Create the "Best" button --- */
  best_button = gtk_button_new_with_label("Best");

  gtk_signal_connect(GTK_OBJECT(best_button), "clicked",
                     GTK_SIGNAL_FUNC(best_func),
                     dialog);

  /* --- Allow "Best" to be a default --- */
  GTK_WIDGET_SET_FLAGS(best_button, GTK_CAN_DEFAULT);

  /* --- Add the Best button to the bottom right --- */
  gtk_box_pack_start(GTK_BOX(hbox2), best_button, TRUE, TRUE, 0);

  /* --- Make the "Best" the default --- */
  gtk_widget_grab_default(best_button);

  /* --- Make the button visible --- */
  gtk_widget_show(best_button);

  /*
   * --- Hex button
   */

  /* --- Create the "Hex" button --- */
  hex_button = gtk_button_new_with_label("Hex");

  gtk_signal_connect(GTK_OBJECT(hex_button), "clicked",
                     GTK_SIGNAL_FUNC(hex_func),
                     dialog);

  /* --- Allow "Hex" to be a default --- */
  GTK_WIDGET_SET_FLAGS(hex_button, GTK_CAN_DEFAULT);

  /* --- Add the Hex button to the bottom right --- */
  gtk_box_pack_start(GTK_BOX(hbox2), hex_button, TRUE, TRUE, 0);

  /* --- Make the "Hex" the default --- */
  gtk_widget_grab_default(hex_button);

  /* --- Make the button visible --- */
  gtk_widget_show(hex_button);

  /*
   * --- Raw button
   */

  /* --- Create the "Raw" button --- */
  raw_button = gtk_button_new_with_label("Raw");

  gtk_signal_connect(GTK_OBJECT(raw_button), "clicked",
                     GTK_SIGNAL_FUNC(raw_func),
                     dialog);

  /* --- Allow "Raw" to be a default --- */
  GTK_WIDGET_SET_FLAGS(raw_button, GTK_CAN_DEFAULT);

  /* --- Add the Raw button to the bottom right --- */
  gtk_box_pack_start(GTK_BOX(hbox2), raw_button, TRUE, TRUE, 0);

  /* --- Make the "Raw" the default --- */
  gtk_widget_grab_default(raw_button);

  /* --- Make the button visible --- */
  gtk_widget_show(raw_button);

  /*
   * --- Find button
   */

  /* --- Create the "Find" button --- */
  find_button = gtk_button_new_with_label("Find");

  gtk_signal_connect(GTK_OBJECT(find_button), "clicked",
                     GTK_SIGNAL_FUNC(findfunc_file_viewer),
                     dialog);

  /* --- Allow "Find" to be a default --- */
  GTK_WIDGET_SET_FLAGS(find_button, GTK_CAN_DEFAULT);

  /* --- Add the Find button to the bottom right --- */
  gtk_box_pack_start(GTK_BOX(hbox3), find_button, TRUE, TRUE, 0);

  /* --- Make the "Find" the default --- */
  gtk_widget_grab_default(find_button);

  /* --- Make the button visible --- */
  gtk_widget_show(find_button);

  /*
   * --- Font button
   */

  /* --- Create the "Font" button --- */
  font_button = gtk_button_new_with_label("Font");

  gtk_signal_connect(GTK_OBJECT(font_button), "clicked",
                     GTK_SIGNAL_FUNC(donefunc_file_viewer),
                     dialog);

  /* --- Allow "Font" to be a default --- */
  GTK_WIDGET_SET_FLAGS(font_button, GTK_CAN_DEFAULT);

  /* --- Add the Font button to the bottom right --- */
  gtk_box_pack_start(GTK_BOX(hbox3), font_button, TRUE, TRUE, 0);

  /* --- Make the "Font" the default --- */
  gtk_widget_grab_default(font_button);

  /* --- Make the button visible --- */
  gtk_widget_show(font_button);

  /*
   * --- Done button
   */

  /* --- Create the "Done" button --- */
  done_button = gtk_button_new_with_label("Done");

  gtk_signal_connect(GTK_OBJECT(done_button), "clicked",
                     GTK_SIGNAL_FUNC(donefunc_file_viewer),
                     dialog);

  /* --- Allow "Done" to be a default --- */
  GTK_WIDGET_SET_FLAGS(done_button, GTK_CAN_DEFAULT);

  /* --- Add the Done button to the bottom right --- */
  gtk_box_pack_start(GTK_BOX(hbox3), done_button, TRUE, TRUE, 0);

  /* --- Make the "Done" the default --- */
  gtk_widget_grab_default(done_button);

  /* --- Make the button visible --- */
  gtk_widget_show(done_button);

  /*
   * --- Print button
   */

  /* --- Create the "Print" button --- */
  print_button = gtk_button_new_with_label("Print");

  gtk_signal_connect(GTK_OBJECT(print_button), "clicked",
                     GTK_SIGNAL_FUNC(donefunc_file_viewer),
                     dialog);

  /* --- Allow "Print" to be a default --- */
  GTK_WIDGET_SET_FLAGS(print_button, GTK_CAN_DEFAULT);

  /* --- Add the Font button to the bottom right --- */
  gtk_box_pack_start(GTK_BOX(hbox4), print_button, TRUE, TRUE, 0);

  /* --- Make the "Print" the default --- */
  gtk_widget_grab_default(print_button);

  /* --- Make the button visible --- */
  gtk_widget_show(print_button);

  /*
   * --- Help button
   */

  /* --- Create the "Help" button --- */
  help_button = gtk_button_new_with_label("Help");

  gtk_signal_connect(GTK_OBJECT(help_button), "clicked",
                     GTK_SIGNAL_FUNC(help_func_file_viewer),
                     dialog);

  /* --- Add the "Help" button to the dialog --- */
  gtk_box_pack_start(GTK_BOX(hbox4), help_button, TRUE, TRUE, 0);

  /* --- Make the button visible. --- */
  gtk_widget_show(help_button);

  /* --- Show the dialog --- */
  gtk_widget_show(dialog);

  /* --- Only this window can be used for now --- */
  gtk_grab_add(dialog);
}

