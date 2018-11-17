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
 #include "cursor.h"

namespace Martian {
	 
	 Cursor* Cursor::instance = NULL;
	 
	/*****************************
	**
	** CLASE Cursor
	**
	******************************/	

	
	Cursor::Cursor() {
        useImageCursor = false;
		showAltWhenFinishEffect = false;
		showAlt = false;
		waitingAlt = false;
		fontText = "";
        cursors = new AnimatedElement();
		
		alignAlt = ALIGN_LEFT;
		posAlt = VALIGN_BOTTOM;
		
		paddingX = 5;
		paddingY = 30;
		sizeBorder = 1;
		
		mlWaitingAlt = 500;
		
		scaleAlt = 1.0;
		
		rAltText = 255;
		gAltText = 255;
		bAltText = 255;
		rAltBg = 0;
		gAltBg = 0;
		bAltBg = 0;
		aAltBg = 180;
		rAltBorder = 255;
		gAltBorder = 255;
		bAltBorder = 255;
		
		grpAlt = new Group();
		
		textAlt = new Element();
		textAlt->addFrameSurface(Primitives::GetInstance()->rectangle(1, 1, 0, 0, 0));
		textAlt->showBorder();
		
		bgAlt = new Element();
		bgAlt->addFrameSurface(Primitives::GetInstance()->rectangle(1, 1, 0, 0, 0));
		bgAlt->setXY(-4,-4);
		
		grpAlt->addElement(textAlt);
		grpAlt->addElement(bgAlt);
		
	}
	
    Cursor* Cursor::GetInstance () {
    	if ( instance == NULL ) {
    		instance = new Cursor();
    	}
    	return instance;	
    }
	
	void Cursor::showText() {
		
		if (waitingAlt) {
			bool todo = false;
			
			if ( Chronometer::GetInstance()->verifyTime("waiting_alt", mlWaitingAlt) ) {
				todo = true;
				waitingAlt = false;
				Chronometer::GetInstance()->removeTime("waiting_alt");
			}
			
			if (todo) {
				textAlt->setCurrentScale(1.0);
				
				showAlt = true;
				textAlt->changeFrameText(0, fontText, text, ALIGN_LEFT);
				textAlt->createBorder(rAltBorder, bAltBorder, gAltBorder, sizeBorder, 5);
				bgAlt->changeFrameSurface(0, Primitives::GetInstance()->rectangle(textAlt->getWidth()+8, textAlt->getHeight()+8, rAltBg, bAltBg, gAltBg));
				bgAlt->setAlpha(aAltBg);
				
				textAlt->setCurrentScale(0.0);
				textAlt->setScaleGL(scaleAlt, 150);
				bgAlt->setCurrentScale(0.0);
				bgAlt->setScaleGL(scaleAlt, 150);
				
				int mouse_x, mouse_y;
				SDL_PumpEvents();
				SDL_GetMouseState(&mouse_x, &mouse_y);
				
				float dx = 0;
				float dy = 0;
				switch (alignAlt) {
					case ALIGN_CENTER:
						dx = -(bgAlt->getWidthOriginal()*scaleAlt)/2;
					break;
					case ALIGN_RIGHT:
						dx = -bgAlt->getWidthOriginal()*scaleAlt;
					break;
				}
				switch (posAlt) {
					case VALIGN_TOP:
						dy = -paddingY - (bgAlt->getHeightOriginal()*scaleAlt);
					break;
				}
				
				grpAlt->setXY(mouse_x+paddingX+dx, mouse_y+paddingY+dy);
			}
			
		}
		
	}
	
	void Cursor::showText(string t, int align, int pos) {
		forceHideText();
		text = t;
		alignAlt = align;
		posAlt = pos;
		waitingAlt = true;
		Chronometer::GetInstance()->setTime("waiting_alt");
	}
	
	void Cursor::hideText() {
		showAltWhenFinishEffect = false;
		waitingAlt = false;
		textAlt->setScaleGL(0.0, 100);
		bgAlt->setScaleGL(0.0, 100);
	}
	
	void Cursor::hideText(string t) {
		if (text == t) {
			hideText();
		}
	}
    
    void Cursor::setCursor(string name) { 
         cursors->setForceAnimation(name); 
    }
    
	void Cursor::addCursor(string name, string file) {
        cursors->addFrameFileFromData(file);
        Animation a;
        a.setName(name);
        a.addFrame(cursors->getFrames()-1);
        cursors->addAnimation(a);
    }
    
	void Cursor::addAnimatedCursor(string name, string file, string ext, int nFrames) {
        int beginFrame = cursors->getFrames()-1;
        cursors->addRangeFramesFromData(file, ext, 0, nFrames-1);
        Animation a;
        a.addRangeFrame(beginFrame, beginFrame+nFrames-1, 1);
        cursors->addAnimation(a);
    }
    
	void Cursor::draw() {
		showText();
		if (showAlt) {
			if (showAltWhenFinishEffect) {
				if (textAlt->getCurrentScaleX()<=0.1) {
					showAlt = false;
					showAltWhenFinishEffect = false;
				}
			}
			
            bgAlt->draw();
			textAlt->draw();
		}
        if (useImageCursor) {
			int mouse_x, mouse_y;
			SDL_PumpEvents();
			SDL_GetMouseState(&mouse_x, &mouse_y);
            cursors->setXY(mouse_x, mouse_y);
            cursors->draw();
        }
    }
	
	void Cursor::unLoad() {
		delete textAlt;
		delete bgAlt;
		delete cursors;
    }

		
}
