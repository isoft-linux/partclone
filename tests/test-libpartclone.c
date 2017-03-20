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

#include <pthread.h>

/*******dd progress begin**********/
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/param.h>
#include <sys/time.h>
#include <dirent.h>
#include <inttypes.h>
#include <fcntl.h>
#include <sys/ioctl.h>
# include <linux/fs.h>
#include <libgen.h>
#define PROC_PATH       "/proc"
#define MAX_PIDS        32
#define MAX_RESULTS     32
#define MAX_FD_PER_PID  512
#define LINE_LEN        256

#define PM_NONE         0
#define PM_READ         1   // read only
#define PM_WRITE        2   // write only
#define PM_READWRITE    4

typedef struct fdinfo_t {
    int num;
    off_t size;
    off_t pos;
    char mode;
    char name[MAXPATHLEN + 1];
    struct timeval tv;
} fdinfo_t;

typedef struct pidinfo_t {
    pid_t pid;
    char name[MAXPATHLEN + 1];
} pidinfo_t;
typedef struct result_t {
    pidinfo_t pid;
    fdinfo_t fd;
} result_t;


#define DIM(x) (sizeof(x)/sizeof(*(x)))

static const char     *sizes[]   = { "EiB", "PiB", "TiB", "GiB", "MiB", "KiB", "B" };
static const uint64_t  exbibytes = 1024ULL * 1024ULL * 1024ULL *
                                   1024ULL * 1024ULL * 1024ULL;
/*******dd progress end**********/


void *thread_test_dd(void *arg);
void *thread_test(void *arg);
typedef struct {
    partType type;
    char *src;
    char *dst;
    int  overwrite;
    void *callback ;
}test_t;
static void *callback(void *arg) 
{
    float *ret = (float *)arg;
    //char *ss = (char *)arg;
    if ((int)*ret%50 == 1)
        printf("callback[%0.2f]\n", (float)*ret);

    //printf("callback[%s]\n", ss);
    return NULL;
}

/*******dd progress begin**********/
void format_size(uint64_t size, char *result)
{
    uint64_t multiplier;
    int i;

    multiplier = exbibytes;

    for (i = 0 ; i < DIM(sizes) ; i++, multiplier /= 1024) {
        if (size < multiplier)
            continue;
        if (size % multiplier == 0)
            sprintf(result, "%" PRIu64 " %s", size / multiplier, sizes[i]);
        else
            sprintf(result, "%.1f %s", (float) size / multiplier, sizes[i]);
        return;
    }

    strcpy(result, "0");
    return;
}


char is_numeric(char *str)
{
    while (*str) {
        if(!isdigit(*str))
            return 0;
        str++;
    }
    return 1;
}

int find_fd_for_pid(const char *bin_name,int *fd_list, int max_fd,pidinfo_t *pidinfo)
{
    DIR *proc;
    struct dirent *direntp;
    struct stat stat_buf;
    char fullpath_dir[MAXPATHLEN + 1];
    char fullpath_exe[MAXPATHLEN + 1];
    char exe[MAXPATHLEN + 1];
    int pid_count=0;
    pid_t pid = 0;
    char link_dest[MAXPATHLEN + 1];
    int count = 0;
    ssize_t len;

    proc=opendir(PROC_PATH);
    if (!proc) {
        printf("opendir");
        printf(stderr,"Can't open %s\n",PROC_PATH);
        return -1;
    }

    while ((direntp = readdir(proc)) != NULL) {
        snprintf(fullpath_dir, MAXPATHLEN, "%s/%s", PROC_PATH, direntp->d_name);
        if (stat(fullpath_dir, &stat_buf) == -1) {
            continue;
        }

        if ((S_ISDIR(stat_buf.st_mode) && is_numeric(direntp->d_name))) {
            snprintf(fullpath_exe, MAXPATHLEN, "%s/exe", fullpath_dir);
            len=readlink(fullpath_exe, exe, MAXPATHLEN);
            if (len != -1)
                exe[len] = 0;
            else {
                // Will be mostly "Permission denied"
                continue;
            }
            char *p = basename(exe);
            if (p==NULL)
                continue;

            if (!strcmp(basename(exe), bin_name)) {
                pid = atol(direntp->d_name);
                pid_count++;
                if(pid_count > 1)
                    break;
            }
        }
    }

    closedir(proc);
    proc = NULL;

    if (pid_count < 1 ) {
        return -1;
    }

    snprintf(fullpath_dir, MAXPATHLEN, "%s/%d/fd", PROC_PATH, pid);

    proc = opendir(fullpath_dir);
    if (!proc) {
        printf("opendir");
        printf(stderr,"Can't open %s\n",fullpath_dir);
        return 0;
    }

    pidinfo->pid = pid;
    snprintf(pidinfo->name,MAXPATHLEN,"%s",bin_name);

    while ((direntp = readdir(proc)) != NULL) {
        snprintf(fullpath_exe, MAXPATHLEN, "%s/%s", fullpath_dir, direntp->d_name);
        if (stat(fullpath_exe, &stat_buf) == -1) {
            continue;
        }

        // if not a regular file or a block device
        if(!S_ISREG(stat_buf.st_mode) && !S_ISBLK(stat_buf.st_mode))
            continue;

        // try to read link ...
        len = readlink(fullpath_exe, link_dest, MAXPATHLEN);
        if (len != -1)
            link_dest[len] = 0;
        else
            continue;

        // try to stat link target (invalid link ?)
        if (stat(link_dest, &stat_buf) == -1)
            continue;

        // OK, we've found a potential interesting file.

        fd_list[count++] = atoi(direntp->d_name);
        //~ printf("[debug] %s\n",fullpath_exe);
        if (count == max_fd)
            break;
    }

    closedir(proc);
    return count;
}

