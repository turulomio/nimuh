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
 
#include "missions.h"

/*****************************
**
** CLASE Level
**
******************************/	

Level::Level(string d, string n) {
	directory = d;
	name = n;
	typeScenary = SCENARY_CLOSED;
}

string Level::getPath() { 
	return parentMission->getPath() + directory; 
}

bool Level::existFile(string f) { 
    string file = getPath() + "/" + f;
	return WorkingData::GetInstance()->existFile(file);
}



/*****************************
**
** CLASE Mission
**
******************************/	

Mission::Mission(string d, string n) {
	directory = d;
	name = n;
	cursor = 0;
	isUserMission = true;
}

string Mission::getPath() {
	string d="";
	if (isUserMission) {
		d += Hash::getPathData() + "missions/" + directory + "/";
	} else {
		d += string(DATA_DIR) + "/adventure/" + directory + "/";
	}
	return d;
}

bool Mission::addLevel(Level* l) { 
	for (int i=0; i<(int)levels.size(); i++) {
		if ( (getLevel(i)->getName()==l->getName()) || (getLevel(i)->getDirectory()==l->getDirectory()) ){ 
			return false; 
		} 
	}
    l->setParentMission(this);
	levels.push_back(l); 

	
	return true; 
}

bool Mission::upLevel(int l) {
	if (l>0) {
		Level* auxLevel = levels[l];
		levels[l] = levels[l-1];
		levels[l-1] = auxLevel;
		//levels.erase(levels.begin()+l);
		//levels.insert(levels.begin()+l, 1, auxLevel);
		return true;
	} else {
		return false;
	}
}

bool Mission::downLevel(int l) {
	if (l<(int)levels.size()-1) {
		Level* auxLevel = levels[l];
		levels[l] = levels[l+1];
		levels[l+1] = auxLevel;
		//levels.erase(levels.begin()+l);
		//levels.insert(levels.begin()+l+1, 1, auxLevel);
		return true;
	} else {
		return false;
	}
}

void Mission::removeLevel(int i) { 
	if (getLevel(i)!=NULL) {
		WorkingData::GetInstance()->deleteDirectory(getLevel(i)->getPath());
		levels.erase(levels.begin()+i); 
	}
}

void Mission::load() {
	string file = "";
	if (!getIsUserMission()) {
		file = (string)DATA_DIR + "/adventure/" + getDirectory() + "/mission.xml";
	} else {
		file = Hash::getPathData() + "missions/" + getDirectory() + "/mission.xml";
	}
	parseAddLevelsXML((char*)file.c_str(), this);
}

void Mission::save() {

	string file = Hash::getPathData() + "missions/" + getDirectory() + "/mission.xml";
	
	string chainFile = "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n<mission name=\"" + getName() + "\">\n";
	
	chainFile += "\t<author name=\"" + getNameAuthor() + "\" />\n";
	
	chainFile += "\t<levels>\n";
	
	MoveFirst();
	
	while (!isEOF()) {
		
		chainFile += "\t\t<level directory=\"" + getLevel()->getDirectory() + "\" />\n";
		
		MoveNext();
	}
	
	
	chainFile += "\t</levels>\n";
	
	chainFile += "</mission>\n";

    WorkingData::GetInstance()->createFile(file, chainFile, true);
		
}

/*****************************
**
** CLASE Misions
**
******************************/	

Missions* Missions::instance = NULL;

Missions::Missions() {
	cursor = 0;
	directory = "";
	currentMission = NULL;
	currentLevel = NULL;
}

Missions* Missions::GetInstance () {
	if ( instance == NULL ) {
		instance = new Missions();
	}
	return instance;
}

bool Missions::setCurrentMissionAndLevel(int i) {
	if ( getMission( i ) != NULL ) {
		currentMission = getMission( i );
		if (currentMission->getNLevels()>0) {
			int level = Users::GetInstance()->getCurrentUser()->getLevelInMission(currentMission->getDirectory());
			if (level<0) {
				Users::GetInstance()->getCurrentUser()->addMission(currentMission->getDirectory(), 0);
				Users::GetInstance()->save();
				currentLevel = currentMission->getLevel(0);
			} else {
				currentLevel = currentMission->getLevel(level);
			}
			return true;
		}
	}
	return false;
}

