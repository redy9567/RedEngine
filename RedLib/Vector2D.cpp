#include "Vector2D.h"
#include <math.h>

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

Vector2D::Vector2D(double x, double y) //NOTE: loss of precision, used to remove ambiguity
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

Vector2D Vector2D::operator*(const float scalar) const
{
	return Vector2D(scalar * mX, scalar * mY);
}

Vector2D Vector2D::operator/(const float scalar) const
{
	return Vector2D(mX / scalar, mY / scalar);
}

Vector2D Vector2D::operator*(const int scalar) const
{
	return Vector2D(scalar * mX, scalar * mY);
}

Vector2D Vector2D::operator/(const int scalar) const
{
	return Vector2D(mX / scalar, mY / scalar);
}

Vector2D Vector2D::operator*(const double scalar) const
{
	return Vector2D(scalar * mX, scalar * mY);
}

Vector2D Vector2D::operator/(const double scalar) const
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

float Vector2D::length()
{
	if(mX + mY == 0.0f)
		return 0.0f;

	float x2 = mX * mX;
	float y2 = mY * mY;
	return sqrt(x2 + y2);
}

void Vector2D::normalize()
{
	float len = length();

	if(len == 0.0f)
		return;

	mX /= len;
	mY /= len;
}

