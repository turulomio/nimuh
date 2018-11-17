/*
 * Martian: Motor para creación de videojuegos con SDL y OpenGL
 * Copyright (C) 2007  Javier Pérez Pacheco
 *
 * Este motor tiene licencia Creative Commons y se permite
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
 */
 
#ifndef ELEMENTS_H_
#define ELEMENTS_H_

#ifdef WIN32
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#endif
#if defined(__APPLE__) && defined(__MACH__)
#include <OpenGL/gl.h>	// Header File For The OpenGL32 Library
#include <OpenGL/glu.h>	// Header File For The GLu32 Library
#else
#include <GL/gl.h>	// Header File For The OpenGL32 Library
#include <GL/glu.h>	// Header File For The GLu32 Library
#endif

#include <stdlib.h>
#include <SDL.h>
#include <SDL_image.h>
#include <math.h>
#include "defines.h"
#include "joystick.h"
#include "scene.h"
#include "world.h"
#include <string>
#include <cmath>
#include <fstream>
#include <iostream>
#include <vector>
#include <map>

#include <dirent.h> 

using namespace std;

namespace Martian {
	
	class Joystick;
	class World;
	class Scene;
		
	typedef struct
	{
		float x1, y1, x2, y2;
	} Bounds;
	
	typedef struct
	{
		float x, y;
	} Position;
	
	typedef struct
	{
		int w, h;
	} Size;
	
	typedef struct
	{
		int r, g, b;
	} Color;
	
	class Converter {
	public :
		static Converter * GetInstance ();
		int ml2cycles(int ml);
		int time2cycle(string time);
		vector<string> split(string txt, string chunk);
		string join(vector<string> txt, string chunk);
		string fillZeros(int i);
		~Converter ();
	private :
		Converter ();
		static Converter *instance;
		
	};
	
	class WorkingData {
	public :
		static WorkingData * GetInstance ();
		bool validCharacter(string c);
		bool existFile(string file);
		bool createFile(string file, string text, bool changeSpecialsCharacters);
		void createDirectory(string dir);
		void deleteDirectory(string dir);
		string replace(string chain, string search, string replace);
		string getPath(string file);
		string getFilename(string file);
		string getExtension(string file);
		string getToUpper(string str);
		string getToLower(string str);
		~WorkingData ();
	private :
		WorkingData ();
		static WorkingData *instance;
		
	};
	
	class WorkingSurfaces {
	public :
		static WorkingSurfaces * GetInstance ();
		SDL_Surface* surfaceFromImage(string path);
		SDL_Surface* mixSurfaces(SDL_Surface* back, SDL_Surface* front, Bounds *destiny);
		Size getSize(string file);
		~WorkingSurfaces ();
	private :
		WorkingSurfaces ();
		static WorkingSurfaces *instance;
		
	};
	
	class Primitives {
	public :
		static Primitives * GetInstance ();
		void put_pixel(SDL_Surface *_ima, int x, int y, Uint32 pixel);
		SDL_Surface* rectangle(int w, int h, int r, int g, int b);
		SDL_Surface* rectangle ( int w, int h, int r, int g, int b, int border, int rb, int gb, int bb );
		SDL_Surface* border ( int w, int h, int r, int g, int b, int thickness ) { return border ( w, h, r, g, b, thickness, 0, false ); }
		SDL_Surface* border ( int w, int h, int r, int g, int b, int thickness, int space ) { return border ( w, h, r, g, b, thickness, space, false ); }
		SDL_Surface* border ( int w, int h, int r, int g, int b, int thickness, int space, bool intercaleSpace );
		~Primitives ();
	private :
		Primitives ();
		static Primitives *instance;
		
	};
	
	class VectorColors {
	public :
		void addColor(Color c) { colors.push_back(c); }
		void addColor(int r, int g, int b) { Color c; c.r = r; c.g = g; c.b = b; colors.push_back(c); }
		void clear() { colors.clear(); }
		int count() { return (int)colors.size(); }
		int getIndexColor(int r, int g, int b);
		Color* getColor(int n);
		
		VectorColors ();
		~VectorColors ();
	private :
		vector<Color> colors;
		
	};
	
	class Frame {
		
	public:
           
        Frame ();
		~Frame();
           
		int w, h;
		int w_gl, h_gl;
		GLuint texture;
		int sizeTexGL(int w, int h);
		SDL_RWops* RWFromRar(char *fileRar, char *file);
		void load(char *path);
		void load(char *path, SDL_Surface *sc);
		void loadSurface (SDL_Surface *surface);
		void loadGLSurface (SDL_Surface *surface);
		//void loadGLSurfaceWithoutAlpha (SDL_Surface *surface);
		void loadSurface (SDL_Surface *surface, SDL_Surface *sc);
		void loadGL(char *path);
		//void loadGLWithoutAlpha(char *path);
		SDL_Surface* SurfaceGL(SDL_Surface* sfc);
		void loadGLFromRAR (char *fileRar, char *path);
		void unLoad();
	
	};
		
	class Animation {
		
	private:
		vector<int> frame;
		int currentFrame;
		bool stopped;
		int avFrame;
		int typeRotation;
		int cyclesBetweenFrames, cycles;
	
		int nextFrame();
		bool hasFrame() { if (currentFrame>=0) { return true; } else { return false; } };
		
	public:
		string name;
		bool isLastFrame;
		Animation ();
		~Animation();
	
		int lastFrame() { return (int)frame.size()-1; };
		
		int getCycleInFrame() { return cycles%cyclesBetweenFrames; };
	
		/*********************
		* PLAYER
		**********************/
		bool playing() { return !stopped; };
		void stop() { stopped = true; };
		void play() { stopped = false; };
		void swapPlayStop() { stopped = !stopped; };
		void start() { cycles = 0; currentFrame = 0; stopped = false; };
		/*********************
		* CONTROL FRAMES
		**********************/
		int getIndexFrame() { return currentFrame; };
		int getCurrentFrame() { return frame[currentFrame]; };
		void clearFrames() { frame.clear(); };
		void addFrame(int f) { frame.push_back(f); currentFrame = 0; };
		void addRangeFrame(int begin, int end, int steps);
		void setCyclesBetweenFrames (int c) { cyclesBetweenFrames = c; }
		int getCyclesBetweenFrames() { return cyclesBetweenFrames; }
		int getFrame();	
		/*********************
		* OTHERS
		**********************/
		//void setName(char *n) { strcpy(name, n); };
		void setName(string n) { name = n; };
		string getName() { return name; };
		void setTypeRotation(int r) { typeRotation = r; }
	
	};
	
	class Group;
	class GroupScene;

	class Element {
		
	protected:
		GroupScene *groupScene;
		Group *group;
	
