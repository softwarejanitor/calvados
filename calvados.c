/*
 *
 * cavaldos.c
 *
 * Designed to be a workalike of CiderPress.
 *
 * 20170310 Leeland Heins
 *
 */
#include <gtk/gtk.h>
#include <gdk/gdkkeysyms.h>

#include "calvados.h"

int main(int argc, char *argv[])
{
  /* Our root window */
  GtkWidget *window;

  GtkWidget *vbox;

  GtkWidget *menubar;

  /* File menu widgets */
  GtkWidget *fileMenu;
  GtkWidget *newMenu;
  GtkWidget *diskImageMi;
  GtkWidget *shrinkItArchiveMi;
  GtkWidget *fileMi;
  GtkWidget *newMi;
  GtkWidget *openMi;
  GtkWidget *openVolumeMi;
  GtkWidget *reopenMi;
  GtkWidget *saveChangesMi;
  GtkWidget *closeMi;
  GtkWidget *fileSep1;
  GtkWidget *archiveInfoMi;
  GtkWidget *printMi;
  GtkWidget *fileSep2;
  GtkWidget *quitMi;

  /* Edit menu widgets */
  GtkWidget *editMenu;
  GtkWidget *editMi;
  GtkWidget *copyMi;
  GtkWidget *pasteMi;
  GtkWidget *pasteSpecialMi;
  GtkWidget *editSep1;
  GtkWidget *findMi;
  GtkWidget *editSep2;
  GtkWidget *sortMenu;
  GtkWidget *sortMi;
  GtkWidget *byOriginalOrderMi;
  GtkWidget *byPathnameMi;
  GtkWidget *byFileTypeMi;
  GtkWidget *byAuxtypeMi;
  GtkWidget *byModificationDateMi;
  GtkWidget *byFormatMi;
  GtkWidget *bySizeMi;
  GtkWidget *byRatioMi;
  GtkWidget *byPackedSizeMi;
  GtkWidget *byAccessMi;
  GtkWidget *selectAllMi;
  GtkWidget *invertSelectionMi;
  GtkWidget *preferencesMi;

  /* Action menu widgets */
  GtkWidget *actionMenu;
  GtkWidget *actionsMi;
  GtkWidget *viewMi;
  GtkWidget *extractMi;
  GtkWidget *testMi;
  GtkWidget *renameMi;
  GtkWidget *deleteMi;
  GtkWidget *recompressMi;
  GtkWidget *actionSep1;
  GtkWidget *addFilesMi;
  GtkWidget *addDiskImageMi;
  GtkWidget *createSubdirectoryMi;
  GtkWidget *actionSep2;
  GtkWidget *openAsDiskImageMi;
  GtkWidget *editCommentMi;
  GtkWidget *editAttributesMi;
  GtkWidget *renameVolumeMi;
  GtkWidget *actionSep3;
  GtkWidget *convertToDiskImageMi;
  GtkWidget *convertToArchiveFileMi;
  GtkWidget *importFileFromWAVMi;
  GtkWidget *importBASFromTextMi;

  /* Tools menu widgets */
  GtkWidget *toolsMenu;
  GtkWidget *toolsMi;
  GtkWidget *diskSectorViewerMi;
  GtkWidget *diskImageConverterMi;
  GtkWidget *bulkDiskImageConverterMi;
  GtkWidget *toolsSep1;
  GtkWidget *volumeCopierOpenVolumeMi;
  GtkWidget *volumeCopierOpenFileMi;
  GtkWidget *mergeSSTImagesMi;
  GtkWidget *toolsSep2;
  GtkWidget *TwoMGPropertiesEditorMi;
  GtkWidget *EOLScannerMi;

  /* Help menu widgets */
  GtkWidget *helpMenu;
  GtkWidget *helpMi;
  GtkWidget *contentsMi;
  GtkWidget *visitCalvadosWebsiteMi;
  GtkWidget *helpSep1;
  GtkWidget *aboutCalvadosMi;

  /* For keyboard accellerators */
  GtkAccelGroup *accel_group = NULL;

  /* For sort submenu */
  GSList *sort_radio_group = NULL;

  /* Tool bar widgets */
  GtkWidget *toolbar;
  /*GtkToolItem *newTb;*/
  GtkWidget *openTbImage;
  GtkToolItem *openTb;
  GtkWidget *openVolumeTbImage;
  GtkToolItem *openVolumeTb;
  GtkWidget *newArchiveTbImage;
  GtkToolItem *newArchiveTb;
  /*GtkToolItem *saveTb;*/
  GtkWidget *createDiskImageTbImage;
  GtkToolItem *createDiskImageTb;
  GtkWidget *printTbImage;
  GtkToolItem *printTb;
  GtkToolItem *tbSep1;
  GtkWidget *addFilesTbImage;
  GtkToolItem *addFilesTb;
  GtkWidget *addDiskImageTbImage;
  GtkToolItem *addDiskImageTb;
  GtkWidget *viewTbImage;
  GtkToolItem *viewTb;
  GtkWidget *extractTbImage;
  GtkToolItem *extractTb;
  GtkWidget *testTbImage;
  GtkToolItem *testTb;
  GtkWidget *renameTbImage;
  GtkToolItem *renameTb;
  GtkWidget *deleteTbImage;
  GtkToolItem *deleteTb;
  GtkWidget *recompressTbImage;
  GtkToolItem *recompressTb;
  GtkWidget *editCommentTbImage;
  GtkToolItem *editCommentTb;
  GtkToolItem *tbSep2;
  GtkWidget *diskSectorViewerTbImage;
  GtkToolItem *diskSectorViewerTb;
  GtkWidget *diskImageConverterTbImage;
  GtkToolItem *diskImageConverterTb;
  GtkWidget *volumeCopierTbImage;
  GtkToolItem *volumeCopierTb;
  GtkWidget *mergeSSTImagesTbImage;
  GtkToolItem *mergeSSTImagesTb;
  GtkToolItem *tbSep3;
  GtkToolItem *exitTb;

  GtkWidget *statusbar;

  /* Initialise GTK+ passing to it all command line arguments  */
  gtk_init(&argc, &argv);

  /* create a new window, set values */
  window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
  gtk_window_set_default_size(GTK_WINDOW(window), WINDOW_WIDTH, WINDOW_HEIGHT);
  gtk_window_set_title(GTK_WINDOW(window), "Calvados");

  /* Primary app vbox */
  vbox = gtk_vbox_new(FALSE, 0);
  gtk_container_add(GTK_CONTAINER(window), vbox);

  /* Primary app menu bar */
  menubar = gtk_menu_bar_new();
  /* File menu */
  fileMenu = gtk_menu_new();
  /* Edit menu */
  editMenu = gtk_menu_new();
  /* Action menu */
  actionMenu = gtk_menu_new();
  /* Tools menu */
  toolsMenu = gtk_menu_new();
  /* Help menu */
  helpMenu = gtk_menu_new();

  /* For keyboard accellerators */
  accel_group = gtk_accel_group_new();
  gtk_window_add_accel_group(GTK_WINDOW(window), accel_group);

  /* File menu bar items */
  fileMi = gtk_menu_item_new_with_mnemonic("_File");

  newMenu = gtk_menu_new();
  newMi = gtk_image_menu_item_new_from_stock(GTK_STOCK_NEW, accel_group);
  diskImageMi = gtk_menu_item_new_with_label("Disk image");
  shrinkItArchiveMi = gtk_menu_item_new_with_label("ShrinkIt Archive");

  /* 'New' submenu */
  gtk_menu_item_set_submenu(GTK_MENU_ITEM(newMi), newMenu);
  gtk_menu_shell_append(GTK_MENU_SHELL(newMenu), diskImageMi);
  gtk_menu_shell_append(GTK_MENU_SHELL(newMenu), shrinkItArchiveMi);

  gtk_widget_add_accelerator(shrinkItArchiveMi, "activate", accel_group, GDK_n, GDK_CONTROL_MASK, GTK_ACCEL_VISIBLE);

  openMi = gtk_image_menu_item_new_from_stock(GTK_STOCK_OPEN, accel_group);

  openVolumeMi = gtk_menu_item_new_with_mnemonic("_Open volume...");

  gtk_widget_add_accelerator(openVolumeMi, "activate", accel_group, GDK_o, GDK_CONTROL_MASK|GDK_SHIFT_MASK, GTK_ACCEL_VISIBLE);

  reopenMi = gtk_menu_item_new_with_mnemonic("_Reopen");

  gtk_widget_add_accelerator(reopenMi, "activate", accel_group, GDK_r, GDK_CONTROL_MASK, GTK_ACCEL_VISIBLE);

  saveChangesMi = gtk_menu_item_new_with_mnemonic("_Save changes");

  gtk_widget_add_accelerator(saveChangesMi, "activate", accel_group, GDK_s, GDK_CONTROL_MASK, GTK_ACCEL_VISIBLE);

  closeMi = gtk_image_menu_item_new_from_stock(GTK_STOCK_CLOSE, accel_group);

  fileSep1 = gtk_separator_menu_item_new();

  archiveInfoMi = gtk_menu_item_new_with_mnemonic("Archive _Info");

  gtk_widget_add_accelerator(archiveInfoMi, "activate", accel_group, GDK_i, GDK_CONTROL_MASK, GTK_ACCEL_VISIBLE);

  printMi = gtk_image_menu_item_new_from_stock(GTK_STOCK_PRINT, accel_group);

  gtk_widget_add_accelerator(printMi, "activate", accel_group, GDK_p, GDK_CONTROL_MASK, GTK_ACCEL_VISIBLE);

  fileSep2 = gtk_separator_menu_item_new();

  quitMi = gtk_image_menu_item_new_from_stock(GTK_STOCK_QUIT, accel_group);

  gtk_widget_add_accelerator(quitMi, "activate", accel_group, GDK_q, GDK_CONTROL_MASK, GTK_ACCEL_VISIBLE);

  /* Set up file menu */
  gtk_menu_item_set_submenu(GTK_MENU_ITEM(fileMi), fileMenu);
  gtk_menu_shell_append(GTK_MENU_SHELL(fileMenu), newMi);
  gtk_menu_shell_append(GTK_MENU_SHELL(fileMenu), openMi);
  gtk_menu_shell_append(GTK_MENU_SHELL(fileMenu), openVolumeMi);
  gtk_menu_shell_append(GTK_MENU_SHELL(fileMenu), reopenMi);
  gtk_menu_shell_append(GTK_MENU_SHELL(fileMenu), saveChangesMi);
  gtk_menu_shell_append(GTK_MENU_SHELL(fileMenu), closeMi);
  gtk_menu_shell_append(GTK_MENU_SHELL(fileMenu), fileSep1);
  gtk_menu_shell_append(GTK_MENU_SHELL(fileMenu), archiveInfoMi);
  gtk_menu_shell_append(GTK_MENU_SHELL(fileMenu), printMi);
  gtk_menu_shell_append(GTK_MENU_SHELL(fileMenu), fileSep2);
  gtk_menu_shell_append(GTK_MENU_SHELL(fileMenu), quitMi);
  /* Add file menu to menu bar */
  gtk_menu_shell_append(GTK_MENU_SHELL(menubar), fileMi);

  /* Edit menu bar items */
  editMi = gtk_menu_item_new_with_mnemonic("_Edit");
  copyMi = gtk_image_menu_item_new_from_stock(GTK_STOCK_COPY, accel_group);
  pasteMi = gtk_image_menu_item_new_from_stock(GTK_STOCK_PASTE, accel_group);
  pasteSpecialMi = gtk_menu_item_new_with_label("Paste Special");
  editSep1 = gtk_separator_menu_item_new();
  findMi = gtk_image_menu_item_new_from_stock(GTK_STOCK_FIND, accel_group);
  editSep2 = gtk_separator_menu_item_new();

  sortMenu = gtk_menu_new();
  sortMi = gtk_menu_item_new_with_mnemonic("_Sort");
  byOriginalOrderMi = gtk_radio_menu_item_new_with_label(sort_radio_group, "By original order");
  sort_radio_group = gtk_radio_menu_item_group(GTK_RADIO_MENU_ITEM(byOriginalOrderMi));
  gtk_check_menu_item_set_active(GTK_CHECK_MENU_ITEM(byOriginalOrderMi), TRUE);
  byPathnameMi = gtk_radio_menu_item_new_with_label(sort_radio_group, "By pathname");
  sort_radio_group = gtk_radio_menu_item_group(GTK_RADIO_MENU_ITEM(byPathnameMi));
  /*gtk_check_menu_item_set_active(GTK_CHECK_MENU_ITEM(byPathnameMi), FALSE);*/
  byFileTypeMi = gtk_radio_menu_item_new_with_label(sort_radio_group, "By file type");
  sort_radio_group = gtk_radio_menu_item_group(GTK_RADIO_MENU_ITEM(byFileTypeMi));
  /*gtk_check_menu_item_set_active(GTK_CHECK_MENU_ITEM(byFileTypeMi), FALSE);*/
  byAuxtypeMi = gtk_radio_menu_item_new_with_label(sort_radio_group, "By auxtype");
  sort_radio_group = gtk_radio_menu_item_group(GTK_RADIO_MENU_ITEM(byAuxtypeMi));
  /*gtk_check_menu_item_set_active(GTK_CHECK_MENU_ITEM(byAuxtypeMi), FALSE);*/
  byModificationDateMi = gtk_radio_menu_item_new_with_label(sort_radio_group, "By modification date");
  sort_radio_group = gtk_radio_menu_item_group(GTK_RADIO_MENU_ITEM(byModificationDateMi));
  /*gtk_check_menu_item_set_active(GTK_CHECK_MENU_ITEM(byModificationDateMi), FALSE);*/
  byFormatMi = gtk_radio_menu_item_new_with_label(sort_radio_group, "By format");
  sort_radio_group =  gtk_radio_menu_item_group(GTK_RADIO_MENU_ITEM(byFormatMi));
  /*gtk_check_menu_item_set_active(GTK_CHECK_MENU_ITEM(byFormatMi), FALSE);*/
  bySizeMi = gtk_radio_menu_item_new_with_label(sort_radio_group, "By size");
  sort_radio_group = gtk_radio_menu_item_group(GTK_RADIO_MENU_ITEM(bySizeMi));
  /*gtk_check_menu_item_set_active(GTK_CHECK_MENU_ITEM(bySizeMi), FALSE);*/
  byRatioMi = gtk_radio_menu_item_new_with_label(sort_radio_group, "By ratio");
  sort_radio_group = gtk_radio_menu_item_group(GTK_RADIO_MENU_ITEM(byRatioMi));
  /*gtk_check_menu_item_set_active(GTK_CHECK_MENU_ITEM(byRatioMi), FALSE);*/
  byPackedSizeMi = gtk_radio_menu_item_new_with_label(sort_radio_group, "By packed size");
  sort_radio_group = gtk_radio_menu_item_group(GTK_RADIO_MENU_ITEM(byPackedSizeMi));
  /*gtk_check_menu_item_set_active(GTK_CHECK_MENU_ITEM(byPackedSizeMi), FALSE);*/
  byAccessMi = gtk_radio_menu_item_new_with_label(sort_radio_group, "By access");
  sort_radio_group = gtk_radio_menu_item_group(GTK_RADIO_MENU_ITEM(byAccessMi));
  /*gtk_check_menu_item_set_active(GTK_CHECK_MENU_ITEM(byAccessMi), FALSE);*/

  /* 'Sort' submenu */
  gtk_menu_item_set_submenu(GTK_MENU_ITEM(sortMi), sortMenu);
  gtk_menu_shell_append(GTK_MENU_SHELL(sortMenu), byOriginalOrderMi);
  gtk_menu_shell_append(GTK_MENU_SHELL(sortMenu), byPathnameMi);
  gtk_menu_shell_append(GTK_MENU_SHELL(sortMenu), byAuxtypeMi);
  gtk_menu_shell_append(GTK_MENU_SHELL(sortMenu), byModificationDateMi);
  gtk_menu_shell_append(GTK_MENU_SHELL(sortMenu), byFormatMi);
  gtk_menu_shell_append(GTK_MENU_SHELL(sortMenu), bySizeMi);
  gtk_menu_shell_append(GTK_MENU_SHELL(sortMenu), byRatioMi);
  gtk_menu_shell_append(GTK_MENU_SHELL(sortMenu), byPackedSizeMi);
  gtk_menu_shell_append(GTK_MENU_SHELL(sortMenu), byAccessMi);

  selectAllMi = gtk_menu_item_new_with_mnemonic("Select _all");
  gtk_widget_add_accelerator(selectAllMi, "activate", accel_group, GDK_a, GDK_CONTROL_MASK, GTK_ACCEL_VISIBLE);
  invertSelectionMi = gtk_menu_item_new_with_mnemonic("_Invert selection");
  gtk_widget_add_accelerator(invertSelectionMi, "activate", accel_group, GDK_i, GDK_CONTROL_MASK, GTK_ACCEL_VISIBLE);
  preferencesMi = gtk_menu_item_new_with_mnemonic("_Preferences...");
  gtk_widget_add_accelerator(preferencesMi, "activate", accel_group, GDK_p, GDK_CONTROL_MASK|GDK_SHIFT_MASK, GTK_ACCEL_VISIBLE);

  /* Set up edit menu */
  gtk_menu_item_set_submenu(GTK_MENU_ITEM(editMi), editMenu);
  gtk_menu_shell_append(GTK_MENU_SHELL(editMenu), copyMi);
  gtk_menu_shell_append(GTK_MENU_SHELL(editMenu), pasteMi);
  gtk_menu_shell_append(GTK_MENU_SHELL(editMenu), pasteSpecialMi);
  gtk_menu_shell_append(GTK_MENU_SHELL(editMenu), editSep1);
  gtk_menu_shell_append(GTK_MENU_SHELL(editMenu), findMi);
  gtk_menu_shell_append(GTK_MENU_SHELL(editMenu), editSep2);
  gtk_menu_shell_append(GTK_MENU_SHELL(editMenu), sortMi);
  gtk_menu_shell_append(GTK_MENU_SHELL(editMenu), selectAllMi);
  gtk_menu_shell_append(GTK_MENU_SHELL(editMenu), invertSelectionMi);
  gtk_menu_shell_append(GTK_MENU_SHELL(editMenu), preferencesMi);
  /* Add edit menu to menu bar */
  gtk_menu_shell_append(GTK_MENU_SHELL(menubar), editMi);

  /* connect 'preferences' menu item to the preferences dialog event */
  g_signal_connect(G_OBJECT(preferencesMi), "activate", G_CALLBACK(preferences), NULL);

  /* Action menu bar items */
  actionsMi = gtk_menu_item_new_with_label("Actions");
  viewMi = gtk_menu_item_new_with_mnemonic("_View...");
  extractMi = gtk_menu_item_new_with_mnemonic("_Extract...");
  testMi = gtk_menu_item_new_with_mnemonic("_Test...");
  renameMi = gtk_menu_item_new_with_label("Rename...");
  deleteMi = gtk_menu_item_new_with_label("Delete...");
  recompressMi = gtk_menu_item_new_with_label("Re-compress...");
  actionSep1 = gtk_separator_menu_item_new();
  addFilesMi = gtk_menu_item_new_with_mnemonic("Add _files");
  addDiskImageMi = gtk_menu_item_new_with_mnemonic("Add _disk image");
  createSubdirectoryMi = gtk_menu_item_new_with_mnemonic("Create _subdirectory");
  actionSep2 = gtk_separator_menu_item_new();
  openAsDiskImageMi = gtk_menu_item_new_with_mnemonic("_Open As Disk Image");
  editCommentMi = gtk_menu_item_new_with_mnemonic("Edit _comment...");
  editAttributesMi = gtk_menu_item_new_with_mnemonic("Edit _attributes...");
  renameVolumeMi = gtk_menu_item_new_with_label("Rename Volume...");
  actionSep3 = gtk_separator_menu_item_new();
  convertToDiskImageMi = gtk_menu_item_new_with_mnemonic("_Convert to disk image...");
  convertToArchiveFileMi = gtk_menu_item_new_with_mnemonic("_Convert to archive file...");
  importFileFromWAVMi = gtk_menu_item_new_with_label("Import File From WAV...");
  importBASFromTextMi = gtk_menu_item_new_with_mnemonic("Import _BAS From Text...");

  /* Set up action menu */
  gtk_menu_item_set_submenu(GTK_MENU_ITEM(actionsMi), actionMenu);
  gtk_menu_shell_append(GTK_MENU_SHELL(actionMenu), viewMi);
  gtk_menu_shell_append(GTK_MENU_SHELL(actionMenu), extractMi);
  gtk_menu_shell_append(GTK_MENU_SHELL(actionMenu), testMi);
  gtk_menu_shell_append(GTK_MENU_SHELL(actionMenu), renameMi);
  gtk_menu_shell_append(GTK_MENU_SHELL(actionMenu), deleteMi);
  gtk_menu_shell_append(GTK_MENU_SHELL(actionMenu), recompressMi);
  gtk_menu_shell_append(GTK_MENU_SHELL(actionMenu), actionSep1);
  gtk_menu_shell_append(GTK_MENU_SHELL(actionMenu), addFilesMi);
  gtk_menu_shell_append(GTK_MENU_SHELL(actionMenu), addDiskImageMi);
  gtk_menu_shell_append(GTK_MENU_SHELL(actionMenu), createSubdirectoryMi);
  gtk_menu_shell_append(GTK_MENU_SHELL(actionMenu), actionSep2);
  gtk_menu_shell_append(GTK_MENU_SHELL(actionMenu), openAsDiskImageMi);
  gtk_menu_shell_append(GTK_MENU_SHELL(actionMenu), editCommentMi);
  gtk_menu_shell_append(GTK_MENU_SHELL(actionMenu), editAttributesMi);
  gtk_menu_shell_append(GTK_MENU_SHELL(actionMenu), renameVolumeMi);
  gtk_menu_shell_append(GTK_MENU_SHELL(actionMenu), actionSep3);
  gtk_menu_shell_append(GTK_MENU_SHELL(actionMenu), convertToDiskImageMi);
  gtk_menu_shell_append(GTK_MENU_SHELL(actionMenu), convertToArchiveFileMi);
  gtk_menu_shell_append(GTK_MENU_SHELL(actionMenu), importFileFromWAVMi);
  gtk_menu_shell_append(GTK_MENU_SHELL(actionMenu), importBASFromTextMi);
  /* Add action menu to menu bar */
  gtk_menu_shell_append(GTK_MENU_SHELL(menubar), actionsMi);

  /* Tools menu bar items */
  toolsMi = gtk_menu_item_new_with_label("Tools");
  diskSectorViewerMi = gtk_menu_item_new_with_mnemonic("_Disk sector viewer");
  diskImageConverterMi = gtk_menu_item_new_with_mnemonic("Disk _image converter");
  bulkDiskImageConverterMi = gtk_menu_item_new_with_mnemonic("_Bulk disk image converter");
  toolsSep1 = gtk_separator_menu_item_new();
  volumeCopierOpenVolumeMi = gtk_menu_item_new_with_mnemonic("_Volume Copier (open volume)");
  volumeCopierOpenFileMi = gtk_menu_item_new_with_label("Volume Copier (open file)");
  mergeSSTImagesMi = gtk_menu_item_new_with_mnemonic("_Merge SST Images");
  toolsSep2 = gtk_separator_menu_item_new();
  TwoMGPropertiesEditorMi = gtk_menu_item_new_with_label("2MG Properties Editor");
  EOLScannerMi = gtk_menu_item_new_with_label("EOL Scanner");

  /* Set up tools menu */
  gtk_menu_item_set_submenu(GTK_MENU_ITEM(toolsMi), toolsMenu);
  gtk_menu_shell_append(GTK_MENU_SHELL(toolsMenu), diskSectorViewerMi);
  gtk_menu_shell_append(GTK_MENU_SHELL(toolsMenu), diskImageConverterMi);
  gtk_menu_shell_append(GTK_MENU_SHELL(toolsMenu), bulkDiskImageConverterMi);
  gtk_menu_shell_append(GTK_MENU_SHELL(toolsMenu), toolsSep1);
  gtk_menu_shell_append(GTK_MENU_SHELL(toolsMenu), volumeCopierOpenVolumeMi);
  gtk_menu_shell_append(GTK_MENU_SHELL(toolsMenu), volumeCopierOpenFileMi);
  gtk_menu_shell_append(GTK_MENU_SHELL(toolsMenu), mergeSSTImagesMi);
  gtk_menu_shell_append(GTK_MENU_SHELL(toolsMenu), toolsSep2);
  gtk_menu_shell_append(GTK_MENU_SHELL(toolsMenu), TwoMGPropertiesEditorMi);
  gtk_menu_shell_append(GTK_MENU_SHELL(toolsMenu), EOLScannerMi);
  /* Add Tools menu to menu bar */
  gtk_menu_shell_append(GTK_MENU_SHELL(menubar), toolsMi);

  /* Help menu bar items */
  helpMi = gtk_menu_item_new_with_mnemonic("_Help");
  contentsMi = gtk_menu_item_new_with_mnemonic("_Contents...");
  visitCalvadosWebsiteMi = gtk_menu_item_new_with_mnemonic("Visit Calvados _website");
  helpSep1 = gtk_separator_menu_item_new();
  aboutCalvadosMi = gtk_menu_item_new_with_label("About Calvados");

  /* Set up help menu */
  gtk_menu_item_set_submenu(GTK_MENU_ITEM(helpMi), helpMenu);
  gtk_menu_shell_append(GTK_MENU_SHELL(helpMenu), contentsMi);
  gtk_menu_shell_append(GTK_MENU_SHELL(helpMenu), visitCalvadosWebsiteMi);
  gtk_menu_shell_append(GTK_MENU_SHELL(helpMenu), helpSep1);
  gtk_menu_shell_append(GTK_MENU_SHELL(helpMenu), aboutCalvadosMi);
  /* Add help menu to menu bar */
  gtk_menu_shell_append(GTK_MENU_SHELL(menubar), helpMi);

  /* Add menu bar to vbox */
  gtk_box_pack_start(GTK_BOX(vbox), menubar, FALSE, FALSE, 0);

  /* connect 'open image' menu item to the create welcomeage dialog event */
  g_signal_connect(G_OBJECT(openMi), "activate", G_CALLBACK(open_file), NULL);

  /* connect 'disk image' menu item to the create disk image dialog event */
  g_signal_connect(G_OBJECT(diskImageMi), "activate", G_CALLBACK(create_disk_image), NULL);

  /* connect 'shrinkit archive' menu item to the new archive dialog event */
  g_signal_connect(G_OBJECT(shrinkItArchiveMi), "activate", G_CALLBACK(new_archive), NULL);

  /* connect 'select volume' menu item to the open volume dialog event */
  g_signal_connect(G_OBJECT(openVolumeMi), "activate", G_CALLBACK(select_volume), NULL);

  /* connect 'about' menu item to the about box event */
  g_signal_connect(G_OBJECT(aboutCalvadosMi), "activate", G_CALLBACK(show_about), NULL);

  /* connect 'disk sector viewer' menu item to the popup menu event */
  g_signal_connect(G_OBJECT(diskSectorViewerMi), "activate", G_CALLBACK(disk_sector_viewer_popup), NULL);

  /* Connect 'quit' menu item to the window's "destroy" event */
  g_signal_connect(G_OBJECT(quitMi), "activate", G_CALLBACK(gtk_main_quit), NULL);

  /* Create the tool bar */
  toolbar = gtk_toolbar_new();
  gtk_toolbar_set_style(GTK_TOOLBAR(toolbar), GTK_TOOLBAR_ICONS);

  /*newTb = gtk_tool_button_new_from_stock(GTK_STOCK_NEW);
  gtk_toolbar_insert(GTK_TOOLBAR(toolbar), newTb, -1);*/

  /*openTb = gtk_tool_button_new_from_stock(GTK_STOCK_OPEN);*/
  openTbImage = gtk_image_new_from_file((gchar *)"images/openTb.png");
  openTb = gtk_tool_button_new((GtkWidget *)openTbImage, "Open");
  gtk_toolbar_insert(GTK_TOOLBAR(toolbar), openTb, -1);

  gtk_widget_set_tooltip_text(GTK_WIDGET(openTb), "Open (Ctrl-O)");

  openVolumeTbImage = gtk_image_new_from_file((gchar *)"images/openVolumeTb.png");
  openVolumeTb = gtk_tool_button_new((GtkWidget *)openVolumeTbImage, "Open Volume");
  gtk_toolbar_insert(GTK_TOOLBAR(toolbar), openVolumeTb, -1);

  gtk_widget_set_tooltip_text(GTK_WIDGET(openVolumeTb), "Open volume (Ctrl-Shift-O)");

  newArchiveTbImage = gtk_image_new_from_file((gchar *)"images/newArchiveTb.png");
  newArchiveTb = gtk_tool_button_new((GtkWidget *)newArchiveTbImage, "New Archive");
  gtk_toolbar_insert(GTK_TOOLBAR(toolbar), newArchiveTb, -1);

  gtk_widget_set_tooltip_text(GTK_WIDGET(newArchiveTb), "New Archive (Ctrl-N)");

  createDiskImageTbImage = gtk_image_new_from_file((gchar *)"images/createDiskImageTb.png");
  createDiskImageTb = gtk_tool_button_new((GtkWidget *)createDiskImageTbImage, "Create Disk Image");
  gtk_toolbar_insert(GTK_TOOLBAR(toolbar), createDiskImageTb, -1);

  gtk_widget_set_tooltip_text(GTK_WIDGET(createDiskImageTb), "Create Disk Image");

  /*saveTb = gtk_tool_button_new_from_stock(GTK_STOCK_SAVE);
  gtk_toolbar_insert(GTK_TOOLBAR(toolbar), saveTb, -1);*/

  printTbImage = gtk_image_new_from_file((gchar *)"images/printTb.png");
  printTb = gtk_tool_button_new((GtkWidget *)printTbImage, "Print");
  gtk_toolbar_insert(GTK_TOOLBAR(toolbar), printTb, -1);

  gtk_widget_add_accelerator(GTK_WIDGET(printTb), "clicked", accel_group, GDK_p, GDK_CONTROL_MASK, GTK_ACCEL_MASK);

  gtk_widget_set_tooltip_text(GTK_WIDGET(printTb), "Print (Ctrl-P)");

  tbSep1 = gtk_separator_tool_item_new();
  gtk_toolbar_insert(GTK_TOOLBAR(toolbar), tbSep1, -1);

  addFilesTbImage = gtk_image_new_from_file((gchar *)"images/addFilesTb.png");
  addFilesTb = gtk_tool_button_new((GtkWidget *)addFilesTbImage, "Add Files");
  gtk_toolbar_insert(GTK_TOOLBAR(toolbar), addFilesTb, -1);

  gtk_widget_set_tooltip_text(GTK_WIDGET(addFilesTb), "Add Files");

  addDiskImageTbImage = gtk_image_new_from_file((gchar *)"images/addDiskImageTb.png");
  addDiskImageTb = gtk_tool_button_new((GtkWidget *)addDiskImageTbImage, "Add Disk Image");
  gtk_toolbar_insert(GTK_TOOLBAR(toolbar), addDiskImageTb, -1);

  gtk_widget_set_tooltip_text(GTK_WIDGET(addDiskImageTb), "Add disk image");

  viewTbImage = gtk_image_new_from_file((gchar *)"images/viewTb.png");
  viewTb = gtk_tool_button_new((GtkWidget *)viewTbImage, "View");
  gtk_toolbar_insert(GTK_TOOLBAR(toolbar), viewTb, -1);

  gtk_widget_set_tooltip_text(GTK_WIDGET(viewTb), "View (tab)");

  extractTbImage = gtk_image_new_from_file((gchar *)"images/extractTb.png");
  extractTb = gtk_tool_button_new((GtkWidget *)extractTbImage, "Extract");
  gtk_toolbar_insert(GTK_TOOLBAR(toolbar), extractTb, -1);

  gtk_widget_set_tooltip_text(GTK_WIDGET(extractTb), "Extract");

  testTbImage = gtk_image_new_from_file((gchar *)"images/testTb.png");
  testTb = gtk_tool_button_new((GtkWidget *)testTbImage, "Test");
  gtk_toolbar_insert(GTK_TOOLBAR(toolbar), testTb, -1);

  gtk_widget_set_tooltip_text(GTK_WIDGET(testTb), "Test");

  renameTbImage = gtk_image_new_from_file((gchar *)"images/renameTb.png");
  renameTb = gtk_tool_button_new((GtkWidget *)renameTbImage, "Rename");
  gtk_toolbar_insert(GTK_TOOLBAR(toolbar), renameTb, -1);

  gtk_widget_set_tooltip_text(GTK_WIDGET(renameTb), "Rename");

  deleteTbImage = gtk_image_new_from_file((gchar *)"images/deleteTb.png");
  deleteTb = gtk_tool_button_new((GtkWidget *)deleteTbImage, "Delete");
  gtk_toolbar_insert(GTK_TOOLBAR(toolbar), deleteTb, -1);

  gtk_widget_set_tooltip_text(GTK_WIDGET(deleteTb), "Delete (DEL)");

  recompressTbImage = gtk_image_new_from_file((gchar *)"images/recompressTb.png");
  recompressTb = gtk_tool_button_new((GtkWidget *)recompressTbImage, "Re-compress");
  gtk_toolbar_insert(GTK_TOOLBAR(toolbar), recompressTb, -1);

  gtk_widget_set_tooltip_text(GTK_WIDGET(recompressTb), "Recompress");

  editCommentTbImage = gtk_image_new_from_file((gchar *)"images/editCommentTb.png");
  editCommentTb = gtk_tool_button_new((GtkWidget *)editCommentTbImage, "Edit Comment");
  gtk_toolbar_insert(GTK_TOOLBAR(toolbar), editCommentTb, -1);

  gtk_widget_set_tooltip_text(GTK_WIDGET(editCommentTb), "Edit Comment");

  tbSep2 = gtk_separator_tool_item_new();
  gtk_toolbar_insert(GTK_TOOLBAR(toolbar), tbSep2, -1);

  diskSectorViewerTbImage = gtk_image_new_from_file((gchar *)"images/diskSectorViewerTb.png");
  diskSectorViewerTb = gtk_tool_button_new((GtkWidget *)diskSectorViewerTbImage, "Disk Sector Viewer");
  gtk_toolbar_insert(GTK_TOOLBAR(toolbar), diskSectorViewerTb, -1);

  gtk_widget_set_tooltip_text(GTK_WIDGET(diskSectorViewerTb), "Disk Sector Viewer");

  diskImageConverterTbImage = gtk_image_new_from_file((gchar *)"images/diskImageConverterTb.png");
  diskImageConverterTb = gtk_tool_button_new((GtkWidget *)diskImageConverterTbImage, "Disk Image Converter");
  gtk_toolbar_insert(GTK_TOOLBAR(toolbar), diskImageConverterTb, -1);

  gtk_widget_set_tooltip_text(GTK_WIDGET(diskImageConverterTb), "Disk Image Converter");

  volumeCopierTbImage = gtk_image_new_from_file((gchar *)"images/volumeCopierTb.png");
  volumeCopierTb = gtk_tool_button_new((GtkWidget *)volumeCopierTbImage, "Volume Copier");
  gtk_toolbar_insert(GTK_TOOLBAR(toolbar), volumeCopierTb, -1);

  gtk_widget_set_tooltip_text(GTK_WIDGET(volumeCopierTb), "Volume Copier (open volume)");

  mergeSSTImagesTbImage = gtk_image_new_from_file((gchar *)"images/mergeSSTImagesTb.png");
  mergeSSTImagesTb = gtk_tool_button_new((GtkWidget *)mergeSSTImagesTbImage, "Merge SST Images");
  gtk_toolbar_insert(GTK_TOOLBAR(toolbar), mergeSSTImagesTb, -1);

  gtk_widget_set_tooltip_text(GTK_WIDGET(mergeSSTImagesTb), "Merge SST Images");

  tbSep3 = gtk_separator_tool_item_new();
  gtk_toolbar_insert(GTK_TOOLBAR(toolbar), tbSep3, -1);

  exitTb = gtk_tool_button_new_from_stock(GTK_STOCK_QUIT);
  gtk_toolbar_insert(GTK_TOOLBAR(toolbar), exitTb, -1);

  gtk_widget_set_tooltip_text(GTK_WIDGET(exitTb), "Exit");

  /* Hook up the open image button to the open file dialog box */
  g_signal_connect(G_OBJECT(openTb), "clicked", G_CALLBACK(open_file), NULL);

  /* Hook up the create disk image button to the create disk image dialog box */
  g_signal_connect(G_OBJECT(createDiskImageTb), "clicked", G_CALLBACK(create_disk_image), NULL);

  /* Hook up the new archive image button to the create disk image dialog box */
  g_signal_connect(G_OBJECT(newArchiveTb), "clicked", G_CALLBACK(new_archive), NULL);

  /* Hook up the open volume button to the select volume dialog box */
  g_signal_connect(G_OBJECT(openVolumeTb), "clicked", G_CALLBACK(select_volume), NULL);

  /* Hook up the disk sector viewer button to the disk sector viewer popup menu */
  g_signal_connect(G_OBJECT(diskSectorViewerTb), "clicked", G_CALLBACK(disk_sector_viewer_popup), NULL);

  /* Hook up the exit button to the quit function */
  g_signal_connect(G_OBJECT(exitTb), "clicked", G_CALLBACK(gtk_main_quit), NULL);

  /* Add the tool bar to the vbox */
  gtk_box_pack_start(GTK_BOX(vbox), toolbar, FALSE, FALSE, 5);

  /*button = gtk_button_new_with_label("Hello Window");
  gtk_container_add(GTK_CONTAINER(vbox), button);
  g_signal_connect(G_OBJECT(button), "clicked", G_CALLBACK(gtk_main_quit), NULL);*/

  /* Add the status bar */
  statusbar = gtk_statusbar_new();
  gtk_box_pack_end(GTK_BOX(vbox), statusbar, FALSE, TRUE, 0);

  /* connect the windows "destroy" event */
  g_signal_connect(G_OBJECT(window), "destroy", G_CALLBACK(gtk_main_quit), NULL);

  /* set the window as visible */
  gtk_widget_show_all(window);

  /* run the GTK+ main loop */
  gtk_main();

  return 0;
}

