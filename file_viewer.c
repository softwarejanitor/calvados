#include <gtk/gtk.h>

#include "calvados.h"

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
  GtkWidget *dataForkRb;
  GtkWidget *resourceForkRb;
  GtkWidget *commentRb;
  GtkWidget *fileCombo;
  GtkWidget *next_button;
  GtkWidget *prev_button;
  GtkWidget *best_button;
  GtkWidget *raw_button;
  GtkWidget *find_button;
  GtkWidget *hbox2;
  GtkWidget *print_button;
  GtkWidget *font_button;
  GtkWidget *done_button;
  GtkWidget *help_button;

  g_print("File viewer dialog box goes here\n");

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

  hbox2 = gtk_hbox_new(FALSE, 0);
  gtk_box_pack_start(GTK_BOX(hbox1), hbox2, TRUE, TRUE, 0);
  gtk_widget_show(hbox2);
  
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
  gtk_box_pack_start(GTK_BOX(hbox2), done_button, TRUE, TRUE, 0);

  /* --- Make the "Done" the default --- */
  gtk_widget_grab_default(done_button);

  /* --- Make the button visible --- */
  gtk_widget_show(done_button);

  /*
   * --- Font button
   */

  /* --- Create the "Font" button --- */
  font_button = gtk_button_new_with_label("Font");

  gtk_signal_connect(GTK_OBJECT(done_button), "clicked",
                     GTK_SIGNAL_FUNC(donefunc_file_viewer),
                     dialog);

  /* --- Allow "Font" to be a default --- */
  GTK_WIDGET_SET_FLAGS(font_button, GTK_CAN_DEFAULT);

  /* --- Add the Font button to the bottom right --- */
  gtk_box_pack_start(GTK_BOX(hbox2), font_button, TRUE, TRUE, 0);

  /* --- Make the "Font" the default --- */
  gtk_widget_grab_default(font_button);

  /* --- Make the button visible --- */
  gtk_widget_show(font_button);

  /*
   * --- Find button
   */

  /* --- Create the "Find" button --- */
  find_button = gtk_button_new_with_label("Find");

  gtk_signal_connect(GTK_OBJECT(done_button), "clicked",
                     GTK_SIGNAL_FUNC(findfunc_file_viewer),
                     dialog);

  /* --- Allow "Font" to be a default --- */
  GTK_WIDGET_SET_FLAGS(find_button, GTK_CAN_DEFAULT);

  /* --- Add the Font button to the bottom right --- */
  gtk_box_pack_start(GTK_BOX(hbox2), find_button, TRUE, TRUE, 0);

  /* --- Make the "Find" the default --- */
  gtk_widget_grab_default(find_button);

  /* --- Make the button visible --- */
  gtk_widget_show(find_button);

  /*
   * --- Help button
   */

  /* --- Create the "Help" button --- */
  help_button = gtk_button_new_with_label("Help");

  gtk_signal_connect(GTK_OBJECT(help_button), "clicked",
                     GTK_SIGNAL_FUNC(help_func_file_viewer),
                     dialog);

  /* --- Add the "Help" button to the dialog --- */
  gtk_box_pack_start(GTK_BOX(hbox2), done_button, TRUE, TRUE, 0);

  /* --- Make the button visible. --- */
  gtk_widget_show(help_button);

  /* --- Show the dialog --- */
  gtk_widget_show(dialog);

  /* --- Only this window can be used for now --- */
  gtk_grab_add(dialog);
}

