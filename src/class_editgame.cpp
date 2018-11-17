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
 
#include "class_editgame.h"

/*****************************
**
** CLASE Door
**
******************************/
	

EditDoor::EditDoor() : Door () {
		
}

EditDoor::~EditDoor () {
	unLoad();
}

bool EditDoor::setForcePosition(BoardPosition p) { 
	if (!p.out) { 
		if ( (p.x==0) || (p.x==EditBoard::GetInstance()->getCols()-1)
				|| (p.y==0) || (p.y==EditBoard::GetInstance()->getRows()-1) ) {
			xBoard = p.x; 
			yBoard = p.y; 
			if (p.x==0) {
				setDoorPosition(LEFT);
				setX(Plot::GetInstance()->getX(p.x,p.y)+(20*getCurrentScaleX())); 
				setY(Plot::GetInstance()->getY(p.x,p.y)-heightElement); 
			}
			if (p.x==EditBoard::GetInstance()->getCols()-1) {
				setDoorPosition(RIGHT);
				setX(Plot::GetInstance()->getX(p.x,p.y)-(30*getCurrentScaleX())); 
				setY(Plot::GetInstance()->getY(p.x,p.y)-heightElement); 
			}
			if (p.y==0) {
				setDoorPosition(UP);
				setX(Plot::GetInstance()->getX(p.x,p.y)-(23*getCurrentScaleX())); 
				setY(Plot::GetInstance()->getY(p.x,p.y)-heightElement); 
			}
			if (p.y==EditBoard::GetInstance()->getRows()-1) {
				setDoorPosition(DOWN);
				setX(Plot::GetInstance()->getX(p.x,p.y)+(25*getCurrentScaleX()));
				setY(Plot::GetInstance()->getY(p.x,p.y)-heightElement); 
			}
			
			return true; 
			
		} else {
			return false; 
		}
	}
	return false; 
}

bool EditDoor::setForcePosition(int x, int y) { 
	BoardPosition p; 
	p.x=x; 
	p.y=y; 
	p.out = !EditBoard::GetInstance()->positionIsOnBoard(p); 
	return setForcePosition(p); 
}

/*****************************
**
** CLASE EditScenary
**
******************************/

EditScenary::EditScenary() : Scenary () {
	editable = true;
}

EditScenary::~EditScenary () {
	unLoad();
}

void EditScenary::setTypeTiled(int t) {
    if ( Missions::GetInstance()->currentLevel->existFile("tile_down.png") 
        && Missions::GetInstance()->currentLevel->existFile("tile_up.png") ) {
                                                                           
    	tileRight->changeFrameFile(0, Missions::GetInstance()->currentLevel->getPath() + "/tile_down.png");
    	tileRightUp->changeFrameFile(0, Missions::GetInstance()->currentLevel->getPath() + "/tile_up.png");
    	tileLeft->changeFrameFile(0, Missions::GetInstance()->currentLevel->getPath() + "/tile_down.png");
    	tileLeftUp->changeFrameFile(0, Missions::GetInstance()->currentLevel->getPath() + "/tile_up.png");
    	
    	EditBoard::GetInstance()->getSceneEditGame()->typeTiled->setSensitive(false);
    	EditBoard::GetInstance()->tiledOfLevel = true;
    	
    } else {
    	if (t<BoardInfo::GetInstance()->getValueToInt("NTYPES_TILED")) {	
    		typeTiled = t;
    	} else {
    		typeTiled = 0;
    	}
    	
    	char tmp[4];
    	sprintf(tmp, "%d", typeTiled);
    	
    	tileRight->changeFrameFileFromData(0, "/scenary/tile_"+string(tmp)+"_down.png");
    	tileRightUp->changeFrameFileFromData(0, "/scenary/tile_"+string(tmp)+"_up.png");
    	tileLeft->changeFrameFileFromData(0, "/scenary/tile_"+string(tmp)+"_down.png");
    	tileLeftUp->changeFrameFileFromData(0, "/scenary/tile_"+string(tmp)+"_up.png");
    	
    	EditBoard::GetInstance()->getSceneEditGame()->typeTiled->setSensitive(true);
    	EditBoard::GetInstance()->tiledOfLevel = false;
    	
   }
}

void EditScenary::setTypeTerrain(int t) {
     
    if ( Missions::GetInstance()->currentLevel->existFile("terrain.jpg") ) {
                                                                           
        terrainOpened->changeFrameFile(0, Missions::GetInstance()->currentLevel->getPath() + "/terrain.jpg");
        
        EditBoard::GetInstance()->getSceneEditGame()->typeTerrain->setSensitive(false);
        EditBoard::GetInstance()->terrainOfLevel = true;
        
    } else {
    	if (t<BoardInfo::GetInstance()->getValueToInt("NTYPES_TERRAIN")) {	
    		typeTerrain = t;
    	} else {
    		typeTerrain = 0;
    	}
    	
    	char tmp[4];
    	sprintf(tmp, "%d", typeTerrain);
    	
    	terrainOpened->changeFrameFileFromData(0, "/scenary/terrain"+string(tmp)+".jpg");
    	
    	EditBoard::GetInstance()->getSceneEditGame()->typeTerrain->setSensitive(true);
    	EditBoard::GetInstance()->terrainOfLevel = false;
    	
    }
}

void EditScenary::setTypeWall(int t) {
     
    if ( Missions::GetInstance()->currentLevel->existFile("wallscenary.png") ) {
                                                                           
        wallLeft->changeFrameFile(0, Missions::GetInstance()->currentLevel->getPath() + "/wallscenary.png");
		wallRight->changeFrameFile(0, Missions::GetInstance()->currentLevel->getPath() + "/wallscenary.png");
        EditBoard::GetInstance()->wallScennaryOfLevel = true;
        
    } else {
    	if (t<BoardInfo::GetInstance()->getValueToInt("NTYPES_WALLSCENARY")) {	
    		typeWall = t;
    	} else {
    		typeWall = 0;
    	}
    	
    	char tmp[4];
    	sprintf(tmp, "%d", typeWall);
    	
    	wallLeft->changeFrameFileFromData(0, "/scenary/wallscenary"+string(tmp)+".png");
		wallRight->changeFrameFileFromData(0, "/scenary/wallscenary"+string(tmp)+".png");
    	
    	EditBoard::GetInstance()->wallScennaryOfLevel = false;
    	
    }
}

void EditScenary::draw() {
	if (type==SCENARY_CLOSED) {
		drawScenaryClosed();
	} else {
		drawScenaryOpened();
	}
}

void EditScenary::drawScenaryClosed() {
	wallLeft->draw();
	wallRight->draw();

	paintTiled();
	
	shadowWall->draw();
		
	if (editable && showGuides) {
		guideLeft->draw();
		guideRight->draw();
	}
	
	for (int i=0; i<(int)objects.size(); i++) {
		objects[i]->draw();
	}
	
	for (int i=0; i<(int)objects.size(); i++) {
		objects[i]->drawIcons();
	}

}

void EditScenary::drawScenaryOpened() {
	terrainOpened->draw();
	
	if (editable && showGuides) {
		guideLeft->draw();
		guideRight->draw();
	}
	
	for (int i=0; i<(int)objects.size(); i++) {
		objects[i]->draw();
	}
	paintTiled();
	
	for (int i=0; i<(int)objects.size(); i++) {
		objects[i]->drawIcons();
	}
}

void EditScenary::paintTiled() {
	int x, y;
	
	for (y=0; y<nVerticalTiles; y++) {
		for (x=0; x<EditBoard::GetInstance()->getCols()+1; x++) {
			if (y==nVerticalTiles-1) {
				tileRightUp->setX(Plot::GetInstance()->getX(x,0)-1);
				tileRightUp->setY(Plot::GetInstance()->getY(x,0)+38-(y*separatedTilesClosed));
				tileRightUp->draw();
				tileLeftUp->setX(-Plot::GetInstance()->getX(x,0)+1);
				tileLeftUp->setY(Plot::GetInstance()->getY(x,0)+38-(y*separatedTilesClosed));
				tileLeftUp->draw();
			} else {
				tileRight->setX(Plot::GetInstance()->getX(x,0)-1);
				tileRight->setY(Plot::GetInstance()->getY(x,0)+38-(y*separatedTilesClosed));
				tileRight->draw();
				tileLeft->setX(-Plot::GetInstance()->getX(x,0)+1);
				tileLeft->setY(Plot::GetInstance()->getY(x,0)+38-(y*separatedTilesClosed));
				tileLeft->draw();
			}
		}
	}
}

/*****************************
**
** CLASE EditBoard
**
******************************/

EditBoard* EditBoard::instance = NULL;

EditBoard::EditBoard() : Group () {
	multiLanguage = false;
	rows = 6;
	cols = 6;
	typeFloor = 0;
	typeWall = 0;
	typePavement = 0;
	indexz = 0;
	posX = World::width/2;
	posY = POSITION_Y_BOARD;
	typeSize = BOARD_6X6;
	hasEnemy1 = false;
	hasEnemy2 = false;
	hasEnemy3 = false;
	hasBlackHole0 = false;
	hasBlackHole1 = false;
	hasKey = false;
	hasTrap = false;
	directionKey = "right";
	hasTray = false;
	
	town.name="";
	town.province="";
	town.nickname="";
	
	helpName = "";
	
	infoTown.clear();
		
	typeMusic = -1;
	
	hasMap = false;
	fileFromDataMap = "";
	fileFromLevelMap = "";
	
	wallsOfLevel = false;
	terrainOfLevel = false;
	wallScennaryOfLevel = false;
	musicOfLevel = false;
	pavementOfLevel = false;
	floorOfLevel = false;
	tiledOfLevel = false;
	
}

