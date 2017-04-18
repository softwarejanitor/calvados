#include <gtk/gtk.h>
#include <gdk/gdkkeysyms.h>

#include "calvados.h"

/*
 *
 * upRbCallback()
 *
 */
void upRbCallback(GtkWidget *widget, gpointer data)
{
  /* --- Display message --- */
  g_print("clicked %s\n", (char *)data);
}


/*
 *
 * downRbCallback()
 *
 */
void downRbCallback(GtkWidget *widget, gpointer data)
{
  /* --- Display message --- */
  g_print("clicked %s\n", (char *)data);
}


/*
 *
 * find_next()
 *
 */
void find_next(GtkWidget *widget, gpointer data)
{
  /* --- Display message --- */
  g_print("Find Next function goes here.\n");
}


/*
 *
 * find()
 *
 * Find from the menu.
 *
 */
void find(GtkWidget *widget, gpointer data)
{
  GtkWidget *dialog;
  GtkWidget *hbox1;
  GtkWidget *vbox1;
  GtkWidget *vbox2;
  GtkWidget *vbox3;
  GtkWidget *vbox4;
  GtkWidget *hbox2;
  GtkWidget *hbox3;
  GtkWidget *findWhatLabel;
  GtkWidget *findWhatEntry;
  GtkWidget *matchWholeWordOnlyCb;
  GtkWidget *matchCaseCb;
  GtkWidget *directionFrame;
  GSList *directionRbGroup = NULL;
  GtkWidget *upRb;
  GtkWidget *downRb;
  GtkWidget *find_next_button;
  GtkWidget *cancel_button;

  /* --- Display message --- */
  /*g_print("Find function goes here.\n");*/

  /* --- Create the dialog --- */
  dialog = gtk_dialog_new();

  /* --- Trap the window close signal to release the grab --- */
  gtk_signal_connect(GTK_OBJECT(dialog), "destroy",
                      GTK_SIGNAL_FUNC(closing_dialog),
                      &dialog);

  /* --- Set the title --- */
  gtk_window_set_title(GTK_WINDOW(dialog), "Find");

  /* --- Add a small border --- */
  gtk_container_border_width(GTK_CONTAINER(dialog), 5);

  hbox1 = gtk_hbox_new(FALSE, 0);
  gtk_box_pack_start(GTK_BOX(GTK_DIALOG(dialog)->vbox), hbox1, TRUE, TRUE, 0);
  gtk_widget_show(hbox1);

  vbox1 = gtk_vbox_new(FALSE, 0);
  gtk_box_pack_start(GTK_BOX(hbox1), vbox1, TRUE, TRUE, 0);
  gtk_widget_show(vbox1);

  hbox2 = gtk_hbox_new(FALSE, 0);
  gtk_box_pack_start(GTK_BOX(vbox1), hbox2, TRUE, TRUE, 0);
  gtk_widget_show(hbox2);

  findWhatLabel = gtk_label_new("Find What: ");
  gtk_misc_set_alignment(GTK_MISC(findWhatLabel), 0, 0.5);
  gtk_box_pack_start(GTK_BOX(hbox2), findWhatLabel, TRUE, TRUE, 0);
  gtk_widget_show(findWhatLabel);

  findWhatEntry = gtk_entry_new();
  gtk_box_pack_start(GTK_BOX(hbox2), findWhatEntry, TRUE, TRUE, 0);
  gtk_widget_show(findWhatEntry);

  hbox3 = gtk_hbox_new(FALSE, 0);
  gtk_box_pack_start(GTK_BOX(vbox1), hbox3, TRUE, TRUE, 0);
  gtk_widget_show(hbox3);

  vbox2 = gtk_vbox_new(FALSE, 0);
  gtk_box_pack_start(GTK_BOX(hbox3), vbox2, TRUE, TRUE, 0);
  gtk_widget_show(vbox2);

  matchWholeWordOnlyCb = gtk_check_button_new_with_label("Match Whole Word Only");
  gtk_box_pack_start(GTK_BOX(vbox2), matchWholeWordOnlyCb, TRUE, TRUE, 0);
  gtk_widget_show(matchWholeWordOnlyCb);

  matchCaseCb = gtk_check_button_new_with_label("Match Cased Only");
  gtk_box_pack_start(GTK_BOX(vbox2), matchCaseCb, TRUE, TRUE, 0);
  gtk_widget_show(matchCaseCb);

  directionFrame = gtk_frame_new("Direction");
  gtk_box_pack_start(GTK_BOX(hbox3), directionFrame, TRUE, TRUE, 0);
  gtk_widget_show(directionFrame);

  vbox3 = gtk_vbox_new(FALSE, 0);
  gtk_container_add(GTK_CONTAINER(directionFrame), vbox3);
  gtk_widget_show(vbox3);

  upRb = create_radio(vbox3, &directionRbGroup, "Up");
  downRb = create_radio(vbox3, &directionRbGroup, "Down");

  gtk_signal_connect(GTK_OBJECT(upRb), "clicked", GTK_SIGNAL_FUNC(upRbCallback), (gpointer)"upRb");
  gtk_signal_connect(GTK_OBJECT(downRb), "clicked", GTK_SIGNAL_FUNC(downRbCallback), (gpointer)"downRb");

  vbox4 = gtk_vbox_new(FALSE, 0);
  gtk_box_pack_start(GTK_BOX(hbox1), vbox4, TRUE, TRUE, 0);
  gtk_widget_show(vbox4);

  /*
   * --- Find Next button
   */

  /* --- Create the "Find Next" button --- */
  find_next_button = gtk_button_new_with_label("Find Next");

  gtk_signal_connect(GTK_OBJECT(find_next_button), "clicked",
                     GTK_SIGNAL_FUNC(find_next),
                     dialog);

  /* --- Allow "Cancel" to be a default --- */
  GTK_WIDGET_SET_FLAGS(find_next_button, GTK_CAN_DEFAULT);

  /* --- Add the Find Next button to the bottom hbox2 --- */
  gtk_box_pack_start(GTK_BOX(vbox4), find_next_button, TRUE, TRUE, 0);

  /* --- Make the "Find Next" the default --- */
  gtk_widget_grab_default(find_next_button);

  /* --- Make the button visible --- */
  gtk_widget_show(find_next_button);

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
  gtk_box_pack_start(GTK_BOX(vbox4), cancel_button, TRUE, TRUE, 0);

  /* --- Make the button visible. --- */
  gtk_widget_show(cancel_button);

  /* --- Show the dialog --- */
  gtk_widget_show(dialog);

  /* --- Only this window can be used for now --- */
  gtk_grab_add(dialog);
}

