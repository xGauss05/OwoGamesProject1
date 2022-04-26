#include "SceneLose.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleCollisions.h"
#include "ModuleEnemies.h"
#include "ModulePowerup.h"
#include "ModulePlayer.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"

#include "SDL/include/SDL_scancode.h"

SceneLose::SceneLose(bool startEnabled) : Module(startEnabled) {

}

SceneLose::~SceneLose() {
}

// Load assets
bool SceneLose::Start() {
	bool ret = true;
	bgTexture = App->textures->Load("img/sprites/lose.png");
	App->audio->PlayMusic("sounds/bgm/124.ogg", 1.0f);

	App->render->camera.x = 0;
	App->render->camera.y = 0;
	return ret;
}

update_status SceneLose::Update() {
	if (App->input->keys[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_DOWN) {
		App->fade->FadeToBlack(this, (Module*)App->title, 0);
	}
	if (App->input->keys[SDL_SCANCODE_ESCAPE] == KEY_STATE::KEY_REPEAT) {
		return update_status::UPDATE_STOP;
	}
	return update_status::UPDATE_CONTINUE;
}

// Update: draw background
update_status SceneLose::PostUpdate() {
	App->render->Blit(bgTexture, 0, 0, NULL);
	return update_status::UPDATE_CONTINUE;
}

bool SceneLose::CleanUp() {

	return true;
}