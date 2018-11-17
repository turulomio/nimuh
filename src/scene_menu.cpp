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
 
#include "scene_menu.h"

class SceneMenu;

void alert_bPlay_SceneMenu_OnClick (Scene *s, Button *b, string data) {
	SceneMenu* se = (SceneMenu*)s;
	if (b->getParameter("type")=="accept") {
		Users::GetInstance()->getCurrentUser()->setLevelInMission("andalucia", 0);
		Users::GetInstance()->save();
		if (Missions::GetInstance()->setCurrentMissionAndLevel("andalucia")) {
			se->goToScene("infotown", 2000, SCENE_TRANSITION_SCALEx2_ROTATE);
		}
	} else {
		se->setStatusSceneWithReturnSceneFromMessage();
	}
}

void bPlay_SceneMenu_OnClick (Scene *s, Button *b)
{
	SceneMenu* se = (SceneMenu*)s;
	if (Users::GetInstance()->getCurrentUser()!=NULL) {
		if (Missions::GetInstance()->setCurrentMissionAndLevel("andalucia")) {
			if (Missions::GetInstance()->currentLevel==NULL) {
				se->showAlert(Language::GetInstance()->getText("info"), Language::GetInstance()->getText("missionfinish"), alert_bPlay_SceneMenu_OnClick, SCENE_MENU_MAIN);
			} else {
				Sounds::GetInstance()->getSound("main_music")->stop(2000);
				se->goToScene("infotown", 2000, SCENE_TRANSITION_SCALEx2_ROTATE);
			}
		} else {
			se->showMessageBox(Language::GetInstance()->getText("info"), Language::GetInstance()->getText("noexistmission"), SCENE_MENU_MAIN);
		}
	} else {
		se->showMessageBox(Language::GetInstance()->getText("info"), Language::GetInstance()->getText("loginuser"), SCENE_MENU_MAIN);
	}
}

void bMissions_SceneMenu_OnClick (Scene *s, Button *b) {
	SceneMenu* se = (SceneMenu*)s;
	if (Users::GetInstance()->getCurrentUser()!=NULL) {
		Sounds::GetInstance()->getSound("main_music")->stop(2000);
		Missions::GetInstance()->currentMission = NULL;
		Missions::GetInstance()->currentLevel = NULL;
		se->goToScene("createmission", 2000, SCENE_TRANSITION_SCALEx2_ROTATE);
	} else {
		se->showMessageBox(Language::GetInstance()->getText("info"), Language::GetInstance()->getText("loginuser"), SCENE_MENU_MAIN);
	}
}

void bPreferences_SceneMenu_OnClick (Scene *s, Button *b) {
	SceneMenu* se = (SceneMenu*)s;
	se->setSaveImage(true);
	se->setStatusScene(SCENE_MENU_OPTIONS);
}


void bHowto_SceneMenu_OnClick (Scene *s, Button *b) {
	SceneMenu* se = (SceneMenu*)s;
	se->setSaveImage(true);
	se->setStatusScene(SCENE_MENU_HOWTOPLAY);
}

void bCredits_SceneMenu_OnClick (Scene *s, Button *b) {
	SceneMenu* se = (SceneMenu*)s;
	Sounds::GetInstance()->getSound("main_music")->stop(2000);
	se->goToScene("credits", 2000, SCENE_TRANSITION_SCALEx2_ROTATE);
}

void bQuit_SceneMenu_OnClick (Scene *s, Button *b) {
	SceneMenu* se = (SceneMenu*)s;
	se->goToScene("quit");
}

void bChangeUser_SceneMenu_OnClick (Scene *s, Button *b) {
	SceneMenu* se = (SceneMenu*)s;
	se->setSaveImage(true);
	se->setStatusScene(SCENE_MENU_CHANGEUSER);
}

void newUser_SceneMenu_OnClickButtonOnMessage (Scene *s, Button *b, string data)
{
	SceneMenu* se = (SceneMenu*)s;
	if (b->getParameter("type")=="accept") {
		if (Users::GetInstance()->addUser(data)) {
			Users::GetInstance()->save();
			se->createUserButtons();
			se->setStatusSceneWithReturnSceneFromMessage();
		} else {
			se->showMessageBox(Language::GetInstance()->getText("info"), Language::GetInstance()->getText("existname"), SCENE_MENU_CHANGEUSER);
		}
	} else {
		se->setStatusSceneWithReturnSceneFromMessage();
	}
}

void bNewUser_SceneMenu_OnClick (Scene *s, Button *b) {
	SceneMenu* se = (SceneMenu*)s;
	se->showInput(Language::GetInstance()->getText("newuser"), Language::GetInstance()->getText("intousername"), 18, newUser_SceneMenu_OnClickButtonOnMessage, SCENE_MENU_CHANGEUSER);
}

void bBack_SceneMenu_OnClick (Scene *s, Button *b) {
	SceneMenu* se = (SceneMenu*)s;
	se->setStatusScene(SCENE_MENU_MAIN);
}

void bSelectUser_SceneCreateMission_OnClick (Scene *s, Button *b) {
	SceneMenu* se = (SceneMenu*)s;
	int i = atoi(b->getParameter("index").c_str());
	if ( Users::GetInstance()->getUser( i ) != NULL ) {
		se->changeUser(i);
		se->setStatusScene(SCENE_MENU_MAIN);
	}
}

void alert_bDeleteUser_SceneCreateMission_OnClick (Scene *s, Button *b, string data) {
	SceneMenu* se = (SceneMenu*)s;
	if (b->getParameter("type")=="accept") {
		int i = atoi(b->getParameter("index").c_str());
		int cUser = atoi(Options::GetInstance()->getValue("user").c_str());
		if (i==cUser) {
			se->changeUser(-1);
		}
		Users::GetInstance()->removeUser(i);
		Users::GetInstance()->save();
		se->createUserButtons();
	}
	se->setStatusSceneWithReturnSceneFromMessage();
}

