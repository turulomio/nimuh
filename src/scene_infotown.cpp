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
 
#include "scene_infotown.h"

class SceneInfoTown;

void bContinue_SceneInfoTown_OnClick (Scene *s, Button *b) {
	SceneInfoTown* se = (SceneInfoTown*)s;
	if (se->getStatusScene() == SCENE_INFOTOWN_MAIN) {
		Sounds::GetInstance()->getSound("music")->stop(2000);
		Sounds::GetInstance()->getSound("ovni_sound")->stop(2000);
		se->goToScene("game", 2000, SCENE_TRANSITION_FADEOUT);
	} else {
		se->setStatusScene(SCENE_INFOTOWN_MAIN);
	}
}	

SceneInfoTown::SceneInfoTown() : SceneAnimation () {
	statusScene = SCENE_INFOTOWN_MAIN;
	txtActive = "";
	bActive = 0;
	nButtons = 0;
	map.hasMap = false;
	map.file = "";
	map.title1 = "";
	map.text1 = "";
	map.title2 = "";
	map.text2 = "";
}

SceneInfoTown::~SceneInfoTown() {
	unLoad();
}

void SceneInfoTown::setStatusScene(int s) {
     statusScene = s;
     
     switch (statusScene) {
            case SCENE_INFOTOWN_MAIN:
                 Sounds::GetInstance()->getSound("ovni_sound")->play(3, -1, 2000);
            break;
     }
}

void SceneInfoTown::loadMapElements() {
	frameUp = new Element();
	frameUp->addFrameFileFromData("/windows/frame_up.png");
	frameUp->setFadeIn(1000);
	
	frameDown = new Element();
	frameDown->setY(World::height);
	frameDown->setVAlign(VALIGN_BOTTOM);
	frameDown->addFrameFileFromData("/windows/frame_down.png");
	frameDown->setFadeIn(1000);
	
	bgText = new Element();
	bgText->setXY(590, 95);
	bgText->addFrameSurface(Primitives::GetInstance()->rectangle(190, 475, 0, 0, 0));
	bgText->setAlpha(160);
	
}