		float perspectiveX1;
		float perspectiveY1;
		float perspectiveX2;
		float perspectiveY2;
		float perspectiveX3;
		float perspectiveY3;
		float perspectiveX4;
		float perspectiveY4;
		
		Element *elmBorder;
		bool hasBorder;
		bool showBorderElement;
	
		Element *elmBackground;
		bool hasBackground;
		bool showBackgroundElement;
		
		float factorMaskW, factorMaskH;
		
		float posX, posY, oldX, oldY;
		// flexible
		float xs, ys;
		// direccion
		float dx, dy; 
		// movimiento 
		float polarCos, polarSen, polarDistance; // direction polar coord
		float polarEndX, polarEndY;
		int nCyclesMovementNormal, countCyclesMovementNormal;
		int dirX, dirY;
		// por posicion
		float posXNew, posYNew; // direccion por posicion
	
		int typeMovement;
		bool isMovement;
	
		bool flip, flop;
	
		bool visible;
	
		int indexz;
		// colorizar con OpenGL
		int red, green, blue;
		
		// factors
		
		float flexibleData0, flexibleData1;
		int smoothData;
		
		// rotar
	
		float rot;
		bool forceRotateCenter;
		int typeRotate;
		float rotX, rotY, rotZ;
		float factorRotate;
		float endRotate;
		bool canRotate;
		float sRotate;
	
		int alpha; // factor alpha aplicado al elemento
		int cyclesFadeIn, cyclesFadeInTotal;
		int cyclesFadeOut, cyclesFadeOutTotal;
		int typeElement;
		int align, valign;
		int cycle;
		int blinking, stateBlinking; // variables de control de parpadeo
		bool activeBlinking;
		int cyclesBlinking;
		//int cortinilla, maxCortinilla;
		
		// scale
		bool canScale;
		int typeScale;
		float factorScaleX, factorScaleY;
		float currentScaleX, currentScaleY;
		float endScaleX, endScaleY;
		float xsScale, ysScale;
		
		int cFrame; // frame actual
		
		bool toDoAllEffects;
		
		map<string, string> parameters;
		
	private:
		void addFrame (Frame *frame);
		void addFrame (string file);
		void changeFrame (int position, Frame *frame);
		void changeFrame (int position, string file);
	
	public:
		vector<Frame*> sprite;
		/*********************
		* CONSTRUCTORS
		**********************/
		Element ();
		~Element();
		
		/*********************
		* BORDER AND BG
		**********************/
		void createBorder(int r, int g, int b, int border, int padding);
		void showBorder() { showBorderElement = true; }
		void hideBorder() { showBorderElement = false; }
		Element *getElmBorder() { return elmBorder; }
		
		void createBackground(int r, int g, int b, int padding);
		void showBackground() { showBackgroundElement = true; }
		void hideBackground() { showBackgroundElement = false; }
		Element *getElmBackground() { return elmBackground; }
		
		/*********************
		* COLORS
		**********************/
		void setRGB(int r, int g, int b) { red = r; green = g; blue = b; }
		int getRed() { return red; }
		int getGreen() { return green; }
		int getBlue() { return blue; }
		void removeRGB() { red = 255; green = 255; blue = 255; }

		/*********************
		* PARAMETERS
		**********************/
		void addParameter(string name, string value) { parameters[name] = value; }
		string getParameter(string name) { return parameters[name]; }
		/*********************
		* ROTATE
		**********************/
		void setForceRotateCenter(bool f) { forceRotateCenter = f; }
		bool getForceRotateCenter() { return forceRotateCenter; }
		void setRot(float r) { rot = r; }
		void setRotX(float r) { rotX = r; }
		void setRotY(float r) { rotY = r; }
		void setRotZ(float r) { rotZ = r; }
		void addRot(float a) { rot += a; }
		void setRot(float r, float x, float y, float z) { rot = r; rotX = x; rotY = y; rotZ = z; }
		float getRot() { return rot; }
		// movements
		void removeRotation() { canRotate= false; setRot(0); typeRotate = NO_ROTATE; }
		void setRotationNormal (float degreesEnd, int ml);
		void setRotationNormal (float degreesBegin, float degreesEnd, int ml);
		void setRotationSmooth (float degreesEnd);
		void setRotationFlexible (float degreesEnd);
		/*********************
		* FRAMES
		**********************/
		void addFrameFile (string file);
		void addFrameFileFromData (string file);
		void addFrameFile (string name, string ext, int valueInRange);
		void addFrameFileFromData (string name, string ext, int valueInRange);
		void addFrameText (string font, string text, int align);
		void addFrameText (string font, string text, int align, int width);
		void addFrameLanguage (string font, string key, int align);
		void addFrameLanguage (string font, string key, int align, int width);
		void addFrameSurface (SDL_Surface *sfc);
		
		void changeFrameFile (int pos, string file);
		void changeFrameFileFromData (int pos, string file);
		void changeFrameFile (int pos, string name, string ext, int valueInRange);
		void changeFrameFileFromData (int pos, string name, string ext, int valueInRange);
		void changeFrameText (int pos, string font, string text, int align);
		void changeFrameText (int pos, string font, string text, int align, int width);
		void changeFrameLanguage (int pos, string font, string key, int align);
		void changeFrameLanguage (int pos, string font, string key, int align, int width);
		void changeFrameSurface (int pos, SDL_Surface *sfc);
		
