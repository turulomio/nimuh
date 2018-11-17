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
 
#include "class_game.h"

/*****************************
**
** CLASE BoardInfo
**
******************************/	

BoardInfo* BoardInfo::instance = NULL;

BoardInfo::BoardInfo(string file) : Hash (file, false) {
}

BoardInfo* BoardInfo::GetInstance () {
	if ( instance == NULL ) {
		instance = new BoardInfo("/board/boardinfo.xml");
	}
	return instance;	
}

/*****************************
**
** CLASE TypeObjectScenary
**
******************************/

void TypeObjectsScenary_parseXML(char fileXML[128]);

TypeObjectsScenary* TypeObjectsScenary::instance = NULL;

TypeObjectsScenary::TypeObjectsScenary() {
	cursor = 0;
}

TypeObjectsScenary* TypeObjectsScenary::GetInstance () {
	if ( instance == NULL ) {
		instance = new TypeObjectsScenary();
	}
	return instance;	
}

TypeObjectScenary* TypeObjectsScenary::getObject(string name) {
	for (int i=0; i<(int)objects.size(); i++) {
		if (objects[i].name == name) return &objects[i];
	}
	return NULL;
}

void TypeObjectsScenary::load() {
	clear();
	char tmp[128];
	sprintf(tmp, "%s/scenary/objects.xml", DATA_DIR);
	TypeObjectsScenary_parseXML(tmp);
}

static void TypeObjectsScenary_start(void *userData, const char *el, const char **attr) {
	int i;
	if (strcmp(el, "object") == 0) {
		TypeObjectScenary obj;
		obj.minScale = 0.3;
		obj.maxScale = 1.2;
		for (i = 0; attr[i]; i += 2) {
			if (strcmp(attr[i], "name") == 0) {
				obj.name = attr[i+1];
			}
			if (strcmp(attr[i], "file") == 0) {
				obj.file = attr[i+1];
			}
			if (strcmp(attr[i], "min-scale") == 0) {
				obj.minScale = atof(attr[i+1]);
			}
			if (strcmp(attr[i], "max-scale") == 0) {
				obj.maxScale = atof(attr[i+1]);
			}
			if (strcmp(attr[i], "type") == 0) {
				if (strcmp(attr[i+1], "opened") == 0) {
					obj.type = SCENARY_OPENED;
				} else {
					obj.type = SCENARY_CLOSED;
				}
			}
			if (strcmp(attr[i], "category") == 0) {
				obj.category = attr[i+1];
			}
		}
		TypeObjectsScenary::GetInstance()->addObject(obj);
	}
}

static void TypeObjectsScenary_end(void *userData, const char *el)
{

}

void TypeObjectsScenary_parseXML(char fileXML[128]) {
	char buffer[8192];
	int done;
	
	XML_Parser p = XML_ParserCreate("ISO-8859-1");
	if (! p) {
		printf("It could not have sufficient memory parser\n");
	}
	string data = "";
	XML_SetUserData(p, &data);	
	XML_SetElementHandler(p, TypeObjectsScenary_start, TypeObjectsScenary_end);

	FILE *file = fopen(fileXML, "r");
	if(!file)
		printf("Error opening file XML\n");
	
	do
	{
		size_t len = fread(buffer, 1, sizeof(buffer), file);
		done = len < sizeof(buffer);
		if(!XML_Parse(p, buffer, len, done)){
			printf("Error making the parse\n");
		}
			//parse_error(&data, XML_ErrorString(XML_GetErrorCode(data.parser)));
	}
	while(!done);
	fclose(file);
}

/*****************************
**
** CLASE BoardScale
**
******************************/

BoardScale* BoardScale::instance = NULL;

BoardScale::BoardScale() {
    w_tile = W_TILE;
    h_tile = H_TILE;
    scale = 1.0f;
}

BoardScale* BoardScale::GetInstance () {
	if ( instance == NULL ) {
		instance = new BoardScale();
	}
	return instance;	
}

void BoardScale::setScale (float s) {
    w_tile = (int)W_TILE*s;
    h_tile = (int)H_TILE*s;
    scale = s;
}

/*****************************
**
** CLASE MouseMap
**
******************************/

MouseMapTile* MouseMapTile::instance = NULL;

MouseMapTile::MouseMapTile() {
	//createMap ();
}

MouseMapTile* MouseMapTile::GetInstance () {
	if ( instance == NULL ) {
		instance = new MouseMapTile();
	}
	return instance;	
}

void MouseMapTile::createMap () {
	int x, y;
	int rest=0; 
	map.clear();
	
	int w = BoardScale::GetInstance()->getWTile();
	int h = BoardScale::GetInstance()->getHTile();
	
	int chain = (w/2)/(h/2);
	int aux=0;
	
	for (y=0; y<h; y++) {
		// no se pq pero tengo que multiplicar cuando es 6x6
		if (y<(h/2)) {
			if (w==W_TILE) rest += chain*2;
			else rest += chain;
		} else {
			if (w==W_TILE) rest -= chain*2;
			else rest -= chain;
		}

		for (x=0; x<w; x++) {	
			if ( (x<(w/2)) && (y<(h/2)) ) { // 1
				if (x < (w/2)-rest) {
					aux = 1;
				} else {
					aux = 0;
				}
			}
			if ( (x>=(w/2)) && (y<(h/2)) ) { // 2
				if (x > (w/2)+rest) {
					aux = 2;
				} else {
					aux = 0;
				}
			}
			if ( (x<(w/2)) && (y>=(h/2)) ) { // 3
				if (x < (w/2)-rest) {
					aux = 3;
				} else {
					aux = 0;
				}
			}
			if ( (x>=(w/2)) && (y>=(h/2)) ) { // 4
				if (x > (w/2)+rest) {
					aux = 4;
				} else {
					aux = 0;
				}
			}
			map.push_back(aux);
		}
	}

}

int MouseMapTile::getPosMouse (int x, int y) {
	int w = BoardScale::GetInstance()->getWTile();
	int h = BoardScale::GetInstance()->getHTile();
    if ( ( (y*w)+x>=0 ) && ( (y*h)+x<map.size() ) ) { 
         return map[(y*w)+x]; 
    } else {
           return 0; 
    }
}

/*****************************
**
** CLASE Plot
**
******************************/

Plot* Plot::instance = NULL;

Plot::Plot() {
}

Plot* Plot::GetInstance () {
	if ( instance == NULL ) {
		instance = new Plot();
	}
	return instance;	
}

/*****************************
**
** CLASE ObjectScenary
**
******************************/
	

ObjectScenary::ObjectScenary() : ElementDnD () {
	showIcons = false;
	lock = false;
	flipObject = false;
	typeScenary = SCENARY_CLOSED;
	origen = ORIGENOBJECT_GAME;
	typeObject = TYPEOBJECT_3D;
	
	fontText = "";
	text = "-";
	alignText = ALIGN_LEFT;
	colorText.r = 255;
	colorText.g = 255;
	colorText.b = 255;
	
	minScale = 0.3;
    maxScale = 1.2;
		
	iconZoomin = new Button();	
	iconZoomin->setScales(1.0, 1.1);
	iconZoomin->setVAlign(VALIGN_BOTTOM);
	iconZoomin->setX(0);
	iconZoomin->setY(0);
	
	iconZoomin->imageOut(WorkingSurfaces::GetInstance()->surfaceFromImage((string)DATA_DIR + "/editgame/ico_zoomin.png"));
	iconZoomin->setAnimation("out");
	
	iconZoomout = new Button();	
	iconZoomout->setScales(1.0, 1.1);
	iconZoomout->setVAlign(VALIGN_BOTTOM);
	iconZoomout->setX(0);
	iconZoomout->setY(0);
	
	iconZoomout->imageOut(WorkingSurfaces::GetInstance()->surfaceFromImage((string)DATA_DIR + "/editgame/ico_zoomout.png"));
	iconZoomout->setAnimation("out");
	
	iconDuplicate = new Button();	
	iconDuplicate->setScales(1.0, 1.1);
	iconDuplicate->setVAlign(VALIGN_BOTTOM);
	iconDuplicate->setX(0);
	iconDuplicate->setY(0);
	
	iconDuplicate->imageOut(WorkingSurfaces::GetInstance()->surfaceFromImage((string)DATA_DIR + "/editgame/ico_duplicate.png"));
	iconDuplicate->setAnimation("out");
	
	iconDelete = new Button();	
	iconDelete->setScales(1.0, 1.1);
	iconDelete->setVAlign(VALIGN_BOTTOM);
	iconDelete->setX(0);
	iconDelete->setY(0);
	
	iconDelete->imageOut(WorkingSurfaces::GetInstance()->surfaceFromImage((string)DATA_DIR + "/editgame/ico_delete.png"));
	iconDelete->setAnimation("out");
	
	iconLock = new Button();	
	iconLock->setScales(1.0, 1.1);
	iconLock->setVAlign(VALIGN_BOTTOM);
	iconLock->setX(0);
	iconLock->setY(0);
	
	iconLock->imageOut(WorkingSurfaces::GetInstance()->surfaceFromImage((string)DATA_DIR + "/editgame/ico_unlock.png"));
	iconLock->setAnimation("out");
	
	iconFlip = new Button();	
	iconFlip->setScales(1.0, 1.1);
	iconFlip->setVAlign(VALIGN_BOTTOM);
	iconFlip->setX(0);
	iconFlip->setY(0);
	
	iconFlip->imageOut(WorkingSurfaces::GetInstance()->surfaceFromImage((string)DATA_DIR + "/editgame/ico_flip.png"));
	iconFlip->setAnimation("out");
	
	iconOrderBottom = new Button();	
	iconOrderBottom->setScales(1.0, 1.1);
	iconOrderBottom->setVAlign(VALIGN_BOTTOM);
	iconOrderBottom->setX(0);
	iconOrderBottom->setY(0);
	
	iconOrderBottom->imageOut(WorkingSurfaces::GetInstance()->surfaceFromImage((string)DATA_DIR + "/editgame/ico_orderbottom.png"));
	iconOrderBottom->setAnimation("out");
	
	iconOrderTop = new Button();	
	iconOrderTop->setScales(1.0, 1.1);
	iconOrderTop->setVAlign(VALIGN_BOTTOM);
	iconOrderTop->setX(0);
	iconOrderTop->setY(0);
	
	iconOrderTop->imageOut(WorkingSurfaces::GetInstance()->surfaceFromImage((string)DATA_DIR + "/editgame/ico_ordertop.png"));
	iconOrderTop->setAnimation("out");


}

ObjectScenary::~ObjectScenary () {
	parameters.clear();
	
	delete iconZoomin;
	delete iconZoomout;
	delete iconDuplicate;
	delete iconDelete;
	delete iconOrderTop;
	delete iconOrderBottom;
	delete iconFlip;
	delete iconLock;
}

void ObjectScenary::setFlip (bool f) {
	flipObject = f;
	if (typeObject == TYPEOBJECT_3D) {
		flip = f;
	} else {
		float d = (tan(25.5*3.14159265/180)*getWidthOriginal())/2;
		if (f) {
			setPerspective(0, d, 0, -d, 0, d, 0, -d);
		} else {
			setPerspective(0, -d, 0, d, 0, -d, 0, d);
		}
	}
}

void ObjectScenary::swapLock () {
     if (!lock) {
         lock = true;
         setToDoDnd (false);
         iconZoomin->setSensitive(false);
         iconZoomout->setSensitive(false);
         iconDuplicate->setSensitive(false);
         iconDelete->setSensitive(false);
         iconOrderTop->setSensitive(false);
         iconOrderBottom->setSensitive(false);
         iconFlip->setSensitive(false);
		 
         iconZoomin->setRGB(100, 100, 100);
         iconZoomout->setRGB(100, 100, 100);
         iconDuplicate->setRGB(100, 100, 100);
         iconDelete->setRGB(100, 100, 100);
         iconOrderTop->setRGB(100, 100, 100);
         iconOrderBottom->setRGB(100, 100, 100);
         iconFlip->setRGB(100, 100, 100);
		 
	     iconLock->changeFrameSurface(0, WorkingSurfaces::GetInstance()->surfaceFromImage((string)DATA_DIR + "/editgame/ico_lock.png"));
     } else {
         lock = false;
         setToDoDnd (true); 
         iconZoomin->setSensitive(true);
         iconZoomout->setSensitive(true);
         iconDuplicate->setSensitive(true);
         iconDelete->setSensitive(true);
         iconOrderTop->setSensitive(true);
         iconOrderBottom->setSensitive(true);
         iconFlip->setSensitive(true);
		 
         iconZoomin->setRGB(255, 255, 255);
         iconZoomout->setRGB(255, 255, 255);
         iconDuplicate->setRGB(255, 255, 255);
         iconDelete->setRGB(255, 255, 255);
         iconOrderTop->setRGB(255, 255, 255);
         iconOrderBottom->setRGB(255, 255, 255);
         iconFlip->setRGB(255, 255, 255);
		 
         iconLock->changeFrameSurface(0, WorkingSurfaces::GetInstance()->surfaceFromImage((string)DATA_DIR + "/editgame/ico_unlock.png"));
     }
} 

void ObjectScenary::setX (float x) { 
	oldX = posX; 
	posX = x; 
    if (getBounds().x1>0) {
    	iconZoomin->setX(getBounds().x1);
    	iconZoomout->setX(getBounds().x1+20);
    	iconLock->setX(getBounds().x1+40);
    	iconDelete->setX(getBounds().x1+60);
    	
    	iconOrderTop->setX(getBounds().x1);
    	iconOrderBottom->setX(getBounds().x1+20);
    	iconDuplicate->setX(getBounds().x1+40);
    	iconFlip->setX(getBounds().x1+60);
    } else {
    	iconZoomin->setX(0);
    	iconZoomout->setX(20);
    	iconLock->setX(40);
    	iconDelete->setX(60);
    	
    	iconOrderTop->setX(0);
    	iconOrderBottom->setX(20);
    	iconDuplicate->setX(40);
    	iconFlip->setX(60);
    }
}
	
void ObjectScenary::setY (float y) { 
	oldY = posY; 
	posY = y; 
    if (getBounds().y1>36) {
    	iconZoomin->setY(getBounds().y1-20);
    	iconZoomout->setY(getBounds().y1-20);
    	iconLock->setY(getBounds().y1-20);
    	iconDelete->setY(getBounds().y1-20);
    	
    	iconOrderTop->setY(getBounds().y1);
    	iconOrderBottom->setY(getBounds().y1);
    	iconDuplicate->setY(getBounds().y1);
    	iconFlip->setY(getBounds().y1);
    } else {
    	iconZoomin->setY(16);
    	iconZoomout->setY(16);
    	iconLock->setY(16);
    	iconDelete->setY(16);
    	
    	iconOrderTop->setY(36);
    	iconOrderBottom->setY(36);
    	iconDuplicate->setY(36);
    	iconFlip->setY(36);
    }
}

void ObjectScenary::addX (float x) { 
     setX(getXWithoutDisplacementByGroups()+x);
}

void ObjectScenary::addY (float y) { 
    setY(getY()+y);
}

void ObjectScenary::setGroup(Group *g) { 
	group = g; 
}

void ObjectScenary::onOver()
{
	if (showIcons) {
		iconZoomin->onOver();
		iconZoomout->onOver();
		iconDuplicate->onOver();
		iconDelete->onOver();
    	iconOrderTop->onOver();
    	iconOrderBottom->onOver();
    	if (typeScenary==SCENARY_OPENED) iconFlip->onOver();
    	iconLock->onOver();
	}
	if (isOnMouseOver() && !isRollOver) {
		isRollOver = true;
	}
	if (!isOnMouseOver() && isRollOver) {
		isRollOver = false;
		if (getTypeObject()==TYPEOBJECT_TEXT) {
			setRGB(getColorText().r, getColorText().g, getColorText().b);
		} else {
			setRGB(255, 255, 255);
		}
	}
	if (toDoDnd && isDnd) {	
		int cMouseX, cMouseY;
		SDL_GetMouseState(&cMouseX, &cMouseY);
		cMouseX -= (int)getDisplacementInXByGroups();
		cMouseY -= (int)getDisplacementInYByGroups();
		addX(cMouseX - mouseX);
		addY(cMouseY - mouseY);
		mouseX = cMouseX;
		mouseY = cMouseY;
		if (typeScenary==SCENARY_CLOSED) {
    		if ( (getX()<getDisplacementInXByGroups()) && (!getFlip()) ) {
    			setFlip(true);
    			setAlign(ALIGN_RIGHT);
    			iconZoomin->addX(-getWidth());
    			iconZoomout->addX(-getWidth());
    			iconDuplicate->addX(-getWidth());
    			iconDelete->addX(-getWidth());
    			iconOrderTop->addX(-getWidth());
    			iconOrderBottom->addX(-getWidth());
    			iconFlip->addX(-getWidth());
    			iconLock->addX(-getWidth());
    		}
    		if ( (getX()>=getDisplacementInXByGroups()) && (getFlip()) ) {
    			setFlip(false);
    			setAlign(ALIGN_LEFT);
    			iconZoomin->addX(getWidth());
    			iconZoomout->addX(getWidth());
    			iconDuplicate->addX(getWidth());
    			iconDelete->addX(getWidth());
    			iconOrderTop->addX(getWidth());
    			iconOrderBottom->addX(getWidth());
    			iconFlip->addX(getWidth());
    			iconLock->addX(getWidth());
    		}
        }
	}
	
}

void ObjectScenary::draw () {
	move();
	transforms();
	paintSprite();
}

void ObjectScenary::drawIcons () {
	if (showIcons) {
		iconZoomin->draw();
		iconZoomout->draw();
		iconDuplicate->draw();
		iconDelete->draw();
		iconOrderTop->draw();
		iconOrderBottom->draw();
		if (typeScenary==SCENARY_OPENED) iconFlip->draw();
		iconLock->draw();
	}
}