void SceneInfoTown::load() {
	
	ProgressBar *pb = new ProgressBar(4, 200, 16, 255, 255, 255);
	pb->setBg((string)DATA_DIR + "/title.png");
	pb->setBgBar((string)DATA_DIR + "/bg_barprogress.png");
    pb->setPositionBar(World::width/2, 300);	
	
	pb->setText("font-texts", Language::GetInstance()->getText("loading_objects"));
	pb->draw();
	
	initialize();

	statusScene = SCENE_INFOTOWN_MAIN;
		
	map.hasMap = false;
	map.file = "";
	map.title1 = "";
	map.text1 = "";
	map.title2 = "";
	map.text2 = "";
	
	txtActive = "";
	bActive = 0;
	nButtons = 0;
	
	cycles = 0;

	ActionAnimation *fadein = new ActionAnimation("setfadein", 0);
	fadein->addParameter("para1", "250");
		
	ObjectAnimation* bg = new ObjectAnimation();
	bg->setType("element");
	bg->getElement()->show();

	bg->getElement()->addFrameFileFromData("/town_info/screens.png");
	bg->getElement()->setIndexZ(4);
	
	bg->addAction(fadein);
	this->addObjectAnimation(bg);
	
	fadein->addParameter("para1", "1000");
	
	ObjectAnimation* blackTitle = new ObjectAnimation();
	blackTitle->setType("element");
	blackTitle->getElement()->setXY(100, 10);
	blackTitle->getElement()->show();

	blackTitle->getElement()->addFrameSurface(Primitives::GetInstance()->rectangle(350, 90, 0, 0, 0));
	blackTitle->getElement()->setIndexZ(2);
	
	this->addObjectAnimation(blackTitle);
	
	ObjectAnimation* blackText = new ObjectAnimation();
	blackText->setType("element");
	blackText->getElement()->setXY(140, 450);
	blackText->getElement()->show();

	blackText->getElement()->addFrameSurface(Primitives::GetInstance()->rectangle(310, 90, 0, 0, 0));
	blackText->getElement()->setIndexZ(2);
	
	this->addObjectAnimation(blackText);
		
	ObjectAnimation* space = new ObjectAnimation();
	space->setType("element");
	space->getElement()->setX(870);
	space->getElement()->setAlign(ALIGN_RIGHT);
	space->getElement()->hide();

	space->getElement()->addFrameFileFromData("/town_info/space.png");
	space->getElement()->setIndexZ(0);
	
	
	space->addAction(new ActionAnimation("show", 800));
	ActionAnimation *fadeinSpace = new ActionAnimation("setfadein", 800);
	fadeinSpace->addParameter("para1", "200");
	space->addAction(fadeinSpace);
	
	string t = "14000";
	
	ActionAnimation *space1 = new ActionAnimation("setmovementnormal", atoi(t.c_str())*0);
	space1->addParameter("para1", "840");
	space1->addParameter("para2", "20");
	space1->addParameter("para3", t);
	space1->setTimeRepeat(atoi(t.c_str())*4);
	
	ActionAnimation *space2 = new ActionAnimation("setmovementnormal", atoi(t.c_str())*1);
	space2->addParameter("para1", "800");
	space2->addParameter("para2", "0");
	space2->addParameter("para3", t);
	space2->setTimeRepeat(atoi(t.c_str())*4);
	
	ActionAnimation *space3 = new ActionAnimation("setmovementnormal", atoi(t.c_str())*2);
	space3->addParameter("para1", "840");
	space3->addParameter("para2", "-20");
	space3->addParameter("para3", t);
	space3->setTimeRepeat(atoi(t.c_str())*4);
	
	ActionAnimation *space4 = new ActionAnimation("setmovementnormal", atoi(t.c_str())*3);
	space4->addParameter("para1", "880");
	space4->addParameter("para2", "0");
	space4->addParameter("para3", t);
	space4->setTimeRepeat(atoi(t.c_str())*4);
	
	space->addAction(space1);
	space->addAction(space2);
	space->addAction(space3);
	space->addAction(space4);
	
	this->addObjectAnimation(space);
		
	ObjectAnimation* elvis = new ObjectAnimation();
	elvis->setName("elvis");
	elvis->setType("element");
	elvis->getElement()->setXY(425, 380);
	elvis->getElement()->show();

	elvis->getElement()->addRangeFramesFromData("town_info/elvis", "png", 0, 4);
	
	Animation a;
	a.setName("move");
	a.setCyclesBetweenFrames(8);
	a.addRangeFrame(0, 4, 1);
	elvis->getElement()->addAnimation(a);
	
	elvis->getElement()->setIndexZ(6);
		
	ActionAnimation *actElvis1 = new ActionAnimation();
	actElvis1->function = "swapplaystop";
	actElvis1->cycle = 0;
	actElvis1->cyclesRepeat = 200;
	
	elvis->addAction(fadein);
	elvis->addAction(actElvis1);
	this->addObjectAnimation(elvis);
	
	ObjectAnimation* rocket = new ObjectAnimation();
	rocket->setType("element");
	rocket->getElement()->setRot(-10);
	rocket->getElement()->setXY(619, 454);
	rocket->getElement()->setAlign(ALIGN_CENTER);
	rocket->getElement()->setVAlign(VALIGN_CENTER);
	rocket->getElement()->show();

	rocket->getElement()->addFrameFileFromData("/town_info/rocket.png");
	rocket->getElement()->setIndexZ(0);
	
	rocket->addAction(fadein);
	
	ActionAnimation *rocket1 = new ActionAnimation("setrotationnormal", 1000);
	rocket1->addParameter("para1", "10");
	rocket1->addParameter("para2", "5000");
	rocket1->setTimeRepeat(10000);
	rocket->addAction(rocket1);
	
	ActionAnimation *rocket2 = new ActionAnimation("setrotationnormal", 6000);
	rocket2->addParameter("para1", "-10");
	rocket2->addParameter("para2", "5000");
	rocket2->setTimeRepeat(10000);
	rocket->addAction(rocket2);
	
	this->addObjectAnimation(rocket);
	
	ObjectAnimation* lights = new ObjectAnimation();
	lights->setType("element");
	lights->getElement()->setXY(0, 600);
	lights->getElement()->setVAlign(VALIGN_BOTTOM);
	lights->getElement()->show();

	lights->getElement()->addRangeFramesFromData("town_info/light", "png", 0, 4);
	
	Animation b;
	b.setName("move");
	b.setCyclesBetweenFrames(60);
	b.addFrame(0);
	b.addFrame(1);
	b.addFrame(3);
	b.addFrame(2);
	b.addFrame(3);
	b.addFrame(4);
	b.addFrame(2);
	b.addFrame(1);	
	b.addFrame(4);	
	b.addFrame(3);	
	lights->getElement()->addAnimation(b);
	
	lights->getElement()->setIndexZ(7);
	
	lights->addAction(fadein);
	this->addObjectAnimation(lights);
	
	ObjectAnimation* pino = new ObjectAnimation();
	pino->setName("pino");
	pino->setType("element");
	pino->getElement()->setXY(481, 70);
	pino->getElement()->show();

	pino->getElement()->addRangeFramesFromData("town_info/pino", "png", 0, 4);
	
	Animation d;
	d.setName("move");
	d.setCyclesBetweenFrames(20);
	d.addRangeFrame(0, 4, 1);
	d.addRangeFrame(3, 1, -1);
	pino->getElement()->addAnimation(d);
	
	pino->getElement()->setIndexZ(8);
	
	pino->addAction(fadein);
	this->addObjectAnimation(pino);
	
	ObjectAnimation* interferences = new ObjectAnimation();
	interferences->setName("interferences");
	interferences->setType("element");
	interferences->getElement()->setAlign(ALIGN_CENTER);
	interferences->getElement()->setVAlign(VALIGN_CENTER);
	interferences->getElement()->setXY(640, 300);
	interferences->getElement()->show();

	interferences->getElement()->addFrameFileFromData("/town_info/interferences.png");
	
	interferences->getElement()->setIndexZ(3);
	
	interferences->addAction(fadein);
	this->addObjectAnimation(interferences);
	
	upArrow = new Element();
	upArrow->setXY(417, 169);
	upArrow->addFrameFileFromData("/town_info/scroll_up.png");
	upArrow->setIndexZ(3);
	upArrow->setBlinking(30);
	upArrow->setActiveBlinking(true);
	upArrow->setRGB(190, 195, 53);
	upArrow->hide();
	
	upArrow->setFadeIn(1000);
	
	downArrow = new Element();
	downArrow->setXY(417, 307);
	downArrow->setFlop(true);
	downArrow->addFrameFileFromData("/town_info/scroll_up.png");
	downArrow->setIndexZ(3);
	downArrow->setBlinking(30);
	downArrow->setActiveBlinking(true);
	downArrow->setRGB(190, 195, 53);
	
	downArrow->setFadeIn(1000);
	
	pb->setText("font-texts", Language::GetInstance()->getText("loading_buttons"));
	pb->draw();
	
	up = new Button();
	up->setScales(1.0, 1.15);
	up->setXY(470, 145);
	up->setAlign(ALIGN_CENTER);
	up->setVAlign(VALIGN_CENTER);
	
	up->imageOut(WorkingSurfaces::GetInstance()->surfaceFromImage((string)DATA_DIR + "/town_info/up.png"));
	up->setAnimation("out");

	up->setIndexZ(7);
	
	up->setFadeIn(1000);
	
	down = new Button();
	down->setScales(1.0, 1.15);
	down->setXY(470, 350);
	down->setAlign(ALIGN_CENTER);
	down->setVAlign(VALIGN_CENTER);
	
	down->imageOut(WorkingSurfaces::GetInstance()->surfaceFromImage((string)DATA_DIR + "/town_info/down.png"));
	down->setAnimation("out");

	down->setIndexZ(7);
	
	down->setFadeIn(1000);
		
	nButtons = 0;
	
	bContinue = new Button();	
	bContinue->setScales(0.65, 0.75);
	bContinue->setIndexZ(7);
	bContinue->setAlign(ALIGN_CENTER);
	bContinue->setVAlign(VALIGN_CENTER);
	bContinue->setXY(685, 530);

	bContinue->addFrameFileFromData("/town_info/" + Language::GetInstance()->getFilename("continue_0", "png"));
	bContinue->addFrameFileFromData("/town_info/" + Language::GetInstance()->getFilename("continue_1", "png"));
	bContinue->addFrameFileFromData("/town_info/" + Language::GetInstance()->getFilename("continue_2", "png"));
	bContinue->addFrameFileFromData("/town_info/" + Language::GetInstance()->getFilename("continue_3", "png"));
	
	Animation c;
	c.setName("out");
	c.setCyclesBetweenFrames(12);
	c.addRangeFrame(0, 3, 1);
	bContinue->addAnimation(c);
	
	bContinue->setAnimation("out");

	bContinue->OnClick = bContinue_SceneInfoTown_OnClick;
	
	titleTexts = new Element();
	titleTexts->setXY(299, 487);
	titleTexts->setAlign(ALIGN_CENTER);
	titleTexts->setVAlign(VALIGN_CENTER);
	titleTexts->setCurrentScale(0.55);
	titleTexts->setIndexZ(3);
	titleTexts->setRot(-2);
	titleTexts->setFadeIn(1000);
	
	pb->setText("font-texts", Language::GetInstance()->getText("loading_sounds"));
	pb->draw();
	
	// sounds
	
	Sounds::GetInstance()->addSoundFromData("music", "music", "sound/music_town.ogg");
	Sounds::GetInstance()->addSoundFromData("ovni_sound", "low_music", "sound/ovni_sound.ogg");
	Sounds::GetInstance()->getSound("music")->play(1, -1, 2000);
	
	pb->setText("font-texts", Language::GetInstance()->getText("loading_animation"));
	pb->draw();

	parseXMLInfoTown((char*)Missions::GetInstance()->pathXMLLevel().c_str(), this);
	organizeButtons();
	
	if (map.hasMap) { 
		setStatusScene(SCENE_INFOTOWN_MAP);
		loadMapElements();
	} else {
		setStatusScene(SCENE_INFOTOWN_MAIN);
    }
	
	txtActive = "txt0";
	bActive = 0;
	
	titleTexts->setCurrentFrame(0);

	loadPhotos(WorkingData::GetInstance()->getPath(Missions::GetInstance()->pathXMLLevel()) + "photos");

	delete pb;

}