EditBoard* EditBoard::GetInstance () {
	if ( instance == NULL ) {
		instance = new EditBoard();
	}
	return instance;	
}

void EditBoard::setTypeWall(int t) {
     
    if ( Missions::GetInstance()->currentLevel->existFile("wall_h.png") 
        && Missions::GetInstance()->currentLevel->existFile("wall_v.png") ) {
                                                                          
    	wallBottom->changeFrameFile(0, Missions::GetInstance()->currentLevel->getPath()+"/wall_h.png");
    	wallRight->changeFrameFile(0, Missions::GetInstance()->currentLevel->getPath()+"/wall_v.png");
    	sceneeditgame->typeWall->setSensitive(false);
    	wallsOfLevel = true;
    	
    } else {
    	if (t<BoardInfo::GetInstance()->getValueToInt("NTYPES_WALL")) {
    		typeWall = t;
    	} else {
    		typeWall = 0;
    	}
    	
    	char tmp[128];
    	
    	sprintf(tmp, "/board/wall_%d_h.png", typeWall);
    	wallBottom->changeFrameFileFromData(0, tmp);
    	
    	sprintf(tmp, "/board/wall_%d_v.png", typeWall);
    	wallRight->changeFrameFileFromData(0, tmp);
    	
    	sceneeditgame->typeWall->setSensitive(true);
    	wallsOfLevel = false;
    }
	
}

void EditBoard::setTypeFloor(int t) {
     
    if ( Missions::GetInstance()->currentLevel->existFile("floor0.png") 
        && Missions::GetInstance()->currentLevel->existFile("floor1.png") ) {
    	floor0->changeFrameFile(0, Missions::GetInstance()->currentLevel->getPath()+"/floor0.png");
    	floor1->changeFrameFile(0, Missions::GetInstance()->currentLevel->getPath()+"/floor1.png");
    	
    	sceneeditgame->typeFloor->setSensitive(false);
    	floorOfLevel = true;
    	
    } else {
    	if (t<BoardInfo::GetInstance()->getValueToInt("NTYPES_FLOOR")) {	
    		typeFloor = t;
    	} else {
    		typeFloor = 0;
    	}
    	
    	floor0->changeFrameFileFromData(0, "/board/floor", "png", typeFloor*2);
    	floor1->changeFrameFileFromData(0, "/board/floor", "png", (typeFloor*2)+1);
    	
    	sceneeditgame->typeFloor->setSensitive(true);
    	floorOfLevel = false;
    }
	
}

void EditBoard::setTypePavement(int t) {
     
    if ( Missions::GetInstance()->currentLevel->existFile("pavement_bottom.png") 
        && Missions::GetInstance()->currentLevel->existFile("pavement_top.png") ) {
                                                                               
    	pavementTop->changeFrameFile(0, Missions::GetInstance()->currentLevel->getPath()+"/pavement_top.png");
    	pavementBottom->changeFrameFile(0, Missions::GetInstance()->currentLevel->getPath()+"/pavement_bottom.png");
    	
    	sceneeditgame->typePavement->setSensitive(false);
    	pavementOfLevel = true;
    	
    } else {
    	if (t<BoardInfo::GetInstance()->getValueToInt("NTYPES_PAVEMENT")) {	
    		typePavement = t;
    	} else {
    		typePavement = 0;
    	}
    	
    	char tmp[128];
    	
    	sprintf(tmp, "/board/pavement_%d_top.png", typePavement);
    	pavementTop->changeFrameFileFromData(0, tmp);
    	
    	sprintf(tmp, "/board/pavement_%d_bottom.png", typePavement);
    	pavementBottom->changeFrameFileFromData(0, tmp);
    	
    	sceneeditgame->typePavement->setSensitive(true);
    	pavementOfLevel = false;
    	
    }
}

void EditBoard::setTypeSize(int t) {
	float s = 1.0;
	typeSize = t;
	int oldRows = rows;
	int oldCols = cols;
	switch(t) {
		case BOARD_6X6:
			pavementBottom->setY(179);
			s = 1.0;
			BoardScale::GetInstance()->setScale(s);
			cols = 6;
			rows = 6;
		break;
		case BOARD_7X7:
			pavementBottom->setY(178);
			s = 0.86;
			BoardScale::GetInstance()->setScale(s);
			cols = 7;
			rows = 7;
		break;
		case BOARD_8X8:
			pavementBottom->setY(182);
			s = 0.76;
			BoardScale::GetInstance()->setScale(s);
			cols = 8;
			rows = 8;
		break;
		case BOARD_9X9:
			pavementBottom->setY(177);
			s = 0.67;
			BoardScale::GetInstance()->setScale(s);
			cols = 9;
			rows = 9;
		break;
		case BOARD_10X10:
			pavementBottom->setY(178);
			s = 0.61;
			BoardScale::GetInstance()->setScale(s);
			cols = 10;
			rows = 10;
		break;
	}
	
	floor0->setCurrentScale(s);
	floor1->setCurrentScale(s);
	trap->setCurrentScale(s);

	scenary->scaleTiles(s);
	
	wallRight->setCurrentScale(s);
	wallRight->setScaleHeightElement(s);
	wallRight->setScaleDisplacementX(s);
	
	wallBottom->setCurrentScale(s);
	wallBottom->setScaleHeightElement(s);
	wallBottom->setScaleDisplacementX(s);
	
	nimuh->setCurrentScale(s);
	nimuh->setScaleHeightElement(s);
	
	BoardPosition p;
	if (nimuh->getPosition().x>=cols-1) {
		p.x = cols-1;
	} else {
		p.x = nimuh->getPosition().x;
	}
	if (nimuh->getPosition().y>=rows-1) {
		p.y = rows-1;
	} else {
		p.y = nimuh->getPosition().y;
	}
	p.out = !EditBoard::GetInstance()->positionIsOnBoard(p);
	nimuh->setForcePosition(p);
	
	enemy1->setCurrentScale(s);
	enemy1->setScaleHeightElement(s);
		
	if (enemy1->getPosition().x>=cols-1) {
		p.x = cols-1;
	} else {
		p.x = enemy1->getPosition().x;
	}
	if (enemy1->getPosition().y>=rows-1) {
		p.y = rows-1;
	} else {
		p.y = enemy1->getPosition().y;
	}
	p.out = !EditBoard::GetInstance()->positionIsOnBoard(p);
	
	enemy1->setForcePosition(p);
	
	enemy2->setCurrentScale(s);
	enemy2->setScaleHeightElement(s);
	
	if (enemy2->getPosition().x>=cols-1) {
		p.x = cols-1;
	} else {
		p.x = enemy2->getPosition().x;
	}
	if (enemy2->getPosition().y>=rows-1) {
		p.y = rows-1;
	} else {
		p.y = enemy2->getPosition().y;
	}
	p.out = !EditBoard::GetInstance()->positionIsOnBoard(p);
	
	enemy2->setForcePosition(p);
	
	enemy3->setCurrentScale(s);
	enemy3->setScaleHeightElement(s);
	
	if (enemy3->getPosition().x>=cols-1) {
		p.x = cols-1;
	} else {
		p.x = enemy3->getPosition().x;
	}
	if (enemy3->getPosition().y>=rows-1) {
		p.y = rows-1;
	} else {
		p.y = enemy3->getPosition().y;
	}
	p.out = !EditBoard::GetInstance()->positionIsOnBoard(p);
	
	enemy3->setForcePosition(p);
	
	blackHole0->setCurrentScale(s);
	blackHole0->setScaleHeightElement(s);
	
	if (blackHole0->getPosition().x>=cols-1) {
		p.x = cols-1;
	} else {
		p.x = blackHole0->getPosition().x;
	}
	if (blackHole0->getPosition().y>=rows-1) {
		p.y = rows-1;
	} else {
		p.y = blackHole0->getPosition().y;
	}
	p.out = !EditBoard::GetInstance()->positionIsOnBoard(p);
	
	blackHole0->setForcePosition(p);
	
	blackHole1->setCurrentScale(s);
	blackHole1->setScaleHeightElement(s);
	
	if (blackHole1->getPosition().x>=cols-1) {
		p.x = cols-1;
	} else {
		p.x = blackHole1->getPosition().x;
	}
	if (blackHole1->getPosition().y>=rows-1) {
		p.y = rows-1;
	} else {
		p.y = blackHole1->getPosition().y;
	}
	p.out = !EditBoard::GetInstance()->positionIsOnBoard(p);
	
	blackHole1->setForcePosition(p);
	
	door->setCurrentScale(s);
	//door->setScaleHeightElement(s);
	
	if (door->getPosition().x>=oldCols-1) {
		p.x = cols-1;
	} else {
		p.x = door->getPosition().x;
	}
	if (door->getPosition().y>=oldRows-1) {
		p.y = rows-1;
	} else {
		p.y = door->getPosition().y;
	}
	p.out = !EditBoard::GetInstance()->positionIsOnBoard(p);
	
	door->setForcePosition(p);
	
	key->setCurrentScale(s);
	key->setScaleHeightElement(s);
	
	if (key->getPosition().x>=cols-1) {
		p.x = cols-1;
	} else {
		p.x = key->getPosition().x;
	}
	if (key->getPosition().y>=rows-1) {
		p.y = rows-1;
	} else {
		p.y = key->getPosition().y;
	}
	p.out = !EditBoard::GetInstance()->positionIsOnBoard(p);
	
	key->setForcePosition(p);
	
	doorKeyBottom->setCurrentScale(s);
	doorKeyBottom->setScaleHeightElement(s);
	
	if (doorKeyBottom->getPosition().x>=cols-1) {
		p.x = cols-1;
	} else {
		p.x = doorKeyBottom->getPosition().x;
	}
	if (doorKeyBottom->getPosition().y>=rows-1) {
		p.y = rows-1;
	} else {
		p.y = doorKeyBottom->getPosition().y;
	}
	p.out = !EditBoard::GetInstance()->positionIsOnBoard(p);
	
	doorKeyBottom->setForcePosition(p);
	
	doorKeyRight->setCurrentScale(s);
	doorKeyRight->setScaleHeightElement(s);
	
	if (doorKeyRight->getPosition().x>=cols-1) {
		p.x = cols-1;
	} else {
		p.x = doorKeyRight->getPosition().x;
	}
	if (doorKeyRight->getPosition().y>=rows-1) {
		p.y = rows-1;
	} else {
		p.y = doorKeyRight->getPosition().y;
	}
	p.out = !EditBoard::GetInstance()->positionIsOnBoard(p);
	
	doorKeyRight->setForcePosition(p);
	
	tray->setCurrentScale(s);
	tray->setScaleHeightElement(s);
	
	if (tray->getPosition().x>=cols-1) {
		p.x = cols-1;
	} else {
		p.x = tray->getPosition().x;
	}
	if (tray->getPosition().y>=rows-1) {
		p.y = rows-1;
	} else {
		p.y = tray->getPosition().y;
	}
	p.out = !EditBoard::GetInstance()->positionIsOnBoard(p);
	
	tray->setForcePosition(p);
	
	floorOn->setCurrentScale(s);
	floorOn->setScaleHeightElement(s);

	MouseMapTile::GetInstance()->createMap();

}

