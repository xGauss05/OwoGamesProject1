#include "Enemy_Truck.h"

#include "Application.h"
#include "ModuleCollisions.h"
#include "ModuleAudio.h"

#include "ModulePlayer.h"
#include "ModuleParticles.h"
#include "ModuleEnemies.h"
#include "ModulePowerup.h"

#include "Globals.h"
#include "SDL/include/SDL.h"

#define TRUCK_SCORE 500;

// Should appear once per level
Enemy_Truck::Enemy_Truck(int x, int y) : Enemy(x, y) {
	anim.PushBack({ 0, 0, 92, 58 });
	anim.PushBack({ 96, 0, 92, 58 });
	anim.loop = true;
	currentAnimTop = &anim;
	t1 = SDL_GetTicks();

	path.PushBack({ -1.0f, 0 }, 50);

	collider = App->collisions->AddCollider({ 0, 0, 92, 58 }, Collider::Type::TRUCK, (Module*)App->enemies);
}

void Enemy_Truck::Update() {
	
	if (this->position.x >= 415) {
		path.Update();
		position = spawnPos + path.GetRelativePosition();
	}
	if (this->position.x <= 415) {
		int t2 = SDL_GetTicks();
		if ((t2 - t1) / 3000.0f >= 1) {
			t1 = t2;
			App->enemies->AddEnemy(ENEMY_TYPE::TACKLER, position.x + 92, position.y);
		}
	}
	Enemy::Update();
}

void Enemy_Truck::OnCollision(Collider* collider) {
	if (collider->type == Collider::Type::EXPLOSION) {
		App->particles->AddParticle(App->particles->truckAnim, position.x, position.y, Collider::Type::NONE);
		App->player->score += TRUCK_SCORE;
	}
}

void Enemy_Truck::Shoot() {
}

