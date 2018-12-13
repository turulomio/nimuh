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
 
#include "scene_createmissions.h"

void bCreateMission_SceneCreateMission_OnClick (Scene *s, Button *b) {
	SceneCreateMission* se = (SceneCreateMission*)s;
    if ( (se->nameAuthor->getText()=="") || (se->missionName->getText()=="") ) {
        se->showMessageBox(Language::GetInstance()->getText("info"), Language::GetInstance()->getText("allobligatory"), SCENE_CREATEMISSION_NEW);
    } else {
		Mission *m = new Mission(se->getNameProject(se->missionName->getText()), se->missionName->getText());
		m->setNameAuthor(se->nameAuthor->getText());
		if (Missions::GetInstance()->addMission(m)) {
    		se->createMissionsButtons();
    		se->setStatusScene(SCENE_CREATEMISSION_MAIN);
    		Missions::GetInstance()->save();
    		Users::GetInstance()->getCurrentUser()->addMyMission(m->getDirectory());
    		Users::GetInstance()->save();
        } else {
            se->showMessageBox(Language::GetInstance()->getText("info"), Language::GetInstance()->getText("existmission"), SCENE_CREATEMISSION_NEW);
        }
    }
}

void bCreateLevel_SceneCreateMission_OnClick (Scene *s, Button *b) {
	SceneCreateMission* se = (SceneCreateMission*)s;
    if ( (se->levelName->getText()=="") || (se->provinceName->getText()=="") ) {
        se->showMessageBox(Language::GetInstance()->getText("info"), Language::GetInstance()->getText("allobligatory"), SCENE_CREATEMISSION_NEWLEVEL);
    } else {
        Level *l = new Level(se->getNameProject(se->levelName->getText()), se->levelName->getText());
        l->setProvince(se->provinceName->getText());
		if (se->tScClosed->getActive()) {
			l->setTypeScenary(SCENARY_CLOSED);
		} else {
			l->setTypeScenary(SCENARY_OPENED);
		}
		Missions::GetInstance()->currentMission->addLevel(l);
		se->createLevelsButtons(Missions::GetInstance()->currentMission);
		se->setStatusScene(SCENE_CREATEMISSION_LEVELS);
		Missions::GetInstance()->save();
    }
}

void bNewMision_SceneCreateMission_OnClick (Scene *s, Button *b) {
	SceneCreateMission* se = (SceneCreateMission*)s;
	se->missionName->setActive(true);
	se->missionName->setText("");
	se->nameAuthor->setText(Users::GetInstance()->getCurrentUser()->getName());
	se->setStatusScene(SCENE_CREATEMISSION_NEW);
}

void bNewLevel_SceneCreateMission_OnClick (Scene *s, Button *b) {
	SceneCreateMission* se = (SceneCreateMission*)s;
	se->levelName->setActive(true);
	se->levelName->setText("");
	se->provinceName->setText("");
	se->setStatusScene(SCENE_CREATEMISSION_NEWLEVEL);
}


void bBack_SceneCreateMission_OnClick (Scene *s, Button *b) {
	SceneCreateMission* se = (SceneCreateMission*)s;
	if (se->getStatusScene()==SCENE_CREATEMISSION_MAIN) {
		se->goToScene("menu", 2000, SCENE_TRANSITION_FADEOUT);
	} else if (se->getStatusScene()==SCENE_CREATEMISSION_LEVELS) {
		se->setStatusScene(SCENE_CREATEMISSION_MAIN);
	} else if (se->getStatusScene()==SCENE_CREATEMISSION_NEWLEVEL) {
		se->setStatusScene(SCENE_CREATEMISSION_LEVELS);
	} else {
		se->setStatusScene(SCENE_CREATEMISSION_MAIN);
	}
}

void bQuit_SceneCreateMission_OnClick (Scene *s, Button *b) {
	SceneCreateMission* se = (SceneCreateMission*)s;
	Sounds::GetInstance()->getSound("music_editor")->stop(2000);
	se->goToScene("menu", 2000, SCENE_TRANSITION_FADEOUT);
}

void alert_bPlayMision_SceneCreateMission_OnClick (Scene *s, Button *b, string data) {
	SceneCreateMission* se = (SceneCreateMission*)s;
	if (b->getParameter("type")=="accept") {
		Users::GetInstance()->getCurrentUser()->setLevelInMission(Missions::GetInstance()->currentMission->getDirectory(), 0);
		Users::GetInstance()->save();
		if (Missions::GetInstance()->setCurrentMissionAndLevel(Missions::GetInstance()->currentMission->getDirectory())) {
            Sounds::GetInstance()->getSound("music_editor")->stop(2000);
			se->goToScene("infotown", 2000, SCENE_TRANSITION_SCALEx2_ROTATE);
		}
	} else {
		se->setStatusSceneWithReturnSceneFromMessage();
	}
}

void bPlayMision_SceneCreateMission_OnClick (Scene *s, Button *b) {
	SceneCreateMission* se = (SceneCreateMission*)s;
	int i = atoi(se->dataMissions->getDataIndex()->getParameter("index-mission").c_str());
	if ( Missions::GetInstance()->getMission( i ) != NULL ) {
		if (Missions::GetInstance()->setCurrentMissionAndLevel(i)) {
			if (Missions::GetInstance()->currentMission->getNLevels()>0) {
				if (Missions::GetInstance()->currentLevel==NULL) {
					se->showAlert(Language::GetInstance()->getText("info"), Language::GetInstance()->getText("missionfinish"), alert_bPlayMision_SceneCreateMission_OnClick, SCENE_CREATEMISSION_MAIN);
				} else {
                    Sounds::GetInstance()->getSound("music_editor")->stop(2000);
					se->goToScene("infotown", 2000, SCENE_TRANSITION_SCALEx2_ROTATE);
				}
			} else {
				se->showMessageBox(Language::GetInstance()->getText("info"), Language::GetInstance()->getText("needlevels"), SCENE_CREATEMISSION_MAIN);
			}
		} else {
			se->showMessageBox(Language::GetInstance()->getText("info"), Language::GetInstance()->getText("needlevels"), SCENE_CREATEMISSION_MAIN);
		}
	}
}


void bEditMision_SceneCreateMission_OnClick (Scene *s, Button *b) {
	SceneCreateMission* se = (SceneCreateMission*)s;
	int i = atoi(se->dataMissions->getDataIndex()->getParameter("index-mission").c_str());
	if ( Missions::GetInstance()->getMission( i ) != NULL ) {
		se->createLevelsButtons(Missions::GetInstance()->getMission( i ));
		se->setStatusScene(SCENE_CREATEMISSION_LEVELS);
	}
}

void bPlayLevel_SceneCreateMission_OnClick (Scene *s, Button *b) {
	SceneCreateMission* se = (SceneCreateMission*)s;
	int i = atoi(b->getParameter("index").c_str());
	if ( Missions::GetInstance()->currentMission->getLevel( i ) != NULL ) {
		Users::GetInstance()->getCurrentUser()->setLevelInCurrentMission(i);
		Users::GetInstance()->save();
		se->goToScene("infotown", 2000, SCENE_TRANSITION_SCALEx2_ROTATE);
        Missions::GetInstance()->currentLevel = Missions::GetInstance()->currentMission->getLevel( i );
        Sounds::GetInstance()->getSound("music_editor")->stop(2000);
	}
}

void bEditLevel_SceneCreateMission_OnClick (Scene *s, Button *b) {
	SceneCreateMission* se = (SceneCreateMission*)s;
	int i = atoi(b->getParameter("index").c_str());
	if ( Missions::GetInstance()->currentMission->getLevel( i ) != NULL ) {
		se->goToScene("editgame", 2000, SCENE_TRANSITION_FADEOUT);
        Missions::GetInstance()->currentLevel = Missions::GetInstance()->currentMission->getLevel( i );
        Sounds::GetInstance()->getSound("music_editor")->stop(2000);
	}
}


void bUpLevel_SceneCreateMission_OnClick (Scene *s, Button *b) {
	SceneCreateMission* se = (SceneCreateMission*)s;
	int i = atoi(b->getParameter("index").c_str());
	if ( Missions::GetInstance()->currentMission->getLevel( i ) != NULL ) {
        Missions::GetInstance()->currentMission->upLevel( i );
		se->createLevelsButtons(Missions::GetInstance()->currentMission);
	}
}

void bDownLevel_SceneCreateMission_OnClick (Scene *s, Button *b) {
	SceneCreateMission* se = (SceneCreateMission*)s;
	int i = atoi(b->getParameter("index").c_str());
	if ( Missions::GetInstance()->currentMission->getLevel( i ) != NULL ) {
        Missions::GetInstance()->currentMission->downLevel( i );
		se->createLevelsButtons(Missions::GetInstance()->currentMission);
	}
}

void alert_bDeleteLevel_SceneCreateMission_OnClick (Scene *s, Button *b, string data) {
	SceneCreateMission* se = (SceneCreateMission*)s;
	if (b->getParameter("type")=="accept") {
		int i = atoi(b->getParameter("index").c_str());
		Missions::GetInstance()->currentMission->removeLevel(i);
		se->createLevelsButtons(Missions::GetInstance()->currentMission);
	}
	se->setStatusSceneWithReturnSceneFromMessage();
}

void bDeleteLevel_SceneCreateMission_OnClick (Scene *s, Button *b) {
	SceneCreateMission* se = (SceneCreateMission*)s;
	int i = atoi(b->getParameter("index").c_str());
	if ( Missions::GetInstance()->currentMission->getLevel( i ) != NULL ) {
		se->msg_bAccept->addParameter("index", b->getParameter("index"));
		se->showAlert(Language::GetInstance()->getText("info"), Language::GetInstance()->getText("areyousuredelete"), alert_bDeleteLevel_SceneCreateMission_OnClick, SCENE_CREATEMISSION_LEVELS);
	}
}

