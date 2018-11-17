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

#include "elements.h"

namespace Martian {
	
	/*****************************
	**
	** CLASE Converter
	**
	******************************/	

	Converter* Converter::instance = NULL;
	
	Converter::Converter() {
	}
	
	Converter* Converter::GetInstance () {
		if ( instance == NULL ) {
			instance = new Converter();
		}
		return instance;	
	}
	
	int Converter::ml2cycles(int ml) {
		return (int)( ((float)ml/1000) * Timer::GetInstance()->getFPS() );
	}
	
	vector<string> Converter::split(string txt, string chunk) {
		int i,j;
		vector<string> strSeparate;
		for (i=0; i<(int)txt.length(); i++) {
			if ( (txt.substr(i, (int)chunk.length()) == chunk) || (i>=(int)txt.length()-1) ) {
				int ini = 0, end = 0;
				for (j=0; j<(int)strSeparate.size(); j++) {
					ini += (int)strSeparate[j].length()+1;
				}
				if (i>=(int)txt.length()-1) {
					end = i-ini+1;
				} else {
					end = i-ini;
				}
				strSeparate.push_back(txt.substr(ini, end));
			}
		}
		return strSeparate;
	}
	
	string Converter::join(vector<string> txt, string chunk) {
		int i;
		string strJoin;
		for (i=0; i<(int)txt.size(); i++) {
			strJoin += txt[i];
			if (i<(int)txt.size()-1) strJoin += "|";
		}
		return strJoin;
	}
	
	int Converter::time2cycle(string time) {
		int minutes = 0;
		int	seconds = 0;
		int	fracseconds = 0;
		
		int c[3];
		char *chunk;
		
		chunk = strtok( (char*)time.c_str(), ":" );
		c[0] = atoi(chunk);
		int cont = 1;
		while( (chunk = strtok( NULL, ":" )) != NULL ) {
			c[cont] = atoi(chunk);
			cont++;
		}
		
		switch(cont) {
			case 1:
				fracseconds = c[0];
			break;
			case 2:
				fracseconds = c[1];
				seconds = c[0];
			break;
			case 3:
				fracseconds = c[2];
				seconds = c[1];
				minutes = c[0];
			break;
		}
				
		return ( (minutes*60)*Timer::GetInstance()->getFPS() ) + ( seconds*Timer::GetInstance()->getFPS() ) + ( ((float)fracseconds/60)*Timer::GetInstance()->getFPS() );
	}
	
	string Converter::fillZeros(int i) {
		string chain = "";
		char numbers[4];
		if ( (i>=0) && (i<10) ) {
			sprintf(numbers, "%d", i);
			chain += "000" + string(numbers);
		} else if ( (i>=10) && (i<100) ) {
			sprintf(numbers, "%d", i);
			chain += "00" + string(numbers);
		} else if ( (i>=100) && (i<1000) ) {
			sprintf(numbers, "%d", i);
			chain += "0" + string(numbers);
		} else if ( (i>=1000) && (i<10000) ) {
			sprintf(numbers, "%d", i);
			chain += string(numbers);
		} else {
			chain += "0000";
		}
		return chain;
	}
		
	/*****************************
	**
	** CLASE VerifyInfo
	**
	******************************/	

	WorkingData* WorkingData::instance = NULL;
	
	WorkingData::WorkingData() {
	}
	
	WorkingData* WorkingData::GetInstance () {
		if ( instance == NULL ) {
			instance = new WorkingData();
		}
		return instance;	
	}
	
	bool WorkingData::validCharacter(string c) {
		string chain_letters = " abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890ñÑ!¡?¿@#$%&'+-=><*/,.:;-_()[]{}|^`~\\";

		for (int i = 0; i<(int)chain_letters.size(); i ++) {
			if (chain_letters.substr(i, 1)==c) {
				return true;
			}
		}
		
		return false;
		
	}
	
	bool WorkingData::createFile(string file, string text, bool changeSpecialsCharacters) {

		FILE *f;
		f = fopen((char*)file.c_str(), "w+");
		
		if(!f) return false;
		
		string textToFile;
		
		if (changeSpecialsCharacters) {
			textToFile = replace(text, "ñ", "#");
			textToFile = replace(textToFile, "Ñ", "$");
        } else {
			textToFile = text;
        }
		
		fwrite(textToFile.c_str(), strlen(textToFile.c_str()), 1, f);
		
		fclose(f);
		
		return true;
	}
	
	bool WorkingData::existFile(string file) {
        vector<string> s = Converter::GetInstance()->split(file, "/");
        string f = s[(int)s.size()-1];
        string dir = "";
		
		if (file.substr(0,1) == "/") dir += "/";

        for (int i=0; i<(int)s.size()-1; i++) {
            if (s[i]!="") dir += s[i] + "/";
        }

    	DIR *pdir;
    	struct dirent *pent;
    	pdir=opendir(dir.c_str());
    	if (pdir) {
            while ((pent=readdir(pdir))) {
                 if ( strcmp(pent->d_name, f.c_str()) == 0 ) {
                      closedir(pdir);
                      return true;
                 }
            }
            closedir(pdir);
        }
        
		return false;
	}
	
	string WorkingData::replace(string chain, string search, string replace) {
        string::size_type pos = 0;
        string chainReplaced = chain;
        while ( (pos = chainReplaced.find(search, pos)) != string::npos ) {
            chainReplaced.replace( pos, search.size(), replace );
            pos++;
        }
        return chainReplaced;
    }
	
	void WorkingData::createDirectory(string dir) {
         if (!existFile(dir)) {
            #ifdef WIN32
                string directory = replace(dir, "/", "\\");
                
                char DirName[256];
                char* p = (char*)directory.c_str();
                char* q = DirName; 
                while(*p)
                {
                    if (('\\' == *p) || ('/' == *p))
                    {
                        if (':' != *(p-1))
                        {
                           CreateDirectory(DirName, NULL);
                        }
                    }
                    *q++ = *p++;
                    *q = '\0';
                }
                CreateDirectory(DirName, NULL);
                
            #else
                string cmd = "mkdir " + dir;
                system(cmd.c_str());
            #endif
       }
	}
	
	void WorkingData::deleteDirectory(string dir) {
         if (existFile(dir)) {
            #ifdef WIN32
                 string directory = replace(dir, "/", "\\");
				 char fileFound[256];
				 WIN32_FIND_DATA info;
				 HANDLE hp; 
				 sprintf(fileFound, "%s\\*.*", directory.c_str());
				 hp = FindFirstFile(fileFound, &info);
				 do
					{
						if (!((strcmp(info.cFileName, ".")==0)||
							  (strcmp(info.cFileName, "..")==0)))
						{
						  if((info.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)==
													 FILE_ATTRIBUTE_DIRECTORY)
						  {
                              string subFolder = directory;
							  subFolder.append("\\");
							  subFolder.append(info.cFileName);
							  deleteDirectory((char*)subFolder.c_str());
							  RemoveDirectory(subFolder.c_str());
						  }
						  else
						  {
							  sprintf(fileFound,"%s\\%s", directory.c_str(), info.cFileName);
							  BOOL retVal = DeleteFile(fileFound);
						  }
						}
				 
					} while(FindNextFile(hp, &info)); 
				 FindClose(hp);
				 RemoveDirectory(directory.c_str());
            #else
                string cmd = "rm -r " + dir;
                system(cmd.c_str());
            #endif
       }
	}
	
	string WorkingData::getPath(string file) {
        vector<string> s = Converter::GetInstance()->split(file, "/");
        string dir = "";
		
		if (file.substr(0,1) == "/") dir += "/";

        for (int i=0; i<(int)s.size()-1; i++) {
            if (s[i]!="") dir += s[i] + "/";
        }
        return dir;
    }
    
	string WorkingData::getFilename(string file) {
        vector<string> s = Converter::GetInstance()->split(file, "/");
        string f = s[(int)s.size()-1];
        return f;
    }
	
	string WorkingData::getExtension(string file) {
        vector<string> s = Converter::GetInstance()->split(file, ".");
        string ext = s[(int)s.size()-1];
        return getToUpper(ext);
    }
    
    string WorkingData::getToUpper(string str) {
       for(unsigned int i=0;i<str.length();i++) {
          str[i] = toupper(str[i]);
       }
       return str;
    }
    
    string WorkingData::getToLower(string str) {
       for(unsigned int i=0;i<str.length();i++) {
          str[i] = tolower(str[i]);
       }
       return str;
    }
	
	/*****************************
	**
	** CLASE WorkingSurfaces
	**
	******************************/	

	WorkingSurfaces* WorkingSurfaces::instance = NULL;
	
	WorkingSurfaces::WorkingSurfaces() {
	}
	
	WorkingSurfaces* WorkingSurfaces::GetInstance () {
		if ( instance == NULL ) {
			instance = new WorkingSurfaces();
		}
		return instance;	
	}
	
	SDL_Surface* WorkingSurfaces::surfaceFromImage(string path) {
		SDL_Surface* temp = IMG_Load((char*)path.c_str());
		if ( temp == NULL ) {
			printf("Unable to load %s: %s\n", path.c_str(), SDL_GetError());
		}
		return temp;
	}
 
	SDL_Surface* WorkingSurfaces::mixSurfaces(SDL_Surface* back, SDL_Surface* front, Bounds *destiny) {
		
		SDL_Surface *image;
		
	#if SDL_BYTEORDER == SDL_BIG_ENDIAN
		  image = SDL_CreateRGBSurface(SDL_SWSURFACE, back->w, back->h, back->format->BitsPerPixel,
									  0xff000000, 0x00ff0000, 0x0000ff00, 0x000000ff);
	#else
		  image = SDL_CreateRGBSurface(SDL_SWSURFACE, back->w, back->h, back->format->BitsPerPixel,
									  0x000000ff, 0x0000ff00, 0x00ff0000, 0xff000000);
	#endif
		Uint32 saved_flags;
		Uint8  saved_alpha;
		saved_flags = back->flags&(SDL_SRCALPHA|SDL_RLEACCELOK);
		saved_alpha = back->format->alpha;
		if ( (saved_flags & SDL_SRCALPHA) == SDL_SRCALPHA ) {
			SDL_SetAlpha(back, 0, 0);
		}		
	   
		
		if (destiny==NULL) {
			SDL_BlitSurface(back, NULL, image, NULL);
			if ( (saved_flags & SDL_SRCALPHA) == SDL_SRCALPHA ) {
				SDL_SetAlpha(back, saved_flags, saved_alpha);
			}
			SDL_BlitSurface(front, NULL, image, NULL);
			if ( (saved_flags & SDL_SRCALPHA) == SDL_SRCALPHA ) {
				SDL_SetAlpha(back, saved_flags, saved_alpha);
			}
		} else {
			SDL_BlitSurface(back, NULL, image, NULL);
			if ( (saved_flags & SDL_SRCALPHA) == SDL_SRCALPHA ) {
				SDL_SetAlpha(back, saved_flags, saved_alpha);
			}
			SDL_Rect o = {0, 0, (int)destiny->x2-(int)destiny->x1, (int)destiny->y2-(int)destiny->y1};
			SDL_Rect d = {(int)destiny->x1, (int)destiny->y1, (int)destiny->x2-(int)destiny->x1, (int)destiny->y2-(int)destiny->y1};
			SDL_BlitSurface(front, &o, image, &d);
			if ( (saved_flags & SDL_SRCALPHA) == SDL_SRCALPHA ) {
				SDL_SetAlpha(back, saved_flags, saved_alpha);
			}
		}
		SDL_FreeSurface(front);
		SDL_FreeSurface(back);
		return image;
		
	}
	
	Size WorkingSurfaces::getSize(string file) {
		SDL_Surface* temp = IMG_Load((char*)file.c_str());
		Size s;
		if ( temp == NULL ) {
			printf("Unable to load %s: %s\n", file.c_str(), SDL_GetError());
			s.w = 0;
			s.h = 0;
		} else {
			s.w = temp->w;
			s.h = temp->h;
			SDL_FreeSurface(temp);
		}
		return s;
	}
	
	/*****************************
	**
	** CLASE Primitives
	**
	******************************/	

	Primitives* Primitives::instance = NULL;
	
	Primitives::Primitives() {
	}
	
	Primitives* Primitives::GetInstance () {
		if ( instance == NULL ) {
			instance = new Primitives();
		}
		return instance;	
	}
	
	SDL_Surface* Primitives::rectangle ( int w, int h, int r, int g, int b ) {
		SDL_Surface *surface;
		Uint32 rmask, gmask, bmask, amask;
		
    	#if SDL_BYTEORDER == SDL_BIG_ENDIAN
    		rmask = 0xff000000;
    		gmask = 0x00ff0000;
    		bmask = 0x0000ff00;
    		amask = 0x000000ff;
    	#else
    		rmask = 0x000000ff;
    		gmask = 0x0000ff00;
    		bmask = 0x00ff0000;
    		amask = 0xff000000;
    	#endif
				
		surface = SDL_CreateRGBSurface(SDL_SWSURFACE, w, h, 32,
									   rmask, gmask, bmask, amask);
		
	
		int colorkey = SDL_MapRGB(surface->format, r, g, b);
		SDL_FillRect(surface, NULL, colorkey);
		return surface;
	}
	
    void Primitives::put_pixel(SDL_Surface *_ima, int x, int y, Uint32 pixel) {
    	int bpp = _ima->format->BytesPerPixel;
    	Uint8 *p = (Uint8 *)_ima->pixels + y * _ima->pitch + x*bpp;
    
    	switch (bpp)
    	{
    		case 1:
    			*p = pixel;
    			break;
    			
    		case 2:
    			*(Uint16 *)p = pixel;
    			break;
    			
    		case 3:
    			if (SDL_BYTEORDER == SDL_BIG_ENDIAN)
    			{
    				p[0]=(pixel >> 16) & 0xff;
    				p[1]=(pixel >> 8) & 0xff;
    				p[2]=pixel & 0xff;
    			}
    			else
    			{
    				p[0]=pixel & 0xff;
    				p[1]=(pixel >> 8) & 0xff;
    				p[2]=(pixel >> 16) & 0xff;
    			}
    			break;
    			
    		case 4:
    			*(Uint32 *) p = pixel;
    			break;
    	}
    }
	
	SDL_Surface* Primitives::border ( int w, int h, int r, int g, int b, int thickness, int space, bool intercaleSpace ) {
		SDL_Surface *surface;
		Uint32 rmask, gmask, bmask, amask;
		
    	#if SDL_BYTEORDER == SDL_BIG_ENDIAN
    		rmask = 0xff000000;
    		gmask = 0x00ff0000;
    		bmask = 0x0000ff00;
    		amask = 0x000000ff;
    	#else
    		rmask = 0x000000ff;
    		gmask = 0x0000ff00;
    		bmask = 0x00ff0000;
    		amask = 0xff000000;
    	#endif
				
		surface = SDL_CreateRGBSurface(SDL_SWSURFACE, w, h, 32,
									   rmask, gmask, bmask, amask);	
		
        Uint32 color = SDL_MapRGB (surface->format, r, g, b);
                
    	int x = 0, y = 0;
    	
        bool paint = true;
        
        for (y = 1; y <= thickness; y++) {
            if (!intercaleSpace) {
               paint = true;
            } else {
               if (y%2==0) {
                  paint = true;
               } else {
                  paint = false;
               }
            }
        	for (x = 1; x < w; x++) {
                if (space!=0) if (x%space==0) paint = !paint;
                if (paint) {
            		put_pixel (surface, x, y, color);
            		put_pixel (surface, x, h-y, color);
                }
            }
        }
        
       	paint = true;
       	
        for (x = 1; x <= thickness; x++) {
            if (!intercaleSpace) {
               paint = true;
            } else {
               if (x%2==0) {
                  paint = true;
               } else {
                  paint = false;
               }
            }
        	for (y = 1; y < h; y++) {
                if (space!=0) if (y%space==0) paint = !paint;
                if (paint) {
            		put_pixel (surface, x, y, color);
            		put_pixel (surface, w-x, y, color);
                }
            }
        }  
		
		return surface;
	}
	
	SDL_Surface* Primitives::rectangle ( int w, int h, int r, int g, int b, int border, int rb, int gb, int bb ) {
		SDL_Surface *surface;
		Uint32 rmask, gmask, bmask, amask;
		
    	#if SDL_BYTEORDER == SDL_BIG_ENDIAN
    		rmask = 0xff000000;
    		gmask = 0x00ff0000;
    		bmask = 0x0000ff00;
    		amask = 0x000000ff;
    	#else
    		rmask = 0x000000ff;
    		gmask = 0x0000ff00;
    		bmask = 0x00ff0000;
    		amask = 0xff000000;
    	#endif
				
		surface = SDL_CreateRGBSurface(SDL_SWSURFACE, w, h, 32,
									   rmask, gmask, bmask, amask);
		
	
		int colorkey = SDL_MapRGB(surface->format, rb, gb, bb);
		SDL_FillRect(surface, NULL, colorkey);
		
		SDL_Rect rect;
		rect.x = border;
		rect.y = border;
		rect.w = w-(border*2);
		rect.h = h-(border*2);
		
		SDL_Surface* surface2 = SDL_CreateRGBSurface(SDL_SWSURFACE, w-(border*2), h-(border*2), 32,
									   rmask, gmask, bmask, amask);
		
		colorkey = SDL_MapRGB(surface->format, r, g, b);
		SDL_FillRect(surface2, NULL, colorkey);
		
		SDL_BlitSurface(surface2, NULL, surface, &rect);
		
		SDL_FreeSurface(surface2);
		
		return surface;
	}
	
	/*****************************
	**
	** CLASE VectorColors
	**
	******************************/
		
	VectorColors::VectorColors() {
	}
	
	VectorColors::~VectorColors() {
		colors.clear();
	}
		
	int VectorColors::getIndexColor(int r, int g, int b) {
		for (int i=0; i<(int)colors.size(); i++) {
			if ( (getColor(i)->r == r) && (getColor(i)->g == g) && (getColor(i)->b == b) ) {
				 return i;
			}
		}
		return 0;
	}
		
