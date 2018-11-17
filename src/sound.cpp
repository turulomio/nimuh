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
 

#include "sound.h"
namespace Martian {
	
	/*****************************
	**
	** CLASE SOUND
	**
	******************************/	

	map<string, int> Sound::porcentVolumeByCategory;
		
	Sound::Sound() {
		name = "";
		isCommon = false;
		category = "default";
		currentChannel = 1;
		volume = 128;
	}
	
	Sound::~Sound () {
		unLoad();
	}
	
	void Sound::unLoad()
	{
		if (name!="null") {
			Mix_FreeChunk(sound);
			sound = NULL;
		}
	}
	
	int Sound::getPorcentVolumeByCategory(string cat) { 
		static map<string, int>::iterator it;
		bool hasCat = false;
		for (it=porcentVolumeByCategory.begin(); it!=porcentVolumeByCategory.end(); ++it) {
			if ((*it).first==cat) {
				hasCat = true;
			}
		}
		int vol = 0;
		if (hasCat) {
			vol = porcentVolumeByCategory[cat]; 
		} else {
			vol = porcentVolumeByCategory["default"]; 
		}
		if (vol<0) vol = 0;
		return vol;
	}
	
	void Sound::stop(int ms) { 
		if (name!="null") {
			if (Mix_FadingChannel(currentChannel) == MIX_NO_FADING) {
				Mix_FadeOutChannel (currentChannel, ms); 
			}
		}
	}
	 
	/*****************************
	**
	** CLASE SOUNDS
	**
	******************************/	
	
	Sounds* Sounds::instance = NULL;

	Sounds::Sounds() {
	}
	
    Sounds* Sounds::GetInstance () {
    	if ( instance == NULL ) {
    		instance = new Sounds();
			instance->addSound("null", "", "", true);
    	}
    	return instance;	
    }
	
	Sounds::~Sounds () {
		unLoad();
	}
	
	void Sounds::init()
	{
		if (Mix_OpenAudio (44100, AUDIO_S16, 2, 4096) < 0) {
			printf ("Can't open SDL_MIXER: %s\n", SDL_GetError());
		}
		Mix_AllocateChannels(16);
		
		Sound::setPorcentVolumeByCategory("default", 100);
		
	}
	
	void Sounds::addSound(string name, string category, string sound, bool coommon) { 
		
		Mix_Chunk *chunck = Mix_LoadWAV (sound.c_str());
		if ( ( chunck != NULL ) || (name == "null") ) {
			Sound* s = new Sound(); 
			s->setCommon(coommon);
    		s->setName(name); 
    		if (category !="") s->setCategory(category); 
    		s->setSound(chunck); 
    		sounds.push_back(s); 
		} else {
    		printf ("Sound don't load: %s\n", Mix_GetError());
        }
	}
	
	bool Sounds::existSound(string name) {
		int i;
		for (i=0; i<(int)sounds.size(); i++) {
			if (sounds[i]->getName() == name) {
				return true;
			}
		}
		return false;
	}
	
	Sound* Sounds::getSound(string name) {
		int i;
		for (i=0; i<(int)sounds.size(); i++) {
			if (sounds[i]->getName() == name) {
				return sounds[i];
			}
		}
		printf("Sound: %s don't found\n", name.c_str());
		return getSound("null");
	}
	
	bool Sounds::removeSound(string name) {
		int i;
		int pos = -1;
		for (i=0; i<(int)sounds.size(); i++) {
			if (sounds[i]->getName() == name) {
				pos = i;
			}
		}
		if (pos!=-1) {
			//delete sounds[pos];
			vector<Sound*>::iterator it;
			it = sounds.begin();
			sounds.erase(it+pos);
			return true;
		}
		return false;
	}
	
	void Sounds::stopAll()
	{
		int i;
		for (i=0; i<(int)sounds.size(); i++) {
			sounds[i]->stop();
		}
	}
	
	void Sounds::stopByCategory(string c) {
		int i;
		for (i=0; i<(int)sounds.size(); i++) {
			if (sounds[i]->getCategory() == c) {
				sounds[i]->stop();
			}
		}
	}
	
	void Sounds::unLoad()
	{
		stopAll();
		int i;
		for (i=(int)sounds.size()-1; i>=0; i--) {
			if (!sounds[i]->getCommon()) {
				delete sounds[i];
				sounds.erase(sounds.begin()+i);
			}
		}
		
	}
	
	void Sounds::unLoadAll()
	{
		stopAll();
		int i;
		for (i=0; i<(int)sounds.size(); i++) {
			delete sounds[i];
		}
		
		sounds.clear();
		
	}
	
	
}
