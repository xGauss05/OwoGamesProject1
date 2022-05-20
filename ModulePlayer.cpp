#include "ModulePlayer.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleParticles.h"
#include "ModuleAudio.h"
#include "ModuleCollisions.h"
#include "ModuleFadeToBlack.h"
#include "ModuleFonts.h"

#include "SceneLevel1.h"

#include "Globals.h"
#include <string>
#include "SDL/include/SDL_scancode.h"

ModulePlayer::ModulePlayer(bool startEnabled) : Module(startEnabled) {
	facing = Directions::UP;
	weapon = Weapon::NORMAL;
	movementDir = Directions::UP;
	place = Place::LAND;

	ammunition = 0;
	score = 0;

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

	// Throw grenade animations
	upThrowGrenade.PushBack({ 320, 0, 32, 32 });
	upThrowGrenade.PushBack({ 352, 0, 32, 32 });
	upThrowGrenade.PushBack({ 384, 0, 32, 32 });
	upThrowGrenade.PushBack({ 416, 0, 32, 32 });
	upThrowGrenade.PushBack({ 448, 0, 32, 32 });
	upThrowGrenade.speed = 0.1f;
	upThrowGrenade.loop = false;

	upRightThrowGrenade.PushBack({ 320, 32, 32, 32 });
	upRightThrowGrenade.PushBack({ 352, 32, 32, 32 });
	upRightThrowGrenade.PushBack({ 384, 32, 32, 32 });
	upRightThrowGrenade.PushBack({ 416, 32, 32, 32 });
	upRightThrowGrenade.PushBack({ 448, 32, 32, 32 });
	upRightThrowGrenade.speed = 0.1f;
	upRightThrowGrenade.loop = false;

	rightThrowGrenade.PushBack({ 320, 64, 32, 32 });
	rightThrowGrenade.PushBack({ 352, 64, 32, 32 });
	rightThrowGrenade.PushBack({ 384, 64, 32, 32 });
	rightThrowGrenade.PushBack({ 416, 64, 32, 32 });
	rightThrowGrenade.PushBack({ 448, 64, 32, 32 });
	rightThrowGrenade.speed = 0.1f;
	rightThrowGrenade.loop = false;

	downRightThrowGrenade.PushBack({ 320, 96, 32, 32 });
	downRightThrowGrenade.PushBack({ 352, 96, 32, 32 });
	downRightThrowGrenade.PushBack({ 384, 96, 32, 32 });
	downRightThrowGrenade.PushBack({ 416, 96, 32, 32 });
	downRightThrowGrenade.PushBack({ 448, 96, 32, 32 });
	downRightThrowGrenade.speed = 0.1f;
	downRightThrowGrenade.loop = false;

	downThrowGrenade.PushBack({ 320, 128, 32, 32 });
	downThrowGrenade.PushBack({ 352, 128, 32, 32 });
	downThrowGrenade.PushBack({ 384, 128, 32, 32 });
	downThrowGrenade.PushBack({ 416, 128, 32, 32 });
	downThrowGrenade.PushBack({ 448, 128, 32, 32 });
	downThrowGrenade.speed = 0.1f;
	downThrowGrenade.loop = false;

	downLeftThrowGrenade.PushBack({ 320, 160, 32, 32 });
	downLeftThrowGrenade.PushBack({ 352, 160, 32, 32 });
	downLeftThrowGrenade.PushBack({ 384, 160, 32, 32 });
	downLeftThrowGrenade.PushBack({ 416, 160, 32, 32 });
	downLeftThrowGrenade.PushBack({ 448, 160, 32, 32 });
	downLeftThrowGrenade.speed = 0.1f;
	downLeftThrowGrenade.loop = false;

	leftThrowGrenade.PushBack({ 320, 192, 32, 32 });
	leftThrowGrenade.PushBack({ 352, 192, 32, 32 });
	leftThrowGrenade.PushBack({ 384, 192, 32, 32 });
	leftThrowGrenade.PushBack({ 416, 192, 32, 32 });
	leftThrowGrenade.PushBack({ 448, 192, 32, 32 });
	leftThrowGrenade.speed = 0.1f;
	leftThrowGrenade.loop = false;

}

ModulePlayer::~ModulePlayer() {
}

