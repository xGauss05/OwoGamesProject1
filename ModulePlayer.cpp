#include "ModulePlayer.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleParticles.h"
#include "ModuleAudio.h"
#include "ModuleCollisions.h"
#include "ModuleFadeToBlack.h"

#include "Globals.h"

#include "SDL/include/SDL_scancode.h"

ushort deathCooldown = 0;

ModulePlayer::ModulePlayer(bool startEnabled) : Module(startEnabled) {
	facing = Directions::UP;
	weapon = Weapon::NORMAL;
	movementDir = Directions::UP;

	// idle animation - just one sprite
	idleAnimTop.PushBack({ 0, 0, 32, 32 });
	idleAnimBot.PushBack({ 256, 0, 32, 32 });

	// Animations ---
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

	// Water animation
	waterAnimBot.PushBack({ 160, 256, 32, 32 });
	waterAnimBot.PushBack({ 192, 256, 32, 32 });
	waterAnimBot.PushBack({ 224, 256, 32, 32 });
	waterAnimBot.PushBack({ 256, 256, 32, 32 });
	waterAnimBot.loop = true;
	waterAnimBot.speed = 0.1f;

	//trench animation
	trenchAnimBot.PushBack({ 160, 288, 32, 32 });
	trenchAnimBot.PushBack({ 192, 288, 32, 32 });
	trenchAnimBot.loop = true;
	trenchAnimBot.speed = 0.1f;

	// Normal weapon animations
	upNorWeaponAnim.PushBack({ 0, 0, 32,32 });
	upRightNorWeaponAnim.PushBack({ 32,0, 32,32 });
	upLeftNorWeaponAnim.PushBack({ 224,0, 32,32 });
	downNorWeaponAnim.PushBack({ 128,0, 32,32 });
	downRightNorWeaponAnim.PushBack({ 96,0, 32,32 });
	downLeftNorWeaponAnim.PushBack({ 160,0, 32,32 });
	rightNorWeaponAnim.PushBack({ 64,0, 32,32 });
	leftNorWeaponAnim.PushBack({ 192,0, 32,32 });

	// Normal weapon shooting animations
	upShotNorWeaponAnim.PushBack({ 0, 32, 32,32 });
	upRightShotNorWeaponAnim.PushBack({ 32,32, 32,32 });
	upLeftShotNorWeaponAnim.PushBack({ 224,32, 32,32 });
	downShotNorWeaponAnim.PushBack({ 128,32, 32,32 });
	downRightShotNorWeaponAnim.PushBack({ 96,32, 32,32 });
	downLeftShotNorWeaponAnim.PushBack({ 160,32, 32,32 });
	rightShotNorWeaponAnim.PushBack({ 64,32, 32,32 });
	leftShotNorWeaponAnim.PushBack({ 192,32, 32,32 });

	// Powerup weapon animations
	upPowWeaponAnim.PushBack({ 0, 64, 32,32 });
	upRightPowWeaponAnim.PushBack({ 32,64, 32,32 });
	upLeftPowWeaponAnim.PushBack({ 224,64, 32,32 });
	downPowWeaponAnim.PushBack({ 128,64, 32,32 });
	downRightPowWeaponAnim.PushBack({ 96,64, 32,32 });
	downLeftPowWeaponAnim.PushBack({ 160,64, 32,32 });
	rightPowWeaponAnim.PushBack({ 64,64, 32,32 });
	leftPowWeaponAnim.PushBack({ 192,64, 32,32 });

	// Powerup weapon shooting animations
	upShotPowWeaponAnim.PushBack({ 0, 96, 32,32 });
	upRightShotPowWeaponAnim.PushBack({ 32,96, 32,32 });
	upLeftShotPowWeaponAnim.PushBack({ 224,96, 32,32 });
	downShotPowWeaponAnim.PushBack({ 128,96, 32,32 });
	downRightShotPowWeaponAnim.PushBack({ 96,96, 32,32 });
	downLeftShotPowWeaponAnim.PushBack({ 160,96, 32,32 });
	rightShotPowWeaponAnim.PushBack({ 64,96, 32,32 });
	leftShotPowWeaponAnim.PushBack({ 192,96, 32,32 });
}

ModulePlayer::~ModulePlayer() {
}

