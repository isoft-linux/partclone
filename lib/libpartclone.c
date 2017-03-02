/**
 * Copyright (c) 2017 Leslie Zhai <xiang.zhai@i-soft.com.cn>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 */

#include <dlfcn.h>
#include <stdio.h>

#include "libpartclone.h"

int g_cancel_clone = 0 ;

typedef int (*fptr_libpartclone_main)(int argc,
                                      char **argv,
                                      callback_routine fptr,
                                      void *arg);

int partClone(partType type,
              char *part,
              char *img,
              int  overwite,
              callback_routine fptr,
              void *arg)
{
    void *dp = NULL;
    char *err = NULL;
    int argc = 0;
    char **argv = NULL;
    switch (type) {
    default:
        break;
    case LIBPARTCLONE_FAT:
        dp = dlopen(PLUGINDIR "/libpartclone.fat.so", RTLD_NOW);
        if (dp == NULL) {
            printf("ERROR: %s\n", dlerror());
            goto cleanup;
        }
        break;
    case LIBPARTCLONE_BTRFS:
        dp = dlopen(PLUGINDIR "/libpartclone.btrfs.so", RTLD_NOW);
        if (dp == NULL) {
            printf("ERROR: %s\n", dlerror());
            goto cleanup;
        }
        break;
    case LIBPARTCLONE_F2FS:
        dp = dlopen(PLUGINDIR "/libpartclone.f2fs.so", RTLD_NOW);
        if (dp == NULL) {
            printf("ERROR: %s\n", dlerror());
            goto cleanup;
        }
        break;
    case LIBPARTCLONE_HFSP:
        dp = dlopen(PLUGINDIR "/libpartclone.hfsp.so", RTLD_NOW);
        if (dp == NULL) {
            printf("ERROR: %s\n", dlerror());
            goto cleanup;
        }
        break;
    case LIBPARTCLONE_MINIX:
        dp = dlopen(PLUGINDIR "/libpartclone.minix.so", RTLD_NOW);
        if (dp == NULL) {
            printf("ERROR: %s\n", dlerror());
            goto cleanup;
        }
        break;
    case LIBPARTCLONE_XFS:
        dp = dlopen(PLUGINDIR "/libpartclone.xfs.so", RTLD_NOW);
        if (dp == NULL) {
            printf("ERROR: %s\n", dlerror());
            goto cleanup;
        }
        break;
    case LIBPARTCLONE_EXFAT:
        dp = dlopen(PLUGINDIR "/libpartclone.exfat.so", RTLD_NOW);
        if (dp == NULL) {
            printf("ERROR: %s\n", dlerror());
            goto cleanup;
        }
        break;
    case LIBPARTCLONE_UNKNOWN:
        dp = dlopen(PLUGINDIR "/libpartclone.dd.so", RTLD_NOW);
        if (dp == NULL) {
            printf("ERROR: %s\n", dlerror());
            goto cleanup;
        }
        break;

    case LIBPARTCLONE_NTFS:
        dp = dlopen(PLUGINDIR "/libpartclone.ntfs.so", RTLD_NOW);
        if (dp == NULL) {
            printf("ERROR: %s\n", dlerror());
            goto cleanup;
        }
        break;
    case LIBPARTCLONE_EXTFS:
        dp = dlopen(PLUGINDIR "/libpartclone.extfs.so", RTLD_NOW);
        if (dp == NULL) {
            printf("ERROR: %s\n", dlerror());
            goto cleanup;
        }
        break;
    }

    fptr_libpartclone_main libpartclone_main =
        (fptr_libpartclone_main)dlsym(dp, "libpartclone_main");
    err = dlerror();
    if (err) {
        printf("ERROR: %s\n", err);
        goto cleanup;
    }

    // command[./test-libpartclone-extfs -d -c -s /dev/sda7 -o /home/test/gits/test/sda7.img]
    // => argc argv
    argc = 7;
    argv = malloc((argc+1) * sizeof(char*));
    argv[0] = strdup("partClone");
    argv[1] = strdup("-d");
    argv[2] = strdup("-c");
    argv[3] = strdup("-s");
    argv[4] = strdup(part);
    if (overwite == 1)
        argv[5] = strdup("-O");
    else
        argv[5] = strdup("-o");
    argv[6] = strdup(img);
    argv[7] = NULL;

    for (int i = 0;i < argc; i++) {
        printf("argv[%s]\n",argv[i]);
    }

    libpartclone_main(argc, argv, fptr, NULL);

cleanup:
    if (dp) {
        dlclose(dp);
        dp = NULL;
    }
    if (argc > 0 && argv != NULL) {
        for (int i = 0;i < argc; i++) {
            free(argv[i]);
            argv[i] = NULL;
        }
        free(argv);
        argv = NULL;
        argc = 0;
    }

    printf("DEBUG: %s, %s, line %d: Bye ;-)\n",
            __FILE__, __func__, __LINE__);

    return 0;
}

int partRestore(partType type,
                char *img,
                char *part,
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

    libpartclone_main(argc, argv, fptr, NULL);

cleanup:
    if (dp) {
        dlclose(dp);
        dp = NULL;
    }
    if (argc > 0 && argv != NULL) {
        for (int i = 0;i < argc; i++) {
            free(argv[i]);
            argv[i] = NULL;
        }
        free(argv);
        argv = NULL;
        argc = 0;
    }
    if (path) {
        free(path);
        path = NULL;
    }

    printf("DEBUG: %s, %s, line %d:restore done!\n",
            __FILE__, __func__, __LINE__);
    return 0;
}

int partInfo(char *img, partInfo_t *info)
{
    void *dp = NULL;
    char *err = NULL;
    int argc = 0;
    char **argv = NULL;
    if (img == NULL) {
        printf("ERROR: source image is null!\n");
        goto cleanup;
    }

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

    // command[./test-libpartclone-info -s /home/test/gits/test/sda7.img]
    // => argc argv
    argc = 3;
    argv = malloc((argc+1) * sizeof(char*));
    argv[0] = strdup("partClone");
    argv[1] = strdup("-s");
    argv[2] = strdup(img);
    argv[3] = NULL;

    for (int i = 0;i < argc; i++) {
        printf("argv[%s]\n",argv[i]);
    }

    libpartclone_main(argc, argv, NULL,(void *)info);

cleanup:
    if (dp) {
        dlclose(dp);
        dp = NULL;
    }
    if (argc > 0 && argv != NULL) {
        for (int i = 0;i < argc; i++) {
            free(argv[i]);
            argv[i] = NULL;
        }
        free(argv);
        argv = NULL;
        argc = 0;
    }

    printf("DEBUG: %s, %s, line %d: Bye ;-)\n",
            __FILE__, __func__, __LINE__);

    return 0;
}
int partCloneCancel(int cancel)
{
    g_cancel_clone = cancel;
    return 0;
}
