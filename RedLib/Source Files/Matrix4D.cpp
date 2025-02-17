#include "Matrix4D.h"
#include <assert.h>

Matrix4D::Matrix4D()
{
	mFirstRow = Vector4D::Zero();
	mSecondRow = Vector4D::Zero();
	mThirdRow = Vector4D::Zero();
	mFourthRow = Vector4D::Zero();
	mColumnMajorFloatArray = nullptr;
};

Matrix4D::Matrix4D(Vector4D row1, Vector4D row2, Vector4D row3, Vector4D row4)
{
	mFirstRow = row1;
	mSecondRow = row2;
	mThirdRow = row3;
	mFourthRow = row4;
	mColumnMajorFloatArray = nullptr;
}

Matrix4D::~Matrix4D()
{
	cleanupColumnMajorFloatArray();
}

Matrix4D Matrix4D::operator=(const Matrix4D& other)
{
	cleanupColumnMajorFloatArray();
	mFirstRow = other.mFirstRow;
	mSecondRow = other.mSecondRow;
	mThirdRow = other.mThirdRow;
	mFourthRow = other.mFourthRow;
	return *this;
}

Matrix4D Matrix4D::operator+(const Matrix4D& other) const
{
	return Matrix4D(mFirstRow + other.mFirstRow, mSecondRow + other.mSecondRow, mThirdRow + other.mThirdRow, mFourthRow + other.mFourthRow);
}

Matrix4D Matrix4D::operator-(const Matrix4D& other) const
{
	return Matrix4D(mFirstRow - other.mFirstRow, mSecondRow - other.mSecondRow, mThirdRow - other.mThirdRow, mFourthRow - other.mFourthRow);
}

Matrix4D Matrix4D::operator*(const float scalar) const
{
	return Matrix4D(mFirstRow * scalar, mSecondRow * scalar, mThirdRow * scalar, mFourthRow * scalar);
}

Matrix4D Matrix4D::operator/(const float scalar) const
{
	return Matrix4D(mFirstRow / scalar, mSecondRow / scalar, mThirdRow / scalar, mFourthRow / scalar);
}

Matrix4D Matrix4D::operator*(const int scalar) const
{
	return Matrix4D(mFirstRow * scalar, mSecondRow * scalar, mThirdRow * scalar, mFourthRow * scalar);
}

Matrix4D Matrix4D::operator/(const int scalar) const
{
	return Matrix4D(mFirstRow / scalar, mSecondRow / scalar, mThirdRow / scalar, mFourthRow / scalar);
}

Matrix4D Matrix4D::operator*(const double scalar) const
{
	return Matrix4D(mFirstRow * scalar, mSecondRow * scalar, mThirdRow * scalar, mFourthRow * scalar);
}

Matrix4D Matrix4D::operator/(const double scalar) const
{
	return Matrix4D(mFirstRow / scalar, mSecondRow / scalar, mThirdRow / scalar, mFourthRow / scalar);
}

Matrix4D Matrix4D::operator*(const Matrix4D& other) const
{
	return Matrix4D(
		Vector4D(mFirstRow * other.getColumn(0), mFirstRow * other.getColumn(1), mFirstRow * other.getColumn(2), mFirstRow * other.getColumn(3)),
		Vector4D(mSecondRow * other.getColumn(0), mSecondRow * other.getColumn(1), mSecondRow * other.getColumn(2), mSecondRow * other.getColumn(3)),
		Vector4D(mThirdRow * other.getColumn(0), mThirdRow * other.getColumn(1), mThirdRow * other.getColumn(2), mThirdRow * other.getColumn(3)),
		Vector4D(mFourthRow * other.getColumn(0), mFourthRow * other.getColumn(1), mFourthRow * other.getColumn(2), mFourthRow * other.getColumn(3))
	);
}

