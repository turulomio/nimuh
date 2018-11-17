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
 
#include "scene_game.h"

class SceneGame;
	
void bNext_SceneGame_OnClick (Scene *s, Button *b) {
	//SceneGame* se = (SceneGame*)s;
	Board::GetInstance()->nextHistory();
}

void bPrevious_SceneGame_OnClick (Scene *s, Button *b) {
	//SceneGame* se = (SceneGame*)s;
	Board::GetInstance()->previousHistory();
}

void bOption_SceneGame_OnClick (Scene *s, Button *b) {
	SceneGame* se = (SceneGame*)s;
	se->typeMusic->setFrame(se->getTypeMusic());
	se->setSaveImage(true);
	se->setStatusScene(SCENE_GAME_OPTIONS);
}

void bReset_SceneGame_OnClick (Scene *s, Button *b) {
	SceneGame* se = (SceneGame*)s;
	se->clear();
	Board::GetInstance()->loadLevel();
	se->setStatusScene(SCENE_GAME_MAIN);
}

void bQuit_SceneGame_OnClick (Scene *s, Button *b) {
	SceneGame* se = (SceneGame*)s;
	se->getMusicGame()->stop(2000);
	se->goToScene("menu", 2000, SCENE_TRANSITION_FADEOUT);
}

void bAcceptInfo_SceneGame_OnClick (Scene *s, Button *b) {
	SceneGame* se = (SceneGame*)s;
	if (se->getStatusScene()==SCENE_GAME_TRAY) {
		Sounds::GetInstance()->getSound("eating")->play(9, -1);
	}
	se->setStatusScene(SCENE_GAME_MAIN);
}

void bAccept_SceneGame_OnClick (Scene *s, Button *b) {
	SceneGame* se = (SceneGame*)s;
	
	char tmp[8];
	sprintf (tmp, "%d", se->volumeMusics->getIndex());
	Options::GetInstance()->setValue("music", tmp);
	sprintf (tmp, "%d", se->volumeEffects->getIndex());
	Options::GetInstance()->setValue("effects", tmp);
	if (se->cbHelpActived->getActive()) {
 	   Options::GetInstance()->setValue("helpactived", "true");
    } else {
 	   Options::GetInstance()->setValue("helpactived", "false");           
    }
	Options::GetInstance()->save();
	
	Sound::setPorcentVolumeByCategory("music", 20*(Options::GetInstance()->getValueToInt("music")));
	Sound::setPorcentVolumeByCategory("high_music", 20*(Options::GetInstance()->getValueToInt("music")+1));
	Sound::setPorcentVolumeByCategory("low_music", 20*(Options::GetInstance()->getValueToInt("music")-1));
	Sound::setPorcentVolumeByCategory("musicgame", (20*(Options::GetInstance()->getValueToInt("music")))/3);
	Sound::setPorcentVolumeByCategory("effect", 20*(Options::GetInstance()->getValueToInt("effects")));

	se->loadMusic(se->typeMusic->getIndex());
	se->getMusicGame()->play(1,-1);
		
	se->setStatusScene(SCENE_GAME_MAIN);
}

void bCancel_SceneGame_OnClick (Scene *s, Button *b) {
	SceneGame* se = (SceneGame*)s;
	se->setStatusScene(SCENE_GAME_MAIN);
}

void bRetry_SceneGame_OnClick (Scene *s, Button *b) {
	SceneGame* se = (SceneGame*)s;
	se->clear();
	Board::GetInstance()->loadLevel();
	se->setStatusScene(SCENE_GAME_MAIN);
}

void bLeave_SceneGame_OnClick (Scene *s, Button *b) {
	SceneGame* se = (SceneGame*)s;
	se->getMusicGame()->stop(2000);
	se->goToScene("menu", 2000, SCENE_TRANSITION_FADEOUT);
}

void bContinue_SceneGame_OnClick (Scene *s, Button *b) {
	SceneGame* se = (SceneGame*)s;
	se->goToNextLevel();
}

void bBack_SceneGame_OnClick (Scene *s, Button *b) {
	SceneGame* se = (SceneGame*)s;
	se->getMusicGame()->stop(2000);
	se->goToScene("menu", 2000, SCENE_TRANSITION_FADEOUT);
}



SceneGame::SceneGame() : Scene () {
	statusScene = SCENE_GAME_MAIN;
	active = false;
	hasEyeInformation = false;
	hasHelp = false;
	indexMusicActive = 0;
	animationEnd = false;
	hasHelpFirstLevel = false;
	showedHelpFirstLevel = false;
}

void SceneGame::goToNextLevel() {
	if (Users::GetInstance()->getCurrentUser()->getLevelInCurrentMission() > Missions::GetInstance()->currentMission->getNLevels()-1) {
		if (Missions::GetInstance()->currentMission->getDirectory()=="andalucia") {
			setDrawCursor(false);
			setStatusScene(SCENE_GAME_ENDANIMATION);
		} else {
			setStatusScene(SCENE_GAME_FINISH);
		}
	} else {
		if (Missions::GetInstance()->setCurrentLevel()) {
			if (!animationEnd) {
				goToScene("infotown", 1000, SCENE_TRANSITION_FADEOUT_SCALEx0);
			} else {
				setDrawCursor(false);
				setStatusScene(SCENE_GAME_ENDANIMATION);
			}
		} else {
			if (Missions::GetInstance()->currentMission->getDirectory()=="andalucia") {
				setDrawCursor(false);
				setStatusScene(SCENE_GAME_ENDANIMATION);
			} else {
				setStatusScene(SCENE_GAME_FINISH);
			}
		}
	}
}

void SceneGame::setAnimationEnd (string a) { 
	animationEnd = true; 
	s_animend = new SceneAnimation();
	s_animend->setId(5);
	s_animend->setWorld((World*)this);
	s_animend->setDirectory(a);
	s_animend->setNameSceneWhenScape("infotown");
	s_animend->setDrawCursor(false);
}

SceneGame::~SceneGame() {
	unLoad();
}

void SceneGame::setStatusScene(int s) {
     statusScene = s;
	 Board::GetInstance()->beginAnimationWaiting();
     switch(statusScene) {
        case SCENE_GAME_MAIN:
			if (!getMusicGame()->playing()) {
				getMusicGame()->play(1, -1, 2000);
			}
        break;
        case SCENE_GAME_CAPTURED:
        case SCENE_GAME_WINNING:
            getMusicGame()->stop(2000);
			Sounds::GetInstance()->getSound("eating")->stop();
        break;
		case SCENE_GAME_WIN:
			windowWin->setCurrentScale(0);
			windowWin->setScaleFlexible(windowWin->getWidthOriginal(), windowWin->getHeightOriginal());
			textInWindows->setCurrentFrame(0);
			textInWindows->setFadeIn(1000);
			frameUp->setY(-150);
			frameUp->setMovementSmoothY(0);
			frameDown->setY(800);
			frameDown->setMovementSmoothY(600);
			Sounds::GetInstance()->getSound("windows_win")->play(8, 0);
		break;
		case SCENE_GAME_LOST:
			windowLost->setCurrentScale(0);
			windowLost->setScaleFlexible(windowLost->getWidthOriginal(), windowLost->getHeightOriginal());
			textInWindows->setCurrentFrame(1);
			textInWindows->setFadeIn(1000);
			frameUp->setY(-150);
			frameUp->setMovementSmoothY(0);
			frameDown->setY(800);
			frameDown->setMovementSmoothY(600);
			Sounds::GetInstance()->getSound("windows_captured")->play(8, 0);
		break;	
		case SCENE_GAME_TRAY:
			bAcceptInfo->setY(421);
			bgInfo->setCurrentScale(0);
			bgInfo->setScaleFlexible(bgInfo->getWidthOriginal(), bgInfo->getHeightOriginal());
			frameUp->setY(-150);
			frameUp->setMovementSmoothY(0);
			frameDown->setY(800);
			frameDown->setMovementSmoothY(600);
		break;
		case SCENE_GAME_HELP:
			bAcceptInfo->setY(421);
			bgInfo->setCurrentScale(0);
			bgInfo->setScaleFlexible(bgInfo->getWidthOriginal(), bgInfo->getHeightOriginal());
			frameUp->setY(-150);
			frameUp->setMovementSmoothY(0);
			frameDown->setY(800);
			frameDown->setMovementSmoothY(600);
		break;
		case SCENE_GAME_FINISH:
			windowFinish->setCurrentScale(0);
			windowFinish->setScaleFlexible(windowFinish->getWidthOriginal(), windowFinish->getHeightOriginal());
			textInWindowsFinal->setFadeIn(1000);
		break;	
		case SCENE_GAME_HELPFIRSTLEVEL:
			bAcceptInfo->setY(490);
		break;	
	 }
}

