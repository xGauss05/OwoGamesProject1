#ifndef __MODULE_POWERUP_H__
#define __MODULE_POWERUP_H__

#include "Module.h"

#define MAX_POWERUPS 50
enum class POWERUP_TYPE {
	NO_TYPE,
	HEAVY_RIFLE,
	FLAMETHROWER
};

struct PowerupSpawnpoint {
	POWERUP_TYPE type = POWERUP_TYPE::NO_TYPE;
	int x, y;
};

class Powerup;
struct SDL_Texture;

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

	bool CleanUp() override;
	// Collision callback, called when the player intersects with another collider
	void OnCollision(Collider* c1, Collider* c2) override;

	bool AddPowerup(POWERUP_TYPE type, int x, int y);

	void HandlePowerupsSpawn();

	void HandlePowerupsDespawn();

private:
	// Spawns a new enemy using the data from the queue
	void SpawnPowerup(const PowerupSpawnpoint& info);

private:
	PowerupSpawnpoint spawnQueue[MAX_POWERUPS];

	Powerup* powerUps[MAX_POWERUPS] = { nullptr };

	SDL_Texture* texture = nullptr;
	
	int pickUpFx = 0;
};
#endif