/**
 * The part of partclone 
 *
 * Copyright (c) 2007~ Thomas Tsai <thomas at nchc org tw>
 *
 * The utility to print out the Image information. 
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 */

#include <config.h>
#include <features.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <malloc.h>
#include <stdarg.h>
#include <string.h>

#include "libpartclone.h"
#include "partclone.h"

/// cmd_opt structure defined in partclone.h
cmd_opt opt;

void info_usage(void) {
	fprintf(stderr, "partclone v%s http://partclone.org\n"
	                "Usage: partclone.info [FILE]\n"
	                "Or: partclone.info [OPTIONS]\n"
	                "\n"
		"    -s,  --source FILE      Source FILE, or stdin(-)\n"
		"    -L,  --logfile FILE     Log FILE\n"
		"    -dX, --debug=X          Set the debug level to X = [0|1|2]\n"
		"    -q,  --quiet            Disable progress message\n"
		"    -v,  --version          Display partclone version\n"
		"    -h,  --help             Display this help\n"
		, VERSION);
	return;
}


void info_options (int argc, char **argv){

    static const char *sopt = "-hvqd::L:s:";
    static const struct option lopt[] = {
	{ "help",	no_argument,	    NULL,   'h' },
	{ "print_version",  no_argument,	NULL,   'v' },
	{ "source",	required_argument,  NULL,   's' },
	{ "debug",	optional_argument,  NULL,   'd' },
	{ "logfile",	    required_argument,	NULL,   'L' },
	{ "quiet",              no_argument,            NULL,   'q' },
	{ NULL,			0,			NULL,    0  }
    };
	int c;
	memset(&opt, 0, sizeof(cmd_opt));
	opt.debug = 0;
	opt.quiet = 0;
	opt.info  = 1;
	opt.logfile = "/tmp/partclone.log";
	opt.target  = 0;
	opt.clone   = 0;
	opt.restore = 0;
	opt.info = 1;	
    optind = 0;
    optarg = NULL;
    while ((c = getopt_long(argc, argv, sopt, lopt, NULL)) != -1) {
	switch (c) {
	    case 'h':
	    case '?':
		info_usage();
		break;
	    case 'v':
		print_version();
		break;
	    case 's':
		opt.source = optarg;
		break;
	    case 'q':
		opt.quiet = 1;
		break;
	    case 'd':
		if (optarg)
		    opt.debug = atol(optarg);
		else
		    opt.debug = 1;
		break;
	    case 'L':
		opt.logfile = optarg;
		break;
	    default:
		fprintf(stderr, "Unknown option '%s'.\n", argv[optind-1]);
		info_usage();
	}
    }

    if ( opt.source == 0 )
        info_usage();

}

/**
 * main functiom - print Image file metadata.
 */
