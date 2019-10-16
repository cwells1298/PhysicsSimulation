#pragma once
#include "PhysicsEngine.h"
#include "BasicActors.h"
#include <iostream>
#include <iomanip>
#include <array>

namespace PhysicsEngine
{
	//Boxes
	DynamicActor* CreateBoxDynamic(PxVec3 pos, PxVec3 dim, PxReal density, PxMaterial* default_material);	

	DynamicActor* CreateBoxKinematic(PxVec3 pos, PxVec3 dim, PxReal density, PxMaterial* default_material);

	StaticActor* CreateBoxStatic(PxVec3 pos, PxVec3 dim, PxReal density, PxMaterial* default_material);
	
	//Capsules
	DynamicActor* CreateCapsuleDynamic(PxVec3 pos, PxReal radius, PxReal halfHeight, PxReal density, PxMaterial* default_material);
	
	DynamicActor* CreateCapsuleKinematic(PxVec3 pos, PxReal radius, PxReal halfHeight, PxReal density, PxMaterial* default_material);

	StaticActor* CreateCapsuleStatic(PxVec3 pos, PxReal radius, PxReal halfHeight, PxReal density, PxMaterial* default_material);

	//Spheres
	DynamicActor* CreateSphereDynamic(PxVec3 pos, PxReal radius, PxReal density, PxMaterial* default_material);

	DynamicActor* CreateSphereKinematic(PxVec3 pos, PxReal radius, PxReal density, PxMaterial* default_material);

	StaticActor* CreateSphereStatic(PxVec3 pos, PxReal radius, PxReal density, PxMaterial* default_material);
	
	//Convex Meshes
	DynamicActor* CreateConvexMeshDynamic(PxVec3 pos, PxReal scale, PxConvexMesh* mesh, PxReal density, PxMaterial * default_material);

	DynamicActor* CreateConvexMeshKinematic(PxVec3 pos, PxReal scale, PxConvexMesh* mesh, PxReal density, PxMaterial * default_material);

	StaticActor* CreateConvexMeshStatic(PxVec3 pos, PxReal scale, PxConvexMesh* mesh, PxReal density, PxMaterial * default_material);

	//Triangle Mesh
	DynamicActor* CreateTriangleMeshDynamic(PxVec3 pos, PxReal scale, PxTriangleMesh* mesh, PxReal density, PxMaterial * default_material);

	DynamicActor* CreateTriangleMeshKinematic(PxVec3 pos, PxReal scale, PxTriangleMesh* mesh, PxReal density, PxMaterial * default_material);

	StaticActor* CreateTriangleMeshStatic(PxVec3 pos, PxReal scale, PxTriangleMesh* mesh, PxReal density, PxMaterial * default_material);

	//Create Wedge
	ConvexMesh* CreateWedgeDynamic(PxVec3 pos, PxReal width, PxReal height, PxReal length, PxReal density, PxMaterial* default_material);

	ConvexMesh* CreateWedgeKinematic(PxVec3 pos, PxReal width, PxReal height, PxReal length, PxReal density, PxMaterial* default_material, PxReal scale);

	//Create Rugby Ball
	ConvexMesh * CreateBallDynamic(PxVec3 pos, PxReal scale, PxReal density, PxMaterial * default_material);

	class Bullet
	{
	public:
		DynamicActor* bulletActor;
		bool isActive = false;
		Bullet(PxTransform trans, PxReal scale, PxReal density, bool gravDisable, PxMaterial* default_material);

		void Fire(PxReal initForce);
	};

}

//#pragma once
//#include "PhysicsEngine.h"
//#include <iostream>
//#include <iomanip>
//
//namespace PhysicsEngine
//{
//	PxRigidDynamic* CreateBoxDynamic(PxVec3 pos, PxVec3 dim, PxReal density, PxPhysics* physics, PxMaterial* default_material);	
//
//	PxRigidDynamic* CreateBoxKinematic(PxVec3 pos, PxVec3 dim, PxReal density, PxPhysics* physics, PxMaterial* default_material);
//
//	PxRigidStatic* CreateBoxStatic(PxVec3 pos, PxVec3 dim, PxReal density, PxPhysics* physics, PxMaterial* default_material);
//	
//	PxRigidDynamic* CreateCapsuleDynamic(PxVec3 pos, PxReal radius, PxReal halfHeight, PxReal density, PxPhysics* physics, PxMaterial* default_material);
//	
//	PxRigidDynamic* CreateCapsuleKinematic(PxVec3 pos, PxReal radius, PxReal halfHeight, PxReal density, PxPhysics* physics, PxMaterial* default_material);
//
//	PxRigidStatic* CreateCapsuleStatic(PxVec3 pos, PxReal radius, PxReal halfHeight, PxReal density, PxPhysics* physics, PxMaterial* default_material);
//
//	PxRigidDynamic* CreateSphereDynamic(PxVec3 pos, PxReal radius, PxReal density, PxPhysics* physics, PxMaterial* default_material);
//
//	PxRigidDynamic* CreateSphereKinematic(PxVec3 pos, PxReal radius, PxReal density, PxPhysics* physics, PxMaterial* default_material);
//
//	PxRigidStatic* CreateSphereStatic(PxVec3 pos, PxReal radius, PxReal density, PxPhysics* physics, PxMaterial* default_material);
//}
//
