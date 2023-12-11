#pragma once
#include <string>
#include "Trackable.h"
#include "FreeType/ft2build.h"
#include "FreeType/freetype/freetype.h"
#include <unordered_map>
#include "Vector2D.h"

class Font : public Trackable
{
public:
	friend class GraphicsSystem;
	friend class FontManager;


private:
	struct Character
	{
		unsigned int textureID;
		Vector2D size;
		Vector2D bearing;
		unsigned int advance;
	};

	Font(FT_Library* lib, std::string filepath, int pointSize = 12);
	~Font();

	Font() = delete;

	std::string mFilepath;
	int mPointSize = 12;
	FT_Face mFontFace;
	std::unordered_map<char, Character> mCharacters;
};