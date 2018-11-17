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
 
 #include "world.h"

namespace Martian {
	
	 int World::width = 0;
	 int World::height = 0;
	
	 World::World(int w, int h, string titleWindow) {
		 
		existDataDirectory = WorkingData::GetInstance()->existFile(string(DATA_DIR)+"/.");
		 
		srand(time(NULL));
		 
		width = w;
		height = h;
		 
		currentScene = -1;
	
		// Init SDL
		 
		if (SDL_Init(SDL_INIT_TIMER | SDL_INIT_VIDEO | SDL_INIT_JOYSTICK | SDL_INIT_AUDIO) < 0)
		{
			printf ("No se puede iniciar SDL: %s\n", SDL_GetError());
		}
	
		fullscreen = false;

		//modeScreen ();
		
		//SDL_ShowCursor(0);
		SDL_WM_SetCaption(titleWindow.c_str(), titleWindow.c_str());
				
		// load timer
		
		Timer::GetInstance();
		
	}
	
	
	void World::InitGL()
	{
	    //glViewport(0, 0, WIDTH_SCREEN, HEIGHT_SCREEN);
	
		glEnable(GL_TEXTURE_2D);
		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
			
		glShadeModel(GL_SMOOTH);
		
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(0, width, height, 0, -1000, 1000);    
		glMatrixMode(GL_MODELVIEW);
		
	}
	
	
	void World::modeScreen () {
		Uint32 flags;
		int screen_bpp;
				
		if (Options::GetInstance()->getValue("fullscreen") != "") {
			if (Options::GetInstance()->getValue("fullscreen") == "true") {
				fullscreen = true;
			} else {
				fullscreen = false;
			}
		} else {
			fullscreen = false;
		}
		
		//flags = SDL_HWSURFACE | SDL_DOUBLEBUF;
		
		if ( fullscreen ) {
			flags = SDL_FULLSCREEN | SDL_OPENGL;
		} else {
			flags = SDL_OPENGL;
		}
		
		screen_bpp = 24;
		
		//flags |= SDL_OPENGL;
	
		
		screen = SDL_SetVideoMode (width, height, 0, flags);
		
		InitGL();
	}

	int World::loadScene(string sc) {
		if (sc=="quit") {
			return -1;
		} else {
			return getScene(sc)->getId();
		}
	}	
	
	void World::unLoad() {
		Sounds::GetInstance()->unLoadAll();
		Fonts::GetInstance()->unLoad();
		Cursor::GetInstance()->unLoad();
	}


}
