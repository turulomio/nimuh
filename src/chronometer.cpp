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
 
 
#include "chronometer.h"

namespace Martian {
	
	/*****************************
	**
	** CLASE CHRONOMETER
	**
	******************************/	

	Chronometer* Chronometer::instance = NULL;
	
	Chronometer::Chronometer() {
	}
	
	Chronometer* Chronometer::GetInstance () {
		if ( instance == NULL ) {
			instance = new Chronometer();
		}
		return instance;	
	}
	
	int Chronometer::getTime(string name) { 
		if (chrono[name])
			return SDL_GetTicks ()-chrono[name]; 
		else
			return -1;
	}
	
	int Chronometer::getCycles(string name) { 
		return Converter::GetInstance()->ml2cycles(getTime(name)); 
	}
	
	bool Chronometer::existTime(string name, int time) { 
		for (int i=0; i<(int)lastTimes.size(); i++) {
			if ( (lastTimes[i].name == name) && (lastTimes[i].time == time) ) {
				return true;
			}
		}
		return false;
	}
	
	bool Chronometer::existName(string name) { 
		map<string, int>::iterator it;
		for (it=chrono.begin(); it!=chrono.end(); ++it) {
			if ((*it).first == name) {
				return true;
			}
		}
		return false;
	}
		
	bool Chronometer::verifyTime(string name, int time) { 
		if (existTime(name, time)) {
			return false;
		} else {
			if (getTime(name)>=time) {
				LastTimes lt;
				lt.name = name;
				lt.time = time;
				lastTimes.push_back(lt);
				return true;
			}
		}
		return false;
	}
	
	void Chronometer::removeTime(string name) { 
		if (existName(name)) {
			cleanLastTimes(name);
			map<string, int>::iterator item;
			item = chrono.find(name);
			chrono.erase(item);
		}
	}
	
	void Chronometer::cleanLastTimes(string name) {
		for (int i=0; i<(int)lastTimes.size(); i++) {
			if (lastTimes[i].name == name) {
				lastTimes.erase(lastTimes.begin()+i);
				i--;
			}
		}
	}
	
}
