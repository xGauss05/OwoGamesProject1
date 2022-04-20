#ifndef __APPLICATION_H__
#define __APPLICATION_H__

#include "Globals.h"

#define NUM_MODULES 15

class Module;
class ModuleWindow;
class ModuleInput;
class ModuleTextures;
class ModuleAudio;
class ModulePlayer;
class SceneIntro;
class SceneTitle;
class SceneLevel1;
class SceneWin;
class ModuleParticles;
class ModuleCollisions;
class ModuleRender;
class ModuleEnemies;
class ModulePowerup;
class ModuleFadeToBlack;

class Application {

public:

	// Constructor. Creates all necessary modules for the application
	Application();

	// Destructor. Removes all module objects
	~Application();

	// Initializes all modules
	bool Init();

	// Updates all modules (PreUpdate, Update and PostUpdate)
	update_status Update();

	// Releases all the application data
	bool CleanUp();

public:
	// An array to store all modules
	Module* modules[NUM_MODULES];

	// All the modules stored individually
	ModuleWindow* window = nullptr;
	ModuleInput* input = nullptr;
	ModuleTextures* textures = nullptr;
	ModuleAudio* audio = nullptr;

	ModulePlayer* player = nullptr;
	SceneIntro* intro = nullptr;
	SceneTitle* title = nullptr;
	SceneLevel1* level1 = nullptr;
	SceneWin* win = nullptr;
	ModuleParticles* particles = nullptr;

	ModuleCollisions* collisions = nullptr;

	ModuleRender* render = nullptr;

	ModuleEnemies* enemies = nullptr;
	ModulePowerup* powerups = nullptr;

	ModuleFadeToBlack* fade = nullptr;
};

// Global var made extern for Application ---
extern Application* App;

#endif // __APPLICATION_H__
