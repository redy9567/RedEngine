#include "Matrix4D.h"
#include <assert.h>

Matrix4D::Matrix4D()
{
	firstRow = Vector4D::Zero();
	secondRow = Vector4D::Zero();
	thirdRow = Vector4D::Zero();
	fourthRow = Vector4D::Zero();
};

Matrix4D::Matrix4D(Vector4D row1, Vector4D row2, Vector4D row3, Vector4D row4)
{
	firstRow = row1;
	secondRow = row2;
	thirdRow = row3;
	fourthRow = row4;
}

Matrix4D::~Matrix4D()
{

}

Matrix4D Matrix4D::operator=(const Matrix4D& other)
{
	firstRow = other.firstRow;
	secondRow = other.secondRow;
	thirdRow = other.thirdRow;
	fourthRow = other.fourthRow;
	return *this;
}

Matrix4D Matrix4D::operator+(const Matrix4D& other) const
{
	return Matrix4D(firstRow + other.firstRow, secondRow + other.secondRow, thirdRow + other.thirdRow, fourthRow + other.fourthRow);
}

Matrix4D Matrix4D::operator-(const Matrix4D& other) const
{
	return Matrix4D(firstRow - other.firstRow, secondRow - other.secondRow, thirdRow - other.thirdRow, fourthRow - other.fourthRow);
}

Matrix4D Matrix4D::operator*(const float scalar) const
{
	return Matrix4D(firstRow * scalar, secondRow * scalar, thirdRow * scalar, fourthRow * scalar);
}

Matrix4D Matrix4D::operator/(const float scalar) const
{
	return Matrix4D(firstRow / scalar, secondRow / scalar, thirdRow / scalar, fourthRow / scalar);
}

Matrix4D Matrix4D::operator*(const int scalar) const
{
	return Matrix4D(firstRow * scalar, secondRow * scalar, thirdRow * scalar, fourthRow * scalar);
}

Matrix4D Matrix4D::operator/(const int scalar) const
{
	return Matrix4D(firstRow / scalar, secondRow / scalar, thirdRow / scalar, fourthRow / scalar);
}

Matrix4D Matrix4D::operator*(const double scalar) const
{
	return Matrix4D(firstRow * scalar, secondRow * scalar, thirdRow * scalar, fourthRow * scalar);
}

Matrix4D Matrix4D::operator/(const double scalar) const
{
	return Matrix4D(firstRow / scalar, secondRow / scalar, thirdRow / scalar, fourthRow / scalar);
}

Matrix4D Matrix4D::operator*(const Matrix4D& other) const
{
	return Matrix4D(
		Vector4D(firstRow * other.getColumn(0), firstRow * other.getColumn(1), firstRow * other.getColumn(2), firstRow * other.getColumn(3)),
		Vector4D(secondRow * other.getColumn(0), secondRow * other.getColumn(1), secondRow * other.getColumn(2), secondRow * other.getColumn(3)),
		Vector4D(thirdRow * other.getColumn(0), thirdRow * other.getColumn(1), thirdRow * other.getColumn(2), thirdRow * other.getColumn(3)),
		Vector4D(fourthRow * other.getColumn(0), fourthRow * other.getColumn(1), fourthRow * other.getColumn(2), fourthRow * other.getColumn(3))
	);
}

Matrix4D Matrix4D::operator+=(const Matrix4D& other)
{
	firstRow += other.firstRow;
	secondRow += other.secondRow;
	thirdRow += other.thirdRow;
	fourthRow += other.fourthRow;

	return *this;
}

Matrix4D Matrix4D::operator-=(const Matrix4D& other)
{
	firstRow -= other.firstRow;
	secondRow -= other.secondRow;
	thirdRow -= other.thirdRow;
	fourthRow -= other.fourthRow;

	return *this;
}

Matrix4D Matrix4D::operator*=(const float scalar)
{
	firstRow *= scalar;
	secondRow *= scalar;
	thirdRow *= scalar;
	fourthRow *= scalar;
	return *this;
}

Matrix4D Matrix4D::operator/=(const float scalar)
{
	firstRow /= scalar;
	secondRow /= scalar;
	thirdRow /= scalar;
	fourthRow /= scalar;
	return *this;
}

bool Matrix4D::operator==(const Matrix4D& other) const
{
	return firstRow == other.firstRow && secondRow == other.secondRow && thirdRow == other.thirdRow && fourthRow == other.fourthRow;
}

bool Matrix4D::operator!=(const Matrix4D& other) const
{
	return !(firstRow == other.firstRow && secondRow == other.secondRow && thirdRow == other.thirdRow && fourthRow == other.fourthRow);
}

Vector4D Matrix4D::operator[](int index) const
{
	return getRow(index);
}

std::ostream& Matrix4D::write(std::ostream& out) const
{
	out << firstRow << std::endl << secondRow << std::endl << thirdRow << std::endl << fourthRow << std::endl;

	return out;
}

Vector4D Matrix4D::getRow(int index) const
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
	case 3:
		return fourthRow;
		break;
	default:
		assert(false);
		return Vector4D::Zero();
		break;
	}
}

Vector4D Matrix4D::getColumn(int index) const
{
	return Vector4D(firstRow[index], secondRow[index], thirdRow[index], fourthRow[index]);
}

std::ostream& operator<<(std::ostream& out, Matrix4D const& mat)
{
	mat.write(out);
	return out;
}