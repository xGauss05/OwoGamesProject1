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
	bgTexture = App->textures->Load("Assets/img/sprites/win.png");
	App->audio->PlayMusic("Assets/sounds/bgm/127.ogg", 3.0f);
	countdown = 10;
	App->render->camera.x = 0;
	App->render->camera.y = 0;
	t1 = SDL_GetTicks();
	return ret;
}

update_status SceneWin::Update() {
	int t2 = SDL_GetTicks();
	if ((t2 - t1) / 1000.0f >= 1) {
		countdown--;
		t1 = t2;
	}
	
	bool toSkip = false;
	if (App->input->controllerCount > 0) {
		for (int i = 0; i < App->input->controllerCount; ++i) {
			if (App->input->controllers[i]->buttons[SDL_CONTROLLER_BUTTON_A] == KEY_DOWN) {
				toSkip = true;
			}
		}
	}

	if (App->input->keys[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_DOWN ||
		countdown == 1 || toSkip) {
		
		App->fade->FadeToBlack(this, (Module*)App->prevtitle, 0);
	}
	if (App->input->keys[SDL_SCANCODE_ESCAPE] == KEY_STATE::KEY_REPEAT) {
		return update_status::UPDATE_STOP;
	}
	return update_status::UPDATE_CONTINUE;
}

// Update: draw background
update_status SceneWin::PostUpdate() {
	App->render->Blit(bgTexture, 0, 0, NULL);
	return update_status::UPDATE_CONTINUE;
}

bool SceneWin::CleanUp() {
	App->textures->Unload(bgTexture);
	bgTexture = nullptr;
	return true;
}