		void addRangeFrames (string name, string ext, int valBeg, int valEnd);
		void addRangeFramesFromData (string name, string ext, int valBeg, int valEnd);
		int getFrames () { return (int)sprite.size(); }
		void setCurrentFrame(int c) { if (c<(int)sprite.size()) cFrame = c; }
		int getCurrentFrame() { return cFrame; }
		void previousFrame() { int c = cFrame - 1; if (c>=0) { cFrame = c; } else { cFrame = (int)sprite.size()-1; } }
		void nextFrame() { int c = cFrame + 1; if (c<(int)sprite.size()) { cFrame = c; } else { cFrame = 0; } }
		void firstFrame() { cFrame = 0; }
		void lastFrame() { cFrame = (int)sprite.size()-1; }
		/*********************
		* EFFECTS
		**********************/
		void setMlBlinking (int ml) { cyclesBlinking = Converter::GetInstance()->ml2cycles(ml); }
		void setActiveBlinking (bool b) { activeBlinking = b; }
		void setBlinking (int b) { blinking = b; }
		int getBlinking() { return blinking; }
		void setFadeIn (int ml, int alphaBegin) { cyclesFadeOut = 0; cyclesFadeInTotal = Converter::GetInstance()->ml2cycles(ml); cyclesFadeIn = Converter::GetInstance()->ml2cycles(ml); cyclesFadeOut = 0; alpha = alphaBegin; }
		void setFadeIn (int ml) { setFadeIn (ml, 0); }
		int getFadeIn() { return cyclesFadeIn; }
		void setFadeOut (int ml, int alphaEnd) { cyclesFadeIn = 0; cyclesFadeOutTotal = Converter::GetInstance()->ml2cycles(ml); cyclesFadeOut = Converter::GetInstance()->ml2cycles(ml); cyclesFadeIn = 0; alpha = alphaEnd; }
		void setFadeOut (int ml) { setFadeOut (ml, 255); }
		int getFadeOut() { return cyclesFadeOut; }
		//void setCortinilla (int c) { maxCortinilla = c; cortinilla = c; }
		//int getCortinilla() { return cortinilla; }
		void setAlpha (int a) { alpha = a; };
		void addAlpha (int a) { alpha+=a; };
		void removeAlpha () { alpha = 255; };
		int getAlpha () { return alpha; };
		/*********************
		* LIMITS
		**********************/
		// límites del elemento en la pantalla
		// se utilizan para saber cuando un elemento tiene que ser descargado al salir de la pantalla
		int getLimitTop () { return (-getHeight() * 2) -5; }
		int getLimitBottom ();
		int getLimitRight ();
		int getLimitLeft () { return -getWidth() * 2 -5; }
		bool outLimitScreen ();
		/*********************
		* ALIGN
		**********************/
		void setAlign (int a) { align = a; }
		void setVAlign (int a) { valign = a; }
		int getAlign () { return align; }
		int getVAlign () { return valign; }
		/*********************
		* SCALE
		**********************/
		void setCurrentScale (float s) { currentScaleX = s; currentScaleY = s; };
		void setCurrentScaleX (float s) { currentScaleX = s; };
		float getCurrentScaleX () { return currentScaleX; };
		void setCurrentScaleY (float s) { currentScaleY = s; };
		float getCurrentScaleY () { return currentScaleY; };
		void addCurrentScale (float s) { currentScaleX += s; currentScaleY += s; };
		void addCurrentScaleX (float s) { currentScaleX += s; };
		void addCurrentScaleY (float s) { currentScaleY += s; };
		
		void setScale (float w, float h);
		void setScaleW (float w) { float h = getHeightOriginal()*w/getWidthOriginal(); setScale(w, h); }
		void setScaleH (float h) { float w = getWidthOriginal()*h/getHeightOriginal(); setScale(w, h); }
		
		// movements
		void removeScale() { canScale = false; setCurrentScale(1); typeScale = NO_SCALE; }
		void setScaleGL (float s, int mlRoute) { setScale(getWidthOriginal()*s, getHeightOriginal()*s, mlRoute); }
		void setScale (float w, float h, int mlRoute);
		void setScaleW (float w, int mlRoute) { float h = getHeightOriginal()*w/getWidthOriginal(); setScale(w, h, mlRoute); }
		void setScaleH (float h, int mlRoute) { float w = getWidthOriginal()*h/getHeightOriginal(); setScale(w, h, mlRoute); }
		void setScaleSmooth (float w, float h);
		void setScaleSmoothW (float w) { float h = getHeightOriginal()*w/getWidthOriginal(); setScaleSmooth(w, h); }
		void setScaleSmoothH (float h) { float w = getWidthOriginal()*h/getHeightOriginal(); setScaleSmooth(w, h); }
		void setScaleFlexible (float w, float h);
		void setScaleFlexibleW (float w) { float h = getHeightOriginal()*w/getWidthOriginal(); setScaleFlexible(w, h); }
		void setScaleFlexibleH (float h) { float w = getWidthOriginal()*h/getHeightOriginal(); setScaleFlexible(w, h); }
		/*********************
		* MOVEMENTS
		**********************/
		bool getIsMovement() { return isMovement; }
		void removeTypeMovement () { typeMovement = NO_MOVEMENT; }
		void setTypeMovement (int c) { typeMovement = c; }
		int getTypeMovement () { return typeMovement; }
		void setDPolarCos (float c) { polarCos = c; }
		void setDPolarSen (float s) { polarSen = s; }
		void setDPolarDistance (float d) { polarDistance = d; }
		float getDPolarCos () { return polarCos; }
		float getDPolarSen () { return polarSen; }
		float getDPolarDistance () { return polarDistance; }
		float getCountCyclesMovementNormal () { return countCyclesMovementNormal; }
		float getNCyclesMovementNormal () { return nCyclesMovementNormal; }
		// normal
		void setMovementNormal (float x, float y, int ml);
		void setMovementNormalX (float x, int ml) { setMovementNormal(x, getYWithoutDisplacementByGroups(), ml); }
		void setMovementNormalY (float y, int ml) { setMovementNormal(getXWithoutDisplacementByGroups(), y, ml); }
		// smooth
		void setMovementSmooth (float x, float y) { posXNew = x; posYNew = y; typeMovement = MOVEMENT_SMOOTH; }
		void setMovementSmoothX (float x) { setMovementSmooth(x, getYWithoutDisplacementByGroups()); }
		void setMovementSmoothY (float y) { setMovementSmooth(getXWithoutDisplacementByGroups(), y); }
		// flexible
		void setMovementFlexible (float x, float y) { xs= 0.0f; ys= 0.0f; posXNew = x; posYNew = y; typeMovement = MOVEMENT_FLEXIBLE; }
		void setMovementFlexibleX (float x) { setMovementFlexible(x, getYWithoutDisplacementByGroups()); }
		void setMovementFlexibleY (float y) { setMovementFlexible(getXWithoutDisplacementByGroups(), y); }
		// desplazamiento
		void setDX (int x) { dx = x; }
		void setDY (int y) { dy = y; }
		float getDX () { return dx; }
		float getDY () { return dy; }
		