void ObjectScenary::unLoad() {
	int i;
	for (i=0; i<(int)sprite.size(); i++)
		delete sprite[i];
	sprite.clear();	
	parameters.clear();
	
	delete iconZoomin;
	delete iconZoomout;
	delete iconDuplicate;
	delete iconDelete;
	delete iconOrderTop;
	delete iconOrderBottom;
	delete iconFlip;
	delete iconLock;
}

/*****************************
**
** CLASE Scenary
**
******************************/
	

Scenary::Scenary() : Group () {
	posX = World::width/2;
	posY = 0;
	
	separatedTilesClosed = 25.0;
	
    colorRWallClosed = 255;
    colorGWallClosed = 255;
    colorBWallClosed = 255;
	
	editable = false;
	showGuides = false;
	type = SCENARY_CLOSED;
	c_typeTiledBottom = 0;
	nVerticalTiles = 4;
	
	shadowWall = new Element();
	shadowWall->addFrameFileFromData("/scenary/wall_shadow.png");
	shadowWall->setAlign(ALIGN_CENTER);
	addElement(shadowWall);
	
	wallRight = new Element();
	wallRight->addFrameFileFromData("/scenary/wallscenary0.png");
	wallRight->setAlign(ALIGN_LEFT);
	addElement(wallRight);	
	
	wallLeft = new Element();
	wallLeft->addFrameFileFromData("/scenary/wallscenary0.png");
	wallLeft->setFlip(true);
	wallLeft->setAlign(ALIGN_RIGHT);
	addElement(wallLeft);	
	
	guideRight = new Element();
	guideRight->addFrameFileFromData("/scenary/guide_closed.png");
	guideRight->addFrameFileFromData("/scenary/guide_opened.png");
	guideRight->setAlign(ALIGN_LEFT);
	addElement(guideRight);
	
	guideLeft = new Element();
	guideLeft->addFrameFileFromData("/scenary/guide_closed.png");
	guideLeft->addFrameFileFromData("/scenary/guide_opened.png");
	guideLeft->setFlip(true);
	guideLeft->setAlign(ALIGN_RIGHT);
	addElement(guideLeft);	
	
	tileRight = new Element();
	tileRight->addFrameFileFromData("/scenary/tile_0_down.png");
	tileRight->setVAlign(VALIGN_BOTTOM);
	tileRight->setGroup(Board::GetInstance());	
	
	tileRightUp = new Element();
	tileRightUp->addFrameFileFromData("/scenary/tile_0_up.png");
	tileRightUp->setVAlign(VALIGN_BOTTOM);
	tileRightUp->setGroup(Board::GetInstance());	
	
	tileLeft = new Element();
	tileLeft->addFrameFileFromData("/scenary/tile_0_down.png");
	tileLeft->setFlip(true);
	tileLeft->setAlign(ALIGN_RIGHT);
	tileLeft->setVAlign(VALIGN_BOTTOM);
	tileLeft->setGroup(Board::GetInstance());	
	
	tileLeftUp = new Element();
	tileLeftUp->addFrameFileFromData("/scenary/tile_0_up.png");
	tileLeftUp->setFlip(true);
	tileLeftUp->setAlign(ALIGN_RIGHT);
	tileLeftUp->setVAlign(VALIGN_BOTTOM);
	tileLeftUp->setGroup(Board::GetInstance());
	
	terrainOpened = new Element();
	terrainOpened->setAlign(ALIGN_CENTER);
	terrainOpened->addFrameFileFromData("/scenary/terrain0.jpg");
	addElement(terrainOpened);	
		
	typeTiled = 0;
	typeTerrain = 0;
	typeWall = 0;
	
}

Scenary::~Scenary () {
	unLoad();
}

void Scenary::setType (int t) { 
     type = t; 
     if (type == SCENARY_CLOSED) {
        guideRight->setCurrentFrame(0);
        guideLeft->setCurrentFrame(0);
     } else {
        guideRight->setCurrentFrame(1);
        guideLeft->setCurrentFrame(1);  
     }
}

void Scenary::clear() {
	for (int i=0; i<(int)objects.size(); i++) {
		//delete objects[i];
		objects[i]->unLoad();
	}
	objects.clear();
}

void Scenary::hide() {
    setAlpha(0);
    tileRight->setAlpha(0);
    tileRightUp->setAlpha(0);
    tileLeft->setAlpha(0);
    tileLeftUp->setAlpha(0);
}

void Scenary::show() {
    setFadeIn(1000);
    tileRight->setFadeIn(4000);
    tileRightUp->setFadeIn(4000);
    tileLeft->setFadeIn(4000);
    tileLeftUp->setFadeIn(4000);
}

void Scenary::setTypeTiled(int t) {
    if ( Missions::GetInstance()->currentLevel->existFile("tile_down.png") 
        && Missions::GetInstance()->currentLevel->existFile("tile_up.png") ) {
                                                                           
    	tileRight->changeFrameFile(0, Missions::GetInstance()->currentLevel->getPath() + "/tile_down.png");
    	tileRightUp->changeFrameFile(0, Missions::GetInstance()->currentLevel->getPath() + "/tile_up.png");
    	tileLeft->changeFrameFile(0, Missions::GetInstance()->currentLevel->getPath() + "/tile_down.png");
    	tileLeftUp->changeFrameFile(0, Missions::GetInstance()->currentLevel->getPath() + "/tile_up.png");
    	
    	Board::GetInstance()->tiledOfLevel = true;
    	
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
    	
    	Board::GetInstance()->tiledOfLevel = false;
    	
   }
}

void Scenary::setTypeTerrain(int t) {
     
    if ( Missions::GetInstance()->currentLevel->existFile("terrain.jpg") ) {
                                                                           
        terrainOpened->changeFrameFile(0, Missions::GetInstance()->currentLevel->getPath() + "/terrain.jpg");
        Board::GetInstance()->terrainOfLevel = true;
        
    } else {
    	if (t<BoardInfo::GetInstance()->getValueToInt("NTYPES_TERRAIN")) {	
    		typeTerrain = t;
    	} else {
    		typeTerrain = 0;
    	}
    	
    	char tmp[4];
    	sprintf(tmp, "%d", typeTerrain);
    	
    	terrainOpened->changeFrameFileFromData(0, "/scenary/terrain"+string(tmp)+".jpg");
    	
    	Board::GetInstance()->terrainOfLevel = false;
    	
    }
}

void Scenary::setTypeWall(int t) {
     
    if ( Missions::GetInstance()->currentLevel->existFile("wallscenary.png") ) {
                                                                           
        wallLeft->changeFrameFile(0, Missions::GetInstance()->currentLevel->getPath() + "/wallscenary.png");
		wallRight->changeFrameFile(0, Missions::GetInstance()->currentLevel->getPath() + "/wallscenary.png");
        Board::GetInstance()->wallScennaryOfLevel = true;
        
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
    	
    	Board::GetInstance()->wallScennaryOfLevel = false;
    	
    }
}

void Scenary::scaleTiles (float scale) {
	tileRight->setCurrentScale(scale);
	tileRightUp->setCurrentScale(scale);
	tileLeft->setCurrentScale(scale);
	tileLeftUp->setCurrentScale(scale);
	separatedTilesClosed = 25.0 * scale;
}

void Scenary::setColorInWalls(int r, int g, int b) { 
     colorRWallClosed = r;
     colorGWallClosed = g;
     colorBWallClosed = b;
          
     wallLeft->setRGB(r, g, b); 
     wallRight->setRGB(r, g, b); 
}

void Scenary::addTextObject(string t, string f, int a, Color c, int x, int y, float scale, bool flip, bool lock) {
	
	ObjectScenary *obj = new ObjectScenary();
	obj->setType("text");
	
	obj->setText(t, f, a, c);
	
	obj->addFrameText(f, t, a);
	
	obj->setRGB(c.r, c.g, c.b);
	
	obj->createBorder(220, 20, 20, 2, 5);
	obj->hideBorder();
	obj->setX(x);
	obj->setY(y);
	obj->setCurrentScale(scale);
	obj->setTypeScenary(type);
	obj->setTypeObject(TYPEOBJECT_TEXT);
	obj->setFlip(flip);
	addObject(TYPEOBJECT_TEXT, obj, lock);
}

void Scenary::addObject(int typeObj, int origenObj, string object) {
	addObject(typeObj, origenObj, object, 30, 0);
}

void Scenary::addObject(int typeObj, int origenObj, string object, int x, int y) {
	addObject(typeObj, origenObj, object, x, y, 1.0);
}

void Scenary::addObject(int typeObj, int origenObj, string object, int x, int y, float scale) {
	addObject(typeObj, origenObj, object, x, y, scale, false);
}

void Scenary::addObject(int typeObj, int origenObj, string object, int x, int y, float scale, bool flip) {
	addObject(typeObj, origenObj, object, x, y, scale, flip, false);
}

void Scenary::addObject(int typeObj, int origenObj, string object, int x, int y, float scale, bool flip, bool lock) {
	char tmp[128];
	bool addobj = true;
	
	TypeObjectScenary *os = TypeObjectsScenary::GetInstance()->getObject(object);
	
	if ( (os==NULL) && (origenObj==ORIGENOBJECT_GAME) ) {
		addobj = false;
	}
	
	if (addobj) {
		ObjectScenary *obj = new ObjectScenary();
		if (origenObj==ORIGENOBJECT_GAME) {
			sprintf(tmp, "%s/scenary/%s", DATA_DIR, os->file.c_str());
			obj->setMinScale(os->minScale);
			obj->setMaxScale(os->maxScale);
		} else {
			sprintf(tmp, "%s/objects/%s", Missions::GetInstance()->currentLevel->getPath().c_str(), object.c_str());
		}
		obj->setType(object);
		obj->addFrameFile(tmp);
		obj->createBorder(220, 20, 20, 2, 5);
		obj->hideBorder();
		obj->setX(x);
		obj->setY(y);
		obj->setCurrentScale(scale);
		obj->setTypeScenary(type);
		obj->setTypeObject(typeObj);
		obj->setFlip(flip);
		addObject(origenObj, obj, lock);
	} else {
		printf("Object '%s' don't exist\n", object.c_str());
	}
}

void Scenary::addObject(int origenObj, ObjectScenary* el) { 
	addObject(origenObj, el, false);
}

void Scenary::addObject(int origenObj, ObjectScenary* el, bool lock) { 
	el->setOrigen(origenObj);
    addElement(el);
	objects.push_back(el); 
	el->setGroup(this); 
	if (type==SCENARY_CLOSED) {
    	if (el->getX()<el->getDisplacementInXByGroups()) { 
    		el->setFlip(true); 
    		el->setAlign(ALIGN_RIGHT); 
    		el->iconZoomin->addX(-el->getWidth());
    		el->iconZoomout->addX(-el->getWidth());
    		el->iconDuplicate->addX(-el->getWidth());
    		el->iconDelete->addX(-el->getWidth());
    		el->iconLock->addX(-el->getWidth());
    		el->iconFlip->addX(-el->getWidth());
    		el->iconOrderBottom->addX(-el->getWidth());
    		el->iconOrderTop->addX(-el->getWidth());
    	} 
    }
    if (lock) el->swapLock();
}

void Scenary::onOver() {
	if (editable) {
		int i;
		for (i=0; i<(int)objects.size(); i++) {
			objects[i]->onOver();
		}
		
		int objColor = -1;
		for (i=0; i<(int)objects.size(); i++) {
			if ( (objects[i]->isOnMouseOver()) && (!objects[i]->getLock()) ) {
                if (objColor < 0) {
                    objColor = i;
                } else {
                    if (objects[i]->getIndexZ() >= objects[objColor]->getIndexZ()) {
                        objColor = i;
                    }
                }
			}
        }
        if (objColor >= 0) {
            for (i=0; i<(int)objects.size(); i++) {
                if (i==objColor) {
					objects[i]->setRGB(160, 160, 160);
                } else {
					if (objects[i]->getTypeObject()==TYPEOBJECT_TEXT) {
						objects[i]->setRGB(objects[i]->getColorText().r, objects[i]->getColorText().g, objects[i]->getColorText().b);
					} else {
						objects[i]->setRGB(255, 255, 255);
					}
                }
            }
        }
	}
}

void Scenary::verifyClick () {
	if (editable) {
		int i;
		int objDrag = -1;
		for (i=0; i<(int)objects.size(); i++) {
			if ( (objects[i]->isOnMouseOver()) && (!objects[i]->getLock()) ) {
                if (objDrag < 0) {
                    objDrag = i;
                } else {
                    if (objects[i]->getIndexZ() >= objects[objDrag]->getIndexZ()) {
                        objDrag = i;
                    }
                }
			}
        }
        if (objDrag >= 0) objects[objDrag]->startDrag();        
		for (i=0; i<(int)objects.size(); i++) {
			/*if (objects[i]->isOnMouseOver()) {
				objects[i]->startDrag();
			}*/
			if (objects[i]->getShowIcons()) {
				if (objects[i]->iconZoomin->isOnMouseOver()) {
					if (objects[i]->getCurrentScaleX()>objects[i]->getMinScale()) objects[i]->addCurrentScale(-0.1);
				}
				if (objects[i]->iconZoomout->isOnMouseOver()) {
					if (objects[i]->getCurrentScaleX()<objects[i]->getMaxScale()) objects[i]->addCurrentScale(0.1);
				}
				if (objects[i]->iconDuplicate->isOnMouseOver()) {
					char tmp[128];
					ObjectScenary *obj = new ObjectScenary();
					obj->setType(objects[i]->getType());
					if (objects[i]->getOrigen()==ORIGENOBJECT_GAME) {
						sprintf(tmp, "%s/scenary/%s",  DATA_DIR, TypeObjectsScenary::GetInstance()->getObject(objects[i]->getType())->file.c_str());
					} else {
						sprintf(tmp, "%s/objects/%s", Missions::GetInstance()->currentLevel->getPath().c_str(), objects[i]->getType().c_str());
					}
					obj->addFrameFile(tmp);
					float dx = objects[i]->getXWithoutDisplacementByGroups()+objects[i]->getWidth();
					if (objects[i]->getX()+objects[i]->getWidth()>740) {
                          dx = objects[i]->getXWithoutDisplacementByGroups()-objects[i]->getWidth();
                    }
					obj->createBorder(220, 20, 20, 2, 5);
					obj->hideBorder();
					obj->setX(dx);
					obj->setY(objects[i]->getYWithoutDisplacementByGroups());
					obj->setCurrentScale(objects[i]->getCurrentScaleX());
					obj->setTypeScenary(objects[i]->getTypeScenary());
					obj->setTypeObject(objects[i]->getTypeObject());
					obj->setFlip(objects[i]->getFlip());
					addObject(objects[i]->getOrigen(), obj);
				}
				if (objects[i]->iconDelete->isOnMouseOver()) {
					vector<ObjectScenary*>::iterator e = objects.begin();
					objects.erase(e+i);
				}
				if (objects[i]->iconLock->isOnMouseOver()) {
					objects[i]->swapLock();
				}
				if (objects[i]->iconOrderTop->isOnMouseOver()) {
					if (i<(int)objects.size()-1) {
                         ObjectScenary* aux = objects[i];
                         objects[i] = objects[i+1];
                         objects[i+1] = aux;
                    }
				}
				if (objects[i]->iconOrderBottom->isOnMouseOver()) {
					if (i>0) {
                         ObjectScenary* aux = objects[i];
                         objects[i] = objects[i-1];
                         objects[i-1] = aux;
                    }
				}
				if (objects[i]->getTypeScenary()==SCENARY_OPENED) {
                    if (objects[i]->iconFlip->isOnMouseOver()) {
                        objects[i]->swapFlip();
                    }
                }
			}
		}
	}
}

void Scenary::verifyShowIcons () {
	if (editable) {
		int objSelect = -1;
		Uint8 *keystate = SDL_GetKeyState(NULL);
		if ( keystate[SDLK_RCTRL] || keystate[SDLK_LCTRL]) {
			for (int i=0; i<(int)objects.size(); i++) {
				if ( (objects[i]->isOnMouseOver()) && (objects[i]->getLock()) ) {
					if (objSelect < 0) {
						objSelect = i;
					} else {
						if (objects[i]->getIndexZ() >= objects[objSelect]->getIndexZ()) {
							objSelect = i;
						}
					}
				}
			}
		} else {
			for (int i=0; i<(int)objects.size(); i++) {
				if ( (objects[i]->isOnMouseOver()) && (!objects[i]->getLock()) ) {
					if (objSelect < 0) {
						objSelect = i;
					} else {
						if (objects[i]->getIndexZ() >= objects[objSelect]->getIndexZ()) {
							objSelect = i;
						}
					}
				}
			}
		}
  
		int i;
		for (i=0; i<(int)objects.size(); i++) {
			if ( (objects[i]->isOnMouseOver()) && (i==objSelect) ) {
				objects[i]->swapShowIcons();
				if (objects[i]->getShowIcons()) {
					objects[i]->showBorder();
				} else {
					objects[i]->hideBorder();
				}
			} else {
				objects[i]->setShowIcons(false);
				objects[i]->hideBorder();
			}
		}
		if (objSelect>=0) {
    		objects[objSelect]->setX(objects[objSelect]->getXWithoutDisplacementByGroups());
    		objects[objSelect]->setY(objects[objSelect]->getYWithoutDisplacementByGroups());
        }
	}
}

