#pragma once
#include "PhysicsEngine.h"
#include "CreateShapes.h"
#include "DefaultMaterials.h"
#include "CompoundShape.h"
#include <iostream>
#include <iomanip>
#include <array>
#include <math.h>

namespace PhysicsEngine
{
	enum ShapeType {Gun, Ball, Ram};

	class CW_DynamicActor
	{
	public:
		DynamicActor* mainActor;

		CW_DynamicActor(Scene* scene);

		//Box
		void AddActor(PxVec3 pos, PxVec3 dim, PxReal density, PxMaterial * default_material);

		//Capsule
		void AddActor(PxVec3 pos, PxReal radius, PxReal halfHeight, PxReal density, PxMaterial * default_material);

		//Sphere
		void AddActor(PxVec3 pos, PxReal radius, PxReal density, PxMaterial * default_material);

		//Convex Mesh
		void AddActor(PxVec3 pos, ShapeType shape, PxReal scale, PxReal density, PxMaterial * default_material);

		void RemoveActor();

		void SetKinematic(bool isKinematic);

		void SetTrigger(bool isTrigger);

		void MoveObject(PxVec3 pos);

		void RotateObject(PxQuat rot);
			
	private:
		Scene* currentScene;
		bool actorPresent = false;
	};

	class CW_StaticActor
	{
	public:
		StaticActor* mainActor;

		//Box
		void AddActor(PxVec3 pos, PxVec3 dim, PxReal density, PxMaterial * default_material);

		void RemoveActor();

		CW_StaticActor(Scene* scene);

	private:
		Scene* currentScene;
		bool actorPresent = false;
	};

	class BatteringRam
	{
	public:
		BatteringRam(Scene* scene, PxVec3 pos, PxPhysics* phys, PxReal scale);

		//TODO add slidable holder for battering ram
		//TODO change ram to cylinder
		//TODO use real density of wood 
		//TODO use real density of rope

		void AddForce(PxReal forceToAdd);

		void ChangeGravity(bool gravityActive);

		void MoveRamPressed(PxReal angularVelocity, bool limited);

		void MoveRamReleased();

		void DropRam(bool limited);

		void ChangeSpeed(float speedChange, int extreme);

		PxReal ramSpeed = 0;
		int extremeMultiplier = 10;

		CW_DynamicActor *ram;
		Actor* ramAct;

	private:
		CW_DynamicActor *anchorAnchor1, *anchorAnchor2, *anchorAnchor3, *anchorAnchor4;
		CW_DynamicActor *ropeAnchor1, *ropeAnchor2, *ropeAnchor3, *ropeAnchor4;
		CW_DynamicActor *rope1, *rope2, *rope3, *rope4;		
		
		CW_DynamicActor *base;
		CW_DynamicActor *leg1, *leg2, *leg3, *leg4;

		Actor* ropeA1Act, *ropeA2Act, *ropeA3Act, *ropeA4Act;
		Actor* rope1Act, *rope2Act, *rope3Act, *rope4Act;
		

		RevoluteJoint* jointAnchor1,* jointAnchor2,* jointAnchor3,* jointAnchor4;
		PxRevoluteJoint* jA1, *jA2, *jA3, *jA4;

		FixedJoint* baseJoint1, *baseJoint2, *baseJoint3, *baseJoint4;
		FixedJoint* legJoint1, *legJoint2, *legJoint3, *legJoint4;
		Actor* baseAct, *leg1Act, *leg2Act, *leg3Act, *leg4Act;

		PxRigidBody* ramBody;
				
		PxReal maxSpeed = 10.0f;
		PxReal minSpeed = 0.0f;

		DefaultMats* mats;
		Colours* cols;
		PxPhysics* physics;

		PxReal woodDensity = 740; //Density of English Oak
		PxReal ropeDensity = 1490; //Density of hempen rope
	};

	class Posts
	{
	public:
		Posts(Scene* scene, PxVec3 pos, PxPhysics* phys, PxReal scale);
		void AlterWind(PxReal windValue);
		PxRigidBody* postBody;
	private:
		DefaultMats* mats;
		Colours* cols;
		PxPhysics* physics;

		CompoundShape* posts;
		CW_DynamicActor* goalTrigger;
		Cloth* goalCloth,* goalCloth2;
	};

	class RugbyBall
	{
	public:
		RugbyBall(Scene* scene, PxVec3 pos, PxPhysics* phys, PxReal scale, PxReal density);
		void ResetPosition();
		CW_DynamicActor* ball;
		Actor* ballAct;
		PxRigidBody* ballBody;
	private:
		DefaultMats* mats;
		Colours* cols;
		PxPhysics* physics;
		
		PxVec3 startPos;
		PxReal baseScale = 0.3f;
		
	};

	class WindMage
	{
	public:
		WindMage(Scene* scene, PxVec3 pos, PxPhysics* phys, PxReal scale);
		CW_DynamicActor* mage;
		CW_DynamicActor* wind;
		PxRigidBody* mageBody;
		RevoluteJoint* jointAnchor1;
		Actor* mageAct;
		Actor* windAct;
	private:
		DefaultMats* mats;
		Colours* cols;
		PxPhysics* physics;

		PxReal rotSpeed = 3.0f;
	};
}
