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
#ifndef JOYSTICK_H_
#define JOYSTICK_H_

#include <SDL.h>
#include <SDL_mixer.h>
#include "defines.h"

namespace Martian {
	class Joystick {
		
	private:
	
	public:
		SDL_Joystick *joystick;
		Joystick ();
		void initJoystick ();
		int verifyButtonJoystick(int button);
		void unLoadJoystick ();
	};
}
#endif /* JOYSTICK_H_ */
