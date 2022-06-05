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

	upLeftThrowGrenade.PushBack({ 320, 224, 32, 32 });
	upLeftThrowGrenade.PushBack({ 352, 224, 32, 32 });
	upLeftThrowGrenade.PushBack({ 384, 224, 32, 32 });
	upLeftThrowGrenade.PushBack({ 416, 224, 32, 32 });
	upLeftThrowGrenade.PushBack({ 448, 224, 32, 32 });
	upLeftThrowGrenade.speed = 0.1f;
	upLeftThrowGrenade.loop = false;

}

ModulePlayer::~ModulePlayer() {
}

bool ModulePlayer::Start() {
	LOG("Loading player textures");
	//App->fonts->Enable();
	score = 0;
	ammunition = 0;
	continueCooldown = 9;
	deathCooldown = 0;
	invincibleCooldown = 0;
	spawnPoint = -INT_MAX;
	lives = 3;
	grenades = MAX_GRENADES;
	t1 = SDL_GetTicks();

	playerTexture = App->textures->Load("Assets/img/sprites/player.png"); // player spritesheet
	weaponTexture = App->textures->Load("Assets/img/sprites/weapon.png"); // weapon spritesheet

	currentAnimTop = &idleAnimTop;
	currentAnimBot = &idleAnimBot;
	currentWeaponAnim = &upNorWeaponAnim;

	deathAnimTop.Reset();
	deathAnimBot.Reset();

	facing = Directions::UP;
	weapon = Weapon::NORMAL;
	movementDir = Directions::UP;
	place = Place::LAND;

	dead = false;
	godMode = false;
	isThrowing = false;
	immovable = false;
	isHit = false;
	isRespawning = false;
	invincible = false;

	// Initiate player audios here
	shotFx = App->audio->LoadFx("Assets/sounds/sfx/142.wav"); // shot sfx
	playerDeadFx = App->audio->LoadFx("Assets/sounds/sfx/195.wav"); // dead sfx
	heavyRifleFx = App->audio->LoadFx("Assets/sounds/sfx/153.wav");
	flamethrowerFx = App->audio->LoadFx("Assets/sounds/sfx/136.wav");
	throwGrenadeFx = App->audio->LoadFx("Assets/sounds/sfx/137.wav");

	// Initial position
	position.x = 240;
	position.y = -30;

	// Player collider
	collider = App->collisions->AddCollider({ position.x, position.y, 32, 40 }, Collider::Type::PLAYER, this);

	// UI for 0.5
	font = App->fonts->Load("Assets/img/sprites/font.png", "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ.@'&-                       ", 8);
	ui_logos = App->fonts->Load("Assets/img/sprites/logos.png", "ABCDEFGHIJKLMNOPQR                  ", 6);
	// F     - lives icons
	// GH MN - gun icon
	// IJ OP - ºgrenade icon
	return true;
}

void ModulePlayer::shootNormal() {
	switch (facing) {
	case Directions::UP:
		App->particles->AddParticle(App->particles->shot_up, position.x + 19, position.y - 16, Collider::Type::PLAYER_SHOT);
		currentWeaponAnim = &upShotNorWeaponAnim;
		break;
	case Directions::UP_RIGHT:
		App->particles->AddParticle(App->particles->shot_up_right, position.x + 29, position.y - 10, Collider::Type::PLAYER_SHOT);
		currentWeaponAnim = &upRightShotNorWeaponAnim;
		break;
	case Directions::UP_LEFT:
		App->particles->AddParticle(App->particles->shot_up_left, position.x - 1, position.y - 24, Collider::Type::PLAYER_SHOT);
		currentWeaponAnim = &upLeftShotNorWeaponAnim;
		break;
	case Directions::DOWN:
		App->particles->AddParticle(App->particles->shot_down, position.x + 9, position.y + 4, Collider::Type::PLAYER_SHOT);
		currentWeaponAnim = &downShotNorWeaponAnim;
		break;
	case Directions::DOWN_RIGHT:
		App->particles->AddParticle(App->particles->shot_down_right, position.x + 25, position.y + 16, Collider::Type::PLAYER_SHOT);
		currentWeaponAnim = &downRightShotNorWeaponAnim;
		break;
	case Directions::DOWN_LEFT:
		App->particles->AddParticle(App->particles->shot_down_left, position.x, position.y + 4, Collider::Type::PLAYER_SHOT);
		currentWeaponAnim = &downLeftShotNorWeaponAnim;
		break;
	case Directions::RIGHT:
		App->particles->AddParticle(App->particles->shot_right, position.x + 26, position.y - 2, Collider::Type::PLAYER_SHOT);
		currentWeaponAnim = &rightShotNorWeaponAnim;
		break;
	case Directions::LEFT:
		App->particles->AddParticle(App->particles->shot_left, position.x, position.y, Collider::Type::PLAYER_SHOT);
		currentWeaponAnim = &leftShotNorWeaponAnim;
		break;
	}
}

void ModulePlayer::shootHeavyRifle() {
	ammunition--;
	switch (facing) {
	case Directions::UP:
		App->particles->AddParticle(App->particles->hrifle_up, position.x + 19, position.y - 16, Collider::Type::PLAYER_SHOT);
		currentWeaponAnim = &upShotPowWeaponAnim;
		break;
	case Directions::UP_RIGHT:
		App->particles->AddParticle(App->particles->hrifle_up_right, position.x + 29, position.y - 28, Collider::Type::PLAYER_SHOT);
		currentWeaponAnim = &upRightShotPowWeaponAnim;
		break;
	case Directions::UP_LEFT:
		App->particles->AddParticle(App->particles->hrifle_up_left, position.x - 1, position.y - 24, Collider::Type::PLAYER_SHOT);
		currentWeaponAnim = &upLeftShotPowWeaponAnim;
		break;
	case Directions::DOWN:
		App->particles->AddParticle(App->particles->hrifle_down, position.x + 7, position.y + 15, Collider::Type::PLAYER_SHOT);
		currentWeaponAnim = &downShotPowWeaponAnim;
		break;
	case Directions::DOWN_RIGHT:
		App->particles->AddParticle(App->particles->hrifle_down_right, position.x + 25, position.y + 16, Collider::Type::PLAYER_SHOT);
		currentWeaponAnim = &downRightShotPowWeaponAnim;
		break;
	case Directions::DOWN_LEFT:
		App->particles->AddParticle(App->particles->hrifle_down_left, position.x - 16, position.y, Collider::Type::PLAYER_SHOT);
		currentWeaponAnim = &downLeftShotPowWeaponAnim;
		break;
	case Directions::RIGHT:
		App->particles->AddParticle(App->particles->hrifle_right, position.x + 26, position.y, Collider::Type::PLAYER_SHOT);
		currentWeaponAnim = &rightShotPowWeaponAnim;
		break;
	case Directions::LEFT:
		App->particles->AddParticle(App->particles->hrifle_left, position.x, position.y, Collider::Type::PLAYER_SHOT);
		currentWeaponAnim = &leftShotPowWeaponAnim;
		break;
	}
}

