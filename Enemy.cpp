#include "Enemy.h"

#include "Application.h"
#include "ModuleCollisions.h"
#include "ModuleParticles.h"
#include "ModuleAudio.h"
#include "ModuleRender.h"

Enemy::Enemy(int x, int y) : position(x, y) {
	spawnPos = position;
	enemyDeadFx = App->audio->LoadFx("sounds/sfx/194.wav");
}

Enemy::~Enemy() {
	if (collider != nullptr)
		collider->pendingToDelete = true;
}

const Collider* Enemy::GetCollider() const {
	return collider;
}

void Enemy::Update() {
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
		App->render->Blit(texture, position.x, position.y + 32, &(currentAnimBot->GetCurrentFrame()));
}

void Enemy::lookAtPlayer()
{

}
//void Enemy::OnCollision(Collider* collider) {
//	
//
//	//App->particles->AddParticle(App->particles->explosion, position.x, position.y);
//	//App->audio->PlayFx(enemyDeadFx);
//}

