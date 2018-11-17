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

#ifndef SCENE_H_
#define SCENE_H_

#include <SDL.h>
#include <SDL_mixer.h>
#include "defines.h"
#include "elements.h"
#include "joystick.h"
#include "font.h"
#include "timer.h"
#include "language.h"
#include "hash.h"
#include "chronometer.h"
#include "cursor.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <string>

#include <cmath>
#include <iostream>
#include <vector>

using namespace std;

namespace Martian {
	
	class GroupScene;
	class Fonts;
	class Button;
	class Entry;
	class Chronometer;
	class Element;
	class World;
	
	class Debug {
		
	private:
		Debug ();
		bool todo;
		static Debug *instance;
	
	public:
		static Debug * GetInstance ();
		void writeText (string text) { if (todo) printf("%s\n", text.c_str()); }
		
		void setDebug (bool d) { todo =  d; }
		bool getDebug () { return todo; }
		
		~Debug ();		
	};
	
	class Scene {
		
	protected:
		Uint8 *keys;
		int identificator;
		string nextScene;
		bool quit;
		bool isLoad;
		GroupScene* groupScene;
				
		static int nScreenShot;
		bool saveImage;
		int levelSaveImage;
		Element *imgOnSaveImg;
		Element *elmImgSave[NELMIMGSAVE];

		int statusScene;
		int returnSceneFromMessage;
	
		string nextSceneWhenWait;
		int msWhenWait;
	
		int currentFPS;
		Element * elCurrentFPS;
		
		World* world;
		
		bool drawCursor;
			
	public:
	
		void setDrawCursor(bool dc) { drawCursor = dc; }
		bool getDrawCursor() { return drawCursor; }
	
		Scene();
		~Scene();
	
		void clearElmImgSave ();
	
		void setCurrentFPS ();
		
		void setWorld (World* w) { world = w; }
		World* getWorld () { return world; }
	
		static void createStaticsElements ();
	
		Element* getElmImgSave(int n) { if (n<NELMIMGSAVE) return elmImgSave[n]; else return elmImgSave[0]; }
		
		// messages
		static Element *msg_title, *msg_text, *msg_bgMessage, *msg_bgAlert;
		static bool hasMsg_bg;
		static bool hasMsg_title;
		static int posXBAcceptInAlert, posXBCancelInAlert;
		static Entry *msg_entry;
		static string msg_fontTitle, msg_fontText, msg_fontButtons, msg_fontEntry;
		static Button *msg_bAccept, *msg_bCancel;
		void (*OnClickButtonOnAlert)(Scene*, Button*, string data);
		void (*OnClickButtonOnInput)(Scene*, Button*, string data);
	
		void colorImgOnSaveImg (int alpha, int r, int g, int b);
	
		void goToScene(string ns) { setQuit(true); setNextScene(ns);	}
		void goToScene(string ns, int ms) { goToScene(ns, ms, SCENE_TRANSITION_NO); }
		void goToScene(string ns, int ms, int transition);
	
		void setStatusScene(int s) { statusScene = s; }
		int getStatusScene() { return statusScene; }
		
		int getReturnSceneFromMessage() { return returnSceneFromMessage; }
		
		void setStatusSceneWithReturnSceneFromMessage() { statusScene = returnSceneFromMessage; }
	
		void saveImg (int level, bool withImgOnSaveImg);
		void saveScreenShot();
	
		void setSaveImage(bool s) { clearElmImgSave (); levelSaveImage = 0; saveImage = s; }
		void setSaveImage(bool s, int l) { clearElmImgSave (); levelSaveImage = l; saveImage = s; }
		void verifySaveImage();
	
		void setId(int i) { identificator = i; }
		int getId() { return identificator; }
		void setNextScene(string sc) { nextScene = sc; }
		string getNextScene() { return nextScene; }
		void setQuit(bool q) { quit = q; }
		bool getQuit() { return quit; }
		void setIsLoad(bool l) { isLoad = l; }
		bool getIsLoad() { return isLoad; }
		
		GroupScene* getGroupScene() { return groupScene; }
		
		void initialize();
		void load();
		
		void drawLastElements();

		/*********************
		* BUTTONS
		**********************/
		void verifyClickElements_Main();
		void verifyOverElements_Main();
		
		void verifyClickElements_MessageBox();
		void verifyOverElements_MessageBox();
		
		void verifyClickElements_Alert();
		void verifyOverElements_Alert();
		
		void verifyClickElements_Input();
		void verifyOverElements_Input();
		
		/*********************
		* SCENES
		**********************/
		bool drawScene ();
		
		void drawSceneMain ();
		void drawSceneMainByIndexZ(int z);
		
		void drawCommonsScene ();
		
		void drawSceneWaitingNextScene ();
		
		void showMessageBox (string tit, string txt, int returnScene);
		void drawSceneMessageBox ();
		void drawSceneMessageBoxByIndexZ(int z);
		
		void showInput (string tit, string txt, void (*function)(Scene*, Button*, string data), int returnScene) { showInput(tit, txt, -1, function, returnScene); }
		void showInput (string tit, string txt, int maxLetters, void (*function)(Scene*, Button*, string data), int returnScene);
		void drawSceneInput ();
		void drawSceneInputByIndexZ(int z);
		
		void showAlert (string tit, string txt, void (*function)(Scene*, Button*, string data), int returnScene);
		void drawSceneAlert ();
		void drawSceneAlertByIndexZ(int z);
		
		/*********************
		* CONTROL
		**********************/
		void verifyKeys(int est);
		void unLoad();
		
		void unLoadCommons();
		
	};
	
}

#endif /* SCENE_H_ */
