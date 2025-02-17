//#include "Camera2D.h"
//#include "GraphicsSystem.h"
//
//Camera2D::Camera2D()
//{
//    mLoc = Vector2D::Zero();
//    mIsBeingDragged = false;
//    mDragStartPos = Vector2D::Zero();
//    mCameraStartPos = Vector2D::Zero();
//    mResolution = Vector2D::Zero();
//}
//
//Camera2D::Camera2D(Vector2D location, Vector2D resolution)
//{
//    mLoc = location;
//    mResolution = resolution;
//    mIsBeingDragged = false;
//    mDragStartPos = Vector2D::Zero();
//    mCameraStartPos = Vector2D::Zero();
//}
//
//Camera2D::~Camera2D()
//{
//    
//}
//
//void Camera2D::startMouseDrag(Vector2D mousePos)
//{
//    mDragStartPos = mousePos;
//    mCameraStartPos = mLoc;
//    mIsBeingDragged = true;
//}
//
//void Camera2D::update(Vector2D mousePos)
//{
//    if (mIsBeingDragged)
//    {
//        Vector2D gridTranslation = GraphicsSystem::getInstance()->convertToGridCoordinates(mDragStartPos - mousePos);
//
//        mLoc = mCameraStartPos + gridTranslation;
//    }
//}
//
//void Camera2D::stopMouseDrag()
//{
//    mIsBeingDragged = false;
//}