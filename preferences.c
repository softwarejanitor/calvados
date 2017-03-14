#include <gtk/gtk.h>
#include <gdk/gdkkeysyms.h>

#include "calvados.h"

/*
 *
 * apply_func_preferences()
 *
 * Actually do apply of preferences.
 *
 */
void apply_func_preferences()
{
  g_print("Apply function goes here.\n");
}


/*
 *
 * help_func_preferences()
 *
 * Help function for preferences
 *
 */
void help_func_preferences()
{
  g_print("Help function goes here.\n");
}


/*
 *
 * page_switch()
 *
 * Event that occurs when a different page is now
 * the focus.
 *
 */
static void page_switch(GtkWidget *widget,
                         GtkNotebookPage *page,
                         gint page_num)
{
    g_print("page switch\n");
}


/*
 *
 * add_page()
 *
 * Add a page to the notebook
 *
 * notebook - existing notebook
 * szName - name to give to the new page
 *
 */
GtkWidget *add_page(GtkWidget *notebook, char *szName)
{
  GtkWidget *label;
  /*GtkWidget *frame;*/
  GtkWidget *pageVbox;

  /* --- Create a label from the name. --- */
  label = gtk_label_new(szName);
  gtk_widget_show(label);

  /* --- Create a frame for the page --- */
  /*frame = gtk_frame_new(szName);*/
  /*gtk_widget_show(frame);*/
  pageVbox = gtk_vbox_new(FALSE, 0);
  gtk_widget_show(pageVbox);

  /* --- Add a page with the frame and label --- */
  /*gtk_notebook_append_page(GTK_NOTEBOOK(notebook), frame, label);*/
  gtk_notebook_append_page(GTK_NOTEBOOK(notebook), pageVbox, label);

  /*return (frame);*/
  return pageVbox;
}


/*
 *
 * create_notebook()
 *
 * Create a new notebook and add pages to it.
 *
 * window - window to create the notebook in.
 *
 */
GtkWidget *create_notebook(GtkWidget *window, GtkPositionType pos)
{
  GtkWidget *box1;
  GtkWidget *notebook;

  /* --- Let us know when getting destroyed. --- */
  gtk_signal_connect(GTK_OBJECT(window), "destroy",
                     GTK_SIGNAL_FUNC(gtk_widget_destroyed),
                     &window);

  /* --- Set border width --- */
  gtk_container_border_width(GTK_CONTAINER(window), 0);

  box1 = gtk_vbox_new(FALSE, 0);
  gtk_container_add(GTK_CONTAINER(window), box1);

  /* --- Create the notebook --- */
  notebook = gtk_notebook_new();

  /* --- Listen for the switch page event --- */
  gtk_signal_connect(GTK_OBJECT(notebook), "switch_page",
                     GTK_SIGNAL_FUNC(page_switch), NULL);

  /* --- Make sure tabs are set on correct side --- */
  gtk_notebook_set_tab_pos(GTK_NOTEBOOK(notebook), pos);

  /* --- Add notebook to vbox --- */
  gtk_box_pack_start(GTK_BOX(box1), notebook, TRUE, TRUE, 0);

  /* --- Give notebook a border --- */
  gtk_container_border_width(GTK_CONTAINER(notebook), 10);

  /* --- Show everything. --- */
  gtk_widget_show_all(window);

  return notebook;
}


/*
 *
 * preferences()
 *
 * Preferences dialog box
 *
 */
