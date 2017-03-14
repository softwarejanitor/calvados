#include <gtk/gtk.h>
#include <gdk/gdkkeysyms.h>

#include "calvados.h"

/*
 *
 * create_disk_image()
 *
 * Create Disk Image dialog box.
 *
 */
void create_disk_image()
{
  GtkWidget *dialog_window;
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
  GtkWidget *s140kRb;
  GtkWidget *s800kRb;
  GtkWidget *s14MRb;
  GtkWidget *s5MBRb;
  GtkWidget *s16MBRb;
  GtkWidget *s20MBRb;
  GtkWidget *s32MBRb;
  GtkWidget *specifyRb;
  GtkWidget *blocksEntry;
  GtkWidget *blocksLabel;
  GtkWidget *specifyHbox;
  GtkWidget *allocateDOSTracksCb;
  GtkWidget *diskVolumeLabel;
  GtkWidget *diskVolumeEntry;
  GtkWidget *diskVolumeHbox;
  GtkWidget *prodosVolumeLabel;
  GtkWidget *prodosVolumeEntry;
  GtkWidget *pascalVolumeLabel;
  GtkWidget *pascalVolumeEntry;
  GtkWidget *hfsVolumeLabel;
  GtkWidget *hfsVolumeEntry;

  /* --- Create the dialog --- */
  dialog_window = gtk_dialog_new();

  /* --- Trap the window close signal to release the grab --- */
  gtk_signal_connect(GTK_OBJECT(dialog_window), "destroy",
                      GTK_SIGNAL_FUNC(closing_dialog),
                      &dialog_window);

  /* --- Set the title --- */
  gtk_window_set_title(GTK_WINDOW(dialog_window), "Create Disk Image");

  /* --- Add a small border --- */
  gtk_container_border_width(GTK_CONTAINER(dialog_window), 5);

  /* Two columns top portion of dialog vbox */
  hbox1 = gtk_hbox_new(FALSE, 0);
  gtk_box_pack_start(GTK_BOX(GTK_DIALOG(dialog_window)->vbox), hbox1, TRUE, TRUE, 0);

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

  dos32Rb = gtk_radio_button_new_with_label(NULL, "DOS 3.2 (13-sector)");
  dos33Rb = gtk_radio_button_new_with_label_from_widget(GTK_RADIO_BUTTON(dos32Rb), "DOS 3.3");
  prodosRb = gtk_radio_button_new_with_label_from_widget(GTK_RADIO_BUTTON(dos33Rb), "ProDOS");
  pascalRb = gtk_radio_button_new_with_label_from_widget(GTK_RADIO_BUTTON(prodosRb), "Pascal");
  hfsRb = gtk_radio_button_new_with_label_from_widget(GTK_RADIO_BUTTON(pascalRb), "HFS");
  blankRb = gtk_radio_button_new_with_label_from_widget(GTK_RADIO_BUTTON(hfsRb), "Blank");

  gtk_box_pack_start(GTK_BOX(filesystemVbox), dos32Rb, TRUE, TRUE, 0);
  gtk_box_pack_start(GTK_BOX(filesystemVbox), dos33Rb, TRUE, TRUE, 0);
  gtk_box_pack_start(GTK_BOX(filesystemVbox), prodosRb, TRUE, TRUE, 0);
  gtk_box_pack_start(GTK_BOX(filesystemVbox), pascalRb, TRUE, TRUE, 0);
  gtk_box_pack_start(GTK_BOX(filesystemVbox), hfsRb, TRUE, TRUE, 0);
  gtk_box_pack_start(GTK_BOX(filesystemVbox), blankRb, TRUE, TRUE, 0);

  gtk_widget_show(dos32Rb);
  gtk_widget_show(dos33Rb);
  gtk_widget_show(prodosRb);
  gtk_widget_show(pascalRb);
  gtk_widget_show(hfsRb);
  gtk_widget_show(blankRb);

  s140kRb = gtk_radio_button_new_with_label(NULL, "140KB (5.25\" floppy)");
  s800kRb = gtk_radio_button_new_with_label_from_widget(GTK_RADIO_BUTTON(s140kRb), "800KB (3.5\" floppy)");
  s14MRb = gtk_radio_button_new_with_label_from_widget(GTK_RADIO_BUTTON(s800kRb), "1.4MB (3.5\" PC floppy)");
  s5MBRb = gtk_radio_button_new_with_label_from_widget(GTK_RADIO_BUTTON(s14MRb), "5MB");
  s16MBRb = gtk_radio_button_new_with_label_from_widget(GTK_RADIO_BUTTON(s5MBRb), "16MB");
  s20MBRb = gtk_radio_button_new_with_label_from_widget(GTK_RADIO_BUTTON(s16MBRb), "20MB");
  s32MBRb = gtk_radio_button_new_with_label_from_widget(GTK_RADIO_BUTTON(s20MBRb), "32MB (largest ProDOS volume)");
  specifyRb = gtk_radio_button_new_with_label_from_widget(GTK_RADIO_BUTTON(s32MBRb), "Specify size:");

  specifyHbox = gtk_hbox_new(FALSE, 0);

  blocksEntry = gtk_entry_new();
  gtk_entry_set_max_length(GTK_ENTRY(blocksEntry), 8);

  blocksLabel = gtk_label_new(" blocks");
  gtk_misc_set_alignment(GTK_MISC(blocksLabel), 0, 0.5);

  gtk_box_pack_start(GTK_BOX(specifyHbox), specifyRb, TRUE, TRUE, 0);
  gtk_box_pack_start(GTK_BOX(specifyHbox), blocksEntry, TRUE, TRUE, 0);
  gtk_box_pack_start(GTK_BOX(specifyHbox), blocksLabel, TRUE, TRUE, 0);

  gtk_box_pack_start(GTK_BOX(newDiskSizeVbox), s140kRb, TRUE, TRUE, 0);
  gtk_box_pack_start(GTK_BOX(newDiskSizeVbox), s800kRb, TRUE, TRUE, 0);
  gtk_box_pack_start(GTK_BOX(newDiskSizeVbox), s14MRb, TRUE, TRUE, 0);
  gtk_box_pack_start(GTK_BOX(newDiskSizeVbox), s5MBRb, TRUE, TRUE, 0);
  gtk_box_pack_start(GTK_BOX(newDiskSizeVbox), s16MBRb, TRUE, TRUE, 0);
  gtk_box_pack_start(GTK_BOX(newDiskSizeVbox), s20MBRb, TRUE, TRUE, 0);
  gtk_box_pack_start(GTK_BOX(newDiskSizeVbox), s32MBRb, TRUE, TRUE, 0);
  gtk_box_pack_start(GTK_BOX(newDiskSizeVbox), specifyHbox, TRUE, TRUE, 0);

  gtk_widget_show(s140kRb);
  gtk_widget_show(s800kRb);
  gtk_widget_show(s14MRb);
  gtk_widget_show(s5MBRb);
  gtk_widget_show(s16MBRb);
  gtk_widget_show(s20MBRb);
  gtk_widget_show(s32MBRb);
  gtk_widget_show(specifyRb);
  gtk_widget_show(blocksEntry);
  gtk_widget_show(blocksLabel);
  gtk_widget_show(specifyHbox);

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

  /*
   * --- OK button
   */

  /* --- Create the "OK" button --- */
  ok_button = gtk_button_new_with_label("OK");

  gtk_signal_connect(GTK_OBJECT(ok_button), "clicked",
                     GTK_SIGNAL_FUNC(okfunc_create_disk_image),
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
                     GTK_SIGNAL_FUNC(help_func_create_disk_image),
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

