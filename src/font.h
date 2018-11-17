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

#ifndef FONT_H_
#define FONT_H_

#include <stdlib.h>
#include <string.h>
#include <SDL.h>
#include <SDL_mixer.h>
#include "defines.h"
#include "elements.h"
#include <map>
#include <string>
#include <vector>

using namespace std;

namespace Martian {
	
	class Element;
	
	typedef struct
	{
		int nLines;
		string text;
		int xPosCursor;
		vector<int> nLettersByLine;
	} InfoFontBitMap;
	
	class FontBitMap {
		
	private:
		int nLetters;
		SDL_Surface *letters[150];
		string file; 
		bool preload;
	
		void loadLetters();
		void unLoadLetters();
	
	public:
		FontBitMap (string file_img, bool pl);
		~FontBitMap ();
	
		bool columnTransparent (SDL_Surface * img, int column);
		void createElements (SDL_Surface * img);
		void saveLetter (SDL_Surface * img, int index, int x, int y, int w, int h);
		Uint32 get_pixel (SDL_Surface * img, int x, int y);
		int getIndexLetter (char c);
		void writeIndexWord (char* c);
		SDL_Surface* getWord (char * chain);
	
		void unLoad();
	
	};
	
	
	class Fonts {
		
	private:
        map<string, FontBitMap*> fontsbitmap;
		string defaultFont, lastFont;
		Fonts ();
		static Fonts *instance;
	public:
		static Fonts* GetInstance ();
		~Fonts ();
	
		void setDefaultFont(string f) { defaultFont = f; }
		string getDefaultFont() { if (defaultFont == "") { return lastFont; } else { return defaultFont; } }
	
		void addFontBitMap(string name, string file) { addFontBitMap(name, file, true); }
		void addFontBitMap(string name, string file, bool preload) { fontsbitmap[name] = new FontBitMap(file, preload); lastFont = name; }
		FontBitMap* getFontBitMap(string name) { return fontsbitmap[name]; }
		
		bool existFont(string name);
	
		SDL_Surface* getSurface_TextBitMap (string nameFont, int align, string text) {  return getSurface_TextBitMap (nameFont, -1, align, text); }
		SDL_Surface* getSurface_TextBitMap (string nameFont, int width, int align, string text) { return getSurface_TextBitMap (nameFont, 1.0, width, align, text); }
		SDL_Surface* getSurface_TextBitMap (string nameFont, float scale, int width, int align, string text) { return getSurface_TextBitMap (nameFont, -1, scale, width, align, text); }
		SDL_Surface* getSurface_TextBitMap (string nameFont, int nLines, float scale, int width, int align, string text);
		
		InfoFontBitMap getInfoFontBitMap (string nameFont, int nLines, float scale, int width, int align, string text);
		
		void unLoad ();
	};
	
}

#endif /* FONT_H_ */
