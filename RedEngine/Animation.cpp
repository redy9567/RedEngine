#include "Animation.h"
#include "Sprite.h"
#include "GraphicsBuffer.h"

Animation::Animation(Sprite* frames, int numOfFrames, int fps)
{
	mSprites.resize(numOfFrames);

	for(int i = 0; i < numOfFrames; i++)
	{
		mSprites.push_back(frames + i); //Pointer math
	}

	mCurrentFrame = 0;
	mOwnsSprites = false;

	mFPS = fps;
	mTimePerFrame = 1.0 / fps;
	mTimer = 0.0;
}

Animation::Animation(GraphicsBuffer* gb, int rows, int columns, int fps)
{
	mCurrentFrame = 0;
	mOwnsSprites = true;

	mFPS = fps;
	mTimePerFrame = 1.0 / fps;
	mTimer = 0.0;

	int spriteWidth = gb->getWidth() / columns;
	int spriteHeight = gb->getHeight() / rows;

	
	for(int j = 0; j < rows; j++)
	{
		for(int i = 0; i < columns; i++)
		{
			Sprite* spr = new Sprite(gb, Vector2D(i * spriteWidth, j * spriteHeight), Vector2D(spriteWidth, spriteHeight));
			mSprites.push_back(spr);
		}
	}
}

Animation::~Animation()
{
	if (mOwnsSprites)
	{
		while(mSprites.size() > 0)
		{
			Sprite* spr = mSprites.back();
			delete spr;
			mSprites.pop_back();
		}	
		
	}
}

void Animation::update(double deltaTime)
{
	mTimer += deltaTime;
	while (mTimer >= mTimePerFrame)
	{
		mTimer -= mTimePerFrame;
		
		mCurrentFrame++;
		if (mCurrentFrame >= mSprites.size())
		{
			mCurrentFrame = 0;
		}
	}
}

Sprite* Animation::getCurrentSprite()
{
	return mSprites.at(mCurrentFrame);
}