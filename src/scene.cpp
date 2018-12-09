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
 
 
#include "scene.h"

namespace Martian {
	
	/*****************************
	**
	** CLASE DEBUG
	**
	******************************/	

	Debug* Debug::instance = NULL;
	
	Debug::Debug() {
		todo = false;
	}
	
	Debug* Debug::GetInstance () {
		if ( instance == NULL ) {
			instance = new Debug();
		}
		return instance;	
	}
	
	/*****************************
	**
	** CLASE SCENE
	**
	******************************/	

	int Scene::nScreenShot = 0;
	Element *Scene::msg_title = NULL;
	Element *Scene::msg_text = NULL;
	Element *Scene::msg_bgAlert = NULL;
	Element *Scene::msg_bgMessage = NULL;
	Button *Scene::msg_bAccept = NULL;
	Button *Scene::msg_bCancel = NULL;
	Entry *Scene::msg_entry = NULL;
	string Scene::msg_fontTitle = "";
	string Scene::msg_fontText = "";
	string Scene::msg_fontButtons = "";
	string Scene::msg_fontEntry = "";
	bool Scene::hasMsg_bg = false;
	bool Scene::hasMsg_title = false;
	int Scene::posXBAcceptInAlert = 200;
    int Scene::posXBCancelInAlert = 600;
	
	Scene::Scene() {
		levelSaveImage = 0;
		returnSceneFromMessage = 0;
		nScreenShot = 0;
		saveImage = false;
		isLoad = false;
		nextSceneWhenWait = "";
		msWhenWait = 0;
		groupScene = new GroupScene();
	
		currentFPS = -1;
		
		drawCursor = true;
		
	}
	
	void Scene::clearElmImgSave () {
		colorImgOnSaveImg (180, 0, 0, 0); 
		for (int i=0; i<NELMIMGSAVE; i++) {
			elmImgSave[i]->removeScale();
			elmImgSave[i]->removeAlpha();
			elmImgSave[i]->removeRotation();
			elmImgSave[i]->removeRGB();
			elmImgSave[i]->removeTypeMovement();
		}
	}
	
	void Scene::setCurrentFPS () {
		
		if (currentFPS!= Timer::GetInstance()->getLastCurrentFPS()) {
			
			currentFPS = Timer::GetInstance()->getLastCurrentFPS();
			
			char tmp[8];
			
			sprintf(tmp, "FPS: %d", currentFPS);

			if (elCurrentFPS->getFrames()>0) {
				elCurrentFPS->changeFrameText(0, Fonts::GetInstance()->getDefaultFont(), tmp, ALIGN_CENTER);
			} else {
				elCurrentFPS->addFrameText(Fonts::GetInstance()->getDefaultFont(), tmp, ALIGN_CENTER);
			}
			
		}
	}
	
	void Scene::verifySaveImage() { 
		if (saveImage) { 
			saveImg(levelSaveImage, true); 
			saveImage = false; 
		} 
	}
	
	void Scene::goToScene(string ns, int ms, int transition) { 
		Cursor::GetInstance()->forceHideText();
		setStatusScene(SCENE_WAITINGNEXTSCENE);
		nextSceneWhenWait = ns; 
		Chronometer::GetInstance()->setTime("quitwait"); 
		msWhenWait = ms; 
		setSaveImage(true, 1);
		colorImgOnSaveImg (0, 0, 0, 0);
		switch (transition) {
			case SCENE_TRANSITION_FADEOUT:
				getElmImgSave(1)->setFadeOut((ms/4)*3);
			break;
			case SCENE_TRANSITION_FADEOUT_SCALEx0:
				getElmImgSave(1)->setFadeOut((ms/4)*3);
				getElmImgSave(1)->setScale(0, 0, (ms/4)*3);
			break;
			case SCENE_TRANSITION_FADEOUT_SCALEx0_ROTATE:
				getElmImgSave(1)->setFadeOut((ms/4)*3);
				getElmImgSave(1)->setScale(0, 0, (ms/4)*3);
				getElmImgSave(1)->setRotationNormal(360, (ms/4)*3);
			break;
			case SCENE_TRANSITION_SCALEx0:
				getElmImgSave(1)->setScale(0, 0, (ms/4)*3);
			break;
			case SCENE_TRANSITION_SCALEx0_ROTATE:
				getElmImgSave(1)->setScale(0, 0, (ms/4)*3);
				getElmImgSave(1)->setRotationNormal(360, (ms/4)*3);
			break;
			case SCENE_TRANSITION_SCALEx2:
				getElmImgSave(1)->setFadeOut((ms/4)*3);
				getElmImgSave(1)->setScaleGL(2, (ms/4)*3);
			break;
			case SCENE_TRANSITION_SCALEx2_ROTATE:
				getElmImgSave(1)->setFadeOut((ms/4)*3);
				getElmImgSave(1)->setScaleGL(2, (ms/4)*3);
				getElmImgSave(1)->setRotationNormal(360, (ms/4)*3);
			break;
		}
	}
	
