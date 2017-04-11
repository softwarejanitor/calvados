#include <string.h>
#include <gtk/gtk.h>
#include <gdk/gdkkeysyms.h>
#include <gdk/gdkkeysyms-compat.h>

#include "calvados.h"

GtkWidget *allocateDOSTracksCb;
GtkWidget *diskVolumeEntry;
GtkWidget *prodosVolumeEntry;
GtkWidget *pascalVolumeEntry;
GtkWidget *hfsVolumeEntry;
GtkWidget *blocksEntry;
GtkWidget *blocksLabel;

/*
 *
 * Grey out radio buttons, checkboxes and entries as appropriate
 * for filesystem radio button group.
 *
 */
void filesystemRbCallback(GtkWidget *widget, gpointer *data)
{
  if ((strcmp((char *)data, "dos32Rb") == 0) ||
      (strcmp((char *)data, "dos33Rb") == 0)) {
    gtk_widget_set_sensitive(allocateDOSTracksCb, TRUE);
    gtk_widget_set_sensitive(diskVolumeEntry, TRUE);
    gtk_widget_set_sensitive(prodosVolumeEntry, FALSE);
    gtk_widget_set_sensitive(pascalVolumeEntry, FALSE);
    gtk_widget_set_sensitive(hfsVolumeEntry, FALSE);
  } else if (strcmp((char *)data, "prodosRb") == 0) {
    gtk_widget_set_sensitive(allocateDOSTracksCb, FALSE);
    gtk_widget_set_sensitive(diskVolumeEntry, FALSE);
    gtk_widget_set_sensitive(prodosVolumeEntry, TRUE);
    gtk_widget_set_sensitive(pascalVolumeEntry, FALSE);
    gtk_widget_set_sensitive(hfsVolumeEntry, FALSE);
  } else if (strcmp((char *)data, "pascalRb") == 0) {
    gtk_widget_set_sensitive(allocateDOSTracksCb, FALSE);
    gtk_widget_set_sensitive(diskVolumeEntry, FALSE);
    gtk_widget_set_sensitive(prodosVolumeEntry, FALSE);
    gtk_widget_set_sensitive(pascalVolumeEntry, TRUE);
    gtk_widget_set_sensitive(hfsVolumeEntry, FALSE);
  } else if (strcmp((char *)data, "hfsRb") == 0) {
    gtk_widget_set_sensitive(allocateDOSTracksCb, FALSE);
    gtk_widget_set_sensitive(diskVolumeEntry, FALSE);
    gtk_widget_set_sensitive(prodosVolumeEntry, FALSE);
    gtk_widget_set_sensitive(pascalVolumeEntry, FALSE);
    gtk_widget_set_sensitive(hfsVolumeEntry, TRUE);
  } else if (strcmp((char *)data, "blankRb") == 0) {
    gtk_widget_set_sensitive(allocateDOSTracksCb, FALSE);
    gtk_widget_set_sensitive(diskVolumeEntry, FALSE);
    gtk_widget_set_sensitive(prodosVolumeEntry, FALSE);
    gtk_widget_set_sensitive(pascalVolumeEntry, FALSE);
    gtk_widget_set_sensitive(hfsVolumeEntry, FALSE);
  }
}


void newDiskSizeRbCallback(GtkWidget *widget, gpointer *data)
{
  if (strcmp((char *)data, "specifyRb") == 0) {
    gtk_widget_set_sensitive(blocksEntry, TRUE);
    gtk_widget_set_sensitive(blocksLabel, TRUE);
  } else {
    gtk_widget_set_sensitive(blocksEntry, FALSE);
    gtk_widget_set_sensitive(blocksLabel, FALSE);
  }
}


/*
 *
 * create_disk_image()
 *
 * Create Disk Image dialog box.
 *
 */
