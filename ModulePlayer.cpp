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
	upAnimTop.PushBack({ 0,   0, 32, 32 });
	upAnimTop.PushBack({ 32,  0, 32, 32 });
	upAnimTop.PushBack({ 64,  0, 32, 32 });
	upAnimTop.PushBack({ 96,  0, 32, 32 });
	upAnimTop.PushBack({ 128, 0, 32, 32 });
	upAnimTop.PushBack({ 96,  0, 32, 32 });
	upAnimTop.PushBack({ 64,  0, 32, 32 });
	upAnimTop.PushBack({ 32,  0, 32, 32 });
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
	upRightAnimTop.PushBack({ 0,   32, 32, 32 });
	upRightAnimTop.PushBack({ 32,  32, 32, 32 });
	upRightAnimTop.PushBack({ 64,  32, 32, 32 });
	upRightAnimTop.PushBack({ 96,  32, 32, 32 });
	upRightAnimTop.PushBack({ 128, 32, 32, 32 });
	upRightAnimTop.PushBack({ 96,  32, 32, 32 });
	upRightAnimTop.PushBack({ 64,  32, 32, 32 });
	upRightAnimTop.PushBack({ 32,  32, 32, 32 });
	upRightAnimTop.loop = true;
	upRightAnimTop.speed = 0.1f;

	// Move up-right, bot
	upRightAnimBot.PushBack({ 160, 32, 32, 32 });
	upRightAnimBot.PushBack({ 192, 32, 32, 32 });
	upRightAnimBot.PushBack({ 224, 32, 32, 32 });
	upRightAnimBot.PushBack({ 256, 32, 32, 32 });
	upRightAnimBot.PushBack({ 288, 32, 32, 32 });
	upRightAnimBot.PushBack({ 256, 32, 32, 32 });
	upRightAnimBot.PushBack({ 224, 32, 32, 32 });
	upRightAnimBot.PushBack({ 192, 32, 32, 32 });
	upRightAnimBot.loop = true;
	upRightAnimBot.speed = 0.1f;

	// Move right, top
	rightAnimTop.PushBack({ 0,   64, 32, 32 });
	rightAnimTop.PushBack({ 32,  64, 32, 32 });
	rightAnimTop.PushBack({ 64,  64, 32, 32 });
	rightAnimTop.PushBack({ 96,  64, 32, 32 });
	rightAnimTop.PushBack({ 128, 64, 32, 32 });
	rightAnimTop.PushBack({ 96,  64, 32, 32 });
	rightAnimTop.PushBack({ 64,  64, 32, 32 });
	rightAnimTop.PushBack({ 32,  64, 32, 32 });
	rightAnimTop.loop = true;
	rightAnimTop.speed = 0.1f;

	// Move right, bot
	rightAnimBot.PushBack({ 160, 64, 32, 32 });
	rightAnimBot.PushBack({ 192, 64, 32, 32 });
	rightAnimBot.PushBack({ 224, 64, 32, 32 });
	rightAnimBot.PushBack({ 256, 64, 32, 32 });
	rightAnimBot.PushBack({ 288, 64, 32, 32 });
	rightAnimBot.PushBack({ 256, 64, 32, 32 });
	rightAnimBot.PushBack({ 224, 64, 32, 32 });
	rightAnimBot.PushBack({ 192, 64, 32, 32 });
	rightAnimBot.loop = true;
	rightAnimBot.speed = 0.1f;

	// Move down-right, top
	downRightAnimTop.PushBack({ 0,   96, 32, 32 });
	downRightAnimTop.PushBack({ 32,  96, 32, 32 });
	downRightAnimTop.PushBack({ 64,  96, 32, 32 });
	downRightAnimTop.PushBack({ 96,  96, 32, 32 });
	downRightAnimTop.PushBack({ 128, 96, 32, 32 });
	downRightAnimTop.PushBack({ 96,  96, 32, 32 });
	downRightAnimTop.PushBack({ 64,  96, 32, 32 });
	downRightAnimTop.PushBack({ 32,  96, 32, 32 });
	downRightAnimTop.loop = true;
	downRightAnimTop.speed = 0.1f;

	// Move down-right, bot
	downRightAnimBot.PushBack({ 160, 96, 32, 32 });
	downRightAnimBot.PushBack({ 192, 96, 32, 32 });
	downRightAnimBot.PushBack({ 224, 96, 32, 32 });
	downRightAnimBot.PushBack({ 256, 96, 32, 32 });
	downRightAnimBot.PushBack({ 288, 96, 32, 32 });
	downRightAnimBot.PushBack({ 256, 96, 32, 32 });
	downRightAnimBot.PushBack({ 224, 96, 32, 32 });
	downRightAnimBot.PushBack({ 192, 96, 32, 32 });
	downRightAnimBot.loop = true;
	downRightAnimBot.speed = 0.1f;

	// Move down, top
	downAnimTop.PushBack({ 0,   128, 32, 32 });
	downAnimTop.PushBack({ 32,  128, 32, 32 });
	downAnimTop.PushBack({ 64,  128, 32, 32 });
	downAnimTop.PushBack({ 96,  128, 32, 32 });
	downAnimTop.PushBack({ 128, 128, 32, 32 });
	downAnimTop.PushBack({ 96,  128, 32, 32 });
	downAnimTop.PushBack({ 64,  128, 32, 32 });
	downAnimTop.PushBack({ 32,  128, 32, 32 });
	downAnimTop.loop = true;
	downAnimTop.speed = 0.1f;

	// Move down, bot
	downAnimBot.PushBack({ 160, 128, 32, 32 });
	downAnimBot.PushBack({ 192, 128, 32, 32 });
	downAnimBot.PushBack({ 224, 128, 32, 32 });
	downAnimBot.PushBack({ 256, 128, 32, 32 });
	downAnimBot.PushBack({ 288, 128, 32, 32 });
	downAnimBot.PushBack({ 256, 128, 32, 32 });
	downAnimBot.PushBack({ 224, 128, 32, 32 });
	downAnimBot.PushBack({ 192, 128, 32, 32 });
	downAnimBot.loop = true;
	downAnimBot.speed = 0.1f;

	// Move down-left, top
	downLeftAnimTop.PushBack({ 0,   160, 32, 32 });
	downLeftAnimTop.PushBack({ 32,  160, 32, 32 });
	downLeftAnimTop.PushBack({ 64,  160, 32, 32 });
	downLeftAnimTop.PushBack({ 96,  160, 32, 32 });
	downLeftAnimTop.PushBack({ 128, 160, 32, 32 });
	downLeftAnimTop.PushBack({ 96,  160, 32, 32 });
	downLeftAnimTop.PushBack({ 64,  160, 32, 32 });
	downLeftAnimTop.PushBack({ 32,  160, 32, 32 });
	downLeftAnimTop.loop = true;
	downLeftAnimTop.speed = 0.1f;

	// Move down-left, bot
	downLeftAnimBot.PushBack({ 160, 160, 32, 32 });
	downLeftAnimBot.PushBack({ 192, 160, 32, 32 });
	downLeftAnimBot.PushBack({ 224, 160, 32, 32 });
	downLeftAnimBot.PushBack({ 256, 160, 32, 32 });
	downLeftAnimBot.PushBack({ 288, 160, 32, 32 });
	downLeftAnimBot.PushBack({ 256, 160, 32, 32 });
	downLeftAnimBot.PushBack({ 224, 160, 32, 32 });
	downLeftAnimBot.PushBack({ 192, 160, 32, 32 });
	downLeftAnimBot.loop = true;
	downLeftAnimBot.speed = 0.1f;

	// Move left, top
	leftAnimTop.PushBack({ 0,   192, 32, 32 });
	leftAnimTop.PushBack({ 32,  192, 32, 32 });
	leftAnimTop.PushBack({ 64,  192, 32, 32 });
	leftAnimTop.PushBack({ 96,  192, 32, 32 });
	leftAnimTop.PushBack({ 128, 192, 32, 32 });
	leftAnimTop.PushBack({ 96,  192, 32, 32 });
	leftAnimTop.PushBack({ 64,  192, 32, 32 });
	leftAnimTop.PushBack({ 32,  192, 32, 32 });
	leftAnimTop.loop = true;
	leftAnimTop.speed = 0.1f;

	// Move left, bot
	leftAnimBot.PushBack({ 160, 192, 32, 32 });
	leftAnimBot.PushBack({ 192, 192, 32, 32 });
	leftAnimBot.PushBack({ 224, 192, 32, 32 });
	leftAnimBot.PushBack({ 256, 192, 32, 32 });
	leftAnimBot.PushBack({ 288, 192, 32, 32 });
	leftAnimBot.PushBack({ 256, 192, 32, 32 });
	leftAnimBot.PushBack({ 224, 192, 32, 32 });
	leftAnimBot.PushBack({ 192, 192, 32, 32 });
	leftAnimBot.loop = true;
	leftAnimBot.speed = 0.1f;

	// Move up-left, top
	upLeftAnimTop.PushBack({ 0,   224, 32, 32 });
	upLeftAnimTop.PushBack({ 32,  224, 32, 32 });
	upLeftAnimTop.PushBack({ 64,  224, 32, 32 });
	upLeftAnimTop.PushBack({ 96,  224, 32, 32 });
	upLeftAnimTop.PushBack({ 128, 224, 32, 32 });
	upLeftAnimTop.PushBack({ 96,  224, 32, 32 });
	upLeftAnimTop.PushBack({ 64,  224, 32, 32 });
	upLeftAnimTop.PushBack({ 32,  224, 32, 32 });
	upLeftAnimTop.loop = true;
	upLeftAnimTop.speed = 0.1f;

	// Move up-left, bot
	upLeftAnimBot.PushBack({ 160, 224, 32, 32 });
	upLeftAnimBot.PushBack({ 192, 224, 32, 32 });
	upLeftAnimBot.PushBack({ 224, 224, 32, 32 });
	upLeftAnimBot.PushBack({ 256, 224, 32, 32 });
	upLeftAnimBot.PushBack({ 288, 224, 32, 32 });
	upLeftAnimBot.PushBack({ 256, 224, 32, 32 });
	upLeftAnimBot.PushBack({ 224, 224, 32, 32 });
	upLeftAnimBot.PushBack({ 192, 224, 32, 32 });
	upLeftAnimBot.loop = true;
	upLeftAnimBot.speed = 0.1f;

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
	position.x = 240;
	position.y = 120;

	// player collider
	collider = App->collisions->AddCollider({ position.x, position.y, 32, 64 }, Collider::Type::PLAYER, this);

	return ret;
}