void bViewHelp_SceneCreateMission_OnClick (Scene *s, Button *b) {
	SceneCreateMission* se = (SceneCreateMission*)s;
	se->setElmHelp(atoi(b->getParameter("index_help").c_str()));
}

void bIndex_SceneCreateMission_OnClick (Scene *s, Button *b) {
	SceneCreateMission* se = (SceneCreateMission*)s;
	se->setElmHelp(-1);
}

void bPrevious_SceneCreateMission_OnClick (Scene *s, Button *b) {
	SceneCreateMission* se = (SceneCreateMission*)s;
	se->previousElmHelp();
}

void bNext_SceneCreateMission_OnClick (Scene *s, Button *b) {
	SceneCreateMission* se = (SceneCreateMission*)s;
	se->nextElmHelp();
}

void bCancel_SceneCreateMission_OnClick (Scene *s, Button *b) {
	SceneCreateMission* se = (SceneCreateMission*)s;
	se->setStatusScene(SCENE_CREATEMISSION_MAIN);
}

void bHelp_SceneCreateMission_OnClick (Scene *s, Button *b) {
	SceneCreateMission* se = (SceneCreateMission*)s;
	se->setSaveImage(true);
	se->setStatusScene(SCENE_CREATEMISSION_HELP);
}

/*****************************
**
** CLASE ButtonLevel
**
******************************/	

ButtonLevel::ButtonLevel(string t) : Group () {
	
	indexz = 0;
	
	bg = new Element();	
	bg->setX(70);
	bg->setY(0);
	bg->addFrameFileFromData("/createmissions/boxlevel_text.png");
	this->addElement(bg);
	
	bgNumber = new Element();	
	bgNumber->setX(0);
	bgNumber->setY(0);
	bgNumber->addFrameFileFromData("/createmissions/boxlevel_number.png");
	this->addElement(bgNumber);	
	
	title = new Button();
	title->setScales(1.0, 1.03);
	title->setRGB(213, 220, 248);
	title->setX(85);
	title->setY(28);
	title->setVAlign(VALIGN_CENTER);
	title->imageOut(Fonts::GetInstance()->getSurface_TextBitMap("font-texts", ALIGN_LEFT, t));
	title->OnClick = bPlayLevel_SceneCreateMission_OnClick;
	title->setAlt(Language::GetInstance()->getText("help_bpreview"), ALIGN_LEFT, VALIGN_BOTTOM);
	this->addElement(title);
	
	number = new Element();	
	number->setCurrentScale(0.8);
	number->setRGB(188, 222, 30);
	number->setX(31);
	number->setY(30);
	number->setAlign(ALIGN_CENTER);
	number->setVAlign(VALIGN_CENTER);
	number->addFrameSurface(Primitives::GetInstance()->rectangle(1, 1, 0, 0, 0));
	this->addElement(number);
	
	bEdit = new Button();
	bEdit->setScales(1.0, 1.1);
	bEdit->setAlign(ALIGN_CENTER);
	bEdit->setVAlign(VALIGN_CENTER);
	bEdit->setX(480);
	bEdit->setY(28);
	bEdit->imageOut(WorkingSurfaces::GetInstance()->surfaceFromImage((string)DATA_DIR + "/interface/" + Language::GetInstance()->getFilename("edit", "png")));
	bEdit->setAnimation("out");
	bEdit->OnClick = bEditLevel_SceneCreateMission_OnClick;
	bEdit->setAlt(Language::GetInstance()->getText("help_bedit"), ALIGN_LEFT, VALIGN_BOTTOM);
	this->addElement(bEdit);
	
	bUp = new Button();
	bUp->setScales(1.0, 1.1);
	bUp->setAlign(ALIGN_CENTER);
	bUp->setVAlign(VALIGN_CENTER);
	bUp->setX(605);
	bUp->setY(28);
	bUp->imageOut(WorkingSurfaces::GetInstance()->surfaceFromImage((string)DATA_DIR + "/interface/up.png"));
	bUp->setAnimation("out");
	bUp->OnClick = bUpLevel_SceneCreateMission_OnClick;
	bUp->setAlt(Language::GetInstance()->getText("help_buplevel"), ALIGN_LEFT, VALIGN_BOTTOM);
	this->addElement(bUp);
	
	bDown = new Button();
	bDown->setFlop(true);
	bDown->setScales(1.0, 1.1);
	bDown->setAlign(ALIGN_CENTER);
	bDown->setVAlign(VALIGN_CENTER);
	bDown->setX(565);
	bDown->setY(28);
	bDown->imageOut(WorkingSurfaces::GetInstance()->surfaceFromImage((string)DATA_DIR + "/interface/up.png"));
	bDown->setAnimation("out");
	bDown->OnClick = bDownLevel_SceneCreateMission_OnClick;
	bDown->setAlt(Language::GetInstance()->getText("help_bdownlevel"), ALIGN_LEFT, VALIGN_BOTTOM);
	this->addElement(bDown);
	
	bDelete = new Button();
	bDelete->setScales(1.0, 1.1);
	bDelete->setAlign(ALIGN_CENTER);
	bDelete->setVAlign(VALIGN_CENTER);
	bDelete->setX(650);
	bDelete->setY(28);
	bDelete->imageOut(WorkingSurfaces::GetInstance()->surfaceFromImage((string)DATA_DIR + "/interface/delete.png"));
	bDelete->setAnimation("out");
	bDelete->OnClick = bDeleteLevel_SceneCreateMission_OnClick;
	bDelete->setAlt(Language::GetInstance()->getText("help_bdeletelevel"), ALIGN_LEFT, VALIGN_BOTTOM);
	this->addElement(bDelete);
	
}

ButtonLevel::~ButtonLevel() {
	unLoad();
}

void ButtonLevel::setIndex (int i) { 
	index = i; 
	char tmp[4]; 
	sprintf(tmp, "%d", i);
	title->addParameter("index", tmp); 
	bEdit->addParameter("index", tmp); 
	bUp->addParameter("index", tmp); 
	bDown->addParameter("index", tmp); 
	bDelete->addParameter("index", tmp); 
}

void ButtonLevel::setNumber (int i) {
	char tmp[4];
	
	sprintf(tmp, "%d", i);
	
	number->changeFrameText(0, "font-computer", tmp, ALIGN_CENTER);
	
}

void ButtonLevel::draw() {
	work();
	bg->draw();
	bgNumber->draw();
	number->draw();
	title->draw();
	bEdit->draw();
	bUp->draw();
	bDown->draw();
	bDelete->draw();
}

void ButtonLevel::onOver() {
	bEdit->onOver();
	bUp->onOver();
	bDown->onOver();
	bDelete->onOver();
	title->onOver();
}

bool ButtonLevel::verifyClick(SceneCreateMission *sc) {
	if (title->isOnMouseOver()) {
		title->OnClick(sc, title);
		return true;
	}
	if (bEdit->isOnMouseOver()) {
		bEdit->OnClick(sc, bEdit);
		return true;
	}
	if (bUp->isOnMouseOver()) {
		bUp->OnClick(sc, bUp);
		return true;
	}
	if (bDown->isOnMouseOver()) {
		bDown->OnClick(sc, bDown);
		return true;
	}
	if (bDelete->isOnMouseOver()) {
		bDelete->OnClick(sc, bDelete);
		return true;
	}
	return false;
}

void ButtonLevel::unLoad() {
	delete bg;
	delete title;
	delete bEdit;
	delete bUp;
	delete bDown;
	delete bDelete;
	delete number;
	delete bgNumber;
}


/*****************************
**
** CLASE SceneCreateMission
**
******************************/	

SceneCreateMission::SceneCreateMission() : Scene () {
	statusScene = SCENE_CREATEMISSION_MAIN;
}

SceneCreateMission::~SceneCreateMission() {
	unLoad();
}

void SceneCreateMission::setElmHelp(int i) { 
	nElmHelp = i; 
	if (nElmHelp>=0) { 
		elmHelp->setCurrentFrame(i); 
	} 
	
	if (nElmHelp<=-1) {
		bPrevious->setRGB(190, 190, 190);
		bPrevious->setSensitive(false);
	} else {
		bPrevious->setRGB(0, 255, 0);
		bPrevious->setSensitive(true);
	}
	
	if (nElmHelp>=elmHelp->getFrames()-1) {
		bNext->setRGB(190, 190, 190);
		bNext->setSensitive(false);
	} else {
		bNext->setRGB(0, 255, 0);
		bNext->setSensitive(true);
	}

}

void SceneCreateMission::setStatusScene(int s) {
	statusScene = s;
	textHelp->setCurrentFrame(statusScene);
	textHelp->setFadeIn(1000);
	
	switch (statusScene) {
		case SCENE_CREATEMISSION_MAIN:
			bgCoverFlow->setCurrentScale(0);
			bgCoverFlow->setScaleGL(1.0, 400);
		
			nameMissionCover->setFadeIn(400);
			authorMissionCover->setFadeIn(400);
			nLevelsCover->setFadeIn(400);
			bPlay->setFadeIn(400);
			bEdit->setFadeIn(400);
			bPlay->setFadeIn(400);
			bNewMission->setFadeIn(400);
		
			bgInfoMission->setRot(270, 1.0, 0.0, 0.0);
			bgInfoMission->setRotationNormal(360, 400);
		
			dataMissions->setY(-800);
			dataMissions->setMovementSmoothY(220);
		break;
		case SCENE_CREATEMISSION_NEW:
		break;
		case SCENE_CREATEMISSION_LEVELS:
			bgLevels->setCurrentScale(0);
			bgLevels->setScaleGL(1.0, 400);
		
			titleMission->setFadeIn(400);
			bNewLevel->setFadeIn(400);
	
			dataLevel->setX(840);
			dataLevel->setMovementSmoothX(40);
		break;
		case SCENE_CREATEMISSION_NEWLEVEL:
		break;
	}
}

