#include "ModulePlayer.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleParticles.h"
#include "ModuleAudio.h"
#include "ModuleCollisions.h"

#include "SDL/include/SDL_scancode.h"

ModulePlayer::ModulePlayer() {
	// idle animation - just one sprite
	idleAnimTop.PushBack({ 0, 0, 32, 32 });
	idleAnimBot.PushBack({ 256, 0, 32, 32 });

	// Insert player animations here
	// move up
	upAnimBot.PushBack({ 160, 0, 32, 32 });
	upAnimBot.PushBack({ 192, 0, 32, 32 });
	upAnimBot.PushBack({ 224, 0, 32, 32 });
	upAnimBot.PushBack({ 256, 0, 32, 32 });
	upAnimBot.PushBack({ 288, 0, 32, 32 });
	upAnimBot.PushBack({ 256, 0, 32, 32 });
	upAnimBot.PushBack({ 224, 0, 32, 32 });
	upAnimBot.PushBack({ 192, 0, 32, 32 });
	upAnimBot.loop = true;
	upAnimBot.speed = 0.1f;

	// Move down
	downAnimBot.PushBack({ 160, 127, 32, 32 });
	downAnimBot.PushBack({ 192, 127, 32, 32 });
	downAnimBot.PushBack({ 224, 127, 32, 32 });
	downAnimBot.PushBack({ 256, 127, 32, 32 });
	downAnimBot.PushBack({ 288, 127, 32, 32 });
	downAnimBot.PushBack({ 256, 127, 32, 32 });
	downAnimBot.PushBack({ 224, 127, 32, 32 });
	downAnimBot.PushBack({ 192, 127, 32, 32 });
	downAnimBot.loop = true;
	downAnimBot.speed = 0.1f;

	// Move right
	rightAnimBot.PushBack({ 160, 63, 32, 32 });
	rightAnimBot.PushBack({ 192, 63, 32, 32 });
	rightAnimBot.PushBack({ 224, 63, 32, 32 });
	rightAnimBot.PushBack({ 256, 63, 32, 32 });
	rightAnimBot.PushBack({ 288, 63, 32, 32 });
	rightAnimBot.PushBack({ 256, 63, 32, 32 });
	rightAnimBot.PushBack({ 224, 63, 32, 32 });
	rightAnimBot.PushBack({ 192, 63, 32, 32 });
	rightAnimBot.loop = true;
	rightAnimBot.speed = 0.1f;

	// Move left
	leftAnimBot.PushBack({ 160, 191, 32, 32 });
	leftAnimBot.PushBack({ 192, 191, 32, 32 });
	leftAnimBot.PushBack({ 224, 191, 32, 32 });
	leftAnimBot.PushBack({ 256, 191, 32, 32 });
	leftAnimBot.PushBack({ 288, 191, 32, 32 });
	leftAnimBot.PushBack({ 256, 191, 32, 32 });
	leftAnimBot.PushBack({ 224, 191, 32, 32 });
	leftAnimBot.PushBack({ 192, 191, 32, 32 });
	leftAnimBot.loop = true;
	leftAnimBot.speed = 0.1f;

	// Move up-right
	upRightAnimBot.PushBack({ 160, 31, 32, 32 });
	upRightAnimBot.PushBack({ 192, 31, 32, 32 });
	upRightAnimBot.PushBack({ 224, 31, 32, 32 });
	upRightAnimBot.PushBack({ 256, 31, 32, 32 });
	upRightAnimBot.PushBack({ 288, 31, 32, 32 });
	upRightAnimBot.PushBack({ 256, 31, 32, 32 });
	upRightAnimBot.PushBack({ 224, 31, 32, 32 });
	upRightAnimBot.PushBack({ 192, 31, 32, 32 });
	upRightAnimBot.loop = true;
	upRightAnimBot.speed = 0.1f;

	// Move up-left
	upLeftAnimBot.PushBack({ 160, 223, 32, 32 });
	upLeftAnimBot.PushBack({ 192, 223, 32, 32 });
	upLeftAnimBot.PushBack({ 224, 223, 32, 32 });
	upLeftAnimBot.PushBack({ 256, 223, 32, 32 });
	upLeftAnimBot.PushBack({ 288, 223, 32, 32 });
	upLeftAnimBot.PushBack({ 256, 223, 32, 32 });
	upLeftAnimBot.PushBack({ 224, 223, 32, 32 });
	upLeftAnimBot.PushBack({ 192, 223, 32, 32 });
	upLeftAnimBot.loop = true;
	upLeftAnimBot.speed = 0.1f;

	// Move down-left

	// Move down-right
}

ModulePlayer::~ModulePlayer() {
}

