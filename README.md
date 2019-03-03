![Nimuh](https://github.com/Turulomio/nimuh/blob/master/data/nimuh.png)

About this Fork
===============
This a fork of  https://sourceforge.net/projects/nimuh/.

This work is licensed under a Creative Commons Attribution-Noncommercial-Share Alike 2.5 Spain License. 

It was developed originally by the people in AUTHORS. It's last versión was 1.02 and was developed en 2008-02-23.

This fork was made to solve problems compiling in Linux and to recover this good game. If you like it, you can help improving this game.

Installation in Linux
=====================
If you use Gentoo, you can use this [ebuild](https://github.com/Turulomio/myportage/blob/master/games-puzzle/nimuh).

If you use other Linux distribution you must write on the code main directory and write:

`mkdir build`

`cd build`

`cmake -DCMAKE_INSTALL_PREFIX:PATH=/usr ..`

`make`

`make install`

Execute the game with:
 
`nimuh`

Installation in Windows
=======================

Download nimuh-X.X.X.zip versión from releases

Unzip it and execute nimuh.exe

Compilation in Windows
======================

Go to the MSYS2 download page and download the installer for 64 bits. Run this installer and install to the default location. 

Follow instructions in https://www.msys2.org

After updating MSYS, you need to install packages needed to compile nimuh. Simply paste the following into your command prompt 
(via the right mouse button) and hit enter. 

`pacman -S mingw-w64-x86_64-gcc mingw-w64-x86_64-SDL mingw-w64-x86_64-SDL_mixer mingw-w64-x86_64-libxml2 mingw-w64-x86_64-libpng mingw-w64-x86_64-openal mingw-w64-x86_64-libvorbis mingw-w64-x86_64-binutils mingw-w64-x86_64-freetype mingw-w64-x86_64-libzip autoconf automake-wrapper git pkgconfig make mingw-w64-x86_64-SDL_image cmake`

Sometimes compiler path is not found, so just type:

`export PATH=$PATH:/mingw64/bin/`

Clone the nimuh repository with:

`git clone https://github.com/turulomio/nimuh/`

`mkdir build`

`cd build`

`cmake -DCMAKE_INSTALL_PREFIX:PATH=/usr ..`

`make`

`make install`

Move to dist/nimuh directory and execute nimuh.exe.

Code documentation
==================
We have generated a [Doxygen code documentation](http://turulomio.users.sourceforge.net/doxygen/nimuh/index.html).

Changelog
=========
1.0.6
-----
- Added version to menu scene

1.0.5
-----
- Removed compilation warnings.
- Windows compilation and distribution.
- Added icon to executable in Windows

1.0.4
-----
- Added desktop file for UNIX installation in CMakeList.txt

1.0.3
-----
- Sourceforge project forket in GitHub
- Changed autotools to CMake

1.0.2
-----
- Solve problem with joystick
- Solve error in the third level (english version)

1.0.0
-----
- Stable version

