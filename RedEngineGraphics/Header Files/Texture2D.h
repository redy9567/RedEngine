#pragma once
#include "Trackable.h"
#include <string>

class Texture2D : public Trackable
{

public:
	friend class GraphicsSystem;
	friend class Mesh2D;

	Texture2D(std::string filepath, bool hasAlpha = false);
	~Texture2D();

	int getHeight() { return mHeight; }
	int getWidth() { return mWidth; }

private:
	Texture2D() = delete;

	void freeRawData();

	int mHeight;
	int mWidth;
	int mNRChannels;

	bool mHasAlpha;

	unsigned int mTOI;

	unsigned char* mData;

	int mReferences; //Count of how many objects are using this texture

};