void EditBoard::loadLevel() {

	clear();
	
	string f = Hash::getPathData() + "missions/" + Missions::GetInstance()->currentMission->getDirectory() + "/" + Missions::GetInstance()->currentLevel->getDirectory() + "/level.xml";
	
	parseEditScreenXML((char*)f.c_str());


}

bool EditBoard::save() {
     
    // verify
        
    if ( (hasBlackHole0 && !hasBlackHole1) || (!hasBlackHole0 && hasBlackHole1) ) {
         sceneeditgame->showMessageBox(Language::GetInstance()->getText("info"), Language::GetInstance()->getText("twoblackhole"), SCENE_EDITGAME_MAIN);
         return false;
    }
    
    if (!hasEnemy1 && !hasEnemy2) {
         sceneeditgame->showMessageBox(Language::GetInstance()->getText("info"), Language::GetInstance()->getText("oneenemy"), SCENE_EDITGAME_MAIN);
         return false;
    }

    char tmp_val[128];

	string file = Hash::getPathData() + "missions/" + Missions::GetInstance()->currentMission->getDirectory() + "/" + Missions::GetInstance()->currentLevel->getDirectory() + "/level.xml";
	
	string chainFile = "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n<level>\n";
	
	if (multiLanguage) {
		chainFile += "\t<multilanguage value=\"true\" />\n";
	}
	
	chainFile += "\t<data>\n";
	
	chainFile += "\t\t<town name=\"" + town.name + "\" province=\"" + town.province + "\">\n";
	
	for (int i=0; i<(int)infoTown.size(); i++) {
 	    chainFile += "\t\t\t<information button=\"" + infoTown[i].button + "\" title=\"" + infoTown[i].title + "\" text=\"" + WorkingData::GetInstance()->replace(infoTown[i].text, "|", " ") + "\" />\n";
    }
	
	chainFile += "\t\t</town>\n";
	
    if (hasTray) {
		for (int i=0; i<(int)infoTray.size(); i++) {
        	chainFile += "\t\t<info-tray lang=\"" + infoTray[i].lang + "\" title=\"" + infoTray[i].title + "\" text=\"" + infoTray[i].text + "\" />\n";
		}
    }
    
    chainFile += "\t</data>\n";
    
    if (hasMap) {
		if (fileFromDataMap!="") {
        	chainFile += "\t<map file-fromdata=\"" + fileFromDataMap + "\" />\n";
		} else {
			chainFile += "\t<map file-fromlevel=\"" + fileFromLevelMap + "\" />\n";
		}
		for (int i=0; i<(int)map.size(); i++) {
			chainFile += "\t\t<texts-map lang=\"" + map[i].lang + "\" title-1=\"" + map[i].title1 + "\" text-1=\"" + map[i].text1 + "\" title-2=\"" + map[i].title2 + "\" text-2=\"" + map[i].text2 + "\" distance-second-text=\"" + map[i].distanceSecondText + "\" />\n";
		}
		chainFile += "\t</map>\n";
    }
    
    string tsize = "6x6";
	switch(typeSize) {
		case BOARD_6X6:
			tsize = "6x6";
		break;
		case BOARD_7X7:
			tsize = "7x7";
		break;
		case BOARD_8X8:
			tsize = "8x8";
		break;
		case BOARD_9X9:
			tsize = "9x9";
		break;
		case BOARD_10X10:
			tsize = "10x10";
		break;
    }
    
    sprintf (tmp_val, "\t<board type=\"%s\" floor=\"%d\" wall=\"%d\" pavement=\"%d\" />\n", tsize.c_str(), typeFloor, typeWall, typePavement);   
    chainFile += tmp_val;
    
	if (typeMusic>=0) {
       sprintf (tmp_val, "\t<music type=\"%d\" />\n", typeMusic);
       chainFile += tmp_val;       
    }
	
    if (helpName!="") {
       chainFile += "\t<help name=\"" + helpName + "\" />\n";
    }
        
    chainFile += scenary->toXML();
    
    chainFile += "\t<objects>\n";
    
    if (hasBlackHole0) {
		sprintf (tmp_val, "\t\t<blackhole0 x=\"%d\" y=\"%d\" />\n", blackHole0->getXBoard(), blackHole0->getYBoard());
    	chainFile += tmp_val;  
    }
    if (hasBlackHole1) {
		sprintf (tmp_val, "\t\t<blackhole1 x=\"%d\" y=\"%d\" />\n", blackHole1->getXBoard(), blackHole1->getYBoard());
    	chainFile += tmp_val;
    }
    if (hasTrap) {
		sprintf (tmp_val, "\t\t<trap x=\"%d\" y=\"%d\" />\n", posTrap.x, posTrap.y);
    	chainFile += tmp_val;  
    }
    if (hasTray) {
		sprintf (tmp_val, "\t\t<tray x=\"%d\" y=\"%d\" />\n", tray->getXBoard(), tray->getYBoard());
    	chainFile += tmp_val;  
    }
    if (hasKey) {
		sprintf (tmp_val, "\t\t<key x=\"%d\" y=\"%d\" />\n", key->getXBoard(), key->getYBoard());
    	chainFile += tmp_val;
    	if (directionKey=="right") {
			sprintf (tmp_val, "\t\t<door-key x=\"%d\" y=\"%d\" direction=\"right\" />\n", doorKeyRight->getXBoard(), doorKeyRight->getYBoard());
	    	chainFile += tmp_val;
        } else {
			sprintf (tmp_val, "\t\t<door-key x=\"%d\" y=\"%d\" direction=\"bottom\" />\n", doorKeyBottom->getXBoard(), doorKeyBottom->getYBoard());
	    	chainFile += tmp_val;
        }
    }
    
    chainFile += "\t</objects>\n";
    
    chainFile += "\t<position>\n";
    
    sprintf (tmp_val, "\t\t<exit x=\"%d\" y=\"%d\" />\n", door->getXBoard(), door->getYBoard());
    chainFile += tmp_val;
    
    sprintf (tmp_val, "\t\t<player x=\"%d\" y=\"%d\" />\n", nimuh->getXBoard(), nimuh->getYBoard());
    chainFile += tmp_val;
    
	if (hasEnemy1) {
    	sprintf (tmp_val, "\t\t<enemy1 x=\"%d\" y=\"%d\" />\n", enemy1->getXBoard(), enemy1->getYBoard());
    	chainFile += tmp_val;
	}
	
	if (hasEnemy2) {
		sprintf (tmp_val, "\t\t<enemy2 x=\"%d\" y=\"%d\" />\n", enemy2->getXBoard(), enemy2->getYBoard());
    	chainFile += tmp_val;
	}
	
	if (hasEnemy3) {
		sprintf (tmp_val, "\t\t<enemy3 x=\"%d\" y=\"%d\" />\n", enemy3->getXBoard(), enemy3->getYBoard());
    	chainFile += tmp_val;
	}
    
    chainFile += "\t</position>\n";
    
    chainFile += "\t<walls>\n";
    
    int x=0, y=0;
    string w="";
    bool todo = false;
	for (y=0; y<rows; y++) {
        for (x=0; x<cols; x++) {
            w="";
            todo = false;
            if ( hasWallRight(x, y) ) {
                 w = w + " right=\"true\"";
                 todo = true;
            }
            if ( hasWallBottom(x, y) ) {
                 w = w + " bottom=\"true\"";
                 todo = true;
            }
            if (todo) {
               sprintf (tmp_val, "\t\t<wall x=\"%d\" y=\"%d\"%s />\n", x, y, w.c_str());
               chainFile += tmp_val;
            }
       }
	}
	
	chainFile += "\t</walls>\n";

    chainFile += "</level>\n";
    
	return WorkingData::GetInstance()->createFile(file, chainFile, true);	

}

void EditBoard::clear() {

	hasEnemy1 = false;
	hasEnemy2 = false;
	hasEnemy3 = false;
	
	hasBlackHole0 = false;
	hasBlackHole1 = false;
	
	hasKey = false;
	hasTrap = false;
	directionKey = "right";
	
	hasTray = false;
	
	for (int i=0; i<MAX_TILES_INLINE*MAX_TILES_INLINE; i++) {
		walls[i].wallBottom = false;
		walls[i].wallRight = false;
	}
	nimuh->setForcePosition(0,0);
	
	enemy1->setForcePosition(0,0);
	enemy2->setForcePosition(0,0);
	enemy3->setForcePosition(0,0);
	setTypeSize(BOARD_6X6);
	
	wallsOfLevel = false;
	wallScennaryOfLevel = false;
	terrainOfLevel = false;
	musicOfLevel = false;
	pavementOfLevel = false;
	floorOfLevel = false;
	tiledOfLevel = false;

}

