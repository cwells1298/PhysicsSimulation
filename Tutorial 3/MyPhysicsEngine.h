#pragma once

#include "BasicActors.h"
#include "Actors.h"
#include "DefaultMaterials.h"
#include <iostream>
#include <iomanip>

namespace PhysicsEngine
{
	using namespace std;
	
	//a list of colours: Circus Palette
	static const PxVec3 color_palette[] = {PxVec3(46.f/255.f,9.f/255.f,39.f/255.f),PxVec3(217.f/255.f,0.f/255.f,0.f/255.f),
		PxVec3(255.f/255.f,45.f/255.f,0.f/255.f),PxVec3(255.f/255.f,140.f/255.f,54.f/255.f),PxVec3(4.f/255.f,117.f/255.f,111.f/255.f)};
	   	
	struct FilterGroup
	{
		enum Enum
		{
			ACTOR0		= (1 << 0),
			ACTOR1		= (1 << 1),
			ACTOR2		= (1 << 2)
			//add more if you need
		};
	};

	///A customised collision class, implemneting various callbacks
	class MySimulationEventCallback : public PxSimulationEventCallback
	{
	public:
		//an example variable that will be checked in the main simulation loop
		int goalCount = 0;
		bool goalScored = false;
		bool trigger;		
		string ballName;
		string windName;
		bool addForce = false;
		PxVec3 forceToAdd;

		MySimulationEventCallback() : trigger(false) {}

		///Method called when the contact with the trigger object is detected.
		virtual void onTrigger(PxTriggerPair* pairs, PxU32 count) 
		{
			//you can read the trigger information here
			for (PxU32 i = 0; i < count; i++)
			{
				//filter out contact with the planes
				if (pairs[i].otherShape->getGeometryType() != PxGeometryType::ePLANE)
				{
					//check if eNOTIFY_TOUCH_FOUND trigger
					if (pairs[i].status & PxPairFlag::eNOTIFY_TOUCH_FOUND)
					{
						//cerr << "onTrigger::eNOTIFY_TOUCH_FOUND" << endl;
						trigger = true;

						//Check if object is the rugby ball (only Sphere present in the scene is the rugby ball, only trigger collider present is goal)
						if (pairs[i].otherActor->getName() == ballName && pairs[i].triggerActor->getName() == windName)
						{
							cout << "Ball Hit Wind Spell" << endl;
							PxRigidBody* ballBody = (PxRigidBody*)pairs[i].otherActor;
							PxRigidBody* windBody = (PxRigidBody*)pairs[i].triggerActor;
							
							PxReal forceMag = 150.0f;
							PxQuat forceDirection = windBody->getGlobalPose().q;
							forceToAdd = PxVec3(forceDirection.z,forceDirection.y, forceDirection.x) * forceMag;
							cout << "X: " << forceToAdd.x << "; Y: " << forceToAdd.y << "; Z: " << forceToAdd.z << endl;
							addForce = true;
						}
						else if (pairs[i].otherActor->getName() == ballName)
						{
							cout << "Goal Scored" << endl;
							goalCount += 3;
						}
					}
					//check if eNOTIFY_TOUCH_LOST trigger
					if (pairs[i].status & PxPairFlag::eNOTIFY_TOUCH_LOST)
					{
						//cerr << "onTrigger::eNOTIFY_TOUCH_LOST" << endl;
						trigger = false;
					}
				}
			}
		}

		///Method called when the contact by the filter shader is detected.
		virtual void onContact(const PxContactPairHeader &pairHeader, const PxContactPair *pairs, PxU32 nbPairs) 
		{
			cerr << "Contact found between " << pairHeader.actors[0]->getName() << " " << pairHeader.actors[1]->getName() << endl;

			//check all pairs
			for (PxU32 i = 0; i < nbPairs; i++)
			{
				//check eNOTIFY_TOUCH_FOUND
				if (pairs[i].events & PxPairFlag::eNOTIFY_TOUCH_FOUND)
				{
					cerr << "onContact::eNOTIFY_TOUCH_FOUND" << endl;
				}
				//check eNOTIFY_TOUCH_LOST
				if (pairs[i].events & PxPairFlag::eNOTIFY_TOUCH_LOST)
				{
					cerr << "onContact::eNOTIFY_TOUCH_LOST" << endl;
				}
			}
		}

