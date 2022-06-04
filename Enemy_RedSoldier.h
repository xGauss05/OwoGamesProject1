#ifndef __ENEMY_REDSOLDIER_H__
#define __ENEMY_REDSOLDIER_H__

#include "Enemy.h"
#include "Path.h"

class Enemy_RedSoldier : public Enemy
{
public:
	// Constructor (x y coordinates in the world)
	// Creates animation and movement data and the collider
	Enemy_RedSoldier(int x, int y, ushort behaviour);

	// The enemy is going to follow the different steps in the path
	// Position will be updated depending on the speed defined at each step
	void Update() override;

	void OnCollision(Collider* collider) override;

	void Shoot() override;

	void Burst();

private:
	// A set of steps that define the position in the screen
	// And an animation for each step
	Path path;
	ushort behaviour = 0;

	int shootdelay;
	int shotCount;

	bool burst = false;
	int burstDelay = 0;
	int burstCount = 0;

	// This enemy has one sprite and one frame
	// We are keeping it an animation for consistency with other enemies
	Animation topAnim;
	Animation botAnim;

	//Crouch
	Animation topUpCrouch, botUpCrouch;
	Animation topUpRightCrouch, botUpRightCrouch;
	Animation topRightCrouch, botRightCrouch;
	Animation topDownRightCrouch, botDownRightCrouch;
	Animation topDownCrouch, botDownCrouch;
	Animation topDownLeftCrouch, botDownLeftCrouch;
	Animation topLeftCrouch, botLeftCrouch;
	Animation topUpLeftCrouch, botUpLeftCrouch;

	//Shoot
	Animation topUpShoot, botUpShoot;
	Animation topUpRightShoot, botUpRightShoot;
	Animation topRightShoot, botRightShoot;
	Animation topDownRightShoot, botDownRightShoot;
	Animation topDownShoot, botDownShoot;
	Animation topDownLeftShoot, botDownLeftShoot;
	Animation topLeftShoot, botLeftShoot;
	Animation topUpLeftShoot, botUpLeftShoot;
};

#endif // __ENEMY_REDSOLDIER_H__