int get_fdinfo(pid_t pid, int fdnum, fdinfo_t *fd_info)
{
    struct stat stat_buf;
    char fdpath[MAXPATHLEN + 1];
    char line[LINE_LEN];
    FILE *fp;
    int flags;
    struct timezone tz;

    fd_info->num = fdnum;
    fd_info->mode = PM_NONE;

    ssize_t len;
    snprintf(fdpath, MAXPATHLEN, "%s/%d/fd/%d", PROC_PATH, pid, fdnum);

    len=readlink(fdpath, fd_info->name, MAXPATHLEN);
    if (len != -1)
        fd_info->name[len] = 0;
    else {
        //~ nperror("readlink");
        return 0;
    }

    if (stat(fd_info->name, &stat_buf) == -1) {
        //~ printf("[debug] %i - %s\n",pid,fd_info->name);
        return 0;
    }

    if (S_ISBLK(stat_buf.st_mode)) {
        int fd;
        fd = open(fd_info->name, O_RDONLY);
        if (fd < 0) {
            return 0;
        }
        if (ioctl(fd, BLKGETSIZE64, &fd_info->size) < 0) {
            close(fd);
            return 0;
        }
        close(fd);
    } else {
        fd_info->size = stat_buf.st_size;
    }

    flags = 0;
    fd_info->pos = 0;
    snprintf(fdpath, MAXPATHLEN, "%s/%d/fdinfo/%d", PROC_PATH, pid, fdnum);
    fp = fopen(fdpath, "rt");
    gettimeofday(&fd_info->tv, &tz);
    if (!fp) {
        return 0;
    }
    while (fgets(line, LINE_LEN - 1, fp) != NULL) {
        if (!strncmp(line, "pos:", 4))
            fd_info->pos = atoll(line + 5);
        if (!strncmp(line, "flags:", 6))
            flags = atoll(line + 7);
    }
    if ((flags & O_ACCMODE) == O_RDONLY)
        fd_info->mode = PM_READ;
    if ((flags & O_ACCMODE) == O_WRONLY)
        fd_info->mode = PM_WRITE;
    if ((flags & O_ACCMODE) == O_RDWR)
        fd_info->mode = PM_READWRITE;
    fclose(fp);
    return 1;
}

int monitor_processes(const char *cmd)
{
    int pid_count=0 ,fd_count=0, result_count=0;
    int i,j;
    pidinfo_t pidinfo_list[1];
    fdinfo_t fdinfo;
    fdinfo_t biggest_fd;
    int fdnum_list[MAX_FD_PER_PID];
    off_t max_size;
    char fsize[64];
    char fpos[64];
    char ftroughput[64];
    float perc;
    signed char still_there;
    signed char search_all = 1;
    static signed char first_pass = 1;

    first_pass = 0;
    search_all = 0;
    pidinfo_t pidinfo;
    memset(&pidinfo,0,sizeof(pidinfo_t));
    fd_count = find_fd_for_pid(cmd,fdnum_list, MAX_FD_PER_PID,&pidinfo);

    max_size = 0;
    printf("\n fd_count[%d]\n",fd_count);
    if (fd_count < 1) {
        return -1;
    }
    for (j = 0 ; j < fd_count ; j++) {
        get_fdinfo(pidinfo.pid, fdnum_list[j], &fdinfo);
        if (fdinfo.size > max_size) {
            biggest_fd = fdinfo;
            max_size = fdinfo.size;
        }
    }

    if (!max_size) { // nothing found
        return -1;
    }
    format_size(biggest_fd.pos, fpos);
    format_size(biggest_fd.size, fsize);
    perc = ((double)100 / (double)biggest_fd.size) * (double)biggest_fd.pos;


    printf("[%5d] %s %s\n\t%.1f%% (%s / %s)",
        pidinfo.pid,
        pidinfo.name,
        biggest_fd.name,
        perc,
        fpos,
        fsize);

    printf("\n\n");

}
/*******dd progress end**********/

