/**
 * Copyright (c) 2017 Leslie Zhai <xiang.zhai@i-soft.com.cn>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 */

#include <dlfcn.h>

#include "libpartclone.h"

int partClone(partType type, 
              char *part, 
              char *img, 
              callback_routine fptr, 
              void *arg) 
{
    return 0;
}

int partRestore(partType type, 
                char *img, 
                char *part, 
                callback_routine fptr, 
                void *arg) 
{
    return 0;
}

int partInfo(char *img, void *info) 
{
    return 0;
}
