#include "Matrix3D.h"
#include <assert.h>

Matrix3D::Matrix3D()
{
	mFirstRow = Vector3D::Zero();
	mSecondRow = Vector3D::Zero();
	mThirdRow = Vector3D::Zero();
	mColumnMajorFloatArray = nullptr;
};

Matrix3D::Matrix3D(float a, float b, float c, float d, float e, float f, float g, float h, float i)
{
	mFirstRow = Vector3D(a, b, c);
	mSecondRow = Vector3D(d, e, f);
	mThirdRow = Vector3D(g, h, i);
	mColumnMajorFloatArray = nullptr;
}

Matrix3D::Matrix3D(int a, int b, int c, int d, int e, int f, int g, int h, int i)
{
	mFirstRow = Vector3D(a, b, c);
	mSecondRow = Vector3D(d, e, f);
	mThirdRow = Vector3D(g, h, i);
	mColumnMajorFloatArray = nullptr;
}

Matrix3D::Matrix3D(double a, double b, double c, double d, double e, double f, double g, double h, double i)
{
	mFirstRow = Vector3D(a, b, c);
	mSecondRow = Vector3D(d, e, f);
	mThirdRow = Vector3D(g, h, i);
	mColumnMajorFloatArray = nullptr;
}

Matrix3D::Matrix3D(unsigned int a, unsigned int b, unsigned int c, unsigned int d, unsigned int e, unsigned int f, unsigned int g, unsigned int h, unsigned int i)
{
	mFirstRow = Vector3D(a, b, c);
	mSecondRow = Vector3D(d, e, f);
	mThirdRow = Vector3D(g, h, i);
	mColumnMajorFloatArray = nullptr;
}

Matrix3D::Matrix3D(Vector3D row1, Vector3D row2, Vector3D row3)
{
	mFirstRow = row1;
	mSecondRow = row2;
	mThirdRow = row3;
	mColumnMajorFloatArray = nullptr;
}

Matrix3D::~Matrix3D()
{
	cleanupColumnMajorFloatArray();
}

Matrix3D Matrix3D::operator=(const Matrix3D& other)
{
	cleanupColumnMajorFloatArray();

	mFirstRow = other.mFirstRow;
	mSecondRow = other.mSecondRow;
	mThirdRow = other.mThirdRow;
	return *this;
}

Matrix3D Matrix3D::operator+(const Matrix3D& other) const
{
	return Matrix3D(mFirstRow + other.mFirstRow, mSecondRow + other.mSecondRow, mThirdRow + other.mThirdRow);
}

Matrix3D Matrix3D::operator-(const Matrix3D& other) const
{
	return Matrix3D(mFirstRow - other.mFirstRow, mSecondRow - other.mSecondRow, mThirdRow - other.mThirdRow);
}

Matrix3D Matrix3D::operator*(const float scalar) const
{
	return Matrix3D(mFirstRow * scalar, mSecondRow * scalar, mThirdRow * scalar);
}

Matrix3D Matrix3D::operator/(const float scalar) const
{
	return Matrix3D(mFirstRow / scalar, mSecondRow / scalar, mThirdRow / scalar);
}

Matrix3D Matrix3D::operator*(const int scalar) const
{
	return Matrix3D(mFirstRow * scalar, mSecondRow * scalar, mThirdRow * scalar);
}

Matrix3D Matrix3D::operator/(const int scalar) const
{
	return Matrix3D(mFirstRow / scalar, mSecondRow / scalar, mThirdRow / scalar);
}

Matrix3D Matrix3D::operator*(const double scalar) const
{
	return Matrix3D(mFirstRow * scalar, mSecondRow * scalar, mThirdRow * scalar);
}

Matrix3D Matrix3D::operator/(const double scalar) const
{
	return Matrix3D(mFirstRow / scalar, mSecondRow / scalar, mThirdRow / scalar);
}

