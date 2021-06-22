#include "AnimationManager.h"
#include "AnimationData.h"
#include "Animation.h"

using namespace std;

AnimationManager::AnimationManager()
{

}

AnimationManager::~AnimationManager()
{
    if(!mAnimations.empty())
    {
        clear();
    }
}

Animation* AnimationManager::createAnimation(AnimationData* data, int fps)
{
    return new Animation(data, fps);
}

Animation* AnimationManager::createAndManageAnimation(AnimationData* data, int fps)
{
    Animation* anim = new Animation(data, fps);
    mAnimations.push_back(anim);
    return anim;
}

void AnimationManager::addAnimation(Animation* anim)
{
    mAnimations.push_back(anim);
}

void AnimationManager::removeAnimation(Animation* anim)
{
    for(vector<Animation*>::iterator i = mAnimations.begin(); i != mAnimations.end(); i++)
    {
        if(*i == anim)
        {
            mAnimations.erase(i);
            return;
        }
    }
}

void AnimationManager::removeAndDeleteAnimation(Animation* anim)
{
    for(vector<Animation*>::iterator i = mAnimations.begin(); i != mAnimations.end(); i++)
    {
        if(*i == anim)
        {
            delete *i;
            mAnimations.erase(i);
            return;
        }
    }
}

void AnimationManager::deleteAnimation(Animation* anim)
{
    delete anim;
}

int AnimationManager::findAnimation(Animation* anim)
{
    int index = 0;
    for(vector<Animation*>::iterator i = mAnimations.begin(); i != mAnimations.end(); i++)
    {
        if(*i == anim)
        {
            return index;
        }
        index++;
    }
    return -1;
}

Animation* AnimationManager::getAnimationAt(int index)
{
    int ind = 0;
    for(vector<Animation*>::iterator i = mAnimations.begin(); i != mAnimations.end(); i++)
    {
        if(ind != index)
        {
            ind++;
            continue;
        }

        return *i;
    }
    return nullptr;
}

void AnimationManager::update(float deltaTime)
{
    for(vector<Animation*>::iterator i = mAnimations.begin(); i != mAnimations.end(); i++)
    {
        (*i)->update(deltaTime);
    }
}

void AnimationManager::clear()
{
    if(mAnimations.size() > 0)
    {
        for(vector<Animation*>::iterator i = mAnimations.begin(); i != mAnimations.end(); i++)
        {
            delete (*i);
        }
    }

    mAnimations.clear();
}