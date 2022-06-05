#ifndef __BREAKABLE_BARRICADE_V_H__
#define __BREAKABLE_BARRICADE_V_H__

#include "Breakable.h"

class Breakable_Barricade_V : public Breakable {
public:
	// Constructor (x y coordinates in the world)
	// Creates animation and movement data and the collider
	Breakable_Barricade_V(int x, int y);

	// The breakable is going to follow the different steps in the path
	// Position will be updated depending on the speed defined at each step
	void Update() override;

	void OnCollision(Collider* collider) override;

};

#endif // __BREAKABLE_BARRICADE_V_H__