void bDeleteUser_SceneCreateMission_OnClick (Scene *s, Button *b) {
	SceneMenu* se = (SceneMenu*)s;
	int i = atoi(b->getParameter("index").c_str());
	if ( Users::GetInstance()->getUser( i ) != NULL ) {
		se->msg_bAccept->addParameter("index", b->getParameter("index"));
		se->showAlert(Language::GetInstance()->getText("info"), Language::GetInstance()->getText("areyousuredelete"), alert_bDeleteUser_SceneCreateMission_OnClick, SCENE_MENU_CHANGEUSER);
	}
}

void bAccept_SceneMenu_OnClick (Scene *s, Button *b) {
	SceneMenu* se = (SceneMenu*)s;
	bool hasChange = false;
	if ( se->cbFullscreen->getActive() ) {
		if (Options::GetInstance()->getValue("fullscreen") == "false") hasChange = true;
		Options::GetInstance()->setValue("fullscreen", "true");
	} else {
		if (Options::GetInstance()->getValue("fullscreen") == "true") hasChange = true;
		Options::GetInstance()->setValue("fullscreen", "false");
	}
	if (se->typeLang->getIndex()==0) {
		if (Options::GetInstance()->getValue("lang") == "en") hasChange = true;
		Options::GetInstance()->setValue("lang", "es");
	} else {
		if (Options::GetInstance()->getValue("lang") == "es") hasChange = true;
		Options::GetInstance()->setValue("lang", "en");
	}
	char tmp[8];
	sprintf (tmp, "%d", se->volumeMusics->getIndex());
	Options::GetInstance()->setValue("music", tmp);
	sprintf (tmp, "%d", se->volumeEffects->getIndex());
	Options::GetInstance()->setValue("effects", tmp);
	
	Options::GetInstance()->save();
	
	Sound::setPorcentVolumeByCategory("music", 20*(Options::GetInstance()->getValueToInt("music")));
	Sound::setPorcentVolumeByCategory("high_music", 20*(Options::GetInstance()->getValueToInt("music")+1));
	Sound::setPorcentVolumeByCategory("low_music", 20*(Options::GetInstance()->getValueToInt("music")-1));
	Sound::setPorcentVolumeByCategory("musicgame", (20*(Options::GetInstance()->getValueToInt("music")))/3);
	Sound::setPorcentVolumeByCategory("effect", 20*(Options::GetInstance()->getValueToInt("effects")));

	Sounds::GetInstance()->getSound("main_music")->play(1, -1, 2000);
	
	if (hasChange) {
		se->showMessageBox(Language::GetInstance()->getText("info"), Language::GetInstance()->getText("exitforchange"), SCENE_MENU_MAIN);
	} else {
		se->setStatusScene(SCENE_MENU_MAIN);
	}
}

void bCancel_SceneMenu_OnClick (Scene *s, Button *b) {
	SceneMenu* se = (SceneMenu*)s;
	se->setStatusScene(SCENE_MENU_MAIN);
}

/*****************************
**
** CLASS PlanetButton
**
******************************/

PlanetButton::PlanetButton()  : Group () {
	
	anim = new AnimatedElement();	
	anim->setVAlign(VALIGN_CENTER);
	anim->setAlign(ALIGN_CENTER);
	this->addElement((Element*)anim);
	
	button = new Button();	
	button->setSoundOn("click1");
	button->setScales(1.0, 1.1);
	button->setVAlign(VALIGN_CENTER);
	button->setAlign(ALIGN_CENTER);
	button->setAlpha(0);
	button->setSensitive(false);
	this->addElement((Element*)button);
	
	indexz = 0;
	
	pixMov = 0;
	avPixMov = 0.1;
	
	factorPixMov = 0.1;

}

PlanetButton::~PlanetButton() {
	unLoad();
}

void PlanetButton::onOver() { 	
	if (button->onOver()) {
		if (button->isRollOver) {
			anim->setScaleGL(1.1, 100);
		} else {
			anim->setScaleGL(1.0, 100);
		}
	}
	
}

void PlanetButton::draw () { 
	if (pixMov>=10) {
		avPixMov = -factorPixMov;
	}
	if (pixMov<=0) {
		avPixMov = factorPixMov;
	}
	pixMov += avPixMov;
	button->addY(avPixMov);
	anim->addY(avPixMov);

	work();  
	if (isOnMouseOver()) { 
		if (button->getAnimation()->getName()=="on") {
			button->setAlpha(255);
		} else {
			button->setAlpha(0);
		}
		button->draw(); 
	} 
	anim->draw(); 
}

/*****************************
**
** CLASE ButtonMission
**
******************************/	

ButtonUser::ButtonUser() : Group () {
	
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
	
	bSelect = new Button();
	bSelect->setSoundOn("click0");
	bSelect->setScales(1.0, 1.1);
	bSelect->setAlign(ALIGN_CENTER);
	bSelect->setVAlign(VALIGN_CENTER);
	bSelect->setX(350);
	bSelect->setY(22);
	bSelect->imageOut(WorkingSurfaces::GetInstance()->surfaceFromImage((string)DATA_DIR + "/interface/" + Language::GetInstance()->getFilename("use", "png")));
	bSelect->setAnimation("out");
	bSelect->OnClick = bSelectUser_SceneCreateMission_OnClick;
	this->addElement(bSelect);
		
	bDelete = new Button();
	bDelete->setSoundOn("click0");
	bDelete->setScales(1.0, 1.1);
	bDelete->setAlign(ALIGN_CENTER);
	bDelete->setVAlign(VALIGN_CENTER);
	bDelete->setX(420);
	bDelete->setY(22);
	bDelete->imageOut(WorkingSurfaces::GetInstance()->surfaceFromImage((string)DATA_DIR + "/interface/delete.png"));
	bDelete->setAnimation("out");
	bDelete->OnClick = bDeleteUser_SceneCreateMission_OnClick;
	this->addElement(bDelete);
	
}

