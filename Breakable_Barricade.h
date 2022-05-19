#ifndef __POWERUP_BREAKABLE_H__
#define __POWERUP_BREAKABLE_H__

#include "Breakable.h"

class Breakable_Barricade :  public Breakable {
public:
	// Constructor (x y coordinates in the world)
// Creates animation and movement data and the collider
	Breakable_Barricade(int x, int y);

	// The enemy is going to follow the different steps in the path
	// Position will be updated depending on the speed defined at each step
	void Update() override;
	void OnCollision(Collider* collider) override;
private:

};

#endif // __POWERUP_BREAKABLE_H__