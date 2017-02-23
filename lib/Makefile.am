partcloneincludedir = $(includedir)/partclone-0.3.5
partcloneinclude_HEADERS = partclone.h	\
						   $(NULL)

lib_LTLIBRARIES = libpartclone.la
libpartclone_la_SOURCES = partclone.c	\
					      $(NULL)
libpartclone_la_CFLAGS = -DLIBDIR=\""$(libdir)"\"	\
					     $(NULL)
libpartclone_la_LIBADD = ${DL_LIBS}	\
					     $(NULL)
