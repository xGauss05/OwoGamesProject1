#include "ModuleParticles.h"

#include "Application.h"

#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleCollisions.h"
#include "ModuleAudio.h"
#include "SDL/include/SDL_timer.h"

ModuleParticles::ModuleParticles() {
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
		particles[i] = nullptr;
}

ModuleParticles::~ModuleParticles() {
}

bool ModuleParticles::Start() {
	LOG("Loading particles");
	texture = App->textures->Load("img/sprites/bullets.png");

	// Explosion particle
	// Put the animations here, 
	// Variables need to be declared in the header
	explosion.anim.PushBack({ 274, 296, 33, 30 });
	explosion.anim.PushBack({ 313, 296, 33, 30 });
	explosion.anim.PushBack({ 346, 296, 33, 30 });
	explosion.anim.PushBack({ 382, 296, 33, 30 });
	explosion.anim.PushBack({ 419, 296, 33, 30 });
	explosion.anim.PushBack({ 457, 296, 33, 30 });
	explosion.anim.loop = false;
	explosion.anim.speed = 0.3f;

	// Enemy shots
	enemy_shot.anim.PushBack({ 197, 65, 5, 6 });
	enemy_shot.anim.PushBack({ 213, 65, 5, 6 });
	enemy_shot.anim.loop = true;
	enemy_shot.speed.x = 3;
	enemy_shot.lifetime = 30;
	enemy_shot.anim.speed = 0.2f;

	// Normal player shots
	shot_up.anim.PushBack({ 3, 179, 10, 11 });
	shot_up.anim.PushBack({ 20, 178, 10, 11 });
	shot_up.anim.loop = true;
	shot_up.speed.x = 3;
	shot_up.lifetime = 30;
	shot_up.anim.speed = 0.2f;

	shot_up_right.anim.PushBack({ 35,180,9,12 });
	shot_up_right.anim.PushBack({ 51,180,9,12 });
	shot_up_right.anim.loop = true;
	shot_up_right.speed.x = 3;
	shot_up_right.lifetime = 30;
	shot_up_right.anim.speed = 0.2f;

	shot_up_left.anim.PushBack({ 35,180,9,12 });
	shot_up_left.anim.PushBack({ 51,180,9,12 });
	shot_up_left.anim.loop = true;
	shot_up_left.speed.x = 3;
	shot_up_left.lifetime = 30;
	shot_up_left.anim.speed = 0.2f;

	shot_down.anim.PushBack({ 35,180,9,12 });
	shot_down.anim.PushBack({ 51,180,9,12 });
	shot_down.anim.loop = true;
	shot_down.speed.x = 3;
	shot_down.lifetime = 30;
	shot_down.anim.speed = 0.2f;

	shot_down_right.anim.PushBack({ 35,180,9,12 });
	shot_down_right.anim.PushBack({ 51,180,9,12 });
	shot_down_right.anim.loop = true;
	shot_down_right.speed.x = 3;
	shot_down_right.lifetime = 30;
	shot_down_right.anim.speed = 0.2f;

	shot_down_left.anim.PushBack({ 35,180,9,12 });
	shot_down_left.anim.PushBack({ 51,180,9,12 });
	shot_down_left.anim.loop = true;
	shot_down_left.speed.x = 3;
	shot_down_left.lifetime = 30;
	shot_down_left.anim.speed = 0.2f;

	shot_right.anim.PushBack({ 35,180,9,12 });
	shot_right.anim.PushBack({ 51,180,9,12 });
	shot_right.anim.loop = true;
	shot_right.speed.x = 3;
	shot_right.lifetime = 30;
	shot_right.anim.speed = 0.2f;

	shot_left.anim.PushBack({ 35,180,9,12 });
	shot_left.anim.PushBack({ 51,180,9,12 });
	shot_left.anim.loop = true;
	shot_left.speed.x = 3;
	shot_left.lifetime = 30;
	shot_left.anim.speed = 0.2f;

	// Heavy Rifle player shots
	hrifle_up.anim.PushBack({ 5,208,9,29 });
	hrifle_up.anim.PushBack({ 21,208,9,29 });
	hrifle_up.anim.loop = true;
	hrifle_up.speed.x = 3;
	hrifle_up.lifetime = 30;
	hrifle_up.anim.speed = 0.2f;

	hrifle_up_left.anim.PushBack({ 5,208,9,29 });
	hrifle_up_left.anim.PushBack({ 21,208,9,29 });
	hrifle_up_left.anim.loop = true;
	hrifle_up_left.speed.x = 3;
	hrifle_up_left.lifetime = 30;
	hrifle_up_left.anim.speed = 0.2f;

	hrifle_up_right.anim.PushBack({ 5,208,9,29 });
	hrifle_up_right.anim.PushBack({ 21,208,9,29 });
	hrifle_up_right.anim.loop = true;
	hrifle_up_right.speed.x = 3;
	hrifle_up_right.lifetime = 30;
	hrifle_up_right.anim.speed = 0.2f;

	hrifle_down.anim.PushBack({ 5,208,9,29 });
	hrifle_down.anim.PushBack({ 21,208,9,29 });
	hrifle_down.anim.loop = true;
	hrifle_down.speed.x = 3;
	hrifle_down.lifetime = 30;
	hrifle_down.anim.speed = 0.2f;

	hrifle_down_left.anim.PushBack({ 5,208,9,29 });
	hrifle_down_left.anim.PushBack({ 21,208,9,29 });
	hrifle_down_left.anim.loop = true;
	hrifle_down_left.speed.x = 3;
	hrifle_down_left.lifetime = 30;
	hrifle_down_left.anim.speed = 0.2f;

	hrifle_down_right.anim.PushBack({ 5,208,9,29 });
	hrifle_down_right.anim.PushBack({ 21,208,9,29 });
	hrifle_down_right.anim.loop = true;
	hrifle_down_right.speed.x = 3;
	hrifle_down_right.lifetime = 30;
	hrifle_down_right.anim.speed = 0.2f;

	hrifle_right.anim.PushBack({ 5,208,9,29 });
	hrifle_right.anim.PushBack({ 21,208,9,29 });
	hrifle_right.anim.loop = true;
	hrifle_right.speed.x = 3;
	hrifle_right.lifetime = 30;
	hrifle_right.anim.speed = 0.2f;

	hrifle_left.anim.PushBack({ 5,208,9,29 });
	hrifle_left.anim.PushBack({ 21,208,9,29 });
	hrifle_left.anim.loop = true;
	hrifle_left.speed.x = 3;
	hrifle_left.lifetime = 30;
	hrifle_left.anim.speed = 0.2f;

	// Flamethrower player shots
	fthrower_up.anim.PushBack({ 5,0,19,64 });
	fthrower_up.anim.PushBack({ 134,0,18,63 });
	fthrower_up.anim.loop = true;
	fthrower_up.speed.x = 3;
	fthrower_up.lifetime = 30;
	fthrower_up.anim.speed = 0.2f;

	fthrower_up_left.anim.PushBack({ 5,208,9,29 });
	fthrower_up_left.anim.PushBack({ 21,208,9,29 });
	fthrower_up_left.anim.loop = true;
	fthrower_up_left.speed.x = 3;
	fthrower_up_left.lifetime = 30;
	fthrower_up_left.anim.speed = 0.2f;

	fthrower_up_right.anim.PushBack({ 5,208,9,29 });
	fthrower_up_right.anim.PushBack({ 21,208,9,29 });
	fthrower_up_right.anim.loop = true;
	fthrower_up_right.speed.x = 3;
	fthrower_up_right.lifetime = 30;
	fthrower_up_right.anim.speed = 0.2f;

	fthrower_down.anim.PushBack({ 5,208,9,29 });
	fthrower_down.anim.PushBack({ 21,208,9,29 });
	fthrower_down.anim.loop = true;
	fthrower_down.speed.x = 3;
	fthrower_down.lifetime = 30;
	fthrower_down.anim.speed = 0.2f;

	fthrower_down_left.anim.PushBack({ 5,208,9,29 });
	fthrower_down_left.anim.PushBack({ 21,208,9,29 });
	fthrower_down_left.anim.loop = true;
	fthrower_down_left.speed.x = 3;
	fthrower_down_left.lifetime = 30;
	fthrower_down_left.anim.speed = 0.2f;

	fthrower_down_right.anim.PushBack({ 5,208,9,29 });
	fthrower_down_right.anim.PushBack({ 21,208,9,29 });
	fthrower_down_right.anim.loop = true;
	fthrower_down_right.speed.x = 3;
	fthrower_down_right.lifetime = 30;
	fthrower_down_right.anim.speed = 0.2f;

	fthrower_left.anim.PushBack({ 5,208,9,29 });
	fthrower_left.anim.PushBack({ 21,208,9,29 });
	fthrower_left.anim.loop = true;
	fthrower_left.speed.x = 3;
	fthrower_left.lifetime = 30;
	fthrower_left.anim.speed = 0.2f;

	fthrower_right.anim.PushBack({ 5,208,9,29 });
	fthrower_right.anim.PushBack({ 21,208,9,29 });
	fthrower_right.anim.loop = true;
	fthrower_right.speed.x = 3;
	fthrower_right.lifetime = 30;
	fthrower_right.anim.speed = 0.2f;

	return true;
}

