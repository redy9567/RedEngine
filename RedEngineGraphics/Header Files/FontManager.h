#pragma once
#include "Trackable.h"
#include <string>
#include <unordered_map>
#include "FreeType/ft2build.h"
#include "FreeType/freetype/freetype.h"

class Font;

class FontManager : public Trackable
{

public:
	friend class GraphicsSystem;

private:
	static FontManager* getInstance();
	static void cleanupInstance();

	bool init();
	void cleanup();

	//Font
	void createAndAddFont(std::string key, std::string filepath, int pointSize = 12);
	void removeAndDeleteFont(std::string key);
	Font* getFont(std::string key) { return mFonts.at(key); }

	FontManager();
	~FontManager();

	static FontManager* mspInstance;

	std::unordered_map<std::string, Font*> mFonts;

	FT_Library* mpFreeTypeLibrary;

	unsigned int mVBO, mVAO; //Shared vertex objects for OpenGL drawing

};