void SceneInfoTown::upText() {
	if (nButtons>0) {
		Element *obj = getObjectAnimation(txtActive)->getElement();
		if (obj->getY()<150) {
			obj->addY(10);
			downArrow->show();
		} else {
			upArrow->hide();
			obj->setY(150);
		}
	}
}

void SceneInfoTown::downText() {
	if (nButtons>0) {
		Element *obj = getObjectAnimation(txtActive)->getElement();
		if (obj->getY()+obj->getHeight()>350) {
			upArrow->show();
			obj->addY(-10);
		} else {
			downArrow->hide();
		}
	}
}

void SceneInfoTown::loadPhotos(string path) {
	DIR *pdir;
	struct dirent *pent;
	
	photos = new Slide();
	photos->setXY(640, 300);
	photos->setAlign(ALIGN_CENTER);
	photos->setVAlign(VALIGN_CENTER);
	photos->setIndexZ(2);
	photos->setTimeNextFrame(8000);
	photos->setMlFade(600);
	photos->setFadeIn(2000);
	
	pdir=opendir(path.c_str());
	if (pdir) {
        while ((pent=readdir(pdir))) {
             string ext = WorkingData::GetInstance()->getExtension(pent->d_name);
             if ( ext == "JPG" || ext == "PNG" ) {
                  photos->addFrameFile(path + "/" + pent->d_name);
             }
        }
        closedir(pdir);
    }
    
    if (photos->getFrames()==0) {
        photos->addFrameSurface(Primitives::GetInstance()->rectangle(1, 1, 0, 0, 0));
    }
	
	photos->setCurrentScale(0.0);
	photos->setScaleGL(1.0, 2000);
	
}

