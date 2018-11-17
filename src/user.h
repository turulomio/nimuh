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

#ifndef USER_H_
#define USER_H_

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
#include "missions.h"

using namespace std;
using namespace Martian;

void parseUserXML(char fileXML[128]);

typedef struct
{
	string directory;
	int level;
} DataMission;

class User {
public :
	User (string n);
	string getName() { return name; }
	
	bool addMission(DataMission m);
	bool addMission(string directory) { DataMission m; m.directory = directory; m.level = 1; return addMission(m); }
	bool addMission(string directory, int l) { DataMission m; m.directory = directory; m.level = l; return addMission(m); }
	
	void setLevelInMission(string mission, int l);
	void setLevelInCurrentMission(int l);
	void addLevelInMission(string mission);
	void addLevelInCurrentMission();
	int getLevelInMission(string mission);
	int getLevelInCurrentMission();
	
	bool addMyMission(string m);
	bool isMyMission(string m);
		
	~User ();

	vector<DataMission> missions;
	vector<string> my_missions;
	
private :
	string name;

};

	
typedef struct
{
	User *auxUser;
	bool inUser;
} DictionaryUserXML;

class Users {
public :
	static Users * GetInstance ();

	bool addUser(User* u);
	bool addUser(string u) { User *aux = new User(u); return addUser(aux);  }

	void MoveFirst() { cursor = 0; }
	void MoveLast() { cursor = users.size()-1; }
	void MovePrevious() { cursor--; }
	void MoveNext() { cursor++; }
	bool isBOF() { return (cursor<0)?true:false; }
	bool isEOF() { return (cursor>((int)users.size()-1))?true:false; }
	User* getUser() { return users[cursor]; }
	
	User* getCurrentUser();
	
	User* getUser(int i) { return (i<0 || i>((int)users.size()-1))?NULL:users[i]; }
	
	void removeUser(int i) { users.erase(users.begin()+i); }
	
	void load(string f);
	
	bool save();
	
	int getNUsers() { return users.size(); }

	~Users ();
private :
	string file;
	int cursor;
	vector<User*> users;
	Users ();
	static Users *instance;
	
};


#endif /* USER_H_ */