bool ModulePlayer::Start() {
	LOG("Loading player textures");

	bool ret = true;

	playerTexture = App->textures->Load("img/sprites/player.png"); // player spritesheet
	weaponTexture = App->textures->Load("img/sprites/weapon.png"); // weapon spritesheet
	currentAnimTop = &idleAnimTop;
	currentAnimBot = &idleAnimBot;
	currentWeaponAnim = &upNorWeaponAnim;
	facing = Directions::UP;
	weapon = Weapon::NORMAL;
	movementDir = Directions::UP;
	dead = false;
	godMode = false;

	// Initiate player audios here
	shotFx = App->audio->LoadFx("sounds/sfx/142.wav"); // shot sfx
	deadFx = App->audio->LoadFx("sounds/sfx/195.wav"); // dead sfx
	heavyRifleFx = App->audio->LoadFx("sounds/sfx/153.wav");
	flamethrowerFx = App->audio->LoadFx("sounds/sfx/136.wav");

	// Initial position
	position.x = 240;
	position.y = 120;

	// Player collider
	collider = App->collisions->AddCollider({ position.x, position.y, 32, 64 }, Collider::Type::PLAYER, this);

	return ret;
}

void ModulePlayer::shootNormal() {
	switch (facing) {
	case Directions::UP:
		App->particles->AddParticle(App->particles->shot_up, position.x + 19, position.y, Collider::Type::PLAYER_SHOT);
		break;
	case Directions::UP_RIGHT:
		App->particles->AddParticle(App->particles->shot_up_right, position.x + 29, position.y + 11, Collider::Type::PLAYER_SHOT);
		break;
	case Directions::UP_LEFT:
		App->particles->AddParticle(App->particles->shot_up_left, position.x - 1, position.y, Collider::Type::PLAYER_SHOT);
		break;
	case Directions::DOWN:
		App->particles->AddParticle(App->particles->shot_down, position.x + 9, position.y + 50, Collider::Type::PLAYER_SHOT);
		break;
	case Directions::DOWN_RIGHT:
		App->particles->AddParticle(App->particles->shot_down_right, position.x + 25, position.y + 42, Collider::Type::PLAYER_SHOT);
		break;
	case Directions::DOWN_LEFT:
		App->particles->AddParticle(App->particles->shot_down_left, position.x, position.y + 31, Collider::Type::PLAYER_SHOT);
		break;
	case Directions::RIGHT:
		App->particles->AddParticle(App->particles->shot_right, position.x + 26, position.y + 23, Collider::Type::PLAYER_SHOT);
		break;
	case Directions::LEFT:
		App->particles->AddParticle(App->particles->shot_left, position.x, position.y + 24, Collider::Type::PLAYER_SHOT);
		break;
	}
}

void ModulePlayer::shootHeavyRifle() {
	ammunition--;
	switch (facing) {
	case Directions::UP:
		App->particles->AddParticle(App->particles->hrifle_up, position.x + 13, position.y, Collider::Type::PLAYER_SHOT);
		break;
	case Directions::UP_RIGHT:
		App->particles->AddParticle(App->particles->hrifle_up_right, position.x + 32, position.y, Collider::Type::PLAYER_SHOT);
		break;
	case Directions::UP_LEFT:
		App->particles->AddParticle(App->particles->hrifle_up_left, position.x, position.y, Collider::Type::PLAYER_SHOT);
		break;
	case Directions::DOWN:
		App->particles->AddParticle(App->particles->hrifle_down, position.x + 13, position.y + 64, Collider::Type::PLAYER_SHOT);
		break;
	case Directions::DOWN_RIGHT:
		App->particles->AddParticle(App->particles->hrifle_down_right, position.x + 32, position.y + 64, Collider::Type::PLAYER_SHOT);
		break;
	case Directions::DOWN_LEFT:
		App->particles->AddParticle(App->particles->hrifle_down_left, position.x, position.y + 64, Collider::Type::PLAYER_SHOT);
		break;
	case Directions::RIGHT:
		App->particles->AddParticle(App->particles->hrifle_right, position.x + 32, position.y + 29, Collider::Type::PLAYER_SHOT);
		break;
	case Directions::LEFT:
		App->particles->AddParticle(App->particles->hrifle_left, position.x, position.y + 29, Collider::Type::PLAYER_SHOT);
		break;
	}
}

