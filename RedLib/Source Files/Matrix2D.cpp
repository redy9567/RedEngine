#include "Matrix2D.h"
#include <assert.h>

Matrix2D::Matrix2D()
{
	mFirstRow = Vector2D::Zero();
	mSecondRow = Vector2D::Zero();
};

Matrix2D::Matrix2D(float a, float b, float c, float d)
{
	mFirstRow = Vector2D(a, b);
	mSecondRow = Vector2D(c, d);
}

Matrix2D::Matrix2D(int a, int b, int c, int d)
{
	mFirstRow = Vector2D(a, b);
	mSecondRow = Vector2D(c, d);
}

Matrix2D::Matrix2D(double a, double b, double c, double d)
{
	mFirstRow = Vector2D(a, b);
	mSecondRow = Vector2D(c, d);
}

Matrix2D::Matrix2D(unsigned int a, unsigned int b, unsigned int c, unsigned int d)
{
	mFirstRow = Vector2D(a, b);
	mSecondRow = Vector2D(c, d);
}

Matrix2D::Matrix2D(Vector2D row1, Vector2D row2)
{
	mFirstRow = row1;
	mSecondRow = row2;
}

Matrix2D::~Matrix2D()
{

}

Matrix2D Matrix2D::operator=(const Matrix2D& other)
{
	mFirstRow = other.mFirstRow;
	mSecondRow = other.mSecondRow;
	return *this;
}

Matrix2D Matrix2D::operator+(const Matrix2D& other) const
{
	return Matrix2D(mFirstRow + other.mFirstRow, mSecondRow + other.mSecondRow);
}

Matrix2D Matrix2D::operator-(const Matrix2D& other) const
{
	return Matrix2D(mFirstRow - other.mFirstRow, mSecondRow - other.mSecondRow);
}

Matrix2D Matrix2D::operator*(const float scalar) const
{
	return Matrix2D(mFirstRow * scalar, mSecondRow * scalar);
}

Matrix2D Matrix2D::operator/(const float scalar) const
{
	return Matrix2D(mFirstRow / scalar, mSecondRow / scalar);
}

Matrix2D Matrix2D::operator*(const int scalar) const
{
	return Matrix2D(mFirstRow * scalar, mSecondRow * scalar);
}

Matrix2D Matrix2D::operator/(const int scalar) const
{
	return Matrix2D(mFirstRow / scalar, mSecondRow / scalar);
}

Matrix2D Matrix2D::operator*(const double scalar) const
{
	return Matrix2D(mFirstRow * scalar, mSecondRow * scalar);
}

Matrix2D Matrix2D::operator/(const double scalar) const
{
	return Matrix2D(mFirstRow / scalar, mSecondRow / scalar);
}

Matrix2D Matrix2D::operator*(const Matrix2D& other) const
{
	return Matrix2D(
		Vector2D(mFirstRow * other.getColumn(0), mFirstRow * other.getColumn(1)),
		Vector2D(mSecondRow * other.getColumn(0), mSecondRow * other.getColumn(1))
	);
}

Matrix2D Matrix2D::operator+=(const Matrix2D& other)
{
	mFirstRow += other.mFirstRow;
	mSecondRow += other.mSecondRow;

	return *this;
}

Matrix2D Matrix2D::operator-=(const Matrix2D& other)
{
	mFirstRow -= other.mFirstRow;
	mSecondRow -= other.mSecondRow;

	return *this;
}

Matrix2D Matrix2D::operator*=(const float scalar)
{
	mFirstRow *= scalar;
	mSecondRow *= scalar;
	return *this;
}

Matrix2D Matrix2D::operator/=(const float scalar)
{
	mFirstRow /= scalar;
	mSecondRow /= scalar;
	return *this;
}

bool Matrix2D::operator==(const Matrix2D& other) const
{
	return mFirstRow == other.mFirstRow && mSecondRow == other.mSecondRow;
}

bool Matrix2D::operator!=(const Matrix2D& other) const
{
	return !(mFirstRow == other.mFirstRow && mSecondRow == other.mSecondRow);
}

Vector2D Matrix2D::operator[](int index) const
{
	return getRow(index);
}

std::ostream& Matrix2D::write(std::ostream& out) const
{
	out << mFirstRow << std::endl << mSecondRow << std::endl;

	return out;
}

Vector2D Matrix2D::getRow(int index) const
{
	switch (index)
	{
	case 0:
		return mFirstRow;
		break;
	case 1:
		return mSecondRow;
		break;
	default:
		assert(false);
		return Vector2D::Zero();
		break;
	}
}

Vector2D Matrix2D::getColumn(int index) const
{
	return Vector2D(mFirstRow[index], mSecondRow[index]);
}

std::ostream& operator<<(std::ostream& out, Matrix2D const& mat)
{
	mat.write(out);
	return out;
}