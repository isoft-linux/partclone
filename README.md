libpartclone
------------

C/C++ wrapper for partclone.


## Architecture for libpartclone

```
.
├── docs <-- TODO: libpartclone API doc.
├── fail-mbr
├── HACKING <-- TODO: code review by analyzer and sanitizer
├── lib <-- TODO: C/C++ wrapper
│   ├── partclone.c
│   └── partclone.h
├── partclone-0.3.5.pc.in <-- TODO: pkgconfig
├── src <-- TODO: plugin - change exit to return
│   ├── bitmap.h
│   ├── btrfs
│   ├── btrfsclone.c
│   ├── btrfsclone.h
│   ├── checksum.c
│   ├── checksum.h
│   ├── ddclone.c
│   ├── ddclone.h
│   ├── deplib_version.c
│   ├── exfat
│   ├── exfatclone.h
│   ├── extfsclone.c
│   ├── extfsclone.h
│   ├── f2fs
│   ├── f2fsclone.c
│   ├── f2fsclone.h
│   ├── fatclone.c
│   ├── fatclone.h
│   ├── fs_common.h
│   ├── fstype.c
│   ├── fuseimg.c
│   ├── gettext.h
│   ├── hfsplusclone.c
│   ├── hfsplusclone.h
│   ├── info.c
│   ├── jfsclone.c
│   ├── jfsclone.h
│   ├── main.c <-- TODO: libpartclone_main
│   ├── minixclone.c
│   ├── minixclone.h
│   ├── nilfsclone.c
│   ├── nilfsclone.h
│   ├── ntfsclone-ng.c
│   ├── ntfsclone-ng.h
│   ├── ntfsfixboot.c
│   ├── partclone.c
│   ├── partclone.h
│   ├── progress.c
│   ├── progress.h
│   ├── readblock.c
│   ├── reiser4clone.c
│   ├── reiser4clone.h
│   ├── reiserfsclone.c
│   ├── reiserfsclone.h
│   ├── ufs
│   ├── ufsclone.c
│   ├── ufsclone.h
│   ├── version.h
│   ├── vmfs5clone.c
│   ├── vmfsclone.c
│   ├── vmfsclone.h
│   ├── xfs
│   ├── xfsclone.c
│   └── xfsclone.h
├── tests <-- TODO: a lot of testcases
│   ├── clang-analyzer.sh <-- TODO: clang analyzer for Preprocessed file
```

## Build && Install

Please read [INSTALL](https://github.com/isoft-linux/partclone/blob/libpartclone/INSTALL)

### Architecture for library and header

```
├── /usr/lib/libpartclone-0.3.5 <-- TODO: plugin
│   ├── libpartclone.block.so
│   ├── libpartclone.btrfs.so
│   ├── libpartclone.chkimg.so
│   ├── libpartclone.dd.so
│   ├── libpartclone.exfat.so
│   ├── libpartclone.extfs.so
│   ├── libpartclone.f2fs.so
│   ├── libpartclone.fat.so
│   ├── libpartclone.hfsp.so
│   ├── libpartclone.imager.so
│   ├── libpartclone.imgfuse.so
│   ├── libpartclone.info.so
│   ├── libpartclone.minix.so
│   ├── libpartclone.ntfsfixboot.so
│   ├── libpartclone.ntfs.so
│   ├── libpartclone.restore.so
│   └── libpartclone.xfs.so
├── /usr/lib/libpartclone.so <-- TODO: C/C++ wrapper
├── /usr/lib/pkgconfig/partclone-0.3.5.pc <-- TODO: C/C++ wrapper
├── /usr/include/partclone-0.3.5
│   └── partclone.h <-- TODO: C/C++ wrapper
```


## Code review before Git push

Please read [HACKING](https://github.com/isoft-linux/partclone/blob/libpartclone/HACKING) 
for clang (static) analyzer and (dynamic) sanitizer before Git push, but maunally ignore
[False Positive](https://clang-analyzer.llvm.org/faq.html).
