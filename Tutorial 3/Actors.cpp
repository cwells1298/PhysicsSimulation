#include "Actors.h"

using namespace PhysicsEngine;

PhysicsEngine::CW_DynamicActor::CW_DynamicActor(Scene* scene)
{
	currentScene = scene;
}

void PhysicsEngine::CW_DynamicActor::AddActor(PxVec3 pos, PxVec3 dim, PxReal density, PxMaterial * default_material)
{
	if (actorPresent == false)
	{
		mainActor = CreateBoxDynamic(pos, dim, density, default_material);
		currentScene->Add(mainActor);
		actorPresent = true;
	}
	else
	{
		cout << "Actor already exists";
	}
}

void PhysicsEngine::CW_DynamicActor::AddActor(PxVec3 pos, PxReal radius, PxReal halfHeight, PxReal density, PxMaterial * default_material)
{
	if (actorPresent == false)
	{
		mainActor = CreateCapsuleDynamic(pos, radius, halfHeight, density, default_material);
		currentScene->Add(mainActor);
		actorPresent = true;
	}
	else
	{
		cout << "Actor already exists";
	}
}

void PhysicsEngine::CW_DynamicActor::AddActor(PxVec3 pos, PxReal radius, PxReal density, PxMaterial * default_material)
{
	if (actorPresent == false)
	{
		mainActor = CreateSphereDynamic(pos, radius, density, default_material);
		currentScene->Add(mainActor);
		actorPresent = true;
	}
	else
	{
		cout << "Actor already exists";
	}
}

void PhysicsEngine::CW_DynamicActor::AddActor(PxVec3 pos, ShapeType shape, PxReal scale, PxReal density, PxMaterial * default_material)
{
	if (actorPresent == false)
	{
		bool actorAdded = true;
		switch (shape)
		{
		case Ball:
			mainActor = CreateBallDynamic(pos, scale, density, default_material);
			currentScene->Add(mainActor);
			break;
		default:
			cout << "Shape not available";
			actorAdded = false;
			break;
		}

		actorPresent = actorAdded;
	}
	else
	{
		cout << "Actor already exists";
	}
}

void PhysicsEngine::CW_DynamicActor::RemoveActor()
{
	PxActor* actor = (PxRigidActor*)mainActor->Get();
	actor->release();
	mainActor  = NULL;
	actorPresent = false;
}

void PhysicsEngine::CW_DynamicActor::SetKinematic(bool isKinematic)
{
	mainActor->SetKinematic(isKinematic);
}

void PhysicsEngine::CW_DynamicActor::SetTrigger(bool isTrigger)
{
	mainActor->SetTrigger(isTrigger);
}

void PhysicsEngine::CW_DynamicActor::MoveObject(PxVec3 pos)
{
	mainActor->GetShape(0)->setLocalPose(PxTransform(pos));
}

void PhysicsEngine::CW_DynamicActor::RotateObject(PxQuat rot)
{
	mainActor->GetShape(0)->setLocalPose(PxTransform(rot));
}

void PhysicsEngine::CW_StaticActor::AddActor(PxVec3 pos, PxVec3 dim, PxReal density, PxMaterial * default_material)
{
	if (actorPresent == false)
	{
		mainActor = CreateBoxStatic(pos, dim, density, default_material);
		currentScene->Add(mainActor);
		actorPresent = true;
	}
	else
	{
		cout << "Actor already exists";
	}
}

void PhysicsEngine::CW_StaticActor::RemoveActor()
{
	PxActor* actor = (PxRigidActor*)mainActor->Get();
	actor->release();
	mainActor = NULL;
}

PhysicsEngine::CW_StaticActor::CW_StaticActor(Scene * scene)
{
	currentScene = scene;
}

