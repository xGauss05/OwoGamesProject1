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
#include "ModuleBreakable.h"

#define Y_BG_POSITION -3920

SceneLevel1::SceneLevel1(bool startEnabled) : Module(startEnabled) {
}

SceneLevel1::~SceneLevel1() {
}

// Load assets
bool SceneLevel1::Start() {
	LOG("Loading background assets");

	bool ret = true;

	mapTexture = App->textures->Load("Assets/img/sprites/map_broken_WIP.png");
	parallaxTexture = App->textures->Load("Assets/img/sprites/paralax_map.png");
	App->audio->PlayMusic("Assets/sounds/bgm/106.ogg", 1.0f); // bgm Farm
	
	
	// Entities --- Add enemies/powerups here
	App->enemies->AddEnemy(ENEMY_TYPE::TRUCK, 300, -350);
	//App->powerups->AddPowerup(POWERUP_TYPE::HOSTAGE, 300, -60);
	//App->powerups->AddPowerup(POWERUP_TYPE::FLAMETHROWER, 240, -60);
	//App->powerups->AddPowerup(POWERUP_TYPE::FLAMETHROWER, 230, -60);

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

	App->collisions->AddCollider({ 255, -2365, 150, 25 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 372, -2390, 25, 50 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 350, -2465, 25, 75 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 375, -2520, 37, 55 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 600, -2770, 25, 85 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 570, -2800, 30, 30 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 540, -2830, 30, 30 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 510, -2860, 30, 30 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 480, -2830, 30, 30 }, Collider::Type::WALL);

	App->collisions->AddCollider({ 480, -3370, 85, 25 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 565, -3420, 25, 50 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 540, -3525, 25, 105 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 565, -3560, 35, 35 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 600, -3705, 25, 145 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 570, -3795, 25, 90 }, Collider::Type::WALL);

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

	App->collisions->AddCollider({ 660, -2395, 243, 60 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 733, -2425, 86, 30 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 827, -2457, 20, 32 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 853, -2762, 25, 305 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 875, -2800, 30, 30 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 905, -2830, 30, 30 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 935, -2860, 30, 30 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 965, -2830, 30, 30 }, Collider::Type::WALL);

	App->collisions->AddCollider({ 910, -3370, 85, 25 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 880, -3445, 25, 75 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 910, -3500, 25, 50 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 885, -3630, 25, 120 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 915, -3695, 30, 60 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 940, -3780, 25, 85 }, Collider::Type::WALL);


	// Rock
	App->breakables->AddBreakable(BREAKABLE_TYPE::BARRICADE_H, 128, -432);
	App->breakables->AddBreakable(BREAKABLE_TYPE::BARRICADE_H, 160, -432);
	App->breakables->AddBreakable(BREAKABLE_TYPE::BARRICADE_H, 256, -432);
	App->breakables->AddBreakable(BREAKABLE_TYPE::BARRICADE_H, 288, -432);
	App->breakables->AddBreakable(BREAKABLE_TYPE::BARRICADE_H, 288, -848);
	App->breakables->AddBreakable(BREAKABLE_TYPE::BARRICADE_H, 320, -848);
	App->breakables->AddBreakable(BREAKABLE_TYPE::BARRICADE_H, 128, -930);
	App->breakables->AddBreakable(BREAKABLE_TYPE::BARRICADE_H, 160, -930);
	App->breakables->AddBreakable(BREAKABLE_TYPE::BARRICADE_H, 192, -930);
	App->breakables->AddBreakable(BREAKABLE_TYPE::BARRICADE_H, 416, -1424);
	App->breakables->AddBreakable(BREAKABLE_TYPE::BARRICADE_H, 448, -1424);
	App->breakables->AddBreakable(BREAKABLE_TYPE::BARRICADE_V, 480, -1455);

	App->breakables->AddBreakable(BREAKABLE_TYPE::BARRICADE_H, 256, -1824);
	App->breakables->AddBreakable(BREAKABLE_TYPE::BARRICADE_H, 288, -1824);
	App->breakables->AddBreakable(BREAKABLE_TYPE::BARRICADE_H, 320, -1824);
	App->breakables->AddBreakable(BREAKABLE_TYPE::BARRICADE_H, 352, -1824);
	App->breakables->AddBreakable(BREAKABLE_TYPE::BARRICADE_H, 384, -1824);
	App->breakables->AddBreakable(BREAKABLE_TYPE::BARRICADE_H, 416, -1824);

	App->breakables->AddBreakable(BREAKABLE_TYPE::BARRICADE_H, 542, -1824);
	App->breakables->AddBreakable(BREAKABLE_TYPE::BARRICADE_H, 574, -1824);
	App->breakables->AddBreakable(BREAKABLE_TYPE::BARRICADE_H, 606, -1824);
	App->breakables->AddBreakable(BREAKABLE_TYPE::BARRICADE_H, 638, -1824);
	App->breakables->AddBreakable(BREAKABLE_TYPE::BARRICADE_H, 670, -1824);
	App->breakables->AddBreakable(BREAKABLE_TYPE::BARRICADE_H, 702, -1824);
	App->breakables->AddBreakable(BREAKABLE_TYPE::BARRICADE_H, 734, -1824);

	App->breakables->AddBreakable(BREAKABLE_TYPE::BARRICADE_H, 416, -2432);
	App->breakables->AddBreakable(BREAKABLE_TYPE::BARRICADE_H, 448, -2432);
	App->breakables->AddBreakable(BREAKABLE_TYPE::BARRICADE_H, 480, -2432);
	App->breakables->AddBreakable(BREAKABLE_TYPE::BARRICADE_H, 512, -2432);
	App->breakables->AddBreakable(BREAKABLE_TYPE::BARRICADE_V, 544, -2448);

	App->breakables->AddBreakable(BREAKABLE_TYPE::BARRICADE_H, 512, -2528);
	App->breakables->AddBreakable(BREAKABLE_TYPE::BARRICADE_H, 544, -2528);
	App->breakables->AddBreakable(BREAKABLE_TYPE::BARRICADE_H, 576, -2528);
	App->breakables->AddBreakable(BREAKABLE_TYPE::BARRICADE_H, 608, -2528);
	App->breakables->AddBreakable(BREAKABLE_TYPE::BARRICADE_H, 640, -2528);
	App->breakables->AddBreakable(BREAKABLE_TYPE::BARRICADE_H, 672, -2528);
	App->breakables->AddBreakable(BREAKABLE_TYPE::BARRICADE_V, 704, -2544);
	App->breakables->AddBreakable(BREAKABLE_TYPE::BARRICADE_V, 704, -2576);

	App->breakables->AddBreakable(BREAKABLE_TYPE::BARRICADE_H, 704, -2752);
	App->breakables->AddBreakable(BREAKABLE_TYPE::BARRICADE_H, 736, -2752);
	App->breakables->AddBreakable(BREAKABLE_TYPE::BARRICADE_H, 768, -2752);
	App->breakables->AddBreakable(BREAKABLE_TYPE::BARRICADE_H, 800, -2752);

	App->breakables->AddBreakable(BREAKABLE_TYPE::BARRICADE_H, 640, -2864);
	App->breakables->AddBreakable(BREAKABLE_TYPE::BARRICADE_H, 672, -2864);
	App->breakables->AddBreakable(BREAKABLE_TYPE::BARRICADE_H, 704, -2864);

	App->breakables->AddBreakable(BREAKABLE_TYPE::BARRICADE_H, 800, -2864);
	App->breakables->AddBreakable(BREAKABLE_TYPE::BARRICADE_H, 832, -2864);
	App->breakables->AddBreakable(BREAKABLE_TYPE::BARRICADE_H, 864, -2864);

	App->breakables->AddBreakable(BREAKABLE_TYPE::BARRICADE_H, 608, -3344);
	App->breakables->AddBreakable(BREAKABLE_TYPE::BARRICADE_H, 704, -3344);
	App->breakables->AddBreakable(BREAKABLE_TYPE::BARRICADE_H, 800, -3344);

	App->breakables->AddBreakable(BREAKABLE_TYPE::BARRICADE_V, 608, -3376);
	App->breakables->AddBreakable(BREAKABLE_TYPE::BARRICADE_V, 608, -3408);

	App->breakables->AddBreakable(BREAKABLE_TYPE::BARRICADE_H, 640, -3376);
	App->breakables->AddBreakable(BREAKABLE_TYPE::BARRICADE_H, 672, -3376);
	App->breakables->AddBreakable(BREAKABLE_TYPE::BARRICADE_H, 704, -3376);

	App->breakables->AddBreakable(BREAKABLE_TYPE::BARRICADE_H, 800, -3376);
	App->breakables->AddBreakable(BREAKABLE_TYPE::BARRICADE_H, 832, -3376);

	App->breakables->AddBreakable(BREAKABLE_TYPE::BARRICADE_H, 672, -3424);
	App->breakables->AddBreakable(BREAKABLE_TYPE::BARRICADE_H, 704, -3424);
	App->breakables->AddBreakable(BREAKABLE_TYPE::BARRICADE_H, 736, -3424);
	App->breakables->AddBreakable(BREAKABLE_TYPE::BARRICADE_H, 768, -3424);
	App->breakables->AddBreakable(BREAKABLE_TYPE::BARRICADE_H, 800, -3424);
	App->breakables->AddBreakable(BREAKABLE_TYPE::BARRICADE_H, 832, -3424);


	//triangle
	App->breakables->AddBreakable(BREAKABLE_TYPE::BARBED_1, 448, -1550);
	App->breakables->AddBreakable(BREAKABLE_TYPE::BARBED_1, 480, -1550);

	App->breakables->AddBreakable(BREAKABLE_TYPE::BARBED_2, 320, -1938);
	App->breakables->AddBreakable(BREAKABLE_TYPE::BARBED_2, 352, -1938);
	App->breakables->AddBreakable(BREAKABLE_TYPE::BARBED_2, 384, -1938);
	App->breakables->AddBreakable(BREAKABLE_TYPE::BARBED_2, 416, -1938);
	App->breakables->AddBreakable(BREAKABLE_TYPE::BARBED_2, 546, -1938);
	App->breakables->AddBreakable(BREAKABLE_TYPE::BARBED_2, 578, -1938);
	App->breakables->AddBreakable(BREAKABLE_TYPE::BARBED_2, 610, -1938);

	App->breakables->AddBreakable(BREAKABLE_TYPE::BARBED_2, 352, -2066);
	App->breakables->AddBreakable(BREAKABLE_TYPE::BARBED_2, 578, -2066);

	App->breakables->AddBreakable(BREAKABLE_TYPE::BARBED_2, 416, -2098);
	App->breakables->AddBreakable(BREAKABLE_TYPE::BARBED_2, 448, -2098);
	App->breakables->AddBreakable(BREAKABLE_TYPE::BARBED_2, 480, -2098);
	App->breakables->AddBreakable(BREAKABLE_TYPE::BARBED_2, 448, -2130);

	App->breakables->AddBreakable(BREAKABLE_TYPE::BARBED_2, 320, -2196);
	App->breakables->AddBreakable(BREAKABLE_TYPE::BARBED_2, 320, -2228);
	App->breakables->AddBreakable(BREAKABLE_TYPE::BARBED_2, 352, -2196);
	App->breakables->AddBreakable(BREAKABLE_TYPE::BARBED_2, 352, -2228);

	App->breakables->AddBreakable(BREAKABLE_TYPE::BARBED_1, 578, -2355);
	App->breakables->AddBreakable(BREAKABLE_TYPE::BARBED_1, 610, -2355);

	App->breakables->AddBreakable(BREAKABLE_TYPE::BARBED_1, 578, -2862);
	App->breakables->AddBreakable(BREAKABLE_TYPE::BARBED_1, 610, -2862);
	App->breakables->AddBreakable(BREAKABLE_TYPE::BARBED_1, 610, -2830);
	App->breakables->AddBreakable(BREAKABLE_TYPE::BARBED_1, 642, -2830);
	App->breakables->AddBreakable(BREAKABLE_TYPE::BARBED_1, 674, -2830);
	App->breakables->AddBreakable(BREAKABLE_TYPE::BARBED_1, 706, -2830);

	App->breakables->AddBreakable(BREAKABLE_TYPE::BARBED_1, 802, -2830);
	App->breakables->AddBreakable(BREAKABLE_TYPE::BARBED_1, 834, -2830);


	//Fence

	App->breakables->AddBreakable(BREAKABLE_TYPE::FENCE, 256, -1902, 3);
	App->breakables->AddBreakable(BREAKABLE_TYPE::FENCE, 288, -1902, 2);
	App->breakables->AddBreakable(BREAKABLE_TYPE::FENCE, 320, -1902, 3);
	App->breakables->AddBreakable(BREAKABLE_TYPE::FENCE, 352, -1902, 2);
	App->breakables->AddBreakable(BREAKABLE_TYPE::FENCE, 384, -1902, 3);
	App->breakables->AddBreakable(BREAKABLE_TYPE::FENCE, 416, -1902, 2);
	App->breakables->AddBreakable(BREAKABLE_TYPE::FENCE, 448, -1902, 3);
	App->breakables->AddBreakable(BREAKABLE_TYPE::FENCE, 480, -1902, 2);
	App->breakables->AddBreakable(BREAKABLE_TYPE::FENCE, 512, -1902, 3);
	App->breakables->AddBreakable(BREAKABLE_TYPE::FENCE, 544, -1902, 2);
	App->breakables->AddBreakable(BREAKABLE_TYPE::FENCE, 576, -1902, 3);
	App->breakables->AddBreakable(BREAKABLE_TYPE::FENCE, 608, -1902, 2);
	App->breakables->AddBreakable(BREAKABLE_TYPE::FENCE, 640, -1902, 3);
	App->breakables->AddBreakable(BREAKABLE_TYPE::FENCE, 672, -1902, 2);
	App->breakables->AddBreakable(BREAKABLE_TYPE::FENCE, 704, -1902, 3);
	App->breakables->AddBreakable(BREAKABLE_TYPE::FENCE, 736, -1902, 2);

	App->breakables->AddBreakable(BREAKABLE_TYPE::FENCE, 256, -2286, 3);
	App->breakables->AddBreakable(BREAKABLE_TYPE::FENCE, 288, -2286, 2);
	App->breakables->AddBreakable(BREAKABLE_TYPE::FENCE, 320, -2286, 3);
	App->breakables->AddBreakable(BREAKABLE_TYPE::FENCE, 352, -2286, 2);
	App->breakables->AddBreakable(BREAKABLE_TYPE::FENCE, 384, -2286, 3);
	App->breakables->AddBreakable(BREAKABLE_TYPE::FENCE, 416, -2286, 4);

	App->breakables->AddBreakable(BREAKABLE_TYPE::FENCE, 512, -2286, 1);
	App->breakables->AddBreakable(BREAKABLE_TYPE::FENCE, 544, -2286, 2);
	App->breakables->AddBreakable(BREAKABLE_TYPE::FENCE, 576, -2286, 3);
	App->breakables->AddBreakable(BREAKABLE_TYPE::FENCE, 608, -2286, 2);
	App->breakables->AddBreakable(BREAKABLE_TYPE::FENCE, 640, -2286, 3);
	App->breakables->AddBreakable(BREAKABLE_TYPE::FENCE, 672, -2286, 2);
	App->breakables->AddBreakable(BREAKABLE_TYPE::FENCE, 704, -2286, 3);
	App->breakables->AddBreakable(BREAKABLE_TYPE::FENCE, 736, -2286, 2);

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
	App->collisions->AddCollider({ 255, -2320, 95, 30 }, Collider::Type::NON_DEST_BAR);
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
	App->collisions->AddCollider({ 0, 240, 500, 10 }, Collider::Type::WALL);

	App->collisions->AddCollider({ 226, -1865, 30, 325 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 768, -1865, 30, 325 }, Collider::Type::WALL);

	App->collisions->AddCollider({ 420, -3320, 60, 520 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 992, -3320, 60, 520 }, Collider::Type::WALL);

	App->collisions->AddCollider({ 690, -3930, 175, 10}, Collider::Type::WALL);

	// Water
		//First

	App->collisions->AddCollider({ 80, 210, 325, 30 }, Collider::Type::WATER);
	App->collisions->AddCollider({ 110, 180, 260, 30 }, Collider::Type::WATER);
	App->collisions->AddCollider({ 140, 140, 225, 40 }, Collider::Type::WATER);
	App->collisions->AddCollider({ 165, 110, 185, 30 }, Collider::Type::WATER);
	App->collisions->AddCollider({ 195, 75, 140, 35 }, Collider::Type::WATER);
	App->collisions->AddCollider({ 215, 45, 105, 30 }, Collider::Type::WATER);
	//Second
	App->collisions->AddCollider({ 255, -1610, 130, 5 }, Collider::Type::WATER);
	App->collisions->AddCollider({ 615, -1610, 140,  5}, Collider::Type::WATER);
	//Third
	App->collisions->AddCollider({ 480, -3260, 256, 370 }, Collider::Type::WATER);
	App->collisions->AddCollider({ 795, -3260, 256, 370 }, Collider::Type::WATER);

	//Trenches
	App->collisions->AddCollider({ 140, -925, 160, 5 }, Collider::Type::TRENCH);
	App->collisions->AddCollider({ 255, -1820, 180, 5 }, Collider::Type::TRENCH);
	App->collisions->AddCollider({ 560, -1820, 180, 5 }, Collider::Type::TRENCH);
	App->collisions->AddCollider({ 430, -2430, 100, 5 }, Collider::Type::TRENCH);
	App->collisions->AddCollider({ 430, -2430, 100, 5 }, Collider::Type::TRENCH);
	App->collisions->AddCollider({ 525, -2525, 160, 5 }, Collider::Type::TRENCH);
	App->collisions->AddCollider({ 720, -2745, 100, 5 }, Collider::Type::TRENCH);
	App->collisions->AddCollider({ 690, -3420, 135, 5 }, Collider::Type::TRENCH);

	//bridge

	App->breakables->AddBreakable(BREAKABLE_TYPE::BRIDGE, 736, -3280);
	App->breakables->AddBreakable(BREAKABLE_TYPE::BRIDGE, 736, -3248);
	App->breakables->AddBreakable(BREAKABLE_TYPE::BRIDGE, 736, -3216);
	App->breakables->AddBreakable(BREAKABLE_TYPE::BRIDGE, 736, -3184);
	App->breakables->AddBreakable(BREAKABLE_TYPE::BRIDGE, 736, -3152);
	App->breakables->AddBreakable(BREAKABLE_TYPE::BRIDGE, 736, -3120);
	App->breakables->AddBreakable(BREAKABLE_TYPE::BRIDGE, 736, -3088);
	App->breakables->AddBreakable(BREAKABLE_TYPE::BRIDGE, 736, -3056);
	App->breakables->AddBreakable(BREAKABLE_TYPE::BRIDGE, 736, -3024);
	App->breakables->AddBreakable(BREAKABLE_TYPE::BRIDGE, 736, -2992);
	App->breakables->AddBreakable(BREAKABLE_TYPE::BRIDGE, 736, -2960);
	App->breakables->AddBreakable(BREAKABLE_TYPE::BRIDGE, 736, -2928);

	App->player->Enable();
	App->enemies->Enable();
	App->powerups->Enable();
	App->breakables->Enable();
	App->collisions->Enable();

	App->render->camera.x = App->player->position.x - SCREEN_WIDTH / SCREEN_SIZE + 32 / SCREEN_SIZE;
	App->render->camera.y = App->player->position.y - SCREEN_HEIGHT / 3 * SCREEN_SIZE;

	return ret;
}

