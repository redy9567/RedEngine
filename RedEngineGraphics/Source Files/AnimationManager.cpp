#pragma once
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
	for (unordered_map<string, Animation*>::iterator it = mAnimations.begin();
		it != mAnimations.end(); it++)
	{
		delete it->second;
	}
	mAnimations.clear();

	for (unordered_map<string, AnimationData*>::iterator it = mAnimationData.begin();
		it != mAnimationData.end(); it++)
	{
		delete it->second;
	}
	mAnimationData.clear();
}

void AnimationManager::createAndAddAnimationData(string key, Texture2D** texture, int numHorizontal, int numVertical, Vector2D scale)
{
	AnimationData* data = new AnimationData(texture, numHorizontal, numVertical, scale);

	mAnimationData.emplace(key, data);
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

bool AnimationManager::createAndAddAnimation(string key, string animationDataKey, int mFPS)
{
	AnimationData* data = mAnimationData.at(animationDataKey);

	if (!data)
		return false;

	Animation* anim = new Animation(data, mFPS);
	mAnimations.emplace(key, anim);
}

void AnimationManager::removeAnimation(string key)
{
	Animation* anim = mAnimations.at(key);

	if (anim)
	{
		delete anim;
		mAnimations.erase(key);
	}
}

void AnimationManager::update(float deltaTime)
{
	for (unordered_map<string, Animation*>::iterator it = mAnimations.begin();
		it != mAnimations.end(); it++)
	{
		it->second->update(deltaTime);
	}
}