ButtonUser::~ButtonUser() {
	unLoad();
}

void ButtonUser::setIndex (int i) { 
	index = i; 
	char tmp[4]; 
	sprintf(tmp, "%d", i);
	bSelect->addParameter("index", tmp); 
	bDelete->addParameter("index", tmp); 
}

void ButtonUser::setTitle(string t) {
	
	title->changeFrameText(0, "font-texts", t, ALIGN_CENTER);
	
}

void ButtonUser::draw() {
	work();
	bg->draw();
	title->draw();
	bSelect->draw();
	bDelete->draw();
}

void ButtonUser::onOver() {
	bSelect->onOver();
	bDelete->onOver();
}

void ButtonUser::verifyClick(SceneMenu *sc) {
	if (bSelect->isOnMouseOver()) {
		bSelect->OnClick(sc, bSelect);
	}
	if (bDelete->isOnMouseOver()) {
		bDelete->OnClick(sc, bDelete);
	}
}

void ButtonUser::unLoad() {
	bg->unLoad();
	title->unLoad();
	bSelect->unLoad();
	bDelete->unLoad();
}

/*****************************
**
** CLASE SceneMenu
**
******************************/	

SceneMenu::SceneMenu() : Scene () {
	statusScene = SCENE_MENU_MAIN;
}

SceneMenu::~SceneMenu() {
	unLoad();
}

void SceneMenu::setStatusScene(int s) {
     statusScene = s;
     switch(statusScene) {
        case SCENE_MENU_CHANGEUSER:
			bBack->setX(580);
			bBack->setY(485);
        break;
        case SCENE_MENU_HOWTOPLAY:
			bBack->setX(760);
			bBack->setY(560);
        break;
	}
	
}

