#include "Matrix3D.h"
#include <assert.h>

Matrix3D::Matrix3D()
{
	firstRow = Vector3D::Zero();
	secondRow = Vector3D::Zero();
	thirdRow = Vector3D::Zero();
};

Matrix3D::Matrix3D(float a, float b, float c, float d, float e, float f, float g, float h, float i)
{
	firstRow = Vector3D(a, b, c);
	secondRow = Vector3D(d, e, f);
	thirdRow = Vector3D(g, h, i);
}

Matrix3D::Matrix3D(int a, int b, int c, int d, int e, int f, int g, int h, int i)
{
	firstRow = Vector3D(a, b, c);
	secondRow = Vector3D(d, e, f);
	thirdRow = Vector3D(g, h, i);
}

Matrix3D::Matrix3D(double a, double b, double c, double d, double e, double f, double g, double h, double i)
{
	firstRow = Vector3D(a, b, c);
	secondRow = Vector3D(d, e, f);
	thirdRow = Vector3D(g, h, i);
}

Matrix3D::Matrix3D(unsigned int a, unsigned int b, unsigned int c, unsigned int d, unsigned int e, unsigned int f, unsigned int g, unsigned int h, unsigned int i)
{
	firstRow = Vector3D(a, b, c);
	secondRow = Vector3D(d, e, f);
	thirdRow = Vector3D(g, h, i);
}

Matrix3D::Matrix3D(Vector3D row1, Vector3D row2, Vector3D row3)
{
	firstRow = row1;
	secondRow = row2;
	thirdRow = row3;
}

Matrix3D::~Matrix3D()
{

}

Matrix3D Matrix3D::operator=(const Matrix3D& other)
{
	firstRow = other.firstRow;
	secondRow = other.secondRow;
	thirdRow = other.thirdRow;
	return *this;
}

Matrix3D Matrix3D::operator+(const Matrix3D& other) const
{
	return Matrix3D(firstRow + other.firstRow, secondRow + other.secondRow, thirdRow + other.thirdRow);
}

Matrix3D Matrix3D::operator-(const Matrix3D& other) const
{
	return Matrix3D(firstRow - other.firstRow, secondRow - other.secondRow, thirdRow - other.thirdRow);
}

Matrix3D Matrix3D::operator*(const float scalar) const
{
	return Matrix3D(firstRow * scalar, secondRow * scalar, thirdRow * scalar);
}

Matrix3D Matrix3D::operator/(const float scalar) const
{
	return Matrix3D(firstRow / scalar, secondRow / scalar, thirdRow / scalar);
}

Matrix3D Matrix3D::operator*(const int scalar) const
{
	return Matrix3D(firstRow * scalar, secondRow * scalar, thirdRow * scalar);
}

Matrix3D Matrix3D::operator/(const int scalar) const
{
	return Matrix3D(firstRow / scalar, secondRow / scalar, thirdRow / scalar);
}

Matrix3D Matrix3D::operator*(const double scalar) const
{
	return Matrix3D(firstRow * scalar, secondRow * scalar, thirdRow * scalar);
}

Matrix3D Matrix3D::operator/(const double scalar) const
{
	return Matrix3D(firstRow / scalar, secondRow / scalar, thirdRow / scalar);
}

Matrix3D Matrix3D::operator*(const Matrix3D& other) const
{
	return Matrix3D(
		Vector3D(firstRow * other.getColumn(0), firstRow * other.getColumn(1), firstRow * other.getColumn(2)),
		Vector3D(secondRow * other.getColumn(0), secondRow * other.getColumn(1), secondRow * other.getColumn(2)),
		Vector3D(thirdRow * other.getColumn(0), thirdRow * other.getColumn(1), thirdRow * other.getColumn(2))
	);
}

Matrix3D Matrix3D::operator+=(const Matrix3D& other)
{
	firstRow += other.firstRow;
	secondRow += other.secondRow;
	thirdRow += other.thirdRow;

	return *this;
}

Matrix3D Matrix3D::operator-=(const Matrix3D& other)
{
	firstRow -= other.firstRow;
	secondRow -= other.secondRow;
	thirdRow -= other.thirdRow;

	return *this;
}

Matrix3D Matrix3D::operator*=(const float scalar)
{
	firstRow *= scalar;
	secondRow *= scalar;
	thirdRow *= scalar;
	return *this;
}

Matrix3D Matrix3D::operator/=(const float scalar)
{
	firstRow /= scalar;
	secondRow /= scalar;
	thirdRow /= scalar;
	return *this;
}

bool Matrix3D::operator==(const Matrix3D& other) const
{
	return firstRow == other.firstRow && secondRow == other.secondRow && thirdRow == other.thirdRow;
}

bool Matrix3D::operator!=(const Matrix3D& other) const
{
	return !(firstRow == other.firstRow && secondRow == other.secondRow && thirdRow == other.thirdRow);
}

Vector3D Matrix3D::operator[](int index) const
{
	return getRow(index);
}

std::ostream& Matrix3D::write(std::ostream& out) const
{
	out << firstRow << std::endl << secondRow << std::endl << thirdRow << std::endl;

	return out;
}

Vector3D Matrix3D::getRow(int index) const
{
	switch (index)
	{
	case 0:
		return firstRow;
		break;
	case 1:
		return secondRow;
		break;
	case 2:
		return thirdRow;
		break;
	default:
		assert(false);
		return Vector3D::Zero();
		break;
	}
}

Vector3D Matrix3D::getColumn(int index) const
{
	return Vector3D(firstRow[index], secondRow[index], thirdRow[index]);
}

std::ostream& operator<<(std::ostream& out, Matrix3D const& mat)
{
	mat.write(out);
	return out;
}