void EditBoard::cleanWalls() {
	for (int i=0; i<MAX_TILES_INLINE*MAX_TILES_INLINE; i++) {
		walls[i].wallBottom = false;
		walls[i].wallRight = false;
	}
	
	hasBlackHole0 = false;
	hasBlackHole1 = false;
	
	hasKey = false;
	hasTrap = false;
	directionKey = "right";
	
	hasTray = false;
	
}

void EditBoard::cleanScenary() {
	scenary->clear();	
}

BoardPosition EditBoard::getPositionPlayer() { 
	return nimuh->getPosition(); 
}

BoardPosition EditBoard::getPositionEnemy1() { 
	return enemy1->getPosition(); 
}

BoardPosition EditBoard::getPositionEnemy2() { 
	return enemy2->getPosition(); 
}

BoardPosition EditBoard::getPositionEnemy3() { 
	return enemy3->getPosition(); 
}

void EditBoard::setBlackHole0(int x, int y) { 
	BoardPosition p; 
	p.x = x; 
	p.y = y; 
	p.out = !positionIsOnBoard(p); 
	blackHole0->setForcePosition(p); 
	hasBlackHole0 = true;
}

void EditBoard::setBlackHole1(int x, int y) { 
	BoardPosition p; 
	p.x = x; 
	p.y = y; 
	p.out = !positionIsOnBoard(p); 
	blackHole1->setForcePosition(p); 
	hasBlackHole1 = true;
}

void EditBoard::setKey(int x, int y) { 
	BoardPosition p; 
	p.x = x; 
	p.y = y; 
	p.out = !positionIsOnBoard(p); 
	key->setForcePosition(p); 
	hasKey = true;
}

void EditBoard::setDoorKey(int x, int y, string dk) { 
	BoardPosition p; 
	p.x = x; 
	p.y = y; 
	p.out = !positionIsOnBoard(p); 
	doorKeyBottom->setForcePosition(p); 
	doorKeyRight->setForcePosition(p); 
	directionKey = dk;
	hasKey = true;
}

void EditBoard::setPositionPlayer(int x, int y) { 
	BoardPosition p; 
	p.x = x; 
	p.y = y; 
	p.out = !positionIsOnBoard(p); 
	posBegPlayer = p; 
	nimuh->setForcePosition(p); 
}

void EditBoard::setPositionEnemy1(int x, int y) { 
	BoardPosition p;
	p.x = x; 
	p.y = y; 
	p.out = !positionIsOnBoard(p); 
	posBegEnemy1 = p;
	enemy1->setForcePosition(p); 
	hasEnemy1 = true;
}

void EditBoard::setPositionEnemy2(int x, int y) { 
	BoardPosition p; 
	p.x = x; 
	p.y = y; 
	p.out = !positionIsOnBoard(p); 
	posBegEnemy2 = p; 
	enemy2->setForcePosition(p); 
	hasEnemy2 = true;
}

void EditBoard::setPositionEnemy3(int x, int y) { 
	BoardPosition p; 
	p.x = x; 
	p.y = y; 
	p.out = !positionIsOnBoard(p); 
	posBegEnemy3 = p; 
	enemy3->setForcePosition(p); 
	hasEnemy3 = true;
}

void EditBoard::setPositionExit(int x, int y) { 
	BoardPosition p; 
	p.x = x; 
	p.y = y; 
	p.out = !positionIsOnBoard(p); 
	posExit= p; 
	door->setForcePosition(p); 
}

void EditBoard::setPositionTrap(int x, int y) { 
	posTrap.x = x; 
	posTrap.y = y; 
	posTrap.out = !positionIsOnBoard(posTrap); 
	hasTrap = true;
}

void EditBoard::setPositionTray(int x, int y) { 
	BoardPosition p; 
	p.x = x; 
	p.y = y; 
	p.out = !positionIsOnBoard(p); 
	tray->setInitialPosition(p);
	hasTray = true;
	sceneeditgame->handTray->setMovementNormalX(165, 500);
	sceneeditgame->btHandTray->setSensitive(true);
}

BoardPosition EditBoard::getPositionMouse() {
	
	int w = BoardScale::GetInstance()->getWTile();
	int h = BoardScale::GetInstance()->getHTile();
	
	int mouse_x, mouse_y;
	SDL_PumpEvents();
	SDL_GetMouseState(&mouse_x, &mouse_y);
	
	// impares con una columna menos
	int ncol = getCols() - (getCols()%2);
	
	int x = ( ( mouse_x - ( (int)getX() - (w/2) - ((w/2)*ncol) ) ) / w ) - ncol/2;
	
	int y = ( mouse_y - (int)getY() ) / h;
		
	int off_x = ( ( mouse_x - ( (int)getX() - (w/2) - ((w/2)*ncol) ) ) % w );
	
	int off_y = ( mouse_y - (int)getY() ) % h;
	
	int off = MouseMapTile::GetInstance()->getPosMouse(off_x,off_y);
	
	int x0 = x+y;
	
	int y0;
	if (x==y+1) {
		y0 = -1;
	} else if (x>y+1) {
		y0 = -2;
	} else {
		y0 = abs(x-y);
	}
	
	if (off==TILE_RIGHT) {
		x0++;
	} else if (off==TILE_LEFT) {
    	if ( (x0==0) && (y0==0) ) {
        	BoardPosition p;
        	p.x = -1;
        	p.y = -1;
        	p.out = true;
        	return p;
        }
		x0--;
	} else if (off==TILE_UP) {
    	if ( (x0==0) && (y0==0) ) {
        	BoardPosition p;
        	p.x = -1;
        	p.y = -1;
        	p.out = true;
        	return p;
        }
		y0--;
	} else if (off==TILE_DOWN) {
		y0++;
	}

	BoardPosition p;
	p.x = x0;
	p.y = y0;
	p.out = !positionIsOnBoard(p);
	
	return p;
}

bool EditBoard::positionIsOnBoard(BoardPosition p) {
	if ( (p.x<0) || (p.x>=getRows()) ) {
		return false;
	}
	if ( (p.y<0) || (p.y>=getCols()) ) {
		return false;
	}
	return true;
}

bool EditBoard::hasWallBetweenCells(BoardPosition p1, BoardPosition p2) {
     if (p1.x+1 == p2.x) { // right
         return hasWallRight(p1.x, p1.y);
     } else if (p1.x-1 == p2.x) { // left
         return hasWallRight(p2.x, p2.y);
     } else if (p1.y+1 == p2.y) { // down
         return hasWallBottom(p1.x, p1.y);
     } else if (p1.y-1 == p2.y) { // up
         return hasWallBottom(p2.x, p2.y);     
     }
     return false;
}

