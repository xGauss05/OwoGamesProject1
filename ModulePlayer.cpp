#include "ModulePlayer.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleParticles.h"
#include "ModuleAudio.h"
#include "ModuleCollisions.h"

#include "SDL/include/SDL_scancode.h"

ModulePlayer::ModulePlayer(bool startEnabled) : Module(startEnabled) {
	direction = UP;
	weapon = NORMAL;
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

	// Death animation, top 
	deathAnimTop.PushBack({ 0,   320, 32, 32 });
	deathAnimTop.PushBack({ 32,  320, 32, 32 });
	deathAnimTop.PushBack({ 64,  320, 32, 32 });
	deathAnimTop.PushBack({ 96,  320, 32, 32 });
	deathAnimTop.PushBack({ 128, 320, 32, 32 });
	deathAnimTop.PushBack({ 160, 320, 32, 32 });
	deathAnimTop.PushBack({ 192, 320, 32, 32 });
	deathAnimTop.PushBack({ 224, 320, 32, 32 });
	deathAnimTop.PushBack({ 256, 320, 32, 32 });
	deathAnimTop.PushBack({ 288, 320, 32, 32 });
	deathAnimTop.speed = 0.15f;
	deathAnimTop.loop = false;

	// Death animation, bot
	deathAnimBot.PushBack({ 0,   352, 32, 32 });
	deathAnimBot.PushBack({ 32,  352, 32, 32 });
	deathAnimBot.PushBack({ 64,  352, 32, 32 });
	deathAnimBot.PushBack({ 96,  352, 32, 32 });
	deathAnimBot.PushBack({ 128, 352, 32, 32 });
	deathAnimBot.PushBack({ 160, 352, 32, 32 });
	deathAnimBot.PushBack({ 192, 352, 32, 32 });
	deathAnimBot.PushBack({ 224, 352, 32, 32 });
	deathAnimBot.PushBack({ 256, 352, 32, 32 });
	deathAnimBot.PushBack({ 288, 352, 32, 32 });
	deathAnimBot.speed = 0.15f;
	deathAnimBot.loop = false;

}

ModulePlayer::~ModulePlayer() {
}

bool ModulePlayer::Start() {
	LOG("Loading player textures");

	bool ret = true;

	texture = App->textures->Load("img/sprites/player.png"); // player spritesheet
	currentAnimTop = &idleAnimTop;
	currentAnimBot = &idleAnimBot;

	dead = false;

	// initiate player audios here
	shotFx = App->audio->LoadFx("sounds/sfx/142.wav"); // shot sfx
	deadFx = App->audio->LoadFx("sounds/sfx/195.wav"); // dead sfx
	heavyRifleFx = App->audio->LoadFx("sounds/sfx/153.wav");
	flamethrowerFx = App->audio->LoadFx("sounds/sfx/136.wav");

	// initial position
	position.x = 240;
	position.y = 120;

	// player collider
	collider = App->collisions->AddCollider({ position.x, position.y, 32, 64 }, Collider::Type::PLAYER, this);

	return ret;
}

void shootNormal() {
	switch (App->player->direction) {
	case Directions::UP:
	{
		App->particles->AddParticle(App->particles->shot_up, App->player->position.x + 13, App->player->position.y, Collider::Type::PLAYER_SHOT);
	}
	break;
	case Directions::UP_RIGHT:
	{
		App->particles->AddParticle(App->particles->shot_up_right, App->player->position.x + 32, App->player->position.y, Collider::Type::PLAYER_SHOT);
	}
	break;
	case Directions::UP_LEFT:
	{
		App->particles->AddParticle(App->particles->shot_up_left, App->player->position.x, App->player->position.y, Collider::Type::PLAYER_SHOT);
	}
	break;
	case Directions::DOWN:
	{
		App->particles->AddParticle(App->particles->shot_down, App->player->position.x + 13, App->player->position.y + 64, Collider::Type::PLAYER_SHOT);
	}
	break;
	case Directions::DOWN_RIGHT:
	{
		App->particles->AddParticle(App->particles->shot_down_right, App->player->position.x + 32, App->player->position.y + 64, Collider::Type::PLAYER_SHOT);
	}
	break;
	case Directions::DOWN_LEFT:
	{
		App->particles->AddParticle(App->particles->shot_down_left, App->player->position.x, App->player->position.y + 64, Collider::Type::PLAYER_SHOT);
	}
	break;
	case Directions::RIGHT:
	{
		App->particles->AddParticle(App->particles->shot_right, App->player->position.x + 32, App->player->position.y + 29, Collider::Type::PLAYER_SHOT);
	}
	break;
	case Directions::LEFT:
	{
		App->particles->AddParticle(App->particles->shot_left, App->player->position.x, App->player->position.y + 29, Collider::Type::PLAYER_SHOT);
	}
	break;
	}
}

