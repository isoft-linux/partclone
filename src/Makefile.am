AUTOMAKE_OPTIONS = subdir-objects
AM_CPPFLAGS = -DLOCALEDIR=\"$(localedir)\" -D_FILE_OFFSET_BITS=64 -DLIBPARTCLONE
LIBADD = $(LIBINTL)
plugin_LTLIBRARIES=libpartclone.info.la libpartclone.dd.la libpartclone.restore.la libpartclone.chkimg.la libpartclone.imager.la libpartclone.imgfuse.la libpartclone.block.la
TOOLBOX = srcdir=$(top_srcdir) builddir=$(top_builddir) $(top_srcdir)/toolbox

BTRFS_SOURCE=\
btrfs/bitops.h btrfs/ctree.h btrfs/extent_io.c btrfs/inode-item.c btrfs/math.h btrfs/radix-tree.c btrfs/root-tree.c btrfs/ulist.c btrfs/volumes.c\
btrfs/btrfsck.h btrfs/dir-item.c btrfs/extent_io.h btrfs/inode-map.c btrfs/print-tree.c btrfs/radix-tree.h btrfs/send.h btrfs/ulist.h btrfs/volumes.h\
btrfs/btrfs-list.c btrfs/disk-io.c btrfs/extent-tree.c btrfs/ioctl.h btrfs/print-tree.h btrfs/raid6.c btrfs/send-stream.c btrfs/utils.c\
btrfs/btrfs-list.h btrfs/disk-io.h btrfs/file-item.c btrfs/kerncompat.h btrfs/qgroup.c btrfs/rbtree.c btrfs/send-stream.h btrfs/utils.h\
btrfs/crc32c.c btrfs/free-space-cache.c btrfs/list.h btrfs/qgroup.h btrfs/rbtree.h btrfs/send-utils.c btrfs/utils-lib.c btrfs/rbtree-utils.c\
btrfs/crc32c.h btrfs/extent-cache.c btrfs/free-space-cache.h btrfs/list_sort.c btrfs/qgroup-verify.c btrfs/repair.c btrfs/send-utils.h\
btrfs/uuid-tree.c btrfs/ctree.c btrfs/extent-cache.h btrfs/hash.h btrfs/list_sort.h btrfs/qgroup-verify.h btrfs/repair.h btrfs/transaction.h\
btrfs/version.h btrfs/rbtree-utils.h btrfs/rbtree_augmented.h btrfs/internal.h btrfs/commands.h

XFS_SOURCE=\
xfs/atomic.h xfs/libxfs_priv.h xfs/xfs_arch.h xfs/xfs_da_format.h xfs/xfs_inode_fork.h xfs/bitops.h xfs/libxlog.h xfs/xfs_attr.c xfs/xfs_dir2_block.c xfs/xfs_inode.h xfs/cache.c xfs/linux.c xfs/xfs_attr_leaf.c xfs/xfs_dir2.c xfs/xfs_log_format.h xfs/cache.h xfs/linux.h xfs/xfs_attr_leaf.h xfs/xfs_dir2_data.c xfs/xfs_log_recover.h xfs/command.h xfs/list.h xfs/xfs_attr_remote.c xfs/xfs_dir2.h xfs/xfs_log_rlimit.c xfs/crc32.c xfs/logitem.c xfs/xfs_attr_remote.h xfs/xfs_dir2_leaf.c xfs/xfs_metadump.h xfs/crc32defs.h xfs/parent.h xfs/xfs_attr_sf.h xfs/xfs_dir2_node.c xfs/xfs_mount.h xfs/path.h xfs/xfs_bit.c xfs/xfs_dir2_priv.h xfs/xfs_quota_defs.h  xfs/platform_defs.h xfs/xfs_bit.h xfs/xfs_dir2_sf.c xfs/xfs_rtbitmap.c xfs/handle.h xfs/platform_defs.h.in xfs/xfs_bmap_btree.c xfs/xfs_dquot_buf.c xfs/xfs_sb.c xfs/hlist.h xfs/project.h xfs/xfs_bmap_btree.h xfs/xfs_format.h xfs/xfs_sb.h xfs/init.c xfs/radix-tree.c xfs/xfs_bmap.c xfs/xfs_fs.h xfs/xfs_shared.h xfs/init.h xfs/radix-tree.h xfs/xfs_bmap.h xfs/xfs.h xfs/xfs_symlink_remote.c xfs/input.h xfs/rdwr.c xfs/xfs_btree.c xfs/xfs_ialloc_btree.c xfs/xfs_trace.h xfs/jdm.h xfs/trans.c xfs/xfs_btree.h xfs/xfs_ialloc_btree.h xfs/xfs_trans.h xfs/kmem.c xfs/util.c xfs/xfs_btree_trace.h xfs/xfs_ialloc.c xfs/xfs_trans_resv.c xfs/kmem.h xfs/xfs_alloc_btree.c xfs/xfs_cksum.h xfs/xfs_ialloc.h xfs/xfs_trans_resv.h xfs/libxfs_api_defs.h xfs/xfs_alloc_btree.h xfs/xfs_da_btree.c xfs/xfs_inode_buf.c xfs/xfs_trans_space.h xfs/libxfs.h xfs/xfs_alloc.c xfs/xfs_da_btree.h xfs/xfs_inode_buf.h xfs/xfs_types.h xfs/libxfs_io.h xfs/xfs_alloc.h xfs/xfs_da_format.c xfs/xfs_inode_fork.c xfs/xqm.h xfs/crc32table.h

