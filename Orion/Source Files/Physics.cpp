#include "Physics.h"
#include <math.h>

using namespace std;

float gravity = 9.81f;
float pendulumLength = 10.0f;

float startingX = 1.0f;

float smallAnglePendulumAngle(float t)
{
	//Scale by 85% to make up for the fact that 1/pendulum length is slightly off from sin(theta)
	return cos(sqrt(gravity / pendulumLength) * t) * 1 / pendulumLength * 0.85f ;
}

float smallAnglePendulumFunction(float t)
{
	return startingX * cos(sqrt(gravity / pendulumLength) * t);
}