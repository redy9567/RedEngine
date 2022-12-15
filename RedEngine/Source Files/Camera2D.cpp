#include "Camera2D.h"

Camera2D::Camera2D()
{
    mLoc = Vector2D::Zero();
}

Camera2D::Camera2D(Vector2D location)
{
    mLoc = location;
}

Camera2D::~Camera2D()
{
    
}