void SceneMenu::load() {

	initialize();
	
	Missions::GetInstance()->currentMission = NULL;
		
	char tmp[128];
		
	ProgressBar *pb = new ProgressBar(3, 200, 16, 255, 255, 255);

	pb->setBg((string)DATA_DIR + "/title.png");
	pb->setBgBar((string)DATA_DIR + "/bg_barprogress.png");
    pb->setPositionBar(World::width/2, 300);
	pb->setText("font-texts", Language::GetInstance()->getText("loading_user"));
	pb->draw();
	
	howtoplay = new Element();	
	howtoplay->addFrameSurface(WorkingSurfaces::GetInstance()->surfaceFromImage((string)DATA_DIR + "/misc/" + Language::GetInstance()->getFilename("howtoplay", "png")));
	
	stars = new ParticlesSystem();
	stars->setFrame((string)DATA_DIR + "/particles/point.png");
	stars->setDisplacementX(0, 1);
	stars->setPositions(-200, 0, 1000, 600);
	stars->setType(TYPE_STARS);
	stars->start();
			
	Button *bUp = new Button();
	bUp->setScales(1.0, 1.1);
	bUp->setAlign(ALIGN_CENTER);
	bUp->setVAlign(VALIGN_CENTER);
	
	bUp->imageOut(WorkingSurfaces::GetInstance()->surfaceFromImage((string)DATA_DIR + "/createmissions/bup_on.png"));
	bUp->imageOff(WorkingSurfaces::GetInstance()->surfaceFromImage((string)DATA_DIR + "/createmissions/bup_off.png"));
	bUp->setAnimation("out");
	
	Button *bDown = new Button();
	bDown->setFlop(true);
	bDown->setScales(1.0, 1.1);
	bDown->setAlign(ALIGN_CENTER);
	bDown->setVAlign(VALIGN_CENTER);
	
	bDown->imageOut(WorkingSurfaces::GetInstance()->surfaceFromImage((string)DATA_DIR + "/createmissions/bup_on.png"));
	bDown->imageOff(WorkingSurfaces::GetInstance()->surfaceFromImage((string)DATA_DIR + "/createmissions/bup_off.png"));
	bDown->setAnimation("out");
	
	dataUsers = new ListView();
	dataUsers->setTodoMovement(false);
	dataUsers->setXY(160, 170);
	dataUsers->setItemsVisible(5);
	dataUsers->setSeparateGrid(50);
	dataUsers->setButtons(bUp, bDown, 515);	
	
	// sounds
	
	Sounds::GetInstance()->addSoundFromData("main_music", "music", "sound/options.ogg");	
	
	pb->setText("font-texts", Language::GetInstance()->getText("loading_buttons"));
	pb->draw();
	
	Animation aPlanet;
	aPlanet.setName("move");
	aPlanet.addRangeFrame(0, 9, 1);
	
	bPlay = new PlanetButton();	
	bPlay->setFactorPixMov(0.07);
	bPlay->setX(110);
	bPlay->setY(-300);
	
	bPlay->getAnimatedElement()->addRangeFramesFromData("main_menu/" + Language::GetInstance()->getLang() + "/play", "png", 0, 9);
	
	bPlay->getAnimatedElement()->addAnimation(aPlanet);
	bPlay->getAnimatedElement()->getAnimation()->stop();
	
	bPlay->imageOutButton(Primitives::GetInstance()->rectangle(bPlay->getAnimatedElement()->getWidth(), bPlay->getAnimatedElement()->getHeight(), 255, 255, 255));
	bPlay->imageOnButton(WorkingSurfaces::GetInstance()->surfaceFromImage((string)DATA_DIR + "/main_menu/play_glow.png"));
	
	bPlay->getButton()->OnClick = bPlay_SceneMenu_OnClick;
	
	getGroupScene()->addGroup(bPlay);
	
	bMissions = new PlanetButton();	
	bMissions->setFactorPixMov(0.1);
	bMissions->setX(680);
	bMissions->setY(-300);
	
	bMissions->getAnimatedElement()->addRangeFramesFromData("main_menu/" + Language::GetInstance()->getLang() + "/missions", "png", 0, 9);
	
	bMissions->getAnimatedElement()->addAnimation(aPlanet);
	bMissions->getAnimatedElement()->getAnimation()->stop();
	
	bMissions->imageOutButton(Primitives::GetInstance()->rectangle(bMissions->getAnimatedElement()->getWidth(), bMissions->getAnimatedElement()->getHeight(), 255, 255, 255));
	bMissions->imageOnButton(WorkingSurfaces::GetInstance()->surfaceFromImage((string)DATA_DIR + "/main_menu/mission_glow.png"));
	
	bMissions->getButton()->OnClick = bMissions_SceneMenu_OnClick;
		
	getGroupScene()->addGroup(bMissions);
	
	bHowto = new PlanetButton();	
	bHowto->setFactorPixMov(0.063);
	bHowto->setX(285);
	bHowto->setY(-300);
	
	bHowto->getAnimatedElement()->addRangeFramesFromData("main_menu/" + Language::GetInstance()->getLang() + "/howto", "png", 0, 9);
	
	bHowto->getAnimatedElement()->addAnimation(aPlanet);
	bHowto->getAnimatedElement()->getAnimation()->stop();
	
	bHowto->imageOutButton(Primitives::GetInstance()->rectangle(bHowto->getAnimatedElement()->getWidth(), bHowto->getAnimatedElement()->getHeight(), 255, 255, 255));
	bHowto->imageOnButton(WorkingSurfaces::GetInstance()->surfaceFromImage((string)DATA_DIR + "/main_menu/howto_glow.png"));
	
	bHowto->getButton()->OnClick = bHowto_SceneMenu_OnClick;
		
	getGroupScene()->addGroup(bHowto);
	
	bCredits = new PlanetButton();	
	bCredits->setFactorPixMov(0.075);
	bCredits->setX(90);
	bCredits->setY(-300);
	
	bCredits->getAnimatedElement()->addRangeFramesFromData("main_menu/" + Language::GetInstance()->getLang() + "/credits", "png", 0, 9);
	
	bCredits->getAnimatedElement()->addAnimation(aPlanet);
	bCredits->getAnimatedElement()->getAnimation()->stop();
	
	bCredits->imageOutButton(Primitives::GetInstance()->rectangle(bCredits->getAnimatedElement()->getWidth(), bCredits->getAnimatedElement()->getHeight(), 255, 255, 255));
	bCredits->imageOnButton(WorkingSurfaces::GetInstance()->surfaceFromImage((string)DATA_DIR + "/main_menu/credits_glow.png"));
	
	bCredits->getButton()->OnClick = bCredits_SceneMenu_OnClick;
		
	getGroupScene()->addGroup(bCredits);
	
	bPreferences = new PlanetButton();
	bPreferences->setFactorPixMov(0.08);
	bPreferences->setX(380);
	bPreferences->setY(-300);
	
	bPreferences->getAnimatedElement()->addRangeFramesFromData("main_menu/" + Language::GetInstance()->getLang() + "/preferences", "png", 0, 9);
	
	bPreferences->getAnimatedElement()->addAnimation(aPlanet);
	bPreferences->getAnimatedElement()->getAnimation()->stop();
	
	bPreferences->imageOutButton(Primitives::GetInstance()->rectangle(bPreferences->getAnimatedElement()->getWidth(), bPreferences->getAnimatedElement()->getHeight(), 255, 255, 255));
	bPreferences->imageOnButton(WorkingSurfaces::GetInstance()->surfaceFromImage((string)DATA_DIR + "/main_menu/preferences_glow.png"));
	
	bPreferences->getButton()->OnClick = bPreferences_SceneMenu_OnClick;
		
	getGroupScene()->addGroup(bPreferences);
	
	bQuit = new PlanetButton();	
	bQuit->setFactorPixMov(0.09);
	bQuit->setX(710);
	bQuit->setY(-300);
	
	bQuit->getAnimatedElement()->addRangeFramesFromData("main_menu/" + Language::GetInstance()->getLang() + "/quit", "png", 0, 9);
	
	bQuit->getAnimatedElement()->addAnimation(aPlanet);
	bQuit->getAnimatedElement()->getAnimation()->stop();
	
	bQuit->imageOutButton(Primitives::GetInstance()->rectangle(bQuit->getAnimatedElement()->getWidth(), bQuit->getAnimatedElement()->getHeight(), 255, 255, 255));
	bQuit->imageOnButton(WorkingSurfaces::GetInstance()->surfaceFromImage((string)DATA_DIR + "/main_menu/quit_glow.png"));
	
	bQuit->getButton()->OnClick = bQuit_SceneMenu_OnClick;
		
	getGroupScene()->addGroup(bQuit);
	
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
		
	earth = new Element();	
	earth->setAlign(ALIGN_CENTER);
	earth->setVAlign(VALIGN_CENTER);
	earth->setXY(410, 350);
	earth->setCurrentScale(0);
	
	earth->addFrameFileFromData("/main_menu/earth.png");
		
	getGroupScene()->addElement(earth);
	
	title = new Element();	
	title->setIndexZ(1);
	title->setAlign(ALIGN_CENTER);
	//title->setVAlign(VALIGN_CENTER);
	title->setXY(370, -500);
	
	title->addFrameFileFromData("/main_menu/title.png");
	
	getGroupScene()->addElement(title);
	
	bgOptions = new Element();
	bgOptions->setAlign(ALIGN_CENTER);
	bgOptions->setVAlign(VALIGN_CENTER);
	bgOptions->setXY(World::width/2, 250);
	bgOptions->addFrameFileFromData("/windows/" + Language::GetInstance()->getFilename("options", "png"));
	
	getGroupScene()->addElement(bgOptions);
	
	bgUsers = new Element();
	bgUsers->setAlign(ALIGN_CENTER);
	bgUsers->setVAlign(VALIGN_CENTER);
	bgUsers->setXY(425, 285);
	bgUsers->addFrameFileFromData("/interface/base_users.png");
	
	getGroupScene()->addElement(bgUsers);
	
	nousers = new Element();
	nousers->setAlign(ALIGN_CENTER);
	nousers->setX(World::width/2);
	nousers->setY(190);
	nousers->setCurrentScale(1.4);
	
	nousers->addFrameLanguage("font-texts", "nousers", ALIGN_CENTER);
	
	getGroupScene()->addElement(nousers);
	
	
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
	
	volumeMusics->setArrows(WorkingSurfaces::GetInstance()->surfaceFromImage((string)DATA_DIR+"/windows/arrow_left.png"), WorkingSurfaces::GetInstance()->surfaceFromImage((string)DATA_DIR+"/windows/arrow_right.png"));
	volumeEffects->setArrows(WorkingSurfaces::GetInstance()->surfaceFromImage((string)DATA_DIR+"/windows/arrow_left.png"), WorkingSurfaces::GetInstance()->surfaceFromImage((string)DATA_DIR+"/windows/arrow_right.png"));
	
	getGroupScene()->addGroup(volumeMusics);
	getGroupScene()->addGroup(volumeEffects);
	
	cbFullscreen = new CheckButton("font-texts", Language::GetInstance()->getText("fullscreen"));
	cbFullscreen->setX(425);
	cbFullscreen->setY(230);
	
	cbFullscreen->imageActive(WorkingSurfaces::GetInstance()->surfaceFromImage((string)DATA_DIR + "/interface/rad_on.png"));
	cbFullscreen->imageInactive(WorkingSurfaces::GetInstance()->surfaceFromImage((string)DATA_DIR + "/interface/rad_off.png"));
	
	if (Options::GetInstance()->getValue("fullscreen") == "true")
		cbFullscreen->setActive(true);
	
	getGroupScene()->addGroup(cbFullscreen);
	
	titleLang = new Element();
	titleLang->setVAlign(VALIGN_CENTER);
	titleLang->setAlign(ALIGN_CENTER);
	titleLang->setX(530);
	titleLang->setY(300);

	titleLang->addFrameLanguage("font-texts", "typelang", ALIGN_CENTER);
	
	getGroupScene()->addElement(titleLang);
	
	titleUsers = new Element();
	titleUsers->setCurrentScale(0.6);
	titleUsers->setRGB(234, 238, 53);
	titleUsers->setX(230);
	titleUsers->setY(97);
	
	titleUsers->addFrameLanguage("font-computer", "users", ALIGN_CENTER);
	
	getGroupScene()->addElement(titleUsers);
	
	typeLang = new SelectButton();
	typeLang->setX(460);
	typeLang->setY(330);
	
	typeLang->addObject(Fonts::GetInstance()->getSurface_TextBitMap("font-text", ALIGN_CENTER, "ESPAÑOL"));
	typeLang->addObject(Fonts::GetInstance()->getSurface_TextBitMap("font-text", ALIGN_CENTER, "ENGLISH"));
	
	if (Options::GetInstance()->getValue("lang")=="es") {
		typeLang->setFrame(0);
	} else {
		typeLang->setFrame(1);
	}
	
	typeLang->setArrows(WorkingSurfaces::GetInstance()->surfaceFromImage((string)DATA_DIR+"/windows/arrow_left.png"), WorkingSurfaces::GetInstance()->surfaceFromImage((string)DATA_DIR+"/windows/arrow_right.png"));
	
	getGroupScene()->addGroup(typeLang);
	
	bAccept = new Button();
	bAccept->setScales(0.4, 0.45);
	bAccept->setAlign(ALIGN_CENTER);
	bAccept->setVAlign(VALIGN_CENTER);
	bAccept->setX(265);
	bAccept->setY(382);
	bAccept->setRGB(0, 255, 0);

	bAccept->OnClick = bAccept_SceneMenu_OnClick;
	
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
	
	bCancel->OnClick = bCancel_SceneMenu_OnClick;
	
	sprintf(tmp, Language::GetInstance()->getText("cancel").c_str());
	bCancel->imageOut(Fonts::GetInstance()->getSurface_TextBitMap("font-computer", ALIGN_CENTER, tmp));
	bCancel->setAnimation("out");
	
	getGroupScene()->addElement(bCancel);
		
	nameUser = new Element();	
	nameUser->setAlign(ALIGN_CENTER);
	nameUser->setVAlign(VALIGN_CENTER);
	nameUser->setX(World::width-110);
	nameUser->setY(40);
	nameUser->hide();
	if (Users::GetInstance()->getCurrentUser()==NULL) {
		sprintf(tmp, Language::GetInstance()->getText("nouser").c_str());
	} else {
		sprintf(tmp, Users::GetInstance()->getCurrentUser()->getName().c_str());
	}

	nameUser->addFrameSurface(Fonts::GetInstance()->getSurface_TextBitMap("font-texts", ALIGN_CENTER, tmp));
	
	bChangeUser = new Button();	
	bChangeUser->setSoundOn("click0");
	bChangeUser->setScales(0.9, 0.94);
	bChangeUser->setAlign(ALIGN_CENTER);
	bChangeUser->setVAlign(VALIGN_CENTER);
	bChangeUser->setX(World::width-110);
	bChangeUser->setY(55);
	bChangeUser->hide();
	
	//sprintf(tmp, Language::GetInstance()->getText("changeuser").c_str());
	bChangeUser->imageOut(WorkingSurfaces::GetInstance()->surfaceFromImage((string)DATA_DIR + "/main_menu/" + Language::GetInstance()->getFilename("userbox", "png")));
	bChangeUser->setAnimation("out");
	
	bChangeUser->OnClick = bChangeUser_SceneMenu_OnClick;
	
	getGroupScene()->addElement(bChangeUser);
		
	// buttons of change user
	
	bBack = new Button();
	bBack->setSoundOn("click0");
	bBack->setScales(1.0, 1.1);
	bBack->setAlign(ALIGN_CENTER);
	bBack->setVAlign(VALIGN_CENTER);
	bBack->setX(580);
	bBack->setY(485);
	
	bBack->imageOn(WorkingSurfaces::GetInstance()->surfaceFromImage((string)DATA_DIR + "/createmissions/" + Language::GetInstance()->getFilename("back", "png")));
	bBack->setAnimation("out");
	
	bBack->OnClick = bBack_SceneMenu_OnClick;
	
	getGroupScene()->addElement(bBack);
	
	bNewUser = new Button();
	bNewUser->setSoundOn("click0");
	bNewUser->setScales(0.65, 0.68);
	bNewUser->setAlign(ALIGN_CENTER);
	bNewUser->setVAlign(VALIGN_CENTER);
	bNewUser->setX(395);
	bNewUser->setY(448);
	bNewUser->setRGB(0,255,0);
	
	bNewUser->imageOut(Fonts::GetInstance()->getSurface_TextBitMap("font-computer", ALIGN_CENTER, Language::GetInstance()->getText("new")));
	bNewUser->setAnimation("out");
	
	bNewUser->OnClick = bNewUser_SceneMenu_OnClick;
	
	getGroupScene()->addElement(bNewUser);
	
	pb->setText("font-texts", Language::GetInstance()->getText("loading_userbuttons"));
	pb->draw();
		
	createUserButtons();
	
	Sounds::GetInstance()->getSound("main_music")->play(1, -1, 2000);
	
	Chronometer::GetInstance()->removeTime("intro_menu");
	Chronometer::GetInstance()->setTime("intro_menu");
	
	delete pb;
	
}

