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
    // command line[test clone  /dev/sda7 /home/xx extfs]
    if (argc == 5) {
        if (strcmp(argv[1],"clone") == 0) {
            fmt = argv[4];
            if (strcmp(fmt, "extfs") == 0) {
                type = LIBPARTCLONE_EXTFS;
            } else if (strcmp(fmt, "ntfs") == 0) {
                type = LIBPARTCLONE_NTFS;
            } else {
                //todo...
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
    } else {

#if 1
        printf("command line:test-libpartclone clone src dst file_type(extfs|ntfs|...)\n");
#else
        partClone(LIBPARTCLONE_EXTFS,
              "/dev/sda7", 
              "/home/test/gits/test/sda7_2.img", 
              callback, 
              NULL);
#endif
    }

    return 0;
}
