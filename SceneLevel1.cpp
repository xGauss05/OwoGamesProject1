#include "SceneLevel1.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleCollisions.h"
#include "ModuleEnemies.h"
#include "ModulePowerup.h"
#include "ModulePlayer.h"
#include "ModuleParticles.h"

#define Y_BG_POSITION -3920

SceneLevel1::SceneLevel1(bool startEnabled) : Module(startEnabled) {
}

SceneLevel1::~SceneLevel1() {
}

// Load assets
bool SceneLevel1::Start() {
	LOG("Loading background assets");

	bool ret = true;

	bgTexture = App->textures->Load("Assets/img/sprites/map.png");
	paralaxTexture = App->textures->Load("Assets/img/sprites/paralax_map.png");
	App->audio->PlayMusic("Assets/sounds/bgm/106.ogg", 1.0f); // bgm Farm

	// Entities --- Add enemies/powerups here
	App->powerups->AddPowerup(POWERUP_TYPE::HOSTAGE, 300, -60);
	//App->powerups->AddPowerup(POWERUP_TYPE::HEAVY_RIFLE, 300, -60);
	//App->powerups->AddPowerup(POWERUP_TYPE::FLAMETHROWER, 230, -60);
	//App->enemies->AddEnemy(ENEMY_TYPE::GREENSOLDIER, 260, -60);
	//App->enemies->AddEnemy(ENEMY_TYPE::GREENSOLDIER, 180, -500);
	//App->enemies->AddEnemy(ENEMY_TYPE::GREENSOLDIER, 280, -500);
	//App->enemies->AddEnemy(ENEMY_TYPE::REDSOLDIER, 230, -600);
	//App->enemies->AddEnemy(ENEMY_TYPE::GREENSOLDIER, 210, 300, 0);
	//App->enemies->AddEnemy(ENEMY_TYPE::GREENSOLDIER, 260, 300, 1);
	//App->enemies->AddEnemy(ENEMY_TYPE::REDSOLDIER, 310, 300);

	// Colliders --- Make collision boxes here
	// Left colliders
	App->collisions->AddCollider({ 30, 140, 30, 100 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 60, 110, 30, 30 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 90, 75, 30, 35 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 120, -20, 30, 95 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 150, -50, 35, 30 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 180, -210, 30, 160 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 155, -270, 30, 60 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 120, -300, 30, 30 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 90, -475, 30, 175 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 115, -535, 30, 60 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 120, -565, 60, 30 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 180, -725, 40, 160 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 170, -755, 20, 30 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 150, -790, 20, 35 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 110, -820, 40, 30 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 90, -975, 20, 155 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 110, -1015, 50, 40 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 160, -1045, 250, 35 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 410, -1075, 35, 30 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 440, -1235, 30, 160 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 400, -1325, 35, 90 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 390, -1355, 25, 30 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 380, -1425, 25, 70 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 415, -1565, 25, 140 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 255, -1565, 160, 25 }, Collider::Type::WALL);



	// Right colliders
	App->collisions->AddCollider({ 450, 205, 30, 35 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 425, 135, 25, 70 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 405, 105, 20, 30 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 360, 45, 45, 60 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 335, 5, 25, 40 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 300, -290, 35, 295 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 325, -475, 30, 185 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 295, -805, 30, 330 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 300, -805, 100, 30 }, Collider::Type::WALL);
	//85 right
	App->collisions->AddCollider({ 400, -840, 45, 30 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 445, -875, 110, 35 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 535, -1025, 20, 150 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 555, -1315, 30, 290 }, Collider::Type::WALL);
	//130 right
	App->collisions->AddCollider({ 585, -1375, 30, 60 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 560, -1575, 25, 200 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 570, -1575, 190, 20 }, Collider::Type::WALL);


	// Rock
	App->collisions->AddCollider({ 128, -425, 65, 20 }, Collider::Type::BARRICADE);
	App->collisions->AddCollider({ 255, -425, 65, 20 }, Collider::Type::BARRICADE);
	App->collisions->AddCollider({ 285, -840, 65, 20 }, Collider::Type::BARRICADE);
	App->collisions->AddCollider({ 128, -920, 95, 20 }, Collider::Type::BARRICADE);
	App->collisions->AddCollider({ 415, -1415, 65, 20 }, Collider::Type::BARRICADE);
	App->collisions->AddCollider({ 485, -1450, 20, 30 }, Collider::Type::BARRICADE);
	App->collisions->AddCollider({ 448, -1550, 65, 32 }, Collider::Type::BARRICADE);

	// Non destroyable barricade
	App->collisions->AddCollider({ 575, -1680, 65, 30 }, Collider::Type::NON_DEST_BAR);
	App->collisions->AddCollider({ 350, -1680, 65, 30 }, Collider::Type::NON_DEST_BAR);
	App->collisions->AddCollider({ 255, -1775, 160, 30 }, Collider::Type::NON_DEST_BAR);
	App->collisions->AddCollider({ 575, -1775, 195, 30 }, Collider::Type::NON_DEST_BAR);
	App->collisions->AddCollider({ 705, -1940, 60, 30 }, Collider::Type::NON_DEST_BAR);
	App->collisions->AddCollider({ 255, -1970, 60, 60 }, Collider::Type::NON_DEST_BAR);
	App->collisions->AddCollider({ 640, -1970, 60, 60 }, Collider::Type::NON_DEST_BAR);
	App->collisions->AddCollider({ 255, -2165, 30, 195 }, Collider::Type::NON_DEST_BAR);
	App->collisions->AddCollider({ 255, -2225, 60, 60 }, Collider::Type::NON_DEST_BAR);
	App->collisions->AddCollider({ 670, -2225, 30, 255 }, Collider::Type::NON_DEST_BAR);
	App->collisions->AddCollider({ 255, -2320, 95, 30  }, Collider::Type::NON_DEST_BAR);
	App->collisions->AddCollider({ 670, -2320, 195, 30 }, Collider::Type::NON_DEST_BAR);
	App->collisions->AddCollider({ 515, -2645, 130, 60 }, Collider::Type::NON_DEST_BAR);
	App->collisions->AddCollider({ 610, -2675, 30, 30 }, Collider::Type::NON_DEST_BAR);
	App->collisions->AddCollider({ 575, -3505, 30, 65 }, Collider::Type::NON_DEST_BAR);
	App->collisions->AddCollider({ 865, -3505, 30, 30 }, Collider::Type::NON_DEST_BAR);
	App->collisions->AddCollider({ 610, -3760, 95, 30 }, Collider::Type::NON_DEST_BAR);
	App->collisions->AddCollider({ 830, -3760, 95, 30 }, Collider::Type::NON_DEST_BAR);
	App->collisions->AddCollider({ 705, -3790, 30, 30 }, Collider::Type::NON_DEST_BAR);
	App->collisions->AddCollider({ 800, -3790, 30, 30 }, Collider::Type::NON_DEST_BAR);

	//Houses
	App->collisions->AddCollider({ 415, -2645, 95, 145 }, Collider::Type::NON_DEST_BAR);
	App->collisions->AddCollider({ 610, -3920, 95, 155 }, Collider::Type::NON_DEST_BAR);
	App->collisions->AddCollider({ 830, -3920, 95, 155 }, Collider::Type::NON_DEST_BAR);

	//Borders
	//App->collisions->AddCollider({ 0, 240, 500, 10 }, Collider::Type::WALL);

	App->collisions->AddCollider({ 226, -1865, 30, 325 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 768, -1865, 30, 325 }, Collider::Type::WALL);

	App->collisions->AddCollider({ 420, -3320, 60, 520 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 992, -3320, 60, 520 }, Collider::Type::WALL);

	// Water
		//First
	App->collisions->AddCollider({ 80, 210, 325, 30 }, Collider::Type::WATER);
	App->collisions->AddCollider({ 110, 180, 260, 30 }, Collider::Type::WATER);
	App->collisions->AddCollider({ 140, 140, 225, 40 }, Collider::Type::WATER);
	App->collisions->AddCollider({ 165, 110, 185, 30 }, Collider::Type::WATER);
	App->collisions->AddCollider({ 195, 75, 140, 35 }, Collider::Type::WATER);
	App->collisions->AddCollider({ 215, 35, 105, 40 }, Collider::Type::WATER);
	//Second
	App->collisions->AddCollider({ 255, -1625, 140, 20 }, Collider::Type::WATER);
	App->collisions->AddCollider({ 605, -1625, 140, 20 }, Collider::Type::WATER);
	//Third
	App->collisions->AddCollider({ 480, -3286, 260, 405 }, Collider::Type::WATER);
	App->collisions->AddCollider({ 795, -3286, 260, 405 }, Collider::Type::WATER);

	//Trenches
	App->collisions->AddCollider({ 140, -945, 160, 30 }, Collider::Type::TRENCH);
	App->collisions->AddCollider({ 255, -1840, 180, 25 }, Collider::Type::TRENCH);
	App->collisions->AddCollider({ 560, -1840, 180, 25 }, Collider::Type::TRENCH);
	App->collisions->AddCollider({ 430, -2450, 100, 25 }, Collider::Type::TRENCH);
	App->collisions->AddCollider({ 430, -2450, 100, 25 }, Collider::Type::TRENCH);
	App->collisions->AddCollider({ 525, -2545, 160, 25 }, Collider::Type::TRENCH);
	App->collisions->AddCollider({ 720, -2765, 100, 25 }, Collider::Type::TRENCH);
	App->collisions->AddCollider({ 690, -3440, 135, 25 }, Collider::Type::TRENCH);

	App->player->Enable();
	App->enemies->Enable();
	App->powerups->Enable();
	App->collisions->Enable();

	App->render->camera.x = App->player->position.x - SCREEN_WIDTH / 2 + 16;
	App->render->camera.y = App->player->position.y - SCREEN_HEIGHT / 1.5f;

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
	App->collisions->Disable();
	App->powerups->Disable();
   	App->enemies->Disable();
	App->player->Disable();
	App->textures->Unload(bgTexture);
	bgTexture = nullptr;
	// Handle memory leaks

	return true;
}

void SceneLevel1::DrawParalax() {
	App->render->Blit(paralaxTexture, 0, Y_BG_POSITION, NULL);
}
