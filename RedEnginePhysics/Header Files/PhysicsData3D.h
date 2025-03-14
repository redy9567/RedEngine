#pragma once

#include "Trackable.h"
#include "Vector3D.h"

class PhysicsData3D : public Trackable
{

public:
    friend class GameObject3D;

    Vector3D getPos() { return mPos; }
    Vector3D getVel() { return mVel; }
    float getMass() { return 1.0f / mInverseMass; }
    Vector3D getRotation() { return mRotation; }
    Vector3D getRotVel() { return mRotVel; }
    float getDampingConstnat() { return mDampingConstant; }

    void setPos(Vector3D pos) { mPos = pos; }
    void setVel(Vector3D vel) { mVel = vel; }
    void setMass(float mass) { mInverseMass = (mass == 0.0f) ? 0.0f : 1.0f / mass; }
    void setRotation(Vector3D rot) { mRotation = rot; }
    void setRotVel(Vector3D rotVel) { mRotVel = rotVel; }
    void setDampingConstant(float dampingConstant) { mDampingConstant = dampingConstant; }

    void integrate(float deltaTime);

    void addForce(Vector3D force) { mForceAccumulator += force; }
    void addTorque(Vector3D torque) { mTorqueAccumulator += torque; }

private:
    PhysicsData3D();
    PhysicsData3D(Vector3D, Vector3D, float, Vector3D, Vector3D, float);

    Vector3D mPos;
    Vector3D mVel;
    float mInverseMass;
    Vector3D mRotation;
    Vector3D mRotVel;
    float mDampingConstant;

    Vector3D mForceAccumulator;
    Vector3D mTorqueAccumulator;

};