	Color* VectorColors::getColor(int n) {
		if (n<(int)colors.size()) {
			return &colors[n];
		} else {
			return NULL;
		}
	}
	
	
	/*****************************
	**
	** CLASE FRAME
	**
	******************************/
	
	Frame::Frame() {
		w = 0;
        h = 0;
		w_gl = 0;
        h_gl = 0;
		texture = 0;
	}
	
	Frame::~Frame() {
		unLoad();
	}
	
	int Frame::sizeTexGL(int w, int h) {
		
		int size, sizeGL;
		
		(w>h)?size=w:size=h;
		
		sizeGL = 4;
		
		while (sizeGL < size) {
			sizeGL *= 2;
		}
		
		return sizeGL;
		
		
	}
	
	SDL_Surface* Frame::SurfaceGL(SDL_Surface* sfc)
	{
		SDL_Surface *temp = SDL_DisplayFormatAlpha(sfc);
		SDL_FreeSurface(sfc);
		SDL_Surface *image;
		
		int sizeGL = sizeTexGL(temp->w, temp->h);
		
		w = temp->w;
		h = temp->h;
		w_gl = sizeGL;
		h_gl = sizeGL;
		
		Uint32 saved_flags;
		Uint8  saved_alpha;
	  
	#if SDL_BYTEORDER == SDL_BIG_ENDIAN
		  image = SDL_CreateRGBSurface(SDL_SWSURFACE, w_gl, h_gl, temp->format->BitsPerPixel,
									  0xff000000, 0x00ff0000, 0x0000ff00, 0x000000ff);
	#else
		  image = SDL_CreateRGBSurface(SDL_SWSURFACE, w_gl, h_gl, temp->format->BitsPerPixel,
									  0x000000ff, 0x0000ff00, 0x00ff0000, 0xff000000);
	#endif
		
		/* Save the alpha blending attributes */
		saved_flags = temp->flags&(SDL_SRCALPHA|SDL_RLEACCELOK);
		saved_alpha = temp->format->alpha;
		if ( (saved_flags & SDL_SRCALPHA) == SDL_SRCALPHA ) {
			SDL_SetAlpha(temp, 0, 0);
		}
		
		/*int colorkey = SDL_MapRGB(temp->format, 255, 0, 255);
		SDL_SetColorKey(image, SDL_SRCCOLORKEY, colorkey);
		SDL_FillRect(image, 0, colorkey);*/
		
	   
		SDL_BlitSurface(temp, 0, image, 0);
		
		if ( (saved_flags & SDL_SRCALPHA) == SDL_SRCALPHA ) {
			SDL_SetAlpha(temp, saved_flags, saved_alpha);
		}
		
		SDL_FreeSurface(temp);
		
		return(image);
	}
	 
