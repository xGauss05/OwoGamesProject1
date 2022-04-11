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
	// Move up, top
	upAnimTop.PushBack({ 0, 0, 32, 32 });
	upAnimTop.PushBack({ 33, 0, 32, 32 });
	upAnimTop.PushBack({ 65, 0, 32, 32 });
	upAnimTop.PushBack({ 97, 0, 32, 32 });
	upAnimTop.PushBack({ 129, 0, 32, 32 });
	upAnimTop.PushBack({ 97, 0, 32, 32 });
	upAnimTop.PushBack({ 65, 0, 32, 32 });
	upAnimTop.PushBack({ 33, 0, 32, 32 });
	upAnimTop.loop = true;
	upAnimTop.speed = 0.1f;
	// Move up, bot
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

	// Move up-right, top
	upRightAnimTop.PushBack({ 160, 31, 32, 32 });
	upRightAnimTop.PushBack({ 192, 31, 32, 32 });
	upRightAnimTop.PushBack({ 224, 31, 32, 32 });
	upRightAnimTop.PushBack({ 256, 31, 32, 32 });
	upRightAnimTop.PushBack({ 288, 31, 32, 32 });
	upRightAnimTop.PushBack({ 256, 31, 32, 32 });
	upRightAnimTop.PushBack({ 224, 31, 32, 32 });
	upRightAnimTop.PushBack({ 192, 31, 32, 32 });
	upRightAnimTop.loop = true;
	upRightAnimTop.speed = 0.1f;
	// Move up-right, bot
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

	// Move up-left, top
	upLeftAnimTop.PushBack({ 0, 225, 32, 32 });
	upLeftAnimTop.PushBack({ 33, 225, 32, 32 });
	upLeftAnimTop.PushBack({ 65, 225, 32, 32 });
	upLeftAnimTop.PushBack({ 97, 225, 32, 32 });
	upLeftAnimTop.PushBack({ 129, 225, 32, 32 });
	upLeftAnimTop.PushBack({ 97, 225, 32, 32 });
	upLeftAnimTop.PushBack({ 65, 225, 32, 32 });
	upLeftAnimTop.PushBack({ 33, 225, 32, 32 });
	upLeftAnimTop.loop = true;
	upLeftAnimTop.speed = 0.1f;
	// Move up-left, bot
	upLeftAnimBot.PushBack({ 160, 225, 32, 32 });
	upLeftAnimBot.PushBack({ 192, 225, 32, 32 });
	upLeftAnimBot.PushBack({ 224, 225, 32, 32 });
	upLeftAnimBot.PushBack({ 256, 225, 32, 32 });
	upLeftAnimBot.PushBack({ 288, 225, 32, 32 });
	upLeftAnimBot.PushBack({ 256, 225, 32, 32 });
	upLeftAnimBot.PushBack({ 224, 225, 32, 32 });
	upLeftAnimBot.PushBack({ 192, 225, 32, 32 });
	upLeftAnimBot.loop = true;
	upLeftAnimBot.speed = 0.1f;

	// Move down, top
	downAnimTop.PushBack({ 0, 128, 32, 32 });
	downAnimTop.PushBack({ 33, 128, 32, 32 });
	downAnimTop.PushBack({ 65, 128, 32, 32 });
	downAnimTop.PushBack({ 97, 128, 32, 32 });
	downAnimTop.PushBack({ 129, 128, 32, 32 });
	downAnimTop.PushBack({ 97, 128, 32, 32 });
	downAnimTop.PushBack({ 65, 128, 32, 32 });
	downAnimTop.PushBack({ 33, 128, 32, 32 });
	downAnimTop.loop = true;
	downAnimTop.speed = 0.1f;

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

	// Move down-left

	// Move down-right
}

ModulePlayer::~ModulePlayer() {
}

