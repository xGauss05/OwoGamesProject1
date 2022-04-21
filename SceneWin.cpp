#include "SceneWin.h"

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

SceneWin::SceneWin(bool startEnabled) : Module(startEnabled) {

}

SceneWin::~SceneWin() {
}

// Load assets
bool SceneWin::Start() {
	bool ret = true;
	bgTexture = App->textures->Load("img/sprites/win.png");
	App->audio->PlayMusic("sounds/bgm/127.ogg", 1.0f);

	App->render->camera.x = 0;
	App->render->camera.y = 0;
	return ret;
}

update_status SceneWin::Update() {
	if (App->input->keys[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_DOWN) {
		App->fade->FadeToBlack(this, (Module*)App->title, 0);
	}
	return update_status::UPDATE_CONTINUE;
}

// Update: draw background
update_status SceneWin::PostUpdate() {
	App->render->Blit(bgTexture, 0, 0, NULL);
	return update_status::UPDATE_CONTINUE;
}

bool SceneWin::CleanUp() {

	return true;
}