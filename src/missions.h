/*
 * DESCRIPCION DEL JUEGO
 * Copyright (C) 2007  Javier Pérez Pacheco
 *
 * Este juego tienen licencia Creative Commons y se permite
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
 * GRAFISMO Y 3D
 * Jesus Carrasco
 * Cadiz (Spain)
 * carrasco.carrasco@gmail.com
 *
 * MUSICA Y GRAFISMO
 * Shano Lores
 * Cadiz (Spain)
 * shanakla@gmail.com
 *
 */

#ifndef MISION_H_
#define MISION_H_

#include <SDL.h>
#include <SDL_mixer.h>
#include <expat.h>
#include <map>
#include <string>
#include <cmath>
#include <iostream>
#include <vector>

#include <errno.h> 
#include <dirent.h> 
#include <stdio.h> 
#include <stdlib.h> 

#include "defines.h"
#include "defines_game.h"
#include "font.h"
#include "user.h"

using namespace std;
using namespace Martian;

class Mission;

typedef struct
{
	string name, nameAuthor, emailAuthor;
} DictionaryNameMissionXML;

typedef struct
{
	string name, province;
	int typeScenary;
} DictionaryNameLevelXML;

typedef struct
{
	Mission *mission;
} DictionaryAddLevelsXML;

DictionaryNameMissionXML parseNameMissionXML(char fileXML[128]);

DictionaryNameLevelXML parseNameLevelXML(char fileXML[128]);

void parseAddLevelsXML(char fileXML[128], Mission *m);

class Level {
public :
	Level (string d, string n);
	string getName() { return name; }
	string getDirectory() { return directory; }
	void setProvince(string p) { province = p; }
	string getProvince() { return province; }
	
	void setTypeScenary(int t) { typeScenary = t; }
	int getTypeScenary() { return typeScenary; }
	
	void setParentMission(Mission *p) { parentMission = p; }
	
	string getPath();
	
	bool existFile(string f);
	
	~Level ();

private :
	Mission *parentMission;
	string name, directory, province;
	int typeScenary;
	
};

class Mission {
public :
	Mission (string d, string n);
	void setName(string n) { name = n; }
	string getName() { return name; }
	string getDirectory() { return directory; }
	void setNameAuthor(string n) { nameAuthor = n; }
	string getNameAuthor() { return nameAuthor; }
	
	bool addLevel(Level* l);
	~Mission ();

	void MoveFirst() { cursor = 0; }
	void MoveLast() { cursor = levels.size()-1; }
	void MovePrevious() { cursor--; }
	void MoveNext() { cursor++; }
	bool isBOF() { return (cursor<0)?true:false; }
	bool isEOF() { return (cursor>((int)levels.size()-1))?true:false; }
	Level* getLevel() { if (cursor>(int)levels.size()-1) { return NULL; } else { return levels[cursor]; } }
	
	Level* getLevel(int p) { if (p>(int)levels.size()-1) { return NULL; } else { return levels[p]; } }
	
	void removeLevel(int i);
	
	bool upLevel(int l);
	bool downLevel(int l);
	
	void setIsUserMission(bool u) { isUserMission = u; }
	bool getIsUserMission() { return isUserMission; }
	
	string getPath();
	
	int getNLevels() { return (int)levels.size(); }
	
	void load();
	void save();
		
private :
	vector<Level*> levels;
	bool isUserMission;
	int cursor;
	string name, directory, nameAuthor;
	
};

class Missions {
public :
	static Missions * GetInstance ();

	Mission* currentMission;
	Level* currentLevel;

	bool setCurrentLevel();
	bool setCurrentMissionAndLevel(int i);
	bool setCurrentMissionAndLevel(string name);

	string pathXMLLevel();

	bool addMission(Mission* m);
	bool addMission(string directory, string name) { Mission *aux = new Mission(directory, name); return addMission(aux);  }

	void MoveFirst() { cursor = 0; }
	void MoveLast() { cursor = missions.size()-1; }
	void MovePrevious() { cursor--; }
	void MoveNext() { cursor++; }
	bool isBOF() { return (cursor<0)?true:false; }
	bool isEOF() { return (cursor>((int)missions.size()-1))?true:false; }
	Mission* getMission() { return missions[cursor]; }
	
	Mission* getCurrentMission();
	int getCursor() { return cursor; }
	
	Mission* getMission(int i) { return (i>((int)missions.size()-1))?NULL:missions[i]; }
	
	bool existDirectoryOfMission(string m);
	
	bool existDirectoryOfLevel(string m, string l);
	
	void load();
	void save();
	
	int getNMissions() { return missions.size(); }

	~Missions ();
private :
	string directory;
	int cursor;
	vector<Mission*> missions;
	Missions ();
	static Missions *instance;
	
};


#endif /* MISION_H_ */
