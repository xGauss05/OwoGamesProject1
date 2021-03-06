#include "Application.h"

#include "ModuleParticles.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleCollisions.h"
#include "ModuleAudio.h"

#include "SDL/include/SDL_timer.h"

ModuleParticles::ModuleParticles(bool startEnabled) : Module(startEnabled) {
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
		particles[i] = nullptr;
}

ModuleParticles::~ModuleParticles() {
}

bool ModuleParticles::Start() {
	LOG("Loading particles");
	bulletsTexture = App->textures->Load("Assets/img/sprites/bullets.png");
	explosionTexture = App->textures->Load("Assets/img/sprites/explosions.png");
	hostageTexture = App->textures->Load("Assets/img/sprites/hostage.png");
	greenEnemiesTexture = App->textures->Load("Assets/img/sprites/green_enemy.png");
	redEnemiesTexture = App->textures->Load("Assets/img/sprites/red_enemy.png");
	truckTexture = App->textures->Load("Assets/img/sprites/truck.png");
	grenadeExplosionFx = App->audio->LoadFx("Assets/sounds/sfx/186.wav");

	// Put the animations here, 
	// Variables need to be declared in the header

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
	shot_up.lifetime = 30;
	shot_up.anim.speed = 0.2f;
	shot_up.speed.x = 0;
	shot_up.speed.y = -5;

	shot_up_right.anim.PushBack({ 35,180,9,12 });
	shot_up_right.anim.PushBack({ 51,180,9,12 });
	shot_up_right.anim.loop = true;
	shot_up_right.lifetime = 30;
	shot_up_right.anim.speed = 0.2f;
	shot_up_right.speed.x = 5;
	shot_up_right.speed.y = -5;

	shot_up_left.anim.PushBack({ 227,180,9,12 });
	shot_up_left.anim.PushBack({ 243,180,9,12 });
	shot_up_left.anim.loop = true;
	shot_up_left.lifetime = 30;
	shot_up_left.anim.speed = 0.2f;
	shot_up_left.speed.x = -5;
	shot_up_left.speed.y = -5;

	shot_down.anim.PushBack({ 133,180,9,12 });
	shot_down.anim.PushBack({ 149,180,9,12 });
	shot_down.anim.loop = true;
	shot_down.lifetime = 30;
	shot_down.anim.speed = 0.2f;
	shot_down.speed.x = 0;
	shot_down.speed.y = 5;

	shot_down_right.anim.PushBack({ 98,180,9,12 });
	shot_down_right.anim.PushBack({ 114,180,9,12 });
	shot_down_right.anim.loop = true;
	shot_down_right.lifetime = 30;
	shot_down_right.anim.speed = 0.2f;
	shot_down_right.speed.x = 5;
	shot_down_right.speed.y = 5;

	shot_down_left.anim.PushBack({ 164,180,9,12 });
	shot_down_left.anim.PushBack({ 180,180,9,12 });
	shot_down_left.anim.loop = true;
	shot_down_left.lifetime = 30;
	shot_down_left.anim.speed = 0.2f;
	shot_down_left.speed.x = -5;
	shot_down_left.speed.y = 5;

	shot_right.anim.PushBack({ 66,180,9,12 });
	shot_right.anim.PushBack({ 83,180,9,12 });
	shot_right.anim.loop = true;
	shot_right.lifetime = 30;
	shot_right.anim.speed = 0.2f;
	shot_right.speed.x = 5;
	shot_right.speed.y = 0;

	shot_left.anim.PushBack({ 195,180,9,12 });
	shot_left.anim.PushBack({ 210,180,9,12 });
	shot_left.anim.loop = true;
	shot_left.lifetime = 30;
	shot_left.anim.speed = 0.2f;
	shot_left.speed.x = -5;
	shot_left.speed.y = 0;
	shot_left.explodes = false;
	shot_left.isExplosion = false;

	// Heavy Rifle player shots
	hrifle_up.anim.PushBack({ 5,208,9,29 });
	hrifle_up.anim.PushBack({ 21,208,9,29 });
	hrifle_up.anim.loop = true;
	hrifle_up.lifetime = 30;
	hrifle_up.anim.speed = 0.2f;
	hrifle_up.speed.x = 0;
	hrifle_up.speed.y = -5;
	hrifle_up.explodes = true;

	hrifle_up_left.anim.PushBack({ 203,211,24,25 });
	hrifle_up_left.anim.PushBack({ 227,211,24,25 });
	hrifle_up_left.anim.loop = true;
	hrifle_up_left.lifetime = 30;
	hrifle_up_left.anim.speed = 0.2f;
	hrifle_up_left.speed.x = -5;
	hrifle_up_left.speed.y = -5;
	hrifle_up_left.explodes = true;

	hrifle_up_right.anim.PushBack({ 33,211,27,29 });
	hrifle_up_right.anim.PushBack({ 60,211,27,29 });
	hrifle_up_right.anim.loop = true;
	hrifle_up_right.lifetime = 30;
	hrifle_up_right.anim.speed = 0.2f;
	hrifle_up_right.speed.x = 5;
	hrifle_up_right.speed.y = -5;
	hrifle_up_right.explodes = true;

	hrifle_down.anim.PushBack({ 5,208,9,29 });
	hrifle_down.anim.PushBack({ 21,208,9,29 });
	hrifle_down.anim.loop = true;
	hrifle_down.lifetime = 30;
	hrifle_down.anim.speed = 0.2f;
	hrifle_down.speed.x = 0;
	hrifle_down.speed.y = 5;
	hrifle_down.explodes = true;

	hrifle_down_left.anim.PushBack({ 147,211,24,25 });
	hrifle_down_left.anim.PushBack({ 171,211,24,25 });
	hrifle_down_left.anim.loop = true;
	hrifle_down_left.lifetime = 30;
	hrifle_down_left.anim.speed = 0.2f;
	hrifle_down_left.speed.x = -5;
	hrifle_down_left.speed.y = 5;
	hrifle_down_left.explodes = true;

	hrifle_down_right.anim.PushBack({ 91,208,24,25 });
	hrifle_down_right.anim.PushBack({ 116,208,24,25 });
	hrifle_down_right.anim.loop = true;
	hrifle_down_right.lifetime = 30;
	hrifle_down_right.anim.speed = 0.2f;
	hrifle_down_right.speed.x = 5;
	hrifle_down_right.speed.y = 5;
	hrifle_down_right.explodes = true;

	hrifle_right.anim.PushBack({ 3,245,28,7 });
	hrifle_right.anim.PushBack({ 34,245,28,7 });
	hrifle_right.anim.loop = true;
	hrifle_right.lifetime = 30;
	hrifle_right.anim.speed = 0.2f;
	hrifle_right.speed.x = 5;
	hrifle_right.speed.y = 0;
	hrifle_right.explodes = true;

	hrifle_left.anim.PushBack({ 64,245,28,7 });
	hrifle_left.anim.PushBack({ 96,245,28,7 });
	hrifle_left.anim.loop = true;
	hrifle_left.lifetime = 30;
	hrifle_left.anim.speed = 0.2f;
	hrifle_left.speed.x = -5;
	hrifle_left.speed.y = 0;
	hrifle_left.explodes = true;

	// Flamethrower player shots
	fthrower_up.anim.PushBack({ 5,0,19,64 });
	fthrower_up.anim.PushBack({ 134,0,18,63 });
	fthrower_up.anim.loop = true;
	fthrower_up.lifetime = 30;
	fthrower_up.anim.speed = 0.2f;
	fthrower_up.speed.x = 0;
	fthrower_up.speed.y = -5;
	fthrower_up.explodes = true;

	fthrower_up_left.anim.PushBack({ 0,111,43,44 });
	fthrower_up_left.anim.PushBack({ 95,111,44,42 });
	fthrower_up_left.anim.loop = true;
	fthrower_up_left.lifetime = 30;
	fthrower_up_left.anim.speed = 0.2f;
	fthrower_up_left.speed.x = -5;
	fthrower_up_left.speed.y = -5;
	fthrower_up_left.explodes = true;

	fthrower_up_right.anim.PushBack({ 4,63,44,44 });
	fthrower_up_right.anim.PushBack({ 100,63,44,42 });
	fthrower_up_right.anim.loop = true;
	fthrower_up_right.lifetime = 30;
	fthrower_up_right.anim.speed = 0.2f;
	fthrower_up_right.speed.x = 5;
	fthrower_up_right.speed.y = -5;
	fthrower_up_right.explodes = true;

	fthrower_down.anim.PushBack({ 101,0,19,64 });
	fthrower_down.anim.PushBack({ 230,1,18,63 });
	fthrower_down.anim.loop = true;
	fthrower_down.lifetime = 30;
	fthrower_down.anim.speed = 0.2f;
	fthrower_down.speed.x = 0;
	fthrower_down.speed.y = 5;
	fthrower_down.explodes = true;

	fthrower_down_left.anim.PushBack({ 47,116,44,44 });
	fthrower_down_left.anim.PushBack({ 143,116,42,44 });
	fthrower_down_left.anim.loop = true;
	fthrower_down_left.lifetime = 30;
	fthrower_down_left.anim.speed = 0.2f;
	fthrower_down_left.speed.x = -5;
	fthrower_down_left.speed.y = 5;
	fthrower_down_left.explodes = true;

	fthrower_down_right.anim.PushBack({ 52,68,44,44 });
	fthrower_down_right.anim.PushBack({ 150,68,42,44 });
	fthrower_down_right.anim.loop = true;
	fthrower_down_right.lifetime = 30;
	fthrower_down_right.anim.speed = 0.2f;
	fthrower_down_right.speed.x = 5;
	fthrower_down_right.speed.y = 5;
	fthrower_down_right.explodes = true;

	fthrower_left.anim.PushBack({ 31,39,65,18 });
	fthrower_left.anim.PushBack({ 159,39,64,19 });
	fthrower_left.anim.loop = true;
	fthrower_left.lifetime = 30;
	fthrower_left.anim.speed = 0.2f;
	fthrower_left.speed.x = -5;
	fthrower_left.speed.y = 0;
	fthrower_left.explodes = true;

	fthrower_right.anim.PushBack({ 31,5,65,19 });
	fthrower_right.anim.PushBack({ 160,6,64,18 });
	fthrower_right.anim.loop = true;
	fthrower_right.lifetime = 30;
	fthrower_right.anim.speed = 0.2f;
	fthrower_right.speed.x = 5;
	fthrower_right.speed.y = 0;
	fthrower_right.explodes = true;

	// Grenade player/enemy shots
	grenade.anim.PushBack({ 0,160,16,16 });
	grenade.anim.PushBack({ 16,160,16,16 });
	grenade.anim.PushBack({ 32,160,16,16 });
	grenade.anim.PushBack({ 48,160,16,16 });
	grenade.anim.PushBack({ 64,160,16,16 });
	grenade.anim.PushBack({ 80,160,16,16 });
	grenade.anim.PushBack({ 96,160,16,16 });
	grenade.anim.PushBack({ 112,160,16,16 });
	grenade.anim.PushBack({ 128,160,16,16 });
	grenade.anim.PushBack({ 144,160,16,16 });
	grenade.anim.PushBack({ 160,160,16,16 });
	grenade.anim.PushBack({ 176,160,16,16 });
	grenade.anim.loop = true;
	grenade.lifetime = 50;
	grenade.anim.speed = 0.2f;
	grenade.speed.x = 0;
	grenade.speed.y = 5;
	grenade.explodes = true;

	grenExplosion.anim.PushBack({ 0,0,64,64 });
	grenExplosion.anim.PushBack({ 64,0,64,64 });
	grenExplosion.anim.PushBack({ 128,0,64,64 });
	grenExplosion.anim.PushBack({ 192,0,64,64 });
	grenExplosion.anim.PushBack({ 256,0,64,64 });
	grenExplosion.anim.PushBack({ 320,0,64,64 });
	grenExplosion.anim.loop = false;
	grenExplosion.anim.speed = 0.45f;
	grenExplosion.speed.x = 0;
	grenExplosion.speed.y = 0;
	grenExplosion.isExplosion = true;

	// Hostage "particles"
	hostagePickUpTop.anim.PushBack({ 0 ,64,32,32 });
	hostagePickUpTop.anim.PushBack({ 32 ,64,32,32 });
	hostagePickUpTop.anim.PushBack({ 64 ,64,32,32 });
	hostagePickUpTop.anim.PushBack({ 96 ,64,32,32 });
	hostagePickUpTop.anim.speed = 0.08f;
	hostagePickUpTop.anim.loop = false;
	hostagePickUpTop.isHostage = true;

	hostagePickUpBot.anim.PushBack({ 0,96,32, 32 });
	hostagePickUpBot.anim.PushBack({ 32,96,32, 32 });
	hostagePickUpBot.anim.PushBack({ 64,96,32, 32 });
	hostagePickUpBot.anim.PushBack({ 96,96,32, 32 });
	hostagePickUpBot.anim.speed = 0.08f;
	hostagePickUpBot.anim.loop = false;
	hostagePickUpBot.isHostage = true;

	hostageDeathTop.anim.PushBack({ 0,  128, 32, 32 });
	hostageDeathTop.anim.PushBack({ 32, 128, 32, 32 });
	hostageDeathTop.anim.PushBack({ 64, 128, 32, 32 });
	hostageDeathTop.anim.PushBack({ 96, 128, 32, 32 });
	hostageDeathTop.anim.speed = 0.08f;
	hostageDeathTop.anim.loop = false;
	hostageDeathTop.isHostage = true;

	hostageDeathBot.anim.PushBack({ 0,  160, 32, 32 });
	hostageDeathBot.anim.PushBack({ 32, 160, 32, 32 });
	hostageDeathBot.anim.PushBack({ 64, 160, 32, 32 });
	hostageDeathBot.anim.PushBack({ 96, 160, 32, 32 });
	hostageDeathBot.anim.speed = 0.08f;
	hostageDeathBot.anim.loop = false;
	hostageDeathBot.isHostage = true;

	//Enemy deaths
	greenDeathAnimTop.anim.PushBack({ 0,  448,32,32 });
	greenDeathAnimTop.anim.PushBack({ 32, 448,32,32 });
	greenDeathAnimTop.anim.PushBack({ 64, 448,32,32 });
	greenDeathAnimTop.anim.PushBack({ 96, 448,32,32 });
	greenDeathAnimTop.anim.PushBack({ 128,448,32,32 });
	greenDeathAnimTop.anim.PushBack({ 160,448,32,32 });
	greenDeathAnimTop.anim.PushBack({ 192,448,32,32 });
	greenDeathAnimTop.anim.PushBack({ 224,448,32,32 });
	greenDeathAnimTop.anim.PushBack({ 256,448,32,32 });
	greenDeathAnimTop.anim.PushBack({ 288,448,32,32 });
	greenDeathAnimTop.anim.PushBack({ 320,448,32,32 });
	greenDeathAnimTop.anim.PushBack({ 352,448,32,32 });
	greenDeathAnimTop.anim.PushBack({ 384,448,32,32 });
	greenDeathAnimTop.anim.speed = 0.2f;
	greenDeathAnimTop.lifetime = 70;
	greenDeathAnimTop.speed = { 0, -1 };
	greenDeathAnimTop.anim.loop = false;
	greenDeathAnimTop.isGreenEnemy = true;

	greenDeathAnimBot.anim.PushBack({ 0,  480,32,32 });
	greenDeathAnimBot.anim.PushBack({ 32, 480,32,32 });
	greenDeathAnimBot.anim.PushBack({ 64, 480,32,32 });
	greenDeathAnimBot.anim.PushBack({ 96, 480,32,32 });
	greenDeathAnimBot.anim.PushBack({ 128,480,32,32 });
	greenDeathAnimBot.anim.PushBack({ 160,480,32,32 });
	greenDeathAnimBot.anim.PushBack({ 192,480,32,32 });
	greenDeathAnimBot.anim.PushBack({ 224,480,32,32 });
	greenDeathAnimBot.anim.PushBack({ 256,480,32,32 });
	greenDeathAnimBot.anim.PushBack({ 288,480,32,32 });
	greenDeathAnimBot.anim.PushBack({ 320,480,32,32 });
	greenDeathAnimBot.anim.PushBack({ 352,480,32,32 });
	greenDeathAnimBot.anim.PushBack({ 384,480,32,32 });
	greenDeathAnimBot.anim.speed = 0.2f;
	greenDeathAnimBot.lifetime = 70;
	greenDeathAnimBot.speed = { 0, -1 };
	greenDeathAnimBot.anim.loop = false;
	greenDeathAnimBot.isGreenEnemy = true;

	redDeathAnimTop.anim.PushBack({ 0,  448,32,32 });
	redDeathAnimTop.anim.PushBack({ 32, 448,32,32 });
	redDeathAnimTop.anim.PushBack({ 64, 448,32,32 });
	redDeathAnimTop.anim.PushBack({ 96, 448,32,32 });
	redDeathAnimTop.anim.PushBack({ 128,448,32,32 });
	redDeathAnimTop.anim.PushBack({ 160,448,32,32 });
	redDeathAnimTop.anim.PushBack({ 192,448,32,32 });
	redDeathAnimTop.anim.PushBack({ 224,448,32,32 });
	redDeathAnimTop.anim.PushBack({ 256,448,32,32 });
	redDeathAnimTop.anim.PushBack({ 288,448,32,32 });
	redDeathAnimTop.anim.PushBack({ 320,448,32,32 });
	redDeathAnimTop.anim.PushBack({ 352,448,32,32 });
	redDeathAnimTop.anim.PushBack({ 384,448,32,32 });
	redDeathAnimTop.anim.speed = 0.2f;
	redDeathAnimTop.lifetime = 70;
	redDeathAnimTop.speed = { 0, -1 };
	redDeathAnimTop.anim.loop = false;
	redDeathAnimTop.isRedEnemy = true;

	redDeathAnimBot.anim.PushBack({ 0,  480,32,32 });
	redDeathAnimBot.anim.PushBack({ 32, 480,32,32 });
	redDeathAnimBot.anim.PushBack({ 64, 480,32,32 });
	redDeathAnimBot.anim.PushBack({ 96, 480,32,32 });
	redDeathAnimBot.anim.PushBack({ 128,480,32,32 });
	redDeathAnimBot.anim.PushBack({ 160,480,32,32 });
	redDeathAnimBot.anim.PushBack({ 192,480,32,32 });
	redDeathAnimBot.anim.PushBack({ 224,480,32,32 });
	redDeathAnimBot.anim.PushBack({ 256,480,32,32 });
	redDeathAnimBot.anim.PushBack({ 288,480,32,32 });
	redDeathAnimBot.anim.PushBack({ 320,480,32,32 });
	redDeathAnimBot.anim.PushBack({ 352,480,32,32 });
	redDeathAnimBot.anim.PushBack({ 384,480,32,32 });
	redDeathAnimBot.anim.speed = 0.2f;
	redDeathAnimBot.lifetime = 70;
	redDeathAnimBot.speed = { 0, -1 };
	redDeathAnimBot.anim.loop = false;
	redDeathAnimBot.isRedEnemy = true;

	truckAnim.anim.PushBack({ 0, 63, 92, 58 });
	truckAnim.anim.PushBack({ 96, 63, 92, 58 });
	truckAnim.anim.PushBack({ 0, 63, 92, 58 });
	truckAnim.anim.PushBack({ 96, 63, 92, 58 });
	truckAnim.anim.speed = 0.2f;
	truckAnim.lifetime = 70;
	truckAnim.anim.loop = false;
	truckAnim.isTruckEnemy = true;

	return true;
}