void SceneMenu::changeUser(int i) {
	
	if ( i==-1 || Users::GetInstance()->getUser( i ) != NULL ) {
		
		char tmp[8];
		sprintf(tmp, "%d", i);
		Options::GetInstance()->setValue("user", tmp);
		Options::GetInstance()->save();
		
		Frame fr;
		char tmp_name[128];
		
		if (Users::GetInstance()->getCurrentUser()==NULL) {
			sprintf(tmp_name, Language::GetInstance()->getText("nouser").c_str());
		} else {
			sprintf(tmp_name, Users::GetInstance()->getCurrentUser()->getName().c_str());
		}
		
		nameUser->changeFrameSurface(0, Fonts::GetInstance()->getSurface_TextBitMap("font-texts", ALIGN_CENTER, tmp_name));
		
	}
	
}

void SceneMenu::createUserButtons() {
	
	dataUsers->MoveFirst();
	while (!dataUsers->isEOF()) {
        delete (ButtonUser*)dataUsers->getData();
        dataUsers->MoveNext();
    }
	
	dataUsers->inicialize();
	
	char tmp[128];
	
	Users::GetInstance()->MoveFirst();
	
	int i=0;
	
	while (!Users::GetInstance()->isEOF()) {
		ButtonUser *bUser = new ButtonUser();
		bUser->setIndex(i);
		
		sprintf(tmp, Users::GetInstance()->getUser()->getName().c_str());
		
		bUser->setTitle(tmp);
		
		Users::GetInstance()->MoveNext();
		
		getGroupScene()->addGroup((Group*)bUser);
		
		dataUsers->add(bUser);
		
		i++;
	}

}

