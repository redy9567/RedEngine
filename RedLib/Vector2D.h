#pragma once

class Vector2D
{

public:
	Vector2D();
	Vector2D(float x, float y);
	Vector2D(int x, int y);
	~Vector2D();

	Vector2D operator=(const Vector2D& other);

	float getX() { return mX; }
	float getY() { return mY; }

private:
	float mX, mY;

};