void ModulePlayer::shootFlamethrower() {
	ammunition--;
	switch (facing) {
	case Directions::UP:
		App->particles->AddParticle(App->particles->fthrower_up, position.x + 13, position.y - 82, Collider::Type::PLAYER_SHOT);
		currentWeaponAnim = &upShotPowWeaponAnim;
		break;
	case Directions::UP_RIGHT:
		App->particles->AddParticle(App->particles->fthrower_up_right, position.x + 32, position.y - 46, Collider::Type::PLAYER_SHOT);
		currentWeaponAnim = &upRightShotPowWeaponAnim;
		break;
	case Directions::UP_LEFT:
		App->particles->AddParticle(App->particles->fthrower_up_left, position.x - 32, position.y - 58, Collider::Type::PLAYER_SHOT);
		currentWeaponAnim = &upLeftShotPowWeaponAnim;
		break;
	case Directions::DOWN:
		App->particles->AddParticle(App->particles->fthrower_down, position.x + 1, position.y + 16, Collider::Type::PLAYER_SHOT);
		currentWeaponAnim = &downShotPowWeaponAnim;
		break;
	case Directions::DOWN_RIGHT:
		App->particles->AddParticle(App->particles->fthrower_down_right, position.x + 28, position.y + 24, Collider::Type::PLAYER_SHOT);
		currentWeaponAnim = &downRightShotPowWeaponAnim;
		break;
	case Directions::DOWN_LEFT:
		App->particles->AddParticle(App->particles->fthrower_down_left, position.x - 32, position.y, Collider::Type::PLAYER_SHOT);
		currentWeaponAnim = &downLeftShotPowWeaponAnim;
		break;
	case Directions::RIGHT:
		App->particles->AddParticle(App->particles->fthrower_right, position.x + 32, position.y - 8, Collider::Type::PLAYER_SHOT);
		currentWeaponAnim = &rightShotPowWeaponAnim;
		break;
	case Directions::LEFT:
		App->particles->AddParticle(App->particles->fthrower_left, position.x - 64, position.y - 4, Collider::Type::PLAYER_SHOT);
		currentWeaponAnim = &leftShotPowWeaponAnim;
		break;
	}
}

void ModulePlayer::throwGrenade() {
	isThrowing = true;
	grenades--;
	App->audio->PlayFx(throwGrenadeFx);
	switch (facing) {
	case Directions::UP:
		App->particles->grenade.speed.x = 0;
		App->particles->grenade.speed.y = -2;
		App->particles->AddParticle(App->particles->grenade, position.x, position.y, Collider::Type::NONE);
		break;
	case Directions::UP_RIGHT:
		App->particles->grenade.speed.x = 2;
		App->particles->grenade.speed.y = -2;
		App->particles->AddParticle(App->particles->grenade, position.x - 8, position.y - 8, Collider::Type::NONE);
		break;
	case Directions::UP_LEFT:
		App->particles->grenade.speed.x = -2;
		App->particles->grenade.speed.y = -2;
		App->particles->AddParticle(App->particles->grenade, position.x + 8, position.y, Collider::Type::NONE);
		break;
	case Directions::DOWN:
		App->particles->grenade.speed.x = 0;
		App->particles->grenade.speed.y = 2;
		App->particles->AddParticle(App->particles->grenade, position.x + 13, position.y + 8, Collider::Type::NONE);
		break;
	case Directions::DOWN_RIGHT:
		App->particles->grenade.speed.x = 2;
		App->particles->grenade.speed.y = 2;
		App->particles->AddParticle(App->particles->grenade, position.x + 16, position.y - 8, Collider::Type::NONE);
		break;
	case Directions::DOWN_LEFT:
		App->particles->grenade.speed.x = -2;
		App->particles->grenade.speed.y = 2;
		App->particles->AddParticle(App->particles->grenade, position.x, position.y + 8, Collider::Type::NONE);
		break;
	case Directions::RIGHT:
		App->particles->grenade.speed.x = 2;
		App->particles->grenade.speed.y = 0;
		App->particles->AddParticle(App->particles->grenade, position.x + 28, position.y - 16, Collider::Type::NONE);
		break;
	case Directions::LEFT:
		App->particles->grenade.speed.x = -2;
		App->particles->grenade.speed.y = 0;
		App->particles->AddParticle(App->particles->grenade, position.x, position.y - 16, Collider::Type::NONE);
		break;
	}
}