bool ModulePlayer::Start() {
	LOG("Loading player textures");
	score = 0;
	ammunition = 0;
	deathCooldown = 0;
	lives = 2;
	grenades = MAX_GRENADES;

	playerTexture = App->textures->Load("Assets/img/sprites/player.png"); // player spritesheet
	weaponTexture = App->textures->Load("Assets/img/sprites/weapon.png"); // weapon spritesheet

	currentAnimTop = &idleAnimTop;
	currentAnimBot = &idleAnimBot;
	currentWeaponAnim = &upNorWeaponAnim;

	facing = Directions::UP;
	weapon = Weapon::NORMAL;
	movementDir = Directions::UP;
	place = Place::LAND;

	dead = false;
	godMode = false;
	isThrowing = false;

	// Initiate player audios here
	shotFx = App->audio->LoadFx("Assets/sounds/sfx/142.wav"); // shot sfx
	playerDeadFx = App->audio->LoadFx("Assets/sounds/sfx/195.wav"); // dead sfx
	heavyRifleFx = App->audio->LoadFx("Assets/sounds/sfx/153.wav");
	flamethrowerFx = App->audio->LoadFx("Assets/sounds/sfx/136.wav");
	throwGrenadeFx = App->audio->LoadFx("Assets/sounds/sfx/137.wav");

	// Initial position
	position.x = 240;
	position.y = 120;

	// Player collider
	collider = App->collisions->AddCollider({ position.x, position.y, 32, 64 }, Collider::Type::PLAYER, this);

	// UI for 0.5
	App->fonts->Load("Assets/img/sprites/font.png", "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ.@'&-                       ", 8);

	return true;
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
		App->particles->AddParticle(App->particles->hrifle_up, position.x + 19, position.y, Collider::Type::PLAYER_SHOT);
		break;
	case Directions::UP_RIGHT:
		App->particles->AddParticle(App->particles->hrifle_up_right, position.x + 29, position.y - 3, Collider::Type::PLAYER_SHOT);
		break;
	case Directions::UP_LEFT:
		App->particles->AddParticle(App->particles->hrifle_up_left, position.x - 1, position.y, Collider::Type::PLAYER_SHOT);
		break;
	case Directions::DOWN:
		App->particles->AddParticle(App->particles->hrifle_down, position.x + 7, position.y + 15, Collider::Type::PLAYER_SHOT);
		break;
	case Directions::DOWN_RIGHT:
		App->particles->AddParticle(App->particles->hrifle_down_right, position.x + 25, position.y + 42, Collider::Type::PLAYER_SHOT);
		break;
	case Directions::DOWN_LEFT:
		App->particles->AddParticle(App->particles->hrifle_down_left, position.x - 16, position.y + 31, Collider::Type::PLAYER_SHOT);
		break;
	case Directions::RIGHT:
		App->particles->AddParticle(App->particles->hrifle_right, position.x + 26, position.y + 23, Collider::Type::PLAYER_SHOT);
		break;
	case Directions::LEFT:
		App->particles->AddParticle(App->particles->hrifle_left, position.x, position.y + 24, Collider::Type::PLAYER_SHOT);
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

void ModulePlayer::throwGrenade() {
	isThrowing = true;
	grenades--;
	App->audio->PlayFx(throwGrenadeFx);
	//App->particles->grenade.explodes = true;
	switch (facing) {
	case Directions::UP:
		App->particles->grenade.speed.x = 0;
		App->particles->grenade.speed.y = -2;
		App->particles->AddParticle(App->particles->grenade, position.x + 13, position.y, Collider::Type::NONE);
		break;
	case Directions::UP_RIGHT:
		App->particles->grenade.speed.x = 2;
		App->particles->grenade.speed.y = -2;
		App->particles->AddParticle(App->particles->grenade, position.x + 32, position.y, Collider::Type::NONE);
		break;
	case Directions::UP_LEFT:
		App->particles->grenade.speed.x = -2;
		App->particles->grenade.speed.y = -2;
		App->particles->AddParticle(App->particles->grenade, position.x, position.y, Collider::Type::NONE);
		break;
	case Directions::DOWN:
		App->particles->grenade.speed.x = 0;
		App->particles->grenade.speed.y = 2;
		App->particles->AddParticle(App->particles->grenade, position.x + 13, position.y + 64, Collider::Type::NONE);
		break;
	case Directions::DOWN_RIGHT:
		App->particles->grenade.speed.x = 2;
		App->particles->grenade.speed.y = 2;
		App->particles->AddParticle(App->particles->grenade, position.x + 32, position.y + 64, Collider::Type::NONE);
		break;
	case Directions::DOWN_LEFT:
		App->particles->grenade.speed.x = -2;
		App->particles->grenade.speed.y = 2;
		App->particles->AddParticle(App->particles->grenade, position.x, position.y + 64, Collider::Type::NONE);
		break;
	case Directions::RIGHT:
		App->particles->grenade.speed.x = 2;
		App->particles->grenade.speed.y = 0;
		App->particles->AddParticle(App->particles->grenade, position.x + 32, position.y + 29, Collider::Type::NONE);
		break;
	case Directions::LEFT:
		App->particles->grenade.speed.x = -2;
		App->particles->grenade.speed.y = 0;
		App->particles->AddParticle(App->particles->grenade, position.x, position.y + 29, Collider::Type::NONE);
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
				if (currentAnimBot != &waterAnimBot)
					if (currentAnimBot != &waterAnimBot)
						currentAnimBot = &waterAnimBot;

				break;
			case Place::TRENCH:
				if (currentAnimBot != &trenchAnimBot)
					currentAnimBot = &trenchAnimBot;

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
				if (currentAnimBot != &waterAnimBot)
					currentAnimBot = &waterAnimBot;

				break;
			case Place::TRENCH:
				if (currentAnimBot != &trenchAnimBot)
					currentAnimBot = &trenchAnimBot;

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
				if (currentAnimBot != &waterAnimBot)
					currentAnimBot = &waterAnimBot;

				break;
			case Place::TRENCH:
				if (currentAnimBot != &trenchAnimBot)
					currentAnimBot = &trenchAnimBot;

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
				if (currentAnimBot != &waterAnimBot)
					currentAnimBot = &waterAnimBot;

				break;
			case Place::TRENCH:
				if (currentAnimBot != &trenchAnimBot)
					currentAnimBot = &trenchAnimBot;

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
				if (currentAnimBot != &waterAnimBot)
					currentAnimBot = &waterAnimBot;

				break;
			case Place::TRENCH:
				if (currentAnimBot != &trenchAnimBot)
					currentAnimBot = &trenchAnimBot;

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
				if (currentAnimBot != &waterAnimBot)
					currentAnimBot = &waterAnimBot;

				break;
			case Place::TRENCH:
				if (currentAnimBot != &trenchAnimBot)
					currentAnimBot = &trenchAnimBot;

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
				if (currentAnimBot != &waterAnimBot)
					currentAnimBot = &waterAnimBot;

				break;
			case Place::TRENCH:
				if (currentAnimBot != &trenchAnimBot)
					currentAnimBot = &trenchAnimBot;

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

	if (ammunition == 0 && weapon != Weapon::NORMAL)
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

		if (App->input->keys[SDL_SCANCODE_E] == KEY_STATE::KEY_DOWN) {
			switch (facing) {
			case UP:
				if (currentAnimTop != &upThrowGrenade)
					currentAnimTop = &upThrowGrenade;
				break;
			case UP_RIGHT:
				if (currentAnimTop != &upRightThrowGrenade)
					currentAnimTop = &upRightThrowGrenade;
				break;
			case UP_LEFT:
				if (currentAnimTop != &upLeftThrowGrenade)
					currentAnimTop = &upLeftThrowGrenade;
				break;
			case DOWN:
				if (currentAnimTop != &downThrowGrenade)
					currentAnimTop = &downThrowGrenade;
				break;
			case DOWN_RIGHT:
				if (currentAnimTop != &downRightThrowGrenade)
					currentAnimTop = &downRightThrowGrenade;
				break;
			case DOWN_LEFT:
				if (currentAnimTop != &downLeftThrowGrenade)
					currentAnimTop = &downLeftThrowGrenade;
				break;
			case RIGHT:
				if (currentAnimTop != &rightThrowGrenade)
					currentAnimTop = &rightThrowGrenade;
				break;
			case LEFT:
				if (currentAnimTop != &leftThrowGrenade)
					currentAnimTop = &leftThrowGrenade;
				break;
			}

			if (grenades > 0) {
				throwGrenade();
			}
		}
	}

	if (dead) {
		godMode = true;
		deathCooldown++;

		if (currentAnimTop != &deathAnimTop)
			currentAnimTop = &deathAnimTop;
		if (currentAnimBot != &deathAnimBot)
			currentAnimBot = &deathAnimBot;

		if (deathCooldown == 0) {
			App->audio->PlayFx(playerDeadFx);
		}

		if (deathCooldown >= DEATH_ANIM_DURATION) {
			deathAnimTop.Reset();
			deathAnimBot.Reset();
			//godMode = false;
			if (lives == 0) {
				App->fade->FadeToBlack((Module*)App->level1, (Module*)App->lose, 0);
			} else {
				dead = false;
				//deathCooldown = 0;
			}
		}
	}

	// Invincible frames
	if (deathCooldown >= DEATH_ANIM_DURATION) {
		invincibleCooldown++;
		if (invincibleCooldown >= INVINCIBLE_DURATION) {
			godMode = false;
			deathCooldown = 0;
			invincibleCooldown = 0;
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
	if (App->input->keys[SDL_SCANCODE_F4] == KEY_STATE::KEY_DOWN && 
		!dead) {
		// Handle insta lose
		dead = true;
		lives--;
	}

	if (App->input->keys[SDL_SCANCODE_ESCAPE] == KEY_STATE::KEY_REPEAT) {
		return update_status::UPDATE_STOP;
	}

	place = Place::LAND;

	if (isThrowing && currentAnimTop->HasFinished()) {
		isThrowing = false;
	}

	// Updates player collider position
	collider->SetPos(position.x, position.y);
	currentAnimTop->Update();
	currentAnimBot->Update();
	currentWeaponAnim->Update();

	return update_status::UPDATE_CONTINUE;
}

update_status ModulePlayer::PostUpdate() {
	// Weapon textures --
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

	// Parallax
	if (App->level1->IsEnabled()) {
		App->level1->DrawParallax();
	}

	// UI ---
	App->fonts->BlitText(15, 20, 0, "1 UP");
	std::string temp = std::to_string(score);
	char const* num_char = temp.c_str();
	App->fonts->BlitText(15, 30, 0, num_char);

	// decorative UI
	App->fonts->BlitText(SCREEN_WIDTH - 45, 20, 0, "2 UP");
	App->fonts->BlitText(SCREEN_WIDTH - 20, 30, 0, "0");
	App->fonts->BlitText(80, 10, 0, "HI");
	App->fonts->BlitText(120, 10, 0, "30000");
	App->fonts->BlitText(SCREEN_WIDTH - 75, SCREEN_HEIGHT - 15, 0, "CREDITS 0");

	if (lives >= 1) {
		// need to change to lives icon
		App->fonts->BlitText(5, SCREEN_HEIGHT - 25, 0, "H");
	}
	if (lives >= 2) {
		// need to change to lives icon
		App->fonts->BlitText(15, SCREEN_HEIGHT - 25, 0, "H");
	}

	// need to change for the grenade icon
	App->fonts->BlitText(5, 45, 0, "GRENADES");
	temp = std::to_string(grenades);
	num_char = temp.c_str();
	App->fonts->BlitText(5, 55, 0, num_char);

	if (weapon != Weapon::NORMAL) {
		// need to change for the ammo icon
		App->fonts->BlitText(5, 65, 0, "AMMO");
		temp = std::to_string(ammunition);
		num_char = temp.c_str();
		App->fonts->BlitText(5, 75, 0, num_char);
	}

	return update_status::UPDATE_CONTINUE;
}

void ModulePlayer::OnCollision(Collider* c1, Collider* c2) {
	if (c1 == collider) {
		switch (c2->type) {
		case Collider::Type::ENEMY:
			if (godMode == false) {
				this->dead = true;
				lives--;
			}
			break;
		case Collider::Type::ENEMY_SHOT:
			if (godMode == false) {
				this->dead = true;
				lives--;
			}
			break;
		case Collider::Type::EXPLOSION:
			if (godMode == false) {
				this->dead = true;
				lives--;
			}
			break;
		case Collider::Type::POWER_UP:
			// Sound pick up at Powerup.cpp
			// Weapon changes at each Powerup_(weaponname).cpp
			c2->pendingToDelete = true;
			ammunition = MAX_AMMO;
			grenades = MAX_GRENADES;
			break;
		case Collider::Type::HOSTAGE:
			c2->pendingToDelete = true;
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
		case Collider::Type::BREAKABLE:
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
		case Collider::Type::NON_DEST_BAR:
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

		}

		if (c2->type != Collider::Type::WATER && c2->type != Collider::Type::TRENCH) {
			place = Place::LAND;
		}
	}
}

bool ModulePlayer::CleanUp() {
	App->textures->Unload(playerTexture);
	App->textures->Unload(weaponTexture);
	App->audio->UnloadFx(shotFx);
	App->audio->UnloadFx(playerDeadFx);
	App->audio->UnloadFx(heavyRifleFx);
	App->audio->UnloadFx(flamethrowerFx);
	App->fonts->UnLoad(0);
	return true;
}