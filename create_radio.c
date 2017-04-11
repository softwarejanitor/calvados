#include <gtk/gtk.h>

#include "calvados.h"

/*
 *
 * create_radio()
 *
 * Create a radio button.  Handles putting them into groups.
 *
 */
GtkWidget *create_radio(GtkWidget *box, GSList **group, char *rLabel)
{
  GtkWidget *radio;

  /* --- Get the radio button --- */
  radio = gtk_radio_button_new_with_label (*group, rLabel);

  *group = gtk_radio_button_group(GTK_RADIO_BUTTON(radio));

  /* --- Pack the radio button into the vertical/horizontal box (box).  --- */
  gtk_box_pack_start(GTK_BOX(box), radio, FALSE, FALSE, 10);

  /* --- Show the widget --- */
  gtk_widget_show(radio);

  return (radio);
}

