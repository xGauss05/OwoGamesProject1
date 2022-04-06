#include "ModuleScene.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleCollisions.h"

ModuleScene::ModuleScene() {}
ModuleScene::~ModuleScene() {}

// Load assets
bool ModuleScene::Start() {
	LOG("Loading background assets");

	bool ret = true;

	bgTexture = App->textures->Load("Assets/background.png"); // needs to be changed
	App->audio->PlayMusic("sounds/bgm/106.ogg", 1.0f);

	// Colliders ---
	// Bottom collider
	// Make collision boxes here
	//App->collisions->AddCollider({ 0, 224, 3930, 16 }, Collider::Type::WALL);

	//App->collisions->AddCollider({ 1375, 0, 3930, 16 }, Collider::Type::WALL);
	//App->collisions->AddCollider({ 141, 191, 65, 80 }, Collider::Type::WALL);
	//App->collisions->AddCollider({ 205, 207, 65, 80 }, Collider::Type::WALL);
	//App->collisions->AddCollider({ 591, 207, 65, 80 }, Collider::Type::WALL);
	//App->collisions->AddCollider({ 719, 191, 65, 80 }, Collider::Type::WALL);
	//App->collisions->AddCollider({ 1231, 207, 65, 80 }, Collider::Type::WALL);

	//App->collisions->AddCollider({ 1375, 16, 113, 80 }, Collider::Type::WALL);
	//App->collisions->AddCollider({ 1375, 143, 113, 80 }, Collider::Type::WALL);

	return ret;
}

update_status ModuleScene::Update() {
	App->render->camera.x += 3;

	return update_status::UPDATE_CONTINUE;
}

// Update: draw background
update_status ModuleScene::PostUpdate() {
	// Draw everything --------------------------------------
	App->render->Blit(bgTexture, 0, 0, NULL);

	return update_status::UPDATE_CONTINUE;
}