PhysicsEngine::BatteringRam::BatteringRam(Scene* scene, PxVec3 pos, PxPhysics* phys, PxReal scale)
{
	physics = phys;
	mats = new DefaultMats(physics);
	cols = new Colours();

	////Base
	//{
	//	base = new CW_DynamicActor(scene);
	//	base->AddActor(pos + (scale * PxVec3(0.0f, 0.01f, 7.5f)), scale * PxVec3(3.5f, 0.01f, 8.0f), 100.0f, mats->cw_defaultMaterial);
	//	base->mainActor->Color(cols->colourWood);
	//	base->mainActor->Name("Base");
	//	baseAct = (Actor*)base->mainActor;
	//	base->SetKinematic(true);
	//}

	////Leg 1
	//{
	//	leg1 = new CW_DynamicActor(scene);
	//	leg1->AddActor(pos + (scale * PxVec3(-3.0f, 5.25f, 0.0f)), scale * PxVec3(0.5f, 5.25f, 0.5f), 1.0f, mats->cw_defaultMaterial);
	//	leg1->mainActor->Color(cols->colourStone);
	//	leg1->mainActor->Name("Leg1");
	//	leg1Act = (Actor*)leg1->mainActor;
	//	leg1->SetKinematic(true);
	//	baseJoint1 = new FixedJoint(baseAct, PxTransform(PxVec3(-1.5f, 0.01f, -3.75f)), leg1Act, PxTransform(PxVec3(0.0f, -2.625f, 0.0f)));
	//}

	////Leg 2
	//{
	//	leg2 = new CW_DynamicActor(scene);
	//	leg2->AddActor(pos + (scale * PxVec3(3.0f, 5.25f, 0.0f)), scale * PxVec3(0.5f, 5.25f, 0.5f), 1.0f, mats->cw_defaultMaterial);
	//	leg2->mainActor->Color(cols->colourStone);
	//	leg2->mainActor->Name("Leg2");
	//	leg2Act = (Actor*)leg2->mainActor;
	//	leg2->SetKinematic(true);
	//	baseJoint2 = new FixedJoint(baseAct, PxTransform(PxVec3(1.5f, 0.01f, -3.75f)), leg2Act, PxTransform(PxVec3(0.0f, -2.625f, 0.0f)));
	//}

	////Leg 3
	//{
	//	leg3 = new CW_DynamicActor(scene);
	//	leg3->AddActor(pos + (scale * PxVec3(-3.0f, 5.25f, 15.0f)), scale * PxVec3(0.5f, 5.25f, 0.5f), 1.0f, mats->cw_defaultMaterial);
	//	leg3->mainActor->Color(cols->colourStone);
	//	leg3->mainActor->Name("Leg3");
	//	leg3Act = (Actor*)leg3->mainActor;
	//	leg3->SetKinematic(true);
	//	baseJoint3 = new FixedJoint(baseAct, PxTransform(PxVec3(-1.5f, 0.01f, 3.75f)), leg3Act, PxTransform(PxVec3(0.0f, -2.625f, 0.0f)));
	//}

	////Leg 4
	//{
	//	leg4 = new CW_DynamicActor(scene);
	//	leg4->AddActor(pos + (scale * PxVec3(3.0f, 5.25f, 15.0f)), scale * PxVec3(0.5f, 5.25f, 0.5f), 1.0f, mats->cw_defaultMaterial);
	//	leg4->mainActor->Color(cols->colourStone);
	//	leg4->mainActor->Name("Leg4");
	//	leg4Act = (Actor*)leg4->mainActor;
	//	leg4->SetKinematic(true);
	//	baseJoint4 = new FixedJoint(baseAct, PxTransform(PxVec3(1.5f, 0.01f, 3.75f)), leg4Act, PxTransform(PxVec3(0.0f, -2.625f, 0.0f)));
	//}

	//Rope1
	{
		ropeAnchor1 = new CW_DynamicActor(scene);
		ropeAnchor1->AddActor(pos + (scale * PxVec3(-3.0f, 11.0f, 0.0f)), scale * PxVec3(0.5f, 0.5f, 0.5f), 1.0f, mats->cw_defaultMaterial);
		ropeAnchor1->mainActor->Color(cols->colourWood);
		ropeAnchor1->mainActor->Name("RopeAnchor1");
		ropeAnchor1->SetKinematic(true);
		ropeAnchor1->mainActor->GetShape(0)->setFlag(PxShapeFlag::eSIMULATION_SHAPE, false);
		ropeA1Act = (Actor*)ropeAnchor1->mainActor;
		rope1 = new CW_DynamicActor(scene);
		rope1->AddActor(pos + (scale * PxVec3(-2.0f, 11.0f, 5.0f)), scale * PxVec3(0.5f, 0.5f, 5.0f), 1.0f, mats->cw_defaultMaterial);
		rope1->mainActor->Color(cols->colourRope);
		rope1->mainActor->Name("Rope1");
		//rope1->mainActor->GetShape(0)->setFlag(PxShapeFlag::eSIMULATION_SHAPE, false);
		rope1Act = (Actor*)rope1->mainActor;
		
		//legJoint1 = new FixedJoint(leg1Act, PxTransform(scale * PxVec3(0.0f, 5.25f, 0.0f)), ropeA1Act, PxTransform(scale * PxVec3(0.0f, -0.5f, 0.0f)));

		jointAnchor1 = new RevoluteJoint(ropeA1Act, PxTransform(scale * PxVec3(0.5f, 0.0f, 0.0f)), rope1Act, PxTransform(scale * PxVec3(-0.5f, 0.0f, 4.5f)));
		jointAnchor1->SetLimits(-PxPi / 2, -PxPi / 2);
		jA1 = (PxRevoluteJoint*)jointAnchor1->Get();
	}

	//Rope2
	{
		ropeAnchor2 = new CW_DynamicActor(scene);
		ropeAnchor2->AddActor(pos + (scale * PxVec3(3.0f, 11.0f, 0.0f)), scale * PxVec3(0.5f, 0.5f, 0.5f), 1.0f, mats->cw_defaultMaterial);
		ropeAnchor2->mainActor->Color(cols->colourWood);
		ropeAnchor2->mainActor->Name("RopeAnchor2");
		ropeAnchor2->SetKinematic(true);
		ropeAnchor2->mainActor->GetShape(0)->setFlag(PxShapeFlag::eSIMULATION_SHAPE, false);
		ropeA2Act = (Actor*)ropeAnchor2->mainActor;

		rope2 = new CW_DynamicActor(scene);
		rope2->AddActor(pos + (scale * PxVec3(2.0f, 11.0f, 5.0f)), scale * PxVec3(0.5f, 0.5f, 5.0f), 1.0f, mats->cw_defaultMaterial);
		rope2->mainActor->Color(cols->colourRope);
		rope2->mainActor->Name("Rope2");
		//rope2->mainActor->GetShape(0)->setFlag(PxShapeFlag::eSIMULATION_SHAPE, false);
		rope2Act = (Actor*)rope2->mainActor;

		//legJoint2 = new FixedJoint(leg2Act, PxTransform(scale * PxVec3(0.0f, 5.25f, 0.0f)), ropeA2Act, PxTransform(scale * PxVec3(0.0f, -0.5f, 0.0f)));

		jointAnchor2 = new RevoluteJoint(ropeA2Act, PxTransform(scale * PxVec3(-0.5f, 0.0f, 0.0f)), rope2Act, PxTransform(scale * PxVec3(0.5f, 0.0f, 4.5f)));
		jointAnchor2->SetLimits(-PxPi / 2, -PxPi / 2);
		jA2 = (PxRevoluteJoint*)jointAnchor2->Get();
	}

	//Rope3
	{
		ropeAnchor3 = new CW_DynamicActor(scene);
		ropeAnchor3->AddActor(pos + (scale * PxVec3(-3.0f, 11.0f, 15.0f)), scale * PxVec3(0.5f, 0.5f, 0.5f), 1.0f, mats->cw_defaultMaterial);
		ropeAnchor3->mainActor->Color(cols->colourWood);
		ropeAnchor3->mainActor->Name("RopeAnchor3");
		ropeAnchor3->SetKinematic(true);
		ropeAnchor3->mainActor->GetShape(0)->setFlag(PxShapeFlag::eSIMULATION_SHAPE, false);
		ropeA3Act = (Actor*)ropeAnchor3->mainActor;

		rope3 = new CW_DynamicActor(scene);
		rope3->AddActor(pos + (scale * PxVec3(-2.0f, 11.0f, 20.0f)), scale * PxVec3(0.5f, 0.5f, 5.0f), 1.0f, mats->cw_defaultMaterial);
		rope3->mainActor->Color(cols->colourRope);
		rope3->mainActor->Name("Rope3");
		//rope3->mainActor->GetShape(0)->setFlag(PxShapeFlag::eSIMULATION_SHAPE, false);
		rope3Act = (Actor*)rope3->mainActor;

		//legJoint3 = new FixedJoint(leg3Act, PxTransform(scale * PxVec3(0.0f, 5.25f, 0.0f)), ropeA3Act, PxTransform(scale * PxVec3(0.0f, -0.5f, 0.0f)));
		
		jointAnchor3 = new RevoluteJoint(ropeA3Act, PxTransform(scale * PxVec3(0.5f, 0.0f, 0.0f)), rope3Act, PxTransform(scale * PxVec3(-0.5f, 0.0f, 4.5f)));
		jointAnchor3->SetLimits(-PxPi / 2, -PxPi / 2);
		jA3 = (PxRevoluteJoint*)jointAnchor3->Get();
	}

	//Rope4
	{
		ropeAnchor4 = new CW_DynamicActor(scene);
		ropeAnchor4->AddActor(pos + (scale * PxVec3(3.0f, 11.0f, 15.0f)), scale * PxVec3(0.5f, 0.5f, 0.5f), 1.0f, mats->cw_defaultMaterial);
		ropeAnchor4->mainActor->Color(cols->colourWood);
		ropeAnchor4->mainActor->Name("RopeAnchor4");
		ropeAnchor4->SetKinematic(true);
		ropeAnchor4->mainActor->GetShape(0)->setFlag(PxShapeFlag::eSIMULATION_SHAPE, false);
		ropeA4Act = (Actor*)ropeAnchor4->mainActor;
		
		rope4 = new CW_DynamicActor(scene);
		rope4->AddActor(pos + (scale * PxVec3(2.0f, 11.0f, 20.0f)), scale * PxVec3(0.5f, 0.5f, 5.0f), 1.0f, mats->cw_defaultMaterial);
		rope4->mainActor->Color(cols->colourRope);
		rope4->mainActor->Name("Rope4");
		//rope4->mainActor->GetShape(0)->setFlag(PxShapeFlag::eSIMULATION_SHAPE, false);
		rope4Act = (Actor*)rope4->mainActor;

		//legJoint4 = new FixedJoint(leg4Act, PxTransform(scale * PxVec3(0.0f, 5.25f, 0.0f)), ropeA4Act, PxTransform(scale * PxVec3(0.0f, -0.5f, 0.0f)));

		jointAnchor4 = new RevoluteJoint(ropeA4Act, PxTransform(scale * PxVec3(-0.5f, 0.0f, 0.0f)), rope4Act, PxTransform(scale * PxVec3(0.5f, 0.0f, 4.5f)));
		jointAnchor4->SetLimits(-PxPi / 2, -PxPi / 2);
		jA4 = (PxRevoluteJoint*)jointAnchor4->Get();
	}

	//Ram, English Oak Density shown as 740kg/m3, set as 7.4 to avoid issues
	{
		ram = new CW_DynamicActor(scene);
		ram->AddActor(pos + (scale * PxVec3(0.0f, 11.0f, 15.0f)), scale * PxVec3(1.5f, 1.5f, 7.5f), 7.40f, mats->cw_woodMaterial);
		ram->mainActor->Color(cols->colourWood);		
		ram->mainActor->Name("Ram");
		ramAct = (Actor*)ram->mainActor;
		ramBody = (PxRigidBody*)ram->mainActor->Get();

		//Attach Ropes
		RevoluteJoint joint(rope1Act, PxTransform(scale * PxVec3(-0.5f, 0.0f, -5.0f)), ramAct, PxTransform(scale * PxVec3(-2.5f, 0.0f, -7.5f)));

		RevoluteJoint joint2(rope2Act, PxTransform(scale * PxVec3(0.5f, 0.0f, -5.0f)), ramAct, PxTransform(scale * PxVec3(2.5f, 0.0f, -7.5f)));

		RevoluteJoint joint3(rope3Act, PxTransform(scale * PxVec3(-0.5f, 0.0f, -5.0f)), ramAct, PxTransform(scale * PxVec3(-2.5f, 0.0f, 7.5f)));

		RevoluteJoint joint4(rope4Act, PxTransform(scale * PxVec3(0.5f, 0.0f, -5.0f)), ramAct, PxTransform(scale * PxVec3(2.5f, 0.0f, 7.5f)));

		//ram->mainActor->SetKinematic(true);
	}

	//Disable Grav (testing)
	{
		rope1->mainActor->GetShape(0)->getActor()->setActorFlag(PxActorFlag::eDISABLE_GRAVITY, true);
		rope2->mainActor->GetShape(0)->getActor()->setActorFlag(PxActorFlag::eDISABLE_GRAVITY, true);
		rope3->mainActor->GetShape(0)->getActor()->setActorFlag(PxActorFlag::eDISABLE_GRAVITY, true);
		rope4->mainActor->GetShape(0)->getActor()->setActorFlag(PxActorFlag::eDISABLE_GRAVITY, true);		
		
		ropeAnchor1->mainActor->GetShape(0)->getActor()->setActorFlag(PxActorFlag::eDISABLE_GRAVITY, true);
		ropeAnchor2->mainActor->GetShape(0)->getActor()->setActorFlag(PxActorFlag::eDISABLE_GRAVITY, true);
		ropeAnchor3->mainActor->GetShape(0)->getActor()->setActorFlag(PxActorFlag::eDISABLE_GRAVITY, true);
		ropeAnchor4->mainActor->GetShape(0)->getActor()->setActorFlag(PxActorFlag::eDISABLE_GRAVITY, true);
	}

	//ChangeGravity(true);
}

