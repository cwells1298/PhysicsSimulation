#include "CompoundShape.h"

namespace PhysicsEngine
{
	void CompoundShape::AddShape(PxVec3 pos, PxQuat rot, PxVec3 dim, PxReal density, PxMaterial* default_material)//Box
	{
		CreateShape(PxBoxGeometry(dim), density);
		GetShape(numObjects)->setLocalPose(PxTransform(pos));
		GetShape(numObjects)->setMaterials(&default_material, 1);		
		//GetShape(numObjects)->Col	
		numObjects++;
	}

	void CompoundShape::AddShape(PxVec3 pos, PxQuat rot, PxReal radius, PxReal halfHeight, PxReal density, PxMaterial* default_material)//Capsule
	{
		CreateShape(PxCapsuleGeometry(radius, halfHeight), density);
		GetShape(numObjects)->setLocalPose(PxTransform(pos, rot));
		//this.colors(numObjects) = Color(PxVec3(0.0f / 255.f, 128.0f / 255.f, 255.0f / 255.f));
		numObjects++;
	}

	void CompoundShape::AddShape(PxVec3 pos, PxQuat rot, PxReal radius, PxReal density, PxMaterial* default_material)//Sphere
	{
		CreateShape(PxSphereGeometry(radius), density);
		GetShape(numObjects)->setLocalPose(PxTransform(pos, rot));
		//this.colors(numObjects) = Color(PxVec3(0.0f / 255.f, 128.0f / 255.f, 255.0f / 255.f));
		numObjects++;
	}

	void CompoundShape::AddGlobalRotation(PxQuat newQ)
	{
		newQ *= mainRigidBody->getGlobalPose().q;
		mainRigidBody->setGlobalPose(PxTransform(mainRigidBody->getGlobalPose().p, newQ));
	}

	void CompoundShape::AddLocalRotation(PxQuat newQ, int objectNum)
	{
		PxTransform q = GetShape(objectNum)->getLocalPose();
		newQ *= q.q;
		GetShape(objectNum)->setLocalPose(PxTransform(q.p, newQ));
	}
}