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

	bgTexture = App->textures->Load("Assets/img/sprites/title_map_large.png");
	introAssets = App->textures->Load("Assets/img/sprites/intro_assets.png");
	
	App->audio->PlayMusic("Assets/sounds/bgm/112.ogg", 1.0f);
	bombFx = App->audio->LoadFx("Assets/sounds/sfx/137.wav");

	duration = 0;
	
	bombsAnim.FullReset();
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
	
	planesAnim.FullReset();
	planesAnim.PushBack({ 224, 112, 128, 128 });
	planesAnim.loop = false;

	playerMiniAnim.FullReset();
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
	playerMiniAnim.speed = 0.21f;

	boatAnim.FullReset();
	boatAnim.PushBack({ 0 , 64, 32, 96 });
	boatAnim.PushBack({ 32, 64, 32, 96 });
	boatAnim.PushBack({ 64, 64, 32, 96 });
	boatAnim.PushBack({ 96, 64, 32, 96 });
	boatAnim.loop = true;
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

	boat.x = (SCREEN_WIDTH / 2) - 8;
	boat.y = (SCREEN_HEIGHT / 2) + 64;

	planes[0].x = (SCREEN_WIDTH / 2) - 64;
	planes[0].y = SCREEN_HEIGHT + 96;
	planes[1].x = 0 - 32;
	planes[1].y = SCREEN_HEIGHT + 128 + 96;
	planes[2].x = SCREEN_WIDTH - 96;
	planes[2].y = SCREEN_HEIGHT + 128 + 96;

	playerMini.x = -32;
	bombs[0].x = SCREEN_WIDTH;
	bombs[1].x = -32;
	bombs[2].x = SCREEN_WIDTH;
	bombs[3].x = -32;
	bombs[4].x = SCREEN_WIDTH;
	bombs[5].x = -32;
	bombs[6].x = SCREEN_WIDTH;
	bombs[7].x = -32;


	return ret;
}

update_status SceneTitle::Update() {

	bool toSkip = false;
	if (App->input->controllerCount > 0) {
		for (int i = 0; i < App->input->controllerCount; ++i) {
			if (App->input->controllers[i]->buttons[SDL_CONTROLLER_BUTTON_A] == KEY_DOWN) {
				toSkip = true;
			}
		}
	}

	if (App->input->keys[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_DOWN || duration >= SCENE_DURATION || toSkip) {
		App->fade->FadeToBlack(this, (Module*)App->level1, 0);
	}

	if(App->input->keys[SDL_SCANCODE_ESCAPE] == KEY_STATE::KEY_REPEAT) {
		return update_status::UPDATE_STOP;
	}

	if (duration < 360) {
		App->render->camera.y -= 2 * SCREEN_SIZE;
	}
	if (duration < 400 && duration >= 360) {
		App->render->camera.y -= 1 * SCREEN_SIZE;
	}
	if (duration < 360) {
		boat.y -= 4;
	}
	if (duration < 405 && duration >= 360) {
		boat.y -= 2;
	}
	
	if (duration == 180) {
		assetsAnim[2].Reset();
		bombs[0].x = (SCREEN_WIDTH / 2) - 8;
		bombs[0].y = -528; //-176
		App->audio->PlayFx(bombFx);
	}
	if (duration == 185) {
		assetsAnim[3].Reset();
		bombs[1].x = (SCREEN_WIDTH / 2) - 8;
		bombs[1].y = -588; //-206
		App->audio->PlayFx(bombFx);
	}
	if (duration == 200) {
		assetsAnim[4].Reset();
		bombs[2].x = (SCREEN_WIDTH / 2) - 8;
		bombs[2].y = -648; //-236
		App->audio->PlayFx(bombFx);
	}
	if (duration == 210) {
		assetsAnim[5].Reset();
		bombs[3].x = (SCREEN_WIDTH / 2) - 8;
		bombs[3].y = -708; //-266
		App->audio->PlayFx(bombFx);
	}
	if (duration == 220) {
		assetsAnim[6].Reset();
		bombs[4].x = (SCREEN_WIDTH / 2) - 8;
		bombs[4].y = -768; //-296
		App->audio->PlayFx(bombFx);
	}
	if (duration == 230) {
		assetsAnim[7].Reset();
		bombs[5].x = (SCREEN_WIDTH / 2) - 8;
		bombs[5].y = -828; //-326
		App->audio->PlayFx(bombFx);
	}
	if (duration == 240) {
		assetsAnim[8].Reset();
		bombs[6].x = (SCREEN_WIDTH / 2) - 8;
		bombs[6].y = -888; //-356
		App->audio->PlayFx(bombFx);
	}
	if (duration == 250) {
		assetsAnim[9].Reset();
		bombs[7].x = (SCREEN_WIDTH / 2) - 8;
		bombs[7].y = -948; //-386
		App->audio->PlayFx(bombFx);
	}
	if (duration == 425) {
		assetsAnim[1].Reset();
		playerMini.x = boat.x;
		playerMini.y = boat.y + 16;
	}

	for (int i = 0; i < 8; ++i) {
		if (i % 2 == 0) {
			if (assetsAnim[i + 2].GetCurrentFrameNum() < 6) {
				bombs[i].x += 1;
				bombs[i].y -= 4;
			}
		}
		else {
			if (assetsAnim[i + 2].GetCurrentFrameNum() < 6) {
				bombs[i].x -= 1;
				bombs[i].y -= 4;
			}
		}
	}

	if (assetsAnim[1].GetCurrentFrameNum() < 8) {
		playerMini.x -= 1;
		playerMini.y -= 1;
	}

	planes[0].y -= 6;
	planes[1].y -= 6;
	planes[2].y -= 6;

	for (int i = 0; i < MAX_ASSETS_TITLE; ++i) {
		assetsAnim[i].Update();
	}




	++duration;

	return update_status::UPDATE_CONTINUE;
}

// Update: draw background
update_status SceneTitle::PostUpdate() {
	App->render->Blit(bgTexture, 0, SCREEN_HEIGHT - 1904, NULL);

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
	App->audio->UnloadFx(bombFx);
	return true;
}