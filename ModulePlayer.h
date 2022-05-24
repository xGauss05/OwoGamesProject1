#ifndef __MODULE_PLAYER_H__
#define __MODULE_PLAYER_H__

#include "Module.h"
#include "Animation.h"
#include "p2Point.h"

struct SDL_Texture;
struct Collider;

#define MAX_AMMO	50
#define MAX_GRENADES 50

enum Directions {
	UP, DOWN, RIGHT, 
	LEFT, UP_RIGHT, UP_LEFT, 
	DOWN_RIGHT, DOWN_LEFT
};

enum Weapon {
	NORMAL, HEAVY_RIFLE, FLAMETHROWER
};

enum Place {
	LAND, WATER, TRENCH
};

class ModulePlayer : public Module {
public:
	// Constructor
	ModulePlayer(bool startEnabled);

	// Destructor
	~ModulePlayer();

	// Called when the module is activated
	// Loads the necessary textures for the player
	bool Start() override;

	// Functions to shoot the corresponding weapon
	void shootNormal();
	void shootHeavyRifle();
	void shootFlamethrower();
	void throwGrenade();

	// Called at the middle of the application loop
	// Processes new input and handles player movement
	update_status Update() override;

	// Called at the end of the application loop
	// Performs the render call of the player sprite
	update_status PostUpdate() override;

	// Collision callback, called when the player intersects with another collider
	void OnCollision(Collider* c1, Collider* c2) override;

	bool CleanUp() override;
public:
	// Position of the player in the map
	iPoint position;

	// The speed in which we move the player (pixels per frame)
	int speed = 1;

	// The player spritesheet loaded into an SDL_Texture
	SDL_Texture* playerTexture = nullptr;
	SDL_Texture* weaponTexture = nullptr;

	// Sets the player direction
	Directions facing;

	// Variable to handle wall collisions.
	Directions movementDir;

	// Sets the weapon that the player has
	Weapon weapon;

	// Set place player is in
	Place place;

	// The pointer to the current player animation
	// It will be switched depending on the player's movement direction
	Animation* currentAnimTop = nullptr;
	Animation* currentAnimBot = nullptr;
	Animation* currentWeaponAnim = nullptr;

	// Animations ---
	
	// Idle animation
	Animation idleAnimTop, idleAnimBot;
	// Up
	Animation upAnimTop, upAnimBot;
	// Up-Right
	Animation upRightAnimTop, upRightAnimBot;
	// Up-Left
	Animation upLeftAnimTop, upLeftAnimBot;
	// Down
	Animation downAnimTop, downAnimBot;
	// Down-Right
	Animation downRightAnimTop, downRightAnimBot;
	// Down-Left
	Animation downLeftAnimTop, downLeftAnimBot;
	// Right
	Animation rightAnimTop, rightAnimBot;
	// Left
	Animation leftAnimTop, leftAnimBot;
	// Death
	Animation deathAnimTop, deathAnimBot;
	//No leg
	Animation waterAnimBot, trenchAnimBot;

	// Weapon animations ---
	// Up
	Animation upNorWeaponAnim, upPowWeaponAnim;
	Animation upShotNorWeaponAnim, upShotPowWeaponAnim;	
	// Up-Right
	Animation upRightNorWeaponAnim, upRightPowWeaponAnim;
	Animation upRightShotNorWeaponAnim, upRightShotPowWeaponAnim;
	// Up-Left
	Animation upLeftNorWeaponAnim, upLeftPowWeaponAnim;
	Animation upLeftShotNorWeaponAnim, upLeftShotPowWeaponAnim;
	// Down
	Animation downNorWeaponAnim, downPowWeaponAnim;
	Animation downShotNorWeaponAnim, downShotPowWeaponAnim;
	// Down-Right
	Animation downRightNorWeaponAnim, downRightPowWeaponAnim;
	Animation downRightShotNorWeaponAnim, downRightShotPowWeaponAnim;
	// Down-Left
	Animation downLeftNorWeaponAnim, downLeftPowWeaponAnim;
	Animation downLeftShotNorWeaponAnim, downLeftShotPowWeaponAnim;
	// Right
	Animation rightNorWeaponAnim, rightPowWeaponAnim;
	Animation rightShotNorWeaponAnim, rightShotPowWeaponAnim;
	// Left
	Animation leftNorWeaponAnim, leftPowWeaponAnim;
	Animation leftShotNorWeaponAnim, leftShotPowWeaponAnim;

	// Throw grenade animations ---
	// Up
	Animation upThrowGrenade;
	// Up-Right
	Animation upRightThrowGrenade;
	// Up-Left
	Animation upLeftThrowGrenade;
	// Down
	Animation downThrowGrenade;
	// Down-Right
	Animation downRightThrowGrenade;
	// Down-Right
	Animation downLeftThrowGrenade;
	// Right
	Animation rightThrowGrenade;
	// Left
	Animation leftThrowGrenade;

	ushort deathCooldown = 0;
	ushort invincibleCooldown = 0;
	// The player's collider
	Collider* collider = nullptr;

	// A flag to detect when the player has been killed
	bool dead = false;

	// God mode flag
	bool godMode = false;

	// Flag for throwing grenade state
	bool isThrowing = false;

	// Flag to prevent the player from moving
	bool immovable = false;

	// Amount of shots available. Max defined in MAX_AMMO
	ushort ammunition = 0;

	// Score of the player
	uint score;

	// Spawn point where it needs to spawn
	ushort spawnPoint;

	// Lives of the player
	ushort lives = 2;

	// Amount of grenades available. Max defined in MAX_GRENADES
	ushort grenades = MAX_GRENADES;

	// Sound effects indexes
	uint shotFx = 0;
	uint playerDeadFx = 0;
	uint heavyRifleFx = 0;
	uint flamethrowerFx = 0;
	uint throwGrenadeFx = 0;

	// Fonts indexes
	uint font = 0;
	uint ui_logos = 0;
};

#endif //!__MODULE_PLAYER_H__