void SceneGame::loadMusic(int t) {
	if (Sounds::GetInstance()->existSound("musicgame")) {
		Sounds::GetInstance()->getSound("musicgame")->stop();
		Sounds::GetInstance()->getSound("musicgame")->unLoad();
		Sounds::GetInstance()->removeSound("musicgame");
	}
	
	bool todo = true;
	
	if ( Missions::GetInstance()->currentLevel->existFile("music.ogg") ) {
        todo = false;
        Sounds::GetInstance()->addSound("musicgame", "musicgame", Missions::GetInstance()->currentLevel->getPath() + "/music.ogg");
        Board::GetInstance()->musicOfLevel = true;
        if (!Sounds::GetInstance()->existSound("musicgame")) {
            todo = true;
        }
    }
    
    if (todo) {
    	setTypeMusic(t);
    	char tmp[8];
    	sprintf (tmp, "%d", t);
    	Options::GetInstance()->setValue("musicgame", tmp);
    	Options::GetInstance()->save();
    	
    	sprintf(tmp, "game%d", t);
    	Sounds::GetInstance()->addSoundFromData("musicgame", "musicgame", "sound/"+(string)tmp+".ogg");
    	Board::GetInstance()->musicOfLevel = false;
    }
}

void SceneGame::verifyEyeInformation() {
	string dirL = Missions::GetInstance()->currentLevel->getPath() + "/eyeleft";
	string dirR = Missions::GetInstance()->currentLevel->getPath() + "/eyeright";
	
	DIR *pdir;
	struct dirent *pent;
	
	if ( WorkingData::GetInstance()->existFile(dirL) && WorkingData::GetInstance()->existFile(dirR) ) {
		
		hasEyeInformation = true;
		
		pdir=opendir(dirR.c_str());
		
		if (pdir) {
			while ((pent=readdir(pdir))) {
				 string ext = WorkingData::GetInstance()->getExtension(pent->d_name);
				 if ( ext == "PNG" ) {
					imageEyeRight->addFrameFile(dirR+"/"+pent->d_name);
				 }
			}
			closedir(pdir);
		}
		
		pdir=opendir(dirL.c_str());
		
		if (pdir) {
			while ((pent=readdir(pdir))) {
				 string ext = WorkingData::GetInstance()->getExtension(pent->d_name);
				 if ( ext == "PNG" ) {
					imageEyeLeft->addFrameFile(dirL+"/"+pent->d_name);
				 }
			}
			closedir(pdir);
		}
		
		
	}
	
}

void SceneGame::createHelpFirstLevel() {
	
	hasHelpFirstLevel = true;
	helpFirstLevel = new Slide();
	helpFirstLevel->setTypeSlide(TYPESLIDE_ROTATE);
	helpFirstLevel->setX(400);
	helpFirstLevel->setY(280);
	
	helpFirstLevel->addFrameFileFromData(Language::GetInstance()->getFilename("/help/sol_level1_0", "jpg"));
	helpFirstLevel->addFrameFileFromData(Language::GetInstance()->getFilename("/help/sol_level1_1", "jpg"));
	helpFirstLevel->addFrameFileFromData(Language::GetInstance()->getFilename("/help/sol_level1_2", "jpg"));
	helpFirstLevel->addFrameFileFromData(Language::GetInstance()->getFilename("/help/sol_level1_3", "jpg"));
	helpFirstLevel->addFrameFileFromData(Language::GetInstance()->getFilename("/help/sol_level1_4", "jpg"));
	
	bRightFirstLevel = new Button();
	bRightFirstLevel->setXY(670, 260);
	bRightFirstLevel->setSoundClick("beep1");
	bRightFirstLevel->setFlip(true);
	bRightFirstLevel->setScales(1.0, 1.05);
	bRightFirstLevel->setVAlign(VALIGN_CENTER);
	
	bRightFirstLevel->imageOut(WorkingSurfaces::GetInstance()->surfaceFromImage((string)DATA_DIR + "/createmissions/bleft_on.png"));
	bRightFirstLevel->imageOff(WorkingSurfaces::GetInstance()->surfaceFromImage((string)DATA_DIR + "/createmissions/bleft_off.png"));
	bRightFirstLevel->setAnimation("out");
	
	bLeftFirstLevel = new Button();
	bLeftFirstLevel->setXY(130, 260);
	bLeftFirstLevel->setSoundClick("beep1");
	bLeftFirstLevel->setScales(1.0, 1.05);
	bLeftFirstLevel->setVAlign(VALIGN_CENTER);
	bLeftFirstLevel->setAlign(ALIGN_RIGHT);
	
	bLeftFirstLevel->imageOut(WorkingSurfaces::GetInstance()->surfaceFromImage((string)DATA_DIR + "/createmissions/bleft_on.png"));
	bLeftFirstLevel->imageOff(WorkingSurfaces::GetInstance()->surfaceFromImage((string)DATA_DIR + "/createmissions/bleft_off.png"));
	bLeftFirstLevel->setAnimation("out");
	
}

