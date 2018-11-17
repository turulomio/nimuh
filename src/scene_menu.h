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

#ifndef SCENEMENU_H_
#define SCENEMENU_H_

#include "martian.h"
#include "scene.h"
#include "user.h"
#include "missions.h"

using namespace std;
using namespace Martian;

#define SCENE_MENU_MAIN 0
#define SCENE_MENU_CHANGEUSER 1
#define SCENE_MENU_OPTIONS 2
#define SCENE_MENU_HOWTOPLAY 3

class SceneMenu;

class PlanetButton : public Group {

private:
	AnimatedElement *anim;
	Button *button;
	int indexz;

	float pixMov;
	float avPixMov;

	float factorPixMov;
	
public:
	PlanetButton ();
	~PlanetButton();
	
	AnimatedElement* getAnimatedElement() { return anim; }
	Button* getButton() { return button; }

	void imageOutButton(SDL_Surface *sfc) { button->imageOut(sfc); }
	void imageOnButton(SDL_Surface *sfc) { button->imageOn(sfc); }
	
	void onOver();
	
	void setFactorPixMov(float f) { factorPixMov = f; }
	
	void setSensitive(bool s) { button->setSensitive(s); }
	
	bool isOnMouseOver() { return button->isOnMouseOver(); }
	
	void setIndexZ (int z) { indexz = z; }
	int getIndexZ () { return indexz; }
	
	void draw ();
	
};

class ButtonUser : public Group  {

private:
	Element *bg;
	Element *title;
	Button *bSelect, *bDelete;
	int indexz;
	int index;

public:
	ButtonUser ();
	~ButtonUser();

	void setTitle(string t);

	void setIndex (int i);
	int getIndex () { return index; }
	
	void setIndexZ (int z) { indexz = z; }
	int getIndexZ () { return indexz; }
	
	void draw();
	
	void onOver();
	
	void unLoad();
	
	void verifyClick(SceneMenu *sc);

};

class SceneMenu : public Scene {
	
private:
	PlanetButton* bPlay;
	Button* bChangeUser;
	PlanetButton* bMissions;
	PlanetButton* bCredits;
	PlanetButton* bHowto;
	PlanetButton* bPreferences;
	PlanetButton* bQuit;

	Element *earth, *title;

	Button* bNewUser;
	Button* bBack;

	Element *bgOptions, *bgUsers;
	Button *bAccept, *bCancel;
	
	Element *nousers;

	Element *frameUp, *frameDown;

	Element *titleLang;
	Element *titleUsers;

	Element *nameUser;
		
	ListView *dataUsers;
	
	ParticlesSystem *stars;
	
	Element *howtoplay;
	
public:
	
	Element *titleVolumeMusics, *titleVolumeEffects;
	SelectButton *volumeMusics, *volumeEffects;
	CheckButton *cbFullscreen;
	SelectButton *typeLang;

	SceneMenu();
	~SceneMenu();
	void load();

	void createUserButtons();
	void changeUser(int i);
	
	void setStatusScene(int s);


	/*********************
	* BUTTONS
	**********************/
	void verifyClickElements_Main();
	void verifyOverElements_Main();
	void verifyClickElements_ChangeUser();
	void verifyOverElements_ChangeUser();
	void verifyClickElements_Options();
	void verifyOverElements_Options();
	void verifyClickElements_Howtoplay();
	void verifyOverElements_Howtoplay();
	/*********************
	* ESCENES
	**********************/
	bool drawScene ();

	void drawSceneMain ();
	void drawSceneMainByIndexZ(int z);
	
	void drawSceneChangeUser ();
	void drawSceneChangeUserByIndexZ(int z);
	
	void drawSceneOptions ();
	void drawSceneOptionsByIndexZ(int z);
	
	void drawSceneHowtoplay ();
	void drawSceneHowtoplayByIndexZ(int z);
	
	/*********************
	* CONTROL
	**********************/
	void unLoad();
};
	


#endif /* SCENEMENU_H_ */