bool ModuleParticles::CleanUp() {
	LOG("Unloading particles");
	App->textures->Unload(bulletsTexture);
	App->textures->Unload(explosionTexture);
	App->textures->Unload(hostageTexture);
	App->textures->Unload(greenEnemiesTexture);
	App->textures->Unload(redEnemiesTexture);
	App->textures->Unload(truckTexture);
	App->audio->UnloadFx(grenadeExplosionFx);
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
			if (c2->type == Collider::Type::BREAKABLE ||
				c2->type == Collider::Type::ENEMY ||
				c2->type == Collider::Type::TRUCK ||
				c2->type == Collider::Type::BOSS ||
				c2->type == Collider::Type::HOSTAGE) {
				if (particles[i]->explodes && !particles[i]->isExplosion) {
					App->particles->AddParticle(App->particles->grenExplosion, particles[i]->position.x - 26, particles[i]->position.y - 26, Collider::Type::EXPLOSION);
					App->audio->PlayFx(grenadeExplosionFx);
				}
			}
			if (!particles[i]->isExplosion && !particles[i]->isHostage) {
				delete particles[i];
				particles[i] = nullptr;
			}
			break;
		}
	}
}

update_status ModuleParticles::Update() {
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i) {
		Particle* particle = particles[i];

		if (particle == nullptr)	continue;

		// Call particle Update. If it has reached its lifetime, destroy it
		if (!particle->Update()) {
			if (particle->explodes && !particle->isExplosion) {
				App->particles->AddParticle(App->particles->grenExplosion, particle->position.x - 26, particle->position.y - 26, Collider::Type::EXPLOSION);
				App->audio->PlayFx(grenadeExplosionFx);
			}

			delete particle;
			particles[i] = nullptr;
		}
	}

	return update_status::UPDATE_CONTINUE;
}

