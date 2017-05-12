AUTOMAKE_OPTIONS = subdir-objects 
SUBDIRS= po src lib tests
if ENABLE_FAIL_MBR
SUBDIRS += fail-mbr
endif
#SUBDIRS += docs

ACLOCAL_AMFLAGS = -I m4

EXTRA_DIST = m4/ChangeLog  config.rpath toolbox src/deplib_version.c src/version.h src/ufs

pkgconfigdir = $(libdir)/pkgconfig
pkgconfig_DATA = libpartclone.pc

ChangeLog: FORCE
	srcdir=. $(SHELL) ./toolbox --update-log

FORCE:

AM_DISTCHECK_CONFIGURE_FLAGS = --disable-reiserfs --enable-fat --enable-hfsp --enable-btrfs --disable-ncursesw --enable-ntfs --enable-exfat --enable-f2fs --enable-minix --disable-nilfs2 --enable-xfs
#DISTCHECK_CONFIGURE_FLAGS = dc=ok