string Scenary::toXML () {
    string xml="";
    string tscenary = "closed";
	switch(type) {
		case SCENARY_CLOSED:
			tscenary = "closed";
		break;
		case SCENARY_OPENED:
			tscenary = "opened";
		break;
    }
	    
    char tmp_val[128];
    sprintf (tmp_val, "\t<scenary type=\"%s\" red=\"%d\" green=\"%d\" blue=\"%d\" type-tiled=\"%d\" ntiles=\"%d\" type-terrain=\"%d\" type-wall=\"%d\">\n", tscenary.c_str(), getR_ColorInWalls(), getG_ColorInWalls(), getB_ColorInWalls(), typeTiled, nVerticalTiles, typeTerrain, typeWall);
    xml = xml + tmp_val;
    
	int i;
	for (i=0; i<(int)objects.size(); i++) {
		char tmp_val2[512];
        char tmp_f[8];
        if (objects[i]->getFlip()) {
           sprintf(tmp_f, "true");
        } else {
           sprintf(tmp_f, "false");
        }
        char tmp_l[8];
        if (objects[i]->getLock()) {
           sprintf(tmp_l, "true");
        } else {
           sprintf(tmp_l, "false");
        }
		char tmp_o[8];
        if (objects[i]->getOrigen() == ORIGENOBJECT_GAME) {
           sprintf(tmp_o, "game");
        } else {
           sprintf(tmp_o, "personal");
        }

        if (objects[i]->getTypeObject() == TYPEOBJECT_2D) {
        	sprintf (tmp_val2, "\t\t<object name=\"%s\" x=\"%d\" y=\"%d\" scale=\"%f\" flip=\"%s\" lock=\"%s\" origen=\"%s\" type=\"2d\" />\n", objects[i]->getType().c_str(), (int)objects[i]->getXWithoutDisplacementByGroups(), (int)objects[i]->getYWithoutDisplacementByGroups(), objects[i]->getCurrentScaleX(), tmp_f, tmp_l, tmp_o);
        } else if (objects[i]->getTypeObject() == TYPEOBJECT_TEXT) {
        	sprintf (tmp_val2, "\t\t<object name=\"%s\" x=\"%d\" y=\"%d\" scale=\"%f\" flip=\"%s\" lock=\"%s\" origen=\"%s\" type=\"text\" text=\"%s\" font=\"%s\" align=\"%d\" r=\"%d\" g=\"%d\" b=\"%d\" />\n", objects[i]->getType().c_str(), (int)objects[i]->getXWithoutDisplacementByGroups(), (int)objects[i]->getYWithoutDisplacementByGroups(), objects[i]->getCurrentScaleX(), tmp_f, tmp_l, tmp_o, objects[i]->getText().c_str(), objects[i]->getFontText().c_str(), objects[i]->getAlignText(), objects[i]->getColorText().r, objects[i]->getColorText().g, objects[i]->getColorText().b);
        } else {
			sprintf (tmp_val2, "\t\t<object name=\"%s\" x=\"%d\" y=\"%d\" scale=\"%f\" flip=\"%s\" lock=\"%s\" origen=\"%s\" type=\"3d\" />\n", objects[i]->getType().c_str(), (int)objects[i]->getXWithoutDisplacementByGroups(), (int)objects[i]->getYWithoutDisplacementByGroups(), objects[i]->getCurrentScaleX(), tmp_f, tmp_l, tmp_o);
		}
		
        xml = xml + tmp_val2;
	}
    
    xml = xml + "\t</scenary>\n";
    
    return xml;
}

void Scenary::removeDnd () {
	if (editable) {
		int i;
		for (i=0; i<(int)objects.size(); i++) {
			objects[i]->drop();
		}
	}
}

void Scenary::draw() {
	if (type==SCENARY_CLOSED) {
		drawScenaryClosed();
	} else {
		drawScenaryOpened();
	}
	if (editable && showGuides) {
		guideLeft->draw();
		guideRight->draw();
	}
}

void Scenary::drawScenaryClosed() {
	wallLeft->draw();
	wallRight->draw();
	
	paintTiled();
	
	shadowWall->draw();
	for (int i=0; i<(int)objects.size(); i++) {
		objects[i]->draw();
	}

}

void Scenary::drawScenaryOpened() {
	
	terrainOpened->draw();
	for (int i=0; i<(int)objects.size(); i++) {
		objects[i]->draw();
	}
	
	paintTiled();
		
}

