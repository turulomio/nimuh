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
 
 #include "font.h"
 
namespace Martian {
		
	/*****************************
	**
	** CLASE FUENTE
	**
	******************************/
	
	/*
		Basado en el artículo de Hugo Ruscitti "Fuentes Gráficas" en Losersjuegos
		http://www.losersjuegos.com.ar/referencia/articulos/fuentes_graficas/fuentes_graficas.php
	*/
	
	FontBitMap::FontBitMap(string file_img, bool pl) {
		
		nLetters = 0;
		file = file_img;
		preload = pl;
		
		if (preload) {
			loadLetters ();
		}
	}
	
	FontBitMap::~FontBitMap() {
		unLoad();
	}
	
	void FontBitMap::loadLetters ()	{
		SDL_Surface *image = IMG_Load((char*)file.c_str());
		createElements(image);
		SDL_FreeSurface(image);
	}
	
	void FontBitMap::unLoadLetters () {
		int i;
		for (i=0; i<nLetters; i++) {
			SDL_FreeSurface(letters[i]);
		}
		nLetters = 0;
	}
	
	Uint32 FontBitMap::get_pixel (SDL_Surface * img, int x, int y) {
		int bpp = img->format->BytesPerPixel;
		Uint8 *p = (Uint8 *) img->pixels + y * img->pitch + x * bpp;
	
		switch (bpp)
		{
			case 1:
				return *p;
			
			case 2:
				return *(Uint16 *)p;
	
			case 3:
				if (SDL_BYTEORDER == SDL_BIG_ENDIAN)
					return p[0] << 16 | p[1] << 8 | p[2];
				else
					return p[0] | p[1] << 8 | p[2] << 16;
	
			case 4:
				return *(Uint32 *)p;
	
			default:
				return 0;
		}
	}
	
	bool FontBitMap::columnTransparent (SDL_Surface * img, int column) {
		Uint32 pixel_transparent = get_pixel (img, 0, 0);
		int row;
		
		/* busca un pixel opaco */
		for (row = 0; row < img->h; row ++)
		{
			if (pixel_transparent != get_pixel (img, column, row))
				return false;
		}
	
		return true;
	}
	
	void FontBitMap::saveLetter (SDL_Surface * img, int index, int x, int y, int w, int h)
	{
		SDL_Surface *image;
		
		Uint32 saved_flags;
		Uint8  saved_alpha;
	  
	#if SDL_BYTEORDER == SDL_BIG_ENDIAN
		  image = SDL_CreateRGBSurface(SDL_SWSURFACE, w, h, img->format->BitsPerPixel,
									  0xff000000, 0x00ff0000, 0x0000ff00, 0x000000ff);
	#else
		  image = SDL_CreateRGBSurface(SDL_SWSURFACE, w, h, img->format->BitsPerPixel,
									  0x000000ff, 0x0000ff00, 0x00ff0000, 0xff000000);
	#endif
		
		saved_flags = img->flags&(SDL_SRCALPHA|SDL_RLEACCELOK);
		saved_alpha = img->format->alpha;
		if ( (saved_flags & SDL_SRCALPHA) == SDL_SRCALPHA ) {
			SDL_SetAlpha(img, 0, 0);
		}
		
		int colorkey = SDL_MapRGB(img->format, 255, 0, 255);
		SDL_SetColorKey(image, SDL_SRCCOLORKEY, colorkey);
		SDL_FillRect(image, 0, colorkey);
		
		SDL_Rect src;
		
		src.x = x;
		src.y = y;
		src.h = h;
		src.w = w;
		
		SDL_BlitSurface(img, &src, image, 0);
		
		if ( (saved_flags & SDL_SRCALPHA) == SDL_SRCALPHA ) {
			SDL_SetAlpha(img, saved_flags, saved_alpha);
		}
		
		letters[index] = image;
		nLetters++;
		
	}
	
	void FontBitMap::createElements (SDL_Surface * img) {
		int indexLetter = 0;
		int inLetter = false;
		int w = 0; /* ancho de la letra actual */
		int i;
	
		for (i = 0; i < img->w; i ++)
		{
			if (columnTransparent (img, i))
			{
				
				if (inLetter)
				{
					saveLetter(img, indexLetter, i - w, 0, w, img->h);
					inLetter = false;
					indexLetter ++;
				}
			}
			else
			{
				if (inLetter)
					w ++;
				else
				{
					w = 1;
					inLetter = true;
				}
			}
		}
	
	
	}
	
