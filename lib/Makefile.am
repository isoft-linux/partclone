partcloneincludedir = $(includedir)/partclone-0.3.5
partcloneinclude_HEADERS = libpartclone.h	\
						   $(NULL)

lib_LTLIBRARIES = libpartclone.la
libpartclone_la_SOURCES = libpartclone.c	\
					      $(NULL)
libpartclone_la_CFLAGS = -DLIBDIR=\""$(libdir)"\"	\
                        -DPLUGINDIR=\""$(plugindir)"\"   \
                        ${LIBPARTCLONE_CFLAGS}	\
					     $(NULL)
libpartclone_la_LIBADD = ${DL_LIBS}	\
					     $(NULL)
