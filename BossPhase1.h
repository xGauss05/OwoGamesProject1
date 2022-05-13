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
	Path path;

	Animation topAnim;
	Animation botAnim;

	int shootdelay;
};

#endif // __BOSSPHASE1__