void PhysicsEngine::BatteringRam::AddForce(PxReal forceToAdd)
{
	//ramBody->addForce(PxVec3(-forceToAdd, 0.0f, 0.0f));
}

void PhysicsEngine::BatteringRam::ChangeGravity(bool gravityInActive)
{
	ram->mainActor->GetShape(0)->getActor()->setActorFlag(PxActorFlag::eDISABLE_GRAVITY, gravityInActive);
}

void PhysicsEngine::BatteringRam::MoveRamPressed(PxReal angularVelocity, bool limited)
{
	ram->SetKinematic(false);
	ram->mainActor->GetShape(0)->getActor()->setActorFlag(PxActorFlag::eDISABLE_GRAVITY, true);		
	jointAnchor1->SetLimits(-PxPi / 2, 0);
	jointAnchor2->SetLimits(-PxPi / 2, 0);
	jointAnchor3->SetLimits(-PxPi / 2, 0);
	jointAnchor4->SetLimits(-PxPi / 2, 0);
	jointAnchor1->DriveVelocity(angularVelocity);
	jointAnchor2->DriveVelocity(angularVelocity);
	jointAnchor3->DriveVelocity(angularVelocity);
	jointAnchor4->DriveVelocity(angularVelocity);

	jA1->setRevoluteJointFlag(PxRevoluteJointFlag::eLIMIT_ENABLED, limited);
	jA2->setRevoluteJointFlag(PxRevoluteJointFlag::eLIMIT_ENABLED, limited);
	jA3->setRevoluteJointFlag(PxRevoluteJointFlag::eLIMIT_ENABLED, limited);
	jA4->setRevoluteJointFlag(PxRevoluteJointFlag::eLIMIT_ENABLED, limited);
}