		void addDX () { posX += dx; }
		void addDY () { posY += dy; }
		/*********************
		* POSITION
		**********************/
		Bounds getBounds();
		Position getCenterPosition();
		void setX (float x) { oldX = posX; posX = x; }
		void setY (float y) { oldY = posY; posY = y; }
		void setXY (float x, float y) { setX(x); setY(y); }
		void addX (float x) { oldX = posX; posX += x; }
		void addY (float y) { oldY = posY; posY += y; }
		void addXY (float x, float y) { addX(x); addY(y); }
		float getOldX () { return oldX; }
		float getOldY () { return oldY; }
		float getDisplacementInXByGroups ();
		float getDisplacementInYByGroups ();
		float getXWithoutDisplacementByGroups () { return posX; }
		float getYWithoutDisplacementByGroups () { return posY; }
		float getX ();
		float getY ();
		float getValueXPlusGroups (float x);
		float getValueYPlusGroups (float y);
		void setTypeElement (int te) { typeElement= te; }
		int getTypeElement () { return typeElement; }
		void move ();
		void transforms ();
		/*********************
		* ATRIBUTTES
		**********************/	
		void setPerspective(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4);
		void setPerspectiveRelative(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4);
		void setVelocitySmooth (int t);
		void setVelocityFlexible (int t);
		int getWidth () { return sprite[getCurrentFrame()]->w * currentScaleX; }
		int getHeight () { return sprite[getCurrentFrame()]->h * currentScaleY; }
		int getWidthOriginal () { return sprite[getCurrentFrame()]->w; }
		int getHeightOriginal () { return sprite[getCurrentFrame()]->h; }
		void show () { visible = true; }
		void hide () { visible = false; }
		bool isVisible () { return visible; }
		void setFlip (bool f) { flip = f; }
		bool getFlip () { return flip; }
		void swapFlip () { flip = !flip; }
		void setFlop (bool f) { flop = f; }
		bool getFlop () { return flop; }
		void swapFlop () { flop = !flop; }
		void setToDoAllEffects (bool e) { toDoAllEffects = e; }
		bool getToDoAllEffects () { return toDoAllEffects; }
		void setGroup(Group *g) { group = g; }
		void removeGroup() { group = NULL; }
		Group* getGroup() { return group; }
		void setGroupScene(GroupScene *g) { groupScene = g; }
		void removeGroupScene() { groupScene = NULL; }
		GroupScene* getGroupScene() { return groupScene; }
		/*********************
		* SURFACES
		**********************/
		void setIndexZ (int z) { indexz = z; }
		int getIndexZ () { return indexz; }
		void draw();
		void paintSprite();
		void unLoad ();
	};
	
	class GroupScene;
	
	class Group {
		
	protected:
		vector<Element*> elements;
		vector<Group*> groups;
		float posX, posY;
		float oldX, oldY;
		GroupScene *groupScene;
		Group *group;
	
		int cycle;
	
		// flexible
		float xs, ys;
		// direccion
		float dx, dy; 
		// movimiento 
		float polarCos, polarSen, polarDistance; // direction polar coord
		float polarEndX, polarEndY;
		int nCyclesMovementNormal, countCyclesMovementNormal;
		int dirX, dirY;
		// por posicion
		float posXNew, posYNew; // direccion por posicion
	
		int typeMovement;
		bool isMovement;
	
		int alpha; // factor alpha aplicado al elemento
		int cyclesFadeIn, cyclesFadeInTotal;
		int cyclesFadeOut, cyclesFadeOutTotal;
		
		int blinking, stateBlinking; // variables de control de parpadeo
		int cyclesBlinking;
		
		// factors
		
		float flexibleData0, flexibleData1;
		int smoothData;
	
	public:
		Group ();
		void addElement(Element *el) { elements.push_back(el); el->setGroup(this); }
		void addGroup(Group *gr) { groups.push_back(gr); gr->setGroup(this); }
		void setCurrentScale(float s);
		
		void setX(float x) { oldX = posX; posX = x; }
		void setY(float y) { oldY = posY; posY = y; }
		void setXY(float x, float y) { setX(x); setY(y); }
		void addX(float x) { oldX = posX; posX += x; }
		void addY(float y) { oldY = posY; posY += y; }
		void addXY(float x, float y) { addX(x); addY(y); }
		float getX();
		float getY();
		float getXWithoutDisplacementByGroups () { return posX; }
		float getYWithoutDisplacementByGroups () { return posY; }
		
		void setGroup(Group *g) { group = g; }
		void removeGroup() { group = NULL; }
		Group* getGroup() { return group; }
		void setGroupScene(GroupScene *g) { groupScene = g; }
		void removeGroupScene() { groupScene = NULL; }
		GroupScene* getGroupScene() { return groupScene; }
		
		/*********************
		* EFFECTS
		**********************/
		void setMlBlinking (int ml) { cyclesBlinking = Converter::GetInstance()->ml2cycles(ml); }
		void setBlinking (int b) { blinking = b; }
		int getBlinking() { return blinking; }
		void setFadeIn (int ml) { cyclesFadeInTotal = Converter::GetInstance()->ml2cycles(ml); cyclesFadeIn = Converter::GetInstance()->ml2cycles(ml); cyclesFadeOut = 0; alpha = 0; }
		int getFadeIn() { return cyclesFadeIn; }
		void setFadeOut (int ml) { cyclesFadeOutTotal = Converter::GetInstance()->ml2cycles(ml); cyclesFadeOut = Converter::GetInstance()->ml2cycles(ml); cyclesFadeIn = 0; alpha = 255; }
		int getFadeOut() { return cyclesFadeOut; }
		void setAlpha (int a) { alpha = a; todoAlpha (); };
		void addAlpha (int a) { alpha+=a; todoAlpha (); };
		void removeAlpha () { alpha = 255; todoAlpha (); };
		void todoAlpha ();
		int getAlpha () { return alpha; };
		
		/*********************
		* MOVEMENTS
		**********************/
		bool getIsMovement() { return isMovement; }
		void removeTypeMovement () { typeMovement = NO_MOVEMENT; }
		void setTypeMovement (int c) { typeMovement = c; }
		int getTypeMovement () { return typeMovement; }
		void setDPolarCos (float c) { polarCos = c; }
		void setDPolarSen (float s) { polarSen = s; }
		void setDPolarDistance (float d) { polarDistance = d; }
		float getDPolarCos () { return polarCos; }
		float getDPolarSen () { return polarSen; }
		float getDPolarDistance () { return polarDistance; }
		float getCountCyclesMovementNormal () { return countCyclesMovementNormal; }
		float getNCyclesMovementNormal () { return nCyclesMovementNormal; }
		// normal
		void setMovementNormal (float x, float y, int ml);
		void setMovementNormalX (float x, int ml) { setMovementNormal(x, posY, ml); }
		void setMovementNormalY (float y, int ml) { setMovementNormal(posX, y, ml); }
		// smooth
		void setMovementSmooth (float x, float y) { posXNew = x; posYNew = y; typeMovement = MOVEMENT_SMOOTH; }
		void setMovementSmoothX (float x) { setMovementSmooth(x, posY); }
		void setMovementSmoothY (float y) { setMovementSmooth(posX, y); }
		// flexible
		void setMovementFlexible (float x, float y) { xs= 0.0f; ys= 0.0f; posXNew = x; posYNew = y; typeMovement = MOVEMENT_FLEXIBLE; }
		void setMovementFlexibleX (float x) { setMovementFlexible(x, posY); }
		void setMovementFlexibleY (float y) { setMovementFlexible(posX, y); }
		// desplazamiento
		void setDX (int x) { dx = x; }
		void setDY (int y) { dy = y; }
		float getDX () { return dx; }
		float getDY () { return dy; }
		
		void addDX () { posX += dx; }
		void addDY () { posY += dy; }
		
		void setVelocitySmooth (int t);
		void setVelocityFlexible (int t);
		
		void move();
		void work();
		void draw();
		void unLoad();
		
	};
	
