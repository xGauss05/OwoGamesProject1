#include "ModulePowerup.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleCollisions.h"

#include "SDL/include/SDL_scancode.h"

ModulePowerup::ModulePowerup() {

}

ModulePowerup::~ModulePowerup() {
}

bool ModulePowerup::Start() {
	texture = App->textures->Load("img/sprites/weapon.png");
	return false;
}

update_status ModulePowerup::Update() {
	return update_status::UPDATE_CONTINUE;
}

update_status ModulePowerup::PostUpdate() {
	return update_status::UPDATE_CONTINUE;
}

void ModulePowerup::OnCollision(Collider* c1, Collider* c2) {
	
}