/**********************
  DRAWSCENE MAIN
**********************/

void SceneMenu::drawSceneMain () {
     
    if ( Chronometer::GetInstance()->verifyTime("intro_menu", 400) ) {
        bPlay->setMovementSmoothY(320);
    }
	if ( Chronometer::GetInstance()->verifyTime("intro_menu", 800) ) {
        bPreferences->setMovementSmoothY(470);
    }
    if ( Chronometer::GetInstance()->verifyTime("intro_menu", 1200) ) {
        bMissions->setMovementSmoothY(320);
    }
    if ( Chronometer::GetInstance()->verifyTime("intro_menu", 1600) ) {
		bHowto->setMovementSmoothY(220);
    }
	if ( Chronometer::GetInstance()->verifyTime("intro_menu", 2000) ) {
		bCredits->setMovementSmoothY(530);
    }
	if ( Chronometer::GetInstance()->verifyTime("intro_menu", 2400) ) {
        bQuit->setMovementSmoothY(500);
    }
    if ( Chronometer::GetInstance()->verifyTime("intro_menu", 2800) ) {
        bPlay->getAnimatedElement()->setForceAnimation("move", 1);
    }
    if ( Chronometer::GetInstance()->verifyTime("intro_menu", 3200) ) {
        bPreferences->getAnimatedElement()->setForceAnimation("move", 1);
    }
    if ( Chronometer::GetInstance()->verifyTime("intro_menu", 3600) ) {
        bMissions->getAnimatedElement()->setForceAnimation("move", 1);
    }
    if ( Chronometer::GetInstance()->verifyTime("intro_menu", 4000) ) {
		bHowto->getAnimatedElement()->setForceAnimation("move", 1);
    }
    if ( Chronometer::GetInstance()->verifyTime("intro_menu", 4400) ) {
		bCredits->getAnimatedElement()->setForceAnimation("move", 1);
    }
    if ( Chronometer::GetInstance()->verifyTime("intro_menu", 4800) ) {
        bQuit->getAnimatedElement()->setForceAnimation("move", 1);
    }
    if ( Chronometer::GetInstance()->verifyTime("intro_menu", 5200) ) {
        earth->setScaleFlexible(earth->getWidthOriginal(), earth->getHeightOriginal());
		earth->setRotationFlexible(360);
    }
    if ( Chronometer::GetInstance()->verifyTime("intro_menu", 5600) ) {
        title->setMovementSmoothY(0);
		nameUser->show();
		bChangeUser->show();
        nameUser->setFadeIn(600);
		bChangeUser->setFadeIn(600);
		bPlay->setSensitive(true);
		bPreferences->setSensitive(true);
		bMissions->setSensitive(true);
		bQuit->setSensitive(true);
		bHowto->setSensitive(true);
		bCredits->setSensitive(true);
    }
			
	verifyOverElements_Main();
	
	stars->draw();

	for (int i=0; i<MAX_INDEXZ; i++) {
		drawSceneMainByIndexZ(i);
	}
	
}