	void Scene::createStaticsElements () {
		char tmp[8];
		
		hasMsg_bg = false;
		hasMsg_title = true;
		
		strcpy(tmp, "Title");
		
		msg_title = new Element();
		msg_title->setAlign(ALIGN_CENTER);
		msg_title->setVAlign(VALIGN_CENTER);
		msg_title->setX(World::width/2);
		msg_title->setY(140);
		
		msg_title->addFrameText(Fonts::GetInstance()->getDefaultFont(), tmp, ALIGN_CENTER);

		strcpy(tmp, "Text");

		msg_text = new Element();
		msg_text->setAlign(ALIGN_CENTER);
		msg_text->setVAlign(VALIGN_CENTER);
		msg_text->setX(World::width/2);
		msg_text->setY(240);
		
		msg_text->addFrameText(Fonts::GetInstance()->getDefaultFont(), tmp, ALIGN_CENTER);
		
		msg_bAccept = new Button();
		msg_bAccept->addParameter("type", "accept");
		msg_bAccept->setScales(1.0, 1.1);
		msg_bAccept->setAlign(ALIGN_CENTER);
		msg_bAccept->setVAlign(VALIGN_CENTER);
		msg_bAccept->setX(World::width/4);
		msg_bAccept->setY(420);
		
		if (Language::GetInstance()->getText("accept")!="-") {
			sprintf(tmp, "%s", Language::GetInstance()->getText("accept").c_str());
		} else {
			sprintf(tmp, "%s", "Accept");
		}
		msg_bAccept->imageOut(Fonts::GetInstance()->getSurface_TextBitMap(Fonts::GetInstance()->getDefaultFont(), ALIGN_CENTER, tmp));
		msg_bAccept->setAnimation("out");
		

		msg_bCancel = new Button();
		msg_bCancel->addParameter("type", "cancel");
		msg_bCancel->setScales(1.0, 1.1);
		msg_bCancel->setAlign(ALIGN_CENTER);
		msg_bCancel->setVAlign(VALIGN_CENTER);
		msg_bCancel->setX((World::width/4)*3);
		msg_bCancel->setY(420);
		
		if (Language::GetInstance()->getText("cancel")!="-") {
			sprintf(tmp, "%s", Language::GetInstance()->getText("cancel").c_str());
		} else {
			sprintf(tmp, "Cancel");
		}
		msg_bCancel->imageOut(Fonts::GetInstance()->getSurface_TextBitMap(Fonts::GetInstance()->getDefaultFont(), ALIGN_CENTER, tmp));
		msg_bCancel->setAnimation("out");
		
		msg_entry = new Entry(NULL, 400, 40, 0, 10);
		msg_entry->setNoSpace(true);
		msg_entry->setX((World::width/2)-200);
		msg_entry->setY(310);
		msg_entry->setActive(true);

	}
	
	void Scene::colorImgOnSaveImg (int alpha, int r, int g, int b) {
		imgOnSaveImg->changeFrameSurface(0, Primitives::GetInstance()->rectangle(World::width, World::height, 0, 0, 0));
		imgOnSaveImg->setAlpha(alpha);
	}
	