EXFATFS_SOURCE=exfat/cluster.c exfat/utf.c exfat/utils.c exfat/lookup.c exfat/io.c exfat/log.c exfat/node.c exfat/mount.c exfat/time.c

F2FS_SOURCE=f2fs/fsck.c f2fs/libf2fs.c f2fs/fsck.h f2fs/mount.c f2fs/f2fs_fs.h f2fs/list.h f2fs/f2fs.h

if ENABLE_STATIC
AM_LDFLAGS=-static
endif

if ENABLE_TINFO
LIBS+=-ltinfo
endif

AM_CFLAGS=-D_FILE_OFFSET_BITS=64 -DLIBPARTCLONE

if ENABLE_MEMTRACE
AM_CFLAGS+=-DMEMTRACE -DMEMWATCH -DMW_STDIO
endif

if ENABLE_NCURSESW
AM_CFLAGS+=-I/usr/include/ncursesw
endif

LIBPARTCLONE_CFLAGS=-I$(top_srcdir)/lib -I.

version.h: FORCE
	$(TOOLBOX) --update-version

main_files=main.c partclone.c progress.c checksum.c partclone.h progress.h gettext.h checksum.h bitmap.h

libpartclone_info_la_SOURCES=info.c partclone.c checksum.c partclone.h fs_common.h checksum.h
libpartclone_info_la_CFLAGS = ${LIBPARTCLONE_CFLAGS}
libpartclone_info_la_LDFLAGS=-avoid-version

libpartclone_restore_la_SOURCES=$(main_files) ddclone.c ddclone.h
libpartclone_restore_la_CFLAGS=-DRESTORE -DDD ${LIBPARTCLONE_CFLAGS}
libpartclone_restore_la_LDFLAGS=-avoid-version

libpartclone_chkimg_la_SOURCES=$(main_files) ddclone.c ddclone.h
libpartclone_chkimg_la_CFLAGS=-DCHKIMG -DDD ${LIBPARTCLONE_CFLAGS}
libpartclone_chkimg_la_LDFLAGS=-avoid-version

libpartclone_dd_la_SOURCES=$(main_files) ddclone.c ddclone.h
libpartclone_dd_la_CFLAGS=-DDD ${LIBPARTCLONE_CFLAGS}
libpartclone_dd_la_LDFLAGS=-avoid-version

libpartclone_imager_la_SOURCES=$(main_files) ddclone.c ddclone.h
libpartclone_imager_la_CFLAGS=-DIMG ${LIBPARTCLONE_CFLAGS}
libpartclone_imager_la_LDFLAGS=-avoid-version

if ENABLE_EXTFS
plugin_LTLIBRARIES += libpartclone.extfs.la
libpartclone_extfs_la_SOURCES=$(main_files) extfsclone.c extfsclone.h
libpartclone_extfs_la_CFLAGS=-DEXTFS ${LIBPARTCLONE_CFLAGS}
libpartclone_extfs_la_LIBADD=-lext2fs -lcom_err -lpthread
libpartclone_extfs_la_LDFLAGS=-avoid-version
endif

