#include "Breakable_Barricade_H.h"

#include "Application.h"
#include "ModuleCollisions.h"
#include "ModuleAudio.h"

#include "ModulePlayer.h"

Breakable_Barricade_H::Breakable_Barricade_H(int x, int y) : Breakable(x, y) {
	collider = App->collisions->AddCollider({ 0, 0, 32, 32 }, Collider::Type::BREAKABLE, (Module*)App->breakables);
	animation.PushBack({ 0,0,32,32 });
	currentAnim = &animation;
}

void Breakable_Barricade_H::Update() {
	Breakable::Update();
}

void Breakable_Barricade_H::OnCollision(Collider* collider) {

}
