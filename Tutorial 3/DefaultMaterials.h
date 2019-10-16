#pragma once
#include "PhysicsEngine.h"
#include <iostream>
#include <iomanip>
#include <array>

using namespace PhysicsEngine;

class DefaultMats
{
public:
	DefaultMats(PxPhysics* phys);

	PxMaterial* cw_defaultMaterial;
	PxMaterial* cw_woodMaterial;
	PxMaterial* cw_metalMaterial;
	PxMaterial* cw_rubberMaterial;
	PxMaterial* cw_glassMaterial;
	PxMaterial* cw_concreteMaterial;
	PxMaterial* cw_grassMaterial;
private:
	PxPhysics* physics;
};

class Colours
{
public:
	PxVec3 colourWood = PxVec3(90.0f / 255.0f, 56.0f / 255.0f, 38.0f / 255.0f);
	PxVec3 colourStone = PxVec3(149.0f / 255.0f, 148.0f / 255.0f, 139.0f / 255.0f);
	PxVec3 colourRope = PxVec3(185.0f / 255.0f, 148.0f / 255.0f, 130.0f / 255.0f);
	PxVec3 colourGrass = PxVec3(96.0f / 255.0f, 158.0f / 255.0f, 56.0f / 255.0f);
	PxVec3 colourGoalPosts = PxVec3(240.0f / 255.0f, 240.0f / 255.0f, 240.0f / 255.0f);
	PxVec3 colourGoalTrigger = PxVec3(50.0f / 255.0f, 50.0f / 255.0f, 50.0f / 255.0f);
	PxVec3 colourWindTrigger = PxVec3(135.0f / 255.0f, 206.0f / 255.0f, 235.0f / 255.0f);
	PxVec3 colourMage = PxVec3(50.0f / 255.0f, 50.0f / 255.0f, 235.0f / 255.0f);
	//PxVec3 colourMetal = PxVec3(90.0f / 255.0f, 56.0f / 255.0f, 38.0f / 255.0f);
};