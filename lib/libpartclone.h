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

/* FIXME: I have no idea why use char[] as the type? */
typedef struct {
    char type[16];              /* Why not partType */
    unsigned long long devSize;           /* Why not unsinged long long */
    unsigned long long usedSize;
    partType newType;
    unsigned long long total;   /* I need it for precise comparison! */
    unsigned long long used;
    /* TODO: Add more if any ... */
} partInfo_t;

/**
 * callback routine
 * @param percent
 * @param remaining
 * @return NULL
 */
typedef void *(*callback_routine)(void *, void *);

/**
 * error routine
 * @param arg thisPtr for C++ static member function
 * @param msg Error message
 * @return NULL
 */
typedef void *(*error_routine)(void *, void *);

/**
 * Clone Partition to Image file or Partition
 *
 * @param type Partition Type
 * @param src Partition such as /dev/sda1 
 * @param dst Image save Path or Partition such as /dev/sdb1
 * @param overwrite Whether or not Overwrite the Image file
 * @param callback Callback function pointer
 * @param error Error function pointer
 * @param arg The arguement for Callback or Error function pointer
 * @return 0 for success but -1 for failure
 */
LIBPARTCLONE_EXPORTED int partClone(partType type, 
                                    const char *src, 
                                    const char *dst, 
                                    int  overwrite,
                                    callback_routine callback,
                                    error_routine error,
                                    void *arg);

/**
 * Partition restore from the Image file
 * @param type Partition Type
 * @param img the Image file path
 * @param part Partition
 * @param callback
 * @param error
 * @param arg The arguement for callback and error function pointer
 * @return 0
 */
LIBPARTCLONE_EXPORTED int partRestore(partType type, 
                                      const char *img, 
                                      const char *part, 
                                      callback_routine callback,
                                      error_routine error,
                                      void *arg);

/**
 * Partition Image information
 *
 * @param img the Image path
 * @param info reference value
 * @return 0
 */
LIBPARTCLONE_EXPORTED int partInfo(const char *img, partInfo_t *info);

LIBPARTCLONE_EXPORTED int partCloneCancel(int cancel);

#ifdef __cplusplus
}
#endif

#endif /* __LIBPARTCLONE_H__ */