void PhysicsEngine::BatteringRam::MoveRamReleased()
{
	ram->mainActor->GetShape(0)->getActor()->setActorFlag(PxActorFlag::eDISABLE_GRAVITY, false);
	jointAnchor1->DriveVelocity(0);
	jointAnchor2->DriveVelocity(0);
	jointAnchor3->DriveVelocity(0);
	jointAnchor4->DriveVelocity(0);
	ram->SetKinematic(true);
}

void PhysicsEngine::BatteringRam::DropRam(bool limited)
{
	//TODO disable motors, if not, create timed obstacles to create some degree of challenge to scoring try?
	ram->SetKinematic(false);
	ram->mainActor->GetShape(0)->getActor()->setActorFlag(PxActorFlag::eDISABLE_GRAVITY, false);
	jointAnchor1->SetLimits(-PxPi / 2, 0);
	jointAnchor2->SetLimits(-PxPi / 2, 0);
	jointAnchor3->SetLimits(-PxPi / 2, 0);
	jointAnchor4->SetLimits(-PxPi / 2, 0);
	jointAnchor1->DriveVelocity(-ramSpeed);
	jointAnchor2->DriveVelocity(-ramSpeed);
	jointAnchor3->DriveVelocity(-ramSpeed);
	jointAnchor4->DriveVelocity(-ramSpeed);
	jA1->setRevoluteJointFlag(PxRevoluteJointFlag::eLIMIT_ENABLED, limited);
	jA2->setRevoluteJointFlag(PxRevoluteJointFlag::eLIMIT_ENABLED, limited);
	jA3->setRevoluteJointFlag(PxRevoluteJointFlag::eLIMIT_ENABLED, limited);
	jA4->setRevoluteJointFlag(PxRevoluteJointFlag::eLIMIT_ENABLED, limited);
}

