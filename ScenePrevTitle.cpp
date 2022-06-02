#include "ScenePrevTitle.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"

#include "SDL/include/SDL_scancode.h"

ScenePrevTitle::ScenePrevTitle(bool startEnabled) : Module(startEnabled) {}

ScenePrevTitle::~ScenePrevTitle() {}

// Load assets
bool ScenePrevTitle::Start() {
	LOG("Loading background assets");

	bool ret = true;

	introAssets = App->textures->Load("Assets/img/sprites/intro_assets.png");
	bgTexture = App->textures->Load("Assets/img/sprites/title_map_large.png");

	photoAnim.FullReset();
	photoAnim.PushBack({ 208, 240, 128, 144 });
	photoAnim.loop = false;
	
	photo.x = 500;


	logoAnim.FullReset();
	logoAnim.PushBack({ 0, 240, 208, 160 });
	logoAnim.loop = false;

	duration = 0;

	scenePart = 0;

	App->render->camera.x = 500;
	App->render->camera.y = 0;

	return ret;
}

update_status ScenePrevTitle::Update() {
	duration++;

	switch (scenePart) {
	case 0:
		if (App->input->keys[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_DOWN ||
			duration >= SCENE_DURATION / 2) {
			scenePart = 1;
			App->render->camera.x = 0;
			App->render->camera.y = 0;
		}
		break;
	case 1:
		if (App->input->keys[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_DOWN ||
			duration >= SCENE_DURATION) {
			App->fade->FadeToBlack(this, (Module*)App->title, 90);
		}
		break;
	default:
		break;
	}

	if (App->input->keys[SDL_SCANCODE_ESCAPE] == KEY_STATE::KEY_REPEAT) {
		return update_status::UPDATE_STOP;
	}

	return update_status::UPDATE_CONTINUE;
}

// Update: draw background
update_status ScenePrevTitle::PostUpdate() {
	// Draw everything --------------------------------------
	App->render->Blit(bgTexture, 0, SCREEN_HEIGHT - 1904, NULL);
	
	SDL_Rect rect = photoAnim.GetCurrentFrame();
	App->render->Blit(introAssets, photo.x, photo.y, &rect);

	rect = logoAnim.GetCurrentFrame();
	App->render->Blit(introAssets, logo.x, logo.y, &rect);


	return update_status::UPDATE_CONTINUE;
}

bool ScenePrevTitle::CleanUp() {
	App->textures->Unload(bgTexture);
	bgTexture = nullptr;
	return true;
}