update_status ModulePlayer::Update() {
	// Moving the player with the camera scroll

	// Change Direction
	if (App->input->keys[SDL_SCANCODE_I] != KEY_STATE::KEY_IDLE ||
		App->input->keys[SDL_SCANCODE_J] != KEY_STATE::KEY_IDLE ||
		App->input->keys[SDL_SCANCODE_K] != KEY_STATE::KEY_IDLE ||
		App->input->keys[SDL_SCANCODE_L] != KEY_STATE::KEY_IDLE) {

		// Direction to UP
		if (App->input->keys[SDL_SCANCODE_I] == KEY_STATE::KEY_REPEAT &&
			App->input->keys[SDL_SCANCODE_J] == KEY_STATE::KEY_IDLE &&
			App->input->keys[SDL_SCANCODE_K] == KEY_STATE::KEY_IDLE &&
			App->input->keys[SDL_SCANCODE_L] == KEY_STATE::KEY_IDLE) {
			direction = Directions::UP;
			currentAnimTop = &upAnimTop;
		}

		// Direction to UP_RIGHT
		if (App->input->keys[SDL_SCANCODE_I] == KEY_STATE::KEY_REPEAT &&
			App->input->keys[SDL_SCANCODE_J] == KEY_STATE::KEY_IDLE &&
			App->input->keys[SDL_SCANCODE_K] == KEY_STATE::KEY_IDLE &&
			App->input->keys[SDL_SCANCODE_L] == KEY_STATE::KEY_REPEAT) {
			direction = Directions::UP_RIGHT;
			currentAnimTop = &upRightAnimTop;
		}

		// Direction to RIGHT
		if (App->input->keys[SDL_SCANCODE_I] == KEY_STATE::KEY_IDLE &&
			App->input->keys[SDL_SCANCODE_J] == KEY_STATE::KEY_IDLE &&
			App->input->keys[SDL_SCANCODE_K] == KEY_STATE::KEY_IDLE &&
			App->input->keys[SDL_SCANCODE_L] == KEY_STATE::KEY_REPEAT) {
			direction = Directions::RIGHT;
			currentAnimTop = &rightAnimTop;
		}

		// Direction to DOWN_RIGHT
		if (App->input->keys[SDL_SCANCODE_I] == KEY_STATE::KEY_IDLE &&
			App->input->keys[SDL_SCANCODE_J] == KEY_STATE::KEY_IDLE &&
			App->input->keys[SDL_SCANCODE_K] == KEY_STATE::KEY_REPEAT &&
			App->input->keys[SDL_SCANCODE_L] == KEY_STATE::KEY_REPEAT) {
			direction = Directions::DOWN_RIGHT;
			currentAnimTop = &downRightAnimTop;
		}

		// Direction to DOWN
		if (App->input->keys[SDL_SCANCODE_I] == KEY_STATE::KEY_IDLE &&
			App->input->keys[SDL_SCANCODE_J] == KEY_STATE::KEY_IDLE &&
			App->input->keys[SDL_SCANCODE_K] == KEY_STATE::KEY_REPEAT &&
			App->input->keys[SDL_SCANCODE_L] == KEY_STATE::KEY_IDLE) {
			direction = Directions::DOWN;
			currentAnimTop = &downAnimTop;
		}

		// Direction to DOWN_LEFT
		if (App->input->keys[SDL_SCANCODE_I] == KEY_STATE::KEY_IDLE &&
			App->input->keys[SDL_SCANCODE_J] == KEY_STATE::KEY_REPEAT &&
			App->input->keys[SDL_SCANCODE_K] == KEY_STATE::KEY_REPEAT &&
			App->input->keys[SDL_SCANCODE_L] == KEY_STATE::KEY_IDLE) {
			direction = Directions::DOWN_LEFT;
			currentAnimTop = &downLeftAnimTop;
		}

		// Direction to LEFT
		if (App->input->keys[SDL_SCANCODE_I] == KEY_STATE::KEY_IDLE &&
			App->input->keys[SDL_SCANCODE_J] == KEY_STATE::KEY_REPEAT &&
			App->input->keys[SDL_SCANCODE_K] == KEY_STATE::KEY_IDLE &&
			App->input->keys[SDL_SCANCODE_L] == KEY_STATE::KEY_IDLE) {
			direction = Directions::LEFT;
			currentAnimTop = &leftAnimTop;
		}

		// Direction to UP_LEFT
		if (App->input->keys[SDL_SCANCODE_I] == KEY_STATE::KEY_REPEAT &&
			App->input->keys[SDL_SCANCODE_J] == KEY_STATE::KEY_REPEAT &&
			App->input->keys[SDL_SCANCODE_K] == KEY_STATE::KEY_IDLE &&
			App->input->keys[SDL_SCANCODE_L] == KEY_STATE::KEY_IDLE) {
			direction = Directions::UP_LEFT;
			currentAnimTop = &upLeftAnimTop;
		}
		idleAnimTop.frames[0] = currentAnimTop->frames[currentAnimTop->GetCurrentFrameNum()];
	}
	
	// Movement
	if (App->input->keys[SDL_SCANCODE_W] == KEY_STATE::KEY_IDLE &&
		App->input->keys[SDL_SCANCODE_A] == KEY_STATE::KEY_IDLE &&
		App->input->keys[SDL_SCANCODE_S] == KEY_STATE::KEY_IDLE &&
		App->input->keys[SDL_SCANCODE_D] == KEY_STATE::KEY_IDLE) {

		currentAnimTop = &idleAnimTop;
		currentAnimBot = &idleAnimBot;
	}
	else {

		// Move UP
		if (App->input->keys[SDL_SCANCODE_W] == KEY_STATE::KEY_REPEAT &&
			App->input->keys[SDL_SCANCODE_A] == KEY_STATE::KEY_IDLE &&
			App->input->keys[SDL_SCANCODE_S] == KEY_STATE::KEY_IDLE &&
			App->input->keys[SDL_SCANCODE_D] == KEY_STATE::KEY_IDLE) {
			position.y -= speed;
			if (currentAnimBot != &upAnimBot) {
				currentAnimBot = &upAnimBot;
			}
		}

		// Move UP_RIGHT
		if (App->input->keys[SDL_SCANCODE_W] == KEY_STATE::KEY_REPEAT &&
			App->input->keys[SDL_SCANCODE_A] == KEY_STATE::KEY_IDLE &&
			App->input->keys[SDL_SCANCODE_S] == KEY_STATE::KEY_IDLE &&
			App->input->keys[SDL_SCANCODE_D] == KEY_STATE::KEY_REPEAT) {
			position.y -= speed;
			position.x += speed;
			if (currentAnimBot != &upRightAnimBot) {
				currentAnimBot = &upRightAnimBot;
			}
		}

		// Move RIGHT
		if (App->input->keys[SDL_SCANCODE_W] == KEY_STATE::KEY_IDLE &&
			App->input->keys[SDL_SCANCODE_A] == KEY_STATE::KEY_IDLE &&
			App->input->keys[SDL_SCANCODE_S] == KEY_STATE::KEY_IDLE &&
			App->input->keys[SDL_SCANCODE_D] == KEY_STATE::KEY_REPEAT) {
			position.x += speed;
			if (currentAnimBot != &rightAnimBot) {
				currentAnimBot = &rightAnimBot;
			}
		}

		// Move DOWN_RIGHT
		if (App->input->keys[SDL_SCANCODE_W] == KEY_STATE::KEY_IDLE &&
			App->input->keys[SDL_SCANCODE_A] == KEY_STATE::KEY_IDLE &&
			App->input->keys[SDL_SCANCODE_S] == KEY_STATE::KEY_REPEAT &&
			App->input->keys[SDL_SCANCODE_D] == KEY_STATE::KEY_REPEAT) {
			position.y += speed;
			position.x += speed;
			if (currentAnimBot != &downRightAnimBot) {
				currentAnimBot = &downRightAnimBot;
			}
		}

		// Move DOWN
		if (App->input->keys[SDL_SCANCODE_W] == KEY_STATE::KEY_IDLE &&
			App->input->keys[SDL_SCANCODE_A] == KEY_STATE::KEY_IDLE &&
			App->input->keys[SDL_SCANCODE_S] == KEY_STATE::KEY_REPEAT &&
			App->input->keys[SDL_SCANCODE_D] == KEY_STATE::KEY_IDLE) {
			position.y += speed;
			if (currentAnimBot != &downAnimBot) {
				currentAnimBot = &downAnimBot;
			}
		}

		// Move DOWN_LEFT
		if (App->input->keys[SDL_SCANCODE_W] == KEY_STATE::KEY_IDLE &&
			App->input->keys[SDL_SCANCODE_A] == KEY_STATE::KEY_REPEAT &&
			App->input->keys[SDL_SCANCODE_S] == KEY_STATE::KEY_REPEAT &&
			App->input->keys[SDL_SCANCODE_D] == KEY_STATE::KEY_IDLE) {
			position.y += speed;
			position.x -= speed;
			if (currentAnimBot != &downLeftAnimBot) {
				currentAnimBot = &downLeftAnimBot;
			}
		}

		// Move LEFT
		if (App->input->keys[SDL_SCANCODE_W] == KEY_STATE::KEY_IDLE &&
			App->input->keys[SDL_SCANCODE_A] == KEY_STATE::KEY_REPEAT &&
			App->input->keys[SDL_SCANCODE_S] == KEY_STATE::KEY_IDLE &&
			App->input->keys[SDL_SCANCODE_D] == KEY_STATE::KEY_IDLE) {
			position.x -= speed;
			if (currentAnimBot != &leftAnimBot) {
				currentAnimBot = &leftAnimBot;
			}
		}

		// Move UP_LEFT
		if (App->input->keys[SDL_SCANCODE_W] == KEY_STATE::KEY_REPEAT &&
			App->input->keys[SDL_SCANCODE_A] == KEY_STATE::KEY_REPEAT &&
			App->input->keys[SDL_SCANCODE_S] == KEY_STATE::KEY_IDLE &&
			App->input->keys[SDL_SCANCODE_D] == KEY_STATE::KEY_IDLE) {
			position.y -= speed;
			position.x -= speed;
			if (currentAnimBot != &upLeftAnimBot) {
				currentAnimBot = &upLeftAnimBot;
			}
		}

		//activate top anim when moving
		switch (direction)
		{
		case UP:
			currentAnimTop = &upAnimTop;
			break;
		case DOWN:
			currentAnimTop = &downAnimTop;
			break;
		case RIGHT:
			currentAnimTop = &rightAnimTop;
			break;
		case LEFT:
			currentAnimTop = &leftAnimTop;
			break;
		case UP_RIGHT:
			currentAnimTop = &upRightAnimTop;
			break;
		case UP_LEFT:
			currentAnimTop = &upLeftAnimTop;
			break;
		case DOWN_RIGHT:
			currentAnimTop = &downRightAnimTop;
			break;
		case DOWN_LEFT:
			currentAnimTop = &downLeftAnimTop;
			break;
		default:
			break;
		}

		//set the idles to the current frame
		idleAnimTop.frames[0] = currentAnimTop->GetCurrentFrame();
		idleAnimBot.frames[0] = currentAnimBot->GetCurrentFrame();
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
