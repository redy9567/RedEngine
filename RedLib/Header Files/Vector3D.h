#pragma once
#include "Trackable.h"
#include <ostream>

class Matrix3D;

class Vector3D : public Trackable
{

public:
	Vector3D();
	Vector3D(float x, float y, float z);
	Vector3D(int x, int y, int z);
	Vector3D(double x, double y, double z);
	Vector3D(unsigned int x, unsigned int y, unsigned int z);
	Vector3D(const Vector3D& other);
	~Vector3D();

	Vector3D operator=(const Vector3D& other);

	Vector3D operator+(const Vector3D& other) const;
	Vector3D operator-(const Vector3D& other) const;
	Vector3D operator*(const float scalar) const;
	Vector3D operator/(const float scalar) const;
	Vector3D operator*(const int scalar) const;
	Vector3D operator/(const int scalar) const;
	Vector3D operator*(const double scalar) const;
	Vector3D operator/(const double scalar) const;

	float operator*(const Vector3D& other) const;
	Vector3D operator*(const Matrix3D& other) const;

	Vector3D operator+=(const Vector3D& other);
	Vector3D operator-=(const Vector3D& other);
	Vector3D operator*=(const float scalar);
	Vector3D operator/=(const float scalar);

	bool operator==(const Vector3D& other) const;
	bool operator!=(const Vector3D& other) const;

	float operator[](int) const;

	std::ostream& write(std::ostream& out) const;
	std::string toString() const;

	float length() const;
	void normalize();

	Vector3D normalized() const;

	float getX() const { return mX; }
	float getY() const { return mY; }
	float getZ() const { return mZ; }

	void setX(float x) { mX = x; }
	void setX(int x) { mX = (float)x; }
	void setX(double x) { mX = (float)x; }

	void setY(float y) { mY = y; }
	void setY(int y) { mY = (float)y; }
	void setY(double y) { mY = (float)y; }

	void setZ(float z) { mZ = z; }
	void setZ(int z) { mZ = (float)z; }
	void setZ(double z) { mZ = (float)z; }

	static const Vector3D Zero() { return Vector3D(0, 0, 0); }
	static const Vector3D One() { return Vector3D(1, 1, 1); }
	static const Vector3D Left() { return Vector3D(-1, 0, 0); }
	static const Vector3D Right() { return Vector3D(1, 0, 0); }
	static const Vector3D Up() { return Vector3D(0, 1, 0); }
	static const Vector3D Down() { return Vector3D(0, -1, 0); }
	static const Vector3D Forward() { return Vector3D(0, 0, 1); }
	static const Vector3D Backward() { return Vector3D(0, 0, -1); }

	static float Dot(const Vector3D a, const Vector3D b);
	static Vector3D Cross(const Vector3D a, const Vector3D b);

	static bool IsPointWithinBounds(Vector3D point, Vector3D lower, Vector3D upper);

	float getMostSignificantComponent();

private:
	float mX, mY, mZ;
	
};

//global operator overloads (to get better implementation with ostream)
std::ostream& operator<<(std::ostream& out, Vector3D const &vec);
