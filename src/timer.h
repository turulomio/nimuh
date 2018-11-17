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
#ifndef TIMER_H_
#define TIMER_H_

#include <stdlib.h>
#include <string.h>
#include <SDL.h>
#include "defines.h"

namespace Martian {
		
	class Timer {
	public :
		static Timer * GetInstance ();
	
		void setFPS(int f);
		int getFPS() { return fps; };
		
		void inializeCurrentFPS() { currentFPS = 0; }
		void setCurrentFPS(int f) { currentFPS = f; }
		void addCurrentFPS() { currentFPS++; }
		int getCurrentFPS() { return currentFPS; };
		
		int getLastCurrentFPS() { return lastCurrentFPS; };
		
		void setTicksBeginNow() { ticksBegin = SDL_GetTicks (); };
		void waitFrame();
		~Timer ();
	private :
		Uint32 start;
		Uint32 ticksBegin;
		unsigned int fps;
		Uint32 ticksBegin_currentFPS;
		unsigned int currentFPS;
		unsigned int lastCurrentFPS; 
		Uint32 mlByFrame;
		Timer ();
		static Timer *instance;
		
	};
	
}

#endif /* TIMER_H_ */