void SceneCreateMission::load() {

	initialize();
	
	ProgressBar *pb = new ProgressBar(7, 200, 16, 255, 255, 255);
	pb->setBg((string)DATA_DIR + "/title.png");
	pb->setBgBar((string)DATA_DIR + "/bg_barprogress.png");
    pb->setPositionBar(World::width/2, 300);
    
	pb->setText("font-texts", Language::GetInstance()->getText("loading_backgrounds"));
	pb->draw();
	
	// sounds
	
	Sounds::GetInstance()->addSoundFromData("music_editor", "music", "sound/music_editor.ogg");
		
	bgCoverFlow = new Element();
	bgCoverFlow->setXY(World::width/2, 220);
	bgCoverFlow->setAlign(ALIGN_CENTER);
	bgCoverFlow->setVAlign(VALIGN_CENTER);
	bgCoverFlow->addFrameFileFromData("/createmissions/base_cflow.png");
	
	bgInfoMission = new Element();
	bgInfoMission->setXY(World::width/2, 400);
	bgInfoMission->setAlign(ALIGN_CENTER);
	bgInfoMission->setVAlign(VALIGN_CENTER);
	bgInfoMission->addFrameFileFromData("/createmissions/screen_cflow.png");
	
	bgLevels = new Element();
	bgLevels->setXY(World::width/2, 278);
	bgLevels->setAlign(ALIGN_CENTER);
	bgLevels->setVAlign(VALIGN_CENTER);
	bgLevels->addFrameFileFromData("/createmissions/base_levels.png");
	
	titleFormMission = new Element();
	titleFormMission->setXY(World::width/2, 190);
	titleFormMission->setAlign(ALIGN_CENTER);
	titleFormMission->setVAlign(VALIGN_BOTTOM);
	titleFormMission->addFrameSurface(WorkingSurfaces::GetInstance()->surfaceFromImage((string)DATA_DIR + "/createmissions/" + Language::GetInstance()->getFilename("form_create_mission", "png")));
	
	bgFormMission = new Element();
	bgFormMission->setXY(World::width/2, 150);
	bgFormMission->setAlign(ALIGN_CENTER);
	bgFormMission->addFrameFileFromData("/createmissions/form_base_missions.png");
	
	titleFormLevel = new Element();
	titleFormLevel->setXY(World::width/2, 170);
	titleFormLevel->setAlign(ALIGN_CENTER);
	titleFormLevel->setVAlign(VALIGN_BOTTOM);
	titleFormLevel->addFrameSurface(WorkingSurfaces::GetInstance()->surfaceFromImage((string)DATA_DIR + "/createmissions/" + Language::GetInstance()->getFilename("form_create_level", "png")));
	
	bgFormLevel = new Element();
	bgFormLevel->setXY(World::width/2, 130);
	bgFormLevel->setAlign(ALIGN_CENTER);
	bgFormLevel->addFrameFileFromData("/createmissions/form_base_levels.png");
	
	nameMissionCover = new Element();
	nameMissionCover->setCurrentScale(0.6);
	nameMissionCover->setXY(World::width/2, 388);
	nameMissionCover->setAlign(ALIGN_CENTER);
	nameMissionCover->setVAlign(VALIGN_CENTER);
	nameMissionCover->setRGB(234, 238, 53);
	nameMissionCover->addFrameSurface(Primitives::GetInstance()->rectangle(1, 1, 0, 0, 0));
	
	authorMissionCover = new Element();
	authorMissionCover->setCurrentScale(0.42);
	authorMissionCover->setXY(World::width/2, 416);
	authorMissionCover->setAlign(ALIGN_CENTER);
	authorMissionCover->setVAlign(VALIGN_CENTER);
	authorMissionCover->setRGB(190, 195, 53);
	authorMissionCover->addFrameSurface(Primitives::GetInstance()->rectangle(1, 1, 0, 0, 0));
	
	nLevelsCover = new Element();
	nLevelsCover->setCurrentScale(0.42);
	nLevelsCover->setXY(World::width/2, 440);
	nLevelsCover->setAlign(ALIGN_CENTER);
	nLevelsCover->setVAlign(VALIGN_CENTER);
	nLevelsCover->setRGB(190, 195, 53);
	nLevelsCover->addFrameSurface(Primitives::GetInstance()->rectangle(1, 1, 0, 0, 0));
	
	frameUp = new Element();
	frameUp->addFrameSurface(WorkingSurfaces::GetInstance()->surfaceFromImage((string)DATA_DIR + "/createmissions/" + Language::GetInstance()->getFilename("frameup", "png")));
	
	frameUpLevels = new Element();
	frameUpLevels->addFrameSurface(WorkingSurfaces::GetInstance()->surfaceFromImage((string)DATA_DIR + "/createmissions/" + Language::GetInstance()->getFilename("frameup_levels", "png")));
	
	frameDown = new Element();
	frameDown->setY(World::height);
	frameDown->setVAlign(VALIGN_BOTTOM);
	frameDown->addFrameFileFromData("/createmissions/framedown.png");
	
	faceEnemy1 = new Element();
	faceEnemy1->setX(10);
	faceEnemy1->setY(World::height-10);
	faceEnemy1->setVAlign(VALIGN_BOTTOM);
	faceEnemy1->addFrameFileFromData("/createmissions/face_enemy1.png");
	
	textHelp = new Element();	
	textHelp->setCurrentScale(0.93);
	textHelp->setX(132);
	textHelp->setY(532);
	
	textHelp->addFrameText("font-texts", Language::GetInstance()->getText("help_createmission"), ALIGN_LEFT);
	textHelp->addFrameText("font-texts", Language::GetInstance()->getText("help_newmission"), ALIGN_LEFT);
	textHelp->addFrameText("font-texts", Language::GetInstance()->getText("help_createlevel"), ALIGN_LEFT);
	textHelp->addFrameText("font-texts", Language::GetInstance()->getText("help_newlevel"), ALIGN_LEFT);

    textHelp->setFadeIn(1000);
	
	// HELP
	
	char tmp[128];
	
	bHelp = new Button();
	bHelp->setScales(1.0, 1.1);
	bHelp->setAlign(ALIGN_CENTER);
	bHelp->setVAlign(VALIGN_CENTER);
	bHelp->setX(750);
	bHelp->setY(130);
	bHelp->setAlt(Language::GetInstance()->getText("help_bhelp"), ALIGN_RIGHT, VALIGN_BOTTOM);
	
	bHelp->imageOut(WorkingSurfaces::GetInstance()->surfaceFromImage((string)DATA_DIR + "/createmissions/" + Language::GetInstance()->getFilename("help", "png")));

	bHelp->setAnimation("out");

	bHelp->OnClick = bHelp_SceneCreateMission_OnClick;

	getGroupScene()->addElement((Element*)bHelp);
	
	bgHelp = new Element();	
	bgHelp->setAlign(ALIGN_CENTER);
	bgHelp->setVAlign(VALIGN_CENTER);
	bgHelp->setXY(World::width/2, 300);
	bgHelp->addFrameFileFromData("/help/help_bg.png");
	
	getGroupScene()->addElement(bgHelp);
	
	titleIndex = new Element();	
	titleIndex->setIndexZ(2);
	titleIndex->setCurrentScale(0.6);
	titleIndex->setXY(60, 103);
	titleIndex->setRGB(234, 238, 53);
	titleIndex->addFrameLanguage("font-computer", "index", ALIGN_LEFT);
	
	getGroupScene()->addElement(titleIndex);
	
	bIndex = new Button();
	bIndex->setIndexZ(1);
	bIndex->setScales(0.4, 0.45);
	bIndex->setAlign(ALIGN_CENTER);
	bIndex->setVAlign(VALIGN_CENTER);
	bIndex->setX(115);
	bIndex->setY(487);
	bIndex->setRGB(0, 255, 0);

	bIndex->OnClick = bIndex_SceneCreateMission_OnClick;
	
	sprintf(tmp, "%s", Language::GetInstance()->getText("index").c_str());
	bIndex->imageOut(Fonts::GetInstance()->getSurface_TextBitMap("font-computer", ALIGN_CENTER, tmp));
	bIndex->setAnimation("out");
	
	getGroupScene()->addElement(bIndex);
	
	bPrevious = new Button();
	bPrevious->setIndexZ(1);
	bPrevious->setScales(0.4, 0.45);
	bPrevious->setAlign(ALIGN_CENTER);
	bPrevious->setVAlign(VALIGN_CENTER);
	bPrevious->setX(337);
	bPrevious->setY(487);
	bPrevious->setRGB(0, 255, 0);

	bPrevious->OnClick = bPrevious_SceneCreateMission_OnClick;
	
	sprintf(tmp, "%s", Language::GetInstance()->getText("previous").c_str());
	bPrevious->imageOut(Fonts::GetInstance()->getSurface_TextBitMap("font-computer", ALIGN_CENTER, tmp));
	bPrevious->setAnimation("out");
	
	getGroupScene()->addElement(bPrevious);
	
	bNext = new Button();
	bNext->setIndexZ(1);
	bNext->setScales(0.4, 0.45);
	bNext->setAlign(ALIGN_CENTER);
	bNext->setVAlign(VALIGN_CENTER);
	bNext->setX(503);
	bNext->setY(487);
	bNext->setRGB(0, 255, 0);

	bNext->OnClick = bNext_SceneCreateMission_OnClick;
	
	sprintf(tmp, "%s", Language::GetInstance()->getText("next").c_str());
	bNext->imageOut(Fonts::GetInstance()->getSurface_TextBitMap("font-computer", ALIGN_CENTER, tmp));
	bNext->setAnimation("out");
	
	getGroupScene()->addElement(bNext);
	
	bCancel = new Button();
	bCancel->setIndexZ(1);
	bCancel->setScales(0.4, 0.45);
	bCancel->setAlign(ALIGN_CENTER);
	bCancel->setVAlign(VALIGN_CENTER);
	bCancel->setX(691);
	bCancel->setY(487);
	bCancel->setRGB(255, 0, 0);
	
	bCancel->OnClick = bCancel_SceneCreateMission_OnClick;
	
	sprintf(tmp, "%s", Language::GetInstance()->getText("cancel").c_str());
	bCancel->imageOut(Fonts::GetInstance()->getSurface_TextBitMap("font-computer", ALIGN_CENTER, tmp));
	bCancel->setAnimation("out");
	
	getGroupScene()->addElement(bCancel);
	
	bHelp1 = new Button();
	bHelp1->addParameter("index_help", "0");
	bHelp1->setIndexZ(2);
	bHelp1->setScales(1.0, 1.05);
	bHelp1->setX(100);
	bHelp1->setY(150);

	bHelp1->OnClick = bViewHelp_SceneCreateMission_OnClick;
	
	bHelp1->imageOut(Fonts::GetInstance()->getSurface_TextBitMap("font-texts", ALIGN_CENTER, Language::GetInstance()->getText("help_createmission_1")));
	bHelp1->setAnimation("out");
	
	getGroupScene()->addElement(bHelp1);
	
	bHelp2 = new Button();
	bHelp2->addParameter("index_help", "1");
	bHelp2->setIndexZ(2);
	bHelp2->setScales(1.0, 1.05);
	bHelp2->setX(100);
	bHelp2->setY(190);

	bHelp2->OnClick = bViewHelp_SceneCreateMission_OnClick;
	
	bHelp2->imageOut(Fonts::GetInstance()->getSurface_TextBitMap("font-texts", ALIGN_CENTER, Language::GetInstance()->getText("help_createmission_2")));
	bHelp2->setAnimation("out");
	
	getGroupScene()->addElement(bHelp2);
	
	bHelp3 = new Button();
	bHelp3->addParameter("index_help", "2");
	bHelp3->setIndexZ(2);
	bHelp3->setScales(1.0, 1.05);
	bHelp3->setX(100);
	bHelp3->setY(230);

	bHelp3->OnClick = bViewHelp_SceneCreateMission_OnClick;
	
	bHelp3->imageOut(Fonts::GetInstance()->getSurface_TextBitMap("font-texts", ALIGN_CENTER, Language::GetInstance()->getText("help_createmission_3")));
	bHelp3->setAnimation("out");
	
	getGroupScene()->addElement(bHelp3);
	
	bHelp4 = new Button();
	bHelp4->addParameter("index_help", "3");
	bHelp4->setIndexZ(2);
	bHelp4->setScales(1.0, 1.05);
	bHelp4->setX(100);
	bHelp4->setY(270);

	bHelp4->OnClick = bViewHelp_SceneCreateMission_OnClick;
	
	bHelp4->imageOut(Fonts::GetInstance()->getSurface_TextBitMap("font-texts", ALIGN_CENTER, Language::GetInstance()->getText("help_createmission_4")));
	bHelp4->setAnimation("out");
	
	getGroupScene()->addElement(bHelp4);
	
	elmHelp = new Element();	
	elmHelp->setAlign(ALIGN_CENTER);
	elmHelp->setVAlign(VALIGN_CENTER);
	elmHelp->setXY(World::width/2, 300);
	
	elmHelp->addFrameSurface(WorkingSurfaces::GetInstance()->surfaceFromImage((string)DATA_DIR + "/help/" + Language::GetInstance()->getFilename("createmission_help_1", "png")));
	elmHelp->addFrameSurface(WorkingSurfaces::GetInstance()->surfaceFromImage((string)DATA_DIR + "/help/" + Language::GetInstance()->getFilename("createmission_help_2", "png")));
	elmHelp->addFrameSurface(WorkingSurfaces::GetInstance()->surfaceFromImage((string)DATA_DIR + "/help/" + Language::GetInstance()->getFilename("createmission_help_3", "png")));
	elmHelp->addFrameSurface(WorkingSurfaces::GetInstance()->surfaceFromImage((string)DATA_DIR + "/help/" + Language::GetInstance()->getFilename("createmission_help_4", "png")));
	
	getGroupScene()->addElement(elmHelp);
	
	setElmHelp(-1);

	pb->setText("font-texts", Language::GetInstance()->getText("loading_listmission"));
	pb->draw();

	stars = new ParticlesSystem();
	stars->setFrame((string)DATA_DIR + "/particles/point.png");
	stars->setDisplacementX(0, 1);
	stars->setPositions(-200, 0, 1000, 600);
	stars->setType(TYPE_STARS);
	stars->start();

	Button *bRight = new Button();
	bRight->setSoundClick("beep1");
	bRight->setFlip(true);
	bRight->setScales(1.0, 1.05);
	bRight->setVAlign(VALIGN_CENTER);
	
	bRight->imageOut(WorkingSurfaces::GetInstance()->surfaceFromImage((string)DATA_DIR + "/createmissions/bleft_on.png"));
	bRight->imageOff(WorkingSurfaces::GetInstance()->surfaceFromImage((string)DATA_DIR + "/createmissions/bleft_off.png"));
	bRight->setAnimation("out");
	
	Button *bLeft = new Button();
	bLeft->setSoundClick("beep1");
	bLeft->setScales(1.0, 1.05);
	bLeft->setVAlign(VALIGN_CENTER);
	
	bLeft->imageOut(WorkingSurfaces::GetInstance()->surfaceFromImage((string)DATA_DIR + "/createmissions/bleft_on.png"));
	bLeft->imageOff(WorkingSurfaces::GetInstance()->surfaceFromImage((string)DATA_DIR + "/createmissions/bleft_off.png"));
	bLeft->setAnimation("out");
	
	indexMissionActive = -1;
		
	dataMissions = new CoverFlow();
	dataMissions->setWidthItem(200);
	dataMissions->setXY(0, 220);
	dataMissions->setSeparateGrid(120);
	dataMissions->setButtons(bLeft, bRight, -17, 120);
	
	pb->setText("font-texts", Language::GetInstance()->getText("loading_listlevels"));
	pb->draw();
	
	Button *bUp = new Button();
	bUp->setSoundClick("beep1");
	bUp->setScales(1.0, 1.1);
	bUp->setAlign(ALIGN_CENTER);
	bUp->setVAlign(VALIGN_CENTER);
	
	bUp->imageOut(WorkingSurfaces::GetInstance()->surfaceFromImage((string)DATA_DIR + "/createmissions/bup_on.png"));
	bUp->imageOff(WorkingSurfaces::GetInstance()->surfaceFromImage((string)DATA_DIR + "/createmissions/bup_off.png"));
	bUp->setAnimation("out");
	
	Button *bDown = new Button();
	bDown->setSoundClick("beep1");
	bDown->setFlop(true);
	bDown->setScales(1.0, 1.1);
	bDown->setAlign(ALIGN_CENTER);
	bDown->setVAlign(VALIGN_CENTER);
	
	bDown->imageOut(WorkingSurfaces::GetInstance()->surfaceFromImage((string)DATA_DIR + "/createmissions/bup_on.png"));
	bDown->imageOff(WorkingSurfaces::GetInstance()->surfaceFromImage((string)DATA_DIR + "/createmissions/bup_off.png"));
	bDown->setAnimation("out");
	
	dataLevel = new ListView();
	dataLevel->setTodoMovement(false);
	dataLevel->setXY(40, 158);
	dataLevel->setSeparateGrid(65);
	dataLevel->setButtons(bUp, bDown, 710);
	
	pb->setText("font-texts", Language::GetInstance()->getText("loading_buttons"));
	pb->draw();
								
	bBack = new Button();
	bBack->setScales(1.0, 1.1);
	bBack->setAlign(ALIGN_CENTER);
	bBack->setVAlign(VALIGN_CENTER);
	bBack->setX(630);
	bBack->setY(475);
	
	bBack->imageOn(WorkingSurfaces::GetInstance()->surfaceFromImage((string)DATA_DIR + "/createmissions/" + Language::GetInstance()->getFilename("back", "png")));
	bBack->setAnimation("out");
	
	bBack->OnClick = bBack_SceneCreateMission_OnClick;
	
	getGroupScene()->addElement((Element*)bBack);
	
	bPlay = new Button();
	bPlay->setScales(1.0, 1.05);
	bPlay->setAlign(ALIGN_CENTER);
	bPlay->setVAlign(VALIGN_CENTER);
	bPlay->setX(331);
	bPlay->setY(474);
	bPlay->imageOut(WorkingSurfaces::GetInstance()->surfaceFromImage((string)DATA_DIR + "/createmissions/" + Language::GetInstance()->getFilename("play", "png")));
	//sprintf(tmp, Language::GetInstance()->getText("play").c_str());
	//bPlay->imageOn(Fonts::GetInstance()->getSurface_TextBitMap("font-menu-light", ALIGN_CENTER, tmp));
	bPlay->setAnimation("out");
	bPlay->OnClick = bPlayMision_SceneCreateMission_OnClick;
	
	bEdit = new Button();
	bEdit->setScales(1.0, 1.05);
	bEdit->setAlign(ALIGN_CENTER);
	bEdit->setVAlign(VALIGN_CENTER);
	bEdit->setX(478);
	bEdit->setY(474);
	bEdit->imageOut(WorkingSurfaces::GetInstance()->surfaceFromImage((string)DATA_DIR + "/createmissions/" + Language::GetInstance()->getFilename("edit_on", "png")));
	bEdit->imageOff(WorkingSurfaces::GetInstance()->surfaceFromImage((string)DATA_DIR + "/createmissions/" + Language::GetInstance()->getFilename("edit_off", "png")));
	bEdit->setAnimation("out");
	//bEdit->setSensitive(false);
	bEdit->OnClick = bEditMision_SceneCreateMission_OnClick;
	
	bQuit = new Button();
	bQuit->setScales(1.0, 1.1);
	bQuit->setAlign(ALIGN_CENTER);
	bQuit->setVAlign(VALIGN_CENTER);
	bQuit->setX(700);
	bQuit->setY(460);
	bQuit->imageOn(WorkingSurfaces::GetInstance()->surfaceFromImage((string)DATA_DIR + "/createmissions/" + Language::GetInstance()->getFilename("exit", "png")));
	bQuit->setAnimation("out");
	bQuit->OnClick = bQuit_SceneCreateMission_OnClick;
	
	bNewMission = new Button();
	bNewMission->setScales(1.0, 1.1);
	bNewMission->setAlign(ALIGN_CENTER);
	bNewMission->setVAlign(VALIGN_CENTER);
	bNewMission->setX(130);
	bNewMission->setY(420);
	bNewMission->setAlt(Language::GetInstance()->getText("help_bnewmission"), ALIGN_LEFT, VALIGN_BOTTOM);
	
	bNewMission->imageOut(WorkingSurfaces::GetInstance()->surfaceFromImage((string)DATA_DIR + "/createmissions/" + Language::GetInstance()->getFilename("create_mission", "png")));

	bNewMission->setAnimation("out");

	bNewMission->OnClick = bNewMision_SceneCreateMission_OnClick;

	getGroupScene()->addElement((Element*)bNewMission);

	bNewLevel = new Button();
	bNewLevel->setScales(0.45, 0.48);
	bNewLevel->setAlign(ALIGN_CENTER);
	bNewLevel->setVAlign(VALIGN_CENTER);
	bNewLevel->setX(408);
	bNewLevel->setY(440);
	bNewLevel->setRGB(0,255,0);

	//bNewLevel->imageOn(WorkingSurfaces::GetInstance()->surfaceFromImage((string)DATA_DIR + "/createmissions/" + Language::GetInstance()->getFilename("add_level", "png")));
	bNewLevel->imageOut(Fonts::GetInstance()->getSurface_TextBitMap("font-computer", ALIGN_CENTER, Language::GetInstance()->getText("addlevel")));
	bNewLevel->setAnimation("out");
	
	bNewLevel->OnClick = bNewLevel_SceneCreateMission_OnClick;
	
	getGroupScene()->addElement((Element*)bNewLevel);
	
	bCreateMission = new Button();
	bCreateMission->setScales(0.4, 0.45);
	bCreateMission->setAlign(ALIGN_CENTER);
	bCreateMission->setVAlign(VALIGN_CENTER);
	bCreateMission->setX(390);
	bCreateMission->setY(334);
	bCreateMission->setRGB(0,255,0);
	
	bCreateMission->imageOut(Fonts::GetInstance()->getSurface_TextBitMap("font-computer", ALIGN_CENTER, Language::GetInstance()->getText("create")));
	bCreateMission->setAnimation("out");
	
	bCreateMission->OnClick = bCreateMission_SceneCreateMission_OnClick;
	
	getGroupScene()->addElement((Element*)bCreateMission);
	
	bCreateLevel = new Button();
	bCreateLevel->setScales(0.4, 0.45);
	bCreateLevel->setAlign(ALIGN_CENTER);
	bCreateLevel->setVAlign(VALIGN_CENTER);
	bCreateLevel->setX(World::width/2);
	bCreateLevel->setY(426);
	bCreateLevel->setRGB(0,255,0);
	
	bCreateLevel->imageOut(Fonts::GetInstance()->getSurface_TextBitMap("font-computer", ALIGN_CENTER, Language::GetInstance()->getText("create")));
    bCreateLevel->setAnimation("out");
	
	bCreateLevel->OnClick = bCreateLevel_SceneCreateMission_OnClick;
	
	getGroupScene()->addElement((Element*)bCreateLevel);
	
	pb->setText("font-texts", Language::GetInstance()->getText("loading_forms"));
	pb->draw();
		
	missionName = new Entry(NULL, 450, 25, 10, 10);
	missionName->setNoSigns(true);
	missionName->setMaxLetters(35);
	missionName->setFontLabel("font-texts");
	missionName->setFont("font-computer");
	missionName->setLabel(Language::GetInstance()->getText("namemission"));
	missionName->setHorizontal(false);
	missionName->setX(World::width/2);
	missionName->setY(200);
	missionName->addFrameBoxNormal(WorkingSurfaces::GetInstance()->surfaceFromImage((string)DATA_DIR + "/createmissions/bg_textbox.png"));
	missionName->addFrameBoxOnOver(WorkingSurfaces::GetInstance()->surfaceFromImage((string)DATA_DIR + "/createmissions/bg_textbox_on.png"));
	missionName->addFrameBoxActived(WorkingSurfaces::GetInstance()->surfaceFromImage((string)DATA_DIR + "/createmissions/bg_textbox_active.png"));
	
	getGroupScene()->addElement((Element*)missionName);
	
	nameAuthor = new Entry(missionName, 450, 25, 10, 10);
	nameAuthor->setNoSigns(true);
	nameAuthor->setMaxLetters(35);
	nameAuthor->setFontLabel("font-texts");
	nameAuthor->setFont("font-computer");
	nameAuthor->setLabel(Language::GetInstance()->getText("nameauthor"));
	nameAuthor->setHorizontal(false);
	nameAuthor->setX(World::width/2);
	nameAuthor->setY(265);
	nameAuthor->addFrameBoxNormal(WorkingSurfaces::GetInstance()->surfaceFromImage((string)DATA_DIR + "/createmissions/bg_textbox.png"));
	nameAuthor->addFrameBoxOnOver(WorkingSurfaces::GetInstance()->surfaceFromImage((string)DATA_DIR + "/createmissions/bg_textbox_on.png"));
	nameAuthor->addFrameBoxActived(WorkingSurfaces::GetInstance()->surfaceFromImage((string)DATA_DIR + "/createmissions/bg_textbox_active.png"));
	
	getGroupScene()->addElement((Element*)nameAuthor);
			
	levelName = new Entry(NULL, 450, 25, 10, 10);
	levelName->setNoSigns(true);
	levelName->setMaxLetters(35);
	levelName->setFontLabel("font-texts");
	levelName->setFont("font-computer");
	levelName->setLabel(Language::GetInstance()->getText("namelevel"));
	levelName->setHorizontal(false);
	levelName->setX(World::width/2);
	levelName->setY(180);
	levelName->addFrameBoxNormal(WorkingSurfaces::GetInstance()->surfaceFromImage((string)DATA_DIR + "/createmissions/bg_textbox.png"));
	levelName->addFrameBoxOnOver(WorkingSurfaces::GetInstance()->surfaceFromImage((string)DATA_DIR + "/createmissions/bg_textbox_on.png"));
	levelName->addFrameBoxActived(WorkingSurfaces::GetInstance()->surfaceFromImage((string)DATA_DIR + "/createmissions/bg_textbox_active.png"));
	
	getGroupScene()->addElement((Element*)levelName);
		
	provinceName = new Entry(levelName, 450, 25, 10, 10);
	provinceName->setNoSigns(true);
	provinceName->setMaxLetters(35);
	provinceName->setFontLabel("font-texts");
	provinceName->setFont("font-computer");
	provinceName->setLabel(Language::GetInstance()->getText("nameprovince"));
	provinceName->setHorizontal(false);
	provinceName->setX(World::width/2);
	provinceName->setY(245);
	provinceName->addFrameBoxNormal(WorkingSurfaces::GetInstance()->surfaceFromImage((string)DATA_DIR + "/createmissions/bg_textbox.png"));
	provinceName->addFrameBoxOnOver(WorkingSurfaces::GetInstance()->surfaceFromImage((string)DATA_DIR + "/createmissions/bg_textbox_on.png"));
	provinceName->addFrameBoxActived(WorkingSurfaces::GetInstance()->surfaceFromImage((string)DATA_DIR + "/createmissions/bg_textbox_active.png"));
	
	getGroupScene()->addElement((Element*)provinceName);
	
	titleTypeScenary = new Element();
	titleTypeScenary->setX(World::width/2);
	titleTypeScenary->setY(335);
	titleTypeScenary->setAlign(ALIGN_CENTER);
	titleTypeScenary->addFrameLanguage("font-texts", "typesceneary", ALIGN_CENTER);
	
	getGroupScene()->addElement(titleTypeScenary);
	
	tScOpened = new RadioButton(NULL, "font-texts", Language::GetInstance()->getText("opened"));	
	tScOpened->setX(420);
	tScOpened->setY(365);
	
	tScOpened->imageInactive( WorkingSurfaces::GetInstance()->surfaceFromImage(string(DATA_DIR)+"/interface/rad_off.png") );
	tScOpened->imageActive( WorkingSurfaces::GetInstance()->surfaceFromImage(string(DATA_DIR)+"/interface/rad_on.png") );
	
	getGroupScene()->addGroup(tScOpened);
	
	tScClosed = new RadioButton(tScOpened, "font-texts", Language::GetInstance()->getText("closed"));	
	tScClosed->setX(270);
	tScClosed->setY(365);
	
	tScClosed->imageInactive( WorkingSurfaces::GetInstance()->surfaceFromImage(string(DATA_DIR)+"/interface/rad_off.png") );
	tScClosed->imageActive( WorkingSurfaces::GetInstance()->surfaceFromImage(string(DATA_DIR)+"/interface/rad_on.png") );
	
	getGroupScene()->addGroup(tScClosed);
	
	tScClosed->setActive(true);
	
	pb->setText("font-texts", Language::GetInstance()->getText("loading_titles"));
	pb->draw();
		
	nomission = new Element();
	nomission->setAlign(ALIGN_CENTER);
	nomission->setX(World::width/2);
	nomission->setY(190);
	nomission->setCurrentScale(1.4);
	
	nomission->addFrameLanguage("font-texts", "nomission", ALIGN_CENTER);
	
	getGroupScene()->addElement(nomission);
	
	nolevels = new Element();
	nolevels->setAlign(ALIGN_CENTER);
	nolevels->setX(World::width/2);
	nolevels->setY(190);
	nolevels->setCurrentScale(1.4);
	
	nolevels->addFrameLanguage("font-texts", "nolevels", ALIGN_CENTER);
	
	getGroupScene()->addElement(nolevels);
		
	titleMission = new Element();
	titleMission->setCurrentScale(0.6);
	titleMission->setRGB(234, 238, 53);
	titleMission->setX(117);
	titleMission->setY(90);
	
	titleMission->addFrameSurface(Primitives::GetInstance()->rectangle(10, 10, 0, 0, 0));
	
	getGroupScene()->addElement(titleMission);
	
	pb->setText("font-texts", Language::GetInstance()->getText("loading_missions"));
	pb->draw();
	
	createMissionsButtons();
		
	if (Missions::GetInstance()->currentMission!=NULL) {
		if (Missions::GetInstance()->currentLevel!=NULL) {
			Debug::GetInstance()->writeText("Cargando niveles");
			createLevelsButtons(Missions::GetInstance()->currentMission);
			setStatusScene(SCENE_CREATEMISSION_LEVELS);
		} else {
			setStatusScene(SCENE_CREATEMISSION_MAIN);
		}
    } else {
		setStatusScene(SCENE_CREATEMISSION_MAIN);
    }
    
   	Sounds::GetInstance()->getSound("music_editor")->play(1, -1, 2000);
    
   	delete pb;
    	
}

string SceneCreateMission::getNameProject(string name) {
       
     string searchString( " " ); 
     string replaceString( "" );
     string::size_type pos = 0;
     while ( (pos = name.find(searchString, pos)) != string::npos ) {
        name.replace( pos, searchString.size(), replaceString );
        pos++;
     }
     
     searchString = "ñ"; 
     replaceString = "n";
     pos = 0;
     while ( (pos = name.find(searchString, pos)) != string::npos ) {
        name.replace( pos, searchString.size(), replaceString );
        pos++;
     }
     
     searchString = "-"; 
     replaceString = "_";
     pos = 0;
     while ( (pos = name.find(searchString, pos)) != string::npos ) {
        name.replace( pos, searchString.size(), replaceString );
        pos++;
     }
     
     searchString = "á"; 
     replaceString = "a";
     pos = 0;
     while ( (pos = name.find(searchString, pos)) != string::npos ) {
        name.replace( pos, searchString.size(), replaceString );
        pos++;
     }
     
     searchString = "é"; 
     replaceString = "e";
     pos = 0;
     while ( (pos = name.find(searchString, pos)) != string::npos ) {
        name.replace( pos, searchString.size(), replaceString );
        pos++;
     }
     
     searchString = "í"; 
     replaceString = "i";
     pos = 0;
     while ( (pos = name.find(searchString, pos)) != string::npos ) {
        name.replace( pos, searchString.size(), replaceString );
        pos++;
     }
     
     searchString = "ó"; 
     replaceString = "o";
     pos = 0;
     while ( (pos = name.find(searchString, pos)) != string::npos ) {
        name.replace( pos, searchString.size(), replaceString );
        pos++;
     }
     
     searchString = "ú"; 
     replaceString = "u";
     pos = 0;
     while ( (pos = name.find(searchString, pos)) != string::npos ) {
        name.replace( pos, searchString.size(), replaceString );
        pos++;
     }
     
     for(unsigned int i=0;i<name.length();i++) {
         name[i] = tolower(name[i]);
     }
     return name;
     
}

void SceneCreateMission::createMissionsButtons() {
	
	dataMissions->inicialize();
		
	Missions::GetInstance()->MoveFirst();
	int i=0;

	while (!Missions::GetInstance()->isEOF()) {
          
        if (Missions::GetInstance()->getMission()->getDirectory()!="andalucia") {
                                                                                
    		Debug::GetInstance()->writeText("Mision: " + Missions::GetInstance()->getMission()->getName());
              
			Element* bMission = new Element();	
			
			string fileCover = Missions::GetInstance()->getMission()->getPath() + "/cover.png";
            
            if (WorkingData::GetInstance()->existFile(fileCover)) {
    			bMission->addFrameFile(fileCover);
            } else {
                SDL_Surface *sfc = Fonts::GetInstance()->getSurface_TextBitMap("font-texts", 100, ALIGN_LEFT, Missions::GetInstance()->getMission()->getName());
                Bounds b;
                b.x1 = 10;
                b.y1 = 90;
                b.x2 = 10+sfc->w;
                b.y2 = 90+sfc->h;
				SDL_Surface *sfcEnd = WorkingSurfaces::GetInstance()->mixSurfaces(
    					WorkingSurfaces::GetInstance()->surfaceFromImage((string)DATA_DIR+"/misc/cover.png"),
    					sfc, &b);

				sfc = Fonts::GetInstance()->getSurface_TextBitMap("font-texts", 100, ALIGN_LEFT, Missions::GetInstance()->getMission()->getName());
				sfcEnd = WorkingSurfaces::GetInstance()->mixSurfaces(
    					sfcEnd, sfc, &b);
				sfc = Fonts::GetInstance()->getSurface_TextBitMap("font-texts", 100, ALIGN_LEFT, Missions::GetInstance()->getMission()->getName());
				sfcEnd = WorkingSurfaces::GetInstance()->mixSurfaces(
    					sfcEnd, sfc, &b);
    			bMission->addFrameSurface(sfcEnd);
            }
			
			char tmp[4];
			sprintf(tmp, "%d", i);
			
    		bMission->addParameter("index-mission", tmp);

            getGroupScene()->addElement(bMission);

			dataMissions->add(bMission);
			
			Debug::GetInstance()->writeText("Mision agregada");
			
		}
		
		Missions::GetInstance()->MoveNext();
		i++;
	}
	
	dataMissions->startPosition();
	
}

void SceneCreateMission::createLevelsButtons(Mission *mission) {
	
	int bitem = 0;
	
	if (Missions::GetInstance()->currentMission!=NULL) {
		if (Missions::GetInstance()->currentMission->getDirectory()==mission->getDirectory()) {
			bitem = dataLevel->getBeginItem();
		} else {
			bitem = 0;
		}
	}
	
	Missions::GetInstance()->currentMission = mission;
	
	Debug::GetInstance()->writeText("Mision: " + Missions::GetInstance()->currentMission->getName());
	
	
	
	dataLevel->MoveFirst();
	while (!dataLevel->isEOF()) {
        delete (ButtonLevel*)dataLevel->getData();
        dataLevel->MoveNext();
    }
	
	dataLevel->inicialize();
		
	string tmpname;
	if (Missions::GetInstance()->currentMission->getName().length()>15) {
       tmpname = Missions::GetInstance()->currentMission->getName().substr(0, 15).c_str() + string("...");
    } else {
       tmpname = Missions::GetInstance()->currentMission->getName();
    }

	titleMission->addFrameText("font-computer", tmpname, ALIGN_CENTER);
	titleMission->lastFrame();
	
	mission->MoveFirst();
	int i=0;
	
	while (!mission->isEOF()) {
		string n = mission->getLevel()->getName() + " (" + mission->getLevel()->getProvince() + ")";
		
		if (n.length() >35) {
			n = n.substr(0, 35) + "...";
		}
		
		ButtonLevel *bLevel = new ButtonLevel(n);
		if (i==0) bLevel->getButtonUp()->hide();
		if (i==mission->getNLevels()-1) bLevel->getButtonDown()->hide();
		bLevel->setIndex(i);
		bLevel->setNumber(i+1);

		mission->MoveNext();
		
		getGroupScene()->addGroup(bLevel);
		
		dataLevel->add(bLevel);
		
		i++;
	}
	
	Missions::GetInstance()->currentMission->save();
	//printf("dola: %d\n", bitem);
	dataLevel->setBeginItem(bitem);
	
}

/**********************
  DRAWSCENE MAIN
**********************/

void SceneCreateMission::drawSceneMain () {
    if (dataMissions->getNItems()>0) {
    	int i = atoi(dataMissions->getDataIndex()->getParameter("index-mission").c_str());
    	if (indexMissionActive!=i) {
    		indexMissionActive = i;
    		string tmpname;
    		if (Missions::GetInstance()->getMission(indexMissionActive)->getName().length()>12) {
               tmpname = Missions::GetInstance()->getMission(indexMissionActive)->getName().substr(0, 12).c_str() + string("...");
            } else {
               tmpname = Missions::GetInstance()->getMission(indexMissionActive)->getName().c_str();
            }
    		nameMissionCover->addFrameText("font-computer", tmpname, ALIGN_CENTER);
    		nameMissionCover->lastFrame();
    		authorMissionCover->addFrameText("font-computer", Language::GetInstance()->getText("author") + ": " + Missions::GetInstance()->getMission(indexMissionActive)->getNameAuthor(), ALIGN_CENTER);
    		authorMissionCover->lastFrame();
    		char tmp[32];
    		sprintf(tmp, "%s: %d", (char*)Language::GetInstance()->getText("levels").c_str(), Missions::GetInstance()->getMission(indexMissionActive)->getNLevels());
    		nLevelsCover->addFrameText("font-computer", tmp, ALIGN_CENTER);
    		nLevelsCover->lastFrame();
    		bEdit->setSensitive(Users::GetInstance()->getCurrentUser()->isMyMission(Missions::GetInstance()->getMission(indexMissionActive)->getDirectory()));
    	}
    }
	verifyOverElements_Main();

	stars->draw();

	for (int i=0; i<MAX_INDEXZ; i++) {
		drawSceneMainByIndexZ(i);
	}

}

void SceneCreateMission::drawSceneMainByIndexZ(int z) {
	
	if (dataMissions->getNItems()>0) {
		if (bgInfoMission->getIndexZ() == z) {
			bgInfoMission->draw();
		}
		
		if (bgCoverFlow->getIndexZ() == z) {
			bgCoverFlow->draw();
		}
	
		if (bPlay->getIndexZ() == z) {
			bPlay->draw();
		}
		
		if (bEdit->getIndexZ() == z) {
			bEdit->draw();
		}
		if (nameMissionCover->getIndexZ() == z) {
			nameMissionCover->draw();
		}
		if (authorMissionCover->getIndexZ() == z) {
			authorMissionCover->draw();
		}
		if (nLevelsCover->getIndexZ() == z) {
			nLevelsCover->draw();
		}
		if (dataMissions->getIndexZ() == z) {
			dataMissions->work();
        	dataMissions->draw();
		}
	} else {
		if (nomission->getIndexZ() == z) {
			nomission->draw();
		}
	}
	
	if (bQuit->getIndexZ() == z) {
		bQuit->draw();
	}
	
	if (frameUp->getIndexZ() == z) {
		frameUp->draw();
	}
	
	if (frameDown->getIndexZ() == z) {
		frameDown->draw();
	}
	
	if (faceEnemy1->getIndexZ() == z) {
		faceEnemy1->draw();
	}
	
	if (textHelp->getIndexZ() == z) {
		textHelp->draw();
	}
	
	if (bNewMission->getIndexZ() == z) {
		bNewMission->draw();
	}
	
	if (bHelp->getIndexZ() == z) {
		bHelp->draw();
	}
}

void SceneCreateMission::verifyClickElements_Main() {
	if (bNewMission->isOnMouseOver()) {
		Cursor::GetInstance()->forceHideText();
		bNewMission->OnClick(this, bNewMission);
	}
	if (bHelp->isOnMouseOver()) {
		Cursor::GetInstance()->forceHideText();
		bHelp->OnClick(this, bHelp);
	}
	if (bQuit->isOnMouseOver()) {
		bQuit->OnClick(this, bQuit);
	}
	
	if (bPlay->isOnMouseOver()) {
		bPlay->OnClick(this, bPlay);
	}
	
	if (bEdit->isOnMouseOver()) {
		bEdit->OnClick(this, bEdit);
	}
	
	dataMissions->verifyClickButtons();


}

void SceneCreateMission::verifyOverElements_Main() {
	bQuit->onOver();
	bPlay->onOver();
	bEdit->onOver();
	bNewMission->onOver();
	bHelp->onOver();
	
	dataMissions->onOver();

}

/**********************
  DRAWSCENE NEW
**********************/

void SceneCreateMission::drawSceneNewMission () {
	
	verifyOverElements_NewMision();
	stars->draw();	
	
	for (int i=0; i<MAX_INDEXZ; i++) {
		drawSceneNewMissionByIndexZ(i);
	}
	
}

void SceneCreateMission::drawSceneNewMissionByIndexZ(int z) {
     
	if (frameUp->getIndexZ() == z) {
		frameUp->draw();
	}
	
	if (frameDown->getIndexZ() == z) {
		frameDown->draw();
	}
	
	if (faceEnemy1->getIndexZ() == z) {
		faceEnemy1->draw();
	}
	
	if (textHelp->getIndexZ() == z) {
		textHelp->draw();
	}
    	
    if (bgFormMission->getIndexZ() == z) {
		bgFormMission->draw();
	}
	
    if (titleFormMission->getIndexZ() == z) {
		titleFormMission->draw();
	}
	
	if (missionName->getIndexZ() == z) {
		missionName->draw();
	}
	if (nameAuthor->getIndexZ() == z) {
		nameAuthor->draw();
	}
	if (bBack->getIndexZ() == z) {
		bBack->draw();
	}
	
	if (bCreateMission->getIndexZ() == z) {
		bCreateMission->draw();
	}
}

void SceneCreateMission::verifyClickElements_NewMision() {
	if (bCreateMission->isOnMouseOver()) {
		bCreateMission->OnClick(this, bCreateMission);
	}
	if (bBack->isOnMouseOver()) {
		bBack->OnClick(this, bBack);
	}
	if (missionName->isOnMouseOver()) {
		missionName->setActive(true);
	}
	if (nameAuthor->isOnMouseOver()) {
		nameAuthor->setActive(true);
	}
}

void SceneCreateMission::verifyOverElements_NewMision() {
	missionName->onOver();
	nameAuthor->onOver();
	bBack->onOver();
	bCreateMission->onOver();
}

/**********************
  DRAWSCENE LEVELS
**********************/

void SceneCreateMission::drawSceneLevels () {
	
	verifyOverElements_Levels();
	stars->draw();
	
	for (int i=0; i<MAX_INDEXZ; i++) {
		drawSceneLevelsByIndexZ(i);
	}
	
}

void SceneCreateMission::drawSceneLevelsByIndexZ(int z) {
     
	if (bBack->getIndexZ() == z) {
		bBack->draw();
	}
	
	if (frameUpLevels->getIndexZ() == z) {
		frameUpLevels->draw();
	}
	
	if (frameDown->getIndexZ() == z) {
		frameDown->draw();
	}
	
	if (bgLevels->getIndexZ() == z) {
		bgLevels->draw();
	}
	
	if (faceEnemy1->getIndexZ() == z) {
		faceEnemy1->draw();
	}
	
	if (textHelp->getIndexZ() == z) {
		textHelp->draw();
	}
	
	if ( (Missions::GetInstance()->currentMission->getNLevels()>0) && (Missions::GetInstance()->currentMission!=NULL) ) {
		if (dataLevel->getIndexZ() == z) {
			dataLevel->work();
			dataLevel->draw();
		}
	} else {
		if (nolevels->getIndexZ() == z) {
			nolevels->draw();
		}
	}
			
	if (bNewLevel->getIndexZ() == z) {
		bNewLevel->draw();
	}
	
	if (titleMission->getIndexZ() == z) {
		titleMission->draw();
	}
}

void SceneCreateMission::verifyClickElements_Levels() {
	if (bNewLevel->isOnMouseOver()) {
		bNewLevel->OnClick(this, bNewLevel);
	}
	if (bBack->isOnMouseOver()) {
		bBack->OnClick(this, bBack);
	}

	dataLevel->verifyClickButtons();
	
	dataLevel->MoveFirst();
	while (!dataLevel->isEOF()) {
        if (dataLevel->isVisible()) {
           ButtonLevel *bm = (ButtonLevel*)dataLevel->getData();
           if (bm->verifyClick(this)) {
			   dataLevel->MoveLast();
			   break;
		   }
        }
        dataLevel->MoveNext();
    }
    
}

void SceneCreateMission::verifyOverElements_Levels() {

	bBack->onOver();
	bNewLevel->onOver();
	
	dataLevel->MoveFirst();
	while (!dataLevel->isEOF()) {
        if (dataLevel->isVisible()) {
            ButtonLevel *bm = (ButtonLevel*)dataLevel->getData();
            bm->onOver();
        }
        dataLevel->MoveNext();
    }
}


/**********************
  DRAWSCENE NEW LEVEL
**********************/

void SceneCreateMission::drawSceneNewLevel () {
     
	
	verifyOverElements_NewLevel();
	stars->draw();
	
	for (int i=0; i<MAX_INDEXZ; i++) {
		drawSceneNewLevelByIndexZ(i);
	}
	
}

void SceneCreateMission::drawSceneNewLevelByIndexZ(int z) {
     
	if (frameUpLevels->getIndexZ() == z) {
		frameUpLevels->draw();
	}
	
	if (frameDown->getIndexZ() == z) {
		frameDown->draw();
	}
	
	if (faceEnemy1->getIndexZ() == z) {
		faceEnemy1->draw();
	}
	
	if (textHelp->getIndexZ() == z) {
		textHelp->draw();
	}
	
    if (bgFormLevel->getIndexZ() == z) {
		bgFormLevel->draw();
	}
	
    if (titleFormLevel->getIndexZ() == z) {
		titleFormLevel->draw();
	}
	
	if (levelName->getIndexZ() == z) {
		levelName->draw();
	}
	if (provinceName->getIndexZ() == z) {
		provinceName->draw();
	}
	
	if (titleTypeScenary->getIndexZ() == z) {
		titleTypeScenary->draw();
	}
	
	if (tScClosed->getIndexZ() == z) {
		tScClosed->draw();
	}
	
	if (tScOpened->getIndexZ() == z) {
		tScOpened->draw();
	}

	if (bBack->getIndexZ() == z) {
		bBack->draw();
	}
	
	if (bCreateLevel->getIndexZ() == z) {
		bCreateLevel->draw();
	}
}

void SceneCreateMission::verifyClickElements_NewLevel() {
	if (tScOpened->isOnMouseOver()) {
		tScOpened->setActive(true);
	}
	if (tScClosed->isOnMouseOver()) {
		tScClosed->setActive(true);
	}
	if (bCreateLevel->isOnMouseOver()) {
		bCreateLevel->OnClick(this, bCreateLevel);
	}
	if (bBack->isOnMouseOver()) {
		bBack->OnClick(this, bBack);
	}
	if (levelName->isOnMouseOver()) {
		levelName->setActive(true);
	}
	if (provinceName->isOnMouseOver()) {
		provinceName->setActive(true);
	}

}

void SceneCreateMission::verifyOverElements_NewLevel() {
	levelName->onOver();
	provinceName->onOver();
	bBack->onOver();
	bCreateLevel->onOver();
}

