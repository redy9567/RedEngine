#include "Vector3D.h"
#include <math.h>
#include <assert.h>
#include "Matrix3D.h"
#include <string>

using namespace std;

Vector3D::Vector3D()
{
	mX = 0.0f;
	mY = 0.0f;
	mZ = 0.0f;
}

Vector3D::~Vector3D()
{

}

Vector3D::Vector3D(float x, float y, float z)
{
	mX = x;
	mY = y;
	mZ = z;
}

Vector3D::Vector3D(int x, int y, int z)
{
	mX = (float)x;
	mY = (float)y;
	mZ = (float)z;
}

Vector3D::Vector3D(double x, double y, double z) //NOTE: loss of precision, used to remove ambiguity
{
	mX = (float)x;
	mY = (float)y;
	mZ = (float)z;
}

Vector3D::Vector3D(unsigned int x, unsigned int y, unsigned int z)
{
	mX = (float)x;
	mY = (float)y;
	mZ = (float)z;
}

Vector3D::Vector3D(const Vector3D& other)
{
	mX = other.mX;
	mY = other.mY;
	mZ = other.mZ;
}

Vector3D Vector3D::operator=(const Vector3D& other)
{
	mX = other.mX;
	mY = other.mY;
	mZ = other.mZ;
	return *this;
}

Vector3D Vector3D::operator+(const Vector3D& other) const
{
	return Vector3D(mX + other.mX, mY + other.mY, mZ + other.mZ);
}

Vector3D Vector3D::operator-(const Vector3D& other) const
{
	return Vector3D(mX - other.mX, mY - other.mY, mZ - other.mZ);
}

Vector3D Vector3D::operator*(const float scalar) const
{
	return Vector3D(scalar * mX, scalar * mY, scalar * mZ);
}

Vector3D Vector3D::operator/(const float scalar) const
{
	return Vector3D(mX / scalar, mY / scalar, mZ / scalar);
}

Vector3D Vector3D::operator*(const int scalar) const
{
	return Vector3D(scalar * mX, scalar * mY, scalar * mZ);
}

Vector3D Vector3D::operator/(const int scalar) const
{
	return Vector3D(mX / scalar, mY / scalar, mZ / scalar);
}

Vector3D Vector3D::operator*(const double scalar) const
{
	return Vector3D(scalar * mX, scalar * mY, scalar * mZ);
}

Vector3D Vector3D::operator/(const double scalar) const
{
	return Vector3D(mX / scalar, mY / scalar, mZ / scalar);
}

Vector3D Vector3D::operator+=(const Vector3D& other)
{
	mX += other.mX;
	mY += other.mY;
	mZ += other.mZ;
	return *this;
}

Vector3D Vector3D::operator-=(const Vector3D& other)
{
	mX -= other.mX;
	mY -= other.mY;
	mZ -= other.mZ;
	return *this;
}

Vector3D Vector3D::operator*=(const float scalar)
{
	mX *= scalar;
	mY *= scalar;
	mZ *= scalar;
	return *this;
}

Vector3D Vector3D::operator/=(const float scalar)
{
	mX /= scalar;
	mY /= scalar;
	mZ /= scalar;
	return *this;
}

float Vector3D::length() const
{
	if(!mX && !mY && !mZ)
		return 0.0f;

	float x2 = mX * mX;
	float y2 = mY * mY;
	float z2 = mZ * mZ;
	return sqrt(x2 + y2 + z2);
}

void Vector3D::normalize()
{
	float len = length();

	if(len == 0.0f || len == 1.0f)
		return;

	mX /= len;
	mY /= len;
	mZ /= len;
}

Vector3D Vector3D::normalized() const
{
	float len = length();

	if(len == 0.0f)
		return Zero();
	else if(len == 1.0f)
		return *this;

	return Vector3D(mX / len, mY / len, mZ / len);
}

ostream& Vector3D::write(ostream& out) const
{
	out << toString();
	
	return out;
}

string Vector3D::toString() const
{
	return "(" + to_string(mX) + ", " + to_string(mY) + ", " + to_string(mZ) + ")";
}

std::ostream& operator<<(std::ostream& out, Vector3D const &vec)
{
	vec.write(out);
	return out;
}

bool Vector3D::operator==(const Vector3D& other) const
{
	return (mX == other.getX() && mY == other.getY() && mZ == other.getZ());
}

bool Vector3D::operator!=(const Vector3D& other) const
{
	return !(mX == other.getX() && mY == other.getY() && mZ == other.getZ());
}

float Vector3D::operator[](int index) const
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
	default:
		assert(false);
		return -1.0f;
		break;
	}
}

float Vector3D::Dot(const Vector3D a, const Vector3D b)
{
	return a[0] * b[0] + a[1] * b[1] + a[2] * b[2];
}

float Vector3D::operator*(const Vector3D& other) const
{
	return Dot(*this, other);
}

Vector3D Vector3D::Cross(const Vector3D a, const Vector3D b)
{
	return Vector3D(
		a.mY * b.mZ - a.mZ * b.mY,
		a.mZ * b.mX - a.mX * b.mZ,
		a.mX * b.mY - a.mY * b.mX
	);
}

Vector3D Vector3D::operator*(const Matrix3D& other) const
{
	return Vector3D(Dot(*this, other.getColumn(0)), Dot(*this, other.getColumn(1)), Dot(*this, other.getColumn(2)));
}

bool Vector3D::IsPointWithinBounds(Vector3D point, Vector3D lower, Vector3D upper)
{
	return	point.getX() > lower.getX() &&
		point.getY() > lower.getY() &&
		point.getZ() > lower.getZ() &&
		point.getX() < upper.getX() &&
		point.getY() < upper.getY() &&
		point.getZ() < upper.getZ();
}

float Vector3D::getMostSignificantComponent()
{
	float absX = abs(getX());
	float absY = abs(getY());
	float absZ = abs(getZ());

	if (absX > absY && absX > absZ)
		return getX();
	else if (absY > absX && absY > absZ)
		return getY();
	else if (absZ > absX && absZ > absY)
		return getZ();

	if (absY == absZ && absY > absX)
		return getY();
	else
		return getX();
}