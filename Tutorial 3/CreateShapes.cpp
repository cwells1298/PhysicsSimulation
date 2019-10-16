#include "CreateShapes.h"

using namespace PhysicsEngine;

//Boxes
DynamicActor * PhysicsEngine::CreateBoxDynamic(PxVec3 pos, PxVec3 dim, PxReal density, PxMaterial * default_material)
{
	DynamicActor* newShape = new DynamicActor(PxTransform(pos));
	newShape->CreateShape(PxBoxGeometry(dim), density);
	newShape->Material(default_material);
	return newShape;
}

DynamicActor * PhysicsEngine::CreateBoxKinematic(PxVec3 pos, PxVec3 dim, PxReal density, PxMaterial * default_material)
{
	DynamicActor* newShape = new DynamicActor(PxTransform(pos));
	newShape->CreateShape(PxBoxGeometry(dim), density);
	newShape->Material(default_material);
	newShape->SetKinematic(true);
	newShape->SetKinematic(true);
	return newShape;
}

StaticActor * PhysicsEngine::CreateBoxStatic(PxVec3 pos, PxVec3 dim, PxReal density, PxMaterial * default_material)
{
	StaticActor* newShape = new StaticActor(PxTransform(pos));
	newShape->CreateShape(PxBoxGeometry(dim), density);
	newShape->Material(default_material);
	return newShape;
}

//Capsules
DynamicActor * PhysicsEngine::CreateCapsuleDynamic(PxVec3 pos, PxReal radius, PxReal halfHeight, PxReal density, PxMaterial * default_material)
{
	DynamicActor* newShape = new DynamicActor(PxTransform(pos));
	newShape->CreateShape(PxCapsuleGeometry(radius, halfHeight), density);
	newShape->Material(default_material);
	return newShape;
}

DynamicActor * PhysicsEngine::CreateCapsuleKinematic(PxVec3 pos, PxReal radius, PxReal halfHeight, PxReal density, PxMaterial * default_material)
{
	DynamicActor* newShape = new DynamicActor(PxTransform(pos));
	newShape->CreateShape(PxCapsuleGeometry(radius, halfHeight), density);
	newShape->Material(default_material);
	newShape->SetKinematic(true);
	return newShape;
}

StaticActor * PhysicsEngine::CreateCapsuleStatic(PxVec3 pos, PxReal radius, PxReal halfHeight, PxReal density, PxMaterial * default_material)
{
	StaticActor* newShape = new StaticActor(PxTransform(pos));
	newShape->CreateShape(PxCapsuleGeometry(radius, halfHeight), density);
	newShape->Material(default_material);
	return newShape;
}

//Spheres
DynamicActor * PhysicsEngine::CreateSphereDynamic(PxVec3 pos, PxReal radius, PxReal density, PxMaterial * default_material)
{
	DynamicActor* newShape = new DynamicActor(PxTransform(pos));
	newShape->CreateShape(PxSphereGeometry(radius), density);
	newShape->Material(default_material);
	return newShape;
}

DynamicActor * PhysicsEngine::CreateSphereKinematic(PxVec3 pos, PxReal radius, PxReal density, PxMaterial * default_material)
{
	DynamicActor* newShape = new DynamicActor(PxTransform(pos));
	newShape->CreateShape(PxSphereGeometry(radius), density);
	newShape->Material(default_material);
	newShape->SetKinematic(true);
	return newShape;
}

StaticActor * PhysicsEngine::CreateSphereStatic(PxVec3 pos, PxReal radius, PxReal density, PxMaterial * default_material)
{
	StaticActor* newShape = new StaticActor(PxTransform(pos));
	newShape->CreateShape(PxSphereGeometry(radius), density);
	newShape->Material(default_material);
	return newShape;
}

//Convex Meshes
DynamicActor * PhysicsEngine::CreateConvexMeshDynamic(PxVec3 pos, PxReal scale, PxConvexMesh* mesh, PxReal density, PxMaterial * default_material)
{
	DynamicActor* newShape = new DynamicActor(PxTransform(pos));
	newShape->CreateShape(PxConvexMeshGeometry(mesh, PxMeshScale(scale)), density);
	newShape->Material(default_material);
	return newShape;
}

DynamicActor * PhysicsEngine::CreateConvexMeshKinematic(PxVec3 pos, PxReal scale, PxConvexMesh* mesh, PxReal density, PxMaterial * default_material)
{
	DynamicActor* newShape = new DynamicActor(PxTransform(pos));
	newShape->CreateShape(PxConvexMeshGeometry(mesh, PxMeshScale(scale)), density);
	newShape->Material(default_material);
	newShape->SetKinematic(true);
	return newShape;
}

StaticActor * PhysicsEngine::CreateConvexMeshStatic(PxVec3 pos, PxReal scale, PxConvexMesh* mesh, PxReal density, PxMaterial * default_material)
{
	StaticActor* newShape = new StaticActor(PxTransform(pos));
	newShape->CreateShape(PxConvexMeshGeometry(mesh, PxMeshScale(scale)), density);
	newShape->Material(default_material);
	return newShape;
}

//Triangle Meshes
DynamicActor * PhysicsEngine::CreateTriangleMeshDynamic(PxVec3 pos, PxReal scale, PxTriangleMesh* mesh, PxReal density, PxMaterial * default_material)
{
	DynamicActor* newShape = new DynamicActor(PxTransform(pos));
	newShape->CreateShape(PxTriangleMeshGeometry(mesh, PxMeshScale(scale)), density);
	newShape->Material(default_material);
	return newShape;
}

