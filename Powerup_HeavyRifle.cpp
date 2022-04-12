#include "Powerup_HeavyRifle.h"

#include "Application.h"
#include "ModuleCollisions.h"

Powerup_HeavyRifle::Powerup_HeavyRifle(int x, int y) : Powerup(x, y) {
	//(empty).PushBack({ 5,72,21,22 });
	//currentAnim = &(empty);

	collider = App->collisions->AddCollider({ 0, 0, 23, 23 }, Collider::Type::POWER_UP, (Module*)App->enemies);
}

void Powerup_HeavyRifle::Update() {

	position = spawnPos;

	// Call to the base class. It must be called at the end
	// It will update the collider depending on the position
	Powerup::Update();
}
