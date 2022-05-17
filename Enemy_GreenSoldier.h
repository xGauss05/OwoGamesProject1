#ifndef __ENEMY_GREENSOLDIER_H__
#define __ENEMY_GREENSOLDIER_H__

#include "Enemy.h"
#include "Path.h"

class Enemy_GreenSoldier : public Enemy
{
public:
	// Constructor (x y coordinates in the world)
	// Creates animation and movement data and the collider
	Enemy_GreenSoldier(int x, int y, unsigned short behaviour);

	// The enemy is going to follow the different steps in the path
	// Position will be updated depending on the speed defined at each step
	void Update() override;

	void OnCollision(Collider* collider) override;

	void Shoot() override;

private:
	// A set of steps that define the position in the screen
	// And an animation for each step
	Path path;

	Animation defaultTopAnim;
	Animation botAnimLeft;
	Animation botAnimRight;

	unsigned short behaviour;
	int shootdelay;
	int grenadeDelay;
};

#endif // __ENEMY_GREENSOLDIER_H__