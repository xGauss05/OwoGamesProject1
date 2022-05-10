#include "ModuleCollisions.h"

#include "Application.h"

#include "ModuleRender.h"
#include "ModuleInput.h"

#include "ModuleEnemies.h"
#include "Enemy.h"
#include <math.h>

#include "ModulePlayer.h"
#include "ModuleFonts.h"
#include <string>
using namespace std;

#include "SDL/include/SDL_render.h"
#include "SDL/include/SDL_Scancode.h"

ModuleCollisions::ModuleCollisions(bool startEnabled) : Module(startEnabled) {
	for (uint i = 0; i < MAX_COLLIDERS; ++i)
		colliders[i] = nullptr;

	// Make types of collision depending of which type of collision you want
	matrix[Collider::Type::WALL][Collider::Type::WALL] = false;
	matrix[Collider::Type::WALL][Collider::Type::PLAYER] = true;
	matrix[Collider::Type::WALL][Collider::Type::ENEMY] = false;
	matrix[Collider::Type::WALL][Collider::Type::PLAYER_SHOT] = false;
	matrix[Collider::Type::WALL][Collider::Type::ENEMY_SHOT] = false;
	matrix[Collider::Type::WALL][Collider::Type::POWER_UP] = false;
	matrix[Collider::Type::WALL][Collider::Type::WATER] = false;
	matrix[Collider::Type::WALL][Collider::Type::TRENCH] = false;
	matrix[Collider::Type::WALL][Collider::Type::BARRICADE] = false;

	matrix[Collider::Type::PLAYER][Collider::Type::WALL] = true;
	matrix[Collider::Type::PLAYER][Collider::Type::PLAYER] = false;
	matrix[Collider::Type::PLAYER][Collider::Type::ENEMY] = true;
	matrix[Collider::Type::PLAYER][Collider::Type::PLAYER_SHOT] = false;
	matrix[Collider::Type::PLAYER][Collider::Type::ENEMY_SHOT] = true;
	matrix[Collider::Type::PLAYER][Collider::Type::POWER_UP] = true;
	matrix[Collider::Type::PLAYER][Collider::Type::WATER] = true;
	matrix[Collider::Type::PLAYER][Collider::Type::TRENCH] = true;
	matrix[Collider::Type::PLAYER][Collider::Type::BARRICADE] = true;

	matrix[Collider::Type::ENEMY][Collider::Type::WALL] = false;
	matrix[Collider::Type::ENEMY][Collider::Type::PLAYER] = true;
	matrix[Collider::Type::ENEMY][Collider::Type::ENEMY] = false;
	matrix[Collider::Type::ENEMY][Collider::Type::PLAYER_SHOT] = true;
	matrix[Collider::Type::ENEMY][Collider::Type::ENEMY_SHOT] = false;
	matrix[Collider::Type::ENEMY][Collider::Type::POWER_UP] = false;
	matrix[Collider::Type::ENEMY][Collider::Type::WATER] = false;
	matrix[Collider::Type::ENEMY][Collider::Type::TRENCH] = false;
	matrix[Collider::Type::ENEMY][Collider::Type::BARRICADE] = true;

	matrix[Collider::Type::PLAYER_SHOT][Collider::Type::WALL] = false;
	matrix[Collider::Type::PLAYER_SHOT][Collider::Type::PLAYER] = false;
	matrix[Collider::Type::PLAYER_SHOT][Collider::Type::ENEMY] = true;
	matrix[Collider::Type::PLAYER_SHOT][Collider::Type::PLAYER_SHOT] = false;
	matrix[Collider::Type::PLAYER_SHOT][Collider::Type::ENEMY_SHOT] = false;
	matrix[Collider::Type::PLAYER_SHOT][Collider::Type::POWER_UP] = false;
	matrix[Collider::Type::PLAYER_SHOT][Collider::Type::WATER] = false;
	matrix[Collider::Type::PLAYER_SHOT][Collider::Type::TRENCH] = false;
	matrix[Collider::Type::PLAYER_SHOT][Collider::Type::BARRICADE] = true;

	matrix[Collider::Type::ENEMY_SHOT][Collider::Type::WALL] = false;
	matrix[Collider::Type::ENEMY_SHOT][Collider::Type::PLAYER] = true;
	matrix[Collider::Type::ENEMY_SHOT][Collider::Type::ENEMY] = false;
	matrix[Collider::Type::ENEMY_SHOT][Collider::Type::PLAYER_SHOT] = false;
	matrix[Collider::Type::ENEMY_SHOT][Collider::Type::ENEMY_SHOT] = false;
	matrix[Collider::Type::ENEMY_SHOT][Collider::Type::POWER_UP] = false;
	matrix[Collider::Type::ENEMY_SHOT][Collider::Type::WATER] = false;
	matrix[Collider::Type::ENEMY_SHOT][Collider::Type::TRENCH] = false;
	matrix[Collider::Type::ENEMY_SHOT][Collider::Type::BARRICADE] = true;

	matrix[Collider::Type::POWER_UP][Collider::Type::WALL] = false;
	matrix[Collider::Type::POWER_UP][Collider::Type::PLAYER] = true;
	matrix[Collider::Type::POWER_UP][Collider::Type::ENEMY] = false;
	matrix[Collider::Type::POWER_UP][Collider::Type::PLAYER_SHOT] = false;
	matrix[Collider::Type::POWER_UP][Collider::Type::ENEMY_SHOT] = false;
	matrix[Collider::Type::POWER_UP][Collider::Type::POWER_UP] = false;
	matrix[Collider::Type::POWER_UP][Collider::Type::WATER] = false;
	matrix[Collider::Type::POWER_UP][Collider::Type::TRENCH] = false;
	matrix[Collider::Type::POWER_UP][Collider::Type::BARRICADE] = false;
	

	matrix[Collider::Type::WATER][Collider::Type::WALL] = false;
	matrix[Collider::Type::WATER][Collider::Type::PLAYER] = true;
	matrix[Collider::Type::WATER][Collider::Type::ENEMY] = false;
	matrix[Collider::Type::WATER][Collider::Type::PLAYER_SHOT] = false;
	matrix[Collider::Type::WATER][Collider::Type::ENEMY_SHOT] = false;
	matrix[Collider::Type::WATER][Collider::Type::POWER_UP] = false;
	matrix[Collider::Type::WATER][Collider::Type::WATER] = false;
	matrix[Collider::Type::WATER][Collider::Type::TRENCH] = false;
	matrix[Collider::Type::WATER][Collider::Type::BARRICADE] = false;

	matrix[Collider::Type::TRENCH][Collider::Type::WALL] = false;
	matrix[Collider::Type::TRENCH][Collider::Type::PLAYER] = true;
	matrix[Collider::Type::TRENCH][Collider::Type::ENEMY] = false;
	matrix[Collider::Type::TRENCH][Collider::Type::PLAYER_SHOT] = false;
	matrix[Collider::Type::TRENCH][Collider::Type::ENEMY_SHOT] = false;
	matrix[Collider::Type::TRENCH][Collider::Type::POWER_UP] = false;
	matrix[Collider::Type::TRENCH][Collider::Type::WATER] = false;
	matrix[Collider::Type::TRENCH][Collider::Type::TRENCH] = false;
	matrix[Collider::Type::TRENCH][Collider::Type::BARRICADE] = false;

	matrix[Collider::Type::BARRICADE][Collider::Type::WALL] = false;
	matrix[Collider::Type::BARRICADE][Collider::Type::PLAYER] = true;
	matrix[Collider::Type::BARRICADE][Collider::Type::ENEMY] = true;
	matrix[Collider::Type::BARRICADE][Collider::Type::PLAYER_SHOT] = true;
	matrix[Collider::Type::BARRICADE][Collider::Type::ENEMY_SHOT] = true;
	matrix[Collider::Type::BARRICADE][Collider::Type::POWER_UP] = false;
	matrix[Collider::Type::BARRICADE][Collider::Type::WATER] = false;
	matrix[Collider::Type::BARRICADE][Collider::Type::TRENCH] = false;
	matrix[Collider::Type::BARRICADE][Collider::Type::BARRICADE] = false;
}

