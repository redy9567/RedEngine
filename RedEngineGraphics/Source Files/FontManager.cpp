#include "FontManager.h"
#include "Font.h"
#include <iostream>

using namespace std;

FontManager* FontManager::mspInstance = nullptr;

FontManager* FontManager::getInstance()
{
	if (!mspInstance)
		mspInstance = new FontManager();

	return mspInstance;
}

void FontManager::cleanupInstance()
{
	if (mspInstance)
	{
		delete mspInstance;
		mspInstance = nullptr;
	}
}

FontManager::FontManager()
{
	mpFreeTypeLibrary = nullptr;
	mVBO = -1;
	mVAO = -1;
}

FontManager::~FontManager()
{

}

bool FontManager::init()
{
	mpFreeTypeLibrary = new FT_Library();

	if (FT_Init_FreeType(mpFreeTypeLibrary))
	{
		std::cout << "ERROR::FREETYPE: Could not init FreeType Library" << std::endl;
		return false;
	}
	return true;
}

void FontManager::cleanup()
{
	for (unordered_map<string, Font*>::iterator it = mFonts.begin();
		it != mFonts.end(); it++)
	{
		delete it->second;
	}
	mFonts.clear();

	FT_Done_FreeType(*mpFreeTypeLibrary);

	delete mpFreeTypeLibrary;
	mpFreeTypeLibrary = nullptr;
}

void FontManager::createAndAddFont(string key, string filepath, int pointSize)
{
	Font* font = new Font(mpFreeTypeLibrary, filepath, pointSize);

	mFonts.emplace(key, font);
}

void FontManager::removeAndDeleteFont(string key)
{
	Font* font = mFonts.at(key);

	if (font)
	{
		delete font;
		mFonts.erase(key);
	}
}
