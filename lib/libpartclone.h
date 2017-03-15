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

#ifndef LIBPARTCLONE_EXPORTED
#define LIBPARTCLONE_EXPORTED __attribute__((__visibility__("default")))
#endif

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
    LIBPARTCLONE_EXTFS = 0,
    LIBPARTCLONE_HFSP,
    LIBPARTCLONE_BTRFS,
    LIBPARTCLONE_F2FS,
    LIBPARTCLONE_MINIX,
    LIBPARTCLONE_XFS,
    LIBPARTCLONE_NTFS,
    LIBPARTCLONE_FAT,
    LIBPARTCLONE_EXFAT,
    LIBPARTCLONE_UNKNOWN
} partType;

typedef void *(*callback_routine)(void *);

typedef struct {
    char type[16];
    char devSize[32];
    char usedSize[32];
    char freeSize[32];
    char blockSize[32];
    int  imageVersion;
    int  cpuBits;
    char partcloneVersion[16];
    // ......
} partInfo_t;

/* TODO: clone partition into image file */
LIBPARTCLONE_EXPORTED int partClone(partType type, 
                                    const char *part, 
                                    const char *img, 
                                    int  overwrite,
                                    callback_routine fptr, 
                                    void *arg);

/* TODO: restore partition from image file */
LIBPARTCLONE_EXPORTED int partRestore(partType type, 
                                      const char *img, 
                                      const char *part, 
                                      callback_routine fptr, 
                                      void *arg);

/* TODO: define info structure instead of void ptr */
LIBPARTCLONE_EXPORTED int partInfo(const char *img, partInfo_t *info);

LIBPARTCLONE_EXPORTED int partCloneCancel(int cancel);
#ifdef __cplusplus
}
#endif

#endif /* __LIBPARTCLONE_H__ */
