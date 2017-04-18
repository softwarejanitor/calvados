/*
 *
 * cavaldos.h
 *
 * Include for cavaldos.
 *
 */

/* Main window size */
#define WINDOW_WIDTH 1300
#define WINDOW_HEIGHT 725
#define LIST_WIDTH 1280
#define LIST_HEIGHT 705

enum {
  COL_VOLUME_OR_DEVICE_NAME = 0,
  COL_REMARK,
  NUM_SELECT_VOLUME_COLS
};

/* Prototypes */
void close_dialog(GtkWidget *widget, gpointer data);
void closing_dialog(GtkWidget *widget, gpointer data);
void select_volume(GtkWidget *widget, gpointer data);
void show_about(GtkWidget *widget, gpointer data);
void disk_sector_viewer_popup();
void okfunc_create_disk_image(GtkWidget *widget, gpointer data);
void okfunc_select_volume(GtkWidget *widget, gpointer data);
void help_func_create_disk_image(GtkWidget *widget, gpointer data);
void help_func_select_volume(GtkWidget *widget, gpointer data);
void create_disk_image();
void do_open_file(char *filename);
void open_file();
void save_to_file(char *filename);
void do_new_archive(char *filename);
void new_archive();
void preferences();
void print_page(GtkWidget *widget, gpointer user_data);
void add_files();
GtkWidget *create_radio(GtkWidget *box, GSList **group, char *rLabel);
void acceptfunc_add_files(GtkWidget *widget, gpointer data);
void help_func_add_files(GtkWidget *widget, gpointer data);
void extract_files();
void extractfunc_extract_files(GtkWidget *widget, gpointer data);
void help_func_extract_files(GtkWidget *widget, gpointer data);
void disk_image_converter(GtkWidget *widget, gpointer data);
void do_image_converter(char *filename);
void do_add_files(char *filename);
void archive_info();
void help_func_archive_info(GtkWidget *widget, gpointer data);
void delete_file(GtkWidget *widget, gpointer data);
void rename_file(GtkWidget *widget, gpointer data);
void select_first_sst_image(GtkWidget *widget, gpointer data);
void select_image_convert(GtkWidget *widget, gpointer data);
void recompress_files(GtkWidget *widget, gpointer data);
void show_error(GtkWidget *widget, gpointer data, char *message);
GtkWidget *display_image(GtkWidget *widget, gpointer data, GtkWidget *mw_box);
void file_viewer(GtkWidget *widget, gpointer data);
void donefunc_file_viewer(GtkWidget *widget, gpointer data);
void help_func_file_viewer(GtkWidget *widget, gpointer data);
void add_disk_image(GtkWidget *widget, gpointer data);
void test(GtkWidget *widget, gpointer data);
void edit_comment(GtkWidget *widget, gpointer data);
void findfunc_file_viewer(GtkWidget *widget, gpointer data);
void bulk_disk_image_converter(GtkWidget *widget, gpointer data);
void close_menu_item(GtkWidget *widget, gpointer data);
void save_changes(GtkWidget *widget, gpointer data);
void reopen_menu_item(GtkWidget *widget, gpointer data);
void copy_menu_item(GtkWidget *widget, gpointer data);
void paste(GtkWidget *widget, gpointer data);
void paste_special(GtkWidget *widget, gpointer data);
void find(GtkWidget *widget, gpointer data);
void select_all(GtkWidget *widget, gpointer data);
void invert_selection(GtkWidget *widget, gpointer data);
void create_subdirectory(GtkWidget *widget, gpointer data);
void open_as_disk_image(GtkWidget *widget, gpointer data);
void edit_attributes(GtkWidget *widget, gpointer data);
void rename_volume(GtkWidget *widget, gpointer data);
void convert_to_disk_image(GtkWidget *widget, gpointer data);
void convert_to_archive_file(GtkWidget *widget, gpointer data);
void import_file_from_wav(GtkWidget *widget, gpointer data);
void import_bas_from_text(GtkWidget *widget, gpointer data);
void contents(GtkWidget *widget, gpointer data);
void visit_website(GtkWidget *widget, gpointer data);
void volume_copier_open_volume(GtkWidget *widget, gpointer data);
void volume_copier_open_file(GtkWidget *widget, gpointer data);
void twomg_properties_editor(GtkWidget *widget, gpointer data);
void eol_scanner(GtkWidget *widget, gpointer data);
void do_eol_scan(char *filename);
void do_2mg_edit(char *filename);
void do_volume_copier_open_file(char *filename);
void okfunc_volume_copier_open_volume(GtkWidget *widget, gpointer data);
void help_func_volume_copier_open_volume(GtkWidget *widget, gpointer data);
void do_bulk_disk_converter(char *filename);