void SceneGame::load() {
	
	initialize();
	
	hasEyeInformation = false;
	hasHelp = false;
	
	char tmp[128];
	
	ProgressBar *pb = new ProgressBar(5, 200, 16, 255, 255, 255);

	pb->setBg((string)DATA_DIR + "/title.png");
	pb->setBgBar((string)DATA_DIR + "/bg_barprogress.png");
    pb->setPositionBar(World::width/2, 300);
	pb->setText("font-texts", Language::GetInstance()->getText("loading_sounds"));
	pb->draw();

	Sounds::GetInstance()->addSoundFromData("steps_nimuh", "effect", "sound/steps_nimuh.ogg");
	Sounds::GetInstance()->addSoundFromData("steps_enemy1", "effect", "sound/steps_enemy1.ogg");
	Sounds::GetInstance()->addSoundFromData("steps_enemy2", "effect", "sound/steps_enemy2.ogg");
	Sounds::GetInstance()->addSoundFromData("steps_enemy3", "effect", "sound/steps_enemy3.ogg");
	Sounds::GetInstance()->addSoundFromData("teletransport", "effect", "sound/teletransport.ogg");
	Sounds::GetInstance()->addSoundFromData("blackhole_in", "effect", "sound/blackhole_in.ogg");
	Sounds::GetInstance()->addSoundFromData("blackhole_out", "effect", "sound/blackhole_out.ogg");
	Sounds::GetInstance()->addSoundFromData("doorkey", "effect", "sound/doorkey.ogg");
	Sounds::GetInstance()->addSoundFromData("pop", "effect", "sound/pop.ogg");
	Sounds::GetInstance()->addSoundFromData("colision", "effect", "sound/colision.ogg");
	Sounds::GetInstance()->addSoundFromData("eating", "low_effect", "sound/eating.ogg");
	Sounds::GetInstance()->addSoundFromData("out_door", "effect", "sound/out_door.ogg");
	Sounds::GetInstance()->addSoundFromData("windows_captured", "music", "sound/windows_captured.ogg");
	Sounds::GetInstance()->addSoundFromData("windows_win", "music", "sound/windows_win.ogg");
	Sounds::GetInstance()->addSoundFromData("open_tray", "music", "sound/open_tray.ogg");
	Sounds::GetInstance()->addSoundFromData("menubar", "effect", "sound/menubar.ogg");
	Sounds::GetInstance()->addSoundFromData("open_eye", "effect", "sound/open_eye.ogg");
	Sounds::GetInstance()->addSoundFromData("nimuh_scratch", "effect", "sound/nimuh_scratch.ogg");
	Sounds::GetInstance()->addSoundFromData("nimuh_clean", "effect", "sound/nimuh_clean.ogg");
	Sounds::GetInstance()->addSoundFromData("enemy1_impatient", "effect", "sound/enemy1_impatient.ogg");
	Sounds::GetInstance()->addSoundFromData("enemy1_proud", "effect", "sound/enemy1_proud.ogg");
	Sounds::GetInstance()->addSoundFromData("enemy2_cazzo", "effect", "sound/enemy2_cazzo.ogg");
	Sounds::GetInstance()->addSoundFromData("enemy2_peeing", "effect", "sound/enemy2_peeing.ogg");
	Sounds::GetInstance()->addSoundFromData("gun", "effect", "sound/gun.ogg");
	Sounds::GetInstance()->addSoundFromData("jail", "effect", "sound/jail.ogg");
	Sounds::GetInstance()->addSoundFromData("crying", "low_effect", "sound/crying.ogg");
	
	pb->setText("font-texts", Language::GetInstance()->getText("loading_menu"));
	pb->draw();

	menu = new Group();
	menu->setY(379);
	
	bgMenu = new Element();
	bgMenu->addFrameFileFromData("/menu/bg.png");
	
	menu->addElement(bgMenu);
	getGroupScene()->addElement(bgMenu);
	
	bNext = new Button();	
	bNext->setSoundOn("click0");
	bNext->setAlign(ALIGN_CENTER);
	bNext->setVAlign(VALIGN_CENTER);
	bNext->setX(472);
	bNext->setY(175);
	
	bNext->imageOut(WorkingSurfaces::GetInstance()->surfaceFromImage((string)DATA_DIR + "/menu/b_next_off.png"));
	bNext->imageOn(WorkingSurfaces::GetInstance()->surfaceFromImage((string)DATA_DIR + "/menu/b_next_on.png"));
	bNext->setAnimation("out");
	
	bNext->OnClick = bNext_SceneGame_OnClick;
	
	menu->addElement((Element*)bNext);

	getGroupScene()->addElement(bNext);
	
	bPrevious = new Button();
	bPrevious->setSoundOn("click0");
	bPrevious->setAlign(ALIGN_CENTER);
	bPrevious->setVAlign(VALIGN_CENTER);
	bPrevious->setX(321);
	bPrevious->setY(176);
	
	bPrevious->imageOut(WorkingSurfaces::GetInstance()->surfaceFromImage((string)DATA_DIR + "/menu/b_previous_off.png"));
	bPrevious->imageOn(WorkingSurfaces::GetInstance()->surfaceFromImage((string)DATA_DIR + "/menu/b_previous_on.png"));
	bPrevious->setAnimation("out");
	
	bPrevious->OnClick = bPrevious_SceneGame_OnClick;
	
	menu->addElement((Element*)bPrevious);

	getGroupScene()->addElement(bPrevious);
	
	bReset = new Button();
	bReset->setSoundOn("click0");
	bReset->setAlign(ALIGN_CENTER);
	bReset->setVAlign(VALIGN_CENTER);
	bReset->setX(369);
	bReset->setY(199);
	
	bReset->imageOut(WorkingSurfaces::GetInstance()->surfaceFromImage((string)DATA_DIR + "/menu/" + Language::GetInstance()->getFilename("b_reset_off", "png")));
	bReset->imageOn(WorkingSurfaces::GetInstance()->surfaceFromImage((string)DATA_DIR + "/menu/" + Language::GetInstance()->getFilename("b_reset_on", "png")));
	bReset->setAnimation("out");
	
	bReset->OnClick = bReset_SceneGame_OnClick;
	
	menu->addElement((Element*)bReset);

	getGroupScene()->addElement(bReset);
	
	bOption = new Button();
	bOption->setSoundOn("click0");
	bOption->setAlign(ALIGN_CENTER);
	bOption->setVAlign(VALIGN_CENTER);
	bOption->setX(397);
	bOption->setY(171);
	
	bOption->imageOut(WorkingSurfaces::GetInstance()->surfaceFromImage((string)DATA_DIR + "/menu/" + Language::GetInstance()->getFilename("b_options_off", "png")));
	bOption->imageOn(WorkingSurfaces::GetInstance()->surfaceFromImage((string)DATA_DIR + "/menu/" + Language::GetInstance()->getFilename("b_options_on", "png")));
	bOption->setAnimation("out");
	
	bOption->OnClick = bOption_SceneGame_OnClick;
	
	menu->addElement((Element*)bOption);

	getGroupScene()->addElement(bOption);

	bQuit = new Button();
	bQuit->setSoundOn("click0");
	bQuit->setAlign(ALIGN_CENTER);
	bQuit->setVAlign(VALIGN_CENTER);
	bQuit->setX(423);
	bQuit->setY(196);
	
	bQuit->imageOut(WorkingSurfaces::GetInstance()->surfaceFromImage((string)DATA_DIR + "/menu/" + Language::GetInstance()->getFilename("b_quit_off", "png")));
	bQuit->imageOn(WorkingSurfaces::GetInstance()->surfaceFromImage((string)DATA_DIR + "/menu/" + Language::GetInstance()->getFilename("b_quit_on", "png")));
	bQuit->setAnimation("out");
	
	bQuit->OnClick = bQuit_SceneGame_OnClick;
	
	menu->addElement((Element*)bQuit);

	getGroupScene()->addElement(bQuit);
	
	eyeLeft = new AnimatedElement();
	eyeLeft->setAlign(ALIGN_CENTER);
	eyeLeft->setVAlign(VALIGN_CENTER);
	eyeLeft->addRangeFramesFromData("menu/eye_left", "png", 0, 4);
	eyeLeft->setXY(75, 86);
	menu->addElement((Element*)eyeLeft);
	
	imageEyeLeft = new Slide();
	imageEyeLeft->setXY(75, 86);
	imageEyeLeft->setAlign(ALIGN_CENTER);
	imageEyeLeft->setVAlign(VALIGN_CENTER);
	imageEyeLeft->setTimeNextFrame(15000);
	menu->addElement((Element*)imageEyeLeft);
	
	eyeRight = new AnimatedElement();
	eyeRight->setAlign(ALIGN_CENTER);
	eyeRight->setVAlign(VALIGN_CENTER);
	eyeRight->addRangeFramesFromData("menu/eye_right", "png", 0, 4);
	eyeRight->setXY(724, 88);
	menu->addElement((Element*)eyeRight);
	
	imageEyeRight = new Slide();
	imageEyeRight->setXY(724, 88);
	imageEyeRight->setAlign(ALIGN_CENTER);
	imageEyeRight->setVAlign(VALIGN_CENTER);
	imageEyeRight->setTimeNextFrame(15000);
	menu->addElement((Element*)imageEyeRight);
	
	verifyEyeInformation();
	
	levelStatus = new Element();
	//levelStatus->setCurrentScale(0.5);
	levelStatus->setAlign(ALIGN_CENTER);
	levelStatus->setVAlign(VALIGN_CENTER);
	sprintf(tmp, "%d/%d", Users::GetInstance()->getCurrentUser()->getLevelInCurrentMission()+1, Missions::GetInstance()->currentMission->getNLevels());
	levelStatus->addFrameText("font-texts", tmp, ALIGN_CENTER);
	levelStatus->setXY(215, 140);
	menu->addElement(levelStatus);
	
	chronometer = new ChronometerElement("game", "font-texts");
	//chronometer->setCurrentScale(0.4);
	chronometer->setXY(564, 139);
	chronometer->setSeconds(0);
	menu->addGroup(chronometer);
	
	Animation a;
	a.setName("open");
	a.setCyclesBetweenFrames(6);
	a.addRangeFrame(0, 4, 1);
	eyeRight->addAnimation(a);
	eyeLeft->addAnimation(a);
	
	Animation b;
	b.setName("close");
	b.setCyclesBetweenFrames(6);
	b.addRangeFrame(4, 0, -1);
	eyeRight->addAnimation(b);
	eyeLeft->addAnimation(b);
	
	Animation c;
	c.setName("closed");
	c.addFrame(0);
	eyeRight->addAnimation(c);
	eyeLeft->addAnimation(c);
	
	Animation d;
	d.setName("opened");
	d.addFrame(4);
	eyeRight->addAnimation(d);
	eyeLeft->addAnimation(d);
	
	//eyeLeft->setForceAnimation("open", 1);
	//eyeRight->setForceAnimation("open", 1);
	eyeRight->setForceAnimation("closed");
	eyeLeft->setForceAnimation("closed");
	
	pb->setText("font-texts", Language::GetInstance()->getText("loading_titles"));
	pb->draw();
		
	windowFinish = new Element();	
	windowFinish->setAlign(ALIGN_CENTER);
	windowFinish->setVAlign(VALIGN_CENTER);
	windowFinish->setXY(World::width/2, 250);
	windowFinish->addFrameSurface(WorkingSurfaces::GetInstance()->surfaceFromImage((string)DATA_DIR + "/windows/" + Language::GetInstance()->getFilename("congratulations", "png")));
			
	windowLost = new Element();	
	windowLost->setAlign(ALIGN_CENTER);
	windowLost->setVAlign(VALIGN_CENTER);
	windowLost->setXY(World::width/2, 250);
	windowLost->addFrameSurface(WorkingSurfaces::GetInstance()->surfaceFromImage((string)DATA_DIR + "/windows/" + Language::GetInstance()->getFilename("captured", "png")));
	
	windowWin = new Element();	
	windowWin->setAlign(ALIGN_CENTER);
	windowWin->setVAlign(VALIGN_CENTER);
	windowWin->setXY(World::width/2, 250);
	windowWin->addFrameSurface(WorkingSurfaces::GetInstance()->surfaceFromImage((string)DATA_DIR + "/windows/" + Language::GetInstance()->getFilename("completed", "png")));
	
	textInWindows = new Element();	
	textInWindows->setCurrentScale(0.37);
	textInWindows->setXY(360, 240);
	
	textInWindows->addFrameLanguage("font-computer", "txt_win", ALIGN_LEFT);
	textInWindows->addFrameLanguage("font-computer", "txt_lost", ALIGN_LEFT);
	
	textInWindowsFinal = new Element();	
	textInWindowsFinal->setAlign(ALIGN_CENTER);
	textInWindowsFinal->setCurrentScale(0.41);
	textInWindowsFinal->setRGB(190, 195, 53);
	textInWindowsFinal->setXY(399, 265);
		
	textInWindowsFinal->addFrameLanguage("font-computer", "txt_final", ALIGN_CENTER);
	
	bRetry = new Button();
	bRetry->setScales(0.40, 0.42);
	bRetry->setAlign(ALIGN_CENTER);
	bRetry->setVAlign(VALIGN_CENTER);
	bRetry->setX(265);
	bRetry->setY(375);
	bRetry->setRGB(0,255,0);

	bRetry->imageOut(Fonts::GetInstance()->getSurface_TextBitMap("font-computer", ALIGN_CENTER, Language::GetInstance()->getText("retry")));
	bRetry->setAnimation("out");
	
	bRetry->OnClick = bRetry_SceneGame_OnClick;
	
	getGroupScene()->addElement((Element*)bRetry);
	
	bContinue = new Button();
	bContinue->setScales(0.40, 0.42);
	bContinue->setAlign(ALIGN_CENTER);
	bContinue->setVAlign(VALIGN_CENTER);
	bContinue->setX(265);
	bContinue->setY(375);
	bContinue->setRGB(0,255,0);

	bContinue->imageOut(Fonts::GetInstance()->getSurface_TextBitMap("font-computer", ALIGN_CENTER, Language::GetInstance()->getText("continue")));
	bContinue->setAnimation("out");
	
	bContinue->OnClick = bContinue_SceneGame_OnClick;
	
	getGroupScene()->addElement((Element*)bContinue);
	
	bLeave = new Button();
	bLeave->setScales(0.40, 0.42);
	bLeave->setAlign(ALIGN_CENTER);
	bLeave->setVAlign(VALIGN_CENTER);
	bLeave->setX(540);
	bLeave->setY(375);
	bLeave->setRGB(255,0,0);

	bLeave->imageOut(Fonts::GetInstance()->getSurface_TextBitMap("font-computer", ALIGN_CENTER, Language::GetInstance()->getText("leave")));
	bLeave->setAnimation("out");
	
	bLeave->OnClick = bLeave_SceneGame_OnClick;
	
	getGroupScene()->addElement((Element*)bLeave);
	
	bBack = new Button();
	bBack->setScales(0.37, 0.40);
	bBack->setAlign(ALIGN_CENTER);
	bBack->setVAlign(VALIGN_CENTER);
	bBack->setX(399);
	bBack->setY(387);
	bBack->setRGB(0,255,0);

	bBack->imageOut(Fonts::GetInstance()->getSurface_TextBitMap("font-computer", ALIGN_CENTER, Language::GetInstance()->getText("backmenu")));
	bBack->setAnimation("out");
	
	bBack->OnClick = bBack_SceneGame_OnClick;
	
	getGroupScene()->addElement((Element*)bBack);
	
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
		
	pb->setText("font-texts", Language::GetInstance()->getText("loading_options"));
	pb->draw();
	
	bgOptions = new Element();
	bgOptions->setAlign(ALIGN_CENTER);
	bgOptions->setVAlign(VALIGN_CENTER);
	bgOptions->setXY(World::width/2, 250);
	bgOptions->addFrameFileFromData("/windows/" + Language::GetInstance()->getFilename("options", "png"));
	
	titleVolumeMusics = new Element();
	titleVolumeMusics->setAlign(ALIGN_CENTER);
	titleVolumeMusics->setVAlign(VALIGN_CENTER);
	titleVolumeMusics->setX(270);
	titleVolumeMusics->setY(230);

	titleVolumeMusics->addFrameLanguage("font-texts", "volumemusic", ALIGN_CENTER);
	
	getGroupScene()->addElement(titleVolumeMusics);
	
	titleVolumeEffects = new Element();
	titleVolumeEffects->setAlign(ALIGN_CENTER);
	titleVolumeEffects->setVAlign(VALIGN_CENTER);
	titleVolumeEffects->setX(270);
	titleVolumeEffects->setY(300);

	titleVolumeEffects->addFrameLanguage("font-texts", "volumeeffects", ALIGN_CENTER);
	
	getGroupScene()->addElement(titleVolumeEffects);
	
	titleTypeMusic = new Element();
	titleTypeMusic->setVAlign(VALIGN_CENTER);
	titleTypeMusic->setAlign(ALIGN_CENTER);
	titleTypeMusic->setX(530);
	titleTypeMusic->setY(300);

	titleTypeMusic->addFrameLanguage("font-texts", "typemusic", ALIGN_CENTER);
	
	getGroupScene()->addElement(titleTypeMusic);
	
	volumeMusics = new SelectButton();
	volumeMusics->setX(175);
	volumeMusics->setY(260);
	//volumeMusics->OnClick = volumeMusics_SceneEditGame_OnClick;
	
	volumeEffects = new SelectButton();
	volumeEffects->setX(175);
	volumeEffects->setY(330);
	//volumeMusics->OnClick = volumeMusics_SceneEditGame_OnClick;

	int i;

	for (i=0; i<NVOLUMES; i++) {
		sprintf(tmp, "%s/interface/sound%d.png", DATA_DIR, i);
		volumeMusics->addObject(WorkingSurfaces::GetInstance()->surfaceFromImage(tmp));
		sprintf(tmp, "%s/interface/fx%d.png", DATA_DIR, i);
		volumeEffects->addObject(WorkingSurfaces::GetInstance()->surfaceFromImage(tmp));
	}
	
	volumeMusics->setFrame(Options::GetInstance()->getValueToInt("music"));
	volumeEffects->setFrame(Options::GetInstance()->getValueToInt("effects"));
	
	cbHelpActived = new CheckButton("font-texts", Language::GetInstance()->getText("activehelp"));
	cbHelpActived->setX(425);
	cbHelpActived->setY(230);
	
	cbHelpActived->imageActive(WorkingSurfaces::GetInstance()->surfaceFromImage((string)DATA_DIR + "/interface/rad_on.png"));
	cbHelpActived->imageInactive(WorkingSurfaces::GetInstance()->surfaceFromImage((string)DATA_DIR + "/interface/rad_off.png"));
	
	if (Options::GetInstance()->getValue("helpactived") == "true")
		cbHelpActived->setActive(true);
	
	getGroupScene()->addGroup(cbHelpActived);
		
	typeMusic = new SelectButton();
	typeMusic->setX(470);
	typeMusic->setY(330);
	
	for (i=0; i<BoardInfo::GetInstance()->getValueToInt("NTYPES_MUSICGAME"); i++) {
		sprintf(tmp, "%s %d", Language::GetInstance()->getText("type").c_str(), i+1);
		typeMusic->addObject(Fonts::GetInstance()->getSurface_TextBitMap("font-texts", ALIGN_CENTER, tmp));
	}
	
	//typeMusic->setFrame(Options::GetInstance()->getValueToInt("musicgame"));
	
	
	volumeMusics->setArrows(WorkingSurfaces::GetInstance()->surfaceFromImage((string)DATA_DIR+"/windows/arrow_left.png"), WorkingSurfaces::GetInstance()->surfaceFromImage((string)DATA_DIR+"/windows/arrow_right.png"));
	volumeEffects->setArrows(WorkingSurfaces::GetInstance()->surfaceFromImage((string)DATA_DIR+"/windows/arrow_left.png"), WorkingSurfaces::GetInstance()->surfaceFromImage((string)DATA_DIR+"/windows/arrow_right.png"));
	typeMusic->setArrows(WorkingSurfaces::GetInstance()->surfaceFromImage((string)DATA_DIR+"/windows/arrow_left.png"), WorkingSurfaces::GetInstance()->surfaceFromImage((string)DATA_DIR+"/windows/arrow_right.png"));
	
	getGroupScene()->addGroup(volumeMusics);
	getGroupScene()->addGroup(volumeEffects);
	
	bAccept = new Button();
	bAccept->setScales(0.4, 0.45);
	bAccept->setAlign(ALIGN_CENTER);
	bAccept->setVAlign(VALIGN_CENTER);
	bAccept->setX(265);
	bAccept->setY(382);
	bAccept->setRGB(0, 255, 0);

	bAccept->OnClick = bAccept_SceneGame_OnClick;
	
	sprintf(tmp, Language::GetInstance()->getText("accept").c_str());
	bAccept->imageOut(Fonts::GetInstance()->getSurface_TextBitMap("font-computer", ALIGN_CENTER, tmp));
	bAccept->setAnimation("out");
	
	getGroupScene()->addElement(bAccept);

	bCancel = new Button();
	bCancel->setScales(0.4, 0.45);
	bCancel->setAlign(ALIGN_CENTER);
	bCancel->setVAlign(VALIGN_CENTER);
	bCancel->setX(540);
	bCancel->setY(382);
	bCancel->setRGB(255, 0, 0);
	
	bCancel->OnClick = bCancel_SceneGame_OnClick;
	
	sprintf(tmp, Language::GetInstance()->getText("cancel").c_str());
	bCancel->imageOut(Fonts::GetInstance()->getSurface_TextBitMap("font-computer", ALIGN_CENTER, tmp));
	bCancel->setAnimation("out");
	
	getGroupScene()->addElement(bCancel);
	
	bgInfo = new Element();
	bgInfo->setAlign(ALIGN_CENTER);
	bgInfo->setVAlign(VALIGN_CENTER);
	bgInfo->setXY(World::width/2, 250);
	bgInfo->addFrameFileFromData("/windows/" + Language::GetInstance()->getFilename("info", "png"));
	
	
	bAcceptInfo = new Button();
	bAcceptInfo->setScales(0.4, 0.45);
	bAcceptInfo->setAlign(ALIGN_CENTER);
	bAcceptInfo->setVAlign(VALIGN_CENTER);
	bAcceptInfo->setX(400);
	bAcceptInfo->setY(421);
	bAcceptInfo->setRGB(0, 255, 0);

	bAcceptInfo->OnClick = bAcceptInfo_SceneGame_OnClick;
	
	sprintf(tmp, Language::GetInstance()->getText("accept").c_str());
	bAcceptInfo->imageOut(Fonts::GetInstance()->getSurface_TextBitMap("font-computer", ALIGN_CENTER, tmp));
	bAcceptInfo->setAnimation("out");
	
	getGroupScene()->addElement(bAcceptInfo);
		
	pb->setText("font-texts", Language::GetInstance()->getText("loading_board"));
	pb->draw();

	imageHelp = new Element();
	imageHelp->setXY(200, 300);
	imageHelp->setAlign(ALIGN_CENTER);
	imageHelp->setVAlign(VALIGN_CENTER);
	
	imageHelp->addFrameSurface(Primitives::GetInstance()->rectangle(1, 1, 0, 0, 0));
	
	titleHelp = new Element();
	titleHelp->setRGB(234, 238, 53);
	titleHelp->setXY(480, 218);
	titleHelp->setCurrentScale(0.40);
	titleHelp->setAlign(ALIGN_CENTER);
	titleHelp->setVAlign(VALIGN_CENTER);
	
	titleHelp->addFrameSurface(Primitives::GetInstance()->rectangle(1, 1, 0, 0, 0));
	
	textHelp = new Element();
	textHelp->setXY(310, 255);
	textHelp->setCurrentScale(0.90);
	
	textHelp->addFrameSurface(Primitives::GetInstance()->rectangle(1, 1, 0, 0, 0));
	
	loadMusic(getTypeMusic ());

	Board::GetInstance()->setSceneGame(this);
	Board::GetInstance()->load();
	clear();
	Board::GetInstance()->loadLevel();
			
	nameProvince = new MarqueeElement();
	nameProvince->setAlign(ALIGN_CENTER);
	nameProvince->setVAlign(VALIGN_CENTER);
	nameProvince->setText("font-computer", Board::GetInstance()->town.province, 10);
	nameProvince->setXY(101, 192);
	nameProvince->setCurrentScale(0.45);
	
	menu->addElement((Element*)nameProvince);
	
	nameTown = new MarqueeElement();
	nameTown->setAlign(ALIGN_CENTER);
	nameTown->setVAlign(VALIGN_CENTER);
	nameTown->setText("font-computer", Board::GetInstance()->town.name, 10);
	nameTown->setXY(701, 192);
	nameTown->setCurrentScale(0.45);
	
	menu->addElement((Element*)nameTown);
	
	titleInfoTray = new Element();
	titleInfoTray->setRGB(234, 238, 53);
	titleInfoTray->setXY(480, 218);
	titleInfoTray->setCurrentScale(0.40);
	titleInfoTray->setAlign(ALIGN_CENTER);
	titleInfoTray->setVAlign(VALIGN_CENTER);
	if (Board::GetInstance()->infoTray.title=="") {
		titleInfoTray->addFrameSurface(Primitives::GetInstance()->rectangle(1, 1, 0, 0, 0));
	} else {
		titleInfoTray->addFrameText("font-computer", Board::GetInstance()->infoTray.title, ALIGN_LEFT);
	}

	textInfoTray = new Element();
	textInfoTray->setXY(310, 255);
	textInfoTray->setCurrentScale(0.90);
	if (Board::GetInstance()->infoTray.text=="") {
		textInfoTray->addFrameSurface(Primitives::GetInstance()->rectangle(1, 1, 0, 0, 0));
	} else {
		textInfoTray->addFrameText("font-texts", Board::GetInstance()->infoTray.text, ALIGN_LEFT, 340);		
	}
	
	drawFood = new Element();
	drawFood->setXY(200, 300);
	drawFood->setAlign(ALIGN_CENTER);
	drawFood->setVAlign(VALIGN_CENTER);
	string fileFood = Missions::GetInstance()->currentLevel->getPath() +"/food.png";
	if (WorkingData::GetInstance()->existFile(fileFood)) {
		SDL_Surface *sfc = WorkingSurfaces::GetInstance()->surfaceFromImage(fileFood);
		if ( (sfc->h>200) || (sfc->w>200) ) {
			drawFood->addFrameSurface(Primitives::GetInstance()->rectangle(1, 1, 0, 0, 0));
		} else {
			drawFood->addFrameFile(fileFood);
		}
		SDL_FreeSurface(sfc);
	} else {
		drawFood->addFrameSurface(Primitives::GetInstance()->rectangle(1, 1, 0, 0, 0));
	}
	
	getGroupScene()->addGroup(Board::GetInstance());
	
	getMusicGame()->play(1, -1, 2000);
	
	delete pb;
	
}

