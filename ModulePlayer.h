#ifndef __MODULE_PLAYER_H__
#define __MODULE_PLAYER_H__

#include "Module.h"
#include "Animation.h"
#include "p2Point.h"

struct SDL_Texture;
struct Collider;

#define MAX_AMMO	50

enum Directions {
	UP, DOWN, RIGHT, 
	LEFT, UP_RIGHT, UP_LEFT, 
	DOWN_RIGHT, DOWN_LEFT
};

enum Weapon {
	NORMAL, HEAVY_RIFLE, FLAMETHROWER
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

	// Called at the middle of the application loop
	// Processes new input and handles player movement
	update_status Update() override;

	// Called at the end of the application loop
	// Performs the render call of the player sprite
	update_status PostUpdate() override;

	// Collision callback, called when the player intersects with another collider
	void OnCollision(Collider* c1, Collider* c2) override;

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


	// The player's collider
	Collider* collider = nullptr;

	// A flag to detect when the player has been destroyed
	bool dead = false;

	// God mode flag
	bool godMode = false;

	// Amount of shots available. Max defined in MAX_AMMO
	ushort ammunition = 0;

	// Sound effects indices
	uint shotFx = 0;
	uint deadFx = 0;
	uint heavyRifleFx = 0;
	uint flamethrowerFx = 0;
};

#endif //!__MODULE_PLAYER_H__
