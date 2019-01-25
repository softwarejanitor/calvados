#include <gtk/gtk.h>
#include <gdk/gdkkeysyms.h>

#include "calvados.h"

extern GtkWidget *s140kRb;
extern GtkWidget *s800kRb;
extern GtkWidget *s14MRb;
extern GtkWidget *s5MBRb;
extern GtkWidget *s16MBRb;
extern GtkWidget *s20MBRb;
extern GtkWidget *s32MBRb;

/*
 *
 * okfunc_create_disk_image()
 *
 * OK Function for create disk image
 *
 * Show that the "OK" button was pressed
 *
 */
void okfunc_create_disk_image(GtkWidget *widget, gpointer data)
{
  /* --- Display message --- */
  g_print("Create function goes here.\n");

  if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(s140kRb)) == TRUE) {
    g_print("140k\n");
  }
  if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(s800kRb)) == TRUE) {
    g_print("800k\n");
  }

  /* --- Close it. --- */
  gtk_widget_destroy(GTK_WIDGET(data));
}

