#include <gtk/gtk.h>
#include <gtk/gtkunixprint.h>

#include "calvados.h"

GMainLoop *loop;

/*
 *
 * print_end()
 *
 */
static void print_end(GtkPrintJob *print_job, gpointer user_data, GError *err)
{
  g_main_loop_quit(loop);
  g_assert(err == NULL);
}


/*
 *
 * print_page()
 *
 */
void print_page(GtkWidget *widget, gpointer user_data)
{
  GtkWindow *parent = user_data;
  GtkPrintJob *print_job;
  GtkPrinter *printer;
  GtkPrintSettings *settings;
  GtkPageSetup *page_setup;
  GtkWidget *dialog;
  cairo_t *cr;
  cairo_surface_t *surface;

  dialog = gtk_print_unix_dialog_new(NULL, parent);
  if (gtk_dialog_run(GTK_DIALOG(dialog)) == GTK_RESPONSE_OK) {
    printer = gtk_print_unix_dialog_get_selected_printer(GTK_PRINT_UNIX_DIALOG(dialog));
    settings = gtk_print_unix_dialog_get_settings(GTK_PRINT_UNIX_DIALOG(dialog));
    page_setup = gtk_print_unix_dialog_get_page_setup(GTK_PRINT_UNIX_DIALOG(dialog));

    print_job = gtk_print_job_new("Example title", printer, settings, page_setup);
    surface = gtk_print_job_get_surface(print_job, NULL);

    cr = cairo_create(surface);

    cairo_set_source_rgb(cr, 0.6, 0.6, 0.6);
    cairo_set_line_width(cr, 1);

    cairo_rectangle(cr, 20, 20, 120, 80);
    cairo_rectangle(cr, 180, 20, 80, 80);
    cairo_stroke_preserve(cr);
    cairo_fill(cr);

    cairo_show_page(cr);

    cairo_surface_finish(surface);

    loop = g_main_loop_new(NULL,FALSE);

    gtk_print_job_send(print_job, print_end, NULL, NULL);

    g_main_loop_run(loop);

    cairo_destroy(cr);
    cairo_surface_destroy(surface);

    g_main_loop_unref(loop);
    g_object_unref(settings);
    g_object_unref(page_setup);
    g_object_unref(printer);
  }
  gtk_widget_destroy(dialog);

  return;
}