/*
 * test commands:
 *
 * clone:
 * ./test-libpartclone clone   /dev/sda7 /home/test/gits/test/sda7.img extf
 *
 * restore:
 * ./test-libpartclone restore /home/test/gits/test/sda7.img /dev/sda7 extf
 *
 * info:
 * ./test-libpartclone info /home/test/gits/test/sda7.img
 *
*/
int main(int argc, char *argv[]) 
{
    partType type = LIBPARTCLONE_UNKNOWN;
    const char *src = NULL;
    const char *dst = NULL;
    const char *fmt = NULL;
    if (argc < 3) {
        printf("command line:test-libpartclone clone(info|restore) src dst file_type(extfs|ntfs|...)\n");
        return 0;
    }
    if (strcmp(argv[1],"clone") == 0 || strcmp(argv[1],"restore") == 0) {
         if (argc >= 5){
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
                printf("DEBUG: %s, %s, line %d,no this type.test done!\n",
                       __FILE__, __func__, __LINE__);
                return 0;
            }

            src = argv[2];
            dst = argv[3];

            printf("DEBUG: %s, %s, line %d:clone [%s] to [%s],type[%s]\n",
                   __FILE__, __func__, __LINE__,
                   src,dst,fmt);
            if (strcmp(argv[1],"clone") == 0) {
                int overwrite = 0;
                if (argc >5) {
                    overwrite = (argv[5][0] == 'O') ? 1 : 0;
                }
#if 1
                partClone(type,
                      src,
                      dst,
                      overwrite,
                      callback,
                      NULL,
                      NULL);
#else
                pthread_t prog_thread;
                test_t tstr;// use local parm to test. use malloc finally.
                tstr.type = type;
                tstr.src = src;
                tstr.dst = dst;
                tstr.overwrite = overwrite;
                tstr.callback = callback;

                int ret = pthread_create(&prog_thread, NULL, thread_test, (void *)&tstr);
                printf("\ncall thread[%d]!\n",ret);

                sleep(10);

                printf("\n\n\ncancel clone...\n");

                partCloneCancel(1);

                sleep(10);
#endif
            } else if (strcmp(argv[1],"restore") == 0) {
                partRestore(type,
                      src,
                      dst,
                      callback,
                      NULL, 
                      NULL);
            }
        } else {
             printf("command line:test-libpartclone clone(info|restore) src dst file_type(extfs|ntfs|...)\n");
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
    } else if(strcmp(argv[1],"dd") == 0) {

        // test-libpartclone  dd 1 1 1 1 1
        pthread_t prog_thread;
        test_t tstr;// use local parm to test. use malloc finally.
        tstr.type = type;
        tstr.src = "/dev/sda7";
        tstr.dst = "/home/test/tmp/test.img";

        int ret = pthread_create(&prog_thread, NULL, thread_test_dd, (void *)&tstr);
        printf("\ncall thread[%d]!\n",ret);

        sleep(2);
        for(int i = 0;i<20;i++) {
            monitor_processes("dd");
            sleep(1);
        }

        printf("\n\n\ntest over,alt +c!!!!\n");

        sleep(15);

    } else {
        printf("command line:test-libpartclone clone(info|restore) src dst file_type(extfs|ntfs|...)\n");
    }

    return 0;
}

void *thread_test(void *arg)
{
    printf("\nin thread!\n");

    test_t *p = (test_t *)arg;
    partClone(p->type,
          p->src,
          p->dst,
          p->overwrite,
          p->callback,
          NULL,
          NULL);

    pthread_detach(pthread_self());
}

void *thread_test_dd(void *arg)
{
    char cmd[1024]="";
    test_t *p = (test_t *)arg;
    snprintf(cmd,sizeof(cmd),"dd if=%s of=%s ",p->src,p->dst);
    printf("\nin thread,[%s]\n",cmd);
    system(cmd);

    pthread_detach(pthread_self());
}
