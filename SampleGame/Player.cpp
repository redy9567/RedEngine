#include "Player.h"

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
    mLoc += mMoveDirection * deltaTime * mMovementSpeed;
}

void Player::setMoveDirection(Vector2D dir)
{
    mMoveDirection = dir;
}