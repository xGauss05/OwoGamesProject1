#ifndef __POWERUP_FLAMETHROWER_H__
#define __POWERUP_FLAMETHROWER_H__

#include "Powerup.h"

class Powerup_Flamethrower : public Powerup {
public:
	// Constructor (x y coordinates in the world)
	// Creates animation and the collider
	Powerup_Flamethrower(int x, int y);

	void Update() override;

	void OnCollision(Collider* collider) override;

};

#endif // __POWERUP_FLAMETHROWER_H__