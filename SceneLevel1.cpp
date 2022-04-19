#include "SceneLevel1.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleCollisions.h"
#include "ModuleEnemies.h"
#include "ModulePowerup.h"

SceneLevel1::SceneLevel1(bool startEnabled) : Module(startEnabled) {}
SceneLevel1::~SceneLevel1() {}

#define Y_BG_POSITION -3920
// Load assets
bool SceneLevel1::Start() {
	LOG("Loading background assets");

	bool ret = true;

	bgTexture = App->textures->Load("img/sprites/map.png"); // needs to be changed
	App->audio->PlayMusic("sounds/bgm/106.ogg", 1.0f); // bgm Farm

	// Colliders --- Make collision boxes here

	App->powerups->AddPowerup(POWERUP_TYPE::HEAVY_RIFLE, 300, -60);
	App->powerups->AddPowerup(POWERUP_TYPE::FLAMETHROWER, 230, -60);
	App->enemies->AddEnemy(ENEMY_TYPE::GREENSOLDIER, 260, -60);
	App->enemies->AddEnemy(ENEMY_TYPE::GREENSOLDIER, 180, -500);
	App->enemies->AddEnemy(ENEMY_TYPE::GREENSOLDIER, 280, -500);
	App->enemies->AddEnemy(ENEMY_TYPE::REDSOLDIER, 230, -600);

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

	// Right colliders
	App->collisions->AddCollider({ 450, 205, 60, 35 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 425, 135, 85, 70 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 405, 105, 105, 30 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 360, 45, 150, 60 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 335, 5, 175, 40 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 300, -290, 210, 295 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 325, -475, 185, 185 }, Collider::Type::WALL);

	//Rock
	App->collisions->AddCollider({ 128, -425, 65, 20 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 255, -425, 65, 20 }, Collider::Type::WALL);

	//Down
	


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
