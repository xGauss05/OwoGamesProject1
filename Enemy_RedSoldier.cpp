#include "Enemy_RedSoldier.h"

#include "Application.h"
#include "ModuleCollisions.h"
#include "ModuleAudio.h"

#include "ModuleParticles.h"
#include "ModuleEnemies.h" //(Testing)
#include "ModulePowerup.h" //(Testing)

Enemy_RedSoldier::Enemy_RedSoldier(int x, int y) : Enemy(x, y) 
{
	topAnim.PushBack({ 0,0,32,32 });
	currentAnimTop = &topAnim;

	botAnim.PushBack({ 160,128,32,32 });
	currentAnimBot = &botAnim;

	path.PushBack({ 0, -1.0f }, 50);
	path.PushBack({ 0, 1.0f }, 50);


	collider = App->collisions->AddCollider({ 0, 0, 36, 72 }, Collider::Type::ENEMY, (Module*)App->enemies);
}

void Enemy_RedSoldier::Update()
{
	//path.Update();
	//position = spawnPos + path.GetRelativePosition();
	Shoot();

	// Call to the base class. It must be called at the end
	// It will update the collider depending on the position
	Enemy::Update();
}

void Enemy_RedSoldier::OnCollision(Collider* collider) {
	App->audio->PlayFx(enemyDeadFx);
	App->powerups->AddPowerup(POWERUP_TYPE::HEAVY_RIFLE, position.x, position.y);

	//App->particles->AddParticle(App->particles->explosion, position.x, position.y);
	//App->audio->PlayFx(enemyDeadFx);
}

void Enemy_RedSoldier::Shoot()
{
	if (shootdelay >= 50)
	{
		App->particles->AddParticle(App->particles->shot_down, position.x + 16, position.y + 32, Collider::Type::ENEMY_SHOT);
		shootdelay = 0;
	}

	shootdelay++;
}

