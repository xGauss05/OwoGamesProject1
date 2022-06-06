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



// Should appear once per level
Enemy_Truck::Enemy_Truck(int x, int y) : Enemy(x, y) {
	anim.PushBack({ 0, 0, 92, 58 });
	anim.PushBack({ 96, 0, 92, 58 });
	anim.loop = true;
	currentAnimTop = &anim;
	timerSpawn = SDL_GetTicks();
	timerInvincible = SDL_GetTicks();
	explosionInvincible = 2;
	hits = 50;
	isHit = false;
	path.PushBack({ -1.0f, 0 }, 50);

	collider = App->collisions->AddCollider({ 0, 0, 92, 58 }, Collider::Type::TRUCK, (Module*)App->enemies);
}

void Enemy_Truck::Update() {
	if (isHit) {
		int t2 = SDL_GetTicks();
		if (t2 - timerInvincible >= 1) {
			timerInvincible = t2;
			explosionInvincible--;
		}
		if (explosionInvincible <= 0) {
			isHit = false;
			explosionInvincible = 2;
		}
	}
	if (this->position.x >= 415) {
		path.Update();
		position = spawnPos + path.GetRelativePosition();
	}
	if (this->position.x <= 415) {
		int t2 = SDL_GetTicks();
		if ((t2 - timerSpawn) / 3000.0f >= 1) {
			timerSpawn = t2;
			App->enemies->AddEnemy(ENEMY_TYPE::TACKLER, position.x + 92, position.y + SCREEN_WIDTH);
		}
	}
	Enemy::Update();
}

void Enemy_Truck::OnCollision(Collider* collider) {
	if (collider->type == Collider::Type::EXPLOSION &&
		!isHit) {
		hits += 10;
		isHit = true;
		//App->particles->AddParticle(App->particles->truckAnim, position.x, position.y, Collider::Type::NONE);
		//App->player->score += TRUCK_SCORE;
	}
	if (collider->type == Collider::Type::PLAYER_SHOT) {
		hits += 10;
	}
}

void Enemy_Truck::Shoot() {
}

