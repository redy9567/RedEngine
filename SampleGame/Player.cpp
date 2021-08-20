#include "Player.h"
#include "EventSystem.h"
#include "PlayerMoveEvent.h"

Player::Player()
    : Unit()
{
    mMoveDirection = Vector2D::Zero();
    mMovementSpeed = 0.0f;
}

Player::Player(Animation* anim, float moveSpeed, Vector2D loc)
    : Unit(anim, loc)
{
    mMoveDirection = Vector2D::Zero();
    mMovementSpeed = moveSpeed;
}

Player::~Player()
{
    
}

void Player::update(double deltaTime)
{

    if(mMoveDirection != Vector2D::Zero())
	{
		mLoc += mMoveDirection * deltaTime * mMovementSpeed;
		EventSystem::getInstance()->fireEvent(PlayerMoveEvent(mLoc));
	}
}

void Player::setMoveDirection(Vector2D dir)
{
    mMoveDirection = dir;
}