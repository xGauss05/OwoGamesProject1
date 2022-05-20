#include "Breakable_Bridge.h"

#include "Application.h"
#include "ModuleCollisions.h"
#include "ModuleAudio.h"

#include "ModulePlayer.h"

Breakable_Bridge::Breakable_Bridge(int x, int y) : Breakable(x, y) {
	collider = App->collisions->AddCollider({ 0, 0, 23, 23 }, Collider::Type::BREAKABLE, (Module*)App->breakables);


}

void Breakable_Bridge::Update() {
	Breakable::Update();
}

void Breakable_Bridge::OnCollision(Collider* collider) {
	if (collider->type == Collider::Type::EXPLOSION) {
		App->collisions->AddCollider({ this->position.x, this->position.y, 23, 23 }, Collider::Type::WATER);
	}
}
