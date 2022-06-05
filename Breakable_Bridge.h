#ifndef __BREAKABLE_BRIDGE_H__
#define __BREAKABLE_BRIDGE_H__

#include "Breakable.h"

class Breakable_Bridge : public Breakable {
public:
	// Constructor (x y coordinates in the world)
	// Creates animation and movement data and the collider
	Breakable_Bridge(int x, int y);

	// The breakable is going to follow the different steps in the path
	// Position will be updated depending on the speed defined at each step
	void Update() override;

	void OnCollision(Collider* collider) override;

};

#endif // __BREAKABLE_BRIDGE_H__