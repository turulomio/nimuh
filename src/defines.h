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
 
#ifndef DEFINES_H_
#define DEFINES_H_

namespace Martian {

	#define CONFIG_DIR_UNIX "nimuh"
	
	#define MAX_INDEXZ 10
	
	// scenes
	
	#define SCENE_ALERT 100
	#define SCENE_INPUT 101
	#define SCENE_MESSAGEBOX 102
	#define SCENE_WAITINGNEXTSCENE 103
	
	#define SCENE_TRANSITION_NO 0
	#define SCENE_TRANSITION_FADEOUT 1
	#define SCENE_TRANSITION_FADEOUT_SCALEx0 2
	#define SCENE_TRANSITION_FADEOUT_SCALEx0_ROTATE 4
	#define SCENE_TRANSITION_SCALEx0 5
	#define SCENE_TRANSITION_SCALEx0_ROTATE 6
	#define SCENE_TRANSITION_SCALEx2 7
	#define SCENE_TRANSITION_SCALEx2_ROTATE 8
	
		
	#define NELMIMGSAVE 2
	
	
	#define VELOCITY_VERYSLOW 0
	#define VELOCITY_SLOW 1
	#define VELOCITY_NORMAL 2
	#define VELOCITY_QUICK 3
	#define VELOCITY_VERYQUICK 4
	
	// movements
	
	#define NO_MOVEMENT 0
	#define MOVEMENT_DISPLACEMENT 1
	#define MOVEMENT_NORMAL 2
	#define MOVEMENT_SMOOTH 3
	#define MOVEMENT_FLEXIBLE 4
	
	// scale
	
	#define NO_SCALE 0
	#define SCALE_NORMAL 1
	#define SCALE_SMOOTH 2
	#define SCALE_FLEXIBLE 3
	
	// rotate
	
	#define NO_ROTATE 0
	#define ROTATE_NORMAL 1
	#define ROTATE_SMOOTH 2
	#define ROTATE_FLEXIBLE 3
	
	// particles
	
	#define NPARTICLES 200
	#define TYPE_EXPLOSION 0
	#define TYPE_STARS 1


	#define PARTICLE_BEINGBORN 0	
	#define PARTICLE_LIFE 1
	#define PARTICLE_DYING 2
	
	// rotate types
	#define AHEADBACK_ROTATION 0
	#define CIRCULAR_ROTATION 1
	
	// slides types
	#define TYPESLIDE_FADE 0
	#define TYPESLIDE_ROTATE 1
	
	// aligns
	
	#define ALIGN_LEFT 0 
	#define ALIGN_CENTER 1 
	#define ALIGN_RIGHT 2 
	#define VALIGN_TOP 0 
	#define VALIGN_CENTER 1 
	#define VALIGN_BOTTOM 2 
	
	// directions
	
	#define DIR_RIGHT 0
	#define DIR_LEFT 1
	#define DIR_UP 2
	#define DIR_DOWN 3
	
	// direcciones
	
	#define RIGHT 0
	#define LEFT 1
	#define UP 2
	#define DOWN 3
	#define OTHER 4
	
	
	// joystick
	
	#define JOY_SHUT 0
}	

#endif /* DEFINES_H_ */
