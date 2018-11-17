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

#ifndef SCENECREATEMISSION_H_
#define SCENECREATEMISSION_H_

#include "martian.h"
#include "scene.h"
#include "missions.h"
#include "font.h"

using namespace std;
using namespace Martian;

#define SCENE_CREATEMISSION_MAIN 0
#define SCENE_CREATEMISSION_NEW 1
#define SCENE_CREATEMISSION_LEVELS 2
#define SCENE_CREATEMISSION_NEWLEVEL 3
#define SCENE_CREATEMISSION_HELP 4

class SceneCreateMission;

class ButtonLevel : public Group  {

private:
	Element *bg, *bgNumber;
	Button *title;
	Element *number;
	Button *bEdit, *bUp, *bDown, *bDelete;
	int indexz;
	int index;

public:
	ButtonLevel (string t);
	~ButtonLevel();

	void setNumber (int i);
	void setTitle(string t);

	void setIndex (int i);
	int getIndex () { return index; }

	Button* getButtonUp () { return bUp; }
	Button* getButtonDown () { return bDown; }
	
	void setIndexZ (int z) { indexz = z; }
	int getIndexZ () { return indexz; }
	
	void draw();
	
	void onOver();
	
	void unLoad();
	
	bool verifyClick(SceneCreateMission *sc);

};


class SceneCreateMission : public Scene {
	
private:

	Button* bNewMission;
	Button* bNewLevel;
	Button* bBack;
	Button* bQuit;
	Button* bCreateMission;
	Button* bCreateLevel;
	Button* bPlay;
	Button* bEdit;
	Button* bHelp;
	
	Element *bgCoverFlow, *bgInfoMission, *bgLevels;
	
	Element *textHelp;
	
	Element *bgFormMission, *bgFormLevel;
	Element *titleFormMission, *titleFormLevel;

	Element *nameMissionCover, *authorMissionCover, *nLevelsCover;
	
	Element *frameUpLevels, *frameUp, *frameDown, *faceEnemy1;

	Element *nomission, *nolevels;
    Element *titleMission;

    ParticlesSystem *stars;

	int indexMissionActive;
	
	int nElmHelp;

public:
	Element *bgHelp;
	Element *elmHelp;
	
	Element *titleIndex;
	
	Button *bIndex, *bPrevious, *bNext, * bCancel;

	Button *bHelp1, *bHelp2, *bHelp3, *bHelp4;

	CoverFlow *dataMissions;
	ListView *dataLevel;
	
	Entry *missionName;
	Entry *nameAuthor;
	//Entry *emailAuthor;

	Entry *levelName;
	Entry *provinceName;

	Element *titleTypeScenary;

	RadioButton *tScOpened, *tScClosed;

	SceneCreateMission();
	~SceneCreateMission();
	void load();
	
	void setStatusScene(int s);
	
	string getNameProject(string name);

	void createMissionsButtons();
	
	void createLevelsButtons(Mission *mission);
	
	void previousElmHelp() { if (nElmHelp>=0) { setElmHelp(nElmHelp-1); } }
	void nextElmHelp() { if (nElmHelp<elmHelp->getFrames()-1) { setElmHelp(nElmHelp+1); } }
	void setElmHelp(int i);

	/*********************
	* BUTTONS
	**********************/
	void verifyClickElements_Main();
	void verifyOverElements_Main();

	void verifyClickElements_NewMision();
	void verifyOverElements_NewMision();
	
	void verifyClickElements_Levels();
	void verifyOverElements_Levels();
	
	void verifyClickElements_NewLevel();
	void verifyOverElements_NewLevel();
	
	void verifyClickElements_Help();
	void verifyOverElements_Help();

	/*********************
	* ESCENES
	**********************/
	bool drawScene ();

	void drawSceneMain ();
	void drawSceneMainByIndexZ(int z);
	
	void drawSceneNewMission ();
	void drawSceneNewMissionByIndexZ(int z);
	
	void drawSceneLevels ();
	void drawSceneLevelsByIndexZ(int z);
	
	void drawSceneNewLevel ();
	void drawSceneNewLevelByIndexZ(int z);
	
	void drawSceneHelp ();
	void drawSceneHelpByIndexZ(int z);

	/*********************
	* CONTROL
	**********************/
	void unLoad();
};
	


#endif /* SCENECREATEMISSION_H_ */
