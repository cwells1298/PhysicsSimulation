#include "VisualDebugger.h"
#include <vector>
#include "Extras\Camera.h"
#include "Extras\Renderer.h"
#include "Extras\HUD.h"

namespace VisualDebugger
{
	using namespace physx;

	enum RenderMode
	{
		DEBUG,
		NORMAL,
		BOTH
	};

	enum HUDState
	{
		EMPTY = 0,
		HELP = 1,
		PAUSE = 2,
		STATS = 3
	};

	//function declarations
	void KeyHold();
	void KeySpecial(int key, int x, int y);
	void KeyRelease(unsigned char key, int x, int y);
	void KeyPress(unsigned char key, int x, int y);

	void motionCallback(int x, int y);
	void mouseCallback(int button, int state, int x, int y);
	void exitCallback(void);

	void RenderScene();
	void ToggleRenderMode();
	void HUDInit();

	///simulation objects
	Camera* camera;
	PhysicsEngine::MyScene* scene;
	PxReal delta_time = 1.f/60.f;
	PxReal delta_timeExtreme = 1.f/1.f;
	PxReal delta_times[8] = { 1.f / 240.f, 1.f / 120.f, 1.f / 60.f, 1.f / 30.f, 1.f / 15.f, 1.f / 7.5f, 1.f / 3.25f, 1.f / 1.625f };
	int currentDelta = 2;
	PxReal gForceStrength = 20;
	RenderMode render_mode = NORMAL;
	const int MAX_KEYS = 256;
	bool key_state[MAX_KEYS];
	bool hud_show = true;
	HUD hud;
	HUD scoreHud;
	HUD statHud;
	int currentScore = 0;
	int currentSecondFrameCount = 0;
	int totalFrameCount = 0;
	int previousTimestamp = 0;
	double maxFrameRate = 0.0;
	double minFrameRate = 999999.0;
	double averageFPS = 0.0;
	double currentFrameRate = 0.0;
	bool showStats = false;

	//Init the debugger
	void Init(const char *window_name, int width, int height)
	{
		///Init PhysX
		PhysicsEngine::PxInit();
		scene = new PhysicsEngine::MyScene();
		scene->Init();

		///Init renderer
		Renderer::BackgroundColor(PxVec3(150.f/255.f,150.f/255.f,150.f/255.f));
		Renderer::SetRenderDetail(40);
		Renderer::InitWindow(window_name, width, height);
		Renderer::Init();

		camera = new Camera(PxVec3(-5.0f, 5.0f, -10.0f), PxVec3(0.f,-.1f,1.f), 7.5f);

		//initialise HUD
		HUDInit();

		///Assign callbacks
		//render
		glutDisplayFunc(RenderScene);

		//keyboard
		glutKeyboardFunc(KeyPress);
		glutSpecialFunc(KeySpecial);
		glutKeyboardUpFunc(KeyRelease);

		//mouse
		glutMouseFunc(mouseCallback);
		glutMotionFunc(motionCallback);

		//exit
		atexit(exitCallback);

		//init motion callback
		motionCallback(0,0);
	}

