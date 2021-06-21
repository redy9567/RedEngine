#include "Trackable.h"
#include <vector>

class Sprite;
class GraphicsBuffer;

class AnimationData : public Trackable
{

public:
    AnimationData(Sprite* frames, int numOfFrames);
	AnimationData(GraphicsBuffer* gb, int rows, int columns, float scale = 1.0f);
	~AnimationData();

    Sprite* getSprite(int index);
    int getFrameCount() { return mSprites.size(); }

private:
    AnimationData() = delete;

    std::vector<Sprite*> mSprites;
	bool mOwnsSprites;

};