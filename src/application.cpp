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
 
 #include "application.h"


Application::Application(int w, int h, string titleWindow)  : World (w, h, titleWindow) {

	if (existDataDirectory) {	
		// configuration files
		
		SDL_EnableKeyRepeat(SDL_DEFAULT_REPEAT_DELAY, SDL_DEFAULT_REPEAT_INTERVAL);
		SDL_EnableUNICODE(1); 
		
		changeLanguage = false;
		
		if (Options::GetInstance()->getNItems() == 0) {
			Options::GetInstance()->addItem("fullscreen", "true");
			Options::GetInstance()->addItem("helpactived", "true");
			Options::GetInstance()->addItem("music", "3");
			Options::GetInstance()->addItem("effects", "3");
			Options::GetInstance()->addItem("debug", "false");
			Options::GetInstance()->addItem("lang", "es");
			Options::GetInstance()->addItem("user", "-1");
			Options::GetInstance()->addItem("scene", "");
			Options::GetInstance()->save();
			changeLanguage = true;
		}
			
		Options::GetInstance()->addItem("mission", "-1");
		Options::GetInstance()->save();
		
		if (Options::GetInstance()->getValue("debug") == "true") {
			Debug::GetInstance()->setDebug(true);
		}
		
		Users::GetInstance()->load("user.xml");
		
		if (Users::GetInstance()->getCurrentUser()==NULL) {
			Options::GetInstance()->setValue("user", "-1");
			Options::GetInstance()->save();
		}
		
		Missions::GetInstance()->load();
		
		// sounds
		
		Sounds::GetInstance()->init();
			
		Sound::setPorcentVolumeByCategory("default", 80);
		Sound::setPorcentVolumeByCategory("music", 20*(Options::GetInstance()->getValueToInt("music")));
		Sound::setPorcentVolumeByCategory("high_music", 20*(Options::GetInstance()->getValueToInt("music")+1));
		Sound::setPorcentVolumeByCategory("low_music", 20*(Options::GetInstance()->getValueToInt("music")-1));
		Sound::setPorcentVolumeByCategory("musicgame", (20*(Options::GetInstance()->getValueToInt("music")))/3);
		Sound::setPorcentVolumeByCategory("effect", 20*(Options::GetInstance()->getValueToInt("effects")));
		Sound::setPorcentVolumeByCategory("high_effect", 20*(Options::GetInstance()->getValueToInt("effects")+1));
		Sound::setPorcentVolumeByCategory("low_effect", 20*(Options::GetInstance()->getValueToInt("effects")-1));
		
		Sounds::GetInstance()->addSoundFromData("beep0", "effect", "sound/beep0.ogg", true);
		Sounds::GetInstance()->addSoundFromData("beep1", "effect", "sound/beep1.ogg", true);
		Sounds::GetInstance()->addSoundFromData("click0", "effect", "sound/click0.ogg", true);
		Sounds::GetInstance()->addSoundFromData("click1", "effect", "sound/click1.ogg", true);
		// fonts
		Fonts::GetInstance()->addFontBitMap("font-titles", (string)DATA_DIR + "/fonts/font-titles.png", false);
		Fonts::GetInstance()->addFontBitMap("font-wall0", (string)DATA_DIR + "/fonts/font-wall0.png", false);
		Fonts::GetInstance()->addFontBitMap("font-wall1", (string)DATA_DIR + "/fonts/font-wall1.png", false);
		Fonts::GetInstance()->addFontBitMap("font-wall2", (string)DATA_DIR + "/fonts/font-wall2.png", false);
		Fonts::GetInstance()->addFontBitMap("font-wall3", (string)DATA_DIR + "/fonts/font-wall3.png", false);
		Fonts::GetInstance()->addFontBitMap("font-wall4", (string)DATA_DIR + "/fonts/font-wall4.png", false);
		Fonts::GetInstance()->addFontBitMap("font-wall5", (string)DATA_DIR + "/fonts/font-wall5.png", false);
		Fonts::GetInstance()->addFontBitMap("font-computer", (string)DATA_DIR + "/fonts/font-computer.png");
		Fonts::GetInstance()->addFontBitMap("font-texts", (string)DATA_DIR + "/fonts/font-texts.png");
		
		TypeObjectsScenary::GetInstance()->load();
		
		Language::GetInstance()->setLang(Options::GetInstance()->getValue("lang"));
		
		loadScenes();
		modeScreen();
		
		// messagebox, input and alerts
		
		createStaticsElements_InScene();
		Scene::msg_fontTitle = "font-computer";
		Scene::msg_fontText = "font-texts";
		Scene::msg_fontButtons = "font-computer";
		Scene::msg_fontEntry = "font-computer";
		
		Cursor::GetInstance()->setUseImageCursor(true);
		Cursor::GetInstance()->addCursor("default", "/cursors/default.png");
		Cursor::GetInstance()->addCursor("help", "/cursors/help.png");
		Cursor::GetInstance()->addCursor("rotate", "/cursors/rotate.png");
		Cursor::GetInstance()->setCursor("default");
		Cursor::GetInstance()->setFontText("font-texts");
		Cursor::GetInstance()->setScaleAlt(0.8);
		Cursor::GetInstance()->setSizeBorder(2);
	}
}

