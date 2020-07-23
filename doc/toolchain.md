# Toolchain Setup
This will briefly describe the steps needed to get going on various
types of systems.

## Arch Linux
The build-related tools are acquired through the following packages:
```
pacman -Syu base-devel arm-none-eabi-binutils arm-none-eabi-gcc arm-none-eabi-gdb arm-none-eabi-newlib
```

OpenOCD must be built from source however. This can be done via the AUR
package `openocd-git`. Either use a AUR helper like `yay` or acquire the
PKGBUILD and build it manually:

### AUR Helper example using yay:
```
yay -S openocd-git
```

### Manual build:
```
username@hostname:~/Projects
➜ curl -O
https://aur.archlinux.org/cgit/aur.git/snapshot/openocd-git.tar.gz
  % Total    % Received % Xferd  Average Speed   Time    Time     Time      Current
                                 Dload  Upload   Total   Spent    Left      Speed
100  1662    0  1662    0     0   2085      0 --:--:-- --:--:-- --:--:--    2082
username@hostname:~/Projects
➜ tar zxvf openocd-git.tar.gz
openocd-git/
openocd-git/.SRCINFO
openocd-git/.gitignore
openocd-git/PKGBUILD
username@hostname:~/Projects
➜ cd openocd-git
username@hostname:openocd-git on  master [!?]
➜ makepkg
==> Making package: openocd-git 0.10.0.r1089.g3bfe49266-1 (Mon 04 May 2020 09:38:58 AM PDT)
==> Checking runtime dependencies...
==> Checking buildtime dependencies...
==> Retrieving sources...
  -> Cloning openocd-git git repo...
Cloning into bare repository
'/home/username/Projects/openocd-git/openocd-git'...
remote: Counting objects: 144297, done.
remote: Compressing objects: 100% (163/163), done.
remote: Total 144297 (delta 86), reused 84 (delta 49)
Receiving objects: 100% (144297/144297), 36.54 MiB | 11.55 MiB/s, done.
Resolving deltas: 100% (122388/122388), done.
==> Validating source files with md5sums...
    openocd-git ... Skipped
==> Validating source files with sha1sums...
    openocd-git ... Skipped
==> Extracting sources...
  -> Creating working copy of openocd-git git repo...
Cloning into 'openocd-git'...
done.
==> Starting prepare()...
==> Starting pkgver()...
==> Updated version: openocd-git 0.10.0.r1213.g968d3851e-1
==> Starting build()...
+ aclocal
+ libtoolize --automake --copy
+ autoconf
+ autoheader
+ automake --gnu --add-missing --copy
Makefile.am:46: warning: wildcard $(srcdir: non-POSIX variable name
Makefile.am:46: (probably a GNU make extension)
Makefile.am: installing './INSTALL'
Makefile.am:23: installing './mdate-sh'
Makefile.am:23: installing './texinfo.tex'
Setting up submodules
Submodule 'jimtcl' (https://repo.or.cz/jimtcl.git) registered for path
'jimtcl'
Submodule 'src/jtag/drivers/libjaylink'
(https://repo.or.cz/libjaylink.git) registered for path
'src/jtag/drivers/libjaylink'
Submodule 'tools/git2cl' (https://repo.or.cz/git2cl.git) registered for
path 'tools/git2cl'
Cloning into
'/home/username/Projects/openocd-git/src/openocd-git/jimtcl'...
Cloning into
'/home/username/Projects/openocd-git/src/openocd-git/src/jtag/drivers/libjaylink'...
Cloning into
'/home/username/Projects/openocd-git/src/openocd-git/tools/git2cl'...
Submodule path 'jimtcl': checked out
'0aa0fb4e3a38d38a49de9eb585d93d63a370dcf6'
Submodule path 'src/jtag/drivers/libjaylink': checked out
'f73ad5e667ae8b26a52b847c603fdadaabf302a6'
Submodule path 'tools/git2cl': checked out
'8373c9f74993e218a08819cbcdbab3f3564bbeba'
Generating build system...
libtoolize: putting auxiliary files in AC_CONFIG_AUX_DIR, 'build-aux'.
libtoolize: copying file 'build-aux/config.guess'
libtoolize: copying file 'build-aux/config.sub'
libtoolize: copying file 'build-aux/install-sh'
libtoolize: copying file 'build-aux/ltmain.sh'
libtoolize: putting macros in AC_CONFIG_MACRO_DIRS, 'm4'.
libtoolize: copying file 'm4/libtool.m4'
libtoolize: copying file 'm4/ltoptions.m4'
libtoolize: copying file 'm4/ltsugar.m4'
libtoolize: copying file 'm4/ltversion.m4'
libtoolize: copying file 'm4/lt~obsolete.m4'
configure.ac:42: installing 'build-aux/ar-lib'
configure.ac:37: installing 'build-aux/compile'
configure.ac:30: installing 'build-aux/missing'
Makefile.am: installing './INSTALL'
libjaylink/Makefile.am: installing 'build-aux/depcomp'
Bootstrap complete. Quick build instructions:
./configure ....
checking for makeinfo... makeinfo
checking for a BSD-compatible install... /usr/bin/install -c
checking whether build environment is sane... yes
checking for a thread-safe mkdir -p... /usr/bin/mkdir -p
checking for gawk... gawk
checking whether make sets $(MAKE)... yes

......

make[4]: Leaving directory
'/home/username/Projects/openocd-git/src/openocd-git'
make[3]: Leaving directory
'/home/username/Projects/openocd-git/src/openocd-git'
make[2]: Leaving directory
'/home/username/Projects/openocd-git/src/openocd-git'
make[1]: Leaving directory
'/home/username/Projects/openocd-git/src/openocd-git'
==> Tidying install...
  -> Removing libtool files...
  -> Purging unwanted files...
  -> Removing static library files...
  -> Compressing man and info pages...
==> Checking for packaging issues...
==> Creating package "openocd-git"...
  -> Generating .PKGINFO file...
  -> Generating .BUILDINFO file...
  -> Generating .MTREE file...
  -> Compressing package...
: Can't translate pathname
'usr/share/openocd/scripts/target/1986ве1т.cfg' to UTF-8: Can't
translate pathname 'usr/share/openocd/scripts/target/к1879xб1я.cfg' to
UTF-8==> Leaving fakeroot environment.
==> Finished making: openocd-git 0.10.0.r1213.g968d3851e-1 (Mon 04 May
2020 09:39:55 AM PDT)
username@hostname:openocd-git on  master [!?]
➜ sudo pacman -U openocd-git-0.10.0.r1213.g968d3851e-1-x86_64.pkg.tar.xz
[sudo] password for username:
loading packages...
resolving dependencies...
looking for conflicting packages...

Packages (1) openocd-git-0.10.0.r1213.g968d3851e-1

Total Installed Size:  5.08 MiB
Net Upgrade Size:      0.00 MiB

:: Proceed with installation? [Y/n]
(1/1) checking keys in keyring      [########################################################################################################################] 100%
(1/1) checking package integrity    [########################################################################################################################] 100%
(1/1) loading package files         [########################################################################################################################] 100%
(1/1) checking for file conflicts   [########################################################################################################################] 100%
(1/1) checking available disk space [########################################################################################################################] 100%
:: Processing package changes...
(1/1) upgrading openocd-git         [########################################################################################################################] 100%
:: Running post-transaction hooks...
(1/3) Reloading device manager configuration...
(2/3) Arming ConditionNeedsUpdate...
(3/3) Updating the info directory file...
username@hostname:openocd-git on  master [!?]
➜
```

## Debian
Debian's packages are named as follows:
```
apt install gcc-arm-none-eabi gdb-arm-none-eabi
```
