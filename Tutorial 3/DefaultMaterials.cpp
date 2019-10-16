#include "DefaultMaterials.h"

using namespace PhysicsEngine;

DefaultMats::DefaultMats(PxPhysics * phys)
{
	physics = phys;
	cw_defaultMaterial = physics->createMaterial(0.0f, 0.0f, 0.0f);
	cw_woodMaterial = physics->createMaterial(0.35f, 0.2f, 0.603f);
	cw_metalMaterial = physics->createMaterial(0.74f, 0.57f, 0.597f);
	cw_rubberMaterial = physics->createMaterial(0.55f, 0.4f, 0.828f);
	cw_glassMaterial = physics->createMaterial(0.94f, 0.4f, 0.658f);
}