void SceneMenu::drawSceneMainByIndexZ(int z) {
	if (bChangeUser->getIndexZ() == z) {
		bChangeUser->draw();
	}
	if (nameUser->getIndexZ() == z) {
		nameUser->draw();
	}
	if (earth->getIndexZ() == z) {
		earth->draw();
	}
	if (title->getIndexZ() == z) {
		title->draw();
	}
	if (bPlay->getIndexZ() == z) {
		bPlay->draw();
	}
	if (bMissions->getIndexZ() == z) {
		bMissions->draw();
	}
	if (bHowto->getIndexZ() == z) {
		bHowto->draw();
	}
	if (bCredits->getIndexZ() == z) {
		bCredits->draw();
	}
	if (bPreferences->getIndexZ() == z) {
		bPreferences->draw();
	}
	if (bQuit->getIndexZ() == z) {
		bQuit->draw();
	}
	
}

void SceneMenu::verifyClickElements_Main() {
	if (bPlay->isOnMouseOver()) {
		bPlay->getButton()->OnClick(this, bPlay->getButton());
	}
	if (bMissions->isOnMouseOver()) {
		bMissions->getButton()->OnClick(this, bMissions->getButton());
	}
	if (bHowto->isOnMouseOver()) {
		bHowto->getButton()->OnClick(this, bHowto->getButton());
	}
	if (bCredits->isOnMouseOver()) {
		bCredits->getButton()->OnClick(this, bCredits->getButton());
	}
	if (bQuit->isOnMouseOver()) {
		bQuit->getButton()->OnClick(this, bQuit->getButton());
	}
	if (bPreferences->isOnMouseOver()) {
		bPreferences->getButton()->OnClick(this, bPreferences->getButton());
	}
	if (bChangeUser->isOnMouseOver()) {
		bChangeUser->OnClick(this, bChangeUser);
	}
}

void SceneMenu::verifyOverElements_Main() {
	bPlay->onOver();
	bMissions->onOver();
	bPreferences->onOver();
	bCredits->onOver();
	bHowto->onOver();
	bQuit->onOver();
	bChangeUser->onOver();
}

/**********************
  DRAWSCENE CHANGEUSER
**********************/

void SceneMenu::drawSceneChangeUser () {
	
	verifyOverElements_ChangeUser();
	elmImgSave[0]->draw();
	
	for (int i=0; i<MAX_INDEXZ; i++) {
		drawSceneChangeUserByIndexZ(i);
	}
	
}

void SceneMenu::drawSceneChangeUserByIndexZ(int z) {
     
	if (bBack->getIndexZ() == z) {
		bBack->draw();
	}
     
	if (frameUp->getIndexZ() == z) {
		frameUp->draw();
	}
	if (frameDown->getIndexZ() == z) {
		frameDown->draw();
	}
	
	if (bgUsers->getIndexZ() == z) {
		bgUsers->draw();
	}
	
	if (titleUsers->getIndexZ() == z) {
		titleUsers->draw();
	}
	
	if (Users::GetInstance()->getNUsers()>0) {
        if (dataUsers->getIndexZ() == z) {
           dataUsers->draw();
        }
	} else {
		if (nousers->getIndexZ() == z) {
			nousers->draw();
		}
	}
	
	
	if (bNewUser->getIndexZ() == z) {
		bNewUser->draw();
	}
	
}

void SceneMenu::verifyClickElements_ChangeUser() {
	if (bNewUser->isOnMouseOver()) {
		bNewUser->OnClick(this, bNewUser);
	}
	if (bBack->isOnMouseOver()) {
		bBack->OnClick(this, bBack);
	}
	
	dataUsers->verifyClickButtons();
	
	dataUsers->MoveFirst();
	while (!dataUsers->isEOF()) {
        if (dataUsers->isVisible()) {
           ButtonUser *bu = (ButtonUser*)dataUsers->getData();
           bu->verifyClick(this);
        }
        dataUsers->MoveNext();
    }
    
}

void SceneMenu::verifyOverElements_ChangeUser() {
	bBack->onOver();
	bNewUser->onOver();
	
	dataUsers->MoveFirst();
	while (!dataUsers->isEOF()) {
        if (dataUsers->isVisible()) {
           ButtonUser *bu = (ButtonUser*)dataUsers->getData();
           bu->onOver();
        }
        dataUsers->MoveNext();
    }
}

/**********************
  DRAWSCENE CHANGEUSER
**********************/

void SceneMenu::drawSceneHowtoplay () {
	
	verifyOverElements_Howtoplay();
	elmImgSave[0]->draw();
	
	for (int i=0; i<MAX_INDEXZ; i++) {
		drawSceneHowtoplayByIndexZ(i);
	}
	
}

void SceneMenu::drawSceneHowtoplayByIndexZ(int z) {
	
	if (howtoplay->getIndexZ() == z) {
		howtoplay->draw();
	}
	
	if (bBack->getIndexZ() == z) {
		bBack->draw();
	}
	
}