bool ModulePlayer::Start() {
	LOG("Loading player textures");

	bool ret = true;

	texture = App->textures->Load("img/sprites/player.png"); // player spritesheet
	currentAnimTop = &idleAnimTop;
	currentAnimBot = &idleAnimBot;

	// initiate player audios here
	shotFx = App->audio->LoadFx("sounds/sfx/128.wav"); // shot sfx
	deadFx = App->audio->LoadFx("sounds/sfx/195.wav"); // dead sfx

	// initial position
	position.x = 150;
	position.y = 120;

	// player collider
	collider = App->collisions->AddCollider({ position.x, position.y, 32, 64 }, Collider::Type::PLAYER, this);

	return ret;
}

update_status ModulePlayer::Update() {
	// Moving the player with the camera scroll

	// Go left
	if (App->input->keys[SDL_SCANCODE_A] == KEY_STATE::KEY_REPEAT &&
		App->input->keys[SDL_SCANCODE_W] == KEY_STATE::KEY_IDLE &&
		App->input->keys[SDL_SCANCODE_S] == KEY_STATE::KEY_IDLE) {
		position.x -= speed;
		if (currentAnimBot != &leftAnimBot) {
			leftAnimBot.Reset();
			currentAnimBot = &leftAnimBot;
		}
	}

	// Go right
	if (App->input->keys[SDL_SCANCODE_D] == KEY_STATE::KEY_REPEAT &&
		App->input->keys[SDL_SCANCODE_W] == KEY_STATE::KEY_IDLE &&
		App->input->keys[SDL_SCANCODE_S] == KEY_STATE::KEY_IDLE) {
		position.x += speed;
		if (currentAnimBot != &rightAnimBot) {
			rightAnimBot.Reset();
			currentAnimBot = &rightAnimBot;
		}
	}

	// Go down
	if (App->input->keys[SDL_SCANCODE_S] == KEY_STATE::KEY_REPEAT) {
		position.y += speed;
		if (currentAnimBot != &downAnimBot) {
			downAnimBot.Reset();
			currentAnimBot = &downAnimBot;
		}
	}

	// Go up
	if (App->input->keys[SDL_SCANCODE_W] == KEY_STATE::KEY_REPEAT &&
		App->input->keys[SDL_SCANCODE_D] == KEY_STATE::KEY_IDLE &&
		App->input->keys[SDL_SCANCODE_A] == KEY_STATE::KEY_IDLE) {
		position.y -= speed;
		if (currentAnimBot != &upAnimBot) {
			upAnimBot.Reset();
			currentAnimBot = &upAnimBot;
		}
	}

	// Go up-right
	if (App->input->keys[SDL_SCANCODE_W] == KEY_STATE::KEY_REPEAT && 
		App->input->keys[SDL_SCANCODE_D] == KEY_STATE::KEY_REPEAT) {
		position.y -= speed;
		position.x += speed;
		if (currentAnimBot != &upRightAnimBot) {
			upRightAnimBot.Reset();
			currentAnimBot = &upRightAnimBot;
		}
	}

	// Go up-left
	if (App->input->keys[SDL_SCANCODE_W] == KEY_STATE::KEY_REPEAT &&
		App->input->keys[SDL_SCANCODE_A] == KEY_STATE::KEY_REPEAT) {
		position.y -= speed;
		position.x -= speed;
		if (currentAnimBot != &upLeftAnimBot) {
			upLeftAnimBot.Reset();
			currentAnimBot = &upLeftAnimBot;
		}
	}

	if (App->input->keys[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_DOWN) {
		App->particles->AddParticle(App->particles->shot, position.x + 20, position.y, Collider::Type::PLAYER_SHOT);
		App->audio->PlayFx(shotFx);
	}

	// If no up/down movement detected, set the current animation back to idle
	if (App->input->keys[SDL_SCANCODE_S] == KEY_STATE::KEY_IDLE
		&& App->input->keys[SDL_SCANCODE_W] == KEY_STATE::KEY_IDLE) {
	/*	currentAnimTop = &idleAnimTop;
		currentAnimBot = &idleAnimBot;*/
	}
	// Updates player collider position
	collider->SetPos(position.x, position.y);
	currentAnimTop->Update();
	currentAnimBot->Update();

	if (dead) {
		destroyedCountdown--;
		if (destroyedCountdown <= 0)
			return update_status::UPDATE_STOP;
	}

	return update_status::UPDATE_CONTINUE;
}

update_status ModulePlayer::PostUpdate() {
	if (!dead) {
		SDL_Rect rect = currentAnimTop->GetCurrentFrame();
		App->render->Blit(texture, position.x, position.y, &rect);
		rect = currentAnimBot->GetCurrentFrame();
		App->render->Blit(texture, position.x, position.y + 31, &rect);
	}
	return update_status::UPDATE_CONTINUE;
}

void ModulePlayer::OnCollision(Collider* c1, Collider* c2) {
	if (!this->dead) {
		// Delete player
		this->dead = true;
		// Delete player collider
		c1->pendingToDelete = true;
		App->audio->PlayFx(deadFx);
		App->particles->AddParticle(App->particles->explosion, position.x, position.y - 10);
	}
}
