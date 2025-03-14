#include "GameObject3D.h"

GameObject3D::GameObject3D()
{
	mLoc = Vector3D::Zero();
	mRotation = Vector3D::Zero();
	mScale = Vector3D::Zero();
	mColor = Vector3D::Zero();

	mpMesh = nullptr;
}

GameObject3D::GameObject3D(Mesh3D* mesh, Vector3D loc, Vector3D color, Vector3D scale, Vector3D rot)
{
	mLoc = loc;
	mScale = scale;
	mRotation = rot;
	mColor = color;

	mpMesh = mesh;
}

GameObject3D::~GameObject3D()
{

}