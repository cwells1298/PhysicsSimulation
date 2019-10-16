#pragma once

#include "MyPhysicsEngine.h"
#include <sstream>

namespace VisualDebugger
{
	using namespace physx;

	///Init visualisation
	void Init(const char *window_name, int width=512, int height=512);

	///Start visualisation
	void Start();
}