	int FontBitMap::getIndexLetter (char c) {
		char n[4];
		
		sprintf(n, "%d", c);
		
		int ind = atoi(n);

		int i;
		static char chain_letters [] = "abcdefghijklmnopqrstuvwxyz"\
					"ABCDEFGHIJKLMNOPQRSTUVWXYZ" \
					"1234567890" \
					"ñÑáéíóúÁÉÍÓÚäëïöü"\
					"!¡?¿@#$%&'+-=><*/,.:;-_()[]{}|^`~\\"\
					"àèìòùâêîôû";
	
	
		if (c == ' ')
			return 1;
		
        if (ind==-95) return 64; // á
        if (ind==-87) return 65; // é
        if (ind==-83) return 66; // í
		if (ind==-77) return 67; // ó
        if (ind==-70) return 68; // ú
		/*if (ind==-127) return 69; // Á -> tiene problemas
		if (ind==-119) return 70; // É -> tiene problemas*/
		if (ind==-79) return 62; // ñ
	
		for (i = 0; chain_letters [i]; i ++)
		{
			if (c == chain_letters [i]) {
				return i;
			}
		}
		//printf ("Don't find index for '%c' '%d'\n", c, c);
		return -1;
	}
	
	void FontBitMap::writeIndexWord (char* c) {
		for (int i = 0; c [i]; i ++)
		{
			printf( "%d\n", c [i] );
		}
	}
	
	SDL_Surface* FontBitMap::getWord (char * chain)	{	
		
		if (!preload) {
			loadLetters ();
		}
		
		int i;
		int widthImg=0;

		for (i = 0; chain[i]; i ++)
		{
			int ind = getIndexLetter(chain [i]);
			if (ind>=0) {
				if (chain [i] == ' ') {
					char c_[2] = "_";
					widthImg += letters[getIndexLetter(c_[0])]->w;
				} else {
					widthImg += letters[getIndexLetter(chain [i])]->w;
				}
			}
		}

		SDL_Surface *image;
		
		Uint32 saved_flags;
		Uint8  saved_alpha;
	  
	#if SDL_BYTEORDER == SDL_BIG_ENDIAN
		  image = SDL_CreateRGBSurface(SDL_SWSURFACE, widthImg, letters[0]->h, letters[0]->format->BitsPerPixel,
									  0xff000000, 0x00ff0000, 0x0000ff00, 0x000000ff);
	#else
		  image = SDL_CreateRGBSurface(SDL_SWSURFACE, widthImg,letters[0]->h, letters[0]->format->BitsPerPixel,
									  0x000000ff, 0x0000ff00, 0x00ff0000, 0xff000000);
	#endif
	
		widthImg = 0;

		for (i = 0; chain[i]; i ++)
		{
			int ind = getIndexLetter(chain [i]);
			if (ind>=0) {
				if (chain [i] == ' ') {
					char c_[2] = "_";
					widthImg+=letters[getIndexLetter(c_[0])]->w;
					continue;
				}
				
				/* Save the alpha blending attributes */
				
				saved_flags = letters[getIndexLetter(chain [i])]->flags&(SDL_SRCALPHA|SDL_RLEACCELOK);
				saved_alpha = letters[getIndexLetter(chain [i])]->format->alpha;
				if ( (saved_flags & SDL_SRCALPHA) == SDL_SRCALPHA ) {
					SDL_SetAlpha(letters[getIndexLetter(chain [i])], 0, 0);
				}
				
				SDL_Rect dest;
				
				dest.x = widthImg;
				dest.y = 0;
				dest.w = letters[getIndexLetter(chain [i])]->w;
				dest.h = letters[getIndexLetter(chain [i])]->h;
				
				SDL_BlitSurface(letters[getIndexLetter(chain [i])], 0, image, &dest);
				
				if ( (saved_flags & SDL_SRCALPHA) == SDL_SRCALPHA ) {
					SDL_SetAlpha(letters[getIndexLetter(chain [i])], saved_flags, saved_alpha);
				}
				
				widthImg += letters[getIndexLetter(chain [i])]->w;
			}
		}
		
		if (!preload) {
			unLoadLetters ();
		}
		
		return image;
		
	}
	
