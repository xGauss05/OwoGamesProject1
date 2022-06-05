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
	photoTexture = App->textures->Load("Assets/img/sprites/pretitle_photo.png");

	logoAnim.FullReset();
	logoAnim.PushBack({ 0, 240, 208, 160 });
	logoAnim.loop = false;

	logo.x = (SCREEN_WIDTH / 2) - 104;
	logo.y = 20;

	boatAnim.FullReset();
	boatAnim.PushBack({ 0 , 64, 32, 96 });
	boatAnim.PushBack({ 32, 64, 32, 96 });
	boatAnim.PushBack({ 64, 64, 32, 96 });
	boatAnim.PushBack({ 96, 64, 32, 96 });
	boatAnim.loop = true;
	boatAnim.speed = 0.1f;

	boat.x = (SCREEN_WIDTH / 2) - 8;
	boat.y = (SCREEN_HEIGHT / 2) + 64;

	duration = 0;

	scenePart = 0;

	App->render->camera.x = 500;
	App->render->camera.y = 0;

	return ret;
}

update_status ScenePrevTitle::Update() {
	duration++;

	bool toSkip = false;
	if (App->input->controllerCount > 0) {
		for (int i = 0; i < App->input->controllerCount; ++i) {
			if (App->input->controllers[i]->buttons[SDL_CONTROLLER_BUTTON_A] == KEY_DOWN) {
				toSkip = true;
			}
		}
	}

	switch (scenePart) {
	case 0:
		if (App->input->keys[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_DOWN ||
			duration >= SCENE_DURATION / 2 || toSkip) {
			scenePart = 1;
			App->render->camera.x = 0;
			App->render->camera.y = 0;
		}
		break;
	case 1:
		if (App->input->keys[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_DOWN ||
			duration >= SCENE_DURATION || toSkip) {
			App->fade->FadeToBlack(this, (Module*)App->title, 90);
		}
		App->render->camera.y -= 2 * SCREEN_SIZE;
		boat.y -= 4;
		logo.y -= 4;
		boatAnim.Update();

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
	
	App->render->Blit(photoTexture, 500, 0, NULL);

	SDL_Rect rect = logoAnim.GetCurrentFrame();
	App->render->Blit(introAssets, logo.x, logo.y, &rect);

	rect = boatAnim.GetCurrentFrame();
	App->render->Blit(introAssets, boat.x, boat.y, &rect);


	return update_status::UPDATE_CONTINUE;
}

bool ScenePrevTitle::CleanUp() {
	App->textures->Unload(bgTexture);
	bgTexture = nullptr;
	App->textures->Unload(introAssets);
	introAssets = nullptr;
	App->textures->Unload(photoTexture);
	photoTexture = nullptr;

	return true;
}