	void Scene::initialize() {
         
        Debug::GetInstance()->writeText("Cargando nuevo escenario");
		
		Chronometer::GetInstance()->removeTime("quitwait");
		
		nextSceneWhenWait = "";
		msWhenWait = 0;
		
		quit = false;
		
		isLoad = true;
		
		if (Debug::GetInstance()->getDebug()) {
			elCurrentFPS = new Element();
			elCurrentFPS->setX(10);
			elCurrentFPS->setY(10);
			elCurrentFPS->addFrameSurface(Primitives::GetInstance()->rectangle(1, 1, 0, 0, 0));
		}
		
		imgOnSaveImg = new Element();
		imgOnSaveImg->setX(0);
		imgOnSaveImg->setY(0);
		imgOnSaveImg->setAlpha(180);
		imgOnSaveImg->addFrameSurface(Primitives::GetInstance()->rectangle(World::width, World::height, 0, 0, 0));
		
		for (int i=0; i<NELMIMGSAVE; i++) {
			elmImgSave[i] = new Element();
			elmImgSave[i]->setAlign(ALIGN_CENTER);
			elmImgSave[i]->setVAlign(VALIGN_CENTER);
			elmImgSave[i]->setX(World::width/2);
			elmImgSave[i]->setY(World::height/2);
			elmImgSave[i]->addFrameSurface(Primitives::GetInstance()->rectangle(2, 2, 0, 0, 0));
		}
		
	}
	
	void Scene::drawLastElements() {
		if (Debug::GetInstance()->getDebug()) {
			setCurrentFPS ();
			elCurrentFPS->draw();
		}
		
        if (drawCursor) Cursor::GetInstance()->draw();
    }
		
	void Scene::saveImg (int level, bool withImgOnSaveImg) {
	
		if (withImgOnSaveImg) {
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			imgOnSaveImg->draw();
			glDisable(GL_BLEND);
		}
		
		SDL_Surface *temp;
		unsigned char *pixels;
		int i;
		temp = SDL_CreateRGBSurface(SDL_SWSURFACE, World::width, World::height, 24,
	#if SDL_BYTEORDER == SDL_LIL_ENDIAN
									0x000000FF, 0x0000FF00, 0x00FF0000, 0
	#else
									0x00FF0000, 0x0000FF00, 0x000000FF, 0
	#endif
								   );
		if (temp == NULL)
		  return;
	
		pixels = (unsigned char*) malloc(3 * World::width * World::height);
		if (pixels == NULL)
		{
		  SDL_FreeSurface(temp);
		  return;
		}
	
		glReadPixels(0, 0, World::width, World::height, GL_RGB, GL_UNSIGNED_BYTE, pixels);
	
		for (i=0; i<World::height; i++)
		  memcpy(((char *) temp->pixels) + temp->pitch * i, pixels + 3*World::width * (World::height-i-1), World::width*3);
		free(pixels);
	
		elmImgSave[level]->changeFrameSurface(0, temp);
		
	}
	
	void Scene::saveScreenShot() {			
		SDL_Surface *temp;
		unsigned char *pixels;
		int i;
		temp = SDL_CreateRGBSurface(SDL_SWSURFACE, World::width, World::height, 24,
	#if SDL_BYTEORDER == SDL_LIL_ENDIAN
									0x000000FF, 0x0000FF00, 0x00FF0000, 0
	#else
									0x00FF0000, 0x0000FF00, 0x000000FF, 0
	#endif
								   );
		if (temp == NULL)
		  return;
	
		pixels = (unsigned char*) malloc(3 * World::width * World::height);
		if (pixels == NULL)
		{
		  SDL_FreeSurface(temp);
		  return;
		}
	
		glReadPixels(0, 0, World::width, World::height, GL_RGB, GL_UNSIGNED_BYTE, pixels);
	
		for (i=0; i<World::height; i++)
		  memcpy(((char *) temp->pixels) + temp->pitch * i, pixels + 3*World::width * (World::height-i-1), World::width*3);
		free(pixels);
		
		char file[128];
		sprintf(file, "%s/shot%d.bmp", Hash::getPathData().c_str(), nScreenShot);
		
		SDL_SaveBMP(temp, file);
		
		SDL_FreeSurface(temp);
		
		nScreenShot++;
	}
	
	/****************************
	  DRAWSCENE WAITINGNEXTSCENE
	*****************************/
	
	void Scene::drawSceneWaitingNextScene () {
		elmImgSave[1]->draw();
		
		if (Chronometer::GetInstance()->getTime("quitwait") > msWhenWait) {
			goToScene(nextSceneWhenWait);
		}
		
	}
	
	/**********************
	  DRAWSCENE MESAGEBOX
	**********************/
	