void Application::createStaticsElements_InScene () {
	char tmp[200];
	
	Scene::hasMsg_bg = true;
	Scene::hasMsg_title = false;
	
	Scene::msg_bgMessage = new Element();
	Scene::msg_bgMessage->setAlign(ALIGN_CENTER);
	Scene::msg_bgMessage->setVAlign(VALIGN_CENTER);
	Scene::msg_bgMessage->setXY(World::width/2, 250);
	
	Scene::msg_bgMessage->addFrameFileFromData("/windows/" + Language::GetInstance()->getFilename("showmessage", "png"));
	
	Scene::msg_bgAlert = new Element();
	Scene::msg_bgAlert->setAlign(ALIGN_CENTER);
	Scene::msg_bgAlert->setVAlign(VALIGN_CENTER);
	Scene::msg_bgAlert->setXY(World::width/2, 250);
	
	Scene::msg_bgAlert->addFrameFileFromData("/windows/" + Language::GetInstance()->getFilename("showalert", "png"));

	strcpy(tmp, "Text");

	Scene::msg_text = new Element();
	Scene::msg_text->setAlign(ALIGN_CENTER);
	Scene::msg_text->setVAlign(VALIGN_TOP);
	Scene::msg_text->setX(World::width/2);
	Scene::msg_text->setY(250);
	
	Scene::msg_text->addFrameText(Fonts::GetInstance()->getDefaultFont(), tmp, ALIGN_CENTER);
	
	Scene::posXBAcceptInAlert = 263;
	Scene::posXBCancelInAlert = 540;
	
	Scene::msg_bAccept = new Button();
	Scene::msg_bAccept->addParameter("type", "accept");
	Scene::msg_bAccept->setScales(0.4, 0.45);
	Scene::msg_bAccept->setAlign(ALIGN_CENTER);
	Scene::msg_bAccept->setVAlign(VALIGN_CENTER);
	Scene::msg_bAccept->setX(World::width/4);
	Scene::msg_bAccept->setY(383);
	Scene::msg_bAccept->setRGB(0,255,0);
	
	if (Language::GetInstance()->getText("accept")!="-") {
		sprintf(tmp, Language::GetInstance()->getText("accept").c_str());
	} else {
		sprintf(tmp, "Accept");
	}
	Scene::msg_bAccept->imageOut(Fonts::GetInstance()->getSurface_TextBitMap(Fonts::GetInstance()->getDefaultFont(), ALIGN_CENTER, tmp));
	Scene::msg_bAccept->setAnimation("out");
	
	Scene::msg_bCancel = new Button();
	Scene::msg_bCancel->addParameter("type", "cancel");
	Scene::msg_bCancel->setScales(0.4, 0.45);
	Scene::msg_bCancel->setAlign(ALIGN_CENTER);
	Scene::msg_bCancel->setVAlign(VALIGN_CENTER);
	Scene::msg_bCancel->setX((World::width/4)*3);
	Scene::msg_bCancel->setY(383);
	Scene::msg_bCancel->setRGB(255,0,0);
	
	if (Language::GetInstance()->getText("cancel")!="-") {
		sprintf(tmp, Language::GetInstance()->getText("cancel").c_str());
	} else {
		sprintf(tmp, "Cancel");
	}
	
	Scene::msg_bCancel->imageOut(Fonts::GetInstance()->getSurface_TextBitMap(Fonts::GetInstance()->getDefaultFont(), ALIGN_CENTER, tmp));
	Scene::msg_bCancel->setAnimation("out");
	
	Scene::msg_entry = new Entry(NULL, 550, 40, 0, 10);
	Scene::msg_entry->setNoSigns(true);
	Scene::msg_entry->setX((World::width/2)-200);
	Scene::msg_entry->setY(310);
	Scene::msg_entry->setActive(true);
	Scene::msg_entry->setDrawBox(false);
}

