#pragma once

#include "Trackable.h"
#include "Vector2D.h"

class Camera2D : public Trackable
{

public:
    Camera2D();
    Camera2D(Vector2D location);
    ~Camera2D();

    void setLoc(Vector2D location) { mLoc = location; }

    Vector2D getLoc() { return mLoc; }

    void startMouseDrag(Vector2D mousePos);
    void update(Vector2D mousePos);
    void stopMouseDrag();

private:
    Vector2D mLoc;

    bool mIsBeingDragged;
    Vector2D mDragStartPos, mCameraStartPos;

};