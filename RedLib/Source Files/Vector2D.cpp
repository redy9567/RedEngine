#include "Vector2D.h"
#include <math.h>
#include <assert.h>
#include <Matrix2D.h>
#include <string>

using namespace std;

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

Vector2D::Vector2D(unsigned int x, unsigned int y)
{
	mX = (float)x;
	mY = (float)y;
}

Vector2D::Vector2D(float xy)
{
	mX = xy;
	mY = xy;
}

Vector2D::Vector2D(int xy)
{
	mX = (float)xy;
	mY = (float)xy;
}

Vector2D::Vector2D(double xy) //NOTE: loss of precision, used to remove ambiguity
{
	mX = (float)xy;
	mY = (float)xy;
}

Vector2D::Vector2D(unsigned int xy)
{
	mX = (float)xy;
	mY = (float)xy;
}

Vector2D Vector2D::operator=(const Vector2D& other)
{
	mX = other.mX;
	mY = other.mY;
	return *this;
}

Vector2D Vector2D::operator+(const Vector2D& other) const
{
	return Vector2D(mX + other.mX, mY + other.mY);
}

Vector2D Vector2D::operator-(const Vector2D& other) const
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

float Vector2D::length() const
{
	if(!mX && !mY)
		return 0.0f;

	float x2 = mX * mX;
	float y2 = mY * mY;
	return sqrt(x2 + y2);
}

void Vector2D::normalize()
{
	float len = length();

	if(len == 0.0f || len == 1.0f)
		return;

	mX /= len;
	mY /= len;
}

Vector2D Vector2D::normalized() const
{
	float len = length();

	if(len == 0.0f)
		return Zero();
	else if(len == 1.0f)
		return *this;

	return Vector2D(mX / len, mY / len);
}

ostream& Vector2D::write(ostream& out) const
{
	out << toString();
	
	return out;
}

string Vector2D::toString() const
{
	return "(" + to_string(mX) + ", " + to_string(mY) + ")";
}

std::ostream& operator<<(std::ostream& out, Vector2D const &vec)
{
	vec.write(out);
	return out;
}

bool Vector2D::operator==(const Vector2D& other) const
{
	return (mX == other.getX() && mY == other.getY());
}

bool Vector2D::operator!=(const Vector2D& other) const
{
	return !(mX == other.getX() && mY == other.getY());
}

float Vector2D::operator[](int index) const
{
	switch (index)
	{
	case 0:
		return mX;
		break;
	case 1:
		return mY;
		break;
	default:
		assert(false);
		return -1.0f;
		break;
	}
}

float Vector2D::Dot(const Vector2D a, const Vector2D b)
{
	return a[0] * b[0] + a[1] * b[1];
}

float Vector2D::operator*(const Vector2D& other) const
{
	return Dot(*this, other);
}

Vector2D Vector2D::operator*(const Matrix2D& other) const
{
	return Vector2D(Dot(*this, other.getColumn(0)), Dot(*this, other.getColumn(1)));
}

bool Vector2D::IsPointWithinBounds(Vector2D point, Vector2D lower, Vector2D upper)
{
	return point.getX() > lower.getX() &&
		point.getY() > lower.getY() &&
		point.getX() < upper.getX() &&
		point.getY() < upper.getY();
}

Vector2D Vector2D::Midpoint(const Vector2D a, const Vector2D b)
{
	return (a + b) / 2;
}

Vector2D Vector2D::axisDivide(const Vector2D& other) const
{
	return Vector2D(mX / other.mX, mY / other.mY);
}