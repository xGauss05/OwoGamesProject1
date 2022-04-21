#include "SceneLevel1.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleCollisions.h"
#include "ModuleEnemies.h"
#include "ModulePowerup.h"
#include "ModulePlayer.h"

#define Y_BG_POSITION -3920

SceneLevel1::SceneLevel1(bool startEnabled) : Module(startEnabled) {}

SceneLevel1::~SceneLevel1() {}

// Load assets
bool SceneLevel1::Start() {
	LOG("Loading background assets");

	bool ret = true;

	bgTexture = App->textures->Load("img/sprites/map.png");
	App->audio->PlayMusic("sounds/bgm/106.ogg", 1.0f); // bgm Farm


	// Entities --- Add enemies/powerups here

	App->powerups->AddPowerup(POWERUP_TYPE::HEAVY_RIFLE, 300, -60);
	App->powerups->AddPowerup(POWERUP_TYPE::FLAMETHROWER, 230, -60);
	App->enemies->AddEnemy(ENEMY_TYPE::GREENSOLDIER, 260, -60);
	App->enemies->AddEnemy(ENEMY_TYPE::GREENSOLDIER, 180, -500);
	App->enemies->AddEnemy(ENEMY_TYPE::GREENSOLDIER, 280, -500);
	App->enemies->AddEnemy(ENEMY_TYPE::REDSOLDIER, 230, -600);

	// Colliders --- Make collision boxes here
	// Left colliders
	App->collisions->AddCollider({0, 140, 60, 100}, Collider::Type::WALL);
	App->collisions->AddCollider({ 0, 110, 90, 30 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 0, 75, 120, 35 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 0, -20, 150, 95 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 0, -50, 185, 30 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 0, -210, 210, 160 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 0, -270, 185, 60 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 0, -300, 150, 30 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 0, -475, 120, 175 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 0, -535, 145, 60 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 0, -565, 190, 30 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 0, -725, 210, 160 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 0, -755, 190, 30 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 0, -790, 170, 35 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 0, -820, 150, 30 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 0, -970, 110, 150 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 0, -1010, 160, 40 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 0, -1045, 410, 35 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 0, -1075, 445, 30 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 0, -1235, 470, 160 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 0, -1325, 435, 90 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 0, -1355, 415, 30 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 0, -1425, 405, 70 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 0, -1565, 440, 140 }, Collider::Type::WALL);


	// Right colliders
	App->collisions->AddCollider({ 450, 205, 60, 35 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 425, 135, 85, 70 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 405, 105, 105, 30 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 360, 45, 150, 60 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 335, 5, 175, 40 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 300, -290, 210, 295 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 325, -475, 185, 185 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 295, -810, 215, 335 }, Collider::Type::WALL);
		//85 right
	App->collisions->AddCollider({ 400, -840, 235, 30 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 445, -875, 190, 35 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 535, -1025, 100, 150 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 555, -1315, 80, 290 }, Collider::Type::WALL);
		//130 right
	App->collisions->AddCollider({ 585, -1375, 180, 60 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 560, -1575, 205, 200 }, Collider::Type::WALL);


	// Rock
	App->collisions->AddCollider({ 128, -425, 65, 20 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 255, -425, 65, 20 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 285, -840, 65, 20 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 128, -920, 95, 20 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 415, -1415, 65, 20 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 485, -1450, 20, 30 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 448, -1550, 65, 32 }, Collider::Type::WALL);

	// Down
	

	App->player->Enable();
	App->enemies->Enable();
	App->powerups->Enable();

	return ret;
}

update_status SceneLevel1::Update() {
	return update_status::UPDATE_CONTINUE;
}

// Update: draw background
update_status SceneLevel1::PostUpdate() {
	// Draw everything --------------------------------------
	App->render->Blit(bgTexture, 0, Y_BG_POSITION, NULL);

	return update_status::UPDATE_CONTINUE;
}

bool SceneLevel1::CleanUp() {
	// Disables the player, enemies and powerups.	
	App->player->Disable();
	App->enemies->Disable();
	App->powerups->Disable();

	// Handle memory leaks

	return true;
}