void SceneGame::clear () {
	
	active = false;
	
	animationEnd = false;
	
	hasHelpFirstLevel = false;
	showedHelpFirstLevel = false;
	
	Sounds::GetInstance()->getSound("eating")->stop();
	
	menu->setY(600);
	
	eyeLeft->setForceAnimation("closed");
	eyeRight->setForceAnimation("closed");
	
	Chronometer::GetInstance()->removeTime("intro_board");
	Chronometer::GetInstance()->setTime("intro_board");
	
	chronometer->stop();
	chronometer->reset();
	
	//Board::GetInstance()->clear();
	
}

void SceneGame::loadHelp (string name) {
	
	hasHelp = true;

	if (name=="enemy1") {
		imageHelp->changeFrameFileFromData(0, "/help/enemy1.png");
		titleHelp->changeFrameLanguage(0, "font-computer", "helpboardtitle_enemy1", ALIGN_LEFT);
		textHelp->changeFrameLanguage(0, "font-texts", "helpboardtext_enemy1", ALIGN_LEFT, 340);
	} else if (name=="enemy2") {
		imageHelp->changeFrameFileFromData(0, "/help/enemy2.png");
		titleHelp->changeFrameLanguage(0, "font-computer", "helpboardtitle_enemy2", ALIGN_LEFT);
		textHelp->changeFrameLanguage(0, "font-texts", "helpboardtext_enemy2", ALIGN_LEFT, 340);
	} else if (name=="enemy3") {
		imageHelp->changeFrameFileFromData(0, "/help/enemy3.png");
		titleHelp->changeFrameLanguage(0, "font-computer", "helpboardtitle_enemy3", ALIGN_LEFT);
		textHelp->changeFrameLanguage(0, "font-texts", "helpboardtext_enemy3", ALIGN_LEFT, 340);
	} else if (name=="tray") {
		imageHelp->changeFrameFileFromData(0, "/help/tray.png");
		titleHelp->changeFrameLanguage(0, "font-computer", "helpboardtitle_tray", ALIGN_LEFT);
		textHelp->changeFrameLanguage(0, "font-texts", "helpboardtext_tray", ALIGN_LEFT, 340);
	} else if (name=="blackhole") {
		imageHelp->changeFrameFileFromData(0, "/help/blackhole.png");	
		titleHelp->changeFrameLanguage(0, "font-computer", "helpboardtitle_blackhole", ALIGN_LEFT);
		textHelp->changeFrameLanguage(0, "font-texts", "helpboardtext_blackhole", ALIGN_LEFT, 340);
	} else if (name=="trap") {
		imageHelp->changeFrameFileFromData(0, "/help/trap.png");
		titleHelp->changeFrameLanguage(0, "font-computer", "helpboardtitle_trap", ALIGN_LEFT);
		textHelp->changeFrameLanguage(0, "font-texts", "helpboardtext_trap", ALIGN_LEFT, 340);
	} else if (name=="key") {
		imageHelp->changeFrameFileFromData(0, "/help/grate.png");
		titleHelp->changeFrameLanguage(0, "font-computer", "helpboardtitle_key", ALIGN_LEFT);
		textHelp->changeFrameLanguage(0, "font-texts", "helpboardtext_key", ALIGN_LEFT, 340);
	} else if (name=="helpfirstlevel") {
		imageHelp->changeFrameFileFromData(0, "/help/help.png");
		titleHelp->changeFrameLanguage(0, "font-computer", "helpboardtitle_helpfirstlevel", ALIGN_LEFT);
		textHelp->changeFrameLanguage(0, "font-texts", "helpboardtext_helpfirstlevel", ALIGN_LEFT, 340);
	}
	
	
}