		virtual void onConstraintBreak(PxConstraintInfo *constraints, PxU32 count) {}
		virtual void onWake(PxActor **actors, PxU32 count) {}
		virtual void onSleep(PxActor **actors, PxU32 count) {}
	};

	//A simple filter shader based on PxDefaultSimulationFilterShader - without group filtering
	static PxFilterFlags CustomFilterShader( PxFilterObjectAttributes attributes0,	PxFilterData filterData0,
		PxFilterObjectAttributes attributes1,	PxFilterData filterData1,
		PxPairFlags& pairFlags,	const void* constantBlock,	PxU32 constantBlockSize)
	{
		// let triggers through
		if(PxFilterObjectIsTrigger(attributes0) || PxFilterObjectIsTrigger(attributes1))
		{
			pairFlags = PxPairFlag::eTRIGGER_DEFAULT;
			return PxFilterFlags();
		}

		pairFlags = PxPairFlag::eCONTACT_DEFAULT;
		//enable continous collision detection
//		pairFlags |= PxPairFlag::eCCD_LINEAR;
		
		
		//customise collision filtering here
		//e.g.

		// trigger the contact callback for pairs (A,B) where 
		// the filtermask of A contains the ID of B and vice versa.
		if((filterData0.word0 & filterData1.word1) && (filterData1.word0 & filterData0.word1))
		{
			//trigger onContact callback for this pair of objects
			pairFlags |= PxPairFlag::eNOTIFY_TOUCH_FOUND;
			pairFlags |= PxPairFlag::eNOTIFY_TOUCH_LOST;
//			pairFlags |= PxPairFlag::eNOTIFY_CONTACT_POINTS;
		}

		return PxFilterFlags();
	};

	///Custom scene class
	class MyScene : public Scene
	{
		vector<RugbyBall*> ball;
		vector<Posts*> postFriendlyTeam;
		vector<Posts*> postOpposingTeam;
		vector<WindMage*> windMage;
		vector<ConvexMesh*> ramp;
		vector<CW_StaticActor*> halfwayLine;
		vector<CW_StaticActor*> frontWall; 
		vector<CW_StaticActor*> leftWall;
		vector<CW_StaticActor*> rightWall;
		vector<CW_StaticActor*> backWall;
		//TODO place ball on knockable plinth (allows vertical force to be applied)

		PxPhysics* physics;
		DefaultMats* mats;
		Colours* colours;
		float pitchScale = 0.5f;
		
		PxU32 previousTimestamp = 0;		
		int frameNum = 0;

		bool limitRotation = true;
		//0 = normal, 1 = 10x, 2 = 100x
		int extremeSpeedStep = 0;
		int maxSpeedStep = 5;
	public:
		//specify your custom filter shader here
		//PxDefaultSimulationFilterShader by default
		MyScene() : Scene(CustomFilterShader) {};		
		MySimulationEventCallback* my_callback;
		PxU32 minTimePerFrame = 99999;
		PxU32 maxTimePerFrame = 0;
		PxU32 averageTimePerFrame = 0;

		vector<BatteringRam*> battRam;
		Plane* plane;

		int pitchNumber = 1;
		float windValue = -20.0f;
		float maxWind = 5.0f;
		float minWind = -5.0f;

		///A custom scene class
		void SetVisualisation()
		{
			px_scene->setVisualizationParameter(PxVisualizationParameter::eSCALE, 1.0f);
			//px_scene->setVisualizationParameter(PxVisualizationParameter::eACTOR_AXES, 1.0f);
			px_scene->setVisualizationParameter(PxVisualizationParameter::eCOLLISION_SHAPES, 1.0f);
			px_scene->setVisualizationParameter(PxVisualizationParameter::eJOINT_LIMITS, 1.0f);
			px_scene->setVisualizationParameter(PxVisualizationParameter::eJOINT_LOCAL_FRAMES, 1.0f);
		}