	void FontBitMap::unLoad () {
		unLoadLetters();
	}
	
	 
	/*****************************
	**
	** CLASS FONTS
	**
	******************************/
	
	Fonts* Fonts::instance = NULL;
	
	Fonts::Fonts() {
		defaultFont = "";
		lastFont = "";
	}
	
	Fonts* Fonts::GetInstance () {
		if ( instance == NULL ) {
			instance = new Fonts();
		}
		return instance;	
	}
	
	bool Fonts::existFont(string name) {
		map<string, FontBitMap*>::iterator it;
		for (it=fontsbitmap.begin(); it!=fontsbitmap.end(); ++it) {
			if ((*it).first==name) {
				return true;
			}
		}
		return false;
	}
	
	InfoFontBitMap Fonts::getInfoFontBitMap (string nameFont, int nLines, float scale, int width, int align, string text) {
	    
	    string txt = WorkingData::GetInstance()->replace(text, "#", "ñ");
		txt = WorkingData::GetInstance()->replace(txt, "$", "Ñ");
	    
		FontBitMap *auxFuentMB;

		if (existFont(nameFont)) {
			auxFuentMB = fontsbitmap[nameFont];
		} else {
			auxFuentMB = fontsbitmap[getDefaultFont()];
		}
		
		if (width>0) {
			vector<string> strSeparateIntro = Converter::GetInstance()->split(txt, "|");

			int i,j;
			for (j=0; j<(int)strSeparateIntro.size(); j++) {
				int lastSpace = 0;
				int lastSpaceWithIntro = 0;
				for (i=0; i<(int)strSeparateIntro[j].length(); i++) {
					if ( (strSeparateIntro[j].substr(i, 1) == " ") || (i>=(int)strSeparateIntro[j].length()-1) ) {
											
						SDL_Surface* sfc = auxFuentMB->getWord((char*)strSeparateIntro[j].substr(lastSpaceWithIntro, i-lastSpaceWithIntro).c_str());
						
						if ((sfc->w*scale) > width) {
							lastSpaceWithIntro = lastSpace;
							strSeparateIntro[j].replace(lastSpace, 1, "|");
						}

						lastSpace = i;
						
						SDL_FreeSurface(sfc);
						
					}
				}

			}
			txt = Converter::GetInstance()->join(strSeparateIntro, "|");
			
		}		
		
		vector<string> strSeparateIntro = Converter::GetInstance()->split(txt, "|");
		if ((int)strSeparateIntro.size()<=0) strSeparateIntro.push_back(txt);
		
		if (nLines>0) {
			if ((int)strSeparateIntro.size()>nLines) {
            	int last = (int)strSeparateIntro.size();
            	strSeparateIntro.erase(strSeparateIntro.begin()+nLines, strSeparateIntro.begin()+last);   
			}
        }
		SDL_Surface* sfc = auxFuentMB->getWord((char*)strSeparateIntro[strSeparateIntro.size()-1].c_str());
		int xCursor = sfc->w*scale;
		SDL_FreeSurface(sfc);
		
		vector<int> lettersByLine;
		for (int i=0; i<(int)strSeparateIntro.size(); i++) {
            lettersByLine.push_back(strSeparateIntro[i].length());
        }
 
	    
	    InfoFontBitMap ifbm;
	    ifbm.text = Converter::GetInstance()->join(strSeparateIntro, "|");
	    ifbm.nLines = (int)strSeparateIntro.size();
	    ifbm.xPosCursor = xCursor;
	    ifbm.nLettersByLine = lettersByLine;
	    return ifbm;
    }
	
