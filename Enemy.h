#ifndef __ENEMY_H__
#define __ENEMY_H__

#include "p2Point.h"
#include "Animation.h"

struct SDL_Texture;
struct Collider;

#define SHOT_SPEED_STRAIGHT 3
#define SHOT_SPEED_DIAGONAL 2.12f

class Enemy {
public:
	// Constructor
	// Saves the spawn position for later movement calculations
	Enemy(int x, int y);

	// Destructor
	virtual ~Enemy();

	// Returns the enemy's collider
	const Collider* GetCollider() const;

	// Called from inhering enemies' Udpate
	// Updates animation and collider position
	virtual void Update();

	// Called from ModuleEnemies' Update
	virtual void Draw();

	// Collision response
	// Triggers an animation and a sound fx
	virtual void OnCollision(Collider* collider) = 0;

	//Calculate enemy rotation with respect to the player
	void lookAtPlayer();
	void updateDirection();

	//The way each enemy shoots, defined by the specific classes
	virtual void Shoot() = 0;

public:
	// The current position and orientation in the world
	enum Directions {
		UP, DOWN, RIGHT,
		LEFT, UP_RIGHT, UP_LEFT,
		DOWN_RIGHT, DOWN_LEFT
	};
	
	iPoint position;
	float alpha;
	float degrees;
	Directions looking;

	// The distance in pixels to the player
	iPoint distance;

	// The enemy's texture
	SDL_Texture* texture = nullptr;

	// Sound fx when destroyed
	int enemyDeadFx = 0;
	int enemyShotFx = 0;
protected:
	// A ptr to the current animation
	Animation* currentAnimTop = nullptr;
	Animation* currentAnimBot = nullptr;

	// The enemy's collider
	Collider* collider = nullptr;
	// Original spawn position. Stored for movement calculations
	iPoint spawnPos;
};

#endif // __ENEMY_H__