update_status SceneLevel1::Update() {
	if (App->player->lives == 0 && !isLevelMusic) {
		isLevelMusic = true;
		isContinueMusic = false;
		App->audio->PlayMusic("Assets/sounds/bgm/124.ogg", 1.0f);
	}

	if (App->player->lives >= 1 && !isContinueMusic) {
		isContinueMusic = true;
		isLevelMusic = false;
		App->audio->PlayMusic("Assets/sounds/bgm/106.ogg", 1.0f); // bgm Farm
	}

	return update_status::UPDATE_CONTINUE;
}

// Update: draw background
update_status SceneLevel1::PostUpdate() {
	// Draw everything --------------------------------------
	App->render->Blit(mapTexture, 0, Y_BG_POSITION, NULL);

	return update_status::UPDATE_CONTINUE;
}

bool SceneLevel1::CleanUp() {
	// Disables the player, enemies and powerups.	

	App->breakables->Disable();
	App->powerups->Disable();
	App->enemies->Disable();
	App->player->Disable();
	App->collisions->Disable();

	App->textures->Unload(mapTexture);
	mapTexture = nullptr;
	App->textures->Unload(parallaxTexture);
	parallaxTexture = nullptr;
	// Handle memory leaks

	return true;
}

void SceneLevel1::DrawParallax() {
	App->render->Blit(parallaxTexture, 0, Y_BG_POSITION, NULL);
}
