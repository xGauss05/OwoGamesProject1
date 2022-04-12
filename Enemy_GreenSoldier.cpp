#include "Enemy_GreenSoldier.h"

#include "Application.h"
#include "ModuleCollisions.h"

Enemy_GreenSoldier::Enemy_GreenSoldier(int x, int y) : Enemy(x, y)
{
	//(empty).PushBack({ 5,72,21,22 });
	//currentAnim = &(empty);

	//Have the Brown Cookies describe a path in the screen
	path.PushBack({ -1.0f, 0 }, 50);
	path.PushBack({ 1.0f, 0 }, 50);


	collider = App->collisions->AddCollider({ 0, 0, 36, 72 }, Collider::Type::ENEMY, (Module*)App->enemies);
}

void Enemy_GreenSoldier::Update()
{
	path.Update();
	position = spawnPos + path.GetRelativePosition();

	// Call to the base class. It must be called at the end
	// It will update the collider depending on the position
	Enemy::Update();
}
