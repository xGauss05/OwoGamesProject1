#include "Enemy_Truck.h"

#include "Application.h"
#include "ModuleCollisions.h"
#include "ModuleAudio.h"

#include "ModulePlayer.h"
#include "ModuleParticles.h"
#include "ModuleEnemies.h" //(Testing)
#include "ModulePowerup.h" //(Testing)

#define TRUCK_SCORE 300;

Enemy_Truck::Enemy_Truck(int x, int y) : Enemy(x, y) {
	anim.PushBack({  0, 0, 92, 58 });
	anim.PushBack({ 96, 0, 92, 58 });
	currentAnimTop = &anim;

	path.PushBack({ -1.0f, 0 }, 50);
	/*path.PushBack({0, 1.0f}, 50); */


	collider = App->collisions->AddCollider({ 0, 0, 92, 58 }, Collider::Type::ENEMY, (Module*)App->enemies);
}

void Enemy_Truck::Update() {

	Enemy::Update();
}

void Enemy_Truck::OnCollision(Collider* collider) {
	if (collider->type == Collider::Type::EXPLOSION) {

		App->player->score += TRUCK_SCORE;
	}



}

void Enemy_Truck::Shoot() {
}

