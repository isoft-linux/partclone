AUTOMAKE_OPTIONS = subdir-objects 
SUBDIRS= po src lib docs tests fail-mbr

ACLOCAL_AMFLAGS = -I m4

EXTRA_DIST = m4/ChangeLog  config.rpath toolbox src/deplib_version.c src/version.h src/ufs debian

pkgconfigdir = $(libdir)/pkgconfig
pkgconfig_DATA = partclone-0.3.5.pc

ChangeLog: FORCE
	srcdir=. $(SHELL) ./toolbox --update-log

FORCE:
