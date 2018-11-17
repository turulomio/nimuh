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
 
#include "scene_editgame.h"

class SceneEditGame;

void typeBoard_SceneEditGame_OnClick (Scene *s, SelectButton *b) {
	SceneEditGame* se = (SceneEditGame*)s;
	EditBoard::GetInstance()->setTypeSize(se->typeBoard->getIndex());
}

void typeFloor_SceneEditGame_OnClick (Scene *s, SelectButton *b) {
	SceneEditGame* se = (SceneEditGame*)s;
	EditBoard::GetInstance()->setTypeFloor(se->typeFloor->getIndex());
}

void typePavement_SceneEditGame_OnClick (Scene *s, SelectButton *b) {
	SceneEditGame* se = (SceneEditGame*)s;
	EditBoard::GetInstance()->setTypePavement(se->typePavement->getIndex());
}

void typeTiled_SceneEditGame_OnClick (Scene *s, SelectButton *b) {
	SceneEditGame* se = (SceneEditGame*)s;
	EditBoard::GetInstance()->getScenary()->setTypeTiled(se->typeTiled->getIndex());
}

void typeWall_SceneEditGame_OnClick (Scene *s, SelectButton *b) {
	SceneEditGame* se = (SceneEditGame*)s;
	EditBoard::GetInstance()->setTypeWall(se->typeWall->getIndex());
}

void nTilesClosed_SceneEditGame_OnClick (Scene *s, SelectButton *b) {
	SceneEditGame* se = (SceneEditGame*)s;
	EditBoard::GetInstance()->getScenary()->setNVerticalTiles(se->nTilesClosed->getIndex());
}

void typeTerrain_SceneEditGame_OnClick (Scene *s, SelectButton *b) {
	SceneEditGame* se = (SceneEditGame*)s;
	EditBoard::GetInstance()->getScenary()->setTypeTerrain(se->typeTerrain->getIndex());
}

void typeWallScenary_SceneEditGame_OnClick (Scene *s, SelectButton *b) {
	SceneEditGame* se = (SceneEditGame*)s;
	EditBoard::GetInstance()->getScenary()->setTypeWall(se->typeWallScenary->getIndex());
}

void colorWall_SceneEditGame_OnClick (Scene *s, SelectButton *b) {
	SceneEditGame* se = (SceneEditGame*)s;
	int ind = se->colorWall->getIndex();
	int red = se->vcolorsWall->getColor(ind)->r;
	int green = se->vcolorsWall->getColor(ind)->g;
	int blue = se->vcolorsWall->getColor(ind)->b;
	EditBoard::GetInstance()->getScenary()->setColorInWalls(red, green, blue);
}

void bRules_SceneEditGame_OnClick (Scene *s, Button *b) {
	EditBoard::GetInstance()->getScenary()->swapShowGuides();
}

void bAddObject_SceneEditGame_OnClick (Scene *s, Button *b) {
	SceneEditGame* se = (SceneEditGame*)s;
	se->setSaveImage(true);
	se->setStatusScene(SCENE_EDITGAME_ADDOBJECT);
}

void insertObjectsGame_SceneEditGame_OnClick (Scene *s, Button *b) {
	SceneEditGame* se = (SceneEditGame*)s;
	EditBoard::GetInstance()->getScenary()->addObject(TYPEOBJECT_3D, ORIGENOBJECT_GAME, b->getParameter("name"));
	se->setStatusScene(SCENE_EDITGAME_MAIN);
}

void insertObjectsPersonal_SceneEditGame_OnClick (Scene *s, Button *b) {
	SceneEditGame* se = (SceneEditGame*)s;
	int tObj = TYPEOBJECT_3D;
	if (EditBoard::GetInstance()->getSceneEditGame()->rad2d->getActive()) {
		tObj = TYPEOBJECT_2D;
	}	
	
	EditBoard::GetInstance()->getScenary()->addObject(tObj, ORIGENOBJECT_PERSONAL, b->getParameter("name"));
	se->setStatusScene(SCENE_EDITGAME_MAIN);
}

void bInsertText_SceneGame_OnClick (Scene *s, Button *b) {
	SceneEditGame* se = (SceneEditGame*)s;
	string font = "";
	int align = ALIGN_LEFT;
	char tmp[32];
	sprintf(tmp, "font-wall%d", EditBoard::GetInstance()->getSceneEditGame()->typeTextsInWall->getIndex());
	font = tmp;
	if (EditBoard::GetInstance()->getSceneEditGame()->radAlignLeftText->getActive()) {
		align = ALIGN_LEFT;
	} else if (EditBoard::GetInstance()->getSceneEditGame()->radAlignCenterText->getActive()) {
		align = ALIGN_CENTER;
	} else if (EditBoard::GetInstance()->getSceneEditGame()->radAlignRightText->getActive()) {
		align = ALIGN_RIGHT;
	}
	Color c;
	int ind = se->colorTextsInWall->getIndex();
	c.r = se->vcolorsTextInWall->getColor(ind)->r;
	c.g = se->vcolorsTextInWall->getColor(ind)->g;
	c.b = se->vcolorsTextInWall->getColor(ind)->b;
	EditBoard::GetInstance()->getScenary()->addTextObject(EditBoard::GetInstance()->getSceneEditGame()->taText->getText(), font, align, c, 10, 10, 1.0, false, false);
	se->setStatusScene(SCENE_EDITGAME_MAIN);
}

void bObjectsGame_SceneEditGame_OnClick (Scene *s, Button *b) {
	SceneEditGame* se = (SceneEditGame*)s;
	se->bObjectsGame->setIndexZ(2);
	se->bObjectsGame->setRGB(255,255,255);
	se->bObjectsPersonal->setIndexZ(0);
	se->bObjectsPersonal->setRGB(160,160,160);
	se->bObjectsTexts->setIndexZ(0);
	se->bObjectsTexts->setRGB(160,160,160);
	se->setPageAddObject(SCENE_EDITGAME_ADDOBJECT_GAME);
}

void bObjectsPersonal_SceneEditGame_OnClick (Scene *s, Button *b) {
	SceneEditGame* se = (SceneEditGame*)s;
	se->bObjectsPersonal->setIndexZ(2);
	se->bObjectsPersonal->setRGB(255,255,255);
	se->bObjectsGame->setIndexZ(0);
	se->bObjectsGame->setRGB(160,160,160);
	se->bObjectsTexts->setIndexZ(0);
	se->bObjectsTexts->setRGB(160,160,160);
	se->setPageAddObject(SCENE_EDITGAME_ADDOBJECT_PERSONAL);
}

void bObjectsTexts_SceneEditGame_OnClick (Scene *s, Button *b) {
	SceneEditGame* se = (SceneEditGame*)s;
	se->bObjectsTexts->setIndexZ(2);
	se->bObjectsTexts->setRGB(255,255,255);
	se->bObjectsPersonal->setIndexZ(0);
	se->bObjectsPersonal->setRGB(160,160,160);
	se->bObjectsGame->setIndexZ(0);
	se->bObjectsGame->setRGB(160,160,160);
	se->setPageAddObject(SCENE_EDITGAME_ADDOBJECT_TEXT);
}

void bInfoMain_SceneEditGame_OnClick (Scene *s, Button *b) {
	SceneEditGame* se = (SceneEditGame*)s;
	se->bInfoMain->setIndexZ(2);
	se->bInfoMain->setRGB(255,255,255);
	se->bInfoData->setIndexZ(0);
	se->bInfoData->setRGB(160,160,160);
	se->bInfoMusic->setIndexZ(0);
	se->bInfoMusic->setRGB(160,160,160);
	se->setPageEditInfo(SCENE_EDITGAME_EDITINFO_MAIN);
}

void bInfoData_SceneEditGame_OnClick (Scene *s, Button *b) {
	SceneEditGame* se = (SceneEditGame*)s;
	se->bInfoMain->setIndexZ(0);
	se->bInfoMain->setRGB(160,160,160);
	se->bInfoData->setIndexZ(2);
	se->bInfoData->setRGB(255,255,255);
	se->bInfoMusic->setIndexZ(0);
	se->bInfoMusic->setRGB(160,160,160);
	se->setPageEditInfo(SCENE_EDITGAME_EDITINFO_DATA);
}

void bInfoMusic_SceneEditGame_OnClick (Scene *s, Button *b) {
	SceneEditGame* se = (SceneEditGame*)s;
	se->bInfoMain->setIndexZ(0);
	se->bInfoMain->setRGB(160,160,160);
	se->bInfoData->setIndexZ(0);
	se->bInfoData->setRGB(160,160,160);
	se->bInfoMusic->setIndexZ(2);
	se->bInfoMusic->setRGB(255,255,255);
	se->setPageEditInfo(SCENE_EDITGAME_EDITINFO_MUSIC);
}

void bSave_SceneEditGame_OnClick (Scene *s, Button *b) {
	SceneEditGame* se = (SceneEditGame*)s;
	
	if (EditBoard::GetInstance()->save()) { 
        se->showMessageBox(Language::GetInstance()->getText("info"), Language::GetInstance()->getText("savefilesuccessful"), SCENE_EDITGAME_MAIN);
    }
}

void bClean_SceneEditGame_OnClick (Scene *s, Button *b) {
	SceneEditGame* se = (SceneEditGame*)s;
	se->setSaveImage(true);
	se->setStatusScene(SCENE_EDITGAME_CLEAN);
}

void bCleanBoard_SceneEditGame_OnClick (Scene *s, Button *b) {
	SceneEditGame* se = (SceneEditGame*)s;
	EditBoard::GetInstance()->cleanWalls();
	se->setStatusScene(SCENE_EDITGAME_MAIN);
}

void bCleanScenary_SceneEditGame_OnClick (Scene *s, Button *b) {
	SceneEditGame* se = (SceneEditGame*)s;
	EditBoard::GetInstance()->cleanScenary();
	se->setStatusScene(SCENE_EDITGAME_MAIN);
}

void bCleanReset_SceneEditGame_OnClick (Scene *s, Button *b) {
	SceneEditGame* se = (SceneEditGame*)s;
	EditBoard::GetInstance()->loadLevel();
	se->setStatusScene(SCENE_EDITGAME_MAIN);
}

void bHelp_SceneEditGame_OnClick (Scene *s, Button *b) {
	SceneEditGame* se = (SceneEditGame*)s;
	se->setSaveImage(true);
	se->setStatusScene(SCENE_EDITGAME_HELP);
}

void alert_bQuit_SceneEditGame_OnClick (Scene *s, Button *b, string data) {
	SceneEditGame* se = (SceneEditGame*)s;
	if (b->getParameter("type")=="accept") {
		Sounds::GetInstance()->getSound("music_editor")->stop(2000);
		se->goToScene("createmission", 2000, SCENE_TRANSITION_FADEOUT);
	} else {
		se->setStatusSceneWithReturnSceneFromMessage();
	}
}

void bQuit_SceneEditGame_OnClick (Scene *s, Button *b) {
	SceneEditGame* se = (SceneEditGame*)s;
	se->showAlert(Language::GetInstance()->getText("info"), Language::GetInstance()->getText("areyousurequit"), alert_bQuit_SceneEditGame_OnClick, SCENE_EDITGAME_MAIN);
}

void btHandTray_SceneEditGame_OnClick (Scene *s, Button *b) {
	SceneEditGame* se = (SceneEditGame*)s;
	se->titleFood->setText(EditBoard::GetInstance()->infoTray[0].title);
	se->textFood->setText(EditBoard::GetInstance()->infoTray[0].text);
	if (WorkingData::GetInstance()->existFile(Missions::GetInstance()->currentLevel->getPath()+"/food.png")) {
		SDL_Surface *sfc = WorkingSurfaces::GetInstance()->surfaceFromImage(Missions::GetInstance()->currentLevel->getPath()+"/food.png");
		if ( (sfc->h>200) || (sfc->w>200) ) {
			se->infoImageFood->setRGB(255, 0, 0);
			se->infoImageFood->changeFrameLanguage(0, "font-texts", "nosizefood-png", ALIGN_CENTER);
		} else {
			se->infoImageFood->setRGB(255, 255, 255);
			se->infoImageFood->changeFrameFile(0, Missions::GetInstance()->currentLevel->getPath()+"/food.png");
		}
		SDL_FreeSurface(sfc);
	} else {
		se->infoImageFood->setRGB(255, 0, 0);
		string text = Language::GetInstance()->getText("nofood-png") + "|" + Missions::GetInstance()->currentLevel->getPath();
		se->infoImageFood->changeFrameText(0, "font-texts", text, ALIGN_CENTER);
	}
	se->setSaveImage(true);
	se->setStatusScene(SCENE_EDITGAME_EDITFOOD);
}

void bAccept_SceneEditGame_OnClick (Scene *s, Button *b) {
	SceneEditGame* se = (SceneEditGame*)s;
	if (se->getStatusScene()==SCENE_EDITGAME_EDITFOOD) {
		EditBoard::GetInstance()->infoTray[0].title = se->titleFood->getText();
		EditBoard::GetInstance()->infoTray[0].text = se->textFood->getText();
		se->setStatusScene(SCENE_EDITGAME_MAIN);
    } else if (se->getStatusScene()==SCENE_EDITGAME_EDITINFO) {
		Missions::GetInstance()->currentMission->setName(se->missionName->getText());
		Missions::GetInstance()->currentMission->setNameAuthor(se->nameAuthor->getText());
		Missions::GetInstance()->currentMission->save();
		EditBoard::GetInstance()->town.name = se->levelName->getText();
		EditBoard::GetInstance()->town.province = se->provinceName->getText();
		if (se->radMusic0->getActive()) {
			EditBoard::GetInstance()->setTypeMusic(0);
		} else if (se->radMusic1->getActive()) {
			EditBoard::GetInstance()->setTypeMusic(1);
		} else if (se->radMusic2->getActive()) {
			EditBoard::GetInstance()->setTypeMusic(2);
		} else if (se->radMusic3->getActive()) {
			EditBoard::GetInstance()->setTypeMusic(3);
		}
		
		se->setStatusScene(SCENE_EDITGAME_MAIN);
    } else if (se->getStatusScene()==SCENE_EDITGAME_ADDINFOTOWN) {
		if (se->indexEditInfoTown<0) {
			InformationTown it;
			it.title = se->eTitleInfoTown->getText();
			it.text = se->taInfoTown->getText();
			char tmp[4];
			sprintf(tmp, "%d", se->typeButtonInfoTown->getIndex());
			it.button = tmp;
			EditBoard::GetInstance()->getSceneEditGame()->addInfoTown(it);
		} else {
			EditBoard::GetInstance()->infoTown[se->indexEditInfoTown].title = se->eTitleInfoTown->getText();
			EditBoard::GetInstance()->infoTown[se->indexEditInfoTown].text = se->taInfoTown->getText();
			char tmp[4];
			sprintf(tmp, "%d", se->typeButtonInfoTown->getIndex());
			EditBoard::GetInstance()->infoTown[se->indexEditInfoTown].button = tmp;
			((InfoButton*)se->dataInfo->getData(se->indexEditInfoTown))->setTitle(se->eTitleInfoTown->getText());
		}
		se->setStatusScene(SCENE_EDITGAME_EDITINFO);
    }
}

void bCancel_SceneEditGame_OnClick (Scene *s, Button *b) {
	SceneEditGame* se = (SceneEditGame*)s;
	if (se->getStatusScene()==SCENE_EDITGAME_ADDINFOTOWN) {
    	se->setStatusScene(SCENE_EDITGAME_EDITINFO);
	} else {
		se->setStatusScene(SCENE_EDITGAME_MAIN);
	}
}

void bEditInfo_SceneEditGame_OnClick (Scene *s, Button *b) {
	SceneEditGame* se = (SceneEditGame*)s;
	se->setSaveImage(true);
    se->missionName->setActive(true);
    se->missionName->setText(Missions::GetInstance()->currentMission->getName());
    se->nameAuthor->setText(Missions::GetInstance()->currentMission->getNameAuthor());
    se->levelName->setText(EditBoard::GetInstance()->town.name);
    se->provinceName->setText(EditBoard::GetInstance()->town.province);
	se->setStatusScene(SCENE_EDITGAME_EDITINFO);
}

void bAddInfo_SceneEditGame_OnClick (Scene *s, Button *b) {
	SceneEditGame* se = (SceneEditGame*)s;
	se->setSaveImage(true, 1);
	if ((int)EditBoard::GetInstance()->infoTown.size()>=4) {
        se->showMessageBox(Language::GetInstance()->getText("info"), Language::GetInstance()->getText("nomoredata"), SCENE_EDITGAME_EDITINFO);
    } else {
    	se->indexEditInfoTown = -1;
    	se->typeButtonInfoTown->setFrame(0);
    	se->eTitleInfoTown->setText("");
    	se->taInfoTown->setText("");
	    se->eTitleInfoTown->setActive(true);
    	se->setStatusScene(SCENE_EDITGAME_ADDINFOTOWN);
    }
}

void bEditInfoButton_SceneEditGame_OnClick (Scene *s, Button *b) {
	SceneEditGame* se = (SceneEditGame*)s;
	se->setSaveImage(true, 1);
	se->indexEditInfoTown = atoi(b->getParameter("index").c_str());
	se->typeButtonInfoTown->setFrame(atoi(EditBoard::GetInstance()->infoTown[se->indexEditInfoTown].button.c_str()));
	se->eTitleInfoTown->setText(EditBoard::GetInstance()->infoTown[se->indexEditInfoTown].title);
	se->taInfoTown->setText(EditBoard::GetInstance()->infoTown[se->indexEditInfoTown].text);
	se->eTitleInfoTown->setActive(true);
	se->setStatusScene(SCENE_EDITGAME_ADDINFOTOWN);
}

void alert_bDeleteInfoButton_SceneEditGame_OnClick (Scene *s, Button *b, string data) {
	SceneEditGame* se = (SceneEditGame*)s;
	if (b->getParameter("type")=="accept") {
		int i = atoi(b->getParameter("index").c_str());
		EditBoard::GetInstance()->infoTown.erase(EditBoard::GetInstance()->infoTown.begin()+i);
		se->createInfoButtons();
	}
	se->setStatusSceneWithReturnSceneFromMessage();
}

void bDeleteInfoButton_SceneEditGame_OnClick (Scene *s, Button *b) {
	SceneEditGame* se = (SceneEditGame*)s;
	se->msg_bAccept->addParameter("index", b->getParameter("index"));
	se->showAlert(Language::GetInstance()->getText("info"), Language::GetInstance()->getText("areyousuredelete"), alert_bDeleteInfoButton_SceneEditGame_OnClick, SCENE_EDITGAME_EDITINFO);
}

void bViewHelp_SceneEditGame_OnClick (Scene *s, Button *b) {
	SceneEditGame* se = (SceneEditGame*)s;
	se->setElmHelp(atoi(b->getParameter("index_help").c_str()));
}

void bIndex_SceneEditGame_OnClick (Scene *s, Button *b) {
	SceneEditGame* se = (SceneEditGame*)s;
	se->setElmHelp(-1);
}

void bPrevious_SceneEditGame_OnClick (Scene *s, Button *b) {
	SceneEditGame* se = (SceneEditGame*)s;
	se->previousElmHelp();
}

void bNext_SceneEditGame_OnClick (Scene *s, Button *b) {
	SceneEditGame* se = (SceneEditGame*)s;
	se->nextElmHelp();
}

/*****************************
**
** CLASE InfoButton
**
******************************/	

InfoButton::InfoButton() : Group () {
	
	indexz = 0;
	
	bg = new Element();	
	bg->setX(0);
	bg->setY(0);
	bg->addFrameFileFromData("/interface/boxuser_text.png");
	this->addElement(bg);
		
	title = new Element();	
	title->setX(15);
	title->setY(22);
	title->setVAlign(VALIGN_CENTER);
	title->addFrameSurface(Primitives::GetInstance()->rectangle(1, 1, 0, 0, 0));
	this->addElement(title);
	
	bEdit = new Button();
	bEdit->setScales(0.9, 0.95);
	bEdit->setAlign(ALIGN_CENTER);
	bEdit->setVAlign(VALIGN_CENTER);
	bEdit->setX(350);
	bEdit->setY(22);
	bEdit->imageOut(WorkingSurfaces::GetInstance()->surfaceFromImage((string)DATA_DIR + "/interface/" + Language::GetInstance()->getFilename("edit", "png")));
	bEdit->setAnimation("out");
	bEdit->OnClick = bEditInfoButton_SceneEditGame_OnClick;
	this->addElement(bEdit);
		
	bDelete = new Button();
	bDelete->setScales(1.0, 1.1);
	bDelete->setAlign(ALIGN_CENTER);
	bDelete->setVAlign(VALIGN_CENTER);
	bDelete->setX(420);
	bDelete->setY(22);
	bDelete->imageOut(WorkingSurfaces::GetInstance()->surfaceFromImage((string)DATA_DIR + "/interface/delete.png"));
	bDelete->setAnimation("out");
	bDelete->OnClick = bDeleteInfoButton_SceneEditGame_OnClick;
	this->addElement(bDelete);
	
}

InfoButton::~InfoButton() {
	unLoad();
}

void InfoButton::setIndex (int i) { 
	index = i; 
	char tmp[4]; 
	sprintf(tmp, "%d", i);
	bEdit->addParameter("index", tmp); 
	bDelete->addParameter("index", tmp); 
}

void InfoButton::setTitle(string t) {
	
	title->changeFrameText(0, "font-texts", t, ALIGN_CENTER);
	
}

void InfoButton::draw() {
	work();
	bg->draw();
	title->draw();
	bEdit->draw();
	bDelete->draw();
}

void InfoButton::onOver() {
	bEdit->onOver();
	bDelete->onOver();
}

void InfoButton::verifyClick(SceneEditGame *sc) {
	if (bEdit->isOnMouseOver()) {
		bEdit->OnClick(sc, bEdit);
	}
	if (bDelete->isOnMouseOver()) {
		bDelete->OnClick(sc, bDelete);
	}
}

void InfoButton::unLoad() {
	bg->unLoad();
	title->unLoad();
	bEdit->unLoad();
	bDelete->unLoad();
}



/*****************************
**
** CLASE SceneEditGame
**
******************************/	

SceneEditGame::SceneEditGame() : Scene () {
	statusScene = SCENE_EDITGAME_MAIN;
	pageAddObject = SCENE_EDITGAME_ADDOBJECT_GAME;
	pageEditInfo = SCENE_EDITGAME_EDITINFO_MAIN;
	indexEditInfoTown = -1;
	nElmHelp = -1;
}

SceneEditGame::~SceneEditGame() {
	unLoad();
}

void SceneEditGame::addInfoTown(InformationTown it) {
	EditBoard::GetInstance()->infoTown.push_back(it);
	if (!EditBoard::GetInstance()->multiLanguage) {
		int index = (int)EditBoard::GetInstance()->infoTown.size()-1;
		InfoButton *bInfoButton = new InfoButton();
		bInfoButton->setIndex(index);
				
		bInfoButton->setTitle(EditBoard::GetInstance()->infoTown[index].title);
				
		getGroupScene()->addGroup((Group*)bInfoButton);
		
		dataInfo->add(bInfoButton);
	}
}

void SceneEditGame::createInfoButtons() {
	
	if (!EditBoard::GetInstance()->multiLanguage) {
		dataInfo->MoveFirst();
		while (!dataInfo->isEOF()) {
			delete (InfoButton*)dataInfo->getData();
			dataInfo->MoveNext();
		}
		dataInfo->inicialize();
			
		
		for (int i=0; i<(int)EditBoard::GetInstance()->infoTown.size(); i++) {
			int index = (int)EditBoard::GetInstance()->infoTown.size()-1;
			InfoButton *bInfoButton = new InfoButton();
			bInfoButton->setIndex(index);
					
			bInfoButton->setTitle(EditBoard::GetInstance()->infoTown[index].title);
					
			getGroupScene()->addGroup((Group*)bInfoButton);
			
			dataInfo->add(bInfoButton);
		}
	}
}

void SceneEditGame::setTextDisplay(int i) {
	if (i<0) {
		menuTown->show();
		menuText->hide();
	} else {
		menuText->setCurrentFrame(i);
		menuTown->hide();
		menuText->show();
	}
}

void SceneEditGame::setElmHelp(int i) { 
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

void SceneEditGame::setStatusScene(int s) {
     statusScene = s;
     switch(statusScene) {
        case SCENE_EDITGAME_EDITFOOD:
		case SCENE_EDITGAME_EDITINFO:
			bAccept->setY(487);
			bCancel->setX(505);
			bCancel->setY(487);
        break;
		case SCENE_EDITGAME_CLEAN:
			bAccept->setY(430);
			bCancel->setX(505);
			bCancel->setY(430);
		break;
		case SCENE_EDITGAME_HELP:
			bCancel->setX(691);
			bCancel->setY(487);
		break;
	}
}

void SceneEditGame::load() {

	initialize();
	
	statusScene = SCENE_EDITGAME_MAIN;
	pageAddObject = SCENE_EDITGAME_ADDOBJECT_GAME;
	pageEditInfo = SCENE_EDITGAME_EDITINFO_MAIN;
	
	vcolorsWall = new VectorColors();
	vcolorsWall->addColor(255, 255, 255);
	vcolorsWall->addColor(244, 244, 212);
	vcolorsWall->addColor(244, 239, 181);
	vcolorsWall->addColor(255, 222, 254);
	vcolorsWall->addColor(141, 195, 146);
	vcolorsWall->addColor(191, 166, 193);
	vcolorsWall->addColor(214, 227, 224);
	vcolorsWall->addColor(227, 214, 221);
	vcolorsWall->addColor(217, 203, 184);
	vcolorsWall->addColor(203, 217, 184);
	vcolorsWall->addColor(79, 142, 84);
	vcolorsWall->addColor(50, 166, 151);
	vcolorsWall->addColor(131, 131, 150);
	vcolorsWall->addColor(123, 113, 5);
	
	vcolorsTextInWall = new VectorColors();
	vcolorsTextInWall->addColor(255, 255, 255);
	vcolorsTextInWall->addColor(255, 0, 0);
	vcolorsTextInWall->addColor(129, 246, 77);
	vcolorsTextInWall->addColor(0, 0, 255);
	vcolorsTextInWall->addColor(251, 31, 176);
	vcolorsTextInWall->addColor(246, 232, 77);
	vcolorsTextInWall->addColor(246, 176, 77);
	vcolorsTextInWall->addColor(200, 77, 246);
	vcolorsTextInWall->addColor(114, 74, 52);
	vcolorsTextInWall->addColor(180, 180, 180);
	vcolorsTextInWall->addColor(120, 120, 120);
	vcolorsTextInWall->addColor(60, 60, 60);
	vcolorsTextInWall->addColor(0, 0, 0);
	
	char tmp[128], tmp_on[128], tmp_off[128];
	
	ProgressBar *pb = new ProgressBar(4, 200, 16, 255, 255, 255);
	pb->setBg((string)DATA_DIR + "/title.png");
	pb->setBgBar((string)DATA_DIR + "/bg_barprogress.png");
    pb->setPositionBar(World::width/2, 300);	
	
	pb->setText("font-texts", Language::GetInstance()->getText("loading_buttons"));
	pb->draw();

	// sounds
	
	Sounds::GetInstance()->addSoundFromData("music_editor", "music", "sound/music_editor.ogg");
	
	/************* 
		RADIOS
	*************/
	
	multiLanguageNoSupport = new Element();
	multiLanguageNoSupport->setCurrentScale(1.2);
	multiLanguageNoSupport->setAlign(ALIGN_CENTER);
	multiLanguageNoSupport->setVAlign(VALIGN_CENTER);
	multiLanguageNoSupport->setIndexZ(2);
	multiLanguageNoSupport->setXY(400, 200);
	multiLanguageNoSupport->addFrameText("font-texts", Language::GetInstance()->getText("multilanguagenosupport"), ALIGN_CENTER);
	getGroupScene()->addElement(multiLanguageNoSupport);
	
	sprintf(tmp_on, "%s/editgame/b_on.png", DATA_DIR);
	sprintf(tmp_off, "%s/editgame/b_off.png", DATA_DIR);
	
	
	bNimuh = new RadioButton(NULL);	
	bNimuh->setX(10);
	bNimuh->setY(370);
	bNimuh->addParameter("object", "nimuh");
	
	sprintf(tmp, "%s/editgame/b_nimuh.png", DATA_DIR);
	bNimuh->imageInactive(WorkingSurfaces::GetInstance()->mixSurfaces( WorkingSurfaces::GetInstance()->surfaceFromImage(tmp_off), WorkingSurfaces::GetInstance()->surfaceFromImage(tmp), NULL ));
	bNimuh->imageActive(WorkingSurfaces::GetInstance()->mixSurfaces( WorkingSurfaces::GetInstance()->surfaceFromImage(tmp_on), WorkingSurfaces::GetInstance()->surfaceFromImage(tmp), NULL ));
	
	getGroupScene()->addGroup(bNimuh);

	bEnemy1 = new RadioButton(bNimuh);
	bEnemy1->setX(10);
	bEnemy1->setY(415);
	bEnemy1->addParameter("object", "enemy1");
	
	sprintf(tmp, "%s/editgame/b_enemy1.png", DATA_DIR);
	bEnemy1->imageInactive(WorkingSurfaces::GetInstance()->mixSurfaces( WorkingSurfaces::GetInstance()->surfaceFromImage(tmp_off), WorkingSurfaces::GetInstance()->surfaceFromImage(tmp), NULL ));
	bEnemy1->imageActive(WorkingSurfaces::GetInstance()->mixSurfaces( WorkingSurfaces::GetInstance()->surfaceFromImage(tmp_on), WorkingSurfaces::GetInstance()->surfaceFromImage(tmp), NULL ));
	
	getGroupScene()->addGroup(bEnemy1);
	
	bEnemy2 = new RadioButton(bNimuh);
	bEnemy2->setX(10);
	bEnemy2->setY(460);
	bEnemy2->addParameter("object", "enemy2");
	
	sprintf(tmp, "%s/editgame/b_enemy2.png", DATA_DIR);
	bEnemy2->imageInactive(WorkingSurfaces::GetInstance()->mixSurfaces( WorkingSurfaces::GetInstance()->surfaceFromImage(tmp_off), WorkingSurfaces::GetInstance()->surfaceFromImage(tmp), NULL ));
	bEnemy2->imageActive(WorkingSurfaces::GetInstance()->mixSurfaces( WorkingSurfaces::GetInstance()->surfaceFromImage(tmp_on), WorkingSurfaces::GetInstance()->surfaceFromImage(tmp), NULL ));
	
	getGroupScene()->addGroup(bEnemy2);
	
	bEnemy3 = new RadioButton(bNimuh);
	bEnemy3->setX(10);
	bEnemy3->setY(505);
	bEnemy3->addParameter("object", "enemy3");
	
	sprintf(tmp, "%s/editgame/b_enemy3.png", DATA_DIR);
	bEnemy3->imageInactive(WorkingSurfaces::GetInstance()->mixSurfaces( WorkingSurfaces::GetInstance()->surfaceFromImage(tmp_off), WorkingSurfaces::GetInstance()->surfaceFromImage(tmp), NULL ));
	bEnemy3->imageActive(WorkingSurfaces::GetInstance()->mixSurfaces( WorkingSurfaces::GetInstance()->surfaceFromImage(tmp_on), WorkingSurfaces::GetInstance()->surfaceFromImage(tmp), NULL ));
	
	getGroupScene()->addGroup(bEnemy3);
	
	bDoor = new RadioButton(bNimuh);
	bDoor->setX(10);
	bDoor->setY(550);
	bDoor->addParameter("object", "door");
	
	sprintf(tmp, "%s/editgame/b_door.png", DATA_DIR);
	bDoor->imageInactive(WorkingSurfaces::GetInstance()->mixSurfaces( WorkingSurfaces::GetInstance()->surfaceFromImage(tmp_off), WorkingSurfaces::GetInstance()->surfaceFromImage(tmp), NULL ));
	bDoor->imageActive(WorkingSurfaces::GetInstance()->mixSurfaces( WorkingSurfaces::GetInstance()->surfaceFromImage(tmp_on), WorkingSurfaces::GetInstance()->surfaceFromImage(tmp), NULL ));

	getGroupScene()->addGroup(bDoor);
	
	bWallRight = new RadioButton(bNimuh);	
	bWallRight->setX(60);
	bWallRight->setY(415);
	bWallRight->addParameter("object", "wallright");
	
	sprintf(tmp, "%s/editgame/b_wall_right.png", DATA_DIR);
	bWallRight->imageInactive(WorkingSurfaces::GetInstance()->mixSurfaces( WorkingSurfaces::GetInstance()->surfaceFromImage(tmp_off), WorkingSurfaces::GetInstance()->surfaceFromImage(tmp), NULL ));
	bWallRight->imageActive(WorkingSurfaces::GetInstance()->mixSurfaces( WorkingSurfaces::GetInstance()->surfaceFromImage(tmp_on), WorkingSurfaces::GetInstance()->surfaceFromImage(tmp), NULL ));
	
	getGroupScene()->addGroup(bWallRight);
	
	bWallBottom = new RadioButton(bNimuh);
	bWallBottom->setX(60);
	bWallBottom->setY(460);
	bWallBottom->addParameter("object", "wallbottom");
	
	sprintf(tmp, "%s/editgame/b_wall_bottom.png", DATA_DIR);
	bWallBottom->imageInactive(WorkingSurfaces::GetInstance()->mixSurfaces( WorkingSurfaces::GetInstance()->surfaceFromImage(tmp_off), WorkingSurfaces::GetInstance()->surfaceFromImage(tmp), NULL ));
	bWallBottom->imageActive(WorkingSurfaces::GetInstance()->mixSurfaces( WorkingSurfaces::GetInstance()->surfaceFromImage(tmp_on), WorkingSurfaces::GetInstance()->surfaceFromImage(tmp), NULL ));

	getGroupScene()->addGroup(bWallBottom);
	
	bBlackHole1 = new RadioButton(bNimuh);
	bBlackHole1->setX(60);
	bBlackHole1->setY(505);
	bBlackHole1->addParameter("object", "blackhole1");
	
	sprintf(tmp, "%s/editgame/b_blackhole1.png", DATA_DIR);
	bBlackHole1->imageInactive(WorkingSurfaces::GetInstance()->mixSurfaces( WorkingSurfaces::GetInstance()->surfaceFromImage(tmp_off), WorkingSurfaces::GetInstance()->surfaceFromImage(tmp), NULL ));
	bBlackHole1->imageActive(WorkingSurfaces::GetInstance()->mixSurfaces( WorkingSurfaces::GetInstance()->surfaceFromImage(tmp_on), WorkingSurfaces::GetInstance()->surfaceFromImage(tmp), NULL ));
	
	getGroupScene()->addGroup(bBlackHole1);
	
	bBlackHole2 = new RadioButton(bNimuh);
	bBlackHole2->setX(60);
	bBlackHole2->setY(550);
	bBlackHole2->addParameter("object", "blackhole2");
	
	sprintf(tmp, "%s/editgame/b_blackhole2.png", DATA_DIR);
	bBlackHole2->imageInactive(WorkingSurfaces::GetInstance()->mixSurfaces( WorkingSurfaces::GetInstance()->surfaceFromImage(tmp_off), WorkingSurfaces::GetInstance()->surfaceFromImage(tmp), NULL ));
	bBlackHole2->imageActive(WorkingSurfaces::GetInstance()->mixSurfaces( WorkingSurfaces::GetInstance()->surfaceFromImage(tmp_on), WorkingSurfaces::GetInstance()->surfaceFromImage(tmp), NULL ));
	
	getGroupScene()->addGroup(bBlackHole2);
	
	bTrap = new RadioButton(bNimuh);
	bTrap->setX(110);
	bTrap->setY(460);
	bTrap->addParameter("object", "trap");
	
	sprintf(tmp, "%s/editgame/b_trap.png", DATA_DIR);
	bTrap->imageInactive(WorkingSurfaces::GetInstance()->mixSurfaces( WorkingSurfaces::GetInstance()->surfaceFromImage(tmp_off), WorkingSurfaces::GetInstance()->surfaceFromImage(tmp), NULL ));
	bTrap->imageActive(WorkingSurfaces::GetInstance()->mixSurfaces( WorkingSurfaces::GetInstance()->surfaceFromImage(tmp_on), WorkingSurfaces::GetInstance()->surfaceFromImage(tmp), NULL ));
	
	getGroupScene()->addGroup(bTrap);
	
	bKey = new RadioButton(bNimuh);
	bKey->setX(110);
	bKey->setY(505);
	bKey->addParameter("object", "key");
	
	sprintf(tmp, "%s/editgame/b_key.png", DATA_DIR);
	bKey->imageInactive(WorkingSurfaces::GetInstance()->mixSurfaces( WorkingSurfaces::GetInstance()->surfaceFromImage(tmp_off), WorkingSurfaces::GetInstance()->surfaceFromImage(tmp), NULL ));
	bKey->imageActive(WorkingSurfaces::GetInstance()->mixSurfaces( WorkingSurfaces::GetInstance()->surfaceFromImage(tmp_on), WorkingSurfaces::GetInstance()->surfaceFromImage(tmp), NULL ));
	
	getGroupScene()->addGroup(bKey);
	
	bDoorKey = new RadioButton(bNimuh);
	bDoorKey->setX(110);
	bDoorKey->setY(550);
	bDoorKey->addParameter("object", "doorkey");
	
	sprintf(tmp, "%s/editgame/b_grate.png", DATA_DIR);
	bDoorKey->imageInactive(WorkingSurfaces::GetInstance()->mixSurfaces( WorkingSurfaces::GetInstance()->surfaceFromImage(tmp_off), WorkingSurfaces::GetInstance()->surfaceFromImage(tmp), NULL ));
	bDoorKey->imageActive(WorkingSurfaces::GetInstance()->mixSurfaces( WorkingSurfaces::GetInstance()->surfaceFromImage(tmp_on), WorkingSurfaces::GetInstance()->surfaceFromImage(tmp), NULL ));
	
	getGroupScene()->addGroup(bDoorKey);
	
	bEat = new RadioButton(bNimuh);
	bEat->setX(160);
	bEat->setY(505);
	bEat->addParameter("object", "tray");
	
	sprintf(tmp, "%s/editgame/b_tray.png", DATA_DIR);
	bEat->imageInactive(WorkingSurfaces::GetInstance()->mixSurfaces( WorkingSurfaces::GetInstance()->surfaceFromImage(tmp_off), WorkingSurfaces::GetInstance()->surfaceFromImage(tmp), NULL ));
	bEat->imageActive(WorkingSurfaces::GetInstance()->mixSurfaces( WorkingSurfaces::GetInstance()->surfaceFromImage(tmp_on), WorkingSurfaces::GetInstance()->surfaceFromImage(tmp), NULL ));
	
	getGroupScene()->addGroup(bEat);
	
	bNimuh->setActive(true);
	
	pb->setText("font-texts", Language::GetInstance()->getText("loading_box"));
	pb->draw();
	
	/************* 
		SELECTS
	*************/
		
	typeBoard = new SelectButton();
	typeBoard->setX(564);
	typeBoard->setY(465);
	typeBoard->OnClick = typeBoard_SceneEditGame_OnClick;
	typeBoard->addObject(WorkingSurfaces::GetInstance()->surfaceFromImage((string)DATA_DIR + "/editgame/t_6x6.png"));
	typeBoard->addObject(WorkingSurfaces::GetInstance()->surfaceFromImage((string)DATA_DIR + "/editgame/t_7x7.png"));
	typeBoard->addObject(WorkingSurfaces::GetInstance()->surfaceFromImage((string)DATA_DIR + "/editgame/t_8x8.png"));
	typeBoard->addObject(WorkingSurfaces::GetInstance()->surfaceFromImage((string)DATA_DIR + "/editgame/t_9x9.png"));
	typeBoard->addObject(WorkingSurfaces::GetInstance()->surfaceFromImage((string)DATA_DIR + "/editgame/t_10x10.png"));
		
	typeFloor = new SelectButton();
	typeFloor->setX(564);
	typeFloor->setY(500);
	typeFloor->OnClick = typeFloor_SceneEditGame_OnClick;
	
	int i;
	
	for (i=0; i<BoardInfo::GetInstance()->getValueToInt("NTYPES_FLOOR"); i++) {
		sprintf(tmp, "%s/editgame/t_floor_%s.png", DATA_DIR, Converter::GetInstance()->fillZeros(i).c_str());
		typeFloor->addObject(WorkingSurfaces::GetInstance()->surfaceFromImage(tmp));
	}
	
	typeWall = new SelectButton();
	typeWall->setX(564);
	typeWall->setY(535);
	typeWall->OnClick = typeWall_SceneEditGame_OnClick;
	for (i=0; i<BoardInfo::GetInstance()->getValueToInt("NTYPES_WALL"); i++) {
		sprintf(tmp, "%s/editgame/t_wall_%s.png", DATA_DIR, Converter::GetInstance()->fillZeros(i).c_str());
		typeWall->addObject(WorkingSurfaces::GetInstance()->surfaceFromImage(tmp));
	}
	
	typePavement = new SelectButton();
	typePavement->setMinSeparateButtons(43);
	typePavement->setX(564);
	typePavement->setY(570);
	typePavement->OnClick = typePavement_SceneEditGame_OnClick;
	for (i=0; i<BoardInfo::GetInstance()->getValueToInt("NTYPES_PAVEMENT"); i++) {
		sprintf(tmp, "%s/editgame/t_pavement_%s.png", DATA_DIR, Converter::GetInstance()->fillZeros(i).c_str());
		typePavement->addObject(WorkingSurfaces::GetInstance()->surfaceFromImage(tmp));
	}
	
	typeTiled = new SelectButton();
	typeTiled->setX(705);
	typeTiled->OnClick = typeTiled_SceneEditGame_OnClick;

	for (i=0; i<BoardInfo::GetInstance()->getValueToInt("NTYPES_TILED"); i++) {
		sprintf(tmp, "%s/editgame/t_tiled_%s.png", DATA_DIR, Converter::GetInstance()->fillZeros(i).c_str());
		typeTiled->addObject(WorkingSurfaces::GetInstance()->surfaceFromImage(tmp));
	}

	nTilesClosed = new SelectButton();
	nTilesClosed->setMinSeparateButtons(23);
	nTilesClosed->setX(705);
	nTilesClosed->OnClick = nTilesClosed_SceneEditGame_OnClick;
	for (i=0; i<=7; i++) {
		sprintf(tmp, "%d", i);
		nTilesClosed->addObject(Fonts::GetInstance()->getSurface_TextBitMap("font-texts", ALIGN_CENTER, tmp));
	}
	
	nTilesClosed->setFrame(0);
	
	colorWall = new SelectButton();
	colorWall->setX(705);
	colorWall->OnClick = colorWall_SceneEditGame_OnClick;

	for (i=0; i<vcolorsWall->count(); i++) {
		colorWall->addObject(Primitives::GetInstance()->rectangle(23, 23, vcolorsWall->getColor(i)->r, vcolorsWall->getColor(i)->g, vcolorsWall->getColor(i)->b));
	}
	
	typeTerrain = new SelectButton();
	typeTerrain->setX(705);
	typeTerrain->setY(520);
	typeTerrain->OnClick = typeTerrain_SceneEditGame_OnClick;
	for (i=0; i<BoardInfo::GetInstance()->getValueToInt("NTYPES_TERRAIN"); i++) {
		sprintf(tmp, "%s/editgame/t_terrain_%s.png", DATA_DIR, Converter::GetInstance()->fillZeros(i).c_str());
		typeTerrain->addObject(WorkingSurfaces::GetInstance()->surfaceFromImage(tmp));
	}
	
	typeWallScenary = new SelectButton();
	typeWallScenary->setX(705);
	typeWallScenary->setY(525);
	typeWallScenary->OnClick = typeWallScenary_SceneEditGame_OnClick;
	for (i=0; i<BoardInfo::GetInstance()->getValueToInt("NTYPES_WALLSCENARY"); i++) {
		sprintf(tmp, "%s/editgame/t_wallscenary_%s.png", DATA_DIR, Converter::GetInstance()->fillZeros(i).c_str());
		typeWallScenary->addObject(WorkingSurfaces::GetInstance()->surfaceFromImage(tmp));
	}
	
	typeBoard->setArrows(WorkingSurfaces::GetInstance()->surfaceFromImage((string)DATA_DIR+"/editgame/arrow_left.png"), WorkingSurfaces::GetInstance()->surfaceFromImage((string)DATA_DIR+"/editgame/arrow_right.png"));
	typeFloor->setArrows(WorkingSurfaces::GetInstance()->surfaceFromImage((string)DATA_DIR+"/editgame/arrow_left.png"), WorkingSurfaces::GetInstance()->surfaceFromImage((string)DATA_DIR+"/editgame/arrow_right.png"));
	typePavement->setArrows(WorkingSurfaces::GetInstance()->surfaceFromImage((string)DATA_DIR+"/editgame/arrow_left.png"), WorkingSurfaces::GetInstance()->surfaceFromImage((string)DATA_DIR+"/editgame/arrow_right.png"));
	colorWall->setArrows(WorkingSurfaces::GetInstance()->surfaceFromImage((string)DATA_DIR+"/editgame/arrow_left.png"), WorkingSurfaces::GetInstance()->surfaceFromImage((string)DATA_DIR+"/editgame/arrow_right.png"));
	typeWall->setArrows(WorkingSurfaces::GetInstance()->surfaceFromImage((string)DATA_DIR+"/editgame/arrow_left.png"), WorkingSurfaces::GetInstance()->surfaceFromImage((string)DATA_DIR+"/editgame/arrow_right.png"));
	nTilesClosed->setArrows(WorkingSurfaces::GetInstance()->surfaceFromImage((string)DATA_DIR+"/editgame/arrow_left.png"), WorkingSurfaces::GetInstance()->surfaceFromImage((string)DATA_DIR+"/editgame/arrow_right.png"));
	typeTiled->setArrows(WorkingSurfaces::GetInstance()->surfaceFromImage((string)DATA_DIR+"/editgame/arrow_left.png"), WorkingSurfaces::GetInstance()->surfaceFromImage((string)DATA_DIR+"/editgame/arrow_right.png"));
	typeTerrain->setArrows(WorkingSurfaces::GetInstance()->surfaceFromImage((string)DATA_DIR+"/editgame/arrow_left.png"), WorkingSurfaces::GetInstance()->surfaceFromImage((string)DATA_DIR+"/editgame/arrow_right.png"));
	typeWallScenary->setArrows(WorkingSurfaces::GetInstance()->surfaceFromImage((string)DATA_DIR+"/editgame/arrow_left.png"), WorkingSurfaces::GetInstance()->surfaceFromImage((string)DATA_DIR+"/editgame/arrow_right.png"));
	
	bAddObject = new Button();
	bAddObject->setX(707);
	bAddObject->setY(545);
	bAddObject->imageOut(WorkingSurfaces::GetInstance()->surfaceFromImage((string)DATA_DIR + "/editgame/" + Language::GetInstance()->getFilename("addobject", "png")));
	bAddObject->setAnimation("out");
	bAddObject->OnClick = bAddObject_SceneEditGame_OnClick;
	getGroupScene()->addElement(bAddObject);
	
	
	pb->setText("font-texts", Language::GetInstance()->getText("loading_menu"));
	pb->draw();
	
	frameUp = new Element();	
	frameUp->setAlign(ALIGN_CENTER);
	frameUp->setVAlign(VALIGN_TOP);
	frameUp->setXY(World::width/2, 0);
	frameUp->addFrameSurface(WorkingSurfaces::GetInstance()->surfaceFromImage((string)DATA_DIR + "/windows/frame_up.png"));
	
	frameDown = new Element();
	frameDown->setAlign(ALIGN_CENTER);
	frameDown->setVAlign(VALIGN_BOTTOM);
	frameDown->setXY(World::width/2, 600);
	frameDown->addFrameSurface(WorkingSurfaces::GetInstance()->surfaceFromImage((string)DATA_DIR + "/windows/frame_down.png"));
	
	
	bgBox = new Element();	
	bgBox->setIndexZ(1);
	bgBox->setAlign(ALIGN_CENTER);
	bgBox->setVAlign(VALIGN_CENTER);
	bgBox->setXY(World::width/2, 300);
	bgBox->addFrameFileFromData("/windows/bigbox.png");
	
	getGroupScene()->addElement(bgBox);
	
	middleBox = new Element();	
	middleBox->setAlign(ALIGN_CENTER);
	middleBox->setVAlign(VALIGN_CENTER);
	middleBox->setXY(World::width/2, 300);
	middleBox->addFrameFileFromData("/windows/middlebox.png");
	
	getGroupScene()->addElement(middleBox);
	
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

	bIndex->OnClick = bIndex_SceneEditGame_OnClick;
	
	sprintf(tmp, Language::GetInstance()->getText("index").c_str());
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

	bPrevious->OnClick = bPrevious_SceneEditGame_OnClick;
	
	sprintf(tmp, Language::GetInstance()->getText("previous").c_str());
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

	bNext->OnClick = bNext_SceneEditGame_OnClick;
	
	sprintf(tmp, Language::GetInstance()->getText("next").c_str());
	bNext->imageOut(Fonts::GetInstance()->getSurface_TextBitMap("font-computer", ALIGN_CENTER, tmp));
	bNext->setAnimation("out");
	
	getGroupScene()->addElement(bNext);
	
	bHelp1 = new Button();
	bHelp1->addParameter("index_help", "0");
	bHelp1->setIndexZ(2);
	bHelp1->setScales(1.0, 1.05);
	bHelp1->setX(100);
	bHelp1->setY(150);

	bHelp1->OnClick = bViewHelp_SceneEditGame_OnClick;
	
	bHelp1->imageOut(Fonts::GetInstance()->getSurface_TextBitMap("font-texts", ALIGN_CENTER, Language::GetInstance()->getText("help_editlevel_1")));
	bHelp1->setAnimation("out");
	
	getGroupScene()->addElement(bHelp1);
	
	bHelp2 = new Button();
	bHelp2->addParameter("index_help", "1");
	bHelp2->setIndexZ(2);
	bHelp2->setScales(1.0, 1.05);
	bHelp2->setX(100);
	bHelp2->setY(185);

	bHelp2->OnClick = bViewHelp_SceneEditGame_OnClick;
	
	bHelp2->imageOut(Fonts::GetInstance()->getSurface_TextBitMap("font-texts", ALIGN_CENTER, Language::GetInstance()->getText("help_editlevel_2")));
	bHelp2->setAnimation("out");
	
	getGroupScene()->addElement(bHelp2);
	
	bHelp3 = new Button();
	bHelp3->addParameter("index_help", "2");
	bHelp3->setIndexZ(2);
	bHelp3->setScales(1.0, 1.05);
	bHelp3->setX(100);
	bHelp3->setY(220);

	bHelp3->OnClick = bViewHelp_SceneEditGame_OnClick;
	
	bHelp3->imageOut(Fonts::GetInstance()->getSurface_TextBitMap("font-texts", ALIGN_CENTER, Language::GetInstance()->getText("help_editlevel_3")));
	bHelp3->setAnimation("out");
	
	getGroupScene()->addElement(bHelp3);
	
	bHelp4 = new Button();
	bHelp4->addParameter("index_help", "3");
	bHelp4->setIndexZ(2);
	bHelp4->setScales(1.0, 1.05);
	bHelp4->setX(100);
	bHelp4->setY(255);

	bHelp4->OnClick = bViewHelp_SceneEditGame_OnClick;
	
	bHelp4->imageOut(Fonts::GetInstance()->getSurface_TextBitMap("font-texts", ALIGN_CENTER, Language::GetInstance()->getText("help_editlevel_4")));
	bHelp4->setAnimation("out");
	
	getGroupScene()->addElement(bHelp4);
	
	bHelp5 = new Button();
	bHelp5->addParameter("index_help", "4");
	bHelp5->setIndexZ(2);
	bHelp5->setScales(1.0, 1.05);
	bHelp5->setX(100);
	bHelp5->setY(290);

	bHelp5->OnClick = bViewHelp_SceneEditGame_OnClick;
	
	bHelp5->imageOut(Fonts::GetInstance()->getSurface_TextBitMap("font-texts", ALIGN_CENTER, Language::GetInstance()->getText("help_editlevel_5")));
	bHelp5->setAnimation("out");
	
	getGroupScene()->addElement(bHelp5);
	
	bHelp6 = new Button();
	bHelp6->addParameter("index_help", "5");
	bHelp6->setIndexZ(2);
	bHelp6->setScales(1.0, 1.05);
	bHelp6->setX(100);
	bHelp6->setY(325);

	bHelp6->OnClick = bViewHelp_SceneEditGame_OnClick;
	
	bHelp6->imageOut(Fonts::GetInstance()->getSurface_TextBitMap("font-texts", ALIGN_CENTER, Language::GetInstance()->getText("help_editlevel_6")));
	bHelp6->setAnimation("out");
	
	getGroupScene()->addElement(bHelp6);
	
	bHelp7 = new Button();
	bHelp7->addParameter("index_help", "6");
	bHelp7->setIndexZ(2);
	bHelp7->setScales(1.0, 1.05);
	bHelp7->setX(100);
	bHelp7->setY(360);

	bHelp7->OnClick = bViewHelp_SceneEditGame_OnClick;
	
	bHelp7->imageOut(Fonts::GetInstance()->getSurface_TextBitMap("font-texts", ALIGN_CENTER, Language::GetInstance()->getText("help_editlevel_7")));
	bHelp7->setAnimation("out");
	
	getGroupScene()->addElement(bHelp7);
	
	bHelp8 = new Button();
	bHelp8->addParameter("index_help", "8");
	bHelp8->setIndexZ(2);
	bHelp8->setScales(1.0, 1.05);
	bHelp8->setX(100);
	bHelp8->setY(395);

	bHelp8->OnClick = bViewHelp_SceneEditGame_OnClick;
	
	bHelp8->imageOut(Fonts::GetInstance()->getSurface_TextBitMap("font-texts", ALIGN_CENTER, Language::GetInstance()->getText("help_editlevel_8")));
	bHelp8->setAnimation("out");
	
	getGroupScene()->addElement(bHelp8);
	
	
	elmHelp = new Element();	
	elmHelp->setAlign(ALIGN_CENTER);
	elmHelp->setVAlign(VALIGN_CENTER);
	elmHelp->setXY(World::width/2, 300);
	
	elmHelp->addFrameSurface(WorkingSurfaces::GetInstance()->surfaceFromImage((string)DATA_DIR + "/help/" + Language::GetInstance()->getFilename("editlevel_help_1", "png")));
	elmHelp->addFrameSurface(WorkingSurfaces::GetInstance()->surfaceFromImage((string)DATA_DIR + "/help/" + Language::GetInstance()->getFilename("editlevel_help_2", "png")));
	elmHelp->addFrameSurface(WorkingSurfaces::GetInstance()->surfaceFromImage((string)DATA_DIR + "/help/" + Language::GetInstance()->getFilename("editlevel_help_3", "png")));
	elmHelp->addFrameSurface(WorkingSurfaces::GetInstance()->surfaceFromImage((string)DATA_DIR + "/help/" + Language::GetInstance()->getFilename("editlevel_help_4", "png")));
	elmHelp->addFrameSurface(WorkingSurfaces::GetInstance()->surfaceFromImage((string)DATA_DIR + "/help/" + Language::GetInstance()->getFilename("editlevel_help_5", "png")));
	elmHelp->addFrameSurface(WorkingSurfaces::GetInstance()->surfaceFromImage((string)DATA_DIR + "/help/" + Language::GetInstance()->getFilename("editlevel_help_6_1", "png")));
	elmHelp->addFrameSurface(WorkingSurfaces::GetInstance()->surfaceFromImage((string)DATA_DIR + "/help/" + Language::GetInstance()->getFilename("editlevel_help_6_2", "png")));
	elmHelp->addFrameSurface(WorkingSurfaces::GetInstance()->surfaceFromImage((string)DATA_DIR + "/help/" + Language::GetInstance()->getFilename("editlevel_help_7", "png")));
	elmHelp->addFrameSurface(WorkingSurfaces::GetInstance()->surfaceFromImage((string)DATA_DIR + "/help/" + Language::GetInstance()->getFilename("editlevel_help_8", "png")));
	
	getGroupScene()->addElement(elmHelp);
	
	setElmHelp(-1);
	
	titleFood = new Entry(NULL, 450, 25, 10, 10);
	titleFood->setIndexZ(2);
	titleFood->setNoSigns(true);
	titleFood->setMaxLetters(35);
	titleFood->setFontLabel("font-texts");
	titleFood->setFont("font-computer");
	titleFood->setLabel(Language::GetInstance()->getText("titlefood"));
	titleFood->setHorizontal(false);
	titleFood->setX(World::width/2);
	titleFood->setY(280);
	titleFood->addFrameBoxNormal(WorkingSurfaces::GetInstance()->surfaceFromImage((string)DATA_DIR + "/createmissions/bg_textbox.png"));
	titleFood->addFrameBoxOnOver(WorkingSurfaces::GetInstance()->surfaceFromImage((string)DATA_DIR + "/createmissions/bg_textbox_on.png"));
	titleFood->addFrameBoxActived(WorkingSurfaces::GetInstance()->surfaceFromImage((string)DATA_DIR + "/createmissions/bg_textbox_active.png"));
	
	getGroupScene()->addElement((Element*)titleFood);
	
	titleFood->setActive(true);
	
	textFood = new Entry(titleFood, 450, 25, 10, 10);
	textFood->setMultiline(true);
	textFood->setTotalRows(3);
	textFood->setIndexZ(2);
	textFood->setFontLabel("font-texts");
	textFood->setFont("font-computer");
	textFood->setLabel(Language::GetInstance()->getText("textfood"));
	textFood->setHorizontal(false);
	textFood->setX(World::width/2);
	textFood->setY(350);
	textFood->addFrameBoxNormal(WorkingSurfaces::GetInstance()->surfaceFromImage((string)DATA_DIR + "/createmissions/bg_small_textarea.png"));
	textFood->addFrameBoxOnOver(WorkingSurfaces::GetInstance()->surfaceFromImage((string)DATA_DIR + "/createmissions/bg_small_textarea_on.png"));
	textFood->addFrameBoxActived(WorkingSurfaces::GetInstance()->surfaceFromImage((string)DATA_DIR + "/createmissions/bg_small_textarea_active.png"));
	
	getGroupScene()->addElement((Element*)textFood);
	
	infoImageFood = new Element();	
	infoImageFood->setIndexZ(2);
	infoImageFood->setAlign(ALIGN_CENTER);
	infoImageFood->setVAlign(VALIGN_CENTER);
	infoImageFood->setXY(World::width/2, 170);
	infoImageFood->addFrameSurface(Primitives::GetInstance()->rectangle(1,1,0,0,0));
	
	getGroupScene()->addElement(infoImageFood);
	
	bAccept = new Button();
	bAccept->setIndexZ(1);
	bAccept->setScales(0.4, 0.45);
	bAccept->setAlign(ALIGN_CENTER);
	bAccept->setVAlign(VALIGN_CENTER);
	bAccept->setX(285);
	bAccept->setY(487);
	bAccept->setRGB(0, 255, 0);

	bAccept->OnClick = bAccept_SceneEditGame_OnClick;
	
	sprintf(tmp, Language::GetInstance()->getText("accept").c_str());
	bAccept->imageOut(Fonts::GetInstance()->getSurface_TextBitMap("font-computer", ALIGN_CENTER, tmp));
	bAccept->setAnimation("out");
	
	getGroupScene()->addElement(bAccept);

	bCancel = new Button();
	bCancel->setIndexZ(1);
	bCancel->setScales(0.4, 0.45);
	bCancel->setAlign(ALIGN_CENTER);
	bCancel->setVAlign(VALIGN_CENTER);
	bCancel->setX(505);
	bCancel->setY(487);
	bCancel->setRGB(255, 0, 0);
	
	bCancel->OnClick = bCancel_SceneEditGame_OnClick;
	
	sprintf(tmp, Language::GetInstance()->getText("cancel").c_str());
	bCancel->imageOut(Fonts::GetInstance()->getSurface_TextBitMap("font-computer", ALIGN_CENTER, tmp));
	bCancel->setAnimation("out");
	
	getGroupScene()->addElement(bCancel);
	
	bCleanScenary = new Button();
	bCleanScenary->setScales(1.0, 1.1);
	bCleanScenary->setAlign(ALIGN_CENTER);
	bCleanScenary->setVAlign(VALIGN_CENTER);
	bCleanScenary->setX(400);
	bCleanScenary->setY(200);
	
	bCleanScenary->OnClick = bCleanScenary_SceneEditGame_OnClick;
	
	bCleanScenary->imageOut(WorkingSurfaces::GetInstance()->surfaceFromImage((string)DATA_DIR + "/editgame/" + Language::GetInstance()->getFilename("b_cleanscenary", "png")));
	bCleanScenary->setAnimation("out");
	
	getGroupScene()->addElement(bCleanScenary);
	
	bCleanBoard = new Button();
	bCleanBoard->setScales(1.0, 1.1);
	bCleanBoard->setAlign(ALIGN_CENTER);
	bCleanBoard->setVAlign(VALIGN_CENTER);
	bCleanBoard->setX(400);
	bCleanBoard->setY(280);
	
	bCleanBoard->OnClick = bCleanBoard_SceneEditGame_OnClick;
	
	bCleanBoard->imageOut(WorkingSurfaces::GetInstance()->surfaceFromImage((string)DATA_DIR + "/editgame/" + Language::GetInstance()->getFilename("b_cleanboard", "png")));
	bCleanBoard->setAnimation("out");
	
	getGroupScene()->addElement(bCleanBoard);
	
	bCleanReset = new Button();
	bCleanReset->setScales(1.0, 1.1);
	bCleanReset->setAlign(ALIGN_CENTER);
	bCleanReset->setVAlign(VALIGN_CENTER);
	bCleanReset->setX(400);
	bCleanReset->setY(360);
	
	bCleanReset->OnClick = bCleanReset_SceneEditGame_OnClick;
	
	bCleanReset->imageOut(WorkingSurfaces::GetInstance()->surfaceFromImage((string)DATA_DIR + "/editgame/" + Language::GetInstance()->getFilename("b_cleanreset", "png")));
	bCleanReset->setAnimation("out");
	
	getGroupScene()->addElement(bCleanReset);
	
	/************* 
	  INFO
	*************/
	
	bInfoMain = new Button();
	bInfoMain->setIndexZ(2);
	bInfoMain->setScales(1.0, 1.03);
	bInfoMain->setAlign(ALIGN_CENTER);
	bInfoMain->setVAlign(VALIGN_CENTER);
	bInfoMain->setX(230);
	bInfoMain->setY(78);
	bInfoMain->imageOut(WorkingSurfaces::GetInstance()->surfaceFromImage((string)DATA_DIR + "/editgame/" + Language::GetInstance()->getFilename("b_info_main", "png") ));
	bInfoMain->setAnimation("out");
	bInfoMain->OnClick = bInfoMain_SceneEditGame_OnClick;
	getGroupScene()->addElement(bInfoMain);
	
	bInfoData = new Button();	
	bInfoData->setIndexZ(0);
	bInfoData->setRGB(160, 160, 160);
	bInfoData->setScales(1.0, 1.03);
	bInfoData->setAlign(ALIGN_CENTER);
	bInfoData->setVAlign(VALIGN_CENTER);
	bInfoData->setX(355);
	bInfoData->setY(78);
	bInfoData->imageOut(WorkingSurfaces::GetInstance()->surfaceFromImage((string)DATA_DIR + "/editgame/" + Language::GetInstance()->getFilename("b_info_data", "png") ));
	bInfoData->setAnimation("out");
	bInfoData->OnClick = bInfoData_SceneEditGame_OnClick;
	getGroupScene()->addElement(bInfoData);
	
	bInfoMusic = new Button();	
	bInfoMusic->setIndexZ(0);
	bInfoMusic->setRGB(160, 160, 160);
	bInfoMusic->setScales(1.0, 1.03);
	bInfoMusic->setAlign(ALIGN_CENTER);
	bInfoMusic->setVAlign(VALIGN_CENTER);
	bInfoMusic->setX(480);
	bInfoMusic->setY(78);
	bInfoMusic->imageOut(WorkingSurfaces::GetInstance()->surfaceFromImage((string)DATA_DIR + "/editgame/" + Language::GetInstance()->getFilename("b_info_music", "png") ));
	bInfoMusic->setAnimation("out");
	bInfoMusic->OnClick = bInfoMusic_SceneEditGame_OnClick;
	getGroupScene()->addElement(bInfoMusic);
	
	missionName = new Entry(NULL, 450, 25, 10, 10);
	missionName->setNoSigns(true);
	missionName->setIndexZ(1);
	missionName->setMaxLetters(35);
	missionName->setFontLabel("font-texts");
	missionName->setFont("font-computer");
	missionName->setLabel(Language::GetInstance()->getText("namemission"));
	missionName->setHorizontal(false);
	missionName->setX(World::width/2);
	missionName->setY(150);
	missionName->addFrameBoxNormal(WorkingSurfaces::GetInstance()->surfaceFromImage((string)DATA_DIR + "/createmissions/bg_textbox.png"));
	missionName->addFrameBoxOnOver(WorkingSurfaces::GetInstance()->surfaceFromImage((string)DATA_DIR + "/createmissions/bg_textbox_on.png"));
	missionName->addFrameBoxActived(WorkingSurfaces::GetInstance()->surfaceFromImage((string)DATA_DIR + "/createmissions/bg_textbox_active.png"));
	
	getGroupScene()->addElement((Element*)missionName);
	
	nameAuthor = new Entry(missionName, 450, 25, 10, 10);
	nameAuthor->setNoSigns(true);
	nameAuthor->setIndexZ(1);
	nameAuthor->setMaxLetters(35);
	nameAuthor->setFontLabel("font-texts");
	nameAuthor->setFont("font-computer");
	nameAuthor->setLabel(Language::GetInstance()->getText("nameauthor"));
	nameAuthor->setHorizontal(false);
	nameAuthor->setX(World::width/2);
	nameAuthor->setY(225);
	nameAuthor->addFrameBoxNormal(WorkingSurfaces::GetInstance()->surfaceFromImage((string)DATA_DIR + "/createmissions/bg_textbox.png"));
	nameAuthor->addFrameBoxOnOver(WorkingSurfaces::GetInstance()->surfaceFromImage((string)DATA_DIR + "/createmissions/bg_textbox_on.png"));
	nameAuthor->addFrameBoxActived(WorkingSurfaces::GetInstance()->surfaceFromImage((string)DATA_DIR + "/createmissions/bg_textbox_active.png"));
	
	getGroupScene()->addElement((Element*)nameAuthor);
			
	levelName = new Entry(missionName, 450, 25, 10, 10);
	levelName->setNoSigns(true);
	levelName->setIndexZ(1);
	levelName->setMaxLetters(35);
	levelName->setFontLabel("font-texts");
	levelName->setFont("font-computer");
	levelName->setLabel(Language::GetInstance()->getText("namelevel"));
	levelName->setHorizontal(false);
	levelName->setX(World::width/2);
	levelName->setY(300);
	levelName->addFrameBoxNormal(WorkingSurfaces::GetInstance()->surfaceFromImage((string)DATA_DIR + "/createmissions/bg_textbox.png"));
	levelName->addFrameBoxOnOver(WorkingSurfaces::GetInstance()->surfaceFromImage((string)DATA_DIR + "/createmissions/bg_textbox_on.png"));
	levelName->addFrameBoxActived(WorkingSurfaces::GetInstance()->surfaceFromImage((string)DATA_DIR + "/createmissions/bg_textbox_active.png"));
	
	getGroupScene()->addElement((Element*)levelName);
		
	provinceName = new Entry(missionName, 450, 25, 10, 10);
	provinceName->setNoSigns(true);
	provinceName->setIndexZ(1);
	provinceName->setMaxLetters(35);
	provinceName->setFontLabel("font-texts");
	provinceName->setFont("font-computer");
	provinceName->setLabel(Language::GetInstance()->getText("nameprovince"));
	provinceName->setHorizontal(false);
	provinceName->setX(World::width/2);
	provinceName->setY(375);
	provinceName->addFrameBoxNormal(WorkingSurfaces::GetInstance()->surfaceFromImage((string)DATA_DIR + "/createmissions/bg_textbox.png"));
	provinceName->addFrameBoxOnOver(WorkingSurfaces::GetInstance()->surfaceFromImage((string)DATA_DIR + "/createmissions/bg_textbox_on.png"));
	provinceName->addFrameBoxActived(WorkingSurfaces::GetInstance()->surfaceFromImage((string)DATA_DIR + "/createmissions/bg_textbox_active.png"));
	
	getGroupScene()->addElement((Element*)provinceName);
	
	/*********************
	  INFORMATION TOWN
	**********************/
	
	noExistInfoTown = new Element();
	noExistInfoTown->setCurrentScale(1.2);
	noExistInfoTown->setAlign(ALIGN_CENTER);
	noExistInfoTown->setVAlign(VALIGN_CENTER);
	noExistInfoTown->setIndexZ(2);
	noExistInfoTown->setXY(400, 230);
	noExistInfoTown->addFrameText("font-texts", Language::GetInstance()->getText("noexistinfotown"), ALIGN_CENTER);
	getGroupScene()->addElement(noExistInfoTown);
	
	dataInfo = new ListView();
	dataInfo->setIndexZ(2);
	dataInfo->setTodoMovement(false);
	dataInfo->setXY(160, 150);
	dataInfo->setItemsVisible(4);
	dataInfo->setSeparateGrid(60);
	
	bAddInfo = new Button();	
	bAddInfo->setIndexZ(1);
	bAddInfo->setScales(1.0, 1.03);
	bAddInfo->setAlign(ALIGN_CENTER);
	bAddInfo->setVAlign(VALIGN_CENTER);
	bAddInfo->setXY(400, 420);
	bAddInfo->setRGB(0, 255, 0);
	bAddInfo->imageOut(WorkingSurfaces::GetInstance()->surfaceFromImage((string)DATA_DIR + "/editgame/" + Language::GetInstance()->getFilename("b_addinfo", "png")));
	bAddInfo->OnClick = bAddInfo_SceneEditGame_OnClick;
		
	typeButtonInfoTown = new SelectButton();
	typeButtonInfoTown->setIndexZ(1);
	typeButtonInfoTown->setX(320);
	typeButtonInfoTown->setY(130);
	
	for (i=0; i<8; i++) {
		sprintf(tmp, "%s/town_info/button%d_off.png", DATA_DIR, i);
		typeButtonInfoTown->addObject(WorkingSurfaces::GetInstance()->surfaceFromImage(tmp));
	}
	
	typeButtonInfoTown->setArrows(WorkingSurfaces::GetInstance()->surfaceFromImage((string)DATA_DIR+"/windows/arrow_left.png"), WorkingSurfaces::GetInstance()->surfaceFromImage((string)DATA_DIR+"/windows/arrow_right.png"));
		
	eTitleInfoTown = new Entry(NULL, 450, 25, 10, 10);
	eTitleInfoTown->setNoSigns(true);
	eTitleInfoTown->setMaxLetters(14);
	eTitleInfoTown->setIndexZ(1);
	eTitleInfoTown->setFontLabel("font-texts");
	eTitleInfoTown->setFont("font-texts");
	eTitleInfoTown->setLabel(Language::GetInstance()->getText("title"));
	eTitleInfoTown->setHorizontal(false);
	eTitleInfoTown->setX(World::width/2);
	eTitleInfoTown->setY(190);
	eTitleInfoTown->addFrameBoxNormal(WorkingSurfaces::GetInstance()->surfaceFromImage((string)DATA_DIR + "/createmissions/bg_textbox.png"));
	eTitleInfoTown->addFrameBoxOnOver(WorkingSurfaces::GetInstance()->surfaceFromImage((string)DATA_DIR + "/createmissions/bg_textbox_on.png"));
	eTitleInfoTown->addFrameBoxActived(WorkingSurfaces::GetInstance()->surfaceFromImage((string)DATA_DIR + "/createmissions/bg_textbox_active.png"));
		
	getGroupScene()->addElement((Element*)eTitleInfoTown);
		
	taInfoTown = new Entry(eTitleInfoTown, 440, 25, 10, 10);
	taInfoTown->setMultiline(true);
	taInfoTown->setTotalRows(6);
	taInfoTown->setIndexZ(1);
	taInfoTown->setFontLabel("font-texts");
	taInfoTown->setFont("font-texts");
	taInfoTown->setLabel(Language::GetInstance()->getText("text"));
	taInfoTown->setHorizontal(false);
	taInfoTown->setX(World::width/2);
	taInfoTown->setY(265);
	taInfoTown->addFrameBoxNormal(WorkingSurfaces::GetInstance()->surfaceFromImage((string)DATA_DIR + "/createmissions/bg_middle_textarea.png"));
	taInfoTown->addFrameBoxOnOver(WorkingSurfaces::GetInstance()->surfaceFromImage((string)DATA_DIR + "/createmissions/bg_middle_textarea_on.png"));
	taInfoTown->addFrameBoxActived(WorkingSurfaces::GetInstance()->surfaceFromImage((string)DATA_DIR + "/createmissions/bg_middle_textarea_active.png"));
		
	getGroupScene()->addElement((Element*)taInfoTown);
	
	eTitleInfoTown->setActive(true);
	
	/************* 
	  RAD MUSIC
	*************/
	
	radMusic0 = new RadioButton(NULL, "font-texts", "Blah, blah, blah (Reggae)");	
	radMusic0->setIndexZ(1);
	radMusic0->setX(200);
	radMusic0->setY(170);
	
	radMusic0->imageInactive( WorkingSurfaces::GetInstance()->surfaceFromImage((string)DATA_DIR + "/interface/rad_off.png") );
	radMusic0->imageActive( WorkingSurfaces::GetInstance()->surfaceFromImage((string)DATA_DIR + "/interface/rad2_on.png") );
	
	getGroupScene()->addGroup(radMusic0);
	
	radMusic1 = new RadioButton(radMusic0, "font-texts", "Babosa cantarina (Alegre)");	
	radMusic1->setIndexZ(1);
	radMusic1->setX(200);
	radMusic1->setY(220);
	
	radMusic1->imageInactive( WorkingSurfaces::GetInstance()->surfaceFromImage((string)DATA_DIR + "/interface/rad_off.png") );
	radMusic1->imageActive( WorkingSurfaces::GetInstance()->surfaceFromImage((string)DATA_DIR + "/interface/rad2_on.png") );
	
	getGroupScene()->addGroup(radMusic1);
	
	radMusic2 = new RadioButton(radMusic0, "font-texts", "El tango de la pena (Tango)");	
	radMusic2->setIndexZ(1);
	radMusic2->setX(200);
	radMusic2->setY(270);
	
	radMusic2->imageInactive( WorkingSurfaces::GetInstance()->surfaceFromImage((string)DATA_DIR + "/interface/rad_off.png") );
	radMusic2->imageActive( WorkingSurfaces::GetInstance()->surfaceFromImage((string)DATA_DIR + "/interface/rad2_on.png") );
	
	getGroupScene()->addGroup(radMusic2);
	
	radMusic3 = new RadioButton(radMusic0, "font-texts", "Rumbum (Rumba-Jazz)");	
	radMusic3->setIndexZ(1);
	radMusic3->setX(200);
	radMusic3->setY(320);
	
	radMusic3->imageInactive( WorkingSurfaces::GetInstance()->surfaceFromImage((string)DATA_DIR + "/interface/rad_off.png") );
	radMusic3->imageActive( WorkingSurfaces::GetInstance()->surfaceFromImage((string)DATA_DIR + "/interface/rad2_on.png") );
	
	getGroupScene()->addGroup(radMusic3);
	
	radMusic0->setActive(true);
		
	/************* 
	  HAND TRAY
	*************/
	
	handTray = new Group();
	handTray->setX(0);
	handTray->setY(450);
	
	bgHandTray = new Element();	
	bgHandTray->addFrameFileFromData("/editgame/handtray.png");
	
	handTray->addElement(bgHandTray);
	
	getGroupScene()->addGroup(handTray);
	
	btHandTray = new Button();	
	btHandTray->setAlign(ALIGN_CENTER);
	btHandTray->setVAlign(VALIGN_CENTER);
	btHandTray->setXY(76, 55);
	btHandTray->imageOut(WorkingSurfaces::GetInstance()->surfaceFromImage((string)DATA_DIR + "/editgame/edit_eat.png"));
	btHandTray->setSensitive(false);
	btHandTray->OnClick = btHandTray_SceneEditGame_OnClick;
	
	handTray->addElement(btHandTray);
	
	/************* 
		MENU
	*************/
	
	menuBg = new Element();	
	menuBg->setVAlign(VALIGN_BOTTOM);
	menuBg->setX(0);
	menuBg->setY(World::height);
	menuBg->addFrameFileFromData("/editgame/menu_bg.png");
	getGroupScene()->addElement(menuBg);
	
	menu = new Group();
	menu->setX(239);
	menu->setY(540);
	
	menuTown = new MarqueeElement();
	menuTown->setCurrentScale(0.34);
	menuTown->setAlign(ALIGN_CENTER);
	menuTown->setVAlign(VALIGN_CENTER);
	menuTown->setX(168);
	menuTown->setY(45);
	menuTown->setRGB(234, 238, 53);
	
	menu->addElement(menuTown);
	getGroupScene()->addElement(menuTown);
	
	menuText = new Element();	
	menuText->setAlign(ALIGN_CENTER);
	menuText->setVAlign(VALIGN_CENTER);
	menuText->setX(168);
	menuText->setY(45);
	menuText->setCurrentScale(0.34);
	menuText->hide();
	
	menuText->addFrameText("font-computer", Language::GetInstance()->getText("menuedit"), ALIGN_CENTER);
	menuText->addFrameText("font-computer", Language::GetInstance()->getText("menusave"), ALIGN_CENTER);
	menuText->addFrameText("font-computer", Language::GetInstance()->getText("menuguides"), ALIGN_CENTER);
	menuText->addFrameText("font-computer", Language::GetInstance()->getText("exit"), ALIGN_CENTER);
	menuText->addFrameText("font-computer", Language::GetInstance()->getText("menuaddobject"), ALIGN_CENTER);
	menuText->addFrameText("font-computer", Language::GetInstance()->getText("menupersonage"), ALIGN_CENTER);
	menuText->addFrameText("font-computer", Language::GetInstance()->getText("menuobject"), ALIGN_CENTER);
	menuText->addFrameText("font-computer", Language::GetInstance()->getText("menueat"), ALIGN_CENTER);
	menuText->addFrameText("font-computer", Language::GetInstance()->getText("menuclean"), ALIGN_CENTER);
	menuText->addFrameText("font-computer", Language::GetInstance()->getText("menuhelp"), ALIGN_CENTER);
	menuText->addFrameText("font-computer", Language::GetInstance()->getText("menuselecttypeboard"), ALIGN_CENTER);
	menuText->addFrameText("font-computer", Language::GetInstance()->getText("menuselecttypefloor"), ALIGN_CENTER);
	menuText->addFrameText("font-computer", Language::GetInstance()->getText("menuselecttypewall"), ALIGN_CENTER);
	menuText->addFrameText("font-computer", Language::GetInstance()->getText("menuselecttypepavement"), ALIGN_CENTER);
	menuText->addFrameText("font-computer", Language::GetInstance()->getText("menuselecttypetiled"), ALIGN_CENTER);
	menuText->addFrameText("font-computer", Language::GetInstance()->getText("menuselectntilesclosed"), ALIGN_CENTER);
	menuText->addFrameText("font-computer", Language::GetInstance()->getText("menuselectcolorwall"), ALIGN_CENTER);
	menuText->addFrameText("font-computer", Language::GetInstance()->getText("menuselecttypeterrain"), ALIGN_CENTER);
	menuText->addFrameText("font-computer", Language::GetInstance()->getText("menuselecttypewallscenary"), ALIGN_CENTER);
	
	menu->addElement(menuText);
	getGroupScene()->addElement(menuText);
	
	setTextDisplay(-1);
		
	bEditInfo = new Button();
	bEditInfo->setSoundOn("click0");
	bEditInfo->setScales(1.0, 1.05);
	bEditInfo->setAlign(ALIGN_CENTER);
	bEditInfo->setVAlign(VALIGN_CENTER);
	bEditInfo->setX(80);
	bEditInfo->setY(10);
	bEditInfo->imageOut(WorkingSurfaces::GetInstance()->surfaceFromImage((string)DATA_DIR + "/editgame/menuitem_editinfo.png"));
	bEditInfo->setAnimation("out");
	bEditInfo->OnClick = bEditInfo_SceneEditGame_OnClick;
	menu->addElement(bEditInfo);
	getGroupScene()->addElement(bEditInfo);
		
	bSave = new Button();
	bSave->setSoundOn("click0");
	bSave->setScales(1.0, 1.05);
	bSave->setAlign(ALIGN_CENTER);
	bSave->setVAlign(VALIGN_CENTER);
	bSave->setX(115);
	bSave->setY(10);
	bSave->imageOut(WorkingSurfaces::GetInstance()->surfaceFromImage((string)DATA_DIR + "/editgame/menuitem_save.png"));
	bSave->setAnimation("out");
	bSave->OnClick = bSave_SceneEditGame_OnClick;
	menu->addElement(bSave);
	getGroupScene()->addElement(bSave);
		
	bRules = new Button();
	bRules->setSoundOn("click0");
	bRules->setScales(1.0, 1.05);
	bRules->setAlign(ALIGN_CENTER);
	bRules->setVAlign(VALIGN_CENTER);
	bRules->setX(150);
	bRules->setY(10);
	bRules->imageOut(WorkingSurfaces::GetInstance()->surfaceFromImage((string)DATA_DIR + "/editgame/menuitem_rules.png"));
	bRules->setAnimation("out");
	bRules->OnClick = bRules_SceneEditGame_OnClick;
	menu->addElement(bRules);
	getGroupScene()->addElement(bRules);
	
	bClean = new Button();
	bClean->setSoundOn("click0");
	bClean->setScales(1.0, 1.05);
	bClean->setAlign(ALIGN_CENTER);
	bClean->setVAlign(VALIGN_CENTER);
	bClean->setX(185);
	bClean->setY(10);
	bClean->imageOut(WorkingSurfaces::GetInstance()->surfaceFromImage((string)DATA_DIR + "/editgame/menuitem_clean.png"));
	bClean->setAnimation("out");
	bClean->OnClick = bClean_SceneEditGame_OnClick;
	menu->addElement(bClean);
	getGroupScene()->addElement(bClean);
	
	bHelp = new Button();
	bHelp->setSoundOn("click0");
	bHelp->setScales(1.0, 1.05);
	bHelp->setAlign(ALIGN_CENTER);
	bHelp->setVAlign(VALIGN_CENTER);
	bHelp->setX(220);
	bHelp->setY(10);
	bHelp->imageOut(WorkingSurfaces::GetInstance()->surfaceFromImage((string)DATA_DIR + "/editgame/menuitem_help.png"));
	bHelp->setAnimation("out");
	bHelp->OnClick = bHelp_SceneEditGame_OnClick;
	menu->addElement(bHelp);
	getGroupScene()->addElement(bHelp);
	
	bQuit = new Button();	
	bQuit->setSoundOn("click0");
	bQuit->setScales(1.0, 1.05);
	bQuit->setAlign(ALIGN_CENTER);
	bQuit->setVAlign(VALIGN_CENTER);
	bQuit->setX(255);
	bQuit->setY(10);
	bQuit->imageOut(WorkingSurfaces::GetInstance()->surfaceFromImage((string)DATA_DIR + "/editgame/menuitem_quit.png"));
	bQuit->setAnimation("out");
	bQuit->OnClick = bQuit_SceneEditGame_OnClick;
	menu->addElement(bQuit);
	getGroupScene()->addElement(bQuit);
	
	pb->setText("font-texts", Language::GetInstance()->getText("loading_level"));
	pb->draw();
	
	EditBoard::GetInstance()->setSceneEditGame(this);
	EditBoard::GetInstance()->load();
	EditBoard::GetInstance()->loadLevel();
	
	if (EditBoard::GetInstance()->getScenary()->getType()==SCENARY_CLOSED) {
		typeTiled->setY(435);
		nTilesClosed->setY(465);
		colorWall->setY(495);
	} else {
		typeTiled->setY(440);
		nTilesClosed->setY(480);
	}
	
	getGroupScene()->addGroup(EditBoard::GetInstance());
	
	menuTown->setText("font-computer", WorkingData::GetInstance()->getToUpper(EditBoard::GetInstance()->town.name), 17);
	
	// group of the objects in sceneaddobject
	
	blueLine = new Element();
	blueLine->setIndexZ(1);
	blueLine->setXY(70, 70);
	blueLine->addFrameSurface(Primitives::GetInstance()->rectangle(660, 490, 62, 98, 140));
	getGroupScene()->addElement(blueLine);
	
	infoObjectsPersonal = new Element();
	infoObjectsPersonal->setAlign(ALIGN_CENTER);
	infoObjectsPersonal->setVAlign(VALIGN_BOTTOM);
	infoObjectsPersonal->setIndexZ(2);
	infoObjectsPersonal->setRGB(190, 195, 53);
	infoObjectsPersonal->setCurrentScale(0.9);
	infoObjectsPersonal->setXY(400, 550);
	string text = Language::GetInstance()->getText("personalfile") + "|" + Missions::GetInstance()->currentLevel->getPath() + "/objects";
	infoObjectsPersonal->addFrameText("font-texts", text, ALIGN_CENTER);
	getGroupScene()->addElement(infoObjectsPersonal);
	
	bgArrow = new Element();
	bgArrow->setIndexZ(0);
	bgArrow->setXY(700, 100);
	bgArrow->addFrameFileFromData("/editgame/bg_arrow.png");
	getGroupScene()->addElement(bgArrow);
	
	bgButton = new Element();
	bgButton->setIndexZ(1);
	bgButton->setAlign(ALIGN_CENTER);
	bgButton->setVAlign(VALIGN_CENTER);
	bgButton->setXY(400, 577);
	bgButton->addFrameFileFromData("/editgame/bluebox.png");
	getGroupScene()->addElement(bgButton);
	
	bCancelObjects = new Button();
	bCancelObjects->setIndexZ(2);
	bCancelObjects->setScales(0.4, 0.45);
	bCancelObjects->setAlign(ALIGN_CENTER);
	bCancelObjects->setVAlign(VALIGN_CENTER);
	bCancelObjects->setX(405);
	bCancelObjects->setY(574);
	bCancelObjects->setRGB(255, 0, 0);
	
	bCancelObjects->OnClick = bCancel_SceneEditGame_OnClick;
	
	sprintf(tmp, Language::GetInstance()->getText("cancel").c_str());
	bCancelObjects->imageOut(Fonts::GetInstance()->getSurface_TextBitMap("font-computer", ALIGN_CENTER, tmp));
	bCancelObjects->setAnimation("out");
	
	getGroupScene()->addElement(bCancelObjects);
	
	bObjectsGame = new Button();
	bObjectsGame->setIndexZ(2);
	bObjectsGame->setScales(1.0, 1.03);
	bObjectsGame->setAlign(ALIGN_CENTER);
	bObjectsGame->setVAlign(VALIGN_CENTER);
	bObjectsGame->setX(175);
	bObjectsGame->setY(53);
	bObjectsGame->imageOut(WorkingSurfaces::GetInstance()->surfaceFromImage((string)DATA_DIR + "/editgame/" + Language::GetInstance()->getFilename("b_objects_game", "png") ));
	bObjectsGame->setAnimation("out");
	bObjectsGame->OnClick = bObjectsGame_SceneEditGame_OnClick;
	getGroupScene()->addElement(bObjectsGame);
	
	bObjectsPersonal = new Button();	
	bObjectsPersonal->setIndexZ(0);
	bObjectsPersonal->setRGB(160, 160, 160);
	bObjectsPersonal->setScales(1.0, 1.03);
	bObjectsPersonal->setAlign(ALIGN_CENTER);
	bObjectsPersonal->setVAlign(VALIGN_CENTER);
	bObjectsPersonal->setX(360);
	bObjectsPersonal->setY(53);
	bObjectsPersonal->imageOut(WorkingSurfaces::GetInstance()->surfaceFromImage((string)DATA_DIR + "/editgame/" + Language::GetInstance()->getFilename("b_objects_personal", "png") ));
	bObjectsPersonal->setAnimation("out");
	bObjectsPersonal->OnClick = bObjectsPersonal_SceneEditGame_OnClick;
	getGroupScene()->addElement(bObjectsPersonal);
	
	bObjectsTexts = new Button();	
	bObjectsTexts->setIndexZ(0);
	bObjectsTexts->setRGB(160, 160, 160);
	bObjectsTexts->setScales(1.0, 1.03);
	bObjectsTexts->setAlign(ALIGN_CENTER);
	bObjectsTexts->setVAlign(VALIGN_CENTER);
	bObjectsTexts->setX(545);
	bObjectsTexts->setY(53);
	bObjectsTexts->imageOut(WorkingSurfaces::GetInstance()->surfaceFromImage((string)DATA_DIR + "/editgame/" + Language::GetInstance()->getFilename("b_objects_text", "png") ));
	bObjectsTexts->setAnimation("out");
	bObjectsTexts->OnClick = bObjectsTexts_SceneEditGame_OnClick;
	getGroupScene()->addElement(bObjectsTexts);
	
	objectsGame = new ListImage(4, 6);
	objectsGame->setIndexZ(1);
	objectsGame->setSeparateGrid(110);
	objectsGame->setX(70);
	objectsGame->setY(120);
	
	if (EditBoard::GetInstance()->getScenary()->getType()==SCENARY_CLOSED) {
        objectsGame->addCategory("windows");
        objectsGame->addCategory("doors");
        objectsGame->addCategory("lights");
        objectsGame->addCategory("elements");
        objectsGame->addCategory("decorative");
    } else {
        objectsGame->addCategory("nature");
        objectsGame->addCategory("beach");
        objectsGame->addCategory("benchs");
        objectsGame->addCategory("construction");
        objectsGame->addCategory("elements");
    }
	
	TypeObjectsScenary::GetInstance()->MoveFirst();
	for (i=0; !TypeObjectsScenary::GetInstance()->isEOF(); i++) {
		if (EditBoard::GetInstance()->getScenary()->getType()==TypeObjectsScenary::GetInstance()->getObject()->type) {
			Button *b = new Button();
			b->setScales(1.0, 1.05);
			sprintf(tmp, "%s/scenary/min_%s", DATA_DIR, TypeObjectsScenary::GetInstance()->getObject()->file.c_str());
			b->imageOut(WorkingSurfaces::GetInstance()->surfaceFromImage(tmp));
			b->setAnimation("out");
			b->addParameter("name", TypeObjectsScenary::GetInstance()->getObject()->name);
			b->addParameter("category", TypeObjectsScenary::GetInstance()->getObject()->category);
			b->OnClick = insertObjectsGame_SceneEditGame_OnClick;
			objectsGame->add(b);
		}
		TypeObjectsScenary::GetInstance()->MoveNext();
	}
    
	Element *boxObjects = new Element();
	boxObjects->addFrameFileFromData("/editgame/box_object.png");
	
	//gObjects->addElement(boxObjects);
	
	Button* bUpObjects = new Button();
	bUpObjects->setSoundClick("beep1");
	bUpObjects->setScales(1.0, 1.05);
	bUpObjects->setAlign(ALIGN_CENTER);
	bUpObjects->setVAlign(VALIGN_CENTER);
	
	bUpObjects->imageOut(WorkingSurfaces::GetInstance()->surfaceFromImage((string)DATA_DIR + "/interface/arrow_up.png"));
	
	bUpObjects->imageOff(WorkingSurfaces::GetInstance()->surfaceFromImage((string)DATA_DIR + "/interface/arrow_up_off.png"));
	bUpObjects->setAnimation("out");
	
	getGroupScene()->addElement((Element*)bUpObjects);
	
	bUpObjects->setSensitive(false);
    
    Button* bDownObjects = new Button();
	bDownObjects->setSoundClick("beep1");
    bDownObjects->setScales(1.0, 1.05);
	bDownObjects->setFlop(true);
	bDownObjects->setAlign(ALIGN_CENTER);
	bDownObjects->setVAlign(VALIGN_CENTER);
	
	bDownObjects->imageOut(WorkingSurfaces::GetInstance()->surfaceFromImage((string)DATA_DIR + "/interface/arrow_up.png"));
	
	bDownObjects->imageOff(WorkingSurfaces::GetInstance()->surfaceFromImage((string)DATA_DIR + "/interface/arrow_up_off.png"));
	bDownObjects->setAnimation("out");
	
	getGroupScene()->addElement((Element*)bDownObjects);
	
	bDownObjects->setSensitive(false);
	
	objectsGame->setButtons(bUpObjects, bDownObjects, 678, 42);
	objectsGame->setBoxImage(boxObjects);
	
	if (EditBoard::GetInstance()->getScenary()->getType()==SCENARY_CLOSED) {
         objectsGame->setCategory("windows");
    } else {
         objectsGame->setCategory("nature");
    }
	
	// personal objects
	
	objectsPersonal = new ListImage(3, 6);
	objectsPersonal->setIndexZ(1);
	objectsPersonal->setSeparateGrid(110);
	objectsPersonal->setX(70);
	objectsPersonal->setY(160);
	
	loadObjectsPersonal ();
	
	Button* bUpObjectsPersonal = new Button();
	bUpObjectsPersonal->setSoundClick("beep1");
	bUpObjectsPersonal->setScales(1.0, 1.05);
	bUpObjectsPersonal->setAlign(ALIGN_CENTER);
	bUpObjectsPersonal->setVAlign(VALIGN_CENTER);
	
	bUpObjectsPersonal->imageOut(WorkingSurfaces::GetInstance()->surfaceFromImage((string)DATA_DIR + "/interface/arrow_up.png"));
	
	bUpObjectsPersonal->imageOff(WorkingSurfaces::GetInstance()->surfaceFromImage((string)DATA_DIR + "/interface/arrow_up_off.png"));
	bUpObjectsPersonal->setAnimation("out");
	
	getGroupScene()->addElement((Element*)bUpObjectsPersonal);
	
	bUpObjectsPersonal->setSensitive(false);
    
    Button* bDownObjectsPersonal = new Button();
	bDownObjectsPersonal->setSoundClick("beep1");
    bDownObjectsPersonal->setScales(1.0, 1.05);
	bDownObjectsPersonal->setFlop(true);
	bDownObjectsPersonal->setAlign(ALIGN_CENTER);
	bDownObjectsPersonal->setVAlign(VALIGN_CENTER);
	
	bDownObjectsPersonal->imageOut(WorkingSurfaces::GetInstance()->surfaceFromImage((string)DATA_DIR + "/interface/arrow_up.png"));
	
	bDownObjectsPersonal->imageOff(WorkingSurfaces::GetInstance()->surfaceFromImage((string)DATA_DIR + "/interface/arrow_up_off.png"));
	bDownObjectsPersonal->setAnimation("out");
	
	getGroupScene()->addElement((Element*)bDownObjectsPersonal);
	
	bDownObjectsPersonal->setSensitive(false);
	
	objectsPersonal->setButtons(bUpObjectsPersonal, bDownObjectsPersonal, 678, 42);
	
	Element *boxObjectsPersonal = new Element();
	boxObjectsPersonal->addFrameFileFromData("/editgame/box_object.png");
	
	objectsPersonal->setBoxImage(boxObjectsPersonal);
	
	objectsPersonal->verifyObjectsToShow();
	
	// categories radios
	
	rbTypeClosedWindows = new RadioButton(NULL, "font-texts", Language::GetInstance()->getText("windows"));
	rbTypeClosedWindows->setIndexZ(1);
	rbTypeClosedWindows->setX(80);
	rbTypeClosedWindows->setY(80);
	
	rbTypeClosedWindows->imageActive(WorkingSurfaces::GetInstance()->surfaceFromImage((string)DATA_DIR + "/interface/radblue_on.png"));
	rbTypeClosedWindows->imageInactive(WorkingSurfaces::GetInstance()->surfaceFromImage((string)DATA_DIR + "/interface/radblue_off.png"));
	
	getGroupScene()->addGroup(rbTypeClosedWindows);
	
	rbTypeClosedDoors = new RadioButton(rbTypeClosedWindows, "font-texts", Language::GetInstance()->getText("doors"));
	rbTypeClosedDoors->setIndexZ(1);
	rbTypeClosedDoors->setX(205);
	rbTypeClosedDoors->setY(80);
	
	rbTypeClosedDoors->imageActive(WorkingSurfaces::GetInstance()->surfaceFromImage((string)DATA_DIR + "/interface/radblue_on.png"));
	rbTypeClosedDoors->imageInactive(WorkingSurfaces::GetInstance()->surfaceFromImage((string)DATA_DIR + "/interface/radblue_off.png"));
	
	getGroupScene()->addGroup(rbTypeClosedDoors);
	
	rbTypeClosedLights = new RadioButton(rbTypeClosedWindows, "font-texts", Language::GetInstance()->getText("lights"));
	rbTypeClosedLights->setIndexZ(1);
	rbTypeClosedLights->setX(330);
	rbTypeClosedLights->setY(80);
	
	rbTypeClosedLights->imageActive(WorkingSurfaces::GetInstance()->surfaceFromImage((string)DATA_DIR + "/interface/radblue_on.png"));
	rbTypeClosedLights->imageInactive(WorkingSurfaces::GetInstance()->surfaceFromImage((string)DATA_DIR + "/interface/radblue_off.png"));
	
	getGroupScene()->addGroup(rbTypeClosedLights);
	
	rbTypeClosedElements = new RadioButton(rbTypeClosedWindows, "font-texts", Language::GetInstance()->getText("elements"));
	rbTypeClosedElements->setIndexZ(1);
	rbTypeClosedElements->setX(440);
	rbTypeClosedElements->setY(80);
	
	rbTypeClosedElements->imageActive(WorkingSurfaces::GetInstance()->surfaceFromImage((string)DATA_DIR + "/interface/radblue_on.png"));
	rbTypeClosedElements->imageInactive(WorkingSurfaces::GetInstance()->surfaceFromImage((string)DATA_DIR + "/interface/radblue_off.png"));
	
	getGroupScene()->addGroup(rbTypeClosedElements);
	
	rbTypeClosedDecorative = new RadioButton(rbTypeClosedWindows, "font-texts", Language::GetInstance()->getText("decorative"));
	rbTypeClosedDecorative->setIndexZ(1);
	rbTypeClosedDecorative->setX(580);
	rbTypeClosedDecorative->setY(80);
	
	rbTypeClosedDecorative->imageActive(WorkingSurfaces::GetInstance()->surfaceFromImage((string)DATA_DIR + "/interface/radblue_on.png"));
	rbTypeClosedDecorative->imageInactive(WorkingSurfaces::GetInstance()->surfaceFromImage((string)DATA_DIR + "/interface/radblue_off.png"));
	
	getGroupScene()->addGroup(rbTypeClosedDecorative);
	
	rbTypeClosedWindows->setActive(true);
	
	rbTypeOpenedNature = new RadioButton(NULL, "font-texts", Language::GetInstance()->getText("nature"));
	rbTypeOpenedNature->setIndexZ(1);
	rbTypeOpenedNature->setX(80);
	rbTypeOpenedNature->setY(80);
	
	rbTypeOpenedNature->imageActive(WorkingSurfaces::GetInstance()->surfaceFromImage((string)DATA_DIR + "/interface/radblue_on.png"));
	rbTypeOpenedNature->imageInactive(WorkingSurfaces::GetInstance()->surfaceFromImage((string)DATA_DIR + "/interface/radblue_off.png"));
	
	getGroupScene()->addGroup(rbTypeOpenedNature);
	
	rbTypeOpenedBeach = new RadioButton(rbTypeOpenedNature, "font-texts", Language::GetInstance()->getText("beach"));
	rbTypeOpenedBeach->setIndexZ(1);
	rbTypeOpenedBeach->setX(215);
	rbTypeOpenedBeach->setY(80);
	
	rbTypeOpenedBeach->imageActive(WorkingSurfaces::GetInstance()->surfaceFromImage((string)DATA_DIR + "/interface/radblue_on.png"));
	rbTypeOpenedBeach->imageInactive(WorkingSurfaces::GetInstance()->surfaceFromImage((string)DATA_DIR + "/interface/radblue_off.png"));
	
	getGroupScene()->addGroup(rbTypeOpenedBeach);
	
	rbTypeOpenedBench = new RadioButton(rbTypeOpenedNature, "font-texts", Language::GetInstance()->getText("benchs"));
	rbTypeOpenedBench->setIndexZ(1);
	rbTypeOpenedBench->setX(320);
	rbTypeOpenedBench->setY(80);
	
	rbTypeOpenedBench->imageActive(WorkingSurfaces::GetInstance()->surfaceFromImage((string)DATA_DIR + "/interface/radblue_on.png"));
	rbTypeOpenedBench->imageInactive(WorkingSurfaces::GetInstance()->surfaceFromImage((string)DATA_DIR + "/interface/radblue_off.png"));
	
	getGroupScene()->addGroup(rbTypeOpenedBench);
	
	rbTypeOpenedConstruction = new RadioButton(rbTypeOpenedNature, "font-texts", Language::GetInstance()->getText("construction"));
	rbTypeOpenedConstruction->setIndexZ(1);
	rbTypeOpenedConstruction->setX(430);
	rbTypeOpenedConstruction->setY(80);
	
	rbTypeOpenedConstruction->imageActive(WorkingSurfaces::GetInstance()->surfaceFromImage((string)DATA_DIR + "/interface/radblue_on.png"));
	rbTypeOpenedConstruction->imageInactive(WorkingSurfaces::GetInstance()->surfaceFromImage((string)DATA_DIR + "/interface/radblue_off.png"));
	
	getGroupScene()->addGroup(rbTypeOpenedConstruction);
	
	rbTypeOpenedElements = new RadioButton(rbTypeOpenedNature, "font-texts", Language::GetInstance()->getText("elements"));
	rbTypeOpenedElements->setIndexZ(1);
	rbTypeOpenedElements->setX(580);
	rbTypeOpenedElements->setY(80);
	
	rbTypeOpenedElements->imageActive(WorkingSurfaces::GetInstance()->surfaceFromImage((string)DATA_DIR + "/interface/radblue_on.png"));
	rbTypeOpenedElements->imageInactive(WorkingSurfaces::GetInstance()->surfaceFromImage((string)DATA_DIR + "/interface/radblue_off.png"));
	
	getGroupScene()->addGroup(rbTypeOpenedElements);
	
	rbTypeOpenedNature->setActive(true);
	
	// personal radios
	
	rad2d = new RadioButton(NULL, "font-texts", Language::GetInstance()->getText("object2d"));
	rad2d->setIndexZ(1);
	rad2d->setX(140);
	rad2d->setY(80);
	
	rad2d->imageActive(WorkingSurfaces::GetInstance()->surfaceFromImage((string)DATA_DIR + "/interface/radblue_on.png"));
	rad2d->imageInactive(WorkingSurfaces::GetInstance()->surfaceFromImage((string)DATA_DIR + "/interface/radblue_off.png"));
	
	getGroupScene()->addGroup(rad2d);
	
	string txt_rad3d="";
	if (EditBoard::GetInstance()->getScenary()->getType()==SCENARY_CLOSED) {
		txt_rad3d = Language::GetInstance()->getText("object3d_closed");
	} else {
		txt_rad3d = Language::GetInstance()->getText("object3d_opened");
	}
	
	rad3d = new RadioButton(rad2d, "font-texts", txt_rad3d);
	rad3d->setIndexZ(1);
	rad3d->setX(140);
	rad3d->setY(120);
	
	rad3d->imageActive(WorkingSurfaces::GetInstance()->surfaceFromImage((string)DATA_DIR + "/interface/radblue_on.png"));
	rad3d->imageInactive(WorkingSurfaces::GetInstance()->surfaceFromImage((string)DATA_DIR + "/interface/radblue_off.png"));
		
	getGroupScene()->addGroup(rad3d);
	
	if (EditBoard::GetInstance()->getScenary()->getType()==SCENARY_CLOSED) {
		rad2d->setActive(true);
	} else {
		rad3d->setActive(true);
	}
	
	
	titleTypeTextsInWall = new Element();
	titleTypeTextsInWall->setIndexZ(1);
	titleTypeTextsInWall->setVAlign(VALIGN_CENTER);
	titleTypeTextsInWall->setAlign(ALIGN_CENTER);
	titleTypeTextsInWall->setX(400);
	titleTypeTextsInWall->setY(130);

	titleTypeTextsInWall->addFrameLanguage("font-texts", "typefont", ALIGN_CENTER);
	
	getGroupScene()->addElement(titleTypeTextsInWall);
	
	typeTextsInWall = new SelectButton();
	typeTextsInWall->setIndexZ(1);
	typeTextsInWall->setX(305);
	typeTextsInWall->setY(170);
	
	typeTextsInWall->addObject(WorkingSurfaces::GetInstance()->surfaceFromImage((string)DATA_DIR+"/misc/font_wall0.png"));
	typeTextsInWall->addObject(WorkingSurfaces::GetInstance()->surfaceFromImage((string)DATA_DIR+"/misc/font_wall1.png"));
	typeTextsInWall->addObject(WorkingSurfaces::GetInstance()->surfaceFromImage((string)DATA_DIR+"/misc/font_wall2.png"));
	typeTextsInWall->addObject(WorkingSurfaces::GetInstance()->surfaceFromImage((string)DATA_DIR+"/misc/font_wall3.png"));
	typeTextsInWall->addObject(WorkingSurfaces::GetInstance()->surfaceFromImage((string)DATA_DIR+"/misc/font_wall4.png"));
	typeTextsInWall->addObject(WorkingSurfaces::GetInstance()->surfaceFromImage((string)DATA_DIR+"/misc/font_wall5.png"));
	
	typeTextsInWall->setArrows(WorkingSurfaces::GetInstance()->surfaceFromImage((string)DATA_DIR+"/windows/arrow_left.png"), WorkingSurfaces::GetInstance()->surfaceFromImage((string)DATA_DIR+"/windows/arrow_right.png"));
	
	colorTextsInWall = new SelectButton();
	colorTextsInWall->setIndexZ(1);
	colorTextsInWall->setX(350);
	colorTextsInWall->setY(270);

	for (i=0; i<vcolorsTextInWall->count(); i++) {
		colorTextsInWall->addObject(Primitives::GetInstance()->rectangle(40, 40, vcolorsTextInWall->getColor(i)->r, vcolorsTextInWall->getColor(i)->g, vcolorsTextInWall->getColor(i)->b));
	}
	
	colorTextsInWall->setArrows(WorkingSurfaces::GetInstance()->surfaceFromImage((string)DATA_DIR+"/windows/arrow_left.png"), WorkingSurfaces::GetInstance()->surfaceFromImage((string)DATA_DIR+"/windows/arrow_right.png"));
	
	taText = new Entry(NULL, 440, 29, 10, 10);
	taText->setMultiline(true);
	taText->setTotalRows(3);
	taText->setIndexZ(1);
	taText->setFontLabel("font-texts");
	taText->setFont("font-texts");
	taText->setLabel(Language::GetInstance()->getText("inserttext"));
	taText->setHorizontal(false);
	taText->setX(World::width/2);
	taText->setY(330);
	taText->addFrameBoxNormal(WorkingSurfaces::GetInstance()->surfaceFromImage((string)DATA_DIR + "/createmissions/bg_bluesmall_textarea.png"));
	taText->addFrameBoxOnOver(WorkingSurfaces::GetInstance()->surfaceFromImage((string)DATA_DIR + "/createmissions/bg_bluesmall_textarea_on.png"));
	taText->addFrameBoxActived(WorkingSurfaces::GetInstance()->surfaceFromImage((string)DATA_DIR + "/createmissions/bg_bluesmall_textarea_active.png"));
	
	getGroupScene()->addElement((Element*)taText);
	
	taText->setActive(true);
	
	bInsertText = new Button();	
	bInsertText->setScales(1.0, 1.05);
	bInsertText->setIndexZ(1);
	bInsertText->setAlign(ALIGN_CENTER);
	bInsertText->setVAlign(VALIGN_CENTER);
	bInsertText->setX(400);
	bInsertText->setY(480);
	
	bInsertText->imageOut(WorkingSurfaces::GetInstance()->surfaceFromImage((string)DATA_DIR + "/editgame/" + Language::GetInstance()->getFilename("b_inserttext", "png")));
	bInsertText->setAnimation("out");
	
	bInsertText->OnClick = bInsertText_SceneGame_OnClick;

	getGroupScene()->addElement(bInsertText);
	
	radAlignLeftText = new RadioButton(NULL);	
	radAlignLeftText->setIndexZ(1);
	radAlignLeftText->setX(340);
	radAlignLeftText->setY(205);
	
	radAlignLeftText->imageInactive( WorkingSurfaces::GetInstance()->surfaceFromImage(string(DATA_DIR) + "/editgame/b_alignleft_off.png") );
	radAlignLeftText->imageActive( WorkingSurfaces::GetInstance()->surfaceFromImage(string(DATA_DIR) + "/editgame/b_alignleft_on.png") );
	
	getGroupScene()->addGroup(radAlignLeftText);
	
	radAlignCenterText = new RadioButton(radAlignLeftText);	
	radAlignCenterText->setIndexZ(1);
	radAlignCenterText->setX(390);
	radAlignCenterText->setY(205);
	
	radAlignCenterText->imageInactive( WorkingSurfaces::GetInstance()->surfaceFromImage(string(DATA_DIR) + "/editgame/b_aligncenter_off.png") );
	radAlignCenterText->imageActive( WorkingSurfaces::GetInstance()->surfaceFromImage(string(DATA_DIR) + "/editgame/b_aligncenter_on.png") );
	
	getGroupScene()->addGroup(radAlignCenterText);
	
	radAlignRightText = new RadioButton(radAlignLeftText);	
	radAlignRightText->setIndexZ(1);
	radAlignRightText->setX(440);
	radAlignRightText->setY(205);
	
	radAlignRightText->imageInactive( WorkingSurfaces::GetInstance()->surfaceFromImage(string(DATA_DIR) + "/editgame/b_alignright_off.png") );
	radAlignRightText->imageActive( WorkingSurfaces::GetInstance()->surfaceFromImage(string(DATA_DIR) + "/editgame/b_alignright_on.png") );
	
	getGroupScene()->addGroup(radAlignRightText);
	
	radAlignLeftText->setActive(true);
	
	Sounds::GetInstance()->getSound("music_editor")->play(1, -1, 2000);
	
	
	delete pb;
	
}

void SceneEditGame::loadObjectsPersonal () {
	
	objectsPersonal->clear();
	
	DIR *pdir;
	struct dirent *pent;
		
	string path = Missions::GetInstance()->currentLevel->getPath() + "/objects";
	
	pdir=opendir(path.c_str());
	
	if (pdir) {
        while ((pent=readdir(pdir))) {
             string ext = WorkingData::GetInstance()->getExtension(pent->d_name);
             if ( ext == "JPG" || ext == "PNG" ) {
				Button *b = new Button();
				char tmp[128];
				sprintf(tmp, "%s/%s", path.c_str(), pent->d_name);
				b->imageOut(WorkingSurfaces::GetInstance()->surfaceFromImage(tmp));
				
				Size size = WorkingSurfaces::GetInstance()->getSize(tmp);
				float scale = 1.0;
				if (size.h > size.w) {
					scale = 90.0/(float)size.h;
				} else {
					scale = 90.0/(float)size.w;
				}
				b->setScales(scale, scale+0.05);
				
				b->setAnimation("out");
				b->addParameter("name", pent->d_name);
				b->OnClick = insertObjectsPersonal_SceneEditGame_OnClick;
				objectsPersonal->add(b);
             }
        }
        closedir(pdir);
    }
    
}

/**********************
  DRAWSCENE MAIN
**********************/

void SceneEditGame::drawSceneMain () {
	
	verifyOverElements_Main();
	
	for (int i=0; i<MAX_INDEXZ; i++) {
		drawSceneMainByIndexZ(i);
	}
	
}

void SceneEditGame::drawSceneMainByIndexZ(int z) {
	if (EditBoard::GetInstance()->getIndexZ() == z) {
		EditBoard::GetInstance()->draw();	
	}
	if (bgHandTray->getIndexZ() == z) {
		handTray->work();
		bgHandTray->draw();
		btHandTray->draw();
	}
	if (menuBg->getIndexZ() == z) {
		menuBg->draw();
	}
	if (bNimuh->getIndexZ() == z) {
		bNimuh->draw();
	}
	if (bEnemy1->getIndexZ() == z) {
		bEnemy1->draw();
	}
	if (bEnemy2->getIndexZ() == z) {
		bEnemy2->draw();
	}
	if (bEnemy3->getIndexZ() == z) {
		bEnemy3->draw();
	}
	if (bBlackHole1->getIndexZ() == z) {
		bBlackHole1->draw();
	}
	if (bBlackHole2->getIndexZ() == z) {
		bBlackHole2->draw();
	}
	if (bTrap->getIndexZ() == z) {
		bTrap->draw();
	}
	if (bKey->getIndexZ() == z) {
		bKey->draw();
	}
	if (bDoorKey->getIndexZ() == z) {
		bDoorKey->draw();
	}
	if (bEat->getIndexZ() == z) {
		bEat->draw();
	}
	if (bWallRight->getIndexZ() == z) {
		bWallRight->draw();
	}
	if (bWallBottom->getIndexZ() == z) {
		bWallBottom->draw();
	}
	if (bDoor->getIndexZ() == z) {
		bDoor->draw();
	}
	if (typeBoard->getIndexZ() == z) {
		typeBoard->draw();
	}
	if (typeFloor->getIndexZ() == z) {
		typeFloor->draw();
	}
	if (EditBoard::GetInstance()->getScenary()->getType()==SCENARY_CLOSED) {
    	if (colorWall->getIndexZ() == z) {
    		colorWall->draw();
    	}
		if (typeWallScenary->getIndexZ() == z) {
    		typeWallScenary->draw();
    	}
    } else {
    	if (typeTerrain->getIndexZ() == z) {
    		typeTerrain->draw();
    	}
    }
	if (typeWall->getIndexZ() == z) {
		typeWall->draw();
	}
	if (nTilesClosed->getIndexZ() == z) {
		nTilesClosed->draw();
	}
	if (typeTiled->getIndexZ() == z) {
		typeTiled->draw();
	}
	if (typePavement->getIndexZ() == z) {
		typePavement->draw();
	}
	if (bEditInfo->getIndexZ() == z) {
		bEditInfo->draw();
	}
	if (bAddObject->getIndexZ() == z) {
		bAddObject->draw();
	}
	if (bSave->getIndexZ() == z) {
		bSave->draw();
	}
	if (bRules->getIndexZ() == z) {
		bRules->draw();
	}
	if (bClean->getIndexZ() == z) {
		bClean->draw();
	}
	if (bHelp->getIndexZ() == z) {
		bHelp->draw();
	}
	if (menuTown->getIndexZ() == z) {
		menuTown->draw();
	}
	if (menuText->getIndexZ() == z) {
		menuText->draw();
	}
	if (bQuit->getIndexZ() == z) {
		bQuit->draw();
	}
}

void SceneEditGame::verifyClickElements_Main() {
	if (bNimuh->isOnMouseOver()) {
		bNimuh->setActive(true);
		EditBoard::GetInstance()->changeGhost();
	}
	if (bEnemy1->isOnMouseOver()) {
		bEnemy1->setActive(true);
		EditBoard::GetInstance()->changeGhost();
	}
	if (bEnemy2->isOnMouseOver()) {
		bEnemy2->setActive(true);
		EditBoard::GetInstance()->changeGhost();
	}
	if (bEnemy3->isOnMouseOver()) {
		bEnemy3->setActive(true);
		EditBoard::GetInstance()->changeGhost();
	}
	if (bBlackHole1->isOnMouseOver()) {
		bBlackHole1->setActive(true);
		EditBoard::GetInstance()->changeGhost();
	}
	if (bBlackHole2->isOnMouseOver()) {
		bBlackHole2->setActive(true);
		EditBoard::GetInstance()->changeGhost();
	}
	if (bTrap->isOnMouseOver()) {
		bTrap->setActive(true);
		EditBoard::GetInstance()->changeGhost();
	}
	if (bKey->isOnMouseOver()) {
		bKey->setActive(true);
		EditBoard::GetInstance()->changeGhost();
	}
	if (bDoorKey->isOnMouseOver()) {
		bDoorKey->setActive(true);
		EditBoard::GetInstance()->changeGhost();
	}
	if (bEat->isOnMouseOver()) {
		bEat->setActive(true);
		EditBoard::GetInstance()->changeGhost();
	}
	if (bWallRight->isOnMouseOver()) {
		bWallRight->setActive(true);
		EditBoard::GetInstance()->changeGhost();
	}
	if (bWallBottom->isOnMouseOver()) {
		bWallBottom->setActive(true);
		EditBoard::GetInstance()->changeGhost();
	}
	if (bDoor->isOnMouseOver()) {
		bDoor->setActive(true);
		EditBoard::GetInstance()->changeGhost();
	}
	if (typeBoard->isOnMouseOver()) {
		if (typeBoard->getOverBottom()==LEFT) {
			typeBoard->previousFrame();
		}
		if (typeBoard->getOverBottom()==RIGHT) {
			typeBoard->nextFrame();
		}
		typeBoard->OnClick(this, typeBoard);
	}
	if (typeFloor->isOnMouseOver()) {
        if (typeFloor->getSensitive()) {
    		if (typeFloor->getOverBottom()==LEFT) {
    			typeFloor->previousFrame();
    		}
    		if (typeFloor->getOverBottom()==RIGHT) {
    			typeFloor->nextFrame();
    		}
    		typeFloor->OnClick(this, typeFloor);
        } else {
            showMessageBox(Language::GetInstance()->getText("info"), Language::GetInstance()->getText("component_lock"), SCENE_EDITGAME_MAIN);
        }
	}
	if (typePavement->isOnMouseOver()) {
        if (typePavement->getSensitive()) {
    		if (typePavement->getOverBottom()==LEFT) {
    			typePavement->previousFrame();
    		}
    		if (typePavement->getOverBottom()==RIGHT) {
    			typePavement->nextFrame();
    		}
    		typePavement->OnClick(this, typePavement);
        } else {
            showMessageBox(Language::GetInstance()->getText("info"), Language::GetInstance()->getText("component_lock"), SCENE_EDITGAME_MAIN);
        }
	}
	if (typeWall->isOnMouseOver()) {
        if (typeWall->getSensitive()) {
    		if (typeWall->getOverBottom()==LEFT) {
    			typeWall->previousFrame();
    		}
    		if (typeWall->getOverBottom()==RIGHT) {
    			typeWall->nextFrame();
    		}
    		typeWall->OnClick(this, typeWall);
        } else {
            showMessageBox(Language::GetInstance()->getText("info"), Language::GetInstance()->getText("component_lock"), SCENE_EDITGAME_MAIN);
        }
	}
	if (typeTiled->isOnMouseOver()) {
        if (typeTiled->getSensitive()) {
    		if (typeTiled->getOverBottom()==LEFT) {
    			typeTiled->previousFrame();
    		}
    		if (typeTiled->getOverBottom()==RIGHT) {
    			typeTiled->nextFrame();
    		}
    		typeTiled->OnClick(this, typeTiled);
        } else {
            showMessageBox(Language::GetInstance()->getText("info"), Language::GetInstance()->getText("component_lock"), SCENE_EDITGAME_MAIN);
        }
	}
	if (nTilesClosed->isOnMouseOver()) {
		if (nTilesClosed->getOverBottom()==LEFT) {
			nTilesClosed->previousFrame();
		}
		if (nTilesClosed->getOverBottom()==RIGHT) {
			nTilesClosed->nextFrame();
		}
		nTilesClosed->OnClick(this, nTilesClosed);
	}
	if (EditBoard::GetInstance()->getScenary()->getType()==SCENARY_CLOSED) {
    	if (colorWall->isOnMouseOver()) {
    		if (colorWall->getOverBottom()==LEFT) {
    			colorWall->previousFrame();
    		}
    		if (colorWall->getOverBottom()==RIGHT) {
    			colorWall->nextFrame();
    		}
    		colorWall->OnClick(this, colorWall);
    	}
		if (typeWallScenary->isOnMouseOver()) {
			if (typeWallScenary->getSensitive()) {
				if (typeWallScenary->getOverBottom()==LEFT) {
					typeWallScenary->previousFrame();
				}
				if (typeWallScenary->getOverBottom()==RIGHT) {
					typeWallScenary->nextFrame();
				}
				typeWallScenary->OnClick(this, typeWallScenary);
            } else {
                showMessageBox(Language::GetInstance()->getText("info"), Language::GetInstance()->getText("component_lock"), SCENE_EDITGAME_MAIN);
            }
    	}
    } else {
    	if (typeTerrain->isOnMouseOver()) {
           if (typeTerrain->getSensitive()) {
        		if (typeTerrain->getOverBottom()==LEFT) {
        			typeTerrain->previousFrame();
        		}
        		if (typeTerrain->getOverBottom()==RIGHT) {
        			typeTerrain->nextFrame();
        		}
        		typeTerrain->OnClick(this, typeTerrain);
            } else {
                showMessageBox(Language::GetInstance()->getText("info"), Language::GetInstance()->getText("component_lock"), SCENE_EDITGAME_MAIN);
            }
    	}
    }
	if (btHandTray->isOnMouseOver()) {
		btHandTray->OnClick(this, btHandTray);
	}
	if (bEditInfo->isOnMouseOver()) {
		bEditInfo->OnClick(this, bEditInfo);
	}
	if (bSave->isOnMouseOver()) {
		bSave->OnClick(this, bSave);
	}
	if (bAddObject->isOnMouseOver()) {
		bAddObject->OnClick(this, bAddObject);
	}
	if (bRules->isOnMouseOver()) {
		bRules->OnClick(this, bRules);
	}
	if (bClean->isOnMouseOver()) {
		bClean->OnClick(this, bClean);
	}
	if (bHelp->isOnMouseOver()) {
		bHelp->OnClick(this, bHelp);
	}
	if (bQuit->isOnMouseOver()) {
		bQuit->OnClick(this, bQuit);
	}
	EditBoard::GetInstance()->verifyClickOnBoard();
}

void SceneEditGame::verifyOverElements_Main() {
     
	bool canHideText = true;
	
	if (bEditInfo->onOver()) {
         if (bEditInfo->isRollOver) {
        	setTextDisplay(0);
        	canHideText = false;
         } else {
            if (canHideText) {
    		   setTextDisplay(-1);
            }
         }
    }
    
	if (bSave->onOver()) {
         if (bSave->isRollOver) {
        	setTextDisplay(1);
        	canHideText = false;
         } else {
            if (canHideText) {
    		   setTextDisplay(-1);
            }
         }
    }
    
	if (bRules->onOver()) {
         if (bRules->isRollOver) {
        	setTextDisplay(2);
        	canHideText = false;
         } else {
            if (canHideText) {
    		   setTextDisplay(-1);
            }
         }
    }
    
	if (bClean->onOver()) {
         if (bClean->isRollOver) {
        	setTextDisplay(8);
        	canHideText = false;
         } else {
            if (canHideText) {
    		   setTextDisplay(-1);
            }
         }
    }
    
	if (bHelp->onOver()) {
         if (bHelp->isRollOver) {
        	setTextDisplay(9);
        	canHideText = false;
         } else {
            if (canHideText) {
    		   setTextDisplay(-1);
            }
         }
    }
    
	if (bQuit->onOver()) {
         if (bQuit->isRollOver) {
        	setTextDisplay(3);
        	canHideText = false;
         } else {
            if (canHideText) {
    		   setTextDisplay(-1);
            }
         }
    }
    
	if (bAddObject->onOver()) {
         if (bAddObject->isRollOver) {
        	setTextDisplay(4);
        	canHideText = false;
         } else {
            if (canHideText) {
    		   setTextDisplay(-1);
            }
         }
    }
    
	if (bNimuh->onOver()) {
         if (bNimuh->isRollOver) {
        	setTextDisplay(5);
        	canHideText = false;
         } else {
            if (canHideText) {
    		   setTextDisplay(-1);
            }
         }
    }
    
	if (bEnemy1->onOver()) {
         if (bEnemy1->isRollOver) {
        	setTextDisplay(5);
        	canHideText = false;
         } else {
            if (canHideText) {
    		   setTextDisplay(-1);
            }
         }
    }
    
	if (bEnemy2->onOver()) {
         if (bEnemy2->isRollOver) {
        	setTextDisplay(5);
        	canHideText = false;
         } else {
            if (canHideText) {
    		   setTextDisplay(-1);
            }
         }
    }
	
	if (bEnemy3->onOver()) {
         if (bEnemy3->isRollOver) {
        	setTextDisplay(5);
        	canHideText = false;
         } else {
            if (canHideText) {
    		   setTextDisplay(-1);
            }
         }
    }
	
	if (bWallRight->onOver()) {
         if (bWallRight->isRollOver) {
        	setTextDisplay(6);
        	canHideText = false;
         } else {
            if (canHideText) {
    		   setTextDisplay(-1);
            }
         }
    }
    
	if (bWallBottom->onOver()) {
         if (bWallBottom->isRollOver) {
        	setTextDisplay(6);
        	canHideText = false;
         } else {
            if (canHideText) {
    		   setTextDisplay(-1);
            }
         }
    }
    
	if (bDoor->onOver()) {
         if (bDoor->isRollOver) {
        	setTextDisplay(6);
        	canHideText = false;
         } else {
            if (canHideText) {
    		   setTextDisplay(-1);
            }
         }
    }
    
    if (bBlackHole1->onOver()) {
         if (bBlackHole1->isRollOver) {
        	setTextDisplay(6);
        	canHideText = false;
         } else {
            if (canHideText) {
    		   setTextDisplay(-1);
            }
         }
    }
    
    if (bBlackHole2->onOver()) {
         if (bBlackHole2->isRollOver) {
        	setTextDisplay(6);
        	canHideText = false;
         } else {
            if (canHideText) {
    		   setTextDisplay(-1);
            }
         }
    }
    
    if (bTrap->onOver()) {
         if (bTrap->isRollOver) {
        	setTextDisplay(6);
        	canHideText = false;
         } else {
            if (canHideText) {
    		   setTextDisplay(-1);
            }
         }
    }
    
    if (bKey->onOver()) {
         if (bKey->isRollOver) {
        	setTextDisplay(6);
        	canHideText = false;
         } else {
            if (canHideText) {
    		   setTextDisplay(-1);
            }
         }
    }
    
    if (bDoorKey->onOver()) {
         if (bDoorKey->isRollOver) {
        	setTextDisplay(6);
        	canHideText = false;
         } else {
            if (canHideText) {
    		   setTextDisplay(-1);
            }
         }
    }
    
    if (bEat->onOver()) {
         if (bEat->isRollOver) {
        	setTextDisplay(6);
        	canHideText = false;
         } else {
            if (canHideText) {
    		   setTextDisplay(-1);
            }
         }
    }
    
    if (btHandTray->onOver()) {
         if (btHandTray->isRollOver) {
        	setTextDisplay(7);
        	canHideText = false;
         } else {
            if (canHideText) {
    		   setTextDisplay(-1);
            }
         }
    }
	
    if (typeBoard->onOver()) {
         if (typeBoard->isRollOver) {
        	setTextDisplay(10);
        	canHideText = false;
         } else {
            if (canHideText) {
    		   setTextDisplay(-1);
            }
         }
    }
	
    if (typeFloor->onOver()) {
         if (typeFloor->isRollOver) {
        	setTextDisplay(11);
        	canHideText = false;
         } else {
            if (canHideText) {
    		   setTextDisplay(-1);
            }
         }
    }
	
    if (typeWall->onOver()) {
         if (typeWall->isRollOver) {
        	setTextDisplay(12);
        	canHideText = false;
         } else {
            if (canHideText) {
    		   setTextDisplay(-1);
            }
         }
    }
	
    if (typePavement->onOver()) {
         if (typePavement->isRollOver) {
        	setTextDisplay(13);
        	canHideText = false;
         } else {
            if (canHideText) {
    		   setTextDisplay(-1);
            }
         }
    }
	
    if (typeTiled->onOver()) {
         if (typeTiled->isRollOver) {
        	setTextDisplay(14);
        	canHideText = false;
         } else {
            if (canHideText) {
    		   setTextDisplay(-1);
            }
         }
    }
	
    if (nTilesClosed->onOver()) {
         if (nTilesClosed->isRollOver) {
        	setTextDisplay(15);
        	canHideText = false;
         } else {
            if (canHideText) {
    		   setTextDisplay(-1);
            }
         }
    }
	
	if (EditBoard::GetInstance()->getScenary()->getType()==SCENARY_CLOSED) {
		if (typeWallScenary->onOver()) {
			 if (typeWallScenary->isRollOver) {
				setTextDisplay(18);
				canHideText = false;
			 } else {
				if (canHideText) {
				   setTextDisplay(-1);
				}
			 }
		}
		if (colorWall->onOver()) {
			 if (colorWall->isRollOver) {
				setTextDisplay(16);
				canHideText = false;
			 } else {
				if (canHideText) {
				   setTextDisplay(-1);
				}
			 }
		}
	} else {
		if (typeTerrain->onOver()) {
			 if (typeTerrain->isRollOver) {
				setTextDisplay(17);
				canHideText = false;
			 } else {
				if (canHideText) {
				   setTextDisplay(-1);
				}
			 }
		}
	}
	
	EditBoard::GetInstance()->verifyMouseOnBoard();
}

/**********************
  DRAWSCENE ADDOBJECT
**********************/

void SceneEditGame::drawSceneAddObject () {

	verifyOverElements_AddObject();
	elmImgSave[0]->draw();

	for (int i=0; i<MAX_INDEXZ; i++) {
		drawSceneAddObjectByIndexZ(i);
	}
	
}

void SceneEditGame::drawSceneAddObjectByIndexZ(int z) {
	
	if (blueLine->getIndexZ() == z) {
		blueLine->draw();
	}
	
	if (pageAddObject == SCENE_EDITGAME_ADDOBJECT_GAME) {
        if (EditBoard::GetInstance()->getScenary()->getType()==SCENARY_CLOSED) {
    		if (rbTypeClosedWindows->getIndexZ() == z) {
    			rbTypeClosedWindows->draw();
    		}
    		if (rbTypeClosedDoors->getIndexZ() == z) {
    			rbTypeClosedDoors->draw();
    		}
    		if (rbTypeClosedLights->getIndexZ() == z) {
    			rbTypeClosedLights->draw();
    		}
    		if (rbTypeClosedElements->getIndexZ() == z) {
    			rbTypeClosedElements->draw();
    		}
    		if (rbTypeClosedDecorative->getIndexZ() == z) {
    			rbTypeClosedDecorative->draw();
    		}
        } else {
    		if (rbTypeOpenedNature->getIndexZ() == z) {
    			rbTypeOpenedNature->draw();
    		}
    		if (rbTypeOpenedBeach->getIndexZ() == z) {
    			rbTypeOpenedBeach->draw();
    		}
    		if (rbTypeOpenedBench->getIndexZ() == z) {
    			rbTypeOpenedBench->draw();
    		}
    		if (rbTypeOpenedConstruction->getIndexZ() == z) {
    			rbTypeOpenedConstruction->draw();
    		}
    		if (rbTypeOpenedElements->getIndexZ() == z) {
    			rbTypeOpenedElements->draw();
    		}
        }
		if (objectsGame->getIndexZ() == z) {
			objectsGame->draw();
		}
		if (bgArrow->getIndexZ() == z) {
			bgArrow->setXY(727, 140);
			bgArrow->draw();
			bgArrow->setXY(727, 497);
			bgArrow->draw();
		}
	} else if (pageAddObject == SCENE_EDITGAME_ADDOBJECT_PERSONAL) {
		if (objectsPersonal->getIndexZ() == z) {
			objectsPersonal->draw();
		}

		if (rad2d->getIndexZ() == z) {
			rad2d->draw();
		}
		
		if (rad3d->getIndexZ() == z) {
			rad3d->draw();
		}

		if (infoObjectsPersonal->getIndexZ() == z) {
			infoObjectsPersonal->draw();
		}

		
		if (bgArrow->getIndexZ() == z) {
			bgArrow->setXY(727, 180);
			bgArrow->draw();
			bgArrow->setXY(727, 426);
			bgArrow->draw();
		}

	} else if (pageAddObject == SCENE_EDITGAME_ADDOBJECT_TEXT) {
		if (titleTypeTextsInWall->getIndexZ() == z) {
			titleTypeTextsInWall->draw();
		}		
		if (typeTextsInWall->getIndexZ() == z) {
			typeTextsInWall->draw();
		}
		if (colorTextsInWall->getIndexZ() == z) {
			colorTextsInWall->draw();
		}
		if (taText->getIndexZ() == z) {
			taText->draw();
		}
		if (radAlignLeftText->getIndexZ() == z) {
			radAlignLeftText->draw();
		}
		if (radAlignCenterText->getIndexZ() == z) {
			radAlignCenterText->draw();
		}
		if (radAlignRightText->getIndexZ() == z) {
			radAlignRightText->draw();
		}
		if (bInsertText->getIndexZ() == z) {
			bInsertText->draw();
		}
	}
	
	if (bgButton->getIndexZ() == z) {
		bgButton->draw();
	}
	
	if (bObjectsPersonal->getIndexZ() == z) {
		bObjectsPersonal->draw();
	}
	
	if (bObjectsGame->getIndexZ() == z) {
		bObjectsGame->draw();
	}
	
	if (bObjectsTexts->getIndexZ() == z) {
		bObjectsTexts->draw();
	}
	
	if (bCancelObjects->getIndexZ() == z) {
		bCancelObjects->draw();
	}
	
}

void SceneEditGame::verifyClickElements_AddObject() {

	if (pageAddObject == SCENE_EDITGAME_ADDOBJECT_GAME) {
                      
        if (EditBoard::GetInstance()->getScenary()->getType()==SCENARY_CLOSED) {
    		if (rbTypeClosedWindows->isOnMouseOver()) {
    			rbTypeClosedWindows->setActive(true);
    			objectsGame->setCategory("windows");
    		}
    		if (rbTypeClosedDoors->isOnMouseOver()) {
    			rbTypeClosedDoors->setActive(true);
    			objectsGame->setCategory("doors");
    		}
    		if (rbTypeClosedLights->isOnMouseOver()) {
    			rbTypeClosedLights->setActive(true);
    			objectsGame->setCategory("lights");
    		}
    		if (rbTypeClosedElements->isOnMouseOver()) {
    			rbTypeClosedElements->setActive(true);
    			objectsGame->setCategory("elements");
    		}
    		if (rbTypeClosedDecorative->isOnMouseOver()) {
    			rbTypeClosedDecorative->setActive(true);
    			objectsGame->setCategory("decorative");
    		}
        } else {
    		if (rbTypeOpenedNature->isOnMouseOver()) {
    			rbTypeOpenedNature->setActive(true);
    			objectsGame->setCategory("nature");
    		}
    		if (rbTypeOpenedBeach->isOnMouseOver()) {
    			rbTypeOpenedBeach->setActive(true);
    			objectsGame->setCategory("beach");
    		}
    		if (rbTypeOpenedBench->isOnMouseOver()) {
    			rbTypeOpenedBench->setActive(true);
    			objectsGame->setCategory("benchs");
    		}
    		if (rbTypeOpenedConstruction->isOnMouseOver()) {
    			rbTypeOpenedConstruction->setActive(true);
    			objectsGame->setCategory("construction");
    		}
    		if (rbTypeOpenedElements->isOnMouseOver()) {
    			rbTypeOpenedElements->setActive(true);
    			objectsGame->setCategory("elements");
    		}
        }
                      
		objectsGame->MoveFirst();
		
		while (!objectsGame->isEOF()) {
			if ( (objectsGame->getData()->isOnMouseOver()) 
					&& (objectsGame->getData()->isVisible()) ) {
				objectsGame->getData()->OnClick(this, objectsGame->getData());
			}
			objectsGame->MoveNext();
		}
		
		objectsGame->verifyClickButtons();
	} else if (pageAddObject == SCENE_EDITGAME_ADDOBJECT_PERSONAL) {
		
		if (rad2d->isOnMouseOver()) {
			rad2d->setActive(true);
		}
		
		if (rad3d->isOnMouseOver()) {
			rad3d->setActive(true);
		}
		
		objectsPersonal->MoveFirst();
		
		while (!objectsPersonal->isEOF()) {
			if ( (objectsPersonal->getData()->isOnMouseOver()) 
					&& (objectsPersonal->getData()->isVisible()) ) {
				objectsPersonal->getData()->OnClick(this, objectsPersonal->getData());
			}
			objectsPersonal->MoveNext();
		}
		
		objectsPersonal->verifyClickButtons();
	} else if (pageAddObject == SCENE_EDITGAME_ADDOBJECT_TEXT) {
		if (typeTextsInWall->isOnMouseOver()) {
			if (typeTextsInWall->getOverBottom()==LEFT) {
				typeTextsInWall->previousFrame();
			}
			if (typeTextsInWall->getOverBottom()==RIGHT) {
				typeTextsInWall->nextFrame();
			}
		}
		if (colorTextsInWall->isOnMouseOver()) {
			if (colorTextsInWall->getOverBottom()==LEFT) {
				colorTextsInWall->previousFrame();
			}
			if (colorTextsInWall->getOverBottom()==RIGHT) {
				colorTextsInWall->nextFrame();
			}
		}
		if (bInsertText->isOnMouseOver()) {
			bInsertText->OnClick(this, bInsertText);
		}
		if (radAlignLeftText->isOnMouseOver()) {
			radAlignLeftText->setActive(true);
		}
		if (radAlignCenterText->isOnMouseOver()) {
			radAlignCenterText->setActive(true);
		}
		if (radAlignRightText->isOnMouseOver()) {
			radAlignRightText->setActive(true);
		}
	}
	
	if (bObjectsPersonal->isOnMouseOver()) {
		bObjectsPersonal->OnClick(this, bObjectsPersonal);
	}
	
	if (bObjectsGame->isOnMouseOver()) {
		bObjectsGame->OnClick(this, bObjectsGame);
	}
	
	if (bObjectsTexts->isOnMouseOver()) {
		bObjectsTexts->OnClick(this, bObjectsTexts);
	}
	
	if (bCancelObjects->isOnMouseOver()) {
		bCancelObjects->OnClick(this, bCancelObjects);
	}
}


void SceneEditGame::verifyOverElements_AddObject() {
	if (pageAddObject == SCENE_EDITGAME_ADDOBJECT_GAME) {
		objectsGame->onOver();
	} else if (pageAddObject == SCENE_EDITGAME_ADDOBJECT_PERSONAL) {
		objectsPersonal->onOver();
	} else if (pageAddObject == SCENE_EDITGAME_ADDOBJECT_TEXT) {
		bInsertText->onOver();
	}
	bObjectsGame->onOver();
	bObjectsPersonal->onOver();
	bCancelObjects->onOver();
}

/**********************
  DRAWSCENE EDITFOOD
**********************/

void SceneEditGame::drawSceneEditFood () {
	
	verifyOverElements_EditFood();
	elmImgSave[0]->draw();
	
	for (int i=0; i<MAX_INDEXZ; i++) {
		drawSceneEditFoodByIndexZ(i);
	}
	
}

void SceneEditGame::drawSceneEditFoodByIndexZ(int z) {
	if (frameUp->getIndexZ() == z) {
		frameUp->draw();
	}
	if (frameDown->getIndexZ() == z) {
		frameDown->draw();
	}
	if (bgBox->getIndexZ() == z) {
		bgBox->draw();
	}
	
	if (EditBoard::GetInstance()->multiLanguage) {		
		if (multiLanguageNoSupport->getIndexZ() == z) {
			multiLanguageNoSupport->draw();
		}
	} else {
		if (infoImageFood->getIndexZ() == z) {
			infoImageFood->draw();
		}
		if (titleFood->getIndexZ() == z) {
			titleFood->draw();
		}
		if (textFood->getIndexZ() == z) {
			textFood->draw();
		}
	}
	if (bAccept->getIndexZ() == z) {
		bAccept->draw();
	}
	if (bCancel->getIndexZ() == z) {
		bCancel->draw();
	}
}

void SceneEditGame::verifyClickElements_EditFood() {
	if (bAccept->isOnMouseOver()) {
		bAccept->OnClick(this, bAccept);
	}
	if (bCancel->isOnMouseOver()) {
		bCancel->OnClick(this, bCancel);
	}
	if (titleFood->isOnMouseOver()) {
		titleFood->setActive(true);
	}
	if (textFood->isOnMouseOver()) {
		textFood->setActive(true);
	}
}


void SceneEditGame::verifyOverElements_EditFood() {
	bAccept->onOver();
	bCancel->onOver();
	titleFood->onOver();
	textFood->onOver();
}

/**********************
  DRAWSCENE EDITINFO
**********************/

void SceneEditGame::drawSceneEditInfo () {
	
	verifyOverElements_EditInfo();
	elmImgSave[0]->draw();
	
	for (int i=0; i<MAX_INDEXZ; i++) {
		drawSceneEditInfoByIndexZ(i);
	}
	
}

void SceneEditGame::drawSceneEditInfoByIndexZ(int z) {
	if (frameUp->getIndexZ() == z) {
		frameUp->draw();
	}
	if (frameDown->getIndexZ() == z) {
		frameDown->draw();
	}
	if (bgBox->getIndexZ() == z) {
		bgBox->draw();
	}
	
	if (bInfoMain->getIndexZ() == z) {
		bInfoMain->draw();
	}
	if (bInfoData->getIndexZ() == z) {
		bInfoData->draw();
	}
	if (bInfoMusic->getIndexZ() == z) {
		bInfoMusic->draw();
	}
	
	switch (pageEditInfo) {
		case SCENE_EDITGAME_EDITINFO_MAIN:
			if (levelName->getIndexZ() == z) {
				levelName->draw();
			}
			if (provinceName->getIndexZ() == z) {
				provinceName->draw();
			}
			if (missionName->getIndexZ() == z) {
				missionName->draw();
			}
			if (nameAuthor->getIndexZ() == z) {
				nameAuthor->draw();
			}
		break;
		case SCENE_EDITGAME_EDITINFO_DATA:
			if (EditBoard::GetInstance()->multiLanguage) {
				if (multiLanguageNoSupport->getIndexZ() == z) {
					multiLanguageNoSupport->draw();
				}
			} else {
				if (dataInfo->getNItems()<=0) {
					if (noExistInfoTown->getIndexZ() == z) {
						noExistInfoTown->draw();
					}
				} else {
					if (dataInfo->getIndexZ() == z) {
						dataInfo->draw();
					}
				}
				if (bAddInfo->getIndexZ() == z) {
					bAddInfo->draw();
				}
				
			}
		break;
		case SCENE_EDITGAME_EDITINFO_MUSIC:
			if (radMusic0->getIndexZ() == z) {
				radMusic0->draw();
			}
			if (radMusic1->getIndexZ() == z) {
				radMusic1->draw();
			}
			if (radMusic2->getIndexZ() == z) {
				radMusic2->draw();
			}
			if (radMusic3->getIndexZ() == z) {
				radMusic3->draw();
			}
		break;
	}

	if (bAccept->getIndexZ() == z) {
		bAccept->draw();
	}
	if (bCancel->getIndexZ() == z) {
		bCancel->draw();
	}
}

void SceneEditGame::verifyClickElements_EditInfo() {
	if (bAccept->isOnMouseOver()) {
		bAccept->OnClick(this, bAccept);
	}
	if (bCancel->isOnMouseOver()) {
		bCancel->OnClick(this, bCancel);
	}
	if (bInfoMain->isOnMouseOver()) {
		bInfoMain->OnClick(this, bInfoMain);
	}
	if (bInfoData->isOnMouseOver()) {
		bInfoData->OnClick(this, bInfoData);
	}
	if (bInfoMusic->isOnMouseOver()) {
		bInfoMusic->OnClick(this, bInfoMusic);
	}
	switch (pageEditInfo) {
		case SCENE_EDITGAME_EDITINFO_MAIN:
        	if (missionName->isOnMouseOver()) {
        		missionName->setActive(true);
        	}
        	if (nameAuthor->isOnMouseOver()) {
        		nameAuthor->setActive(true);
        	}
        	if (levelName->isOnMouseOver()) {
        		levelName->setActive(true);
        	}
        	if (provinceName->isOnMouseOver()) {
        		provinceName->setActive(true);
        	}
		break;
		case SCENE_EDITGAME_EDITINFO_DATA:
			if (!EditBoard::GetInstance()->multiLanguage) {
				if (dataInfo->getNItems()>0) {
					dataInfo->MoveFirst();
					while (!dataInfo->isEOF()) {
						if (dataInfo->isVisible()) {
						   InfoButton *bu = (InfoButton*)dataInfo->getData();
						   bu->verifyClick(this);
						}
						dataInfo->MoveNext();
					}
				}
				if (bAddInfo->isOnMouseOver()) {
					bAddInfo->OnClick(this, bAddInfo);
				}
			}
		break;
		case SCENE_EDITGAME_EDITINFO_MUSIC:
			if (radMusic0->isOnMouseOver()) {
				radMusic0->setActive(true);
			}
			if (radMusic1->isOnMouseOver()) {
				radMusic1->setActive(true);
			}
			if (radMusic2->isOnMouseOver()) {
				radMusic2->setActive(true);
			}
			if (radMusic3->isOnMouseOver()) {
				radMusic3->setActive(true);
			}
		break;
    }
}


void SceneEditGame::verifyOverElements_EditInfo() {

	bAccept->onOver();
	bCancel->onOver();
	bInfoMain->onOver();
	bInfoData->onOver();
	bInfoMusic->onOver();
	switch (pageEditInfo) {
		case SCENE_EDITGAME_EDITINFO_MAIN:
        	levelName->onOver();
        	provinceName->onOver();
        	missionName->onOver();
        	nameAuthor->onOver();
		break;
		case SCENE_EDITGAME_EDITINFO_DATA:
			if ( (!EditBoard::GetInstance()->multiLanguage) && (dataInfo->getNItems()>0) ) {
				dataInfo->MoveFirst();
				while (!dataInfo->isEOF()) {
					if (dataInfo->isVisible()) {
					   InfoButton *bu = (InfoButton*)dataInfo->getData();
					   bu->onOver();
					}
					dataInfo->MoveNext();
				}
			}
			bAddInfo->onOver();
		break;
    }
}

/**********************
  DRAWSCENE CLEAN
**********************/

void SceneEditGame::drawSceneClean () {
	
	verifyOverElements_Clean();
	elmImgSave[0]->draw();
	
	for (int i=0; i<MAX_INDEXZ; i++) {
		drawSceneCleanByIndexZ(i);
	}
	
}

void SceneEditGame::drawSceneCleanByIndexZ(int z) {
	if (frameUp->getIndexZ() == z) {
		frameUp->draw();
	}
	if (frameDown->getIndexZ() == z) {
		frameDown->draw();
	}
	if (middleBox->getIndexZ() == z) {
		middleBox->draw();
	}
	if (bCleanScenary->getIndexZ() == z) {
		bCleanScenary->draw();
	}
	if (bCleanBoard->getIndexZ() == z) {
		bCleanBoard->draw();
	}
	if (bCleanReset->getIndexZ() == z) {
		bCleanReset->draw();
	}
	if (bAccept->getIndexZ() == z) {
		bAccept->draw();
	}
	if (bCancel->getIndexZ() == z) {
		bCancel->draw();
	}
}

void SceneEditGame::verifyClickElements_Clean() {
	if (bAccept->isOnMouseOver()) {
		bAccept->OnClick(this, bAccept);
	}
	if (bCancel->isOnMouseOver()) {
		bCancel->OnClick(this, bCancel);
	}
	if (bCleanScenary->isOnMouseOver()) {
		bCleanScenary->OnClick(this, bCleanScenary);
	}
	if (bCleanBoard->isOnMouseOver()) {
		bCleanBoard->OnClick(this, bCleanBoard);
	}
	if (bCleanReset->isOnMouseOver()) {
		bCleanReset->OnClick(this, bCleanReset);
	}
}


void SceneEditGame::verifyOverElements_Clean() {
	bAccept->onOver();
	bCancel->onOver();
	bCleanScenary->onOver();
	bCleanBoard->onOver();
	bCleanReset->onOver();
}

/**********************
  DRAWSCENE ADDINFOTOWN
**********************/

void SceneEditGame::drawSceneAddInfoTown () {
	
	verifyOverElements_Help();
	elmImgSave[1]->draw();
	
	for (int i=0; i<MAX_INDEXZ; i++) {
		drawSceneAddInfoTownByIndexZ(i);
	}
	
}

void SceneEditGame::drawSceneAddInfoTownByIndexZ(int z) {
	if (frameUp->getIndexZ() == z) {
		frameUp->draw();
	}
	if (frameDown->getIndexZ() == z) {
		frameDown->draw();
	}
	if (bgBox->getIndexZ() == z) {
		bgBox->draw();
	}
	if (typeButtonInfoTown->getIndexZ() == z) {
		typeButtonInfoTown->draw();
	}
	if (eTitleInfoTown->getIndexZ() == z) {
		eTitleInfoTown->draw();
	}
	if (taInfoTown->getIndexZ() == z) {
		taInfoTown->draw();
	}
	if (bAccept->getIndexZ() == z) {
		bAccept->draw();
	}
	if (bCancel->getIndexZ() == z) {
		bCancel->draw();
	}
}

void SceneEditGame::verifyClickElements_AddInfoTown() {
	if (bAccept->isOnMouseOver()) {
		bAccept->OnClick(this, bAccept);
	}
	if (bCancel->isOnMouseOver()) {
		bCancel->OnClick(this, bCancel);
	}
	if (eTitleInfoTown->isOnMouseOver()) {
		eTitleInfoTown->setActive(true);
	}
	if (taInfoTown->isOnMouseOver()) {
		taInfoTown->setActive(true);
	}
	if (typeButtonInfoTown->isOnMouseOver()) {
		if (typeButtonInfoTown->getOverBottom()==LEFT) {
			typeButtonInfoTown->previousFrame();
		}
		if (typeButtonInfoTown->getOverBottom()==RIGHT) {
			typeButtonInfoTown->nextFrame();
		}
	}
}


void SceneEditGame::verifyOverElements_AddInfoTown() {
	bAccept->onOver();
	bCancel->onOver();
}

/**********************
  DRAWSCENE HELP
**********************/

void SceneEditGame::drawSceneHelp () {
	
	verifyOverElements_Help();
	elmImgSave[0]->draw();
	
	for (int i=0; i<MAX_INDEXZ; i++) {
		drawSceneHelpByIndexZ(i);
	}
	
}

void SceneEditGame::drawSceneHelpByIndexZ(int z) {
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
		if (bHelp5->getIndexZ() == z) {
			bHelp5->draw();
		}
		if (bHelp6->getIndexZ() == z) {
			bHelp6->draw();
		}
		if (bHelp7->getIndexZ() == z) {
			bHelp7->draw();
		}
		if (bHelp8->getIndexZ() == z) {
			bHelp8->draw();
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

void SceneEditGame::verifyClickElements_Help() {
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
		if (bHelp5->isOnMouseOver()) {
			bHelp5->OnClick(this, bHelp5);
		}
		if (bHelp6->isOnMouseOver()) {
			bHelp6->OnClick(this, bHelp6);
		}
		if (bHelp7->isOnMouseOver()) {
			bHelp7->OnClick(this, bHelp7);
		}
		if (bHelp8->isOnMouseOver()) {
			bHelp8->OnClick(this, bHelp8);
		}
	}
}


void SceneEditGame::verifyOverElements_Help() {
	if (nElmHelp==-1) {
		bHelp1->onOver();
		bHelp2->onOver();
		bHelp3->onOver();
		bHelp4->onOver();
		bHelp5->onOver();
		bHelp6->onOver();
		bHelp7->onOver();
		bHelp8->onOver();
	}
	bIndex->onOver();
	bPrevious->onOver();
	bNext->onOver();
	bCancel->onOver();
}
	
bool SceneEditGame::drawScene() {
	
	glClear(GL_COLOR_BUFFER_BIT); // | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	
	drawCommonsScene ();
	
	switch(statusScene) {
	
		case SCENE_EDITGAME_MAIN:
			
			drawSceneMain();
		
			// Comprobando teclas para opciones			
			{ SDL_Event event;
				while ( SDL_PollEvent(&event) ) {
					if ( event.type == SDL_QUIT ) {
						goToScene("quit");
					}
					
					if ( event.key.keysym.sym == SDLK_s ) {
						saveScreenShot();
					}
					
					if ( event.type == SDL_KEYDOWN ) {
						if ( event.key.keysym.sym == SDLK_ESCAPE ) {
							goToScene("menu");
						}
					}
					
					if ( event.type == SDL_MOUSEBUTTONDOWN ) {
						if ( event.button.button == SDL_BUTTON_LEFT ) {
							verifyClickElements_Main();
						}
					}
					
					if ( event.type == SDL_MOUSEBUTTONUP ) {
						if ( event.button.button == SDL_BUTTON_LEFT ) {
							EditBoard::GetInstance()->verifyUnClickOnBoard();
						}
						if ( event.button.button == SDL_BUTTON_RIGHT ) {
							EditBoard::GetInstance()->getScenary()->verifyShowIcons();
						}
					}
		
				}
			}
			
		break;
			
		case SCENE_EDITGAME_ADDOBJECT:
			
			drawSceneAddObject();
		
			// Comprobando teclas para opciones			
			{ SDL_Event event;
				while ( SDL_PollEvent(&event) ) {
					if ( event.type == SDL_QUIT ) {
						goToScene("quit");
					}
										
					if ( event.type == SDL_KEYDOWN ) {
                    	switch (pageAddObject) {
                    		case SCENE_EDITGAME_ADDOBJECT_TEXT:
						         taText->insertTextUnicode(event.key.keysym.sym, event.key.keysym.unicode);
                            break;
                        }
						if ( event.key.keysym.sym == SDLK_ESCAPE ) {
							setStatusScene(SCENE_EDITGAME_MAIN);
						}
					}
					
					if ( event.type == SDL_MOUSEBUTTONDOWN ) {
						if ( event.button.button == SDL_BUTTON_LEFT ) {
							verifyClickElements_AddObject();
						}
        				if ( ( event.button.button == 4 ) ) {
							if (pageAddObject == SCENE_EDITGAME_ADDOBJECT_GAME) {
        						objectsGame->upItems();
							} else if (pageAddObject == SCENE_EDITGAME_ADDOBJECT_PERSONAL) {
								objectsPersonal->upItems();
							}
        				}
						if ( ( event.button.button == 5 ) ) {
							if (pageAddObject == SCENE_EDITGAME_ADDOBJECT_GAME) {
        						objectsGame->downItems();
							} else if (pageAddObject == SCENE_EDITGAME_ADDOBJECT_PERSONAL) {
								objectsPersonal->downItems();
							}
        				}
					}
					
		
				}
			}
		
		break;
		
		case SCENE_EDITGAME_EDITFOOD:
			
			drawSceneEditFood();
		
			// Comprobando teclas para opciones			
			{ SDL_Event event;
				while ( SDL_PollEvent(&event) ) {
					if ( event.type == SDL_QUIT ) {
						goToScene("quit");
					}
										
					if ( event.type == SDL_KEYDOWN ) {
						if ( event.key.keysym.sym == SDLK_ESCAPE ) {
							setStatusScene(SCENE_EDITGAME_MAIN);
						}
						titleFood->insertTextUnicode(event.key.keysym.sym, event.key.keysym.unicode);
					}
										
					if ( event.type == SDL_MOUSEBUTTONDOWN ) {
						if ( event.button.button == SDL_BUTTON_LEFT ) {
							verifyClickElements_EditFood();
						}
					}
					
		
				}
			}
		
		break;
		
		case SCENE_EDITGAME_EDITINFO:
			
			drawSceneEditInfo();
		
			// Comprobando teclas para opciones			
			{ SDL_Event event;
				while ( SDL_PollEvent(&event) ) {
					if ( event.type == SDL_QUIT ) {
						goToScene("quit");
					}
										
					if ( event.type == SDL_KEYDOWN ) {
                    	switch (pageEditInfo) {
                    		case SCENE_EDITGAME_EDITINFO_MAIN:
						         missionName->insertTextUnicode(event.key.keysym.sym, event.key.keysym.unicode);
                            break;
                    		case SCENE_EDITGAME_EDITINFO_DATA:
                        		taInfoTown->insertTextUnicode(event.key.keysym.sym, event.key.keysym.unicode);
                            break;
                        }
						if ( event.key.keysym.sym == SDLK_ESCAPE ) {
							setStatusScene(SCENE_EDITGAME_MAIN);
						}
					}
					
					if ( event.type == SDL_MOUSEBUTTONDOWN ) {
						if ( event.button.button == SDL_BUTTON_LEFT ) {
							verifyClickElements_EditInfo();
						}
					}
					
		
				}
			}
		
		break;
			
		case SCENE_EDITGAME_CLEAN:
			
			drawSceneClean();
		
			// Comprobando teclas para opciones			
			{ SDL_Event event;
				while ( SDL_PollEvent(&event) ) {
					if ( event.type == SDL_QUIT ) {
						goToScene("quit");
					}
										
					if ( event.type == SDL_KEYDOWN ) {
						if ( event.key.keysym.sym == SDLK_ESCAPE ) {
							setStatusScene(SCENE_EDITGAME_MAIN);
						}
					}
					
					if ( event.type == SDL_MOUSEBUTTONDOWN ) {
						if ( event.button.button == SDL_BUTTON_LEFT ) {
							verifyClickElements_Clean();
						}
					}
					
		
				}
			}
		
		break;
			
		case SCENE_EDITGAME_HELP:
			
			drawSceneHelp();
		
			// Comprobando teclas para opciones			
			{ SDL_Event event;
				while ( SDL_PollEvent(&event) ) {
					if ( event.type == SDL_QUIT ) {
						goToScene("quit");
					}
										
					if ( event.type == SDL_KEYDOWN ) {
						if ( event.key.keysym.sym == SDLK_ESCAPE ) {
							setStatusScene(SCENE_EDITGAME_MAIN);
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
			
		case SCENE_EDITGAME_ADDINFOTOWN:
			
			drawSceneAddInfoTown();
		
			// Comprobando teclas para opciones			
			{ SDL_Event event;
				while ( SDL_PollEvent(&event) ) {
					if ( event.type == SDL_QUIT ) {
						goToScene("quit");
					}
										
					if ( event.type == SDL_KEYDOWN ) {
                        eTitleInfoTown->insertTextUnicode(event.key.keysym.sym, event.key.keysym.unicode);
						if ( event.key.keysym.sym == SDLK_ESCAPE ) {
							setStatusScene(SCENE_EDITGAME_MAIN);
						}
					}
					
					if ( event.type == SDL_MOUSEBUTTONDOWN ) {
						if ( event.button.button == SDL_BUTTON_LEFT ) {
							verifyClickElements_AddInfoTown();
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
void SceneEditGame::unLoad() {

	unLoadCommons();
	
	statusScene = SCENE_EDITGAME_MAIN;
	
	EditBoard::GetInstance()->unLoad();
	
	delete multiLanguageNoSupport;
	
	delete vcolorsWall;
	delete vcolorsTextInWall;
	
	delete bDoor;
	delete bNimuh;
	delete bEnemy1;
	delete bEnemy2;
	delete bEnemy3;
	delete bBlackHole1;
	delete bBlackHole2;
	delete bTrap;
	delete bKey;
	delete bEat;
	delete bDoorKey;
	delete bWallRight;
	delete bWallBottom;
	delete typeWall;
	delete typeFloor;
	delete typeBoard;
	delete typeTiled;
	delete typePavement;
	delete colorWall;
	delete nTilesClosed;
	delete typeTerrain;
	delete typeWallScenary;
	delete bEditInfo;
	delete bSave;
	delete bAddObject;
	delete bRules;
	delete bClean;
	delete bHelp;
	delete bQuit;
	
	delete frameUp;
	delete frameDown;
	
	delete rad2d;
	delete rad3d;
	
	delete rbTypeClosedWindows;
    delete rbTypeClosedDoors;
    delete rbTypeClosedLights;
    delete rbTypeClosedElements;
    delete rbTypeClosedDecorative;
    delete rbTypeOpenedNature;
    delete rbTypeOpenedBeach;
    delete rbTypeOpenedBench;
    delete rbTypeOpenedConstruction;
    delete rbTypeOpenedElements;
	
	delete typeTextsInWall;
	delete colorTextsInWall;
	delete taText;
	delete titleTypeTextsInWall;
	delete bInsertText;
	delete radAlignLeftText;
	delete radAlignCenterText;
	delete radAlignRightText;
	
	delete menuTown;
	
	delete bgHandTray;
	delete btHandTray;
	delete bgBox;
	delete middleBox;
	
	delete bgHelp;
	delete elmHelp;
	delete titleIndex;
	
	delete bHelp1;
	delete bHelp2;
	delete bHelp3;
	delete bHelp4;
	delete bHelp5;
	delete bHelp6;
	delete bHelp7;
	delete bHelp8;
	
	delete typeButtonInfoTown;
	delete eTitleInfoTown;
	delete taInfoTown;
	delete dataInfo;
	delete noExistInfoTown;
	delete bAddInfo;
	
	delete bCleanBoard;
	delete bCleanScenary;
	delete bCleanReset;
	
	delete levelName;
	delete provinceName;
	delete missionName;
	delete nameAuthor;
	
	delete bInfoMain;
	delete bInfoData;
	delete bInfoMusic;
	
	delete radMusic0;
	delete radMusic1;
	delete radMusic2;
	delete radMusic3;
	
	delete menuText;
	delete menuBg;

	delete bAccept;
	delete bCancel;
	delete bNext;
	delete bPrevious;
	delete bIndex;

	delete titleFood;
	delete textFood;
	delete infoImageFood;

	delete objectsGame;
	delete objectsPersonal;
	delete bObjectsGame;
	delete bObjectsPersonal;
	delete bObjectsTexts;
	delete blueLine;
	delete infoObjectsPersonal;
	
	delete bgButton;
	delete bgArrow;
	
	Sounds::GetInstance()->unLoad();
	
	isLoad = false;

}
