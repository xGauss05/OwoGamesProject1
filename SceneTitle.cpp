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

	assetsPoint[0] = planes[0];
	assetsPoint[1] = planes[1];
	assetsPoint[2] = planes[2];
	assetsPoint[3] = boat;
	assetsPoint[4] = bombs[0];
	assetsPoint[5] = bombs[1];
	assetsPoint[6] = bombs[2];
	assetsPoint[7] = bombs[3];
	assetsPoint[8] = bombs[4];
	assetsPoint[9] = bombs[5];
	assetsPoint[10] = bombs[6];
	assetsPoint[11] = bombs[7];
	assetsPoint[12] = playerMini;

	assetsAnim[0] = planesAnim;
	assetsAnim[1] = planesAnim;
	assetsAnim[2] = planesAnim;
	assetsAnim[3] = boatAnim;
	assetsAnim[4] = bombsAnim;
	assetsAnim[5] = bombsAnim;
	assetsAnim[6] = bombsAnim;
	assetsAnim[7] = bombsAnim;
	assetsAnim[8] = bombsAnim;
	assetsAnim[9] = bombsAnim;
	assetsAnim[10] = bombsAnim;
	assetsAnim[11] = bombsAnim;
	assetsAnim[12] = playerMiniAnim;

	return ret;
}

update_status SceneTitle::Update() {

	if (App->input->keys[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_DOWN || duration >= SCENE_DURATION) {
		App->fade->FadeToBlack(this, (Module*)App->level1, 0);
	}
	if(App->input->keys[SDL_SCANCODE_ESCAPE] == KEY_STATE::KEY_REPEAT) {
		return update_status::UPDATE_STOP;
	}

	++duration;

	return update_status::UPDATE_CONTINUE;
}

// Update: draw background
update_status SceneTitle::PostUpdate() {
	App->render->Blit(bgTexture, 0, 0, NULL);

	/*for (int i = 0; i < 13; ++i) {
		SDL_Rect rect = assetsAnim[i].GetCurrentFrame();
		App->render->Blit(introAssets, assetsPoint[i].x, assetsPoint[i].y, &rect);
	}
	*/
	return update_status::UPDATE_CONTINUE;
}

bool SceneTitle::CleanUp() {
	App->textures->Unload(bgTexture);
	App->textures->Unload(introAssets);
	bgTexture = nullptr;
	introAssets = nullptr;
	return true;
}