#pragma once

#include "Trackable.h"
#include "Vector2D.h"
#include "Vector3D.h"

class Camera3D : public Trackable
{

public:
    Camera3D();
    Camera3D(Vector3D location, Vector2D resolution);
    ~Camera3D();

    void setLoc(Vector3D location) { mLoc = location; }
    void setRotation(Vector3D rotation) { mRotation = rotation; }

    Vector3D getLoc() { return mLoc; }
    Vector3D getRotation() { return mRotation; }
    Vector2D getResolution() { return mResolution; }

private:
    Vector3D mLoc;
    Vector3D mRotation;

    Vector2D mResolution;

};