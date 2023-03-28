#include "Vector4D.h"
#include <math.h>
#include <assert.h>
#include "Matrix4D.h"
#include <string>

using namespace std;

Vector4D::Vector4D()
{
	mX = 0.0f;
	mY = 0.0f;
	mZ = 0.0f;
	mW = 0.0f;
}

Vector4D::~Vector4D()
{

}

Vector4D::Vector4D(float x, float y, float z, float w)
{
	mX = x;
	mY = y;
	mZ = z;
	mW = w;
}

Vector4D::Vector4D(int x, int y, int z, int w)
{
	mX = (float)x;
	mY = (float)y;
	mZ = (float)z;
	mW = (float)w;
}

Vector4D::Vector4D(double x, double y, double z, double w) //NOTE: loss of precision, used to remove ambiguity
{
	mX = (float)x;
	mY = (float)y;
	mZ = (float)z;
	mW = (float)w;
}

Vector4D::Vector4D(unsigned int x, unsigned int y, unsigned int z, unsigned int w)
{
	mX = (float)x;
	mY = (float)y;
	mZ = (float)z;
	mW = (float)w;
}

Vector4D Vector4D::operator=(const Vector4D& other)
{
	mX = other.mX;
	mY = other.mY;
	mZ = other.mZ;
	mW = other.mW;
	return *this;
}

Vector4D Vector4D::operator+(const Vector4D& other) const
{
	return Vector4D(mX + other.mX, mY + other.mY, mZ + other.mZ, mW + other.mW);
}

Vector4D Vector4D::operator-(const Vector4D& other) const
{
	return Vector4D(mX - other.mX, mY - other.mY, mZ - other.mZ, mW - other.mW);
}

Vector4D Vector4D::operator*(const float scalar) const
{
	return Vector4D(scalar * mX, scalar * mY, scalar * mZ, scalar * mW);
}

Vector4D Vector4D::operator/(const float scalar) const
{
	return Vector4D(mX / scalar, mY / scalar, mZ / scalar, mW / scalar);
}

Vector4D Vector4D::operator*(const int scalar) const
{
	return Vector4D(scalar * mX, scalar * mY, scalar * mZ, scalar * mW);
}

Vector4D Vector4D::operator/(const int scalar) const
{
	return Vector4D(mX / scalar, mY / scalar, mZ / scalar, mW / scalar);
}

Vector4D Vector4D::operator*(const double scalar) const
{
	return Vector4D(scalar * mX, scalar * mY, scalar * mZ, scalar * mW);
}

Vector4D Vector4D::operator/(const double scalar) const
{
	return Vector4D(mX / scalar, mY / scalar, mZ / scalar, mW / scalar);
}

Vector4D Vector4D::operator+=(const Vector4D& other)
{
	mX += other.mX;
	mY += other.mY;
	mZ += other.mZ;
	mW += other.mW;
	return *this;
}

Vector4D Vector4D::operator-=(const Vector4D& other)
{
	mX -= other.mX;
	mY -= other.mY;
	mZ -= other.mZ;
	mW -= other.mW;
	return *this;
}

Vector4D Vector4D::operator*=(const float scalar)
{
	mX *= scalar;
	mY *= scalar;
	mZ *= scalar;
	mW *= scalar;
	return *this;
}

Vector4D Vector4D::operator/=(const float scalar)
{
	mX /= scalar;
	mY /= scalar;
	mZ /= scalar;
	mW /= scalar;
	return *this;
}

float Vector4D::length() const
{
	if(!mX && !mY && !mZ && !mW)
		return 0.0f;

	float x2 = mX * mX;
	float y2 = mY * mY;
	float z2 = mZ * mZ;
	float w2 = mW * mW;
	return sqrt(x2 + y2 + z2 + w2);
}

void Vector4D::normalize()
{
	float len = length();

	if(len == 0.0f || len == 1.0f)
		return;

	mX /= len;
	mY /= len;
	mZ /= len;
}

Vector4D Vector4D::normalized() const
{
	float len = length();

	if(len == 0.0f)
		return Zero();
	else if(len == 1.0f)
		return *this;

	return Vector4D(mX / len, mY / len, mZ / len, mW / len);
}

ostream& Vector4D::write(ostream& out) const
{
	out << toString();
	
	return out;
}

string Vector4D::toString() const
{
	return "(" + to_string(mX) + ", " + to_string(mY) + ", " + to_string(mZ) + + ", " + to_string(mW) + ")";
}

std::ostream& operator<<(std::ostream& out, Vector4D const &vec)
{
	vec.write(out);
	return out;
}

bool Vector4D::operator==(const Vector4D& other) const
{
	return (mX == other.getX() && mY == other.getY() && mZ == other.getZ() && mW == other.getW());
}

bool Vector4D::operator!=(const Vector4D& other) const
{
	return !(mX == other.getX() && mY == other.getY() && mZ == other.getZ() && mW == other.getW());
}

float Vector4D::operator[](int index) const
{
	switch (index)
	{
	case 0:
		return mX;
		break;
	case 1:
		return mY;
		break;
	case 2:
		return mZ;
		break;
	case 3:
		return mW;
		break;
	default:
		assert(false);
		return -1.0f;
		break;
	}
}

float Vector4D::Dot(const Vector4D a, const Vector4D b)
{
	return a[0] * b[0] + a[1] * b[1] + a[2] * b[2] + a[3] * b[3];
}

float Vector4D::operator*(const Vector4D& other) const
{
	return Dot(*this, other);
}

Vector4D Vector4D::operator*(const Matrix4D& other) const
{
	return Vector4D(Dot(*this, other.getColumn(0)), Dot(*this, other.getColumn(1)), Dot(*this, other.getColumn(2)), Dot(*this, other.getColumn(3)));
}