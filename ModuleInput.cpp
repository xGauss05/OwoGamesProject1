#include "Globals.h"
#include "Application.h"
#include "ModuleInput.h"
#include "SDL/include/SDL.h"

ModuleInput::ModuleInput(bool startEnabled) : Module(startEnabled) {}

ModuleInput::~ModuleInput() {}

bool ModuleInput::Init() {
	LOG("Init SDL input event system");
	bool ret = true;
	SDL_Init(0);

	if (SDL_InitSubSystem(SDL_INIT_EVENTS) < 0) {
		LOG("SDL_EVENTS could not initialize! SDL_Error: %s\n", SDL_GetError());
		ret = false;
	}

	if (SDL_Init(SDL_INIT_GAMECONTROLLER) != 0) {
		SDL_Log("Unable to initialize SDL controllers: %s", SDL_GetError());
		return false;
	}

	#pragma region Controller initialization

	//Count the numbers of compatible controllers to display it
	int controllerCount = 0;
	for (int i = 0; i < SDL_NumJoysticks(); ++i) { if (SDL_IsGameController(i)) { controllerCount++; } }
	SDL_Log("Controllers found: %i\n", controllerCount);

	for (int i = 0; i < SDL_NumJoysticks(); ++i)
	{
		if (SDL_IsGameController(i))
		{
			SDLcontrollers[i] = SDL_GameControllerOpen(i);

			if (SDLcontrollers[i])
			{
				SDL_Log("Index \'%i\' is a compatible controller, named \'%s\'", i, SDL_GameControllerNameForIndex(i));
				break;
			}
			else
			{
				SDL_Log("Could not open gamecontroller %i: %s\n", i, SDL_GetError());
			}
		}
		else
		{
			SDL_Log("Index \'%i\' is empty\n", i);
		}
	}
	for (size_t i = 0; i < controllerCount; i++)
	{
		if (controllerCount < MAX_CONTROLLERS)
		{
			controllers[i] = new GameController;
		}

		for (size_t j = 0; j < SDL_CONTROLLER_BUTTON_MAX; j++)
		{
			controllers[i]->buttons[j] = KEY_IDLE;
		}
	}

#pragma endregion

	return ret;
}

update_status ModuleInput::PreUpdate() {
	// Read new SDL events, mostly from the window
	SDL_Event event;
	if (SDL_PollEvent(&event)) {
		if (event.type == SDL_QUIT)	return update_status::UPDATE_STOP;
	}

	// Read all keyboard data and update our custom array
	SDL_PumpEvents();
	const Uint8* keyboard = SDL_GetKeyboardState(NULL);
	for (int i = 0; i < MAX_KEYS; ++i) {
		if (keyboard[i])
			keys[i] = (keys[i] == KEY_IDLE) ? KEY_DOWN : KEY_REPEAT;
		else
			keys[i] = (keys[i] == KEY_REPEAT || keys[i] == KEY_DOWN) ? KEY_UP : KEY_IDLE;
	}

	// For each controller available
	for (int i = 0; i < MAX_CONTROLLERS; ++i) {
		if (SDL_IsGameController(i)) {
			controllers[i]->j1_x = SDL_GameControllerGetAxis(SDLcontrollers[i], SDL_CONTROLLER_AXIS_LEFTX);
			controllers[i]->j1_y = SDL_GameControllerGetAxis(SDLcontrollers[i], SDL_CONTROLLER_AXIS_LEFTY);
			controllers[i]->j2_x = SDL_GameControllerGetAxis(SDLcontrollers[i], SDL_CONTROLLER_AXIS_RIGHTX);
			controllers[i]->j2_y = SDL_GameControllerGetAxis(SDLcontrollers[i], SDL_CONTROLLER_AXIS_RIGHTY);
			controllers[i]->LT = SDL_GameControllerGetAxis(SDLcontrollers[i], SDL_CONTROLLER_AXIS_TRIGGERLEFT);
			controllers[i]->RT = SDL_GameControllerGetAxis(SDLcontrollers[i], SDL_CONTROLLER_AXIS_TRIGGERRIGHT);

			//Uint8* gamepad = (Uint8*)SDL_GameControllerEventState(SDL_QUERY);
			for (size_t j = 0; j < SDL_CONTROLLER_BUTTON_MAX; j++)
			{
				//if (gamepad[j])
				if (SDL_GameControllerGetButton(SDLcontrollers[i], (SDL_GameControllerButton)j))
				{
					controllers[i]->buttons[j] = (controllers[i]->buttons[j] == KEY_IDLE) ? KEY_DOWN : KEY_REPEAT;
				}
				else
				{
					controllers[i]->buttons[j] = (controllers[i]->buttons[j] == KEY_REPEAT || (controllers[i]->buttons[j] == KEY_DOWN)) ? KEY_UP : KEY_IDLE;
				}
			}
		}
	}

	return update_status::UPDATE_CONTINUE;
}

bool ModuleInput::CleanUp() {
	LOG("Quitting SDL input event subsystem");

	SDL_QuitSubSystem(SDL_INIT_EVENTS);
	return true;
}