/**********************
  DRAWSCENE HELP
**********************/

void SceneCreateMission::drawSceneHelp () {
	
	verifyOverElements_Help();
	elmImgSave[0]->draw();
	
	for (int i=0; i<MAX_INDEXZ; i++) {
		drawSceneHelpByIndexZ(i);
	}
	
}

void SceneCreateMission::drawSceneHelpByIndexZ(int z) {
	if (frameUp->getIndexZ() == z) {
		frameUp->draw();
	}
	if (frameDown->getIndexZ() == z) {
		frameDown->draw();
	}
	if (bgHelp->getIndexZ() == z) {
		bgHelp->draw();
	}

	if (nElmHelp==-1) {
		if (titleIndex->getIndexZ() == z) {
			titleIndex->draw();
		}
		if (bHelp1->getIndexZ() == z) {
			bHelp1->draw();
		}
		if (bHelp2->getIndexZ() == z) {
			bHelp2->draw();
		}
		if (bHelp3->getIndexZ() == z) {
			bHelp3->draw();
		}
		if (bHelp4->getIndexZ() == z) {
			bHelp4->draw();
		}
	} else {
		if (elmHelp->getIndexZ() == z) {
			elmHelp->draw();
		}
	}
	
	if (bIndex->getIndexZ() == z) {
		bIndex->draw();
	}
	if (bPrevious->getIndexZ() == z) {
		bPrevious->draw();
	}
	if (bNext->getIndexZ() == z) {
		bNext->draw();
	}
	if (bCancel->getIndexZ() == z) {
		bCancel->draw();
	}
}

void SceneCreateMission::verifyClickElements_Help() {
	if (bIndex->isOnMouseOver()) {
		bIndex->OnClick(this, bIndex);
	}
	if (bPrevious->isOnMouseOver()) {
		bPrevious->OnClick(this, bPrevious);
	}
	if (bNext->isOnMouseOver()) {
		bNext->OnClick(this, bNext);
	}
	if (bCancel->isOnMouseOver()) {
		bCancel->OnClick(this, bCancel);
	}
	
	if (nElmHelp==-1) {
		if (bHelp1->isOnMouseOver()) {
			bHelp1->OnClick(this, bHelp1);
		}
		if (bHelp2->isOnMouseOver()) {
			bHelp2->OnClick(this, bHelp2);
		}
		if (bHelp3->isOnMouseOver()) {
			bHelp3->OnClick(this, bHelp3);
		}
		if (bHelp4->isOnMouseOver()) {
			bHelp4->OnClick(this, bHelp4);
		}
	}
}


void SceneCreateMission::verifyOverElements_Help() {
	if (nElmHelp==-1) {
		bHelp1->onOver();
		bHelp2->onOver();
		bHelp3->onOver();
		bHelp4->onOver();
	}
	bIndex->onOver();
	bPrevious->onOver();
	bNext->onOver();
	bCancel->onOver();
}


bool SceneCreateMission::drawScene() {
	
	glClear(GL_COLOR_BUFFER_BIT); // | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	
	drawCommonsScene ();
	
	switch(statusScene) {
	
		case SCENE_CREATEMISSION_MAIN:
	
			drawSceneMain();
		
			// Comprobando teclas para opciones			
			{ SDL_Event event;
				while ( SDL_PollEvent(&event) ) {
					if ( event.type == SDL_QUIT ) {
						goToScene("quit");
					}
					
					if ( event.type == SDL_KEYDOWN ) {
						if ( event.key.keysym.sym == SDLK_ESCAPE ) {
							goToScene("menu");
						}
        				if ( event.key.keysym.sym == SDLK_LEFT ) {
							dataMissions->previousIndex();
        				}
						if ( event.key.keysym.sym == SDLK_RIGHT ) {
							dataMissions->nextIndex();
        				}
					}
					
					if ( event.type == SDL_MOUSEBUTTONDOWN ) {
						if ( event.button.button == SDL_BUTTON_LEFT ) {
							verifyClickElements_Main();
						}
        				if ( ( event.button.button == 4 ) ) {
        					dataMissions->previousIndex();
        				}
						if ( ( event.button.button == 5 ) ) {
        					dataMissions->nextIndex();
        				}
					}
		
				}
			}
			
		break;
			
		case SCENE_CREATEMISSION_NEW:
	
			drawSceneNewMission();
		
			// Comprobando teclas para opciones			
			{ SDL_Event event;
				while ( SDL_PollEvent(&event) ) {
					if ( event.type == SDL_QUIT ) {
						goToScene("quit");
					}
					
					if ( event.type == SDL_KEYDOWN ) {
						missionName->insertTextUnicode(event.key.keysym.sym, event.key.keysym.unicode);
						if ( event.key.keysym.sym == SDLK_ESCAPE ) {
							goToScene("menu");
						}
					}
					
					if ( event.type == SDL_MOUSEBUTTONDOWN ) {
						if ( event.button.button == SDL_BUTTON_LEFT ) {
							verifyClickElements_NewMision();
						}
					}
		
				}
			}
			
		break;
			
		case SCENE_CREATEMISSION_LEVELS:
	
			drawSceneLevels();
		
			// Comprobando teclas para opciones			
			{ SDL_Event event;
				while ( SDL_PollEvent(&event) ) {
					if ( event.type == SDL_QUIT ) {
						goToScene("quit");
					}
					
					if ( event.type == SDL_KEYDOWN ) {
						if ( event.key.keysym.sym == SDLK_ESCAPE ) {
							goToScene("menu");
						}
        				if ( event.key.keysym.sym == SDLK_UP ) {
							dataLevel->upItems();
        				}
						if ( event.key.keysym.sym == SDLK_DOWN ) {
							dataLevel->downItems();
        				}
					}
					
					if ( event.type == SDL_MOUSEBUTTONDOWN ) {
						if ( event.button.button == SDL_BUTTON_LEFT ) {
							verifyClickElements_Levels();
						}
        				if ( ( event.button.button == 4 ) ) {
        					dataLevel->upItems();
        				}
						if ( ( event.button.button == 5 ) ) {
        					dataLevel->downItems();
        				}
					}
		
				}
			}
			
		break;
			
		case SCENE_CREATEMISSION_NEWLEVEL:
	
			drawSceneNewLevel();
		
			// Comprobando teclas para opciones			
			{ SDL_Event event;
				while ( SDL_PollEvent(&event) ) {
					if ( event.type == SDL_QUIT ) {
						goToScene("quit");
					}
					
					if ( event.type == SDL_KEYDOWN ) {
						levelName->insertTextUnicode(event.key.keysym.sym, event.key.keysym.unicode);
						if ( event.key.keysym.sym == SDLK_ESCAPE ) {
							goToScene("menu");
						}
					}
					
					if ( event.type == SDL_MOUSEBUTTONDOWN ) {
						if ( event.button.button == SDL_BUTTON_LEFT ) {
							verifyClickElements_NewLevel();
						}
					}
		
				}
			}
			
		break;
		
		default:
			
			// Comprobando teclas para opciones			
			{ SDL_Event event;
				while ( SDL_PollEvent(&event) ) {
					if ( event.type == SDL_QUIT ) {
						goToScene("quit");
					}
					
					if ( event.type == SDL_KEYDOWN ) {
						goToScene("menu");
					}
					
					if ( event.type == SDL_MOUSEBUTTONDOWN ) {
						goToScene("menu");
					}
		
				}
			}
			
		break;
			
		case SCENE_CREATEMISSION_HELP:
			
			drawSceneHelp();
		
			// Comprobando teclas para opciones			
			{ SDL_Event event;
				while ( SDL_PollEvent(&event) ) {
					if ( event.type == SDL_QUIT ) {
						goToScene("quit");
					}
										
					if ( event.type == SDL_KEYDOWN ) {
						if ( event.key.keysym.sym == SDLK_ESCAPE ) {
							setStatusScene(SCENE_CREATEMISSION_MAIN);
						}
					}
					
					if ( event.type == SDL_MOUSEBUTTONDOWN ) {
						if ( event.button.button == SDL_BUTTON_LEFT ) {
							verifyClickElements_Help();
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
void SceneCreateMission::unLoad() {

	unLoadCommons();
	
    //setStatusScene(SCENE_CREATEMISSION_MAIN);
	//Missions::GetInstance()->currentMission = NULL;
	delete bBack;
	delete bNewMission;
	delete bNewLevel;
	delete bCreateMission;
	delete bCreateLevel;
	delete bEdit;
	delete bPlay;
	delete bHelp;
	
	delete elmHelp;
	
	delete titleIndex;
	
	delete bIndex;
	delete bPrevious;
	delete bNext;
	delete bCancel;

	delete bHelp1;
	delete bHelp2;
	delete bHelp3;
	delete bHelp4;

	delete levelName;
	delete provinceName;
	delete titleMission;

	delete missionName;
	delete nameAuthor;
	delete nomission;
	delete nolevels;
	
	delete bgCoverFlow;
    delete bgInfoMission;
	delete frameUp;
    delete frameDown;
	delete dataMissions;
	
	dataLevel->MoveFirst();
	while (!dataLevel->isEOF()) {
        delete (ButtonLevel*)dataLevel->getData();
        dataLevel->MoveNext();
    }
	delete dataLevel;
	
	delete faceEnemy1;
	delete bgLevels;
	delete nameMissionCover;
	delete authorMissionCover;
	delete nLevelsCover;
	delete textHelp;
	
	delete titleTypeScenary;
	delete tScOpened;
	delete tScClosed;

	delete bgFormMission;
	delete bgFormLevel;
	delete titleFormMission;
	delete titleFormLevel;
	
	delete stars;
	
	Sounds::GetInstance()->unLoad();
	
	isLoad = false;
	
    Debug::GetInstance()->writeText("Escenario 'createmissions' descargado");
    
}