void ModulePlayer::shootFlamethrower() {
	ammunition--;
	switch (facing) {
	case Directions::UP:
		App->particles->AddParticle(App->particles->fthrower_up, position.x + 13, position.y, Collider::Type::PLAYER_SHOT);
		break;
	case Directions::UP_RIGHT:
		App->particles->AddParticle(App->particles->fthrower_up_right, position.x + 32, position.y, Collider::Type::PLAYER_SHOT);
		break;
	case Directions::UP_LEFT:
		App->particles->AddParticle(App->particles->fthrower_up_left, position.x, position.y, Collider::Type::PLAYER_SHOT);
		break;
	case Directions::DOWN:
		App->particles->AddParticle(App->particles->fthrower_down, position.x + 13, position.y + 64, Collider::Type::PLAYER_SHOT);
		break;
	case Directions::DOWN_RIGHT:
		App->particles->AddParticle(App->particles->fthrower_down_right, position.x + 32, position.y + 64, Collider::Type::PLAYER_SHOT);
		break;
	case Directions::DOWN_LEFT:
		App->particles->AddParticle(App->particles->fthrower_down_left, position.x, position.y + 64, Collider::Type::PLAYER_SHOT);
		break;
	case Directions::RIGHT:
		App->particles->AddParticle(App->particles->fthrower_right, position.x + 32, position.y + 29, Collider::Type::PLAYER_SHOT);
		break;
	case Directions::LEFT:
		App->particles->AddParticle(App->particles->fthrower_left, position.x, position.y + 29, Collider::Type::PLAYER_SHOT);
		break;
	}
}

