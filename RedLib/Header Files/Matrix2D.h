#pragma once
#include "Trackable.h"
#include <ostream>
#include "Vector2D.h"

class Matrix2D : public Trackable
{

public:
	Matrix2D();
	Matrix2D(float a, float b, float c, float d);
	Matrix2D(int a, int b, int c, int d);
	Matrix2D(double a, double b, double c, double d);
	Matrix2D(unsigned int a, unsigned int b, unsigned int c, unsigned int d);
	Matrix2D(Vector2D row1, Vector2D row2);
	~Matrix2D();

	Matrix2D operator=(const Matrix2D& other);

	Matrix2D operator+(const Matrix2D& other) const;
	Matrix2D operator-(const Matrix2D& other) const;
	Matrix2D operator*(const float scalar) const;
	Matrix2D operator/(const float scalar) const;
	Matrix2D operator*(const int scalar) const;
	Matrix2D operator/(const int scalar) const;
	Matrix2D operator*(const double scalar) const;
	Matrix2D operator/(const double scalar) const;

	Matrix2D operator*(const Matrix2D& other) const;

	Matrix2D operator+=(const Matrix2D& other);
	Matrix2D operator-=(const Matrix2D& other);
	Matrix2D operator*=(const float scalar);
	Matrix2D operator/=(const float scalar);

	bool operator==(const Matrix2D& other) const;
	bool operator!=(const Matrix2D& other) const;

	Vector2D operator[](int) const;

	std::ostream& write(std::ostream& out) const;

	Vector2D getRow(int index) const;
	Vector2D getColumn(int index) const;

	static const Matrix2D Zero() { return Matrix2D(0, 0, 0, 0); }
	static const Matrix2D Identity() { return Matrix2D(1, 0, 0, 1); }

private:
	Vector2D firstRow, secondRow;

};

//global operator overloads (to get better implementation with ostream)
std::ostream& operator<<(std::ostream& out, Matrix2D const& vec);