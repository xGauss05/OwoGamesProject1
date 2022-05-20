#ifndef __BREAKABLE_BARRICADE_H__
#define __BREAKABLE_BARRICADE_H__

#include "Breakable.h"

class Breakable_Barricade_H :  public Breakable {
public:
	// Constructor (x y coordinates in the world)
	// Creates animation and movement data and the collider
	Breakable_Barricade_H(int x, int y);

	// The enemy is going to follow the different steps in the path
	// Position will be updated depending on the speed defined at each step
	void Update() override;

	void OnCollision(Collider* collider) override;
private:

};

#endif // __BREAKABLE_BARRICADE_H__