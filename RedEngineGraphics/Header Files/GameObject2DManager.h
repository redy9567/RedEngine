#pragma once
#include <vector>
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

	GameObject2D* createGameObject2D(Sprite*, Vector2D loc = Vector2D::Zero());
	GameObject2D* createAndAddGameObject2D(Sprite*, Vector2D loc = Vector2D::Zero(), bool useTopAnchoring = false);
	GameObject2D* createAndAddGameObject2D(Animation*, Vector2D loc = Vector2D::Zero());
	void removeAndDeleteGameObject2D(GameObject2D* obj);
	void removeAndDeleteGameObject2D(int id);
	void addGameObject2D(GameObject2D*);

	void updateAll(float deltaTime);

	void drawAll();

	GameObject2D* getGameObject2D(int id);

	GameObject2DManager();
	~GameObject2DManager();

	static GameObject2DManager* mspInstance;

	std::vector<GameObject2D*> mGameObjects;
};