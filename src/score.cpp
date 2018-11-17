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
 #include "score.h"

namespace Martian {
	 
	 Score* Score::instance = NULL;
	 
	/*****************************
	**
	** CLASE Score
	**
	******************************/	

	
	Score::Score(string file) : Hash (file, true) {
        nPlayers = 5;
	}
	
    Score* Score::GetInstance () {
    	if ( instance == NULL ) {
    		instance = new Score("score.xml");
    	}
    	return instance;	
    }
    
	void Score::orderByScore() {
		int i,j,menor;
        Item aux;
		
		for(i=0;i<items.size();i++)
		{
		   for(j=i+1,menor=i;j<items.size(); j++) {
              if(atoi(items[j].value.c_str())>atoi(items[menor].value.c_str())) 
			      menor=j; 
           }
           aux=items[i]; 
		   items[i]=items[menor]; 
		   items[menor]=aux;
	     }
	 }

	bool Score::save() {
		
		orderByScore();
		FILE *f;
		f = fopen((char*)file.c_str(), "w+");
		
		char tmp_val[128];
		
		sprintf (tmp_val, "<?xml version=\"1.0\" encoding=\"ISO-8859-1\"?>\n<items>\n");
		fwrite(tmp_val, strlen(tmp_val), 1, f);
		
		int i;
		for (i=0; i<items.size(); i++) {
            if (i<nPlayers) {
			   sprintf (tmp_val, "\t<item name=\"%s\" value=\"%s\" />\n", items[i].name.c_str(), items[i].value.c_str());
			   fwrite(tmp_val, strlen(tmp_val), 1, f);
            }
		}
		
		sprintf (tmp_val, "</items>\n");
		fwrite(tmp_val, strlen(tmp_val), 1, f);
		
		fclose(f);
	
		
	}
		
}
