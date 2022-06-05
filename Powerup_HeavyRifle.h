#ifndef __POWERUP_HEAVYRIFLE_H__
#define __POWERUP_HEAVYRIFLE_H__

#include "Powerup.h"

class Powerup_HeavyRifle : public Powerup {
public:
	// Constructor
	// Creates animation and the collider
	Powerup_HeavyRifle(int x, int y);

	void Update() override;

	void OnCollision(Collider* collider) override;

};

#endif // __POWERUP_HEAVYRIFLE_H__