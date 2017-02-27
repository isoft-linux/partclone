TESTS =  dd.test

if ENABLE_FS_TEST
if ENABLE_EXTFS
TESTS += ext2.test
TESTS += ext3.test
TESTS += ext4.test
endif

if ENABLE_BTRFS
TESTS += btrfs.test
endif

if ENABLE_FAT
TESTS += fat.test
endif

if ENABLE_REISERFS
TESTS += reiserfs.test
endif

if ENABLE_HFSP
TESTS += hfsplus.test
endif

if ENABLE_XFS
TESTS += xfs.test
endif

if ENABLE_EXFAT
TESTS += exfat.test
endif

if ENABLE_F2FS
TESTS += f2fs.test
endif

if ENABLE_NTFS
TESTS += ntfs.test
endif

if ENABLE_JFS
TESTS += jfs.test
endif

if ENABLE_BTRFS
TESTS += btrfs.test
endif

if ENABLE_EXFAT
TESTS += exfat.test
endif

if ENABLE_NILFS2
TESTS += nilfs2.test
endif

if ENABLE_NCURSESW
TESTS += ncursesw.test
endif
endif
CLEANFILES = floppy*

LIBPARTCLONE_CFLAGS = -I../lib

noinst_PROGRAMS = test-libpartclone	\
				  test-libpartclone-extfs	\
				  test-libpartclone-ntfs	\
				  test-libpartclone-info	\
				  $(NULL)

test_libpartclone_SOURCES = test-libpartclone.c	\
							$(NULL)
test_libpartclone_CFLAGS = ${LIBPARTCLONE_CFLAGS} \
						   $(NULL)
test_libpartclone_LDADD = ${DL_LIBS}  \
						  -lpartclone	\
						  $(NULL)

test_libpartclone_extfs_SOURCES = test-libpartclone-extfs.c	\
								  $(NULL)
test_libpartclone_extfs_CFLAGS = -DPLUGINDIR=\""$(plugindir)"\"	\
								 ${LIBPARTCLONE_CFLAGS}	\
								 $(NULL)
test_libpartclone_extfs_LDADD = ${DL_LIBS}	\
                                 -lpartclone \
								$(NULL)

test_libpartclone_ntfs_SOURCES = test-libpartclone-ntfs.c	\
								 $(NULL)
test_libpartclone_ntfs_CFLAGS = -DPLUGINDIR=\""$(plugindir)"\"   \
								${LIBPARTCLONE_CFLAGS}	\
								$(NULL)
test_libpartclone_ntfs_LDADD = ${DL_LIBS}  \
							   $(NULL)

test_libpartclone_info_SOURCES = test-libpartclone-info.c	\
								 $(NULL)
test_libpartclone_info_CFLAGS = -DPLUGINDIR=\""$(plugindir)"\"   \
								${LIBPARTCLONE_CFLAGS}  \
								$(NULL)
test_libpartclone_info_LDADD = ${DL_LIBS}  \
							   $(NULL)
