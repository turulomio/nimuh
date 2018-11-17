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

#ifndef CURSOR_H_
#define CURSOR_H_

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
#include "elements.h"

using namespace std;

namespace Martian {
	
	class AnimatedElement;
	class Element;
	class Group;
	
	class Cursor {
	public :
        static Cursor * GetInstance ();
	
		void setPaddingCursor(int x, int y) { paddingX = x; paddingY = y; }
		void setScaleAlt(float s) { scaleAlt = s; }
		void setSizeBorder(int s) { sizeBorder = s; }
		void setMlWaitingAlt(int ml) { mlWaitingAlt = ml; }
			
		void showText(string t) { showText(t, ALIGN_CENTER, VALIGN_BOTTOM); }
		void showText(string t, int align, int pos);
		void showText();
		void forceHideText() { showAlt = false; showAltWhenFinishEffect = false; waitingAlt = false; }
		void hideText();
		void hideText(string t);
	
		void setColorsAltText(int r, int g, int b) { rAltText = r; gAltText = g; bAltText = b; }
		void setColorsAltBackground(int r, int g, int b, int a) { rAltBg = r; gAltBg = g; bAltBg = b; aAltBg = a; }
		void setColorsAltBorder(int r, int g, int b) { rAltBorder = r; gAltBorder = g; bAltBorder = b; }
		
		void setFontText(string f) { fontText = f; }
        
        void setCursor(string name);
		void addCursor(string name, string file);
		void addAnimatedCursor(string name, string file, string ext, int nFrames);
		
		void setUseImageCursor(bool u) { useImageCursor = u; if (useImageCursor) { SDL_ShowCursor (SDL_DISABLE); } else { SDL_ShowCursor (SDL_ENABLE); } }
        
        void draw();
		
		void unLoad();
        
		~Cursor ();
	private :
        static Cursor *instance;
        AnimatedElement *cursors;
        bool useImageCursor;
	
		bool waitingAlt;
	
		int paddingX, paddingY;
	
		float scaleAlt;
		int alignAlt;
		int posAlt;
		int sizeBorder;
		int mlWaitingAlt;
	
		bool showAlt;
		bool showAltWhenFinishEffect;
	
		string text;
		string fontText;
	
		int rAltText, gAltText, bAltText;
		int rAltBg, gAltBg, bAltBg, aAltBg;
		int rAltBorder, gAltBorder, bAltBorder;
	
		Group *grpAlt;
		Element *textAlt;
		Element *bgAlt;
	
		Cursor ();
		
	};
	
}

#endif /* CURSOR_H_ */