Matrix3D Matrix3D::operator*(const Matrix3D& other) const
{
	return Matrix3D(
		Vector3D(mFirstRow * other.getColumn(0), mFirstRow * other.getColumn(1), mFirstRow * other.getColumn(2)),
		Vector3D(mSecondRow * other.getColumn(0), mSecondRow * other.getColumn(1), mSecondRow * other.getColumn(2)),
		Vector3D(mThirdRow * other.getColumn(0), mThirdRow * other.getColumn(1), mThirdRow * other.getColumn(2))
	);
}

Matrix3D Matrix3D::operator+=(const Matrix3D& other)
{
	cleanupColumnMajorFloatArray();

	mFirstRow += other.mFirstRow;
	mSecondRow += other.mSecondRow;
	mThirdRow += other.mThirdRow;

	return *this;
}

Matrix3D Matrix3D::operator-=(const Matrix3D& other)
{
	cleanupColumnMajorFloatArray();

	mFirstRow -= other.mFirstRow;
	mSecondRow -= other.mSecondRow;
	mThirdRow -= other.mThirdRow;

	return *this;
}

Matrix3D Matrix3D::operator*=(const float scalar)
{
	cleanupColumnMajorFloatArray();

	mFirstRow *= scalar;
	mSecondRow *= scalar;
	mThirdRow *= scalar;
	return *this;
}

Matrix3D Matrix3D::operator/=(const float scalar)
{
	cleanupColumnMajorFloatArray();

	mFirstRow /= scalar;
	mSecondRow /= scalar;
	mThirdRow /= scalar;
	return *this;
}

bool Matrix3D::operator==(const Matrix3D& other) const
{
	return mFirstRow == other.mFirstRow && mSecondRow == other.mSecondRow && mThirdRow == other.mThirdRow;
}

bool Matrix3D::operator!=(const Matrix3D& other) const
{
	return !(mFirstRow == other.mFirstRow && mSecondRow == other.mSecondRow && mThirdRow == other.mThirdRow);
}

Vector3D Matrix3D::operator[](int index) const
{
	return getRow(index);
}

std::ostream& Matrix3D::write(std::ostream& out) const
{
	out << mFirstRow << std::endl << mSecondRow << std::endl << mThirdRow << std::endl;

	return out;
}

Vector3D Matrix3D::getRow(int index) const
{
	switch (index)
	{
	case 0:
		return mFirstRow;
		break;
	case 1:
		return mSecondRow;
		break;
	case 2:
		return mThirdRow;
		break;
	default:
		assert(false);
		return Vector3D::Zero();
		break;
	}
}

Vector3D Matrix3D::getColumn(int index) const
{
	return Vector3D(mFirstRow[index], mSecondRow[index], mThirdRow[index]);
}

std::ostream& operator<<(std::ostream& out, Matrix3D const& mat)
{
	mat.write(out);
	return out;
}

void Matrix3D::cleanupColumnMajorFloatArray()
{
	if (mColumnMajorFloatArray)
	{
		delete[] mColumnMajorFloatArray;
		mColumnMajorFloatArray = nullptr;
	}
}

float* Matrix3D::convertToColumnMajorFloatArray()
{
	if (!mColumnMajorFloatArray)
	{
		mColumnMajorFloatArray = new float[9];

		mColumnMajorFloatArray[0] = mFirstRow[0];
		mColumnMajorFloatArray[1] = mSecondRow[0];
		mColumnMajorFloatArray[2] = mThirdRow[0];

		mColumnMajorFloatArray[3] = mFirstRow[1];
		mColumnMajorFloatArray[4] = mSecondRow[1];
		mColumnMajorFloatArray[5] = mThirdRow[1];

		mColumnMajorFloatArray[6] = mFirstRow[2];
		mColumnMajorFloatArray[7] = mSecondRow[2];
		mColumnMajorFloatArray[8] = mThirdRow[2];
	}

	return mColumnMajorFloatArray;
}