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

#ifndef WORLD_H_
#define WORLD_H_

#include <SDL.h>
#include <SDL_mixer.h>
#include "defines.h"
#include "elements.h"
#include "sound.h"
#include "chronometer.h"
#include "joystick.h"
#include "hash.h"
#include "options.h"
#include "score.h"
#include "font.h"
#include "timer.h"
#include "language.h"
#include "scene.h"
#ifdef WIN32
#include "glext.h"
#endif
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <string>

#include <cmath>
#include <iostream>
#include <vector>
#include <map>

using namespace std;

namespace Martian {
	
	class Scene;
	
	class World {
		
	protected:
		bool fullscreen;
		Uint8 *keys;
		Sint16 joyx, joyy;
		
		map<string, Scene*> scenes;
		int currentScene;
		bool existDataDirectory;
		
	public:	
		Joystick *joystick;
		SDL_Surface *screen;
	
		World(int w, int h, string titleWindow);
		void InitGL();
		/*********************
		* SCREEN
		**********************/
		static int width, height;
		void modeScreen();
		void execute();
		/*********************
		* ESCENES
		**********************/
		void addScene(string name, Scene* sc) { scenes[name] = sc; }
		Scene* getScene(string name) { return scenes[name]; }
		void loadScenes();
		int loadScene(string sc);
		
		void unLoad();
		
	};
	
}

#endif /* WORLD_H_ */