	class GroupScene : public Group {
		
	public:
		GroupScene ();
		void addElement(Element *el) { elements.push_back(el); el->setGroupScene(this); }
		void addGroup(Group *gr) { groups.push_back(gr); gr->setGroupScene(this); }
	};
	
	typedef struct
	{
		int numberOfTimes;
		int animation;
	} NextAnimation;

	class AnimatedElement : public Element {
	
	private:
		vector<Animation> animations;
		int currentAnimation, defaultAnimation;
		vector<NextAnimation> nextsAnimations;
		int numberOfTimes;
		int countNumberOfTimes;
		
	public:
		AnimatedElement ();
		~AnimatedElement();
		
		int getCurrentFrame();
		int getNextFrame();
		/*********************
		* ANIMACION
		**********************/
		void addAnimation (Animation a);
		void removeAnimation (string name);
		bool setAnimation (string name) { return setAnimation (name, -1); }
		bool setAnimation (string name, int nt);
		bool setForceAnimation (string name) { return setForceAnimation (name, -1); }
		bool setForceAnimation (string name, int nt);
		bool setDefaultAnimation (string name);
		Animation* getAnimation ();
		Animation* getAnimation (string name);
		bool existAnimation (string name);
		
		void stop() { getAnimation ()->stop(); }
		void play() { getAnimation ()->play(); }
		void swapPlayStop() { getAnimation ()->swapPlayStop(); }
		void start() { getAnimation ()->start(); }
	
		void draw();
	
		void unLoad ();
	};
	
	class MarqueeElement : public AnimatedElement {
	
	private:
        string text;
        int nLetters;
		
	public:
		MarqueeElement ();
		~MarqueeElement();
		
		void setText(string font, string t, int nl);

	};

	class Element_AnimatedGroup : public Element {
	
	private:
		float offsetX, offsetY;
		
	public:
		Element_AnimatedGroup ();
		~Element_AnimatedGroup ();
		void setOffSetX(float x) { offsetX = x; addX(x); }
		void setOffSetY(float y) { offsetY = y; addY(y); }
		void setOffSetX() { addX(offsetX); }
		void setOffSetY() { addY(offsetY); }
		float getOffSetX() { return offsetX; }
		float getOffSetY() { return offsetY; }

	};
	
	class AnimatedGroup {
	
	private:
		int cols;
		int rows;
		int width;
		int height;
		int indexz;
		int cycles;
		
		vector<Element_AnimatedGroup*> elements;
		float posX, posY;
		
		bool reverse;
		
		bool isMovementNormal;
		bool isMovementSmooth;
		bool isMovementFlexible;		
		
		float xMovement, yMovement;
		int mlMovement;
		
		int cyclesChangeElement;
		int currentElement;
		
	public:
		AnimatedGroup ();
		~AnimatedGroup ();
		void setGrid (int c, int r) { cols = c; rows = r; }
		void organizeElements();
		void addElement(Element_AnimatedGroup *el);
		void setX(float x);
		void setY(float y);
		float getX();
		float getY();
		
		void setVelocitySmooth (int t);
		void setVelocityFlexible (int t);
		
	    void setReverse(bool r) { reverse = r; }
	    bool getReverse() { return reverse; }
	
		//void setSize();
		int getWidth () { return width; }
		int getHeight () { return height; }	
		
		void setIndexZ (int z) { indexz = z; }
		int getIndexZ () { return indexz; }
		void setText(string text, string font);
		
		void paintSprites();
		void draw();
		
		// normal
		void setMovementNormal(float x, float y, int ml, int waitMl);
		void setMovementNormalX(float x, int ml, int waitMl) { setMovementNormal(x, posY, ml, waitMl); }
		void setMovementNormalY(float y, int ml, int waitMl) { setMovementNormal(posX, y, ml, waitMl); }
		
		// smooth
		void setMovementSmooth (float x, float y, int waitMl);
		void setMovementSmoothX (float x, int waitMl) { setMovementSmooth(x, posY, waitMl); }
		void setMovementSmoothY (float y, int waitMl) { setMovementSmooth(posX, y, waitMl); }
		// flexible
		void setMovementFlexible (float x, float y, int waitMl);
		void setMovementFlexibleX (float x, int waitMl) { setMovementFlexible(x, posY, waitMl); }
		void setMovementFlexibleY (float y, int waitMl) { setMovementFlexible(posX, y, waitMl); }
		
		void unLoad();
	};
	
	class Button;


    class CoverFlow : public Group {
    	
    private:
    
    	vector<Element*> data;
    	int indexz;
	
    	Button *bLeft, *bRight;
		int index;
    	int beginItem;
    	int itemFadeOut;
    	int itemSeparate;
	
		int width;
		int widthItem;
    	
    	int separateGrid;
    	int itemsVisible;
    	int timeChangeItem;
    	int cursor;
    	
    	bool drawButtons;
    	
   	public:
        CoverFlow ();
		~CoverFlow ();
        
		void setIndexZ (int z) { indexz = z; }
		int getIndexZ () { return indexz; }
	
        //void add(Element* e) { e->addX((((int)data.size())*separateGrid)+(width/2)-(widthItem/2)); this->addElement(e); data.push_back(e); verifySensitiveButtons(); }
		void add(Element* e) { e->setAlign(ALIGN_CENTER); e->setVAlign(VALIGN_CENTER); this->addElement(e); data.push_back(e); verifySensitiveButtons(); }
        
		//void startPosition();
    	
		void MoveFirst() { cursor = 0; }
    	void MoveLast() { cursor = (int)data.size()-1; }
    	void MovePrevious() { cursor--; }
    	void MoveNext() { cursor++; }
    	bool isBOF() { return (cursor<0)?true:false; }
    	bool isEOF() { return (cursor>((int)data.size()-1))?true:false; }
    	Element* getData() { return data[cursor]; }
    	Element* getData(int i) { return data[i]; }
    	Element* getDataIndex() { return data[index]; }
        bool isVisible() { if ( (cursor>=firtsItem()) && (cursor<lastItem()) ) { return true; } else { return false; } }
        bool isVisible(int i) { if ( (i>=firtsItem()) && (i<lastItem()) ) { return true; } else { return false; } }
        int getNItems() { return (int)data.size(); }
        
	    void inicialize();
        
	    int firtsItem() { return beginItem; }
	    int lastItem();
        
        void startPosition();
        
		void setIndex(int i);
        int getIndex() { return index; }
		
        void setWidth(int w) { width = w; }
        int getWidth() { return width; }
		
		void setWidthItem(int w) { widthItem = w; }
        int getWidthItem() { return widthItem; }
		
        void setSeparateGrid(int s) { separateGrid = s; }
        int getSeparateGrid() { return separateGrid; }
        
        void setTimeChangeItem(int t) { timeChangeItem = t; }
        int getTimeChangeItem() { return timeChangeItem; }
        
