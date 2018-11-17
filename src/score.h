/*
 * Martian: Motor para creación de videojuegos con SDL y OpenGL
 * Copyright (C) 2007  Javier Pérez Pacheco
 *
 * Este motor tiene licencia Creative Commons y se permite
 * su modificacion y utilizacion libremente siempre y cuando se
 * cite al autor original y se comparta con la misma licencia.
 * No se permite su uso comercial.
 * 
 * Para mas informacion visite la web:
 * http://creativecommons.org/licenses/by-nc-sa/2.0/es/
 *
 * PROGRAMADOR
 * Javier Pérez Pacheco
 * Cadiz (Spain)
 * javielinux@gmail.com
 *
 */

#ifndef SCORE_H_
#define SCORE_H_

#include <SDL.h>
#include <SDL_mixer.h>
#include <expat.h>
#include <map>
#include <string>
#include <cmath>
#include <iostream>
#include <vector>
#include "defines.h"
#include "martian.h"

using namespace std;

namespace Martian {
	
	class Score : public Hash {
	public :
        static Score * GetInstance ();
        void setNPlayers(int n) { nPlayers = n; }
        int getNPlayers() { return nPlayers; }
        bool save();
		~Score ();
	private :
        static Score *instance;
		Score (string file);
		void orderByScore();
        int nPlayers;			
	};
	
}

#endif /* SCORE_H_ */
