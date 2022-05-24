#include "Breakable_Barbed_1.h"

#include "Application.h"
#include "ModuleCollisions.h"
#include "ModuleAudio.h"

#include "ModulePlayer.h"

Breakable_Barbed_1::Breakable_Barbed_1(int x, int y) : Breakable(x, y) {
	collider = App->collisions->AddCollider({ 0, 0, 32, 32 }, Collider::Type::BREAKABLE, (Module*)App->breakables);
	animation.PushBack({ 0,32,32,32 });
	currentAnim = &animation;
}

void Breakable_Barbed_1::Update() {
	Breakable::Update();
}

void Breakable_Barbed_1::OnCollision(Collider* collider) {

}
