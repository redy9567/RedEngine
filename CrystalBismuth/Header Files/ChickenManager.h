#pragma once
#include <vector>
#include <string>
#include <Vector2D.h>

class Chicken;
enum class ChickenColor;

const float DEFAULT_TIME_TO_HATCH = 20.0f;
const float DEFAULT_TIME_TO_MATURITY = 20.0f;
const float DEFAULT_TIME_TO_DEATH = 500.0f;

class ChickenManager : public Trackable
{
public:
	static ChickenManager* getInstance();
	static void cleanupInstance();

	void init();
	void cleanup();
	void update(float deltaTime);
	void drawAllChickens();

	Chicken* checkChickenHovered(Vector2D mousePos);

	Chicken* createAndAddChicken(ChickenColor color, Vector2D location = Vector2D::Zero());
	void removeAndDeleteChicken(Chicken* chicken);
	void removeAndDeleteChicken(int chickenID);

	Chicken* getChicken(int chickenID);

private:
	ChickenManager();
	~ChickenManager();

	bool checkBreeding(Chicken* chicken1, Chicken* chicken2);
	void breed(Chicken* chicken1, Chicken* chicken2);

	static ChickenManager* mspInstance;

	std::vector<Chicken*> mChickens;
};