DynamicActor * PhysicsEngine::CreateTriangleMeshKinematic(PxVec3 pos, PxReal scale, PxTriangleMesh* mesh, PxReal density, PxMaterial * default_material)
{
	DynamicActor* newShape = new DynamicActor(PxTransform(pos));
	newShape->CreateShape(PxTriangleMeshGeometry(mesh, PxMeshScale(scale)), density);
	newShape->Material(default_material);
	newShape->SetKinematic(true);
	return newShape;
}

StaticActor * PhysicsEngine::CreateTriangleMeshStatic(PxVec3 pos, PxReal scale, PxTriangleMesh* mesh, PxReal density, PxMaterial * default_material)
{
	StaticActor* newShape = new StaticActor(PxTransform(pos));
	newShape->CreateShape(PxTriangleMeshGeometry(mesh, PxMeshScale(scale)), density);
	newShape->Material(default_material);
	return newShape;
}

//Wedge
ConvexMesh * PhysicsEngine::CreateWedgeDynamic(PxVec3 pos, PxReal width, PxReal height, PxReal length, PxReal density, PxMaterial * default_material)
{	
	vector<PxVec3> verts = { PxVec3(-width / 2, -height / 2, -length / 2), PxVec3(-width / 2, height / 2, length / 2), PxVec3(-width / 2, -height / 2, length / 2), PxVec3(width / 2, -height / 2, -length / 2), PxVec3(width / 2, height / 2, length / 2), PxVec3(width / 2, -height / 2, length / 2) };
	//PxU32 wedge_trigs[24] = { 0, 2, 1, 0, 1, 3, 0, 4, 3, 4, 3, 5, 2, 1, 5, 1, 3, 5, 5, 4, 2, 4, 0, 2 };
	ConvexMesh* mesh = new ConvexMesh(verts, PxTransform(pos), density);
	mesh->Material(default_material);
	return mesh;
}

ConvexMesh * PhysicsEngine::CreateWedgeKinematic(PxVec3 pos, PxReal width, PxReal height, PxReal length, PxReal density, PxMaterial * default_material, PxReal scale)
{
	vector<PxVec3> verts = { scale * PxVec3(-width / 2, -height / 2, -length / 2), scale *  PxVec3(-width / 2, height / 2, length / 2),  scale * PxVec3(-width / 2, -height / 2, length / 2),
		 scale * PxVec3(width / 2, -height / 2, -length / 2), scale *  PxVec3(width / 2, height / 2, length / 2),  scale * PxVec3(width / 2, -height / 2, length / 2) };
	//PxU32 wedge_trigs[24] = { 0, 2, 1, 0, 1, 3, 0, 4, 3, 4, 3, 5, 2, 1, 5, 1, 3, 5, 5, 4, 2, 4, 0, 2 };
	ConvexMesh* mesh = new ConvexMesh(verts, PxTransform(pos * scale), density);
	mesh->Material(default_material);
	mesh->SetKinematic(true);
	return mesh;
}

ConvexMesh * PhysicsEngine::CreateBallDynamic(PxVec3 pos, PxReal scale, PxReal density, PxMaterial * default_material)
{
	vector<PxVec3> verts = { scale*PxVec3(0.0f, 0.075f, -0.15f), 
		/**/scale*PxVec3(0.0f, 0.0175f, -0.075f), scale*PxVec3(0.0575f, 0.075f, -0.075f), scale*PxVec3(0.0f, 0.1325f, -0.075f), scale*PxVec3(-0.0575f, 0.075f, -0.075f),

		/**/scale*PxVec3(0.0f, 0.0f, 0.0f), scale*PxVec3(0.075f, 0.075f, 0.0f), scale*PxVec3(0.0f, 0.15f, 0.0f), scale*PxVec3(-0.075f, 0.075f, 0.0f), 

		/**/scale*PxVec3(0.0f, 0.0175f, 0.075f), scale*PxVec3(0.0575f, 0.075f, 0.075f), scale*PxVec3(0.0f, 0.1325f, 0.075f), scale*PxVec3(-0.0575f, 0.075f, 0.075f),

		/**/scale*PxVec3(0.0f, 0.075f, 0.15f) };
	ConvexMesh* mesh = new ConvexMesh(verts, PxTransform(pos), density);
	mesh->Material(default_material);
	return mesh;
}

//Bullet
Bullet::Bullet(PxTransform trans, PxReal scale, PxReal density, bool gravDisable, PxMaterial * default_material)
{
	bulletActor = new DynamicActor(trans);
	bulletActor->CreateShape(PxCapsuleGeometry(0.2f * scale, 0.3f * scale), density);
	bulletActor->GetShape(0)->getActor()->setActorFlag(PxActorFlag::eDISABLE_GRAVITY, gravDisable);
	bulletActor->Material(default_material);	
}

void Bullet::Fire(PxReal initForce)
{
	//bulletActor->GetShape(0)->getActor()->
	PxRigidDynamic* px_actor = (PxRigidDynamic*)bulletActor->Get();
	px_actor->addForce(initForce * PxVec3(1.0f, 0.0f, 0.0f));
}