// Destructor
ModuleCollisions::~ModuleCollisions() {}

update_status ModuleCollisions::PreUpdate() {
	// Remove all colliders scheduled for deletion
	for (uint i = 0; i < MAX_COLLIDERS; ++i) {
		if (colliders[i] != nullptr && colliders[i]->pendingToDelete == true) {
			delete colliders[i];
			colliders[i] = nullptr;
		}
	}

	Collider* c1;
	Collider* c2;

	for (uint i = 0; i < MAX_COLLIDERS; ++i) {
		// Skip empty colliders
		if (colliders[i] == nullptr)
			continue;

		c1 = colliders[i];

		// Avoid checking collisions already checked
		for (uint k = i + 1; k < MAX_COLLIDERS; ++k) {
			// Skip empty colliders
			if (colliders[k] == nullptr)
				continue;

			c2 = colliders[k];

			if (c1->Intersects(c2->rect)) {
				if (matrix[c1->type][c2->type] && c1->listener)
					c1->listener->OnCollision(c1, c2);

				if (matrix[c2->type][c1->type] && c2->listener)
					c2->listener->OnCollision(c2, c1);
			}
		}
	}

	return update_status::UPDATE_CONTINUE;
}

////update_status ModuleCollisions::Update() {
////	if (App->input->keys[SDL_SCANCODE_F2] == KEY_DOWN)
////		debug = !debug;
////
////	return update_status::UPDATE_CONTINUE;
////}

