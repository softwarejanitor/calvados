#include <gtk/gtk.h>

#include "calvados.h"

/*
 *
 * testSelectedFilesRbCallback()
 *
 */
void testSelectedFilesRbCallback(GtkWidget *widget, gpointer data)
{
  /* --- Display message --- */
  g_print("clicked %s\n", (char *)data);
}


/*
 *
 * testAllFilesRbCallback()
 *
 */
void testAllFilesRbCallback(GtkWidget *widget, gpointer data)
{
  /* --- Display message --- */
  g_print("clicked %s\n", (char *)data);
}


/*
 *
 * do_test()
 *
 */
void do_test(GtkWidget *widget, gpointer data)
{
  /* --- Display message --- */
  g_print("Do Test function goes here.\n");
}


/*
 *
 * test()
 *
 * Display test dialog
 *
 */
void test(GtkWidget *widget, gpointer data)
{
  GtkWidget *dialog;
  GtkWidget *vbox;
  GtkWidget *filesFrame;
  GSList *filesRbGroup = NULL;
  GtkWidget *testSelectedFilesRb;
  GtkWidget *testAllFilesRb;
  GtkWidget *hbox;
  GtkWidget *test_button;
  GtkWidget *cancel_button;

  /* --- Display message --- */
  g_print("test goes here\n");

  /* --- Create the dialog --- */
  dialog = gtk_dialog_new();

  /* --- Trap the window close signal to release the grab --- */
  gtk_signal_connect(GTK_OBJECT(dialog), "destroy",
                      GTK_SIGNAL_FUNC(closing_dialog),
                      &dialog);

  /* --- Set the title --- */
  gtk_window_set_title(GTK_WINDOW(dialog), "Test Files");

  /* --- Add a small border --- */
  gtk_container_border_width(GTK_CONTAINER(dialog), 5);

  filesFrame = gtk_frame_new("Files");
  gtk_box_pack_start(GTK_BOX(GTK_DIALOG(dialog)->vbox), filesFrame, TRUE, TRUE, 0);
  gtk_widget_show(filesFrame);

  vbox = gtk_vbox_new(FALSE, 0);
  gtk_container_add(GTK_CONTAINER(filesFrame), vbox);
  gtk_widget_show(vbox);

  testSelectedFilesRb = create_radio(vbox, &filesRbGroup, "Test selected files");
  testAllFilesRb = create_radio(vbox, &filesRbGroup, "Test all files");

  gtk_signal_connect(GTK_OBJECT(testSelectedFilesRb), "clicked", GTK_SIGNAL_FUNC(testSelectedFilesRbCallback), (gpointer)"testSelectedFilesRb");
  gtk_signal_connect(GTK_OBJECT(testAllFilesRb), "clicked", GTK_SIGNAL_FUNC(testAllFilesRbCallback), (gpointer)"testAllFilesRb");

  hbox = gtk_hbox_new(FALSE, 0);
  gtk_box_pack_start(GTK_BOX(GTK_DIALOG(dialog)->vbox), hbox, TRUE, TRUE, 0);
  gtk_widget_show(hbox);

  /*
   * --- Test button
   */

  /* --- Create the "Test" button --- */
  test_button = gtk_button_new_with_label("Test");

  gtk_signal_connect(GTK_OBJECT(test_button), "clicked",
                     GTK_SIGNAL_FUNC(do_test),
                     dialog);

  /* --- Allow "Test" to be a default --- */
  GTK_WIDGET_SET_FLAGS(test_button, GTK_CAN_DEFAULT);

  /* --- Add the Test button to the vbox --- */
  gtk_box_pack_start(GTK_BOX(hbox), test_button, TRUE, TRUE, 0);

  /* --- Make the "Test" the default --- */
  gtk_widget_grab_default(test_button);

  /* --- Make the button visible --- */
  gtk_widget_show(test_button);

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
  gtk_box_pack_start(GTK_BOX(hbox), cancel_button, TRUE, TRUE, 0);

  /* --- Make the button visible. --- */
  gtk_widget_show(cancel_button);

  /* --- Show the dialog --- */
  gtk_widget_show(dialog);

  /* --- Only this window can be used for now --- */
  gtk_grab_add(dialog);
}

