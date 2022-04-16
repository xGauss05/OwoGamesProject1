#ifndef __POWERUP_FLAMETHROWER_H__
#define __POWERUP_FLAMETHROWER_H__

#include "Powerup.h"

class Powerup_Flamethrower : public Powerup {
public:
	// Constructor (x y coordinates in the world)
	// Creates animation and movement data and the collider
	Powerup_Flamethrower(int x, int y);

	// The enemy is going to follow the different steps in the path
	// Position will be updated depending on the speed defined at each step
	void Update() override;
	void OnCollision(Collider* collider) override;
private:
};

#endif // __POWERUP_FLAMETHROWER_H__