		//Custom scene initialisation
		virtual void CustomInit() 
		{
			SetVisualisation();			
			physics = GetPhysics();
			GetMaterial()->setDynamicFriction(.2f);
			mats = new DefaultMats(physics);
			colours = new Colours();

			///Initialise and set the customised event callback
			my_callback = new MySimulationEventCallback();
			px_scene->setSimulationEventCallback(my_callback);
			
			plane = new Plane();
			plane->Color(colours->colourGrass);
			Add(plane);
						
			for (int i = 0; i < pitchNumber; i++)
			{
				float xPos = 40.0f * i;

				BatteringRam* newBattRam = new BatteringRam(this, pitchScale * PxVec3(xPos, 0.0f, -16.0f), physics, pitchScale);
				battRam.push_back(newBattRam);
				newBattRam->ramAct->SetupFiltering(FilterGroup::ACTOR1, FilterGroup::ACTOR0);

				RugbyBall* newBall = new RugbyBall(this, pitchScale * PxVec3(xPos, 0.0f, 0.0f), physics, pitchScale, 7.5f);
				my_callback->ballName = newBall->ball->mainActor->Name();
				ball.push_back(newBall);
				//set collision filter flags
				newBall->ballAct->SetupFiltering(FilterGroup::ACTOR0, FilterGroup::ACTOR1);

				Posts* newPostOpposingTeam = new Posts(this, pitchScale * PxVec3(xPos, 4.0f, 50.0f), physics, pitchScale);
				postOpposingTeam.push_back(newPostOpposingTeam);
				Posts* newPostFriendlyTeam = new Posts(this, pitchScale * PxVec3(xPos, 4.0f, -50.0f), physics, pitchScale);
				postFriendlyTeam.push_back(newPostFriendlyTeam);
				WindMage* newWindMage = new WindMage(this, pitchScale * PxVec3(xPos + 6.0f, 0.0, 25.0f), physics, pitchScale);
				my_callback->windName = newWindMage->wind->mainActor->Name();
				windMage.push_back(newWindMage);
				
				//Basic Environment
				{
					//Halfway Line
					{
						CW_StaticActor* newHalfwayLine = new CW_StaticActor(this);
						newHalfwayLine->AddActor(pitchScale * PxVec3(xPos, 0.0f, 0.0f), pitchScale * PxVec3(20.0f, 0.05f, 0.25f), 1.0f, mats->cw_defaultMaterial);
						newHalfwayLine->mainActor->Color(colours->colourGoalPosts);
						newHalfwayLine->mainActor->GetShape(0)->setFlag(PxShapeFlag::eSIMULATION_SHAPE, false);
						halfwayLine.push_back(newHalfwayLine);
					}

					//Front Wall
					{
						CW_StaticActor* newFrontWall = new CW_StaticActor(this);
						newFrontWall->AddActor(pitchScale * PxVec3(xPos, 2.5f, 60.0f), pitchScale * PxVec3(20.0f, 2.5f, 0.25f), 1.0f, mats->cw_defaultMaterial);
						newFrontWall->mainActor->Color(colours->colourStone);
						frontWall.push_back(newFrontWall);
					}

					//Left Wall
					{
						CW_StaticActor* newLeftWall = new CW_StaticActor(this);
						newLeftWall->AddActor(pitchScale * PxVec3(xPos - 20.0f, 2.5f, 0.0f), pitchScale * PxVec3(0.25f, 2.5f, 60.0f), 1.0f, mats->cw_defaultMaterial);
						newLeftWall->mainActor->Color(colours->colourStone);
						leftWall.push_back(newLeftWall);
					}

					//Right Wall
					{
						CW_StaticActor* newRightWall = new CW_StaticActor(this);
						newRightWall->AddActor(pitchScale * PxVec3(xPos + 20.0f, 2.5f, 0.0f), pitchScale * PxVec3(0.25f, 2.5f, 60.0f), 1.0f, mats->cw_defaultMaterial);
						newRightWall->mainActor->Color(colours->colourStone);
						rightWall.push_back(newRightWall);
					}

					//Back Wall
					{
						CW_StaticActor* newBackWall = new CW_StaticActor(this);
						newBackWall->AddActor(pitchScale * PxVec3(xPos, 2.5f, -60.0f), pitchScale * PxVec3(20.0f, 2.5f, 0.25f), 1.0f, mats->cw_defaultMaterial);
						newBackWall->mainActor->Color(colours->colourStone);
						backWall.push_back(newBackWall);
					}
				}

				float rampHeight = 2.0f;
				float rampWidth = 4.0f;
				ConvexMesh* newRamp = CreateWedgeKinematic(PxVec3(xPos, 0.5f * rampHeight, 10.0f), rampWidth, rampHeight, 6.0f, 1.0f, mats->cw_defaultMaterial, pitchScale);
				Add(newRamp);
				ramp.push_back(newRamp);
			}		
		}