bool ModuleParticles::CleanUp() {
	LOG("Unloading particles");

	// Delete all remaining active particles on application exit 
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i) {
		if (particles[i] != nullptr) {
			delete particles[i];
			particles[i] = nullptr;
		}
	}

	return true;
}

void ModuleParticles::OnCollision(Collider* c1, Collider* c2) {
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i) {
		// Always destroy particles that collide
		if (particles[i] != nullptr && particles[i]->collider == c1) {
			if (c2->type == Collider::Type::WALL) {
				App->particles->AddParticle(App->particles->explosion, particles[i]->position.x, particles[i]->position.y - 10);
				App->audio->PlayFx(1);
			}
			if (c2->type == Collider::Type::PLAYER) {

			}
			delete particles[i];
			particles[i] = nullptr;
			break;
		}

	}
}

update_status ModuleParticles::Update() {
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i) {
		Particle* particle = particles[i];

		if (particle == nullptr)	continue;

		// Call particle Update. If it has reached its lifetime, destroy it
		if (particle->Update() == false) {
			delete particle;
			particles[i] = nullptr;
		}
	}

	return update_status::UPDATE_CONTINUE;
}

update_status ModuleParticles::PostUpdate() {
	//Iterating all particle array and drawing any active particles
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i) {
		Particle* particle = particles[i];

		if (particle != nullptr && particle->isAlive) {
			App->render->Blit(texture, particle->position.x, particle->position.y, &(particle->anim.GetCurrentFrame()));
		}
	}

	return update_status::UPDATE_CONTINUE;
}

void ModuleParticles::AddParticle(const Particle& particle, int x, int y, Collider::Type colliderType, uint delay) {
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i) {
		//Finding an empty slot for a new particle
		if (particles[i] == nullptr) {
			Particle* p = new Particle(particle);

			p->frameCount = -(int)delay;			// We start the frameCount as the negative delay
			p->position.x = x;						// so when frameCount reaches 0 the particle will be activated
			p->position.y = y;

			//Adding the particle's collider
			if (colliderType != Collider::Type::NONE)
				p->collider = App->collisions->AddCollider(p->anim.GetCurrentFrame(), colliderType, this);

			particles[i] = p;
			break;
		}
	}
}
