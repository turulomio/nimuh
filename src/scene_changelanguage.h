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

#ifndef SCENECHANGELANGUAGE_H_
#define SCENECHANGELANGUAGE_H_

#include "martian.h"
#include "scene.h"
#include "user.h"
#include "missions.h"

using namespace std;
using namespace Martian;

#define SCENE_CHANGELANGUAGE_MAIN 0

class SceneChangeLanguage : public Scene {
	
private:


	Button* bSpanish;
	Button* bEnglish;
	Element *text;

	
public:
    
	SceneChangeLanguage();
	~SceneChangeLanguage();
	void load();


	/*********************
	* BUTTONS
	**********************/
	void verifyClickElements_Main();
	void verifyOverElements_Main();

	/*********************
	* ESCENES
	**********************/
	bool drawScene ();

	void drawSceneMain ();
	void drawSceneMainByIndexZ(int z);
		
	/*********************
	* CONTROL
	**********************/
	void unLoad();
};
	


#endif /* SCENECHANGELANGUAGE_H_ */