	// Load Bitmaps And Convert To Textures
	void Frame::loadGL(char *path)
	{	
		// Load Texture
	
		SDL_Surface *surf, *temp;
		
		temp = IMG_Load(path);
		if ( temp == NULL ) {
			printf("Unable to load %s: %s\n", path, SDL_GetError());
		}
		
		surf = SurfaceGL(temp);
		if (!surf) {
			printf ("No se cargo la imagen: %s\n", path);
		}
		
		// Create Texture	
		
		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D , texture);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glPixelStorei(GL_UNPACK_ROW_LENGTH, surf->pitch / surf->format->BytesPerPixel);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, surf->w, surf->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, surf->pixels);
		glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);
		
		SDL_FreeSurface(surf);
	
	};

	void Frame::loadGLSurface (SDL_Surface *surface) {
		
		// Load Texture
	
		SDL_Surface *surf;
		
		surf = SurfaceGL(surface);
		
		// Create Texture	
		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);   // 2d texture (x and y size)
		
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR); // scale linearly when image bigger than texture
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR); // scale linearly when image smalled than texture
	
		
		glTexImage2D(GL_TEXTURE_2D, 0, 4, surf->w, surf->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, surf->pixels);
		glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);
		
		SDL_FreeSurface(surf);
	
	}

	void Frame::unLoad() {
		glDeleteTextures( 1, &texture );
		glBindTexture(GL_TEXTURE_2D,NULL); 
	}

	
	/*****************************
	**
	** CLASS ANIMATION
	**
	******************************/
	
	Animation::Animation() {
		name = "";
		currentFrame = -1;
		cyclesBetweenFrames = 4;
		cycles = 0;
		typeRotation = CIRCULAR_ROTATION;
		avFrame = 1;
		stopped = false;
		isLastFrame = false;
	}
	
	Animation::~Animation() {
		frame.clear();
	}
	
	void Animation::addRangeFrame(int begin, int end, int steps) {
		if (steps>0) {
			for (int i = begin; i<=end; i+=steps) {
				addFrame(i);
			}
		} else {
			for (int i = begin; i>=end; i+=steps) {
				addFrame(i);
			}
		}
			
	}
	
	int Animation::getFrame() {
		if (stopped) { 
			return getCurrentFrame();
		}
		return nextFrame();
	}
	
	int Animation::nextFrame() {
		cycles++;
		isLastFrame = false;
		if (frame.size()==0) return 0;
		if (cycles%cyclesBetweenFrames==0) {
			if ( (currentFrame == (int)frame.size()-1) && (avFrame==1) ) {
				isLastFrame = true;
				if (typeRotation == CIRCULAR_ROTATION) {
					currentFrame = 0;
				} else if (typeRotation == AHEADBACK_ROTATION) {
					currentFrame--;
					avFrame = -1;
				} else {
					currentFrame = 0;
				}
			} else if ( (currentFrame == 0) && (avFrame==-1) ) {
				if (typeRotation == CIRCULAR_ROTATION) {
					currentFrame = frame.size()-1;
				} else if (typeRotation == AHEADBACK_ROTATION) {
					currentFrame++;
					avFrame = 1;
				} else {
					currentFrame = frame.size()-1;
				}
			} else {
				currentFrame += avFrame;
			}
		}
		return frame[currentFrame];
		
	}
	
	/*****************************
	**
	** CLASS GROUP
	**
	******************************/
	
	Group::Group() {
		group = NULL;
		groupScene = NULL;
		posX = 0.0f;
		posY = 0.0f;
		posXNew = 0;
		posYNew = 0;
		polarEndX = 0;
		polarEndY = 0;
		typeMovement = MOVEMENT_DISPLACEMENT;
		isMovement = false;
		blinking = 0;
		stateBlinking = 1;
		
		nCyclesMovementNormal = 0;
		countCyclesMovementNormal = 0;
		dirX = 0;
		dirY = 0;
		dx = 0;
		dy = 0;
		cyclesFadeIn = 0;
		cyclesFadeInTotal = 0;
		cyclesFadeOut = 0;
		cyclesFadeOutTotal = 0;
		cyclesBlinking = 0;
		
		cycle = 0;
		
		oldX = 0;
		oldY = 0;
		alpha = 255;
		
		flexibleData0 = 0.7;
        flexibleData1 = 0.1;
		smoothData = 6;
		
	}
	
	void Group::setVelocitySmooth (int t) {
         switch(t) {
            case VELOCITY_VERYSLOW:
                 smoothData = 12;
            break;
            case VELOCITY_SLOW:
                 smoothData = 9;
            break;
            case VELOCITY_QUICK:
                 smoothData = 5;
            break;
            case VELOCITY_VERYQUICK:
                 smoothData = 4;
            break;
            default:
                 smoothData = 6;
            break;
         }
    }
    
	void Group::setVelocityFlexible (int t) {
         switch(t) {
            case VELOCITY_VERYSLOW:
                 flexibleData0 = 0.88;
                 flexibleData1 = 0.02;
            break;
            case VELOCITY_SLOW:
                 flexibleData0 = 0.83;
                 flexibleData1 = 0.03;
            break;
            case VELOCITY_QUICK:
                 flexibleData0 = 0.75;
                 flexibleData1 = 0.11;
            break;
            case VELOCITY_VERYQUICK:
                 flexibleData0 = 0.73;
                 flexibleData1 = 0.13;
            break;
            default:
                 flexibleData0 = 0.72;
                 flexibleData1 = 0.1;
            break;
         }
    }
	
	void Group::setCurrentScale(float s) {
		for (int i=0; i<(int)elements.size(); i++) {
			elements[i]->setCurrentScale(s);
		}
	}
    
    void Group::todoAlpha () { 
		for (int i=0; i<(int)elements.size(); i++) {
			elements[i]->setAlpha(alpha);
		}
    }
			
	float Group::getX () { 
		float fOut = 0;
		if (groupScene!=NULL) fOut+=groupScene->getX();
		if (group!=NULL) fOut+=group->getX();
		fOut+=posX;
		return fOut;
	}
	
	float Group::getY () { 
		float fOut = 0;
		if (groupScene!=NULL) fOut+=groupScene->getY();
		if (group!=NULL) fOut+=group->getY();
		fOut+=posY;
		return fOut;
	}
	
	void Group::setMovementNormal (float x, float y, int ml) {
		typeMovement = MOVEMENT_NORMAL;
		isMovement = true;
		polarEndX = x;
		polarEndY = y;
		if (polarEndX>=getX()) {
			dirX = DIR_RIGHT;
		} else {
			dirX = DIR_LEFT;
		}
		if (polarEndY>=getY()) {
			dirY = DIR_DOWN;
		} else {
			dirY = DIR_UP;
		}
		float distanceBetweenPositions = sqrt( (double) (y-getY())*(y-getY()) + (x-getX())*(x-getX()));
		float cos = (float)(y-getY())/ distanceBetweenPositions;
		float sen = (float)(x-getX())/ distanceBetweenPositions;
		setDPolarSen(sen);
		setDPolarCos(cos);
		setDPolarDistance(distanceBetweenPositions/Converter::GetInstance()->ml2cycles(ml));
		nCyclesMovementNormal = Converter::GetInstance()->ml2cycles(ml);
		countCyclesMovementNormal = 0;
	}
	
	void Group::move () { 
		if (typeMovement == MOVEMENT_NORMAL) {
    		isMovement = false;
			if ( (dirX==DIR_RIGHT) && (polarEndX>getX()) ) {
				addX( (float) (polarDistance*polarSen) );
				isMovement = true;
			}
			if ( (dirX==DIR_LEFT) && (polarEndX<getX()) ) {
				addX( (float)(polarDistance*polarSen) );
				isMovement = true;
			}
			if ( (dirY==DIR_UP) && (polarEndY<getY()) ) {
				addY( (float)(polarDistance*polarCos) );
				isMovement = true;
			}
			if ( (dirY==DIR_DOWN) && (polarEndY>getY()) ) {
				addY( (float) (polarDistance*polarCos) );
				isMovement = true;
			}
			if (isMovement) countCyclesMovementNormal++;
		} else if (typeMovement == MOVEMENT_SMOOTH) {
            isMovement = false;
			if (posX!=posXNew) { 
				addX( ((posXNew-posX)/smoothData) ); 
				isMovement = true;
				if (oldX == posX) {
					posX = posXNew;
				}
			}
			if (posY!=posYNew) { 
				addY( ((posYNew-posY)/smoothData) ); 
				isMovement = true;
				if (oldY == posY) {
					posY = posYNew;
				}
			}
		} else if (typeMovement == MOVEMENT_FLEXIBLE) {
			xs = (float) (xs*flexibleData0+(posXNew-posX)*flexibleData1); 
			ys = (float) (ys*flexibleData0+(posYNew-posY)*flexibleData1); 
			addX( xs ); 
			addY( ys ); 
		} else if (typeMovement == MOVEMENT_DISPLACEMENT) {
			addX( dx ); 
			addY( dy ); 
		}
	}
	
	void Group::work () {
		
		cycle++;
		
		move();
		
		if (cyclesBlinking>0) {
		
			if (blinking >0) {
				if (cycle%blinking==0) {
					if (stateBlinking==0) {
						stateBlinking = 1;
					} else {
						stateBlinking = 0;
					}
				}
			}
			
			cyclesBlinking--;
			
			if ( (blinking >0) && (stateBlinking==0) ) {
				for (int i=0; i<(int)elements.size(); i++) {
					elements[i]->hide();
				}
			} else {
				for (int i=0; i<(int)elements.size(); i++) {
					elements[i]->show();
				}
			}				
			
		}
		bool changeAlpha = false;
		if (cyclesFadeIn>0) {
            changeAlpha = true;
			cyclesFadeIn--;
			alpha = (255/cyclesFadeInTotal) * (cyclesFadeInTotal - cyclesFadeIn);
			if (cyclesFadeIn == 0) {
				alpha = 255;
			}
		}
		
		if (cyclesFadeOut>0) {
            changeAlpha = true;
			cyclesFadeOut--;
			alpha = 255 - ((255/cyclesFadeOutTotal) * (cyclesFadeOutTotal - cyclesFadeOut));
			if (cyclesFadeOut == 0) {
				alpha = 0;
			}
		}
		if (changeAlpha) {
    		for (int i=0; i<(int)elements.size(); i++) {
    			elements[i]->setAlpha(alpha);
    		}	
        }
	}
	
	void Group::draw () {
		for (int i=0; i<(int)elements.size(); i++) {
			elements[i]->draw();
		}	
    }
    
	void Group::unLoad () {
		for (int i=0; i<(int)elements.size(); i++) {
			delete elements[i];
		}	
    }
    
	/*****************************
	**
	** CLASS MarqueeElement
	**
	******************************/

	MarqueeElement::MarqueeElement() : AnimatedElement () {
        text = "";
        nLetters = 0;
	}	
	
	
	MarqueeElement::~MarqueeElement () {
		unLoad();
	}
	
	void MarqueeElement::setText(string font, string t, int nl) {
		text = t;
		nLetters = nl;
        Animation a;
        a.setName("marquee");
        a.setCyclesBetweenFrames(15);
		if (nLetters>=(int)text.length()) {
             addFrameText(font, text, ALIGN_CENTER);
             a.addFrame(0);
        } else {
             bool sw = true;
             for (int i=0; i<(int)text.length(); i++) {
            	string s = "";
                if ( (sw) && (i<nLetters) ) {
                	for (int j=0; j<nLetters-i; j++) {
                        s = s + " ";
                    }
                    s = s + text.substr(0, i);
                } else if ( (sw) && (i==nLetters) ) {
                    i = -1;
                    sw = false;
                    continue;
                } else {
                    s = s + text.substr(i, nLetters);
                    int size = nLetters-(int)s.length();
                    for (int j=0; j<size; j++) {
                        s = s + " ";
                    }
                }
            	addFrameText(font, s, ALIGN_CENTER);
             }
             a.addRangeFrame(0, text.length()+nLetters-1, 1);
        }

        addAnimation(a);
        setAnimation("marquee");
        
    }
	
	/*****************************
	**
	** CLASS GroupScene
	**
	******************************/

	GroupScene::GroupScene() : Group () {
	}	
	
	/*****************************
	**
	** CLASS ELEMENT
	**
	******************************/
	
	Element::Element() {
		group = NULL;
		groupScene = NULL;
		
		perspectiveX1 = 0;
		perspectiveY1 = 0;
		perspectiveX2 = 0;
		perspectiveY2 = 0;
		perspectiveX3 = 0;
		perspectiveY3 = 0;
		perspectiveX4 = 0;
		perspectiveY4 = 0;
		
		factorMaskW = 1.0; 
        factorMaskH = 1.0; 
		flip = false;
		flop = false;
		indexz = 0;
		typeMovement = MOVEMENT_DISPLACEMENT;
		isMovement = false;
		cycle = 0;
		blinking = 0;
		stateBlinking = 1;
		activeBlinking = false;
		cFrame = 0;
		posX = 0;
		posY = 0;
		posXNew = 0;
		posYNew = 0;
		polarEndX = 0;
		polarEndY = 0;
		nCyclesMovementNormal = 0;
		countCyclesMovementNormal = 0;
		dirX = 0;
		dirY = 0;
		dx = 0;
		dy = 0;
		cyclesFadeIn = 0;
		cyclesFadeInTotal = 0;
		cyclesFadeOut = 0;
		cyclesFadeOutTotal = 0;
		cyclesBlinking = 0;

		red = 255;
		green = 255;
		blue = 255;
		
		// rotate
		typeScale = ROTATE_NORMAL;
		forceRotateCenter = false;
		rot = 0.0f;
		rotX = 0.0f;
		rotY = 0.0f;
		rotZ = 1.0f;
		endRotate = 0.0f;
		factorRotate = 0.0f;
		sRotate = 0.0f;
		canRotate = false;
		// scale
		canScale = false;
		typeScale = SCALE_NORMAL;
		factorScaleX = 0.0;
		factorScaleY = 0.0;
		currentScaleX = 1.0;
		currentScaleY = 1.0;
		endScaleX = 0.0; 
		endScaleY = 0.0;
		xsScale = 0.0;
		ysScale = 0.0;

		visible = true;
		oldX = 0;
		oldY = 0;
		alpha = 255;
		
		toDoAllEffects = true;
		
		align = ALIGN_LEFT;
		valign = VALIGN_TOP;
		
		flexibleData0 = 0.7;
        flexibleData1 = 0.1;
		smoothData = 6;
		
		hasBorder = false;
		showBorderElement = false;
		
		hasBackground = false;
		showBackgroundElement = false;
	}
	
	Element::~Element() {
		unLoad();
	}
	
	void Element::setPerspective(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4) {
		perspectiveX1 = x1;
		perspectiveY1 = y1;
		perspectiveX2 = x2;
		perspectiveY2 = y2;
		perspectiveX3 = x3;
		perspectiveY3 = y3;
		perspectiveX4 = x4;
		perspectiveY4 = y4;
	}
	
	void Element::setPerspectiveRelative(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4) {
		perspectiveX1 = getWidthOriginal()*x1;
		perspectiveY1 = getHeightOriginal()*y1;
		perspectiveX2 = getWidthOriginal()*x2;
		perspectiveY2 = getHeightOriginal()*y2;
		perspectiveX3 = getWidthOriginal()*x3;
		perspectiveY3 = getHeightOriginal()*y3;
		perspectiveX4 = getWidthOriginal()*x4;
		perspectiveY4 = getHeightOriginal()*y4;
	}
	
	void Element::createBorder(int r, int g, int b, int border, int padding) {
		
		int w=0, h=0;
		
		for (int i=0; i<(int)sprite.size(); i++) {
			if (sprite[i]->w > w) {
				w = sprite[i]->w;
			}
			if (sprite[i]->h > h) {
				h = sprite[i]->h;
			}
		}
		
		hasBorder = true;
		elmBorder = new Element();
		elmBorder->setAlign(ALIGN_CENTER);
		elmBorder->setVAlign(VALIGN_CENTER);
		elmBorder->setRGB(r,g,b);
		elmBorder->addFrameSurface(Primitives::GetInstance()->border(w+(padding*2), h+(padding*2), 255, 255, 255, border));
    }
	
	void Element::createBackground(int r, int g, int b, int padding) {
		
		int w=0, h=0;
		
		for (int i=0; i<(int)sprite.size(); i++) {
			if (sprite[i]->w > w) {
				w = sprite[i]->w;
			}
			if (sprite[i]->h > h) {
				h = sprite[i]->h;
			}
		}
		
		hasBackground = true;
		elmBackground = new Element();
		elmBackground->setAlign(ALIGN_CENTER);
		elmBackground->setVAlign(VALIGN_CENTER);
		elmBackground->setRGB(r,g,b);
		elmBackground->addFrameSurface(Primitives::GetInstance()->rectangle(w+((padding-1)*2), h+((padding-1)*2), 255, 255, 255));
    }
		
	void Element::setVelocitySmooth (int t) {
         switch(t) {
            case VELOCITY_VERYSLOW:
                 smoothData = 12;
            break;
            case VELOCITY_SLOW:
                 smoothData = 9;
            break;
            case VELOCITY_QUICK:
                 smoothData = 5;
            break;
            case VELOCITY_VERYQUICK:
                 smoothData = 4;
            break;
            default:
                 smoothData = 6;
            break;
         }
    }
    
	void Element::setVelocityFlexible (int t) {
         switch(t) {
            case VELOCITY_VERYSLOW:
                 flexibleData0 = 0.88;
                 flexibleData1 = 0.02;
            break;
            case VELOCITY_SLOW:
                 flexibleData0 = 0.83;
                 flexibleData1 = 0.03;
            break;
            case VELOCITY_QUICK:
                 flexibleData0 = 0.75;
                 flexibleData1 = 0.11;
            break;
            case VELOCITY_VERYQUICK:
                 flexibleData0 = 0.73;
                 flexibleData1 = 0.13;
            break;
            default:
                 flexibleData0 = 0.72;
                 flexibleData1 = 0.1;
            break;
         }
    }
	
	float Element::getValueXPlusGroups (float x) { 
		float fOut = 0;
		if (groupScene!=NULL) fOut+=groupScene->getX();
		if (group!=NULL) fOut+=group->getX();
		fOut+=x;
		return fOut;
	}
	
	float Element::getValueYPlusGroups (float y) { 
		float fOut = 0;
		if (groupScene!=NULL) fOut+=groupScene->getY();
		if (group!=NULL) fOut+=group->getY();
		fOut+=y;
		return fOut;
	}
	
	float Element::getDisplacementInXByGroups () { 
		float fOut = 0;
		if (groupScene!=NULL) fOut+=groupScene->getX();
		if (group!=NULL) fOut+=group->getX();
		return fOut;
	}
	
	Position Element::getCenterPosition() {
		Position p;
		switch (align) {
			case ALIGN_LEFT:
				p.x = getX()+(getWidth()/2);
			break;
			case ALIGN_CENTER:
				p.x = getX();
			break;
			case ALIGN_RIGHT:
				p.x = getX()-(getWidth()/2);
			break;
		}
		switch (valign) {
			case VALIGN_TOP:
				p.y = getY()+(getHeight()/2);
			break;
			case VALIGN_CENTER:
				p.y = getY();
			break;
			case VALIGN_BOTTOM:
				p.y = getY()-(getHeight()/2);
			break;
		}
		return p;
	}
	
	Bounds Element::getBounds() {
		Bounds b;
		
		float x1 = 0, y1 = 0;
		float x2 = 0, y2 = 0;
		
		if (getAlign() == ALIGN_LEFT) {
			x1 = getX();
		} else if (getAlign() == ALIGN_CENTER) {
			x1 = getX() - (getWidth()/2);
		} else if (getAlign() == ALIGN_RIGHT) {
			x1 = getX() - getWidth();
		}
		
		if (getVAlign() == VALIGN_TOP) {
			y1 = getY();
		} else if (getVAlign() == VALIGN_CENTER) {
			y1 = getY() - (getHeight()/2);
		} else if (getVAlign() == VALIGN_BOTTOM) {
			y1 = getY() - getHeight();
		}
		
		float x2aux1 = x1 + getWidth() + (perspectiveX2*currentScaleX);
		float x2aux2 = x1 + getWidth() + (perspectiveX4*currentScaleX);
		
		if (x2aux1>x2aux2) {
			x2 = x2aux1;
		} else {
			x2 = x2aux2;
		}
		
		float y2aux1 = y1 + getHeight() + (perspectiveY3*currentScaleY);
		float y2aux2 = y1 + getHeight() + (perspectiveY4*currentScaleY);
		
		if (y2aux1>y2aux2) {
			y2 = y2aux1;
		} else {
			y2 = y2aux2;
		}
		
		float x1aux1 = x1 + (perspectiveX1*currentScaleX);
		float x1aux2 = x1 + (perspectiveX3*currentScaleX);
		
		if (x1aux1<x1aux2) {
			x1 = x1aux1;
		} else {
			x1 = x1aux2;
		}
		
		float y1aux1 = y1 + (perspectiveY1*currentScaleY);
		float y1aux2 = y1 + (perspectiveY2*currentScaleY);
		
		if (y1aux1<y1aux2) {
			y1 = y1aux1;
		} else {
			y1 = y1aux2;
		}
		
		b.x1 = x1;
		b.y1 = y1;
		b.x2 = x2;
		b.y2 = y2;
		
		return b;
	}
	
	float Element::getX () { 
		return getDisplacementInXByGroups () + posX;
	}
	
	float Element::getDisplacementInYByGroups () { 
		float fOut = 0;
		if (groupScene!=NULL) fOut+=groupScene->getY();
		if (group!=NULL) fOut+=group->getY();
		return fOut;
	}
	
	float Element::getY () { 
		return getDisplacementInYByGroups () + posY;
	}
	
	int Element::getLimitBottom () { 
		return World::height + (getHeight() * 2) -5; 
	}
	
	int Element::getLimitRight () { 
		return World::width + getWidth() * 2 -5; 
	}
	
	bool Element::outLimitScreen() {
		if ( ( getY() < getLimitTop() ) || ( getY() > getLimitBottom() ) || ( getX() < getLimitLeft() ) || ( getX() > getLimitRight() ) ){ 
			return 1;
		} else {
			return 0;
		}
	}
	
	void Element::unLoad() {
		int i;
		for (i=0; i<(int)sprite.size(); i++)
			delete sprite[i];
		
		parameters.clear();
		sprite.clear();
		if (hasBorder) elmBorder->unLoad();
		if (hasBackground) elmBackground->unLoad();
	}
	
	void Element::addFrame (Frame* frame) {
		sprite.push_back(frame);
	}
	
	void Element::addFrame (string file) {
		Frame *fr = new Frame();
		if (WorkingData::GetInstance()->existFile(file)) {
		   fr->loadGL((char*)file.c_str());
        } else {
           fr->loadGLSurface(Primitives::GetInstance()->rectangle(1, 1, 0, 0, 0));
           printf("Don't exist the file %s\n", file.c_str());
        }
		addFrame(fr);
	}
	
	void Element::changeFrame (int position, Frame *frame) {
        delete sprite[position];
		sprite[position] = frame;
	}
	
	void Element::changeFrame (int position, string file) {
		Frame *fr = new Frame();
		if (WorkingData::GetInstance()->existFile(file)) {
		   fr->loadGL((char*)file.c_str());
        } else {
           fr->loadGLSurface(Primitives::GetInstance()->rectangle(1, 1, 0, 0, 0));
           printf("Don't exist the file %s\n", file.c_str());
        }
		changeFrame (position, fr);
	}
	
	void Element::addFrameFile (string file) {
		addFrame(file);
	}
	
	void Element::addFrameFile (string name, string ext, int valueInRange) {
		string chain = name + string("_");
		char numbers[4];
		sprintf(numbers, "%d", valueInRange);
		if ( (valueInRange>=0) && (valueInRange<10) ) {
			chain += "000" + string(numbers);
		} else if ( (valueInRange>=10) && (valueInRange<100) ) {
			chain += "00" + string(numbers);
		} else if ( (valueInRange>=100) && (valueInRange<1000) ) {
			chain += "0" + string(numbers);
		} else if ( (valueInRange>=1000) && (valueInRange<10000) ) {
			chain += string(numbers);
		} else {
			chain += "0000";
		}
		chain += string(".") + ext;
		addFrameFile(chain);
	}
	
	void Element::addFrameFileFromData (string file) {
		addFrame((string)DATA_DIR + file);
    }
	
	void Element::addFrameFileFromData (string name, string ext, int valueInRange) {
		string chain = name + string("_");
		char numbers[4];
		sprintf(numbers, "%d", valueInRange);
		if ( (valueInRange>=0) && (valueInRange<10) ) {
			chain += "000" + string(numbers);
		} else if ( (valueInRange>=10) && (valueInRange<100) ) {
			chain += "00" + string(numbers);
		} else if ( (valueInRange>=100) && (valueInRange<1000) ) {
			chain += "0" + string(numbers);
		} else if ( (valueInRange>=1000) && (valueInRange<10000) ) {
			chain += string(numbers);
		} else {
			chain += "0000";
		}
		chain += string(".") + ext;
		addFrameFileFromData(chain);
	}
    
	void Element::addFrameText (string font, string text, int align) {
    	Frame *fr = new Frame();
    	fr->loadGLSurface(Fonts::GetInstance()->getSurface_TextBitMap(font, align, (char*)text.c_str()));
		addFrame(fr);
    }
	
	void Element::addFrameText (string font, string text, int align, int width) {
    	Frame *fr = new Frame();
    	fr->loadGLSurface(Fonts::GetInstance()->getSurface_TextBitMap(font, currentScaleX, width, align, (char*)text.c_str()));
		addFrame(fr);
    }
    
	void Element::addFrameLanguage (string font, string key, int align) {
		addFrameSurface(Fonts::GetInstance()->getSurface_TextBitMap(font, align, (char*)Language::GetInstance()->getText(key).c_str()));
    }
	
	void Element::addFrameLanguage (string font, string key, int align, int width) {
		addFrameSurface(Fonts::GetInstance()->getSurface_TextBitMap(font, currentScaleX, width, align, (char*)Language::GetInstance()->getText(key).c_str()));
    }
    
	void Element::addFrameSurface (SDL_Surface *sfc) {
    	Frame *fr = new Frame();
    	fr->loadGLSurface(sfc);
		addFrame(fr);
    }
	
	void Element::changeFrameFile (int pos, string file) {
		changeFrame(pos, file);
	}
	
	void Element::changeFrameFile (int pos, string name, string ext, int valueInRange) {
		string chain = name + string("_");
		char numbers[4];
		sprintf(numbers, "%d", valueInRange);
		if ( (valueInRange>=0) && (valueInRange<10) ) {
			chain += "000" + string(numbers);
		} else if ( (valueInRange>=10) && (valueInRange<100) ) {
			chain += "00" + string(numbers);
		} else if ( (valueInRange>=100) && (valueInRange<1000) ) {
			chain += "0" + string(numbers);
		} else if ( (valueInRange>=1000) && (valueInRange<10000) ) {
			chain += string(numbers);
		} else {
			chain += "0000";
		}
		chain += string(".") + ext;
		changeFrameFile(pos, chain);
	}
	
	void Element::changeFrameFileFromData (int pos, string file) {
		changeFrame(pos, (string)DATA_DIR + file);
    }
	
	void Element::changeFrameFileFromData (int pos, string name, string ext, int valueInRange) {
		string chain = name + string("_");
		char numbers[4];
		sprintf(numbers, "%d", valueInRange);
		if ( (valueInRange>=0) && (valueInRange<10) ) {
			chain += "000" + string(numbers);
		} else if ( (valueInRange>=10) && (valueInRange<100) ) {
			chain += "00" + string(numbers);
		} else if ( (valueInRange>=100) && (valueInRange<1000) ) {
			chain += "0" + string(numbers);
		} else if ( (valueInRange>=1000) && (valueInRange<10000) ) {
			chain += string(numbers);
		} else {
			chain += "0000";
		}
		chain += string(".") + ext;
		changeFrameFileFromData(pos, chain);
	}
    
	void Element::changeFrameText (int pos, string font, string text, int align) {
    	Frame *fr = new Frame();
    	fr->loadGLSurface(Fonts::GetInstance()->getSurface_TextBitMap(font, align, (char*)text.c_str()));
		changeFrame(pos, fr);
    }
	
	void Element::changeFrameText (int pos, string font, string text, int align, int width) {
    	Frame *fr = new Frame();
    	fr->loadGLSurface(Fonts::GetInstance()->getSurface_TextBitMap(font, currentScaleX, width, align, (char*)text.c_str()));
		changeFrame(pos, fr);
    }
    
	void Element::changeFrameLanguage (int pos, string font, string key, int align) {
    	Frame *fr = new Frame();
    	fr->loadGLSurface(Fonts::GetInstance()->getSurface_TextBitMap(font, align, (char*)Language::GetInstance()->getText(key).c_str()));
		changeFrame(pos, fr);
    }
    
	void Element::changeFrameLanguage (int pos, string font, string key, int align, int width) {
    	Frame *fr = new Frame();
    	fr->loadGLSurface(Fonts::GetInstance()->getSurface_TextBitMap(font, currentScaleX, width, align, (char*)Language::GetInstance()->getText(key).c_str()));
		changeFrame(pos, fr);
    }
	
	void Element::changeFrameSurface (int pos, SDL_Surface *sfc) {
    	Frame *fr = new Frame();
    	fr->loadGLSurface(sfc);
		changeFrame(pos, fr);
    }
    	
	void Element::addRangeFrames (string name, string ext, int valBeg, int valEnd) {
		char tmp[128];
		string chain;
		
		for (int i=valBeg; i<=valEnd; i++) {
			chain = name + string("_");
			chain += Converter::GetInstance()->fillZeros(i);
			chain += string(".") + ext;
			strcpy(tmp, chain.c_str());
			Frame *fr = new Frame();
			fr->loadGL(tmp);
			this->addFrame(fr);
		}
	}
	
	void Element::addRangeFramesFromData (string name, string ext, int valBeg, int valEnd) {
		char tmp[128];
		string chain;
		
		for (int i=valBeg; i<=valEnd; i++) {
			chain = DATA_DIR + string("/") + name + string("_");
			chain += Converter::GetInstance()->fillZeros(i);
			chain += string(".") + ext;
			strcpy(tmp, chain.c_str());
			Frame *fr = new Frame();
			fr->loadGL(tmp);
			this->addFrame(fr);
		}
	}
		
	void Element::setRotationNormal ( float degreesEnd, int ml) {
		typeRotate = ROTATE_NORMAL;
		
		endRotate = degreesEnd;
		
		factorRotate = (degreesEnd-rot) / Converter::GetInstance()->ml2cycles(ml);
		
		canRotate = true;
		
	}
	
	void Element::setRotationNormal (float degreesBegin, float degreesEnd, int ml) {
		typeRotate = ROTATE_NORMAL;
		
		endRotate = degreesEnd;
		rot = degreesBegin;
		
		factorRotate = (degreesEnd-rot) / Converter::GetInstance()->ml2cycles(ml);
		
		canRotate = true;
		
	}
	
	void Element::setRotationSmooth (float degreesEnd) {
		typeRotate = ROTATE_SMOOTH;
		
		endRotate = degreesEnd;
		
		canRotate = true;
		
	}
	
	void Element::setRotationFlexible (float degreesEnd) {
		
		typeRotate = ROTATE_FLEXIBLE;
		canRotate = true;
		
		endRotate = degreesEnd;
		
		/*while(rot>360) {
			rot = 360%(int)endRotate;
		}
		if (rot==360) rot = 0;*/
		
	}
	
	void Element::setScale (float w, float h) {
				
		currentScaleX = w/getWidthOriginal();
		currentScaleY = h/getHeightOriginal();		
		
	}
	
	void Element::setScale (float w, float h, int mlRoute) {
		
		typeScale = SCALE_NORMAL;
		canScale = true;
		
		endScaleX = w/getWidthOriginal();
		endScaleY = h/getHeightOriginal();
		
		factorScaleX = (endScaleX-currentScaleX) / Converter::GetInstance()->ml2cycles(mlRoute);
		factorScaleY = (endScaleY-currentScaleY) / Converter::GetInstance()->ml2cycles(mlRoute);
		
	}
	
	void Element::setScaleSmooth (float w, float h) {
		
		typeScale = SCALE_SMOOTH;
		canScale = true;
		
		endScaleX = w/getWidthOriginal();
		endScaleY = h/getHeightOriginal();
		
	}
	
	void Element::setScaleFlexible (float w, float h) {
		
		typeScale = SCALE_FLEXIBLE;
		canScale = true;
		
		endScaleX = w/getWidthOriginal();
		endScaleY = h/getHeightOriginal();
		
	}
	
	void Element::transforms () { 
		// rotate
		
		if (canRotate) {
			if (typeRotate==ROTATE_NORMAL) {
				rot += factorRotate;
				if (factorRotate>0)	{
					if (rot>endRotate) {
						canRotate = false;
						rot = (float)((int)endRotate%360);
					}
				} else {
					if (rot<endRotate) {
						canRotate = false;
						rot = (float)((int)endRotate%360);
					}
				}
			} else if (typeRotate==ROTATE_SMOOTH) {
				rot += (endRotate-rot)/smoothData;
				if ((endRotate-rot)>0) {
					if ((int)rot+1>=(int)endRotate) {
						canRotate = false;
						rot = (float)((int)endRotate%360);
					}
				} else {
					if ((int)rot-1<=(int)endRotate) {
						canRotate = false;
						rot = (float)((int)endRotate%360);
					}
				}
			} else if (typeRotate==ROTATE_FLEXIBLE) {
				sRotate = (float) (sRotate*flexibleData0+(endRotate-rot)*flexibleData1); 
				rot += sRotate;
			}
		}
		
		// scale
		if (canScale) {
			if (typeScale==SCALE_NORMAL) {
				currentScaleX += factorScaleX;
				currentScaleY += factorScaleY;
				if (factorScaleX>=0) {
					if (currentScaleX>=endScaleX) {
						currentScaleX=endScaleX;
						canScale = false;
					}
				} else {
					if (currentScaleX<=endScaleX) {
						currentScaleX=endScaleX;
						canScale = false;
					}
				}
				if (factorScaleY>=0) {
					if (currentScaleY>=endScaleY) {
						currentScaleY=endScaleY;
						canScale = false;
					}
				} else {
					if (currentScaleY<=endScaleY) {
						currentScaleY=endScaleY;
						canScale = false;
					}
				}
			} else if (typeScale==SCALE_SMOOTH) {
				currentScaleX += (endScaleX-currentScaleX)/smoothData;
				currentScaleY += (endScaleY-currentScaleY)/smoothData;
				if (currentScaleX>=endScaleX) {
					currentScaleX=endScaleX;
					canScale = false;
				}
				if (currentScaleY>=endScaleY) {
					currentScaleY=endScaleY;
					canScale = false;
				}
			} else if (typeScale==SCALE_FLEXIBLE) {
				xsScale = (float) (xsScale*flexibleData0+(endScaleX-currentScaleX)*flexibleData1); 
				ysScale = (float) (ysScale*flexibleData0+(endScaleY-currentScaleY)*flexibleData1); 
				currentScaleX += xsScale;
				currentScaleY += ysScale;
				/*if (currentScaleX>=endScaleX) {
					currentScaleX=endScaleX;
					canScale = false;
				}
				if (currentScaleY>=endScaleY) {
					currentScaleY=endScaleY;
					canScale = false;
				}*/
			}
		}
		
	}
	
	void Element::setMovementNormal (float x, float y, int ml) {
		typeMovement = MOVEMENT_NORMAL;
		isMovement = true;
		x = getValueXPlusGroups(x);
		y = getValueYPlusGroups(y);
		polarEndX = x;
		polarEndY = y;
		if (polarEndX>=getX()) {
			dirX = DIR_RIGHT;
		} else {
			dirX = DIR_LEFT;
		}
		if (polarEndY>=getY()) {
			dirY = DIR_DOWN;
		} else {
			dirY = DIR_UP;
		}
		float distanceBetweenPositions = sqrt( (double) (y-getY())*(y-getY()) + (x-getX())*(x-getX()));
		float cos = (float)(y-getY())/ distanceBetweenPositions;
		float sen = (float)(x-getX())/ distanceBetweenPositions;
		setDPolarSen(sen);
		setDPolarCos(cos);
		setDPolarDistance(distanceBetweenPositions/Converter::GetInstance()->ml2cycles(ml));
		nCyclesMovementNormal = Converter::GetInstance()->ml2cycles(ml);
		countCyclesMovementNormal = 0;
	}
	
	void Element::move () { 
		if (typeMovement == MOVEMENT_NORMAL) {
    		isMovement = false;
			if ( (dirX==DIR_RIGHT) && (polarEndX>getX()) ) {
				addX( (float) (polarDistance*polarSen) );
				isMovement = true;
			}
			if ( (dirX==DIR_LEFT) && (polarEndX<getX()) ) {
				addX( (float)(polarDistance*polarSen) );
				isMovement = true;
			}
			if ( (dirY==DIR_UP) && (polarEndY<getY()) ) {
				addY( (float)(polarDistance*polarCos) );
				isMovement = true;
			}
			if ( (dirY==DIR_DOWN) && (polarEndY>getY()) ) {
				addY( (float) (polarDistance*polarCos) );
				isMovement = true;
			}
			if (isMovement) countCyclesMovementNormal++;
		} else if (typeMovement == MOVEMENT_SMOOTH) {
            isMovement = false;
			if (posX!=posXNew) { 
				addX( ((posXNew-posX)/smoothData) ); 
				isMovement = true;
				if (oldX == posX) {
					posX = posXNew;
				}
			}
			if (posY!=posYNew) { 
				addY( ((posYNew-posY)/smoothData) ); 
				isMovement = true;
				if (oldY == posY) {
					posY = posYNew;
				}
			}
		} else if (typeMovement == MOVEMENT_FLEXIBLE) {
			xs = (float) (xs*flexibleData0+(posXNew-posX)*flexibleData1); 
			ys = (float) (ys*flexibleData0+(posYNew-posY)*flexibleData1); 
			addX( xs ); 
			addY( ys ); 
		} else if (typeMovement == MOVEMENT_DISPLACEMENT) {
			addX( dx ); 
			addY( dy ); 
		}
	}
	
	void Element::draw () {
		if ((int)sprite.size()>0) {
			if (toDoAllEffects) {
				move();
				transforms();
			}
			paintSprite();
		}
	}
	
	void Element::paintSprite () {
	
		cycle++;
		
		if (!visible) return;
		
		if ( (hasBackground) && (showBackgroundElement) ) {
			elmBackground->setCurrentScaleX(currentScaleX);
			elmBackground->setCurrentScaleY(currentScaleY);
			elmBackground->setX(getCenterPosition().x);
			elmBackground->setY(getCenterPosition().y);
			elmBackground->setAlpha(getAlpha());
			elmBackground->draw();
        }
		
		if ( (hasBorder) && (showBorderElement) ) {
			elmBorder->setCurrentScaleX(currentScaleX);
			elmBorder->setCurrentScaleY(currentScaleY);
			elmBorder->setX(getCenterPosition().x);
			elmBorder->setY(getCenterPosition().y);
			elmBorder->setAlpha(getAlpha());
			elmBorder->draw();
        }
					
		if (activeBlinking) {
			
			if (blinking >0) {
				if (cycle%blinking==0) {
					if (stateBlinking==0) {
						stateBlinking = 1;
					} else {
						stateBlinking = 0;
					}
				}
			}
						
			if ( (blinking >0) && (stateBlinking==0) ) {
				return;
			}
			
		} else {
		
			if (cyclesBlinking>0) {
			
				if (blinking >0) {
					if (cycle%blinking==0) {
						if (stateBlinking==0) {
							stateBlinking = 1;
						} else {
							stateBlinking = 0;
						}
					}
				}
				
				cyclesBlinking--;
				
				if ( (blinking >0) && (stateBlinking==0) ) {
					return;
				}
							
			}
			
		}
		
		float relW = ((float)sprite[cFrame]->w/(float)sprite[cFrame]->w_gl)*factorMaskW;
		float relH = ((float)sprite[cFrame]->h/(float)sprite[cFrame]->h_gl)*factorMaskH;
		float auxCSX = currentScaleX;
		float auxCSY = currentScaleY;
		currentScaleX -= (1.0 - factorMaskW);
		currentScaleY -= (1.0 - factorMaskH);
		
		float cornerx1, cornerx2, cornery1, cornery2;
		
		if (forceRotateCenter) {
		
			cornerx1 = -getWidth()/2;
			cornerx2 = getWidth()/2;
			cornery1 = -getHeight()/2;
			cornery2 = getHeight()/2;
		
		} else {
			
			switch (align)
			{
				case ALIGN_CENTER:
					cornerx1 = -getWidth()/2;
					cornerx2 = getWidth()/2;
					break;
				case ALIGN_RIGHT:
					cornerx1 = -getWidth();
					cornerx2 = 0;
					break;
				default:
					cornerx1 = 0;
					cornerx2 = getWidth();
					break;
			}
			
			switch (valign)
			{
				case VALIGN_CENTER:
					cornery1 = -getHeight()/2;
					cornery2 = getHeight()/2;
					break;
				case VALIGN_BOTTOM:
					cornery1 = -getHeight();
					cornery2 = 0;
					break;
				default:
					cornery1 = 0;
					cornery2 = getHeight();
					break;
			}
			
		}
				
		float posx1, posy1;
		
		if (forceRotateCenter) {
			switch (align)
			{
				case ALIGN_CENTER:
					posx1 = getX();
					break;
				case ALIGN_RIGHT:
					posx1 = getX()-getWidth()/2;
					break;
				default:
					posx1 = getX()+getWidth()/2;
					break;
			}
			
			switch (valign)
			{
				case VALIGN_CENTER:
					posy1 = getY();
					break;
				case VALIGN_BOTTOM:
					posy1 = getY()-getHeight()/2;
					break;
				default:
					posy1 = getY()+getHeight()/2;
					break;
			}

		} else {
			posx1 = getX();
			posy1 = getY();
		}
			
	
		glPushMatrix();
		
		glEnable(GL_TEXTURE_2D);
		
		
		if (toDoAllEffects) {
		
			if (flip) {
				float aux;
				aux = cornerx1;
				cornerx1 = cornerx2;
				cornerx2 = aux;
			}
			
			if (flop) {
				float aux;
				aux = cornery1;
				cornery1 = cornery2;
				cornery2 = aux;
			}
			
			glColor4ub(red,green,blue,alpha); 
			
			glTranslatef(posx1, posy1, 0);
			
			//glScalef(currentScaleX,currentScaleY,1.0); 
		
			if (rot!=0)
				glRotatef(rot, rotX, rotY, rotZ);
			
			// alpha
			// fade in
			
			if (cyclesFadeIn>0) {
				cyclesFadeIn--;
				alpha = (255/cyclesFadeInTotal) * (cyclesFadeInTotal - cyclesFadeIn);
				if (cyclesFadeIn == 0) {
					alpha = 255;
				}
			}
			
			if (cyclesFadeOut>0) {
				cyclesFadeOut--;
				alpha = 255 - ((255/cyclesFadeOutTotal) * (cyclesFadeOutTotal - cyclesFadeOut));
				if (cyclesFadeOut == 0) {
					alpha = 0;
				}
			}
						
		} else {
			
			glColor4ub(red,green,blue,alpha); 
			
			glTranslatef(posx1, posy1, 0);
			
			if (rot!=0)
				glRotatef(rot, rotX, rotY, rotZ);
						
		}
		
		float x1 = cornerx1 + (perspectiveX1*currentScaleX);
		float y1 = cornery1 + (perspectiveY1*currentScaleY);
		float x2 = cornerx2 + (perspectiveX2*currentScaleX);
		float y2 = cornery1 + (perspectiveY2*currentScaleY);
		float x3 = cornerx1 + (perspectiveX3*currentScaleX);
		float y3 = cornery2 + (perspectiveY3*currentScaleY);
		float x4 = cornerx2 + (perspectiveX4*currentScaleX);
		float y4 = cornery2 + (perspectiveY4*currentScaleY);
		
		glBindTexture(GL_TEXTURE_2D, sprite[cFrame]->texture);

		glBegin(GL_QUADS);
		  glTexCoord2f(0.0f, relH);
		  glVertex2f(x3, y3);
		  glTexCoord2f(relW, relH);
		  glVertex2f(x4, y4);
		  glTexCoord2f(relW, 0.0f);
		  glVertex2f(x2, y2);
		  glTexCoord2f(0.0f, 0.0f);
		  glVertex2f(x1, y1);
		glEnd(); 
		
		//glDisable(GL_BLEND);
		glDisable(GL_TEXTURE_2D);
		
		currentScaleX = auxCSX;
		currentScaleY = auxCSY;
		
		glColor4ub(255,255,255,255); 
		
		glPopMatrix();
		
	}
	
	/*****************************
	**
	** CLASS ANIMATEDELEMENT
	**
	******************************/
	
	AnimatedElement::AnimatedElement()  : Element () {
		currentAnimation = -1;
		defaultAnimation = -1;
		numberOfTimes = -1;
		countNumberOfTimes = 0;
	}
	
	AnimatedElement::~AnimatedElement() {
		unLoad();
	}
	
	int AnimatedElement::getNextFrame () {
		int af = 0;
		int ani = -1;
		if (currentAnimation == -1) {
			if (defaultAnimation == -1) {
				af = 0;
			} else {
				ani = defaultAnimation;
			}
		} else {
			ani = currentAnimation;
		}
		
		if (ani == -1) {
			af = 0;
		} else {
			
			if ( (animations[ani].getIndexFrame()==animations[ani].lastFrame()) 
					&& (animations[ani].getCycleInFrame()==animations[ani].getCyclesBetweenFrames()-1) ) {
				if (numberOfTimes>=0) {
					if (countNumberOfTimes>=numberOfTimes) {
						animations[ani].stop();
					} else {
						countNumberOfTimes++;
					}
				} else {
					if ((int)nextsAnimations.size()>0) {
						currentAnimation = nextsAnimations[0].animation;
						numberOfTimes = nextsAnimations[0].numberOfTimes;
						countNumberOfTimes = 0;
						animations[currentAnimation].start();
						nextsAnimations.erase(nextsAnimations.begin());
						return animations[currentAnimation].getFrame();
					}
				}
			}
			af = animations[ani].getFrame();
		}
		return af;
	}
	
	Animation* AnimatedElement::getAnimation () {
		if (currentAnimation == -1) {
			if (defaultAnimation == -1) {
				return NULL;
			} else {
				return &animations[defaultAnimation];
			}
		} else {
			return &animations[currentAnimation];
		}
		return NULL;
	}
	
	Animation* AnimatedElement::getAnimation (string name) {
		int i;
		for (i=0; i<(int)animations.size(); i++) {
			if ( animations[i].name == name ) {
				return &animations[i];
			}
		}
		return NULL;
	}
	
	int AnimatedElement::getCurrentFrame () {
		int af;
		if (currentAnimation == -1) {
			if (defaultAnimation == -1) {
				af = 0;
			} else {
				af = animations[defaultAnimation].getCurrentFrame();
			}
		} else {
			af = animations[currentAnimation].getCurrentFrame();
		}
		return af;
	}
	
	void AnimatedElement::addAnimation (Animation a) {
		if (defaultAnimation == -1) defaultAnimation = 0;
		animations.push_back(a);
	}
	
	void AnimatedElement::removeAnimation (string name) {
		int i;
		for (i=0; i<(int)animations.size(); i++) {
			if ( animations[i].name == name ) {
				animations.erase(animations.begin()+i);
				return;
			}
		}
	}
	
	bool AnimatedElement::setAnimation (string name, int nt) {
        if (existAnimation(name)) {	
            if (currentAnimation>0) {
    		   if (!animations[currentAnimation].playing()) setForceAnimation(name, nt);
            }
    
    		int i;
    		for (i=0; i<(int)animations.size(); i++) {
    			if ( animations[i].name == name ) {
    				NextAnimation na;
    				na.animation = i;
    				na.numberOfTimes = nt-1;
    				nextsAnimations.push_back(na);
    				return true;
    			}
    		}
        }
		return false;
	}
	
	bool AnimatedElement::existAnimation (string name) {
		int i;
		for (i=0; i<(int)animations.size(); i++) {
			if ( animations[i].name == name ) {
				return true;
			}
		}
		return false;
	}
	
	bool AnimatedElement::setForceAnimation (string name, int nt) {	
        if (existAnimation(name)) {
    		int i;
    		for (i=0; i<(int)animations.size(); i++) {
    			if ( animations[i].name == name ) {
    				numberOfTimes = nt-1;
    				countNumberOfTimes = 0;
    				currentAnimation = i;
    				animations[currentAnimation].start();
    				nextsAnimations.clear();
    				return true;
    			}
    		}
        }
		return false;
	}
	
	bool AnimatedElement::setDefaultAnimation (string name) {
		int i;
		for (i=0; i<(int)animations.size(); i++) {
			if ( animations[i].name == name ) {
				defaultAnimation = i;
				return true;
			}
		}
		return false;
	}
	
	void AnimatedElement::draw () {
		if ((int)sprite.size()>0) {
			cFrame = getNextFrame();
			move();
			transforms();
			paintSprite();
		}
	}
	
	void AnimatedElement::unLoad() {
		int i;
		for (i=0; i<(int)sprite.size(); i++)
			delete sprite[i];
		
		animations.clear();
		nextsAnimations.clear();
		parameters.clear();
		sprite.clear();
	}
	
	/*****************************
	**
	** CLASS ElementDnD
	**
	******************************/
	
	ElementDnD::ElementDnD()  : Element () {
		toDoDnd = true;
		isDnd = false;
		isRollOver = false;
		mouseX = 0;
		mouseY = 0;
	}
	
	ElementDnD::~ElementDnD() {
		unLoad();
	}
	
	void ElementDnD::onOver()
	{
		if (isOnMouseOver() && !isRollOver) {
			isRollOver = true;
		}
		if (!isOnMouseOver() && isRollOver) {
			isRollOver = false;
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
		}
		
	}
	
	bool ElementDnD::isOnMouseOver()
	{
	
		int mouse_x, mouse_y;
	
		SDL_PumpEvents();
		
		SDL_GetMouseState(&mouse_x, &mouse_y);
		
		Bounds b = getBounds();
		
		if ( (mouse_x > b.x1) && (mouse_x < b.x2) &&
			(mouse_y > b.y1) && (mouse_y < b.y2) ) {
			return true;
		}
	
		return false;
	
	}
	
	void ElementDnD::startDrag () { 
		setAlpha(100);
		isDnd = true; 
		SDL_GetMouseState(&mouseX, &mouseY); 
		mouseX -= (int)getDisplacementInXByGroups(); 
		mouseY -= (int)getDisplacementInYByGroups(); 
	}
	
	void ElementDnD::drop () { 
		setAlpha(255);
		isDnd = false; 
	}
		
	/*****************************
	**
	** CLASS Element_AnimatedGroup
	**
	******************************/
	
	Element_AnimatedGroup::Element_AnimatedGroup() : Element() {
		offsetX = 0.0; 
		offsetX = 0.0;
	}

	Element_AnimatedGroup::~Element_AnimatedGroup() {
		unLoad();
	}
	
	/*****************************
	**
	** CLASS ANIMATEDGROUP
	**
	******************************/
	
	AnimatedGroup::AnimatedGroup() {
		cols = 3;
		rows = -1;
		indexz = 0;
		posX = 0.0; 
		posY = 0.0;
		width = 0;
		height = 0;
		
		reverse = false;
		
		isMovementNormal = false;
		isMovementSmooth = false;
		isMovementFlexible = false;
		
		xMovement = 0;
        yMovement = 0;
		mlMovement = 0;
		
		cyclesChangeElement = -1;
		
		currentElement = 0;
		cycles = 0;
	}
	
	AnimatedGroup::~AnimatedGroup() {
		unLoad();
	}
	
	void AnimatedGroup::addElement(Element_AnimatedGroup *el) { 
		elements.push_back(el); 
	}
	
	void AnimatedGroup::organizeElements () { 
        if (cols==-1) {
            cols = ((int)elements.size()/rows)+(elements.size()%rows);
        }
        
        if (rows==-1) {
            rows = ((int)elements.size()/cols)+(elements.size()%cols);
        }

		for (int i=0; i<(int)elements.size(); i++) {
			//int r = elements.size()/rows;
			int c = i%cols;
			int h=0, w=0;
			float x=0.0, y=0.0;
			if (i>0) {
				h = elements[i-1]->getHeight();
				w = elements[i-1]->getWidth();
				x = elements[i-1]->getX();
				y = elements[i-1]->getY();
			}
			if (c==0) {
				elements[i]->setOffSetX(0);
				elements[i]->setOffSetY(y+h);
			} else {
				elements[i]->setOffSetX(x+w);
				elements[i]->setOffSetY(y);
			}

		}
	}
		
	void AnimatedGroup::setVelocitySmooth (int t) {
		int i;
		for (i=0; i<(int)elements.size(); i++) {
			elements[i]->setVelocitySmooth(t);
		}
	}
	
	void AnimatedGroup::setVelocityFlexible (int t) {
		int i;
		for (i=0; i<(int)elements.size(); i++) {
			elements[i]->setVelocityFlexible(t);
		}
	}
	
	void AnimatedGroup::setText (string text, string font) { 
		int i;

		for (i=0; i<(int)text.length(); i++) {
			Element_AnimatedGroup* el = new Element_AnimatedGroup();
			el->addFrameText(font, text.substr(i, 1), ALIGN_CENTER);
			addElement(el);
		}
		
	}
	
	void AnimatedGroup::setMovementNormal(float x, float y, int ml, int waitMl) { 
		isMovementNormal = true;
		isMovementSmooth = false;
		isMovementFlexible = false;
		xMovement = x;
        yMovement = y;
		mlMovement = ml;
		cyclesChangeElement = Converter::GetInstance()->ml2cycles(waitMl);
		if (reverse) currentElement = (int)elements.size()-1; else currentElement = 0;
		cycles = -1;
    }
    
	void AnimatedGroup::setMovementSmooth(float x, float y, int waitMl) { 
		isMovementNormal = false;
		isMovementSmooth = true;
		isMovementFlexible = false;
		xMovement = x;
        yMovement = y;
		cyclesChangeElement = Converter::GetInstance()->ml2cycles(waitMl);
		if (reverse) currentElement = (int)elements.size()-1; else currentElement = 0;
		cycles = -1;
    }
    
	void AnimatedGroup::setMovementFlexible(float x, float y, int waitMl) { 
		isMovementNormal = false;
		isMovementSmooth = false;
		isMovementFlexible = true;
		xMovement = x;
        yMovement = y;
		cyclesChangeElement = Converter::GetInstance()->ml2cycles(waitMl);
		if (reverse) currentElement = (int)elements.size()-1; else currentElement = 0;
		cycles = -1;
    }
	
	void AnimatedGroup::draw () { 
         cycles ++;
         if (isMovementNormal || isMovementSmooth || isMovementFlexible) {
             if ( ( (currentElement>(int)elements.size()-1) && (!reverse) ) 
                  || ( (currentElement<0) && (reverse) )  ) {
        		isMovementNormal = false;
        		isMovementSmooth = false;
        		isMovementFlexible = false;
        		xMovement = 0;
                yMovement = 0;
        		mlMovement = 0;
        		cyclesChangeElement = -1;
        		currentElement = 0;
             } else {
                if (cycles%cyclesChangeElement==0) {
                   if (isMovementNormal) elements[currentElement]->setMovementNormal(xMovement+elements[currentElement]->getOffSetX(), yMovement+elements[currentElement]->getOffSetY(), mlMovement);
                   if (isMovementSmooth) elements[currentElement]->setMovementSmooth(xMovement+elements[currentElement]->getOffSetX(), yMovement+elements[currentElement]->getOffSetY());
                   if (isMovementFlexible) elements[currentElement]->setMovementFlexible(xMovement+elements[currentElement]->getOffSetX(), yMovement+elements[currentElement]->getOffSetY());
                   if (reverse) currentElement--; else currentElement++;
                }
             }
         }
         paintSprites ();
	}
	
	void AnimatedGroup::paintSprites () { 
		int x, y;
		
		for (y=0; y<rows; y++) {
			for (x=0; x<cols; x++) {
				int item = y*cols+x;
				if (item < (int)elements.size()) {
					elements[item]->draw();
				}
			}
		}
		
	}
	
	void AnimatedGroup::setX(float x) { 
		posX = x; 
		int i;
		for (i=0; i<(int)elements.size(); i++) {
			elements[i]->setX(x);
			elements[i]->setOffSetX();
		}
	}
	
	void AnimatedGroup::setY(float y) { 
		posY = y; 
		int i;
		for (i=0; i<(int)elements.size(); i++) {
			elements[i]->setY(y);
			elements[i]->setOffSetY();
		}
	}
	
	void AnimatedGroup::unLoad() { 
		int i;
		for (i=0; i<(int)elements.size(); i++) {
			delete elements[i];
		}
	}
	
	/*****************************
	**
	** CLASS SLIDE
	**
	******************************/
	
	Slide::Slide()  : Element () {
        cyclesNextFrame = -1;
		nextFrame = -1;
		degrees = 0;
		rotX = 0.0f;
		rotY = 1.0f;
		rotZ = 0.0f;
		setAlign(ALIGN_CENTER);
		setVAlign(VALIGN_CENTER);
		changingFrame = false;
		degreesByFrame = 10;
		degreesToDoChange = 90;
		typeSlide = TYPESLIDE_FADE;
		
		mlFade = 1000;
		stopped = false;
		
	}
	
	Slide::~Slide() {
		unLoad();
	}
	
	void Slide::setCurrentFrame(int c) { 
		if ((int)sprite.size()>1) {
			if (c<(int)sprite.size()) {
				nextFrame = c; 
				if ( typeSlide == TYPESLIDE_FADE ) setFadeOut(mlFade);
			}
		}
	}
	
	void Slide::draw () {
		if ((int)sprite.size()>0) {
			move();
			transforms();
			// movement slide
			if ((int)sprite.size()>1) {
				if (nextFrame!=-1) {
					
					if ( typeSlide == TYPESLIDE_FADE ) {
						
						if (getAlpha()<10) {
							cFrame = nextFrame;
							nextFrame = -1;
							setFadeIn(mlFade);
						}
						
					} else if ( typeSlide ==TYPESLIDE_ROTATE ) {
					
						degrees+=degreesByFrame;
						if ( (degrees>=degreesToDoChange) && (!changingFrame) ) {
							degrees = 270;
							cFrame = nextFrame;
							changingFrame = true;
						}
						if (degrees>=360) {
							nextFrame = -1;
							degrees = 0;
							changingFrame = false;
						}
						rot = degrees;
						
					} else {
						cFrame = nextFrame;
						nextFrame = -1;
					}
					
				}
			}
			paintSprite();
			
			if (cyclesNextFrame>0) {
				if (cycle%cyclesNextFrame==0) {
					if (!stopped) setNextFrame();
				}
			}
		}
	}
	
	/*****************************
	**
	** CLASS ChronometerElement
	**
	******************************/
	
	ChronometerElement::ChronometerElement(string n, string f)  : Group () {
		name = n;
		Chronometer::GetInstance()->setTime(name);
		stopped = true;
		font = f;
        pastSeconds = 0;
		indexz = 0;
		
		minute0 = new Slide();
		minute0->setTypeSlide(TYPESLIDE_ROTATE);
		this->addElement((Element*)minute0);
		
		minute1 = new Slide();
		minute1->setTypeSlide(TYPESLIDE_ROTATE);
		this->addElement((Element*)minute1);
		
		second0 = new Slide();
		second0->setTypeSlide(TYPESLIDE_ROTATE);
		this->addElement((Element*)second0);
		
		second1 = new Slide();
		second1->setTypeSlide(TYPESLIDE_ROTATE);
		this->addElement((Element*)second1);
		
		char tmp[4];
		for (int i=0; i<10; i++) {
			sprintf(tmp, "%d", i);
			minute0->addFrameText(font, tmp, ALIGN_LEFT);
			minute1->addFrameText(font, tmp, ALIGN_LEFT);
			second0->addFrameText(font, tmp, ALIGN_LEFT);
			second1->addFrameText(font, tmp, ALIGN_LEFT);
		}
		
		points = new Element();
		points->setAlign(ALIGN_CENTER);
		points->setVAlign(VALIGN_CENTER);
		points->addFrameText(font, ":", ALIGN_LEFT);
		this->addElement(points);
		
	}
	
	ChronometerElement::~ChronometerElement () {
		unLoad();
	}
	
	void ChronometerElement::setTime() {
		int minutes = 0;
		int seconds = 0;
		if (pastSeconds<60) {
			seconds = pastSeconds;
		} else {
			minutes = pastSeconds/60;
			seconds = pastSeconds%60;			
		}
		
		int frMinute0 = minutes/10;
		if (frMinute0!=minute0->getCurrentFrame()) minute0->setCurrentFrame(frMinute0);
		
		minute1->setX(minute0->getWidth()+2);
		int frMinute1 = minutes%10;
		if (frMinute1!=minute1->getCurrentFrame()) minute1->setCurrentFrame(frMinute1);
		
		points->setX(minute1->getXWithoutDisplacementByGroups()+minute1->getWidth()+2);
		
		second0->setX(points->getXWithoutDisplacementByGroups()+points->getWidth()+2);
		int frSeconds0 = seconds/10;
		if (frSeconds0!=second0->getCurrentFrame()) second0->setCurrentFrame(frSeconds0);
		
		second1->setX(second0->getXWithoutDisplacementByGroups()+second0->getWidth()+2);
		int frSeconds1 = seconds%10;
		if (frSeconds1!=second1->getCurrentFrame()) second1->setCurrentFrame(frSeconds1);
		
	}
	
	void ChronometerElement::draw() {
		if (!stopped) {
			if (Chronometer::GetInstance()->getTime(name) >= 1000) {
				Chronometer::GetInstance()->setTime(name);
				addSecond();
			}				
		}		
		minute0->draw();
		minute1->draw();
		points->draw();
		second0->draw();
		second1->draw();
	}
	
	void ChronometerElement::unLoad() {
		delete minute0;
		delete minute1;
		delete points;
		delete second0;
		delete second1;
	}
	
	/*****************************
	**
	** CLASS ProgressBar
	**
	******************************/
	
	ProgressBar::ProgressBar(int tc, int w, int h, int r, int g, int b) {
		
		//Frame frBar;

		width = w;
		height = h;
		
		bar = new Element();
		//frBar.loadGLSurface(Primitives::GetInstance()->rectangle(w, h, r, g, b));
		bar->addFrameSurface(Primitives::GetInstance()->rectangle(w, h, r, g, b));
		bar->setAlign(ALIGN_LEFT);
		bar->setVAlign(VALIGN_BOTTOM);
	
		txt = new Element();
		txt->setAlign(ALIGN_CENTER);
		txt->setVAlign(VALIGN_TOP);
		
		bg = new Element();
		bg->setAlign(ALIGN_CENTER);
		bg->setVAlign(VALIGN_CENTER);
		bg->setX(World::width/2);
		bg->setY(World::height/2);
		
		bg_bar = new Element();
		bg_bar->setAlign(ALIGN_CENTER);
		bg_bar->setVAlign(VALIGN_CENTER);
		
		total = tc;
		status = 0;
		
		posBarX = World::width/2;
        posBarY = World::height/2;
		
		setPositionBar(posBarX, posBarY);
		
	}
	
	ProgressBar::~ProgressBar () {
		unLoad();
	}
	
	void ProgressBar::setPositionBar(int posX, int posY) {
        posBarX = posX;
        posBarY = posY;
		bar->setX(posX-(width/2));
		bar->setY(posY-10);
        bg_bar->setX(bar->getX()+(width/2));
		bg_bar->setY(bar->getY()-(height/2)+1);
		txt->setX(posX);
		txt->setY(posY+10);
	}
	
	void ProgressBar::setText(string font, string t) {
		Debug::GetInstance()->writeText(t);
		if (txt->getFrames()==0) {
			txt->addFrameText(font, t, ALIGN_CENTER);
		} else {
			txt->changeFrameText(0, font, t, ALIGN_CENTER);
		}
	}
	
	void ProgressBar::setBg(string file) {
		if (bg->getFrames()==0) {
			bg->addFrameFile(file);
		} else {
			bg->changeFrameFile(0, file);
		}
	}
	
	void ProgressBar::setBgBar(string file) {
		if (bg_bar->getFrames()==0) {
			bg_bar->addFrameFile(file);
		} else {
			bg_bar->changeFrameFile(0, file);
		}
	}
	
	void ProgressBar::draw() {
		addStatus();
		bar->setCurrentScaleX((float)status/(float)total);
		
		glClear(GL_COLOR_BUFFER_BIT); 
		glLoadIdentity();
	
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		
		if (bg->getFrames()>0) {
			bg->draw();
		}
		
		if (bg_bar->getFrames()>0) {
			bg_bar->draw();
		}
		
		bar->draw();
		
		if (txt->getFrames()>0) {
			txt->draw();
		}
		
		glDisable(GL_BLEND);
	
		SDL_GL_SwapBuffers();

	}
	
	void ProgressBar::unLoad() {
		delete bar;
		delete bg;
		delete txt;
		delete bg_bar;
		Debug::GetInstance()->writeText("Cargado todo el escenario");
	}
	
	/*****************************
	**
	** CLASS ListView
	**
	******************************/

	CoverFlow::CoverFlow() : Group () {
    	beginItem = 0;
    	itemFadeOut = -1;
    	itemSeparate = 0;
		index = 0;
		indexz = 0;
    	
		width = World::width;
		widthItem = 200;
		
    	itemsVisible = 5;
    	cursor = 0;
    	
    	timeChangeItem = 300;
    	
    	separateGrid = 80;
    	drawButtons = false;
	}	
	
	CoverFlow::~CoverFlow() {
		unLoad();
	}
	
	void CoverFlow::inicialize() {
    	beginItem = 0;
    	itemFadeOut = -1;
    	itemSeparate = 0;
		index = 0;
    	
		for (int i=0; i<(int)data.size(); i++) {
			delete data[i];
		}
		data.clear();
    }
	
	int CoverFlow::lastItem() { 
		if (beginItem+itemsVisible<(int)data.size()) { 
			return beginItem+itemsVisible; 
		} else { 
			return (int)data.size(); 
		}
	}
	
    void CoverFlow::setIndex(int i) {
        int oldIndex = index;
		index = i;
		
		if ((int)data.size()>0) {
   			beginItem = index - (itemsVisible/2);
        	itemFadeOut = -1;
        	itemSeparate = 0;
    		
    		data[index]->setMovementNormalX((float)width/2, timeChangeItem);
    		data[index]->setScaleGL(1, timeChangeItem);
			data[index]->removeRGB();
    		
    		// right
    		for (int i=1; i<=(itemsVisible/2); i++) {
    			int value = index + i;
    			if ( (value>=0) && (value<(int)data.size()) ) {
                    if ( (oldIndex<index) && i==(itemsVisible/2) ) {
                         data[value]->setX(((float)width/2) + ((float)widthItem/3) +((i+1)*separateGrid));
                         data[value]->setCurrentScale(0);
                    }
    				data[value]->setMovementNormalX(((float)width/2) + ((float)widthItem/3) +(i*separateGrid), timeChangeItem);
    				data[value]->setScaleGL(1.0-(i*0.3), timeChangeItem);
					data[value]->setRGB(255-(i*100), 255-(i*100), 255-(i*100));
    			}
    		}
    
            // left
    		for (int i=1; i<=(itemsVisible/2); i++) {
    			int value = index - i;
    			if (value>=0) {
                    if ( (oldIndex>index) && i==(itemsVisible/2) ) {
                         data[value]->setX(((float)width/2) - ((float)widthItem/3) -((i+1)*separateGrid));
                         data[value]->setCurrentScale(0);
                    }
    				data[value]->setMovementNormalX(((float)width/2) - ((float)widthItem/3) -(i*separateGrid), timeChangeItem);
    				data[value]->setScaleGL(1.0-(i*0.3), timeChangeItem);
					data[value]->setRGB(255-(i*100), 255-(i*100), 255-(i*100));
    			}
    		}
    
    		/*for (int i=firtsItem(); i<lastItem(); i++) {
    			if ( (i!=index) && (i>=0) ) data[i]->setCurrentScale(0.5);
    		}*/
    		
    		verifySensitiveButtons();
       }
		
    }
    
    
    void CoverFlow::startPosition() {
		index = 0;
		
		if ((int)data.size()>0) {
   			beginItem = index - (itemsVisible/2);
        	itemFadeOut = -1;
        	itemSeparate = 0;
    		
    		data[index]->setX(width/2);
    		data[index]->setCurrentScale(1);
    		
    		for (int i=1; i<=(itemsVisible/2); i++) {
    			int value = index + i;
    			if ( (value>=0) && (value<(int)data.size()) ) {
    				data[value]->setX(((float)width/2) + ((float)widthItem/3) +(i*separateGrid));
					data[value]->setCurrentScale(1.0-(i*0.3));
					data[value]->setRGB(255-(i*100), 255-(i*100), 255-(i*100));
    			}
    		}
  
    		verifySensitiveButtons();
       }
		
    }
	
    void CoverFlow::setButtons(Button *buttom_left, Button *buttom_right, int separateX, int separateY) {
         bLeft = buttom_left;
         bRight = buttom_right;
         this->addElement(bLeft);
         this->addElement(bRight);
         
		 bLeft->setX(5-separateX);
		 bRight->setX(width-bRight->getWidth()-5+separateX);
		 
		 bLeft->setY(separateY);
		 bRight->setY(separateY);
         
         drawButtons = true;
    }
    
    void CoverFlow::verifySensitiveButtons() {
         if (drawButtons) {
              if ( (index>0) ) {
                   bLeft->setSensitive(true);
              } else {
                   bLeft->setSensitive(false);
              }
              
              if ( (index<(int)data.size()-1) ) {
                   bRight->setSensitive(true);
              } else {
                   bRight->setSensitive(false);
              }
         }
    }
    
    void CoverFlow::verifyClickButtons() {
         if (drawButtons) {
        	if (bLeft->isOnMouseOver()) {
				if (bLeft->getSoundClick()!="") Sounds::GetInstance()->getSound(bLeft->getSoundClick())->play(-1, 0);
        		previousIndex();
        	}
        	if (bRight->isOnMouseOver()) {
				if (bRight->getSoundClick()!="") Sounds::GetInstance()->getSound(bRight->getSoundClick())->play(-1, 0);
        		nextIndex();
        	}
         }
    }
    
    void CoverFlow::onOver() {
         bLeft->onOver();
         bRight->onOver();
    }
    
    void CoverFlow::draw() {
		
    	for (int i=firtsItem(); i<lastItem(); i++) {
   			if (i>=0) data[i]->draw();
    	}
        
        if (drawButtons) {
        
       		bLeft->draw();
        	
       		bRight->draw();
        	
        }
        
     }
     
    void CoverFlow::unLoad() {
        if (drawButtons) {
            delete bLeft;
            delete bRight;
        }
		for (int i=0; i<(int)data.size(); i++) {
			delete data[i];
		}
		data.clear();
    }
	
	/*****************************
	**
	** CLASS ListImage
	**
	******************************/

	ListImage::ListImage(int r, int c) : Group () {
		indexz = 0;
		cursor = 0;
		rows = r;
		cols = c;
    	rowBeginObjects = 0;    	
    	separateGrid = 80;
    	drawButtons = false;
		bUp = NULL;
		bDown = NULL;
		boxImage = NULL;
		drawBoxImage = false;
		
		categories.push_back("all");
		
		currentCategory = 0;
		
	}

	ListImage::~ListImage () {
		unLoad();
	}
	
	int ListImage::nTotalRowObjects() { 
        int count = 0;
        for (int i=0; i<(int)data.size(); i++) {
             if ( (data[i]->getParameter("category") == categories[currentCategory]) || (currentCategory==0) ) {
                  count++;
             }
        }        
        
        int v = count/cols; 
        if (count%cols==0) { 
            return v; 
        } else { 
            return v+1; 
        }
    }
	
	void ListImage::add(Button* b) {
		b->setX(( ((int)data.size()%cols) *separateGrid)+(separateGrid/2));
    	b->setY(( ((int)data.size()/cols) *separateGrid)+(separateGrid/2));
    	b->setAlign(ALIGN_CENTER);
    	b->setVAlign(VALIGN_CENTER);
		this->addElement(b);
    	data.push_back(b);
    }
    
	void ListImage::setCategory(string c) {
		for (int i=0; i<(int)categories.size(); i++) {
            if (categories[i]==c) {
                currentCategory = i;
            }
        }
        rowBeginObjects = 0;
        orderElements();
    }
    
    void ListImage::orderElements() {
        int count = 0;
        for (int i=0; i<(int)data.size(); i++) {
             if ( (data[i]->getParameter("category") == categories[currentCategory]) || (currentCategory==0) ) {
        		data[i]->setX(( (count%cols) *separateGrid)+(separateGrid/2));
            	data[i]->setY(( (count/cols) *separateGrid)+(separateGrid/2));
            	data[i]->show();
            	count++;
             }
        }
        verifyObjectsToShow();
    }
	
	void ListImage::verifyObjectsToShow() {
        int count = 0;
		for (int i=0; i<(int)data.size(); i++) {
            if ( (data[i]->getParameter("category") == categories[currentCategory]) || (currentCategory==0) ) {
    			if ( (count>=rowBeginObjects*cols) && (count<(rowBeginObjects+rows)*cols) ) {
    				data[i]->show();
    			} else {
    				data[i]->hide();
    			}
    			count++;
            } else {
                data[i]->hide();       
            }
		}
		
		if (drawButtons) {
    		if (rowBeginObjects>0) {
    			bUp->setSensitive(true);
    		} else {
    			bUp->setSensitive(false);
    		}
    	
    		if (rowBeginObjects+rows<nTotalRowObjects())  {
    			bDown->setSensitive(true);
    		} else {
    			bDown->setSensitive(false);
    		}
        }
	}
	
	void ListImage::inicialize() {
    	rowBeginObjects = 0;
    	
		for (int i=0; i<(int)data.size(); i++) {
			delete data[i];
		}
		data.clear();
    }
	
    void ListImage::setButtons(Button *buttom_up, Button *buttom_down, int xSeparate, int ySeparate) {
		if (bUp!=NULL) {
			delete bUp;
		}
		bUp = buttom_up;
		if (bDown!=NULL) {
			delete bDown;
		}
		bDown = buttom_down;
		this->addElement(bUp);
		this->addElement(bDown);
		
		bUp->setX(xSeparate);
		bUp->setY(ySeparate);
		bDown->setX(xSeparate);
		bDown->setY((rows*separateGrid)-ySeparate);
		
		drawButtons = true;
    }
	
	void ListImage::setBoxImage (Element* box) {
		boxImage = box;
		this->addElement(boxImage);
		drawBoxImage = true;
	}
    
    void ListImage::upItems() { 
		if (rowBeginObjects>0) {
			rowBeginObjects--;
			for (int i=0; i<(int)data.size(); i++) {
				data[i]->addY(110);
			}
			verifyObjectsToShow();
		}
    }
    
    void ListImage::downItems() { 
		if (rowBeginObjects+rows<nTotalRowObjects()) {
			rowBeginObjects++;
			for (int i=0; i<(int)data.size(); i++) {
				data[i]->addY(-110);
			}
			verifyObjectsToShow();
		}
    }
        
    void ListImage::verifyClickButtons() {
		if (drawButtons) {
			if (bUp->isOnMouseOver()) {
				if (bUp->getSoundClick()!="") Sounds::GetInstance()->getSound(bUp->getSoundClick())->play(-1, 0);
				upItems();
			}
			if (bDown->isOnMouseOver()) {
				if (bDown->getSoundClick()!="") Sounds::GetInstance()->getSound(bDown->getSoundClick())->play(-1, 0);
				downItems();
			}
		}
    }
    
    void ListImage::onOver() {
		for (int i=0; i<(int)data.size(); i++) {
			data[i]->onOver();
		}
		if (drawButtons) {
        	bUp->onOver();
        	bDown->onOver();
		}
    }
    
    void ListImage::draw() {
		
		if (drawBoxImage) {
			for (int i=0; i<cols; i++) {
				for (int j=0; j<rows; j++) {
					boxImage->setXY(separateGrid*i, separateGrid*j);
					boxImage->draw();
				}
			}
		}
		
		for (int i=0; i<(int)data.size(); i++) {
			data[i]->draw();
		}
        
        if (drawButtons) {
        
       		bUp->draw();
        	
       		bDown->draw();
        	
        }
        
     }
	 
    void ListImage::clear() {
		for (int i=0; i<(int)data.size(); i++) {
			delete data[i];
		}
		data.clear();
    }
     
    void ListImage::unLoad() {
        if (drawButtons) {
			delete bUp;
            delete bDown;
        }
		if (drawBoxImage) {
			delete boxImage;
		}
		clear();
    }
     

     
	
	/*****************************
	**
	** CLASS ListView
	**
	******************************/

	ListView::ListView() : Group () {
    	beginItem = 0;
    	itemFadeOut = -1;
    	itemSeparate = 0;
		indexz = 0;
		
		todoMovement = true;
    	
    	itemsVisible = 4;
    	cursor = 0;
    	
    	timeChangeItem = 300;
    	
    	separateGrid = 80;
    	drawButtons = false;
		
		bUp = NULL;
		bDown = NULL;
	}	
	
	ListView::~ListView () {
		unLoad();
	}
	
	void ListView::setBeginItem (int b) { 
        beginItem = b; 
		for (int i=0; i<(int)data.size(); i++) {
			data[i]->addY(-(beginItem*separateGrid));
		}
		verifySensitiveButtons();
    }
	
	void ListView::inicialize() {
    	beginItem = 0;
    	itemFadeOut = -1;
    	itemSeparate = 0;
    	
		data.clear();
    }
	
    void ListView::setButtons(Button *buttom_up, Button *buttom_down, int xSeparate) {
		if (bUp!=NULL) {
			delete bUp;
		}
		bUp = buttom_up;
		if (bDown!=NULL) {
			delete bDown;
		}
		bDown = buttom_down;
		this->addElement(bUp);
		this->addElement(bDown);
		
		bUp->setX(xSeparate);
		bDown->setX(xSeparate);
		bDown->setY(itemsVisible*separateGrid);
		
		drawButtons = true;
    }
    
    void ListView::upItems() { 
        bool todo = true;
        if (itemFadeOut!=-1) todo = false;
        for (int i=firtsItem(); i<lastItem(); i++) {
            if (data[i]->getAlpha()!=255) todo = false;
        }
        if (todo) {
        	if (beginItem>0) {
                itemFadeOut = lastItem()-1;
        		beginItem--; 
        		for (int i=0; i<(int)data.size(); i++) {
        			if ( i==itemFadeOut ) {
                        data[i]->setFadeOut(timeChangeItem);
                        itemSeparate = separateGrid;
        			} else if ( (i<firtsItem()) || (i>=lastItem()) ) {
        				data[i]->addY(separateGrid);
        			} else {
        				data[i]->setMovementNormal(posX, data[i]->getY()+separateGrid, timeChangeItem);
        			}
        		}
        		verifySensitiveButtons();
        	}
        }  	
    }
    
    void ListView::downItems() { 
        bool todo = true;
        if (itemFadeOut!=-1) todo = false;
        for (int i=firtsItem(); i<lastItem(); i++) {
            if (data[i]->getAlpha()!=255) todo = false;
        }
        if (todo) {
        	if (beginItem+itemsVisible<(int)data.size()) {
                itemFadeOut = beginItem;
        		beginItem++; 
        		for (int i=0; i<(int)data.size(); i++) {
                    if ( i==itemFadeOut ) {
                        data[i]->setFadeOut(timeChangeItem);
                        itemSeparate = -separateGrid;
        			} else if ( (i<firtsItem()) || (i>=lastItem()) ) {
        				data[i]->addY(-separateGrid);
        			} else {
        				data[i]->setMovementNormal(posX, data[i]->getY()-separateGrid, timeChangeItem);
        			}
        		}
        		verifySensitiveButtons();
        	}
        }
    }
    
    void ListView::verifySensitiveButtons() {
         if (drawButtons) {
              if ( (beginItem>0) ) {
                   bUp->setSensitive(true);
              } else {
                   bUp->setSensitive(false);
              }
              
              if ( (beginItem+itemsVisible<(int)data.size()) ) {
                   bDown->setSensitive(true);
              } else {
                   bDown->setSensitive(false);
              }
         }
    }
    
    void ListView::verifyClickButtons() {
         if (drawButtons) {
        	if (bUp->isOnMouseOver()) {
				if (bUp->getSoundClick()!="") Sounds::GetInstance()->getSound(bUp->getSoundClick())->play(-1, 0);
        		upItems();
        	}
        	if (bDown->isOnMouseOver()) {
				if (bDown->getSoundClick()!="") Sounds::GetInstance()->getSound(bDown->getSoundClick())->play(-1, 0);
        		downItems();
        	}
         }
    }
    
    void ListView::onOver() {
         bUp->onOver();
         bDown->onOver();
    }
    
    void ListView::draw() {
    
        if (itemFadeOut!=-1) {

			data[itemFadeOut]->work();                  
			data[itemFadeOut]->draw();
			
            if (data[itemFadeOut]->getAlpha()<=0) {
                data[itemFadeOut]->addY(itemSeparate);
                data[itemFadeOut]->removeAlpha();
                itemFadeOut=-1;
                if (itemSeparate>0) {
					if (!todoMovement) {
						data[firtsItem()]->addY(itemSeparate);
					}
                    data[firtsItem()]->setFadeIn(timeChangeItem);
                } else {
					if (!todoMovement) {
						data[lastItem()-1]->addY(itemSeparate);
					}
                    data[lastItem()-1]->setFadeIn(timeChangeItem);
                }
            } 
            
            int b, e;
            if (itemSeparate>0) {
                 b = firtsItem()+1;
                 e = lastItem();
            } else {
                 b = firtsItem();
                 e = lastItem()-1;
            }
    		for (int i=b; i<e; i++) {
   				data[i]->work();
   				data[i]->draw();
    		}
    		
        } else {
    		for (int i=firtsItem(); i<lastItem(); i++) {
   				data[i]->work();
   				data[i]->draw();
    		}
        }
        
        if (drawButtons) {
        
       		bUp->draw();
        	
       		bDown->draw();
        	
        }
        
     }
     
    void ListView::unLoad() {
        if (drawButtons) {
            delete bUp;
            delete bDown;
        }
		data.clear();
    }
     
     
	/*****************************
	**
	** CLASS BUTTON
	**
	******************************/
	
	Button::Button()  : AnimatedElement () {
		isRollOver = false;
		scaleOut = 1.0f;
		scaleOn = 1.0f;
		sensitive = true;
		
		textAlt = "";
		alignAlt = ALIGN_LEFT;
		soundOn = "";
		soundOut = "";
		soundClick = "";
	}
	
	Button::~Button() {
		unLoad();
	}
	
	void Button::setSensitive(bool s) { 
         sensitive = s;  
         if (sensitive) {
             if (existAnimation("out")) {	
                 setForceAnimation("out"); 
             }
         } else {
             if (existAnimation("off")) {	
                 setForceAnimation("off"); 
             } 
         }
    }
	
	bool Button::onOver()
	{
        if (sensitive) {
    		if (isOnMouseOver() && !isRollOver) {
				if (textAlt!="") Cursor::GetInstance()->showText(textAlt, alignAlt, valignAlt);
				if (soundOn!="") Sounds::GetInstance()->getSound(soundOn)->play(-1, 0);
					
    			isRollOver = true;
    			if (existAnimation("on")) {
    				setForceAnimation("on");
    			}
    			if (scaleOn!= scaleOut) {
    				setScale(getWidthOriginal()*scaleOn, getHeightOriginal()*scaleOn, 100);
    			}
				return true;
    		}
    		if (!isOnMouseOver() && isRollOver) {
				if (textAlt!="") Cursor::GetInstance()->hideText(textAlt);
				if (soundOut!="") Sounds::GetInstance()->getSound(soundOut)->play(-1, 0);
					
    			setForceAnimation("out");
    			isRollOver = false;
    			if (scaleOn!= scaleOut) {
    				setScale(getWidthOriginal()*scaleOut, getHeightOriginal()*scaleOut, 100);
    			}
				return true;
    		}
        }
		return false;
	}
	
	bool Button::isOnMouseOver()
	{
	    if (!sensitive) return false;
	    
		int mouse_x, mouse_y;
	
		SDL_PumpEvents();
		
		SDL_GetMouseState(&mouse_x, &mouse_y);
		
		Bounds b = getBounds();
		
		if ( (mouse_x > b.x1) && (mouse_x < b.x2) &&
			(mouse_y > b.y1) && (mouse_y < b.y2) ) {
			return true;
		}
	
		return false;
	
	}
	
	
	void Button::imageOut(SDL_Surface* sfc)
	{
		this->addFrameSurface(sfc);
		this->removeAnimation("out");
		Animation anim;
		anim.setName("out");
		anim.addFrame(this->getFrames()-1);
		this->addAnimation(anim);
	}
	
	void Button::imageOn(SDL_Surface* sfc)
	{
		this->addFrameSurface(sfc);
		this->removeAnimation("on");
		Animation anim;
		anim.setName("on");
		anim.addFrame(this->getFrames()-1);
		this->addAnimation(anim);
	}
	
	void Button::imageOff(SDL_Surface* sfc)
	{
		this->addFrameSurface(sfc);
		this->removeAnimation("off");
		Animation anim;
		anim.setName("off");
		anim.addFrame(this->getFrames()-1);
		this->addAnimation(anim);
	}


	/*****************************
	**
	** CLASS CHECKBUTTON
	**
	******************************/
	
	CheckButton::CheckButton()  : Group () {
		isRollOver = false;
		active = false;
		indexz = 0;
		text = "";
		
		textAlt = "";
		alignAlt = ALIGN_LEFT;
		soundOn = "";
		soundOut = "";
		soundClick = "";
		
		scaleOut = 1.0f;
		scaleOn = 1.0f;
		sensitive = true;
		
		elBox = new Element();
		elBox->addFrameSurface(Primitives::GetInstance()->rectangle(20, 20, 255, 0, 0));
		elBox->addFrameSurface(Primitives::GetInstance()->rectangle(20, 20, 255, 0, 0));
		this->addElement(elBox);	
		elBox->setGroup(this);		
		
		char tmp[2];
		sprintf(tmp, ".");
		elText = new Element();
		elText->addFrameText(Fonts::GetInstance()->getDefaultFont(), tmp, ALIGN_CENTER);
		elText->setVAlign(VALIGN_CENTER);
		this->addElement(elText);	
		elText->setGroup(this);
		
	}
	
	CheckButton::CheckButton(string font, string t)  : Group () {
		isRollOver = false;
		active = false;
		indexz = 0;
		text = "";
		
		elBox = new Element();
		this->addElement(elBox);
		elBox->addFrameSurface(Primitives::GetInstance()->rectangle(20, 20, 255, 0, 0));
		elBox->addFrameSurface(Primitives::GetInstance()->rectangle(20, 20, 255, 0, 0));
		elBox->setGroup(this);		
		
		setText(font, t);
		
	}
	
	CheckButton::~CheckButton () {
		unLoad();
	}
	
	bool CheckButton::isOnMouseOver()
	{
	
		int mouse_x, mouse_y;
	
		SDL_PumpEvents();
		
		SDL_GetMouseState(&mouse_x, &mouse_y);
		
		float x1, x2, y1, y2;
		
		x1 = elBox->getX();
		y1 = elBox->getY();
		
		if (text=="") {
			x2 = x1 + elBox->getWidth();
			y2 = y1 + elBox->getHeight();
		} else {
			x2 = x1 + elBox->getWidth() + elText->getWidth() + 10;
			y2 = y1 + elBox->getHeight() + elText->getHeight() + 10;
		}
		
		if ( (mouse_x > x1) && (mouse_x < x2) &&
			(mouse_y > y1) && (mouse_y < y2) ) {
			return true;
		}
	
		return false;
	
	}
	
	bool CheckButton::onOver()
	{
		
        if (sensitive) {
    		if (isOnMouseOver() && !isRollOver) {
				if (textAlt!="") Cursor::GetInstance()->showText(textAlt, alignAlt, valignAlt);
				if (soundOn!="") Sounds::GetInstance()->getSound(soundOn)->play(-1, 0);
					
    			isRollOver = true;
    			if (scaleOn!= scaleOut) {
					for (int i=0; i<(int)elements.size(); i++) {
    					elements[i]->setScale(elements[i]->getWidthOriginal()*scaleOn, elements[i]->getHeightOriginal()*scaleOn, 100);
					}
    			}
				return true;
    		}
    		if (!isOnMouseOver() && isRollOver) {
				if (textAlt!="") Cursor::GetInstance()->hideText(textAlt);
				if (soundOut!="") Sounds::GetInstance()->getSound(soundOut)->play(-1, 0);
				
    			isRollOver = false;
    			if (scaleOn!= scaleOut) {
					for (int i=0; i<(int)elements.size(); i++) {
    					elements[i]->setScale(elements[i]->getWidthOriginal()*scaleOut, elements[i]->getHeightOriginal()*scaleOut, 100);
					}
    			}
				return true;
    		}
        }
		return false;
		
	}
	
	
	void CheckButton::imageActive(SDL_Surface* sfc)
	{
		elBox->changeFrameSurface(1, sfc);
		elText->setX(elBox->getWidth()+5);
		elText->setY(elBox->getHeight()/2);
	}
	
	void CheckButton::imageInactive(SDL_Surface* sfc)
	{
		elBox->changeFrameSurface(0, sfc);
		elText->setX(elBox->getWidth()+5);
		elText->setY(elBox->getHeight()/2);
	}
	
	void CheckButton::setText (string font, string t) {
		if (text=="") {
			text = t;
			elText = new Element();
			elText->addFrameText(font, text, ALIGN_CENTER);
			elText->setVAlign(VALIGN_CENTER);
			elText->setX(elBox->getWidth()+5);
			elText->setY(elBox->getHeight()/2);
			this->addElement(elText);
			elText->setGroup(this);
		} else {
			text = t;
			elText->changeFrameText(0, font, text, ALIGN_CENTER);
			elText->setX(elBox->getWidth()+5);
			elText->setY(elBox->getHeight()/2);
		}
	}
	
	void CheckButton::unLoad()
	{
		delete elBox;
		if (text!="") delete elText;
	}
	
	void CheckButton::draw()
	{
		elBox->draw();
		if (text!="") elText->draw();
	}

	/*****************************
	**
	** CLASS RADIOBUTTON
	**
	******************************/
	
	RadioButton::RadioButton(RadioButton *p)  : CheckButton() {
		parent = p;
		if (parent!=NULL) {
			parent->addChild(this);
		}
	}
	
	RadioButton::RadioButton(RadioButton *p, string font, string t)  : CheckButton(font, t) {
		parent = p;
		if (parent!=NULL) {
			parent->addChild(this);
		}
	}
	
	RadioButton::~RadioButton () {
		unLoad();
	}
	
	void RadioButton::addChild(RadioButton *r) { 
		childs.push_back(r); 
	}
	
	void RadioButton::setActive (bool a) { 
		if (a) {
			RadioButton *p;
			if (parent==NULL) {
				p = this;
			} else {
				p = parent;
			}
			if (p!=NULL) {
				int i;
				for (i=0; i<(int)p->childs.size(); i++) {
					p->childs[i]->setActive(false);
				}
				p->setActive(false);
			}
			active = a; 
			changeFrame(); 
		} else {
			active = a; 
			changeFrame(); 
		}
	}
	
	void RadioButton::swapActive () { 
		RadioButton *p;
		if (parent==NULL) {
			p = this;
		} else {
			p = parent;
		}
		if (p!=NULL) {
			int i;
			for (i=0; i<(int)p->childs.size(); i++) {
				p->childs[i]->setActive(false);
			}
			p->setActive(false);
		}
		active = !active; 
		changeFrame(); 
			
	}
	
	RadioButton* RadioButton::getRadioButtonActive () {
		RadioButton *p;
		if (parent==NULL) {
			p = this;
		} else {
			p = parent;
		}
		if (p!=NULL) {
			int i;
			for (i=0; i<(int)p->childs.size(); i++) {
				if (p->childs[i]->getActive()) {
					return p->childs[i];
				}
			}
			return p;
		}
		return NULL;
	}
	
	void RadioButton::unLoad()
	{
	}
	
	/*****************************
	**
	** CLASS ENTRY
	**
	******************************/
	
	Entry::Entry(Entry *p, int w, int h, float pt, float pl)  : Element () {
		
		parent = p;
		if (parent!=NULL) {
			parent->addChild(this);
		}
		
		totalRows = 1;
		currentRow = 1;
		multiline = false;
		
		width = w;
		height = h;
		padding_top = pt;
		padding_left = pl;
		text = "";
		maxLetters = -1;
		font = Fonts::GetInstance()->getDefaultFont();
		fontLabel = Fonts::GetInstance()->getDefaultFont();
		nospace = false;
		nosigns = false;
		active = false;
		drawBox = true;
		
		bg = new Button();	
		
		bg->imageOut(Primitives::GetInstance()->rectangle(w, h, 0, 0, 0, 2, 255, 255, 255));
		bg->imageOn(Primitives::GetInstance()->rectangle(w, h, 0, 0, 0, 2, 253, 246, 173));
		bg->setAnimation("out");
		
		select = new Element();
		select->addFrameSurface(Primitives::GetInstance()->rectangle(w, h, 253, 246, 173, 2, 255, 255, 255));
		
		elmLabel = new Element();
		elmLabel->setAlign(ALIGN_RIGHT); 
		elmLabel->addFrameSurface(Primitives::GetInstance()->rectangle(2, 2, 0, 0, 0));
		
		this->addFrameSurface(Primitives::GetInstance()->rectangle(2, 2, 0, 0, 0));
				
        elmCursor = new Element();
        elmCursor->addFrameSurface(Primitives::GetInstance()->rectangle(2, h, 255, 255, 255));
    	elmCursor->setBlinking(30);
    	elmCursor->setActiveBlinking(true);
        posCursor=0;
        
		setHorizontal(true); 
        
	}
	
	Entry::~Entry() {
		unLoad();
	}
	
	void Entry::setPosCursor(int p) {
         if (p<0) {
             posCursor = 0;
         } else if (p>(int)text.length()) {
             posCursor = text.length();
         } else {
             posCursor = p;
         }
    }
	
	void Entry::setXCursor() {
         InfoFontBitMap ifb = Fonts::GetInstance()->getInfoFontBitMap (font, -1, currentScaleX, width, ALIGN_LEFT, text.substr(0, posCursor));
         elmCursor->setX(getX()+ifb.xPosCursor); 
         if (multiline) {
             InfoFontBitMap ifbComplete = Fonts::GetInstance()->getInfoFontBitMap (font, -1, currentScaleX, width, ALIGN_LEFT, text);
             //if ( (ifb.nLettersByLine[ifb.nLines-1] == ifbComplete.nLettersByLine[ifb.nLines-1]) 
             //     && (ifb.nLines<ifbComplete.nLines) ) { // last character and isn't in last line
			 currentRow = ifb.nLines;
             elmCursor->setY(getY()+(currentRow-1)*height);
			 if (posCursor>0) {
				 if (text.substr(posCursor-1, 1)=="|") {
					 elmCursor->setX(getX()); 
					 elmCursor->setY(getY()+(currentRow)*height);
				 }
			 }
         }
    }
    
	void Entry::downLineCursor() { 
         if ( (posCursor<(int)text.length()) && (multiline) ) {
             InfoFontBitMap ifb = Fonts::GetInstance()->getInfoFontBitMap (font, -1, currentScaleX, width, ALIGN_LEFT, text.substr(0, posCursor));
             InfoFontBitMap ifbComplete = Fonts::GetInstance()->getInfoFontBitMap (font, -1, currentScaleX, width, ALIGN_LEFT, text);
             if (ifb.nLines<ifbComplete.nLines) {
                  int pos = 0;
                  for (int i=0; i<currentRow; i++) {
                      pos += ifbComplete.nLettersByLine[i]+1;
                  }
                  if (ifb.nLettersByLine[currentRow-1] != ifbComplete.nLettersByLine[currentRow-1]) { // last character
                     pos += ifb.nLettersByLine[currentRow-1];
                  }
                  setPosCursor(pos);
                  setXCursor();
             }
         }
    }
    
	void Entry::upLineCursor() { 
         if ( (posCursor>0) && (multiline) ) {
             InfoFontBitMap ifb = Fonts::GetInstance()->getInfoFontBitMap (font, -1, currentScaleX, width, ALIGN_LEFT, text.substr(0, posCursor));
             if (ifb.nLines>0) {
                  int pos = 0;
                  for (int i=0; i<currentRow-2; i++) {
                      pos += ifb.nLettersByLine[i]+1;
                  }
                  pos += ifb.nLettersByLine[currentRow-1];
                  setPosCursor(pos);
                  setXCursor();
             }
         }
    }
	
	void Entry::forwardCursor() { 
         if (posCursor<(int)text.length()) {
             posCursor++; 
             setXCursor();
         }
    }
    
	void Entry::backCursor() { 
         if (posCursor>0) {
             posCursor--; 
             setXCursor();
         }
    }
	
	void Entry::setHorizontal (bool h) { 
         horizontal = h; 
         if (horizontal) {
            setAlign(ALIGN_LEFT);
            elmCursor->setAlign(ALIGN_LEFT);
            bg->setAlign(ALIGN_LEFT); 
		    select->setAlign(ALIGN_LEFT); 
            elmLabel->setAlign(ALIGN_RIGHT); 
            
            setVAlign(VALIGN_CENTER);
            elmCursor->setVAlign(VALIGN_CENTER);
            bg->setVAlign(VALIGN_CENTER); 
		    select->setVAlign(VALIGN_CENTER); 
            elmLabel->setVAlign(VALIGN_CENTER); 
         } else {
            setAlign(ALIGN_LEFT);
            elmCursor->setAlign(ALIGN_LEFT);
            bg->setAlign(VALIGN_CENTER); 
		    select->setAlign(VALIGN_CENTER);
		    elmLabel->setAlign(ALIGN_CENTER); 
		    
            setVAlign(VALIGN_TOP);
            elmCursor->setVAlign(VALIGN_TOP);
            bg->setVAlign(VALIGN_TOP); 
		    select->setVAlign(VALIGN_TOP);
            elmLabel->setVAlign(VALIGN_BOTTOM); 
         }
    }
	
	void Entry::setX (float x) { 
        if (horizontal) {
    		oldX = posX+padding_left; 
    		posX = x+padding_left; 
    		elmCursor->setX(posX); 
    		bg->setX(x); 
    		select->setX(x); 
    		elmLabel->setX(x-10);
        } else {
    		oldX = posX+padding_left-(width/2); 
    		posX = x+padding_left-(width/2);
    		elmCursor->setX(posX);
    		bg->setX(x); 
    		select->setX(x); 
   			elmLabel->setX(x);
        }
	}
		
	void Entry::setY (float y) { 
        if (horizontal) {
    		oldY = posY+padding_top; 
    		posY = y+padding_top; 
    		elmCursor->setY(posY); 
    		bg->setY(y); 
    		select->setY(y); 
    		elmLabel->setY(y);
        } else {
    		oldY = posY+padding_top; 
    		posY = y+padding_top; 
    		elmCursor->setY(posY); 
    		bg->setY(y); 
    		select->setY(y); 
    		elmLabel->setY(y);
        } 
	}
		
	void Entry::setXY (float x, float y) { 
		setX(x); 
		setY(y); 
	}
	
	void Entry::addChild(Entry *e) { 
		childs.push_back(e); 
	}
	
	void Entry::setLabel (string l) { 
		label = l; 
		elmLabel->changeFrameText(0, fontLabel, label, ALIGN_CENTER);
	}
	
	void Entry::colorBoxNormal (int r, int g, int b, int border, int rb, int gb, int bb) {
		bg->imageOut(Primitives::GetInstance()->rectangle(width, height, r, g, b, border, rb, gb, bb));
	}
	
	void Entry::colorBoxOnOver (int r, int g, int b, int border, int rb, int gb, int bb) {
		bg->imageOn(Primitives::GetInstance()->rectangle(width, height, r, g, b, border, rb, gb, bb));
	}
	
	void Entry::colorBoxActived (int r, int g, int b, int border, int rb, int gb, int bb) {
		select->changeFrameSurface(0, Primitives::GetInstance()->rectangle(width, height, r, g, b, border, rb, gb, bb));
	}
	
	void Entry::addFrameBoxNormal (SDL_Surface *sfc) {
		bg->imageOut(sfc);
	}
	
	void Entry::addFrameBoxOnOver (SDL_Surface *sfc) {
		bg->imageOn(sfc);
	}
	
	void Entry::addFrameBoxActived (SDL_Surface *sfc) {
		select->changeFrameSurface(0, sfc);
	}
		
	void Entry::setActive (bool a) { 
		if (a) {
			Entry *p;
			if (parent==NULL) {
				p = this;
			} else {
				p = parent;
			}
			if (p!=NULL) {
				int i;
				for (i=0; i<(int)p->childs.size(); i++) {
					p->childs[i]->setActive(false);
				}
				p->setActive(false);
			}
			active = a; 
		} else {
			active = a; 
		}
	}
	
	void Entry::swapActive () { 
		Entry *p;
		if (parent==NULL) {
			p = this;
		} else {
			p = parent;
		}
		if (p!=NULL) {
			int i;
			for (i=0; i<(int)p->childs.size(); i++) {
				p->childs[i]->setActive(false);
			}
			p->setActive(false);
		}
		active = !active; 
			
	}
	
	Entry* Entry::getEntryActive () {
		Entry *p;
		if (parent==NULL) {
			p = this;
		} else {
			p = parent;
		}
		if (p!=NULL) {
			int i;
			for (i=0; i<(int)p->childs.size(); i++) {
				if (p->childs[i]->getActive()) {
					return p->childs[i];
				}
			}
			return p;
		}
		return NULL;
	}
	
	Entry* Entry::getNextEntry () {
		Entry *p;
		if (parent==NULL) {
			p = this;
		} else {
			p = parent;
		}
		
		if ((int)p->childs.size()<=0) return NULL;
			
		if (p!=NULL) {
            if (p->getActive()) {
                return p->childs[0];
            }
			int i;
			for (i=0; i<(int)p->childs.size(); i++) {
				if (p->childs[i]->getActive()) {
                    if (i+1<(int)p->childs.size()) {
					   return p->childs[i+1];
                    } else {
                       return p;
                    }
				}
			}
			return p;
		}
		return NULL;
	}
	
	void Entry::setText (string t) { 
		if (maxLetters>0) {
			if ((int)t.length()>maxLetters) { 
				t = t.substr(0, maxLetters); 
			} 
		}
		text = t; 
		updateText();
		setPosCursor(0);
		setXCursor();
		currentRow = 1;
    }
	
	/*void Entry::setText(SDLKey key) {
		getEntryActive()->introKey(key);
	}*/
	
	void Entry::insertText(string t) {
		getEntryActive()->introText(t);
	}
	
	bool Entry::verifyKey (SDLKey k) {
		
		if (text!="") {
			if (k == SDLK_BACKSPACE) {
				text.erase(posCursor-1, 1);
			    updateText();
			    backCursor();
			    return true;
			}
			
			if (k == SDLK_RETURN) {
				if (multiline) {
					text.insert(posCursor, "|");
					forwardCursor();
					updateText();
				}
				return true;
			}
			if (k == SDLK_TAB) {
				if (getNextEntry()!=NULL) getNextEntry()->setActive(true);
				return true;
			}
			
			if (k == SDLK_LEFT) {
			    backCursor();
			    return true;
			}
			if (k == SDLK_RIGHT) {
			    forwardCursor();
			    return true;
			}
			
			if (k == SDLK_UP) {
				if (multiline) upLineCursor();
				return true;
			}
			if (k == SDLK_DOWN) {
				if (multiline) downLineCursor();
				return true;
			}
			if (k == SDLK_LSHIFT) {
				return true;
			}
			if (k == SDLK_RSHIFT) {
				return true;
			}
			if (k == SDLK_RCTRL) {
				return true;
			}
			if (k == SDLK_LCTRL) {
				return true;
			}
			if (k == SDLK_LALT) {
				return true;
			}
			if (k == SDLK_RALT) {
				return true;
			}
		}
		
		return false;
		
	}
	
	void Entry::insertTextUnicode (SDLKey k, int i) {
		
		if (!getEntryActive()->verifyKey(k)) {
			char c[4];
			sprintf(c, "%c", i);

			if (WorkingData::GetInstance()->validCharacter(c)) insertText(c);
		}
		
		
	}
	
	void Entry::introText(string t) {
		if ( (!((int)text.length()+1>maxLetters)) || (maxLetters<0) ) {
			if ( (t=="|") && (!multiline) ) return;
			text.insert(posCursor, t);
			forwardCursor();
			updateText();
		}
	}
	
	void Entry::updateText()
	{
        if (!multiline) {
                        
    		SDL_Surface *sfc;
    		
    		if (text == "") {
    			sfc = Primitives::GetInstance()->rectangle(1, 1, 0, 0, 0);
    		} else {
    			sfc = Fonts::GetInstance()->getSurface_TextBitMap(font, ALIGN_LEFT, text);
    		}
    				
    		this->changeFrameSurface(0, sfc);
    				
    		this->setScaleH(height);
    		
        } else {
			
    		SDL_Surface *sfc;
    		if (text == "") {
    			sfc = Primitives::GetInstance()->rectangle(1, 1, 0, 0, 0);
    		} else {
    			sfc = Fonts::GetInstance()->getSurface_TextBitMap(font, totalRows, getCurrentScaleX(), width, ALIGN_LEFT, text);
    		}
			this->changeFrameSurface(0, sfc);
			
    		InfoFontBitMap info = Fonts::GetInstance()->getInfoFontBitMap(font, totalRows, getCurrentScaleX(), width, ALIGN_LEFT, text);
    		text = info.text;
    		currentRow = info.nLines;
    		
			if (info.nLettersByLine[(int)info.nLettersByLine.size()-1] == 0) {
    			this->setScaleH((currentRow-1)*height);
			} else {
				this->setScaleH(currentRow*height);
			}
			
        }
	}
	
	void Entry::onOver()
	{
		bg->onOver();
	}
	
	bool Entry::isOnMouseOver()
	{
		return bg->isOnMouseOver();
	}
	
	void Entry::draw()
	{
        if (drawBox) {
    		if (active)
    			select->draw();
    		else
    			bg->draw();
        }
		if (label!="")
			elmLabel->draw();
		
		if (text!="") {
			move();
			transforms();
			paintSprite();
		}
		if (active) {
            elmCursor->draw();
        }
	}
	
	void Entry::unLoad()
	{
		/*for (int i=0; i<(int)sprite.size(); i++)
			sprite[i]->unLoad();
		sprite.clear();*/
		delete bg;
		delete select;
		delete elmLabel;
		delete elmCursor;
	}
	
	/*****************************
	**
	** CLASS SELECTBUTTON
	**
	******************************/
	
	SelectButton::SelectButton()  : Group () {
		isRollOver = false;
		arrows = false;
		sensitive = true;
		indexz = 0;
		minSeparateButtons = 0;
		greaterWidthObject = 0;
		
		textAlt = "";
		alignAlt = ALIGN_LEFT;
		soundClick = "";
		
		elObjects = new Element();
		elObjects->setGroup(this);
		
		elArrowLeft = new Button();
		elArrowLeft->setVAlign(VALIGN_CENTER);
		elArrowLeft->addFrameSurface(Primitives::GetInstance()->rectangle(20, 20, 255, 0, 0));
		elArrowLeft->setGroup(this);
		
		elArrowRight = new Button();
		elArrowRight->setVAlign(VALIGN_CENTER);
		elArrowRight->addFrameSurface(Primitives::GetInstance()->rectangle(20, 20, 255, 0, 0));
		elArrowRight->setGroup(this);
		
	}
	
	SelectButton::~SelectButton () {
		unLoad();
	}
	
	void SelectButton::setSensitive(bool s) { 
         sensitive = s;  
         if (sensitive) {
             elObjects->setRGB(255,255,255);
             elArrowLeft->setRGB(255,255,255);
             elArrowRight->setRGB(255,255,255);
         } else {
             elObjects->setRGB(100,100,100);
             elArrowLeft->setRGB(100,100,100);
             elArrowRight->setRGB(100,100,100);
         }
    }
	
	bool SelectButton::onOver()
	{
		
        if (sensitive) {
    		if (isOnMouseOver() && !isRollOver) {
				if (textAlt!="") Cursor::GetInstance()->showText(textAlt, alignAlt, valignAlt);
				isRollOver = true;
				return true;
    		}
    		if (!isOnMouseOver() && isRollOver) {
				if (textAlt!="") Cursor::GetInstance()->hideText(textAlt);
				isRollOver = false;
				return true;
    		}
        }
		return false;
		
	}
	
	void SelectButton::setArrows(SDL_Surface* left, SDL_Surface* right) {
		arrows = true;
		elArrowLeft->changeFrameSurface(0, left);
		elArrowLeft->setX(0);
		elArrowLeft->setY(0);
				
		elArrowRight->changeFrameSurface(0, right);

		if (greaterWidthObject<minSeparateButtons) {
              greaterWidthObject = minSeparateButtons;
        }
        
  		elArrowRight->setX(elArrowLeft->getWidth()+10+greaterWidthObject);
  		elArrowRight->setY(0);
  		   
    	elObjects->setX(elArrowLeft->getWidth()+5+(greaterWidthObject/2));
    	elObjects->setY(0);
    	elObjects->setAlign(ALIGN_CENTER);
    	elObjects->setVAlign(VALIGN_CENTER);

	}
	
	
	bool SelectButton::isOnMouseOver()
	{
	
		int mouse_x, mouse_y;
	
		SDL_PumpEvents();
		
		SDL_GetMouseState(&mouse_x, &mouse_y);
		
		float x1, x2, y1, y2;
			
		if (!arrows) {
			x1 = elObjects->getX();
			y1 = elObjects->getY();
			x2 = x1 + elObjects->getWidth();
			y2 = y1 + elObjects->getHeight();
		} else {
			int mostHeight = 0;
			if ( elArrowLeft->getHeight() > mostHeight ) mostHeight = elArrowLeft->getHeight();
			if ( elObjects->getHeight() > mostHeight ) mostHeight = elObjects->getHeight();
			if ( elArrowRight->getHeight() > mostHeight ) mostHeight = elArrowRight->getHeight();
				
			x1 = elArrowLeft->getX();
			y1 = elArrowLeft->getY()-(mostHeight/2);
			x2 = x1 + greaterWidthObject + elArrowLeft->getWidth() + elArrowRight->getWidth() + 10;
			y2 = y1 + mostHeight;
		}
		
		if ( (mouse_x > x1) && (mouse_x < x2) &&
			(mouse_y > y1) && (mouse_y < y2) ) {
			return true;
		}
	
		return false;
	
	}
	
	int SelectButton::getOverBottom() {
		if (elArrowLeft->isOnMouseOver()) return LEFT;
		if (elArrowRight->isOnMouseOver()) return RIGHT;	
		return -1;
	}
	
	void SelectButton::addObject(SDL_Surface* sfc)
	{
		if (sfc->w > greaterWidthObject) greaterWidthObject = sfc->w;
		elObjects->addFrameSurface(sfc);
	}
		
	
	void SelectButton::unLoad()
	{
		delete elObjects;
		if (arrows) { 
			delete elArrowLeft;
			delete elArrowRight;
		}
	}
	
	void SelectButton::draw()
	{
		elObjects->draw();
		if (arrows) { 
			elArrowLeft->draw();
			elArrowRight->draw();
		}
	}


	/*****************************
	**
	** CLASE Particle
	**
	******************************/
	
	Particle::Particle(ParticlesSystem *ps) : Element () {
	
		particlesSystem = ps;
	
        type = TYPE_EXPLOSION;
        cyclesLife = Converter::GetInstance()->ml2cycles(1000);
        currentCyclesLife = 0;
        
        displacementX = 0;
        displacementY = 0;
        
        positionX = 0; 
        positionY = 0;
        positionW = World::width; 
        positionH = World::height;
        
        changeColor = false;
        currentColor = 0;
        
        color.r = 255;
        color.g = 255;
        color.b = 255;
        
        setRGB(color.r, color.g, color.b);
        
        state = PARTICLE_BEINGBORN;
        
        factorAlpha = 6;
        
        returnToBeBorn = false;
        
        setAlign(ALIGN_CENTER);
        setVAlign(VALIGN_CENTER);
        
        rot = 5;
        
        scale = 0.03;
        
    }
	
	Particle::~Particle () {
		unLoad();
	}
    
    void Particle::setMlLife(int ml) { 
        cyclesLife = Converter::GetInstance()->ml2cycles(ml); 
    }
    
	void Particle::start() {
		show();
		currentCyclesLife = 0;
		
		if (type == TYPE_EXPLOSION) setCurrentScale(1.0);
		
		setRot(0);
		
		setX( positionX + (rand()%(int)positionW) );
		setY( positionY + (rand()%(int)positionH) );
		
	}
	
	void Particle::setPositions(float px, float py, float pw, float ph) {
        positionX = px; 
        positionY = py;
        positionW = pw; 
        positionH = ph;
	}
	
	void Particle::change () {
        if (type == TYPE_EXPLOSION) {
            switch (state) {
                case PARTICLE_BEINGBORN:
                     addAlpha(factorAlpha);
                     if (getAlpha()>=255) {
                         state = PARTICLE_LIFE;
                         setAlpha(255);
                     }
                break;
                case PARTICLE_LIFE:
                     addCurrentCyclesLife();
                     if (currentCyclesLife>=cyclesLife) state = PARTICLE_DYING;
                break;   
                case PARTICLE_DYING:
                     addAlpha(-factorAlpha);
                     if (getAlpha()<=0) {
                        state = PARTICLE_BEINGBORN;
                        setAlpha(0);
                        if (!returnToBeBorn) hide();
                     }
                break;    
            }
            
            if (changeColor) {
                addCurrentColor();
                setRGB(particlesSystem->colors->getColor(currentColor)->r, particlesSystem->colors->getColor(currentColor)->g, particlesSystem->colors->getColor(currentColor)->b); 
            }
            
            addRot(rot);
            addCurrentScale(scale);
            
    		float factorMovHorizontal = 2.0f;
    		float factorMovVertical = 2.0f;
            
    		float rangox = (float)(rand()%(int)factorMovHorizontal)-((factorMovHorizontal/2)-0.5);
    		float rangoy = (float)(rand()%(int)factorMovVertical)-((factorMovVertical/2)-0.5);
    		addX(rangox);
    		addY(rangoy);
    		
        } else if (type == TYPE_STARS) {
               
            switch (state) {
                case PARTICLE_BEINGBORN:
                     addAlpha(factorAlpha);
                     if (getAlpha()>=255) {
                        state = PARTICLE_LIFE;
                        setAlpha(255);
                     }
                break;
                case PARTICLE_LIFE:
                     if (outLimitScreen()) { 
                         state = PARTICLE_BEINGBORN;
                         setAlpha(0);
                         start();
						 setX( positionX + (rand()%((int)positionW)/4) );
                     }
                break; 
            }
            
            if (changeColor) {
                addCurrentColor();
                setRGB(particlesSystem->colors->getColor(currentColor)->r, particlesSystem->colors->getColor(currentColor)->g, particlesSystem->colors->getColor(currentColor)->b); 
            }
			
    		addX(displacementX);
    		addY(displacementY);
    		
        }
	}
	
	/*****************************
	**
	** CLASE ParticlesSystem
	**
	******************************/
	
	ParticlesSystem::ParticlesSystem() {
        type = TYPE_EXPLOSION;
        positionX = 0; 
        positionY = 0;
        positionW = World::width; 
        positionH = World::height;
		
	    nParticles = NPARTICLES;	
        indexz = 0;
        int i;
		for (i=0; i<nParticles; i++) {
			particles[i] = new Particle(this);
			particles[i]->hide();
		}
		
		colors = new VectorColors();
		colors->addColor(100,200,156);
		colors->addColor(76,68,43);
		colors->addColor(245,190,255);
		colors->addColor(34,2,23);
		colors->addColor(100,100,167);
		colors->addColor(255,20,0);
		colors->addColor(129,212,5);
		colors->addColor(45,45,88);
		colors->addColor(45,123,234);
		colors->addColor(72,45,178);
		colors->addColor(92,232,91);
		colors->addColor(90,178,210);
		
    }
    
	ParticlesSystem::ParticlesSystem(int np) {
		type = TYPE_EXPLOSION;
        positionX = 0; 
        positionY = 0;
        positionW = World::width; 
        positionH = World::height;
		
        if (np>NPARTICLES) {
		    nParticles = NPARTICLES;	
        } else {
            nParticles = np;   
        }
        indexz = 0;
        int i;
		for (i=0; i<nParticles; i++) {
			particles[i] = new Particle(this);
			particles[i]->hide();
		}
		
		colors = new VectorColors();
		colors->addColor(100,200,156);
		colors->addColor(76,68,43);
		colors->addColor(245,190,255);
		colors->addColor(34,2,23);
		colors->addColor(100,100,167);
		colors->addColor(255,20,0);
		colors->addColor(129,212,5);
		colors->addColor(45,45,88);
		colors->addColor(45,123,234);
		colors->addColor(72,45,178);
		colors->addColor(92,232,91);
		colors->addColor(90,178,210);
		
    }
	
	ParticlesSystem::~ParticlesSystem () {
		unLoad();
	}
    
    bool ParticlesSystem::isVisible() {
		int i;
		for (i=0; i<nParticles; i++) {
			if (particles[i]->isVisible()) {
               return true;
            }
		}
		return false;
	}
	
	void ParticlesSystem::setType(int t) {
		type = t;
		int i;
		for (i=0; i<nParticles; i++) {
			particles[i]->setType(t);
		}
	}
	
	void ParticlesSystem::start() {
		int i;
		for (i=0; i<nParticles; i++) {
			particles[i]->start();
		}
	}
	
	void ParticlesSystem::setFrame(SDL_Surface* sfc) {
		int i;
		for (i=0; i<nParticles; i++) {
			particles[i]->addFrameSurface(sfc);
		}
	}
	
	void ParticlesSystem::setFrame(string fr) {
		int i;
		for (i=0; i<nParticles; i++) {
			particles[i]->addFrameFile(fr);
		}
	}
	
	void ParticlesSystem::setPositions(float px, float py, float pw, float ph) {
        positionX = px; 
        positionY = py;
        positionW = pw; 
        positionH = ph;
		int i;
		for (i=0; i<nParticles; i++) {
			particles[i]->setPositions(px, py, pw, ph);
		}
	}

	void ParticlesSystem::setChangeColor(bool cl) {
		int i;
		for (i=0; i<nParticles; i++) {
			particles[i]->setChangeColor(cl);
		}
	}
	
	void ParticlesSystem::setScale(int s) {
		int i;
		for (i=0; i<nParticles; i++) {
			particles[i]->setScale(s);
		}
	}
	
	void ParticlesSystem::setCurrentScale(float s) {
		int i;
		for (i=0; i<nParticles; i++) {
			particles[i]->setCurrentScale(s);
		}
	}
	
	void ParticlesSystem::setRotation(int r) {
		int i;
		for (i=0; i<nParticles; i++) {
			particles[i]->setRotation(r);
		}
	}
	
	void ParticlesSystem::setFactorAlpha(float fa) {
		int i;
		for (i=0; i<nParticles; i++) {
			particles[i]->setFactorAlpha(fa);
		}
	}
	
	void ParticlesSystem::setMlLife(int ml) {
		int i;
		for (i=0; i<nParticles; i++) {
			particles[i]->setMlLife(ml);
		}
	}
	
	void ParticlesSystem::setMlLife(int ml1, int ml2) {
		int i;
		for (i=0; i<nParticles; i++) {
            int ml = rand()%(int)(ml2-ml1);
			particles[i]->setMlLife(ml);
		}
	}
	
    void ParticlesSystem::setDisplacementX(float b, float e) {
		int i;
		for (i=0; i<nParticles; i++) {
            /*float d = rand()%(int)(e-b);
            d += b;*/
			float d = rand()%(int)((e-b)*10);
			d /= 10.0;
            d += b;
			if (d==0.0) d=0.1;
			particles[i]->setDisplacementX(d);
		}
    }
    
	void ParticlesSystem::setDisplacementY(float b, float e) {
		int i;
		for (i=0; i<nParticles; i++) {
			float d = rand()%(int)((e-b)*10);
			d /= 10.0;
			d += b;
			if (d==0.0) d=0.1;
			particles[i]->setDisplacementY(d);
		}
    }
	
	void ParticlesSystem::setReturnToBeBorn(bool r) {
		int i;
		for (i=0; i<nParticles; i++) {
			particles[i]->setReturnToBeBorn(r);
		}
	}
    
	void ParticlesSystem::draw() {
		int i;
		for (i=0; i<nParticles; i++) {
			if (particles[i]->isVisible()) {
				particles[i]->change();
				particles[i]->draw();
			}
		}
	}
	
	void ParticlesSystem::unLoad() {
		int i;
		for (i=0; i<nParticles; i++) {
			delete particles[i];
		}
		delete colors;
	}

	
}