void SceneInfoTown::organizeButtons() {
	switch (nButtons) {
		case 2:
			bInfo0->setXY(200, 385);
			bInfo1->setXY(300, 379);
		
			bInfo0->setFadeIn(1000);
			bInfo1->setFadeIn(1000);
		break;
		case 3:
			bInfo0->setXY(170, 385);
			bInfo1->setXY(250, 382);		
			bInfo2->setXY(330, 379);
		
			bInfo0->setFadeIn(1000);
			bInfo1->setFadeIn(1000);
			bInfo2->setFadeIn(1000);
		break;
		case 4:
			bInfo0->setXY(136, 385);
			bInfo1->setXY(212, 383);		
			bInfo2->setXY(290, 381);
			bInfo3->setXY(364, 379);
		
			bInfo0->setFadeIn(1000);
			bInfo1->setFadeIn(1000);
			bInfo2->setFadeIn(1000);
			bInfo3->setFadeIn(1000);
		break;
	}
	if (nButtons>0) bInfo0->setActive(true);
}

void SceneInfoTown::addButton(int type, string alt) {
	char tmp[256];
	switch (nButtons) {
		case 0:
			
			bInfo0 = new RadioButton(NULL);
			bInfo0->setScales(1.0, 1.03);
			bInfo0->addParameter("position", "0");
		
			bInfo0->setAlt(alt, ALIGN_CENTER, VALIGN_BOTTOM);
		
			sprintf(tmp, "%s/town_info/button%d_off.png", DATA_DIR, type);
			bInfo0->imageInactive( WorkingSurfaces::GetInstance()->surfaceFromImage(tmp) );
			sprintf(tmp, "%s/town_info/button%d_on.png", DATA_DIR, type);
			bInfo0->imageActive( WorkingSurfaces::GetInstance()->surfaceFromImage(tmp) );
		
			bInfo0->setIndexZ(7);
		
		break;
		case 1:
			
			bInfo1 = new RadioButton(bInfo0);
			bInfo1->setScales(1.0, 1.03);
			bInfo1->addParameter("position", "0");
		
			bInfo1->setAlt(alt, ALIGN_CENTER, VALIGN_BOTTOM);
		
			sprintf(tmp, "%s/town_info/button%d_off.png", DATA_DIR, type);
			bInfo1->imageInactive( WorkingSurfaces::GetInstance()->surfaceFromImage(tmp) );
			sprintf(tmp, "%s/town_info/button%d_on.png", DATA_DIR, type);
			bInfo1->imageActive( WorkingSurfaces::GetInstance()->surfaceFromImage(tmp) );

			bInfo1->setIndexZ(7);
		
		break;
		case 2:
			
			bInfo2 = new RadioButton(bInfo0);
			bInfo2->setScales(1.0, 1.03);
			bInfo2->addParameter("position", "0");
		
			bInfo2->setAlt(alt, ALIGN_CENTER, VALIGN_BOTTOM);
		
			sprintf(tmp, "%s/town_info/button%d_off.png", DATA_DIR, type);
			bInfo2->imageInactive( WorkingSurfaces::GetInstance()->surfaceFromImage(tmp) );
			sprintf(tmp, "%s/town_info/button%d_on.png", DATA_DIR, type);
			bInfo2->imageActive( WorkingSurfaces::GetInstance()->surfaceFromImage(tmp) );
		
			bInfo2->setIndexZ(7);
		
		break;
		case 3:
			
			bInfo3 = new RadioButton(bInfo0);
			bInfo3->setScales(1.0, 1.03);
			bInfo3->addParameter("position", "0");
		
			bInfo3->setAlt(alt, ALIGN_CENTER, VALIGN_BOTTOM);

			sprintf(tmp, "%s/town_info/button%d_off.png", DATA_DIR, type);
			bInfo3->imageInactive( WorkingSurfaces::GetInstance()->surfaceFromImage(tmp) );
			sprintf(tmp, "%s/town_info/button%d_on.png", DATA_DIR, type);
			bInfo3->imageActive( WorkingSurfaces::GetInstance()->surfaceFromImage(tmp) );
		
			bInfo3->setIndexZ(7);
		
		break;
	}
	
	nButtons++;
}

/**********************
  DRAWSCENE MAP
**********************/

void SceneInfoTown::drawSceneMap () {
	
	verifyOverElements_Map();
	for (int i=0; i<MAX_INDEXZ; i++) {
		drawSceneMapByIndexZ(i);
	}
	
}

