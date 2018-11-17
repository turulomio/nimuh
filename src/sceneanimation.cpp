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
 
 
#include "sceneanimation.h"

namespace Martian {
	
	/*****************************
	**
	** CLASE ActionAnimation
	**
	******************************/	

	ActionAnimation::ActionAnimation() {
		cycle = 0;
		function = "";
		nameObjetive = "";
		cyclesRepeat = 0;
	}
	
	ActionAnimation::ActionAnimation(string f, int t) {
		cycle = Converter::GetInstance()->ml2cycles(t);
		function = f;
		nameObjetive = "";
		cyclesRepeat = 0;
	}
	
	bool ActionAnimation::existParameter(string name) { 
		map<string, string>::iterator it;
		for (it=parameters.begin(); it!=parameters.end(); ++it) {
			if ((*it).first == name) {
				return true;
			}
		}
		return false;
	}
	
	string ActionAnimation::getParameter(string name) { 
		if (existParameter(name))
			return parameters[name]; 
		return "";
	}
	
	/*****************************
	**
	** CLASE ObjectAnimation
	**
	******************************/	

	ObjectAnimation::ObjectAnimation() {
		type = "";
	}
	
	ObjectAnimation::~ObjectAnimation() {
		unLoad();
	}
	
	void ObjectAnimation::setType(string t) { 
		type = t; 
		if (type=="element") {
			elem = new AnimatedElement();
		}
		if (type=="button") {
			button = new Button();
		}
	}
	
	AnimatedElement* ObjectAnimation::getElement() { 
		if (type=="element") {
			return elem; 
		}
		if (type=="button") {
			return button; 
		}
		return NULL;
	}
		
	
	vector<ActionAnimation*> ObjectAnimation::verifyActions(int cycle) {
		vector<ActionAnimation*> acts;
		for (int i=0; i<(int)actions.size(); i++) {
			if (actions[i]->cycle == cycle) {
				acts.push_back(actions[i]);
			}
			if ( (actions[i]->cyclesRepeat>0) && (actions[i]->cycle < cycle) ) {
				if ((cycle-actions[i]->cycle) % actions[i]->cyclesRepeat == 0) {
					acts.push_back(actions[i]);
				}
			}
		}
		return acts;
	}
	
	void ObjectAnimation::unLoad() {
	
		if (type=="element") {
			delete elem; 
		}
		if (type=="button") {
			delete button;
		}
		
		actions.clear();
		actionsOnClick.clear();
		
	}	
	
	/*****************************
	**
	** CLASE SoundAnimation
	**
	******************************/	

	SoundAnimation::SoundAnimation() {
		name = "";
		category = "";
		file = "";
	}
	
	SoundAnimation::~SoundAnimation() {
	}
	
	vector<ActionAnimation*> SoundAnimation::verifyActions(int cycle) {
		vector<ActionAnimation*> acts;
		for (int i=0; i<(int)actions.size(); i++) {
			if (actions[i]->cycle == cycle) {
				acts.push_back(actions[i]);
			}
			if ( (actions[i]->cyclesRepeat>0) && (actions[i]->cycle < cycle) ) {
				if ((cycle-actions[i]->cycle) % actions[i]->cyclesRepeat == 0) {
					acts.push_back(actions[i]);
				}
			}
		}
		return acts;
	}
	
	/*****************************
	**
	** CLASE SCENEANIMATION
	**
	******************************/	

	
	SceneAnimation::SceneAnimation() : Scene () {
		statusScene = SCENEANIMATION_MAIN;
		nameSceneWhenScape = "quit";
		cycles = 0;
		drawStar = false;
		drawProgressBar = false;
	}
	
	SceneAnimation::~SceneAnimation() {
		Sounds::GetInstance()->unLoad();
		
		int i;
		for (i=0; i<(int)objectsanimation.size(); i++) {
			delete objectsanimation[i];
		}
		
		objectsanimation.clear();

		if (drawStar) {
			delete stars;
		}
		
		if (drawProgressBar) {
			delete pb;
		}
		
		isLoad = false;
	}
	
	string SceneAnimation::replace(string chain) {
		
		vector<string> v = Converter::GetInstance()->split(chain, "$");

		string out = "";
		
        for (int i=0; i<(int)v.size(); i++) {
            if ( (v[i]=="lang") || (v[i]=="lang$") ) {
				out += Language::GetInstance()->getLang();
			} else {
				out += v[i];
			}
        }
		
		return out;
		
	}
	
	
	ObjectAnimation* SceneAnimation::getObjectAnimation(string name) {
		for (int i=0; i<(int)objectsanimation.size(); i++) {
			if (objectsanimation[i]->getName() == name) {
				return objectsanimation[i];
			}
		}
		return NULL;
	}
	
	void SceneAnimation::addSoundAnimation(SoundAnimation *s) { 
		Sounds::GetInstance()->addSound(s->getName(), s->getCategory(), s->getFile());
		soundsanimation.push_back(s); 
	}
	
	SoundAnimation* SceneAnimation::getSoundAnimation(string name) {
		for (int i=0; i<(int)soundsanimation.size(); i++) {
			if (soundsanimation[i]->getName() == name) {
				return soundsanimation[i];
			}
		}
		return NULL;
	}
	
