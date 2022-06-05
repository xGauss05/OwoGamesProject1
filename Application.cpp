#include "Application.h"

#include "Module.h"
#include "ModuleWindow.h"
#include "ModuleInput.h"
#include "ModuleTextures.h"
#include "ModuleAudio.h"
#include "ModulePlayer.h"
#include "ModuleParticles.h"
#include "ModuleCollisions.h"
#include "ModuleRender.h"
#include "ModuleEnemies.h"
#include "ModulePowerup.h"
#include "ModuleBreakable.h"
#include "ModuleFadeToBlack.h"
#include "ModuleFonts.h"
#include "ModuleDebug.h"
#include "SceneIntro.h"
#include "SceneTitle.h"
#include "SceneLevel1.h"
#include "SceneWin.h"
#include "ScenePrevTitle.h"

Application::Application() {
	// The order in which the modules are added is very important.
	// It will define the order in which Pre/Update/Post will be called
	// Render should always be last, as our last action should be updating the screen
	modules[0] = window = new ModuleWindow(true);
	modules[1] = input = new ModuleInput(true);
	modules[2] = textures = new ModuleTextures(true);
	modules[3] = audio = new ModuleAudio(true);

	modules[4] = intro = new SceneIntro(true);
	modules[5] = prevtitle = new ScenePrevTitle(false);
	modules[6] = title = new SceneTitle(false);
	modules[7] = level1 = new SceneLevel1(false);
	modules[8] = win = new SceneWin(false);
	
	modules[9] = collisions = new ModuleCollisions(false);
	modules[10] = breakables = new ModuleBreakable(false);
	modules[11] = powerups = new ModulePowerup(false);
	modules[12] = enemies = new ModuleEnemies(false);
	modules[13] = player = new ModulePlayer(false);
	modules[14] = particles = new ModuleParticles(true);

	modules[15] = fonts = new ModuleFonts(true);
	modules[16] = fade = new ModuleFadeToBlack(true);
	modules[17] = debug = new ModuleDebug(false);
	modules[18] = render = new ModuleRender(true);
}

Application::~Application() {
	for (int i = 0; i < NUM_MODULES; ++i) {
		// Important: when deleting a pointer, set it to nullptr afterwards
		// It allows us for null check in other parts of the code
		delete modules[i];
		modules[i] = nullptr;
	}
}

bool Application::Init() {
	bool ret = true;

	for (int i = 0; i < NUM_MODULES && ret; ++i)
		ret = modules[i]->Init();

	for (int i = 0; i < NUM_MODULES && ret; ++i)
		ret = modules[i]->IsEnabled() ? modules[i]->Start() : true;

	return ret;
}

update_status Application::Update() {
	update_status ret = update_status::UPDATE_CONTINUE;

	for (int i = 0; i < NUM_MODULES && ret == update_status::UPDATE_CONTINUE; ++i)
		ret = modules[i]->IsEnabled() ? modules[i]->PreUpdate() : update_status::UPDATE_CONTINUE;

	for (int i = 0; i < NUM_MODULES && ret == update_status::UPDATE_CONTINUE; ++i)
		ret = modules[i]->IsEnabled() ? modules[i]->Update() : update_status::UPDATE_CONTINUE;

	for (int i = 0; i < NUM_MODULES && ret == update_status::UPDATE_CONTINUE; ++i)
		ret = modules[i]->IsEnabled() ? modules[i]->PostUpdate() : update_status::UPDATE_CONTINUE;

	return ret;
}

bool Application::CleanUp() {
	bool ret = true;

	for (int i = NUM_MODULES - 1; i >= 0 && ret; --i)
		ret = modules[i]->IsEnabled() ? modules[i]->CleanUp() : true;

	return ret;
}