	void Scene::showMessageBox (string tit, string txt, int returnScene) {

		statusScene = SCENE_MESSAGEBOX;
		
		returnSceneFromMessage = returnScene;
		
		setSaveImage(true, 1);
	
	    if (hasMsg_title) {
    		if (Scene::msg_fontTitle=="") {
    			Scene::msg_fontTitle=Fonts::GetInstance()->getDefaultFont();
    		}
    		
    		msg_title->changeFrameText(0, Scene::msg_fontTitle, tit, ALIGN_CENTER);
        }
		
		if (Scene::msg_fontText=="") {
			Scene::msg_fontText=Fonts::GetInstance()->getDefaultFont();
		}
		
		msg_text->changeFrameText(0, Scene::msg_fontText, txt, ALIGN_CENTER);
		
		if (Scene::msg_fontButtons=="") {
			Scene::msg_fontButtons=Fonts::GetInstance()->getDefaultFont();
		}
		
		string tmp;
		
		if (Language::GetInstance()->getText("accept")!="-") {
			tmp = Language::GetInstance()->getText("accept");
		} else {
			tmp = "Accept";
		}
		
		msg_bAccept->changeFrameSurface(0, Fonts::GetInstance()->getSurface_TextBitMap(Scene::msg_fontButtons, ALIGN_CENTER, tmp));
		
		msg_bAccept->setX(World::width/2);
		
	}
	
	void Scene::drawSceneMessageBox () {
		
		verifyOverElements_MessageBox();
		
		elmImgSave[1]->draw();
		
		for (int i=0; i<MAX_INDEXZ; i++) {
			drawSceneMessageBoxByIndexZ(i);
		}
		
	}
	
	void Scene::drawSceneMessageBoxByIndexZ(int z) {
		if (hasMsg_bg) {
            if (msg_bgMessage->getIndexZ() == z) {
    			msg_bgMessage->draw();
    		}
        }
		if (hasMsg_title) {
            if (msg_title->getIndexZ() == z) {
    			msg_title->draw();
    		}
        }
		if (msg_text->getIndexZ() == z) {
			msg_text->draw();
		}
		if (msg_bAccept->getIndexZ() == z) {
			msg_bAccept->draw();
		}
	}

	void Scene::verifyClickElements_MessageBox() {
		if (msg_bAccept->isOnMouseOver()) {
			statusScene = returnSceneFromMessage;
		}
	}
	
	void Scene::verifyOverElements_MessageBox() {
		msg_bAccept->onOver();
	}
	
	/**********************
	  DRAWSCENE ALERT
	**********************/
	
	void Scene::showAlert (string tit, string txt, void (*function)(Scene*, Button*, string data), int returnScene) {

		statusScene = SCENE_ALERT;
		
		returnSceneFromMessage = returnScene;
		
		OnClickButtonOnAlert = function;
		
		setSaveImage(true, 1);
		
        if (hasMsg_title) {
    		if (Scene::msg_fontTitle=="") {
    			Scene::msg_fontTitle=Fonts::GetInstance()->getDefaultFont();
    		}
    		msg_title->changeFrameText(0, Scene::msg_fontTitle, tit, ALIGN_CENTER);
        }
        
		if (Scene::msg_fontText=="") {
			Scene::msg_fontText=Fonts::GetInstance()->getDefaultFont();
		}
		
		msg_text->changeFrameText(0, Scene::msg_fontText, txt, ALIGN_CENTER);
		
		if (Scene::msg_fontButtons=="") {
			Scene::msg_fontButtons=Fonts::GetInstance()->getDefaultFont();
		}
		
		string tmp;
		
		if (Language::GetInstance()->getText("accept")!="-") {
			tmp = Language::GetInstance()->getText("accept");
		} else {
			tmp = "Accept";
		}
		
		msg_bAccept->changeFrameSurface(0, Fonts::GetInstance()->getSurface_TextBitMap(Scene::msg_fontButtons, ALIGN_CENTER, tmp));
		
		msg_bAccept->setX(posXBAcceptInAlert);
		
		if (Language::GetInstance()->getText("cancel")!="-") {
			tmp = Language::GetInstance()->getText("cancel");
		} else {
			tmp = "Cancel";
		}
		
		msg_bCancel->changeFrameSurface(0, Fonts::GetInstance()->getSurface_TextBitMap(Scene::msg_fontButtons, ALIGN_CENTER, tmp));
		
		msg_bCancel->setX(posXBCancelInAlert);
		
	}
	
	void Scene::drawSceneAlert () {
		
		verifyOverElements_Alert();
		
		elmImgSave[1]->draw();
		
		for (int i=0; i<MAX_INDEXZ; i++) {
			drawSceneAlertByIndexZ(i);
		}
		
	}
	
