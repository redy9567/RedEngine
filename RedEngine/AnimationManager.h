#include "Trackable.h"
#include <vector>

class Animation;
class AnimationData;

class AnimationManager : public Trackable
{

public:
    AnimationManager();
    ~AnimationManager();

    int getNumOfAnimations() { return mAnimations.size(); }

    Animation* createAnimation(AnimationData* data, int fps);
    Animation* createAndManageAnimation(AnimationData* data, int fps);

    void addAnimation(Animation* anim);
    void removeAnimation(Animation* anim);
    void removeAndDeleteAnimation(Animation* anim);
    void deleteAnimation(Animation* anim);

    int findAnimation(Animation* anim);
    Animation* getAnimationAt(int index);

    void update(float deltaTime);

    void clear();

private:
    std::vector<Animation*> mAnimations;
};