#include "SceneStart.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleCollisions.h"
#include "ModulePlayer.h"

SceneStart::SceneStart(bool startEnabled) : Module(startEnabled) {}

SceneStart::~SceneStart() {}

// Load assets
bool SceneStart::Start() {
	bool ret = true;
	return ret;
}

update_status SceneStart::Update() {
	return update_status::UPDATE_CONTINUE;
}

// Update: draw background
update_status SceneStart::PostUpdate() {

	return update_status::UPDATE_CONTINUE;
}

bool SceneStart::CleanUp() {

	return true;
}