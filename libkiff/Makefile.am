AM_CPPFLAGS = $(GTK_CFLAGS)
AM_LDFLAGS =

lib_LTLIBRARIES = $(KIFF_LIB_PATH)/libkiff.la

__KIFF_LIB_PATH__libkiff_la_LDFLAGS = \
	-version-info $(LIBKIFF_MAJOR_VERSION):$(LIBKIFF_MINOR_VERSION):$(LIBKIFF_MICRO_VERSION)

__KIFF_LIB_PATH__libkiff_la_LIBADD = $(GTK_LIBS)

__KIFF_LIB_PATH__libkiff_la_rootdir = $(includedir)/libkiff

__KIFF_LIB_PATH__libkiff_la_root_HEADERS = \
	$(KIFF_INCLUDE_PATH)/libkiff/kiff_window.h

__KIFF_LIB_PATH__libkiff_la_SOURCES = \
	kiff_window.c

clean-local:
	rm -f *~
