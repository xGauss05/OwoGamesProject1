#include "SceneWin.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleCollisions.h"
#include "ModuleEnemies.h"
#include "ModulePowerup.h"
#include "ModulePlayer.h"

SceneWin::SceneWin(bool startEnabled) : Module(startEnabled) {
}

SceneWin::~SceneWin() {
}

// Load assets
bool SceneWin::Start() {
	bool ret = true;
	return ret;
}

update_status SceneWin::Update() {
	return update_status::UPDATE_CONTINUE;
}

// Update: draw background
update_status SceneWin::PostUpdate() {

	return update_status::UPDATE_CONTINUE;
}

bool SceneWin::CleanUp() {

	return true;
}