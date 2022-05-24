#include "Breakable_Barbed_2.h"

#include "Application.h"
#include "ModuleCollisions.h"
#include "ModuleAudio.h"

#include "ModulePlayer.h"

Breakable_Barbed_2::Breakable_Barbed_2(int x, int y) : Breakable(x, y) {
	collider = App->collisions->AddCollider({ 0, 0, 32, 32 }, Collider::Type::BREAKABLE, (Module*)App->breakables);
	animation.PushBack({ 32,32,32,32 });
	currentAnim = &animation;
}

void Breakable_Barbed_2::Update() {
	Breakable::Update();
}

void Breakable_Barbed_2::OnCollision(Collider* collider) {

}
