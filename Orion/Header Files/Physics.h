#pragma once

float smallAnglePendulumAngle(float t);
float smallAnglePendulumFunction(float t);
float singlePendulumAccelerationFunction(float pendulumLength, float angle);
float doublePendulumFirstAccelerationFunction(float mass1, float mass2, float length1, float length2, float angle1, float angle2, float vel2, float acc2);
float doublePendulumSecondAccelerationFunction(float length1, float length2, float angle1, float angle2, float vel1, float acc1);