Matrix4D Matrix4D::operator+=(const Matrix4D& other)
{
	cleanupColumnMajorFloatArray();
	mFirstRow += other.mFirstRow;
	mSecondRow += other.mSecondRow;
	mThirdRow += other.mThirdRow;
	mFourthRow += other.mFourthRow;

	return *this;
}

Matrix4D Matrix4D::operator-=(const Matrix4D& other)
{
	cleanupColumnMajorFloatArray();
	mFirstRow -= other.mFirstRow;
	mSecondRow -= other.mSecondRow;
	mThirdRow -= other.mThirdRow;
	mFourthRow -= other.mFourthRow;

	return *this;
}

Matrix4D Matrix4D::operator*=(const float scalar)
{
	cleanupColumnMajorFloatArray();
	mFirstRow *= scalar;
	mSecondRow *= scalar;
	mThirdRow *= scalar;
	mFourthRow *= scalar;
	return *this;
}

Matrix4D Matrix4D::operator/=(const float scalar)
{
	cleanupColumnMajorFloatArray();
	mFirstRow /= scalar;
	mSecondRow /= scalar;
	mThirdRow /= scalar;
	mFourthRow /= scalar;
	return *this;
}

bool Matrix4D::operator==(const Matrix4D& other) const
{
	return mFirstRow == other.mFirstRow && mSecondRow == other.mSecondRow && mThirdRow == other.mThirdRow && mFourthRow == other.mFourthRow;
}

bool Matrix4D::operator!=(const Matrix4D& other) const
{
	return !(mFirstRow == other.mFirstRow && mSecondRow == other.mSecondRow && mThirdRow == other.mThirdRow && mFourthRow == other.mFourthRow);
}

Vector4D Matrix4D::operator[](int index) const
{
	return getRow(index);
}

std::ostream& Matrix4D::write(std::ostream& out) const
{
	out << mFirstRow << std::endl << mSecondRow << std::endl << mThirdRow << std::endl << mFourthRow << std::endl;

	return out;
}

Vector4D Matrix4D::getRow(int index) const
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
	case 3:
		return mFourthRow;
		break;
	default:
		assert(false);
		return Vector4D::Zero();
		break;
	}
}

Vector4D Matrix4D::getColumn(int index) const
{
	return Vector4D(mFirstRow[index], mSecondRow[index], mThirdRow[index], mFourthRow[index]);
}

std::ostream& operator<<(std::ostream& out, Matrix4D const& mat)
{
	mat.write(out);
	return out;
}

void Matrix4D::cleanupColumnMajorFloatArray()
{
	if (mColumnMajorFloatArray)
	{
		delete[] mColumnMajorFloatArray;
		mColumnMajorFloatArray = nullptr;
	}
}

float* Matrix4D::convertToColumnMajorFloatArray()
{
	if (!mColumnMajorFloatArray)
	{
		mColumnMajorFloatArray = new float[16];

		mColumnMajorFloatArray[0] = mFirstRow[0];
		mColumnMajorFloatArray[1] = mSecondRow[0];
		mColumnMajorFloatArray[2] = mThirdRow[0];
		mColumnMajorFloatArray[3] = mFourthRow[0];

		mColumnMajorFloatArray[4] = mFirstRow[1];
		mColumnMajorFloatArray[5] = mSecondRow[1];
		mColumnMajorFloatArray[6] = mThirdRow[1];
		mColumnMajorFloatArray[7] = mFourthRow[1];

		mColumnMajorFloatArray[8] = mFirstRow[2];
		mColumnMajorFloatArray[9] = mSecondRow[2];
		mColumnMajorFloatArray[10] = mThirdRow[2];
		mColumnMajorFloatArray[11] = mFourthRow[2];

		mColumnMajorFloatArray[12] = mFirstRow[3];
		mColumnMajorFloatArray[13] = mSecondRow[3];
		mColumnMajorFloatArray[14] = mThirdRow[3];
		mColumnMajorFloatArray[15] = mFourthRow[3];
	}

	return mColumnMajorFloatArray;
}