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

#ifndef SOUND_H_
#define SOUND_H_

#include "config.h"
#include <SDL.h>
#include <SDL_mixer.h>
#include <expat.h>
#include <map>
#include <string>
#include <cmath>
#include <iostream>
#include <vector>
#include <map>
#include "defines.h"

using namespace std;

namespace Martian {
	
	class Sound {
	public :
		Sound ();
	
		bool isCommon;
	
		void setSound(Mix_Chunk* s) { sound = s; }
		Mix_Chunk* getSound() { return sound; }
		
		void setVolume(int vol) { volume = vol; }
			
		void setCommon(bool c) { isCommon = c; }
		bool getCommon() { return isCommon; }
		
		void setName(string n) { name = n; }
		string getName() { return name; }
		
		void setCategory(string c) { category = c; }
		string getCategory() { return category; }
		
		void setCurrentChannel(int c) { currentChannel = c; }
		int getCurrentChannel() { return currentChannel; }
		
		void play(int channel, int loops) { if (name!="null") { setVolumeByPorcent(); setCurrentChannel(channel); Mix_PlayChannel (channel, sound, loops); } }
		void play(int channel, int loops, int ms) { if (name!="null") { setVolumeByPorcent(); setCurrentChannel(channel);  Mix_FadeInChannel (channel, sound, loops, ms); } }
		
		void stop() { if (name!="null") { Mix_HaltChannel(currentChannel); } }
		void stop(int ms);
		
		void pause() { Mix_Pause(currentChannel); }
		int playing() { return Mix_Playing(currentChannel); }
		int paused() { return Mix_Paused(currentChannel); }
		
		void unLoad();
				
		static void setPorcentVolumeByCategory(string cat, int porcent) { porcentVolumeByCategory[cat] = porcent; }
		static int getPorcentVolumeByCategory(string cat);
		
		static map<string, int> porcentVolumeByCategory;
		
		~Sound ();
	private :
		void setVolumeByPorcent() { Mix_VolumeChunk (sound, (volume*getPorcentVolumeByCategory(category))/100); }
		string name;
		string category;
		int currentChannel;
		int volume;
		Mix_Chunk* sound;
		
	};
	
	class Sounds {
	public :
		static Sounds * GetInstance ();
		
	
		void addSound(string name, string sound) { addSound(name, "", sound); }
		void addSound(string name, string category, string sound) { addSound(name, category, sound, false); }
		void addSound(string name, string category, string sound, bool coommon);
	
		void addSoundFromData(string name, string sound) { addSoundFromData(name, "", sound); }
		void addSoundFromData(string name, string category, string sound) { addSound(name, category, string(DATA_DIR) +"/"+ sound, false); }
		void addSoundFromData(string name, string category, string sound, bool coommon) { addSound(name, category, string(DATA_DIR) +"/"+ sound, coommon); }
		
		bool removeSound(string name);
		Sound* getSound(string name);
		bool existSound(string name);

		void stopAll();
		void stopByCategory(string c);
		void unLoad();
		void unLoadAll();
		
		void stopChannel(int channel) { Mix_HaltChannel(channel); }
			
		void init();
			
		~Sounds ();
			
	private :
		static Sounds *instance;
		Sounds ();
		vector<Sound*> sounds;
		
	};
	
}

#endif /* SOUND_H_ */
