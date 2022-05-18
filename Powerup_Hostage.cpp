#include "Powerup_Hostage.h"

#include "Application.h"
#include "ModuleCollisions.h"
#include "ModuleAudio.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"
#include "ModuleParticles.h"

Powerup_Hostage::Powerup_Hostage(int x, int y) : Powerup(x, y) {
	collider = App->collisions->AddCollider({ 0,0,26,26 * 2 }, Collider::Type::HOSTAGE, (Module*)App->powerups);
	pickUpFx = App->audio->LoadFx("Assets/sounds/sfx/181.wav");
	deadFx = App->audio->LoadFx("Assets/sounds/sfx/182.wav");
	idleFx = App->audio->LoadFx("Assets/sounds/sfx/199.wav");
	idleFxCooldown = 0;
	idleAnimTop.PushBack({ 0, 0, 26, 26 });
	idleAnimTop.PushBack({ 32, 0, 26, 26 });
	idleAnimTop.PushBack({ 64, 0, 26, 26 });
	idleAnimTop.PushBack({ 96, 0, 26, 26 });
	idleAnimTop.speed = 0.05f;
	idleAnimTop.loop = true;

	idleAnimBot.PushBack({ 0, 32, 26, 26 });
	idleAnimBot.PushBack({ 32, 32, 26, 26 });
	idleAnimBot.PushBack({ 64, 32, 26, 26 });
	idleAnimBot.PushBack({ 96, 32, 26, 26 });
	idleAnimBot.speed = 0.05f;
	idleAnimBot.loop = true;

	currentAnim = &idleAnimTop;
	currentAnimBot = &idleAnimBot;

}

void Powerup_Hostage::Update() {
	idleFxCooldown++;
	if (idleFxCooldown >= IDLEFX_COOLDOWN) {
		idleFxCooldown = 0;
		App->audio->PlayFx(idleFx);
	}

	if (currentAnimBot != nullptr) {
		currentAnimBot->Update();
	}

	Powerup::Update();
}

void Powerup_Hostage::OnCollision(Collider* collider) {
	if (collider->type == Collider::Type::ENEMY_SHOT ||
		collider->type == Collider::Type::ENEMY ||
		collider->type == Collider::Type::PLAYER_SHOT) {
		App->audio->PlayFx(deadFx);
		if (App->player->score >= 500) {
			App->player->score -= 500;
		} else {
			App->player->score = 0;
		}
		
		// add -500 score animation

		App->particles->AddParticle(App->particles->hostageDeathTop, position.x, position.y, Collider::Type::NONE);
		App->particles->AddParticle(App->particles->hostageDeathBot, position.x, position.y + 26, Collider::Type::NONE);
	
	}

	if (collider->type == Collider::Type::PLAYER) {
		App->audio->PlayFx(pickUpFx);
		App->player->score += 1000;

		// add +1000 score animation
		App->particles->AddParticle(App->particles->hostagePickUpTop, position.x, position.y, Collider::Type::NONE);
		App->particles->AddParticle(App->particles->hostagePickUpBot, position.x, position.y + 26, Collider::Type::NONE);
	}
}

void Powerup_Hostage::Draw() {
	
	if (currentAnimBot != nullptr) {
		App->render->Blit(texture, position.x, position.y + 26, &(currentAnimBot->GetCurrentFrame()));
	}

	Powerup::Draw();
}