	void SceneAnimation::createStars(string f) {
		
		stars = new ParticlesSystem();
		stars->setFrame(getDirectory()+"/"+f);
		stars->setDisplacementX(0, 1);
		stars->setPositions(-200, 0, 1000, 600);
		stars->setType(TYPE_STARS);
		stars->start();
		
		drawStar = true;
		
	}
	
	void SceneAnimation::load() {
		
		initialize();
		
		statusScene = SCENEANIMATION_MAIN;
		
		cycles = 0;
		
		drawStar = false;
		
		showHideStar.clear();
				
		char tmp[128];
		sprintf(tmp, "%s/animation.xml", getDirectory().c_str());	

		parseXMLAnimation(tmp, this);

	}
	
	void SceneAnimation::makeAction_Sound(SoundAnimation *obj, ActionAnimation* act) {
		if (act->function == "play") {
			if (act->getParameter("para3")=="") {
				Sounds::GetInstance()->getSound(obj->getName())->play(atoi(act->getParameter("para1").c_str()), atoi(act->getParameter("para2").c_str()));
			} else {
				Sounds::GetInstance()->getSound(obj->getName())->play(atoi(act->getParameter("para1").c_str()), atoi(act->getParameter("para2").c_str()), atoi(act->getParameter("para3").c_str()));
			}
		}
		if (act->function == "stop") {
			if (act->getParameter("para1")=="") {
				Sounds::GetInstance()->getSound(obj->getName())->stop();
			} else {
				Sounds::GetInstance()->getSound(obj->getName())->stop(atoi(act->getParameter("para1").c_str()));
			}
		}
	}
	
