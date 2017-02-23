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

#if ENABLE_REISER4
#TESTS += reiser4.test
#endif

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

#if ENABLE_UFS
#TESTS += ufs.test
#endif

#if ENABLE_VMFS
#TESTS += vmfs.test
#endif

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

noinst_PROGRAMS = test-libpartclone-extfs	\
				  test-libpartclone-ntfs	\
				  $(NULL)

test_libpartclone_extfs_SOURCES = test-libpartclone-extfs.c	\
								  $(NULL)
test_libpartclone_extfs_CFLAGS = -DLIBDIR=\""$(libdir)"\"	\
								 $(NULL)
test_libpartclone_extfs_LDADD = ${DL_LIBS}	\
								$(NULL)

test_libpartclone_ntfs_SOURCES = test-libpartclone-ntfs.c	\
								 $(NULL)
test_libpartclone_ntfs_CFLAGS = -DLIBDIR=\""$(libdir)"\"   \
								$(NULL)
test_libpartclone_ntfs_LDADD = ${DL_LIBS}  \
							   $(NULL)
