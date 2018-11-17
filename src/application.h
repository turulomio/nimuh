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

#ifndef APPLICATION_H_
#define APPLICATION_H_

#include <SDL.h>
#include <SDL_mixer.h>
#include "martian.h"
#include "user.h"
#include "missions.h"
#include "cursor.h"
#include "sceneanimation.h"
#include "scene_menu.h"
#include "scene_game.h"
#include "scene_editgame.h"
#include "scene_createmissions.h"
#include "scene_infotown.h"
#include "scene_changelanguage.h"
#include "scene_credits.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <string>

#include <cmath>
#include <iostream>
#include <vector>
#include <map>

using namespace std;
using namespace Martian;


class Application : public World {
	
private:
	SceneGame *s_game;
	SceneMenu *s_menu;
	SceneEditGame *s_editgame;
	SceneAnimation *s_mainanim;
	SceneCreateMission *s_createmission;
	SceneInfoTown *s_infotown;
	SceneChangeLanguage *s_changelang;
	SceneCredits *s_credits;

	bool changeLanguage;
	
	void createStaticsElements_InScene ();
public:	

	Application(int w, int h, string titleWindow);
	void loadScenes();
	void execute();

};


#endif /* APPLICATION_H_ */