void shootHeavyRifle() {
	switch (App->player->direction) {
	case Directions::UP:
	{
		App->particles->AddParticle(App->particles->hrifle_up, App->player->position.x + 13, App->player->position.y, Collider::Type::PLAYER_SHOT);
	}
	break;
	case Directions::UP_RIGHT:
	{
		App->particles->AddParticle(App->particles->hrifle_up_right, App->player->position.x + 32, App->player->position.y, Collider::Type::PLAYER_SHOT);
	}
	break;
	case Directions::UP_LEFT:
	{
		App->particles->AddParticle(App->particles->hrifle_up_left, App->player->position.x, App->player->position.y, Collider::Type::PLAYER_SHOT);
	}
	break;
	case Directions::DOWN:
	{
		App->particles->AddParticle(App->particles->hrifle_down, App->player->position.x + 13, App->player->position.y + 64, Collider::Type::PLAYER_SHOT);
	}
	break;
	case Directions::DOWN_RIGHT:
	{
		App->particles->AddParticle(App->particles->hrifle_down_right, App->player->position.x + 32, App->player->position.y + 64, Collider::Type::PLAYER_SHOT);
	}
	break;
	case Directions::DOWN_LEFT:
	{
		App->particles->AddParticle(App->particles->hrifle_down_left, App->player->position.x, App->player->position.y + 64, Collider::Type::PLAYER_SHOT);
	}
	break;
	case Directions::RIGHT:
	{
		App->particles->AddParticle(App->particles->hrifle_right, App->player->position.x + 32, App->player->position.y + 29, Collider::Type::PLAYER_SHOT);
	}
	break;
	case Directions::LEFT:
	{
		App->particles->AddParticle(App->particles->hrifle_left, App->player->position.x, App->player->position.y + 29, Collider::Type::PLAYER_SHOT);
	}
	break;
	}
}

