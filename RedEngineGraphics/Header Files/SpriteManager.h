#pragma once
#include "Trackable.h"
#include <unordered_map>
#include <string>
#include <Vector2D.h>
#include "Sprite.h"

class Texture2D;

class SpriteManager : public Trackable
{
public:
	friend class GraphicsSystem;

private:
	static SpriteManager* getInstance();
	static void cleanupInstance();

	void init();
	void cleanup();

	Sprite* createAndAddSprite(std::string key, Texture2D** texture, Vector2D textureStartLoc, Vector2D size, Vector2D scale = Vector2D::One(), ImageAnchor anchoring = ImageAnchor::Center);
	void removeAndDeleteSprite(std::string key);
	Sprite* getSprite(std::string key) { return mSprites.find(key) == mSprites.end() ? nullptr : mSprites.at(key); }

	SpriteManager();
	~SpriteManager();

	static SpriteManager* mspInstance;

	std::unordered_map<std::string, Sprite*> mSprites;
};