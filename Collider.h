#ifndef __COLLIDER_H__
#define __COLLIDER_H__

#include "SDL/include/SDL_Rect.h"

class Module;

struct Collider {
	enum Type {
		NONE = -1,
		WALL,
		POWER_UP,
		PLAYER,
		ENEMY,
		PLAYER_SHOT,
		ENEMY_SHOT,
		WATER,
		TRENCH,
		HOSTAGE,
		BREAKABLE,
		NON_DEST_BAR,
		EXPLOSION,

		MAX
	};

	//Methods
	Collider(SDL_Rect rectangle, Type type, Module* listener = nullptr);

	void SetPos(int x, int y);

	bool Intersects(const SDL_Rect& r) const;

	//Variables
	SDL_Rect rect;
	bool pendingToDelete = false;
	Type type;
	// Change the listener if the affected needs an interaction
	Module* listener = nullptr;
};

#endif // !__COLLIDER_H__