if ENABLE_REISERFS
plugin_LTLIBRARIES += libpartclone.reiserfs.la
libpartclone_reiserfs_la_SOURCES=$(main_files) reiserfsclone.c reiserfsclone.h
libpartclone_reiserfs_la_CFLAGS=-DREISERFS ${LIBPARTCLONE_CFLAGS}
libpartclone_reiserfs_la_LIBADD=-lreiserfs -ldal
libpartclone_reiserfs_la_LDFLAGS=-avoid-version
endif

if ENABLE_REISER4
plugin_LTLIBRARIES += libpartclone.reiser4.la
libpartclone_reiser4_la_SOURCES=$(main_files) reiser4clone.c reiser4clone.h
libpartclone_reiser4_la_CFLAGS=-DREISER4 ${LIBPARTCLONE_CFLAGS}
libpartclone_reiser4_la_LIBADD=-lreiser4 -laal
libpartclone_reiser4_la_LDFLAGS=-avoid-version
endif

if ENABLE_HFSP
plugin_LTLIBRARIES += libpartclone.hfsp.la
libpartclone_hfsp_la_SOURCES=$(main_files) hfsplusclone.c hfsplusclone.h
libpartclone_hfsp_la_CFLAGS=-DHFSPLUS ${LIBPARTCLONE_CFLAGS}
libpartclone_hfsp_la_LDFLAGS=-avoid-version
endif

if ENABLE_XFS
plugin_LTLIBRARIES += libpartclone.xfs.la
libpartclone_xfs_la_SOURCES=$(main_files) xfsclone.c xfsclone.h $(XFS_SOURCE)
libpartclone_xfs_la_CFLAGS=-DXFS -D_GNU_SOURCE -DNDEBUG $(UUID_CFLAGS) ${LIBPARTCLONE_CFLAGS}
libpartclone_xfs_la_LIBADD=-lrt -lpthread -luuid
libpartclone_xfs_la_LDFLAGS=-avoid-version
endif

if ENABLE_EXFAT
plugin_LTLIBRARIES += libpartclone.exfat.la
libpartclone_exfat_la_SOURCES=$(main_files) exfatclone.c exfatclone.h $(EXFATFS_SOURCE)
libpartclone_exfat_la_CFLAGS=-DEXFAT -D_GNU_SOURCE -std=c99 ${LIBPARTCLONE_CFLAGS}
libpartclone_exfat_la_LDFLAGS=-avoid-version
endif

if ENABLE_F2FS
plugin_LTLIBRARIES += libpartclone.f2fs.la
libpartclone_f2fs_la_SOURCES=$(main_files) f2fsclone.c f2fsclone.h $(F2FS_SOURCE)
libpartclone_f2fs_la_CFLAGS=-DF2FS ${LIBPARTCLONE_CFLAGS}
libpartclone_f2fs_la_LIBADD=-luuid
libpartclone_f2fs_la_LDFLAGS=-avoid-version
endif

if ENABLE_NILFS2
plugin_LTLIBRARIES += libpartclone.nilfs2.la
libpartclone_nilfs2_la_SOURCES=$(main_files) nilfsclone.c nilfsclone.h
libpartclone_nilfs2_la_CFLAGS=-DNILFS ${LIBPARTCLONE_CFLAGS}
libpartclone_nilfs2_la_LIBADD=-lnilfs
libpartclone_nilfs2_la_LDFLAGS=-avoid-version
endif

if ENABLE_FAT
plugin_LTLIBRARIES += libpartclone.fat.la
libpartclone_fat_la_SOURCES=$(main_files) fatclone.c fatclone.h
libpartclone_fat_la_CFLAGS=-DFAT ${LIBPARTCLONE_CFLAGS}
libpartclone_fat_la_LDFLAGS=-avoid-version
endif

plugin_LTLIBRARIES += libpartclone.ntfsfixboot.la
libpartclone_ntfsfixboot_la_SOURCES=ntfsfixboot.c
libpartclone_ntfsfixboot_la_LDFLAGS=-avoid-version
if ENABLE_NTFS
plugin_LTLIBRARIES += libpartclone.ntfs.la
libpartclone_ntfs_la_SOURCES=$(main_files) ntfsclone-ng.c ntfsclone-ng.h
if ENABLE_NTFS_3G
libpartclone_ntfs_la_CFLAGS=-DNTFS3G ${LIBPARTCLONE_CFLAGS}
libpartclone_ntfs_la_LIBADD=-lntfs-3g
else
libpartclone_ntfs_la_CFLAGS=-DNTFS ${LIBPARTCLONE_CFLAGS}
libpartclone_ntfs_la_LIBADD=-lntfs
endif
libpartclone_ntfs_la_LDFLAGS=-avoid-version
endif

