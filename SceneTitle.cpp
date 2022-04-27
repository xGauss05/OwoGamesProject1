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
	bgTexture = App->textures->Load("img/sprites/title.png");
	App->audio->PlayMusic("sounds/bgm/112.ogg", 1.0f);

	introAssets = App->textures->Load("img/sprites/intro_assets.png");

	bombsAnimation.PushBack({ 0 , 160, 16, 16 });
	bombsAnimation.PushBack({ 16, 160, 16, 16 });
	bombsAnimation.PushBack({ 32, 160, 16, 16 });
	bombsAnimation.PushBack({ 48, 160, 16, 16 });
	bombsAnimation.PushBack({ 64, 160, 16, 16 });
	bombsAnimation.PushBack({ 80, 160, 16, 16 });
	bombsAnimation.PushBack({ 96, 160, 16, 16 });
	bombsAnimation.PushBack({ 0  , 176, 32, 64 });
	bombsAnimation.PushBack({ 32 , 176, 32, 64 });
	bombsAnimation.PushBack({ 64 , 176, 32, 64 });
	bombsAnimation.PushBack({ 96 , 176, 32, 64 });
	bombsAnimation.PushBack({ 128, 176, 32, 64 });
	bombsAnimation.PushBack({ 160, 176, 32, 64 });
	bombsAnimation.PushBack({ 192, 176, 32, 64 });
	bombsAnimation.loop = false;

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
	return ret;
}

update_status SceneTitle::Update() {
	if (App->input->keys[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_DOWN) {
		App->fade->FadeToBlack(this, (Module*)App->level1, 0);
	}
	if(App->input->keys[SDL_SCANCODE_ESCAPE] == KEY_STATE::KEY_REPEAT) {
		return update_status::UPDATE_STOP;
	}
	return update_status::UPDATE_CONTINUE;
}

// Update: draw background
update_status SceneTitle::PostUpdate() {
	App->render->Blit(bgTexture, 0, 0, NULL);
	return update_status::UPDATE_CONTINUE;
}

bool SceneTitle::CleanUp() {
	App->textures->Unload(bgTexture);
	App->textures->Unload(introAssets);
	bgTexture = nullptr;
	introAssets = nullptr;
	return true;
}