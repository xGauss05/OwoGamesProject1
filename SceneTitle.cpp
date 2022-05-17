#include "SceneTitle.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleCollisions.h"
#include "ModulePlayer.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"
#include "SceneIntro.h"
#include "SDL/include/SDL_scancode.h"

SceneTitle::SceneTitle(bool startEnabled) : Module(startEnabled) {
}

SceneTitle::~SceneTitle() {}

// Load assets
bool SceneTitle::Start() {
	bool ret = true;

	// Placeholder
	bgTexture = App->textures->Load("Assets/img/sprites/title.png");
	
	App->audio->PlayMusic("Assets/sounds/bgm/112.ogg", 1.0f);
	duration = 0;
	introAssets = App->textures->Load("Assets/img/sprites/intro_assets.png");

	bombsAnim.PushBack({ 0 , 160, 16, 16 });
	bombsAnim.PushBack({ 16, 160, 16, 16 });
	bombsAnim.PushBack({ 32, 160, 16, 16 });
	bombsAnim.PushBack({ 48, 160, 16, 16 });
	bombsAnim.PushBack({ 64, 160, 16, 16 });
	bombsAnim.PushBack({ 80, 160, 16, 16 });
	bombsAnim.PushBack({ 96, 160, 16, 16 });
	bombsAnim.PushBack({ 0  , 176, 32, 64 });
	bombsAnim.PushBack({ 32 , 176, 32, 64 });
	bombsAnim.PushBack({ 64 , 176, 32, 64 });
	bombsAnim.PushBack({ 96 , 176, 32, 64 });
	bombsAnim.PushBack({ 128, 176, 32, 64 });
	bombsAnim.PushBack({ 160, 176, 32, 64 });
	bombsAnim.PushBack({ 192, 176, 32, 64 });
	bombsAnim.speed = 0.15f;
	bombsAnim.loop = false;

	planesAnim.PushBack({ 224, 112, 128, 128 });
	planesAnim.loop = false;

	playerMiniAnim.PushBack({ 0  , 0, 32, 32 });
	playerMiniAnim.PushBack({ 32 , 0, 32, 32 });
	playerMiniAnim.PushBack({ 64 , 0, 32, 32 });
	playerMiniAnim.PushBack({ 96 , 0, 32, 32 });
	playerMiniAnim.PushBack({ 128, 0, 32, 32 });
	playerMiniAnim.PushBack({ 160, 0, 32, 32 });
	playerMiniAnim.PushBack({ 192, 0, 32, 32 });
	playerMiniAnim.PushBack({ 224, 0, 32, 32 });
	playerMiniAnim.PushBack({ 256, 0, 32, 32 });
	playerMiniAnim.PushBack({ 288, 0, 32, 32 });
	playerMiniAnim.PushBack({ 320, 0, 32, 32 });
	playerMiniAnim.PushBack({ 352, 0, 32, 32 });
	playerMiniAnim.loop = false;
	playerMiniAnim.speed = 0.1f;

	boatAnim.PushBack({ 0 , 64, 32, 96 });
	boatAnim.PushBack({ 32, 64, 32, 96 });
	boatAnim.PushBack({ 64, 64, 32, 96 });
	boatAnim.PushBack({ 96, 64, 32, 96 });
	boatAnim.speed = 0.1f;

	App->render->camera.x = 0;
	App->render->camera.y = 0;

	assetsPoint[0] = &boat;
	assetsPoint[1] = &playerMini;
	assetsPoint[2] = &bombs[0];
	assetsPoint[3] = &bombs[1];
	assetsPoint[4] = &bombs[2];
	assetsPoint[5] = &bombs[3];
	assetsPoint[6] = &bombs[4];
	assetsPoint[7] = &bombs[5];
	assetsPoint[8] = &bombs[6];
	assetsPoint[9] = &bombs[7];
	assetsPoint[10] = &planes[0];
	assetsPoint[11] = &planes[1];
	assetsPoint[12] = &planes[2];


	assetsAnim[0] = boatAnim;
	assetsAnim[1] = playerMiniAnim;
	assetsAnim[2] = bombsAnim; 
	assetsAnim[3] = bombsAnim;
	assetsAnim[4] = bombsAnim;
	assetsAnim[5] = bombsAnim;
	assetsAnim[6] = bombsAnim;
	assetsAnim[7] = bombsAnim;
	assetsAnim[8] = bombsAnim;
	assetsAnim[9] = bombsAnim;
	assetsAnim[10] = planesAnim;
	assetsAnim[11] = planesAnim;
	assetsAnim[12] = planesAnim;

	boat.x = (SCREEN_WIDTH / 2) - 16;
	boat.y = (SCREEN_HEIGHT / 2) + 32;

	planes[0].x = (SCREEN_WIDTH / 2) - 64;
	planes[0].y = SCREEN_HEIGHT + 96;
	planes[1].x = 0 - 32;
	planes[1].y = SCREEN_HEIGHT + 128 + 96;
	planes[2].x = SCREEN_WIDTH - 96;
	planes[2].y = SCREEN_HEIGHT + 128 + 96;

	playerMini.x = SCREEN_WIDTH;
	bombs[0].x = SCREEN_WIDTH;
	bombs[1].x = -16;
	bombs[2].x = SCREEN_WIDTH;
	bombs[3].x = -16;
	bombs[4].x = SCREEN_WIDTH;
	bombs[5].x = -16;
	bombs[6].x = SCREEN_WIDTH;
	bombs[7].x = -16;


	return ret;
}

