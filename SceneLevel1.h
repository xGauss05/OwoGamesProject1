#ifndef __MODULE_SCENE1_H__
#define __MODULE_SCENE1_H__

#include "Module.h"
#include "Animation.h"

struct SDL_Texture;

class SceneLevel1 : public Module {
public:
	// Constructor
	SceneLevel1(bool startEnabled);

	// Destructor
	~SceneLevel1();

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

	void DrawParallax();

public:
	// The scene sprite sheet loaded into an SDL_Texture
	SDL_Texture* mapTexture = nullptr;

	// The scence paralax texture loaded into an SDL_Texture
	SDL_Texture* parallaxTexture = nullptr;
	
	// Bools to check if the music has changed
	bool isLevelMusic = false;
	bool isContinueMusic = false;
};

#endif // __MODULE_SCENE1_H__
