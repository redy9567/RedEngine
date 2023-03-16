#pragma once
#include <unordered_map>
#include <string>
#include <Vector2D.h>

class GameObject2D;
class Sprite;
class Animation;

class GameObject2DManager : public Trackable
{
public:
	friend class GraphicsSystem;

private:
	static GameObject2DManager* getInstance();
	static void cleanupInstance();

	void init();
	void cleanup();

	GameObject2D* createAndAddGameObject2D(std::string key, Sprite*, Vector2D loc = Vector2D::Zero());
	GameObject2D* createAndAddGameObject2D(std::string key, Animation*, Vector2D loc = Vector2D::Zero());
	void removeAndDeleteGameObject2D(std::string key);

	GameObject2D* getGameObject2D(std::string key);

	GameObject2DManager();
	~GameObject2DManager();

	static GameObject2DManager* mspInstance;

	std::unordered_map<std::string, GameObject2D*> mGameObjects;
};