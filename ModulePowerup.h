#ifndef __MODULE_POWERUP_H__
#define __MODULE_POWERUP_H__

#include "Module.h"
#include "Animation.h"
#include "p2Point.h"

struct SDL_Texture;
struct Collider;


class ModulePowerup : public Module {
public:
	// Constructor
	ModulePowerup();

	// Destructor
	~ModulePowerup();

	// Called when the module is activated
	// Loads the necessary textures for the player
	bool Start() override;

	// Called at the middle of the application loop
	// Processes new input and handles player movement
	update_status Update() override;

	// Called at the end of the application loop
	// Performs the render call of the player sprite
	update_status PostUpdate() override;

	// Collision callback, called when the player intersects with another collider
	void OnCollision(Collider* c1, Collider* c2) override;
public:
	iPoint position;
	Animation animation;
	SDL_Texture* texture = nullptr;
	Collider* collider = nullptr;
};
#endif