	void SceneAnimation::makeAction_Object(ObjectAnimation *obj, ActionAnimation* act) {
		
		// show hide flip
		
		if (act->function == "show") {
			obj->getElement()->show();
		}
		
		if (act->function == "hide") {
			obj->getElement()->hide();
		}
		
		if (act->function == "showborder") {
			obj->getElement()->showBorder();
		}
		
		if (act->function == "hideborder") {
			obj->getElement()->hideBorder();
		}
		
		if (act->function == "showbackground") {
			obj->getElement()->showBackground();
		}
		
		if (act->function == "hidebackground") {
			obj->getElement()->hideBackground();
		}
		
		if (act->function == "setflip") {
			obj->getElement()->setFlip(atoi(act->getParameter("para1").c_str()));
		}
		
		if (act->function == "setflop") {
			obj->getElement()->setFlop(atoi(act->getParameter("para1").c_str()));
		}
		
		// animations
		
		if (act->function == "setanimation") {
			if (act->getParameter("para2")=="") {
				obj->getElement()->setAnimation( act->getParameter("para1").c_str() );
			} else {
				obj->getElement()->setAnimation( act->getParameter("para1").c_str(), atoi(act->getParameter("para2").c_str()) );
			}
		}
		
		if (act->function == "setforceanimation") {
			if (act->getParameter("para2")=="") {
				obj->getElement()->setForceAnimation( act->getParameter("para1").c_str() );
			} else {
				obj->getElement()->setForceAnimation( act->getParameter("para1").c_str(), atoi(act->getParameter("para2").c_str()) );
			}
		}
		
		if (act->function == "stop") {
			obj->getElement()->stop();
		}
		
		if (act->function == "play") {
			obj->getElement()->play();
		}
		
		if (act->function == "swapplaystop") {
			obj->getElement()->swapPlayStop();
		}
		
		if (act->function == "start") {
			obj->getElement()->start();
		}
		
		// alpha and fades
		
		if (act->function == "setfadein") {
			if (act->getParameter("para2")=="") {
				obj->getElement()->setFadeIn(atoi(act->getParameter("para1").c_str()));
			} else {
				obj->getElement()->setFadeIn(atoi(act->getParameter("para1").c_str()), atoi(act->getParameter("para2").c_str()));
			}
		}
		
		if (act->function == "setfadeout") {
			if (act->getParameter("para2")=="") {
				obj->getElement()->setFadeOut(atoi(act->getParameter("para1").c_str()));
			} else {
				obj->getElement()->setFadeOut(atoi(act->getParameter("para1").c_str()), atoi(act->getParameter("para2").c_str()));
			}
		}
		
		if (act->function == "setmlblinking") {
			obj->getElement()->setMlBlinking(atoi(act->getParameter("para1").c_str()));
		}
		
		if (act->function == "setblinking") {
			obj->getElement()->setBlinking(atoi(act->getParameter("para1").c_str()));
		}
		
		if (act->function == "setalpha") {
			obj->getElement()->setAlpha(atoi(act->getParameter("para1").c_str()));
		}
		
		if (act->function == "removealpha") {
			obj->getElement()->removeAlpha();
		}
		
		// rotation
		
		if (act->function == "setrot") {
			if (act->getParameter("para2")=="") {
				obj->getElement()->setRot( atof(act->getParameter("para1").c_str()) );
			} else {
				obj->getElement()->setRot( atof(act->getParameter("para1").c_str()),
					atof(act->getParameter("para2").c_str()), atof(act->getParameter("para3").c_str()),
					atof(act->getParameter("para4").c_str()) );
			}
		}
		
		if (act->function == "setrotationnormal") {
			if (act->getParameter("para3")=="") {
				obj->getElement()->setRotationNormal( atof(act->getParameter("para1").c_str()),
						atof(act->getParameter("para2").c_str()) );
			} else {
				obj->getElement()->setRotationNormal( atof(act->getParameter("para1").c_str()),
					atof(act->getParameter("para2").c_str()), 
					atof(act->getParameter("para3").c_str()) );
			}
		}
		
		if (act->function == "setrotationsmooth") {
			obj->getElement()->setRotationSmooth(atof(act->getParameter("para1").c_str()));
		}
		
		if (act->function == "setrotationflexible") {
			obj->getElement()->setRotationFlexible(atof(act->getParameter("para1").c_str()));
		}
		
		// scale
		
		if (act->function == "setcurrentscale") {
			obj->getElement()->setCurrentScale(atof(act->getParameter("para1").c_str()));
		}
		
		if (act->function == "setcurrentscalex") {
			obj->getElement()->setCurrentScaleX(atof(act->getParameter("para1").c_str()));
		}
		
		if (act->function == "setcurrentscaley") {
			obj->getElement()->setCurrentScaleY(atof(act->getParameter("para1").c_str()));
		}
		
		if (act->function == "addcurrentscale") {
			obj->getElement()->addCurrentScale(atof(act->getParameter("para1").c_str()));
		}
		
		if (act->function == "addcurrentscalex") {
			obj->getElement()->addCurrentScaleX(atof(act->getParameter("para1").c_str()));
		}
		
		if (act->function == "addcurrentscaley") {
			obj->getElement()->addCurrentScaleY(atof(act->getParameter("para1").c_str()));
		}
		
		if (act->function == "setscale") {
			obj->getElement()->setScale( atof(act->getParameter("para1").c_str()),
				atof(act->getParameter("para2").c_str()), 
				atoi(act->getParameter("para3").c_str()) );
		}
		
		if (act->function == "setscalew") {
			obj->getElement()->setScaleW( atof(act->getParameter("para1").c_str()),
				atoi(act->getParameter("para2").c_str()) );
		}
		
		if (act->function == "setscaleh") {
			obj->getElement()->setScaleH( atof(act->getParameter("para1").c_str()),
				atoi(act->getParameter("para2").c_str()) );
		}
		
		if (act->function == "setscalesmooth") {
			obj->getElement()->setScaleSmooth( atof(act->getParameter("para1").c_str()),
				atof(act->getParameter("para2").c_str()) );
		}
		
		if (act->function == "setscalesmoothw") {
			obj->getElement()->setScaleSmoothW( atof(act->getParameter("para1").c_str()) );
		}
		
		if (act->function == "setscalesmoothh") {
			obj->getElement()->setScaleSmoothH( atof(act->getParameter("para1").c_str()) );
		}
		
		if (act->function == "setscaleflexible") {
			obj->getElement()->setScaleFlexible( atof(act->getParameter("para1").c_str()),
				atof(act->getParameter("para2").c_str()) );
		}
		
		if (act->function == "setscaleflexiblew") {
			obj->getElement()->setScaleFlexibleW( atof(act->getParameter("para1").c_str()) );
		}
		
		if (act->function == "setscaleflexibleh") {
			obj->getElement()->setScaleFlexibleH( atof(act->getParameter("para1").c_str()) );
		}
		
		// movement
		
		if (act->function == "setmovementnormal") {
			obj->getElement()->setMovementNormal( atof(act->getParameter("para1").c_str()),
				atof(act->getParameter("para2").c_str()), 
				atoi(act->getParameter("para3").c_str()) );
		}
		
		if (act->function == "setmovementnormalx") {
			obj->getElement()->setMovementNormalX( atof(act->getParameter("para1").c_str()),
				atoi(act->getParameter("para2").c_str()) );
		}
		
		if (act->function == "setmovementnormaly") {
			obj->getElement()->setMovementNormalY( atof(act->getParameter("para1").c_str()),
				atoi(act->getParameter("para2").c_str()) );
		}
		
		if (act->function == "setmovementsmooth") {
			obj->getElement()->setMovementSmooth( atof(act->getParameter("para1").c_str()),
				atof(act->getParameter("para2").c_str()));
		}
		
		if (act->function == "setmovementsmoothx") {
			obj->getElement()->setMovementSmoothX( atof(act->getParameter("para1").c_str()) );
		}
		
		if (act->function == "setmovementsmoothy") {
			obj->getElement()->setMovementSmoothY( atof(act->getParameter("para1").c_str()) );
		}
		
		if (act->function == "setmovementflexible") {
			obj->getElement()->setMovementFlexible( atof(act->getParameter("para1").c_str()),
				atof(act->getParameter("para2").c_str()));
		}
		
		if (act->function == "setmovementflexiblex") {
			obj->getElement()->setMovementFlexibleX( atof(act->getParameter("para1").c_str()) );
		}
		
		if (act->function == "setmovementflexibley") {
			obj->getElement()->setMovementFlexibleY( atof(act->getParameter("para1").c_str()) );
		}
		
		// position
		
		if (act->function == "setxy") {
			obj->getElement()->setXY( atof(act->getParameter("para1").c_str()),
				atof(act->getParameter("para2").c_str()) );
		}
		
		if (act->function == "setx") {
			obj->getElement()->setX( atof(act->getParameter("para1").c_str()) );
		}
		
		if (act->function == "sety") {
			obj->getElement()->setY( atof(act->getParameter("para1").c_str()) );
		}
		
		if (act->function == "addxy") {
			obj->getElement()->addXY( atof(act->getParameter("para1").c_str()),
				atof(act->getParameter("para2").c_str()) );
		}
		
		if (act->function == "addx") {
			obj->getElement()->addX( atof(act->getParameter("para1").c_str()) );
		}
		
		if (act->function == "addy") {
			obj->getElement()->addY( atof(act->getParameter("para1").c_str()) );
		}
		
		// scene
		
		if (act->function == "setscene") {
			if (act->getParameter("para1")=="nextscene") {
				setNextScene(nameSceneWhenScape);
			} else {
				setNextScene(act->getParameter("para1"));
			}
			setQuit(true);
		}
		
		if (act->function == "gotoscene") {
			string scene="";
			if (act->getParameter("para1")=="nextscene") {
				scene = nameSceneWhenScape;
			} else {
				scene = act->getParameter("para1");
			}
			if (act->getParameter("para2")=="") {
				goToScene(scene);
			} else {
				goToScene(scene, atoi(act->getParameter("para2").c_str()), SCENE_TRANSITION_FADEOUT);
			}
		}
		
	}
	