/**********************
  DRAWSCENE MAIN
**********************/

void SceneGame::drawSceneMain () {
	
	if (!active) {
		if ( Chronometer::GetInstance()->verifyTime("intro_board", 3000) ) {
			menu->setMovementNormalY(379, 700);
			Sounds::GetInstance()->getSound("menubar")->play(6, 0);
		}
		if (hasEyeInformation) {
			if ( Chronometer::GetInstance()->verifyTime("intro_board", 4000) ) {
				eyeLeft->setForceAnimation("open", 1);
				eyeRight->setForceAnimation("open", 1);
				Sounds::GetInstance()->getSound("open_eye")->play(5, 0);
			}
		}
		if ( Chronometer::GetInstance()->verifyTime("intro_board", 5000) ) {
			if ( (hasHelp) && (Options::GetInstance()->getValue("helpactived")=="true") ) {
				setSaveImage(true);
				setStatusScene(SCENE_GAME_HELP);
			}
			chronometer->play();
			active = true;
        }
	}
	
	if ( (chronometer->getSeconds()>120) && hasHelpFirstLevel && !showedHelpFirstLevel) {
		showedHelpFirstLevel = true;
		loadHelp("helpfirstlevel");
		setStatusScene(SCENE_GAME_HELP);
	}

	if ((statusScene==SCENE_GAME_MAIN || statusScene==SCENE_GAME_STARTTRAY)&& active) {
		verifyOverElements_Main();	
		Board::GetInstance()->stopAnimations();
	}
	
	for (int i=0; i<MAX_INDEXZ; i++) {
		drawSceneMainByIndexZ(i);
	}
	
	if (Board::GetInstance()->todoNextTurn) {
         Board::GetInstance()->todoNextTurn = false;
         Board::GetInstance()->nextTurn();
    }
		
}

