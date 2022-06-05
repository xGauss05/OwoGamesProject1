#ifndef __POWERUP_HOSTAGE_H__
#define __POWERUP_HEAVYRIFLE_H__

#include "Powerup.h"
#include "Globals.h"

class Powerup_Hostage : public Powerup {
public:
	// Constructor
	// Creates animation and the collider
	Powerup_Hostage(int x, int y);

	// Destructor
	// Cleans deadFx and idleFx
	~Powerup_Hostage();
	
	// Every 750 frames, idleFx sound is played
	void Update() override;

	// Checks if either shot or picked up by the player
	void OnCollision(Collider* collider) override;

	void Draw() override;

	// Sound Fx indexes
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
