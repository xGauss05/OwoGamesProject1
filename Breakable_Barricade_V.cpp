#include "Breakable_Barricade_v.h"

#include "Application.h"
#include "ModuleCollisions.h"
#include "ModuleAudio.h"

#include "ModulePlayer.h"

Breakable_Barricade_V::Breakable_Barricade_V(int x, int y) : Breakable(x, y) {
	collider = App->collisions->AddCollider({ 0, 0, 32, 32 }, Collider::Type::BREAKABLE, (Module*)App->breakables);
	animation.PushBack({ 0,0,32,32 });
	currentAnim = &animation;
}

void Breakable_Barricade_V::Update() {
	Breakable::Update();
}

void Breakable_Barricade_V::OnCollision(Collider* collider) {

}
