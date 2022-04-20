#ifndef __POWERUP_H__
#define __POWERUP_H__

#include "p2Point.h"
#include "Animation.h"

struct SDL_Texture;
struct Collider;

class Powerup {
public:
	// Constructor
	// Saves the spawn position for later movement calculations
	Powerup(int x, int y);

	// Destructor
	virtual ~Powerup();

	// Returns the powerup's collider
	const Collider* GetCollider() const;

	// Called from inhering powerups' Udpate
	// Updates animation and collider position
	virtual void Update();

	// Called from ModulePowerups' Update
	virtual void Draw();

	// Collision response
	// Triggers a sound fx and updates Player weapon
	virtual void OnCollision(Collider* collider) = 0;

public:
	// The current position in the world
	iPoint position;

	// The powerup's texture
	SDL_Texture* texture = nullptr;

	// Sound fx when pick up
	int pickUpFx = 0;

protected:
	// A ptr to the current animation
	Animation* currentAnim = nullptr;

	// Powerup animation
	Animation weaponAnim;

	// The powerup's collider
	Collider* collider = nullptr;

	// Original spawn position. Stored for movement calculations
	iPoint spawnPos;

};

#endif // __POWERUP_H__