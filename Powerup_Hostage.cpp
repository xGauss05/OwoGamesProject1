#include "Powerup_Hostage.h"

#include "Application.h"
#include "ModuleCollisions.h"
#include "ModuleAudio.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"

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

	deathAnimTop.PushBack({ 0,  128, 26, 26 });
	deathAnimTop.PushBack({ 32, 128, 26, 26 });
	deathAnimTop.PushBack({ 64, 128, 26, 26 });
	deathAnimTop.PushBack({ 96, 128, 26, 26 });
	deathAnimTop.speed = 0.05f;
	deathAnimTop.loop = false;

	deathAnimBot.PushBack({ 0,  160, 26, 26 });
	deathAnimBot.PushBack({ 32, 160, 26, 26 });
	deathAnimBot.PushBack({ 64, 160, 26, 26 });
	deathAnimBot.PushBack({ 96, 160, 26, 26 });
	deathAnimBot.speed = 0.05f;
	deathAnimBot.loop = false;

	pickUpAnimBot.PushBack({});
	pickUpAnimBot.PushBack({});
	pickUpAnimBot.PushBack({});
	pickUpAnimBot.PushBack({});
	pickUpAnimBot.speed = 0.05f;
	pickUpAnimBot.loop = false;

	pickUpAnimBot.PushBack({});
	pickUpAnimBot.PushBack({});
	pickUpAnimBot.PushBack({});
	pickUpAnimBot.PushBack({});
	pickUpAnimBot.speed = 0.05f;
	pickUpAnimBot.loop = false;

	currentAnimTop = &idleAnimTop;
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

	if (currentAnimTop != nullptr) {
		currentAnimTop->Update();
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
		if (currentAnimTop != &deathAnimTop) {
			currentAnimTop = &deathAnimTop;
		}

		if (currentAnimBot != &deathAnimBot) {
			currentAnimBot = &deathAnimBot;
		}
	}
	if (collider->type == Collider::Type::PLAYER) {
		App->audio->PlayFx(pickUpFx);
		App->player->score += 1000;
		if (currentAnimTop != &pickUpAnimTop) {
			currentAnimTop = &pickUpAnimTop;
		}

		if (currentAnimBot != &pickUpAnimBot) {
			currentAnimBot = &pickUpAnimBot;
		}
		// add +1000 socre animation
	}
}

void Powerup_Hostage::Draw() {
	if (currentAnimTop != nullptr) {
		App->render->Blit(texture, position.x, position.y, &(currentAnimTop->GetCurrentFrame()));
	}

	if (currentAnimBot != nullptr) {
		App->render->Blit(texture, position.x, position.y + 26, &(currentAnimBot->GetCurrentFrame()));
	}
}
