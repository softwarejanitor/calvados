#
# Makefile for cavaldos.  Pretty lame, needs to be improved.
#
NAME=calvados
CFLAGS=-g -Wall -o $(NAME)
#GTKFLAGS=-export-dynamic `pkg-config --cflags --libs gtk+-2.0`
GTKFLAGS=`pkg-config --cflags --libs gtk+-2.0`
SRCS=calvados.c select_volume.c closing_dialog.c close_dialog.c show_about.c \
	disk_sector_viewer_popup.c create_disk_image.c new_archive.c \
	open_file.c okfunc_create_disk_image.c okfunc_select_volume.c \
	help_func_create_disk_image.c help_func_select_volume.c \
        do_open_file.c save_to_file.c preferences.c print.c add_files.c \
	do_new_archive.c create_radio.c acceptfunc_add_files.c \
	help_func_add_files.c extract_files.c extractfunc_extract_files.c \
	help_func_extract_files.c disk_image_converter.c do_image_converter.c \
	do_add_files.c archive_info.c edit_comment.c help_func_archive_info.c \
	delete_file.c rename.c select_image_convert.c select_first_sst_image.c \
	recompress_files.c show_error.c file_viewer.c donefunc_file_viewer.c \
	help_func_file_viewer.c add_disk_image.c test.c findfunc_file_viewer.c \
	bulk_disk_image_converter.c close.c save_changes.c reopen.c copy.c paste.c \
	paste_special.c find.c select_all.c invert_selection.c create_subdirectory.c \
	open_as_disk_image.c edit_attributes.c rename_volume.c convert_to_disk_image.c \
	convert_to_archive_file.c import_file_from_wav.c import_bas_from_text.c \
	contents.c visit_website.c volume_copier_open_volume.c volume_copier_open_file.c \
	twomg_properties_editor.c eol_scanner.c do_eol_scan.c do_2mg_edit.c \
	do_volume_copier_open_file.c okfunc_volume_copier_open_volume.c \
	help_func_volume_copier_open_volume.c do_bulk_disk_converter.c
OBJS=$(SRCS:.c=.o)
HEADERS=calvados.h
CC=gcc
DESTDIR=/usr/local

INCLUDES=-I/usr/include/glib-2.0/ \
	-I/usr/lib/x86_64-linux-gnu/glib-2.0/include/ \
	-I/usr/include/pango-1.0/ -I/usr/include/cairo/ \
	-I/usr/include/gdk-pixbuf-2.0/ -I/usr/include/atk-1.0/ \
	-I/usr/include/gtk-unix-print-2.0/

all: calvados

calvados: $(SRCS) $(HEADERS)
	$(CC) $(CFLAGS) $(SRCS) $(GTKFLAGS) $(INCLUDES)

install:
	/usr/bin/install $(NAME) $(DESTDIR)/bin
	/usr/bin/install -D images $(DESTDIR)/images

clean:
	/bin/rm -f $(NAME)