	void HUDInit()
	{
		//initialise HUD
		//add an empty screen
		hud.AddLine(EMPTY, "");
		//add a help screen
		//hud.AddLine(HELP, " Simulation");
		//hud.AddLine(HELP, "    F9 - select next actor");
		//hud.AddLine(HELP, "    F10 - pause");
		//hud.AddLine(HELP, "    F12 - reset");
		//hud.AddLine(HELP, "");
		//hud.AddLine(HELP, " Display");
		//hud.AddLine(HELP, "    F5 - help on/off");
		//hud.AddLine(HELP, "    F6 - shadows on/off");
		//hud.AddLine(HELP, "    F7 - render mode");
		//hud.AddLine(HELP, "");
		hud.AddLine(HELP, " Camera");
		hud.AddLine(HELP, "    W,S,A,D,Q,Z - forward,backward,left,right,up,down");
		hud.AddLine(HELP, "    mouse + click - change orientation");
		hud.AddLine(HELP, "    F8 - reset view");
		hud.AddLine(HELP, "");
	/*	hud.AddLine(HELP, " Force (applied to the selected actor)");
		hud.AddLine(HELP, "    I,K,J,L,U,M - forward,backward,left,right,up,down");*/
		hud.AddLine(HELP, "");
		hud.AddLine(HELP, "Ram Controls");
		hud.AddLine(HELP, "    1 - Move Ram Up");
		hud.AddLine(HELP, "    2 - Move Ram Down");
		hud.AddLine(HELP, "    3 - Release Ram ");
		hud.AddLine(HELP, "    4 - Increase Ram Speed");
		hud.AddLine(HELP, "    5 - Decrease Ram Speed");
		hud.AddLine(HELP, "    P - Show Stats");
		hud.AddLine(HELP, "    O - Toggle Timestep");
		hud.AddLine(HELP, "    I - Toggle Ram Speed Multiplier");
		hud.AddLine(HELP, "    U - Toggle Ram Rotation Limit");
		hud.AddLine(HELP, "    Y - Spawn Additional Ball");

		//add a pause screen
		//hud.AddLine(PAUSE, "");
		//hud.AddLine(PAUSE, "");
		//hud.AddLine(PAUSE, "");
		//hud.AddLine(PAUSE, "   Simulation paused. Press F10 to continue.");
		//set font size for all screens
		hud.FontSize(0.018f);
		//set font color for all screens
		hud.Color(PxVec3(0.f,0.f,0.f));

		statHud.AddLine(EMPTY, "");
		statHud.AddLine(STATS, "");
		statHud.AddLine(STATS, "");
		statHud.AddLine(STATS, "");
		statHud.AddLine(STATS, "");
		statHud.AddLine(STATS, "");
		statHud.AddLine(STATS, "");
		statHud.AddLine(STATS, "");
		statHud.AddLine(STATS, "");
		statHud.AddLine(STATS, "");
		statHud.AddLine(STATS, "");
		statHud.AddLine(STATS, "");
		statHud.AddLine(STATS, "");
		statHud.AddLine(STATS, "");
		statHud.AddLine(STATS, "");
		statHud.AddLine(STATS, "");
		statHud.AddLine(STATS, "");
		statHud.AddLine(STATS, "");
		statHud.AddLine(STATS, "");
		statHud.AddLine(STATS, "");
		statHud.AddLine(STATS, "");
		statHud.AddLine(STATS, "");
		statHud.AddLine(STATS, "");
		statHud.AddLine(STATS, "");
		statHud.AddLine(STATS, "");
		statHud.AddLine(STATS, "");
		statHud.AddLine(STATS, "");
		statHud.AddLine(STATS, "");
		statHud.AddLine(STATS, "");
		statHud.AddLine(STATS, "");
		statHud.AddLine(STATS, "");
		statHud.AddLine(STATS, "");
		statHud.AddLine(STATS, "");
		statHud.AddLine(STATS, "");
		statHud.AddLine(STATS, "");
		statHud.AddLine(STATS, "");

		string currentString = "Current FPS: ";
		stringstream cfr;
		cfr << std::setprecision(2) << std::fixed << currentFrameRate;
		currentString += cfr.str();
		statHud.AddLine(STATS, currentString);
		string averageString = "Average FPS: ";
		stringstream afr;
		afr << std::setprecision(2) << std::fixed << averageFPS;
		averageString += afr.str();
		statHud.AddLine(STATS, averageString);
		string minString = "Min FPS: ";
		stringstream minfr;
		minfr << std::setprecision(2) << std::fixed << minFrameRate;
		minString += minfr.str();
		statHud.AddLine(STATS, minString);
		string maxString = "Max FPS: ";
		stringstream maxfr;
		maxfr << std::setprecision(2) << std::fixed << maxFrameRate;
		maxString += maxfr.str();
		statHud.AddLine(STATS, maxString);
		statHud.Color(PxVec3(0.f, 0.f, 0.f));
				
		//......................................//
		scoreHud.AddLine(HELP, "");
		scoreHud.AddLine(HELP, "");
		scoreHud.AddLine(HELP, "");
		scoreHud.AddLine(HELP, "");
		scoreHud.AddLine(HELP, "");
		scoreHud.AddLine(HELP, "");
		scoreHud.AddLine(HELP, "");
		scoreHud.AddLine(HELP, "");
		scoreHud.AddLine(HELP, "");
		scoreHud.AddLine(HELP, "");
		scoreHud.AddLine(HELP, "");
		scoreHud.AddLine(HELP, "");
		scoreHud.AddLine(HELP, "");
		scoreHud.AddLine(HELP, "");
		scoreHud.AddLine(HELP, "");
		scoreHud.AddLine(HELP, "");
		scoreHud.AddLine(HELP, "");
		scoreHud.AddLine(HELP, "");
		scoreHud.AddLine(HELP, "");
		scoreHud.AddLine(HELP, "");
		scoreHud.AddLine(HELP, "");
		scoreHud.AddLine(HELP, "");
		scoreHud.AddLine(HELP, "");
		scoreHud.AddLine(HELP, "");
		scoreHud.AddLine(HELP, "");
		scoreHud.AddLine(HELP, "");
		scoreHud.AddLine(HELP, "");
		scoreHud.AddLine(HELP, "");
		scoreHud.AddLine(HELP, "");
		scoreHud.AddLine(HELP, "");
		scoreHud.AddLine(HELP, "");
		scoreHud.AddLine(HELP, "");
		scoreHud.AddLine(HELP, "");
		scoreHud.AddLine(HELP, "");
		scoreHud.AddLine(HELP, "");
		scoreHud.AddLine(HELP, "");
		scoreHud.AddLine(HELP, "");
		scoreHud.AddLine(HELP, "");
		scoreHud.AddLine(HELP, "");
		string newScore = "Score: ";
		newScore += to_string(currentScore);
		scoreHud.AddLine(HELP, newScore);

		scoreHud.FontSize(0.025f);
		scoreHud.Color(PxVec3(0.f, 0.f, 0.f));
		scoreHud.ActiveScreen(HELP);
	}

