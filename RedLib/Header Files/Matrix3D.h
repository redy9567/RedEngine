#pragma once
#include "Trackable.h"
#include <ostream>
#include "Vector3D.h"

// Represents a 3x3 matrix that is stored and accessed as Row-Major
class Matrix3D : public Trackable
{

public:
	Matrix3D();
	Matrix3D(	float a, float b, float c, 
				float d, float e, float f,
				float g, float h, float i);

	Matrix3D(	int a, int b, int c, 
				int d, int e, int f,
				int g, int h, int i);

	Matrix3D(	double a, double b, double c,
				double d, double e, double f,
				double g, double h, double i);

	Matrix3D(	unsigned int a, unsigned int b, unsigned int c,
				unsigned int d, unsigned int e, unsigned int f,
				unsigned int g, unsigned int h, unsigned int i);

	Matrix3D(Vector3D row1, Vector3D row2, Vector3D row3);
	~Matrix3D();

	Matrix3D operator=(const Matrix3D& other);

	Matrix3D operator+(const Matrix3D& other) const;
	Matrix3D operator-(const Matrix3D& other) const;
	Matrix3D operator*(const float scalar) const;
	Matrix3D operator/(const float scalar) const;
	Matrix3D operator*(const int scalar) const;
	Matrix3D operator/(const int scalar) const;
	Matrix3D operator*(const double scalar) const;
	Matrix3D operator/(const double scalar) const;

	Matrix3D operator*(const Matrix3D& other) const;

	Matrix3D operator+=(const Matrix3D& other);
	Matrix3D operator-=(const Matrix3D& other);
	Matrix3D operator*=(const float scalar);
	Matrix3D operator/=(const float scalar);

	bool operator==(const Matrix3D& other) const;
	bool operator!=(const Matrix3D& other) const;

	Vector3D operator[](int) const;

	std::ostream& write(std::ostream& out) const;

	Vector3D getRow(int index) const;
	Vector3D getColumn(int index) const;

	static const Matrix3D Zero() { return Matrix3D(	0, 0, 0, 
													0, 0, 0,
													0, 0, 0); }

	static const Matrix3D Identity() { return Matrix3D(	1, 0, 0,
														0, 1, 0,
														0, 0, 1); }

	float* convertToColumnMajorFloatArray();

private:
	void cleanupColumnMajorFloatArray();

	Vector3D mFirstRow, mSecondRow, mThirdRow;

	float* mColumnMajorFloatArray;

};

//global operator overloads (to get better implementation with ostream)
std::ostream& operator<<(std::ostream& out, Matrix3D const& vec);