<div align="center">

![Nimuh](https://github.com/Turulomio/nimuh/raw/master/data/nimuh.png)

# Nimuh

[![Total Downloads](https://img.shields.io/github/downloads/turulomio/nimuh/total?color=blue&label=Total%20Downloads)](https://github.com/turulomio/nimuh/releases)
[![Latest Release](https://img.shields.io/github/v/release/turulomio/nimuh)](https://github.com/turulomio/nimuh/releases)
[![License: CC BY-NC-SA 2.5 ES](https://img.shields.io/badge/License-CC%20BY--NC--SA%202.5%20ES-lightgrey.svg)](https://creativecommons.org/licenses/by-nc-sa/2.5/es/)

</div>

About Nimuh
===========
**Nimuh** is an entertaining puzzle game set across various cities and landmarks of Andalusia.

This project is a modern fork of the original game hosted at [SourceForge](https://sourceforge.net/projects/nimuh/).
It was originally created by the authors listed in [AUTHORS](AUTHORS). Its last original version (1.02) was released on 2008-02-23.

This fork updates the game to support modern Linux and Windows environments, modern compilers (C++11/GCC), CMake build system, cross-compilation with MinGW, and standalone single-file portable packages.

This work is licensed under a [Creative Commons Attribution-NonCommercial-ShareAlike 2.5 Spain License](https://creativecommons.org/licenses/by-nc-sa/2.5/es/).

Downloads (Ready to Play)
=========================
You can download pre-built packages from the [Releases page](https://github.com/turulomio/nimuh/releases):

- **Linux**: Download `nimuh-<version>-linux.run`, make it executable (`chmod +x nimuh-*-linux.run`), and run it directly.
- **Windows (64-bit)**: Download and run `nimuh-<version>-windows-x64-portable.exe` (no installation required).
- **Windows (32-bit)**: Download and run `nimuh-<version>-windows-x86-portable.exe` (no installation required).

Compilation and Installation on Linux
=====================================
Tasks are managed using [Poe the Poet](https://github.com/nat-n/poethepoet) (`poe`). If you do not have it installed:

```bash
pip install poethepoet
```

On Gentoo, you can also use this [ebuild](https://github.com/turulomio/myportage/blob/master/games-puzzle/nimuh).

### 1. Requirements on Gentoo
To build the standalone single-file Linux bundle, install `makeself`:

```bash
emerge app-arch/makeself
```

### 2. Install from source
To compile and install Nimuh to a specific directory prefix:

```bash
# User local directory (no root required)
poe sources-linux ~/.local

# System-wide (e.g. /usr)
sudo poe sources-linux /usr
```

Run the installed game:

```bash
nimuh
```

### 3. Compile standalone single-file package for Linux
To compile the binary, bundle all assets, and generate a single self-extracting executable (`dist/nimuh-<version>-linux.run`) using `makeself`:

```bash
poe binaries-linux
```

Execute the package directly:

```bash
./dist/nimuh-<version>-linux.run
```

### 4. Uninstall
To uninstall Nimuh previously installed on Linux:

```bash
poe sources-linux-uninstall
```

Cross-compilation for Windows (from Linux / Gentoo)
===================================================
You can compile and package Windows binaries directly from Linux using the MinGW toolchain (`dev-util/mingw64-toolchain` on Gentoo, which includes both 64-bit `x86_64-w64-mingw32` and 32-bit `i686-w64-mingw32` compilers).

### 1. Requirements on Gentoo
Install the MinGW-w64 toolchain:

```bash
emerge dev-util/mingw64-toolchain
```

### 2. Build Windows portable packages (64-bit & 32-bit)
To compile and package both Windows versions in a single step:

```bash
poe binaries-windows
```

The `poe binaries-windows` task automatically:
1. Checks for required Windows dependencies and downloads/unpacks them into `.mingw64/` (64-bit) and `.mingw32/` (32-bit) without requiring root permissions.
2. Cross-compiles `nimuh.exe` for both architectures (`x64` and `x86`) with MinGW, including all runtime DLLs and assets.
3. Packages everything into standalone portable executables with the game's icon:
   - `dist/nimuh-<version>-windows-x64-portable.exe` (64-bit)
   - `dist/nimuh-<version>-windows-x86-portable.exe` (32-bit)
   *(When launched on Windows, each unpacks transparently into `%TEMP%\nimuh-<version>-<arch>\` and starts the game).*
4. Automatically cleans up intermediate build folders and temporary payload directories.

### Dependencies setup
Dependencies are downloaded on-demand from the [MSYS2 Repository](https://repo.msys2.org/mingw/) into `.mingw64/` and `.mingw32/`. Alternatively, you can install them system-wide into `/mingw64` or `/mingw32`.



