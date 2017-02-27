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

typedef int (*fptr_libpartclone_main)(int argc, 
                                      char **argv, 
                                      callback_routine fptr, 
                                      void *arg);

static void *callback(void *arg) 
{
    printf("DEBUG: %s, %s, line %d\n", __FILE__, __func__, __LINE__);
    return NULL;
}

int main(int argc, char *argv[]) 
{
    void *dp = NULL;
    char *err = NULL;

    dp = dlopen(PLUGINDIR "/libpartclone.info.so", RTLD_NOW);
    if (dp == NULL) {
        printf("ERROR: %s\n", dlerror());
        goto cleanup;
    }

    fptr_libpartclone_main libpartclone_main = 
        (fptr_libpartclone_main)dlsym(dp, "libpartclone_main");
    err = dlerror();
    if (err) {
        printf("ERROR: %s\n", err);
        goto cleanup;
    }

    libpartclone_main(argc, argv, callback, NULL);

cleanup:
    if (dp) {
        dlclose(dp);
        dp = NULL;
    }

    return 0;
}
