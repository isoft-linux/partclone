AUTOMAKE_OPTIONS = subdir-objects 
SUBDIRS= po src lib tests fail-mbr
#SUBDIRS += docs

ACLOCAL_AMFLAGS = -I m4

EXTRA_DIST = m4/ChangeLog  config.rpath toolbox src/deplib_version.c src/version.h src/ufs

pkgconfigdir = $(libdir)/pkgconfig
pkgconfig_DATA = libpartclone.pc

ChangeLog: FORCE
	srcdir=. $(SHELL) ./toolbox --update-log

FORCE:
