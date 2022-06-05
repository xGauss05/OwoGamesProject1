#ifndef __BOSSPHASE1_H__
#define __BOSSPHASE1_H__

#include "Enemy.h"
#include "Path.h"

class BossPhase1 : public Enemy
{
public:
	// Constructor (x y coordinates in the world)
	// Creates animation and movement data and the collider
	BossPhase1(int x, int y);

	// The enemy is going to follow the different steps in the path
	// Position will be updated depending on the speed defined at each step
	void Update() override;

	void OnCollision(Collider* collider) override;

	void Shoot() override;

private:
	// A set of steps that define the position in the screen
	// And an animation for each step
	Path inOutPath;
	Path path;
	int inOutTime = 100;

	Animation topAnimIdle;
	Animation topAnimSpawn;
	Animation botAnimLeft;
	Animation botAnimRight;
	Animation botAnimSpawn;

	bool inOut = true;
	int inOutTimer = 0;

	iPoint stayPos = { 0,0 };
	int spawnDelay;
	bool spawning;

	int hits = 0;
	int winWait = 0;
};

#endif // __BOSSPHASE1__