void EditBoard::load() {
    
	multiLanguage = false;
	
	wallsOfLevel = false;
	wallScennaryOfLevel = false;
	terrainOfLevel = false;
	musicOfLevel = false;
	pavementOfLevel = false;
	floorOfLevel = false;
	tiledOfLevel = false;
	
	town.name="";
	town.province="";
	town.nickname="";
	
	infoTray.clear();
	
	helpName = "";
	
	hasMap = false;
	fileFromDataMap = "";
	fileFromLevelMap = "";

	map.clear();
	
	infoTown.clear();
		
	floorShadow = new Element();	
	floorShadow->setY(-50);
    floorShadow->setAlign(ALIGN_CENTER);
	floorShadow->addFrameFileFromData("/board/floor_shadow.png");
	floorShadow->show();
    floorShadow->setGroup(this);
	
	floor0 = new Element();	
    floor0->setAlign(ALIGN_CENTER);
	floor0->addFrameFileFromData("/board/floor_0000.png");
	floor0->show();
    floor0->setGroup(this);
	
	floor1 = new Element();	
    floor1->setAlign(ALIGN_CENTER);
	floor1->addFrameFileFromData("/board/floor_0001.png");
	floor1->show();
    floor1->setGroup(this);
	
    pavementTop = new Element();	
    pavementTop->setAlign(ALIGN_CENTER);
    pavementTop->setVAlign(VALIGN_BOTTOM);
    pavementTop->setY(186);
	pavementTop->addFrameFileFromData("/board/pavement_0_top.png");
	pavementTop->show();
    pavementTop->setGroup(this);
    
    pavementBottom = new Element();	
    pavementBottom->setAlign(ALIGN_CENTER);
    pavementBottom->setY(180);
	pavementBottom->addFrameFileFromData("/board/pavement_0_bottom.png");
	pavementBottom->show();
    pavementBottom->setGroup(this);
	
	trap = new Element();	
    trap->setAlign(ALIGN_CENTER);
	trap->addFrameFileFromData("/board/trap_0003.png");
    trap->setGroup(this);
			
	blackHole0 = new ElementIsometric();	
	blackHole0->setHeightElement(30);
	blackHole0->setAlign(ALIGN_CENTER);

	blackHole0->addFrameFileFromData("/editgame/blackhole_1.png");
	
	blackHole1 = new ElementIsometric();	
	blackHole1->setHeightElement(30);
	blackHole1->setAlign(ALIGN_CENTER);
	
	blackHole1->addFrameFileFromData("/editgame/blackhole_2.png");
	
	blackHole0->setGroup(this);
	blackHole1->setGroup(this);
	
	doorKeyBottom = new ElementIsometric();	
	doorKeyBottom->addFrameFileFromData("/objects/grate_0000.png");
	doorKeyBottom->setAlign(ALIGN_RIGHT);
	doorKeyBottom->setHeightElement(60);
	doorKeyBottom->setDisplacementX(8);
	doorKeyBottom->setGroup(this);
	
	doorKeyRight = new ElementIsometric();	
	doorKeyRight->setFlip(true);
	doorKeyRight->addFrameFileFromData("/objects/grate_0000.png");
	doorKeyRight->setHeightElement(60);
	doorKeyRight->setDisplacementX(-8);
	doorKeyRight->setGroup(this);
	
	key = new ElementIsometric();	
	key->setHeightElement(20);
	key->setAlign(ALIGN_CENTER);
	key->addFrameFileFromData("/objects/key.png");
	key->setGroup(this);
	
	tray = new ElementIsometric();	
	tray->setHeightElement(20);
	tray->setAlign(ALIGN_CENTER);
	
	tray->addFrameFileFromData("/objects/tray.png");
	
	tray->setGroup(this);
			
	scenary = new EditScenary();
	
	door = new EditDoor();
	door->setGroup(this);
	
	wallBottom = new ElementIsometric();
	wallBottom->addFrameFileFromData("/board/wall_0_h.png");
	wallBottom->setAlign(ALIGN_RIGHT);
	//wallTop->setVAlign(VALIGN_BOTTOM);
	wallBottom->setHeightElement(25);
	wallBottom->setDisplacementX(10.0);
	wallBottom->setGroup(this);
	
	wallRight = new ElementIsometric();
	wallRight->addFrameFileFromData("/board/wall_0_v.png");
	//wallLeft->setVAlign(VALIGN_CENTER);
	//wallLeft->setAlign(ALIGN_RIGHT);
	wallRight->setHeightElement(25);
	wallRight->setDisplacementX(-10.0);
	wallRight->setGroup(this);
		
	floorOn = new ElementIsometric();	
	floorOn->setHeightElement(0);
	floorOn->setForcePosition(0,0);
	floorOn->setAlign(ALIGN_CENTER);
	floorOn->addFrameFileFromData("/editgame/floor_on.png");
	floorOn->setGroup(this);
	
	nimuh = new ElementIsometric();	
	nimuh->setHeightElement(120);
	nimuh->setForcePosition(0,0);
	nimuh->setAlign(ALIGN_CENTER);
	nimuh->addFrameFileFromData("/nimuh/nimuh_0012.png");
	
	ghost = nimuh;
	
	enemy1 = new ElementIsometric();	
	enemy1->setHeightElement(110);
	enemy1->setForcePosition(0,0);
	enemy1->setAlign(ALIGN_CENTER);
	enemy1->addFrameFileFromData("/enemy1/enemy1_0012.png");
	
	enemy2 = new ElementIsometric();	
	enemy2->setHeightElement(100);
	enemy2->setForcePosition(0,0);
	enemy2->setAlign(ALIGN_CENTER);
	enemy2->addFrameFileFromData("/enemy2/enemy2_0012.png");
	
	enemy3 = new ElementIsometric();	
	enemy3->setHeightElement(110);
	enemy3->setForcePosition(0,0);
	enemy3->setAlign(ALIGN_CENTER);
	enemy3->addFrameFileFromData("/enemy3/enemy3_0004.png");

	Animation a;
	a.setName("stop_right");
	a.addFrame(0);
	nimuh->addAnimation(a);
	enemy1->addAnimation(a);
	enemy2->addAnimation(a);
	enemy3->addAnimation(a);
	
	nimuh->setGroup(this);
	enemy1->setGroup(this);
	enemy2->setGroup(this);
	enemy3->setGroup(this);

	
}

bool EditBoard::verifyPositions(BoardPosition p1, BoardPosition p2) {
     if ( (p1.x == p2.x) && (p1.y == p2.y) ) {
          return true;
     } else {
          return false;       
     }
}

int EditBoard::referencePositions(BoardPosition p1, BoardPosition p2) {
     if ( (p1.x-1 == p2.x) && (p1.y == p2.y) ) {
          return TILE_LEFT;
     } else if ( (p1.x+1 == p2.x) && (p1.y == p2.y) ) {
          return TILE_RIGHT;
     } else if ( (p1.x == p2.x) && (p1.y-1 == p2.y) ) {
          return TILE_UP;
     } else if ( (p1.x == p2.x) && (p1.y+1 == p2.y) ) {
          return TILE_DOWN;
     } else if ( (p1.x == p2.x) && (p1.y == p2.y) ) {
          return TILE_CENTER;
     } else {
          return TILE_OTHER;       
     }
}

void EditBoard::verifyClickOnBoard() { 
	insertObject(getPositionMouse());
	scenary->verifyClick ();
}

void EditBoard::verifyUnClickOnBoard() { 
	scenary->removeDnd();
}

void EditBoard::verifyMouseOnBoard() { 
	scenary->onOver();
	
	bool todoDefaultCursor = true;
	
	BoardPosition p = getPositionMouse();
	if (!p.out) { 
		string obj = sceneeditgame->bNimuh->getRadioButtonActive()->getParameter("object").c_str();
		
		if (obj=="doorkey") {
			if (hasKey) {

				if (verifyPositions(doorKeyRight->getPosition(), p)) {
					todoDefaultCursor = false;
					Cursor::GetInstance()->setCursor("rotate");
				}
				
			}
			
		}
		
	}
	
	if (todoDefaultCursor) Cursor::GetInstance()->setCursor("default");
}

void EditBoard::draw() {
	
	// scenary
	
	scenary->draw();
	
	pavementTop->draw();
	
    int x, y;

		
	for (y=0; y<rows; y++) {
		
        for (x=0; x<cols; x++) {
			int res = 0;
			if (y%2==0) {
				res = 0;
			} else {
				res = 1;
			}
			bool todoFloor = true;
			if (hasTrap) {
				if ( (posTrap.x == x) && (posTrap.y == y) ) {
					trap->setX(Plot::GetInstance()->getX(x, y));
					trap->setY(Plot::GetInstance()->getY(x, y)-2);
					trap->draw();
					todoFloor = false;
				}
			}
			if (todoFloor) {
				if (x%2==res) {
					floor0->setX(Plot::GetInstance()->getX(x, y));
					floor0->setY(Plot::GetInstance()->getY(x, y));
					floor0->draw();
				} else {
					floor1->setX(Plot::GetInstance()->getX(x, y));
					floor1->setY(Plot::GetInstance()->getY(x, y));
					floor1->draw();
				}
			}
        }
		
	}
	
	floorShadow->draw();
	
	// door
	if ( (door->getDoorPosition()==UP) || (door->getDoorPosition()==LEFT) ) {
		door->setAlpha(255);
		door->draw();	
	}
	
	
	// objects
	
	for (int s=0; s<=(rows-1)*2; s++) {
        for (int n=0; n<=s; n++) {
            x = n;
            y = s-n;
			
			if (!(SDL_GetMouseState(NULL, NULL)&SDL_BUTTON(1))) {
				// light
				BoardPosition bpmouse = getPositionMouse();
				if (!bpmouse.out) {
					if ( (bpmouse.x == x) && (bpmouse.y == y) ) {
						if ( (ghost!=NULL) && (ghost!=door) ) {
							ghost->setAlpha(100);
							BoardPosition aux = ghost->getPosition();
							aux.out = false;
							ghost->setForcePosition(bpmouse);
							ghost->draw();
							ghost->setForcePosition(aux);
							ghost->setAlpha(255);
						} else {
							floorOn->setForcePosition(bpmouse);
							floorOn->draw();
						}
					}
				}
			}
			
            if (positionIsOnBoard(getPositionFromXY(x,y))) {
				
                if (hasBlackHole0) {
                    if ( (blackHole0->getXBoard() == x) && (blackHole0->getYBoard() == y) ) {
            			blackHole0->draw();	
            		}
                }
                
                if (hasBlackHole1) {
            		if ( (blackHole1->getXBoard() == x) && (blackHole1->getYBoard() == y) ) {
            			blackHole1->draw();	
            		}
                }
                
        		if ( (nimuh->getXBoard() == x) && (nimuh->getYBoard() == y) ) {
					nimuh->setAlpha(255);
        			nimuh->draw();	
        		}
				if ( (enemy1->getXBoard() == x) && (enemy1->getYBoard() == y) && hasEnemy1 ) {
					enemy1->setAlpha(255);
        			enemy1->draw();	
        		}
				if ( (enemy2->getXBoard() == x) && (enemy2->getYBoard() == y) && hasEnemy2 ) {
        			enemy2->draw();	
        		}
				if ( (enemy3->getXBoard() == x) && (enemy3->getYBoard() == y) && hasEnemy3 ) {
        			enemy3->draw();	
        		}
        		
				if (hasKey) {
					if ( (key->getXBoard() == x) && (key->getYBoard() == y) ) {
						key->draw();
					}
                }
        		
				if (hasKey) {
					
                    if (directionKey == "right") {
						if ( (doorKeyRight->getXBoard() == x) && (doorKeyRight->getYBoard() == y) ) {
							doorKeyRight->draw();
						}
					} else {
						if ( (doorKeyBottom->getXBoard() == x) && (doorKeyBottom->getYBoard() == y) ) {
							doorKeyBottom->draw();
						}
					}
                }
				
				if (hasTray) {
					if ( (tray->getXBoard() == x) && (tray->getYBoard() == y) ) {
						tray->draw();
					}
                }
								
    			// right wall
    			if ( ( hasWallRight(x, y) ) && (x<getCols()) ) {
					BoardPosition bp;
					bp.x = x;
					bp.y = y;
					bp.out = !EditBoard::GetInstance()->positionIsOnBoard(bp);
    				wallRight->setForcePosition(bp);
					wallRight->setAlpha(255);
    				wallRight->draw();
    			}
				
    			// bottom wall
    			if ( ( hasWallBottom(x, y) ) && (y<getRows()) ) {
    				BoardPosition bp;
					bp.x = x;
					bp.y = y;
					bp.out = !EditBoard::GetInstance()->positionIsOnBoard(bp);
    				wallBottom->setForcePosition(bp);
					wallBottom->setAlpha(255);
    				wallBottom->draw();
    			}
				
            }
    		
        }    
    } // final objects
	
	
	pavementBottom->draw();
	
	// door
	if ( (door->getDoorPosition()==DOWN) || (door->getDoorPosition()==RIGHT) ) {
		door->setAlpha(255);
		door->draw();
	}


}

