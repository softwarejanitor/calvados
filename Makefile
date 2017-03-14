#
# Makefile for cavaldos.  Prety lame, needs to be improved.
#
NAME=calvados
CFLAGS=-g -Wall -o $(NAME)
GTKFLAGS=-export-dynamic `pkg-config --cflags --libs gtk+-2.0`
SRCS=calvados.c select_volume.c closing_dialog.c close_dialog.c show_about.c \
	disk_sector_viewer_popup.c create_disk_image.c new_archive.c \
	open_file.c okfunc_create_disk_image.c okfunc_select_volume.c \
	help_func_create_disk_image.c help_func_select_volume.c \
        do_open_file.c save_to_file.c preferences.c
HEADERS=calvados.h
CC=gcc
DESTDIR=/usr/local

INCLUDE=-I/usr/include/glib-2.0/ -I/usr/lib/x86_64-linux-gnu/glib-2.0/include/ -I/usr/include/pango-1.0/ -I/usr/include/cairo/ -I/usr/include/gdk-pixbuf-2.0/ -I/usr/include/atk-1.0/

all: calvados

calvados: $(SRCS) $(HEADERS)
	$(CC) $(CFLAGS) $(SRCS) $(GTKFLAGS)

install:
	/usr/bin/install $(NAME) $(DESTDIR)/bin
	/usr/bin/install -D images $(DESTDIR)/images

clean:
	/bin/rm -f $(NAME)