void create_disk_image()
{
  GtkWidget *dialog;
  GtkWidget *ok_button;
  GtkWidget *cancel_button;
  GtkWidget *help_button;
  GtkWidget *hbox1;
  GtkWidget *vbox1;
  GtkWidget *vbox2;
  GtkWidget *filesystemFrame;
  GtkWidget *newDiskSizeFrame;
  GtkWidget *dosOptionsFrame;
  GtkWidget *prodosOptionsFrame;
  GtkWidget *pascalOptionsFrame;
  GtkWidget *hfsOptionsFrame;
  GtkWidget *filesystemVbox;
  GtkWidget *newDiskSizeVbox;
  GtkWidget *dosOptionsVbox;
  GtkWidget *prodosOptionsVbox;
  GtkWidget *pascalOptionsVbox;
  GtkWidget *hfsOptionsVbox;
  GtkWidget *dos32Rb;
  GtkWidget *dos33Rb;
  GtkWidget *prodosRb;
  GtkWidget *pascalRb;
  GtkWidget *hfsRb;
  GtkWidget *blankRb;
  GSList *filesystemRbGroup = NULL;
  GtkWidget *s140kRb;
  GtkWidget *s800kRb;
  GtkWidget *s14MRb;
  GtkWidget *s5MBRb;
  GtkWidget *s16MBRb;
  GtkWidget *s20MBRb;
  GtkWidget *s32MBRb;
  GtkWidget *specifyHbox;
  GtkWidget *specifyRb;
  GSList *newDiskSizeRbGroup = NULL;
  /*GtkWidget *allocateDOSTracksCb;*/
  GtkWidget *diskVolumeLabel;
  /*GtkWidget *diskVolumeEntry;*/
  GtkWidget *diskVolumeHbox;
  GtkWidget *prodosVolumeLabel;
  /*GtkWidget *prodosVolumeEntry;*/
  GtkWidget *pascalVolumeLabel;
  /*GtkWidget *pascalVolumeEntry;*/
  GtkWidget *hfsVolumeLabel;
  /*GtkWidget *hfsVolumeEntry;*/

  /* --- Create the dialog --- */
  dialog = gtk_dialog_new();

  /* --- Trap the window close signal to release the grab --- */
  gtk_signal_connect(GTK_OBJECT(dialog), "destroy",
                      GTK_SIGNAL_FUNC(closing_dialog),
                      &dialog);

  /* --- Set the title --- */
  gtk_window_set_title(GTK_WINDOW(dialog), "Create Disk Image");

  /* --- Add a small border --- */
  gtk_container_border_width(GTK_CONTAINER(dialog), 5);

  /* Two columns top portion of dialog vbox */
  hbox1 = gtk_hbox_new(FALSE, 0);
  gtk_box_pack_start(GTK_BOX(GTK_DIALOG(dialog)->vbox), hbox1, TRUE, TRUE, 0);

  gtk_widget_show(hbox1);

  /* Left column of hbox1 */
  vbox1 = gtk_vbox_new(FALSE, 0);
  gtk_box_pack_start(GTK_BOX(hbox1), vbox1, TRUE, TRUE, 0);

  /* Right column of hbox1 */
  vbox2 = gtk_vbox_new(FALSE, 0);
  gtk_box_pack_start(GTK_BOX(hbox1), vbox2, TRUE, TRUE, 0);

  gtk_widget_show(vbox1);
  gtk_widget_show(vbox2);

  /* Frames on left column */
  filesystemFrame = gtk_frame_new("Filesystem");
  newDiskSizeFrame = gtk_frame_new("New disk size");

  /* Frames on right column */
  dosOptionsFrame = gtk_frame_new("DOS options");
  prodosOptionsFrame = gtk_frame_new("ProDOS options");
  pascalOptionsFrame = gtk_frame_new("Pascal options");
  hfsOptionsFrame = gtk_frame_new("HFS options");

  gtk_box_pack_start(GTK_BOX(vbox1), filesystemFrame, TRUE, TRUE, 0);
  gtk_box_pack_start(GTK_BOX(vbox1), newDiskSizeFrame, TRUE, TRUE, 0);
  gtk_box_pack_start(GTK_BOX(vbox2), dosOptionsFrame, TRUE, TRUE, 0);
  gtk_box_pack_start(GTK_BOX(vbox2), prodosOptionsFrame, TRUE, TRUE, 0);
  gtk_box_pack_start(GTK_BOX(vbox2), pascalOptionsFrame, TRUE, TRUE, 0);
  gtk_box_pack_start(GTK_BOX(vbox2), hfsOptionsFrame, TRUE, TRUE, 0);

  gtk_widget_show(filesystemFrame);
  gtk_widget_show(newDiskSizeFrame);
  gtk_widget_show(dosOptionsFrame);
  gtk_widget_show(prodosOptionsFrame);
  gtk_widget_show(pascalOptionsFrame);
  gtk_widget_show(hfsOptionsFrame);

  filesystemVbox = gtk_vbox_new(FALSE, 0);
  gtk_container_add(GTK_CONTAINER(filesystemFrame), filesystemVbox);
  gtk_widget_show(filesystemVbox);

  newDiskSizeVbox = gtk_vbox_new(FALSE, 0);
  gtk_container_add(GTK_CONTAINER(newDiskSizeFrame), newDiskSizeVbox);
  gtk_widget_show(newDiskSizeVbox);

  dosOptionsVbox = gtk_vbox_new(FALSE, 0);
  gtk_container_add(GTK_CONTAINER(dosOptionsFrame), dosOptionsVbox);
  gtk_widget_show(dosOptionsVbox);

  prodosOptionsVbox = gtk_vbox_new(FALSE, 0);
  gtk_container_add(GTK_CONTAINER(prodosOptionsFrame), prodosOptionsVbox);
  gtk_widget_show(prodosOptionsVbox);

  pascalOptionsVbox = gtk_vbox_new(FALSE, 0);
  gtk_container_add(GTK_CONTAINER(pascalOptionsFrame), pascalOptionsVbox);
  gtk_widget_show(pascalOptionsVbox);

  hfsOptionsVbox = gtk_vbox_new(FALSE, 0);
  gtk_container_add(GTK_CONTAINER(hfsOptionsFrame), hfsOptionsVbox);
  gtk_widget_show(hfsOptionsVbox);

  dos32Rb = create_radio(filesystemVbox, &filesystemRbGroup, "DOS 3.2 (13-sector)");
  dos33Rb = create_radio(filesystemVbox, &filesystemRbGroup, "DOS 3.3");
  prodosRb = create_radio(filesystemVbox, &filesystemRbGroup, "ProDOS");
  pascalRb = create_radio(filesystemVbox, &filesystemRbGroup, "Pascal");
  hfsRb = create_radio(filesystemVbox, &filesystemRbGroup, "HFS");
  blankRb = create_radio(filesystemVbox, &filesystemRbGroup, "Blank");

  specifyHbox = gtk_hbox_new(FALSE, 0);
  gtk_widget_show(specifyHbox);

  s140kRb = create_radio(newDiskSizeVbox, &newDiskSizeRbGroup, "140KB (5.25\" floppy)");
  s800kRb = create_radio(newDiskSizeVbox, &newDiskSizeRbGroup, "800KB (3.5\" floppy)");
  s14MRb = create_radio(newDiskSizeVbox, &newDiskSizeRbGroup, "1.4MB (3.5\" PC floppy)");
  s5MBRb = create_radio(newDiskSizeVbox, &newDiskSizeRbGroup, "5MB");
  s16MBRb = create_radio(newDiskSizeVbox, &newDiskSizeRbGroup, "16MB");
  s20MBRb = create_radio(newDiskSizeVbox, &newDiskSizeRbGroup, "20MB");
  s32MBRb = create_radio(newDiskSizeVbox, &newDiskSizeRbGroup, "32MB (largest ProDOS volume)");
  specifyRb = create_radio(specifyHbox, &newDiskSizeRbGroup, "Specify size:");

  blocksEntry = gtk_entry_new();
  gtk_entry_set_max_length(GTK_ENTRY(blocksEntry), 8);
  gtk_box_pack_start(GTK_BOX(specifyHbox), blocksEntry, TRUE, TRUE, 0);
  gtk_widget_show(blocksEntry);

  blocksLabel = gtk_label_new(" blocks");
  gtk_misc_set_alignment(GTK_MISC(blocksLabel), 0, 0.5);
  gtk_box_pack_start(GTK_BOX(specifyHbox), blocksLabel, TRUE, TRUE, 0);
  gtk_widget_show(blocksLabel);

  gtk_box_pack_start(GTK_BOX(newDiskSizeVbox), specifyHbox, TRUE, TRUE, 0);

  allocateDOSTracksCb = gtk_check_button_new_with_label("Allocate DOS tracks");

  diskVolumeHbox = gtk_hbox_new(FALSE, 0);

  diskVolumeLabel = gtk_label_new("Disk volume: ");
  gtk_misc_set_alignment(GTK_MISC(diskVolumeLabel), 0, 0.5);

  diskVolumeEntry = gtk_entry_new();
  gtk_entry_set_max_length(GTK_ENTRY(diskVolumeEntry), 3);

  gtk_box_pack_start(GTK_BOX(diskVolumeHbox), diskVolumeLabel, TRUE, TRUE, 0);
  gtk_box_pack_start(GTK_BOX(diskVolumeHbox), diskVolumeEntry, TRUE, TRUE, 0);

  gtk_box_pack_start(GTK_BOX(dosOptionsVbox), allocateDOSTracksCb, TRUE, TRUE, 0);
  gtk_box_pack_start(GTK_BOX(dosOptionsVbox), diskVolumeHbox, TRUE, TRUE, 0);

  gtk_widget_show(allocateDOSTracksCb);
  gtk_widget_show(diskVolumeLabel);
  gtk_widget_show(diskVolumeEntry);
  gtk_widget_show(diskVolumeHbox);

  prodosVolumeLabel = gtk_label_new("ProDOS volume name (15 chars):");
  gtk_misc_set_alignment(GTK_MISC(prodosVolumeLabel), 0, 0.5);

  prodosVolumeEntry = gtk_entry_new();
  gtk_entry_set_max_length(GTK_ENTRY(prodosVolumeEntry), 15);

  gtk_box_pack_start(GTK_BOX(prodosOptionsVbox), prodosVolumeLabel, TRUE, TRUE, 0);
  gtk_box_pack_start(GTK_BOX(prodosOptionsVbox), prodosVolumeEntry, TRUE, TRUE, 0);

  gtk_widget_show(prodosVolumeLabel);
  gtk_widget_show(prodosVolumeEntry);

  pascalVolumeLabel = gtk_label_new("Pascal volume name (7 chars):");
  gtk_misc_set_alignment(GTK_MISC(pascalVolumeLabel), 0, 0.5);

  pascalVolumeEntry = gtk_entry_new();
  gtk_entry_set_max_length(GTK_ENTRY(pascalVolumeEntry), 15);

  gtk_box_pack_start(GTK_BOX(pascalOptionsVbox), pascalVolumeLabel, TRUE, TRUE, 0);
  gtk_box_pack_start(GTK_BOX(pascalOptionsVbox), pascalVolumeEntry, TRUE, TRUE, 0);

  gtk_widget_show(pascalVolumeLabel);
  gtk_widget_show(pascalVolumeEntry);

  hfsVolumeLabel = gtk_label_new("HFS volume name (27 chars):");
  gtk_misc_set_alignment(GTK_MISC(hfsVolumeLabel), 0, 0.5);

  hfsVolumeEntry = gtk_entry_new();
  gtk_entry_set_max_length(GTK_ENTRY(hfsVolumeEntry), 27);

  gtk_box_pack_start(GTK_BOX(hfsOptionsVbox), hfsVolumeLabel, TRUE, TRUE, 0);
  gtk_box_pack_start(GTK_BOX(hfsOptionsVbox), hfsVolumeEntry, TRUE, TRUE, 0);

  gtk_widget_show(hfsVolumeLabel);
  gtk_widget_show(hfsVolumeEntry);

  /* Set default selections. */
  gtk_toggle_button_set_state(GTK_TOGGLE_BUTTON(prodosRb), TRUE);
  gtk_toggle_button_set_state(GTK_TOGGLE_BUTTON(s140kRb), TRUE);
  gtk_toggle_button_set_state(GTK_TOGGLE_BUTTON(allocateDOSTracksCb), TRUE);

  gtk_entry_set_text(GTK_ENTRY(blocksEntry), "280");
  gtk_entry_set_text(GTK_ENTRY(diskVolumeEntry), "254");
  gtk_entry_set_text(GTK_ENTRY(prodosVolumeEntry), "NEW.DISK");
  gtk_entry_set_text(GTK_ENTRY(pascalVolumeEntry), "BLANK");
  gtk_entry_set_text(GTK_ENTRY(hfsVolumeEntry), "New Disk");

  /* Set default sensitivity to prodos */
  gtk_widget_set_sensitive(allocateDOSTracksCb, FALSE);
  gtk_widget_set_sensitive(diskVolumeEntry, FALSE);
  gtk_widget_set_sensitive(prodosVolumeEntry, TRUE);
  gtk_widget_set_sensitive(pascalVolumeEntry, FALSE);
  gtk_widget_set_sensitive(hfsVolumeEntry, FALSE);

  /* Set up callbacks for filesystem frame */
  gtk_signal_connect(GTK_OBJECT(dos32Rb), "clicked", GTK_SIGNAL_FUNC(filesystemRbCallback), (gpointer)"dos32Rb");
  gtk_signal_connect(GTK_OBJECT(dos33Rb), "clicked", GTK_SIGNAL_FUNC(filesystemRbCallback), (gpointer)"dos33Rb");
  gtk_signal_connect(GTK_OBJECT(prodosRb), "clicked", GTK_SIGNAL_FUNC(filesystemRbCallback), (gpointer)"prodosRb");
  gtk_signal_connect(GTK_OBJECT(pascalRb), "clicked", GTK_SIGNAL_FUNC(filesystemRbCallback), (gpointer)"pascalRb");
  gtk_signal_connect(GTK_OBJECT(hfsRb), "clicked", GTK_SIGNAL_FUNC(filesystemRbCallback), (gpointer)"hfsRb");
  gtk_signal_connect(GTK_OBJECT(blankRb), "clicked", GTK_SIGNAL_FUNC(filesystemRbCallback), (gpointer)"blankRb");

  /* Set up callbacks for new disk size frame */
  gtk_signal_connect(GTK_OBJECT(s140kRb), "clicked", GTK_SIGNAL_FUNC(newDiskSizeRbCallback), (gpointer)"s140kRb");
  gtk_signal_connect(GTK_OBJECT(s800kRb), "clicked", GTK_SIGNAL_FUNC(newDiskSizeRbCallback), (gpointer)"s800kRb");
  gtk_signal_connect(GTK_OBJECT(s14MRb), "clicked", GTK_SIGNAL_FUNC(newDiskSizeRbCallback), (gpointer)"s14MRb");
  gtk_signal_connect(GTK_OBJECT(s5MBRb), "clicked", GTK_SIGNAL_FUNC(newDiskSizeRbCallback), (gpointer)"s5MBRb");
  gtk_signal_connect(GTK_OBJECT(s16MBRb), "clicked", GTK_SIGNAL_FUNC(newDiskSizeRbCallback), (gpointer)"s16MBRb");
  gtk_signal_connect(GTK_OBJECT(s20MBRb), "clicked", GTK_SIGNAL_FUNC(newDiskSizeRbCallback), (gpointer)"s20MBRb");
  gtk_signal_connect(GTK_OBJECT(s32MBRb), "clicked", GTK_SIGNAL_FUNC(newDiskSizeRbCallback), (gpointer)"s32MBRb");
  gtk_signal_connect(GTK_OBJECT(specifyRb), "clicked", GTK_SIGNAL_FUNC(newDiskSizeRbCallback), (gpointer)"specifyRb");

  /* Set default sensitivity to not specify */
  gtk_widget_set_sensitive(blocksEntry, FALSE);
  gtk_widget_set_sensitive(blocksLabel, FALSE);

  /*
   * --- OK button
   */

  /* --- Create the "OK" button --- */
  ok_button = gtk_button_new_with_label("OK");

  gtk_signal_connect(GTK_OBJECT(ok_button), "clicked",
                     GTK_SIGNAL_FUNC(okfunc_create_disk_image),
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
                     GTK_SIGNAL_FUNC(help_func_create_disk_image),
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

