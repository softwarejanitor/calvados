#include <gtk/gtk.h>
#include <gdk/gdkkeysyms.h>

/*
 *
 * show_about()
 *
 * Show the about box
 *
 */
void show_about(GtkWidget *widget, gpointer data)
{
  GdkPixbuf *pixbuf = gdk_pixbuf_new_from_file("images/calvados.png", NULL);

  GtkWidget *dialog = gtk_about_dialog_new();
  gtk_about_dialog_set_name(GTK_ABOUT_DIALOG(dialog), "Calvados");
  gtk_about_dialog_set_version(GTK_ABOUT_DIALOG(dialog), "0.2");
  gtk_about_dialog_set_copyright(GTK_ABOUT_DIALOG(dialog),"(c) 2017 Leeland Heins");
  gtk_about_dialog_set_comments(GTK_ABOUT_DIALOG(dialog),
     "Calvados is intended to be a work-alike of CiderPress for Linux.");
  gtk_about_dialog_set_website(GTK_ABOUT_DIALOG(dialog),
     "http://softwarejanitor.com");
  gtk_about_dialog_set_logo(GTK_ABOUT_DIALOG(dialog), pixbuf);
  g_object_unref(pixbuf), pixbuf = NULL;
  gtk_dialog_run(GTK_DIALOG(dialog));
  gtk_widget_destroy(dialog);
}

