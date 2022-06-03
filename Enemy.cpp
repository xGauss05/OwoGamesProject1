#include "Enemy.h"

#include "Application.h"
#include "ModuleCollisions.h"
#include "ModuleParticles.h"
#include "ModuleAudio.h"
#include "ModuleRender.h"

#include "SDL/include/SDL_render.h"
#include "ModulePlayer.h"
#include <math.h>

Enemy::Enemy(int x, int y) : position(x, y) {
	spawnPos = position;
	enemyDeadFx = App->audio->LoadFx("Assets/sounds/sfx/194.wav");
	enemyShotFx = App->audio->LoadFx("Assets/sounds/sfx/128.wav");
	alpha = degrees = 0.0f;
}

Enemy::~Enemy() {
	if (collider != nullptr)
		collider->pendingToDelete = true;
}

const Collider* Enemy::GetCollider() const {
	return collider;
}

void Enemy::Update() {
	lookAtPlayer();
	updateDirection();

	if (currentAnimTop != nullptr)
		currentAnimTop->Update();

	if (currentAnimBot != nullptr)
		currentAnimBot->Update();

	if (collider != nullptr)
		collider->SetPos(position.x, position.y);


	
}

void Enemy::Draw() {

	if (currentAnimBot != nullptr)
		App->render->Blit(texture, position.x, position.y + 32, &(currentAnimBot->GetCurrentFrame()));

	if (currentAnimTop != nullptr)
		App->render->Blit(texture, position.x, position.y + 4, &(currentAnimTop->GetCurrentFrame()));
}

void Enemy::lookAtPlayer()
{
	distance.x = App->player->position.x - this->position.x;
	distance.y = App->player->position.y - this->position.y;

	alpha = atan2(distance.y, distance.x);

	degrees = alpha / (M_PI / 180.0f);

	if (degrees < 0)
		degrees += 360.0f;
}

void Enemy::updateDirection()
{
	// Down
	if (degrees > 247.5 && degrees < 292.5)
		looking = Directions::UP;

	// Down right
	else if (degrees > 292.5 && degrees < 337.5)
		looking = Directions::UP_RIGHT;

	// Down left
	else if (degrees > 202.5 && degrees < 247.5)
		looking = Directions::UP_LEFT;

	// Right
	else if (degrees > 337.5 || degrees < 22.5)
		looking = Directions::RIGHT;

	// Left
	else if (degrees > 157.5 && degrees < 202.5)
		looking = Directions::LEFT;

	// Up right
	else if (degrees > 22.5 && degrees < 67.5)
		looking = Directions::DOWN_RIGHT;

	// Up left
	else if (degrees > 112.5 && degrees < 157.5)
		looking = Directions::DOWN_LEFT;

	// Up
	else if (degrees > 67.5 && degrees < 112.5)
		looking = Directions::DOWN;
}
//void Enemy::OnCollision(Collider* collider) {
//	
//
//	//App->particles->AddParticle(App->particles->explosion, position.x, position.y);
//	//App->audio->PlayFx(enemyDeadFx);
//}