	//Start the main loop
	void Start()
	{ 
		glutMainLoop(); 
	}

	//Render the scene and perform a single simulation step
	void RenderScene()
	{
		currentSecondFrameCount++;
		totalFrameCount++;

		//handle pressed keys
		KeyHold();

		//start rendering
		Renderer::Start(camera->getEye(), camera->getDir());

		if ((render_mode == DEBUG) || (render_mode == BOTH))
		{
			Renderer::Render(scene->Get()->getRenderBuffer());
		}

		if ((render_mode == NORMAL) || (render_mode == BOTH))
		{
			std::vector<PxActor*> actors = scene->GetAllActors();
			if (actors.size())
				Renderer::Render(&actors[0], (PxU32)actors.size());
		}

		//adjust the HUD state
		if (hud_show)
		{
			if (scene->Pause())
			{
				hud.ActiveScreen(PAUSE);
			}
			else 
			{
				hud.ActiveScreen(HELP);
			}

			if (showStats)
			{
				statHud.ActiveScreen(STATS);
			}
			else
			{
				statHud.ActiveScreen(EMPTY);
			}
				
		}
		else
			hud.ActiveScreen(EMPTY);

		//render HUD
		hud.Render();

		/*string goal;
		cin >> goal;*/

		if (scene->my_callback->goalCount != currentScore)
		{
			currentScore = scene->my_callback->goalCount;

			scoreHud.Clear();
			scoreHud.AddLine(HELP, "");
			scoreHud.AddLine(HELP, "");
			scoreHud.AddLine(HELP, "");
			scoreHud.AddLine(HELP, "");
			scoreHud.AddLine(HELP, "");
			scoreHud.AddLine(HELP, "");
			scoreHud.AddLine(HELP, "");
			scoreHud.AddLine(HELP, "");
			scoreHud.AddLine(HELP, "");
			scoreHud.AddLine(HELP, "");
			scoreHud.AddLine(HELP, "");
			scoreHud.AddLine(HELP, "");
			scoreHud.AddLine(HELP, "");
			scoreHud.AddLine(HELP, "");
			scoreHud.AddLine(HELP, "");
			scoreHud.AddLine(HELP, "");
			scoreHud.AddLine(HELP, "");
			scoreHud.AddLine(HELP, "");
			scoreHud.AddLine(HELP, "");
			scoreHud.AddLine(HELP, "");
			scoreHud.AddLine(HELP, "");
			scoreHud.AddLine(HELP, "");
			scoreHud.AddLine(HELP, "");
			scoreHud.AddLine(HELP, "");
			scoreHud.AddLine(HELP, "");
			scoreHud.AddLine(HELP, "");
			scoreHud.AddLine(HELP, "");
			scoreHud.AddLine(HELP, "");
			scoreHud.AddLine(HELP, "");
			scoreHud.AddLine(HELP, "");
			scoreHud.AddLine(HELP, "");
			scoreHud.AddLine(HELP, "");
			scoreHud.AddLine(HELP, "");
			scoreHud.AddLine(HELP, "");
			scoreHud.AddLine(HELP, "");
			scoreHud.AddLine(HELP, "");
			scoreHud.AddLine(HELP, "");
			scoreHud.AddLine(HELP, "");
			scoreHud.AddLine(HELP, "");
			string newScore = "Score: ";
			newScore += to_string(currentScore);
			scoreHud.AddLine(HELP, newScore);
		}

		statHud.Render();
		scoreHud.Render();

		//finish rendering
		Renderer::Finish();

		//perform a single simulation step		
		scene->Update(delta_times[currentDelta]);	

		//Performance analysis
		{
			int currentTimestampMS = glutGet(GLUT_ELAPSED_TIME);

			//If at least a second has passed
			if (currentTimestampMS - previousTimestamp > 1000)
			{				
				double timePerFrame = (currentTimestampMS - previousTimestamp) / 1000.0;
				double framesPerSecond = currentSecondFrameCount / timePerFrame;
				currentSecondFrameCount = 0;
				previousTimestamp = currentTimestampMS;					

				double currentTimestampS = currentTimestampMS / 1000.0;
				averageFPS = totalFrameCount / currentTimestampS;

				if (framesPerSecond > maxFrameRate)
				{
					maxFrameRate = framesPerSecond;
				}

				if (framesPerSecond < minFrameRate)
				{
					minFrameRate = framesPerSecond;
				}

				currentFrameRate = framesPerSecond;

				statHud.Clear();
				statHud.AddLine(EMPTY, "");
				statHud.AddLine(STATS, "");
				statHud.AddLine(STATS, "");
				statHud.AddLine(STATS, "");
				statHud.AddLine(STATS, "");
				statHud.AddLine(STATS, "");
				statHud.AddLine(STATS, "");
				statHud.AddLine(STATS, "");
				statHud.AddLine(STATS, "");
				statHud.AddLine(STATS, "");
				statHud.AddLine(STATS, "");
				statHud.AddLine(STATS, "");
				statHud.AddLine(STATS, "");
				statHud.AddLine(STATS, "");
				statHud.AddLine(STATS, "");
				statHud.AddLine(STATS, "");
				statHud.AddLine(STATS, "");
				statHud.AddLine(STATS, "");
				statHud.AddLine(STATS, "");
				statHud.AddLine(STATS, "");
				statHud.AddLine(STATS, "");
				statHud.AddLine(STATS, "");
				statHud.AddLine(STATS, "");
				statHud.AddLine(STATS, "");
				statHud.AddLine(STATS, "");
				statHud.AddLine(STATS, "");
				statHud.AddLine(STATS, "");
				statHud.AddLine(STATS, "");
				statHud.AddLine(STATS, "");
				statHud.AddLine(STATS, "");
				statHud.AddLine(STATS, "");
				statHud.AddLine(STATS, "");
				statHud.AddLine(STATS, "");
				statHud.AddLine(STATS, "");
				statHud.AddLine(STATS, "");

				string currentString = "Current FPS: ";
				stringstream cfr;
				cfr << std::setprecision(2) << std::fixed << currentFrameRate;
				currentString += cfr.str();
				statHud.AddLine(STATS, currentString);
				string averageString = "Average FPS: ";
				stringstream afr;
				afr << std::setprecision(2) << std::fixed << averageFPS;
				averageString += afr.str();
				statHud.AddLine(STATS, averageString);
				string minString = "Min FPS: ";
				stringstream minfr;
				minfr << std::setprecision(2) << std::fixed << minFrameRate;
				minString += minfr.str();
				statHud.AddLine(STATS, minString);
				string maxString = "Max FPS: ";
				stringstream maxfr;
				maxfr << std::setprecision(2) << std::fixed << maxFrameRate;
				maxString += maxfr.str();
				statHud.AddLine(STATS, maxString);

				string speedString = "Ram Speed: ";
				stringstream speedfr;
				speedfr << std::setprecision(2) << std::fixed << scene->battRam[0]->ramSpeed;
				speedString += speedfr.str();
				statHud.AddLine(STATS, speedString);

				string timeString = "Current Timestep: ";
				stringstream timefr;
				timefr << std::setprecision(6) << std::fixed << delta_times[currentDelta];
				timeString += timefr.str();
				statHud.AddLine(STATS, timeString);
			}
		
		}
	}