void SceneInfoTown::drawSceneMapByIndexZ(int z) {
	if (bgMap->getIndexZ()==z) {
		bgMap->draw();
	}
	if (frameUp->getIndexZ()==z) {
		frameUp->draw();
	}
	if (frameDown->getIndexZ()==z) {
		frameDown->draw();
	}
	if (bgText->getIndexZ()==z) {
		bgText->draw();
	}
	if (map.title1!="") {
		if (title1Map->getIndexZ()==z) {
			title1Map->draw();
		}
	}
	if (map.text1!="") {
		if (text1Map->getIndexZ()==z) {
			text1Map->draw();
		}
	}
	if (map.title2!="") {
		if (title2Map->getIndexZ()==z) {
			title2Map->draw();
		}
	}
	if (map.text2!="") {
		if (text2Map->getIndexZ()==z) {
			text2Map->draw();
		}
	}
	if (bContinue->getIndexZ()==z) {
		bContinue->draw();
	}
}

void SceneInfoTown::verifyOverElements_Map() {
	bContinue->onOver();	
}

void SceneInfoTown::verifyClickElements_Map() {
	if (bContinue->isOnMouseOver()) {
		bContinue->OnClick(this, bContinue);
	}
}

/**********************
  DRAWSCENE MAIN
**********************/

void SceneInfoTown::drawSceneMain () {

	
	verifyOverElements_Main();
	for (int i=0; i<MAX_INDEXZ; i++) {
		drawSceneMainByIndexZ(i);
	}
	cycles++;
	
}

void SceneInfoTown::drawSceneMainByIndexZ(int z) {
	int i;
	for (i=0; i<(int)objectsanimation.size(); i++) {
		if (objectsanimation[i]->getElement()->getIndexZ()==z) {
			if ((int)objectsanimation[i]->verifyActions(cycles).size() > 0) {
				for (int j=0; j<(int)objectsanimation[i]->verifyActions(cycles).size(); j++) {
					makeAction_Object(objectsanimation[i], objectsanimation[i]->verifyActions(cycles)[j]);
				}
			}
			objectsanimation[i]->getElement()->draw();
		}
	}
	
	if (upArrow->getIndexZ()==z) {
		upArrow->draw();
	}
	
	if (downArrow->getIndexZ()==z) {
		downArrow->draw();
	}
	
	if (title->getIndexZ()==z) {
		title->draw();
	}

	if (titleTexts->getIndexZ()==z) {
		titleTexts->draw();
	}
	
	if (photos->getIndexZ()==z) {
		photos->draw();
	}
	
	if (up->getIndexZ()==z) {
		up->draw();
	}
	
	if (down->getIndexZ()==z) {
		down->draw();
	}
	
	if (bContinue->getIndexZ()==z) {
		bContinue->draw();
	}

	if (nButtons>1) {
		for (int i=0; i<nButtons; i++) {
			switch (i) {
				case 0:
					if (bInfo0->getIndexZ()==z) {
						bInfo0->draw();
					}
				break;
				case 1:
					if (bInfo1->getIndexZ()==z) {
						bInfo1->draw();
					}
				break;
				case 2:
					if (bInfo2->getIndexZ()==z) {
						bInfo2->draw();
					}
				break;
				case 3:
					if (bInfo3->getIndexZ()==z) {
						bInfo3->draw();
					}
				break;
			}
		}
	}
}	

void SceneInfoTown::verifyOverElements_Main() {
	int i;
	for (i=0; i<(int)objectsanimation.size(); i++) {
		if (objectsanimation[i]->getType()=="button") {
			Button *b = (Button*)objectsanimation[i]->getElement();
			b->onOver();
		}
	}
	bContinue->onOver();
	up->onOver();
	down->onOver();
	
	if (nButtons>1) {
		for (int i=0; i<nButtons; i++) {
			switch (i) {
				case 0:
					bInfo0->onOver();
				break;
				case 1:
					bInfo1->onOver();
				break;
				case 2:
					bInfo2->onOver();
				break;
				case 3:
					bInfo3->onOver();
				break;
			}
		}
	}
	
}	

