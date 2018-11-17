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
 #include "options.h"

namespace Martian {
	 
	 Options* Options::instance = NULL;
	 
	/*****************************
	**
	** CLASE Options
	**
	******************************/	

	
	Options::Options(string file) : Hash (file, true) {
	}
	
    Options* Options::GetInstance () {
    	if ( instance == NULL ) {
    		instance = new Options("conf.xml");
    	}
    	return instance;	
    }

		
}