void Application::loadScenes() {
	s_menu = new SceneMenu();
	s_menu->setId(1);
	s_menu->setWorld((World*)this);
	addScene("menu", s_menu);
	
	s_game = new SceneGame();
	s_game->setId(2);
	s_game->setWorld((World*)this);
	addScene("game", s_game);
	
	s_editgame = new SceneEditGame();
	s_editgame->setId(3);
	s_editgame->setWorld((World*)this);
	addScene("editgame", s_editgame);
	
	s_createmission = new SceneCreateMission();
	s_createmission->setId(4);
	s_createmission->setWorld((World*)this);
	addScene("createmission", s_createmission);
	
	s_mainanim = new SceneAnimation();
	s_mainanim->setId(5);
	s_mainanim->setWorld((World*)this);
	s_mainanim->setDirectory(string(DATA_DIR) + "/animation");
	s_mainanim->setNameSceneWhenScape("menu");
	s_mainanim->setDrawCursor(false);
	addScene("anim", s_mainanim);
	
	s_infotown = new SceneInfoTown();
	s_infotown->setId(6);
	s_infotown->setWorld((World*)this);
	s_infotown->setNameSceneWhenScape("game");
	addScene("infotown", s_infotown);
	
	s_changelang = new SceneChangeLanguage();
	s_changelang->setId(7);
	s_changelang->setWorld((World*)this);
	addScene("changelang", s_changelang);
	
	s_credits = new SceneCredits();
	s_credits->setId(8);
	s_credits->setWorld((World*)this);
	s_credits->setDrawCursor(false);
	addScene("credits", s_credits);
	
}

void Application::execute() {
	
	if (!existDataDirectory) {
		printf("Don't exist directory data: %s\n", DATA_DIR);
		return;
	}
	
	if (Options::GetInstance()->getValue("scene") != "") {
		currentScene = getScene(Options::GetInstance()->getValue("scene"))->getId();
	} else {
		if (changeLanguage) {
			currentScene = getScene("changelang")->getId();
		} else {
			currentScene = getScene("anim")->getId();
		}
	}

	int done = 0;
	
	while (done == 0) {

		switch (currentScene) {
			// *********************
			// MENU
			// *********************
			case 1:
				if (!s_menu->getIsLoad()) { s_menu->load(); }
				if (s_menu->drawScene()) {
					int idNextScene = loadScene(s_menu->getNextScene());
					if ( idNextScene == -1 ) {
						done = 1;
					} else {
						currentScene = idNextScene;
					}
					s_menu->unLoad();
				}
			break;
			// *********************
			// GAME
			// *********************
			case 2:
				if (!s_game->getIsLoad()) { s_game->load(); }
				if (s_game->drawScene()) {
					int idNextScene = loadScene(s_game->getNextScene());
					if ( idNextScene == -1 ) {
						done = 1;
					} else {
						currentScene = idNextScene;
					}
					s_game->unLoad();
				}
			break;
			// *********************
			// EDIT GAME
			// *********************
			case 3:
				if (!s_editgame->getIsLoad()) { s_editgame->load(); }
				if (s_editgame->drawScene()) {
					int idNextScene = loadScene(s_editgame->getNextScene());
					if ( idNextScene == -1 ) {
						done = 1;
					} else {
						currentScene = idNextScene;
					}
					s_editgame->unLoad();
				}
			break;
			// *********************
			// EDIT CREATE MISION
			// *********************
			case 4:
				if (!s_createmission->getIsLoad()) { s_createmission->load(); }
				if (s_createmission->drawScene()) {
					int idNextScene = loadScene(s_createmission->getNextScene());
					if ( idNextScene == -1 ) {
						done = 1;
					} else {
						currentScene = idNextScene;
					}
					s_createmission->unLoad();
				}
			break;
			// *********************
			// ANIMATION
			// *********************
			case 5:
				if (!s_mainanim->getIsLoad()) { s_mainanim->load(); }
				if (s_mainanim->drawScene()) {
					int idNextScene = loadScene(s_mainanim->getNextScene());
					if ( idNextScene == -1 ) {
						done = 1;
					} else {
						currentScene = idNextScene;
					}
					s_mainanim->unLoad();
				}
			break;
			// *********************
			// INFOTOWN
			// *********************
			case 6:
				if (!s_infotown->getIsLoad()) { s_infotown->load(); }
				if (s_infotown->drawScene()) {
					int idNextScene = loadScene(s_infotown->getNextScene());
					if ( idNextScene == -1 ) {
						done = 1;
					} else {
						currentScene = idNextScene;
					}
					s_infotown->unLoad();
				}
			break;
			// *********************
			// CHANGELANGUAGE
			// *********************
			case 7:
				if (!s_changelang->getIsLoad()) { s_changelang->load(); }
				if (s_changelang->drawScene()) {
					int idNextScene = loadScene(s_changelang->getNextScene());
					if ( idNextScene == -1 ) {
						done = 1;
					} else {
						currentScene = idNextScene;
					}
					s_changelang->unLoad();
				}
			break;
			// *********************
			// CREDITS
			// *********************
			case 8:
				if (!s_credits->getIsLoad()) { s_credits->load(); }
				if (s_credits->drawScene()) {
					int idNextScene = loadScene(s_credits->getNextScene());
					if ( idNextScene == -1 ) {
						done = 1;
					} else {
						currentScene = idNextScene;
					}
					s_credits->unLoad();
				}
			break;
		}

		Timer::GetInstance()->waitFrame();
			
	}
	
	unLoad();
		
}
