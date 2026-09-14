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

To compile the Linux binary and copy all data and media files into `dist/binaries-linux/`:

```bash
poe binaries-linux
```

Execute the binary directly with:

```bash
./dist/binaries-linux/nimuh
```

### Uninstall

To uninstall Nimuh from Linux:

```bash
poe uninstall
```

Compilation for Windows (cross-compilation from Linux)
======================================================
You can compile and package the Windows binaries directly from Linux using MinGW:

```bash
poe binaries-windows
```

This compiles the game and copies the executable and required DLLs into `dist/nimuh-<version>/`.

Requirements for cross-compilation on Gentoo
--------------------------------------------
To cross-compile the Windows binaries on Gentoo, the following components are required:

1. **MinGW-w64 toolchain**:
   Install `dev-util/mingw64-toolchain` to obtain `x86_64-w64-mingw32-gcc`, `x86_64-w64-mingw32-g++`, and `x86_64-w64-mingw32-windres`:
   ```bash
   emerge dev-util/mingw64-toolchain
   ```

2. **Windows libraries and DLLs in `/mingw64`**:
   The build requires MinGW-compiled development libraries and runtime DLLs available under `/mingw64`:
   - Headers and libraries in `/mingw64/include` and `/mingw64/lib` for CMake dependencies (SDL, SDL_image, SDL_mixer, libexpat, etc.).
   - Runtime DLLs in `/mingw64/bin/` (such as `SDL.dll`, `SDL_image.dll`, `libSDL_mixer-1-2-0.dll`, `libexpat-1.dll`, etc.) which are copied into the `dist/nimuh-<version>/` distribution directory.


Installation in Windows from binaries
======================================
1. Download the `nimuh-X.X.X.zip` version from releases.
2. Unzip it.
3. Execute `nimuh.exe`.