bool ModulePlayer::checkMovingDir() {

	bool isActing = false;

	if (App->input->controllerCount > 0) {
		for (int i = 0; i < App->input->controllerCount; ++i) {
			if (App->input->controllers[i]->j1_x > 15000) {
				if (App->input->controllers[i]->j1_y > 15000) {
					movementDir = DOWN_RIGHT;
					isActing = true;
				} else if (App->input->controllers[i]->j1_y < -15000) {
					movementDir = UP_RIGHT;
					isActing = true;
				} else {
					movementDir = RIGHT;
					isActing = true;
				}
			} else if (App->input->controllers[i]->j1_x < -15000) {
				if (App->input->controllers[i]->j1_y > 15000) {
					movementDir = DOWN_LEFT;
					isActing = true;
				} else if (App->input->controllers[i]->j1_y < -15000) {
					movementDir = UP_LEFT;
					isActing = true;
				} else {
					movementDir = LEFT;
					isActing = true;
				}
			} else {
				if (App->input->controllers[i]->j1_y > 15000) {
					movementDir = DOWN;
					isActing = true;
				} else if (App->input->controllers[i]->j1_y < -15000) {
					movementDir = UP;
					isActing = true;
				}
			}
		}
	}

	if (App->input->keys[SDL_SCANCODE_W] != KEY_STATE::KEY_IDLE ||
		App->input->keys[SDL_SCANCODE_A] != KEY_STATE::KEY_IDLE ||
		App->input->keys[SDL_SCANCODE_S] != KEY_STATE::KEY_IDLE ||
		App->input->keys[SDL_SCANCODE_D] != KEY_STATE::KEY_IDLE) {

		// Direction to UP
		if (App->input->keys[SDL_SCANCODE_W] == KEY_STATE::KEY_REPEAT &&
			App->input->keys[SDL_SCANCODE_A] == KEY_STATE::KEY_IDLE &&
			App->input->keys[SDL_SCANCODE_S] == KEY_STATE::KEY_IDLE &&
			App->input->keys[SDL_SCANCODE_D] == KEY_STATE::KEY_IDLE) {
			movementDir = UP;
			isActing = true;
		}
		// Direction to UP_RIGHT
		else if (App->input->keys[SDL_SCANCODE_W] == KEY_STATE::KEY_REPEAT &&
				 App->input->keys[SDL_SCANCODE_A] == KEY_STATE::KEY_IDLE &&
				 App->input->keys[SDL_SCANCODE_S] == KEY_STATE::KEY_IDLE &&
				 App->input->keys[SDL_SCANCODE_D] == KEY_STATE::KEY_REPEAT) {
			movementDir = UP_RIGHT;
			isActing = true;
		}
		// Direction to RIGHT
		else if (App->input->keys[SDL_SCANCODE_W] == KEY_STATE::KEY_IDLE &&
				 App->input->keys[SDL_SCANCODE_A] == KEY_STATE::KEY_IDLE &&
				 App->input->keys[SDL_SCANCODE_S] == KEY_STATE::KEY_IDLE &&
				 App->input->keys[SDL_SCANCODE_D] == KEY_STATE::KEY_REPEAT) {
			movementDir = RIGHT;
			isActing = true;
		}
		// Direction to DOWN_RIGHT
		else if (App->input->keys[SDL_SCANCODE_W] == KEY_STATE::KEY_IDLE &&
				 App->input->keys[SDL_SCANCODE_A] == KEY_STATE::KEY_IDLE &&
				 App->input->keys[SDL_SCANCODE_S] == KEY_STATE::KEY_REPEAT &&
				 App->input->keys[SDL_SCANCODE_D] == KEY_STATE::KEY_REPEAT) {
			movementDir = DOWN_RIGHT;
			isActing = true;
		}
		// Direction to DOWN
		else if (App->input->keys[SDL_SCANCODE_W] == KEY_STATE::KEY_IDLE &&
				 App->input->keys[SDL_SCANCODE_A] == KEY_STATE::KEY_IDLE &&
				 App->input->keys[SDL_SCANCODE_S] == KEY_STATE::KEY_REPEAT &&
				 App->input->keys[SDL_SCANCODE_D] == KEY_STATE::KEY_IDLE) {
			movementDir = Directions::DOWN;
			isActing = true;
		}
		// Direction to DOWN_LEFT
		else if (App->input->keys[SDL_SCANCODE_W] == KEY_STATE::KEY_IDLE &&
				 App->input->keys[SDL_SCANCODE_A] == KEY_STATE::KEY_REPEAT &&
				 App->input->keys[SDL_SCANCODE_S] == KEY_STATE::KEY_REPEAT &&
				 App->input->keys[SDL_SCANCODE_D] == KEY_STATE::KEY_IDLE) {
			movementDir = DOWN_LEFT;
			isActing = true;
		}
		// Direction to LEFT
		else if (App->input->keys[SDL_SCANCODE_W] == KEY_STATE::KEY_IDLE &&
				 App->input->keys[SDL_SCANCODE_A] == KEY_STATE::KEY_REPEAT &&
				 App->input->keys[SDL_SCANCODE_S] == KEY_STATE::KEY_IDLE &&
				 App->input->keys[SDL_SCANCODE_D] == KEY_STATE::KEY_IDLE) {
			movementDir = LEFT;
			isActing = true;
		}

		// Direction to UP_LEFT
		else if (App->input->keys[SDL_SCANCODE_W] == KEY_STATE::KEY_REPEAT &&
				 App->input->keys[SDL_SCANCODE_A] == KEY_STATE::KEY_REPEAT &&
				 App->input->keys[SDL_SCANCODE_S] == KEY_STATE::KEY_IDLE &&
				 App->input->keys[SDL_SCANCODE_D] == KEY_STATE::KEY_IDLE) {
			movementDir = UP_LEFT;
			isActing = true;
		}
	}


	return isActing;

}

