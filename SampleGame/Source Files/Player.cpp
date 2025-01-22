#include "Player.h"
#include "EventSystem.h"
#include "PlayerMoveEvent.h"

Player::Player()
    : GameObject2D()
{
    
}

Player::Player(Animation* anim, float moveSpeed, Vector2D loc)
    : GameObject2D(anim, loc)
{
    mMoveDir = Vector2D::Zero();
    mSpeed = moveSpeed;
}

Player::~Player()
{
    
}

void Player::update(float deltaTime)
{

    if(mMoveDir != Vector2D::Zero())
	{
		mLoc += mMoveDir * deltaTime * mSpeed;
		EventSystem::getInstance()->fireEvent(PlayerMoveEvent(mLoc));
	}
}

void Player::setMoveDirection(Vector2D dir)
{
    mMoveDir = dir;
}