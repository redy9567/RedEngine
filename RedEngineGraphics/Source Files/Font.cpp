#include "Font.h"
#include "FreeType/ft2build.h"
#include "FreeType/freetype/freetype.h"
#include <iostream>
#include <assert.h>

using namespace std;

Font::Font(FT_Library* lib, string filepath, int pointSize) {
	mFilepath = filepath;
	mPointSize = pointSize;
	//GraphicsSystem will properly initilize this font.

	if (FT_New_Face(*lib, filepath.c_str(), 0, &mFontFace))
	{
		cout << "ERROR::FREETYPE: Failed to load font" << endl;
		assert(false);
	}

	FT_Set_Pixel_Sizes(mFontFace, 0, pointSize);

}

Font::~Font()
{
	//Font Face gets cleanedup by Graphics System during letter processing
}