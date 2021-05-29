#include "Vector2D.h"

Vector2D::Vector2D()
{
	mX = 0.0f;
	mY = 0.0f;
}

Vector2D::~Vector2D()
{

}

Vector2D::Vector2D(float x, float y)
{
	mX = x;
	mY = y;
}

Vector2D::Vector2D(int x, int y)
{
	mX = (float)x;
	mY = (float)y;
}

Vector2D Vector2D::operator=(const Vector2D& other)
{
	mX = other.mX;
	mY = other.mY;
	return *this;
}