	void Scene::drawSceneAlertByIndexZ(int z) {
		if (hasMsg_bg) {
            if (msg_bgAlert->getIndexZ() == z) {
    			msg_bgAlert->draw();
    		}
        }
		if (hasMsg_title) {
    		if (msg_title->getIndexZ() == z) {
    			msg_title->draw();
    		}
        }
		if (msg_text->getIndexZ() == z) {
			msg_text->draw();
		}
		if (msg_bAccept->getIndexZ() == z) {
			msg_bAccept->draw();
		}
		if (msg_bCancel->getIndexZ() == z) {
			msg_bCancel->draw();
		}
	}

	void Scene::verifyClickElements_Alert() {
		if (msg_bAccept->isOnMouseOver()) {
			if (OnClickButtonOnAlert!=NULL)
				OnClickButtonOnAlert(this, msg_bAccept, "");
			else
				setStatusSceneWithReturnSceneFromMessage();
		}
		if (msg_bCancel->isOnMouseOver()) {
			if (OnClickButtonOnAlert!=NULL)
				OnClickButtonOnAlert(this, msg_bCancel, "");
			else
				setStatusSceneWithReturnSceneFromMessage();
		}
	}
	
	void Scene::verifyOverElements_Alert() {
		msg_bAccept->onOver();
		msg_bCancel->onOver();
	}
	
	/**********************
	  DRAWSCENE INPUT
	**********************/
	
	void Scene::showInput (string tit, string txt, int maxLetters, void (*function)(Scene*, Button*, string data), int returnScene) {

		statusScene = SCENE_INPUT;
		
		returnSceneFromMessage = returnScene;
		
		OnClickButtonOnInput = function;
		
		setSaveImage(true, 1);
	    if (hasMsg_title) {
    		if (Scene::msg_fontTitle=="") {
    			Scene::msg_fontTitle=Fonts::GetInstance()->getDefaultFont();
    		}
    		msg_title->changeFrameText(0, Scene::msg_fontTitle, tit, ALIGN_CENTER);
        }
        
		if (Scene::msg_fontText=="") {
			Scene::msg_fontText=Fonts::GetInstance()->getDefaultFont();
		}
		msg_text->changeFrameText(0, Scene::msg_fontText, txt, ALIGN_CENTER);
		
		if (Scene::msg_fontButtons=="") {
			Scene::msg_fontButtons=Fonts::GetInstance()->getDefaultFont();
		}
		if (Scene::msg_fontEntry=="") {
			Scene::msg_fontEntry=Fonts::GetInstance()->getDefaultFont();
		}
		
		string tmp;
		
		if (Language::GetInstance()->getText("accept")!="-") {
			tmp = Language::GetInstance()->getText("accept");
		} else {
			tmp = "Accept";
		}
		
		msg_bAccept->changeFrameSurface(0, Fonts::GetInstance()->getSurface_TextBitMap(Scene::msg_fontButtons, ALIGN_CENTER, tmp));
		
		msg_bAccept->setX(posXBAcceptInAlert);
		
		if (Language::GetInstance()->getText("cancel")!="-") {
			tmp = Language::GetInstance()->getText("cancel");
		} else {
			tmp = "Cancel";
		}
		
		msg_bCancel->changeFrameSurface(0, Fonts::GetInstance()->getSurface_TextBitMap(Scene::msg_fontButtons, ALIGN_CENTER, tmp));
		
		msg_bCancel->setX(posXBCancelInAlert);
		
		msg_entry->setMaxLetters(maxLetters);
		msg_entry->setFont(msg_fontEntry);
		msg_entry->setText("");
		
	}
	
	void Scene::drawSceneInput () {
		
		verifyOverElements_Input();
		
		elmImgSave[1]->draw();
		
		for (int i=0; i<MAX_INDEXZ; i++) {
			drawSceneInputByIndexZ(i);
		}
		
	}
	
	void Scene::drawSceneInputByIndexZ(int z) {
		if (hasMsg_bg) {
            if (msg_bgAlert->getIndexZ() == z) {
    			msg_bgAlert->draw();
    		}
        }
        if (hasMsg_title) {
    		if (msg_title->getIndexZ() == z) {
    			msg_title->draw();
    		}
        }
		if (msg_text->getIndexZ() == z) {
			msg_text->draw();
		}
		if (msg_entry->getIndexZ() == z) {
			msg_entry->draw();
		}
		if (msg_bAccept->getIndexZ() == z) {
			msg_bAccept->draw();
		}
		if (msg_bCancel->getIndexZ() == z) {
			msg_bCancel->draw();
		}
	}

