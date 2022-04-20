#include "SceneTitle.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleCollisions.h"


#include "ModulePlayer.h"

SceneTitle::SceneTitle(bool startEnabled) : Module(startEnabled) {
}

SceneTitle::~SceneTitle() {}

// Load assets
bool SceneTitle::Start() {
	bool ret = true;
	return ret;
}

update_status SceneTitle::Update() {
	return update_status::UPDATE_CONTINUE;
}

// Update: draw background
update_status SceneTitle::PostUpdate() {

	return update_status::UPDATE_CONTINUE;
}

bool SceneTitle::CleanUp() {

	return true;
}