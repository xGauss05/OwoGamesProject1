#ifndef __ENEMY_GREENSOLDIER_H__
#define __ENEMY_GREENSOLDIER_H__

#include "Globals.h"

#include "Enemy.h"
#include "Path.h"

class Enemy_GreenSoldier : public Enemy
{
public:

	// Constructor (x y coordinates in the world)
	// Creates animation and movement data and the collider
	Enemy_GreenSoldier(int x, int y, ushort behaviour);

	// The enemy is going to follow the different steps in the path
	// Position will be updated depending on the speed defined at each step

	void initAnimations();
	void syncAnimations();

	void Update() override;

	void OnCollision(Collider* collider) override;

	void Shoot() override;

	void Burst();
	void Grenade();

private:
	// A set of steps that define the position in the screen
	// And an animation for each step
	Path path;

	//Old animations
	Animation defaultTopAnim;
	Animation botAnimLeft;
	Animation botAnimRight;

	//New animations

	//Walk
	Animation topUpWalk, botUpWalk;
	Animation topUpLeftWalk, botUpLeftWalk;
	Animation topLeftWalk, botLeftWalk;
	Animation topDownLeftWalk, botDownLeftWalk;
	Animation topDownWalk, botDownWalk;
	Animation topDownRightWalk, botDownRightWalk;
	Animation topRightWalk, botRightWalk;
	Animation topUpRightWalk, botUpRightWalk;

	//Crouch
	Animation topUpCrouch, botUpCrouch;
	Animation topUpLeftCrouch, botUpLeftCrouch;
	Animation topLeftCrouch, botLeftCrouch;
	Animation topDownLeftCrouch, botDownLeftCrouch;
	Animation topDownCrouch, botDownCrouch;
	Animation topDownRightCrouch, botDownRightCrouch;
	Animation topRightCrouch, botRightCrouch;
	Animation topUpRightCrouch, botUpRightCrouch;

	//Throw Grenade
	Animation topUpGrenade, botUpGrenade;
	Animation topUpLeftGrenade, botUpLeftGrenade;
	Animation topLeftGrenade, botLeftGrenade;
	Animation topDownLeftGrenade, botDownLeftGrenade;
	Animation topDownGrenade, botDownGrenade;
	Animation topDownRightGrenade, botDownRightGrenade;
	Animation topRightGrenade, botRightGrenade;
	Animation topUpRightGrenade, botUpRightGrenade;

	//Shoot
	Animation topUpShoot, botUpShoot;
	Animation topUpLeftShoot, botUpLeftShoot;
	Animation topLeftShoot, botLeftShoot;
	Animation topDownLeftShoot, botDownLeftShoot;
	Animation topDownShoot, botDownShoot;
	Animation topDownRightShoot, botDownRightShoot;
	Animation topRightShoot, botRightShoot;
	Animation topUpRightShoot, botUpRightShoot;


	ushort behaviour;
	bool stationary = false;
	int pathTransitionDelay = 0;
	int pathTransitionDuration = 0;
	int shotCount = 0;

	bool burst = false;
	int burstDelay;
	int shootdelay;
	int burstCount = 0;

	int grenadeDelay;

	ushort leaveDir;
};

#endif // __ENEMY_GREENSOLDIER_H__