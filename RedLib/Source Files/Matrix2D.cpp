#include "Matrix2D.h"
#include <assert.h>

Matrix2D::Matrix2D()
{
	firstRow = Vector2D::Zero();
	secondRow = Vector2D::Zero();
};

Matrix2D::Matrix2D(float a, float b, float c, float d)
{
	firstRow = Vector2D(a, b);
	secondRow = Vector2D(c, d);
}

Matrix2D::Matrix2D(int a, int b, int c, int d)
{
	firstRow = Vector2D(a, b);
	secondRow = Vector2D(c, d);
}

Matrix2D::Matrix2D(double a, double b, double c, double d)
{
	firstRow = Vector2D(a, b);
	secondRow = Vector2D(c, d);
}

Matrix2D::Matrix2D(unsigned int a, unsigned int b, unsigned int c, unsigned int d)
{
	firstRow = Vector2D(a, b);
	secondRow = Vector2D(c, d);
}

Matrix2D::Matrix2D(Vector2D row1, Vector2D row2)
{
	firstRow = row1;
	secondRow = row2;
}

Matrix2D::~Matrix2D()
{

}

Matrix2D Matrix2D::operator=(const Matrix2D& other)
{
	firstRow = other.firstRow;
	secondRow = other.secondRow;
	return *this;
}

Matrix2D Matrix2D::operator+(const Matrix2D& other) const
{
	return Matrix2D(firstRow + other.firstRow, secondRow + other.secondRow);
}

Matrix2D Matrix2D::operator-(const Matrix2D& other) const
{
	return Matrix2D(firstRow - other.firstRow, secondRow - other.secondRow);
}

Matrix2D Matrix2D::operator*(const float scalar) const
{
	return Matrix2D(firstRow * scalar, secondRow * scalar);
}

Matrix2D Matrix2D::operator/(const float scalar) const
{
	return Matrix2D(firstRow / scalar, secondRow / scalar);
}

Matrix2D Matrix2D::operator*(const int scalar) const
{
	return Matrix2D(firstRow * scalar, secondRow * scalar);
}

Matrix2D Matrix2D::operator/(const int scalar) const
{
	return Matrix2D(firstRow / scalar, secondRow / scalar);
}

Matrix2D Matrix2D::operator*(const double scalar) const
{
	return Matrix2D(firstRow * scalar, secondRow * scalar);
}

Matrix2D Matrix2D::operator/(const double scalar) const
{
	return Matrix2D(firstRow / scalar, secondRow / scalar);
}

Matrix2D Matrix2D::operator*(const Matrix2D& other) const
{
	return Matrix2D(
		Vector2D(firstRow * other.getColumn(0), firstRow * other.getColumn(1)),
		Vector2D(secondRow * other.getColumn(0), secondRow * other.getColumn(1))
	);
}

Matrix2D Matrix2D::operator+=(const Matrix2D& other)
{
	firstRow += other.firstRow;
	secondRow += other.secondRow;

	return *this;
}

Matrix2D Matrix2D::operator-=(const Matrix2D& other)
{
	firstRow -= other.firstRow;
	secondRow -= other.secondRow;

	return *this;
}

Matrix2D Matrix2D::operator*=(const float scalar)
{
	firstRow *= scalar;
	secondRow *= scalar;
	return *this;
}

Matrix2D Matrix2D::operator/=(const float scalar)
{
	firstRow /= scalar;
	secondRow /= scalar;
	return *this;
}

bool Matrix2D::operator==(const Matrix2D& other) const
{
	return firstRow == other.firstRow && secondRow == other.secondRow;
}

bool Matrix2D::operator!=(const Matrix2D& other) const
{
	return !(firstRow == other.firstRow && secondRow == other.secondRow);
}

Vector2D Matrix2D::operator[](int index) const
{
	return getRow(index);
}

std::ostream& Matrix2D::write(std::ostream& out) const
{
	out << firstRow << std::endl << secondRow << std::endl;

	return out;
}

Vector2D Matrix2D::getRow(int index) const
{
	switch (index)
	{
	case 0:
		return firstRow;
		break;
	case 1:
		return secondRow;
		break;
	default:
		assert(false);
		return Vector2D::Zero();
		break;
	}
}

Vector2D Matrix2D::getColumn(int index) const
{
	return Vector2D(firstRow[index], secondRow[index]);
}

std::ostream& operator<<(std::ostream& out, Matrix2D const& mat)
{
	mat.write(out);
	return out;
}