#pragma once
#include "PhysicsEngine.h"
#include "CreateShapes.h"
#include <iostream>
#include <iomanip>

enum ShapeType {BoxShape, CapsuleShape, SphereShape, ConvexMeshShape, TriangleMeshShape};

namespace PhysicsEngine
{
	class CompoundShape : public DynamicActor
	{
	public:
		CompoundShape(const PxTransform& pose = PxTransform(PxIdentity)) : DynamicActor(pose)
		{
			mainRigidBody = (PxRigidBody*)this->Get();
		}
	
		void AddShape(PxVec3 pos, PxQuat rot, PxVec3 dim, PxReal density, PxMaterial* default_material);//Box
		void AddShape(PxVec3 pos, PxQuat rot, PxReal radius, PxReal halfHeight, PxReal density, PxMaterial* default_material);//Capsule
		void AddShape(PxVec3 pos, PxQuat rot, PxReal radius, PxReal density, PxMaterial* default_material);//Sphere
		void AddShape(PxVec3 pos, PxQuat rot, PxReal scale, PxConvexMesh* mesh, PxReal density, PxMaterial * default_material);//Convex Mesh
		void AddShape(PxVec3 pos, PxQuat rot, PxReal scale, PxTriangleMesh* mesh, PxReal density, PxMaterial * default_material);//Triangle Mesh

		void AddGlobalRotation(PxQuat newQ);
		void AddLocalRotation(PxQuat newQ, int objectNum);

	private:
		PxRigidBody* mainRigidBody;
		int numObjects = 0;
	};
}