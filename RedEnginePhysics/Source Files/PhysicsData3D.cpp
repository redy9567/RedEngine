#include "PhysicsData3D.h"

PhysicsData3D::PhysicsData3D()
{
    mPos = Vector3D::Zero();
    mVel = Vector3D::Zero();

    mInverseMass = 1.0f;
    mRotation = Vector3D::Zero();
    mRotVel = Vector3D::Zero();
    mDampingConstant = 1.0f;

    mForceAccumulator = Vector3D::Zero();
}

PhysicsData3D::PhysicsData3D(Vector3D pos, Vector3D vel,
    float mass, Vector3D rot, Vector3D rotVel, float dampingConstant)
{
    mPos = pos;
    mVel = vel;

    mInverseMass = (mass == 0.0f) ? 0.0f : 1.0f / mass;
    mRotation = rot;
    mRotVel = rotVel;
    mDampingConstant = dampingConstant;

    mForceAccumulator = Vector3D::Zero();
}

void PhysicsData3D::integrate(float deltaTime)
{
    mPos += mVel * deltaTime;
    mRotation += mRotVel * deltaTime;

    Vector3D acc = mForceAccumulator * mInverseMass;
    Vector3D rotAcc = mTorqueAccumulator * mInverseMass;

    mVel += acc * deltaTime;
    mRotVel += rotAcc * deltaTime;

    mVel *= mDampingConstant;
    mRotVel *= mDampingConstant;

    mForceAccumulator = Vector3D::Zero();
    mTorqueAccumulator = Vector3D::Zero();
}