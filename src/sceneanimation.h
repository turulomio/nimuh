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

#ifndef SCENEANIMATION_H_
#define SCENEANIMATION_H_

#include <SDL.h>
#include <SDL_mixer.h>
#include "defines.h"
#include "elements.h"
#include "joystick.h"
#include "font.h"
#include "timer.h"
#include "language.h"
#include "hash.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <string>

#include <cmath>
#include <iostream>
#include <vector>

using namespace std;

namespace Martian {
	
	#define SCENEANIMATION_MAIN 0
	
	class GroupScene;
	class Fonts;
	class SceneAnimation;
	class ObjectAnimation;
	class SoundAnimation;
	
	void parseXMLAnimation(char fileXML[128], SceneAnimation *s);
	
	int nElementsXMLAnimation(char fileXML[128]);
	
	typedef struct
	{
		SceneAnimation *scene;
		ObjectAnimation *aux;
		SoundAnimation *auxSound;
		bool inSound;
		bool inElement;
		bool inFrames;
		bool inAnimation;
		string nameAnimation;
		bool inAction;
		bool inActionOnClick;
		bool todoBorder;
		int rBorder, gBorder, bBorder, sizeBorder, paddingBorder;
		bool showBorder;
		bool todoBackground;
		int rBg, gBg, bBg, paddingBg;
		bool showBackground;
	} AnimationXML;
	
	typedef struct
	{
		int nElements;
	} ElementsAnimationXML;
	
	
	typedef struct
	{
		string type;
		int cycle;
	} ShowHideElement;
	
	class ActionAnimation {
		
	private:
		map<string, string> parameters;
	
	public:
		string nameObjetive;
		string function;
		int cycle;
		int cyclesRepeat;
	
		ActionAnimation();
		ActionAnimation(string f, int t);
		void addParameter(string name, string value) { parameters[name] = value; }
		string getParameter(string name);
		
		void setTime(int t) { cycle = Converter::GetInstance()->ml2cycles(t); }
		void setTimeRepeat(int t) { cyclesRepeat = Converter::GetInstance()->ml2cycles(t); }
		
		bool existParameter(string name);
		
	};
		
	class ObjectAnimation {
		
	private:
		AnimatedElement *elem;
		Button *button;
		string name;
		string type;
	
	public:
		
		vector<ActionAnimation*> actions;
		vector<ActionAnimation*> actionsOnClick;
	
		ObjectAnimation();
		~ObjectAnimation();
		void setType(string t);
		string getType() { return type; }
		void setName(string n) { name = n; }
		string getName() { return name; }
		AnimatedElement* getElement();
		void addAction(ActionAnimation* action) { actions.push_back(action); }
		void addActionOnClick(ActionAnimation* action) { actionsOnClick.push_back(action); }
		
		vector<ActionAnimation*> verifyActions(int cycle);
		
		void unLoad();
		
	};
	
	class SoundAnimation {
		
	private:
		string name;
		string category;
		string file;
	
	public:
		
		vector<ActionAnimation*> actions;
	
		SoundAnimation();
		~SoundAnimation();
		void setFile(string f) { file = f; }
		string getFile() { return file; }
		void setName(string n) { name = n; }
		string getName() { return name; }
		void setCategory(string c) { category = c; }
		string getCategory() { return category; }

		void addAction(ActionAnimation* action) { actions.push_back(action); }
		
		vector<ActionAnimation*> verifyActions(int cycle);

	};
	
	class SceneAnimation : public Scene {
		
	protected:
		string directory;
		int cycles;
		string nameSceneWhenScape;
		vector<ObjectAnimation*> objectsanimation;
		vector<SoundAnimation*> soundsanimation;

		ParticlesSystem *stars;
		bool drawStar;
		vector<ShowHideElement> showHideStar;
		
	public:
        
		ProgressBar *pb;
		bool drawProgressBar;
	
		SceneAnimation();
		~SceneAnimation();
	
		string replace(string chain);
	
		void createStars(string f);
		void addShowHideStar(ShowHideElement s) { showHideStar.push_back(s); }
	
		void setCycles (int c) { cycles = c; }
		int getCycles () { return cycles; }
		
		void setDirectory (string d) { directory = d; }
		string getDirectory () { return directory; }
		void setNameSceneWhenScape (string n) { nameSceneWhenScape = n; }
		string getNameSceneWhenScape () { return nameSceneWhenScape; }
		void load();
		void addObjectAnimation(ObjectAnimation *o) { objectsanimation.push_back(o); }
		ObjectAnimation* getObjectAnimation(string name);
		
		void addSoundAnimation(SoundAnimation *s);
		SoundAnimation* getSoundAnimation(string name);

		void makeAction_Object(ObjectAnimation *obj, ActionAnimation* act);
		
		void makeAction_Sound(SoundAnimation *obj, ActionAnimation* act);
			
		/*********************
		* BUTTONS
		**********************/
		void verifyClickElements_Main();
		void verifyOverElements_Main();
		/*********************
		* SCENES
		**********************/
		bool drawScene ();
		
		void drawSceneMain ();
		void drawSceneMainByIndexZ(int z);
		
		/*********************
		* CONTROL
		**********************/
		void unLoad();
		
	};
	
}

#endif /* SCENEANIMATION_H_ */