bool ModulePlayer::checkFacingDir() {

	bool isActing = false;

	if (App->input->controllerCount > 0) {
		for (int i = 0; i < App->input->controllerCount; ++i) {
			if (App->input->controllers[i]->j2_x > 15000) {
				if (App->input->controllers[i]->j2_y > 15000) {
					facing = DOWN_RIGHT;
					isActing = true;
				} else if (App->input->controllers[i]->j2_y < -15000) {
					facing = UP_RIGHT;
					isActing = true;
				} else {
					facing = RIGHT;
					isActing = true;
				}
			} else if (App->input->controllers[i]->j2_x < -15000) {
				if (App->input->controllers[i]->j2_y > 15000) {
					facing = DOWN_LEFT;
					isActing = true;
				} else if (App->input->controllers[i]->j2_y < -15000) {
					facing = UP_LEFT;
					isActing = true;
				} else {
					facing = LEFT;
					isActing = true;
				}
			} else {
				if (App->input->controllers[i]->j2_y > 15000) {
					facing = DOWN;
					isActing = true;
				} else if (App->input->controllers[i]->j2_y < -15000) {
					facing = UP;
					isActing = true;
				}
			}
		}
	}

	if (App->input->keys[SDL_SCANCODE_I] != KEY_STATE::KEY_IDLE ||
		App->input->keys[SDL_SCANCODE_J] != KEY_STATE::KEY_IDLE ||
		App->input->keys[SDL_SCANCODE_K] != KEY_STATE::KEY_IDLE ||
		App->input->keys[SDL_SCANCODE_L] != KEY_STATE::KEY_IDLE) {

		// Direction to UP
		if (App->input->keys[SDL_SCANCODE_I] == KEY_STATE::KEY_REPEAT &&
			App->input->keys[SDL_SCANCODE_J] == KEY_STATE::KEY_IDLE &&
			App->input->keys[SDL_SCANCODE_K] == KEY_STATE::KEY_IDLE &&
			App->input->keys[SDL_SCANCODE_L] == KEY_STATE::KEY_IDLE) {
			facing = UP;
			isActing = true;
		}
		// Direction to UP_RIGHT
		else if (App->input->keys[SDL_SCANCODE_I] == KEY_STATE::KEY_REPEAT &&
				 App->input->keys[SDL_SCANCODE_J] == KEY_STATE::KEY_IDLE &&
				 App->input->keys[SDL_SCANCODE_K] == KEY_STATE::KEY_IDLE &&
				 App->input->keys[SDL_SCANCODE_L] == KEY_STATE::KEY_REPEAT) {
			facing = UP_RIGHT;
			isActing = true;
		}
		// Direction to RIGHT
		else if (App->input->keys[SDL_SCANCODE_I] == KEY_STATE::KEY_IDLE &&
				 App->input->keys[SDL_SCANCODE_J] == KEY_STATE::KEY_IDLE &&
				 App->input->keys[SDL_SCANCODE_K] == KEY_STATE::KEY_IDLE &&
				 App->input->keys[SDL_SCANCODE_L] == KEY_STATE::KEY_REPEAT) {
			facing = RIGHT;
			isActing = true;
		}
		// Direction to DOWN_RIGHT
		else if (App->input->keys[SDL_SCANCODE_I] == KEY_STATE::KEY_IDLE &&
				 App->input->keys[SDL_SCANCODE_J] == KEY_STATE::KEY_IDLE &&
				 App->input->keys[SDL_SCANCODE_K] == KEY_STATE::KEY_REPEAT &&
				 App->input->keys[SDL_SCANCODE_L] == KEY_STATE::KEY_REPEAT) {
			facing = DOWN_RIGHT;
			isActing = true;
		}
		// Direction to DOWN
		else if (App->input->keys[SDL_SCANCODE_I] == KEY_STATE::KEY_IDLE &&
				 App->input->keys[SDL_SCANCODE_J] == KEY_STATE::KEY_IDLE &&
				 App->input->keys[SDL_SCANCODE_K] == KEY_STATE::KEY_REPEAT &&
				 App->input->keys[SDL_SCANCODE_L] == KEY_STATE::KEY_IDLE) {
			facing = DOWN;
			isActing = true;
		}
		// Direction to DOWN_LEFT
		else if (App->input->keys[SDL_SCANCODE_I] == KEY_STATE::KEY_IDLE &&
				 App->input->keys[SDL_SCANCODE_J] == KEY_STATE::KEY_REPEAT &&
				 App->input->keys[SDL_SCANCODE_K] == KEY_STATE::KEY_REPEAT &&
				 App->input->keys[SDL_SCANCODE_L] == KEY_STATE::KEY_IDLE) {
			facing = DOWN_LEFT;
			isActing = true;
		}
		// Direction to LEFT
		else if (App->input->keys[SDL_SCANCODE_I] == KEY_STATE::KEY_IDLE &&
				 App->input->keys[SDL_SCANCODE_J] == KEY_STATE::KEY_REPEAT &&
				 App->input->keys[SDL_SCANCODE_K] == KEY_STATE::KEY_IDLE &&
				 App->input->keys[SDL_SCANCODE_L] == KEY_STATE::KEY_IDLE) {
			facing = LEFT;
			isActing = true;
		}

		// Direction to UP_LEFT
		else if (App->input->keys[SDL_SCANCODE_I] == KEY_STATE::KEY_REPEAT &&
				 App->input->keys[SDL_SCANCODE_J] == KEY_STATE::KEY_REPEAT &&
				 App->input->keys[SDL_SCANCODE_K] == KEY_STATE::KEY_IDLE &&
				 App->input->keys[SDL_SCANCODE_L] == KEY_STATE::KEY_IDLE) {
			facing = UP_LEFT;
			isActing = true;
		}
	}

	return isActing;
}

