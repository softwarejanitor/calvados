#include <gtk/gtk.h>
#include <gdk/gdkkeysyms.h>
#include <string.h>

#include "calvados.h"

extern char *open_file_ptr;

/* 
 *
 * do_volume_copier_open_file()
 *
 * Volume copier (open file).
 *
 */
void do_volume_copier_open_file(char *filename)
{
  /* --- Display message --- */
  g_print("Volume copier (open file) function goes here.\n");

  g_print("filename=%s\n", filename);
}

