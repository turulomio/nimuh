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
 #include "hash.h"

namespace Martian {
	 
	/*****************************
	**
	** CLASE Hash
	**
	******************************/	
	string Hash::pathData = "";
	
	Hash::Hash(string file, bool fromConfDirectory) {
        cursor =  0;
		if (fromConfDirectory) {
        	loadFromConfDirectory(file);
		} else {
			loadFromDataDirectory(file);
		}
	}
	
	bool Hash::setValue ( string name, string value ) {
		int i;
		for (i=0; i<(int)items.size(); i++) {
			if (items[i].name == name) {
                items[i].value = value;
				return true;
			}
		}
		return false;
	}
 
	string Hash::getValue ( string name ) {
		int i;
		for (i=0; i<(int)items.size(); i++) {
			if (items[i].name == name) {
				return items[i].value;
			}
		}
		printf("%s don't find\n", name.c_str());
		return "";
	}
	
	int Hash::getValueToInt(string name) {
		int i;
		for (i=0; i<(int)items.size(); i++) {
			if (items[i].name == name) {
				return atoi(items[i].value.c_str());
			}
		}
		printf("%s don't find\n", name.c_str());
		return -1;
	}
	
	void Hash::addItem(string name, string value) {
         
		int i;
		bool isName = false;
		for (i=0; i<(int)items.size(); i++) {
			if (items[i].name == name) {
				isName = true;
			}
		}
        if (isName) {
            setValue(name, value);
        } else {
            Item i;
		    i.name = name;
            i.value = value;
            items.push_back(i);
       }
	}
	
	void Hash::loadFromConfDirectory(string f) { 
		if (Hash::pathData=="") {
			char *directory = NULL;
			char tmp_dir[128];
			if (getenv("HOME") != NULL) {
				directory = getenv("HOME");
				sprintf (tmp_dir, "mkdir %s/.%s", directory, CONFIG_DIR_UNIX);
				system(tmp_dir);
				sprintf (directory, "%s/.%s/", directory, CONFIG_DIR_UNIX);
			} else {
				directory = "./data/";
			}
			Hash::pathData = directory;
		}
        file = Hash::pathData + f; 
		
        FILE *c = fopen((char*)file.c_str(), "r");
        if(!c) save();
        parseHashXML((char*)file.c_str(), this); 
    }
	
	void Hash::loadFromDataDirectory(string f) { 
        file = string(DATA_DIR) + f; 
		
        FILE *c = fopen((char*)file.c_str(), "r");
        if(!c) save();
        parseHashXML((char*)file.c_str(), this); 
    }
    
	bool Hash::save() {
		
		FILE *f;
		f = fopen((char*)file.c_str(), "w+");
		
		char tmp_val[128];
		
		sprintf (tmp_val, "<?xml version=\"1.0\" encoding=\"ISO-8859-1\"?>\n<items>\n");
		fwrite(tmp_val, strlen(tmp_val), 1, f);
		
		int i;
		for (i=0; i<(int)items.size(); i++) {
			sprintf (tmp_val, "\t<item name=\"%s\" value=\"%s\" />\n", items[i].name.c_str(), items[i].value.c_str());
			fwrite(tmp_val, strlen(tmp_val), 1, f);
		}
		
		sprintf (tmp_val, "</items>\n");
		fwrite(tmp_val, strlen(tmp_val), 1, f);
		
		fclose(f);
	
		return true;
	}
	
	
	/*****************************
	**
	** XML
	**
	******************************/
	
	static void startHashXML(void *userData, const char *el, const char **attr) {
		int i;
		ItemXML* data = (ItemXML*)userData;
		
		if (strcmp(el, "item") == 0) {
            string n, v;
			for (i = 0; attr[i]; i += 2) {
				if (strcmp(attr[i], "name") == 0) {
					n = attr[i+1];
				}
				if (strcmp(attr[i], "value") == 0) {
					v = attr[i+1];
				}
			}
			data->hash->addItem(n, v);
		}

	}
	
	static void endHashXML(void *userData, const char *el)
	{
		//ItemXML* data = (ItemXML*)userData;
		
	}
		
	void parseHashXML(char fileXML[128], Hash *h) {
		char buffer[8192];
		int done;
		
		ItemXML data;
		data.hash = h;
		
		XML_Parser p = XML_ParserCreate("ISO-8859-1");
		if (! p) {
			printf("It could not have sufficient memory parser\n");
		}
	
		XML_SetUserData(p, &data);	
		XML_SetElementHandler(p, startHashXML, endHashXML);
	
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
	
}
