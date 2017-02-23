/**
 * Copyright (c) 2017 Leslie Zhai <xiang.zhai@i-soft.com.cn>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 */

#ifndef __LIBPARTCLONE_H__
#define __LIBPARTCLONE_H__

#define LIBPARTCLONE_EXPORTED __attribute__((__visibility__("default")))

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
    EXTFS = 0,
    HFSP,
    BTRFS,
    F2FS,
    MINIX,
    XFS,
    NTFS,
    FAT,
    EXFAT,
    UNKNOWN
} partType;

/* TODO: clone partition into image file */
LIBPARTCLONE_EXPORTED int partClone(partType type, char *part, char *img);

/* TODO: restore partition from image file */
LIBPARTCLONE_EXPORTED int partRestore(partType type, char *img, char *part);

/* TODO: define info structure instead of void ptr */
LIBPARTCLONE_EXPORTED int partInfo(char *img, void *info);

#ifdef __cplusplus
}
#endif

#endif /* __LIBPARTCLONE_H__ */
