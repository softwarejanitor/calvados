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
#include <gdk/gdkkeysyms-compat.h>

#include "calvados.h"

enum {
  COL_PATHNAME = 0,
  COL_TYPE,
  COL_AUX,
  COL_MODDATE,
  COL_FORMAT,
  COL_SIZE,
  COL_RATIO,
  COL_PACKED,
  COL_ACCESS,
  NUM_MAIN_WINDOW_COLS
};


/* For displaying displaying disk images/archives in main window */
GtkListStore *mw_store;
/*GtkTreeIter mw_iter;*/
GtkCellRenderer *mw_renderer;
GtkTreeModel *mw_model;
GtkWidget *mw_view;

/* FIXME -- this needs to be done better. */
char open_file_name[256];
char *open_file_ptr;

/*
 *
 * display_image()
 *
 * Display the tree view in the main window,
 *
 */
GtkWidget *display_image(GtkWidget *widget, gpointer data, GtkWidget *mw_box)
{
  mw_store = gtk_list_store_new(NUM_MAIN_WINDOW_COLS, G_TYPE_STRING, G_TYPE_UINT);

/*FIXME*/
  /* This needs to be in a loop reading from somewhere */
  /* Append a row and fill in some data */
  /*gtk_list_store_append(store, &mw_iter);
  gtk_list_store_set(store, &mw_iter,
                     COL_PATHNAME, "",
                     COL_TYPE, "",
                     COL_AUX, "",
                     COL_MODDATE, "",
                     COL_FORMAT, "",
                     COL_SIZE, "",
                     COL_RATIO, "",
                     COL_PACKED, "",
                     COL_ACCESS, "",
                     -1);*/

  mw_view = gtk_tree_view_new();
  gtk_widget_set_size_request(mw_view, LIST_WIDTH, LIST_HEIGHT);

  /* --- Column #1 --- */
  mw_renderer = gtk_cell_renderer_text_new();
  gtk_tree_view_insert_column_with_attributes(GTK_TREE_VIEW(mw_view),
                                              -1,
                                              "Pathname",
                                              mw_renderer,
                                              "text", COL_PATHNAME,
                                              NULL);

  /* --- Column #2 --- */
  mw_renderer = gtk_cell_renderer_text_new();
  gtk_tree_view_insert_column_with_attributes(GTK_TREE_VIEW(mw_view),
                                              -1,
                                              "Type",
                                              mw_renderer,
                                              "text", COL_TYPE,
                                              NULL);

  /* --- Column #3 --- */
  mw_renderer = gtk_cell_renderer_text_new();
  gtk_tree_view_insert_column_with_attributes(GTK_TREE_VIEW(mw_view),
                                              -1,
                                              "Aux",
                                              mw_renderer,
                                              "text", COL_AUX,
                                              NULL);
  /* --- Column #4 --- */
  mw_renderer = gtk_cell_renderer_text_new();
  gtk_tree_view_insert_column_with_attributes(GTK_TREE_VIEW(mw_view),
                                              -1,
                                              "Mod Date",
                                              mw_renderer,
                                              "text", COL_MODDATE,
                                              NULL);

  /* --- Column #5 --- */
  mw_renderer = gtk_cell_renderer_text_new();
  gtk_tree_view_insert_column_with_attributes(GTK_TREE_VIEW(mw_view),
                                              -1,
                                              "Format",
                                              mw_renderer,
                                              "text", COL_FORMAT,
                                              NULL);

  /* --- Column #6 --- */
  mw_renderer = gtk_cell_renderer_text_new();
  gtk_tree_view_insert_column_with_attributes(GTK_TREE_VIEW(mw_view),
                                              -1,
                                              "Size",
                                              mw_renderer,
                                              "text", COL_SIZE,
                                              NULL);

  /* --- Column #7 --- */
  mw_renderer = gtk_cell_renderer_text_new();
  gtk_tree_view_insert_column_with_attributes(GTK_TREE_VIEW(mw_view),
                                              -1,
                                              "Ratio",
                                              mw_renderer,
                                              "text", COL_RATIO,
                                              NULL);

  /* --- Column #8 --- */
  mw_renderer = gtk_cell_renderer_text_new();
  gtk_tree_view_insert_column_with_attributes(GTK_TREE_VIEW(mw_view),
                                              -1,
                                              "Packed",
                                              mw_renderer,
                                              "text", COL_PACKED,
                                              NULL);

  /* --- Column #9 --- */
  mw_renderer = gtk_cell_renderer_text_new();
  gtk_tree_view_insert_column_with_attributes(GTK_TREE_VIEW(mw_view),
                                              -1,
                                              "Access",
                                              mw_renderer,
                                              "text", COL_ACCESS,
                                              NULL);

  mw_model = GTK_TREE_MODEL(mw_store);

  gtk_tree_view_set_model(GTK_TREE_VIEW(mw_view), mw_model);

  /* The tree view has acquired its own reference to the
   *  model, so we can drop ours. That way the model will
   *  be freed automatically when the tree view is destroyed */
  g_object_unref(mw_model);

  gtk_box_pack_start(GTK_BOX(mw_box), mw_view, TRUE, TRUE, 0);

  gtk_widget_show(mw_view);

  return mw_view;
}


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
  GtkWidget *twoMGPropertiesEditorMi;
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

  open_file_ptr = (char *)open_file_name;

  /* Initialise GTK+ passing to it all command line arguments  */
  gtk_init(&argc, &argv);

  /* create a new window, set values */
  window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
  gtk_window_set_default_size(GTK_WINDOW(window), WINDOW_WIDTH, WINDOW_HEIGHT);
  gtk_window_set_title(GTK_WINDOW(window), "Calvados");
  gtk_window_set_icon_from_file(GTK_WINDOW(window), "images/calvados.png", NULL);

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

  /* connect 'reopen' menu item to the reopen dialog event */
  g_signal_connect(G_OBJECT(reopenMi), "activate", G_CALLBACK(reopen_menu_item), (gpointer)"reopenMi");

  /* connect 'save changes' menu item to the save_changes dialog event */
  g_signal_connect(G_OBJECT(saveChangesMi), "activate", G_CALLBACK(save_changes), (gpointer)"saveChangesMi");

  /* connect 'close' menu item to the close_menu_item dialog event */
  g_signal_connect(G_OBJECT(closeMi), "activate", G_CALLBACK(close_menu_item), (gpointer)"closeMi");

  /* connect 'archive info' menu item to the archive_info dialog event */
  g_signal_connect(G_OBJECT(archiveInfoMi), "activate", G_CALLBACK(archive_info), (gpointer)"archiveInfoMi");

  /* Hook up the print menu item to the print dialog box */
  g_signal_connect(G_OBJECT(printMi), "activate", G_CALLBACK(print_page), (gpointer)window);

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

  /* connect 'copy' menu item to the copy_menu_item dialog event */
  g_signal_connect(G_OBJECT(copyMi), "activate", G_CALLBACK(copy_menu_item), (gpointer)"copyMi");

  /* connect 'paste' menu item to the paste dialog event */
  g_signal_connect(G_OBJECT(pasteMi), "activate", G_CALLBACK(paste), (gpointer)"pasteMi");

  /* connect 'paste special' menu item to the paste_special dialog event */
  g_signal_connect(G_OBJECT(pasteSpecialMi), "activate", G_CALLBACK(paste_special), (gpointer)"pasteSpecialMi");

  /* connect 'find' menu item to the find dialog event */
  g_signal_connect(G_OBJECT(findMi), "activate", G_CALLBACK(find), (gpointer)"findMi");

  /* connect 'select all' menu item to the select_all dialog event */
  g_signal_connect(G_OBJECT(selectAllMi), "activate", G_CALLBACK(select_all), (gpointer)"selectAllMi");

  /* connect 'invert selection' menu item to the invert_selection dialog event */
  g_signal_connect(G_OBJECT(invertSelectionMi), "activate", G_CALLBACK(invert_selection), (gpointer)"invertSelectionMi");

  /* connect 'preferences' menu item to the preferences dialog event */
  g_signal_connect(G_OBJECT(preferencesMi), "activate", G_CALLBACK(preferences), (gpointer)"preferencesMi");

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
  twoMGPropertiesEditorMi = gtk_menu_item_new_with_label("2MG Properties Editor");
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
  gtk_menu_shell_append(GTK_MENU_SHELL(toolsMenu), twoMGPropertiesEditorMi);
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
  g_signal_connect(G_OBJECT(openMi), "activate", G_CALLBACK(open_file), (gpointer)"openMi");

  /* connect 'view' menu item to the file viewer dialog event */
  g_signal_connect(G_OBJECT(viewMi), "activate", G_CALLBACK(file_viewer), (gpointer)"viewMi");

  /* connect 'extract' menu item to the extract dialog event */
  g_signal_connect(G_OBJECT(extractMi), "activate", G_CALLBACK(extract_files), (gpointer)"extractMi");

  /* connect 'test' menu item to the test dialog event */
  g_signal_connect(G_OBJECT(testMi), "activate", G_CALLBACK(test), (gpointer)"testMi");

  /* connect 'disk image' menu item to the create disk image dialog event */
  g_signal_connect(G_OBJECT(diskImageMi), "activate", G_CALLBACK(create_disk_image), (gpointer)"diskImageMi");

  /* connect 'add disk image' menu item to the add disk image dialog event */
  g_signal_connect(G_OBJECT(addDiskImageMi), "activate", G_CALLBACK(add_disk_image), (gpointer)"addDiskImageMi");

  /* connect 'shrinkit archive' menu item to the new archive dialog event */
  g_signal_connect(G_OBJECT(shrinkItArchiveMi), "activate", G_CALLBACK(new_archive), (gpointer)"shrinkItArchiveMi");

  /* connect 'select volume' menu item to the open volume dialog event */
  g_signal_connect(G_OBJECT(openVolumeMi), "activate", G_CALLBACK(select_volume), (gpointer)"openVolumeMi");

  /* connect 'rename' menu item to the rename dialog event */
  g_signal_connect(G_OBJECT(renameMi), "activate", G_CALLBACK(rename_file), (gpointer)"renameMi");

  /* connect 'delete' menu item to the delete dialog event */
  g_signal_connect(G_OBJECT(deleteMi), "activate", G_CALLBACK(delete_file), (gpointer)"deleteMi");

  /* connect 'recompress' menu item to the recompress dialog event */
  g_signal_connect(G_OBJECT(recompressMi), "activate", G_CALLBACK(recompress_files), (gpointer)"recompressMi");

  /* connect 'add files' menu item to the add files dialog event */
  g_signal_connect(G_OBJECT(addFilesMi), "activate", G_CALLBACK(add_files), (gpointer)"addFilesMi");

  /* connect 'create subdirectory' menu item to the create subdirectory dialog event */
  g_signal_connect(G_OBJECT(createSubdirectoryMi), "activate", G_CALLBACK(create_subdirectory), (gpointer)"createSubdirectoryMi");

  /* connect 'open as disk image' menu item to the open as disk image dialog event */
  g_signal_connect(G_OBJECT(openAsDiskImageMi), "activate", G_CALLBACK(open_as_disk_image), (gpointer)"openAsDiskImageMi");

  /* connect 'Edit Attributes' menu item to the edit_attributes dialog event */
  g_signal_connect(G_OBJECT(editAttributesMi), "activate", G_CALLBACK(edit_attributes), (gpointer)"editAttributesMi");

  /* connect 'Rename Volume' menu item to the rename_volume dialog event */
  g_signal_connect(G_OBJECT(renameVolumeMi), "activate", G_CALLBACK(rename_volume), (gpointer)"renameVolumeMi");

  /* connect 'Convert to disk image' menu item to the convert_to_disk_image dialog event */
  g_signal_connect(G_OBJECT(convertToDiskImageMi), "activate", G_CALLBACK(convert_to_disk_image), (gpointer)"convertToDiskImageMi");

  /* connect 'Convert to archive file' menu item to the convert_to_archive_file dialog event */
  g_signal_connect(G_OBJECT(convertToArchiveFileMi), "activate", G_CALLBACK(convert_to_archive_file), (gpointer)"convertToArchiveFileMi");

  /* connect 'Import File from WAV menu item to the import_file_from_wav dialog event */
  g_signal_connect(G_OBJECT(importFileFromWAVMi), "activate", G_CALLBACK(import_file_from_wav), (gpointer)"importFileFromWAVMi");

  /* connect 'Import BAS from Text menu item to the import_bas_from_text dialog event */
  g_signal_connect(G_OBJECT(importBASFromTextMi), "activate", G_CALLBACK(import_bas_from_text), (gpointer)"importBASFromTextMi");

  /* connect 'edit comment' menu item to the edit comment dialog event */
  g_signal_connect(G_OBJECT(editCommentMi), "activate", G_CALLBACK(edit_comment), (gpointer)"editCommentMi");

  /* connect 'contents' menu item to the contents box event */
  g_signal_connect(G_OBJECT(contentsMi), "activate", G_CALLBACK(contents), (gpointer)"contentsMi");

  /* connect 'contents' menu item to the contents box event */
  g_signal_connect(G_OBJECT(visitCalvadosWebsiteMi), "activate", G_CALLBACK(visit_website), (gpointer)"visitCalvadosWebsiteMi");

  /* connect 'about' menu item to the about box event */
  g_signal_connect(G_OBJECT(aboutCalvadosMi), "activate", G_CALLBACK(show_about), (gpointer)"aboutCalvadosMi");

  /* connect 'disk sector viewer' menu item to the popup menu event */
  g_signal_connect(G_OBJECT(diskSectorViewerMi), "activate", G_CALLBACK(disk_sector_viewer_popup), (gpointer)"diskSectorViewerMi");

  /* connect 'Select image convert' menu item to the select image conversions popup menu event */
  g_signal_connect(G_OBJECT(diskImageConverterMi), "activate", G_CALLBACK(select_image_convert), (gpointer)"diskImageConverterMi");

  /* connect 'Select bulk disk image converter' menu item to the bulk disk image converter popup menu event */
  g_signal_connect(G_OBJECT(bulkDiskImageConverterMi), "activate", G_CALLBACK(bulk_disk_image_converter), (gpointer)"bulkDiskImageConverterMi");

  /* connect 'Volume Copier Open Volume' menu item to the volume copier open volume popup menu event */
  g_signal_connect(G_OBJECT(volumeCopierOpenVolumeMi), "activate", G_CALLBACK(volume_copier_open_volume), (gpointer)"volumeCopierOpenVolumeMi");

  /* connect 'Volume Copier Open File' menu item to the volume copier open file popup menu event */
  g_signal_connect(G_OBJECT(volumeCopierOpenFileMi), "activate", G_CALLBACK(volume_copier_open_file), (gpointer)"volumeCopierOpenFileMi");

  /* connect 'Merge SST Images' menu item to the merge sst images popup menu event */
  g_signal_connect(G_OBJECT(mergeSSTImagesMi), "activate", G_CALLBACK(select_first_sst_image), (gpointer)"mergeSSTImagesMi");

  /* connect '2MG Properties Editor' menu item to the 2MG properties editor popup menu event */
  g_signal_connect(G_OBJECT(twoMGPropertiesEditorMi), "activate", G_CALLBACK(twomg_properties_editor), (gpointer)"twoMGPropertiesEditorMi");

  /* connect 'EOL Scanner' menu item to the eol scanner popup menu event */
  g_signal_connect(G_OBJECT(EOLScannerMi), "activate", G_CALLBACK(eol_scanner), (gpointer)"EOLScannerMi");

  /* Connect 'quit' menu item to the window's "destroy" event */
  g_signal_connect(G_OBJECT(quitMi), "activate", G_CALLBACK(gtk_main_quit), (gpointer)"quitMi");

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
  g_signal_connect(G_OBJECT(openTb), "clicked", G_CALLBACK(open_file), (gpointer)"openTb");

  /* Hook up the create disk image button to the create disk image dialog box */
  g_signal_connect(G_OBJECT(createDiskImageTb), "clicked", G_CALLBACK(create_disk_image), (gpointer)"createDiskImageTb");

  /* Hook up the new archive image button to the create disk image dialog box */
  g_signal_connect(G_OBJECT(newArchiveTb), "clicked", G_CALLBACK(new_archive), (gpointer)"newArchiveTb");

  /* Hook up the open volume button to the select volume dialog box */
  g_signal_connect(G_OBJECT(openVolumeTb), "clicked", G_CALLBACK(select_volume), (gpointer)"openVolumeTb");

  /* Hook up the print button to the print dialog box */
  g_signal_connect(G_OBJECT(printTb), "clicked", G_CALLBACK(print_page), (gpointer)window);

  /* Hook up the add files button to the add files dialog box */
  g_signal_connect(G_OBJECT(addFilesTb), "clicked", G_CALLBACK(add_files), (gpointer)"addFilesTb");

  /* Hook up the add disk image button to the add disk image dialog box */
  g_signal_connect(G_OBJECT(addDiskImageTb), "clicked", G_CALLBACK(add_disk_image), (gpointer)"addDiskImageTb");

  /* Hook up the view button to the file viewer dialog box */
  g_signal_connect(G_OBJECT(viewTb), "clicked", G_CALLBACK(file_viewer), (gpointer)"viewTb");

  /* Hook up the extract files button to the extract files dialog box */
  g_signal_connect(G_OBJECT(extractTb), "clicked", G_CALLBACK(extract_files), (gpointer)"extractTb");

  /* Hook up the test button to the test dialog box */
  g_signal_connect(G_OBJECT(testTb), "clicked", G_CALLBACK(test), (gpointer)"testTb");

  /* Hook up the rename button to the rename dialog box */
  g_signal_connect(G_OBJECT(renameTb), "clicked", G_CALLBACK(rename_file), (gpointer)"renameTb");

  /* Hook up the delete button to the delete dialog box */
  g_signal_connect(G_OBJECT(deleteTb), "clicked", G_CALLBACK(delete_file), (gpointer)"deleteTb");

  /* Hook up the recompress button to the delete dialog box */
  g_signal_connect(G_OBJECT(recompressTb), "clicked", G_CALLBACK(recompress_files), (gpointer)"recompressTb");

  /* Hook up the edit comment button to the edit comment dialog box */
  g_signal_connect(G_OBJECT(editCommentTb), "clicked", G_CALLBACK(edit_comment), (gpointer)"editCommentTb");

  /* Hook up the disk sector viewer button to the disk sector viewer popup menu */
  g_signal_connect(G_OBJECT(diskSectorViewerTb), "clicked", G_CALLBACK(disk_sector_viewer_popup), (gpointer)"diskSectorViewerTb");

  /* Hook up the disk image converter button to the disk image converter dialog box */
  g_signal_connect(G_OBJECT(diskImageConverterTb), "clicked", G_CALLBACK(disk_image_converter), (gpointer)"diskImageConverterTb");

  /* Hook up the volume copier button to the volume copier dialog box */
/* FIXME */
  g_signal_connect(G_OBJECT(volumeCopierTb), "clicked", G_CALLBACK(select_volume), (gpointer)"volumeCopierTb");

  /* Hook up the 'Select image convert' button item to the select image conversions dialog box */
  g_signal_connect(G_OBJECT(diskImageConverterTb), "clicked", G_CALLBACK(select_image_convert), (gpointer)"diskImageConverterTb");

  /* Hook up the merge sst images button to the merge sst images dialog box */
  g_signal_connect(G_OBJECT(mergeSSTImagesTb), "clicked", G_CALLBACK(select_first_sst_image), (gpointer)"mergeSSTImagesTb");

  /* Hook up the exit button to the quit function */
  g_signal_connect(G_OBJECT(exitTb), "clicked", G_CALLBACK(gtk_main_quit), (gpointer)"exitTb");

  /* Add the tool bar to the vbox */
  gtk_box_pack_start(GTK_BOX(vbox), toolbar, FALSE, FALSE, 5);

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