void SceneGame::drawSceneMainByIndexZ(int z) {
	if (Board::GetInstance()->getIndexZ() == z) {
		Board::GetInstance()->draw();	
	}
	if (bgMenu->getIndexZ() == z) {
        menu->work();
		bgMenu->draw();
	}
	if (levelStatus->getIndexZ() == z) {
		levelStatus->draw();
	}
	if (chronometer->getIndexZ() == z) {
		chronometer->draw();
	}
	if (hasEyeInformation) {
		if (imageEyeRight->getIndexZ() == z) {
			imageEyeRight->draw();
		}
		if (imageEyeLeft->getIndexZ() == z) {
			imageEyeLeft->draw();
		}
	}
	if (eyeLeft->getIndexZ() == z) {
		eyeLeft->draw();
	}
	if (eyeRight->getIndexZ() == z) {
		eyeRight->draw();
	}
	if (bOption->getIndexZ() == z) {
		bOption->draw();
	}
	if (bNext->getIndexZ() == z) {
		bNext->draw();
	}
	if (bPrevious->getIndexZ() == z) {
		bPrevious->draw();
	}
	if (bReset->getIndexZ() == z) {
		bReset->draw();
	}
	if (bQuit->getIndexZ() == z) {
		bQuit->draw();
	}
	if (nameProvince->getIndexZ() == z) {
		nameProvince->draw();
	}
	if (nameTown->getIndexZ() == z) {
		nameTown->draw();
	}
}

void SceneGame::verifyClickElements_Main() {
	if (bNext->isOnMouseOver()) {
		bNext->OnClick(this, bNext);
		return;
	}
	if (bPrevious->isOnMouseOver()) {
		bPrevious->OnClick(this, bPrevious);
		return;
	}
	if (bOption->isOnMouseOver()) {
		bOption->OnClick(this, bOption);
		return;
	}
	if (bReset->isOnMouseOver()) {
		bReset->OnClick(this, bReset);
		return;
	}
	if (bQuit->isOnMouseOver()) {
		bQuit->OnClick(this, bQuit);
		return;
	}
	Board::GetInstance()->verifyClickOnBoard();
	
}


void SceneGame::verifyOverElements_Main() {
     bReset->onOver();
     bQuit->onOver();
     bOption->onOver();
     bNext->onOver();
     bPrevious->onOver();
}

/**********************
  DRAWSCENE FINISH
**********************/

void SceneGame::drawSceneFinish () {
	
	verifyOverElements_Finish();
	elmImgSave[0]->draw();
	
	for (int i=0; i<MAX_INDEXZ; i++) {
		drawSceneFinishByIndexZ(i);
	}
		
}

void SceneGame::drawSceneFinishByIndexZ(int z) {
	if (frameUp->getIndexZ() == z) {
		frameUp->draw();
	}
	if (frameDown->getIndexZ() == z) {
		frameDown->draw();
	}
	
	if (windowFinish->getIndexZ() == z) {
		windowFinish->draw();
	}
	
	if (textInWindowsFinal->getIndexZ() == z) {
		textInWindowsFinal->draw();
	}
	
	if (bBack->getIndexZ() == z) {
		bBack->draw();
	}
	
}

void SceneGame::verifyClickElements_Finish() {
	if (bBack->isOnMouseOver()) {
		bBack->OnClick(this, bBack);
	}
}

void SceneGame::verifyOverElements_Finish() {
     bBack->onOver();
}


/**********************
  DRAWSCENE WIN
**********************/

void SceneGame::drawSceneWin () {
	
	verifyOverElements_Win();
	elmImgSave[0]->draw();
	
	for (int i=0; i<MAX_INDEXZ; i++) {
		drawSceneWinByIndexZ(i);
	}
		
}

void SceneGame::drawSceneWinByIndexZ(int z) {
	
	if (frameUp->getIndexZ() == z) {
		frameUp->draw();
	}
	if (frameDown->getIndexZ() == z) {
		frameDown->draw();
	}
	
	if (windowWin->getIndexZ() == z) {
		windowWin->draw();
	}
	
	if (textInWindows->getIndexZ() == z) {
		textInWindows->draw();
	}
	
	if (bContinue->getIndexZ() == z) {
		bContinue->draw();
	}
	
	if (bLeave->getIndexZ() == z) {
		bLeave->draw();
	}
	
}

void SceneGame::verifyClickElements_Win() {
	if (bContinue->isOnMouseOver()) {
		bContinue->OnClick(this, bContinue);
	}
	if (bLeave->isOnMouseOver()) {
		bLeave->OnClick(this, bLeave);
	}
}

void SceneGame::verifyOverElements_Win() {
     bLeave->onOver();
     bContinue->onOver();
}

/**********************
  DRAWSCENE LOST
**********************/

void SceneGame::drawSceneLost () {

    verifyOverElements_Lost();
	elmImgSave[0]->draw();
	
	for (int i=0; i<MAX_INDEXZ; i++) {
		drawSceneLostByIndexZ(i);
	}
		
}

void SceneGame::drawSceneLostByIndexZ(int z) {
	if (frameUp->getIndexZ() == z) {
		frameUp->draw();
	}
	if (frameDown->getIndexZ() == z) {
		frameDown->draw();
	}
	
	if (windowLost->getIndexZ() == z) {
		windowLost->draw();
	}
	
	if (textInWindows->getIndexZ() == z) {
		textInWindows->draw();
	}
	
	if (bRetry->getIndexZ() == z) {
		bRetry->draw();
	}
	
	if (bLeave->getIndexZ() == z) {
		bLeave->draw();
	}
	
}

void SceneGame::verifyClickElements_Lost() {
	if (bRetry->isOnMouseOver()) {
		bRetry->OnClick(this, bRetry);
	}
	if (bLeave->isOnMouseOver()) {
		bLeave->OnClick(this, bLeave);
	}
}

void SceneGame::verifyOverElements_Lost() {
     bLeave->onOver();
     bRetry->onOver();
}

/**********************
  DRAWSCENE OPTIONS
**********************/

void SceneGame::drawSceneOptions () {

	verifyOverElements_Options();	
	
	elmImgSave[0]->draw();
	
	for (int i=0; i<MAX_INDEXZ; i++) {
		drawSceneOptionsByIndexZ(i);
	}
		
}

void SceneGame::drawSceneOptionsByIndexZ(int z) {
	if (frameUp->getIndexZ() == z) {
		frameUp->draw();
	}
	if (frameDown->getIndexZ() == z) {
		frameDown->draw();
	}
	if (bgOptions->getIndexZ() == z) {
		bgOptions->draw();
	}
	if (volumeMusics->getIndexZ() == z) {
		volumeMusics->draw();
	}
	if (volumeEffects->getIndexZ() == z) {
		volumeEffects->draw();
	}
	if (typeMusic->getIndexZ() == z) {
		typeMusic->draw();
	}
	if (titleVolumeMusics->getIndexZ() == z) {
		titleVolumeMusics->draw();
	}
	if (titleVolumeEffects->getIndexZ() == z) {
		titleVolumeEffects->draw();
	}
	if (titleTypeMusic->getIndexZ() == z) {
		titleTypeMusic->draw();
	}
	if (cbHelpActived->getIndexZ() == z) {
		cbHelpActived->draw();
	}
	if (bAccept->getIndexZ() == z) {
		bAccept->draw();
	}
	if (bCancel->getIndexZ() == z) {
		bCancel->draw();
	}
}

