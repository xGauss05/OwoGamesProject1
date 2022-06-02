#ifndef __POWERUP_HOSTAGE_H__
#define __POWERUP_HEAVYRIFLE_H__

#include "Powerup.h"
#include "Globals.h"

class Powerup_Hostage : public Powerup {
public:
	// Constructor (x y coordinates in the world)
	// Creates animation and movement data and the collider
	Powerup_Hostage(int x, int y);

	// The powerup is going to follow the different steps in the path
	// Position will be updated depending on the speed defined at each step
	void Update() override;

	void OnCollision(Collider* collider) override;

	void Draw() override;

	int deadFx;
	int idleFx;
protected:
	Animation* currentAnimBot = nullptr;

	Animation idleAnimTop, idleAnimBot;
	Animation pickUpAnimTop, pickUpAnimBot;

private:
	uint idleFxCooldown = 0;

};

#endif // __POWERUP_HOSTAGE_H__