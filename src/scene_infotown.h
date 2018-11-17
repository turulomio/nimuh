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

#ifndef SCENEINFOTOWN_H_
#define SCENEINFOTOWN_H_

#include "martian.h"
#include "scene.h"
#include "missions.h"
#include "sceneanimation.h"

#include <dirent.h> 

#define SCENE_INFOTOWN_MAIN 0
#define SCENE_INFOTOWN_MAP 1

using namespace std;
using namespace Martian;

class SceneInfoTown;

typedef struct
{
	bool hasMap;
	string file;
	string title1;
	string text1;
	string title2;
	string text2;
} Map;

void parseXMLInfoTown(char fileXML[128], SceneInfoTown *s);

class SceneInfoTown : public SceneAnimation {
	
private:
	RadioButton *bInfo0, *bInfo1, *bInfo2, *bInfo3;
	Button *up, *down;
	int nButtons;
	string txtActive;
	int bActive;
	Slide *photos;

	Element *downArrow, *upArrow;

	Button *bContinue;

	Element *frameUp, *frameDown;
	Element *bgText;
	    
public:
	
	string titleProvince;

	Map map;
	Element *bgMap;

	Element *title1Map, *text1Map, *title2Map, *text2Map;

	void setStatusScene(int s);

	void loadMapElements();
	
	SceneInfoTown();
	~SceneInfoTown();
	void load();

	Element *titleTexts;

	MarqueeElement *title;

	void addButton(int type, string alt);
	int getNButtons() { return nButtons; }
	
	void activeNextButton() { if (bActive+1<nButtons) { activeButton(bActive+1); } else { activeButton(0); } }
	void activePreviousButton() { if (bActive-1>=0) { activeButton(bActive-1); } else { activeButton(nButtons-1); } }
	
	void activeButton(int i);

	void organizeButtons();
	
	void upText();
	void downText();
	
	void loadPhotos(string path);

	/*********************
	* BUTTONS
	**********************/
	void verifyClickElements_Main();
	void verifyOverElements_Main();
	
	void verifyClickElements_Map();
	void verifyOverElements_Map();
	/*********************
	* SCENES
	**********************/
	bool drawScene ();
	
	void drawSceneMain ();
	void drawSceneMainByIndexZ(int z);
	
	void drawSceneMap ();
	void drawSceneMapByIndexZ(int z);
	
	/*********************
	* CONTROL
	**********************/
	void unLoad();

};
	


#endif /* SCENEINFOTOWN_H_ */