void SceneGame::verifyClickElements_Options() {
	if (cbHelpActived->isOnMouseOver()) {
		cbHelpActived->swapActive();
	}
	if (bAccept->isOnMouseOver()) {
		bAccept->OnClick(this, bAccept);
	}
	if (bCancel->isOnMouseOver()) {
		bCancel->OnClick(this, bCancel);
	}
	if (volumeMusics->isOnMouseOver()) {
		if (volumeMusics->getOverBottom()==LEFT) {
			volumeMusics->previousFrame();
		}
		if (volumeMusics->getOverBottom()==RIGHT) {
			volumeMusics->nextFrame();
		}
	}
	if (volumeEffects->isOnMouseOver()) {
		if (volumeEffects->getOverBottom()==LEFT) {
			volumeEffects->previousFrame();
		}
		if (volumeEffects->getOverBottom()==RIGHT) {
			volumeEffects->nextFrame();
		}
	}
	if (typeMusic->isOnMouseOver()) {
		if (typeMusic->getOverBottom()==LEFT) {
			typeMusic->previousFrame();
		}
		if (typeMusic->getOverBottom()==RIGHT) {
			typeMusic->nextFrame();
		}
	}
}


void SceneGame::verifyOverElements_Options() {
	bAccept->onOver();
	bCancel->onOver();
}

/**********************
  DRAWSCENE TRAY
**********************/

void SceneGame::drawSceneTray () {

	verifyOverElements_Tray();	
	
	elmImgSave[0]->draw();
	
	for (int i=0; i<MAX_INDEXZ; i++) {
		drawSceneTrayByIndexZ(i);
	}
		
}

void SceneGame::drawSceneTrayByIndexZ(int z) {
	if (frameUp->getIndexZ() == z) {
		frameUp->draw();
	}
	if (frameDown->getIndexZ() == z) {
		frameDown->draw();
	}
	if (bgInfo->getIndexZ() == z) {
		bgInfo->draw();
	}
	if (drawFood->getIndexZ() == z) {
		drawFood->draw();
	}
	if (titleInfoTray->getIndexZ() == z) {
		titleInfoTray->draw();
	}
	if (textInfoTray->getIndexZ() == z) {
		textInfoTray->draw();
	}
	if (bAcceptInfo->getIndexZ() == z) {
		bAcceptInfo->draw();
	}
}

void SceneGame::verifyClickElements_Tray() {
	if (bAcceptInfo->isOnMouseOver()) {
		bAcceptInfo->OnClick(this, bAcceptInfo);
	}
}


void SceneGame::verifyOverElements_Tray() {
	bAcceptInfo->onOver();
}

/**********************
  DRAWSCENE HELP
**********************/

void SceneGame::drawSceneHelp () {

	verifyOverElements_Help();	
	
	elmImgSave[0]->draw();
	
	for (int i=0; i<MAX_INDEXZ; i++) {
		drawSceneHelpByIndexZ(i);
	}
		
}

void SceneGame::drawSceneHelpByIndexZ(int z) {
	if (frameUp->getIndexZ() == z) {
		frameUp->draw();
	}
	if (frameDown->getIndexZ() == z) {
		frameDown->draw();
	}
	if (bgInfo->getIndexZ() == z) {
		bgInfo->draw();
	}
	if (imageHelp->getIndexZ() == z) {
		imageHelp->draw();
	}
	if (titleHelp->getIndexZ() == z) {
		titleHelp->draw();
	}
	if (textHelp->getIndexZ() == z) {
		textHelp->draw();
	}
	if (bAcceptInfo->getIndexZ() == z) {
		bAcceptInfo->draw();
	}
}

void SceneGame::verifyClickElements_Help() {
	if (bAcceptInfo->isOnMouseOver()) {
		bAcceptInfo->OnClick(this, bAcceptInfo);
	}
}


void SceneGame::verifyOverElements_Help() {
	bAcceptInfo->onOver();
}

/**********************
  DRAWSCENE HELPFIRSTLEVEL
**********************/

void SceneGame::drawSceneHelpFirstLevel () {

	verifyOverElements_Help();	
	
	elmImgSave[0]->draw();
	
	for (int i=0; i<MAX_INDEXZ; i++) {
		drawSceneHelpFirstLevelByIndexZ(i);
	}
		
}

void SceneGame::drawSceneHelpFirstLevelByIndexZ(int z) {
	if (frameUp->getIndexZ() == z) {
		frameUp->draw();
	}
	if (frameDown->getIndexZ() == z) {
		frameDown->draw();
	}
	if (helpFirstLevel->getIndexZ() == z) {
		helpFirstLevel->draw();
	}
	if (bLeftFirstLevel->getIndexZ() == z) {
		bLeftFirstLevel->draw();
	}
	if (bRightFirstLevel->getIndexZ() == z) {
		bRightFirstLevel->draw();
	}
	if (bAcceptInfo->getIndexZ() == z) {
		bAcceptInfo->draw();
	}
}

void SceneGame::verifyClickElements_HelpFirstLevel() {
	if (bAcceptInfo->isOnMouseOver()) {
		bAcceptInfo->OnClick(this, bAcceptInfo);
	}
	if (bLeftFirstLevel->isOnMouseOver()) {
		helpFirstLevel->setPreviousFrame();
	}
	if (bRightFirstLevel->isOnMouseOver()) {
		helpFirstLevel->setNextFrame();
	}
}


void SceneGame::verifyOverElements_HelpFirstLevel() {
	bAcceptInfo->onOver();
}


