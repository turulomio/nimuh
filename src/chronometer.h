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
#ifndef CHRONOMETER_H_
#define CHRONOMETER_H_

#include <stdlib.h>
#include <string.h>
#include <SDL.h>
#include <map>
#include <string>
#include <cmath>
#include <iostream>
#include <vector>
#include "defines.h"
#include "elements.h"

using namespace std;

namespace Martian {
		
	typedef struct
	{
		string name;
		int time;
	} LastTimes;
	
	class Chronometer {
		
	private:
		map<string, int> chrono;
		vector<LastTimes> lastTimes;
		Chronometer ();
		static Chronometer *instance;
	
	public:
		static Chronometer * GetInstance ();
		~Chronometer ();		
		void setTime(string name) { chrono[name] = SDL_GetTicks (); cleanLastTimes(name); }
		int getTime(string name);
		int getCycles(string name);
		bool verifyTime(string name, int time);
		bool existTime(string name, int time);
		bool existName(string name);
		void cleanLastTimes(string name);
		void removeTime(string name);
	};
	
}

#endif /* CHRONOMETER_H_ */