bool ModulePlayer::Start() {
	LOG("Loading player textures");

	bool ret = true;
	direction = UP;
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

	// Look Directions
	// Look UP
	if (App->input->keys[SDL_SCANCODE_I] == KEY_STATE::KEY_REPEAT &&
		App->input->keys[SDL_SCANCODE_J] == KEY_STATE::KEY_IDLE &&
		App->input->keys[SDL_SCANCODE_K] == KEY_STATE::KEY_IDLE &&
		App->input->keys[SDL_SCANCODE_L] == KEY_STATE::KEY_IDLE) {
		direction = Directions::UP;
		if (currentAnimTop != &upAnimTop) {
			upAnimTop.Reset();
			currentAnimTop = &upAnimTop;
		}
	}

	// Look UP_RIGHT
	if (App->input->keys[SDL_SCANCODE_I] == KEY_STATE::KEY_REPEAT &&
		App->input->keys[SDL_SCANCODE_J] == KEY_STATE::KEY_IDLE &&
		App->input->keys[SDL_SCANCODE_K] == KEY_STATE::KEY_IDLE &&
		App->input->keys[SDL_SCANCODE_L] == KEY_STATE::KEY_REPEAT) {
		direction = Directions::UP_RIGHT;
		if (currentAnimTop != &upRightAnimTop) {
			upRightAnimTop.Reset();
			currentAnimTop = &upRightAnimTop;
		}
	}

	// Look RIGHT
	if (App->input->keys[SDL_SCANCODE_I] == KEY_STATE::KEY_IDLE &&
		App->input->keys[SDL_SCANCODE_J] == KEY_STATE::KEY_IDLE &&
		App->input->keys[SDL_SCANCODE_K] == KEY_STATE::KEY_IDLE &&
		App->input->keys[SDL_SCANCODE_L] == KEY_STATE::KEY_REPEAT) {
		direction = Directions::RIGHT;
		if (currentAnimTop != &rightAnimTop) {
			rightAnimTop.Reset();
			currentAnimTop = &rightAnimTop;
		}
	}

	// Look DOWN_RIGHT
	if (App->input->keys[SDL_SCANCODE_I] == KEY_STATE::KEY_IDLE &&
		App->input->keys[SDL_SCANCODE_J] == KEY_STATE::KEY_IDLE &&
		App->input->keys[SDL_SCANCODE_K] == KEY_STATE::KEY_REPEAT &&
		App->input->keys[SDL_SCANCODE_L] == KEY_STATE::KEY_REPEAT) {
		direction = Directions::DOWN_RIGHT;
		if (currentAnimTop != &downRightAnimTop) {
			downRightAnimTop.Reset();
			currentAnimTop = &downRightAnimTop;
		}
	}

	// Look DOWN
	if (App->input->keys[SDL_SCANCODE_I] == KEY_STATE::KEY_IDLE &&
		App->input->keys[SDL_SCANCODE_J] == KEY_STATE::KEY_IDLE &&
		App->input->keys[SDL_SCANCODE_K] == KEY_STATE::KEY_REPEAT &&
		App->input->keys[SDL_SCANCODE_L] == KEY_STATE::KEY_IDLE) {
		direction = Directions::DOWN;
		if (currentAnimTop != &downAnimTop) {
			downAnimTop.Reset();
			currentAnimTop = &downAnimTop;
		}
	}

	// Look DOWN_LEFT
	if (App->input->keys[SDL_SCANCODE_I] == KEY_STATE::KEY_IDLE &&
		App->input->keys[SDL_SCANCODE_J] == KEY_STATE::KEY_REPEAT &&
		App->input->keys[SDL_SCANCODE_K] == KEY_STATE::KEY_REPEAT &&
		App->input->keys[SDL_SCANCODE_L] == KEY_STATE::KEY_IDLE) {
		direction = Directions::DOWN_LEFT;
		if (currentAnimTop != &downLeftAnimTop) {
			downLeftAnimTop.Reset();
			currentAnimTop = &downLeftAnimTop;
		}
	}

	// Look LEFT
	if (App->input->keys[SDL_SCANCODE_I] == KEY_STATE::KEY_IDLE &&
		App->input->keys[SDL_SCANCODE_J] == KEY_STATE::KEY_REPEAT &&
		App->input->keys[SDL_SCANCODE_K] == KEY_STATE::KEY_IDLE &&
		App->input->keys[SDL_SCANCODE_L] == KEY_STATE::KEY_IDLE) {
		direction = Directions::LEFT;
		if (currentAnimTop != &leftAnimTop) {
			leftAnimTop.Reset();
			currentAnimTop = &leftAnimTop;
		}
	}

	// Look UP_LEFT
	if (App->input->keys[SDL_SCANCODE_I] == KEY_STATE::KEY_REPEAT &&
		App->input->keys[SDL_SCANCODE_J] == KEY_STATE::KEY_REPEAT &&
		App->input->keys[SDL_SCANCODE_K] == KEY_STATE::KEY_IDLE &&
		App->input->keys[SDL_SCANCODE_L] == KEY_STATE::KEY_IDLE) {
		direction = Directions::UP_LEFT;
		if (currentAnimTop != &upLeftAnimTop) {
			upLeftAnimTop.Reset();
			currentAnimTop = &upLeftAnimTop;
		}
	}

	// Movement
	// Move UP
	if (App->input->keys[SDL_SCANCODE_W] == KEY_STATE::KEY_REPEAT &&
		App->input->keys[SDL_SCANCODE_D] == KEY_STATE::KEY_IDLE &&
		App->input->keys[SDL_SCANCODE_A] == KEY_STATE::KEY_IDLE &&
		App->input->keys[SDL_SCANCODE_S] == KEY_STATE::KEY_IDLE) {
		position.y -= speed;
		if (currentAnimBot != &upAnimBot) {
			upAnimBot.Reset();
			currentAnimBot = &upAnimBot;
		}
	}

	// Move UP_RIGHT
	if (App->input->keys[SDL_SCANCODE_W] == KEY_STATE::KEY_REPEAT &&
		App->input->keys[SDL_SCANCODE_D] == KEY_STATE::KEY_REPEAT &&
		App->input->keys[SDL_SCANCODE_S] == KEY_STATE::KEY_IDLE &&
		App->input->keys[SDL_SCANCODE_A] == KEY_STATE::KEY_IDLE) {
		position.y -= speed;
		position.x += speed;
		if (currentAnimBot != &upRightAnimBot) {
			upRightAnimBot.Reset();
			currentAnimBot = &upRightAnimBot;
		}
	}

	// Move UP_LEFT
	if (App->input->keys[SDL_SCANCODE_W] == KEY_STATE::KEY_REPEAT &&
		App->input->keys[SDL_SCANCODE_A] == KEY_STATE::KEY_REPEAT &&
		App->input->keys[SDL_SCANCODE_D] == KEY_STATE::KEY_IDLE &&
		App->input->keys[SDL_SCANCODE_S] == KEY_STATE::KEY_IDLE) {
		position.y -= speed;
		position.x -= speed;
		if (currentAnimBot != &upLeftAnimBot) {
			upLeftAnimBot.Reset();
			currentAnimBot = &upLeftAnimBot;
		}
	}

	// Move DOWN
	if (App->input->keys[SDL_SCANCODE_S] == KEY_STATE::KEY_REPEAT) {
		position.y += speed;
		if (currentAnimBot != &downAnimBot) {
			downAnimBot.Reset();
			currentAnimBot = &downAnimBot;
		}
	}

	// Move DOWN_RIGHT
	if (App->input->keys[SDL_SCANCODE_S] == KEY_STATE::KEY_REPEAT &&
		App->input->keys[SDL_SCANCODE_D] == KEY_STATE::KEY_REPEAT &&
		App->input->keys[SDL_SCANCODE_W] == KEY_STATE::KEY_IDLE &&
		App->input->keys[SDL_SCANCODE_A] == KEY_STATE::KEY_IDLE) {
		position.y -= speed;
		position.x += speed;
		if (currentAnimBot != &upRightAnimBot) {
			upRightAnimBot.Reset();
			currentAnimBot = &upRightAnimBot;
		}
	}

	// Move DOWN_LEFT
	if (App->input->keys[SDL_SCANCODE_S] == KEY_STATE::KEY_REPEAT &&
		App->input->keys[SDL_SCANCODE_A] == KEY_STATE::KEY_REPEAT &&
		App->input->keys[SDL_SCANCODE_W] == KEY_STATE::KEY_IDLE &&
		App->input->keys[SDL_SCANCODE_D] == KEY_STATE::KEY_IDLE) {
		position.y -= speed;
		position.x += speed;
		if (currentAnimBot != &upRightAnimBot) {
			upRightAnimBot.Reset();
			currentAnimBot = &upRightAnimBot;
		}
	}

	// Move LEFT
	if (App->input->keys[SDL_SCANCODE_A] == KEY_STATE::KEY_REPEAT &&
		App->input->keys[SDL_SCANCODE_W] == KEY_STATE::KEY_IDLE &&
		App->input->keys[SDL_SCANCODE_S] == KEY_STATE::KEY_IDLE &&
		App->input->keys[SDL_SCANCODE_D] == KEY_STATE::KEY_IDLE) {
		position.x -= speed;
		if (currentAnimBot != &leftAnimBot) {
			leftAnimBot.Reset();
			currentAnimBot = &leftAnimBot;
		}
	}

	// Move RIGHT
	if (App->input->keys[SDL_SCANCODE_D] == KEY_STATE::KEY_REPEAT &&
		App->input->keys[SDL_SCANCODE_W] == KEY_STATE::KEY_IDLE &&
		App->input->keys[SDL_SCANCODE_A] == KEY_STATE::KEY_IDLE &&
		App->input->keys[SDL_SCANCODE_S] == KEY_STATE::KEY_IDLE) {
		position.x += speed;
		if (currentAnimBot != &rightAnimBot) {
			rightAnimBot.Reset();
			currentAnimBot = &rightAnimBot;
		}
	}

	if (App->input->keys[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_DOWN) {

		App->audio->PlayFx(shotFx);

		switch (direction) {
		case Directions::UP:
		{
			App->particles->shot.speed.x = 0;
			App->particles->shot.speed.y = -5;
			App->particles->AddParticle(App->particles->shot, position.x + 13, position.y, Collider::Type::PLAYER_SHOT);
		}
		break;
		case Directions::UP_RIGHT:
		{
			App->particles->shot.speed.x = 5;
			App->particles->shot.speed.y = -5;
			App->particles->AddParticle(App->particles->shot, position.x + 32, position.y, Collider::Type::PLAYER_SHOT);
		}
		break;
		case Directions::UP_LEFT:
		{
			App->particles->shot.speed.x = -5;
			App->particles->shot.speed.y = -5;
			App->particles->AddParticle(App->particles->shot, position.x, position.y, Collider::Type::PLAYER_SHOT);
		}
		break;
		case Directions::DOWN:
		{
			App->particles->shot.speed.x = 0;
			App->particles->shot.speed.y = 5;
			App->particles->AddParticle(App->particles->shot, position.x + 13, position.y + 64, Collider::Type::PLAYER_SHOT);
		}
		break;
		case Directions::DOWN_RIGHT:
		{
			App->particles->shot.speed.x = 5;
			App->particles->shot.speed.y = 5;
			App->particles->AddParticle(App->particles->shot, position.x + 32, position.y+64, Collider::Type::PLAYER_SHOT);
		}
		break;
		case Directions::DOWN_LEFT:
		{
			App->particles->shot.speed.x = -5;
			App->particles->shot.speed.y = 5;
			App->particles->AddParticle(App->particles->shot, position.x, position.y + 64, Collider::Type::PLAYER_SHOT);
		}
		break;
		case Directions::RIGHT:
		{
			App->particles->shot.speed.x = 5;
			App->particles->shot.speed.y = 0;
			App->particles->AddParticle(App->particles->shot, position.x + 32, position.y + 29, Collider::Type::PLAYER_SHOT);
		}
		break;
		case Directions::LEFT:
		{
			App->particles->shot.speed.x = -5;
			App->particles->shot.speed.y = 0;
			App->particles->AddParticle(App->particles->shot, position.x, position.y + 29, Collider::Type::PLAYER_SHOT);
		}
		break;
		}
	}

	// If no up/down movement detected, set the current animation back to idle
	// Needs to be improved?
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
