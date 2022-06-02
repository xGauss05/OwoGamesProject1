#include "SceneIntro.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"

#include "SDL/include/SDL_scancode.h"

SceneIntro::SceneIntro(bool startEnabled) : Module(startEnabled) {}

SceneIntro::~SceneIntro() {}

// Load assets
bool SceneIntro::Start() {
	LOG("Loading background assets");

	bool ret = true;

	bgTexture = App->textures->Load("Assets/img/sprites/introduction.png");
	durationTimer = 0;
	// App->audio->PlayMusic("musicname here", 1.0f);

	App->render->camera.x = 0;
	App->render->camera.y = 0;

	return ret;
}

update_status SceneIntro::Update() {
	durationTimer++;
	if (App->input->keys[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_DOWN ||
		durationTimer >= SCENE_DURATION) {
		App->fade->FadeToBlack(this, (Module*)App->prevtitle, 90);
	}
	if (App->input->keys[SDL_SCANCODE_ESCAPE] == KEY_STATE::KEY_REPEAT) {
		return update_status::UPDATE_STOP;
	}

	return update_status::UPDATE_CONTINUE;
}

// Update: draw background
update_status SceneIntro::PostUpdate() {
	// Draw everything --------------------------------------
	App->render->Blit(bgTexture, 0, 0, NULL);

	return update_status::UPDATE_CONTINUE;
}

bool SceneIntro::CleanUp() {
	App->textures->Unload(bgTexture);
	bgTexture = nullptr;
	return true;
}

