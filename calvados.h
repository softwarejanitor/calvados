/*
 *
 * cavaldos.h
 *
 * Include for cavaldos.
 *
 */

#define WINDOW_WIDTH 1300
#define WINDOW_HEIGHT 725

void close_dialog(GtkWidget *widget, gpointer data);
void closing_dialog(GtkWidget *widget, gpointer data);
void select_volume();
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
void new_archive();
void preferences();

