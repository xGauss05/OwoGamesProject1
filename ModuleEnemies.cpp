#include "ModuleEnemies.h"

#include "Application.h"
#include "Globals.h"

#include "ModuleRender.h"
#include "ModuleTextures.h"
#include "ModuleAudio.h"

#include "Enemy.h"
#include "Enemy_GreenSoldier.h"
#include "Enemy_RedSoldier.h"
#include "Enemy_Tackler.h"

#define SPAWN_MARGIN	50

ModuleEnemies::ModuleEnemies(bool startEnabled) : Module(startEnabled)
{
	for (uint i = 0; i < MAX_ENEMIES; ++i)
		enemies[i] = nullptr;
}

ModuleEnemies::~ModuleEnemies() {}

bool ModuleEnemies::Start()
{
	greenEnemyTexture = App->textures->Load("Assets/img/sprites/Spritesheet Guerrilla Enemy OK.png");
	redEnemyTexture = App->textures->Load("Assets/img/sprites/Guerrilla War Enemy Red Spritesheet.png");
	enemyDestroyedFx = App->audio->LoadFx("Assets/sounds/sfx/194.wav");

	return true;
}

update_status ModuleEnemies::Update()
{
	HandleEnemiesSpawn();

	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (enemies[i] != nullptr)
			enemies[i]->Update();
	}

	HandleEnemiesDespawn();

	return update_status::UPDATE_CONTINUE;
}

update_status ModuleEnemies::PostUpdate()
{
	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (enemies[i] != nullptr)
			enemies[i]->Draw();
	}

	return update_status::UPDATE_CONTINUE;
}

// Called before quitting
bool ModuleEnemies::CleanUp()
{
	LOG("Freeing all enemies");
	App->textures->Unload(greenEnemyTexture);
	App->textures->Unload(redEnemyTexture);
	App->audio->UnloadFx(enemyDestroyedFx);

	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (enemies[i] != nullptr)
		{
			App->textures->Unload(enemies[i]->texture);
			App->audio->UnloadFx(enemies[i]->enemyDeadFx);
			delete enemies[i];
			enemies[i] = nullptr;
		}
	}

	return true;
}


/* Behaviour for greensoldiers:
 - 0: Stay squatting (Shoot). WIP
 - 1: Stay squatting (Grenade). WIP
 - 2: Come and tackle (Shoot). WIP
 - 3: Come and tackle (Grenade). WIP
 - 4: Come and shoot to leave (Shoot). WIP
 - 5: Come and shoot to leave (Grenade). WIP
 - 6: Bush surprise (Optional). WIP
*/
bool ModuleEnemies::AddEnemy(ENEMY_TYPE type, int x, int y, ushort behaviour)
{
	bool ret = false;

	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (spawnQueue[i].type == ENEMY_TYPE::NO_TYPE)
		{
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

void ModuleEnemies::HandleEnemiesSpawn()
{
	// Iterate all the enemies queue
	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (spawnQueue[i].type != ENEMY_TYPE::NO_TYPE)
		{
			// Spawn a new enemy if the screen has reached a spawn position
			if (spawnQueue[i].x * SCREEN_SIZE < App->render->camera.x + (App->render->camera.w * SCREEN_SIZE) + SPAWN_MARGIN)
			{
				LOG("Spawning enemy at %d", spawnQueue[i].x * SCREEN_SIZE);

				SpawnEnemy(spawnQueue[i]);
				spawnQueue[i].type = ENEMY_TYPE::NO_TYPE; // Removing the newly spawned enemy from the queue
			}
		}
	}
}

void ModuleEnemies::HandleEnemiesDespawn()
{
	// Iterate existing enemies
	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (enemies[i] != nullptr)
		{
			// Delete the enemy when it has reached the end of the screen
			if (enemies[i]->position.x * SCREEN_SIZE < (App->render->camera.x) - SPAWN_MARGIN)
			{
				LOG("DeSpawning enemy at %d", enemies[i]->position.x * SCREEN_SIZE);

				delete enemies[i];
				enemies[i] = nullptr;
			}
		}
	}
}

void ModuleEnemies::SpawnEnemy(const EnemySpawnpoint& info)
{
	// Find an empty slot in the enemies array
	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (enemies[i] == nullptr)
		{
			switch (info.type)
			{
			case ENEMY_TYPE::GREENSOLDIER:
				enemies[i] = new Enemy_GreenSoldier(info.x, info.y, info.behaviour);
				enemies[i]->texture = greenEnemyTexture;
				enemies[i]->enemyDeadFx = this->enemyDestroyedFx;
				break;
			case ENEMY_TYPE::REDSOLDIER:
				enemies[i] = new Enemy_RedSoldier(info.x, info.y);
				enemies[i]->texture = redEnemyTexture;
				enemies[i]->enemyDeadFx = this->enemyDestroyedFx;
				break;
			case ENEMY_TYPE::TACKLER:
				enemies[i] = new Enemy_Tackler(info.x, info.y);
				enemies[i]->texture = greenEnemyTexture;
				enemies[i]->enemyDeadFx = this->enemyDestroyedFx;
				break;
			}
			break;
		}
	}
}

void ModuleEnemies::OnCollision(Collider* c1, Collider* c2)
{
	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (enemies[i] != nullptr && enemies[i]->GetCollider() == c1)
		{
			enemies[i]->OnCollision(c2); // Notify the enemy of a collision

			delete enemies[i];
			enemies[i] = nullptr;
			break;
		}
	}
}
