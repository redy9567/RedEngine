#pragma once
#include "Trackable.h"
#include "Vector2D.h"
#include <unordered_map>
#include <string>

class Animation;
class AnimationData;
class Texture2D;

class AnimationManager : public Trackable
{

public:
	friend class GraphicsSystem;

private:
	static AnimationManager* getInstance();
	static void cleanupInstance();

	void init();
	void cleanup();

	//AnimationData
	AnimationData* createAndAddAnimationData(std::string key, Texture2D** texture, int numHorizontal, int numVertical, Vector2D scale = Vector2D::One());
	void removeAnimationData(std::string key);

	//Animation
	Animation* createAndAddAnimation(std::string key, std::string animationDataKey, int mFPS);
	void removeAnimation(std::string key);
	Animation* getAnimation(std::string key) { return mAnimations.at(key); }

	AnimationManager();
	~AnimationManager();

	static AnimationManager* mspInstance;

	std::unordered_map<std::string, Animation*> mAnimations;
	std::unordered_map<std::string, AnimationData*> mAnimationData;

};