void preferences()
{
  GtkWidget *dialog_window;
  GtkWidget *dialogVbox;
  GtkWidget *notebook;
  GtkWidget *generalTab;
  GtkWidget *diskImagesTab;
  GtkWidget *fileViewerTab;
  GtkWidget *compressionTab;
  GtkWidget *filesTab;
  GtkWidget *generalHbox;
  GtkWidget *actionHbox;
  GtkWidget *columnsFrame;
  GtkWidget *generalLeftVbox;
  GtkWidget *pathnameCb;
  GtkWidget *typeCb;
  GtkWidget *auxTypeCb;
  GtkWidget *modDateCb;
  GtkWidget *formatCb;
  GtkWidget *sizeCb;
  GtkWidget *ratioCb;
  GtkWidget *packedCb;
  GtkWidget *accessCb;
  GtkWidget *defaultsButton;
  GtkWidget *generalRightVbox;
  GtkWidget *nufxArchivesFrame;
  GtkWidget *filenameMungingFrame;
  GtkWidget *systemFrame;
  GtkWidget *miscellaneousFrame;
  GtkWidget *nufxArchivesVbox;
  GtkWidget *filenameMungingVbox;
  GtkWidget *systemVbox;
  GtkWidget *miscellaneousVbox;
  GtkWidget *mimicShrinkitQuirksCb;
  GtkWidget *handleBadMacArchivesCb;
  GtkWidget *reduceErrorCheckingCb;
  GtkWidget *displayDOS33FilenamesCb;
  GtkWidget *showSpacesAsUnderscoresCb;
  GtkWidget *fileTypeAssociationsButton;
  GtkWidget *stripPathnamesWhenPastingFilesCb;
  GtkWidget *beepWhenActionsCompleteSuccessfullyCb;
  GtkWidget *generalRightSpacerBox;
  GtkWidget *generalLeftSpacerBox;
  GtkWidget *diskImagesVbox;
  GtkWidget *generalFrame;
  GtkWidget *prodosFrame;
  GtkWidget *generalVbox;
  GtkWidget *prodosVbox;
  GtkWidget *confirmDiskImageFormatCb;
  GtkWidget *defaultToReadOnlyCb;
  GtkWidget *allowWriteAccessCb;
  GtkWidget *allowLowerCaseLettersCb;
  GtkWidget *useSparseAllocationCb;
  GtkWidget *diskImagesSpacerBox;
  GtkWidget *fileViewerVbox;
  GtkWidget *convertersFrame;
  GtkWidget *conversionOptionsFrame;
  GtkWidget *convertersVbox;
  GtkWidget *convertersHbox;
  GtkWidget *convertersLeftVbox;
  GtkWidget *convertersRightVbox;
  GtkWidget *compressionVbox;
  /*GtkWidget *spacerBox;*/
  GtkWidget *highASCIITextCb;
  GtkWidget *cpmTextCb;
  GtkWidget *pascalTextCb;
  GtkWidget *pascalCodeCb;
  GtkWidget *applesoftBASICCb;
  GtkWidget *integerBASICCb;
  GtkWidget *assemblySourceCb;
  GtkWidget *proDOSFoldersCb;
  GtkWidget *disassembleCodeCb;
  GtkWidget *resourceForksCb;
  GtkWidget *gwpTeachAWGSCb;
  GtkWidget *eightBitWordProcessorCb;
  GtkWidget *appleworksWPCb;
  GtkWidget *appleworksDBCb;
  GtkWidget *appleworksSSCb;
  GtkWidget *hiresImagesCb;
  GtkWidget *doubleHiresImagesCb;
  GtkWidget *superHiresImagesCb;
  GtkWidget *printShopGraphicsCb;
  GtkWidget *macpaintImagesCb;
  GtkWidget *relaxTypeCheckingOnGraphicsCb;
  GtkWidget *scrollHorizontallyCb;
  GtkWidget *highlightHexDumpColumnsCb;
  GtkWidget *preferSyntaxHighlightingCb;
  GtkWidget *disassembleBRKCOPCp;
  GtkWidget *preferBWforHiresImagesCb;
  GtkAdjustment *viewerFileSizeAdjustment;
  GtkWidget *preferredDHRHbox;
  GtkWidget *preferredDHRLabel;
  GList *preferredDHRComboItems = NULL;
  GtkWidget *preferredDHRCombo;
  GtkWidget *viewerFileSizeHbox;
  GtkWidget *viewerFileSizeLabel;
  GtkWidget *viewerFileSizeSpinner;
  GtkWidget *kBytesLabel;
  GtkWidget *conversionOptionsVbox;
  GtkWidget *defaultCompressionMethodLabel;
  GtkWidget *noCompressionCb;
  GtkWidget *squeezeCb;
  GtkWidget *squeezeLabel;
  GtkWidget *dynamicLZW1Cb;
  GtkWidget *dynamicLZW1Label;
  GtkWidget *dynamicLZW2Cb;
  GtkWidget *dynamicLZW2Label;
  GtkWidget *twelveBitLZCCb;
  GtkWidget *twelveBitLZCLabel;
  GtkWidget *sixteenBitLZCCb;
  GtkWidget *sixteenBitLZCLabel;
  GtkWidget *deflateCb;
  GtkWidget *deflateLabel;
  GtkWidget *bzip2Cb;
  GtkWidget *bzip2Label;
  GtkWidget *filesVbox;
  GtkWidget *folderForTemporaryFilesLabel;
  GtkWidget *ok_button;
  GtkWidget *cancel_button;
  GtkWidget *apply_button;
  GtkWidget *help_button;

  /* --- Create the dialog --- */
  /*dialog_window = gtk_dialog_new();*/
  dialog_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);

  /* --- Trap the window close signal to release the grab --- */
  gtk_signal_connect(GTK_OBJECT(dialog_window), "destroy",
                      GTK_SIGNAL_FUNC(closing_dialog),
                      &dialog_window);

  /* --- Set the title --- */
  gtk_window_set_title(GTK_WINDOW(dialog_window), "Preferences");

  /* --- Add a small border --- */
  gtk_container_border_width(GTK_CONTAINER(dialog_window), 5);

  /* --- Set the window size. --- */
  /*gtk_widget_set_usize(dialog_window, 500, 450);*/

  /* --- Show the dialog --- */
  gtk_widget_show(dialog_window);

  dialogVbox = gtk_vbox_new(FALSE, 0);
  gtk_container_add(GTK_CONTAINER(dialog_window), dialogVbox);
  gtk_widget_show(dialogVbox);

  /*notebook = create_notebook(dialog_window, GTK_POS_TOP);*/
  notebook = create_notebook(dialogVbox, GTK_POS_TOP);

  /* --- Add pages to the notebook --- */
  generalTab = add_page(notebook, "General");
  diskImagesTab = add_page(notebook, "Disk Images");
  fileViewerTab = add_page(notebook, "File Viewer");
  compressionTab = add_page(notebook, "Compression");
  filesTab = add_page(notebook, "Files");

  /* General tab */
  generalHbox = gtk_hbox_new(FALSE, 0);

  gtk_widget_show(generalHbox);

  gtk_container_add(GTK_CONTAINER(generalTab), generalHbox);

  columnsFrame = gtk_frame_new("Columns");

  gtk_widget_show(columnsFrame);

  gtk_box_pack_start(GTK_BOX(generalHbox), columnsFrame, TRUE, TRUE, 0);

  /* Left side of general tab */
  generalLeftVbox = gtk_vbox_new(FALSE, 0);

  gtk_container_add(GTK_CONTAINER(columnsFrame), generalLeftVbox);

  gtk_widget_show(generalLeftVbox);

  pathnameCb = gtk_check_button_new_with_label("Pathname");
  typeCb = gtk_check_button_new_with_label("Type");
  auxTypeCb = gtk_check_button_new_with_label("Aux Type");
  modDateCb = gtk_check_button_new_with_label("Mod Date");
  formatCb = gtk_check_button_new_with_label("Format");
  sizeCb = gtk_check_button_new_with_label("Size");
  ratioCb = gtk_check_button_new_with_label("Ratio");
  packedCb = gtk_check_button_new_with_label("Packed");
  accessCb = gtk_check_button_new_with_label("Access");
  defaultsButton = gtk_button_new_with_label("Defaults");

  gtk_box_pack_start(GTK_BOX(generalLeftVbox), pathnameCb, TRUE, TRUE, 0);
  gtk_box_pack_start(GTK_BOX(generalLeftVbox), typeCb, TRUE, TRUE, 0);
  gtk_box_pack_start(GTK_BOX(generalLeftVbox), auxTypeCb, TRUE, TRUE, 0);
  gtk_box_pack_start(GTK_BOX(generalLeftVbox), modDateCb, TRUE, TRUE, 0);
  gtk_box_pack_start(GTK_BOX(generalLeftVbox), formatCb, TRUE, TRUE, 0);
  gtk_box_pack_start(GTK_BOX(generalLeftVbox), sizeCb, TRUE, TRUE, 0);
  gtk_box_pack_start(GTK_BOX(generalLeftVbox), ratioCb, TRUE, TRUE, 0);
  gtk_box_pack_start(GTK_BOX(generalLeftVbox), packedCb, TRUE, TRUE, 0);
  gtk_box_pack_start(GTK_BOX(generalLeftVbox), accessCb, TRUE, TRUE, 0);
  gtk_box_pack_start(GTK_BOX(generalLeftVbox), defaultsButton, TRUE, TRUE, 0);

  gtk_widget_show(pathnameCb);
  gtk_widget_show(typeCb);
  gtk_widget_show(auxTypeCb);
  gtk_widget_show(modDateCb);
  gtk_widget_show(formatCb);
  gtk_widget_show(sizeCb);
  gtk_widget_show(ratioCb);
  gtk_widget_show(packedCb);
  gtk_widget_show(accessCb);
  gtk_widget_show(defaultsButton);

  /* Left spacer */
  generalLeftSpacerBox = gtk_button_new_with_label(" ");
  gtk_box_pack_start(GTK_BOX(generalLeftVbox), generalLeftSpacerBox, TRUE, TRUE, 0);
  gtk_widget_show(generalLeftSpacerBox);

  /* Right side of general tab */
  generalRightVbox = gtk_vbox_new(FALSE, 0);

  gtk_box_pack_start(GTK_BOX(generalHbox), generalRightVbox, TRUE, TRUE, 0);

  gtk_widget_show(generalRightVbox);

  nufxArchivesFrame = gtk_frame_new("NuFX (ShrinkIt) archives");
  filenameMungingFrame = gtk_frame_new("Filename munging");
  systemFrame = gtk_frame_new("System");
  miscellaneousFrame = gtk_frame_new("Miscellaneous");

  gtk_box_pack_start(GTK_BOX(generalRightVbox), nufxArchivesFrame, TRUE, TRUE, 0);
  gtk_box_pack_start(GTK_BOX(generalRightVbox), filenameMungingFrame, TRUE, TRUE, 0);
  gtk_box_pack_start(GTK_BOX(generalRightVbox), systemFrame, TRUE, TRUE, 0);
  gtk_box_pack_start(GTK_BOX(generalRightVbox), miscellaneousFrame, TRUE, TRUE, 0);

  gtk_widget_show(nufxArchivesFrame);
  gtk_widget_show(filenameMungingFrame);
  gtk_widget_show(systemFrame);
  gtk_widget_show(miscellaneousFrame);

  nufxArchivesVbox = gtk_vbox_new(FALSE, 0);
  filenameMungingVbox = gtk_vbox_new(FALSE, 0);
  systemVbox = gtk_vbox_new(FALSE, 0);
  miscellaneousVbox = gtk_vbox_new(FALSE, 0);

  gtk_container_add(GTK_CONTAINER(nufxArchivesFrame), nufxArchivesVbox);
  gtk_container_add(GTK_CONTAINER(filenameMungingFrame), filenameMungingVbox);
  gtk_container_add(GTK_CONTAINER(systemFrame), systemVbox);
  gtk_container_add(GTK_CONTAINER(miscellaneousFrame), miscellaneousVbox);

  gtk_widget_show(nufxArchivesVbox);
  gtk_widget_show(filenameMungingVbox);
  gtk_widget_show(systemVbox);
  gtk_widget_show(miscellaneousVbox);

  /* NuFX frame */
  mimicShrinkitQuirksCb = gtk_check_button_new_with_label("Mimic ShrinkIt Quirks");
  handleBadMacArchivesCb = gtk_check_button_new_with_label("Handle \"bad Mac\" archives");
  reduceErrorCheckingCb = gtk_check_button_new_with_label("Reduce error checking (not recommended)");

  gtk_box_pack_start(GTK_BOX(nufxArchivesVbox), mimicShrinkitQuirksCb, TRUE, TRUE, 0);
  gtk_box_pack_start(GTK_BOX(nufxArchivesVbox), handleBadMacArchivesCb, TRUE, TRUE, 0);
  gtk_box_pack_start(GTK_BOX(nufxArchivesVbox), reduceErrorCheckingCb, TRUE, TRUE, 0);

  gtk_widget_show(mimicShrinkitQuirksCb);
  gtk_widget_show(handleBadMacArchivesCb);
  gtk_widget_show(reduceErrorCheckingCb);

  /* Filename munging frame */
  displayDOS33FilenamesCb = gtk_check_button_new_with_label("Display DOS 3.3 Filenames in lower case");
  showSpacesAsUnderscoresCb = gtk_check_button_new_with_label("Show spaces as underscores");

  gtk_box_pack_start(GTK_BOX(filenameMungingVbox), displayDOS33FilenamesCb, TRUE, TRUE, 0);
  gtk_box_pack_start(GTK_BOX(filenameMungingVbox), showSpacesAsUnderscoresCb, TRUE, TRUE, 0);

  gtk_widget_show(displayDOS33FilenamesCb);
  gtk_widget_show(showSpacesAsUnderscoresCb);

  /* System frame */
  fileTypeAssociationsButton = gtk_button_new_with_label("File type associations");

  gtk_box_pack_start(GTK_BOX(systemVbox), fileTypeAssociationsButton, TRUE, TRUE, 0);

  gtk_widget_show(fileTypeAssociationsButton);

  /* Miscellaneous frame */
  stripPathnamesWhenPastingFilesCb = gtk_check_button_new_with_label("Strip pathnames when pasting files");
  beepWhenActionsCompleteSuccessfullyCb = gtk_check_button_new_with_label("Beep when actions complete successfully");

  gtk_box_pack_start(GTK_BOX(miscellaneousVbox), stripPathnamesWhenPastingFilesCb, TRUE, TRUE, 0);
  gtk_box_pack_start(GTK_BOX(miscellaneousVbox), beepWhenActionsCompleteSuccessfullyCb, TRUE, TRUE, 0);

  gtk_widget_show(stripPathnamesWhenPastingFilesCb);
  gtk_widget_show(beepWhenActionsCompleteSuccessfullyCb);

  /* Right spacer */
  generalRightSpacerBox = gtk_button_new_with_label(" ");
  gtk_box_pack_start(GTK_BOX(generalRightVbox), generalRightSpacerBox, TRUE, TRUE, 0);
  gtk_widget_show(generalRightSpacerBox);

  /* Disk images tab */
  diskImagesVbox = gtk_vbox_new(FALSE, 0);

  gtk_container_add(GTK_CONTAINER(diskImagesTab), diskImagesVbox);

  gtk_widget_show(diskImagesVbox);

  /* General frame */
  generalFrame = gtk_frame_new("General");

  gtk_widget_show(generalFrame);

  gtk_box_pack_start(GTK_BOX(diskImagesVbox), generalFrame, TRUE, TRUE, 0);

  generalVbox = gtk_vbox_new(FALSE, 0);

  gtk_container_add(GTK_CONTAINER(generalFrame), generalVbox);

  gtk_widget_show(generalVbox);

  confirmDiskImageFormatCb = gtk_check_button_new_with_label("Confirm disk image format");

  gtk_box_pack_start(GTK_BOX(generalVbox), confirmDiskImageFormatCb, TRUE, TRUE, 0);

  gtk_widget_show(confirmDiskImageFormatCb);

  defaultToReadOnlyCb = gtk_check_button_new_with_label("Default to read-only when opening volumes");

  gtk_box_pack_start(GTK_BOX(generalVbox), defaultToReadOnlyCb, TRUE, TRUE, 0);

  gtk_widget_show(defaultToReadOnlyCb);

  allowWriteAccessCb = gtk_check_button_new_with_label("Allow write access to physical disk 0 (not recommended)");

  gtk_box_pack_start(GTK_BOX(generalVbox), allowWriteAccessCb, TRUE, TRUE, 0);

  gtk_widget_show(allowWriteAccessCb);

  /* ProDOS frame */
  prodosFrame = gtk_frame_new("ProDOS");

  gtk_widget_show(prodosFrame);

  gtk_box_pack_start(GTK_BOX(diskImagesVbox), prodosFrame, TRUE, TRUE, 0);

  prodosVbox = gtk_vbox_new(FALSE, 0);

  gtk_container_add(GTK_CONTAINER(prodosFrame), prodosVbox);

  gtk_widget_show(prodosVbox);

  allowLowerCaseLettersCb = gtk_check_button_new_with_label("Allow lower case letters and spaces in filenames");

  gtk_box_pack_start(GTK_BOX(prodosVbox), allowLowerCaseLettersCb, TRUE, TRUE, 0);

  gtk_widget_show(allowLowerCaseLettersCb);

  useSparseAllocationCb = gtk_check_button_new_with_label("Use sparse allocation for empty blocks");

  gtk_box_pack_start(GTK_BOX(prodosVbox), useSparseAllocationCb, TRUE, TRUE, 0);

  gtk_widget_show(useSparseAllocationCb);

  /* spacer */
  diskImagesSpacerBox = gtk_button_new_with_label(" ");
  gtk_box_pack_start(GTK_BOX(diskImagesVbox), diskImagesSpacerBox, TRUE, TRUE, 0);
  gtk_widget_show(diskImagesSpacerBox);

  /* File viewer Tab */
  fileViewerVbox = gtk_vbox_new(FALSE, 0);

  gtk_container_add(GTK_CONTAINER(fileViewerTab), fileViewerVbox);

  gtk_widget_show(fileViewerVbox);

  /* File viewer frames */
  convertersFrame = gtk_frame_new("Converters");

  gtk_box_pack_start(GTK_BOX(fileViewerVbox), convertersFrame, TRUE, TRUE, 0);

  conversionOptionsFrame = gtk_frame_new("Conversion options");

  gtk_box_pack_start(GTK_BOX(fileViewerVbox), conversionOptionsFrame, TRUE, TRUE, 0);

  gtk_widget_show(convertersFrame);
  gtk_widget_show(conversionOptionsFrame);

  /* Converters frame */
  convertersVbox = gtk_vbox_new(FALSE, 0);

  gtk_container_add(GTK_CONTAINER(convertersFrame), convertersVbox);

  gtk_widget_show(convertersVbox);

  convertersHbox = gtk_hbox_new(FALSE, 0);

  gtk_widget_show(convertersHbox);

  gtk_box_pack_start(GTK_BOX(convertersVbox), convertersHbox, TRUE, TRUE, 0);

  convertersLeftVbox = gtk_vbox_new(FALSE, 0);

  gtk_box_pack_start(GTK_BOX(convertersHbox), convertersLeftVbox, TRUE, TRUE, 0);

  convertersRightVbox = gtk_vbox_new(FALSE, 0);

  gtk_box_pack_start(GTK_BOX(convertersHbox), convertersRightVbox, TRUE, TRUE, 0);

  gtk_widget_show(convertersVbox);

  gtk_widget_show(convertersHbox);

  gtk_widget_show(convertersRightVbox);

  gtk_widget_show(convertersLeftVbox);

  /* Left side of converters frame */
  highASCIITextCb = gtk_check_button_new_with_label("High-ASCII text");
  gtk_box_pack_start(GTK_BOX(convertersLeftVbox), highASCIITextCb, TRUE, TRUE, 0);
  gtk_widget_show(highASCIITextCb);

  cpmTextCb = gtk_check_button_new_with_label("CP/M text");
  gtk_box_pack_start(GTK_BOX(convertersLeftVbox), cpmTextCb, TRUE, TRUE, 0);
  gtk_widget_show(cpmTextCb);

  pascalTextCb = gtk_check_button_new_with_label("Pascal text");
  gtk_box_pack_start(GTK_BOX(convertersLeftVbox), pascalTextCb, TRUE, TRUE, 0);
  gtk_widget_show(pascalTextCb);

  pascalCodeCb = gtk_check_button_new_with_label("Pascal code");
  gtk_box_pack_start(GTK_BOX(convertersLeftVbox), pascalCodeCb, TRUE, TRUE, 0);
  gtk_widget_show(pascalCodeCb);

  applesoftBASICCb = gtk_check_button_new_with_label("Applesoft BASIC");
  gtk_box_pack_start(GTK_BOX(convertersLeftVbox), applesoftBASICCb, TRUE, TRUE, 0);
  gtk_widget_show(applesoftBASICCb);

  integerBASICCb = gtk_check_button_new_with_label("Integer BASIC");
  gtk_box_pack_start(GTK_BOX(convertersLeftVbox), integerBASICCb, TRUE, TRUE, 0);
  gtk_widget_show(integerBASICCb);

  assemblySourceCb = gtk_check_button_new_with_label("Assembly source");
  gtk_box_pack_start(GTK_BOX(convertersLeftVbox), assemblySourceCb, TRUE, TRUE, 0);
  gtk_widget_show(assemblySourceCb);

  proDOSFoldersCb = gtk_check_button_new_with_label("ProDOS folders");
  gtk_box_pack_start(GTK_BOX(convertersLeftVbox), proDOSFoldersCb, TRUE, TRUE, 0);
  gtk_widget_show(proDOSFoldersCb);

  disassembleCodeCb = gtk_check_button_new_with_label("Disassemble code");
  gtk_box_pack_start(GTK_BOX(convertersLeftVbox), disassembleCodeCb, TRUE, TRUE, 0);
  gtk_widget_show(disassembleCodeCb);

  resourceForksCb = gtk_check_button_new_with_label("Resource forks");
  gtk_box_pack_start(GTK_BOX(convertersLeftVbox), resourceForksCb, TRUE, TRUE, 0);
  gtk_widget_show(resourceForksCb);

  /* Right side of converters frame */
  gwpTeachAWGSCb = gtk_check_button_new_with_label("GWP (Teach, AWGS)");
  gtk_box_pack_start(GTK_BOX(convertersRightVbox), gwpTeachAWGSCb, TRUE, TRUE, 0);
  gtk_widget_show(gwpTeachAWGSCb);

  eightBitWordProcessorCb = gtk_check_button_new_with_label("8-bit word processor");
  gtk_box_pack_start(GTK_BOX(convertersRightVbox), eightBitWordProcessorCb, TRUE, TRUE, 0);
  gtk_widget_show(eightBitWordProcessorCb);

  appleworksWPCb = gtk_check_button_new_with_label("AppleWorks WP");
  gtk_box_pack_start(GTK_BOX(convertersRightVbox), appleworksWPCb, TRUE, TRUE, 0);
  gtk_widget_show(appleworksWPCb);

  appleworksDBCb = gtk_check_button_new_with_label("AppleWorks DB");
  gtk_box_pack_start(GTK_BOX(convertersRightVbox), appleworksDBCb, TRUE, TRUE, 0);
  gtk_widget_show(appleworksDBCb);

  appleworksSSCb = gtk_check_button_new_with_label("AppleWorks SS");
  gtk_box_pack_start(GTK_BOX(convertersRightVbox), appleworksSSCb, TRUE, TRUE, 0);
  gtk_widget_show(appleworksSSCb);

  hiresImagesCb = gtk_check_button_new_with_label("Hi-Res images");
  gtk_box_pack_start(GTK_BOX(convertersRightVbox), hiresImagesCb, TRUE, TRUE, 0);
  gtk_widget_show(hiresImagesCb);

  doubleHiresImagesCb = gtk_check_button_new_with_label("Double Hi-Res images");
  gtk_box_pack_start(GTK_BOX(convertersRightVbox), doubleHiresImagesCb, TRUE, TRUE, 0);
  gtk_widget_show(doubleHiresImagesCb);

  superHiresImagesCb = gtk_check_button_new_with_label("Super Hi-Res images");
  gtk_box_pack_start(GTK_BOX(convertersRightVbox), superHiresImagesCb, TRUE, TRUE, 0);
  gtk_widget_show(superHiresImagesCb);

  printShopGraphicsCb = gtk_check_button_new_with_label("Print Shop graphics");
  gtk_box_pack_start(GTK_BOX(convertersRightVbox), printShopGraphicsCb, TRUE, TRUE, 0);
  gtk_widget_show(printShopGraphicsCb);

  macpaintImagesCb = gtk_check_button_new_with_label("MacPaint images");
  gtk_box_pack_start(GTK_BOX(convertersRightVbox), macpaintImagesCb, TRUE, TRUE, 0);
  gtk_widget_show(macpaintImagesCb);

  /* Last one in converter frame */
  relaxTypeCheckingOnGraphicsCb = gtk_check_button_new_with_label("Relax type-checking on graphics");
  gtk_box_pack_start(GTK_BOX(convertersVbox), relaxTypeCheckingOnGraphicsCb, TRUE, TRUE, 0);
  gtk_widget_show(relaxTypeCheckingOnGraphicsCb);

  /* Conversion options frame */
  conversionOptionsVbox = gtk_vbox_new(FALSE, 0);

  gtk_container_add(GTK_CONTAINER(conversionOptionsFrame), conversionOptionsVbox);

  gtk_widget_show(conversionOptionsVbox);

  scrollHorizontallyCb = gtk_check_button_new_with_label("Scroll horizontally instead of wrapping words");
  gtk_box_pack_start(GTK_BOX(conversionOptionsVbox), scrollHorizontallyCb, TRUE, TRUE, 0);
  gtk_widget_show(scrollHorizontallyCb);

  highlightHexDumpColumnsCb = gtk_check_button_new_with_label("Highlight hex dump columns (small files)");
  gtk_box_pack_start(GTK_BOX(conversionOptionsVbox), highlightHexDumpColumnsCb, TRUE, TRUE, 0);
  gtk_widget_show(highlightHexDumpColumnsCb);

  preferSyntaxHighlightingCb = gtk_check_button_new_with_label("Prefer syntax highlighting on BASIC programs");
  gtk_box_pack_start(GTK_BOX(conversionOptionsVbox), preferSyntaxHighlightingCb, TRUE, TRUE, 0);
  gtk_widget_show(preferSyntaxHighlightingCb);

  disassembleBRKCOPCp = gtk_check_button_new_with_label("Disassemble BRK/COP as single-byte instructions");
  gtk_box_pack_start(GTK_BOX(conversionOptionsVbox), disassembleBRKCOPCp, TRUE, TRUE, 0);
  gtk_widget_show(disassembleBRKCOPCp);

  preferBWforHiresImagesCb = gtk_check_button_new_with_label("Prefer B&W for hi-res images");
  gtk_box_pack_start(GTK_BOX(conversionOptionsVbox), preferBWforHiresImagesCb, TRUE, TRUE, 0);
  gtk_widget_show(preferBWforHiresImagesCb);

  preferredDHRHbox = gtk_hbox_new(FALSE, 0);

  gtk_box_pack_start(GTK_BOX(conversionOptionsVbox), preferredDHRHbox, TRUE, TRUE, 0);

  gtk_widget_show(preferredDHRHbox);

  preferredDHRLabel = gtk_label_new("Preferred DHR");
  gtk_misc_set_alignment(GTK_MISC(preferredDHRLabel), 0, 0.5);
  gtk_box_pack_start(GTK_BOX(preferredDHRHbox), preferredDHRLabel, TRUE, TRUE, 0);
  gtk_widget_show(preferredDHRLabel);

  /*
   * --- Create a list of the items first
   */
  preferredDHRComboItems = g_list_append(preferredDHRComboItems, "Black & White");
  preferredDHRComboItems = g_list_append(preferredDHRComboItems, "Latched color (recommended)");
  preferredDHRComboItems = g_list_append(preferredDHRComboItems, "Simple 140");
  preferredDHRComboItems = g_list_append(preferredDHRComboItems, "Sliding window");

  /* --- Make a combo box. --- */
  preferredDHRCombo = gtk_combo_new();

  /* --- Create the drop down portion of the combo --- */
  gtk_combo_set_popdown_strings(GTK_COMBO(preferredDHRCombo), preferredDHRComboItems);

  /* --- Default the text in the field to a value --- */
  gtk_entry_set_text(GTK_ENTRY(GTK_COMBO(preferredDHRCombo)->entry), "Latched color (recommended)");

  /* --- Make the edit portion non-editable.  They can pick a
   *     value from the drop down, they just can't end up with
   *     a value that's not in the drop down.
   */
  gtk_entry_set_editable(GTK_ENTRY(GTK_COMBO(preferredDHRCombo)->entry), FALSE);

  gtk_box_pack_start(GTK_BOX(preferredDHRHbox), preferredDHRCombo, TRUE, TRUE, 0);

  gtk_widget_show(preferredDHRCombo);

  viewerFileSizeHbox = gtk_hbox_new(FALSE, 0);

  gtk_box_pack_start(GTK_BOX(fileViewerVbox), viewerFileSizeHbox, TRUE, TRUE, 0);

  gtk_widget_show(viewerFileSizeHbox);

  viewerFileSizeLabel = gtk_label_new("Viewer file size");
  gtk_misc_set_alignment(GTK_MISC(viewerFileSizeLabel), 0, 0.5);
  gtk_box_pack_start(GTK_BOX(viewerFileSizeHbox), viewerFileSizeLabel, TRUE, TRUE, 0);
  gtk_widget_show(viewerFileSizeLabel);

  viewerFileSizeAdjustment = (GtkAdjustment *)gtk_adjustment_new(1024, 0, 32767, 64, 64, 0);
  viewerFileSizeSpinner =  gtk_spin_button_new(viewerFileSizeAdjustment, 1.0, 5);
  gtk_box_pack_start(GTK_BOX(viewerFileSizeHbox), viewerFileSizeSpinner, TRUE, TRUE, 0);
  gtk_widget_show(viewerFileSizeSpinner);

  kBytesLabel = gtk_label_new("kBytes");
  gtk_misc_set_alignment(GTK_MISC(kBytesLabel), 0, 0.5);
  gtk_widget_show(kBytesLabel);
  gtk_box_pack_start(GTK_BOX(viewerFileSizeHbox), kBytesLabel, TRUE, TRUE, 0);


  /* Compression tab */
  compressionVbox = gtk_vbox_new(FALSE, 0);

  gtk_container_add(GTK_CONTAINER(compressionTab), compressionVbox);

  gtk_widget_show(compressionVbox);

  defaultCompressionMethodLabel = gtk_label_new("Default compression method:");
  gtk_widget_show(defaultCompressionMethodLabel);
  gtk_box_pack_start(GTK_BOX(compressionVbox), defaultCompressionMethodLabel, TRUE, TRUE, 0);

  noCompressionCb = gtk_check_button_new_with_label("No compression");
  gtk_box_pack_start(GTK_BOX(compressionVbox), noCompressionCb, TRUE, TRUE, 0);
  gtk_widget_show(noCompressionCb);

  squeezeCb = gtk_check_button_new_with_label("Squeeze");
  gtk_box_pack_start(GTK_BOX(compressionVbox), squeezeCb, TRUE, TRUE, 0);
  gtk_widget_show(squeezeCb);

  squeezeLabel = gtk_label_new("Uses a combination of RLE and Huffman.\rNot compatible with ProDOS 8 ShrinkIt.");
  gtk_box_pack_start(GTK_BOX(compressionVbox), squeezeLabel, TRUE, TRUE, 0);
  gtk_widget_show(squeezeLabel);

  dynamicLZW1Cb = gtk_check_button_new_with_label("Dynamic LZW/1");
  gtk_box_pack_start(GTK_BOX(compressionVbox), dynamicLZW1Cb, TRUE, TRUE, 0);
  gtk_widget_show(dynamicLZW1Cb);

  dynamicLZW1Label = gtk_label_new("The compression method used by ProDOS 8 ShrinkIt.");
  gtk_box_pack_start(GTK_BOX(compressionVbox), dynamicLZW1Label, TRUE, TRUE, 0);
  gtk_widget_show(dynamicLZW1Label);

  dynamicLZW2Cb = gtk_check_button_new_with_label("Dynamic LZW/2 (recommended)");
  gtk_box_pack_start(GTK_BOX(compressionVbox), dynamicLZW2Cb, TRUE, TRUE, 0);
  gtk_widget_show(dynamicLZW2Cb);

  dynamicLZW2Label = gtk_label_new("The compression method used by GS/ShrinkIt");
  gtk_box_pack_start(GTK_BOX(compressionVbox), dynamicLZW2Label, TRUE, TRUE, 0);
  gtk_widget_show(dynamicLZW2Label);

  twelveBitLZCCb = gtk_check_button_new_with_label("12-bit LZC");
  gtk_box_pack_start(GTK_BOX(compressionVbox), twelveBitLZCCb, TRUE, TRUE, 0);
  gtk_widget_show(twelveBitLZCCb);

  twelveBitLZCLabel = gtk_label_new("Compression used by UNIX \"compress\" command.\rNot compatible with ProDOS 8 ShrinkIt.");
  gtk_box_pack_start(GTK_BOX(compressionVbox), twelveBitLZCLabel, TRUE, TRUE, 0);
  gtk_widget_show(twelveBitLZCLabel);

  sixteenBitLZCCb = gtk_check_button_new_with_label("16-bit LZC");
  gtk_box_pack_start(GTK_BOX(compressionVbox), sixteenBitLZCCb, TRUE, TRUE, 0);
  gtk_widget_show(sixteenBitLZCCb);

  sixteenBitLZCLabel = gtk_label_new("Compression used by UNIX \"compress\" command.\rNot compatible with ProDOS 8 ShrinkIt.");
  gtk_box_pack_start(GTK_BOX(compressionVbox), sixteenBitLZCLabel, TRUE, TRUE, 0);
  gtk_widget_show(sixteenBitLZCLabel);

  deflateCb = gtk_check_button_new_with_label("deflate");
  gtk_box_pack_start(GTK_BOX(compressionVbox), deflateCb, TRUE, TRUE, 0);
  gtk_widget_show(deflateCb);

  deflateLabel = gtk_label_new("Uses a combination of RLE and Huffman.\rNot compatible with ProDOS 8 ShrinkIt.");
  gtk_box_pack_start(GTK_BOX(compressionVbox), deflateLabel, TRUE, TRUE, 0);
  gtk_widget_show(deflateLabel);

  bzip2Cb = gtk_check_button_new_with_label("Bzip2");
  gtk_box_pack_start(GTK_BOX(compressionVbox), bzip2Cb, TRUE, TRUE, 0);
  gtk_widget_show(bzip2Cb);

  bzip2Label = gtk_label_new("Compression used by bzip2.\rNot compatible with any Apple II applications.");
  gtk_box_pack_start(GTK_BOX(compressionVbox), bzip2Label, TRUE, TRUE, 0);
  gtk_widget_show(bzip2Label);


  /* Files tab */
  filesVbox = gtk_vbox_new(FALSE, 0);

  gtk_container_add(GTK_CONTAINER(filesTab), filesVbox);

  gtk_widget_show(filesVbox);

  folderForTemporaryFilesLabel = gtk_label_new("Folder for temporary files:");
  gtk_widget_show(folderForTemporaryFilesLabel);
  gtk_box_pack_start(GTK_BOX(filesVbox), folderForTemporaryFilesLabel, TRUE, TRUE, 0);


  /* spacer */
  /*spacerBox = gtk_button_new_with_label(" ");
  gtk_box_pack_start(GTK_BOX(dialogVbox), spacerBox, TRUE, TRUE, 0);
  gtk_widget_show(spacerBox);*/

  /* Action area */
  actionHbox = gtk_hbox_new(FALSE, 0);

  gtk_widget_show(actionHbox);

  gtk_container_add(GTK_CONTAINER(dialogVbox), actionHbox);

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
  gtk_box_pack_start(GTK_BOX(actionHbox), ok_button, TRUE, TRUE, 0);

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
  gtk_box_pack_start(GTK_BOX(actionHbox), cancel_button, TRUE, TRUE, 0);

  /* --- Make the button visible. --- */
  gtk_widget_show(cancel_button);

  /*
   * --- Apply button
   */

  /* --- Create the "Apply" button --- */
  apply_button = gtk_button_new_with_label("Apply");

  gtk_signal_connect(GTK_OBJECT(apply_button), "clicked",
                     GTK_SIGNAL_FUNC(apply_func_preferences),
                     dialog_window);

  /* --- Add the "Apply" button to the dialog --- */
  gtk_box_pack_start(GTK_BOX(actionHbox), apply_button, TRUE, TRUE, 0);

  /* --- Make the button visible. --- */
  gtk_widget_show(apply_button);

  /*
   * --- Help button
   */

  /* --- Create the "Help" button --- */
  help_button = gtk_button_new_with_label("Help");

  gtk_signal_connect(GTK_OBJECT(help_button), "clicked",
                     GTK_SIGNAL_FUNC(help_func_preferences),
                     dialog_window);

  /* --- Add the "Help" button to the dialog --- */
  gtk_box_pack_start(GTK_BOX(actionHbox), help_button, TRUE, TRUE, 0);

  /* --- Make the button visible. --- */
  gtk_widget_show(help_button);

  /* --- Only this window can be used for now --- */
  gtk_grab_add(dialog_window);
}

