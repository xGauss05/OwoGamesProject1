#include "Powerup_Hostage.h"

#include "Application.h"
#include "ModuleCollisions.h"
#include "ModuleAudio.h"

#include "ModulePlayer.h"

Powerup_Hostage::Powerup_Hostage(int x, int y) : Powerup(x, y) {
	//collider = App->collisions->AddCollider({}, Collider::Type::HOSTAGE, (Module*)App->powerups);
	pickUpFx = App->audio->LoadFx("Assets/sounds/sfx/165.wav");
	deadFx = App->audio->LoadFx("Assets/sounds/sfx/182.wav");
	idleFx = App->audio->LoadFx("Assets/sounds/sfx/199.wav");
	idleFxCooldown = 0;
}

void Powerup_Hostage::Update() {
	idleFxCooldown++;
	if (idleFxCooldown >= IDLEFX_COOLDOWN) {
		idleFxCooldown = 0;
		App->audio->PlayFx(idleFx);
	}
	Powerup::Update();
}

void Powerup_Hostage::OnCollision(Collider* collider) {
	if (collider->type == Collider::Type::ENEMY_SHOT ||
		collider->type == Collider::Type::ENEMY ||
		collider->type == Collider::Type::PLAYER_SHOT) {
		App->audio->PlayFx(deadFx);
		App->player->score -= 500;
		// add -500 score animation
	}
	if (collider->type == Collider::Type::PLAYER) {
		App->audio->PlayFx(pickUpFx);
		App->player->score += 1000;
		// add +1000 socre animation
	}
}
