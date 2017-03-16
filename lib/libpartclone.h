/**
 * Copyright (c) 2017 Leslie Zhai <xiang.zhai@i-soft.com.cn>
 * Copyright (c) 2017 fj <fujiang.zhu@i-soft.com.cn>
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

/**
 * callback routine
 * @param percent
 * @param remaining
 * @return NULL
 */
typedef void *(*callback_routine)(void *, void *);

typedef struct {
    char type[16];
    char devSize[32];
    char usedSize[32];
    char freeSize[32];
    char blockSize[32];
    int  imageVersion;
    int  cpuBits;
    char partcloneVersion[16];
    // TODO: Add more if any ...
} partInfo_t;

/**
 * Clone Partition to Image file
 *
 * @param type Partition Type
 * @param part Partition such as /dev/sda1 
 * @param img Image save Path
 * @param overwrite Whether or not Overwrite the Image file
 * @param fptr Callback function pointer
 * @param arg The arguement for Callback function pointer
 * @return 0 for success but -1 for failure
 */
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