void SceneInfoTown::activeButton(int i) {
	switch (i) {
		case 0:
			bInfo0->setActive(true);
			if (txtActive!="txt0") {
				if (getObjectAnimation(txtActive)!=NULL) {
					getObjectAnimation(txtActive)->getElement()->setFadeOut(600);
					getObjectAnimation("txt0")->getElement()->setFadeIn(600);
					getObjectAnimation("txt0")->getElement()->setX(110);
					getObjectAnimation("txt0")->getElement()->setY(150);
					txtActive = "txt0";
					bActive = 0;
					titleTexts->setCurrentFrame(0);
					upArrow->hide();
					downArrow->show();
				}
			}
		break;
		case 1:
			bInfo1->setActive(true);
			if (txtActive!="txt1") {
				if (getObjectAnimation(txtActive)!=NULL) {
					getObjectAnimation(txtActive)->getElement()->setFadeOut(600);
					getObjectAnimation("txt1")->getElement()->setFadeIn(600);
					getObjectAnimation("txt1")->getElement()->setX(110);
					getObjectAnimation("txt1")->getElement()->setY(150);
					txtActive = "txt1";
					bActive = 1;
					titleTexts->setCurrentFrame(1);
					upArrow->hide();
					downArrow->show();
				}
			}
		break;
		case 2:
			bInfo2->setActive(true);
			if (txtActive!="txt2") {
				if (getObjectAnimation(txtActive)!=NULL) {
					getObjectAnimation(txtActive)->getElement()->setFadeOut(600);
					getObjectAnimation("txt2")->getElement()->setFadeIn(600);
					getObjectAnimation("txt2")->getElement()->setX(110);
					getObjectAnimation("txt2")->getElement()->setY(150);
					txtActive = "txt2";
					bActive = 2;
					titleTexts->setCurrentFrame(2);
					upArrow->hide();
					downArrow->show();
				}
			}
		break;
		case 3:
			bInfo3->setActive(true);
			if (txtActive!="txt3") {
				if (getObjectAnimation(txtActive)!=NULL) {
					getObjectAnimation(txtActive)->getElement()->setFadeOut(600);
					getObjectAnimation("txt3")->getElement()->setFadeIn(600);
					getObjectAnimation("txt3")->getElement()->setX(110);
					getObjectAnimation("txt3")->getElement()->setY(150);
					txtActive = "txt3";
					bActive = 3;
					titleTexts->setCurrentFrame(3);
					upArrow->hide();
					downArrow->show();
				}
			}
		break;
	}
}

void SceneInfoTown::verifyClickElements_Main() {
	int i, j;
	for (i=0; i<(int)objectsanimation.size(); i++) {
		if (objectsanimation[i]->getType()=="button") {
			Button *b = (Button*)objectsanimation[i]->getElement();
			if (b->isOnMouseOver()) {
				for (j=0; j<(int)objectsanimation[i]->actionsOnClick.size(); j++) {
					if (objectsanimation[i]->actionsOnClick[j]->nameObjetive!="") {
						makeAction_Object(getObjectAnimation(objectsanimation[i]->actionsOnClick[j]->nameObjetive), objectsanimation[i]->actionsOnClick[j]);
					} else {
						makeAction_Object(objectsanimation[i], objectsanimation[i]->actionsOnClick[j]);
					}
				}
			}	
		}
	}
	
	if (bContinue->isOnMouseOver()) {
		bContinue->OnClick(this, bContinue);
	}
	
	if (up->isOnMouseOver()) {
		upText();
	}
	
	if (down->isOnMouseOver()) {
		downText();
	}
	
	if (nButtons>1) {
		for (int i=0; i<nButtons; i++) {
			switch (i) {
				case 0:
					if (bInfo0->isOnMouseOver()) {
                        Sounds::GetInstance()->getSound("beep1")->play(2, 0);
						activeButton(0);
					}
				break;
				case 1:
					if (bInfo1->isOnMouseOver()) {
                        Sounds::GetInstance()->getSound("beep1")->play(2, 0);
						activeButton(1);
					}
				break;
				case 2:
					if (bInfo2->isOnMouseOver()) {
                        Sounds::GetInstance()->getSound("beep1")->play(2, 0);
						activeButton(2);
					}
				break;
				case 3:
					if (bInfo3->isOnMouseOver()) {
                        Sounds::GetInstance()->getSound("beep1")->play(2, 0);
						activeButton(3);
					}
				break;
			}
		}
	}
	
}

