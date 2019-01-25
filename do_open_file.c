#include <gtk/gtk.h>
#include <gdk/gdkkeysyms.h>
#include <string.h>

#include "calvados.h"

extern char *open_file_ptr;

/* 
 *
 * do_open_file()
 *
 * Open a file.
 *
 */
void do_open_file(char *filename)
{
  /* --- Display message --- */
  g_print("Open file function goes here.\n");
  g_print("filename=%s\n", filename);

  strncpy(open_file_ptr, filename, 255);
}