	void SceneAnimation::drawSceneMain () {
	
		
		verifyOverElements_Main();
		
		for (int i=0; i<(int)soundsanimation.size(); i++) {
			
			if ((int)soundsanimation[i]->verifyActions(cycles).size() > 0) {
				for (int j=0; j<(int)soundsanimation[i]->verifyActions(cycles).size(); j++) {
					makeAction_Sound(soundsanimation[i], soundsanimation[i]->verifyActions(cycles)[j]);
				}
			}

		}
		for (int i=0; i<(int)showHideStar.size(); i++) {
			if (cycles == showHideStar[i].cycle) {
				if (showHideStar[i].type == "show") {
					drawStar = true;
				}
				if (showHideStar[i].type == "hide") {
					drawStar = false;
				}
			}
		}
		if (drawStar) {
			stars->draw();
		}
		
		for (int i=0; i<MAX_INDEXZ; i++) {
			drawSceneMainByIndexZ(i);
		}
		cycles++;
		
	}
	
	void SceneAnimation::drawSceneMainByIndexZ(int z) {
		int i;

		for (i=0; i<(int)objectsanimation.size(); i++) {
			if (objectsanimation[i]->getElement()->getIndexZ()==z) {
				if ((int)objectsanimation[i]->verifyActions(cycles).size() > 0) {
					for (int j=0; j<(int)objectsanimation[i]->verifyActions(cycles).size(); j++) {
						makeAction_Object(objectsanimation[i], objectsanimation[i]->verifyActions(cycles)[j]);
					}
				}
				objectsanimation[i]->getElement()->draw();
			}
		}
	}	
	
	void SceneAnimation::verifyOverElements_Main() {
		int i;
		for (i=0; i<(int)objectsanimation.size(); i++) {
			if (objectsanimation[i]->getType()=="button") {
				Button *b = (Button*)objectsanimation[i]->getElement();
				b->onOver();
			}
		}
	}	
	
	void SceneAnimation::verifyClickElements_Main() {
		int i, j;
		for (i=0; i<(int)objectsanimation.size(); i++) {
			if (objectsanimation[i]->getType()=="button") {
				Button *b = (Button*)objectsanimation[i]->getElement();
				if (b->isOnMouseOver()) {
					for (j=0; j<(int)objectsanimation[i]->actionsOnClick.size(); j++) {
						if (objectsanimation[i]->actionsOnClick[j]->nameObjetive!="") {
							makeAction_Object(getObjectAnimation(objectsanimation[i]->actionsOnClick[j]->nameObjetive), objectsanimation[i]->actionsOnClick[j]);
						} else {
							makeAction_Object(objectsanimation[i], objectsanimation[i]->actionsOnClick[j]);
						}
					}
				}	
			}
		}
	}
	
