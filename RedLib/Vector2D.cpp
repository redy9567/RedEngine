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

Vector2D Vector2D::operator+(const Vector2D& other)
{
	return Vector2D(mX + other.mX, mY + other.mY);
}

Vector2D Vector2D::operator-(const Vector2D& other)
{
	return Vector2D(mX - other.mX, mY - other.mY);
}

Vector2D Vector2D::operator*(const float scalar)
{
	return Vector2D(scalar * mX, scalar * mY);
}

Vector2D Vector2D::operator/(const float scalar)
{
	return Vector2D(mX / scalar, mY / scalar);
}

Vector2D Vector2D::operator+=(const Vector2D& other)
{
	mX += other.mX;
	mY += other.mY;
	return *this;
}

Vector2D Vector2D::operator-=(const Vector2D& other)
{
	mX -= other.mX;
	mY -= other.mY;
	return *this;
}

Vector2D Vector2D::operator*=(const float scalar)
{
	mX *= scalar;
	mY *= scalar;
	return *this;
}

Vector2D Vector2D::operator/=(const float scalar)
{
	mX /= scalar;
	mY /= scalar;
	return *this;
}