update_status ModulePlayer::Update() {

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
			facing = Directions::UP;
			currentAnimTop = &upAnimTop;
			currentAnimBot = &upAnimBot;
			if (weapon == Weapon::NORMAL) {
				currentWeaponAnim = &upNorWeaponAnim;
			} else {
				currentWeaponAnim = &upPowWeaponAnim;
			}
		}

		// Direction to UP_RIGHT
		if (App->input->keys[SDL_SCANCODE_I] == KEY_STATE::KEY_REPEAT &&
			App->input->keys[SDL_SCANCODE_J] == KEY_STATE::KEY_IDLE &&
			App->input->keys[SDL_SCANCODE_K] == KEY_STATE::KEY_IDLE &&
			App->input->keys[SDL_SCANCODE_L] == KEY_STATE::KEY_REPEAT) {
			facing = Directions::UP_RIGHT;
			currentAnimTop = &upRightAnimTop;
			currentAnimBot = &upRightAnimBot;
			if (weapon == Weapon::NORMAL) {
				currentWeaponAnim = &upRightNorWeaponAnim;
			} else {
				currentWeaponAnim = &upRightPowWeaponAnim;
			}
		}

		// Direction to RIGHT
		if (App->input->keys[SDL_SCANCODE_I] == KEY_STATE::KEY_IDLE &&
			App->input->keys[SDL_SCANCODE_J] == KEY_STATE::KEY_IDLE &&
			App->input->keys[SDL_SCANCODE_K] == KEY_STATE::KEY_IDLE &&
			App->input->keys[SDL_SCANCODE_L] == KEY_STATE::KEY_REPEAT) {
			facing = Directions::RIGHT;
			currentAnimTop = &rightAnimTop;
			currentAnimBot = &rightAnimBot;
			if (weapon == Weapon::NORMAL) {
				currentWeaponAnim = &rightNorWeaponAnim;
			} else {
				currentWeaponAnim = &rightPowWeaponAnim;
			}
		}

		// Direction to DOWN_RIGHT
		if (App->input->keys[SDL_SCANCODE_I] == KEY_STATE::KEY_IDLE &&
			App->input->keys[SDL_SCANCODE_J] == KEY_STATE::KEY_IDLE &&
			App->input->keys[SDL_SCANCODE_K] == KEY_STATE::KEY_REPEAT &&
			App->input->keys[SDL_SCANCODE_L] == KEY_STATE::KEY_REPEAT) {
			facing = Directions::DOWN_RIGHT;
			currentAnimTop = &downRightAnimTop;
			currentAnimBot = &downRightAnimBot;
			if (weapon == Weapon::NORMAL) {
				currentWeaponAnim = &downRightNorWeaponAnim;
			} else {
				currentWeaponAnim = &downRightPowWeaponAnim;
			}
		}

		// Direction to DOWN
		if (App->input->keys[SDL_SCANCODE_I] == KEY_STATE::KEY_IDLE &&
			App->input->keys[SDL_SCANCODE_J] == KEY_STATE::KEY_IDLE &&
			App->input->keys[SDL_SCANCODE_K] == KEY_STATE::KEY_REPEAT &&
			App->input->keys[SDL_SCANCODE_L] == KEY_STATE::KEY_IDLE) {
			facing = Directions::DOWN;
			currentAnimTop = &downAnimTop;
			currentAnimBot = &downAnimBot;
			if (weapon == Weapon::NORMAL) {
				currentWeaponAnim = &downNorWeaponAnim;
			} else {
				currentWeaponAnim = &downPowWeaponAnim;
			}
		}

		// Direction to DOWN_LEFT
		if (App->input->keys[SDL_SCANCODE_I] == KEY_STATE::KEY_IDLE &&
			App->input->keys[SDL_SCANCODE_J] == KEY_STATE::KEY_REPEAT &&
			App->input->keys[SDL_SCANCODE_K] == KEY_STATE::KEY_REPEAT &&
			App->input->keys[SDL_SCANCODE_L] == KEY_STATE::KEY_IDLE) {
			facing = Directions::DOWN_LEFT;
			currentAnimTop = &downLeftAnimTop;
			currentAnimBot = &downLeftAnimBot;
			if (weapon == Weapon::NORMAL) {
				currentWeaponAnim = &downLeftNorWeaponAnim;
			} else {
				currentWeaponAnim = &downLeftPowWeaponAnim;
			}
		}

		// Direction to LEFT
		if (App->input->keys[SDL_SCANCODE_I] == KEY_STATE::KEY_IDLE &&
			App->input->keys[SDL_SCANCODE_J] == KEY_STATE::KEY_REPEAT &&
			App->input->keys[SDL_SCANCODE_K] == KEY_STATE::KEY_IDLE &&
			App->input->keys[SDL_SCANCODE_L] == KEY_STATE::KEY_IDLE) {
			facing = Directions::LEFT;
			currentAnimTop = &leftAnimTop;
			currentAnimBot = &leftAnimBot;
			if (weapon == Weapon::NORMAL) {
				currentWeaponAnim = &leftNorWeaponAnim;
			} else {
				currentWeaponAnim = &leftPowWeaponAnim;
			}
		}

		// Direction to UP_LEFT
		if (App->input->keys[SDL_SCANCODE_I] == KEY_STATE::KEY_REPEAT &&
			App->input->keys[SDL_SCANCODE_J] == KEY_STATE::KEY_REPEAT &&
			App->input->keys[SDL_SCANCODE_K] == KEY_STATE::KEY_IDLE &&
			App->input->keys[SDL_SCANCODE_L] == KEY_STATE::KEY_IDLE) {
			facing = Directions::UP_LEFT;
			currentAnimTop = &upLeftAnimTop;
			currentAnimBot = &upLeftAnimBot;
			if (weapon == Weapon::NORMAL) {
				currentWeaponAnim = &upLeftNorWeaponAnim;
			} else {
				currentWeaponAnim = &upLeftPowWeaponAnim;
			}
		}

		switch (place) {
		case Place::TRENCH:
			if (currentAnimBot != &waterAnimBot)
				currentAnimBot = &waterAnimBot;
		case Place::WATER:
			if (currentAnimBot != &trenchAnimBot)
				currentAnimBot = &trenchAnimBot;
		}

		idleAnimTop.frames[0] = currentAnimTop->frames[currentAnimTop->GetCurrentFrameNum()];
		idleAnimBot.frames[0] = currentAnimBot->frames[currentAnimBot->GetCurrentFrameNum()];

	}

	// Player movement
	if (App->input->keys[SDL_SCANCODE_W] == KEY_STATE::KEY_IDLE &&
		App->input->keys[SDL_SCANCODE_A] == KEY_STATE::KEY_IDLE &&
		App->input->keys[SDL_SCANCODE_S] == KEY_STATE::KEY_IDLE &&
		App->input->keys[SDL_SCANCODE_D] == KEY_STATE::KEY_IDLE) {

		currentAnimTop = &idleAnimTop;
		currentAnimBot = &idleAnimBot;
	} else if (!dead) {

		// Move UP
		if (App->input->keys[SDL_SCANCODE_W] == KEY_STATE::KEY_REPEAT &&
			App->input->keys[SDL_SCANCODE_A] == KEY_STATE::KEY_IDLE &&
			App->input->keys[SDL_SCANCODE_S] == KEY_STATE::KEY_IDLE &&
			App->input->keys[SDL_SCANCODE_D] == KEY_STATE::KEY_IDLE) {
			position.y -= speed;
			movementDir = UP;

			switch (place) {
			case Place::LAND:
				if (currentAnimBot != &upAnimBot)
					currentAnimBot = &upAnimBot;

				break;
			case Place::WATER:
				if (currentAnimBot != &waterAnimBot)
					currentAnimBot = &waterAnimBot;

				break;
			case Place::TRENCH:
				if (currentAnimBot != &trenchAnimBot)
					currentAnimBot = &trenchAnimBot;

				break;
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
			switch (place) {
			case Place::LAND:
				if (currentAnimBot != &upRightAnimBot)
					currentAnimBot = &upRightAnimBot;

				break;
			case Place::WATER:
				if (currentAnimBot != &waterAnimBot)
					currentAnimBot = &waterAnimBot;

				break;
			case Place::TRENCH:
				if (currentAnimBot != &trenchAnimBot)
					currentAnimBot = &trenchAnimBot;

				break;
			}
		}

		// Move RIGHT
		if (App->input->keys[SDL_SCANCODE_W] == KEY_STATE::KEY_IDLE &&
			App->input->keys[SDL_SCANCODE_A] == KEY_STATE::KEY_IDLE &&
			App->input->keys[SDL_SCANCODE_S] == KEY_STATE::KEY_IDLE &&
			App->input->keys[SDL_SCANCODE_D] == KEY_STATE::KEY_REPEAT) {
			position.x += speed;
			movementDir = RIGHT;
			switch (place) {
			case Place::LAND:
				if (currentAnimBot != &rightAnimBot)
					currentAnimBot = &rightAnimBot;

				break;
			case Place::WATER:
				if (currentAnimBot != &waterAnimBot)
					currentAnimBot = &waterAnimBot;

				break;
			case Place::TRENCH:
				if (currentAnimBot != &trenchAnimBot)
					currentAnimBot = &trenchAnimBot;

				break;
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
			switch (place) {
			case Place::LAND:
				if (currentAnimBot != &downRightAnimBot)
					currentAnimBot = &downRightAnimBot;

				break;
			case Place::WATER:
				if (currentAnimBot != &waterAnimBot)
					currentAnimBot = &waterAnimBot;

				break;
			case Place::TRENCH:
				if (currentAnimBot != &trenchAnimBot)
					currentAnimBot = &trenchAnimBot;

				break;
			}
		}

		// Move DOWN
		if (App->input->keys[SDL_SCANCODE_W] == KEY_STATE::KEY_IDLE &&
			App->input->keys[SDL_SCANCODE_A] == KEY_STATE::KEY_IDLE &&
			App->input->keys[SDL_SCANCODE_S] == KEY_STATE::KEY_REPEAT &&
			App->input->keys[SDL_SCANCODE_D] == KEY_STATE::KEY_IDLE) {
			position.y += speed;
			movementDir = DOWN;
			switch (place) {
			case Place::LAND:
				if (currentAnimBot != &downAnimBot)
					currentAnimBot = &downAnimBot;

				break;
			case Place::WATER:
				if (currentAnimBot != &waterAnimBot)
					currentAnimBot = &waterAnimBot;

				break;
			case Place::TRENCH:
				if (currentAnimBot != &trenchAnimBot)
					currentAnimBot = &trenchAnimBot;

				break;
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
			switch (place) {
			case Place::LAND:
				if (currentAnimBot != &downLeftAnimBot)
					currentAnimBot = &downLeftAnimBot;

				break;
			case Place::WATER:
				if (currentAnimBot != &waterAnimBot)
					currentAnimBot = &waterAnimBot;

				break;
			case Place::TRENCH:
				if (currentAnimBot != &trenchAnimBot)
					currentAnimBot = &trenchAnimBot;

				break;
			}
		}

		// Move LEFT
		if (App->input->keys[SDL_SCANCODE_W] == KEY_STATE::KEY_IDLE &&
			App->input->keys[SDL_SCANCODE_A] == KEY_STATE::KEY_REPEAT &&
			App->input->keys[SDL_SCANCODE_S] == KEY_STATE::KEY_IDLE &&
			App->input->keys[SDL_SCANCODE_D] == KEY_STATE::KEY_IDLE) {
			position.x -= speed;
			movementDir = LEFT;
			switch (place) {
			case Place::LAND:
				if (currentAnimBot != &leftAnimBot)
					currentAnimBot = &leftAnimBot;

				break;
			case Place::WATER:
				if (currentAnimBot != &waterAnimBot)
					currentAnimBot = &waterAnimBot;

				break;
			case Place::TRENCH:
				if (currentAnimBot != &trenchAnimBot)
					currentAnimBot = &trenchAnimBot;

				break;
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
		}

		// Activate top/bot anim when moving
		switch (facing) {
		case UP:
			currentAnimTop = &upAnimTop;

			switch (place) {
			case Place::LAND:
				if (movementDir == DOWN) {
					if (currentAnimBot != &upAnimBot)
						currentAnimBot = &upAnimBot;
				}
				if (movementDir == DOWN_LEFT) {
					if (currentAnimBot != &upRightAnimBot)
						currentAnimBot = &upRightAnimBot;
				}
				if (movementDir == DOWN_RIGHT) {
					if (currentAnimBot != &upLeftAnimBot)
						currentAnimBot = &upLeftAnimBot;
				}
				break;
			case Place::WATER:
				if (currentAnimBot != &waterAnimBot) {
					currentAnimBot = &waterAnimBot;
				}
				break;
			case Place::TRENCH:
				if (currentAnimBot != &trenchAnimBot) {
					currentAnimBot = &trenchAnimBot;
				}
				break;
			}
			break;
		case DOWN:
			currentAnimTop = &downAnimTop;

			switch (place) {
			case Place::LAND:
				if (movementDir == UP) {
					if (currentAnimBot != &downAnimBot)
						currentAnimBot = &downAnimBot;
				}
				if (movementDir == UP_LEFT) {
					if (currentAnimBot != &downRightAnimBot)
						currentAnimBot = &downRightAnimBot;
				}
				if (movementDir == UP_RIGHT) {
					if (currentAnimBot != &downLeftAnimBot)
						currentAnimBot = &downLeftAnimBot;
				}
				break;
			case Place::WATER:
				if (currentAnimBot != &waterAnimBot) {
					currentAnimBot = &waterAnimBot;
				}
				break;
			case Place::TRENCH:
				if (currentAnimBot != &trenchAnimBot) {
					currentAnimBot = &trenchAnimBot;
				}
				break;
			}
			break;
		case RIGHT:
			currentAnimTop = &rightAnimTop;

			switch (place) {
			case Place::LAND:
				if (movementDir == LEFT) {
					if (currentAnimBot != &rightAnimBot)
						currentAnimBot = &rightAnimBot;
				}
				if (movementDir == UP_LEFT) {
					if (currentAnimBot != &downRightAnimBot)
						currentAnimBot = &downRightAnimBot;
				}
				if (movementDir == DOWN_LEFT) {
					if (currentAnimBot != &downLeftAnimBot)
						currentAnimBot = &downLeftAnimBot;
				}
				if (movementDir == UP) {
					if (currentAnimBot != &upAnimBot)
						currentAnimBot = &upAnimBot;
				}
				break;
			case Place::WATER:
				if (currentAnimBot != &waterAnimBot) {
					currentAnimBot = &waterAnimBot;
				}
				break;
			case Place::TRENCH:
				if (currentAnimBot != &trenchAnimBot) {
					currentAnimBot = &trenchAnimBot;
				}
				break;
			}
			break;
		case LEFT:
			currentAnimTop = &leftAnimTop;

			switch (place) {
			case Place::LAND:
				if (movementDir == RIGHT) {
					if (currentAnimBot != &leftAnimBot)
						currentAnimBot = &leftAnimBot;
				}
				if (movementDir == UP_RIGHT) {
					if (currentAnimBot != &downLeftAnimBot)
						currentAnimBot = &downLeftAnimBot;
				}
				if (movementDir == DOWN_RIGHT) {
					if (currentAnimBot != &upLeftAnimBot)
						currentAnimBot = &upLeftAnimBot;
				}
				break;
			case Place::WATER:
				if (currentAnimBot != &waterAnimBot) {
					currentAnimBot = &waterAnimBot;
				}
				break;
			case Place::TRENCH:
				if (currentAnimBot != &trenchAnimBot) {
					currentAnimBot = &trenchAnimBot;
				}
				break;
			}
			break;
		case UP_RIGHT:
			currentAnimTop = &upRightAnimTop;

			switch (place) {
			case Place::LAND:
				if (movementDir == DOWN_LEFT) {
					if (currentAnimBot != &upRightAnimBot)
						currentAnimBot = &upRightAnimBot;
				}
				if (movementDir == LEFT) {
					if (currentAnimBot != &rightAnimBot)
						currentAnimBot = &rightAnimBot;
				}
				if (movementDir == DOWN) {
					if (currentAnimBot != &upAnimBot)
						currentAnimBot = &upAnimBot;
				}
				break;
			case Place::WATER:
				if (currentAnimBot != &waterAnimBot) {
					currentAnimBot = &waterAnimBot;
				}
				break;
			case Place::TRENCH:
				if (currentAnimBot != &trenchAnimBot) {
					currentAnimBot = &trenchAnimBot;
				}
				break;
			}
			break;
		case UP_LEFT:
			currentAnimTop = &upLeftAnimTop;

			switch (place) {
			case Place::LAND:
				if (movementDir == DOWN_RIGHT) {
					if (currentAnimBot != &upLeftAnimBot)
						currentAnimBot = &upLeftAnimBot;
				}
				if (movementDir == RIGHT) {
					if (currentAnimBot != &leftAnimBot)
						currentAnimBot = &leftAnimBot;
				}
				if (movementDir == DOWN) {
					if (currentAnimBot != &upAnimBot)
						currentAnimBot = &upAnimBot;
				}
				break;
			case Place::WATER:
				if (currentAnimBot != &waterAnimBot) {
					currentAnimBot = &waterAnimBot;
				}
				break;
			case Place::TRENCH:
				if (currentAnimBot != &trenchAnimBot) {
					currentAnimBot = &trenchAnimBot;
				}
				break;
			}
			break;
		case DOWN_RIGHT:
			currentAnimTop = &downRightAnimTop;

			switch (place) {
			case Place::LAND:
				if (movementDir == UP_LEFT) {
					if (currentAnimBot != &downRightAnimBot)
						currentAnimBot = &downRightAnimBot;
				}
				if (movementDir == LEFT) {
					if (currentAnimBot != &leftAnimBot)
						currentAnimBot = &leftAnimBot;
				}
				if (movementDir == UP) {
					if (currentAnimBot != &downAnimBot)
						currentAnimBot = &downAnimBot;
				}
				break;
			case Place::WATER:
				if (currentAnimBot != &waterAnimBot) {
					currentAnimBot = &waterAnimBot;
				}
				break;
			case Place::TRENCH:
				if (currentAnimBot != &trenchAnimBot) {
					currentAnimBot = &trenchAnimBot;
				}
				break;
			}
			break;
		case DOWN_LEFT:
			currentAnimTop = &downLeftAnimTop;

			switch (place) {
			case Place::LAND:
				if (movementDir == UP_RIGHT) {
					if (currentAnimBot != &downLeftAnimBot)
						currentAnimBot = &downLeftAnimBot;
				}
				if (movementDir == RIGHT) {
					if (currentAnimBot != &leftAnimBot)
						currentAnimBot = &leftAnimBot;
				}
				if (movementDir == UP) {
					if (currentAnimBot != &downAnimBot)
						currentAnimBot = &downAnimBot;
				}
				break;
			case Place::WATER:
				if (currentAnimBot != &waterAnimBot) {
					currentAnimBot = &waterAnimBot;
				}
				break;
			case Place::TRENCH:
				if (currentAnimBot != &trenchAnimBot) {
					currentAnimBot = &trenchAnimBot;
				}
				break;
			}
			break;
		default:
			break;
		}
		// Set the idles to the current frame
		idleAnimTop.frames[0] = currentAnimTop->GetCurrentFrame();
		idleAnimBot.frames[0] = currentAnimBot->GetCurrentFrame();
	}

	if (ammunition == 0)
		weapon = Weapon::NORMAL;


	if (!dead) {
		if (App->input->keys[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_DOWN) {
			switch (weapon) {
			case Weapon::FLAMETHROWER:
				App->audio->PlayFx(flamethrowerFx);
				shootFlamethrower();
				break;
			case Weapon::HEAVY_RIFLE:
				App->audio->PlayFx(heavyRifleFx);
				shootHeavyRifle();
				break;
			case Weapon::NORMAL:
				App->audio->PlayFx(shotFx);
				shootNormal();
				break;
			}
		}
	}

	if (dead) {
		// need to implement death behaviour
		currentAnimTop = &deathAnimTop;
		currentAnimBot = &deathAnimBot;
		deathCooldown++;
		if (deathCooldown >= DEATH_ANIM_DURATION) {
			App->fade->FadeToBlack((Module*)App->level1, (Module*)App->lose, 0);
		}
	}

	// God mode cheat
	if (App->input->keys[SDL_SCANCODE_F1] == KEY_STATE::KEY_DOWN) {
		godMode = !godMode;
	}

	// Insta win cheat
	if (App->input->keys[SDL_SCANCODE_F3] == KEY_STATE::KEY_DOWN) {
		App->fade->FadeToBlack((Module*)App->level1, (Module*)App->win, 0);
	}

	// Insta lose cheat
	if (App->input->keys[SDL_SCANCODE_F4] == KEY_STATE::KEY_DOWN && dead == false) {
		// Handle insta lose
		dead = true;
	}

	if (App->input->keys[SDL_SCANCODE_ESCAPE] == KEY_STATE::KEY_REPEAT) {
		return update_status::UPDATE_STOP;
	}

	// Updates player collider position
	collider->SetPos(position.x, position.y);
	currentAnimTop->Update();
	currentAnimBot->Update();
	currentWeaponAnim->Update();

	return update_status::UPDATE_CONTINUE;
}

update_status ModulePlayer::PostUpdate() {
	SDL_Rect rect = currentWeaponAnim->GetCurrentFrame();
	switch (facing) {
	case Directions::LEFT:
		App->render->Blit(weaponTexture, position.x - 14, position.y + 7, &rect);
		break;
	case Directions::UP_LEFT:
		App->render->Blit(weaponTexture, position.x - 14, position.y - 7, &rect);
		break;
	case Directions::UP:
		App->render->Blit(weaponTexture, position.x, position.y - 6, &rect);
		break;
	case Directions::RIGHT:
		App->render->Blit(weaponTexture, position.x + 10, position.y + 8, &rect);
		break;
	case Directions::UP_RIGHT:
		App->render->Blit(weaponTexture, position.x + 15, position.y + 2, &rect);
		break;
	}

	rect = currentAnimBot->GetCurrentFrame();
	App->render->Blit(playerTexture, position.x, position.y + 29, &rect);

	rect = currentAnimTop->GetCurrentFrame();
	App->render->Blit(playerTexture, position.x, position.y, &rect);

	rect = currentWeaponAnim->GetCurrentFrame();
	switch (facing) {
	case Directions::DOWN:
		App->render->Blit(weaponTexture, position.x, position.y + 20, &rect);
		break;
	case Directions::DOWN_RIGHT:
		App->render->Blit(weaponTexture, position.x + 9, position.y + 20, &rect);
		break;
	case Directions::DOWN_LEFT:
		App->render->Blit(weaponTexture, position.x - 16, position.y + 20, &rect);
		break;
	}
	return update_status::UPDATE_CONTINUE;
}

void ModulePlayer::OnCollision(Collider* c1, Collider* c2) {
	place = Place::LAND;
	if (c1 == collider) {
		switch (c2->type) {
		case Collider::Type::ENEMY:
			if (godMode == false) {
				App->audio->PlayFx(deadFx);
				this->dead = true;
			}
			break;
		case Collider::Type::ENEMY_SHOT:
			if (godMode == false) {
				App->audio->PlayFx(deadFx);
				this->dead = true;
			}
			break;
		case Collider::Type::POWER_UP:
			// Sound pick up at Powerup.cpp
			// Weapon changes at each Powerup_(weaponname).cpp
			c2->pendingToDelete = true;
			ammunition = MAX_AMMO;
			break;
		case Collider::Type::WALL:
			switch (movementDir) {
			case UP:
				position.y += speed;
				break;
			case DOWN:
				position.y -= speed;
				break;
			case RIGHT:
				position.x -= speed;
				break;
			case LEFT:
				position.x += speed;
				break;
			case UP_RIGHT:
				position.y += speed;
				position.x -= speed;
				break;
			case UP_LEFT:
				position.y += speed;
				position.x += speed;
				break;
			case DOWN_RIGHT:
				position.y -= speed;
				position.x -= speed;
				break;
			case DOWN_LEFT:
				position.y -= speed;
				position.x += speed;
				break;
			default:
				break;
			}
			break;

		case Collider::Type::WATER:
			currentAnimBot = &waterAnimBot;
			place = Place::WATER;
			break;

		case Collider::Type::TRENCH:
			currentAnimBot = &trenchAnimBot;
			place = Place::TRENCH;
			break;

		}

		if (c2->type != Collider::Type::WATER && c2->type != Collider::Type::TRENCH) {
			place = Place::LAND;
		}
	}
}