	void Scene::verifyClickElements_Input() {
		if (msg_bAccept->isOnMouseOver()) {
			if (OnClickButtonOnInput!=NULL)
				OnClickButtonOnInput(this, msg_bAccept, msg_entry->getText());
			else
				setStatusSceneWithReturnSceneFromMessage();
		}
		if (msg_bCancel->isOnMouseOver()) {
			if (OnClickButtonOnInput!=NULL)
				OnClickButtonOnInput(this, msg_bCancel, "");
			else
				setStatusSceneWithReturnSceneFromMessage();
		}
	}
	
	void Scene::verifyOverElements_Input() {
		msg_bAccept->onOver();
		msg_bCancel->onOver();
		msg_entry->onOver();
	}
	
	
	/**********************
	  DRAWSCENE MESSAGE
	**********************/
	
	void Scene::drawCommonsScene () {
		
		switch(statusScene) {
			
			case SCENE_WAITINGNEXTSCENE:
				drawSceneWaitingNextScene();
			
				// Comprobando teclas para opciones			
				{ SDL_Event event;
					while ( SDL_PollEvent(&event) ) {
						if ( event.type == SDL_QUIT ) {
							setNextScene("quit");
							setQuit(true);
						}
						
						if ( event.type == SDL_KEYDOWN ) {
							if ( event.key.keysym.sym == SDLK_ESCAPE ) {
								//statusScene = returnSceneFromMessage;
							}
						}
									
					}
				}
				
			break;
	
			case SCENE_MESSAGEBOX:
				drawSceneMessageBox();
			
				// Comprobando teclas para opciones			
				{ SDL_Event event;
					while ( SDL_PollEvent(&event) ) {
						if ( event.type == SDL_QUIT ) {
							setNextScene("quit");
							setQuit(true);
						}
						
						if ( event.type == SDL_KEYDOWN ) {
							if ( event.key.keysym.sym == SDLK_ESCAPE ) {
								statusScene = returnSceneFromMessage;
							}
						}
						
						if ( event.type == SDL_MOUSEBUTTONDOWN ) {
							if ( event.button.button == SDL_BUTTON_LEFT ) {
								verifyClickElements_MessageBox();
							}
						}
			
					}
				}
				
			break;

			case SCENE_ALERT:
				drawSceneAlert();
			
				// Comprobando teclas para opciones			
				{ SDL_Event event;
					while ( SDL_PollEvent(&event) ) {
						if ( event.type == SDL_QUIT ) {
							setNextScene("quit");
							setQuit(true);
						}
						
						if ( event.type == SDL_KEYDOWN ) {
							if ( event.key.keysym.sym == SDLK_ESCAPE ) {
								statusScene = returnSceneFromMessage;
							}
						}
						
						if ( event.type == SDL_MOUSEBUTTONDOWN ) {
							if ( event.button.button == SDL_BUTTON_LEFT ) {
								verifyClickElements_Alert();
							}
						}
			
					}
				}
				
			break;
				
			case SCENE_INPUT:
				drawSceneInput();
			
				// Comprobando teclas para opciones			
				{ SDL_Event event;
					while ( SDL_PollEvent(&event) ) {
						if ( event.type == SDL_QUIT ) {
							setNextScene("quit");
							setQuit(true);
						}
						
						if ( event.type == SDL_KEYDOWN ) {
							msg_entry->insertTextUnicode(event.key.keysym.sym, event.key.keysym.unicode);
							if ( event.key.keysym.sym == SDLK_ESCAPE ) {
								statusScene = returnSceneFromMessage;
							}
						}
						
						if ( event.type == SDL_MOUSEBUTTONDOWN ) {
							if ( event.button.button == SDL_BUTTON_LEFT ) {
								verifyClickElements_Input();
							}
						}
			
					}
				}
				
			break;
				
		}
		
	}
	
	void Scene::unLoadCommons() {
		
		Debug::GetInstance()->writeText("Descargando escenario");
		
		Cursor::GetInstance()->forceHideText();
		if (Debug::GetInstance()->getDebug()) {
            delete elCurrentFPS;
        }
        
		delete imgOnSaveImg;
		
		for (int i=0; i<NELMIMGSAVE; i++) {
			delete elmImgSave[i];
		}
		
	}
	
	Scene::~Scene() {
		unLoadCommons();
	}

	
}
