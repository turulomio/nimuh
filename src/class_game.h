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

#ifndef CLASSGAME_H_
#define CLASSGAME_H_

#include "martian.h"
#include "defines_game.h"
#include "scene_game.h"
#include "missions.h"

#include <math.h>

#define W_TILE 130
#define H_TILE 62
#define MAX_TILES_INLINE 10
#define ASPECT_RATIO 0.5

#define TILE_CENTER 0
#define TILE_LEFT 1
#define TILE_UP 2
#define TILE_DOWN 3
#define TILE_RIGHT 4
#define TILE_OTHER 5

using namespace std;
using namespace Martian;

class SceneGame;

void parseScreenXML(char fileXML[256]);

class BoardInfo : public Hash {
public :
	static BoardInfo * GetInstance ();
	~BoardInfo ();
private :
	static BoardInfo *instance;
	BoardInfo (string file);			
};

typedef struct
{
	int x;
	int y;
	bool out;
} BoardPosition;

typedef struct
{
	bool wallBottom;
	bool wallRight;
} Walls;

typedef struct
{
	string name;
	string file;
	string category;
	int type;
	float minScale;
	float maxScale;
} TypeObjectScenary;

typedef struct
{
	string title;
    string text;
	string button;
	string lang;
} InformationTown;

class Enemy;

typedef struct
{
	int number;
	BoardPosition nimuh;
	BoardPosition enemy1;
	BoardPosition enemy2;
	BoardPosition enemy3;
	bool hasTray;
	bool hasEnemy1;
	bool hasEnemy2;
	bool hasEnemy3;
	bool doorKeyClosed;
	Enemy* enemy;
} History;

class TypeObjectsScenary {
public :
	static TypeObjectsScenary * GetInstance ();
	void addObject(TypeObjectScenary obj) { objects.push_back(obj); }
	void clear() { objects.clear(); }
	TypeObjectScenary* getObject(string name);
	void load();

	int cursor;
	void MoveFirst() { cursor = 0; }
	void MoveLast() { cursor = objects.size()-1; }
	void MovePrevious() { cursor--; }
	void MoveNext() { cursor++; }
	bool isBOF() { return (cursor<0)?true:false; }
	bool isEOF() { return (cursor>(int)objects.size()-1)?true:false; }
	TypeObjectScenary* getObject() { return &objects[cursor]; }
	
	~TypeObjectsScenary ();
private :
	TypeObjectsScenary ();
	vector<TypeObjectScenary> objects;
	static TypeObjectsScenary *instance;
	
};

class BoardScale {
public :
	static BoardScale * GetInstance ();
	int getHTile() { return h_tile; }
	int getWTile() { return w_tile; }
	void setScale(float s);
	~BoardScale ();
private :
	BoardScale ();
	float scale;
    int w_tile, h_tile;
	static BoardScale *instance;
	
};

class MouseMapTile {
public :
	static MouseMapTile * GetInstance ();
	void createMap ();
	int getPosMouse (int x, int y);
	~MouseMapTile ();
private :
	MouseMapTile ();
	vector<int> map;
	static MouseMapTile *instance;
	
};

class Plot {
public :
	static Plot * GetInstance ();
	float getX (int x, int y) { return (x-y)*(BoardScale::GetInstance()->getWTile()*ASPECT_RATIO); }
	float getY (int x, int y) { return (x+y)*(BoardScale::GetInstance()->getHTile()*ASPECT_RATIO); }
	~Plot ();
private :
	Plot ();
	static Plot *instance;
	
};

class ObjectScenary : public ElementDnD {
	
private:
	int typeObject;
    int typeScenary;
	int origen;
    bool lock;
	string type;
	bool showIcons;
	float minScale, maxScale;

	bool flipObject;

	string fontText;
	string text;
	int alignText;
	Color colorText;
	
public:
	Button *iconZoomin, *iconZoomout, *iconDelete, *iconDuplicate, *iconLock, *iconFlip, *iconOrderBottom, *iconOrderTop;
	ObjectScenary();
	~ObjectScenary();

	void swapFlip () { setFlip (!flipObject); }
	void setFlip (bool f);
	bool getFlip () { return flipObject; }
	
	void setText(string t, string f, int a, Color c) { text = t; fontText = f; alignText = a; colorText = c; }
	
	string getText() { return text; }
	string getFontText() { return fontText; }
	int getAlignText() { return alignText; }
	Color getColorText() { return colorText; }
	
	void setOrigen(int o) { origen = o; }
	int getOrigen() { return origen; }

	void setMinScale(float s) { minScale = s; }
	float getMinScale() { return minScale; }
	
	void setMaxScale(float s) { maxScale = s; }
	float getMaxScale() { return maxScale; }
	
	void swapLock ();
	bool getLock() { return lock; }
	