bool SceneInfoTown::drawScene() {
	
	glClear(GL_COLOR_BUFFER_BIT); // | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	
	drawCommonsScene ();
	
	switch(statusScene) {
	
		case SCENE_INFOTOWN_MAIN:
	
        	drawSceneMain();
        
        	// Comprobando teclas para opciones			
        	{ SDL_Event event;
        		while ( SDL_PollEvent(&event) ) {
        			if ( event.type == SDL_QUIT ) {
        				setNextScene("quit");
        				return true;
        			}
        			
        			if ( event.type == SDL_KEYDOWN ) {
        				if ( ( event.key.keysym.sym == SDLK_ESCAPE ) ||
							( event.key.keysym.sym == SDLK_RETURN ) ) {
                        	Sounds::GetInstance()->getSound("music")->stop(2000);
                        	Sounds::GetInstance()->getSound("ovni_sound")->stop(2000);
                        	goToScene("game", 2000, SCENE_TRANSITION_FADEOUT);
        				}
        				if ( event.key.keysym.sym == SDLK_UP ) {
							upText();
        				}
						if ( event.key.keysym.sym == SDLK_DOWN ) {
							downText();
        				}
        				if ( event.key.keysym.sym == SDLK_LEFT ) {
							activePreviousButton();
        				}
						if ( event.key.keysym.sym == SDLK_RIGHT ) {
							activeNextButton();
        				}
        			}
        			
        			if ( event.type == SDL_MOUSEBUTTONDOWN ) {
        				if ( ( event.button.button == SDL_BUTTON_LEFT ) ) {
        					verifyClickElements_Main();
        				}
        				if ( ( event.button.button == 4 ) ) {
        					upText();
        				}
						if ( ( event.button.button == 5 ) ) {
        					downText();
        				}
        			}
        				
        		}
        	}
        	
       	break;
			
		case SCENE_INFOTOWN_MAP:
	
        	drawSceneMap();
        
        	// Comprobando teclas para opciones			
        	{ SDL_Event event;
        		while ( SDL_PollEvent(&event) ) {
        			if ( event.type == SDL_QUIT ) {
        				setNextScene("quit");
        				return true;
        			}
        			
        			if ( event.type == SDL_KEYDOWN ) {
        				if ( ( event.key.keysym.sym == SDLK_ESCAPE ) ||
							( event.key.keysym.sym == SDLK_RETURN ) ) {
                        	setStatusScene(SCENE_INFOTOWN_MAIN);
        				}
        			}
        			
        			if ( event.type == SDL_MOUSEBUTTONDOWN ) {
        				if ( ( event.button.button == SDL_BUTTON_LEFT ) ) {
        					verifyClickElements_Map();
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

void SceneInfoTown::unLoad() {

	unLoadCommons();
	
	statusScene = SCENE_INFOTOWN_MAIN;
	
	int i;
	for (i=0; i<(int)objectsanimation.size(); i++) {
		delete objectsanimation[i];
	}
	
	objectsanimation.clear();
	
	Sounds::GetInstance()->unLoad();
	
	delete titleTexts;
	if (nButtons>1) {
		for (int i=0; i<nButtons; i++) {
			switch (i) {
				case 0:
					delete bInfo0;
				break;
				case 1:
					delete bInfo1;
				break;
				case 2:
					delete bInfo2;
				break;
				case 3:
					delete bInfo3;
				break;
			}
		}
	}
	
    delete photos;
    delete up;
    delete down;
    delete title;
    delete bContinue;
	
	delete upArrow;
	delete downArrow;
	
	if (map.hasMap) {
		delete bgMap;
		delete frameUp;
		delete frameDown;
		if (map.title1!="")delete title1Map;
		if (map.text1!="")delete text1Map;
		if (map.title2!="")delete title2Map;
		if (map.text2!="")delete text2Map;
	}
    
	isLoad = false;
	
	Debug::GetInstance()->writeText("Escenario descargado");

}

/*****************************
** FUNCIONES PARA CARGAR SCREEN
******************************/

typedef struct
{
	SceneInfoTown *scene;
	bool firstInformation;
	bool multilanguage;
} InfoTownXML;


static void startInfoTownXML(void *userData, const char *el, const char **attr) {
	InfoTownXML* data = (InfoTownXML*)userData;
	int i;
	
	if (strcmp(el, "multilanguage") == 0) {
		for (i = 0; attr[i]; i += 2) {
			if ( (strcmp(attr[i], "value") == 0) && (strcmp(attr[i+1], "true") == 0) ) {
				data->multilanguage = true;
			}
		}		
	} else if (strcmp(el, "information") == 0) {
		
		string lang="", title="", text="";
		int button=0;
		

		for (i = 0; attr[i]; i += 2) {
			if (strcmp(attr[i], "button") == 0) {
				button = atoi(attr[i+1]);
			} else if (strcmp(attr[i], "title") == 0) {
				title = attr[i+1];
			} else if (strcmp(attr[i], "text") == 0) {
				text = attr[i+1];				
			} else if (strcmp(attr[i], "lang") == 0) {
				lang = attr[i+1];				
			}
		}
		
		bool todo =false;
		
		if (data->multilanguage) {
			if (lang == Language::GetInstance()->getLang()) {
				todo = true;
			}
		} else {
			todo = true;
		}
		
		
		if ( todo ) {
			
			char tmp[8];
			sprintf(tmp, "txt%d", data->scene->getNButtons());
			
			data->scene->addButton(button, title);
			data->scene->titleTexts->addFrameText("font-computer", title, ALIGN_CENTER);			
			
			ObjectAnimation* aux = new ObjectAnimation();
			aux->setName(tmp);
			aux->setType("element");
			aux->getElement()->setX(110);
			aux->getElement()->setY(150);
			aux->getElement()->show();
			aux->getElement()->setAlpha(0);
			aux->getElement()->setRGB(228, 231, 149);
			if (data->firstInformation)	{
				aux->addAction(new ActionAnimation("show", 1000));
				ActionAnimation *aa = new ActionAnimation("setfadein", 1000);
				aa->addParameter("para1", "200");
				aux->addAction(aa);
				data->firstInformation = false;
			}
		
			aux->getElement()->addFrameSurface(Fonts::GetInstance()->getSurface_TextBitMap("font-texts", 310, ALIGN_LEFT, text));
			aux->getElement()->setIndexZ(0);
			
			data->scene->addObjectAnimation(aux);
			
		}
		
	} else if (strcmp(el, "town") == 0) {
		for (i = 0; attr[i]; i += 2) {
			if (strcmp(attr[i], "name") == 0) {
                                
				data->scene->title = new MarqueeElement();
				data->scene->title->setCurrentScale(0.8);
				data->scene->title->setX(270);
				data->scene->title->setY(55);
             	data->scene->title->setAlign(ALIGN_CENTER);
	            data->scene->title->setVAlign(VALIGN_CENTER);
				data->scene->title->setRot(1);
				data->scene->title->setRGB(234, 238, 53);
			
				data->scene->title->setText("font-computer", attr[i+1], 11);
				data->scene->title->setIndexZ(3);
				
				data->scene->title->setFadeIn(2000);
				
			} else if (strcmp(attr[i], "province") == 0) {
				data->scene->titleProvince = attr[i+1];
			} else if (strcmp(attr[i], "nickname") == 0) {
				//Board::GetInstance()->town.nickname = attr[i+1];
			}
		}
	} else if (strcmp(el, "map") == 0) {
        data->scene->map.hasMap = true;
		for (i = 0; attr[i]; i += 2) {
			if (strcmp(attr[i], "file-fromdata") == 0) {
                
				data->scene->map.file = attr[i+1];
				
				data->scene->bgMap = new Element();
				data->scene->bgMap->addFrameFileFromData(data->scene->map.file);
				data->scene->bgMap->setFadeIn(1000);
				
			} else if (strcmp(attr[i], "file-fromlevel") == 0) {
                
				data->scene->map.file = attr[i+1];
				
				data->scene->bgMap = new Element();
				data->scene->bgMap->addFrameFile(Missions::GetInstance()->currentLevel->getPath() + data->scene->map.file);
				data->scene->bgMap->setFadeIn(1000);
				
			}
		}
	} else if (strcmp(el, "texts-map") == 0) {
		
		string text1="", text2="", title1="", title2="", lang="es";
		int distance = 200;
		
		for (i = 0; attr[i]; i += 2) {
			if (strcmp(attr[i], "title-1") == 0) {
				
				title1 = attr[i+1];

			} else if (strcmp(attr[i], "text-1") == 0) {
				
				text1 = attr[i+1];

			} else if (strcmp(attr[i], "title-2") == 0) {
				
				title2 = attr[i+1];
				
			} else if (strcmp(attr[i], "text-2") == 0) {
				
				text2 = attr[i+1];
				
			} else if (strcmp(attr[i], "lang") == 0) {
				
				lang = attr[i+1];
				
			} else if (strcmp(attr[i], "distance-second-text") == 0) {
				
				distance = atoi(attr[i+1]);
				
			}
		}
		
		bool todo =false;
		
		if (data->multilanguage) {
			if (lang == Language::GetInstance()->getLang()) {
				todo = true;
			}
		} else {
			todo = true;
		}
		
		if (todo) {
			data->scene->map.hasMap = true;
			
			if (title1!="") {
				data->scene->map.title1 = title1;
				
				data->scene->title1Map = new Element();
				data->scene->title1Map->setRGB(234, 238, 53);
				data->scene->title1Map->setCurrentScale(0.8);
				data->scene->title1Map->setXY(580, 105);
				data->scene->title1Map->addFrameText("font-titles", data->scene->map.title1, ALIGN_LEFT);
				data->scene->title1Map->setFadeIn(1000);
			}
			
			if (text1!="") {
				data->scene->map.text1 = text1;
				
				data->scene->text1Map = new Element();
				data->scene->text1Map->setCurrentScale(0.77);
				data->scene->text1Map->setXY(600, 145);
				data->scene->text1Map->addFrameText("font-texts", data->scene->map.text1, ALIGN_LEFT, 180);
				data->scene->text1Map->setFadeIn(1000);
			}
			
			if (title2!="") {
				data->scene->map.title2 = title2;
				
				data->scene->title2Map = new Element();
				data->scene->title2Map->setRGB(234, 238, 53);
				data->scene->title2Map->setCurrentScale(0.8);
				data->scene->title2Map->setXY(580, 105+distance);
				data->scene->title2Map->addFrameText("font-titles", data->scene->map.title2, ALIGN_LEFT);
				data->scene->title2Map->setFadeIn(1000);
			}
			
			if (text2!="") {
				data->scene->map.text2 = text2;
				
				data->scene->text2Map = new Element();
				data->scene->text2Map->setCurrentScale(0.77);
				data->scene->text2Map->setXY(600, 145+distance);
				data->scene->text2Map->addFrameText("font-texts", data->scene->map.text2, ALIGN_LEFT, 180);
				data->scene->text2Map->setFadeIn(1000);
			}
		}
		
	}

}

static void endInfoTownXML(void *userData, const char *el)
{
	//InfoTownXML* data = (InfoTownXML*)userData;

}

void parseXMLInfoTown(char fileXML[128], SceneInfoTown *s) {
	char buffer[8192];
	int done;
	
	InfoTownXML data;
	data.scene = s;
	data.firstInformation = true;
	data.multilanguage = false;
	
	XML_Parser p = XML_ParserCreate(NULL);
	if (! p) {
		printf("Podra no tener suficiente memoria para el parser\n");
	}

	XML_SetUserData(p, &data);	
	XML_SetElementHandler(p, startInfoTownXML, endInfoTownXML);

  	FILE *file = fopen(fileXML, "r");
	if(!file)
		printf("Error abriendo archivo XML: %s\n", fileXML);
	
	do
	{
		size_t len = fread(buffer, 1, sizeof(buffer), file);
		done = len < sizeof(buffer);
		//printf("%s\n", buffer);
		if(!XML_Parse(p, buffer, len, done)){
			printf("Error realizando el parse\n");
		}
			//parse_error(&data, XML_ErrorString(XML_GetErrorCode(data.parser)));
	}
	while(!done);
	fclose(file);
}
