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

	if (currentAnimTop != nullptr)
		currentAnimTop->Update();

	if (currentAnimBot != nullptr)
		currentAnimBot->Update();

	if (collider != nullptr)
		collider->SetPos(position.x, position.y);


	
}

void Enemy::Draw() {
	if (currentAnimTop != nullptr)
		App->render->Blit(texture, position.x, position.y, &(currentAnimTop->GetCurrentFrame()));
	if (currentAnimBot != nullptr)
		App->render->Blit(texture, position.x, position.y + 30, &(currentAnimBot->GetCurrentFrame()));
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
//void Enemy::OnCollision(Collider* collider) {
//	
//
//	//App->particles->AddParticle(App->particles->explosion, position.x, position.y);
//	//App->audio->PlayFx(enemyDeadFx);
//}

