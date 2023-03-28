#pragma once
#include "Trackable.h"
#include <unordered_map>
#include <string>

class Texture2D;

class Texture2DManager : public Trackable
{
public:
	friend class GraphicsSystem;

private:
	static Texture2DManager* getInstance();
	static void cleanupInstance();

	void init();
	void cleanup();

	Texture2D* createAndAddTexture2D(std::string key, std::string filepath, bool hasAlpha = false);
	void removeAndDeleteTexture2D(std::string key);

	Texture2DManager();
	~Texture2DManager();

	static Texture2DManager* mspInstance;

	std::unordered_map<std::string, Texture2D*> mTextures;
};