	SDL_Surface* Fonts::getSurface_TextBitMap (string nameFont, int nLines, float scale, int width, int align, string text) {
        string txt = WorkingData::GetInstance()->replace(text, "#", "ñ");
		txt = WorkingData::GetInstance()->replace(txt, "$", "Ñ");
		
		if (txt.substr(txt.length()-1, 1) == "|") {
			txt = txt.substr(0, txt.length()-1);
		}
				
		FontBitMap *auxFuentMB;

		if (existFont(nameFont)) {
			auxFuentMB = fontsbitmap[nameFont];
		} else {
			auxFuentMB = fontsbitmap[getDefaultFont()];
		}
		
		if (width>0) {
			vector<string> strSeparateIntro = Converter::GetInstance()->split(txt, "|");

			int i,j;
			for (j=0; j<(int)strSeparateIntro.size(); j++) {
				int lastSpace = 0;
				int lastSpaceWithIntro = 0;
				for (i=0; i<(int)strSeparateIntro[j].length(); i++) {
					if ( (strSeparateIntro[j].substr(i, 1) == " ") || (i>=(int)strSeparateIntro[j].length()-1) ) {
											
						SDL_Surface* sfc = auxFuentMB->getWord((char*)strSeparateIntro[j].substr(lastSpaceWithIntro, i-lastSpaceWithIntro).c_str());
						
						if ((sfc->w*scale) > width) {
							lastSpaceWithIntro = lastSpace;
							strSeparateIntro[j].replace(lastSpace, 1, "|");
						}

						lastSpace = i;
						
						SDL_FreeSurface(sfc);
						
					}
				}

			}
			txt = Converter::GetInstance()->join(strSeparateIntro, "|");
			
		}		
		
		vector<string> strSeparateIntro = Converter::GetInstance()->split(txt, "|");
		
		if (nLines>0) {
			if ((int)strSeparateIntro.size()>nLines) {
            	int last = (int)strSeparateIntro.size();
            	strSeparateIntro.erase(strSeparateIntro.begin()+nLines, strSeparateIntro.begin()+last);   
			}
        }
		
		int hLine = 0, wLine = 0, numLines = 0;
		SDL_Surface* sfc_line = auxFuentMB->getWord((char*)strSeparateIntro[0].c_str());
		for (int i=0; i<(int)strSeparateIntro.size(); i++) {
			SDL_FreeSurface(sfc_line);
			sfc_line = auxFuentMB->getWord((char*)strSeparateIntro[i].c_str());
			hLine = sfc_line->h;
			if (wLine<sfc_line->w) {
				wLine = sfc_line->w;
			}
			numLines++;
		}
	
		SDL_Surface *image;
		
		Uint32 saved_flags;
		Uint8  saved_alpha;
	  
	#if SDL_BYTEORDER == SDL_BIG_ENDIAN
		  image = SDL_CreateRGBSurface(SDL_SWSURFACE, wLine, hLine*numLines, sfc_line->format->BitsPerPixel,
									  0xff000000, 0x00ff0000, 0x0000ff00, 0x000000ff);
	#else
		  image = SDL_CreateRGBSurface(SDL_SWSURFACE, wLine, hLine*numLines, sfc_line->format->BitsPerPixel,
									  0x000000ff, 0x0000ff00, 0x00ff0000, 0xff000000);
	#endif
		
		SDL_FreeSurface(sfc_line);
		
		SDL_Rect dest;
		
		
		for (int i=0; i<(int)strSeparateIntro.size(); i++) {
			
			sfc_line = auxFuentMB->getWord((char*)strSeparateIntro[i].c_str());
			
			saved_flags = sfc_line->flags&(SDL_SRCALPHA|SDL_RLEACCELOK);
			saved_alpha = sfc_line->format->alpha;
			if ( (saved_flags & SDL_SRCALPHA) == SDL_SRCALPHA ) {
				SDL_SetAlpha(sfc_line, 0, 0);
			}
			
			
			switch(align) {
				case ALIGN_LEFT:
					dest.x = 0;
				break;
				case ALIGN_CENTER:
					dest.x = (wLine/2)-(sfc_line->w/2);
				break;
				case ALIGN_RIGHT:
					dest.x = wLine-sfc_line->w;
				break;
			}
			dest.y = hLine*i;
		   
			SDL_BlitSurface(sfc_line, 0, image, &dest);
			
			if ( (saved_flags & SDL_SRCALPHA) == SDL_SRCALPHA ) {
				SDL_SetAlpha(sfc_line, saved_flags, saved_alpha);
			}
			
			SDL_FreeSurface(sfc_line);
	
		}
		
		return image;

	}
	
	
	
	void Fonts::unLoad () {
		map<string, FontBitMap*>::iterator it;
		for (it=fontsbitmap.begin(); it!=fontsbitmap.end(); ++it) {
			(*it).second->unLoad();
		}
	}
	
}