	bool SceneAnimation::drawScene() {
		
		glClear(GL_COLOR_BUFFER_BIT); // | GL_DEPTH_BUFFER_BIT);
		glLoadIdentity();
	
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		
		drawCommonsScene ();
		
		switch(statusScene) {
		
			case SCENEANIMATION_MAIN:
		
				drawSceneMain();
			
				// Comprobando teclas para opciones			
				{ SDL_Event event;
					while ( SDL_PollEvent(&event) ) {
						if ( event.type == SDL_QUIT ) {
							setNextScene("quit");
							return true;
						}
						
						if ( event.type == SDL_KEYDOWN ) {
							if ( event.key.keysym.sym == SDLK_ESCAPE ) {
								setNextScene(nameSceneWhenScape);
								return true;
							}
						}
						
						if ( event.type == SDL_MOUSEBUTTONDOWN ) {
							if ( ( event.button.button == SDL_BUTTON_LEFT ) ) {
								verifyClickElements_Main();
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
	
	void SceneAnimation::unLoad() {
	
		unLoadCommons();
		
		Sounds::GetInstance()->unLoad();
		
		int i;
		for (i=0; i<(int)objectsanimation.size(); i++) {
			delete objectsanimation[i];
		}
		
		objectsanimation.clear();

		if (drawStar) {
			delete stars;
		}
		
		if (drawProgressBar) {
			delete pb;
		}
		
		isLoad = false;
	
	}

	/*****************************
	**
	** XML
	**
	******************************/
	
	static void startXMLAnimation(void *userData, const char *el, const char **attr) {
		int i;
		AnimationXML* data = (AnimationXML*)userData;
		
		if (data->inElement) {
			if (strcmp(el, "frames") == 0) {
				data->inFrames = true;
			}
			
			if (strcmp(el, "animation") == 0) {
				data->inAnimation = true;
				Animation auxAnimation;
				auxAnimation.setCyclesBetweenFrames(4);
				for (i = 0; attr[i]; i += 2) {
					if (strcmp(attr[i], "name") == 0) {
						auxAnimation.setName(attr[i+1]);
						data->nameAnimation = attr[i+1];
					}
					if (strcmp(attr[i], "cycles-between-frames") == 0) {
						auxAnimation.setCyclesBetweenFrames(atoi(attr[i+1]));
					}
				}
				data->aux->getElement()->addAnimation(auxAnimation);
			}
			
			if (strcmp(el, "actions") == 0) {
				data->inAction = true;
			}
			
			if (strcmp(el, "actions-onclick") == 0) {
				data->inActionOnClick = true;
			}
			
			if (strcmp(el, "border") == 0) {
				data->todoBorder = true;
				for (i = 0; attr[i]; i += 2) {
					if (strcmp(attr[i], "r") == 0) {
						data->rBorder = atoi(attr[i+1]);
					}
					if (strcmp(attr[i], "g") == 0) {
						data->gBorder = atoi(attr[i+1]);
					}
					if (strcmp(attr[i], "b") == 0) {
						data->bBorder = atoi(attr[i+1]);
					}
					if (strcmp(attr[i], "size") == 0) {
						data->sizeBorder = atoi(attr[i+1]);
					}
					if (strcmp(attr[i], "padding") == 0) {
						data->paddingBorder = atoi(attr[i+1]);
					}
					if ( (strcmp(attr[i], "show") == 0) && (strcmp(attr[i+1], "true") == 0) ) {
						data->showBorder = true;
					}
				}
			}
			
			if (strcmp(el, "background") == 0) {
				data->todoBackground = true;
				for (i = 0; attr[i]; i += 2) {
					if (strcmp(attr[i], "r") == 0) {
						data->rBg = atoi(attr[i+1]);
					}
					if (strcmp(attr[i], "g") == 0) {
						data->gBg = atoi(attr[i+1]);
					}
					if (strcmp(attr[i], "b") == 0) {
						data->bBg = atoi(attr[i+1]);
					}
					if (strcmp(attr[i], "padding") == 0) {
						data->paddingBg = atoi(attr[i+1]);
					}
					if ( (strcmp(attr[i], "show") == 0) && (strcmp(attr[i+1], "true") == 0) ) {
						data->showBackground = true;
					}
				}
			}
			
			// nodo: FRAMES
			
			if (data->inFrames) {
				if (strcmp(el, "frame-file") == 0) {
					string file="";
					for (i = 0; attr[i]; i += 2) {
						if (strcmp(attr[i], "file") == 0) {
							file = data->scene->replace(attr[i+1]);
						}
					}
					char tmp[128];
					sprintf(tmp, "%s/%s", data->scene->getDirectory().c_str(), file.c_str());
					data->aux->getElement()->addFrameFile(tmp);			
				}
				if (strcmp(el, "frame-range-file") == 0) {
					string name="", ext="";
					int b = 0, e = 0;
					for (i = 0; attr[i]; i += 2) {
						if (strcmp(attr[i], "name") == 0) {
							name = data->scene->replace(attr[i+1]);
						}
						if (strcmp(attr[i], "extension") == 0) {
							ext = attr[i+1];
						}
						if (strcmp(attr[i], "begin") == 0) {
							b = atoi(attr[i+1]);
						}
						if (strcmp(attr[i], "end") == 0) {
							e = atoi(attr[i+1]);
						}
					}
					char tmp[128];
					sprintf(tmp, "%s/%s", data->scene->getDirectory().c_str(), name.c_str());
					data->aux->getElement()->addRangeFrames(tmp, ext, b, e);			
				}
				if (strcmp(el, "frame-text") == 0) {
					string text, font;
					int width = -1;
					int align = ALIGN_LEFT;
					for (i = 0; attr[i]; i += 2) {
						if (strcmp(attr[i], "text") == 0) {
							text = attr[i+1];
						}
						if (strcmp(attr[i], "font") == 0) {
							font = attr[i+1];
						}
						if (strcmp(attr[i], "width") == 0) {
							width = atoi(attr[i+1]);
						}
						if (strcmp(attr[i], "align") == 0) {
							if (strcmp(attr[i+1], "left") == 0) {
								align = ALIGN_LEFT;
							} else if (strcmp(attr[i+1], "center") == 0) {
								align = ALIGN_CENTER;
							} else if (strcmp(attr[i+1], "right") == 0) {
								align = ALIGN_RIGHT;
							}
						}
					}
					data->aux->getElement()->addFrameText(font, text, align);
				}
				if (strcmp(el, "frame-text-language") == 0) {
					string name, font;
					int width = -1;
					int align = ALIGN_LEFT;
					for (i = 0; attr[i]; i += 2) {
						if (strcmp(attr[i], "name") == 0) {
							name = attr[i+1];
						}
						if (strcmp(attr[i], "font") == 0) {
							font = attr[i+1];
						}
						if (strcmp(attr[i], "width") == 0) {
							width = atoi(attr[i+1]);
						}
						if (strcmp(attr[i], "align") == 0) {
							if (strcmp(attr[i+1], "left") == 0) {
								align = ALIGN_LEFT;
							} else if (strcmp(attr[i+1], "center") == 0) {
								align = ALIGN_CENTER;
							} else if (strcmp(attr[i+1], "right") == 0) {
								align = ALIGN_RIGHT;
							}
						}
					}
					data->aux->getElement()->addFrameText(font, Language::GetInstance()->getText(name), align, width);
				}
			}
			
			// nodo: ANIMATIONS
			
			if (data->inAnimation) {
				if (strcmp(el, "frame-animation") == 0) {
					int from = -1;
					int to = -1;
					int steps = 1;
					for (i = 0; attr[i]; i += 2) {
						if (strcmp(attr[i], "from") == 0) {
							from = atoi(attr[i+1]);
						}
						if (strcmp(attr[i], "to") == 0) {
							to = atoi(attr[i+1]);
						}
						if (strcmp(attr[i], "steps") == 0) {
							steps = atoi(attr[i+1]);
						}
					}
					if (from!=-1) {
						if (to!=-1) {
							data->aux->getElement()->getAnimation(data->nameAnimation)->addRangeFrame(from, to, steps);
						} else {
							data->aux->getElement()->getAnimation(data->nameAnimation)->addFrame(from);
						}
					}
					//data->aux->getElement()->addAnimation(auxAnimation);
				}
			}
			
			// nodo: ACTIONS
			
			if (data->inAction) {
				if (strcmp(el, "action") == 0) {
					ActionAnimation* auxAction = new ActionAnimation();
					for (i = 0; attr[i]; i += 2) {
						if (strcmp(attr[i], "function") == 0) {
							auxAction->function = attr[i+1];
						} else if (strcmp(attr[i], "time") == 0) {
							auxAction->cycle = Converter::GetInstance()->time2cycle(attr[i+1]);
						} else if (strcmp(attr[i], "time-repeat") == 0) {
							auxAction->cyclesRepeat = Converter::GetInstance()->time2cycle(attr[i+1]);
						} else {
							auxAction->addParameter (attr[i], attr[i+1]);
						}
					}
					data->aux->addAction(auxAction);
				}
				
			}
			
			// nodo: ACTIONS-ONCLICK
			
			if (data->inActionOnClick) {
				if (strcmp(el, "action-onclick") == 0) {
					ActionAnimation* auxAction = new ActionAnimation();
					for (i = 0; attr[i]; i += 2) {
						if (strcmp(attr[i], "function") == 0) {
							auxAction->function = attr[i+1];
						} else if (strcmp(attr[i], "time") == 0) {
							auxAction->cycle = Converter::GetInstance()->time2cycle(attr[i+1]);
						} else if (strcmp(attr[i], "objetive") == 0) {
							auxAction->nameObjetive = attr[i+1];
						} else {
							auxAction->addParameter (attr[i], attr[i+1]);
						}
					}
					data->aux->addActionOnClick(auxAction);
				}
				
			}
			
		} else if (data->inSound) {
			
			if (strcmp(el, "actions") == 0) {
				data->inAction = true;
			}
			
			// nodo: ACTIONS
			
			if (data->inAction) {
				if (strcmp(el, "action") == 0) {
					ActionAnimation* auxAction = new ActionAnimation();
					for (i = 0; attr[i]; i += 2) {
						if (strcmp(attr[i], "function") == 0) {
							auxAction->function = attr[i+1];
						} else if (strcmp(attr[i], "time") == 0) {
							auxAction->cycle = Converter::GetInstance()->time2cycle(attr[i+1]);
						} else if (strcmp(attr[i], "time-repeat") == 0) {
							auxAction->cyclesRepeat = Converter::GetInstance()->time2cycle(attr[i+1]);
						} else {
							auxAction->addParameter (attr[i], attr[i+1]);
						}
					}
					data->auxSound->addAction(auxAction);
				}
				
			}
			
		} else {
			
			if (strcmp(el, "progressbar") == 0) {
			
				int r=255, g=255, b=255;
				int w=200, h=16;
				
				string fileBg="";
				string fileBgBar="";
				string text="";
				string font="";
				int posBarX = 400, posBarY = 300;
				
				for (i = 0; attr[i]; i += 2) {
					if (strcmp(attr[i], "file-bg") == 0) {
						fileBg = data->scene->getDirectory() + "/" + attr[i+1];
					}
					if (strcmp(attr[i], "file-bgbar") == 0) {
						fileBgBar = data->scene->getDirectory() + "/" + attr[i+1];
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
					if (strcmp(attr[i], "width") == 0) {
						w = atoi(attr[i+1]);
					}
					if (strcmp(attr[i], "height") == 0) {
						h = atoi(attr[i+1]);
					}
					if (strcmp(attr[i], "x-positionbar") == 0) {
						posBarX = atoi(attr[i+1]);
					}
					if (strcmp(attr[i], "y-positionbar") == 0) {
						posBarY = atoi(attr[i+1]);
					}
					if (strcmp(attr[i], "text") == 0) {
						text = attr[i+1];
					}
					if (strcmp(attr[i], "text-language") == 0) {
						text = Language::GetInstance()->getText(attr[i+1]);
					}
					if (strcmp(attr[i], "font") == 0) {
						font = attr[i+1];
					}
				}
				
				char tmp[128];
				sprintf(tmp, "%s/animation.xml", data->scene->getDirectory().c_str());	
				
				data->scene->pb = new ProgressBar(nElementsXMLAnimation(tmp)-1, w, h, r, g, b);
				
				if (fileBg!="") data->scene->pb->setBg(fileBg);
				if (fileBgBar!="") data->scene->pb->setBgBar(fileBgBar);
				data->scene->pb->setPositionBar(posBarX, posBarY);
				//data->scene->pb->draw();
				
				if (text!="") data->scene->pb->setText(font, text);
				
				data->scene->drawProgressBar = true;
				
			}
			
			if (strcmp(el, "scenewhenscape") == 0) {
			
				for (i = 0; attr[i]; i += 2) {
					if (strcmp(attr[i], "name") == 0) {
						data->scene->setNameSceneWhenScape(attr[i+1]);
					}
				}
				
			}
			
			if (strcmp(el, "debug") == 0) {
			
				for (i = 0; attr[i]; i += 2) {
					if (strcmp(attr[i], "time") == 0) {
						data->scene->setCycles(Converter::GetInstance()->time2cycle(attr[i+1]));
					}
				}
				
			}
			
			if (strcmp(el, "sound") == 0) {
				data->inSound = true;
				
				data->auxSound = new SoundAnimation();
				
				for (i = 0; attr[i]; i += 2) {
					if (strcmp(attr[i], "name") == 0) {
						data->auxSound->setName(attr[i+1]);
					}
					if (strcmp(attr[i], "category") == 0) {
						data->auxSound->setCategory(attr[i+1]);
					}
					if (strcmp(attr[i], "file") == 0) {
						char tmp[128];
						sprintf(tmp, "%s/%s", data->scene->getDirectory().c_str(), attr[i+1]);
						data->auxSound->setFile(tmp);
					}
				}
				
			}
			
			if (strcmp(el, "background-stars") == 0) {
			
				for (i = 0; attr[i]; i += 2) {
					if (strcmp(attr[i], "file") == 0) {
						data->scene->createStars(attr[i+1]);
					}
				}
				
			}
			
			if (strcmp(el, "visible-stars") == 0) {
				ShowHideElement auxShowHideStars;
				for (i = 0; attr[i]; i += 2) {
					if (strcmp(attr[i], "type") == 0) {
						auxShowHideStars.type = attr[i+1];
					}
					if (strcmp(attr[i], "time") == 0) {
						auxShowHideStars.cycle = Converter::GetInstance()->time2cycle(attr[i+1]);
					}
				}
				data->scene->addShowHideStar(auxShowHideStars);
			}
			
			if ( (strcmp(el, "element") == 0) || (strcmp(el, "button") == 0) ) {
				if (data->scene->drawProgressBar) data->scene->pb->draw();
				data->inElement = true;
				data->aux = new ObjectAnimation();
				data->aux->setType((string)el);
				data->aux->getElement()->hide();
				float scaleOn = 1.0, scaleOut = 1.0;
				int r = 255, g = 255, b = 255;
				for (i = 0; attr[i]; i += 2) {
					if ( (strcmp(attr[i], "visible") == 0) && (strcmp(attr[i+1], "show") == 0) ) {
						data->aux->getElement()->show();
					}
					if (strcmp(attr[i], "name") == 0) {
						data->aux->setName(attr[i+1]);
					}
					if (strcmp(attr[i], "scale-out") == 0) {
						scaleOut = atof(attr[i+1]);
					}
					if (strcmp(attr[i], "scale-on") == 0) {
						scaleOn = atof(attr[i+1]);
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
					if (strcmp(attr[i], "x") == 0) {
						data->aux->getElement()->setX(atoi(attr[i+1]));
					}
					if (strcmp(attr[i], "y") == 0) {
						data->aux->getElement()->setY(atoi(attr[i+1]));
					}
					if (strcmp(attr[i], "z-index") == 0) {
						data->aux->getElement()->setIndexZ(atoi(attr[i+1]));
					}
					if (strcmp(attr[i], "alpha") == 0) {
						data->aux->getElement()->setAlpha(atoi(attr[i+1]));
					}					
					if (strcmp(attr[i], "rotate") == 0) {
						data->aux->getElement()->setRot(atof(attr[i+1]));
					}
					if (strcmp(attr[i], "rotate-x") == 0) {
						data->aux->getElement()->setRotX(atof(attr[i+1]));
					}
					if (strcmp(attr[i], "rotate-y") == 0) {
						data->aux->getElement()->setRotY(atof(attr[i+1]));
					}
					if (strcmp(attr[i], "rotate-z") == 0) {
						data->aux->getElement()->setRotZ(atof(attr[i+1]));
					}
					if (strcmp(attr[i], "scale") == 0) {
						data->aux->getElement()->setCurrentScale(atof(attr[i+1]));
					}
					if (strcmp(attr[i], "scale-x") == 0) {
						data->aux->getElement()->setCurrentScaleX(atof(attr[i+1]));
					}
					if (strcmp(attr[i], "scale-y") == 0) {
						data->aux->getElement()->setCurrentScaleY(atof(attr[i+1]));
					}
					if (strcmp(attr[i], "align") == 0) {
						if (strcmp(attr[i+1], "left") == 0) {
							data->aux->getElement()->setAlign(ALIGN_LEFT);
						} else if (strcmp(attr[i+1], "center") == 0) {
							data->aux->getElement()->setAlign(ALIGN_CENTER);
						} else if (strcmp(attr[i+1], "right") == 0) {
							data->aux->getElement()->setAlign(ALIGN_RIGHT);
						}
					}
					if (strcmp(attr[i], "valign") == 0) {
						if (strcmp(attr[i+1], "top") == 0) {
							data->aux->getElement()->setVAlign(VALIGN_TOP);
						} else if (strcmp(attr[i+1], "center") == 0) {
							data->aux->getElement()->setVAlign(VALIGN_CENTER);
						} else if (strcmp(attr[i+1], "bottom") == 0) {
							data->aux->getElement()->setVAlign(VALIGN_BOTTOM);
						}
					}
				}
				
				if (strcmp(el, "button") == 0) {
					((Button*)data->aux->getElement())->setScales(scaleOut, scaleOn);
					((Button*)data->aux->getElement())->setRGB(r,g,b);
				} else {
					((Element*)data->aux->getElement())->setRGB(r,g,b);
				}					
				
			}
		}
	}
	
	static void endXMLAnimation(void *userData, const char *el)
	{
		AnimationXML* data = (AnimationXML*)userData;
		
		if ( (strcmp(el, "element") == 0) || (strcmp(el, "button") == 0) ) {
			if (data->todoBorder) {
				data->aux->getElement()->createBorder(data->rBorder, data->gBorder, data->bBorder, data->sizeBorder, data->paddingBorder);
				if (data->showBorder) data->aux->getElement()->showBorder();
				data->todoBorder = false;
			}
			data->showBorder = false;
			if (data->todoBackground) {
				data->aux->getElement()->createBackground(data->rBg, data->gBg, data->bBg, data->paddingBg);
				if (data->showBackground) data->aux->getElement()->showBackground();
				data->todoBackground = false;
			}
			data->showBackground = false;
			data->scene->addObjectAnimation(data->aux);
			data->inElement = false;
		}
		if (strcmp(el, "sound") == 0) {
			data->scene->addSoundAnimation(data->auxSound);
			data->inSound = false;
		}
		if (strcmp(el, "frames") == 0) {
			data->inFrames = false;
		}
		if (strcmp(el, "actions") == 0) {
			data->inAction = false;
		}
		if (strcmp(el, "actions-onclick") == 0) {
			data->inActionOnClick = false;
		}
		if (strcmp(el, "animation") == 0) {
			data->inAnimation = false;
		}
		
	}
		
	void parseXMLAnimation(char fileXML[128], SceneAnimation *s) {
		char buffer[8192];
		int done;
		
		AnimationXML data;
		data.scene = s;
		data.todoBorder = false;
		data.rBorder = 255;
		data.gBorder = 255;
		data.bBorder = 255;
		data.sizeBorder = 1;
		data.paddingBorder = 5;
		data.showBorder = false;
		data.todoBackground = false;
		data.rBg = 255;
		data.gBg = 255;
		data.bBg = 255;
		data.paddingBg = 5;
		data.showBackground = false;
		data.inSound = false;
		data.inElement = false;
		data.inFrames = false;
		data.inAnimation = false;
		data.nameAnimation = "";
		data.inAction = false;
		data.inActionOnClick = false;
		
		XML_Parser p = XML_ParserCreate("UTF-8");
		if (! p) {
			printf("It could not have sufficient memory parser\n");
		}
	
		XML_SetUserData(p, &data);	
		XML_SetElementHandler(p, startXMLAnimation, endXMLAnimation);
	
		FILE *file = fopen(fileXML, "r");
		if(!file)
			printf("Error opening file XML: %s\n", fileXML);
		
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
	
	static void startElementsXMLAnimation(void *userData, const char *el, const char **attr) {
		ElementsAnimationXML* data = (ElementsAnimationXML*)userData;
		if ( (strcmp(el, "element") == 0) || (strcmp(el, "button") == 0) ) {
			data->nElements++;
		}
	}
	
	static void endElementsXMLAnimation(void *userData, const char *el)	{
	}
	
	
	int nElementsXMLAnimation(char fileXML[128]) {
		char buffer[8192];
		int done;
		
		ElementsAnimationXML data;
		data.nElements = 0;
		
		XML_Parser p = XML_ParserCreate("UTF-8");
		if (! p) {
			printf("It could not have sufficient memory parser\n");
		}
	
		XML_SetUserData(p, &data);	
		XML_SetElementHandler(p, startElementsXMLAnimation, endElementsXMLAnimation);
	
		FILE *file = fopen(fileXML, "r");
		if(!file)
			printf("Error opening file XML 1\n");
		
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
		return data.nElements;
	}
}