	void setX (float x);
	void setY (float y);
	void addX (float x);
	void addY (float y);
	void setGroup(Group *g);
	void removeGroup() { group = NULL; }
	void setType(string t) { type = t; }
	string getType() { return type; }
	
	void setTypeScenary(int t) { typeScenary = t; }
	int getTypeScenary() { return typeScenary; }
	
	void setTypeObject(int t) { typeObject = t; }
	int getTypeObject() { return typeObject; }
	
	void setShowIcons(bool s) { showIcons = s; }
	bool getShowIcons() { return showIcons; }
	void swapShowIcons() { showIcons = !showIcons; }
	void onOver();
	void draw();
	void drawIcons();
	void unLoad();

};

class Scenary : public Group {
	
protected:
	bool editable;
	int type;
	int typeTiled;
	int typeTerrain;
	int c_typeTiledBottom;
	int nVerticalTiles;
	vector<ObjectScenary*> objects;
	Element *tileLeft, *tileLeftUp;
	Element *tileRight, *tileRightUp;

	int typeWall;
	Element *wallLeft, *wallRight, *shadowWall;
	Element *guideLeft, *guideRight;
	bool showGuides;
		
	Element *terrainOpened;

	float separatedTilesClosed;
	
	int colorRWallClosed, colorGWallClosed, colorBWallClosed;

public:

	Scenary();
	~Scenary();
	
	void clear();
	
	void hide();
	void show();

	void setTypeTiled(int t);
	void setTypeTerrain(int t);
	void setTypeWall(int t);

	void addTextObject(string t, string f, int a, Color c, int x, int y, float scale, bool flip, bool lock);

	void addObject(int origenObj, ObjectScenary* el);
    void addObject(int origenObj, ObjectScenary* el, bool lock);

	void addObject(int typeObj, int origenObj, string object);
	void addObject(int typeObj, int origenObj, string object, int x, int y);
	void addObject(int typeObj, int origenObj, string object, int x, int y, float scale);
	void addObject(int typeObj, int origenObj, string object, int x, int y, float scale, bool flip);
	void addObject(int typeObj, int origenObj, string object, int x, int y, float scale, bool flip, bool lock);
		
	int getR_ColorInWalls() { return colorRWallClosed; }
	int getG_ColorInWalls() { return colorGWallClosed; }
	int getB_ColorInWalls() { return colorBWallClosed; }
	
	void setColorInWalls(int r, int g, int b);
	
	string toXML ();
	
	void scaleTiles (float scale);
	
	void onOver ();
	void verifyClick ();
	void verifyShowIcons ();
	void removeDnd ();
	
	void addNVerticalTiles (int n) { nVerticalTiles += n; };
	void setNVerticalTiles (int n) { nVerticalTiles = n; };
	int getNVerticalTiles () { return nVerticalTiles; };
	
	void setType (int t);
	int getType () { return type; };
	
	void setEditable (bool e) { editable = e; };
	bool getEditable () { return editable; };
	
	void setShowGuides (bool s) { showGuides = s; };
	void swapShowGuides () { showGuides = !showGuides; };
	bool getShowGuides () { return showGuides; };
	
	void setC_TypeTiledBottom (int t) { c_typeTiledBottom = t; };
	int getC_TypeTiledBottom () { return c_typeTiledBottom; };
	
	//void setC_ColorWall (int r, int g, int b) { c_colorWallR = r; c_colorWallG = g; c_colorWallB = b; };
	
	void paintTiled();
	
	void draw();
	void drawScenaryClosed();
	void drawScenaryOpened();
	
	void unLoad();

};

class ElementIsometric;
class Player;
class Enemy;
class Door;
	
typedef struct
{
	string name;
	string province;
	string nickname;
} Town;

typedef struct
{
	string title;
	string text;
	string lang;
} InfoTray;

class Board : public Group {
	
private:
	
	int mlPause;

    static Board *instance;
    Board();
    
    ParticlesSystem *explosionEnemies;

    bool inExplosion;
    int paddingExplosion;

	SceneGame *scenegame;

	Scenary *scenary;
	Door *door;
	ElementIsometric *arrow;
	Element *floor0, *floor1;
	AnimatedElement *trap;
	ElementIsometric *particlesTrap;
	int typeFloor;
    int rows, cols;
    int indexz;

	int turn;
	
	bool isAnimationWaiting;
	int typeAnimationWaiting;
	
	ElementIsometric *blackHole0, *blackHole1;
	ElementIsometric *particlesBlackHole0, *particlesBlackHole1;
    bool hasBlackHole0, hasBlackHole1;
	bool canChangeInHistory_BlackHole0, canChangeInHistory_BlackHole1;
	
	ElementIsometric *doorKeyBottom, *doorKeyRight, *key;
	string directionKey;
	bool doorKeyClosed;
	bool hasKey;
	bool canChangeInHistory_Key;
    
