#pragma once
#include "Trackable.h"
#include <ostream>

class Vector4D : public Trackable
{

public:
	Vector4D();
	Vector4D(float x, float y, float z, float w);
	Vector4D(int x, int y, int z, int w);
	Vector4D(double x, double y, double z, double w);
	Vector4D(unsigned int x, unsigned int y, unsigned int z, unsigned int w);
	~Vector4D();

	Vector4D operator=(const Vector4D& other);

	Vector4D operator+(const Vector4D& other) const;
	Vector4D operator-(const Vector4D& other) const;
	Vector4D operator*(const float scalar) const;
	Vector4D operator/(const float scalar) const;
	Vector4D operator*(const int scalar) const;
	Vector4D operator/(const int scalar) const;
	Vector4D operator*(const double scalar) const;
	Vector4D operator/(const double scalar) const;

	float operator*(const Vector4D& other) const;

	Vector4D operator+=(const Vector4D& other);
	Vector4D operator-=(const Vector4D& other);
	Vector4D operator*=(const float scalar);
	Vector4D operator/=(const float scalar);

	bool operator==(const Vector4D& other) const;
	bool operator!=(const Vector4D& other) const;

	float operator[](int) const;

	std::ostream& write(std::ostream& out) const;

	float length() const;
	void normalize();

	Vector4D normalized() const;

	float getX() const { return mX; }
	float getY() const { return mY; }
	float getZ() const { return mZ; }
	float getW() const { return mW; }

	static const Vector4D Zero() { return Vector4D(0, 0, 0, 0); }
	static const Vector4D One() { return Vector4D(1, 1, 1, 1); }
	static const Vector4D Left() { return Vector4D(-1, 0, 0, 1); }
	static const Vector4D Right() { return Vector4D(1, 0, 0, 1); }
	static const Vector4D Up() { return Vector4D(0, -1, 0, 1); }
	static const Vector4D Down() { return Vector4D(0, 1, 0, 1); }
	static const Vector4D Forward() { return Vector4D(0, 0, 1, 1); }
	static const Vector4D Backward() { return Vector4D(0, 0, -1, 1); }

	static float Dot(const Vector4D a, const Vector4D b);

private:
	float mX, mY, mZ, mW;
	
};

//global operator overloads (to get better implementation with ostream)
std::ostream& operator<<(std::ostream& out, Vector4D const &vec);
