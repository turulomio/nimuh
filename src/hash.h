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

#ifndef HASH_H_
#define HASH_H_

#include <SDL.h>
#include <SDL_mixer.h>
#include <expat.h>
#include <map>
#include <string>
#include <cmath>
#include <iostream>
#include <vector>
#include "defines.h"

using namespace std;

namespace Martian {
	
	class Hash;
	
	typedef struct
	{
        Hash * hash;
	} ItemXML;
	
	typedef struct
	{
		string name;
		string value;
	} Item;
	
	void parseHashXML(char fileXML[128], Hash *h);
	
	class Hash {
	public :
		Hash (string file, bool fromConfDirectory);
	
		void addItem(string name, string value);
		bool setValue(string name, string value);
		string getValue(string name);
		int getValueToInt(string name);
		bool save();
		string getPathFile() { return file; }
		static string getPathData() { return pathData; }
		
		void MoveFirst() { cursor = 0; }
		void MoveLast() { cursor = items.size()-1; }
		void MovePrevious() { cursor--; }
		void MoveNext() { cursor++; }
		bool isBOF() { return (cursor<0)?true:false; }
		bool isEOF() { return (cursor>(int)items.size()-1)?true:false; }
        Item getItem() { return items[cursor]; }
        string getName() { return items[cursor].name; }
        string getValue() { return items[cursor].value; }
        
        int getNItems() { return items.size(); }
		
		~Hash ();
	protected :
		vector<Item> items;
		int cursor;
		string file;
		void loadFromConfDirectory(string f);
		void loadFromDataDirectory(string f);
		static string pathData;
	};
	
}

#endif /* HASH_H_ */