void SceneMenu::verifyClickElements_Howtoplay() {
	if (bBack->isOnMouseOver()) {
		bBack->OnClick(this, bBack);
	}
}

void SceneMenu::verifyOverElements_Howtoplay() {
	bBack->onOver();
}

/**********************
  DRAWSCENE OPTIONS
**********************/

void SceneMenu::drawSceneOptions () {
	
	verifyOverElements_Options();
	elmImgSave[0]->draw();
	
	for (int i=0; i<MAX_INDEXZ; i++) {
		drawSceneOptionsByIndexZ(i);
	}
	
}

void SceneMenu::drawSceneOptionsByIndexZ(int z) {
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
	if (titleVolumeMusics->getIndexZ() == z) {
		titleVolumeMusics->draw();
	}
	if (titleVolumeEffects->getIndexZ() == z) {
		titleVolumeEffects->draw();
	}
	if (cbFullscreen->getIndexZ() == z) {
		cbFullscreen->draw();
	}
	if (titleLang->getIndexZ() == z) {
		titleLang->draw();
	}
	if (typeLang->getIndexZ() == z) {
		typeLang->draw();
	}
	if (bAccept->getIndexZ() == z) {
		bAccept->draw();
	}
	if (bCancel->getIndexZ() == z) {
		bCancel->draw();
	}
}

void SceneMenu::verifyClickElements_Options() {
	if (cbFullscreen->isOnMouseOver()) {
		cbFullscreen->swapActive();
	}
	if (typeLang->isOnMouseOver()) {
		if (typeLang->getOverBottom()==LEFT) {
			typeLang->previousFrame();
		}
		if (typeLang->getOverBottom()==RIGHT) {
			typeLang->nextFrame();
		}
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
	if (bAccept->isOnMouseOver()) {
		bAccept->OnClick(this, bAccept);
	}
	if (bCancel->isOnMouseOver()) {
		bCancel->OnClick(this, bCancel);
	} 
}

void SceneMenu::verifyOverElements_Options() {
	bAccept->onOver();
	bCancel->onOver();
}

bool SceneMenu::drawScene() {
	
	glClear(GL_COLOR_BUFFER_BIT); // | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	
	drawCommonsScene ();

	switch(statusScene) {
	
		case SCENE_MENU_MAIN:
	
			drawSceneMain();
		
			// Comprobando teclas para opciones			
			{ SDL_Event event;
				while ( SDL_PollEvent(&event) ) {
					if ( event.type == SDL_QUIT ) {
						goToScene("quit");
					}
					
					if ( event.type == SDL_KEYDOWN ) {
						if ( event.key.keysym.sym == SDLK_ESCAPE ) {
							goToScene("quit");
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
			
		case SCENE_MENU_CHANGEUSER:
	
			drawSceneChangeUser();
		
			// Comprobando teclas para opciones			
			{ SDL_Event event;
				while ( SDL_PollEvent(&event) ) {
					if ( event.type == SDL_QUIT ) {
						goToScene("quit");
					}
					
					if ( event.type == SDL_KEYDOWN ) {
						if ( event.key.keysym.sym == SDLK_ESCAPE ) {
							statusScene = SCENE_MENU_MAIN;
						}
					}
					
					if ( event.type == SDL_MOUSEBUTTONDOWN ) {
						if ( event.button.button == SDL_BUTTON_LEFT ) {
							verifyClickElements_ChangeUser();
						}
					}
		
				}
			}
			
		break;
			
		case SCENE_MENU_HOWTOPLAY:
	
			drawSceneHowtoplay();
		
			// Comprobando teclas para opciones			
			{ SDL_Event event;
				while ( SDL_PollEvent(&event) ) {
					if ( event.type == SDL_QUIT ) {
						goToScene("quit");
					}
					
					if ( event.type == SDL_KEYDOWN ) {
						if ( event.key.keysym.sym == SDLK_ESCAPE ) {
							statusScene = SCENE_MENU_MAIN;
						}
					}
					
					if ( event.type == SDL_MOUSEBUTTONDOWN ) {
						if ( event.button.button == SDL_BUTTON_LEFT ) {
							verifyClickElements_Howtoplay();
						}
					}
		
				}
			}
			
		break;
			
		case SCENE_MENU_OPTIONS:
	
			drawSceneOptions();
		
			// Comprobando teclas para opciones			
			{ SDL_Event event;
				while ( SDL_PollEvent(&event) ) {
					if ( event.type == SDL_QUIT ) {
						goToScene("quit");
					}
					
					if ( event.type == SDL_KEYDOWN ) {
						if ( event.key.keysym.sym == SDLK_ESCAPE ) {
							statusScene = SCENE_MENU_MAIN;
						}
					}
					
					if ( event.type == SDL_MOUSEBUTTONDOWN ) {
						if ( event.button.button == SDL_BUTTON_LEFT ) {
							verifyClickElements_Options();
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
void SceneMenu::unLoad() {

	unLoadCommons();
	
	statusScene = SCENE_MENU_MAIN;
	
	delete bQuit;
	delete bPlay;
	delete bMissions;
	delete bPreferences;
	delete bCredits;
	delete bHowto;
	delete bChangeUser;
	delete bNewUser;
	delete bBack;
	delete title;
	delete earth;
	delete nameUser;
	delete titleUsers;
	
	delete frameUp;
	delete frameDown;
	
	delete titleVolumeMusics;
	delete titleVolumeEffects;
	delete volumeMusics;
	delete volumeEffects;
	delete cbFullscreen;
	delete bgOptions;
	delete bgUsers;
	delete titleLang;
	delete typeLang;
	delete bAccept;
	delete bCancel;
	
	delete howtoplay;
	
	delete nousers;
	
	Sounds::GetInstance()->unLoad();
	
	delete dataUsers;
	
	delete stars;

	isLoad = false;

}