update_status ModuleParticles::PostUpdate() {
	// Iterating all particle array and drawing any active particles
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i) {
		Particle* particle = particles[i];

		if (particle != nullptr && particle->isAlive) {
			if (particle->explodes && !particle->isExplosion && !particle->isHostage && !particle->isGreenEnemy && !particle->isRedEnemy && !particle->isTruckEnemy ||
				!particle->explodes && !particle->isExplosion && !particle->isHostage && !particle->isGreenEnemy && !particle->isRedEnemy && !particle->isTruckEnemy) {
				App->render->Blit(bulletsTexture, particle->position.x, particle->position.y, &(particle->anim.GetCurrentFrame()));
			} else if (!particle->explodes && particle->isExplosion) {
				App->render->Blit(explosionTexture, particle->position.x, particle->position.y, &(particle->anim.GetCurrentFrame()));
			} else if (particle->isHostage) {
				App->render->Blit(hostageTexture, particle->position.x, particle->position.y, &(particle->anim.GetCurrentFrame()));
			} else if (particle->isGreenEnemy) {
				App->render->Blit(greenEnemiesTexture, particle->position.x, particle->position.y, &(particle->anim.GetCurrentFrame()));
			} else if (particle->isRedEnemy) {
				App->render->Blit(redEnemiesTexture, particle->position.x, particle->position.y, &(particle->anim.GetCurrentFrame()));
			} else if (particle->isTruckEnemy) {
				App->render->Blit(truckTexture, particle->position.x, particle->position.y, &(particle->anim.GetCurrentFrame()));
			}
		}
	}
	return update_status::UPDATE_CONTINUE;
}

void ModuleParticles::AddParticle(const Particle& particle, int x, int y, Collider::Type colliderType, uint delay) {
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i) {
		// Finding an empty slot for a new particle
		if (particles[i] == nullptr) {
			Particle* p = new Particle(particle);
			p->frameCount = -(int)delay;			// We start the frameCount as the negative delay
			p->position.x = x;						// so when frameCount reaches 0 the particle will be activated
			p->position.y = y;

			// Adding the particle's collider
			if (colliderType != Collider::Type::NONE)
				p->collider = App->collisions->AddCollider(p->anim.GetCurrentFrame(), colliderType, this);

			particles[i] = p;
			break;
		}
	}
}