bool SceneGame::drawScene() {
     
	if ( statusScene == SCENE_GAME_ENDANIMATION ) {
		if (!s_animend->getIsLoad()) { s_animend->load(); }
		if (s_animend->drawScene()) {
			string scene=s_animend->getNameSceneWhenScape();
			setDrawCursor(true);
			delete s_animend;
			goToScene(scene, 1000, SCENE_TRANSITION_FADEOUT_SCALEx0);
		}
		return false;
	}
	
	glClear(GL_COLOR_BUFFER_BIT); // | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	
	drawCommonsScene ();
	
	switch(statusScene) {
	
		case SCENE_GAME_MAIN:
			drawSceneMain();
		
			// Comprobando teclas para opciones			
			{ SDL_Event event;
				while ( SDL_PollEvent(&event) ) {
					if ( event.type == SDL_QUIT ) {
						goToScene("quit");
					}
					if (active) {
						if ( event.type == SDL_KEYDOWN ) {
							if ( event.key.keysym.sym == SDLK_ESCAPE ) {
								goToScene("menu");
							}
							if (hasHelpFirstLevel) {
								if ( event.key.keysym.sym == SDLK_h ) {
									setStatusScene(SCENE_GAME_HELPFIRSTLEVEL);
								}	
							}
							if ( event.key.keysym.sym == SDLK_s ) {
								saveScreenShot();
							}
							if ( event.key.keysym.sym == SDLK_UP ) {
								Board::GetInstance()->movePlayer(TILE_UP);
							}
							if ( event.key.keysym.sym == SDLK_DOWN ) {
								Board::GetInstance()->movePlayer(TILE_DOWN);
							}
							if ( event.key.keysym.sym == SDLK_LEFT ) {
								Board::GetInstance()->movePlayer(TILE_LEFT);
							}
							if ( event.key.keysym.sym == SDLK_RIGHT ) {
								Board::GetInstance()->movePlayer(TILE_RIGHT);
							}
							if ( event.key.keysym.sym == SDLK_SPACE ) {
								Board::GetInstance()->movePlayer(TILE_CENTER);
							}
							if ( event.key.keysym.sym == SDLK_p ) {
								Uint8 *keystate = SDL_GetKeyState(NULL);
								if ( keystate[SDLK_RCTRL] && keystate[SDLK_LCTRL] ) {
									Chronometer::GetInstance()->setTime("winning");
									setStatusScene(SCENE_GAME_WINNING);
								}
							}
						}
						
						if ( event.type == SDL_MOUSEBUTTONDOWN ) {
							if ( ( event.button.button == SDL_BUTTON_LEFT ) ) {
								verifyClickElements_Main();
							}
						}
					}
				}
			}
			
		break;
			
		case SCENE_GAME_CAPTURED:
			drawSceneMain();
		
			if (Chronometer::GetInstance()->getTime("captured") > 2000) {
				setSaveImage(true);
				setStatusScene(SCENE_GAME_LOST);
			}
		
			// Comprobando teclas para opciones			
			{ SDL_Event event;
				while ( SDL_PollEvent(&event) ) {
					if ( event.type == SDL_QUIT ) {
						setSaveImage(true);
						setStatusScene(SCENE_GAME_LOST);
					}
					
					if ( event.type == SDL_KEYDOWN ) {
						if ( event.key.keysym.sym == SDLK_ESCAPE ) {
							setSaveImage(true);
							setStatusScene(SCENE_GAME_LOST);
						}
					}
		
				}
			}
			
		break;
			
		case SCENE_GAME_WINNING:
			drawSceneMain();
		
			if (Chronometer::GetInstance()->getTime("winning") > 3000) {
				Users::GetInstance()->getCurrentUser()->addLevelInCurrentMission();
				Users::GetInstance()->save();
				setSaveImage(true);
				setStatusScene(SCENE_GAME_WIN);
			}
		
			// Comprobando teclas para opciones			
			{ SDL_Event event;
				while ( SDL_PollEvent(&event) ) {
					if ( event.type == SDL_QUIT ) {
						setSaveImage(true);
						statusScene = SCENE_GAME_WIN;
					}
					
					if ( event.type == SDL_KEYDOWN ) {
						if ( event.key.keysym.sym == SDLK_ESCAPE ) {
							setSaveImage(true);
							setStatusScene(SCENE_GAME_WIN);
						}
					}
		
				}
			}
			
		break;
			
		case SCENE_GAME_WIN:
			drawSceneWin();
			// Comprobando teclas para opciones			
			{ SDL_Event event;
				while ( SDL_PollEvent(&event) ) {
					
					if ( event.type == SDL_KEYDOWN ) {
						if ( ( event.key.keysym.sym == SDLK_ESCAPE ) ||
							( event.key.keysym.sym == SDLK_RETURN ) ) {
							goToNextLevel();
						}
					}
					
					if ( event.type == SDL_MOUSEBUTTONDOWN ) {
						if ( ( event.button.button == SDL_BUTTON_LEFT ) ) {
							verifyClickElements_Win();
						}
					}
							
				}
			}
			
		break;
			
		case SCENE_GAME_LOST:
			drawSceneLost();
			// Comprobando teclas para opciones			
			{ SDL_Event event;
				while ( SDL_PollEvent(&event) ) {
					
					if ( event.type == SDL_KEYDOWN ) {
						if ( ( event.key.keysym.sym == SDLK_ESCAPE ) ||
							( event.key.keysym.sym == SDLK_RETURN ) ) {
							clear();
							Board::GetInstance()->loadLevel();
							setStatusScene(SCENE_GAME_MAIN);
						}
					}
					
					if ( event.type == SDL_MOUSEBUTTONDOWN ) {
						if ( ( event.button.button == SDL_BUTTON_LEFT ) ) {
							verifyClickElements_Lost();
						}
					}
							
				}
			}
			
		break;
			
		case SCENE_GAME_FINISH:
			drawSceneFinish();
			// Comprobando teclas para opciones			
			{ SDL_Event event;
				while ( SDL_PollEvent(&event) ) {
					
					if ( event.type == SDL_KEYDOWN ) {
						if ( ( event.key.keysym.sym == SDLK_ESCAPE ) ||
							( event.key.keysym.sym == SDLK_RETURN ) ) {
							goToScene("menu", 1000, SCENE_TRANSITION_FADEOUT_SCALEx0);
						}
					}
					
					if ( event.type == SDL_MOUSEBUTTONDOWN ) {
						if ( ( event.button.button == SDL_BUTTON_LEFT ) ) {
							verifyClickElements_Finish();
						}
					}
							
				}
			}
			
		break;

			
		case SCENE_GAME_OPTIONS:
			drawSceneOptions();
			// Comprobando teclas para opciones			
			{ SDL_Event event;
				while ( SDL_PollEvent(&event) ) {
											
					if ( event.type == SDL_KEYDOWN ) {
						if ( event.key.keysym.sym == SDLK_ESCAPE ) {
							setStatusScene(SCENE_GAME_MAIN);
						}
						if ( event.key.keysym.sym == SDLK_s ) {
							saveScreenShot();
						}
					}
					
					if ( event.type == SDL_MOUSEBUTTONDOWN ) {
						if ( ( event.button.button == SDL_BUTTON_LEFT ) ) {
							verifyClickElements_Options();
						}
					}

	
				}
			}
			
		break;
			
		case SCENE_GAME_STARTTRAY:
			drawSceneMain();
			if ( Chronometer::GetInstance()->verifyTime("starttray", 500) ) {
				Board::GetInstance()->tray->setFadeOut(800);
			}
		
			if (Chronometer::GetInstance()->getTime("starttray") > 1500) {
				setSaveImage(true);
				Board::GetInstance()->hasTray = false;
				Board::GetInstance()->tray->setCurrentScale(Board::GetInstance()->getScaleByTypeSize());
				Board::GetInstance()->tray->removeTypeMovement();
				Board::GetInstance()->tray->removeRotation();
				Board::GetInstance()->tray->removeAlpha();
				Board::GetInstance()->tray->show();
				Board::GetInstance()->tray->setPosition(Board::GetInstance()->tray->getPosition());
				setStatusScene(SCENE_GAME_TRAY);
			}
		
			// Comprobando teclas para opciones			
			{ SDL_Event event;
				while ( SDL_PollEvent(&event) ) {
					if ( event.type == SDL_QUIT ) {
						setSaveImage(true);
						Board::GetInstance()->hasTray = false;
						statusScene = SCENE_GAME_TRAY;
					}
					
					if ( event.type == SDL_KEYDOWN ) {
						if ( event.key.keysym.sym == SDLK_ESCAPE ) {
							setSaveImage(true);
							Board::GetInstance()->hasTray = false;
							setStatusScene(SCENE_GAME_TRAY);
						}
					}
		
				}
			}
			
		break;
			
		case SCENE_GAME_TRAY:
			drawSceneTray();
			// Comprobando teclas para opciones			
			{ SDL_Event event;
				while ( SDL_PollEvent(&event) ) {
											
					if ( event.type == SDL_KEYDOWN ) {
						if ( ( event.key.keysym.sym == SDLK_ESCAPE ) ||
							( event.key.keysym.sym == SDLK_RETURN ) ) {
							Sounds::GetInstance()->getSound("eating")->play(9, -1);
							setStatusScene(SCENE_GAME_MAIN);
						}
						if ( event.key.keysym.sym == SDLK_s ) {
							saveScreenShot();
						}
					}
					
					if ( event.type == SDL_MOUSEBUTTONDOWN ) {
						if ( ( event.button.button == SDL_BUTTON_LEFT ) ) {
							verifyClickElements_Tray();
						}
					}

	
				}
			}
			
		break;
			
		case SCENE_GAME_HELP:
			drawSceneHelp();
			// Comprobando teclas para opciones			
			{ SDL_Event event;
				while ( SDL_PollEvent(&event) ) {
											
					if ( event.type == SDL_KEYDOWN ) {
						if ( ( event.key.keysym.sym == SDLK_ESCAPE ) ||
							( event.key.keysym.sym == SDLK_RETURN ) ) {
							setStatusScene(SCENE_GAME_MAIN);
						}
						if ( event.key.keysym.sym == SDLK_s ) {
							saveScreenShot();
						}
					}
					
					if ( event.type == SDL_MOUSEBUTTONDOWN ) {
						if ( ( event.button.button == SDL_BUTTON_LEFT ) ) {
							verifyClickElements_Help();
						}
					}

	
				}
			}
			
		break;
			
		case SCENE_GAME_HELPFIRSTLEVEL:
			drawSceneHelpFirstLevel();
			// Comprobando teclas para opciones			
			{ SDL_Event event;
				while ( SDL_PollEvent(&event) ) {
											
					if ( event.type == SDL_KEYDOWN ) {
						if ( ( event.key.keysym.sym == SDLK_ESCAPE ) ||
							( event.key.keysym.sym == SDLK_RETURN ) ) {
							setStatusScene(SCENE_GAME_MAIN);
						}
					}
					
					if ( event.type == SDL_MOUSEBUTTONDOWN ) {
						if ( ( event.button.button == SDL_BUTTON_LEFT ) ) {
							verifyClickElements_HelpFirstLevel();
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
void SceneGame::unLoad() {

	unLoadCommons();
	
	hasHelp = false;
	
	statusScene = SCENE_GAME_MAIN;
	
	Chronometer::GetInstance()->removeTime("intro_board");
	
	Board::GetInstance()->unLoad();
	
	delete bQuit;
	
	delete bReset;
	delete bOption;
	delete bNext;
	delete bPrevious;

	delete bAccept;
	delete bCancel;
	delete bgMenu;
	
	delete bAcceptInfo;
	delete bgInfo;
	
	delete bRetry;
    delete bLeave;
    delete bContinue;
    delete bBack;
	
	delete bgOptions;
	
	delete eyeRight;
	delete eyeLeft;
	delete imageEyeRight;
	delete imageEyeLeft;
	delete levelStatus;
	delete chronometer;
	
	delete windowLost;
	delete windowWin;
	delete windowFinish;
	delete frameDown;
	delete frameUp;
	
	delete titleInfoTray;
	delete textInfoTray;
	delete drawFood;
	
	delete volumeMusics;
	delete volumeEffects;
	delete titleVolumeMusics;
	delete titleVolumeEffects;
	delete titleTypeMusic;
	delete cbHelpActived;
	delete typeMusic;
	delete textInWindows;
	delete textInWindowsFinal;
	
	delete imageHelp;
	delete titleHelp;
	delete textHelp;
	
	if (hasHelpFirstLevel) {
		delete helpFirstLevel;
		delete bRightFirstLevel;
		delete bLeftFirstLevel;
	}
	
	Sounds::GetInstance()->unLoad();
	
	isLoad = false;

}
