#ifndef __BREAKABLE_FENCE_H__
#define __BREAKABLE_FENCE_H__

#include "Breakable.h"

class Breakable_Fence : public Breakable {
public:
	// Constructor (x y coordinates in the world)
	// Creates animation and movement data and the collider
	Breakable_Fence(int x, int y, unsigned short version);

	// The breakable is going to follow the different steps in the path
	// Position will be updated depending on the speed defined at each step
	void Update() override;

	void OnCollision(Collider* collider) override;
private:

};

#endif // __BREAKABLE_FENCE_H__