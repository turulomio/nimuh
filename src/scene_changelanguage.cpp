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
 
#include "scene_changelanguage.h"


void bSpanish_SceneChangeLanguage_OnClick (Scene *s, Button *b)
{
	SceneChangeLanguage* se = (SceneChangeLanguage*)s;
	Options::GetInstance()->setValue("lang", "es");
	Options::GetInstance()->save();
	Language::GetInstance()->setLang("es");
	se->goToScene("anim");
}

void bEnglish_SceneChangeLanguage_OnClick (Scene *s, Button *b)
{
	SceneChangeLanguage* se = (SceneChangeLanguage*)s;
	Options::GetInstance()->setValue("lang", "en");
	Options::GetInstance()->save();
	Language::GetInstance()->setLang("en");
	se->goToScene("anim");
}

/*****************************
**
** CLASE SceneChangeLanguage
**
******************************/	

SceneChangeLanguage::SceneChangeLanguage() : Scene () {
	statusScene = SCENE_CHANGELANGUAGE_MAIN;
}

SceneChangeLanguage::~SceneChangeLanguage() {
	unLoad();
}

void SceneChangeLanguage::load() {

	initialize();
	
	text = new Element();
	text->setAlign(ALIGN_CENTER);
	text->setVAlign(VALIGN_CENTER);
	text->setXY(400, 160);
	text->addFrameText("font-titles", "Seleccionar Idioma|Select language", ALIGN_CENTER);
	getGroupScene()->addElement(text);
	
	bSpanish = new Button();
	bSpanish->setScales(1.0, 1.1);
	bSpanish->setAlign(ALIGN_CENTER);
	bSpanish->setVAlign(VALIGN_CENTER);
	bSpanish->setX(250);
	bSpanish->setY(330);
	
	bSpanish->OnClick = bSpanish_SceneChangeLanguage_OnClick;
	
	bSpanish->imageOut(WorkingSurfaces::GetInstance()->surfaceFromImage((string)DATA_DIR + "/misc/spain.png"));
	bSpanish->setAnimation("out");
	
	getGroupScene()->addElement(bSpanish);
	
	bEnglish = new Button();
	bEnglish->setScales(1.0, 1.1);
	bEnglish->setAlign(ALIGN_CENTER);
	bEnglish->setVAlign(VALIGN_CENTER);
	bEnglish->setX(550);
	bEnglish->setY(330);
	
	bEnglish->OnClick = bEnglish_SceneChangeLanguage_OnClick;
	
	bEnglish->imageOut(WorkingSurfaces::GetInstance()->surfaceFromImage((string)DATA_DIR + "/misc/england.png"));
	bEnglish->setAnimation("out");
	
	getGroupScene()->addElement(bEnglish);
	
}

/**********************
  DRAWSCENE MAIN
**********************/

void SceneChangeLanguage::drawSceneMain () {
			
	verifyOverElements_Main();
	
	for (int i=0; i<MAX_INDEXZ; i++) {
		drawSceneMainByIndexZ(i);
	}
	
}

void SceneChangeLanguage::drawSceneMainByIndexZ(int z) {
	if (text->getIndexZ() == z) {
		text->draw();
	}
	if (bSpanish->getIndexZ() == z) {
		bSpanish->draw();
	}
	if (bEnglish->getIndexZ() == z) {
		bEnglish->draw();
	}
}

void SceneChangeLanguage::verifyClickElements_Main() {
	if (bSpanish->isOnMouseOver()) {
		bSpanish->OnClick(this, bSpanish);
	}
	if (bEnglish->isOnMouseOver()) {
		bEnglish->OnClick(this, bEnglish);
	}
}

void SceneChangeLanguage::verifyOverElements_Main() {
	bEnglish->onOver();
	bSpanish->onOver();
}

bool SceneChangeLanguage::drawScene() {
	
	glClear(GL_COLOR_BUFFER_BIT); // | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	
	drawCommonsScene ();

	switch(statusScene) {
	
		case SCENE_CHANGELANGUAGE_MAIN:
	
			drawSceneMain();
		
			// Comprobando teclas para opciones			
			{ SDL_Event event;
				while ( SDL_PollEvent(&event) ) {
					
					if ( event.type == SDL_MOUSEBUTTONDOWN ) {
						if ( event.button.button == SDL_BUTTON_LEFT ) {
							verifyClickElements_Main();
						}
					}
		
				}
			}
			
		break;
			
	}
	verifySaveImage();
 	drawLastElements();

	glDisable(GL_BLEND);
	
	SDL_GL_SwapBuffers();

	return getQuit();

}
void SceneChangeLanguage::unLoad() {

	unLoadCommons();
	
	statusScene = SCENE_CHANGELANGUAGE_MAIN;
	
	delete text;
	delete bSpanish;
	delete bEnglish;

	isLoad = false;

}
