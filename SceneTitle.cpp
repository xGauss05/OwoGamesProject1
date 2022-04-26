#include "SceneTitle.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleCollisions.h"
#include "ModulePlayer.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"

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

	App->render->camera.x = 0;
	App->render->camera.y = 0;
	return ret;
}

update_status SceneTitle::Update() {
	if (App->input->keys[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_DOWN) {
		App->fade->FadeToBlack(this, (Module*)App->level1, 0);
	}
	return update_status::UPDATE_CONTINUE;
}

// Update: draw background
update_status SceneTitle::PostUpdate() {
	App->render->Blit(bgTexture, 0, 0, NULL);
	return update_status::UPDATE_CONTINUE;
}

bool SceneTitle::CleanUp() {
	
	return true;
}