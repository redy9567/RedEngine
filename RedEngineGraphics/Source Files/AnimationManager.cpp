#include "AnimationManager.h"
#include "AnimationData.h"
#include "Animation.h"

using namespace std;

AnimationManager* AnimationManager::mspInstance = nullptr;

AnimationManager* AnimationManager::getInstance()
{
	if (!mspInstance)
		mspInstance = new AnimationManager();

	return mspInstance;
}

void AnimationManager::cleanupInstance()
{
	if (mspInstance)
	{
		delete mspInstance;
		mspInstance = nullptr;
	}
}

AnimationManager::AnimationManager()
{

}

AnimationManager::~AnimationManager()
{

}

void AnimationManager::init()
{

}

void AnimationManager::cleanup()
{
	for (vector<Animation*>::iterator it = mAnimations.begin();
		it != mAnimations.end(); it++)
	{
		delete *it;
	}
	mAnimations.clear();

	for (unordered_map<string, AnimationData*>::iterator it = mAnimationData.begin();
		it != mAnimationData.end(); it++)
	{
		delete it->second;
	}
	mAnimationData.clear();
}

AnimationData* AnimationManager::createAndAddAnimationData(string key, Texture2D** texture, int numHorizontal, int numVertical, Vector2D scale)
{
	AnimationData* data = new AnimationData(texture, numHorizontal, numVertical, scale);

	mAnimationData.emplace(key, data);

	return data;
}

void AnimationManager::removeAnimationData(string key)
{
	AnimationData* data = mAnimationData.at(key);

	if (data)
	{
		delete data;
		mAnimationData.erase(key);
	}
}

Animation* AnimationManager::createAndAddAnimation(string animationDataKey, int mFPS, bool isLooping)
{
	AnimationData* data = mAnimationData.at(animationDataKey);

	if (!data)
		return nullptr;

	Animation* anim = new Animation(data, mFPS, isLooping);
	mAnimations.push_back(anim);
	return anim;
}

void AnimationManager::removeAndDeleteAnimation(int id)
{
	int i = 0;
	for (vector<Animation*>::iterator it = mAnimations.begin(); it != mAnimations.end(); it++)
	{
		if (i++ == id)
		{
			delete *it;
			mAnimations.erase(it);
			return;
		}
		
	}
}

void AnimationManager::removeAndDeleteAnimation(Animation* anim)
{
	for (vector<Animation*>::iterator it = mAnimations.begin(); it != mAnimations.end(); it++)
	{
		if (*it == anim)
		{
			delete anim;
			mAnimations.erase(it);
			return;
		}
	}
}