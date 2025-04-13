#pragma once
#include "Trackable.h"
#include "Vector3D.h"
#include "PhysicsData3D.h"
#include <assert.h>
#include "Matrix4D.h"

class Mesh3D;

class GameObject3D : public Trackable
{
public:
	friend class GraphicsSystem;
	friend class GameObject3DManager;

	Vector3D getLoc() { return (mPhysicsEnabled) ? mPhysicsData.getPos() : mLoc; }
	Vector3D getScale() { return mScale; }

	Vector3D getRotation() { return (mPhysicsEnabled) ? mPhysicsData.getRotation() : mRotation; }
	Vector3D getColor() { return mColor; }

	PhysicsData3D* getPhysics() { if (mPhysicsEnabled) return &mPhysicsData; else assert(false); }

	void setLoc(Vector3D location) { if (mPhysicsEnabled) mPhysicsData.setPos(location); else mLoc = location; }
	void setScale(Vector3D scale) { mScale = scale; }
	void setRotation(Vector3D rot) { if (mPhysicsEnabled) mPhysicsData.setRotation(rot); else mRotation = rot; }
	void setColor(Vector3D color) { mColor = color; }

	virtual void update(float deltaTime) { if (mPhysicsEnabled) mPhysicsData.integrate(deltaTime); }

	void enablePhysics() { mPhysicsData.setPos(mLoc); mPhysicsData.setRotation(mRotation); mPhysicsEnabled = true; }

	Matrix4D getWorldToObjMatrix() { return mWorldToObjMatrix; }
	Matrix4D getObjToWorldMatrix() { return mObjToWorldMatrix; }

protected:
	GameObject3D();
	virtual ~GameObject3D();

	GameObject3D(Mesh3D* mesh, Vector3D loc = Vector3D::Zero(), Vector3D color = Vector3D::Zero(), Vector3D scale = Vector3D::One(), Vector3D rot = Vector3D::Zero());

	Vector3D mLoc;
	Vector3D mRotation;
	Vector3D mScale;

	Vector3D mColor;

	Mesh3D* mpMesh;

	bool mPhysicsEnabled = false;
	PhysicsData3D mPhysicsData;

	Matrix4D mWorldToObjMatrix;
	Matrix4D mObjToWorldMatrix;

};