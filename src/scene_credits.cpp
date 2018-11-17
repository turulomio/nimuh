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
 
#include "scene_credits.h"


/*****************************
**
** CLASE SceneCredits
**
******************************/	

SceneCredits::SceneCredits() : Scene () {
	statusScene = SCENE_CREDITS_MAIN;
}

SceneCredits::~SceneCredits() {
	unLoad();
}

void SceneCredits::load() {

	initialize();
	
	Sounds::GetInstance()->addSoundFromData("skandaluz", "music", "sound/skandaluz.ogg");
	
	draw0 = new Element();
	draw0->setAlign(ALIGN_CENTER);
	draw0->setXY(400, 0);
	draw0->addFrameFileFromData("/misc/title.jpg");
	getGroupScene()->addElement(draw0);
	draw0->setFadeIn(1000);
	
	draw1 = new Element();
	draw1->setAlign(ALIGN_RIGHT);
	draw1->setVAlign(VALIGN_BOTTOM);
	draw1->setXY(800, 600);
	draw1->addFrameFileFromData("/misc/pjs.jpg");
	getGroupScene()->addElement(draw1);
	draw1->setFadeIn(1000);
	
	draw2 = new Element();
	draw2->setAlign(ALIGN_CENTER);
	draw2->setVAlign(ALIGN_CENTER);
	draw2->setXY(30, 570);
	draw2->addFrameFileFromData("/misc/earth.jpg");
	getGroupScene()->addElement(draw2);
	draw2->setFadeIn(1000);
	
	text0 = new Element();
	text0->hide();
	text0->setAlign(ALIGN_CENTER);
	text0->setVAlign(VALIGN_CENTER);
	text0->setXY(400, 280);
	text0->addFrameLanguage("font-texts", "credits0", ALIGN_CENTER, 650);
	getGroupScene()->addElement(text0);
	
	text1 = new Element();
	text1->hide();
	text1->setAlign(ALIGN_CENTER);
	text1->setVAlign(VALIGN_CENTER);
	text1->setXY(400, 280);
	text1->addFrameLanguage("font-texts", "credits1", ALIGN_CENTER, 650);
	getGroupScene()->addElement(text1);
	
	text2 = new Element();
	text2->setCurrentScale(0.95);
	text2->hide();
	text2->setAlign(ALIGN_CENTER);
	text2->setVAlign(VALIGN_CENTER);
	text2->setXY(400, 300);
	text2->addFrameLanguage("font-texts", "credits2", ALIGN_CENTER, 700);
	getGroupScene()->addElement(text2);
	
	text3 = new Element();
	text3->hide();
	text3->setAlign(ALIGN_CENTER);
	text3->setVAlign(VALIGN_CENTER);
	text3->setXY(400, 270);
	text3->addFrameLanguage("font-texts", "credits3", ALIGN_CENTER, 650);
	getGroupScene()->addElement(text3);
	
	junta = new Element();
	junta->setAlign(ALIGN_CENTER);
	junta->setVAlign(VALIGN_CENTER);
	junta->setXY(400, 280);
	junta->addFrameFileFromData("/misc/junta.png");
	junta->hide();
	getGroupScene()->addElement(junta);
	
	Chronometer::GetInstance()->removeTime("time_credit");
	Chronometer::GetInstance()->setTime("time_credit");	
	
	Sounds::GetInstance()->getSound("skandaluz")->play(1, -1, 2000);
	
	
}

/**********************
  DRAWSCENE MAIN
**********************/

void SceneCredits::drawSceneMain () {
			
	verifyOverElements_Main();
	
    if ( Chronometer::GetInstance()->verifyTime("time_credit", 1000) ) {
		text0->show();
        text0->setFadeIn(2000);
    }
	
	if ( Chronometer::GetInstance()->verifyTime("time_credit", 15000) ) {
		text0->setFadeOut(2000);
		text1->show();
        text1->setFadeIn(2000);
    }
	
	if ( Chronometer::GetInstance()->verifyTime("time_credit", 50000) ) {
		text1->setFadeOut(2000);
		text2->show();
        text2->setFadeIn(2000);
    }
	
	if ( Chronometer::GetInstance()->verifyTime("time_credit", 80000) ) {
		text2->setFadeOut(2000);
		text3->show();
        text3->setFadeIn(2000);
    }
	
    if ( Chronometer::GetInstance()->verifyTime("time_credit", 100000) ) {
		text3->setFadeOut(2000);
		junta->show();
        junta->setFadeIn(2000);
    }
	
	for (int i=0; i<MAX_INDEXZ; i++) {
		drawSceneMainByIndexZ(i);
	}
	
}

void SceneCredits::drawSceneMainByIndexZ(int z) {
	if (draw0->getIndexZ() == z) {
		draw0->draw();
	}
	if (draw1->getIndexZ() == z) {
		draw1->draw();
	}
	if (draw2->getIndexZ() == z) {
		draw2->draw();
	}
	if (junta->getIndexZ() == z) {
		junta->draw();
	}
	if (text0->getIndexZ() == z) {
		text0->draw();
	}
	if (text1->getIndexZ() == z) {
		text1->draw();
	}
	if (text2->getIndexZ() == z) {
		text2->draw();
	}
	if (text3->getIndexZ() == z) {
		text3->draw();
	}
}

void SceneCredits::verifyClickElements_Main() {
}

void SceneCredits::verifyOverElements_Main() {
}

bool SceneCredits::drawScene() {
	
	glClear(GL_COLOR_BUFFER_BIT); // | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	
	drawCommonsScene ();

	switch(statusScene) {
	
		case SCENE_CREDITS_MAIN:
	
			drawSceneMain();
		
			// Comprobando teclas para opciones			
			{ SDL_Event event;
				while ( SDL_PollEvent(&event) ) {
					
					if ( event.type == SDL_KEYDOWN ) {
						if ( event.key.keysym.sym == SDLK_ESCAPE ) {
							Sounds::GetInstance()->getSound("skandaluz")->stop(2000);
							goToScene("menu", 2000, SCENE_TRANSITION_FADEOUT);
						}
					}
					
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
void SceneCredits::unLoad() {

	unLoadCommons();
	
	statusScene = SCENE_CREDITS_MAIN;
	
	Sounds::GetInstance()->unLoad();
	
	delete draw0;
	delete draw1;
	delete draw2;
	delete text0;
	delete text1;
	delete text2;
	delete text3;
	delete junta;

	isLoad = false;

}
