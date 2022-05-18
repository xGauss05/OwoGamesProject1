#ifndef __MODULE_PARTICLES_H__
#define __MODULE_PARTICLES_H__

#include "Module.h"

#include "Globals.h"
#include "Particle.h"
#include "Collider.h"
#include "ModuleAudio.h"

#define MAX_ACTIVE_PARTICLES 500

struct SDL_Texture;
struct Collider;

class ModuleParticles : public Module {
public:
	// Constructor
	// Initializes all the particles in the array to nullptr
	ModuleParticles(bool startEnabled);

	//Destructor
	~ModuleParticles();

	// Called when the module is activated
	// Loads the necessary textures for the particles
	bool Start() override;

	// Called at the middle of the application loop
	// Iterates all the particles and calls its Update()
	// Removes any "dead" particles
	update_status Update() override;

	// Called at the end of the application loop
	// Iterates all the particles and draws them
	update_status PostUpdate() override;

	// Called on application exit
	// Destroys all active particles left in the array
	bool CleanUp() override;

	// Called when a particle collider hits another collider
	void OnCollision(Collider* c1, Collider* c2) override;

	// Creates a new particle and adds it to the array
	// Param particle	- A template particle from which the new particle will be created
	// Param x, y		- Position x,y in the screen (upper left axis)
	// Param delay		- Delay time from the moment the function is called until the particle is displayed in screen
	void AddParticle(const Particle& particle, int x, int y, Collider::Type colliderType = Collider::Type::NONE, uint delay = 0);

private:
	// Particles spritesheet loaded into an SDL Texture
	SDL_Texture* bulletsTexture = nullptr;
	SDL_Texture* explosionTexture = nullptr;

	// An array to store and handle all the particles
	Particle* particles[MAX_ACTIVE_PARTICLES] = { nullptr };

public:
	// All Particle variables here

	// Enemy shot
	Particle enemy_shot;

	// Normal player shots
	Particle shot_up, shot_up_left, shot_up_right,
			 shot_down, shot_down_left, shot_down_right,
			 shot_left, shot_right;

	// Heavy Rifle player shots
	Particle hrifle_up, hrifle_up_left, hrifle_up_right,
			 hrifle_down, hrifle_down_left, hrifle_down_right,
			 hrifle_left, hrifle_right;

	// Flamethrower player shots
	Particle fthrower_up, fthrower_up_left, fthrower_up_right,
			 fthrower_down, fthrower_down_left, fthrower_down_right,
			 fthrower_left, fthrower_right;

	// Generic grenade
	Particle grenade;

	// Explosion
	Particle grenExplosion;

	uint grenadeExplosionFx = 0;

};

#endif // !__MODULEPARTICLES_H__