void shootFlamethrower() {
	switch (App->player->direction) {
	case Directions::UP:
	{
		App->particles->AddParticle(App->particles->fthrower_up, App->player->position.x + 13, App->player->position.y, Collider::Type::PLAYER_SHOT);
	}
	break;
	case Directions::UP_RIGHT:
	{
		App->particles->AddParticle(App->particles->fthrower_up_right, App->player->position.x + 32, App->player->position.y, Collider::Type::PLAYER_SHOT);
	}
	break;
	case Directions::UP_LEFT:
	{
		App->particles->AddParticle(App->particles->fthrower_up_left, App->player->position.x, App->player->position.y, Collider::Type::PLAYER_SHOT);
	}
	break;
	case Directions::DOWN:
	{
		App->particles->AddParticle(App->particles->fthrower_down, App->player->position.x + 13, App->player->position.y + 64, Collider::Type::PLAYER_SHOT);
	}
	break;
	case Directions::DOWN_RIGHT:
	{
		App->particles->AddParticle(App->particles->fthrower_down_right, App->player->position.x + 32, App->player->position.y + 64, Collider::Type::PLAYER_SHOT);
	}
	break;
	case Directions::DOWN_LEFT:
	{
		App->particles->AddParticle(App->particles->fthrower_down_left, App->player->position.x, App->player->position.y + 64, Collider::Type::PLAYER_SHOT);
	}
	break;
	case Directions::RIGHT:
	{
		App->particles->AddParticle(App->particles->fthrower_right, App->player->position.x + 32, App->player->position.y + 29, Collider::Type::PLAYER_SHOT);
	}
	break;
	case Directions::LEFT:
	{
		App->particles->AddParticle(App->particles->fthrower_left, App->player->position.x, App->player->position.y + 29, Collider::Type::PLAYER_SHOT);
	}
	break;
	}
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
	} else {

		// Move UP
		if (App->input->keys[SDL_SCANCODE_W] == KEY_STATE::KEY_REPEAT &&
			App->input->keys[SDL_SCANCODE_A] == KEY_STATE::KEY_IDLE &&
			App->input->keys[SDL_SCANCODE_S] == KEY_STATE::KEY_IDLE &&
			App->input->keys[SDL_SCANCODE_D] == KEY_STATE::KEY_IDLE) {
			position.y -= speed;
			movementDir = UP;
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
			movementDir = UP_RIGHT;
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
			movementDir = RIGHT;
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
			movementDir = DOWN_RIGHT;
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
			movementDir = DOWN;
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
			movementDir = DOWN_LEFT;
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
			movementDir = LEFT;
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
			movementDir = UP_LEFT;
			if (currentAnimBot != &upLeftAnimBot) {
				currentAnimBot = &upLeftAnimBot;
			}
		}

		//activate top anim when moving
		switch (direction) {
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

	if (ammunition == 0) {
		weapon = Weapon::NORMAL;
	}



	if (!dead) {
		if (App->input->keys[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_DOWN) {
			switch (weapon) {
			case Weapon::FLAMETHROWER:
			{
				App->audio->PlayFx(flamethrowerFx);
				ammunition--;
				shootFlamethrower();
			} break;
			case Weapon::HEAVY_RIFLE:
			{
				App->audio->PlayFx(heavyRifleFx);
				ammunition--;
				shootHeavyRifle();
			} break;
			case Weapon::NORMAL:
			{
				App->audio->PlayFx(shotFx);
				shootNormal();
			}break;
			}
		}
	}

	// If no up/down movement detected, set the current animation back to idle
	// Needs to be improved?
	if (App->input->keys[SDL_SCANCODE_S] == KEY_STATE::KEY_IDLE
		&& App->input->keys[SDL_SCANCODE_W] == KEY_STATE::KEY_IDLE) {
		/*	currentAnimTop = &idleAnimTop;
			currentAnimBot = &idleAnimBot;*/
	}

	if (dead) {
		// need to implement death behaviour
		currentAnimTop = &deathAnimTop;
		currentAnimBot = &deathAnimBot;
	}

	if (App->input->keys[SDL_SCANCODE_F1] == KEY_STATE::KEY_DOWN) {
		godMode = !godMode;
	}

	// Updates player collider position
	collider->SetPos(position.x, position.y);
	currentAnimTop->Update();
	currentAnimBot->Update();

	if (App->input->keys[SDL_SCANCODE_ESCAPE] == KEY_STATE::KEY_REPEAT) {
		return update_status::UPDATE_STOP;
	}

	return update_status::UPDATE_CONTINUE;
}

update_status ModulePlayer::PostUpdate() {
	//if (!dead) {
	SDL_Rect rect = currentAnimBot->GetCurrentFrame();
	App->render->Blit(texture, position.x, position.y + 29, &rect);
	rect = currentAnimTop->GetCurrentFrame();
	App->render->Blit(texture, position.x, position.y, &rect);
	//}
	return update_status::UPDATE_CONTINUE;
}

void ModulePlayer::OnCollision(Collider* c1, Collider* c2) {
	if (c1 == collider) {
		switch (c2->type) {
		case Collider::Type::ENEMY:
		{
			if (godMode == false) {
				App->audio->PlayFx(deadFx);

				this->dead = true;
			}
		} break;
		case Collider::Type::ENEMY_SHOT:
		{
			if (godMode == false) {
				App->audio->PlayFx(deadFx);

				this->dead = true;
			}
		} break;
		case Collider::Type::POWER_UP:
		{
			// sound plays at Powerup.cpp
			// weapon changes at each Powerup_(weaponname).cpp
			c2->pendingToDelete = true;
			ammunition = MAX_AMMO;
		} break;
		case Collider::Type::WALL:
		{
			switch (movementDir) {
			case UP:
				position.y += 1;
				break;
			case DOWN:
				position.y -= 1;
				break;
			case RIGHT:
				position.x -= 1;
				break;
			case LEFT:
				position.x += 1;
				break;
			case UP_RIGHT:
				position.y += 1;
				position.x -= 1;
				break;
			case UP_LEFT:
				position.y += 1;
				position.x += 1;
				break;
			case DOWN_RIGHT:
				position.y -= 1;
				position.x -= 1;
				break;
			case DOWN_LEFT:
				position.y -= 1;
				position.x += 1;
				break;
			default:
				break;
			}
		}

		}
	}
}
