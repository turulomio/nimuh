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

#ifndef CLASSEDITGAME_H_
#define CLASSEDITGAME_H_

#include "martian.h"
#include "defines_game.h"
#include "scene_editgame.h"
#include "scene_createmissions.h"
#include "scene_infotown.h"
#include "class_game.h"
#include "elements.h"

using namespace std;
using namespace Martian;

void parseEditScreenXML(char fileXML[128]);

class SceneEditGame;

	
class EditDoor : public Door {
	
public:

	EditDoor();
	~EditDoor ();
	bool setForcePosition(BoardPosition p);
	bool setForcePosition(int x, int y);
	
	void unLoad() { }
};

class EditScenary : public Scenary {

public:
	EditScenary();
	~EditScenary ();
	
	void setTypeTiled(int t);
	void setTypeTerrain(int t);
	void setTypeWall(int t);
	
	void draw();
	void drawScenaryClosed();
	void drawScenaryOpened();
	void paintTiled();

	void unLoad() { }
	
};

typedef struct
{
	string title1;
	string text1;
	string title2;
	string text2;
	string distanceSecondText;
	string lang;
} EditMap;

class EditBoard : public Group {
	
private:
    static EditBoard *instance;
    EditBoard();

	SceneEditGame *sceneeditgame;

	EditScenary *scenary;
	EditDoor *door;
	ElementIsometric *ghost;
	ElementIsometric *nimuh;
	ElementIsometric *enemy1, *enemy2, *enemy3;
	ElementIsometric *floorOn;
	Element *floor0, *floor1;
	Element *trap;

	int typeFloor;
    int rows, cols;
    int indexz;

	int typeMusic;

	ElementIsometric *wallBottom;
	ElementIsometric *wallRight;
	int typeWall;
	
	Element *floorShadow;

	BoardPosition posBegPlayer, posBegEnemy1, posBegEnemy2, posBegEnemy3, posExit;
	Walls walls[MAX_TILES_INLINE*MAX_TILES_INLINE];

	int typeSize;
	
	bool hasEnemy1;
	bool hasEnemy2;
	bool hasEnemy3;
	
	BoardPosition posTrap;
	bool hasTrap;
	
	ElementIsometric *tray;
	bool hasTray;
	
	ElementIsometric *blackHole0, *blackHole1;
    bool hasBlackHole0, hasBlackHole1;
	
	ElementIsometric *doorKeyBottom, *doorKeyRight, *key;
	string directionKey;
	bool hasKey;
	
	Element *pavementTop, *pavementBottom;
	int typePavement;


public:
       
	bool multiLanguage;

	bool wallsOfLevel;
	bool terrainOfLevel;
	bool wallScennaryOfLevel;
	bool musicOfLevel;
	bool pavementOfLevel;
	bool floorOfLevel;
	bool tiledOfLevel;
       
	vector<InformationTown> infoTown;
	string helpName;
	Town town;
	vector<InfoTray> infoTray;

	bool hasMap;
	string fileFromDataMap;
	string fileFromLevelMap;
	vector<EditMap> map;

	static EditBoard * GetInstance ();

	EditScenary* getScenary() { return scenary; }

	~EditBoard ();
	
	void load();
	void loadLevel();
	bool save();
	void clear();

	void setSceneEditGame(SceneEditGame *s) { sceneeditgame = s; }
	SceneEditGame* getSceneEditGame() { return sceneeditgame; }
	
	void setTypeSize(int t);
	int getTypeSize() { return typeSize; }
	void setTypeFloor(int t);
	void setTypeWall(int t);
	void setTypePavement(int t);
	
	bool verifyHasObject(string obj, BoardPosition p);

	void setTypeMusic(int t) { typeMusic = t; }
	int getTypeMusic() { return typeMusic; }
	
	void setCols(int c) { cols = c; }
	int getCols() { return cols; }
	void setRows(int r) { rows = r; }
	int getRows() { return rows; }
	BoardPosition getPositionMouse();
	bool positionIsOnBoard(BoardPosition p);
	bool verifyPositions(BoardPosition p1, BoardPosition p2);
	int referencePositions(BoardPosition p1, BoardPosition p2);
	
	BoardPosition getPositionFromXY(int x, int y) { BoardPosition p; p.x=x; p.y=y; p.out = !Board::GetInstance()->positionIsOnBoard(p); return p; }
	
	void verifyMouseOnBoard();
	void verifyClickOnBoard();
	void verifyUnClickOnBoard();

	/*********************
	* SURFACE
	**********************/
	void draw();
	void setIndexZ (int z) { indexz = z; }
	int getIndexZ () { return indexz; }
	/*********************
	* ELEMENTS
	**********************/
	BoardPosition getPositionPlayer();
	BoardPosition getPositionEnemy1();
	BoardPosition getPositionEnemy2();
	BoardPosition getPositionEnemy3();
	void setBlackHole0(int x, int y);
	void setBlackHole1(int x, int y);
	void setKey(int x, int y);
	void setDoorKey(int x, int y, string dk);
	void setPositionPlayer(int x, int y);
	void setPositionEnemy1(int x, int y);
	void setPositionEnemy2(int x, int y);
	void setPositionEnemy3(int x, int y);
	void setPositionExit(int x, int y);
	void setPositionTrap(int x, int y);
	void setPositionTray(int x, int y);
	
	void cleanWalls();
	void cleanScenary();
	
	void setWallBottom(int x, int y, bool state) { walls[(y*MAX_TILES_INLINE)+x].wallBottom = state; }
	void setWallRight(int x, int y, bool state) { walls[(y*MAX_TILES_INLINE)+x].wallRight = state; }
	bool hasWallBottom(int x, int y) { if (positionIsOnBoard(getPositionFromXY(x,y))) { return walls[(y*MAX_TILES_INLINE)+x].wallBottom; } else { return false; } }
	bool hasWallRight(int x, int y) { if (positionIsOnBoard(getPositionFromXY(x,y))) { return walls[(y*MAX_TILES_INLINE)+x].wallRight; } else { return false; } }
	
	bool hasWallBetweenCells(BoardPosition p1, BoardPosition p2);
	
	void insertObject(BoardPosition p);
	void changeGhost();
	
	void unLoad();

};

#endif /* CLASSEDITGAME_H_ */