	//user defined keyboard handlers
	void UserKeyPress(int key)
	{
		switch (toupper(key))
		{
		//implement your own
		case 'R':
			scene->ExampleKeyPressHandler();
			break;
		case '1':
			scene->MoveBoxUpKeyPressed();
			break;
		case '2':
			scene->MoveBoxDownKeyPressed();
			break;
		case '3':
			scene->ReleaseRamPressed();
			break;		
		case 'P':
			showStats = !showStats;
			break;	
		case 'O':
			currentDelta++;
			currentDelta = currentDelta % 8;
			break;	
		case 'I':
			scene->ToggleExtremeSpeed();
			break;
		case 'U':
			scene->ToggleRotationLimit();
			break;
		case 'Y':
			scene->SpawnBall();
			break;
		default:
			break;
		}
	}

	void UserKeyRelease(int key)
	{
		switch (toupper(key))
		{
		//implement your own
		case 'R':
			scene->ExampleKeyReleaseHandler();
			break;
		case '1':
			scene->MoveBoxKeyReleased();
			break;
		case '2':
			scene->MoveBoxKeyReleased();
			break;
		default:
			break;
		}
	}

	void UserKeyHold(int key)
	{
		switch (toupper(key))
		{
		case '1':
			scene->MoveBoxUpKeyHeld();
			break;
		case '4':
			scene->IncreaseSpeed();
			break;
		case '5':
			scene->DecreaseSpeed();
		default:
			break;
		}
	}

