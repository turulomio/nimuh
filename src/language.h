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

#ifndef LANGUAGE_H_
#define LANGUAGE_H_

#include <SDL.h>
#include <SDL_mixer.h>
#include <expat.h>
#include <map>
#include <string>
#include <cmath>
#include <iostream>
#include <vector>
#include "defines.h"
#include "font.h"

using namespace std;

namespace Martian {
	
	typedef struct
	{
		string lang;
		string reference;
		string text;
		bool inPhrase;
	} DictionaryXML;
	
	typedef struct
	{
		string reference;
		string text;
	} Phrase;
	
	void parseXML(char fileXML[128], string l);
	
	class Language {
	public :
		static Language * GetInstance ();
		void setLang(string c);
		string getLang() { return lang; }
		void addPhrase(string ref, string txt);
		string getText(string ref);
		string getFilename(string file, string ext);
		~Language ();
	private :
		Language ();
		static Language *instance;
		string lang;
		vector<Phrase> dictionary;
		
	};
	
}

#endif /* LANGUAGE_H_ */
