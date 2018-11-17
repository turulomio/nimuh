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

#ifndef SCENEGAME_H_
#define SCENEGAME_H_

#include "martian.h"
#include "scene.h"
#include "user.h"
#include "class_game.h"
#include "sceneanimation.h"

#define SCENE_GAME_MAIN 0
#define SCENE_GAME_WINNING 1
#define SCENE_GAME_WIN 2
#define SCENE_GAME_LOST 3
#define SCENE_GAME_CAPTURED 4
#define SCENE_GAME_OPTIONS 5
#define SCENE_GAME_FINISH 6
#define SCENE_GAME_STARTTRAY 7
#define SCENE_GAME_TRAY 8
#define SCENE_GAME_HELP 9
#define SCENE_GAME_ENDANIMATION 10
#define SCENE_GAME_HELPFIRSTLEVEL 11

using namespace std;
using namespace Martian;

class SceneGame : public Scene {
	
private:
    Button *bQuit, *bReset, *bOption, *bNext, *bPrevious;
	Button *bAccept, *bCancel;
	Element *frameUp, *frameDown;
	
	Button *bRetry, *bLeave, *bContinue, *bBack;

	MarqueeElement *nameProvince, *nameTown;

	Element *titleInfoTray, *textInfoTray, *drawFood;

    Element *windowLost, *windowWin, *windowFinish;
    
	Element *textInWindows, *textInWindowsFinal;

	Group *menu;

	Element *bgMenu;
	AnimatedElement *eyeRight, *eyeLeft;

	Element *bgInfo;
	Button *bAcceptInfo;
	
	bool hasHelp;
	Element *imageHelp, *titleHelp, *textHelp;
	
	bool active;
	
	int indexMusicActive;
		
	SceneAnimation *s_animend;
	   
public:
	
	bool animationEnd;

	bool hasEyeInformation;

	void goToNextLevel();

	void setAnimationEnd (string a);

	void setTypeMusic (int t) { indexMusicActive = t; }
	int getTypeMusic () { return indexMusicActive; }
		
	bool getActive() { return active; }
	
	void verifyEyeInformation();
	
	void loadMusic (int t);
	void loadHelp (string name);
	
	Slide *imageEyeRight, *imageEyeLeft;
	
	Element *levelStatus;
	ChronometerElement *chronometer;
	
	bool hasHelpFirstLevel;
	bool showedHelpFirstLevel;
	Slide *helpFirstLevel;
	Button *bLeftFirstLevel, *bRightFirstLevel;
	
	Element *bgOptions;
	Element *titleVolumeMusics, *titleVolumeEffects, *titleTypeMusic;
	SelectButton *volumeMusics, *volumeEffects, *typeMusic;
	CheckButton *cbHelpActived;

	SceneGame();
	~SceneGame();
	void setStatusScene(int s);
	void load();
	
	void clear();
	
	void createHelpFirstLevel();
	
	Sound* getMusicGame() { return Sounds::GetInstance()->getSound("musicgame"); }

	/*********************
	* BUTTONS
	**********************/
	void verifyClickElements_Main();
	void verifyOverElements_Main();
	
	void verifyClickElements_Options();
	void verifyOverElements_Options();
	
	void verifyClickElements_Lost();
	void verifyOverElements_Lost();
	
	void verifyClickElements_Win();
	void verifyOverElements_Win();
	
	void verifyClickElements_Finish();
	void verifyOverElements_Finish();
	
	void verifyClickElements_Tray();
	void verifyOverElements_Tray();
	
	void verifyClickElements_Help();
	void verifyOverElements_Help();
	
	void verifyClickElements_HelpFirstLevel();
	void verifyOverElements_HelpFirstLevel();
	
	/*********************
	* ESCENES
	**********************/
	bool drawScene ();

	void drawSceneMain ();
	void drawSceneMainByIndexZ(int z);
	
	void drawSceneOptions ();
	void drawSceneOptionsByIndexZ(int z);

	void drawSceneWin ();
	void drawSceneWinByIndexZ(int z);

	void drawSceneLost ();
	void drawSceneLostByIndexZ(int z);
	
	void drawSceneFinish ();
	void drawSceneFinishByIndexZ(int z);

	void drawSceneTray ();
	void drawSceneTrayByIndexZ(int z);
	
	void drawSceneHelp ();
	void drawSceneHelpByIndexZ(int z);
	
	void drawSceneHelpFirstLevel ();
	void drawSceneHelpFirstLevelByIndexZ(int z);
	
	/*********************
	* CONTROL
	**********************/
	void unLoad();
};
	


#endif /* SCENEGAME_H_ */
