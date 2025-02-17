#pragma once
#include "Trackable.h"
#include <ostream>
#include "Vector4D.h"

// Represents a 4x4 matrix that is stored and accessed as Row-Major
class Matrix4D : public Trackable
{

public:
	Matrix4D();
	Matrix4D(Vector4D row1, Vector4D row2, Vector4D row3, Vector4D row4);
	~Matrix4D();

	Matrix4D operator=(const Matrix4D& other);

	Matrix4D operator+(const Matrix4D& other) const;
	Matrix4D operator-(const Matrix4D& other) const;
	Matrix4D operator*(const float scalar) const;
	Matrix4D operator/(const float scalar) const;
	Matrix4D operator*(const int scalar) const;
	Matrix4D operator/(const int scalar) const;
	Matrix4D operator*(const double scalar) const;
	Matrix4D operator/(const double scalar) const;

	Matrix4D operator*(const Matrix4D& other) const;

	Matrix4D operator+=(const Matrix4D& other);
	Matrix4D operator-=(const Matrix4D& other);
	Matrix4D operator*=(const float scalar);
	Matrix4D operator/=(const float scalar);

	bool operator==(const Matrix4D& other) const;
	bool operator!=(const Matrix4D& other) const;

	Vector4D operator[](int) const;

	std::ostream& write(std::ostream& out) const;

	Vector4D getRow(int index) const;
	Vector4D getColumn(int index) const;

	static const Matrix4D Zero() {
		return Matrix4D(
			Vector4D::Zero(),
			Vector4D::Zero(),
			Vector4D::Zero(),
			Vector4D::Zero());
	}

	static const Matrix4D Identity() { 
		return Matrix4D(
			Vector4D(1, 0, 0, 0),
			Vector4D(0, 1, 0, 0),
			Vector4D(0, 0, 1, 0),
			Vector4D(0, 0, 0, 1)
		);
	}

	float* convertToColumnMajorFloatArray();

private:
	void cleanupColumnMajorFloatArray();

	Vector4D mFirstRow, mSecondRow, mThirdRow, mFourthRow;

	float* mColumnMajorFloatArray;

};

//global operator overloads (to get better implementation with ostream)
std::ostream& operator<<(std::ostream& out, Matrix4D const& vec);