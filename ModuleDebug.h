#ifndef __MODULE_DEBUG_H__
#define __MODULE_DEBUG_H__

#include "Module.h"

#define DEBUG_BOX 225

class ModuleDebug : public Module {
public:
	// Constructor
	ModuleDebug(bool startEnabled);

	// Destructor
	~ModuleDebug();

	// Called at the middle of the application loop
	// Switches the debug mode on/off
	update_status Update();

	// Called at the end of the application loop
	// Draw all functionality (if debug mode is enabled)
	update_status PostUpdate();

	// Draws all existing colliders with some transparency
	void DebugDraw();

private:

	// Simple debugging flag to draw all colliders
	bool debug;

	bool variables = false;
	bool camLimits = false;
	bool spawn = false;
};

#endif // __MODULE_DEBUG_H__
