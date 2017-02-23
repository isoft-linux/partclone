#libpartclone

C/C++ wrapper for partclone


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
