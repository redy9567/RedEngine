#pragma once
#include "raylib-cpp.hpp"
#include "Trackable.h"
#include "Vector2D.h"

class GraphicsBuffer : public Trackable
{
public:
	friend class GraphicsSystem;

	GraphicsBuffer(std::string filename);
	~GraphicsBuffer();

	void loadFromFile(std::string filename);

	void unload();

private:
	GraphicsBuffer() = delete;

	raylib::Texture* mTexture;
	int mWidth, mHeight;

};