void EditBoard::insertObject(BoardPosition p) {
	if (!p.out) { 
		string obj = sceneeditgame->bNimuh->getRadioButtonActive()->getParameter("object").c_str();
		
		if (obj=="nimuh") {
		
			if (!verifyHasObject(obj, p)) nimuh->setForcePosition(p);
		}
		
		if (obj=="enemy1") {
			
			if (hasEnemy1) {
				if ( (enemy1->getXBoard() == p.x) && (enemy1->getYBoard() == p.y) ) {
					hasEnemy1 = false;
				}
			} else {
				hasEnemy1 = true;
			}
			
			if (!verifyHasObject(obj, p)) enemy1->setForcePosition(p);
		}
		
		if (obj=="enemy2") {
			if (hasEnemy2) {
				if ( (enemy2->getXBoard() == p.x) && (enemy2->getYBoard() == p.y) ) {
					hasEnemy2 = false;
				}
			} else {
				hasEnemy2 = true;
			}
			
			if (!verifyHasObject(obj, p)) enemy2->setForcePosition(p);
		}
		
		if (obj=="enemy3") {
			if (hasEnemy3) {
				if ( (enemy3->getXBoard() == p.x) && (enemy3->getYBoard() == p.y) ) {
					hasEnemy3 = false;
				}
			} else {
				hasEnemy3 = true;
			}
					
			if (!verifyHasObject(obj, p)) enemy3->setForcePosition(p);
		}
		
		if (obj=="wallbottom") {
			if (hasWallBottom(p.x, p.y))
				setWallBottom( p.x, p.y, false);
			else
				setWallBottom( p.x, p.y, true);
		}

		if (obj=="wallright") {
			if (hasWallRight(p.x, p.y))
				setWallRight( p.x, p.y, false);
			else 
				setWallRight( p.x, p.y, true);
		}
		
		if (obj=="door") {
			door->setForcePosition(p);
		}
		
		if (obj=="trap") {
			if (hasTrap) {
				if ( (posTrap.x == p.x) && (posTrap.y == p.y) ) {
					hasTrap = false;
				}
			} else {
				hasTrap = true;
			}
			
			posTrap = p;
		}
		
		if (obj=="tray") {
			if (hasTray) {
				if ( (tray->getXBoard() == p.x) && (tray->getYBoard() == p.y) ) {
					hasTray = false;
					sceneeditgame->handTray->setMovementNormalX(0, 500);
					sceneeditgame->btHandTray->setSensitive(false);
					infoTray.clear();
				}
			} else {
				hasTray = true;
				sceneeditgame->handTray->setMovementNormalX(165, 500);
				sceneeditgame->btHandTray->setSensitive(true);
				InfoTray it;
				it.title = "Titulo comida";
				it.text = "Coloca aqui el texto de la comida";
				infoTray.push_back(it);
			}
			
			if (!verifyHasObject(obj, p)) tray->setForcePosition(p);
		}
		
		if (obj=="blackhole1") {
			if (hasBlackHole0) {
				if ( (blackHole0->getXBoard() == p.x) && (blackHole0->getYBoard() == p.y) ) {
					hasBlackHole0 = false;
				}
			} else {
				hasBlackHole0 = true;
			}
			
			if (!verifyHasObject(obj, p)) blackHole0->setForcePosition(p);
		}
		
		if (obj=="blackhole2") {
			if (hasBlackHole1) {
				if ( (blackHole1->getXBoard() == p.x) && (blackHole1->getYBoard() == p.y) ) {
					hasBlackHole1 = false;
				}
			} else {
				hasBlackHole1 = true;
			}
			
			if (!verifyHasObject(obj, p)) blackHole1->setForcePosition(p);
		}
		
		if (obj=="key") {
			if (hasKey) {
				if ( (key->getXBoard() == p.x) && (key->getYBoard() == p.y) ) {
					hasKey = false;
				}
			} else {
				hasKey = true;
			}
			
			if (!verifyHasObject(obj, p)) key->setForcePosition(p);
		}
		
		if (obj=="doorkey") {
			if (hasKey) {
                if (directionKey=="right") {
                     if ( (doorKeyRight->getXBoard() == p.x) && (doorKeyRight->getYBoard() == p.y) ) {
                          directionKey = "bottom";
                          ghost = doorKeyBottom;
                     }
                } else {
                     if ( (doorKeyBottom->getXBoard() == p.x) && (doorKeyBottom->getYBoard() == p.y) ) {
                          directionKey = "right";
                          ghost = doorKeyRight;
                     }
                }
                doorKeyRight->setForcePosition(p);
                doorKeyBottom->setForcePosition(p);
			}
			
		}
		
	}
}

bool EditBoard::verifyHasObject(string obj, BoardPosition p) {
     
     if (obj != "nimuh") {
         if (verifyPositions(nimuh->getPosition(), p)) return true;
     }
     
     if (obj != "enemy1") {
         if (hasEnemy1 && verifyPositions(enemy1->getPosition(), p)) return true;
     }
     
     if (obj != "enemy2") {
         if (hasEnemy2 && verifyPositions(enemy2->getPosition(), p)) return true;
     }
     
     if (obj != "enemy3") {
         if (hasEnemy3 && verifyPositions(enemy3->getPosition(), p)) return true;
     }
     
     if (obj != "blackhole1") {
         if (hasBlackHole0 && verifyPositions(blackHole0->getPosition(), p)) return true;
     }
     
     if (obj != "blackhole2") {
         if (hasBlackHole1 && verifyPositions(blackHole1->getPosition(), p)) return true;
     }
     
     if (obj != "key") {
         if (hasKey && verifyPositions(key->getPosition(), p)) return true;
     }
	 
	 if (obj != "tray") {
         if (hasTray && verifyPositions(tray->getPosition(), p)) return true;
     }
          
     return false;
}

void EditBoard::changeGhost() {
	string obj = sceneeditgame->bNimuh->getRadioButtonActive()->getParameter("object").c_str();
	bool hasObject = false;
	if (obj=="nimuh") {
		ghost = nimuh;
		hasObject = true;
	}
	
	if (obj=="enemy1") {
		ghost = enemy1;
		hasObject = true;
	}
	
	if (obj=="enemy2") {
		ghost = enemy2;
		hasObject = true;
	}
	
	if (obj=="enemy3") {
		ghost = enemy3;
		hasObject = true;
	}
	
	if (obj=="wallbottom") {
		ghost = wallBottom;
		hasObject = true;
	}

	if (obj=="wallright") {
		ghost = wallRight;
		hasObject = true;
	}
	
	if (obj=="door") {
		ghost = door;
		hasObject = true;
	}
	
	if (obj=="blackhole1") {
		ghost = blackHole0;
		hasObject = true;
	}
	
	if (obj=="blackhole2") {
		ghost = blackHole1;
		hasObject = true;
	}
	
	if (obj=="key") {
		ghost = key;
		hasObject = true;
	}
	
	if (obj=="tray") {
		ghost = tray;
		hasObject = true;
	}
	
	if (obj=="doorkey") {
        if (directionKey == "right") {
           ghost = doorKeyRight;
	    } else {
           ghost = doorKeyBottom;
        }
		hasObject = true;
	}
	
	if (!hasObject) ghost = NULL;
}

void EditBoard::unLoad() {

	delete door;
	delete scenary;
	delete floor0;
	delete floor1;
	delete wallBottom;
	delete wallRight;
	delete nimuh;
	delete enemy1;
	delete enemy2;
	delete enemy3;

	delete blackHole0;
	delete blackHole1;
	delete doorKeyBottom;
	delete doorKeyRight;
	delete key;
	delete floorShadow;

	delete pavementTop;
	delete pavementBottom;

	delete floorOn;

}

/*****************************
**
** FUNCIONES PARA TRABAJAR
** CON ARCHIVO XML
**
******************************/


/*****************************
** FUNCIONES PARA CARGAR SCREEN
******************************/


typedef struct
{
	int x, y;
	bool bottom, right;
	string direction;
} DataEditScreenXML;


void initDataEditScreenXML(DataEditScreenXML *dataScreen) {
	dataScreen->x = 0;
	dataScreen->y = 0;
	dataScreen->bottom = false;
	dataScreen->right = false;
}

