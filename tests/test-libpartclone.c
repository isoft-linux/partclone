/**
 * Copyright (c) 2017 Leslie Zhai <xiang.zhai@i-soft.com.cn>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 */

#include <stdio.h>
#include <dlfcn.h>
#include <string.h>

#include "libpartclone.h"

static void *callback(void *arg) 
{
    float *ret = (float *)arg;
    //char *ss = (char *)arg;
    if ((int)*ret%50 == 1)
        printf("callback[%0.2f]\n", (float)*ret);

    //printf("callback[%s]\n", ss);
    return NULL;
}

int main(int argc, char *argv[]) 
{
    partType type = LIBPARTCLONE_UNKNOWN;
    const char *src = NULL;
    const char *dst = NULL;
    const char *fmt = NULL;
    if (argc <2) {
        printf("command line:test-libpartclone clone(info|...) src dst file_type(extfs|ntfs|...)\n");
        return 0;
    }
    // command line[test clone  /dev/sda7 /home/xx extfs]
    if (strcmp(argv[1],"clone") == 0) {
         if (argc == 5){
            fmt = argv[4];
            if (strcmp(fmt, "extfs") == 0) {
                type = LIBPARTCLONE_EXTFS;
            } else if (strcmp(fmt, "ntfs") == 0) {
                type = LIBPARTCLONE_NTFS;
            } else if (strcmp(fmt, "fat") == 0) {
                type = LIBPARTCLONE_FAT;
            } else if (strcmp(fmt, "btrfs") == 0) {
                type = LIBPARTCLONE_BTRFS;
            } else if (strcmp(fmt, "f2fs") == 0) {
                type = LIBPARTCLONE_F2FS;
            } else if (strcmp(fmt, "hfsp") == 0) {
                type = LIBPARTCLONE_HFSP;
            } else if (strcmp(fmt, "minix") == 0) {
                type = LIBPARTCLONE_MINIX;
            } else if (strcmp(fmt, "xfs") == 0) {
                type = LIBPARTCLONE_XFS;
            } else if (strcmp(fmt, "exfat") == 0) {
                type = LIBPARTCLONE_EXFAT;
            } else {
                printf("DEBUG: %s, %s, line %d,no this type.test done!\n", __FILE__, __func__, __LINE__);
                return 0;
            }


            src = argv[2];
            dst = argv[3];

            printf("DEBUG: %s, %s, line %d:clone [%s] to [%s],type[%s]\n", __FILE__, __func__, __LINE__,
                   src,dst,fmt);

            partClone(type,
                      src,
                      dst,
                      callback,
                      NULL);
        }
        printf("DEBUG: %s, %s, line %d:test done!\n", __FILE__, __func__, __LINE__);
    } else if (strcmp(argv[1],"info") == 0){
        partInfo_t info;
        memset(&info, 0, sizeof(partInfo_t));
        partInfo(argv[2],&info);

        printf("\n\n\n[%s]'s info:\n",argv[2]);
        printf("fileSystem:\t%s\ndeviceSize:\t%s\nspace in use:\t%s\nfree space:\t%s\n......\n",
               info.type,
               info.devSize,
               info.usedSize,
               info.freeSize);
    } else {
        printf("command line:test-libpartclone clone(info|...) src dst file_type(extfs|ntfs|...)\n");
    }

    return 0;
}