update_status SceneTitle::Update() {

	if (App->input->keys[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_DOWN || duration >= SCENE_DURATION) {
		App->fade->FadeToBlack(this, (Module*)App->level1, 0);
	}

	if(App->input->keys[SDL_SCANCODE_ESCAPE] == KEY_STATE::KEY_REPEAT) {
		return update_status::UPDATE_STOP;
	}

	if (duration < 400) {
		App->render->camera.y -= 1;
	}
	if (duration < 405) {
		boat.y -= 1;
	}
	
	if (duration == 180) {
		bombs[0].x = 104;
		bombs[0].y = -4;
		assetsAnim[2].Reset();
	}
	if (duration == 188) {
		bombs[1].x = 104;
		bombs[1].y = -12;
		assetsAnim[3].Reset();
	}
	if (duration == 196) {
		bombs[2].x = 104;
		bombs[2].y = -20;
		assetsAnim[4].Reset();
	}
	if (duration == 204) {
		bombs[3].x = 104;
		bombs[3].y = -28;
		assetsAnim[5].Reset();
	}
	if (duration == 212) {
		bombs[4].x = 104;
		bombs[4].y = -36;
		assetsAnim[6].Reset();
	}
	if (duration == 220) {
		bombs[5].x = 104;
		bombs[5].y = -44;
		assetsAnim[7].Reset();
	}
	if (duration == 228) {
		bombs[6].x = 104;
		bombs[6].y = -52;
		assetsAnim[8].Reset();
	}
	if (duration == 236) {
		bombs[7].x = 104;
		bombs[7].y = -60;
		assetsAnim[9].Reset();
	}

	for (int i = 0; i < 8; ++i) {
		if (i % 2 == 0) {
			if (assetsAnim[i + 2].GetCurrentFrameNum() < 6) {
				bombs[i].x += 1;
			}
		}
		else {
			if (assetsAnim[i + 2].GetCurrentFrameNum() < 6) {
				bombs[i].x -= 1;
			}
		}
	}

	planes[0].y -= 3;
	planes[1].y -= 3;
	planes[2].y -= 3;

	for (int i = 0; i < MAX_ASSETS_TITLE; ++i) {
		assetsAnim[i].Update();
	}




	++duration;

	return update_status::UPDATE_CONTINUE;
}

// Update: draw background
update_status SceneTitle::PostUpdate() {
	//App->render->Blit(bgTexture, 0, 0, NULL);

	for (int i = 0; i < MAX_ASSETS_TITLE; ++i) {
		SDL_Rect rect = assetsAnim[i].GetCurrentFrame();
		App->render->Blit(introAssets, assetsPoint[i]->x, assetsPoint[i]->y, &rect);
	}
	
	return update_status::UPDATE_CONTINUE;
}

bool SceneTitle::CleanUp() {
	App->textures->Unload(bgTexture);
	App->textures->Unload(introAssets);
	bgTexture = nullptr;
	introAssets = nullptr;
	return true;
}