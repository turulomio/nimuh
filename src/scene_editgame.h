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

#ifndef SCENEEDITGAME_H_
#define SCENEEDITGAME_H_

#include "martian.h"
#include "scene.h"
#include "class_editgame.h"
#include "class_game.h"


#include <dirent.h> 

#define SCENE_EDITGAME_MAIN 0
#define SCENE_EDITGAME_ADDOBJECT 1
#define SCENE_EDITGAME_EDITFOOD 2
#define SCENE_EDITGAME_EDITINFO 3
#define SCENE_EDITGAME_CLEAN 4
#define SCENE_EDITGAME_HELP 5
#define SCENE_EDITGAME_ADDINFOTOWN 6

#define SCENE_EDITGAME_ADDOBJECT_GAME 0
#define SCENE_EDITGAME_ADDOBJECT_PERSONAL 1
#define SCENE_EDITGAME_ADDOBJECT_TEXT 2

#define SCENE_EDITGAME_EDITINFO_MAIN 0
#define SCENE_EDITGAME_EDITINFO_DATA 1
#define SCENE_EDITGAME_EDITINFO_MUSIC 2

using namespace std;
using namespace Martian;

class SceneEditGame;

class InfoButton : public Group  {

private:
	Element *bg;
	Element *title;
	Button *bEdit, *bDelete;
	int indexz;
	int index;

public:
	InfoButton ();
	~InfoButton();

	void setTitle(string t);

	void setIndex (int i);
	int getIndex () { return index; }
	
	void setIndexZ (int z) { indexz = z; }
	int getIndexZ () { return indexz; }
	
	void draw();
	
	void onOver();
	
	void unLoad();
	
	void verifyClick(SceneEditGame *sc);

};

class SceneEditGame : public Scene {
	
private:
	int nElmHelp;

public:
		
	Element *multiLanguageNoSupport;

	VectorColors *vcolorsWall, *vcolorsTextInWall;
       
	Entry *missionName;
	Entry *nameAuthor;

	Entry *levelName;
	Entry *provinceName;

	Button *bInfoMain, *bInfoData, *bInfoMusic;
	
	SelectButton *typeButtonInfoTown;
	Entry *eTitleInfoTown;
	Entry *taInfoTown;

	ListView *dataInfo;
	Element *noExistInfoTown;
	int indexEditInfoTown;
	Button *bAddInfo;

	RadioButton *radMusic0, *radMusic1, *radMusic2, *radMusic3;

	int pageEditInfo;

	RadioButton *bNimuh, *bEnemy1, *bEnemy2, *bEnemy3, *bWallRight, *bWallBottom, *bDoor;
	RadioButton *bBlackHole1, *bBlackHole2, *bTrap, *bKey, *bDoorKey, *bEat;

	Element *menuText;
	MarqueeElement *menuTown;

	SelectButton *typeBoard, *typeFloor, *typeWall, *typeTiled, *typeTerrain, *colorWall, *nTilesClosed, *typePavement, *typeWallScenary;

	Group *menu;
	Element *menuBg;

	Element *frameUp, *frameDown;

	Element *blueLine;

	Group *handTray;
	Element *bgHandTray;
	Button *btHandTray;

	Button *bQuit, *bEditInfo, *bAddObject, *bSave, *bRules, *bClean, *bHelp;

	Element *bgBox;
	Element *bgHelp;
	Element *middleBox;
	Entry *titleFood;
	Entry *textFood;
	
	Element *elmHelp;
	
	Element *titleIndex;
	
	Button *bIndex, *bPrevious, *bNext;

	Button *bHelp1, *bHelp2, *bHelp3, *bHelp4, *bHelp5, *bHelp6, *bHelp7, *bHelp8; 

	Element *infoImageFood;
	
	Button *bAccept, *bCancel;
	
	Button *bCleanScenary, *bCleanBoard, *bCleanReset;
	
	Button *bObjectsGame, *bObjectsPersonal, *bObjectsTexts;
	
	Element *infoObjectsPersonal;

	Element *bgArrow;
	Element *bgButton;
	
	RadioButton *rbTypeClosedWindows, *rbTypeClosedDoors, *rbTypeClosedLights, *rbTypeClosedElements, *rbTypeClosedDecorative;
	RadioButton *rbTypeOpenedNature, *rbTypeOpenedBeach, *rbTypeOpenedBench, *rbTypeOpenedConstruction, *rbTypeOpenedElements;

	ListImage *objectsGame;
	ListImage *objectsPersonal;
	
	RadioButton *rad2d, *rad3d;

	Entry *taText;
	Element *titleTypeTextsInWall;
	SelectButton *typeTextsInWall;
	SelectButton *colorTextsInWall;
	
	RadioButton *radAlignLeftText, *radAlignCenterText, *radAlignRightText;
	
	Button *bInsertText;
		
	Button *bCancelObjects;
	
	int pageAddObject;
	
	void setTextDisplay(int i);
	
	void setPageAddObject(int p) { pageAddObject = p; }
	int getPageAddObject() { return pageAddObject; }
	
	void setPageEditInfo(int p) { pageEditInfo = p; }
	int getPageEditInfo() { return pageEditInfo; }

	SceneEditGame();
	~SceneEditGame();
	void load();
	
	void loadObjectsPersonal ();
	
	void setStatusScene(int s);
		
	void addInfoTown(InformationTown it);
	
	void createInfoButtons();
	
	void previousElmHelp() { if (nElmHelp>=0) { setElmHelp(nElmHelp-1); } }
	void nextElmHelp() { if (nElmHelp<elmHelp->getFrames()-1) { setElmHelp(nElmHelp+1); } }
	void setElmHelp(int i);

	
	/*********************
	* BUTTONS
	**********************/
	void verifyClickElements_Main();
	void verifyOverElements_Main();
	void verifyClickElements_AddObject();
	void verifyOverElements_AddObject();
	void verifyClickElements_EditFood();
	void verifyOverElements_EditFood();
	void verifyClickElements_EditInfo();
	void verifyOverElements_EditInfo();
	void verifyClickElements_AddInfoTown();
	void verifyOverElements_AddInfoTown();
	void verifyClickElements_Clean();
	void verifyOverElements_Clean();
	void verifyClickElements_Help();
	void verifyOverElements_Help();
	/*********************
	* ESCENES
	**********************/
	bool drawScene ();
	
	void drawSceneMain ();
	void drawSceneMainByIndexZ(int z);
	
	void drawSceneAddObject ();
	void drawSceneAddObjectByIndexZ(int z);
	
	void drawSceneEditFood ();
	void drawSceneEditFoodByIndexZ(int z);
	
	void drawSceneEditInfo ();
	void drawSceneEditInfoByIndexZ(int z);
	
	void drawSceneAddInfoTown ();
	void drawSceneAddInfoTownByIndexZ(int z);
	
	void drawSceneClean ();
	void drawSceneCleanByIndexZ(int z);
	
	void drawSceneHelp ();
	void drawSceneHelpByIndexZ(int z);
	
	/*********************
	* CONTROL
	**********************/
	void unLoad();
};
	


#endif /* SCENEEDITGAME_H_ */
