#pragma once
#include "Trackable.h"
#include <string>
#include <vector>
#include "Vector2D.h"

class Texture2D : public Trackable
{

public:
	friend class GraphicsSystem;
	friend class Mesh2D;
	friend class Texture2DManager;

	int getHeight() { return mHeight; }
	int getWidth() { return mWidth; }
	Vector2D getSize() { return Vector2D(mWidth, mHeight); }

private:
	Texture2D(std::string filepath, bool hasAlpha = false);
	Texture2D(std::vector<std::string> filepaths, bool hasAlpha = false);
	~Texture2D();
	Texture2D() = delete;

	void freeRawData();

	int mHeight;
	int mWidth;
	int mNRChannels;

	bool mHasAlpha;

	unsigned int mTOI;

	std::vector<unsigned char*> mData;

	int mReferences; //Count of how many objects are using this texture

};
