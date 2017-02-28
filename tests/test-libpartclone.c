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
    partClone(LIBPARTCLONE_EXTFS, 
              "/dev/sda7", 
              "/home/test/gits/test/sda7_2.img", 
              callback, 
              NULL);
    printf("DEBUG: %s, %s, line %d:test done!\n", __FILE__, __func__, __LINE__);

    return 0;
}
