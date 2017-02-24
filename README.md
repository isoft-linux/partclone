#libpartclone

C/C++ wrapper for partclone.


## Build && Install

```
git checkout libpartclone

libtoolize --force --copy
aclocal -I m4
autoconf
autoheader
automake --add-missing
./configure --prefix=/usr \
    --disable-static \
    --enable-extfs \
    --disable-reiserfs \
    --enable-fat \
    --enable-hfsp \
    --enable-btrfs \
    --enable-ncursesw \
    --enable-ntfs \
    --enable-exfat \
    --enable-f2fs \
    --enable-minix \
    --disable-nilfs2 \
    --enable-xfs

make clean
make -j4
sudo make install
```


## Before git commit

```
scan-build -k -v ./configure --prefix=/usr \
    --disable-static \
    --enable-extfs \
    --disable-reiserfs \
    --enable-fat \
    --enable-hfsp \
    --enable-btrfs \
    --enable-ncursesw \
    --enable-ntfs \
    --enable-exfat \
    --enable-f2fs \
    --enable-minix \
    --disable-nilfs2 \
    --enable-xfs
    
make clean
scan-build -k -v -V make -j4
```

NO bug report then git commit please! but ignore clang analyzer 
[False Positive](https://clang-analyzer.llvm.org/faq.html).
