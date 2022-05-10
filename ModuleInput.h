#ifndef __MODULE_INPUT_H__
#define __MODULE_INPUT_H__

#include "SDL/include/SDL.h"
#include "SDL_image/include/SDL_image.h"
#pragma comment( lib, "SDL/libx86/SDL2.lib" )
#pragma comment( lib, "SDL/libx86/SDL2main.lib" )
#pragma comment( lib, "SDL_image/libx86/SDL2_image.lib" )


#include "SDL_Mixer/include/SDL_mixer.h"




#include "Module.h"
#include "Globals.h"

#define MAX_KEYS	256
#define MAX_CONTROLLERS 8

enum KEY_STATE {
	KEY_IDLE,
	KEY_DOWN,
	KEY_REPEAT,
	KEY_UP
};

struct GameController {
	float j1_x, j1_y, j2_x, j2_y, LT, RT;
	KEY_STATE buttons[SDL_CONTROLLER_BUTTON_MAX];
};

class ModuleInput : public Module {
public:
	// Constructor
	ModuleInput(bool startEnabled);

	// Destructor
	~ModuleInput();

	// Called on application start.
	// Initializes the SDL system for input detection
	bool Init() override;

	// Called at the beginning of the application loop
	// Updates all input data received from SDL
	update_status PreUpdate() override;

	// Called on application exit.
	// Uninitializes the SDL system for input detection
	bool CleanUp() override;

public:
	// An array to fill in the state of all the keyboard keys
	KEY_STATE keys[MAX_KEYS] = { KEY_IDLE };

	SDL_GameController* SDLcontrollers[MAX_CONTROLLERS];
	GameController* controllers[MAX_CONTROLLERS];
};

#endif // __ModuleInput_H__