void PhysicsEngine::BatteringRam::ChangeSpeed(float speedChange, int extreme)
{
	if (extreme)
	{
		speedChange *= pow(extremeMultiplier, extreme);

		PxReal speed = ramSpeed + speedChange;

		if (speed > maxSpeed * extremeMultiplier|| speed < minSpeed * extremeMultiplier)
		{
			cout << "Exceeds Speed Range" << endl;
		}
		else
		{
			ramSpeed = speed;
			cout << "New Speed: " << ramSpeed << endl;
		}
	}
	else
	{
		PxReal speed = ramSpeed + speedChange;

		if (speed > maxSpeed || speed < minSpeed)
		{
			cout << "Exceeds Speed Range" << endl;
		}
		else
		{
			ramSpeed = speed;
			cout << "New Speed: " << ramSpeed << endl;
		}
	}

	
}

PhysicsEngine::Posts::Posts(Scene * scene, PxVec3 pos, PxPhysics * phys, PxReal scale)
{
	physics = phys;
	mats = new DefaultMats(physics);
	cols = new Colours();

	//6 metres apart, 8 metres tall, crossbar at 3m, 0.25m radius
	posts = new CompoundShape(PxTransform(pos));

	//FirstPost
	{
		//pos 0,4,0

		//scale 0.25, 8, 0.25

		posts->AddShape(scale * PxVec3(-3.0f, 4.0f, 0.0f), PxQuat(0.0f, 0.0f, 0.0f, 0.0f),scale * PxVec3(0.25f, 8.0f, 0.25f), 1.0f, mats->cw_defaultMaterial);
		//posts->GetShape(0)->getActor()->co;

		//DynamicActor* act = 
	}

	//SecondPost
	{
		//pos 6,4,0

		//scale 0.25, 8, 0.25

		posts->AddShape(scale * PxVec3(3.0f, 4.0f, 0.0f), PxQuat(0.0f, 0.0f, 0.0f, 0.0f), scale * PxVec3(0.25f, 8.0f, 0.25f), 1.0f, mats->cw_defaultMaterial);
	}

	//CrossBar
	{
		//pos 3,3,0

		//scale 8, 0.25, 0.25

		posts->AddShape(scale * PxVec3(0.0f, 3.0f, 0.0f), PxQuat(0.0f, 0.0f, 0.0f, 0.0f), scale * PxVec3(3.0f, 0.25f, 0.25f), 1.0f, mats->cw_defaultMaterial);
	}

	//Goal Trigger
	{
		goalTrigger = new CW_DynamicActor(scene);
		goalTrigger->AddActor(pos + (scale * PxVec3(0.0f, 7.5f, 0.0f)), scale / 2  * PxVec3(5.25f, 8.0f, 0.25f), 1.0f, mats->cw_defaultMaterial);
		//goalTrigger->mainActor->vis
		goalTrigger->mainActor->Color(cols->colourGoalTrigger);
		goalTrigger->mainActor->Name("GoalTrigger");
		goalTrigger->SetKinematic(true); 
		goalTrigger->SetTrigger(true);
	}

	//Goal Cloth
	{
		goalCloth = new Cloth(PxTransform(pos + (scale * PxVec3(-3.25f, 8.0f, 0.0f)), PxQuat(PxPi/2, PxVec3(0.0f, 0.0f, 1.0f))), scale * PxVec2(3.0f, 3.0f), 20, 20);
		//goalCloth = new Cloth(PxTransform(pos + (scale * PxVec3(-3.0f, 3.0f, 0.0f))), scale * PxVec2(6.0f, 6.0f), 10, 10);
		goalCloth->Color(cols->colourMage);
		((PxCloth*)goalCloth->clothAct)->setExternalAcceleration(PxVec3(-10.0f,0.0f, 0.0f));
		scene->Add(goalCloth);

		goalCloth2 = new Cloth(PxTransform(pos + (scale * PxVec3(3.25f, 8.0f, 0.0f)), PxQuat(PxPi / 2, PxVec3(0.0f, 0.0f, 1.0f))), scale * PxVec2(3.0f, 3.0f), 20, 20);
		//goalCloth = new Cloth(PxTransform(pos + (scale * PxVec3(-3.0f, 3.0f, 0.0f))), scale * PxVec2(6.0f, 6.0f), 10, 10);
		goalCloth2->Color(cols->colourMage);
		((PxCloth*)goalCloth2->clothAct)->setExternalAcceleration(PxVec3(10.0f, 0.0f, 0.0f));
		scene->Add(goalCloth2);
	}

	posts->SetKinematic(true);
	postBody = (PxRigidBody*)posts->Get();
	scene->Add(posts);
}

