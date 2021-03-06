#ifndef __MODULE_ENEMIES_H__
#define __MODULE_ENEMIES_H__

#include "Module.h"
#include "ModuleDebug.h"

#define MAX_ENEMIES		100

enum class ENEMY_TYPE
{
	NO_TYPE, GREENSOLDIER,	REDSOLDIER, TACKLER,
	TRUCK, BOSS
};

struct EnemySpawnpoint
{
	ENEMY_TYPE type = ENEMY_TYPE::NO_TYPE;
	int x, y;
	unsigned short behaviour = 0;
};

class Enemy;
struct SDL_Texture;

class ModuleEnemies : public Module
{
public:
	// Constructor
	ModuleEnemies(bool startEnabled);

	// Destructor
	~ModuleEnemies();

	// Called when the module is activated
	// Loads the necessary textures for the enemies
	bool Start() override;

	// Called at the middle of the application loop
	// Handles all enemies logic and spawning/despawning
	update_status Update() override;

	// Called at the end of the application loop
	// Iterates all the enemies and draws them
	update_status PostUpdate() override;

	// Called on application exit
	// Destroys all active enemies left in the array
	bool CleanUp() override;

	// Called when an enemi collider hits another collider
	// The enemy is destroyed and an explosion particle is fired
	void OnCollision(Collider* c1, Collider* c2) override;

	int randVal(int min, int max);

	/* Add an enemy into the queue to be spawned later
	 Behaviour for Greensoldiers:
 - 0: Stay squatting (Shoot).
 - 1: Up Left (Shoot).
 - 2: Up (Shoot).
 - 3: Up Right (Shoot).
 - 4: Stay squatting (Grenade).
 - 5: Up Left (Grenade).
 - 6: Up (Grenade).
 - 7: Up Right (Grenade).
 Behaviour for Redsoldiers:
 - 0: Drop Heavy rifle.
 - 1: Drop flamethrower.
*/
	bool AddEnemy(ENEMY_TYPE type, int x, int y, ushort behaviour = 0);

	// Iterates the queue and checks for camera position
	void HandleEnemiesSpawn();

	// Destroys any enemies that have moved outside the camera limits
	void HandleEnemiesDespawn();

private:
	// Spawns a new enemy using the data from the queue
	void SpawnEnemy(const EnemySpawnpoint& info);

private:
	// A queue with all spawn points information
	EnemySpawnpoint spawnQueue[MAX_ENEMIES];

	// All spawned enemies in the scene
	Enemy* enemies[MAX_ENEMIES] = { nullptr };

	// The enemies sprite sheets
	SDL_Texture* greenEnemyTexture = nullptr;
	SDL_Texture* redEnemyTexture = nullptr;
	SDL_Texture* truckEnemyTexture = nullptr;
	SDL_Texture* bossTexture = nullptr;

	// The audio fx for destroying an enemy (generic)
	int enemyDestroyedFx = 0;

	friend void ModuleDebug::DebugDraw();
};

#endif // __MODULE_ENEMIES_H__