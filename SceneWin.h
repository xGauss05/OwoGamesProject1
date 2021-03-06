#ifndef __MODULE_SCENEWIN_H__
#define __MODULE_SCENEWIN_H__

#include "Module.h"
#include "Animation.h"

struct SDL_Texture;

class SceneWin : public Module {
public:
	// Constructor
	SceneWin(bool startEnabled);

	// Destructor
	~SceneWin();

	// Called when the module is activated
	// Loads the necessary textures for the map background
	bool Start() override;

	// Called at the middle of the application loop
	// Updates the scene's background animations
	update_status Update() override;

	// Called at the end of the application loop.
	// Performs the render call of all the parts of the scene's background
	update_status PostUpdate() override;

	// Disables the player, the enemies and the powerups.
	bool CleanUp();

public:
	// The scene sprite sheet loaded into an SDL_Texture
	SDL_Texture* bgTexture = nullptr;
	ushort countdown = 10;
	int t1 = 0;
};

#endif // __MODULE_SCENEWIN_H__
