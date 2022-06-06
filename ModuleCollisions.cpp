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
	// -- Wall
	matrix[Collider::Type::WALL][Collider::Type::WALL] = false;
	matrix[Collider::Type::WALL][Collider::Type::PLAYER] = true;
	matrix[Collider::Type::WALL][Collider::Type::ENEMY] = false;
	matrix[Collider::Type::WALL][Collider::Type::PLAYER_SHOT] = false;
	matrix[Collider::Type::WALL][Collider::Type::ENEMY_SHOT] = false;
	matrix[Collider::Type::WALL][Collider::Type::POWER_UP] = false;
	matrix[Collider::Type::WALL][Collider::Type::WATER] = false;
	matrix[Collider::Type::WALL][Collider::Type::TRENCH] = false;
	matrix[Collider::Type::WALL][Collider::Type::BREAKABLE] = false;
	matrix[Collider::Type::WALL][Collider::Type::BREAKABLE_BRIDGE] = false;
	matrix[Collider::Type::WALL][Collider::Type::NON_DEST_BAR] = false;
	matrix[Collider::Type::WALL][Collider::Type::HOSTAGE] = false;
	matrix[Collider::Type::WALL][Collider::Type::EXPLOSION] = false;
	matrix[Collider::Type::WALL][Collider::Type::TRUCK] = false;
	matrix[Collider::Type::WALL][Collider::Type::BOSS] = false;

	// -- Player
	matrix[Collider::Type::PLAYER][Collider::Type::WALL] = true;
	matrix[Collider::Type::PLAYER][Collider::Type::PLAYER] = false;
	matrix[Collider::Type::PLAYER][Collider::Type::ENEMY] = true;
	matrix[Collider::Type::PLAYER][Collider::Type::PLAYER_SHOT] = false;
	matrix[Collider::Type::PLAYER][Collider::Type::ENEMY_SHOT] = true;
	matrix[Collider::Type::PLAYER][Collider::Type::POWER_UP] = true;
	matrix[Collider::Type::PLAYER][Collider::Type::WATER] = true;
	matrix[Collider::Type::PLAYER][Collider::Type::TRENCH] = true;
	matrix[Collider::Type::PLAYER][Collider::Type::BREAKABLE] = true;
	matrix[Collider::Type::PLAYER][Collider::Type::BREAKABLE_BRIDGE] = false;
	matrix[Collider::Type::PLAYER][Collider::Type::NON_DEST_BAR] = true;
	matrix[Collider::Type::PLAYER][Collider::Type::HOSTAGE] = true;
	matrix[Collider::Type::PLAYER][Collider::Type::EXPLOSION] = true;
	matrix[Collider::Type::PLAYER][Collider::Type::TRUCK] = true;
	matrix[Collider::Type::PLAYER][Collider::Type::BOSS] = true;

	// -- Enemy
	matrix[Collider::Type::ENEMY][Collider::Type::WALL] = false;
	matrix[Collider::Type::ENEMY][Collider::Type::PLAYER] = true;
	matrix[Collider::Type::ENEMY][Collider::Type::ENEMY] = false;
	matrix[Collider::Type::ENEMY][Collider::Type::PLAYER_SHOT] = true;
	matrix[Collider::Type::ENEMY][Collider::Type::ENEMY_SHOT] = false;
	matrix[Collider::Type::ENEMY][Collider::Type::POWER_UP] = false;
	matrix[Collider::Type::ENEMY][Collider::Type::WATER] = false;
	matrix[Collider::Type::ENEMY][Collider::Type::TRENCH] = false;
	matrix[Collider::Type::ENEMY][Collider::Type::BREAKABLE] = false;
	matrix[Collider::Type::ENEMY][Collider::Type::BREAKABLE_BRIDGE] = false;
	matrix[Collider::Type::ENEMY][Collider::Type::NON_DEST_BAR] = false;
	matrix[Collider::Type::ENEMY][Collider::Type::HOSTAGE] = false;
	matrix[Collider::Type::ENEMY][Collider::Type::EXPLOSION] = true;
	matrix[Collider::Type::ENEMY][Collider::Type::TRUCK] = false;
	matrix[Collider::Type::ENEMY][Collider::Type::BOSS] = false;

	// -- Player shot
	matrix[Collider::Type::PLAYER_SHOT][Collider::Type::WALL] = false;
	matrix[Collider::Type::PLAYER_SHOT][Collider::Type::PLAYER] = false;
	matrix[Collider::Type::PLAYER_SHOT][Collider::Type::ENEMY] = true;
	matrix[Collider::Type::PLAYER_SHOT][Collider::Type::PLAYER_SHOT] = false;
	matrix[Collider::Type::PLAYER_SHOT][Collider::Type::ENEMY_SHOT] = false;
	matrix[Collider::Type::PLAYER_SHOT][Collider::Type::POWER_UP] = false;
	matrix[Collider::Type::PLAYER_SHOT][Collider::Type::WATER] = false;
	matrix[Collider::Type::PLAYER_SHOT][Collider::Type::TRENCH] = false;
	matrix[Collider::Type::PLAYER_SHOT][Collider::Type::BREAKABLE] = true;
	matrix[Collider::Type::PLAYER_SHOT][Collider::Type::BREAKABLE_BRIDGE] = false;
	matrix[Collider::Type::PLAYER_SHOT][Collider::Type::NON_DEST_BAR] = true;
	matrix[Collider::Type::PLAYER_SHOT][Collider::Type::HOSTAGE] = true;
	matrix[Collider::Type::PLAYER_SHOT][Collider::Type::EXPLOSION] = false;
	matrix[Collider::Type::PLAYER_SHOT][Collider::Type::TRUCK] = true;
	matrix[Collider::Type::PLAYER_SHOT][Collider::Type::BOSS] = true;

	// -- Enemy shot
	matrix[Collider::Type::ENEMY_SHOT][Collider::Type::WALL] = false;
	matrix[Collider::Type::ENEMY_SHOT][Collider::Type::PLAYER] = true;
	matrix[Collider::Type::ENEMY_SHOT][Collider::Type::ENEMY] = false;
	matrix[Collider::Type::ENEMY_SHOT][Collider::Type::PLAYER_SHOT] = false;
	matrix[Collider::Type::ENEMY_SHOT][Collider::Type::ENEMY_SHOT] = false;
	matrix[Collider::Type::ENEMY_SHOT][Collider::Type::POWER_UP] = false;
	matrix[Collider::Type::ENEMY_SHOT][Collider::Type::WATER] = false;
	matrix[Collider::Type::ENEMY_SHOT][Collider::Type::TRENCH] = false;
	matrix[Collider::Type::ENEMY_SHOT][Collider::Type::BREAKABLE] = true;
	matrix[Collider::Type::ENEMY_SHOT][Collider::Type::BREAKABLE_BRIDGE] = false;
	matrix[Collider::Type::ENEMY_SHOT][Collider::Type::NON_DEST_BAR] = true;
	matrix[Collider::Type::ENEMY_SHOT][Collider::Type::HOSTAGE] = true;
	matrix[Collider::Type::ENEMY_SHOT][Collider::Type::EXPLOSION] = false;
	matrix[Collider::Type::ENEMY_SHOT][Collider::Type::TRUCK] = false;
	matrix[Collider::Type::ENEMY_SHOT][Collider::Type::BOSS] = false;

	// -- Power up
	matrix[Collider::Type::POWER_UP][Collider::Type::WALL] = false;
	matrix[Collider::Type::POWER_UP][Collider::Type::PLAYER] = true;
	matrix[Collider::Type::POWER_UP][Collider::Type::ENEMY] = false;
	matrix[Collider::Type::POWER_UP][Collider::Type::PLAYER_SHOT] = false;
	matrix[Collider::Type::POWER_UP][Collider::Type::ENEMY_SHOT] = false;
	matrix[Collider::Type::POWER_UP][Collider::Type::POWER_UP] = false;
	matrix[Collider::Type::POWER_UP][Collider::Type::WATER] = false;
	matrix[Collider::Type::POWER_UP][Collider::Type::TRENCH] = false;
	matrix[Collider::Type::POWER_UP][Collider::Type::BREAKABLE] = false;
	matrix[Collider::Type::POWER_UP][Collider::Type::BREAKABLE_BRIDGE] = false;
	matrix[Collider::Type::POWER_UP][Collider::Type::NON_DEST_BAR] = false;
	matrix[Collider::Type::POWER_UP][Collider::Type::HOSTAGE] = false;
	matrix[Collider::Type::POWER_UP][Collider::Type::EXPLOSION] = false;
	matrix[Collider::Type::POWER_UP][Collider::Type::TRUCK] = false;
	matrix[Collider::Type::POWER_UP][Collider::Type::BOSS] = false;

	// -- Water
	matrix[Collider::Type::WATER][Collider::Type::WALL] = false;
	matrix[Collider::Type::WATER][Collider::Type::PLAYER] = true;
	matrix[Collider::Type::WATER][Collider::Type::ENEMY] = false;
	matrix[Collider::Type::WATER][Collider::Type::PLAYER_SHOT] = false;
	matrix[Collider::Type::WATER][Collider::Type::ENEMY_SHOT] = false;
	matrix[Collider::Type::WATER][Collider::Type::POWER_UP] = false;
	matrix[Collider::Type::WATER][Collider::Type::WATER] = false;
	matrix[Collider::Type::WATER][Collider::Type::TRENCH] = false;
	matrix[Collider::Type::WATER][Collider::Type::BREAKABLE] = false;
	matrix[Collider::Type::WATER][Collider::Type::BREAKABLE_BRIDGE] = false;
	matrix[Collider::Type::WATER][Collider::Type::NON_DEST_BAR] = false;
	matrix[Collider::Type::WATER][Collider::Type::HOSTAGE] = false;
	matrix[Collider::Type::WATER][Collider::Type::EXPLOSION] = false;
	matrix[Collider::Type::WATER][Collider::Type::TRUCK] = false;
	matrix[Collider::Type::WATER][Collider::Type::BOSS] = false;

	// -- Trench
	matrix[Collider::Type::TRENCH][Collider::Type::WALL] = false;
	matrix[Collider::Type::TRENCH][Collider::Type::PLAYER] = true;
	matrix[Collider::Type::TRENCH][Collider::Type::ENEMY] = false;
	matrix[Collider::Type::TRENCH][Collider::Type::PLAYER_SHOT] = false;
	matrix[Collider::Type::TRENCH][Collider::Type::ENEMY_SHOT] = false;
	matrix[Collider::Type::TRENCH][Collider::Type::POWER_UP] = false;
	matrix[Collider::Type::TRENCH][Collider::Type::WATER] = false;
	matrix[Collider::Type::TRENCH][Collider::Type::TRENCH] = false;
	matrix[Collider::Type::TRENCH][Collider::Type::BREAKABLE] = false;
	matrix[Collider::Type::TRENCH][Collider::Type::BREAKABLE_BRIDGE] = false;
	matrix[Collider::Type::TRENCH][Collider::Type::NON_DEST_BAR] = false;
	matrix[Collider::Type::TRENCH][Collider::Type::HOSTAGE] = false;
	matrix[Collider::Type::TRENCH][Collider::Type::EXPLOSION] = false;
	matrix[Collider::Type::TRENCH][Collider::Type::TRUCK] = false;
	matrix[Collider::Type::TRENCH][Collider::Type::BOSS] = false;

	// -- Breakable
	matrix[Collider::Type::BREAKABLE][Collider::Type::WALL] = false;
	matrix[Collider::Type::BREAKABLE][Collider::Type::PLAYER] = true;
	matrix[Collider::Type::BREAKABLE][Collider::Type::ENEMY] = false;
	matrix[Collider::Type::BREAKABLE][Collider::Type::PLAYER_SHOT] = true;
	matrix[Collider::Type::BREAKABLE][Collider::Type::ENEMY_SHOT] = true;
	matrix[Collider::Type::BREAKABLE][Collider::Type::POWER_UP] = false;
	matrix[Collider::Type::BREAKABLE][Collider::Type::WATER] = false;
	matrix[Collider::Type::BREAKABLE][Collider::Type::TRENCH] = false;
	matrix[Collider::Type::BREAKABLE][Collider::Type::BREAKABLE] = false;
	matrix[Collider::Type::BREAKABLE][Collider::Type::BREAKABLE_BRIDGE] = false;
	matrix[Collider::Type::BREAKABLE][Collider::Type::NON_DEST_BAR] = false;
	matrix[Collider::Type::BREAKABLE][Collider::Type::HOSTAGE] = false;
	matrix[Collider::Type::BREAKABLE][Collider::Type::EXPLOSION] = true;
	matrix[Collider::Type::BREAKABLE][Collider::Type::TRUCK] = false;
	matrix[Collider::Type::BREAKABLE][Collider::Type::BOSS] = false;

	// -- Non destroyable barricade
	matrix[Collider::Type::NON_DEST_BAR][Collider::Type::WALL] = false;
	matrix[Collider::Type::NON_DEST_BAR][Collider::Type::PLAYER] = true;
	matrix[Collider::Type::NON_DEST_BAR][Collider::Type::ENEMY] = false;
	matrix[Collider::Type::NON_DEST_BAR][Collider::Type::PLAYER_SHOT] = true;
	matrix[Collider::Type::NON_DEST_BAR][Collider::Type::ENEMY_SHOT] = true;
	matrix[Collider::Type::NON_DEST_BAR][Collider::Type::POWER_UP] = false;
	matrix[Collider::Type::NON_DEST_BAR][Collider::Type::WATER] = false;
	matrix[Collider::Type::NON_DEST_BAR][Collider::Type::TRENCH] = false;
	matrix[Collider::Type::NON_DEST_BAR][Collider::Type::BREAKABLE] = false;
	matrix[Collider::Type::NON_DEST_BAR][Collider::Type::BREAKABLE_BRIDGE] = false;
	matrix[Collider::Type::NON_DEST_BAR][Collider::Type::NON_DEST_BAR] = false;
	matrix[Collider::Type::NON_DEST_BAR][Collider::Type::HOSTAGE] = false;
	matrix[Collider::Type::NON_DEST_BAR][Collider::Type::EXPLOSION] = false;
	matrix[Collider::Type::NON_DEST_BAR][Collider::Type::TRUCK] = false;
	matrix[Collider::Type::NON_DEST_BAR][Collider::Type::BOSS] = false;

	// -- Hostage
	matrix[Collider::Type::HOSTAGE][Collider::Type::WALL] = false;
	matrix[Collider::Type::HOSTAGE][Collider::Type::PLAYER] = true;
	matrix[Collider::Type::HOSTAGE][Collider::Type::ENEMY] = true;
	matrix[Collider::Type::HOSTAGE][Collider::Type::PLAYER_SHOT] = true;
	matrix[Collider::Type::HOSTAGE][Collider::Type::ENEMY_SHOT] = true;
	matrix[Collider::Type::HOSTAGE][Collider::Type::POWER_UP] = false;
	matrix[Collider::Type::HOSTAGE][Collider::Type::WATER] = false;
	matrix[Collider::Type::HOSTAGE][Collider::Type::TRENCH] = false;
	matrix[Collider::Type::HOSTAGE][Collider::Type::BREAKABLE] = false;
	matrix[Collider::Type::HOSTAGE][Collider::Type::BREAKABLE_BRIDGE] = false;
	matrix[Collider::Type::HOSTAGE][Collider::Type::NON_DEST_BAR] = false;
	matrix[Collider::Type::HOSTAGE][Collider::Type::HOSTAGE] = false;
	matrix[Collider::Type::HOSTAGE][Collider::Type::EXPLOSION] = true;
	matrix[Collider::Type::HOSTAGE][Collider::Type::TRUCK] = false;
	matrix[Collider::Type::HOSTAGE][Collider::Type::BOSS] = false;

	// -- Breakable bridge
	matrix[Collider::Type::BREAKABLE_BRIDGE][Collider::Type::WALL] = false;
	matrix[Collider::Type::BREAKABLE_BRIDGE][Collider::Type::PLAYER] = false;
	matrix[Collider::Type::BREAKABLE_BRIDGE][Collider::Type::ENEMY] = false;
	matrix[Collider::Type::BREAKABLE_BRIDGE][Collider::Type::PLAYER_SHOT] = false;
	matrix[Collider::Type::BREAKABLE_BRIDGE][Collider::Type::ENEMY_SHOT] = false;
	matrix[Collider::Type::BREAKABLE_BRIDGE][Collider::Type::POWER_UP] = false;
	matrix[Collider::Type::BREAKABLE_BRIDGE][Collider::Type::WATER] = false;
	matrix[Collider::Type::BREAKABLE_BRIDGE][Collider::Type::TRENCH] = false;
	matrix[Collider::Type::BREAKABLE_BRIDGE][Collider::Type::BREAKABLE] = false;
	matrix[Collider::Type::BREAKABLE_BRIDGE][Collider::Type::BREAKABLE_BRIDGE] = false;
	matrix[Collider::Type::BREAKABLE_BRIDGE][Collider::Type::NON_DEST_BAR] = false;
	matrix[Collider::Type::BREAKABLE_BRIDGE][Collider::Type::HOSTAGE] = false;
	matrix[Collider::Type::BREAKABLE_BRIDGE][Collider::Type::EXPLOSION] = true;
	matrix[Collider::Type::BREAKABLE_BRIDGE][Collider::Type::TRUCK] = false;
	matrix[Collider::Type::BREAKABLE_BRIDGE][Collider::Type::BOSS] = false;

	// -- Explosion
	matrix[Collider::Type::EXPLOSION][Collider::Type::WALL] = false;
	matrix[Collider::Type::EXPLOSION][Collider::Type::PLAYER] = true;
	matrix[Collider::Type::EXPLOSION][Collider::Type::ENEMY] = true;
	matrix[Collider::Type::EXPLOSION][Collider::Type::PLAYER_SHOT] = false;
	matrix[Collider::Type::EXPLOSION][Collider::Type::ENEMY_SHOT] = false;
	matrix[Collider::Type::EXPLOSION][Collider::Type::POWER_UP] = false;
	matrix[Collider::Type::EXPLOSION][Collider::Type::WATER] = false;
	matrix[Collider::Type::EXPLOSION][Collider::Type::TRENCH] = false;
	matrix[Collider::Type::EXPLOSION][Collider::Type::BREAKABLE] = false;
	matrix[Collider::Type::EXPLOSION][Collider::Type::BREAKABLE_BRIDGE] = false;
	matrix[Collider::Type::EXPLOSION][Collider::Type::NON_DEST_BAR] = false;
	matrix[Collider::Type::EXPLOSION][Collider::Type::HOSTAGE] = true;
	matrix[Collider::Type::EXPLOSION][Collider::Type::EXPLOSION] = false;
	matrix[Collider::Type::EXPLOSION][Collider::Type::TRUCK] = true;
	matrix[Collider::Type::EXPLOSION][Collider::Type::BOSS] = true;

	// -- Truck
	matrix[Collider::Type::TRUCK][Collider::Type::WALL] = false;
	matrix[Collider::Type::TRUCK][Collider::Type::PLAYER] = true;
	matrix[Collider::Type::TRUCK][Collider::Type::ENEMY] = false;
	matrix[Collider::Type::TRUCK][Collider::Type::PLAYER_SHOT] = false;
	matrix[Collider::Type::TRUCK][Collider::Type::ENEMY_SHOT] = false;
	matrix[Collider::Type::TRUCK][Collider::Type::POWER_UP] = false;
	matrix[Collider::Type::TRUCK][Collider::Type::WATER] = false;
	matrix[Collider::Type::TRUCK][Collider::Type::TRENCH] = false;
	matrix[Collider::Type::TRUCK][Collider::Type::BREAKABLE] = false;
	matrix[Collider::Type::TRUCK][Collider::Type::BREAKABLE_BRIDGE] = false;
	matrix[Collider::Type::TRUCK][Collider::Type::NON_DEST_BAR] = false;
	matrix[Collider::Type::TRUCK][Collider::Type::HOSTAGE] = false;
	matrix[Collider::Type::TRUCK][Collider::Type::EXPLOSION] = true;
	matrix[Collider::Type::TRUCK][Collider::Type::TRUCK] = true;
	matrix[Collider::Type::TRUCK][Collider::Type::BOSS] = false;

	// -- Boss
	matrix[Collider::Type::BOSS][Collider::Type::WALL] = false;
	matrix[Collider::Type::BOSS][Collider::Type::PLAYER] = true;
	matrix[Collider::Type::BOSS][Collider::Type::ENEMY] = false;
	matrix[Collider::Type::BOSS][Collider::Type::PLAYER_SHOT] = true;
	matrix[Collider::Type::BOSS][Collider::Type::ENEMY_SHOT] = false;
	matrix[Collider::Type::BOSS][Collider::Type::POWER_UP] = false;
	matrix[Collider::Type::BOSS][Collider::Type::WATER] = false;
	matrix[Collider::Type::BOSS][Collider::Type::TRENCH] = false;
	matrix[Collider::Type::BOSS][Collider::Type::BREAKABLE] = false;
	matrix[Collider::Type::BOSS][Collider::Type::BREAKABLE_BRIDGE] = false;
	matrix[Collider::Type::BOSS][Collider::Type::NON_DEST_BAR] = false;
	matrix[Collider::Type::BOSS][Collider::Type::HOSTAGE] = false;
	matrix[Collider::Type::BOSS][Collider::Type::EXPLOSION] = true;
	matrix[Collider::Type::BOSS][Collider::Type::TRUCK] = false;
	matrix[Collider::Type::BOSS][Collider::Type::BOSS] = false;
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