void PhysicsEngine::Posts::AlterWind(PxReal windValue)
{
	((PxCloth*)goalCloth->clothAct)->setExternalAcceleration(PxVec3(windValue, 0.0f, 0.0f));
	((PxCloth*)goalCloth2->clothAct)->setExternalAcceleration(PxVec3(-windValue, 0.0f, 0.0f));
}

PhysicsEngine::RugbyBall::RugbyBall(Scene * scene, PxVec3 pos, PxPhysics * phys, PxReal scale, PxReal density)
{
	physics = phys;
	mats = new DefaultMats(physics);
	cols = new Colours();

	ball = new CW_DynamicActor(scene);
	ball->AddActor(pos + (scale * PxVec3(0.0f, 0.0f, 0.0f)), Ball, scale * 5/** baseScale*/, density, mats->cw_rubberMaterial);	
	//ball->AddActor(pos + (scale * PxVec3(0.0f, 0.0f, 0.0f)), scale * baseScale, density, mats->cw_rubberMaterial);	
	ball->mainActor->Color(cols->colourWood);
	//ball->mainActor->SetKinematic(true);
	ball->mainActor->Name("RugbyBall");
	ballBody = (PxRigidBody*)ball->mainActor->Get();
	startPos = ballBody->getGlobalPose().p;
	PxReal yRot = 0.0f;
	ballBody->setGlobalPose(PxTransform(startPos, PxQuat(yRot, PxVec3(0.0f,1.0f,0.0f))));

	ballAct = (Actor*)ball->mainActor;
	//ballBody->setRigidBodyFlag(PxRigidBodyFlag::eENABLE_CCD, true);
}

