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
	Animation* createAndAddAnimation(std::string animationDataKey, int mFPS, bool isLooping = false);
	void removeAndDeleteAnimation(int id);
	void removeAndDeleteAnimation(Animation* anim);
	Animation* getAnimation(int id) { return mAnimations.at(id); }

	AnimationManager();
	~AnimationManager();

	static AnimationManager* mspInstance;

	std::vector<Animation*> mAnimations;
	std::unordered_map<std::string, AnimationData*> mAnimationData;

};
