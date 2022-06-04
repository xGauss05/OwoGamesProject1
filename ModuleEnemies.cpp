#include "ModuleEnemies.h"

#include "Application.h"
#include "Globals.h"

#include "ModuleRender.h"
#include "ModuleTextures.h"
#include "ModuleAudio.h"

#include <time.h>

#include "Enemy.h"
#include "Enemy_GreenSoldier.h"
#include "Enemy_RedSoldier.h"
#include "Enemy_Tackler.h"
#include "Enemy_Truck.h"

#include "Collider.h"
#define SPAWN_MARGIN	50

ModuleEnemies::ModuleEnemies(bool startEnabled) : Module(startEnabled) {
	for (uint i = 0; i < MAX_ENEMIES; ++i)
		enemies[i] = nullptr;
}

ModuleEnemies::~ModuleEnemies() {
}

bool ModuleEnemies::Start() {
	greenEnemyTexture = App->textures->Load("Assets/img/sprites/Spritesheet Guerrilla Enemy OK 0.2.png");
	redEnemyTexture = App->textures->Load("Assets/img/sprites/Red Enemy Spritesheet.png");
	truckEnemyTexture = App->textures->Load("Assets/img/sprites/truck.png");
	enemyDestroyedFx = App->audio->LoadFx("Assets/sounds/sfx/194.wav");

	srand(time(NULL));

	return true;
}

update_status ModuleEnemies::Update() {
	HandleEnemiesSpawn();

	for (uint i = 0; i < MAX_ENEMIES; ++i) {
		if (enemies[i] != nullptr)
			enemies[i]->Update();
	}

	HandleEnemiesDespawn();

	return update_status::UPDATE_CONTINUE;
}

update_status ModuleEnemies::PostUpdate() {
	for (uint i = 0; i < MAX_ENEMIES; ++i) {
		if (enemies[i] != nullptr)
			enemies[i]->Draw();
	}

	return update_status::UPDATE_CONTINUE;
}

// Called before quitting
bool ModuleEnemies::CleanUp() {
	LOG("Freeing all enemies");
	App->textures->Unload(greenEnemyTexture);
	App->textures->Unload(redEnemyTexture);
	App->audio->UnloadFx(enemyDestroyedFx);

	for (uint i = 0; i < MAX_ENEMIES; ++i) {
		if (enemies[i] != nullptr) {
			App->textures->Unload(enemies[i]->texture);
			App->audio->UnloadFx(enemies[i]->enemyDeadFx);
			delete enemies[i];
			enemies[i] = nullptr;
		}
	}

	return true;
}

int ModuleEnemies::randVal(int min, int max) {

	return (rand() % (max - min + 1)) + min;
}

bool ModuleEnemies::AddEnemy(ENEMY_TYPE type, int x, int y, ushort behaviour) {
	bool ret = false;

	for (uint i = 0; i < MAX_ENEMIES; ++i) {
		if (spawnQueue[i].type == ENEMY_TYPE::NO_TYPE) {
			spawnQueue[i].type = type;
			spawnQueue[i].x = x;
			spawnQueue[i].y = y;
			spawnQueue[i].behaviour = behaviour;
			ret = true;
			break;
		}
	}

	return ret;
}

void ModuleEnemies::HandleEnemiesSpawn() {
	// Iterate all the enemies queue
	for (uint i = 0; i < MAX_ENEMIES; ++i) {
		if (spawnQueue[i].type != ENEMY_TYPE::NO_TYPE) {
			// Spawn a new enemy if the screen has reached a spawn position
			if (spawnQueue[i].y > App->render->camera.y - SPAWN_MARGIN) {
				LOG("Spawning enemy at %d", spawnQueue[i].y);

				SpawnEnemy(spawnQueue[i]);
				spawnQueue[i].type = ENEMY_TYPE::NO_TYPE; // Removing the newly spawned enemy from the queue
			}
		}
	}
}

void ModuleEnemies::HandleEnemiesDespawn() {
	// Iterate existing enemies
	for (uint i = 0; i < MAX_ENEMIES; ++i) {
		if (enemies[i] != nullptr) {
			// Delete the enemy when it has reached the end of the screen
			if (enemies[i]->position.y > App->render->camera.y + App->render->camera.h + SPAWN_MARGIN) {
				LOG("DeSpawning enemy at %d", enemies[i]->position.y);

				delete enemies[i];
				enemies[i] = nullptr;
			}
		}
	}
}

void ModuleEnemies::SpawnEnemy(const EnemySpawnpoint& info) {
	// Find an empty slot in the enemies array
	for (uint i = 0; i < MAX_ENEMIES; ++i) {
		if (enemies[i] == nullptr) {
			switch (info.type) {
			case ENEMY_TYPE::GREENSOLDIER:
				enemies[i] = new Enemy_GreenSoldier(info.x, info.y, info.behaviour);
				enemies[i]->texture = greenEnemyTexture;
				enemies[i]->enemyDeadFx = this->enemyDestroyedFx;
				break;
			case ENEMY_TYPE::REDSOLDIER:
				enemies[i] = new Enemy_RedSoldier(info.x, info.y, info.behaviour);
				enemies[i]->texture = redEnemyTexture;
				enemies[i]->enemyDeadFx = this->enemyDestroyedFx;
				break;
			case ENEMY_TYPE::TACKLER:
				enemies[i] = new Enemy_Tackler(info.x, info.y);
				enemies[i]->texture = greenEnemyTexture;
				enemies[i]->enemyDeadFx = this->enemyDestroyedFx;
				break;
			case ENEMY_TYPE::TRUCK:
				enemies[i] = new Enemy_Truck(info.x, info.y);
				enemies[i]->texture = truckEnemyTexture;
				//enemies[i]->enemyDeadFx = this->enemyDestroyedFx;
				break;
			}
			break;
		}
	}
}

void ModuleEnemies::OnCollision(Collider* c1, Collider* c2) {
	for (uint i = 0; i < MAX_ENEMIES; ++i) {
		if (enemies[i] != nullptr && enemies[i]->GetCollider() == c1) {
			enemies[i]->OnCollision(c2); // Notify the enemy of a collision
			if (enemies[i]->GetCollider()->type == Collider::Type::TRUCK &&
				c2->type == Collider::Type::EXPLOSION) {

				delete enemies[i];
				enemies[i] = nullptr;
			}
			if (c1->type != Collider::Type::TRUCK) {
				delete enemies[i];
				enemies[i] = nullptr;
			}
			break;
		}
	}
}
