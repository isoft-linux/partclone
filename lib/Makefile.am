partcloneincludedir = $(includedir)/libpartclone
partcloneinclude_HEADERS = libpartclone.h	\
						   $(NULL)

lib_LTLIBRARIES = libpartclone.la
libpartclone_la_SOURCES = libpartclone.c	\
					      $(NULL)
libpartclone_la_CFLAGS = -DLIBDIR=\""$(libdir)"\"	\
                        -DPLUGINDIR=\""$(plugindir)"\"   \
                        ${LIBPARTCLONE_CFLAGS}	\
					     $(NULL)
libpartclone_la_LDFLAGS = -version-info $(LT_VERSION_INFO)
libpartclone_la_LIBADD = ${DL_LIBS}	\
					     $(NULL)
