#include "Collider.h"

Collider::Collider(SDL_Rect rectangle, Type type, Module* listener) :
	rect(rectangle), type(type), listener(listener) {
}

Collider::~Collider() {
	listener = nullptr;
}

void Collider::SetPos(int x, int y) {
	rect.x = x;
	rect.y = y;
}

bool Collider::Intersects(const SDL_Rect& r) const {
	// or just code it differently
	return SDL_HasIntersection(&r, &rect);
}