void Scenary::paintTiled() {
	int x, y;
	
	for (y=0; y<nVerticalTiles; y++) {
		for (x=0; x<Board::GetInstance()->getCols()+1; x++) {
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

void Scenary::unLoad() {
	
	delete tileLeft;
	delete tileLeftUp;
	delete tileRight;
	delete tileRightUp;
	delete wallLeft;
	delete wallRight;
	delete guideLeft;
	delete guideRight;
	delete shadowWall;
	delete terrainOpened;
	
	for (int i=0; i<(int)objects.size(); i++) {
		delete objects[i];
	}
	
	objects.clear();
	
}

/*****************************
**
** CLASE ElementIsometric
**
******************************/
	

ElementIsometric::ElementIsometric() : AnimatedElement () {
	heightElement = 0;
	originalHeightElement = 0;
	xBoard = 0;
	yBoard = 0;
	displacementX = 0; 
	originalDisplacementX = 0;
}

ElementIsometric::~ElementIsometric () {
	unLoad();
}

/*****************************
**
** CLASE MovableElementIsometric
**
******************************/
	

MovableElementIsometric::MovableElementIsometric() : ElementIsometric () {
	direction = TILE_RIGHT;
	isMoving = false;
	nMovement = 0;
}

MovableElementIsometric::~MovableElementIsometric () {
	unLoad();
}

bool MovableElementIsometric::setPosition(BoardPosition p) { 
    if (!p.out) { 
		int rel = Board::GetInstance()->referencePositions(getPosition(), p);
		if (rel== TILE_CENTER) {
			//Board::GetInstance()->nextTurn();
			return true;
		}
        if (!Board::GetInstance()->hasWallBetweenCells(getPosition(), p)) {
            if ( rel != TILE_OTHER ) {
                    if ( (rel== TILE_LEFT) && (getAnimation()->getName() != "walk_left") ) {
                         setForceAnimation("walk_left");
                         setDirection(TILE_LEFT);
                    } else if ( (rel== TILE_RIGHT) && (getAnimation()->getName() != "walk_right") ) {
                         setForceAnimation("walk_right");
                         setDirection(TILE_RIGHT);
                    } else if ( (rel== TILE_UP) && (getAnimation()->getName() != "walk_up") ) {
                         setForceAnimation("walk_up");
                         setDirection(TILE_UP);
                    } else if ( (rel== TILE_DOWN) && (getAnimation()->getName() != "walk_down") ) {
                         setForceAnimation("walk_down");
                         setDirection(TILE_DOWN);
                    }
                    setMovementNormal(Plot::GetInstance()->getX(p.x,p.y), Plot::GetInstance()->getY(p.x,p.y)-heightElement, 650); 
                    /*if ( (rel==TILE_UP) || (rel==TILE_LEFT) ) {
                       xBoard = p.x; 
                       yBoard = p.y; 
                    }*/
					setNextXBoard(p.x);
					setNextYBoard(p.y);
                    isMoving = true; 
                    addHistoryPositions(p);
            }
			return true;
        }
    }
	return false;
}

bool MovableElementIsometric::setInitialPosition(BoardPosition p) { 
     if (!p.out) { 
          BoardPosition old = getPosition(); 
          xBoard = p.x; 
          yBoard = p.y;  
          setX(Plot::GetInstance()->getX(p.x,p.y)); 
          setY(Plot::GetInstance()->getY(p.x,p.y)-heightElement); 
          addHistoryPositions(p); 
          return true; 
     } 
     return false; 
}

bool MovableElementIsometric::setForcePosition(BoardPosition p) { 
     if (!p.out) { 
          BoardPosition old = getPosition(); 
          xBoard = p.x; 
          yBoard = p.y;  
          if ( !Board::GetInstance()->verifyPositions(getPosition(), old) ) { 
               setX(Plot::GetInstance()->getX(p.x,p.y)); 
               setY(Plot::GetInstance()->getY(p.x,p.y)-heightElement); 
          } 
          addHistoryPositions(p); 
          return true; 
     } 
     return false; 
}

void MovableElementIsometric::stop() {
    if (getDirection()==TILE_RIGHT) {
       setForceAnimation("stop_right");
    } else if (getDirection()==TILE_LEFT) {
       setForceAnimation("stop_left");
    } else if (getDirection()==TILE_UP) {
       setForceAnimation("stop_up");
    } else if (getDirection()==TILE_DOWN) {
       setForceAnimation("stop_down");
    }
	isMoving = false;
	removeTypeMovement();
	/*if ((int)historyPositions.size()>0) {
       xBoard = historyPositions[historyPositions.size()-1].x;
       yBoard = historyPositions[historyPositions.size()-1].y;
    }*/
}

void MovableElementIsometric::addHistoryPositions(BoardPosition p) { 
	if (nMovement < (int)historyPositions.size()) {
		int i;
		for (i=(int)historyPositions.size()-1; i>nMovement-1; i--) {
			historyPositions.erase(historyPositions.begin()+i);
		}
	}
	historyPositions.push_back(p); 
	nMovement++; 
}

void MovableElementIsometric::previousHistoryPositions() { 
	if (nMovement>1) { 
		nMovement--; 
		BoardPosition p = historyPositions[nMovement-1]; 
		xBoard = p.x; 
		yBoard = p.y; 
		setX(Plot::GetInstance()->getX(p.x,p.y)); 
		setY(Plot::GetInstance()->getY(p.x,p.y)-heightElement);
		if (nMovement-2 > 0) {
			int i = Board::GetInstance()->referencePositions(historyPositions[nMovement-2], p);
			if (i == TILE_LEFT) {
				setForceAnimation("stop_left");
			} else if (i == TILE_RIGHT) {
				setForceAnimation("stop_right");
			} else if (i == TILE_UP) {
				setForceAnimation("stop_up");
			} else if (i == TILE_DOWN) {
				setForceAnimation("stop_down");
			}
		} else {
			setForceAnimation("stop_right");
		}
	} 
}

void MovableElementIsometric::nextHistoryPositions() { 
	if (nMovement<(int)historyPositions.size()) { 
		nMovement++; 
		BoardPosition p = historyPositions[nMovement-1]; 
		xBoard = p.x; 
		yBoard = p.y; 
		setX(Plot::GetInstance()->getX(p.x,p.y)); 
		setY(Plot::GetInstance()->getY(p.x,p.y)-heightElement);
		if (nMovement-2 > 0) {
			int i = Board::GetInstance()->referencePositions(historyPositions[nMovement-2], p);
			if (i == TILE_LEFT) {
				setForceAnimation("stop_left");
			} else if (i == TILE_RIGHT) {
				setForceAnimation("stop_right");
			} else if (i == TILE_UP) {
				setForceAnimation("stop_up");
			} else if (i == TILE_DOWN) {
				setForceAnimation("stop_down");
			}
		} else {
			setForceAnimation("stop_right");
		}
	} 
}

/*****************************
**
** CLASE Player
**
******************************/
	

Player::Player() : MovableElementIsometric () {
}

Player::~Player () {
	unLoad();
}

bool Player::setPosition(BoardPosition p) { 
    if (!p.out) { 
		// verifing is nimuh walk to enemy
		if (Board::GetInstance()->hasEnemy1) {
			if ( Board::GetInstance()->verifyPositions(Board::GetInstance()->getPositionEnemy1(), p) ) {
				Board::GetInstance()->nextTurn();
				return false;
			}
		}
		if (Board::GetInstance()->hasEnemy2) {
    		if ( Board::GetInstance()->verifyPositions(Board::GetInstance()->getPositionEnemy2(), p) ) {
    			Board::GetInstance()->nextTurn();
    			return false;
    		}
        }
		if (Board::GetInstance()->hasEnemy3) {
    		if ( Board::GetInstance()->verifyPositions(Board::GetInstance()->getPositionEnemy3(), p) ) {
    			Board::GetInstance()->nextTurn();
    			return false;
    		}
        }
		
		int rel = Board::GetInstance()->referencePositions(getPosition(), p);
		if (rel== TILE_CENTER) {
            addHistoryPositions(p);
			Board::GetInstance()->nextTurn();
			return true;
		}
        if (!Board::GetInstance()->hasWallBetweenCells(getPosition(), p)) {
            if ( rel != TILE_OTHER ) {
                    if (rel== TILE_LEFT) {
                         setForceAnimation("walk_left");
                         setDirection(TILE_LEFT);
                    } else if (rel== TILE_RIGHT) {
                         setForceAnimation("walk_right");
                         setDirection(TILE_RIGHT);
                    } else if (rel== TILE_UP) {
                         setForceAnimation("walk_up");
                         setDirection(TILE_UP);
                    } else if (rel== TILE_DOWN) {
                         setForceAnimation("walk_down");
                         setDirection(TILE_DOWN);
                    }
                    setMovementNormal(Plot::GetInstance()->getX(p.x,p.y), Plot::GetInstance()->getY(p.x,p.y)-heightElement, 650); 
                    /*if ( (rel==TILE_UP) || (rel==TILE_LEFT) ) {
                       xBoard = p.x; 
                       yBoard = p.y; 
                    }*/
					setNextXBoard(p.x);
					setNextYBoard(p.y);
                    isMoving = true; 
                    addHistoryPositions(p);
					return true;
            }
			return false;
        }
    }
	return false;
}


/*****************************
**
** CLASE Enemy
**
******************************/
	

Enemy::Enemy() : MovableElementIsometric () {
    firstMovementHorizontal = true;
	stopped = false;
}

Enemy::~Enemy () {
	unLoad();
}

bool Enemy::move() { 
	if (!stopped) {
		if (firstMovementHorizontal) {
			if (getXBoard() == Board::GetInstance()->getPositionPlayer().x) {
				return move_Vertical(false);
			} else {
				return move_Horizontal(false);
			}
		} else {
			if (getYBoard() == Board::GetInstance()->getPositionPlayer().y) {
				return move_Horizontal(false);
			} else {
				return move_Vertical(false);
			} 
		}
	}
	return false;
}

bool Enemy::move_Vertical(bool forceNextTurnWithWall) { 
	if (getYBoard() < Board::GetInstance()->getPositionPlayer().y) {
		BoardPosition p;
		p.x = getXBoard();
		p.y = getYBoard()+1;
		p.out = !Board::GetInstance()->positionIsOnBoard(p);
		if ( !Board::GetInstance()->hasWallBetweenCells(getPosition(), p) ) {
			setPosition(p);
			return true;
		} else {
			if (!forceNextTurnWithWall) {
				return move_Horizontal(true);
			} else {
				setForceAnimation("stop_down"); // CUIDADO
				setForcePosition(getPosition());
				//Board::GetInstance()->nextTurn();
				return false;
			}
		}
	} else if (getYBoard() > Board::GetInstance()->getPositionPlayer().y) {
		BoardPosition p;
		p.x = getXBoard();
		p.y = getYBoard()-1;
		p.out = !Board::GetInstance()->positionIsOnBoard(p);
		if ( !Board::GetInstance()->hasWallBetweenCells(getPosition(), p) ) {
			setPosition(p);
			return true;
		} else {
			if (!forceNextTurnWithWall) {
				return move_Horizontal(true);
			} else {
				setForceAnimation("stop_up"); // CUIDADO
				setForcePosition(getPosition());
				//Board::GetInstance()->nextTurn();
				return false;
			}
		}
	} else {
		if (getXBoard() < Board::GetInstance()->getPositionPlayer().x) {
			setForceAnimation("stop_right");
		} else if (getXBoard() > Board::GetInstance()->getPositionPlayer().x) {
			setForceAnimation("stop_left");
		}
		setForcePosition(getPosition());
		//Board::GetInstance()->nextTurn();
		return false;
	}

	return false;
}

bool Enemy::move_Horizontal(bool forceNextTurnWithWall) { 
	if (getXBoard() < Board::GetInstance()->getPositionPlayer().x) {
		BoardPosition p;
		p.x = getXBoard()+1;
		p.y = getYBoard();
		p.out = !Board::GetInstance()->positionIsOnBoard(p);
		if ( !Board::GetInstance()->hasWallBetweenCells(getPosition(), p) ) {
			setPosition(p);
			return true;
		} else {
			if (!forceNextTurnWithWall) {
				return move_Vertical(true);
			} else {
				setForceAnimation("stop_right"); // CUIDADO
				setForcePosition(getPosition());
				//Board::GetInstance()->nextTurn();
				return false;
			}
		}
	} else if (getXBoard() > Board::GetInstance()->getPositionPlayer().x) {
		BoardPosition p;
		p.x = getXBoard()-1;
		p.y = getYBoard();
		p.out = !Board::GetInstance()->positionIsOnBoard(p);
		if ( !Board::GetInstance()->hasWallBetweenCells(getPosition(), p) ) {
			setPosition(p);
			return true;
		} else {
			if (!forceNextTurnWithWall) {
				return move_Vertical(true);
			} else {
				setForceAnimation("stop_left"); // CUIDADO
				setForcePosition(getPosition());
				//Board::GetInstance()->nextTurn();
				return false;
			}
		}
	} else {
		if (getYBoard() < Board::GetInstance()->getPositionPlayer().y) {
			setForceAnimation("stop_down");
		} else if (getYBoard() > Board::GetInstance()->getPositionPlayer().y) {
			setForceAnimation("stop_up");
		}
		setForcePosition(getPosition());
		//Board::GetInstance()->nextTurn();
		return false;
	}

	return false;
}

void Enemy::stop() {
	if ( (Board::GetInstance()->getTurn()==TURN2_ENEMY) 
		|| (Board::GetInstance()->getTurn()==TURN_ENEMY3) ) {
		if (getDirection()==TILE_RIGHT) {
		   setForceAnimation("stop_right");
		} else if (getDirection()==TILE_LEFT) {
		   setForceAnimation("stop_left");
		} else if (getDirection()==TILE_UP) {
		   setForceAnimation("stop_up");
		} else if (getDirection()==TILE_DOWN) {
		   setForceAnimation("stop_down");
		}
	}
	isMoving = false;
	removeTypeMovement();
}

/*****************************
**
** CLASE Door
**
******************************/
	

Door::Door() : ElementIsometric () {
	
	//addFrameFileFromData("/board/door_h.png");
	addRangeFramesFromData("board/door_h", "png", 0, 3);
	
	//addFrameFileFromData("/board/door_v.png");
	addRangeFramesFromData("board/door_v", "png", 0, 3);
	
	Animation a;
	a.setName("horizontal");
	a.setCyclesBetweenFrames(16);
	a.addRangeFrame(0, 3, 1);
	addAnimation(a);
	Animation b;
	b.setName("vertical");
	b.setCyclesBetweenFrames(16);
	b.addRangeFrame(4, 7, 1);
	addAnimation(b);
	
	setDoorPosition(OTHER);
	
}

Door::~Door () {
	unLoad();
}

void Door::setDoorPosition(int p) { 
	doorPosition = p;
	if (doorPosition == DOWN) {
		setAlign(ALIGN_RIGHT);
		setHeightElement(95*getCurrentScaleX());
		setForceAnimation("horizontal");
	} else if (doorPosition == UP) {
		setAlign(ALIGN_LEFT);
		setHeightElement(125*getCurrentScaleX());
		setForceAnimation("horizontal");
	} else if (doorPosition == LEFT) {
		setAlign(ALIGN_RIGHT);
		setHeightElement(125*getCurrentScaleX());
		setForceAnimation("vertical");
	} else if (doorPosition == RIGHT) {
		setAlign(ALIGN_LEFT);
		setHeightElement(95*getCurrentScaleX());
		setForceAnimation("vertical");
	}
}

bool Door::setForcePosition(BoardPosition p) { 
	if (!p.out) { 
		if ( (p.x==0) || (p.x==Board::GetInstance()->getCols()-1)
				|| (p.y==0) || (p.y==Board::GetInstance()->getRows()-1) ) {
			xBoard = p.x; 
			yBoard = p.y; 
					
			if (p.x==0) {
				setDoorPosition(LEFT);
				setX(Plot::GetInstance()->getX(p.x,p.y)+(20*getCurrentScaleX())); 
				setY(Plot::GetInstance()->getY(p.x,p.y)-heightElement); 
			}
			if (p.x==Board::GetInstance()->getCols()-1) {
				setDoorPosition(RIGHT);
				setX(Plot::GetInstance()->getX(p.x,p.y)-(30*getCurrentScaleX())); 
				setY(Plot::GetInstance()->getY(p.x,p.y)-heightElement); 
			}
			if (p.y==0) {
				setDoorPosition(UP);
				setX(Plot::GetInstance()->getX(p.x,p.y)-(23*getCurrentScaleX())); 
				setY(Plot::GetInstance()->getY(p.x,p.y)-heightElement); 
			}
			if (p.y==Board::GetInstance()->getRows()-1) {
				setDoorPosition(DOWN);
				setX(Plot::GetInstance()->getX(p.x,p.y)+(25*getCurrentScaleX())); 
				setY(Plot::GetInstance()->getY(p.x,p.y)-heightElement); 
			}
			
			return true; 
			
		} else {
			setDoorPosition(OTHER);
			return false; 
		}
	}
	setDoorPosition(OTHER);
	return false; 
}

bool Door::setForcePosition(int x, int y) { 
	BoardPosition p; 
	p.x=x; 
	p.y=y; 
	p.out = !Board::GetInstance()->positionIsOnBoard(p); 
	return setForcePosition(p); 
}

/*****************************
**
** CLASE Board
**
******************************/

Board* Board::instance = NULL;

Board::Board() : Group () {
	multiLanguage = false;
	mlPause = 0;
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
	canChangeInHistory_Enemy1 = false;
	hasEnemy2 = false;
	canChangeInHistory_Enemy2 = false;
	hasEnemy3 = false;
	canChangeInHistory_Enemy3 = false;
	hasBlackHole0 = false;
	canChangeInHistory_BlackHole0 = false;
	hasBlackHole1 = false;
	canChangeInHistory_BlackHole1 = false;
	teletransport = false;
	doorKeyClosed = true;
	hasTrap = false;
	hasKey = false;
	canChangeInHistory_Key = false;
	hasTray = false;
	canChangeInHistory_Tray = false;
	directionKey = "right";
	todoNextTurn = false;
	catchedEnemy1 = false;
    catchedEnemy2 = false;
    inExplosion = false;
    paddingExplosion = 0;
	turn = TURN_PLAYER;
	
	town.name="";
	town.province="";
	town.nickname="";
	
	infoTray.title="";
	infoTray.text="";
	
	isAnimationWaiting = false;
	typeAnimationWaiting = 0;
	
	wallsOfLevel = false;
	terrainOfLevel = false;
	wallScennaryOfLevel = false;
	musicOfLevel = false;
	pavementOfLevel = false;
	floorOfLevel = false;
	tiledOfLevel = false;
	
	totalHistory = 0;
	currentHistory = 0;
	
}

Board* Board::GetInstance () {
	if ( instance == NULL ) {
		instance = new Board();
	}
	return instance;	
}

void Board::setTypeWall(int t) {
     
    if ( Missions::GetInstance()->currentLevel->existFile("wall_h.png") 
        && Missions::GetInstance()->currentLevel->existFile("wall_v.png") ) {
                                                                          
    	wallBottom->changeFrameFile(0, Missions::GetInstance()->currentLevel->getPath()+"/wall_h.png");
    	wallRight->changeFrameFile(0, Missions::GetInstance()->currentLevel->getPath()+"/wall_v.png");
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
    	
    	wallsOfLevel = false;
    }
	
	
}

void Board::setTypeFloor(int t) {
     
    if ( Missions::GetInstance()->currentLevel->existFile("floor0.png") 
        && Missions::GetInstance()->currentLevel->existFile("floor1.png") ) {
    	floor0->changeFrameFile(0, Missions::GetInstance()->currentLevel->getPath()+"/floor0.png");
    	floor1->changeFrameFile(0, Missions::GetInstance()->currentLevel->getPath()+"/floor1.png");
    	floorOfLevel = true;
    	
    } else {
    	if (t<BoardInfo::GetInstance()->getValueToInt("NTYPES_FLOOR")) {	
    		typeFloor = t;
    	} else {
    		typeFloor = 0;
    	}
    	
    	floor0->changeFrameFileFromData(0, "/board/floor", "png", typeFloor*2);
    	floor1->changeFrameFileFromData(0, "/board/floor", "png", (typeFloor*2)+1);
    	floorOfLevel = false;
    }
}

void Board::setTypePavement(int t) {
     
    if ( Missions::GetInstance()->currentLevel->existFile("pavement_bottom.png") 
        && Missions::GetInstance()->currentLevel->existFile("pavement_top.png") ) {
                                                                               
    	pavementTop->changeFrameFile(0, Missions::GetInstance()->currentLevel->getPath()+"/pavement_top.png");
    	pavementBottom->changeFrameFile(0, Missions::GetInstance()->currentLevel->getPath()+"/pavement_bottom.png");
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
    	
    	pavementOfLevel = false;
    	
    }
}

float Board::getScaleByTypeSize() {
	switch(typeSize) {
		case BOARD_6X6:
			return 1.0;
		break;
		case BOARD_7X7:
			return 0.86;
		break;
		case BOARD_8X8:
			return 0.76;
		break;
		case BOARD_9X9:
			return 0.67;
		break;
		case BOARD_10X10:
			return 0.61;
		break;
	}
	return 1.0;
}

void Board::setTypeSize(int t) {
	float s = 1.0;
	typeSize = t;
	switch(t) {
		case BOARD_6X6:
			pavementBottom->setY(179);
			s = getScaleByTypeSize();
			BoardScale::GetInstance()->setScale(s);
			cols = 6;
			rows = 6;
		break;
		case BOARD_7X7:
			pavementBottom->setY(178);
			s = getScaleByTypeSize();
			BoardScale::GetInstance()->setScale(s);
			cols = 7;
			rows = 7;
		break;
		case BOARD_8X8:
			pavementBottom->setY(182);
			s = getScaleByTypeSize();
			BoardScale::GetInstance()->setScale(s);
			cols = 8;
			rows = 8;
		break;
		case BOARD_9X9:
			pavementBottom->setY(177);
			s = getScaleByTypeSize();
			BoardScale::GetInstance()->setScale(s);
			cols = 9;
			rows = 9;
		break;
		case BOARD_10X10:
			pavementBottom->setY(178);
			s = getScaleByTypeSize();
			BoardScale::GetInstance()->setScale(s);
			cols = 10;
			rows = 10;
		break;
	}
	
	floor0->setCurrentScale(s);
	floor1->setCurrentScale(s);
	trap->setCurrentScale(s);
	
	particlesTrap->setCurrentScale(s);
	particlesTrap->setScaleHeightElement(s);
	
	scenary->scaleTiles(s);

	wallRight->setCurrentScale(s);
	wallRight->setScaleHeightElement(s);
	wallRight->setScaleDisplacementX(s);
	
	wallBottom->setCurrentScale(s);
	wallBottom->setScaleHeightElement(s);
	wallBottom->setScaleDisplacementX(s);
	
	nimuh->setCurrentScale(s);
	nimuh->setScaleHeightElement(s);
	
	enemy1->setCurrentScale(s);
	enemy1->setScaleHeightElement(s);
	
	enemy2->setCurrentScale(s);
	enemy2->setScaleHeightElement(s);
	
	enemy3->setCurrentScale(s);
	enemy3->setScaleHeightElement(s);
	
	blackHole0->setCurrentScale(s);
	blackHole0->setScaleHeightElement(s);
	
	blackHole1->setCurrentScale(s);
	blackHole1->setScaleHeightElement(s);
	
	particlesBlackHole0->setCurrentScale(s);
	particlesBlackHole0->setScaleHeightElement(s);
	
	particlesBlackHole1->setCurrentScale(s);
	particlesBlackHole1->setScaleHeightElement(s);
	
	arrow->setCurrentScale(s);
	arrow->setScaleHeightElement(s);
	
	door->setCurrentScale(s);
	door->setScaleHeightElement(s);
	
	key->setCurrentScale(s);
	key->setScaleHeightElement(s);
	
	tray->setCurrentScale(s);
	tray->setScaleHeightElement(s);
	
	doorKeyBottom->setCurrentScale(s);
	doorKeyBottom->setScaleHeightElement(s);
	
	doorKeyRight->setCurrentScale(s);
	doorKeyRight->setScaleHeightElement(s);
	
	floorOn->setCurrentScale(s);
	floorOn->setScaleHeightElement(s);
	
	paddingExplosion = (int)(30*s);

	MouseMapTile::GetInstance()->createMap();

}

void Board::loadLevel() {
	clear();
	parseScreenXML((char*)Missions::GetInstance()->pathXMLLevel().c_str());
	addStateHistory();
    scenary->hide();
}

void Board::clear() {
	
	history.clear();
	totalHistory = 0;
	currentHistory = 0;
    
    scenary->clear();
    
	wallsOfLevel = false;
	terrainOfLevel = false;
	wallScennaryOfLevel = false;
	musicOfLevel = false;
	pavementOfLevel = false;
	floorOfLevel = false;
	tiledOfLevel = false;
    
	for (int i=0; i<MAX_TILES_INLINE*MAX_TILES_INLINE; i++) {
		walls[i].wallBottom = false;
		walls[i].wallRight = false;
	}
	
	floor0->setAlpha(0);
	floor1->setAlpha(0);
	
	pavementTop->setAlpha(0);
	pavementBottom->setAlpha(0);
	
	wallBottom->setAlpha(0);
	wallRight->setAlpha(0);
	
	nimuh->setForcePosition(0,0);
	nimuh->clearHistoryPositions();
	nimuh->stop();
	nimuh->setForceAnimation("stop_right");
	nimuh->removeTypeMovement();
	nimuh->removeScale();
	nimuh->removeRotation();
	nimuh->removeAlpha();
	
	nimuh->hide();
	
	enemy1->setForcePosition(0,0);
	enemy1->clearHistoryPositions();
	enemy1->stop();
	enemy1->setForceAnimation("stop_right");
	enemy1->removeTypeMovement();
	enemy1->setStopped(false);

	enemy1->hide();

	enemy2->setForcePosition(0,0);
	enemy2->clearHistoryPositions();
	enemy2->stop();
	enemy2->setForceAnimation("stop_right");
	enemy2->removeTypeMovement();
	enemy2->setStopped(false);

	enemy2->hide();
	
	enemy3->setForcePosition(0,0);
	enemy3->clearHistoryPositions();
	enemy3->stop();
	enemy3->setForceAnimation("stop_right");
	enemy3->removeTypeMovement();
	enemy3->setStopped(false);

	enemy3->hide();

	hasEnemy1 = false;
	canChangeInHistory_Enemy1 = false;
	hasEnemy2 = false;
	canChangeInHistory_Enemy2 = false;
	hasEnemy3 = false;
	canChangeInHistory_Enemy3 = false;
	
	hasBlackHole0 = false;
	canChangeInHistory_BlackHole0 = false;
	hasBlackHole1 = false;
	canChangeInHistory_BlackHole1 = false;
	
	blackHole0->hide();
	blackHole1->hide();
	particlesBlackHole0->hide();
	particlesBlackHole1->hide();
	
	hasKey = false;
	canChangeInHistory_Key = false;
	directionKey = "right";
	doorKeyClosed = true;
	
	key->hide();
	doorKeyRight->hide();
	doorKeyBottom->hide();
	
	doorKeyRight->setForceAnimation("closed");
	doorKeyBottom->setForceAnimation("closed");
	
	tray->removeScale();
	tray->removeTypeMovement();
	tray->removeRotation();
	tray->removeAlpha();
	tray->hide();
	
	hasTray = false;
	canChangeInHistory_Tray = false;
	
	hasTrap = false;
	
	todoNextTurn = false;
	
	inExplosion = false;
		
	turn = TURN_PLAYER;
	
	beginAnimationWaiting();	

}

void Board::swapDoorKey() {
	if (hasKey) {
		if (doorKeyClosed) {
			doorKeyBottom->setForceAnimation("open", 1);
			doorKeyRight->setForceAnimation("open", 1);
		} else {
			doorKeyBottom->setForceAnimation("close", 1);
			doorKeyRight->setForceAnimation("close", 1);
		}
		Sounds::GetInstance()->getSound("doorkey")->play(3, 0);
		pause(800);
		doorKeyClosed = !doorKeyClosed;
	}
}

BoardPosition Board::getPositionPlayer() { 
	return nimuh->getPosition(); 
}

BoardPosition Board::getPositionEnemy1() { 
	return enemy1->getPosition(); 
}

BoardPosition Board::getPositionEnemy2() { 
	return enemy2->getPosition(); 
}

BoardPosition Board::getPositionEnemy3() { 
	return enemy3->getPosition(); 
}

void Board::setBlackHole0(int x, int y) { 
	BoardPosition p; 
	p.x = x; 
	p.y = y; 
	p.out = !positionIsOnBoard(p); 
	blackHole0->setForcePosition(p); 
	particlesBlackHole0->setInitialPosition(p); 
	hasBlackHole0 = true;
	canChangeInHistory_BlackHole0 = true;
}

void Board::setBlackHole1(int x, int y) { 
	BoardPosition p; 
	p.x = x; 
	p.y = y; 
	p.out = !positionIsOnBoard(p); 
	blackHole1->setForcePosition(p); 
	particlesBlackHole1->setInitialPosition(p); 
	hasBlackHole1 = true;
	canChangeInHistory_BlackHole1 = true;
}

void Board::setKey(int x, int y) { 
	BoardPosition p; 
	p.x = x; 
	p.y = y; 
	p.out = !positionIsOnBoard(p); 
	key->setInitialPosition(p); 
	hasKey = true;
	canChangeInHistory_Key = true;
}

void Board::setDoorKey(int x, int y, string dk) { 
	BoardPosition p; 
	p.x = x; 
	p.y = y; 
	p.out = !positionIsOnBoard(p); 
	doorKeyBottom->setInitialPosition(p); 
	doorKeyRight->setInitialPosition(p); 
	directionKey = dk;
	hasKey = true;
	canChangeInHistory_Key = true;
}

void Board::setPositionPlayer(int x, int y) { 
	BoardPosition p; 
	p.x = x; 
	p.y = y; 
	p.out = !positionIsOnBoard(p); 
	nimuh->setInitialPosition(p); 
}

void Board::setPositionEnemy1(int x, int y) { 
	BoardPosition p;
	p.x = x; 
	p.y = y; 
	p.out = !positionIsOnBoard(p); 
	enemy1->setInitialPosition(p); 
	hasEnemy1 = true;
	canChangeInHistory_Enemy1 = true;
}

void Board::setPositionEnemy2(int x, int y) { 
	BoardPosition p; 
	p.x = x; 
	p.y = y; 
	p.out = !positionIsOnBoard(p); 
	enemy2->setInitialPosition(p); 
	hasEnemy2 = true;
	canChangeInHistory_Enemy2 = true;
}

void Board::setPositionEnemy3(int x, int y) { 
	BoardPosition p; 
	p.x = x; 
	p.y = y; 
	p.out = !positionIsOnBoard(p); 
	enemy3->setInitialPosition(p); 
	hasEnemy3 = true;
	canChangeInHistory_Enemy3 = true;
}

void Board::setPositionExit(int x, int y) { 
	BoardPosition p; 
	p.x = x; 
	p.y = y; 
	p.out = !positionIsOnBoard(p); 
	door->setInitialPosition(p);
}

void Board::setPositionTrap(int x, int y) { 
	posTrap.x = x; 
	posTrap.y = y; 
	posTrap.out = !positionIsOnBoard(posTrap); 
	particlesTrap->setInitialPosition(posTrap); 
	hasTrap = true;
}

void Board::setPositionTray(int x, int y) { 
	BoardPosition p; 
	p.x = x; 
	p.y = y; 
	p.out = !positionIsOnBoard(p); 
	tray->setInitialPosition(p);
	hasTray = true;
	canChangeInHistory_Tray = true;
}

BoardPosition Board::getPositionMouse() {
	
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

bool Board::positionIsOnBoard(BoardPosition p) {
	if ( (p.x<0) || (p.x>=getRows()) ) {
		return false;
	}
	if ( (p.y<0) || (p.y>=getCols()) ) {
		return false;
	}
	return true;
}

bool Board::hasWallBottom(int x, int y, bool verifyDoorKey) { 
	if (positionIsOnBoard(getPositionFromXY(x,y))) { 
		if (verifyDoorKey && hasKey && doorKeyClosed && directionKey != "right") {
			if (verifyPositions(getPositionFromXY(x,y), doorKeyBottom->getPosition())) {
				return true;
			}
		}
		return walls[(y*MAX_TILES_INLINE)+x].wallBottom; 
	} else { 
		return false; 
	} 
}

bool Board::hasWallRight(int x, int y, bool verifyDoorKey) { 
	if (positionIsOnBoard(getPositionFromXY(x,y))) { 
		if (verifyDoorKey && hasKey && doorKeyClosed && directionKey == "right") {
			if (verifyPositions(getPositionFromXY(x,y), doorKeyRight->getPosition())) {
				return true;
			}
		}
		return walls[(y*MAX_TILES_INLINE)+x].wallRight; 
	} else { 
		return false; 
	} 
}

bool Board::hasWallBetweenCells(BoardPosition p1, BoardPosition p2, bool verifyDoorKey) {
     if (p1.x+1 == p2.x) { // right
         return hasWallRight(p1.x, p1.y, verifyDoorKey);
     } else if (p1.x-1 == p2.x) { // left
         return hasWallRight(p2.x, p2.y, verifyDoorKey);
     } else if (p1.y+1 == p2.y) { // down
         return hasWallBottom(p1.x, p1.y, verifyDoorKey);
     } else if (p1.y-1 == p2.y) { // up
         return hasWallBottom(p2.x, p2.y, verifyDoorKey);
     }
     return false;
}

void Board::load() {
	
	multiLanguage = false;
     
	wallsOfLevel = false;
	terrainOfLevel = false;
	wallScennaryOfLevel = false;
	musicOfLevel = false;
	pavementOfLevel = false;
	floorOfLevel = false;
	
	town.name="";
	town.province="";
	town.nickname="";
	
	infoTray.title="";
	infoTray.text="";
	
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
	
	trap = new AnimatedElement();	
    trap->setAlign(ALIGN_CENTER);
	trap->addRangeFramesFromData("board/trap", "png", 0, 3);
    trap->setGroup(this);
	
	Animation atrap;
	atrap.setName("move");
	atrap.setCyclesBetweenFrames(20);
	atrap.addRangeFrame(0, 3, 1);
	atrap.addFrame(2);
	atrap.addFrame(1);
	trap->addAnimation(atrap);
	
	particlesTrap = new ElementIsometric();	
	particlesTrap->setHeightElement(40);
	particlesTrap->setAlign(ALIGN_CENTER);

	particlesTrap->addRangeFramesFromData("objects/trap_particles", "png", 0, 3);
	
	particlesTrap->setGroup(this);
	
	Animation p_trap;
	p_trap.setName("move");
	p_trap.setCyclesBetweenFrames(8);
	p_trap.addFrame(0);
	p_trap.addFrame(1);
	p_trap.addFrame(2);
	p_trap.addFrame(3);
	p_trap.addFrame(1);
	p_trap.addFrame(2);
	p_trap.addFrame(1);
	particlesTrap->addAnimation(p_trap);
		
	TypeObjectsScenary::GetInstance()->load();
	
	explosionEnemies = new ParticlesSystem(100);
	explosionEnemies->setFrame((string)DATA_DIR + "/particles/smoke.png");
	explosionEnemies->setMlLife(500, 700);
	
	blackHole0 = new ElementIsometric();	
	blackHole0->setHeightElement(2);
	blackHole0->setAlign(ALIGN_CENTER);

	blackHole0->addRangeFramesFromData("objects/blackhole", "png", 0, 3);
	
	blackHole1 = new ElementIsometric();	
	blackHole1->setHeightElement(2);
	blackHole1->setAlign(ALIGN_CENTER);
	
	blackHole1->addRangeFramesFromData("objects/blackhole", "png", 0, 3);
		
	Animation bh_a;
	bh_a.setName("move");
	bh_a.addRangeFrame(0, 3, 1);
	blackHole0->addAnimation(bh_a);
	blackHole1->addAnimation(bh_a);
	
	blackHole0->setGroup(this);
	blackHole1->setGroup(this);
	
	particlesBlackHole0 = new ElementIsometric();	
	particlesBlackHole0->setHeightElement(40);
	particlesBlackHole0->setAlign(ALIGN_CENTER);

	particlesBlackHole0->addRangeFramesFromData("objects/blackhole_particles", "png", 0, 3);
	
	particlesBlackHole1 = new ElementIsometric();	
	particlesBlackHole1->setHeightElement(50);
	particlesBlackHole1->setAlign(ALIGN_CENTER);

	particlesBlackHole1->addRangeFramesFromData("objects/blackhole_particles", "png", 0, 3);
	
	Animation pbh_a;
	pbh_a.setName("move");
	pbh_a.setCyclesBetweenFrames(8);
	pbh_a.addFrame(0);
	pbh_a.addFrame(1);
	pbh_a.addFrame(2);
	pbh_a.addFrame(3);
	pbh_a.addFrame(1);
	pbh_a.addFrame(2);
	pbh_a.addFrame(1);
	particlesBlackHole0->addAnimation(pbh_a);
	
	Animation pbh_a1;
	pbh_a1.setName("move");
	pbh_a1.setCyclesBetweenFrames(7);
	pbh_a1.addFrame(0);
	pbh_a1.addFrame(1);
	pbh_a1.addFrame(2);
	pbh_a1.addFrame(3);
	pbh_a1.addFrame(2);
	pbh_a1.addFrame(1);
	particlesBlackHole1->addAnimation(pbh_a);
	
	particlesBlackHole0->setGroup(this);
	particlesBlackHole1->setGroup(this);
	
	doorKeyBottom = new ElementIsometric();	
	doorKeyBottom->addRangeFramesFromData("objects/grate", "png", 0, 4);
	doorKeyBottom->setAlign(ALIGN_RIGHT);
	doorKeyBottom->setHeightElement(60);
	doorKeyBottom->setDisplacementX(8);
	doorKeyBottom->setGroup(this);
	
	doorKeyRight = new ElementIsometric();	
	doorKeyRight->setFlip(true);
	doorKeyRight->addRangeFramesFromData("objects/grate", "png", 0, 4);
	doorKeyRight->setHeightElement(60);
	doorKeyRight->setDisplacementX(-8);
	doorKeyRight->setGroup(this);
	
	Animation dk_a;
	dk_a.setName("open");
	dk_a.addRangeFrame(0, 4, 1);
	doorKeyRight->addAnimation(dk_a);
	doorKeyBottom->addAnimation(dk_a);
	
	Animation dk_b;
	dk_b.setName("close");
	dk_b.addRangeFrame(4, 0, -1);
	doorKeyRight->addAnimation(dk_b);
	doorKeyBottom->addAnimation(dk_b);
	
	Animation dk_c;
	dk_c.setName("opened");
	dk_c.addFrame(4);
	doorKeyRight->addAnimation(dk_c);
	doorKeyBottom->addAnimation(dk_c);
	
	Animation dk_d;
	dk_d.setName("closed");
	dk_d.addFrame(0);
	doorKeyRight->addAnimation(dk_d);
	doorKeyBottom->addAnimation(dk_d);
	
	doorKeyRight->setAnimation("closed");
	doorKeyBottom->setAnimation("closed");
	
	key = new ElementIsometric();	
	key->setHeightElement(20);
	key->setAlign(ALIGN_CENTER);
	
	key->addFrameFileFromData("/objects/key.png");
	
	key->setGroup(this);
	
	tray = new ElementIsometric();	
	tray->setForceRotateCenter(true);
	tray->setHeightElement(20);
	tray->setAlign(ALIGN_CENTER);
	
	tray->addFrameFileFromData("/objects/tray.png");
	
	tray->setGroup(this);
	
	scenary = new Scenary();
	scenary->setAlpha(0);
	
	door = new Door();
	door->setGroup(this);
	
	wallBottom = new ElementIsometric();
	wallBottom->addFrameFileFromData("/board/wall_0_h.png");
	wallBottom->setAlign(ALIGN_RIGHT);
	wallBottom->setHeightElement(25);
	wallBottom->setDisplacementX(10);
	wallBottom->setGroup(this);
	
	wallRight = new ElementIsometric();
	wallRight->addFrameFileFromData("/board/wall_0_v.png");
	wallRight->setHeightElement(25);
	wallRight->setDisplacementX(-10);
	wallRight->setGroup(this);
			
	floorOn = new ElementIsometric();	
	floorOn->setHeightElement(0);
	floorOn->setForcePosition(0,0);
	floorOn->setAlign(ALIGN_CENTER);
	floorOn->addFrameFileFromData("/editgame/floor_on.png");
	floorOn->setGroup(this);
			
	// arrow
	
	arrow = new ElementIsometric();
	arrow->addFrameFileFromData("/board/circle.png");
	arrow->addFrameFileFromData("/board/arrow_l.png");
	arrow->addFrameFileFromData("/board/arrow_u.png");
	arrow->addFrameFileFromData("/board/arrow_d.png");
	arrow->addFrameFileFromData("/board/arrow_r.png");
		
	Animation ar_a;
	ar_a.setName("center");
	ar_a.addFrame(0);
	arrow->addAnimation(ar_a);
	Animation ar_b;
	ar_b.setName("left");
	ar_b.addFrame(1);
	arrow->addAnimation(ar_b);
	Animation ar_c;
	ar_c.setName("up");
	ar_c.addFrame(2);
	arrow->addAnimation(ar_c);
	Animation ar_d;
	ar_d.setName("down");
	ar_d.addFrame(3);
	arrow->addAnimation(ar_d);
	Animation ar_e;
	ar_e.setName("right");
	ar_e.addFrame(4);
	arrow->addAnimation(ar_e);
	
	arrow->setAlign(ALIGN_CENTER);
	arrow->setHeightElement(-5);
	arrow->setGroup(this);
	
	// objects and people
	
	nimuh = new Player();
	nimuh->setForceRotateCenter(true);
	nimuh->setHeightElement(120);
	nimuh->setAlign(ALIGN_CENTER);
	
	nimuh->addRangeFramesFromData("nimuh/nimuh", "png", 0, 27);
	
	nimuh->addRangeFramesFromData("nimuh/jail", "png", 0, 3);
	
	nimuh->addRangeFramesFromData("nimuh/clean0", "png", 0, 5);
	nimuh->addRangeFramesFromData("nimuh/clean1", "png", 0, 1);
	
	nimuh->addRangeFramesFromData("nimuh/greeting", "png", 0, 4);
	
	nimuh->addRangeFramesFromData("nimuh/scratch0", "png", 0, 1);
	nimuh->addRangeFramesFromData("nimuh/scratch1", "png", 0, 2);
	
	Animation jail;
	jail.setName("jail");
	jail.addRangeFrame(28, 31, 1);
	nimuh->addAnimation(jail);
	
	Animation clean0;
	clean0.setCyclesBetweenFrames(8);
	clean0.setName("clean0");
	clean0.addRangeFrame(32, 37, 1);
	nimuh->addAnimation(clean0);
	
	Animation cleanremove;
	cleanremove.setCyclesBetweenFrames(8);
	cleanremove.setName("cleanremove");
	cleanremove.addRangeFrame(37, 32, -1);
	nimuh->addAnimation(cleanremove);
	
	Animation clean1;
	clean1.setCyclesBetweenFrames(15);
	clean1.setName("clean1");
	clean1.addRangeFrame(38, 39, 1);
	nimuh->addAnimation(clean1);
	
	Animation greeting;
	greeting.setName("greeting");
	greeting.addRangeFrame(40, 44, 1);
	nimuh->addAnimation(greeting);
	
	Animation greetingremove;
	greetingremove.setName("greetingremove");
	greetingremove.addRangeFrame(44, 40, -1);
	nimuh->addAnimation(greetingremove);
	
	Animation scratch0;
	scratch0.setName("scratch0");
	scratch0.addRangeFrame(45, 46, 1);
	nimuh->addAnimation(scratch0);
	
	Animation scratchremove;
	scratchremove.setName("scratchremove");
	scratchremove.addRangeFrame(46, 45, -1);
	nimuh->addAnimation(scratchremove);
	
	Animation scratch1;
	scratch1.setName("scratch1");
	scratch1.addRangeFrame(47, 49, 1);
	nimuh->addAnimation(scratch1);
	
	enemy1 = new Enemy();	
	enemy1->setHeightElement(110);
	enemy1->setAlign(ALIGN_CENTER);
	
	enemy1->addRangeFramesFromData("enemy1/enemy1", "png", 0, 27);
	
	enemy1->addRangeFramesFromData("enemy1/eating", "png", 0, 3);
	
	enemy1->addRangeFramesFromData("enemy1/crying", "png", 0, 2);
	
	enemy1->addRangeFramesFromData("enemy1/impatient", "png", 0, 3);
	
	enemy1->addRangeFramesFromData("enemy1/proud0", "png", 0, 3);
	enemy1->addRangeFramesFromData("enemy1/proud1", "png", 0, 5);
	
	Animation e1_impatient;
	e1_impatient.setName("impatient");
	e1_impatient.addRangeFrame(35, 38, 1);
	enemy1->addAnimation(e1_impatient);
	
	Animation e1_proud0;
	e1_proud0.setName("proud0");
	e1_proud0.addRangeFrame(39, 42, 1);
	enemy1->addAnimation(e1_proud0);
	
	Animation e1_proudremove;
	e1_proudremove.setName("proudremove");
	e1_proudremove.addRangeFrame(42, 39, -1);
	enemy1->addAnimation(e1_proudremove);
	
	Animation e1_proud1;
	e1_proud1.setName("proud1");
	e1_proud1.addRangeFrame(43, 48, 1);
	enemy1->addAnimation(e1_proud1);
		
	enemy2 = new Enemy();	
	enemy2->setFirstMovementHorizontal(false);
	enemy2->setHeightElement(100);
	enemy2->setAlign(ALIGN_CENTER);
	
	enemy2->addRangeFramesFromData("enemy2/enemy2", "png", 0, 27);
	
	enemy2->addRangeFramesFromData("enemy2/eating", "png", 0, 3);
	
	enemy2->addRangeFramesFromData("enemy2/crying", "png", 0, 2);
	
	enemy2->addRangeFramesFromData("enemy2/cazzo0", "png", 0, 1);
	enemy2->addRangeFramesFromData("enemy2/cazzo1", "png", 0, 2);
	
	enemy2->addRangeFramesFromData("enemy2/peeing", "png", 0, 12);
	
	Animation eating;
	eating.setCyclesBetweenFrames(15);
	eating.setName("eating");
	eating.addRangeFrame(28, 31, 1);
	enemy1->addAnimation(eating);
	enemy2->addAnimation(eating);
	
	Animation crying;
	crying.setCyclesBetweenFrames(15);
	crying.setName("crying");
	crying.addRangeFrame(32, 34, 1);
	crying.addFrame(33);
	enemy1->addAnimation(crying);
	enemy2->addAnimation(crying);
	
	Animation e2_cazzo0;
	e2_cazzo0.setCyclesBetweenFrames(6);
	e2_cazzo0.setName("cazzo0");
	e2_cazzo0.addRangeFrame(35, 36, 1);
	enemy2->addAnimation(e2_cazzo0);
	
	Animation e2_cazzoremove;
	e2_cazzoremove.setCyclesBetweenFrames(6);
	e2_cazzoremove.setName("cazzoremove");
	e2_cazzoremove.addRangeFrame(36, 35, -1);
	enemy2->addAnimation(e2_cazzoremove);
	
	Animation e2_cazzo1;
	e2_cazzo1.setCyclesBetweenFrames(6);
	e2_cazzo1.setName("cazzo1");
	e2_cazzo1.addRangeFrame(37, 39, 1);
	enemy2->addAnimation(e2_cazzo1);
	
	Animation e2_peeing;
	e2_peeing.setCyclesBetweenFrames(8);
	e2_peeing.setName("peeing");
	e2_peeing.addRangeFrame(40, 43, 1);
	e2_peeing.addRangeFrame(42, 43, 1);
	e2_peeing.addRangeFrame(42, 43, 1);
	e2_peeing.addRangeFrame(42, 43, 1);
	e2_peeing.addRangeFrame(44, 45, 1);
	e2_peeing.addFrame(48);
	e2_peeing.addRangeFrame(46, 47, 1);
	e2_peeing.addRangeFrame(46, 47, 1);
	e2_peeing.addRangeFrame(46, 47, 1);
	e2_peeing.addRangeFrame(46, 47, 1);
	e2_peeing.addRangeFrame(46, 47, 1);
	e2_peeing.addFrame(49);
	e2_peeing.addRangeFrame(48, 52, 1);
	enemy2->addAnimation(e2_peeing);
	
	Animation a;
	a.setName("stop_right");
	a.addFrame(12);
	nimuh->addAnimation(a);
	enemy1->addAnimation(a);
	enemy2->addAnimation(a);
	
	Animation b;
	b.setName("stop_left");
	b.addFrame(6);
	nimuh->addAnimation(b);
	enemy1->addAnimation(b);
	enemy2->addAnimation(b);
	
	Animation c;
	c.setName("stop_up");
	c.addFrame(0);
	nimuh->addAnimation(c);
	enemy1->addAnimation(c);
	enemy2->addAnimation(c);
	
	Animation d;
	d.setName("stop_down");
	d.addFrame(18);
	nimuh->addAnimation(d);
	enemy1->addAnimation(d);
	enemy2->addAnimation(d);
		
	Animation e;
	e.setName("walk_right");
	e.addRangeFrame(12, 17, 1);
	nimuh->addAnimation(e);
	enemy1->addAnimation(e);
	enemy2->addAnimation(e);
	
	Animation f;
	f.setName("walk_left");
	f.addRangeFrame(6, 11, 1);
	nimuh->addAnimation(f);
	enemy1->addAnimation(f);
	enemy2->addAnimation(f);
	
	Animation g;
	g.setName("walk_up");
	g.addRangeFrame(0, 5, 1);
	nimuh->addAnimation(g);
	enemy1->addAnimation(g);
	enemy2->addAnimation(g);
	
	Animation h;
	h.setName("walk_down");
	h.addRangeFrame(18, 23, 1);
	nimuh->addAnimation(h);
	enemy1->addAnimation(h);
	enemy2->addAnimation(h);
	
	Animation k;
	k.setName("captured_up");
	k.addFrame(24);
	nimuh->addAnimation(k);
	enemy1->addAnimation(k);
	enemy2->addAnimation(k);
	
	Animation m;
	m.setName("captured_left");
	m.addFrame(25);
	nimuh->addAnimation(m);
	enemy1->addAnimation(m);
	enemy2->addAnimation(m);
	
	Animation n;
	n.setName("captured_right");
	n.addFrame(26);
	nimuh->addAnimation(n);
	enemy1->addAnimation(n);
	enemy2->addAnimation(n);
	
	Animation o;
	o.setName("captured_down");
	o.addFrame(27);
	nimuh->addAnimation(o);
	enemy1->addAnimation(o);
	enemy2->addAnimation(o);
	
	nimuh->setDirection(TILE_RIGHT);
	nimuh->setGroup(this);
	
	enemy1->setDirection(TILE_RIGHT);
	enemy1->setGroup(this);
	
	enemy2->setDirection(TILE_RIGHT);
	enemy2->setGroup(this);
	
	enemy3 = new Enemy();	
	enemy3->setHeightElement(110);
	enemy3->setAlign(ALIGN_CENTER);
	
	enemy3->addRangeFramesFromData("enemy3/enemy3", "png", 0, 11);
	
	enemy3->addRangeFramesFromData("enemy3/eating", "png", 0, 3);
	
	enemy3->addRangeFramesFromData("enemy3/crying", "png", 0, 3);
	
	Animation eating3;
	eating3.setCyclesBetweenFrames(15);
	eating3.setName("eating");
	eating3.addRangeFrame(12, 15, 1);
	enemy3->addAnimation(eating3);
	
	Animation crying3;
	crying3.setCyclesBetweenFrames(15);
	crying3.setName("crying");
	crying3.addRangeFrame(16, 19, 1);
	enemy3->addAnimation(crying3);
	
	Animation a3;
	a3.setName("stop_right");
	a3.addFrame(4);
	enemy3->addAnimation(a3);
	
	Animation b3;
	b3.setName("stop_left");
	b3.addFrame(2);
	enemy3->addAnimation(b3);
	
	Animation c3;
	c3.setName("stop_up");
	c3.addFrame(0);
	enemy2->addAnimation(c3);
	
	Animation d3;
	d3.setName("stop_down");
	d3.addFrame(6);
	enemy3->addAnimation(d3);
		
	Animation e3;
	e3.setName("walk_right");
	e3.addRangeFrame(4, 5, 1);
	enemy3->addAnimation(e3);
	
	Animation f3;
	f3.setName("walk_left");
	f3.addRangeFrame(2, 3, 1);
	enemy3->addAnimation(f3);
	
	Animation g3;
	g3.setName("walk_up");
	g3.addRangeFrame(0, 1, 1);
	enemy3->addAnimation(g3);
	
	Animation h3;
	h3.setName("walk_down");
	h3.addRangeFrame(6, 7, 1);
	enemy3->addAnimation(h3);
	
	Animation k3;
	k3.setName("captured_up");
	k3.addFrame(8);
	enemy3->addAnimation(k3);
	
	Animation m3;
	m3.setName("captured_left");
	m3.addFrame(9);
	enemy3->addAnimation(m3);
	
	Animation n3;
	n3.setName("captured_right");
	n3.addFrame(10);
	enemy3->addAnimation(n3);
	
	Animation o3;
	o3.setName("captured_down");
	o3.addFrame(11);
	enemy3->addAnimation(o3);
	
	enemy3->setDirection(TILE_RIGHT);
	enemy3->setGroup(this);
	
	turn = TURN_PLAYER;
	
}

void Board::changeBoardWithCurrentHistory() {
	
	int index = currentHistory-1;
	
	nimuh->setForcePosition(history[index].nimuh);
	enemy1->setForcePosition(history[index].enemy1);
	enemy2->setForcePosition(history[index].enemy2);
	enemy3->setForcePosition(history[index].enemy3);
	
	if (history[index].hasEnemy1 != hasEnemy1) hasEnemy1 = !hasEnemy1;
	if (history[index].hasEnemy2 != hasEnemy2) hasEnemy2 = !hasEnemy2;
	if (history[index].hasEnemy3 != hasEnemy3) hasEnemy3 = !hasEnemy3;
		
	if (canChangeInHistory_Tray) {

		if (history[index].hasTray != hasTray) {
			hasTray = !hasTray;
			
			int indexEnemy = 0;
			if (hasTray) {
				indexEnemy = index+1;
			} else {
				indexEnemy = index;
			}
			
			if (indexEnemy < (int)history.size()) {
				if (history[indexEnemy].enemy!=NULL) {
					if (hasTray) {
						history[indexEnemy].enemy->setStopped(false);
						history[indexEnemy].enemy->setForceAnimation("stop_right");
						Sounds::GetInstance()->getSound("eating")->stop();
					} else {
						history[indexEnemy].enemy->setStopped(true);
						history[indexEnemy].enemy->setForceAnimation("eating");
						Sounds::GetInstance()->getSound("eating")->play(5, -1);
					}
				}
			}
		}
		
	}
	
	if (canChangeInHistory_Enemy2) {
					
		if (history[index].hasEnemy2 != hasEnemy2) {
			
			hasEnemy2 = !hasEnemy2;
						
		}
				
	}
	
	if (canChangeInHistory_Enemy3) {
					
		if (history[index].hasEnemy3 != hasEnemy3) {
			
			hasEnemy3 = !hasEnemy3;
			
		}

	}
	
	if (canChangeInHistory_Key) {
					
		doorKeyClosed = history[index].doorKeyClosed;
		
		if (doorKeyClosed) {
			doorKeyRight->setForceAnimation("closed");
			doorKeyBottom->setForceAnimation("closed");
		} else {
			doorKeyRight->setForceAnimation("opened");
			doorKeyBottom->setForceAnimation("opened");
		}

	}
	
}

void Board::nextHistory() {
	beginAnimationWaiting();
	if (currentHistory<totalHistory) {
		currentHistory++;
		changeBoardWithCurrentHistory();
	}
}


void Board::previousHistory() {
	beginAnimationWaiting();
	if (currentHistory>1) {
		currentHistory--;
		changeBoardWithCurrentHistory();
	}
}

void Board::addStateHistory() {
	if (currentHistory<totalHistory) {
		for (int i=(int)history.size()-1; i>=0; i--) {
			if (history[i].number>currentHistory) {
				history.erase(history.begin()+i);
			}
		}
		currentHistory++;
		totalHistory = currentHistory;
	} else {
		currentHistory++;
		totalHistory++;
	}
	addHistory();
}

void Board::addHistory() {
	History h;
	h.number = currentHistory;
	h.nimuh = nimuh->getPosition();
	h.enemy1 = enemy1->getPosition();
	h.enemy2 = enemy2->getPosition();
	h.enemy3 = enemy3->getPosition();
	
	h.enemy = NULL;
	
	if (canChangeInHistory_Tray) {
		h.hasTray = hasTray;
		if ( (enemy1->getStopped()) || (enemy2->getStopped()) || (enemy3->getStopped()) ) {
			if ((int)history.size()>0) {
				if ( history[(int)history.size()-1].hasTray ) {
					h.hasTray = false;
					if (enemy1->getStopped()) h.enemy = enemy1;
					if (enemy2->getStopped()) h.enemy = enemy2;
					if (enemy3->getStopped()) h.enemy = enemy3;
				}				
			}
		}
	}
	
	if (canChangeInHistory_Enemy2) {
		h.hasEnemy2 = hasEnemy2;
		if ((int)history.size()>0) {
			if ( history[(int)history.size()-1].hasEnemy2 != hasEnemy2 ) {
				h.enemy = enemy2;
			}				
		}
	}
	
	if (canChangeInHistory_Enemy3) {
		h.hasEnemy3 = hasEnemy3;
		if ((int)history.size()>0) {
			if ( history[(int)history.size()-1].hasEnemy3 != hasEnemy3 ) {
				h.enemy = enemy3;
			}				
		}
	}
	
	if (canChangeInHistory_Key) {
		h.doorKeyClosed = doorKeyClosed;
	}
	
	h.hasEnemy1 = hasEnemy1;
	h.hasEnemy2 = hasEnemy2;
	h.hasEnemy3 = hasEnemy3;
	
	h.doorKeyClosed = doorKeyClosed;
	history.push_back(h);
}

bool Board::verifyPositions(BoardPosition p1, BoardPosition p2) {
     if ( (p1.x == p2.x) && (p1.y == p2.y) ) {
          return true;
     } else {
          return false;       
     }
}

int Board::referencePositions(BoardPosition p1, BoardPosition p2) {
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

void Board::verifyAnimationWaiting() {
     if ( (!isAnimationWaiting) && (turn == TURN_PLAYER) ) {
         if (Chronometer::GetInstance()->getTime("animationwaiting") > 15000) {                                                      
			  Chronometer::GetInstance()->setTime("animationwaiting");
              isAnimationWaiting = true;
              bool hasPersonage = false;
              while (!hasPersonage) {
                  typeAnimationWaiting = rand()%7;
                  switch (typeAnimationWaiting) {
                       case 0:
                       case 1:
                       case 2:
                            hasPersonage = true;
                       break;
                       case 3:
                       case 4:
                            if ( (hasEnemy1) && (!enemy1->getStopped()) ) hasPersonage = true;
                       break;
                       case 5:
                       case 6:
                            if ( (hasEnemy2) && (!enemy2->getStopped()) )  hasPersonage = true;
                       break;
                  }
              }
              switch (typeAnimationWaiting) {
                     case 0:
                          nimuh->setForceAnimation("clean0");
                          nimuh->setAnimation("clean1");
					 	  Sounds::GetInstance()->getSound("nimuh_clean")->play(12, 0);
                     break;
                     case 1:
                          nimuh->setForceAnimation("greeting", 1);
                     break;
                     case 2:
                          nimuh->setForceAnimation("scratch0");
                          nimuh->setAnimation("scratch1");
                          Sounds::GetInstance()->getSound("nimuh_scratch")->play(12, 0);
                     break;
                     case 3:
                          enemy1->setForceAnimation("impatient");
                          Sounds::GetInstance()->getSound("enemy1_impatient")->play(12, 0);
                     break;
                     case 4:
                          enemy1->setForceAnimation("proud0");
                          enemy1->setAnimation("proud1");
					 	  Sounds::GetInstance()->getSound("enemy1_proud")->play(12, 0);
                     break;
                     case 5:
                          enemy2->setForceAnimation("cazzo0");
                          enemy2->setAnimation("cazzo1");
					 	  Sounds::GetInstance()->getSound("enemy2_cazzo")->play(12, 0);
                     break;
                     case 6:
                          enemy2->setForceAnimation("peeing", 1);
					 	  Sounds::GetInstance()->getSound("enemy2_peeing")->play(12, 0);
                     break;
              }
         }
     }
}

void Board::verifyStopAnimationWaiting() {
     if (isAnimationWaiting) {
         if (Chronometer::GetInstance()->getTime("animationwaiting") > 4000) {                                                      
			  beginAnimationWaiting();
              isAnimationWaiting = false;
              switch (typeAnimationWaiting) {
                     case 0:
                          nimuh->setForceAnimation("cleanremove");
					 	  nimuh->setAnimation("stop_right");
                     break;
                     case 1:
                          nimuh->setForceAnimation("greetingremove");
					 	  nimuh->setAnimation("stop_right");
                     break;
                     case 2:
                          nimuh->setForceAnimation("scratchremove");
                          nimuh->setAnimation("stop_right");
                     break;
                     case 3:
                          enemy1->setForceAnimation("stop_right");
                     break;
                     case 4:
                          enemy1->setForceAnimation("proudremove");
                          enemy1->setAnimation("stop_right");
                     break;
                     case 5:
                          enemy2->setForceAnimation("cazzoremove");
                          enemy2->setAnimation("stop_right");
                     break;
                     case 6:
                          enemy2->setAnimation("stop_right");
                     break;
              }
         }
     }
}

void Board::verifyWinPlayer() {

	if ( verifyPositions(nimuh->getPosition(), door->getPosition()) ) {
		nimuh->setScaleW(0,1500);
		nimuh->setMovementNormalY (nimuh->getYWithoutDisplacementByGroups()+((nimuh->getHeight()/2)*nimuh->getCurrentScaleY()), 1500);
		nimuh->setRotationNormal(1080,1500);
		nimuh->setFadeOut(1500);
		Sounds::GetInstance()->getSound("out_door")->play(6, 0);
		Sounds::GetInstance()->getSound("crying")->play(7, 0);
		Chronometer::GetInstance()->setTime("winning");
		scenegame->setStatusScene(SCENE_GAME_WINNING);
		if (hasEnemy1) enemy1->setForceAnimation("crying");
		if (hasEnemy2) enemy2->setForceAnimation("crying");
		if (hasEnemy3) enemy3->setForceAnimation("crying");
	}	

}

void Board::createExplosion(Enemy *e) {
	explosionEnemies->setPositions(posX + Plot::GetInstance()->getX(e->getPosition().x, e->getPosition().y) - ((int)floor0->getWidth()/2) + paddingExplosion, posY+Plot::GetInstance()->getY(e->getPosition().x,e->getPosition().y)-e->getHeightElement() + paddingExplosion, e->getWidth() - paddingExplosion, e->getHeight() - paddingExplosion);
	explosionEnemies->start();  
	Sounds::GetInstance()->getSound("colision")->play(4, 0);
	if (e->getAnimation()->getName()=="eating") {
		Sounds::GetInstance()->getSound("eating")->stop();
	}
	inExplosion = true;   
}

void Board::verifyStartToEat(Enemy *e) {
	if (hasTray) {
		if ( verifyPositions(e->getPosition(), tray->getPosition()) ) {	
			e->setStopped(true);
			e->setForceAnimation("eating");
			Sounds::GetInstance()->getSound("open_tray")->play(9, 0);
			tray->setScaleGL(3.5, 1500);
			tray->setRotationNormal(360, 1500);
			tray->setMovementNormalY(tray->getYWithoutDisplacementByGroups()-(tray->getHeight()*2), 1500);
			Chronometer::GetInstance()->setTime("starttray");
			scenegame->setStatusScene(SCENE_GAME_STARTTRAY);
		}
	}
}

void Board::nextTurn() { 
	if (mlPause>0) return;
    if (inExplosion) return;
     
	if (turn < TURN2_ENEMY) { 
		turn++; 
	} else { 
		turn = 0; 
	}
    //printf("nextturn: %d\n", turn);
    
    if (turn == TURN_PLAYER) {
		addStateHistory();
		beginAnimationWaiting();
    }
    
 	if (turn == TURN_ENEMY3) {
       if (!hasEnemy3) {
          todoNextTurn = true;
       } else {
          if ( ( referencePositions(enemy3->getPosition(), nimuh->getPosition()) != TILE_OTHER ) 
				&& ( !hasWallBetweenCells(enemy3->getPosition(), nimuh->getPosition()) ) && (!enemy3->getStopped()) ) { // atrapado
			if (referencePositions(nimuh->getPosition(), enemy3->getPosition()) == TILE_RIGHT) {
				nimuh->setForceAnimation("captured_right");
			} else if (referencePositions(nimuh->getPosition(), enemy3->getPosition()) == TILE_LEFT) {
				nimuh->setForceAnimation("captured_left");
			} else if (referencePositions(nimuh->getPosition(), enemy3->getPosition()) == TILE_UP) {
				nimuh->setForceAnimation("captured_up");
			} else if (referencePositions(nimuh->getPosition(), enemy3->getPosition()) == TILE_DOWN) {
				nimuh->setForceAnimation("captured_down");
			}
			if (referencePositions(enemy3->getPosition(), nimuh->getPosition()) == TILE_RIGHT) {
				enemy3->setForceAnimation("captured_right");
			} else if (referencePositions(enemy3->getPosition(), nimuh->getPosition()) == TILE_LEFT) {
				enemy3->setForceAnimation("captured_left");
			} else if (referencePositions(enemy3->getPosition(), nimuh->getPosition()) == TILE_UP) {
				enemy3->setForceAnimation("captured_up");
			} else if (referencePositions(enemy3->getPosition(), nimuh->getPosition()) == TILE_DOWN) {
				enemy3->setForceAnimation("captured_down");
			}
			enemy1->stop();
			if (hasEnemy2) enemy2->stop();
			Sounds::GetInstance()->getSound("gun")->play(12, 0);
			Chronometer::GetInstance()->setTime("captured");
			scenegame->setStatusScene(SCENE_GAME_CAPTURED);
		  } else {
			if (!enemy3->move()) {
				todoNextTurn = true;
			} else {
				Sounds::GetInstance()->getSound("steps_enemy3")->play(2, 0);
			}
          }
       }
    }
	
	if ( (turn != TURN_PLAYER) && (turn != TURN_ENEMY3) ) { 
		if ( (hasEnemy1) && ( referencePositions(enemy1->getPosition(), nimuh->getPosition()) != TILE_OTHER ) 
				&& ( !hasWallBetweenCells(enemy1->getPosition(), nimuh->getPosition()) ) && (!enemy1->getStopped()) ) { // atrapado
			if (referencePositions(nimuh->getPosition(), enemy1->getPosition()) == TILE_RIGHT) {
				nimuh->setForceAnimation("captured_right");
			} else if (referencePositions(nimuh->getPosition(), enemy1->getPosition()) == TILE_LEFT) {
				nimuh->setForceAnimation("captured_left");
			} else if (referencePositions(nimuh->getPosition(), enemy1->getPosition()) == TILE_UP) {
				nimuh->setForceAnimation("captured_up");
			} else if (referencePositions(nimuh->getPosition(), enemy1->getPosition()) == TILE_DOWN) {
				nimuh->setForceAnimation("captured_down");
			}
			if (referencePositions(enemy1->getPosition(), nimuh->getPosition()) == TILE_RIGHT) {
				enemy1->setForceAnimation("captured_right");
			} else if (referencePositions(enemy1->getPosition(), nimuh->getPosition()) == TILE_LEFT) {
				enemy1->setForceAnimation("captured_left");
			} else if (referencePositions(enemy1->getPosition(), nimuh->getPosition()) == TILE_UP) {
				enemy1->setForceAnimation("captured_up");
			} else if (referencePositions(enemy1->getPosition(), nimuh->getPosition()) == TILE_DOWN) {
				enemy1->setForceAnimation("captured_down");
			}
			if (hasEnemy2) enemy2->stop();
			if (hasEnemy3) enemy3->stop();
			Sounds::GetInstance()->getSound("gun")->play(12, 0); 
			Chronometer::GetInstance()->setTime("captured");
			scenegame->setStatusScene(SCENE_GAME_CAPTURED);
		} else if ( (hasEnemy2) && ( referencePositions(enemy2->getPosition(), nimuh->getPosition()) != TILE_OTHER ) 
				&& ( !hasWallBetweenCells(enemy2->getPosition(), nimuh->getPosition()) ) && (!enemy2->getStopped()) ) { // atrapado
			if (referencePositions(nimuh->getPosition(), enemy2->getPosition()) == TILE_RIGHT) {
				nimuh->setForceAnimation("captured_right");
			} else if (referencePositions(nimuh->getPosition(), enemy2->getPosition()) == TILE_LEFT) {
				nimuh->setForceAnimation("captured_left");
			} else if (referencePositions(nimuh->getPosition(), enemy2->getPosition()) == TILE_UP) {
				nimuh->setForceAnimation("captured_up");
			} else if (referencePositions(nimuh->getPosition(), enemy2->getPosition()) == TILE_DOWN) {
				nimuh->setForceAnimation("captured_down");
			}
			if (referencePositions(enemy2->getPosition(), nimuh->getPosition()) == TILE_RIGHT) {
				enemy2->setForceAnimation("captured_right");
			} else if (referencePositions(enemy2->getPosition(), nimuh->getPosition()) == TILE_LEFT) {
				enemy2->setForceAnimation("captured_left");
			} else if (referencePositions(enemy2->getPosition(), nimuh->getPosition()) == TILE_UP) {
				enemy2->setForceAnimation("captured_up");
			} else if (referencePositions(enemy2->getPosition(), nimuh->getPosition()) == TILE_DOWN) {
				enemy2->setForceAnimation("captured_down");
			}
			enemy1->stop();
			if (hasEnemy3) enemy3->stop(); 
			Sounds::GetInstance()->getSound("gun")->play(12, 0);
			Chronometer::GetInstance()->setTime("captured");
			scenegame->setStatusScene(SCENE_GAME_CAPTURED);
		} else {
			if (hasEnemy1 && hasEnemy2) {
                catchedEnemy1 = !enemy1->move();    
                catchedEnemy2 = !enemy2->move();  
				if (!catchedEnemy1) Sounds::GetInstance()->getSound("steps_enemy1")->play(2, 0);
				if (!catchedEnemy2) Sounds::GetInstance()->getSound("steps_enemy2")->play(2, 0);
			} else if (hasEnemy1 && !hasEnemy2) {
    			if (!enemy1->move()) {
    				verifyWinPlayer();
    			    todoNextTurn = true;
    			} else {
					Sounds::GetInstance()->getSound("steps_enemy1")->play(2, 0);
				}
            } else if (!hasEnemy1 && hasEnemy2) {
    			if (!enemy2->move()) {
    				verifyWinPlayer();
    			    todoNextTurn = true;
    			} else {
					Sounds::GetInstance()->getSound("steps_enemy2")->play(2, 0);
				}
            }
		}
	} 
}

void Board::stopAnimations() {
	
	verifyAnimationWaiting();
	verifyStopAnimationWaiting();
	
	if (mlPause>0) {
		if (Chronometer::GetInstance()->getTime("pause-board") > mlPause) {
			mlPause = 0;
			todoNextTurn = true;
		} else {
			return;
		}
	}
	
    if (turn == TURN_PLAYER) { 
             
        if (teletransport) {
                           
            if (nimuh->getFadeOut()<=0) {
                 nimuh->setForcePosition(posTeletransport);
                 nimuh->setFadeIn(1000);   
                 pause(1500);
                 teletransport = false;                    
            }

        } else {
              
    		if (nimuh->getIsMovement()) {
    			if (nimuh->getNCyclesMovementNormal()/2 == nimuh->getCountCyclesMovementNormal()) {
    				nimuh->setNextBoardPositionInElement();
    			}
    		}
            if ( (!nimuh->getIsMovement()) && (nimuh->getIsMoving()) ) {
        		nimuh->stop();
        		teletransport = false;
        		if ( hasBlackHole0 && hasBlackHole1 ) {
                     if ( verifyPositions(nimuh->getPosition(), blackHole0->getPosition()) ) {
                          posTeletransport = blackHole1->getPosition();
                          teletransport = true;
						  Sounds::GetInstance()->getSound("teletransport")->play(3, 0);
                     } 
                     if ( verifyPositions(nimuh->getPosition(), blackHole1->getPosition()) ) {
                          posTeletransport = blackHole0->getPosition();
                          teletransport = true;
						  Sounds::GetInstance()->getSound("teletransport")->play(3, 0);
                     }           
                }
				
				if (hasKey) {
					if ( verifyPositions(nimuh->getPosition(), key->getPosition()) ) {
						swapDoorKey();
					}
				}
				                
                if (teletransport) {
                    nimuh->setFadeOut(1000);           
                }
                
                todoNextTurn = !teletransport;
				
				if (hasTrap) {
					if ( verifyPositions(nimuh->getPosition(), posTrap) ) {
                        Sounds::GetInstance()->getSound("jail")->play(12, 0);
						nimuh->setForceAnimation("jail", 1);
						Chronometer::GetInstance()->setTime("captured");
						scenegame->setStatusScene(SCENE_GAME_CAPTURED);
						todoNextTurn = false;
					}
				}
				
            }
                
        }
    }
    
    if ( (hasEnemy3) && (turn == TURN_ENEMY3) ) { 
		if (enemy3->getIsMovement()) {
			if (enemy3->getNCyclesMovementNormal()/2 == enemy3->getCountCyclesMovementNormal()) {
				enemy3->setNextBoardPositionInElement();
				if ( ( verifyPositions(enemy3->getPosition(), enemy2->getPosition()) ) 
                     || ( verifyPositions(enemy3->getPosition(), enemy1->getPosition()) ) ) {
					createExplosion(enemy3);
                }
			}
		}
    	if ( (!enemy3->getIsMovement()) && (enemy3->getIsMoving()) ) {
            enemy3->stop();
    		if (turn == TURN2_ENEMY) {
    			verifyWinPlayer();
    		}
			if (hasKey) {
				if ( verifyPositions(enemy3->getPosition(), key->getPosition()) ) {
					swapDoorKey();
				}
			}
			
			verifyStartToEat(enemy3);

    		todoNextTurn = true;
			// enemy3 is death??
			if ( verifyPositions(enemy3->getPosition(), enemy2->getPosition()) ) {
				hasEnemy3 = false;
			}
			if ( verifyPositions(enemy3->getPosition(), enemy1->getPosition()) ) {
				hasEnemy3 = false;
			}
            if (inExplosion) {
                todoNextTurn = false;    
            }
        }
    }
    
    if ( (turn != TURN_PLAYER) && (turn != TURN_ENEMY3) ) { 

        if (hasEnemy1 && hasEnemy2) {
			if (enemy2->getIsMovement()) {
				if (enemy2->getNCyclesMovementNormal()/2 == enemy2->getCountCyclesMovementNormal()) {
					enemy2->setNextBoardPositionInElement();
					BoardPosition pe1;
					if (enemy1->getIsMoving()) {
                         pe1 = enemy1->getNextBoardPositionInElement();
                    } else {
                         pe1 = enemy1->getPosition();
                    }
					if ( verifyPositions(enemy2->getPosition(), pe1) ) {
                        createExplosion(enemy2);  
                    }
                    if ( (hasEnemy3) && ( verifyPositions(enemy2->getPosition(), enemy3->getPosition()) ) ) {
                        createExplosion(enemy3);
                    }     
				}
			}
			if (enemy1->getIsMovement()) {
				if (enemy1->getNCyclesMovementNormal()/2 == enemy1->getCountCyclesMovementNormal()) {
					enemy1->setNextBoardPositionInElement();
					BoardPosition pe2;
					if (enemy2->getIsMoving()) {
                         pe2 = enemy2->getNextBoardPositionInElement();
                    } else {
                         pe2 = enemy2->getPosition();
                    }
					//printf("hola: %d %d - %d %d\n", enemy1->getPosition().x, enemy1->getPosition().y, pe2.x, pe2.y);
					if ( verifyPositions(enemy1->getPosition(), pe2) ) {
                        createExplosion(enemy2); 
                    }
                    if ( (hasEnemy3) && ( verifyPositions(enemy1->getPosition(), enemy3->getPosition()) ) ) {
                        createExplosion(enemy3);  
                    } 
				}
			}
            if (!catchedEnemy1 && !catchedEnemy2) {
            	if ( (!enemy2->getIsMovement()) && (enemy2->getIsMoving()) &&
                   (!enemy1->getIsMovement()) && (enemy1->getIsMoving()) ) {
            		enemy1->stop();
            		enemy2->stop();
        			if (hasKey) {
        				if ( verifyPositions(enemy1->getPosition(), key->getPosition()) ) {
        					swapDoorKey();
        				}
        			}
        			if (hasKey) {
        				if ( verifyPositions(enemy2->getPosition(), key->getPosition()) ) {
        					swapDoorKey();
        				}
        			}

            		if (turn == TURN2_ENEMY) {
            			verifyWinPlayer();
            		}
            		todoNextTurn = true;
					verifyStartToEat(enemy1);
					verifyStartToEat(enemy2);
                }
            }
            if (catchedEnemy1 && !catchedEnemy2) {
            	if ( (!enemy2->getIsMovement()) && (enemy2->getIsMoving()) ) {
            		enemy2->stop();
        			if (hasKey) {
        				if ( verifyPositions(enemy2->getPosition(), key->getPosition()) ) {
        					swapDoorKey();
        				}
        			}					
            		if (turn == TURN2_ENEMY) {
            			verifyWinPlayer();
            		}
            		todoNextTurn = true;
					verifyStartToEat(enemy2);
                }           
            }
            if (!catchedEnemy1 && catchedEnemy2) {
            	if ( (!enemy1->getIsMovement()) && (enemy1->getIsMoving()) ) {
            		enemy1->stop();
        			if (hasKey) {
        				if ( verifyPositions(enemy1->getPosition(), key->getPosition()) ) {
        					swapDoorKey();
        				}
        			}
            		if (turn == TURN2_ENEMY) {
            			verifyWinPlayer();
            		}
            		todoNextTurn = true;
					verifyStartToEat(enemy1);
                }           
            }
            if (catchedEnemy1 && catchedEnemy2) {
           		todoNextTurn = true;
        		if (turn == TURN2_ENEMY) {
        			verifyWinPlayer();
        		}
            }
			// enemy2 is death??
			if ( verifyPositions(enemy2->getPosition(), enemy1->getPosition()) && todoNextTurn ) {
				hasEnemy2 = false;
			}
			// enemy3 is death??
			if ( verifyPositions(enemy2->getPosition(), enemy3->getPosition()) && todoNextTurn ) {
				hasEnemy3 = false;
			}
			if ( verifyPositions(enemy1->getPosition(), enemy3->getPosition()) && todoNextTurn ) {
				hasEnemy3 = false;
			}
			
            if (inExplosion) {
                todoNextTurn = false;    
            }
        } if (hasEnemy1 && !hasEnemy2) {
			if (enemy1->getIsMovement()) {
				if (enemy1->getNCyclesMovementNormal()/2 == enemy1->getCountCyclesMovementNormal()) {
					enemy1->setNextBoardPositionInElement();
                    if ( (hasEnemy3) && ( verifyPositions(enemy1->getPosition(), enemy3->getPosition()) ) ) {
                        createExplosion(enemy3); 
                    } 
				}
			}
        	if ( (!enemy1->getIsMovement()) && (enemy1->getIsMoving()) ) {
        		enemy1->stop();
        		if (turn == TURN2_ENEMY) {
        			verifyWinPlayer();
        		}
    			if (hasKey) {
    				if ( verifyPositions(enemy1->getPosition(), key->getPosition()) ) {
    					swapDoorKey();
    				}
    			}
				verifyStartToEat(enemy1);
        		todoNextTurn = true;
            }
			
			// enemy3 is death??
			if ( verifyPositions(enemy1->getPosition(), enemy3->getPosition()) && todoNextTurn ) {
				hasEnemy3 = false;
			}
			
            if (inExplosion) {
                todoNextTurn = false;    
            }
			
        } if (!hasEnemy1 && hasEnemy2) {
			if (enemy2->getIsMovement()) {
				if (enemy2->getNCyclesMovementNormal()/2 == enemy2->getCountCyclesMovementNormal()) {
					enemy2->setNextBoardPositionInElement();
                    if ( (hasEnemy3) && ( verifyPositions(enemy2->getPosition(), enemy3->getPosition()) ) ) {
                        createExplosion(enemy3);
                    } 
				}
			}
        	if ( (!enemy2->getIsMovement()) && (enemy2->getIsMoving()) ) {
        		enemy2->stop();
        		if (turn == TURN2_ENEMY) {
        			verifyWinPlayer();
        		}
    			if (hasKey) {
    				if ( verifyPositions(enemy2->getPosition(), key->getPosition()) ) {
    					swapDoorKey();
    				}
    			}
				verifyStartToEat(enemy2);
        		todoNextTurn = true;
            }
			
			// enemy3 is death??
			if ( verifyPositions(enemy2->getPosition(), enemy3->getPosition()) && todoNextTurn ) {
				hasEnemy3 = false;
			}
			
            if (inExplosion) {
                todoNextTurn = false;    
            }
			
        }
        
   }
}

void Board::movePlayer(int pos) {
	if (turn == TURN_PLAYER) {
		if ( (!nimuh->getIsMovement()) && (!nimuh->getIsMoving()) && (mlPause<=0) && (!teletransport) ) {
			beginAnimationWaiting();
			BoardPosition place;
			if (pos==TILE_CENTER) {
				place.x = nimuh->getPosition().x;
				place.y = nimuh->getPosition().y;
			} else if (pos==TILE_LEFT) {
				place.x = nimuh->getPosition().x-1;
				place.y = nimuh->getPosition().y;
			} else if (pos==TILE_RIGHT) {
				place.x = nimuh->getPosition().x+1;
				place.y = nimuh->getPosition().y;
			} else if (pos==TILE_DOWN) {
				place.x = nimuh->getPosition().x;
				place.y = nimuh->getPosition().y+1;
			} else if (pos==TILE_UP) {
				place.x = nimuh->getPosition().x;
				place.y = nimuh->getPosition().y-1;
			}
			place.out = !positionIsOnBoard(place);
			
			bool tileCenter = true;
			if (referencePositions(place, nimuh->getPosition()) != TILE_CENTER) {
				tileCenter = false;
			}
			if (nimuh->setPosition(place)) {
				//addStateHistory();
				if (!tileCenter) {
					Sounds::GetInstance()->getSound("steps_nimuh")->play(2, 0);
				}
			}
		}
	}
}

void Board::verifyClickOnBoard() { 
	if (turn == TURN_PLAYER) {
        beginAnimationWaiting();
		if ( (!nimuh->getIsMovement()) && (!nimuh->getIsMoving()) && (mlPause<=0) && (!teletransport) ) {
			bool tileCenter = true;
			if (referencePositions(getPositionMouse(), nimuh->getPosition()) != TILE_CENTER) {
				tileCenter = false;
			}
			if (nimuh->setPosition(getPositionMouse())) {
				//addStateHistory();
				if (!tileCenter) {
					Sounds::GetInstance()->getSound("steps_nimuh")->play(2, 0);
				}
			}
		}
	}
}


void Board::drawArrow() {
     
	//arrow
	
	if ( (turn == TURN_PLAYER) && (!nimuh->getIsMoving()) && scenegame->getActive()
			&& (scenegame->getStatusScene() == SCENE_GAME_MAIN) ) {
         	
		BoardPosition bpmouse = getPositionMouse();
		if (!bpmouse.out) {
			int rel = referencePositions(nimuh->getPosition(), bpmouse);
			
			if (rel!=TILE_OTHER) {
				arrow->setForcePosition(bpmouse);
				floorOn->setForcePosition(bpmouse);
				bool drawArrow = true;
				if (rel==TILE_CENTER) {
					arrow->setForceAnimation("center");
				} else if (rel==TILE_RIGHT) {
					if (hasWallRight(nimuh->getPosition().x, nimuh->getPosition().y)) {
						drawArrow = false;
					} else {
						arrow->setForceAnimation("right");
					}
				} else if (rel==TILE_LEFT) {
					if (hasWallRight(nimuh->getPosition().x-1, nimuh->getPosition().y)) {
						drawArrow = false;
					} else {
						arrow->setForceAnimation("left");
					}
				} else if (rel==TILE_UP) {
					if (hasWallBottom(nimuh->getPosition().x, nimuh->getPosition().y-1)) {
						drawArrow = false;
					} else {
						arrow->setForceAnimation("up");
					}
				} else if (rel==TILE_DOWN) {
					if (hasWallBottom(nimuh->getPosition().x, nimuh->getPosition().y)) {
						drawArrow = false;
					} else {
						arrow->setForceAnimation("down");
					}
				}
				if (drawArrow) {
					floorOn->draw();
					arrow->draw();
				}
			}
		}
	}
}

void Board::draw() {
	
	if (!scenegame->getActive()) {
		if ( Chronometer::GetInstance()->verifyTime("intro_board", 0) ) {
			floor0->setFadeIn(500);
			floor1->setFadeIn(500);
			trap->setFadeIn(500);
			floor0->setRotationNormal(360, 500);
			floor1->setRotationNormal(360, 500);
			trap->setRotationNormal(360, 500);
		}
		if ( Chronometer::GetInstance()->verifyTime("intro_board", 500) ) {
            scenary->show();
			wallBottom->setFadeIn(500);
			wallRight->setFadeIn(500);
			pavementTop->setFadeIn(500);
			pavementBottom->setFadeIn(500);
        	if (hasBlackHole0) {
				blackHole0->show();
				particlesBlackHole0->show();
				blackHole0->setFadeIn(500);
				particlesBlackHole0->setFadeIn(500);
            }
        	if (hasBlackHole1) {
				blackHole1->show();
				particlesBlackHole1->show();
				blackHole1->setFadeIn(500);
				particlesBlackHole1->setFadeIn(500);
            }
			if (hasKey) {
				key->show();
				doorKeyBottom->show();
				doorKeyRight->show();
				key->setFadeIn(500);
				doorKeyBottom->setFadeIn(500);
				doorKeyRight->setFadeIn(500);
            }
			if (hasTray) {
				tray->show();
				tray->setFadeIn(500);
            }
		}
		if ( Chronometer::GetInstance()->verifyTime("intro_board", 1000) ) {
			if (hasEnemy3) {
				Sounds::GetInstance()->getSound("pop")->play(2, 0);
				enemy3->show();
			}
		}
		if ( Chronometer::GetInstance()->verifyTime("intro_board", 1500) ) {
			if (hasEnemy2) {
				Sounds::GetInstance()->getSound("pop")->play(2, 0);
				enemy2->show();
			}
		}
		if ( Chronometer::GetInstance()->verifyTime("intro_board", 2000) ) {
			if (hasEnemy1) {
				Sounds::GetInstance()->getSound("pop")->play(2, 0);
				enemy1->show();
			}
		}
		if ( Chronometer::GetInstance()->verifyTime("intro_board", 2500) ) {
			Sounds::GetInstance()->getSound("pop")->play(2, 0);
			nimuh->show();
		}
	}
	
	// scenary
	scenary->work();
	scenary->draw();
	
	pavementTop->draw();
	
    int x, y;
	
	// floor
	
	bool todoParticlesTrap = false;
		
	for (y=0; y<rows; y++) {
		
        for (x=0; x<cols; x++) {
			int xs0 = 0;
			int xs1 = 1;
			if (hasTrap) {
				if ( (posTrap.x == 0) && (posTrap.y == 0) ) {
					xs0 = 2;
				}
				if ( (posTrap.x == 1) && (posTrap.y == 0) ) {
					xs1 = 3;
				}
			}
			if ( (y==0) && ( (x==xs0) || (x==xs1) ) ) {
				floor0->setToDoAllEffects(true);
				floor1->setToDoAllEffects(true);
			} else {
				floor0->setToDoAllEffects(false);
				floor1->setToDoAllEffects(false);
			}
			
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
					todoParticlesTrap = true;
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
	
	drawArrow();
	
	// door
	if ( (door->getDoorPosition()==UP) || (door->getDoorPosition()==LEFT) ) {
		door->draw();	
	}
		
	// objects
	
	bool firstWallRight = true;
	bool firstWallBottom = true;
	
	for (int s=0; s<=(rows-1)*2; s++) {
        for (int n=0; n<=s; n++) {
            x = n;
            y = s-n;
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
                
        		//drawArrow(x, y);
                                                              		   			
        		if ( (nimuh->getXBoard() == x) && (nimuh->getYBoard() == y) ) {
        			nimuh->draw();	
        		}
				if ( (enemy1->getXBoard() == x) && (enemy1->getYBoard() == y) && hasEnemy1 ) {
        			enemy1->draw();	
        		}
				if ( (enemy2->getXBoard() == x) && (enemy2->getYBoard() == y) && hasEnemy2 ) {
        			enemy2->draw();	
        		}
				if ( (enemy3->getXBoard() == x) && (enemy3->getYBoard() == y) && hasEnemy3 ) {
        			enemy3->draw();	
        		}
        		
				if (todoParticlesTrap) {
					if ( (posTrap.x == x) && (posTrap.y == y) ) {
						particlesTrap->draw();
					}
				}
        		
                if (hasBlackHole0) {
                    if ( (particlesBlackHole0->getXBoard() == x) && (particlesBlackHole0->getYBoard() == y) ) {
            			particlesBlackHole0->draw();	
            		}
                }
                
                if (hasBlackHole1) {
            		if ( (particlesBlackHole1->getXBoard() == x) && (particlesBlackHole1->getYBoard() == y) ) {
            			particlesBlackHole1->draw();	
            		}
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
    			if ( ( hasWallRight(x, y, false) ) && (x<getCols()) ) {
					if (firstWallRight) {
						wallRight->setToDoAllEffects(true);
						firstWallRight = false;
					} else {
						wallRight->setToDoAllEffects(false);
					}					
    				wallRight->setForcePosition(x,y);
    				wallRight->draw();
    			}
				
    			// bottom wall
    			if ( ( hasWallBottom(x, y, false) ) && (y<getRows()) ) {
					if (firstWallBottom) {
						wallBottom->setToDoAllEffects(true);
						firstWallBottom= false;
					} else {
						wallBottom->setToDoAllEffects(false);
					}
    				wallBottom->setForcePosition(x,y);
    				wallBottom->draw();
    			}

				
            }
    		
        }    
    } // final objects
	
	if (inExplosion) {
       if (!explosionEnemies->isVisible()) {
            inExplosion = false;
            todoNextTurn = true;
       }
       explosionEnemies->draw();
    }
	
	pavementBottom->draw();
	
	// door
	if ( (door->getDoorPosition()==DOWN) || (door->getDoorPosition()==RIGHT) ) {
		door->draw();	
	}
	

}

void Board::unLoad() {
	history.clear();
	delete door;
	delete scenary;
	delete arrow;
	delete floor0;
	delete floor1;
	delete floorShadow;
	delete wallBottom;
	delete wallRight;
	delete nimuh;
	delete enemy1;
	delete enemy2;
	delete enemy3;
	delete explosionEnemies;
	
	delete blackHole0;
	delete blackHole1;
	delete particlesBlackHole0;
	delete particlesBlackHole1;
	delete trap;
	delete particlesTrap;
	delete tray;
	
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
} DataScreenXML;


void initDataScreenXML(DataScreenXML *dataScreen) {
	dataScreen->x = 0;
	dataScreen->y = 0;
	dataScreen->bottom = false;
	dataScreen->right = false;
}

static void startScreenXML(void *userData, const char *el, const char **attr) {

	DataScreenXML* dataScreen = (DataScreenXML*)userData;
	int i;

	if (strcmp(el, "multilanguage") == 0) {
		for (i = 0; attr[i]; i += 2) {
			if ( (strcmp(attr[i], "value") == 0) && (strcmp(attr[i+1], "true") == 0) ) {
				Board::GetInstance()->multiLanguage = true;
			}
		}		
	} else if (strcmp(el, "animation-end") == 0) {
		for (i = 0; attr[i]; i += 2) {
			if (strcmp(attr[i], "fromdata") == 0) {
				Board::GetInstance()->getSceneGame()->setAnimationEnd(string(DATA_DIR) + "/" + attr[i+1]);
			} else if (strcmp(attr[i], "fromlevel") == 0) {
				Board::GetInstance()->getSceneGame()->setAnimationEnd(Missions::GetInstance()->currentLevel->getPath() + "/" + attr[i+1]);
			}
		}
	} else if (strcmp(el, "help-first-level") == 0) {
		for (i = 0; attr[i]; i += 2) {
			if ( (strcmp(attr[i], "value") == 0) && (strcmp(attr[i+1], "true") == 0) ) {
				Board::GetInstance()->getSceneGame()->createHelpFirstLevel();
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
				Board::GetInstance()->town.name = attr[i+1];
			} else if (strcmp(attr[i], "province") == 0) {
				Board::GetInstance()->town.province = attr[i+1];
			} else if (strcmp(attr[i], "nickname") == 0) {
				Board::GetInstance()->town.nickname = attr[i+1];
			}
		}
	} else if (strcmp(el, "help") == 0) {
		for (i = 0; attr[i]; i += 2) {
			if (strcmp(attr[i], "name") == 0) {
				Board::GetInstance()->getSceneGame()->loadHelp(attr[i+1]);
			}
		}
	} else if (strcmp(el, "music") == 0) {
		for (i = 0; attr[i]; i += 2) {
			if (strcmp(attr[i], "type") == 0) {
				Board::GetInstance()->getSceneGame()->loadMusic(atoi(attr[i+1]));
			}
		}
	} else if (strcmp(el, "info-tray") == 0) {
		string titleTray="", textTray="", lang="";
		for (i = 0; attr[i]; i += 2) {
			if (strcmp(attr[i], "title") == 0) {
				titleTray = attr[i+1];
			} else if (strcmp(attr[i], "text") == 0) {
				textTray = attr[i+1];
			} else if (strcmp(attr[i], "lang") == 0) {
				lang = attr[i+1];
			}
		}
		
		bool todo =false;
		
		if (Board::GetInstance()->multiLanguage) {
			if (lang == Language::GetInstance()->getLang()) {
				todo = true;
			}
		} else {
			todo = true;
		}
		if (todo) {
			Board::GetInstance()->infoTray.title = titleTray;
			Board::GetInstance()->infoTray.text = textTray;
			Board::GetInstance()->infoTray.lang = lang;
		}
		
	} else if (strcmp(el, "board") == 0) {
		bool tb = false;
		for (i = 0; attr[i]; i += 2) {
			if ( (strcmp(attr[i], "type") == 0) && (strcmp(attr[i+1], "6x6") == 0) ) {
				Board::GetInstance()->setTypeSize(BOARD_6X6);
				tb = true;
			}
			if ( (strcmp(attr[i], "type") == 0) && (strcmp(attr[i+1], "7x7") == 0) ) {
				Board::GetInstance()->setTypeSize(BOARD_7X7);
				tb = true;
			}
			if ( (strcmp(attr[i], "type") == 0) && (strcmp(attr[i+1], "8x8") == 0) ) {
				Board::GetInstance()->setTypeSize(BOARD_8X8);
				tb = true;
			}
			if ( (strcmp(attr[i], "type") == 0) && (strcmp(attr[i+1], "9x9") == 0) ) {
				Board::GetInstance()->setTypeSize(BOARD_9X9);
				tb = true;
			}
			if ( (strcmp(attr[i], "type") == 0) && (strcmp(attr[i+1], "10x10") == 0) ) {
				Board::GetInstance()->setTypeSize(BOARD_10X10);
				tb = true;
			}
			if (strcmp(attr[i], "floor") == 0) {
				Board::GetInstance()->setTypeFloor(atoi(attr[i+1]));
			}
			if (strcmp(attr[i], "wall") == 0) {
				Board::GetInstance()->setTypeWall(atoi(attr[i+1]));
			}
			if (strcmp(attr[i], "pavement") == 0) {
				Board::GetInstance()->setTypePavement(atoi(attr[i+1]));
			}
		}
		if (!tb) Board::GetInstance()->setTypeSize(BOARD_6X6);
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
					Board::GetInstance()->getScenary()->setType(SCENARY_OPENED);
				} else {
					Board::GetInstance()->getScenary()->setType(SCENARY_CLOSED);
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
		if (Board::GetInstance()->getScenary()->getType() == SCENARY_CLOSED) {
			Board::GetInstance()->getScenary()->setColorInWalls(r, g, b);
			Board::GetInstance()->getScenary()->setNVerticalTiles(ntiles);
			Board::GetInstance()->getScenary()->setTypeTiled(ttiled);
			Board::GetInstance()->getScenary()->setTypeWall(twallscenary);
		} else {
			Board::GetInstance()->getScenary()->setNVerticalTiles(ntiles);
			Board::GetInstance()->getScenary()->setTypeTiled(ttiled);
			Board::GetInstance()->getScenary()->setTypeTerrain(tterrain);
        }
	} else if (strcmp(el, "object") == 0) {
		char name[32];
		int x = 30;
		int y = 0;
		int type = TYPEOBJECT_3D;
		float scale = 1.0;
		bool flip = false;
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
			Board::GetInstance()->getScenary()->addTextObject(text, font, align, c, x, y, scale, flip, false);
		} else {
			Board::GetInstance()->getScenary()->addObject(type, origen, name, x, y, scale, flip);
		}
	}

}

static void endScreenXML(void *userData, const char *el)
{
	DataScreenXML* dataScreen = (DataScreenXML*)userData;

	if (strcmp(el, "player") == 0) {
		Board::GetInstance()->setPositionPlayer(dataScreen->x, dataScreen->y);
		initDataScreenXML(dataScreen);
	} else if (strcmp(el, "enemy1") == 0) {
		Board::GetInstance()->setPositionEnemy1(dataScreen->x, dataScreen->y);
		initDataScreenXML(dataScreen);
	} else if (strcmp(el, "enemy2") == 0) {
		Board::GetInstance()->setPositionEnemy2(dataScreen->x, dataScreen->y);
		initDataScreenXML(dataScreen);
	} else if (strcmp(el, "enemy3") == 0) {
		Board::GetInstance()->setPositionEnemy3(dataScreen->x, dataScreen->y);
		initDataScreenXML(dataScreen);
	} else if (strcmp(el, "exit") == 0) {
		Board::GetInstance()->setPositionExit(dataScreen->x, dataScreen->y);
		initDataScreenXML(dataScreen);
	} else if (strcmp(el, "blackhole0") == 0) {
		Board::GetInstance()->setBlackHole0(dataScreen->x, dataScreen->y);
		initDataScreenXML(dataScreen);
	} else if (strcmp(el, "blackhole1") == 0) {
		Board::GetInstance()->setBlackHole1(dataScreen->x, dataScreen->y);
		initDataScreenXML(dataScreen);
	} else if (strcmp(el, "key") == 0) {
		Board::GetInstance()->setKey(dataScreen->x, dataScreen->y);
		initDataScreenXML(dataScreen);
	} else if (strcmp(el, "trap") == 0) {
		Board::GetInstance()->setPositionTrap(dataScreen->x, dataScreen->y);
		initDataScreenXML(dataScreen);
	} else if (strcmp(el, "tray") == 0) {
		Board::GetInstance()->setPositionTray(dataScreen->x, dataScreen->y);
		initDataScreenXML(dataScreen);
	} else if (strcmp(el, "door-key") == 0) {
		Board::GetInstance()->setDoorKey(dataScreen->x, dataScreen->y, dataScreen->direction);
		initDataScreenXML(dataScreen);
	} else if (strcmp(el, "wall") == 0) {
		if (dataScreen->bottom) {
			Board::GetInstance()->setWallBottom( dataScreen->x, dataScreen->y, true);
		}
		if (dataScreen->right) {
			Board::GetInstance()->setWallRight( dataScreen->x, dataScreen->y, true);
		}
		initDataScreenXML(dataScreen);
	}


}

void parseScreenXML(char fileXML[256]) {
	char buffer[8192];
	int done;
	
	DataScreenXML dataScreen;
	initDataScreenXML(&dataScreen);
	
	XML_Parser p = XML_ParserCreate(NULL);
	if (! p) {
		printf("Podra no tener suficiente memoria para el parser\n");
	}

	XML_SetUserData(p, &dataScreen);	
	XML_SetElementHandler(p, startScreenXML, endScreenXML);

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
