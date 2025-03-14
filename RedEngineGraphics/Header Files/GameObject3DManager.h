#pragma once
#include <vector>
#include <string>
#include <Vector3D.h>

class GameObject3D;
class Sprite;
class Animation;
class Mesh3D;

class GameObject3DManager : public Trackable
{
public:
	friend class GraphicsSystem;

private:
	static GameObject3DManager* getInstance();
	static void cleanupInstance();

	void init();
	void cleanup();

	GameObject3D* createGameObject3D(Mesh3D* mesh, Vector3D loc = Vector3D::Zero(), Vector3D color = Vector3D::Zero(), Vector3D scale = Vector3D::One(), Vector3D rot = Vector3D::Zero());
	GameObject3D* createAndAddGameObject3D(Mesh3D* mesh, Vector3D loc = Vector3D::Zero(), Vector3D color = Vector3D::Zero(), Vector3D scale = Vector3D::One(), Vector3D rot = Vector3D::Zero());
	void removeAndDeleteGameObject3D(GameObject3D* obj);
	void removeAndDeleteGameObject3D(int id);
	void addGameObject3D(GameObject3D*);

	void updateAll(float deltaTime);

	void drawAll();

	GameObject3D* getGameObject3D(int id);

	GameObject3DManager();
	~GameObject3DManager();

	static GameObject3DManager* mspInstance;

	std::vector<GameObject3D*> mGameObjects;
};