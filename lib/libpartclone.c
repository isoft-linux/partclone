/**
 * Copyright (c) 2017 Leslie Zhai <xiang.zhai@i-soft.com.cn>
 * Copyright (c) 2017 fj <fujiang.zhu@i-soft.com.cn>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 */

#include <dlfcn.h>
#include <stdio.h>
#include <limits.h>
#include <string.h>
#include <stdlib.h>

#include "libpartclone.h"

int g_cancel_clone = 0;

typedef int (*fptr_libpartclone_main)(int argc,
                                      char **argv,
                                      callback_routine callback,
                                      error_routine error,
                                      void *arg);

int partClone(partType type,
              const char *src,
              const char *dst,
              int overwrite,
              callback_routine callback,
              error_routine error,
              void *arg)
{
    void *dp = NULL;
    char *err = NULL;
    int argc = 0;
    char **argv = NULL;
    char path[PATH_MAX] = { '\0' };
    int ret = 0;

    if (!src || !dst) {
        ret = -1;
        goto cleanup;
    }

    switch (type) {
    case LIBPARTCLONE_FAT:
        snprintf(path, sizeof(path) - 1, "%s/libpartclone.fat.so", PLUGINDIR);
        break;
    case LIBPARTCLONE_BTRFS:
        snprintf(path, sizeof(path) - 1, "%s/libpartclone.btrfs.so", PLUGINDIR);
        break;
    case LIBPARTCLONE_F2FS:
        snprintf(path, sizeof(path) - 1, "%s/libpartclone.f2fs.so", PLUGINDIR);
        break;
    case LIBPARTCLONE_HFSP:
        snprintf(path, sizeof(path) - 1, "%s/libpartclone.hfsp.so", PLUGINDIR);
        break;
    case LIBPARTCLONE_MINIX:
        snprintf(path, sizeof(path) - 1, "%s/libpartclone.minix.so", PLUGINDIR);
        break;
    case LIBPARTCLONE_XFS:
        snprintf(path, sizeof(path) - 1, "%s/libpartclone.xfs.so", PLUGINDIR);
        break;
    case LIBPARTCLONE_EXFAT:
        snprintf(path, sizeof(path) - 1, "%s/libpartclone.exfat.so", PLUGINDIR);
        break;
    case LIBPARTCLONE_NTFS:
        snprintf(path, sizeof(path) - 1, "%s/libpartclone.ntfs.so", PLUGINDIR);
        break;
    case LIBPARTCLONE_EXTFS:
        snprintf(path, sizeof(path) - 1, "%s/libpartclone.extfs.so", PLUGINDIR);
        break;
    default:
    case LIBPARTCLONE_UNKNOWN:
        snprintf(path, sizeof(path) - 1, "%s/libpartclone.dd.so", PLUGINDIR);
        break;
    }
    dp = dlopen(path, RTLD_NOW);
    if (!dp) {
        ret = -1;
        printf("ERROR: %s\n", dlerror());
        goto cleanup;
    }

    fptr_libpartclone_main libpartclone_main =
        (fptr_libpartclone_main)dlsym(dp, "libpartclone_main");
    err = dlerror();
    if (err) {
        ret = -1;
        printf("ERROR: %s\n", err);
        goto cleanup;
    }

    argc = 7;
    argv = malloc((argc + 1) * sizeof(char*));
    if (!argv) {
        ret = -1;
        goto cleanup;
    }
    argv[0] = strdup("partClone");
    argv[1] = strdup("-d");
    if (strlen(dst) > 4 && dst[0] == '/' && dst[1] == 'd' && dst[2] == 'e' && 
        dst[3] == 'v') {
        argv[2] = strdup("-b");
    } else {
        argv[2] = strdup("-c");
    }
    argv[3] = strdup("-s");
    argv[4] = strdup(src);
    if (overwrite == 1)
        argv[5] = strdup("-O");
    else
        argv[5] = strdup("-o");
    argv[6] = strdup(dst);
    argv[7] = NULL;

    libpartclone_main(argc, argv, callback, error, arg);

cleanup:
    if (dp) {
        dlclose(dp);
        dp = NULL;
    }
    if (argc > 0 && argv != NULL) {
        for (int i = 0;i < argc; i++) {
            if (argv[i]) {
                free(argv[i]);
                argv[i] = NULL;
            }
        }
        free(argv);
        argv = NULL;
        argc = 0;
    }

    return ret;
}