        void setItemsVisible(int i) { itemsVisible = i; }
        int getItemsVisible() { return itemsVisible; }

        void setButtons(Button *buttom_up, Button *buttom_down, int separateX, int separateY);
        
    	void previousIndex() { if (index>0) setIndex(index-1); }
    	void nextIndex() { if (index<(int)data.size()-1) setIndex(index+1); }
    	
    	void verifySensitiveButtons();
    	void verifyClickButtons();
    	void onOver();
    	
    	void draw();
    	
    	void unLoad();
    	
    };

    class ListImage : public Group {
    	
    private:
    
    	vector<Button*> data;
		int indexz;
		int cursor;
	
		int rows, cols;
	
		int rowBeginObjects;
	    
    	Button *bUp, *bDown;
	
		Element *boxImage;
		bool drawBoxImage;
    	
    	int separateGrid;
    	
    	bool drawButtons;
    	
    	int currentCategory;    	
    	vector<string> categories;
    	
   	public:
        ListImage (int r, int c);
		~ListImage ();
	
		void setIndexZ (int z) { indexz = z; }
		int getIndexZ () { return indexz; }
		
		void setBoxImage (Element *box);
		
		int nTotalRowObjects();
        
        void addCategory(string c) { categories.push_back(c); }
        
        void setCategory(string c);
        
        void orderElements();
        
        void add(Button* b);
			
		void verifyObjectsToShow();
               		
    	void MoveFirst() { cursor = 0; }
    	void MoveLast() { cursor = (int)data.size()-1; }
    	void MovePrevious() { cursor--; }
    	void MoveNext() { cursor++; }
    	bool isBOF() { return (cursor<0)?true:false; }
    	bool isEOF() { return (cursor>((int)data.size()-1))?true:false; }
    	Button* getData() { return data[cursor]; }
    	Button* getData(int i) { return data[i]; }
        //bool isVisible() { if ( (cursor>=firtsItem()) && (cursor<lastItem()) ) { return true; } else { return false; } }
        //bool isVisible(int i) { if ( (i>=firtsItem()) && (i<lastItem()) ) { return true; } else { return false; } }

	    void inicialize();
        
	    //int firtsItem() { return beginItem; }
	    //int lastItem() { if (beginItem+itemsVisible<(int)data.size()) { return beginItem+itemsVisible; } else { return (int)data.size(); } }
        
        void setSeparateGrid(int s) { separateGrid = s; }
        int getSeparateGrid() { return separateGrid; }
        
        void setButtons(Button *buttom_up, Button *buttom_down, int xSeparate, int ySeparate);
        
    	void downItems();
    	void upItems();
    	
    	void verifyClickButtons();
    	void onOver();
    	
    	void draw();
    	
		void clear();
    	void unLoad();
    	
    };
	
    class ListView : public Group {
    	
    private:
    
    	vector<Group*> data;
		int indexz;
	
		bool todoMovement; // In first and last element
    
    	Button *bUp, *bDown;
    	int beginItem;
    	int itemFadeOut;
    	int itemSeparate;
    	
    	int separateGrid;
    	int itemsVisible;
    	int timeChangeItem;
    	int cursor;
    	
    	bool drawButtons;
    	
   	public:
        ListView ();
		~ListView ();
	
		void setIndexZ (int z) { indexz = z; }
		int getIndexZ () { return indexz; }
		
		void setBeginItem (int b);
		int getBeginItem () { return beginItem; }
        
        void add(Group* g) { g->addY(((int)data.size())*separateGrid); this->addGroup(g); data.push_back(g); verifySensitiveButtons(); }
               
		void setTodoMovement(bool m) { todoMovement = m; }
		
    	void MoveFirst() { cursor = 0; }
    	void MoveLast() { cursor = (int)data.size()-1; }
    	void MovePrevious() { cursor--; }
    	void MoveNext() { cursor++; }
    	bool isBOF() { return (cursor<0)?true:false; }
    	bool isEOF() { return (cursor>((int)data.size()-1))?true:false; }
    	Group* getData() { return data[cursor]; }
    	Group* getData(int i) { return data[i]; }
        bool isVisible() { if ( (cursor>=firtsItem()) && (cursor<lastItem()) ) { return true; } else { return false; } }
        bool isVisible(int i) { if ( (i>=firtsItem()) && (i<lastItem()) ) { return true; } else { return false; } }

		int getNItems() { return (int)data.size(); }
		
	    void inicialize();
        
	    int firtsItem() { return beginItem; }
	    int lastItem() { if (beginItem+itemsVisible<(int)data.size()) { return beginItem+itemsVisible; } else { return (int)data.size(); } }
        
        void setSeparateGrid(int s) { separateGrid = s; }
        int getSeparateGrid() { return separateGrid; }
        
        void setTimeChangeItem(int t) { timeChangeItem = t; }
        int getTimeChangeItem() { return timeChangeItem; }
        
        void setItemsVisible(int i) { itemsVisible = i; }
        int getItemsVisible() { return itemsVisible; }

        void setButtons(Button *buttom_up, Button *buttom_down, int xSeparate);
        
    	void downItems();
    	void upItems();
    	
    	void verifySensitiveButtons();
    	void verifyClickButtons();
    	void onOver();
    	
    	void draw();
    	
    	void unLoad();
    	
    };
	
	class Slide : public Element {
	
	private:
		int nextFrame;
		int degrees;
		int degreesByFrame;
		int degreesToDoChange;
		bool changingFrame;
		int cyclesNextFrame;
		int typeSlide;
		int mlFade;
	
		bool stopped;
		
	public:
		Slide ();
		~Slide ();
		void setCurrentFrame(int c);
		void setPreviousFrame() { if (getCurrentFrame() > 0) { setCurrentFrame(getCurrentFrame()-1); } else { setCurrentFrame(getFrames()-1); } }
		void setNextFrame() { if (getCurrentFrame() < getFrames()-1) { setCurrentFrame(getCurrentFrame()+1); } else { setCurrentFrame(0); } }
	
		void setDegreesByFrame(int d) { degreesByFrame = d; }
		int getDegreesByFrame() { return degreesByFrame; }
		
		void setDegreesToDoChange(int d) { degreesToDoChange = d; }
		int getDegreesToDoChange() { return degreesToDoChange; }
		
		void setTypeSlide(int t) { typeSlide = t; }
		int getTypeSlide() { return typeSlide; }
		
		void stop() { stopped = true; }
		void play() { stopped = false; }
		bool playing() { return stopped; }
				
		void setMlFade(int t) { mlFade = t; }
		int getMlFade() { return mlFade; }
		
		void setTimeNextFrame(int ml) { cyclesNextFrame = Converter::GetInstance()->ml2cycles(ml); }
	
		void draw();
	};
	
