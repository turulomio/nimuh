![Nimuh](https://github.com/Turulomio/nimuh/blob/master/data/nimuh.png)

About this Fork
===============
This a fork of  https://sourceforge.net/projects/nimuh/.

This work is licensed under a Creative Commons Attribution-Noncommercial-Share Alike 2.5 Spain License. 

It was developed originally by the people in AUTHORS. It's last versión was 1.02 and was developed en 2008-02-23.

This fork was made to solve problems compiling in Linux and to recover this good game. If you like it, you can help improving this game.

Installation
============
If you use Gentoo, you can use this [ebuild](https://github.com/Turulomio/myportage/blob/master/games-puzzle/nimuh).

If you use other Linux distribution or Windows (not tested) you must write on the code main directory and write:

`mkdir build`

`cd build`

`cmake -DCMAKE_INSTALL_PREFIX:PATH=/usr ..`

`make`

`make install`

Execute the game with:
 
`nimuh`

Code documentation
==================
We have generated a [Doxygen code documentation](http://turulomio.users.sourceforge.net/doxygen/nimuh/index.html).