static void startEditScreenXML(void *userData, const char *el, const char **attr) {

	DataEditScreenXML* dataScreen = (DataEditScreenXML*)userData;
	int i;
	
	//printf("el: %s\n", el);

	if (strcmp(el, "multilanguage") == 0) {
		for (i = 0; attr[i]; i += 2) {
			if ( (strcmp(attr[i], "value") == 0) && (strcmp(attr[i+1], "true") == 0) ) {
				EditBoard::GetInstance()->multiLanguage = true;
			}
		}
	} else if (strcmp(el, "player") == 0) {
		for (i = 0; attr[i]; i += 2) {
			if (strcmp(attr[i], "x") == 0) {
				dataScreen->x = atoi(attr[i+1]);
			} else if (strcmp(attr[i], "y") == 0) {
				dataScreen->y = atoi(attr[i+1]);
			}
		}
	} else if (strcmp(el, "enemy1") == 0) {
		for (i = 0; attr[i]; i += 2) {
			if (strcmp(attr[i], "x") == 0) {
				dataScreen->x = atoi(attr[i+1]);
			} else if (strcmp(attr[i], "y") == 0) {
				dataScreen->y = atoi(attr[i+1]);
			}
		}
	} else if (strcmp(el, "enemy2") == 0) {
		for (i = 0; attr[i]; i += 2) {
			if (strcmp(attr[i], "x") == 0) {
				dataScreen->x = atoi(attr[i+1]);
			} else if (strcmp(attr[i], "y") == 0) {
				dataScreen->y = atoi(attr[i+1]);
			}
		}
	} else if (strcmp(el, "enemy3") == 0) {
		for (i = 0; attr[i]; i += 2) {
			if (strcmp(attr[i], "x") == 0) {
				dataScreen->x = atoi(attr[i+1]);
			} else if (strcmp(attr[i], "y") == 0) {
				dataScreen->y = atoi(attr[i+1]);
			}
		}
	} else if (strcmp(el, "exit") == 0) {
		for (i = 0; attr[i]; i += 2) {
			if (strcmp(attr[i], "x") == 0) {
				dataScreen->x = atoi(attr[i+1]);
			} else if (strcmp(attr[i], "y") == 0) {
				dataScreen->y = atoi(attr[i+1]);
			}
		}
	} else if (strcmp(el, "blackhole0") == 0) {
		for (i = 0; attr[i]; i += 2) {
			if (strcmp(attr[i], "x") == 0) {
				dataScreen->x = atoi(attr[i+1]);
			} else if (strcmp(attr[i], "y") == 0) {
				dataScreen->y = atoi(attr[i+1]);
			}
		}
	} else if (strcmp(el, "blackhole1") == 0) {
		for (i = 0; attr[i]; i += 2) {
			if (strcmp(attr[i], "x") == 0) {
				dataScreen->x = atoi(attr[i+1]);
			} else if (strcmp(attr[i], "y") == 0) {
				dataScreen->y = atoi(attr[i+1]);
			}
		}
	} else if (strcmp(el, "key") == 0) {
		for (i = 0; attr[i]; i += 2) {
			if (strcmp(attr[i], "x") == 0) {
				dataScreen->x = atoi(attr[i+1]);
			} else if (strcmp(attr[i], "y") == 0) {
				dataScreen->y = atoi(attr[i+1]);
			}
		}
	} else if (strcmp(el, "trap") == 0) {
		for (i = 0; attr[i]; i += 2) {
			if (strcmp(attr[i], "x") == 0) {
				dataScreen->x = atoi(attr[i+1]);
			} else if (strcmp(attr[i], "y") == 0) {
				dataScreen->y = atoi(attr[i+1]);
			}
		}
	} else if (strcmp(el, "tray") == 0) {
		for (i = 0; attr[i]; i += 2) {
			if (strcmp(attr[i], "x") == 0) {
				dataScreen->x = atoi(attr[i+1]);
			} else if (strcmp(attr[i], "y") == 0) {
				dataScreen->y = atoi(attr[i+1]);
			}
		}
	} else if (strcmp(el, "door-key") == 0) {
		for (i = 0; attr[i]; i += 2) {
			if (strcmp(attr[i], "x") == 0) {
				dataScreen->x = atoi(attr[i+1]);
			} else if (strcmp(attr[i], "y") == 0) {
				dataScreen->y = atoi(attr[i+1]);
			} else if (strcmp(attr[i], "direction") == 0) {
				dataScreen->direction = attr[i+1];
			}
		}
	} else if (strcmp(el, "town") == 0) {
		for (i = 0; attr[i]; i += 2) {
			if (strcmp(attr[i], "name") == 0) {
				EditBoard::GetInstance()->town.name = attr[i+1];
			} else if (strcmp(attr[i], "province") == 0) {
				EditBoard::GetInstance()->town.province = attr[i+1];
			} else if (strcmp(attr[i], "nickname") == 0) {
				EditBoard::GetInstance()->town.nickname = attr[i+1];
			}
		}
	} else if (strcmp(el, "info-tray") == 0) {
		InfoTray it;
		for (i = 0; attr[i]; i += 2) {
			if (strcmp(attr[i], "title") == 0) {
				it.title = attr[i+1];
			} else if (strcmp(attr[i], "text") == 0) {
				it.text = attr[i+1];
			} else if (strcmp(attr[i], "lang") == 0) {
				it.lang = attr[i+1];
			}
		}
		EditBoard::GetInstance()->infoTray.push_back(it);
	} else if (strcmp(el, "information") == 0) {
        InformationTown it;
		for (i = 0; attr[i]; i += 2) {
			if (strcmp(attr[i], "title") == 0) {
				it.title = attr[i+1];
			} else if (strcmp(attr[i], "text") == 0) {
				it.text = attr[i+1];
			} else if (strcmp(attr[i], "button") == 0) {
				it.button = attr[i+1];
			}
		}
		EditBoard::GetInstance()->getSceneEditGame()->addInfoTown(it);
	} else if (strcmp(el, "help") == 0) {
		for (i = 0; attr[i]; i += 2) {
			if (strcmp(attr[i], "name") == 0) {
				EditBoard::GetInstance()->helpName = attr[i+1];
			}
		}
	} else if (strcmp(el, "map") == 0) {
        EditBoard::GetInstance()->hasMap = true;
		for (i = 0; attr[i]; i += 2) {
			if (strcmp(attr[i], "file-fromdata") == 0) {
                EditBoard::GetInstance()->fileFromDataMap = attr[i+1];			
			}
			if (strcmp(attr[i], "file-fromlevel") == 0) {
                EditBoard::GetInstance()->fileFromLevelMap = attr[i+1];			
			}
		}
	} else if (strcmp(el, "texts-map") == 0) {
		EditMap em;
		for (i = 0; attr[i]; i += 2) {
			if (strcmp(attr[i], "title-1") == 0) {
				em.title1 = attr[i+1];
			} else if (strcmp(attr[i], "text-1") == 0) {
				em.text1 = attr[i+1];
			} else if (strcmp(attr[i], "title-2") == 0) {
				em.title2 = attr[i+1];
			} else if (strcmp(attr[i], "text-2") == 0) {
				em.text2 = attr[i+1];
			} else if (strcmp(attr[i], "lang") == 0) {
				em.lang = attr[i+1];
			} else if (strcmp(attr[i], "distance-second-text") == 0) {
				em.distanceSecondText = attr[i+1];
			}		
		}
		EditBoard::GetInstance()->map.push_back(em);
	} else if (strcmp(el, "music") == 0) {
		for (i = 0; attr[i]; i += 2) {
			if (strcmp(attr[i], "type") == 0) {
				int music = atoi(attr[i+1]);
				EditBoard::GetInstance()->setTypeMusic(music);
				switch (music) {
					case 0:
						EditBoard::GetInstance()->getSceneEditGame()->radMusic0->setActive(true);
					break;
					case 1:
						EditBoard::GetInstance()->getSceneEditGame()->radMusic1->setActive(true);
					break;
					case 2:
						EditBoard::GetInstance()->getSceneEditGame()->radMusic2->setActive(true);
					break;
					case 3:
						EditBoard::GetInstance()->getSceneEditGame()->radMusic3->setActive(true);
					break;
				}
			}
		}
	} else if (strcmp(el, "board") == 0) {
		bool tb = false;
		for (i = 0; attr[i]; i += 2) {
			if ( (strcmp(attr[i], "type") == 0) && (strcmp(attr[i+1], "6x6") == 0) ) {
				EditBoard::GetInstance()->setTypeSize(BOARD_6X6);
				tb = true;
			}
			if ( (strcmp(attr[i], "type") == 0) && (strcmp(attr[i+1], "7x7") == 0) ) {
				EditBoard::GetInstance()->setTypeSize(BOARD_7X7);
				tb = true;
			}
			if ( (strcmp(attr[i], "type") == 0) && (strcmp(attr[i+1], "8x8") == 0) ) {
				EditBoard::GetInstance()->setTypeSize(BOARD_8X8);
				tb = true;
			}
			if ( (strcmp(attr[i], "type") == 0) && (strcmp(attr[i+1], "9x9") == 0) ) {
				EditBoard::GetInstance()->setTypeSize(BOARD_9X9);
				tb = true;
			}
			if ( (strcmp(attr[i], "type") == 0) && (strcmp(attr[i+1], "10x10") == 0) ) {
				EditBoard::GetInstance()->setTypeSize(BOARD_10X10);
				tb = true;
			}
			if (strcmp(attr[i], "floor") == 0) {
				EditBoard::GetInstance()->setTypeFloor(atoi(attr[i+1]));
				EditBoard::GetInstance()->getSceneEditGame()->typeFloor->setFrame(atoi(attr[i+1]));
			}
			if (strcmp(attr[i], "wall") == 0) {
				EditBoard::GetInstance()->setTypeWall(atoi(attr[i+1]));
				EditBoard::GetInstance()->getSceneEditGame()->typeWall->setFrame(atoi(attr[i+1]));
			}
			if (strcmp(attr[i], "pavement") == 0) {
				EditBoard::GetInstance()->setTypePavement(atoi(attr[i+1]));
				EditBoard::GetInstance()->getSceneEditGame()->typePavement->setFrame(atoi(attr[i+1]));
			}
		}
		if (!tb) EditBoard::GetInstance()->setTypeSize(BOARD_6X6);
		EditBoard::GetInstance()->getSceneEditGame()->typeBoard->setFrame(EditBoard::GetInstance()->getTypeSize());
	} else if (strcmp(el, "wall") == 0) {
		for (i = 0; attr[i]; i += 2) {
			if (strcmp(attr[i], "x") == 0) {
				dataScreen->x = atoi(attr[i+1]);
			} else if (strcmp(attr[i], "y") == 0) {
				dataScreen->y = atoi(attr[i+1]);
			} else if (strcmp(attr[i], "right") == 0) {
				if (strcmp(attr[i+1], "true")==0) {
					dataScreen->right = true;
			  	}
			} else if (strcmp(attr[i], "bottom") == 0) {
				if (strcmp(attr[i+1], "true")==0) {
					dataScreen->bottom = true;
			  	}
			}
		}
	} else if (strcmp(el, "scenary") == 0) {
		int r = 255, g = 255, b = 255, ntiles = 0, ttiled = 0, tterrain = 0, twallscenary = 0;
		for (i = 0; attr[i]; i += 2) {
			if (strcmp(attr[i], "type") == 0) {
				if (strcmp(attr[i+1], "opened") == 0) {
					EditBoard::GetInstance()->getScenary()->setType(SCENARY_OPENED);
				} else {
					EditBoard::GetInstance()->getScenary()->setType(SCENARY_CLOSED);
				}
			}
			if (strcmp(attr[i], "red") == 0) {
				r = atoi(attr[i+1]);
			}
			if (strcmp(attr[i], "green") == 0) {
				g = atoi(attr[i+1]);
			}
			if (strcmp(attr[i], "blue") == 0) {
				b = atoi(attr[i+1]);
			}
			if (strcmp(attr[i], "ntiles") == 0) {
				ntiles = atoi(attr[i+1]);
			}
			if (strcmp(attr[i], "type-tiled") == 0) {
				ttiled = atoi(attr[i+1]);
			}
			if (strcmp(attr[i], "type-terrain") == 0) {
				tterrain = atoi(attr[i+1]);
			}
			if (strcmp(attr[i], "type-wall") == 0) {
				twallscenary = atoi(attr[i+1]);
			}
		}
		if (EditBoard::GetInstance()->getScenary()->getType() == SCENARY_CLOSED) {
			EditBoard::GetInstance()->getScenary()->setColorInWalls(r, g, b);
			EditBoard::GetInstance()->getSceneEditGame()->colorWall->setFrame( EditBoard::GetInstance()->getSceneEditGame()->vcolorsWall->getIndexColor(r, g, b) );
			EditBoard::GetInstance()->getScenary()->setNVerticalTiles(ntiles);
			EditBoard::GetInstance()->getSceneEditGame()->nTilesClosed->setFrame(ntiles);
			EditBoard::GetInstance()->getScenary()->setTypeTiled(ttiled);
			EditBoard::GetInstance()->getSceneEditGame()->typeTiled->setFrame(ttiled);
			EditBoard::GetInstance()->getScenary()->setTypeWall(twallscenary);
			EditBoard::GetInstance()->getSceneEditGame()->typeWallScenary->setFrame(twallscenary);
		} else {
			EditBoard::GetInstance()->getScenary()->setNVerticalTiles(ntiles);
			EditBoard::GetInstance()->getSceneEditGame()->nTilesClosed->setFrame(ntiles);
			EditBoard::GetInstance()->getScenary()->setTypeTiled(ttiled);
			EditBoard::GetInstance()->getSceneEditGame()->typeTiled->setFrame(ttiled);
			EditBoard::GetInstance()->getScenary()->setTypeTerrain(tterrain);
			EditBoard::GetInstance()->getSceneEditGame()->typeTerrain->setFrame(tterrain);
        }
	} else if (strcmp(el, "object") == 0) {
		char name[32];
		int x = 30;
		int y = 0;
		int type = TYPEOBJECT_3D;
		float scale = 1.0;
		bool flip = false;
		bool lock = false;
		int origen = ORIGENOBJECT_GAME;
		string text = "";
		string font = "";
		int r = 255, g = 255, b = 255;
		int align = ALIGN_CENTER;
		
		for (i = 0; attr[i]; i += 2) {
			if (strcmp(attr[i], "name") == 0) {
				strcpy(name, attr[i+1]);
			}
			if (strcmp(attr[i], "x") == 0) {
				x = atoi(attr[i+1]);
			}
			if (strcmp(attr[i], "y") == 0) {
				y = atoi(attr[i+1]);
			}
			if (strcmp(attr[i], "scale") == 0) {
				scale = atof(attr[i+1]);
			}
			if ( (strcmp(attr[i], "flip") == 0) && (strcmp(attr[i+1], "true") == 0) ) {
				flip = true;
			}
			if ( (strcmp(attr[i], "lock") == 0) && (strcmp(attr[i+1], "true") == 0) ) {
				lock = true;
			}
			if ( (strcmp(attr[i], "origen") == 0) && (strcmp(attr[i+1], "personal") == 0) ) {
				origen = ORIGENOBJECT_PERSONAL;
			}
			if (strcmp(attr[i], "text") == 0) {
				text = attr[i+1];
			}
			if (strcmp(attr[i], "font") == 0) {
				font = attr[i+1];
			}
			if (strcmp(attr[i], "align") == 0) {
				align = atoi(attr[i+1]);
			}
			if (strcmp(attr[i], "r") == 0) {
				r = atoi(attr[i+1]);
			}
			if (strcmp(attr[i], "g") == 0) {
				g = atoi(attr[i+1]);
			}
			if (strcmp(attr[i], "b") == 0) {
				b = atoi(attr[i+1]);
			}
			if (strcmp(attr[i], "type") == 0) {
				if (strcmp(attr[i+1], "2d") == 0) {
					type = TYPEOBJECT_2D;
				} else if (strcmp(attr[i+1], "3d") == 0) {
					type = TYPEOBJECT_3D;
				} else if (strcmp(attr[i+1], "text") == 0) {
					type = TYPEOBJECT_TEXT;
				}
			}
		}
		if (type == TYPEOBJECT_TEXT) {
			Color c;
			c.r = r;
			c.g = g;
			c.b = b;
			EditBoard::GetInstance()->getScenary()->addTextObject(text, font, align, c, x, y, scale, flip, lock);
		} else {
			EditBoard::GetInstance()->getScenary()->addObject(type, origen, name, x, y, scale, flip, lock);
		}
	}

}