	class ChronometerElement : public Group {
    	
    private:
    	bool stopped;
	
    	vector<Group*> data;
		int indexz;
	
		string font;
		string name;
	
		Slide *minute0, *minute1, *second0, *second1;
		Element *points;
	
		int pastSeconds;
    	
   	public:
        ChronometerElement (string n, string f);
		~ChronometerElement ();
	
		void setSeconds(int s) { pastSeconds = s; setTime(); }
		void addSecond() { pastSeconds++; setTime(); }
		void setTime();
		int getSeconds() { return pastSeconds; }
		
		void stop() { stopped = true; }
		void play() { stopped = false; }
		void reset() { pastSeconds = 0; setTime(); }
	
		void setIndexZ (int z) { indexz = z; }
		int getIndexZ () { return indexz; }
		
		void draw();
		void unLoad();
	
	};
	
	class ElementDnD : public Element {
	
	protected:
		bool toDoDnd;
		bool isDnd;
		bool isRollOver;
		int mouseX, mouseY;
		
	public:
		ElementDnD ();
		~ElementDnD ();
		void setToDoDnd (bool b) { toDoDnd = b; }
		bool getToDoDnd () { return toDoDnd; }
		void startDrag ();
		void drop ();
		
		bool isOnMouseOver();
		void onOver();
		
	};

	class ProgressBar {
	private:
		int status, total, width, height;
		int posBarX, posBarY;
		Element *bar, *bg, *txt, *bg_bar;
		string text;
	
	public:
		ProgressBar (int tc, int w, int h, int r, int g, int b);
		~ProgressBar ();
	
		void setText (string font, string t);
		void setBg (string file);
		void setBgBar (string file);
		void setTotal (int t) { status = 0; total = t; }
		int getTotal() { return total; }
		void addStatus() { status++; }
		void draw ();
		void setPositionBar(int posX, int posY);
		void unLoad();
	};
	
	/*****************************
	**
	** CLASS FORM
	**
	******************************/
	
	class Button : public AnimatedElement {
	
	private:
		float scaleOut, scaleOn;
		bool sensitive;
		string textAlt;
		int alignAlt;
		int valignAlt;
		string soundOn, soundOut, soundClick;
		
	public:
		bool isRollOver;
	
		void setAlt(string text, int align, int valign) { textAlt = text; alignAlt = align; valignAlt = valign; }
		
		void setSoundOn(string s) { soundOn = s; }
		void setSoundOut(string s) { soundOut = s; }
		void setSoundClick(string s) { soundClick = s; }
		string getSoundClick() { return soundClick; }
		
		void setSensitive(bool s);
		bool getSensitive() { return sensitive; }
		
		Button ();
		~Button ();
		void setScales(float out, float on) { scaleOn = on; scaleOut = out; setCurrentScale(out); }
		bool isOnMouseOver();
		bool onOver();
		void imageOut(SDL_Surface* sfc);
		void imageOn(SDL_Surface* sfc);
		void imageOff(SDL_Surface* sfc);
		void (*OnClick)(Scene*, Button*);
	};
		
	class CheckButton : public Group {
	
	protected:
		
		bool sensitive;
		float scaleOut, scaleOn;
	
		string textAlt;
		int alignAlt;
		int valignAlt;
		string soundOn, soundOut, soundClick;
	
		map<string, string> parameters;
		Element *elBox, *elText;
		string text;
		float scaleText;
		bool active;
		int indexz;
		void changeFrame() { if (active) { elBox->setCurrentFrame(1); } else { elBox->setCurrentFrame(0); } }
			
	public:
        bool isRollOver;
	
		void setAlt(string text, int align, int valign) { textAlt = text; alignAlt = align; valignAlt = valign; }
		
		void setSoundOn(string s) { soundOn = s; }
		void setSoundOut(string s) { soundOut = s; }
		void setSoundClick(string s) { soundClick = s; }
		string getSoundClick() { return soundClick; }
           
		CheckButton ();
		CheckButton (string font, string t);
		~CheckButton ();
	
		void setScales(float out, float on) { scaleOn = on; scaleOut = out; setCurrentScale(out); }
		
		void setSensitive(bool s);
		bool getSensitive() { return sensitive; }
	
		/*********************
		* PARAMETERS
		**********************/
		void addParameter(string name, string value) { parameters[name] = value; }
		string getParameter(string name) { return parameters[name]; }
		
		/*********************
		* ATRIBUTTES
		**********************/
		void setScaleText (float s) { scaleText = s; if (text!="") elText->setCurrentScale(scaleText); }
		float getScaleText () { return scaleText; }
		void setActive (bool a) { active = a; changeFrame(); }
		bool getActive () { return active; }
		void swapActive () { active = !active; changeFrame(); }
		
		void setIndexZ (int z) { indexz = z; }
		int getIndexZ () { return indexz; }
		void setText (string font, string t);
		
		bool isOnMouseOver();
		bool onOver();
		void imageActive(SDL_Surface* sfc);
		void imageInactive(SDL_Surface* sfc);
		void (*OnClick)(Scene*, CheckButton*);
		void draw();
		void unLoad();
	};
	
	class RadioButton : public CheckButton {
	
	private:
		RadioButton *parent;
		
	public:
		RadioButton (RadioButton *p);
		RadioButton (RadioButton *p, string font, string t);
		~RadioButton ();
	
		RadioButton* getRadioButtonActive ();
		vector<RadioButton*> childs;
		void addChild(RadioButton *r);
		void setActive (bool a);
		void swapActive ();
		void unLoad();
	};
	
	class Entry : public Element {
	
	protected:
        Element *elmCursor;
        int posCursor;
        
		Entry *parent;
		bool active;
		bool nospace;
		bool nosigns;
		bool drawBox;
	
		int maxLetters;
	
		string text, label;
		string font, fontLabel;
	
		Button *bg;
		Element *select;
		Element *elmLabel;
		int width;
		int height;
		float padding_top;
		float padding_left;
		
		bool multiline;
		int totalRows;
		int currentRow;
		
		bool horizontal;
			
		/*void introKey(SDLKey key);*/
		void introText(string t);
		void updateText();
		
		
	public:
		Entry (Entry *p, int w, int h, float pt, float pl);
		~Entry ();
		
		void setPosCursor(int p);
		
		void setXCursor();
		void upLineCursor();
		void downLineCursor();
		void forwardCursor();
		void backCursor();
	
		void setLabel (string l);
		
		void setHorizontal (bool h);
		
		void setTotalRows (int t) { totalRows = t; }
		int getTotalRows () { return totalRows; }
		
		void setMultiline (bool m) { multiline = m; }
		bool getMultiline () { return multiline; }
		
		void setNoSigns (bool n) { nosigns = n; }
	
