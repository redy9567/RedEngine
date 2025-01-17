#include "Physics.h"
#include <math.h>

using namespace std;

float gravity = -9.81f;
float pendulumLength = 10.0f;

float startingX = 1.0f;

float pi = 3.14159265358979323846f;

float smallAnglePendulumAngle(float t)
{
	return cos(sqrt(-gravity / pendulumLength) * t) * 1 / pendulumLength * 45.0f ;
}

float smallAnglePendulumFunction(float t)
{
	return startingX * cos(sqrt(-gravity / pendulumLength) * t);
}

float singlePendulumAccelerationFunction(float pendulumLength, float angle)
{
	return gravity / pendulumLength * sin(angle * pi / 180.0f);
}

float doublePendulumFirstAccelerationFunction(float mass1, float mass2, float length1, float length2, float angle1, float angle2, float vel2, float acc2)
{
	float angle1Rad = angle1 * pi / 180.0f;
	float angle2Rad = angle2 * pi / 180.0f;

	float numerator = -mass2 * length2 * acc2 * cos(angle1Rad - angle2Rad) - mass2 * length2 * vel2 * vel2 * sin(angle1Rad - angle2Rad) - (mass1 + mass2) * gravity * sin(angle1Rad);

	return numerator / ((mass1 + mass2) * length1);
}

float doublePendulumSecondAccelerationFunction(float length1, float length2, float angle1, float angle2, float vel1, float acc1)
{
	float angle1Rad = angle1 * pi / 180.0f;
	float angle2Rad = angle2 * pi / 180.0f;

	return (-length1 * acc1 * cos(angle1Rad - angle2Rad) + length1 * vel1 * vel1 * sin(angle1Rad - angle2Rad) - gravity * sin(angle2Rad)) / length2;
}