////update_status ModuleCollisions::PostUpdate() {
////	if (debug)
////		DebugDraw();
////
////	return update_status::UPDATE_CONTINUE;
////}

////void ModuleCollisions::DebugDraw() {
////	Uint8 alpha = 80;
////	for (uint i = 0; i < MAX_COLLIDERS; ++i) {
////		if (colliders[i] == nullptr)
////			continue;
////
////		switch (colliders[i]->type) {
////		case Collider::Type::NONE: // white
////			App->render->DrawQuad(colliders[i]->rect, 255, 255, 255, alpha);
////			break;
////		case Collider::Type::WALL: // blue
////			App->render->DrawQuad(colliders[i]->rect, 0, 0, 255, alpha);
////			break;
////		case Collider::Type::PLAYER: // green
////			App->render->DrawQuad(colliders[i]->rect, 0, 255, 0, alpha);
////			break;
////		case Collider::Type::HOSTAGE: // green
////			App->render->DrawQuad(colliders[i]->rect, 0, 255, 0, alpha);
////			break;
////		case Collider::Type::ENEMY: // red
////			App->render->DrawQuad(colliders[i]->rect, 255, 0, 0, alpha);
////			break;
////		case Collider::Type::PLAYER_SHOT: // yellow
////			App->render->DrawQuad(colliders[i]->rect, 255, 255, 0, alpha);
////			break;
////		case Collider::Type::ENEMY_SHOT: // magenta
////			App->render->DrawQuad(colliders[i]->rect, 0, 255, 255, alpha);
////			break;
////		case Collider::Type::POWER_UP: // white
////			App->render->DrawQuad(colliders[i]->rect, 255, 255, 255, alpha);
////			break;
////		case Collider::Type::WATER:
////			App->render->DrawQuad(colliders[i]->rect, 0, 255, 100, alpha);
////			break;
////		case Collider::Type::TRENCH:
////			App->render->DrawQuad(colliders[i]->rect, 255, 0, 100, alpha);
////			break;
////		case Collider::Type::BARRICADE:
////			App->render->DrawQuad(colliders[i]->rect, 0, 0, 0, alpha);
////			break;
////		default:
////			break;
////		}
////
////	}
////
////	
////	for (size_t i = 0; i < MAX_ENEMIES; i++)
////	{
////		if (App->enemies->enemies[i] != nullptr)
////		{
////			App->render->DrawLine(	App->enemies->enemies[i]->position.x + 16,
////									App->enemies->enemies[i]->position.y + 32,
////									App->enemies->enemies[i]->position.x + 16 + 20 * cos(App->enemies->enemies[i]->degrees * (M_PI/180)),
////									App->enemies->enemies[i]->position.y + 32 + 20 * sin(App->enemies->enemies[i]->degrees * (M_PI / 180)),
////									0, 255, 0, 255);
////		}
////	}
////
////	//Position debug
////	App->fonts->BlitText(10, 250, 0, "PLAYER");
////
////	App->fonts->BlitText(10, 270, 0, "X.");
////	App->fonts->BlitText(25, 270, 0, std::to_string(App->player->position.x).c_str());
////
////	App->fonts->BlitText(10, 280, 0, "Y.");
////	App->fonts->BlitText(25, 280, 0, std::to_string(App->player->position.y).c_str());
////
////	//Controller debug
////	if (App->input->controllers[0] != nullptr)
////	{
////		App->fonts->BlitText(10, 300, 0, "CONTROLLER");
////
////		App->fonts->BlitText(10, 320, 0, "J1.X");
////		App->fonts->BlitText(50, 320, 0, std::to_string(App->input->controllers[0]->j1_x).c_str());
////
////		App->fonts->BlitText(10, 330, 0, "J1.Y");
////		App->fonts->BlitText(50, 330, 0, std::to_string(App->input->controllers[0]->j1_y).c_str());
////
////		if (App->input->controllers[0]->j1_y < -10000)
////			App->fonts->BlitText(70, 100, 0, "MOV.FORWARDS");
////
////		else if (App->input->controllers[0]->j1_y > 10000)
////			App->fonts->BlitText(70, 120, 0, "MOV.BACKWARDS");
////
////		if (App->input->controllers[0]->j1_x < -10000)
////			App->fonts->BlitText(20, 110, 0, "MOV.LEFT");
////
////		else if (App->input->controllers[0]->j1_x > 10000)
////			App->fonts->BlitText(120, 110, 0, "MOV.RIGHT");
////
////		//
////
////		App->fonts->BlitText(10, 350, 0, "J2.X");
////		App->fonts->BlitText(50, 350, 0, std::to_string(App->input->controllers[0]->j2_x).c_str());
////
////		App->fonts->BlitText(10, 360, 0, "J2.Y");
////		App->fonts->BlitText(50, 360, 0, std::to_string(App->input->controllers[0]->j2_y).c_str());
////
////		if (App->input->controllers[0]->j2_y < -10000)
////			App->fonts->BlitText(70, 200, 0, "AIM.FORWARDS");
////
////		else if (App->input->controllers[0]->j2_y > 10000)
////			App->fonts->BlitText(70, 220, 0, "AIM.BACKWARDS");
////
////		if (App->input->controllers[0]->j2_x < -10000)
////			App->fonts->BlitText(20, 210, 0, "AIM.LEFT");
////
////		else if (App->input->controllers[0]->j2_x > 10000)
////			App->fonts->BlitText(120, 210, 0, "AIM.RIGHT");
////
////	}
////}

// Called before quitting
bool ModuleCollisions::CleanUp() {
	LOG("Freeing all colliders. ");

	for (uint i = 0; i < MAX_COLLIDERS; ++i) {
		if (colliders[i] != nullptr) {
			delete colliders[i];
			colliders[i] = nullptr;
		}
	}

	return true;
}

Collider* ModuleCollisions::AddCollider(SDL_Rect rect, Collider::Type type, Module* listener) {
	Collider* ret = nullptr;

	for (uint i = 0; i < MAX_COLLIDERS; ++i) {
		if (colliders[i] == nullptr) {
			ret = colliders[i] = new Collider(rect, type, listener);
			break;
		}
	}

	return ret;
}
