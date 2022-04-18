#include "Enemy_RedSoldier.h"

#include "Application.h"
#include "ModuleCollisions.h"

#include "ModuleEnemies.h" //(Testing)
#include "ModulePowerup.h" //(Testing)

Enemy_RedSoldier::Enemy_RedSoldier(int x, int y) : Enemy(x, y)
{
	//(empty).PushBack({ 5,72,21,22 });
	//currentAnim = &(empty);

	//Have the Brown Cookies describe a path in the screen
	path.PushBack({ 0, -1.0f }, 50);
	path.PushBack({ 0, 1.0f }, 50);


	collider = App->collisions->AddCollider({ 0, 0, 36, 72 }, Collider::Type::ENEMY, (Module*)App->enemies);
}

void Enemy_RedSoldier::Update()
{
	path.Update();
	position = spawnPos + path.GetRelativePosition();

	// Call to the base class. It must be called at the end
	// It will update the collider depending on the position
	Enemy::Update();
}

void Enemy_RedSoldier::Die()
{
	//App->enemies->AddEnemy(ENEMY_TYPE::REDSOLDIER, 300, -600);
	App->powerups->AddPowerup(POWERUP_TYPE::HEAVY_RIFLE, position.x, position.y);
}