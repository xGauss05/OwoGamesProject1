#ifndef __ENEMY_REDSOLDIER_H__
#define __ENEMY_REDSOLDIER_H__

#include "Enemy.h"
#include "Path.h"

class Enemy_RedSoldier : public Enemy
{
public:
	// Constructor (x y coordinates in the world)
	// Creates animation and movement data and the collider
	Enemy_RedSoldier(int x, int y);

	// The enemy is going to follow the different steps in the path
	// Position will be updated depending on the speed defined at each step
	void Update() override;

	void OnCollision(Collider* collider) override;

	void Shoot() override;

private:
	// A set of steps that define the position in the screen
	// And an animation for each step
	Path path;

	int shootdelay;

	enum Directions {
		UP, DOWN, RIGHT,
		LEFT, UP_RIGHT, UP_LEFT,
		DOWN_RIGHT, DOWN_LEFT
	};

	Directions looking;

	// This enemy has one sprite and one frame
	// We are keeping it an animation for consistency with other enemies
	Animation topAnim;
	Animation botAnim;

	Animation topUp;
	Animation botUp;

	Animation topUpRight;
	Animation botUpRight;

	Animation topRight;
	Animation botRight;

	Animation topDownRight;
	Animation botDownRight;

	Animation topDown;
	Animation botDown;

	Animation topDownLeft;
	Animation botDownLeft;

	Animation topLeft;
	Animation botLeft;

	Animation topUpLeft;
	Animation botUpLeft;
};

#endif // __ENEMY_REDSOLDIER_H__