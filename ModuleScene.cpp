#include "ModuleScene.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleCollisions.h"
#include "ModuleEnemies.h"
#include "ModulePowerup.h"

ModuleScene::ModuleScene() {}
ModuleScene::~ModuleScene() {}

#define Y_BG_POSITION -3920
// Load assets
bool ModuleScene::Start() {
	LOG("Loading background assets");

	bool ret = true;

	bgTexture = App->textures->Load("img/sprites/map.png"); // needs to be changed
	App->audio->PlayMusic("sounds/bgm/106.ogg", 1.0f); // bgm Farm

	// Colliders ---
	// Bottom collider
	// Make collision boxes here

	App->powerups->AddPowerup(POWERUP_TYPE::HEAVY_RIFLE, 300, -60);
	App->enemies->AddEnemy(ENEMY_TYPE::GREENSOLDIER, 260, -60);
	App->enemies->AddEnemy(ENEMY_TYPE::GREENSOLDIER, 180, -500);
	App->enemies->AddEnemy(ENEMY_TYPE::GREENSOLDIER, 280, -500);
	App->enemies->AddEnemy(ENEMY_TYPE::REDSOLDIER, 230, -600);

	return ret;
}

update_status ModuleScene::Update() {
	return update_status::UPDATE_CONTINUE;
}

// Update: draw background
update_status ModuleScene::PostUpdate() {
	// Draw everything --------------------------------------
	App->render->Blit(bgTexture, 0, Y_BG_POSITION, NULL);

	return update_status::UPDATE_CONTINUE;
}
