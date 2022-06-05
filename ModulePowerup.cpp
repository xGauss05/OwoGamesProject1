#include "ModulePowerup.h"

#include "Application.h"
#include "Globals.h"

#include "ModuleRender.h"
#include "ModuleTextures.h"
#include "ModuleAudio.h"
#include "ModuleCollisions.h"

#include "Powerup.h"
#include "Powerup_HeavyRifle.h"
#include "Powerup_Flamethrower.h"
#include "Powerup_Hostage.h"

#define SPAWN_MARGIN	50

ModulePowerup::ModulePowerup(bool startEnabled) : Module(startEnabled) {
	for (uint i = 0; i < MAX_POWERUPS; ++i)
		powerUps[i] = nullptr;
}

ModulePowerup::~ModulePowerup() {
}

bool ModulePowerup::Start() {

	weaponTexture = App->textures->Load("Assets/img/sprites/weapon.png");
	hostageTexture = App->textures->Load("Assets/img/sprites/hostage.png");
	weaponPickUpFx = App->audio->LoadFx("Assets/sounds/sfx/165.wav");
	hostagePickUpFx = App->audio->LoadFx("Assets/sounds/sfx/181.wav");

	return true;
}

update_status ModulePowerup::Update() {
	HandlePowerupsSpawn();

	for (uint i = 0; i < MAX_POWERUPS; ++i) {
		if (powerUps[i] != nullptr)
			powerUps[i]->Update();
	}

	HandlePowerupsDespawn();
	return update_status::UPDATE_CONTINUE;
}

update_status ModulePowerup::PostUpdate() {
	for (uint i = 0; i < MAX_POWERUPS; ++i) {
		if (powerUps[i] != nullptr)
			powerUps[i]->Draw();
	}
	return update_status::UPDATE_CONTINUE;
}

bool ModulePowerup::CleanUp() {
	LOG("Freeing all powerups");
	App->textures->Unload(weaponTexture);
	App->textures->Unload(hostageTexture);
	App->audio->UnloadFx(weaponPickUpFx);
	App->audio->UnloadFx(hostagePickUpFx);
	for (uint i = 0; i < MAX_POWERUPS; ++i) {
		if (powerUps[i] != nullptr) {
			App->audio->UnloadFx(powerUps[i]->pickUpFx);
			App->textures->Unload(powerUps[i]->texture);
			delete powerUps[i];
			powerUps[i] = nullptr;
		}
	}

	return true;
}

bool ModulePowerup::AddPowerup(POWERUP_TYPE type, int x, int y) {
	bool ret = false;

	for (uint i = 0; i < MAX_POWERUPS; ++i) {
		if (spawnQueue[i].type == POWERUP_TYPE::NO_TYPE) {
			spawnQueue[i].type = type;
			spawnQueue[i].x = x;
			spawnQueue[i].y = y;
			ret = true;
			break;
		}
	}

	return ret;
}

void ModulePowerup::HandlePowerupsSpawn() {
	// Iterate all the powerups queue
	for (uint i = 0; i < MAX_POWERUPS; ++i) {
		if (spawnQueue[i].type != POWERUP_TYPE::NO_TYPE) {
			// Spawn a new powerup if the screen has reached a spawn position
			if (spawnQueue[i].y > App->render->camera.y - SPAWN_MARGIN) {
				LOG("Spawning powerup at %d", spawnQueue[i].x * SCREEN_SIZE);

				SpawnPowerup(spawnQueue[i]);
				spawnQueue[i].type = POWERUP_TYPE::NO_TYPE; // Removing the newly spawned powerup from the queue
			}
		}
	}
}

void ModulePowerup::HandlePowerupsDespawn() {
	// Iterate existing powerups
	for (uint i = 0; i < MAX_POWERUPS; ++i) {
		if (powerUps[i] != nullptr) {
			// Delete the powerup when it has reached the end of the screen
			if (powerUps[i]->position.y > App->render->camera.y + App->render->camera.h + SPAWN_MARGIN) {
				LOG("DeSpawning powerup at %d. ", powerUps[i]->position.x * SCREEN_SIZE);

				delete powerUps[i];
				powerUps[i] = nullptr;
			}
		}
	}
}

void ModulePowerup::SpawnPowerup(const PowerupSpawnpoint& info) {
	// Find an empty slot in the powerups array
	for (uint i = 0; i < MAX_POWERUPS; ++i) {
		if (powerUps[i] == nullptr) {
			switch (info.type) {
			case POWERUP_TYPE::HEAVY_RIFLE:
				powerUps[i] = new Powerup_HeavyRifle(info.x, info.y);
				powerUps[i]->texture = this->weaponTexture;
				powerUps[i]->pickUpFx = this->weaponPickUpFx;
				break;
			case POWERUP_TYPE::FLAMETHROWER:
				powerUps[i] = new Powerup_Flamethrower(info.x, info.y);
				powerUps[i]->texture = this->weaponTexture;
				powerUps[i]->pickUpFx = this->weaponPickUpFx;
				break;
			case POWERUP_TYPE::HOSTAGE:
				powerUps[i] = new Powerup_Hostage(info.x, info.y);
				powerUps[i]->texture = this->hostageTexture;
				powerUps[i]->pickUpFx = this->hostagePickUpFx;
				
			}
			break;
		}
	}
}

void ModulePowerup::OnCollision(Collider* c1, Collider* c2) {
	for (uint i = 0; i < MAX_POWERUPS; ++i) {
		if (powerUps[i] != nullptr && powerUps[i]->GetCollider() == c1) {
			App->audio->UnloadFx(powerUps[i]->pickUpFx);

			powerUps[i]->OnCollision(c2);
			delete powerUps[i];
			powerUps[i] = nullptr;
			break;
		}
	}
}