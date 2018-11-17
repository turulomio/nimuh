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
 
#include "user.h"

 
/*****************************
**
** CLASE User
**
******************************/	

User::User(string n) {
	name = n;
}

void User::setLevelInMission(string mission, int l) {
	bool todo = true;
	int i;
	for (i=0; i<(int)missions.size(); i++) {
		if (missions[i].directory == mission) {
			missions[i].level = l;
			todo = false;
		}
	}
	
	if (todo) {
		DataMission dm;
		dm.directory = mission;
		dm.level = l;
		addMission(dm);
	}
	
}

void User::setLevelInCurrentMission(int l) { 
	setLevelInMission(Missions::GetInstance()->currentMission->getDirectory(), l); 
}

void User::addLevelInMission(string mission) {
	bool todo = true;
	int i;
	for (i=0; i<(int)missions.size(); i++) {
		if (missions[i].directory == mission) {
			missions[i].level = missions[i].level+1;
			todo = false;
		}
	}
	
	if (todo) {
		DataMission dm;
		dm.directory = mission;
		dm.level = 0;
		addMission(dm);
	}
	
}

void User::addLevelInCurrentMission() { 
	addLevelInMission(Missions::GetInstance()->currentMission->getDirectory()); 
}

bool User::addMission(DataMission m) { 
	for (int i=0; i<(int)missions.size(); i++) {
		if (missions[i].directory==m.directory) { 
			return false; 
		} 
	}
	missions.push_back(m); 
	return true; 
}

bool User::addMyMission(string m) { 
	for (int i=0; i<(int)my_missions.size(); i++) {
		if (my_missions[i]==m) { 
			return false; 
		} 
	}
	my_missions.push_back(m); 
	return true; 
}

bool User::isMyMission(string m) { 
	for (int i=0; i<(int)my_missions.size(); i++) {
		if (my_missions[i]==m) { 
			return true; 
		} 
	}
	return false; 
}

int User::getLevelInMission(string mission) {
	for (int i=0; i<(int)missions.size(); i++) {
		if (missions[i].directory==mission) { 
			return missions[i].level; 
		} 
	}
	return -1;
}

int User::getLevelInCurrentMission() {
	return getLevelInMission(Missions::GetInstance()->currentMission->getDirectory());
}

/*****************************
**
** CLASE Users
**
******************************/	

Users* Users::instance = NULL;

Users::Users() {
	cursor = 0;
}

Users* Users::GetInstance () {
	if ( instance == NULL ) {
		instance = new Users();
	}
	return instance;	
}

bool Users::addUser(User* u) { 
	for (int i=0; i<(int)users.size(); i++) {
		if (getUser(i)->getName()==u->getName()) { 
			return false; 
		} 
	}
	u->addMission("andalucia", 0);
	users.push_back(u); 
	return true; 
}

User* Users::getCurrentUser() { 
	int i = atoi(Options::GetInstance()->getValue("user").c_str());
	if (getUser(i)==NULL) return NULL;
	return ( (i<0) || (i>(int)users.size()-1) )?NULL:users[i]; 
}

void Users::load(string f) { 
	file = Hash::getPathData() + f; 
		
	FILE *c = fopen((char*)file.c_str(), "r");
	if(!c) save();
	parseUserXML((char*)file.c_str()); 
}

bool Users::save() {
	
	char tmp_val[128];
	string chainFile = "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n<users>\n";
	
	int i, j;
	for (i=0; i<(int)users.size(); i++) {
		
		chainFile += "\t<user name=\"" + users[i]->getName() + "\">\n";
	
			chainFile += "\t\t<missions>\n";
		
			for (j=0; j<(int)users[i]->missions.size(); j++) {
				sprintf (tmp_val, "\t\t\t<mission name=\"%s\" level=\"%d\" />\n", users[i]->missions[j].directory.c_str(), users[i]->missions[j].level);
				chainFile += tmp_val;
			}
			
			chainFile += "\t\t</missions>\n";
			
			chainFile += "\t\t<my-missions>\n";
		
			for (j=0; j<(int)users[i]->my_missions.size(); j++) {
				sprintf (tmp_val, "\t\t\t<my-mission name=\"%s\" />\n", users[i]->my_missions[j].c_str());
				chainFile += tmp_val;
			}
			
			chainFile += "\t\t</my-missions>\n";
			
		chainFile += "\t</user>\n";

	}
	
	chainFile += "</users>\n";
	
	return WorkingData::GetInstance()->createFile(file, chainFile, true);
	
}


/*****************************
**
** XML
**
******************************/

static void startUserXML(void *userData, const char *el, const char **attr) {
	int i;
	DictionaryUserXML* data = (DictionaryUserXML*)userData;
	
	if (data->inUser) {
		if (strcmp(el, "mission") == 0) {
			DataMission m;
			for (i = 0; attr[i]; i += 2) {
				if (strcmp(attr[i], "name") == 0) {
					m.directory = attr[i+1];
				}
				if (strcmp(attr[i], "level") == 0) {
					m.level = atoi(attr[i+1]);
				}
			}
			data->auxUser->addMission(m);
		}
		if (strcmp(el, "my-mission") == 0) {
			DataMission m;
			for (i = 0; attr[i]; i += 2) {
				if (strcmp(attr[i], "name") == 0) {
					data->auxUser->addMyMission(attr[i+1]);
				}
			}
		}
	} else {
		if (strcmp(el, "user") == 0) {
			data->inUser = true;
			for (i = 0; attr[i]; i += 2) {
				if (strcmp(attr[i], "name") == 0) {
					data->auxUser = new User(attr[i+1]);
				}
			}
		}
	}
}

static void endUserXML(void *userData, const char *el)
{
	DictionaryUserXML* data = (DictionaryUserXML*)userData;
	
	if (strcmp(el, "user") == 0) { 
		Users::GetInstance()->addUser(data->auxUser);
		data->inUser = false;
	}
	
}
	
void parseUserXML(char fileXML[128]) {
	char buffer[8192];
	int done;
	
	DictionaryUserXML data;
	data.inUser = false;
	
	XML_Parser p = XML_ParserCreate(NULL);
	if (! p) {
		printf("It could not have sufficient memory parser\n");
	}

	XML_SetUserData(p, &data);	
	XML_SetElementHandler(p, startUserXML, endUserXML);

	FILE *file = fopen(fileXML, "r");
	if(!file)
		printf("Error opening file XML\n");
	
	do
	{
		size_t len = fread(buffer, 1, sizeof(buffer), file);
		done = len < sizeof(buffer);
		if(!XML_Parse(p, buffer, len, done)){
			printf("Error making the parse\n");
		}
			//parse_error(&data, XML_ErrorString(XML_GetErrorCode(data.parser)));
	}
	while(!done);
	fclose(file);
}
