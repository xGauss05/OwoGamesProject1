#include "Powerup.h"

#include "Application.h"
#include "ModuleCollisions.h"
#include "ModuleAudio.h"
#include "ModuleRender.h"

Powerup::Powerup(int x, int y) : position(x, y) {
	spawnPos = position;
}

Powerup::~Powerup() {
	if (collider != nullptr)
		collider->pendingToDelete = true;
}

const Collider* Powerup::GetCollider() const {
	return collider;
}

void Powerup::Update() {
	if (currentAnim != nullptr)
		currentAnim->Update();

	if (collider != nullptr)
		collider->SetPos(position.x, position.y);
}

void Powerup::Draw() {
	if (currentAnim != nullptr)
		App->render->Blit(texture, position.x, position.y, &(currentAnim->GetCurrentFrame()));
}

void Powerup::OnCollision(Collider* collider) {
	App->audio->PlayFx(pickUpFx);
}