if ENABLE_UFS
plugin_LTLIBRARIES += libpartclone.ufs.la
libpartclone_ufs_la_SOURCES=$(main_files) ufsclone.c ufsclone.h
libpartclone_ufs_la_CFLAGS=-DUFS -D_GNU_SOURCE ${LIBPARTCLONE_CFLAGS}
libpartclone_ufs_la_LIBADD=-lufs -lbsd
libpartclone_ufs_la_LDFLAGS=-avoid-version
endif

if ENABLE_VMFS
plugin_LTLIBRARIES += libpartclone.vmfs.la
libpartclone_vmfs_la_SOURCES=$(main_files) vmfsclone.c vmfsclone.h
libpartclone_vmfs_la_CFLAGS=-DVMFS -D_GNU_SOURCE $(UUID_CFLAGS) ${LIBPARTCLONE_CFLAGS}
libpartclone_vmfs_la_LIBADD=-lvmfs -luuid
libpartclone_vmfs_la_LDFLAGS=-avoid-version

plugin_LTLIBRARIES += libpartclone.vmfs5.la
libpartclone_vmfs5_la_SOURCES=$(main_files) vmfs5clone.c vmfsclone.h
libpartclone_vmfs5_la_CFLAGS=-DVMFS -D_GNU_SOURCE $(UUID_CFLAGS) ${LIBPARTCLONE_CFLAGS}
libpartclone_vmfs5_la_LIBADD=-lvmfs -luuid
libpartclone_vmfs5_la_LDFLAGS=-avoid-version

plugin_LTLIBRARIES += libpartclone.fstype.la
libpartclone_fstype_la_SOURCES=fstype.c
libpartclone_fstype_la_CFLAGS=-DVMFS -D_GNU_SOURCE $(UUID_CFLAGS) ${LIBPARTCLONE_CFLAGS}
libpartclone_fstype_la_LIBADD=-lvmfs -luuid
libpartclone_fstype_la_LDFLAGS=-avoid-version

endif

if ENABLE_JFS
plugin_LTLIBRARIES += libpartclone.jfs.la
libpartclone_jfs_la_SOURCES=$(main_files) jfsclone.c jfsclone.h
libpartclone_jfs_la_CFLAGS=-DJFS ${LIBPARTCLONE_CFLAGS}
libpartclone_jfs_la_LIBADD=-luuid -ljfs
libpartclone_jfs_la_LDFLAGS=-avoid-version
endif

if ENABLE_BTRFS
plugin_LTLIBRARIES += libpartclone.btrfs.la
libpartclone_btrfs_la_SOURCES=$(main_files) btrfsclone.c btrfsclone.h $(BTRFS_SOURCE)
libpartclone_btrfs_la_CFLAGS=-DBTRFS -DBTRFS_FLAT_INCLUDES -D_XOPEN_SOURCE=700 -D_GNU_SOURCE ${LIBPARTCLONE_CFLAGS}
libpartclone_btrfs_la_LIBADD=-luuid -lblkid
libpartclone_btrfs_la_LDFLAGS=-avoid-version
endif

if ENABLE_MINIX
plugin_LTLIBRARIES += libpartclone.minix.la
libpartclone_minix_la_SOURCES=$(main_files) minixclone.c minixclone.h
libpartclone_minix_la_CFLAGS=-DMINIX ${LIBPARTCLONE_CFLAGS}
libpartclone_minix_la_LDFLAGS=-avoid-version
endif

if ENABLE_FUSE
libpartclone_imgfuse_la_SOURCES=fuseimg.c partclone.c checksum.c partclone.h fs_common.h checksum.h
libpartclone_imgfuse_la_CFLAGS=-lfuse ${LIBPARTCLONE_CFLAGS}
libpartclone_imgfuse_la_LDFLAGS=-avoid-version

libpartclone_block_la_SOURCES=readblock.c partclone.c checksum.c partclone.h fs_common.h checksum.h
libpartclone_block_la_LDFLAGS=-avoid-version
endif


FORCE:
