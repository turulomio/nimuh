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
 
 
#include "timer.h"

namespace Martian {
	
	/*****************************
	**
	** CLASE TIMER
	**
	******************************/	

	Timer* Timer::instance = NULL;
	
	Timer::Timer() {
		start = SDL_GetTicks ();
		ticksBegin = SDL_GetTicks ();
		mlByFrame = 0;
		fps = 0;
		inializeCurrentFPS();
		ticksBegin_currentFPS = SDL_GetTicks ();
		lastCurrentFPS = 0; 
		setFPS(50);
	}
	
	Timer* Timer::GetInstance () {
		if ( instance == NULL ) {
			instance = new Timer();
		}
		return instance;	
	}
	
	void Timer::waitFrame() {
		Uint32 time = SDL_GetTicks () - ticksBegin;
		if (time<mlByFrame) {
			while (SDL_GetTicks()<ticksBegin+(mlByFrame-time)) {
			}
		}
		setTicksBeginNow();
		if (SDL_GetTicks ()-ticksBegin_currentFPS>1000) {
			ticksBegin_currentFPS = SDL_GetTicks ();
			lastCurrentFPS = currentFPS;
			inializeCurrentFPS();
		} else {
			addCurrentFPS();
		}

	}
	
	void Timer::setFPS(int f) { 
		fps = f;
		mlByFrame = (Uint32)1000/(Uint32)fps;	
	}
	
}