update_status ModulePlayer::Update() {

	if (!dead) {
		if (checkFacingDir()) {
			switch (facing) {
			case Directions::UP:
				if (place == LAND)
					currentAnimBot = &upAnimBot;
				if (!isThrowing)
					currentAnimTop = &upAnimTop;
				else if (currentAnimTop != &upThrowGrenade) {
					int suppVar = currentAnimTop->GetCurrentFrameNum();
					currentAnimTop = &upThrowGrenade;
					currentAnimTop->Reset();
					currentAnimTop->BeginAnimationIn(suppVar);
				}
				if (weapon == Weapon::NORMAL) {
					currentWeaponAnim = &upNorWeaponAnim;
				} else {
					currentWeaponAnim = &upPowWeaponAnim;
				}

				break;
			case Directions::UP_RIGHT:
				if (place == LAND)
					currentAnimBot = &upRightAnimBot;
				if (!isThrowing)
					currentAnimTop = &upRightAnimTop;
				else if (currentAnimTop != &upRightThrowGrenade) {
					int suppVar = currentAnimTop->GetCurrentFrameNum();
					currentAnimTop = &upRightThrowGrenade;
					currentAnimTop->Reset();
					currentAnimTop->BeginAnimationIn(suppVar);
				}

				if (weapon == Weapon::NORMAL) {
					currentWeaponAnim = &upRightNorWeaponAnim;
				} else {
					currentWeaponAnim = &upRightPowWeaponAnim;
				}

				break;
			case Directions::RIGHT:
				if (place == LAND)
					currentAnimBot = &rightAnimBot;
				if (!isThrowing)
					currentAnimTop = &rightAnimTop;
				else if (currentAnimTop != &rightThrowGrenade) {
					int suppVar = currentAnimTop->GetCurrentFrameNum();
					currentAnimTop = &rightThrowGrenade;
					currentAnimTop->Reset();
					currentAnimTop->BeginAnimationIn(suppVar);
				}

				if (weapon == Weapon::NORMAL) {
					currentWeaponAnim = &rightNorWeaponAnim;
				} else {
					currentWeaponAnim = &rightPowWeaponAnim;
				}

				break;
			case Directions::DOWN_RIGHT:
				if (place == LAND)
					currentAnimBot = &downRightAnimBot;
				if (!isThrowing)
					currentAnimTop = &downRightAnimTop;
				else if (currentAnimTop != &downRightThrowGrenade) {
					int suppVar = currentAnimTop->GetCurrentFrameNum();
					currentAnimTop = &downRightThrowGrenade;
					currentAnimTop->Reset();
					currentAnimTop->BeginAnimationIn(suppVar);
				}

				if (weapon == Weapon::NORMAL) {
					currentWeaponAnim = &downRightNorWeaponAnim;
				} else {
					currentWeaponAnim = &downRightPowWeaponAnim;
				}

				break;
			case Directions::DOWN:
				if (place == LAND)
					currentAnimBot = &downAnimBot;
				if (!isThrowing)
					currentAnimTop = &downAnimTop;
				else if (currentAnimTop != &downThrowGrenade) {
					int suppVar = currentAnimTop->GetCurrentFrameNum();
					currentAnimTop = &downThrowGrenade;
					currentAnimTop->Reset();
					currentAnimTop->BeginAnimationIn(suppVar);
				}

				if (weapon == Weapon::NORMAL) {
					currentWeaponAnim = &downNorWeaponAnim;
				} else {
					currentWeaponAnim = &downPowWeaponAnim;
				}

				break;
			case Directions::DOWN_LEFT:
				if (place == LAND)
					currentAnimBot = &downLeftAnimBot;
				if (!isThrowing)
					currentAnimTop = &downLeftAnimTop;
				else if (currentAnimTop != &downLeftThrowGrenade) {
					int suppVar = currentAnimTop->GetCurrentFrameNum();
					currentAnimTop = &downLeftThrowGrenade;
					currentAnimTop->Reset();
					currentAnimTop->BeginAnimationIn(suppVar);
				}

				if (weapon == Weapon::NORMAL) {
					currentWeaponAnim = &downLeftNorWeaponAnim;
				} else {
					currentWeaponAnim = &downLeftPowWeaponAnim;
				}

				break;
			case Directions::LEFT:
				if (place == LAND)
					currentAnimBot = &leftAnimBot;
				if (!isThrowing)
					currentAnimTop = &leftAnimTop;
				else if (currentAnimTop != &leftThrowGrenade) {
					int suppVar = currentAnimTop->GetCurrentFrameNum();
					currentAnimTop = &leftThrowGrenade;
					currentAnimTop->Reset();
					currentAnimTop->BeginAnimationIn(suppVar);
				}

				if (weapon == Weapon::NORMAL) {
					currentWeaponAnim = &leftNorWeaponAnim;
				} else {
					currentWeaponAnim = &leftPowWeaponAnim;
				}

				break;
			case Directions::UP_LEFT:
				if (place == LAND)
					currentAnimBot = &upLeftAnimBot;
				if (!isThrowing)
					currentAnimTop = &upLeftAnimTop;
				else if (currentAnimTop != &upLeftThrowGrenade) {
					int suppVar = currentAnimTop->GetCurrentFrameNum();
					currentAnimTop = &upLeftThrowGrenade;
					currentAnimTop->Reset();
					currentAnimTop->BeginAnimationIn(suppVar);
				}

				if (weapon == Weapon::NORMAL) {
					currentWeaponAnim = &upLeftNorWeaponAnim;
				} else {
					currentWeaponAnim = &upLeftPowWeaponAnim;
				}

				break;
			}
		}
		idleAnimTop.frames[0] = currentAnimTop->frames[currentAnimTop->GetCurrentFrameNum()];
		idleAnimBot.frames[0] = currentAnimBot->frames[currentAnimBot->GetCurrentFrameNum()];
	}

	if (!dead && !immovable) {
		if (!checkMovingDir()) {
			if (!isThrowing) {
				currentAnimTop = &idleAnimTop;
			}
			currentAnimBot = &idleAnimBot;

			switch (facing) {
			case UP:
				if (weapon == Weapon::NORMAL) {
					currentWeaponAnim = &upNorWeaponAnim;
				} else {
					currentWeaponAnim = &upPowWeaponAnim;
				}
				break;
			case DOWN:
				if (weapon == Weapon::NORMAL) {
					currentWeaponAnim = &downNorWeaponAnim;
				} else {
					currentWeaponAnim = &downPowWeaponAnim;
				}
				break;
			case RIGHT:
				if (weapon == Weapon::NORMAL) {
					currentWeaponAnim = &rightNorWeaponAnim;
				} else {
					currentWeaponAnim = &rightPowWeaponAnim;
				}
				break;
			case LEFT:
				if (weapon == Weapon::NORMAL) {
					currentWeaponAnim = &leftNorWeaponAnim;
				} else {
					currentWeaponAnim = &leftPowWeaponAnim;
				}
				break;
			case UP_RIGHT:
				if (weapon == Weapon::NORMAL) {
					currentWeaponAnim = &upRightNorWeaponAnim;
				} else {
					currentWeaponAnim = &upRightPowWeaponAnim;
				}
				break;
			case UP_LEFT:
				if (weapon == Weapon::NORMAL) {
					currentWeaponAnim = &upLeftNorWeaponAnim;
				} else {
					currentWeaponAnim = &upLeftPowWeaponAnim;
				}
				break;
			case DOWN_RIGHT:
				if (weapon == Weapon::NORMAL) {
					currentWeaponAnim = &downRightNorWeaponAnim;
				} else {
					currentWeaponAnim = &downRightPowWeaponAnim;
				}
				break;
			case DOWN_LEFT:
				if (weapon == Weapon::NORMAL) {
					currentWeaponAnim = &downLeftNorWeaponAnim;
				} else {
					currentWeaponAnim = &downLeftPowWeaponAnim;
				}
				break;
			}
		} else {
			switch (movementDir) {
			case Directions::UP:
				position.y -= speed;

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

				break;
			case Directions::UP_RIGHT:
				position.y -= speed;
				position.x += speed;

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

				break;
			case Directions::RIGHT:
				position.x += speed;

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

				break;
			case Directions::DOWN_RIGHT:
				position.y += speed;
				position.x += speed;

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

				break;
			case Directions::DOWN:
				position.y += speed;

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

				break;
			case Directions::DOWN_LEFT:
				position.y += speed;
				position.x -= speed;

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

				break;
			case Directions::LEFT:
				position.x -= speed;

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

				break;
			case Directions::UP_LEFT:
				position.x -= speed;
				position.y -= speed;

				switch (place) {
				case Place::LAND:
					if (currentAnimBot != &upLeftAnimBot)
						currentAnimBot = &upLeftAnimBot;
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
			}
			switch (facing) {
			case UP:
				if (!isThrowing)
					currentAnimTop = &upAnimTop;
				else if (currentAnimTop != &upThrowGrenade) {
					int suppVar = currentAnimTop->GetCurrentFrameNum();
					currentAnimTop = &upThrowGrenade;
					currentAnimTop->Reset();
					currentAnimTop->BeginAnimationIn(suppVar);
				}

				if (weapon == Weapon::NORMAL) {
					currentWeaponAnim = &upNorWeaponAnim;
				} else {
					currentWeaponAnim = &upPowWeaponAnim;
				}

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
				if (!isThrowing)
					currentAnimTop = &downAnimTop;
				else if (currentAnimTop != &downThrowGrenade) {
					int suppVar = currentAnimTop->GetCurrentFrameNum();
					currentAnimTop = &downThrowGrenade;
					currentAnimTop->Reset();
					currentAnimTop->BeginAnimationIn(suppVar);
				}

				if (weapon == Weapon::NORMAL) {
					currentWeaponAnim = &downNorWeaponAnim;
				} else {
					currentWeaponAnim = &downPowWeaponAnim;
				}

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
				if (!isThrowing)
					currentAnimTop = &rightAnimTop;
				else if (currentAnimTop != &rightThrowGrenade) {
					int suppVar = currentAnimTop->GetCurrentFrameNum();
					currentAnimTop = &rightThrowGrenade;
					currentAnimTop->Reset();
					currentAnimTop->BeginAnimationIn(suppVar);
				}

				if (weapon == Weapon::NORMAL) {
					currentWeaponAnim = &rightNorWeaponAnim;
				} else {
					currentWeaponAnim = &rightPowWeaponAnim;
				}

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
				if (!isThrowing)
					currentAnimTop = &leftAnimTop;
				else if (currentAnimTop != &leftThrowGrenade) {
					int suppVar = currentAnimTop->GetCurrentFrameNum();
					currentAnimTop = &leftThrowGrenade;
					currentAnimTop->Reset();
					currentAnimTop->BeginAnimationIn(suppVar);
				}

				if (weapon == Weapon::NORMAL) {
					currentWeaponAnim = &leftNorWeaponAnim;
				} else {
					currentWeaponAnim = &leftPowWeaponAnim;
				}

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
				if (!isThrowing)
					currentAnimTop = &upRightAnimTop;
				else if (currentAnimTop != &upRightThrowGrenade) {
					int suppVar = currentAnimTop->GetCurrentFrameNum();
					currentAnimTop = &upRightThrowGrenade;
					currentAnimTop->Reset();
					currentAnimTop->BeginAnimationIn(suppVar);
				}

				if (weapon == Weapon::NORMAL) {
					currentWeaponAnim = &upRightNorWeaponAnim;
				} else {
					currentWeaponAnim = &upRightPowWeaponAnim;
				}

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
				if (!isThrowing)
					currentAnimTop = &upLeftAnimTop;
				else if (currentAnimTop != &upLeftThrowGrenade) {
					int suppVar = currentAnimTop->GetCurrentFrameNum();
					currentAnimTop = &upLeftThrowGrenade;
					currentAnimTop->Reset();
					currentAnimTop->BeginAnimationIn(suppVar);
				}

				if (weapon == Weapon::NORMAL) {
					currentWeaponAnim = &upLeftNorWeaponAnim;
				} else {
					currentWeaponAnim = &upLeftPowWeaponAnim;
				}

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
				if (!isThrowing)
					currentAnimTop = &downRightAnimTop;
				else if (currentAnimTop != &downRightThrowGrenade) {
					int suppVar = currentAnimTop->GetCurrentFrameNum();
					currentAnimTop = &downRightThrowGrenade;
					currentAnimTop->Reset();
					currentAnimTop->BeginAnimationIn(suppVar);
				}

				if (weapon == Weapon::NORMAL) {
					currentWeaponAnim = &downRightNorWeaponAnim;
				} else {
					currentWeaponAnim = &downRightPowWeaponAnim;
				}

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
				if (!isThrowing)
					currentAnimTop = &downLeftAnimTop;
				else if (currentAnimTop != &downLeftThrowGrenade) {
					int suppVar = currentAnimTop->GetCurrentFrameNum();
					currentAnimTop = &downLeftThrowGrenade;
					currentAnimTop->Reset();
					currentAnimTop->BeginAnimationIn(suppVar);
				}

				if (weapon == Weapon::NORMAL) {
					currentWeaponAnim = &downLeftNorWeaponAnim;
				} else {
					currentWeaponAnim = &downLeftPowWeaponAnim;
				}

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
				default:
					break;
				}
				// Set the idles to the current frame
				idleAnimTop.frames[0] = currentAnimTop->GetCurrentFrame();
				idleAnimBot.frames[0] = currentAnimBot->GetCurrentFrame();

			}
		}
	}

	if (ammunition == 0 && weapon != Weapon::NORMAL)
		weapon = Weapon::NORMAL;

	// Check to shoot or throw grenade
	bool haveToShoot = false;
	bool haveToThrowGrenade = false;

	if (App->input->controllerCount > 0) {
		for (int i = 0; i < App->input->controllerCount; ++i) {
			if (App->input->controllers[i]->buttons[SDL_CONTROLLER_BUTTON_A] == KEY_DOWN) {
				haveToShoot = true;
			}
			if (App->input->controllers[i]->buttons[SDL_CONTROLLER_BUTTON_B] == KEY_DOWN) {
				haveToThrowGrenade = true;
			}
		}
	}

	if (!dead) {
		if (App->input->keys[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_DOWN || haveToShoot) {
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

		if (isThrowing && currentAnimTop->HasFinished()) {
			isThrowing = false;
		}

		if (App->input->keys[SDL_SCANCODE_E] == KEY_STATE::KEY_DOWN || haveToThrowGrenade) {
			if (grenades > 0 && !isThrowing) {
				throwGrenade();
				switch (facing) {
				case UP:
					upThrowGrenade.Reset();
					if (currentAnimTop != &upThrowGrenade) {
						currentAnimTop = &upThrowGrenade;
					}

					break;
				case UP_RIGHT:
					upRightThrowGrenade.Reset();
					if (currentAnimTop != &upRightThrowGrenade) {
						currentAnimTop = &upRightThrowGrenade;
					}
					break;
				case UP_LEFT:
					upLeftThrowGrenade.Reset();
					if (currentAnimTop != &upLeftThrowGrenade) {
						currentAnimTop = &upLeftThrowGrenade;
					}
					break;
				case DOWN:
					downThrowGrenade.Reset();
					if (currentAnimTop != &downThrowGrenade) {
						currentAnimTop = &downThrowGrenade;
					}
					break;
				case DOWN_RIGHT:
					downRightThrowGrenade.Reset();
					if (currentAnimTop != &downRightThrowGrenade) {
						currentAnimTop = &downRightThrowGrenade;
					}
					break;
				case DOWN_LEFT:
					downLeftThrowGrenade.Reset();
					if (currentAnimTop != &downLeftThrowGrenade) {
						currentAnimTop = &downLeftThrowGrenade;
					}
					break;
				case RIGHT:
					rightThrowGrenade.Reset();
					if (currentAnimTop != &rightThrowGrenade) {
						currentAnimTop = &rightThrowGrenade;
					}
					break;
				case LEFT:
					leftThrowGrenade.Reset();
					if (currentAnimTop != &leftThrowGrenade) {
						currentAnimTop = &leftThrowGrenade;
					}
					break;
				}
			}
		}
	}

	// If the player is dead
	if (dead) {
		invincible = true;

		if (deathCooldown == 0) {
			App->audio->PlayFx(playerDeadFx);
			deathAnimTop.Reset();
			deathAnimBot.Reset();
		}

		deathCooldown++;

		if (currentAnimTop != &deathAnimTop)
			currentAnimTop = &deathAnimTop;
		if (currentAnimBot != &deathAnimBot)
			currentAnimBot = &deathAnimBot;

		if (deathCooldown >= DEATH_ANIM_DURATION) {

			if (lives == 0) {


				int t2 = SDL_GetTicks();
				if ((t2 - t1) / 1000.0f >= 1) {
					continueCooldown--;
					t1 = t2;
				}

				if (App->input->keys[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_DOWN) {
					lives = 3;
					continueCooldown = 9;
				}
				if (App->input->controllerCount > 0) {
					for (int i = 0; i < App->input->controllerCount; ++i) {
						if (App->input->controllers[i]->buttons[SDL_CONTROLLER_BUTTON_A] == KEY_DOWN) {
							lives = 3;
							continueCooldown = 9;
						}
					}
				}

				if (continueCooldown == 0)
					App->fade->FadeToBlack((Module*)App->level1, (Module*)App->title, 0);

			} else {
				deathAnimTop.Reset();
				deathAnimBot.Reset();

				facing = UP;
				if (currentAnimTop != &upAnimTop)
					currentAnimTop = &upAnimTop;
				if (currentAnimBot != &upAnimBot)
					currentAnimBot = &upAnimBot;
				if (currentWeaponAnim != &upNorWeaponAnim)
					currentWeaponAnim = &upNorWeaponAnim;

				dead = false;
				grenades = MAX_GRENADES;
				immovable = true;
				isRespawning = true;
				spawnPoint = this->position.y;
				this->position.y += 150;
				if (weapon != Weapon::NORMAL)
					weapon = Weapon::NORMAL;
				
			}
		}
	}

	if (isRespawning) {
		deathCooldown = 0;
		
		if (spawnPoint < this->position.y) {
			this->position.y--;
		} 
		if (spawnPoint >= this->position.y) {
			immovable = false;
			isRespawning = false;
		}
	}

	if (invincible) {
		invincibleCooldown++;
		if (invincibleCooldown >= INVINCIBLE_DURATION) {
			invincible = false;
			isHit = false;
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

	if (App->input->keys[SDL_SCANCODE_BACKSPACE] == KEY_STATE::KEY_DOWN) {
		if (lives != 3) {
			lives = MAX_LIVES;
		}
	}

	// Insta lose cheat
	if (App->input->keys[SDL_SCANCODE_F4] == KEY_STATE::KEY_DOWN &&
		invincibleCooldown == 0 &&
		!dead) {
		// Handle insta lose
		dead = true;
		lives--;
	}

	if (App->input->keys[SDL_SCANCODE_ESCAPE] == KEY_STATE::KEY_REPEAT) {
		return update_status::UPDATE_STOP;
	}

	place = Place::LAND;

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
	if (!dead) {
		switch (facing) {
		case Directions::LEFT:
			App->render->Blit(weaponTexture, position.x - 14, position.y - 17, &rect);
			break;
		case Directions::UP_LEFT:
			App->render->Blit(weaponTexture, position.x - 14, position.y - 31, &rect);
			break;
		case Directions::UP:
			App->render->Blit(weaponTexture, position.x, position.y - 30, &rect);
			break;
		case Directions::RIGHT:
			App->render->Blit(weaponTexture, position.x + 10, position.y - 16, &rect);
			break;
		case Directions::UP_RIGHT:
			App->render->Blit(weaponTexture, position.x + 15, position.y - 22, &rect);
			break;
		}
	}

	rect = currentAnimBot->GetCurrentFrame();
	App->render->Blit(playerTexture, position.x, position.y + 5, &rect);

	rect = currentAnimTop->GetCurrentFrame();
	App->render->Blit(playerTexture, position.x, position.y - 24, &rect);

	rect = currentWeaponAnim->GetCurrentFrame();
	if (!dead) {
		switch (facing) {
		case Directions::DOWN:
			App->render->Blit(weaponTexture, position.x, position.y - 4, &rect);
			break;
		case Directions::DOWN_RIGHT:
			App->render->Blit(weaponTexture, position.x + 9, position.y - 4, &rect);
			break;
		case Directions::DOWN_LEFT:
			App->render->Blit(weaponTexture, position.x - 16, position.y - 4, &rect);
			break;
		}
	}

	// Parallax
	if (App->level1->IsEnabled()) {
		App->level1->DrawParallax();
	}

	// UI ---
	App->fonts->BlitText(15, 20, font, "1 UP");
	std::string temp = std::to_string(score);
	char const* num_char = temp.c_str();
	App->fonts->BlitText(15, 30, font, num_char);

	// decorative UI
	App->fonts->BlitText(SCREEN_WIDTH - 45, 20, font, "2 UP");
	App->fonts->BlitText(SCREEN_WIDTH - 20, 30, font, "0");
	App->fonts->BlitText(80, 10, font, "HI");
	App->fonts->BlitText(120, 10, font, "30000");
	App->fonts->BlitText(SCREEN_WIDTH - 75, SCREEN_HEIGHT - 15, font, "CREDITS 0");

	if (lives >= 2) {
		// need to change to lives icon
		App->fonts->BlitText(5, SCREEN_HEIGHT - 25, ui_logos, "F");
	}
	if (lives >= 3) {
		// need to change to lives icon
		App->fonts->BlitText(15, SCREEN_HEIGHT - 25, ui_logos, "F");
	}
	if (lives == 0) {
		App->fonts->BlitText((SCREEN_WIDTH / 2) - 48, SCREEN_HEIGHT / 2, font, "CONTINUE?");
		temp = std::to_string(continueCooldown);
		num_char = temp.c_str();
		App->fonts->BlitText((SCREEN_WIDTH / 2) - 64, SCREEN_HEIGHT / 2 + 32, font, "WITHIN");
		App->fonts->BlitText((SCREEN_WIDTH / 2), SCREEN_HEIGHT / 2 + 32, font, num_char);
		App->fonts->BlitText((SCREEN_WIDTH / 2) + 32, SCREEN_HEIGHT / 2 + 32, font, "SECONDS");

	}

	// IJ OP for grenade icon
	App->fonts->BlitText(5, 45, ui_logos, "IJ");
	App->fonts->BlitText(5, 52, ui_logos, "OP");
	temp = std::to_string(grenades);
	num_char = temp.c_str();
	App->fonts->BlitText(5, 59, font, num_char);

	if (weapon != Weapon::NORMAL) {
		// GH MN for gun icon
		App->fonts->BlitText(5, 66, ui_logos, "GH");
		App->fonts->BlitText(5, 74, ui_logos, "MN");
		temp = std::to_string(ammunition);
		num_char = temp.c_str();
		App->fonts->BlitText(5, 81, font, num_char);
	}

	return update_status::UPDATE_CONTINUE;
}

void ModulePlayer::OnCollision(Collider* c1, Collider* c2) {
	if (c1 == collider) {
		switch (c2->type) {
		case Collider::Type::ENEMY:
			if (!godMode && !isHit && !invincible) {
				this->dead = true;
				lives--;
				this->isHit = true;
			}
			break;
		case Collider::Type::ENEMY_SHOT:
			if (!godMode && !isHit && !invincible) {
				this->dead = true;
				lives--;
				this->isHit = true;
			}
			break;
		case Collider::Type::EXPLOSION:
			if (!godMode && !isHit && !invincible) {
				this->dead = true;
				lives--;
				this->isHit = true;
			}
			break;
		case Collider::Type::TRUCK:
			if (!godMode && !isHit && !invincible) {
				this->dead = true;
				lives--;
				this->isHit = true;
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
			if (!isRespawning) {
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
				}
			}
			break;

		case Collider::Type::WATER:
			if (currentAnimBot != &waterAnimBot)
				currentAnimBot = &waterAnimBot;
			if (place != Place::WATER)
				place = Place::WATER;
			break;
		case Collider::Type::TRENCH:
			if (currentAnimBot != &trenchAnimBot)
				currentAnimBot = &trenchAnimBot;
			if (place != Place::TRENCH)
				place = Place::TRENCH;
			break;
		case Collider::Type::BREAKABLE:
			if (!isRespawning) {
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
		case Collider::Type::BREAKABLE_BRIDGE:
			place = Place::LAND;
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
	//App->fonts->Disable();
	App->textures->Unload(playerTexture);
	App->textures->Unload(weaponTexture);
	App->audio->UnloadFx(shotFx);
	App->audio->UnloadFx(playerDeadFx);
	App->audio->UnloadFx(heavyRifleFx);
	App->audio->UnloadFx(flamethrowerFx);
	App->audio->UnloadFx(throwGrenadeFx);
	App->fonts->UnLoad(font);
	App->fonts->UnLoad(ui_logos);
	return true;
}