		//Custom udpate function
		virtual void CustomUpdate() 
		{			
			for (RugbyBall* i : ball)
			{
				if (i->ballBody->getGlobalPose().p.z > 60.0f * pitchScale)
				{
					i->ResetPosition();
				}

				PxReal mag = i->ballBody->getLinearVelocity().z;

				if (i->ballBody->getGlobalPose().p.z > 0.5f && mag < 1.5f)
				{
					i->ResetPosition();
				}

				if (i->ballBody->getGlobalPose().p.z < 0.0f)
				{
					i->ResetPosition();
				}

				if (my_callback->goalScored)
				{
					i->ResetPosition();
					my_callback->goalScored = false;
				}

				if (my_callback->addForce)
				{
					my_callback->addForce = false;
					i->ballBody->addForce(my_callback->forceToAdd);
				}
			}	
						
			for (WindMage* i : windMage)
			{
				i->mageBody->setAngularVelocity(PxVec3(0.0f, 1.5f, 0.0f));
			}
			if (windValue == -20.0f)
			{
				windValue = -10.0f;
			}
			else
			{
				windValue = -20.0f;					
			}

			//cout << "Wind: " << windValue << endl;
			for (Posts* i : postFriendlyTeam)
			{
				i->AlterWind(windValue);
			}
			for (Posts* i : postOpposingTeam)
			{
				i->AlterWind(windValue);
			}

		}

		/// An example use of key release handling
		void ExampleKeyReleaseHandler()
		{
			cerr << "I am released!" << endl;
		}

		/// An example use of key presse handling
		void ExampleKeyPressHandler()
		{
			cerr << "I am pressed!" << endl;
		}

		void MoveBoxUpKeyPressed()
		{
			cout << "Moving Box Up: Start" << endl;		
		}

		void MoveBoxUpKeyHeld()
		{
			for (BatteringRam* i : battRam)
			{
				i->MoveRamPressed(PxPi / 5, limitRotation);
			}
		}

		void MoveBoxDownKeyPressed()
		{
			cout << "Moving Box Down" << endl;
			
			for (BatteringRam* i : battRam)
			{
				i->MoveRamPressed(-PxPi / 5, limitRotation);
			}
		}

		void MoveBoxKeyReleased()
		{
			cout << "Stopped Moving Box" << endl;
			for (BatteringRam* i : battRam)
			{
				i->MoveRamReleased();
			}
		}

		void IncreaseSpeed()
		{
			cout << "Increasing Ram Speed" << endl;
			for (BatteringRam* i : battRam)
			{
				i->ChangeSpeed(0.05f, extremeSpeedStep);
			}
		}

		void DecreaseSpeed()
		{
			cout << "Decreasing Ram Speed" << endl;
			for (BatteringRam* i : battRam)
			{
				i->ChangeSpeed(-0.05f, extremeSpeedStep);
			}
		}

		void ReleaseRamPressed()
		{
			cout << "Dropping Ram" << endl;

			for (BatteringRam* i : battRam)
			{
				i->DropRam(limitRotation);
			}			
		}

		void ToggleExtremeSpeed()
		{
			int prevStep = extremeSpeedStep;
			extremeSpeedStep++;
			extremeSpeedStep = extremeSpeedStep % maxSpeedStep;

			for (BatteringRam* i : battRam)
			{
				i->ramSpeed /= pow(i->extremeMultiplier, prevStep);
			}

			if (extremeSpeedStep != 0)
			{
				for (BatteringRam* i : battRam)
				{
					i->ramSpeed *= pow(i->extremeMultiplier, extremeSpeedStep);
				}
			}			
		}

		void ToggleRotationLimit()
		{
			limitRotation = !limitRotation;
		}

		void SpawnBall()
		{
			for (size_t i = 0; i < 10; i++)
			{
				RugbyBall* newBall = new RugbyBall(this, pitchScale * PxVec3(0.0f, 0.0f, 0.0f), physics, pitchScale, 7.5f);
				my_callback->ballName = newBall->ball->mainActor->Name();
				ball.push_back(newBall);
			}
		}
	};
}
