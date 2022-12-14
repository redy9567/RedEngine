#include "AnimationData.h"
#include "Sprite.h"
#include "Texture2D.h"

Sprite* AnimationData::getSprite(int index)
{
	if (mCount == 0)
		return nullptr;

	return mSprites[index];
}

AnimationData::AnimationData(Texture2D** texture, int numHorizontal, int numVertical, Vector2D scale)
{
	Texture2D* tex = *texture;

	int spriteWidth = tex->getWidth() / numHorizontal;
	int spriteHeight = tex->getHeight() / numVertical;

	mCount = numHorizontal * numVertical;
	mSprites = new Sprite*[mCount];

	for (int i = 0; i < numVertical; i++)
	{
		for (int j = 0; j < numHorizontal; j++)
		{
			mSprites[i * numVertical + j] =
				new Sprite(
					texture,
					Vector2D(j * spriteWidth, i * spriteHeight),
					Vector2D(spriteWidth * j, 0),
					Vector2D(spriteWidth, spriteHeight),
					scale);
		}
	}
}

AnimationData::~AnimationData()
{
	for (int i = 0; i < mCount; i++)
	{
		delete mSprites[i];
	}

	delete[] mSprites;
}