static void endEditScreenXML(void *userData, const char *el)
{
	DataEditScreenXML* dataScreen = (DataEditScreenXML*)userData;

	if (strcmp(el, "player") == 0) {
		EditBoard::GetInstance()->setPositionPlayer(dataScreen->x, dataScreen->y);
		initDataEditScreenXML(dataScreen);
	} else if (strcmp(el, "enemy1") == 0) {
		EditBoard::GetInstance()->setPositionEnemy1(dataScreen->x, dataScreen->y);
		initDataEditScreenXML(dataScreen);
	} else if (strcmp(el, "enemy2") == 0) {
		EditBoard::GetInstance()->setPositionEnemy2(dataScreen->x, dataScreen->y);
		initDataEditScreenXML(dataScreen);
	} else if (strcmp(el, "enemy3") == 0) {
		EditBoard::GetInstance()->setPositionEnemy3(dataScreen->x, dataScreen->y);
		initDataEditScreenXML(dataScreen);
	} else if (strcmp(el, "exit") == 0) {
		EditBoard::GetInstance()->setPositionExit(dataScreen->x, dataScreen->y);
		initDataEditScreenXML(dataScreen);
	} else if (strcmp(el, "blackhole0") == 0) {
		EditBoard::GetInstance()->setBlackHole0(dataScreen->x, dataScreen->y);
		initDataEditScreenXML(dataScreen);
	} else if (strcmp(el, "blackhole1") == 0) {
		EditBoard::GetInstance()->setBlackHole1(dataScreen->x, dataScreen->y);
		initDataEditScreenXML(dataScreen);
	} else if (strcmp(el, "key") == 0) {
		EditBoard::GetInstance()->setKey(dataScreen->x, dataScreen->y);
		initDataEditScreenXML(dataScreen);
	} else if (strcmp(el, "trap") == 0) {
		EditBoard::GetInstance()->setPositionTrap(dataScreen->x, dataScreen->y);
		initDataEditScreenXML(dataScreen);
	} else if (strcmp(el, "tray") == 0) {
		EditBoard::GetInstance()->setPositionTray(dataScreen->x, dataScreen->y);
		initDataEditScreenXML(dataScreen);
	} else if (strcmp(el, "door-key") == 0) {
		EditBoard::GetInstance()->setDoorKey(dataScreen->x, dataScreen->y, dataScreen->direction);
		initDataEditScreenXML(dataScreen);
	} else if (strcmp(el, "wall") == 0) {
		if (dataScreen->bottom) {
			EditBoard::GetInstance()->setWallBottom( dataScreen->x, dataScreen->y, true);
		}
		if (dataScreen->right) {
			EditBoard::GetInstance()->setWallRight( dataScreen->x, dataScreen->y, true);
		}
		initDataEditScreenXML(dataScreen);
	}


}

void parseEditScreenXML(char fileXML[128]) {
	char buffer[8192];
	int done;
	
	DataEditScreenXML dataScreen;
	initDataEditScreenXML(&dataScreen);
	
	XML_Parser p = XML_ParserCreate(NULL);
	if (! p) {
		printf("Podra no tener suficiente memoria para el parser\n");
	}

	XML_SetUserData(p, &dataScreen);	
	XML_SetElementHandler(p, startEditScreenXML, endEditScreenXML);

  	FILE *file = fopen(fileXML, "r");
	if(!file)
		printf("Error abriendo archivo XML\n");
	
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