	//handle camera control keys
	void CameraInput(int key)
	{
		switch (toupper(key))
		{
		case 'W':
			camera->MoveForward(delta_time);
			break;
		case 'S':
			camera->MoveBackward(delta_time);
			break;
		case 'A':
			camera->MoveLeft(delta_time);
			break;
		case 'D':
			camera->MoveRight(delta_time);
			break;
		case 'Q':
			camera->MoveUp(delta_time);
			break;
		case 'Z':
			camera->MoveDown(delta_time);
			break;
		default:
			break;
		}
	}

	//handle force control keys
	void ForceInput(int key)
	{
		//if (!scene->GetSelectedActor())
		//	return;

		//switch (toupper(key))
		//{
		//	// Force controls on the selected actor
		//case 'I': //forward
		//	scene->GetSelectedActor()->addForce(PxVec3(0,0,-1)*gForceStrength);
		//	break;
		//case 'K': //backward
		//	scene->GetSelectedActor()->addForce(PxVec3(0,0,1)*gForceStrength);
		//	break;
		//case 'J': //left
		//	scene->GetSelectedActor()->addForce(PxVec3(-1,0,0)*gForceStrength);
		//	break;
		//case 'L': //right
		//	scene->GetSelectedActor()->addForce(PxVec3(1,0,0)*gForceStrength);
		//	break;
		//case 'U': //up
		//	scene->GetSelectedActor()->addForce(PxVec3(0,1,0)*gForceStrength);
		//	break;
		//case 'M': //down
		//	scene->GetSelectedActor()->addForce(PxVec3(0,-1,0)*gForceStrength);
		//	break;
		//default:
		//	break;
		//}
	}

	///handle special keys
	void KeySpecial(int key, int x, int y)
	{
		//simulation control
		switch (key)
		{
			//display control
		case GLUT_KEY_F5:
			//hud on/off
			hud_show = !hud_show;
			break;
		case GLUT_KEY_F6:
			//shadows on/off
			Renderer::ShowShadows(!Renderer::ShowShadows());
			break;
		case GLUT_KEY_F7:
			//toggle render mode
			ToggleRenderMode();
			break;
		case GLUT_KEY_F8:
			//reset camera view
			camera->Reset();
			break;

			//simulation control
		case GLUT_KEY_F9:
			//select next actor
			scene->SelectNextActor();
			break;
		case GLUT_KEY_F10:
			//toggle scene pause
			scene->Pause(!scene->Pause());
			break;
		case GLUT_KEY_F12:
			//resect scene
			scene->Reset();
			break;
		default:
			break;
		}
	}

	//handle single key presses
	void KeyPress(unsigned char key, int x, int y)
	{
		//do it only once
		if (key_state[key] == true)
			return;

		key_state[key] = true;

		//exit
		if (key == 27)
			exit(0);

		UserKeyPress(key);
	}

	//handle key release
	void KeyRelease(unsigned char key, int x, int y)
	{
		key_state[key] = false;
		UserKeyRelease(key);
	}

	//handle holded keys
	void KeyHold()
	{
		for (int i = 0; i < MAX_KEYS; i++)
		{
			if (key_state[i]) // if key down
			{
				CameraInput(i);
				ForceInput(i);
				UserKeyHold(i);
			}
		}
	}

	///mouse handling
	int mMouseX = 0;
	int mMouseY = 0;

	void motionCallback(int x, int y)
	{
		int dx = mMouseX - x;
		int dy = mMouseY - y;

		camera->Motion(dx, dy, delta_time);

		mMouseX = x;
		mMouseY = y;
	}

	void mouseCallback(int button, int state, int x, int y)
	{
		mMouseX = x;
		mMouseY = y;
	}

	void ToggleRenderMode()
	{
		if (render_mode == NORMAL)
			render_mode = DEBUG;
		else if (render_mode == DEBUG)
			render_mode = BOTH;
		else if (render_mode == BOTH)
			render_mode = NORMAL;
	}

	///exit callback
	void exitCallback(void)
	{
		delete camera;
		delete scene;
		PhysicsEngine::PxRelease();
	}
}

