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
#include "language.h"

namespace Martian {
	 
	/*****************************
	**
	** CLASE LANGUAGE
	**
	******************************/	

	Language* Language::instance = NULL;
	
	Language::Language() {
	}
	
	Language* Language::GetInstance () {
		if ( instance == NULL ) {
			instance = new Language();
		}
		return instance;	
	}
	
	void Language::setLang ( string c ) {
        if (c!="") {
    		lang = c;
    		dictionary.clear();
    		char file[128];
    		sprintf(file, "%s/languages.xml", DATA_DIR);
    		parseXML(file, lang);
        }	
	}
	
	string Language::getText ( string ref ) {
		int i;
		for (i=0; i<(int)dictionary.size(); i++) {
			if (dictionary[i].reference == ref) {
				return dictionary[i].text;
			}
		}
		printf("Language: '%s' don't find\n", ref.c_str());
		return "-";
	}
	
	string Language::getFilename(string file, string ext) {
        return file + "_" + lang + "." + ext;
    }
	
	void Language::addPhrase(string ref, string txt) {
		Phrase f;
		f.reference = ref;
		f.text = txt;
		dictionary.push_back(f);
	}
	
	
	/*****************************
	**
	** XML
	**
	******************************/
	
	static void startXML(void *userData, const char *el, const char **attr) {
		int i;
		DictionaryXML* data = (DictionaryXML*)userData;
		
		if (data->inPhrase) {
			if (strcmp(el, data->lang.c_str()) == 0) {
				for (i = 0; attr[i]; i += 2) {
					if (strcmp(attr[i], "value") == 0) {
						data->text = attr[i+1];
					}
				}
				Language::GetInstance()->addPhrase(data->reference, data->text);
			}
		} else {
			if (strcmp(el, "phrase") == 0) {
				data->inPhrase = true;
				for (i = 0; attr[i]; i += 2) {
					if (strcmp(attr[i], "name") == 0) {
						data->reference = attr[i+1];
					}
				}
			}
		}
	}
	
	static void endXML(void *userData, const char *el)
	{
		DictionaryXML* data = (DictionaryXML*)userData;
		
		if (strcmp(el, "phrase") == 0) { 
			data->inPhrase = false;
		}
		
	}
		
	void parseXML(char fileXML[128], string l) {
		char buffer[8192];
		int done;
		
		DictionaryXML data;
		data.lang = l;
		data.inPhrase = false;
		
		XML_Parser p = XML_ParserCreate("UTF-8");
		if (! p) {
			printf("It could not have sufficient memory parser\n");
		}
	
		XML_SetUserData(p, &data);	
		XML_SetElementHandler(p, startXML, endXML);
	
		FILE *file = fopen(fileXML, "r");
		if(!file)
			printf("Error opening file XML\n");
		
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
	
}
