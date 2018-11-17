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

 
 /*****************************
**
** CLASE Joystick
**
******************************/

#include "joystick.h"

namespace Martian {
	
	Joystick::Joystick() {
	}
	 
	
	void Joystick::initJoystick () {
		
		// activa joystick	
		if (SDL_NumJoysticks() >= 1) {
			joystick = SDL_JoystickOpen(0);
			SDL_JoystickEventState (SDL_ENABLE);
		}
		
	}
	
	int Joystick::verifyButtonJoystick(int button) {
		if (SDL_NumJoysticks() >= 1) {
			if (SDL_JoystickGetButton(joystick, button)) {
				return 1;
			}
		}
		return 0;
	}
	
	void Joystick::unLoadJoystick () {
		if (SDL_NumJoysticks() >= 1) {
			SDL_JoystickClose(joystick);
		}
	}

}