		void setNoSpace (bool n) { nospace = n; }
		void setMaxLetters (int m) { maxLetters = m; }
		int getMaxLetters () { return maxLetters; }
		
		void setPaddingTop (float pt) { padding_top = pt; }
		float getPaddingTop () { return padding_top; }
		void setPaddingLeft (float pl) { padding_left = pl; }
		float getPaddingLeft () { return padding_left; }
	
		Element* getBackground () { return bg; }
		
		void colorBoxNormal (int r, int g, int b, int border, int rb, int gb, int bb);
		void colorBoxOnOver (int r, int g, int b, int border, int rb, int gb, int bb);
		void colorBoxActived (int r, int g, int b, int border, int rb, int gb, int bb);
		
		void addFrameBoxNormal (SDL_Surface *sfc);
		void addFrameBoxOnOver (SDL_Surface *sfc);
		void addFrameBoxActived (SDL_Surface *sfc);
	
		void setFont (string f) { font = f; }
		void setFontLabel (string f) { fontLabel = f; }
		
		void insertText (string t);
		bool verifyKey (SDLKey k);
		void insertTextUnicode (SDLKey k, int i);
		void setText (string t);
		/*void setText(SDLKey key);*/
		string getText () { return text; }
		
		void setX (float x);
		void setY (float y);
		void setXY (float x, float y);
		
		Entry* getEntryActive ();
		Entry* getNextEntry ();
		vector<Entry*> childs;
		void addChild(Entry *e);
		void setActive (bool a);
		bool getActive () { return active; }
		void swapActive ();
		void setDrawBox (bool d) { drawBox = d; }
		bool getDrawBox () { return drawBox; }
		
		void onOver();		
		bool isOnMouseOver();
		void draw();
		void unLoad();
		
	};
		
	class SelectButton : public Group  {
	
	private:
		map<string, string> parameters;
		int minSeparateButtons;
		int greaterWidthObject;
		Element *elObjects;
		Button *elArrowLeft, *elArrowRight;
		bool arrows;
		int indexz;
		bool sensitive;
	
		string textAlt;
		int alignAlt;
		int valignAlt;
		string soundClick;
	
	public:
		bool isRollOver;
	
		SelectButton ();
		~SelectButton ();
	
		bool onOver();
	
		void setSensitive(bool s);
		bool getSensitive() { return sensitive; }
		
		void setAlt(string text, int align, int valign) { textAlt = text; alignAlt = align; valignAlt = valign; }
		
		void setSoundClick(string s) { soundClick = s; }
	
		/*********************
		* PARAMETERS
		**********************/
		void addParameter(string name, string value) { parameters[name] = value; }
		string getParameter(string name) { return parameters[name]; }
		
		/*********************
		* ATRIBUTTES
		**********************/
		
		void setIndexZ (int z) { indexz = z; }
		int getIndexZ () { return indexz; }
		
		void setMinSeparateButtons (int m) { minSeparateButtons = m; }
		int getMinSeparateButtons () { return minSeparateButtons; }
		
		void setArrows(SDL_Surface* left, SDL_Surface* right);
		
		void previousFrame() { elObjects->previousFrame(); }
		void nextFrame() { elObjects->nextFrame(); }
		void setFrame(int f) { elObjects->setCurrentFrame(f); }
		int getIndex() { return elObjects->getCurrentFrame(); }
		bool isOnMouseOver();
		int getOverBottom();
		void addObject(SDL_Surface* sfc);
		void (*OnClick)(Scene*, SelectButton*);
		void draw();
		void unLoad();
	};
	
	/*****************************
	**
	** CLASS PARTICLES
	**
	******************************/
	
	class ParticlesSystem;
		
	
	class Particle : public Element {
          
	private:
	
		ParticlesSystem *particlesSystem;
	
        int type;
        
		int cyclesLife, currentCyclesLife;
		
		float positionX, positionY, positionW, positionH;
		
		float displacementX, displacementY;
		
		bool changeColor;
		
		Color color;
		int currentColor;
		
		int state;
		int rot;
		float scale;
		
		int factorAlpha;
		
		bool returnToBeBorn;
	
	public:
		Particle (ParticlesSystem *ps);
		~Particle ();
	
		void setType(int t) { type = t; }
		int getType() { return type; }
		
		void setDisplacementX(float d) { displacementX = d; }
		void setDisplacementY(float d) { displacementY = d; }
		
		void setCurrentColor(int c) { currentColor = c; }
		void addCurrentColor() { currentColor++; if (currentColor>11) currentColor = 0; }
		int getCurrentColor() { return currentColor; }
		
		void setMlLife(int ml);
		
		void setCurrentCyclesLife(int cl) { currentCyclesLife = cl; }
		void addCurrentCyclesLife() { currentCyclesLife++; }
		int getCurrentCyclesLife() { return currentCyclesLife; }
		
		void setState(int st) { state = st; }
		int getState() { return state; }
		
		void setRotation(int r) { rot = r; }
		int getRotation() { return rot; }
		
		void setScale(int s) { scale = s; }
		float getScale() { return scale; }
		
		void setFactorAlpha(int fa) { factorAlpha = fa; }

		void setColor(int r, int g, int b) { color.r = r; color.g = g; color.b = b; setRGB(r,g,b); }		
		void setChangeColor(bool cl) { changeColor = cl; }
		bool getChangeColor() { return changeColor; }
		
		void setReturnToBeBorn(bool r) { returnToBeBorn = r; }
		bool getReturnToBeBorn() { return returnToBeBorn; }
		
		void setPositions(float px, float py, float pw, float ph);
		
		void die() { returnToBeBorn = false; state = PARTICLE_DYING; }
		
		void start();
		void change();
		
	};
	
	
	class ParticlesSystem	{
	private:
		Particle *particles[NPARTICLES];
		int nParticles;
		int indexz;
        int type;
		float positionX, positionY, positionW, positionH;
	
	public:
		VectorColors *colors;	
	
		ParticlesSystem ();
		ParticlesSystem (int np);
		~ParticlesSystem ();
		
		void setType(int t);
		int getType() { return type; }
		
		void start();
		bool isVisible();
		void setPositions(float px, float py, float pw, float ph);
		
		void setFrame(SDL_Surface* sfc);
		void setFrame(string fr);
		
		void setMlLife(int ml);
		void setMlLife(int ml1, int ml2);
		
		void setDisplacementX(float b, float e);
		void setDisplacementY(float b, float e);

		void setRotation(int r);
		
		void setScale(int s);
		
		void setCurrentScale(float s);
		
        void setFactorAlpha(float fa);
		void setChangeColor(bool cl);
		void setReturnToBeBorn(bool r);
		
		void setIndexZ (int z) { indexz = z; }
		int getIndexZ () { return indexz; }
		
		void draw();
		void unLoad();
		
	};
	
}

#endif /* ELEMENTS_H_ */