int partRestore(partType type,
                const char *img,
                const char *part,
                callback_routine fptr,
                void *arg)
{
    void *dp = NULL;
    char *err = NULL;
    int  argc = 0;
    char **argv = NULL;
    char *soStr = NULL;
    char *path  = NULL;
    if (img == NULL || part == NULL) {
        printf("ERROR: parm error!\n");
        goto cleanup;
    }
    switch (type) {
    default:
        soStr = "libpartclone.dd.so";
        break;
    case LIBPARTCLONE_FAT:
        soStr = "libpartclone.fat.so";
        break;
    case LIBPARTCLONE_BTRFS:
        soStr = "libpartclone.btrfs.so";
        break;
    case LIBPARTCLONE_F2FS:
        soStr = "libpartclone.f2fs.so";
        break;
    case LIBPARTCLONE_HFSP:
        soStr = "libpartclone.hfsp.so";
        break;
    case LIBPARTCLONE_MINIX:

        soStr = "libpartclone.minix.so";
        break;
    case LIBPARTCLONE_XFS:

        soStr = "libpartclone.xfs.so";
        break;
    case LIBPARTCLONE_EXFAT:
        soStr = "libpartclone.exfat.so";
        break;
    case LIBPARTCLONE_UNKNOWN:
        soStr = "libpartclone.dd.so";
        break;

    case LIBPARTCLONE_NTFS:
        soStr = "libpartclone.ntfs.so";
        break;
    case LIBPARTCLONE_EXTFS:
        soStr = "libpartclone.extfs.so";
        break;
    }
    int  len = strlen(soStr) + strlen(PLUGINDIR) + 8;
    path = malloc( len * sizeof(char *));
    if (path == NULL)
        goto cleanup;
    memset(path,0,len);
    snprintf(path,len,"%s/%s",PLUGINDIR,soStr);
    dp = dlopen(path, RTLD_NOW);
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

    // command[./test-libpartclone-extfs -d -r -s /home/test/gits/test/sda7.img -o /dev/sda7]
    // => argc argv
    argc = 7;
    argv = malloc((argc+1) * sizeof(char*));
    argv[0] = strdup("partClone");
    argv[1] = strdup("-d");
    argv[2] = strdup("-r");
    argv[3] = strdup("-s");
    argv[4] = strdup(img);
    argv[5] = strdup("-o");
    argv[6] = strdup(part);
    argv[7] = NULL;

    for (int i = 0;i < argc; i++) {
        printf("argv[%s]\n",argv[i]);
    }

    libpartclone_main(argc, argv, fptr, NULL, NULL);

cleanup:
    if (dp) {
        dlclose(dp);
        dp = NULL;
    }
    if (argc > 0 && argv != NULL) {
        for (int i = 0;i < argc; i++) {
            if (argv[1]) {
                free(argv[i]);
                argv[i] = NULL;
            }
        }
        free(argv);
        argv = NULL;
        argc = 0;
    }
    if (path) {
        free(path);
        path = NULL;
    }

    return 0;
}

int partInfo(const char *img, partInfo_t *info)
{
    void *dp = NULL;
    char *err = NULL;
    int argc = 0;
    char **argv = NULL;

    if (!img || !info)
        goto cleanup;

    dp = dlopen(PLUGINDIR "/libpartclone.info.so", RTLD_NOW);
    if (!dp) {
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

    argc = 3;
    argv = malloc((argc + 1) * sizeof(char*));
    argv[0] = strdup("partClone");
    argv[1] = strdup("-s");
    argv[2] = strdup(img);
    argv[3] = NULL;

    libpartclone_main(argc, argv, NULL, NULL, (void *)info);

cleanup:
    if (dp) {
        dlclose(dp);
        dp = NULL;
    }
    if (argc > 0 && argv != NULL) {
        for (int i = 0; i < argc; i++) {
            if (argv[i]) {
                free(argv[i]);
                argv[i] = NULL;
            }
        }
        free(argv);
        argv = NULL;
        argc = 0;
    }

    return 0;
}

int partCloneCancel(int cancel)
{
    g_cancel_clone = cancel;
    return 0;
}