bool Missions::setCurrentMissionAndLevel(string name) {
	for (int i=0; i<(int)missions.size(); i++) {
		if (getMission(i)->getDirectory()==name) { 
			return setCurrentMissionAndLevel(i);
		} 
	}
	return false; 
}

bool Missions::setCurrentLevel() {
	if (currentMission->getNLevels()>0) {
		int level = Users::GetInstance()->getCurrentUser()->getLevelInMission(currentMission->getDirectory());
		if (level<0) {
			Users::GetInstance()->getCurrentUser()->addMission(currentMission->getDirectory(), 0);
			Users::GetInstance()->save();
			currentLevel = currentMission->getLevel(0);
		} else {
			currentLevel = currentMission->getLevel(level);
		}
		return true;
	}
	return false;
}


string Missions::pathXMLLevel() {
	return currentLevel->getPath()+"/level.xml";
	/*if (currentMission->getDirectory()=="andalucia") {
		return (string)DATA_DIR+"/andalucia/"+currentLevel->getDirectory()+"/level.xml";
	} else {
		return Hash::getPathData()+"/missions/"+currentMission->getDirectory()+"/"+currentLevel->getDirectory()+"/level.xml";
	}*/
}

bool Missions::addMission(Mission* m) { 
	for (int i=0; i<(int)missions.size(); i++) {
		if ( (getMission(i)->getDirectory()==m->getDirectory()) || (getMission(i)->getName()==m->getName()) ) { 
			return false; 
		} 
	}
	missions.push_back(m); 
	return true; 
}

Mission* Missions::getCurrentMission() { 
	int i = atoi(Options::GetInstance()->getValue("mission").c_str());
	return ( (i<0) || (i>(int)missions.size()-1) )?NULL:missions[i]; 
}

		
void Missions::load() { 
     
	directory = Hash::getPathData() + "missions";
	
	WorkingData::GetInstance()->createDirectory(directory);
	
	Mission *mAndalucia = new Mission("andalucia", "Nimuh en busca del tesoro andaluz");
	mAndalucia->setIsUserMission(false);
	mAndalucia->setNameAuthor("caninostudios");
	mAndalucia->load();
	addMission(mAndalucia);
	
	DIR *pdir;
	struct dirent *pent;
	
	pdir=opendir(directory.c_str());
	if (!pdir){
		printf ("Don't open directoty of missions: %s\n", directory.c_str());
	} else {
		while ((pent=readdir(pdir))) {
			if ( !(strcmp(pent->d_name, ".")==0) &&
					!(strcmp(pent->d_name, "..")==0) ) {
					string file = Hash::getPathData() + "missions/" + pent->d_name + "/mission.xml";
					DictionaryNameMissionXML data = parseNameMissionXML((char*)file.c_str());
					Mission *m = new Mission(pent->d_name, data.name);
					m->setNameAuthor(data.nameAuthor);
					m->load();
					addMission(m);
			}
		}
		closedir(pdir);
	}
	
}

