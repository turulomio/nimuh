![Nimuh](https://github.com/Turulomio/nimuh/blob/master/data/nimuh.png)

About this Fork
===============
This a fork of  https://sourceforge.net/projects/nimuh/.

This work is licensed under a Creative Commons Attribution-Noncommercial-Share Alike 2.5 Spain License. 

It was developed originally by the people in AUTHORS. It's last versión was 1.02 and was developed en 2008-02-23.

This fork was made to solve problems compiling in Linux and to recover this good game. If you like it, you can help improving this game.

Compilation and Installation in Linux
=====================================
If you use Gentoo, you can use this [ebuild](https://github.com/turulomio/myportage/blob/master/games-puzzle/nimuh).

Tasks are managed with [Poe the Poet](https://github.com/nat-n/poethepoet) (`poe`). If you don't have it installed, you can install it via pip:

```bash
pip install poethepoet
```

### Requirements on Gentoo

To build the standalone single-file package on Gentoo, install `makeself`:

```bash
emerge app-arch/makeself
```

### Install from source

To compile and install Nimuh to a specific directory prefix (such as `/usr`):

```bash
poe sources-linux /usr
```

Execute the game with:
 
```bash
nimuh
```

### Compile standalone binaries for Linux

To compile the Linux binary, bundle all data and media files, and generate a single self-extracting executable (`dist/nimuh-<version>-linux.run`) using `makeself`:

```bash
poe binaries-linux
```

Execute the single-file package directly with:

```bash
./dist/nimuh-<version>-linux.run
```

### Uninstall

To uninstall Nimuh from Linux:

```bash
poe uninstall
```

Cross-compilation for Windows (from Linux / Gentoo)
===================================================
You can compile and package the Windows binaries directly from Linux using the MinGW toolchain (`dev-util/mingw64-toolchain` on Gentoo).

### 1. Requirements on Gentoo
Install the MinGW-w64 toolchain:
```bash
emerge dev-util/mingw64-toolchain
```

### 2. Build Windows package
To compile and package the Windows version:

```bash
poe binaries-windows
```

The `poe binaries-windows` task automatically checks for the required Windows libraries (SDL 1.2, SDL_image, SDL_mixer, EXPAT, and runtime DLLs). If they are not already present in `/mingw64`, it will automatically download and unpack them into `.mingw64/` within the project root.

The executable `nimuh.exe`, required DLLs, and data assets will be placed into `dist/nimuh-<version>/`.

### Dependencies setup
The `poe binaries-windows` task automatically manages all required dependencies locally inside `.mingw64/` without requiring root permissions.

If you prefer to install the Windows dependencies system-wide in `/mingw64`, you can download and unpack the MSYS2 MinGW64 packages (`*.pkg.tar.zst`) directly into `/` from the [MSYS2 MinGW64 Repository](https://repo.msys2.org/mingw/mingw64/).



Installation in Windows from binaries
======================================
1. Download the `nimuh-X.X.X.zip` version from releases.
2. Unzip it.
3. Execute `nimuh.exe`.