    bool teletransport;
    BoardPosition posTeletransport;
	
	ElementIsometric *floorOn;
    
	ElementIsometric *wallBottom;
	ElementIsometric *wallRight;
	int typeWall;
	
	Element *floorShadow;
	
	Element *pavementTop, *pavementBottom;
	int typePavement;

	Walls walls[MAX_TILES_INLINE*MAX_TILES_INLINE];

	int typeSize;
	
	vector<History> history;
	int totalHistory;
	int currentHistory;

public:

	bool multiLanguage;

	bool wallsOfLevel;
	bool terrainOfLevel;
	bool wallScennaryOfLevel;
	bool musicOfLevel;
	bool pavementOfLevel;
	bool floorOfLevel;
	bool tiledOfLevel;
	
	Town town;
	InfoTray infoTray;

	ElementIsometric *tray;	
	bool hasTray;
	bool canChangeInHistory_Tray;

	Player *nimuh;
	Enemy *enemy1;
	bool hasEnemy1;
	bool canChangeInHistory_Enemy1;
	Enemy *enemy2;
	bool hasEnemy2;
	bool canChangeInHistory_Enemy2;
	Enemy *enemy3;
	bool hasEnemy3;
	bool canChangeInHistory_Enemy3;

	BoardPosition posTrap;
	bool hasTrap;

    bool todoNextTurn;
    bool catchedEnemy1, catchedEnemy2;

	void pause(int p) { mlPause = p; Chronometer::GetInstance()->setTime("pause-board"); }

	static Board * GetInstance ();

	Scenary* getScenary() { return scenary; }

	~Board ();
	
	void load();
	void loadLevel();
	void clear();

	void changeBoardWithCurrentHistory();
	void addStateHistory();
	void addHistory();
	void nextHistory();
	void previousHistory();
	
	void setSceneGame(SceneGame *s) { scenegame = s; }
	SceneGame *getSceneGame() { return scenegame; }

	void setTypeSize(int t);
	int getTypeSize() { return typeSize; }
	void setTypeFloor(int t);
	void setTypeWall(int t);
	void setTypePavement(int t);
	
	void createExplosion(Enemy *e);
	void verifyStartToEat(Enemy *e);
	
	void movePlayer(int pos);
	
	void swapDoorKey();

	float getScaleByTypeSize();
	
	void nextTurn();
	int getTurn() { return turn; }

	void setCols(int c) { cols = c; }
	int getCols() { return cols; }
	void setRows(int r) { rows = r; }
	int getRows() { return rows; }
	BoardPosition getPositionMouse();
	bool positionIsOnBoard(BoardPosition p);
	bool verifyPositions(BoardPosition p1, BoardPosition p2);
	int referencePositions(BoardPosition p1, BoardPosition p2);
	
	BoardPosition getPositionFromXY(int x, int y) { BoardPosition p; p.x=x; p.y=y; p.out = !Board::GetInstance()->positionIsOnBoard(p); return p; }

	void beginAnimationWaiting() { Sounds::GetInstance()->stopChannel(12); Chronometer::GetInstance()->setTime("animationwaiting"); isAnimationWaiting = false; }
	void verifyAnimationWaiting();
	void verifyStopAnimationWaiting();
	
	void verifyWinPlayer();
	
	void verifyClickOnBoard();
	void stopAnimations();

	/*********************
	* SURFACE
	**********************/
	void drawArrow();
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
	void setWallBottom(int x, int y, bool state) { walls[(y*MAX_TILES_INLINE)+x].wallBottom = state; }
	void setWallRight(int x, int y, bool state) { walls[(y*MAX_TILES_INLINE)+x].wallRight = state; }
	
	bool hasWallBottom(int x, int y) { return hasWallBottom(x, y, true); }
	bool hasWallRight(int x, int y) { return hasWallRight(x, y, true); }
	bool hasWallBetweenCells(BoardPosition p1, BoardPosition p2) { return hasWallBetweenCells(p1, p2, true); }
	
	bool hasWallBottom(int x, int y, bool verifyDoorKey);
	bool hasWallRight(int x, int y, bool verifyDoorKey);
	bool hasWallBetweenCells(BoardPosition p1, BoardPosition p2, bool verifyDoorKey);
	
	void unLoad();

};

class ElementIsometric : public AnimatedElement {
	
protected:
	float heightElement, originalHeightElement;
	float displacementX, originalDisplacementX;
	int xBoard, yBoard;
	int nextXBoard, nextYBoard;

public:

	ElementIsometric();
	~ElementIsometric();
	void setScaleHeightElement(float s) { heightElement = originalHeightElement * s; }
	void setHeightElement(float h) { heightElement = h; originalHeightElement = h; }
	float getHeightElement() { return heightElement; }
	void setScaleDisplacementX(float s) { displacementX = originalDisplacementX * s; }
	void setDisplacementX(float x) { displacementX = x; originalDisplacementX = x; }
	float getDisplacementX() { return displacementX; }
	void setXBoard(int x) { xBoard = x; }
	int getXBoard() { return xBoard; }
	void setYBoard(int y) { yBoard = y; }
	int getYBoard() { return yBoard; }
	
	void setNextXBoard(int x) { nextXBoard = x; }
	int getNextXBoard() { return nextXBoard; }
	void setNextYBoard(int y) { nextYBoard = y; }
	int getNextYBoard() { return nextYBoard; }
	
	void setNextBoardPositionInElement() { setXBoard(nextXBoard); setYBoard(nextYBoard); }
	BoardPosition getNextBoardPositionInElement() { BoardPosition p; p.x = nextXBoard; p.y = nextYBoard; p.out = !Board::GetInstance()->positionIsOnBoard(p); return p; }
	
	bool setInitialPosition(BoardPosition p)  { return setForcePosition(p); }
	bool setForcePosition(BoardPosition p) { if (!p.out) { xBoard = p.x; yBoard = p.y; setX(Plot::GetInstance()->getX(p.x,p.y)+displacementX); setY(Plot::GetInstance()->getY(p.x,p.y)-heightElement);  return true; } return false; }
	bool setForcePosition(int x, int y) { BoardPosition p; p.x=x; p.y=y; p.out = !Board::GetInstance()->positionIsOnBoard(p); return setForcePosition(p); }
	bool setPosition(BoardPosition p) { return setForcePosition(p.x, p.y); }
	bool setPosition(int x, int y) { return setForcePosition(x, y); }
	
	BoardPosition getPosition() { BoardPosition p; p.x=xBoard; p.y=yBoard; p.out = !Board::GetInstance()->positionIsOnBoard(p); return p; }

	void unLoad() { }
	
};

class MovableElementIsometric : public ElementIsometric {

protected:
	int direction;
    bool isMoving;
	int nMovement; // number of movement in historyPositions
    vector<BoardPosition> historyPositions;
	
public:

	MovableElementIsometric();
	~MovableElementIsometric();

	void setDirection(int d) { direction = d; }
	int getDirection() { return direction; }
	bool getIsMoving() { return isMoving; }
	void stop();

	void clearHistoryPositions() { nMovement = 0; historyPositions.clear(); }
	void addHistoryPositions(BoardPosition p);
	void previousHistoryPositions();
	void nextHistoryPositions();
	
	bool setInitialPosition(BoardPosition p);
	bool setForcePosition(BoardPosition p);
	bool setForcePosition(int x, int y) { BoardPosition p; p.x=x; p.y=y; p.out = !Board::GetInstance()->positionIsOnBoard(p); return setForcePosition(p); }
	bool setPosition(BoardPosition p);
	bool setPosition(int x, int y) { BoardPosition p; p.x=x; p.y=y; p.out = !Board::GetInstance()->positionIsOnBoard(p); return setPosition(p); }

	void unLoad() { historyPositions.clear(); }

};

class Enemy : public MovableElementIsometric {
	
private:
    bool firstMovementHorizontal;
	bool stopped;

public:

	Enemy();
	~Enemy();
	void setStopped(bool s) { stopped = s; }
	int getStopped() { return stopped; }
	
	void setFirstMovementHorizontal(bool f) { firstMovementHorizontal = f; }
	bool getFirstMovementHorizontal() { return firstMovementHorizontal; }
	bool move(); // return true if enemy can move
	bool move_Vertical(bool forceNextTurnWithWall);
	bool move_Horizontal(bool forceNextTurnWithWall);
	void stop();
	
	void unLoad() { }

};

class Player : public MovableElementIsometric {
	
public:

	Player();
	~Player();
	bool setPosition(BoardPosition p);

	void unLoad() { }

};

class Door : public ElementIsometric {

private:
	int doorPosition;
	
public:

	Door();
	~Door();
	void setDoorPosition(int p);
	int getDoorPosition() { return doorPosition; }
	bool setInitialPosition(BoardPosition p) { return setForcePosition(p); }
	bool setForcePosition(BoardPosition p);// { if (!p.out) { xBoard = p.x; yBoard = p.y; setX(Plot::GetInstance()->getX(p.x,p.y)-10); setY(Plot::GetInstance()->getY(p.x,p.y)-heightElement); return true; } return false; }
	bool setForcePosition(int x, int y);// { BoardPosition p; p.x=x; p.y=y; p.out = !Board::GetInstance()->positionIsOnBoard(p); setForcePosition(p); }
	
	void unLoad() { }
};

#endif /* CLASSGAME_H_ */