void PhysicsEngine::RugbyBall::ResetPosition()
{
	PxReal yRot = 0.0f;
	ballBody->setGlobalPose(PxTransform(startPos, PxQuat(yRot, PxVec3(0.0f, 1.0f, 0.0f))));
	ballBody->setLinearVelocity(PxVec3(0.0f, 0.0f, 0.0f));
	ballBody->setAngularVelocity(PxVec3(0.0f, 0.0f, 0.0f));
}

PhysicsEngine::WindMage::WindMage(Scene * scene, PxVec3 pos, PxPhysics * phys, PxReal scale)
{
	physics = phys;
	mats = new DefaultMats(physics);
	cols = new Colours();

	mage = new CW_DynamicActor(scene);
	mage->AddActor(pos + (scale * PxVec3(0.0f, 1.0f, 0.0f)), scale * PxVec3(1.0f, 2.0f, 1.0f), 500.0f, mats->cw_defaultMaterial);
	mage->mainActor->Color(cols->colourMage);
	mage->mainActor->Name("Mage");
	mageBody = (PxRigidBody*)mage->mainActor->Get();
	//mageBody->setAngularVelocity(PxVec3(0.0f, 0.1f, 0.0f));
	mageAct = (Actor*)mage->mainActor;

	wind = new CW_DynamicActor(scene);
	wind->AddActor(pos + (scale * PxVec3(0.0f, 2.0f, 0.0f)), scale * PxVec3(4.0f, 1.0f, 1.0f), 0.001f, mats->cw_defaultMaterial);
	wind->mainActor->Color(cols->colourWindTrigger);
	wind->mainActor->Name("Wind");
	wind->SetTrigger(true);
	windAct = (Actor*)wind->mainActor;

	jointAnchor1 = new RevoluteJoint(mageAct, PxTransform(scale * PxVec3(-5.0f, 5.0f, 0.0f)), windAct, PxTransform(scale * PxVec3(0.0f, 0.0f, 0.0f), PxQuat(-7 * PxPi / 8, PxVec3(0.0f, 0.0f, 1.0f))));
	jointAnchor1->SetLimits(-7* PxPi / 8, -7 * PxPi / 8);
 }