#ifdef LIBPARTCLONE
int libpartclone_main(int argc,
                      char **argv,
                      callback_routine callback,
                      error_routine error,
                      void *arg)
{
#else
int main(int argc, char **argv) 
{
#endif
	int dfr;                  /// file descriptor for source and target
	unsigned long   *bitmap;  /// the point for bitmap data
	image_head_v2    img_head;
	file_system_info fs_info;
	image_options    img_opt;

    if (argc == 2){
	memset(&opt, 0, sizeof(cmd_opt));
	opt.source  = argv[1];
	opt.logfile = "/tmp/partclone.log";
	dfr = open(opt.source, O_RDONLY);
	if (dfr == -1)
	    info_options(argc, argv);
    } else
	info_options(argc, argv);
    open_log(opt.logfile);

    /// print partclone info
    print_partclone_info(opt);

    /**
     * open Image file
     */
    if (opt.source && strcmp(opt.source, "-") == 0) {
        if ((dfr = fileno(stdin)) == -1) {
	    log_mesg(0, 1, 1, opt.debug, "info: open %s(stdin) error\n", opt.source);
            return -1;
        }
    } else {
	dfr = open(opt.source, O_RDONLY);
        if (dfr == -1) {
	    log_mesg(0, 1, 1, opt.debug, "info: Can't open file(%s)\n", opt.source);
            return -1;
        }
    }

    /// get image information from image file
    if (load_image_desc(&dfr, &opt, &img_head, &fs_info, &img_opt) != 0) {
        return -1;
    }
    /// alloc a memory to restore bitmap
    bitmap = pc_alloc_bitmap(fs_info.totalblock);
    if (bitmap == NULL) {
        log_mesg(0, 1, 1, opt.debug, "%s, %i, not enough memory\n", __func__, __LINE__);
        return -1;
    }

    log_mesg(0, 0, 0, opt.debug, "initial main bitmap pointer %p\n", bitmap);
    log_mesg(0, 0, 0, opt.debug, "Initial image hdr: read bitmap table\n");

    /// read and check bitmap from image file
    load_image_bitmap(&dfr, opt, fs_info, img_opt, bitmap);

    log_mesg(0, 0, 0, opt.debug, "check main bitmap pointer %p\n", bitmap);
    log_mesg(0, 0, 0, opt.debug, "print image information\n");

    print_file_system_info(fs_info, opt);
    log_mesg(0, 0, 1, opt.debug, "\n");
    print_image_info(img_head, img_opt, opt);

#ifdef LIBPARTCLONE
    partInfo_t *pinfo = (partInfo_t *)arg;

    unsigned int     block_s = fs_info.block_size;
    unsigned long long total = fs_info.totalblock;
    unsigned long long used  = fs_info.usedblocks;
    if (!arg)
        goto cleanup;

    pinfo->total = total;   /* I need it for precise comparison! */
    pinfo->used = used;
    snprintf(pinfo->type, sizeof(pinfo->type) - 1, "%s", fs_info.fs);
    pinfo->devSize = total * block_s;
    pinfo->usedSize = used * block_s;
    char fs[FS_MAGIC_SIZE+1] = "";
    snprintf(fs, sizeof(fs), "%s", fs_info.fs);
    if (strncmp(fs,xfs_MAGIC,strlen(xfs_MAGIC)) == 0) {
        pinfo->newType = LIBPARTCLONE_XFS;
    } else if (strncmp(fs,extfs_MAGIC,strlen(extfs_MAGIC)) == 0) {
        pinfo->newType = LIBPARTCLONE_EXTFS;
    } else if (strncmp(fs,ext2_MAGIC,strlen(ext2_MAGIC)) == 0) {
        pinfo->newType = LIBPARTCLONE_EXTFS;
    } else if (strncmp(fs,ext3_MAGIC,strlen(ext3_MAGIC)) == 0) {
        pinfo->newType = LIBPARTCLONE_EXTFS;
    } else if (strncmp(fs,ext4_MAGIC,strlen(ext4_MAGIC)) == 0) {
        pinfo->newType = LIBPARTCLONE_EXTFS;
    } else if (strncmp(fs,hfsplus_MAGIC,strlen(hfsplus_MAGIC)) == 0) {
        pinfo->newType = LIBPARTCLONE_HFSP;
    } else if (strncmp(fs,fat_MAGIC,strlen(fat_MAGIC)) == 0) {
        pinfo->newType = LIBPARTCLONE_FAT;
    } else if (strncmp(fs,exfat_MAGIC,strlen(exfat_MAGIC)) == 0) {
        pinfo->newType = LIBPARTCLONE_EXFAT;
    } else if (strncmp(fs,ntfs_MAGIC,strlen(ntfs_MAGIC)) == 0) {
        pinfo->newType = LIBPARTCLONE_NTFS;
    } else if (strncmp(fs,minix_MAGIC,strlen(minix_MAGIC)) == 0) {
        pinfo->newType = LIBPARTCLONE_MINIX;
    } else if (strncmp(fs,btrfs_MAGIC,strlen(btrfs_MAGIC)) == 0) {
        pinfo->newType = LIBPARTCLONE_BTRFS;
    } else if (strncmp(fs,f2fs_MAGIC,strlen(f2fs_MAGIC)) == 0) {
        pinfo->newType = LIBPARTCLONE_F2FS;
    } else {
        pinfo->newType = LIBPARTCLONE_UNKNOWN;
    }
cleanup:
#endif
    close(dfr);     /// close source
    free(bitmap);   /// free bitmap
    close_log();
    return 0;       /// finish
}