void Missions::save() { 
	
	for (int i=0; i<(int)missions.size(); i++) {
        if (missions[i]->getIsUserMission()) {
            // verify directory missions
    		if (!existDirectoryOfMission(missions[i]->getDirectory())) {
                                                                       
    			WorkingData::GetInstance()->createDirectory(Hash::getPathData() + "missions/" + missions[i]->getDirectory());

    			string file = Hash::getPathData() + "missions/" + missions[i]->getDirectory() + "/mission.xml";
    			
    			string chainFile = "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n<mission name=\"" + missions[i]->getName() + "\">\n";
    			
    			chainFile += "\t<author name=\"" + missions[i]->getNameAuthor() + "\"/>\n";
    			
    			chainFile += "</mission>\n";
    			
    			WorkingData::GetInstance()->createFile(file, chainFile, true);
    		}
    		
    		// verify directory levels
    		
    		missions[i]->MoveFirst();
    		
    		while (!missions[i]->isEOF()) {
    		
        		if (!existDirectoryOfLevel(missions[i]->getDirectory(), missions[i]->getLevel()->getDirectory())) {
        		
        		    WorkingData::GetInstance()->createDirectory(Hash::getPathData() + "missions/" + missions[i]->getDirectory() + "/" + missions[i]->getLevel()->getDirectory());
        		    
        		    WorkingData::GetInstance()->createDirectory(Hash::getPathData() + "missions/" + missions[i]->getDirectory() + "/" + missions[i]->getLevel()->getDirectory() + "/objects");
        		    
        		    WorkingData::GetInstance()->createDirectory(Hash::getPathData() + "missions/" + missions[i]->getDirectory() + "/" + missions[i]->getLevel()->getDirectory() + "/photos");
                	
                	string file = Hash::getPathData() + "missions/" + missions[i]->getDirectory() + "/" + missions[i]->getLevel()->getDirectory() + "/level.xml";
                	
                	string chainFileLevel = "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n<level>\n";
                	
                	chainFileLevel += "\t<data>\n";
                	
                	chainFileLevel += "\t\t<town name=\"" + missions[i]->getLevel()->getName() + "\" province=\""+ missions[i]->getLevel()->getProvince() + "\">\n";
                	
                	chainFileLevel += "\t\t</town>\n";
                	
                	chainFileLevel += "\t</data>\n";
                	
					if (missions[i]->getLevel()->getTypeScenary()==SCENARY_CLOSED) {
				    	chainFileLevel += "\t<scenary type=\"closed\">\n";
					} else {
						chainFileLevel += "\t<scenary type=\"opened\">\n";
					}
					
					chainFileLevel += "\t</scenary>\n";
					
					chainFileLevel += "</level>\n";
					
					WorkingData::GetInstance()->createFile(file, chainFileLevel, true);
                	
                }
                
                missions[i]->MoveNext();
                
            } // while
        }
	}
	
}

bool Missions::existDirectoryOfMission(string m) { 

	DIR *pdir;
	struct dirent *pent;
	
	pdir=opendir(directory.c_str());
	if (pdir){
		while ((pent=readdir(pdir))) {
			if (strcmp(pent->d_name, m.c_str())==0) {
				closedir(pdir);
				return true;
			}
		}
		closedir(pdir);
	}
	return false;
}

bool Missions::existDirectoryOfLevel(string m, string l) { 

	DIR *pdir;
	struct dirent *pent;
	
	string d = directory + "/" + m;
	
	pdir=opendir(d.c_str());
	if (pdir){
		while ((pent=readdir(pdir))) {
			if (strcmp(pent->d_name, l.c_str())==0) {
				closedir(pdir);
				return true;
			}
		}
		closedir(pdir);
	}
	return false;
}

/*****************************
**
** XML
**
******************************/

static void startNameMissionXML(void *userData, const char *el, const char **attr) {
	int i;
	DictionaryNameMissionXML* data = (DictionaryNameMissionXML*)userData;
	
	if (strcmp(el, "mission") == 0) {
		for (i = 0; attr[i]; i += 2) {
			if (strcmp(attr[i], "name") == 0) {
				data->name = attr[i+1];
			}
		}
	}
	
	if (strcmp(el, "author") == 0) {
		for (i = 0; attr[i]; i += 2) {
			if (strcmp(attr[i], "name") == 0) {
				data->nameAuthor = attr[i+1];
			}
			if (strcmp(attr[i], "email") == 0) {
				data->emailAuthor = attr[i+1];
			}
		}
	}
}

static void endNameMissionXML(void *userData, const char *el)
{

}
	
DictionaryNameMissionXML parseNameMissionXML(char fileXML[128]) {
	char buffer[8192];
	int done;
	
	DictionaryNameMissionXML data;
	data.name = "";
	data.nameAuthor = "";
	data.emailAuthor = "";
	
	XML_Parser p = XML_ParserCreate(NULL);
	if (! p) {
		printf("It could not have sufficient memory parser\n");
	}

	XML_SetUserData(p, &data);	
	XML_SetElementHandler(p, startNameMissionXML, endNameMissionXML);

	FILE *file = fopen(fileXML, "r");
	if(!file)
		printf("1. Error opening file XML: %s\n", fileXML);
	
	do
	{
		size_t len = fread(buffer, 1, sizeof(buffer), file);
		done = len < sizeof(buffer);
		if(!XML_Parse(p, buffer, len, done)){
			printf("1. Error making the parse\n");
		}
			//parse_error(&data, XML_ErrorString(XML_GetErrorCode(data.parser)));
	}
	while(!done);
	fclose(file);
	
	return data;
}

