#include "Camera3D.h"
#include "GraphicsSystem.h"

Camera3D::Camera3D()
{
    mLoc = Vector3D::Zero();
    mResolution = Vector2D::Zero();
    mRotation = Vector3D::Zero();
}

Camera3D::Camera3D(Vector3D location, Vector2D resolution)
{
    mLoc = location;
    mResolution = resolution;
    mRotation = Vector3D::Zero();
}

Camera3D::~Camera3D()
{
    
}