// level

static void startNameLevelXML(void *userData, const char *el, const char **attr) {
	int i;
	DictionaryNameLevelXML* data = (DictionaryNameLevelXML*)userData;
	
	if (strcmp(el, "town") == 0) {
		for (i = 0; attr[i]; i += 2) {
			if (strcmp(attr[i], "name") == 0) {
				data->name = attr[i+1];
			}
			if (strcmp(attr[i], "province") == 0) {
				data->province = attr[i+1];
			}
		}
	}
	
	if (strcmp(el, "scenary") == 0) {
		for (i = 0; attr[i]; i += 2) {
			if (strcmp(attr[i], "type") == 0) {
				if (strcmp(attr[i+1], "opened") == 0) {
					data->typeScenary = SCENARY_OPENED;
				} else {
					data->typeScenary = SCENARY_CLOSED;
				}
			}
		}
	}	
	
}

static void endNameLevelXML(void *userData, const char *el)
{

}
	
DictionaryNameLevelXML parseNameLevelXML(char fileXML[128]) {
	char buffer[8192];
	int done;
	
	DictionaryNameLevelXML data;
	data.name = "";
	data.province = "";
	data.typeScenary = SCENARY_CLOSED;
	
	XML_Parser p = XML_ParserCreate(NULL);
	if (! p) {
		printf("It could not have sufficient memory parser\n");
	}

	XML_SetUserData(p, &data);	
	XML_SetElementHandler(p, startNameLevelXML, endNameLevelXML);

	FILE *file = fopen(fileXML, "r");
	if(!file)
		printf("2. Error opening file XML: %s\n", fileXML);
	
	do
	{
		size_t len = fread(buffer, 1, sizeof(buffer), file);
		done = len < sizeof(buffer);
		if(!XML_Parse(p, buffer, len, done)){
			printf("2. Error making the parse: %s\n", fileXML);
		}
			//parse_error(&data, XML_ErrorString(XML_GetErrorCode(data.parser)));
	}
	while(!done);
	fclose(file);
	
	return data;
}


// addlevel

static void startAddLevelsXML(void *userData, const char *el, const char **attr) {
	int i;
	DictionaryAddLevelsXML* data = (DictionaryAddLevelsXML*)userData;
	
	if (strcmp(el, "level") == 0) {
		for (i = 0; attr[i]; i += 2) {
			if (strcmp(attr[i], "directory") == 0) {
				string filelevel = data->mission->getPath() + attr[i+1] + "/level.xml";;
				DictionaryNameLevelXML dataLevel = parseNameLevelXML((char*)filelevel.c_str());
				Level *l = new Level (attr[i+1], dataLevel.name);
				l->setProvince(dataLevel.province);
				l->setTypeScenary(dataLevel.typeScenary);
				data->mission->addLevel(l);
			}
		}
	}
	

}

static void endAddLevelsXML(void *userData, const char *el)
{

}
	
void parseAddLevelsXML(char fileXML[128], Mission *m) {
	char buffer[8192];
	int done;
	
	DictionaryAddLevelsXML data;
	data.mission = m;
	
	XML_Parser p = XML_ParserCreate(NULL);
	if (! p) {
		printf("It could not have sufficient memory parser\n");
	}

	XML_SetUserData(p, &data);	
	XML_SetElementHandler(p, startAddLevelsXML, endAddLevelsXML);

	FILE *file = fopen(fileXML, "r");
	if(!file)
		printf("3. Error opening file XML: %s\n", fileXML);
	
	do
	{
		size_t len = fread(buffer, 1, sizeof(buffer), file);
		done = len < sizeof(buffer);
		if(!XML_Parse(p, buffer, len, done)){
			printf("3. Error making the parse\n");
		}
			//parse_error(&data, XML_ErrorString(XML_GetErrorCode(data.parser)));
	}
	while(!done);
	fclose(file);
	
}
