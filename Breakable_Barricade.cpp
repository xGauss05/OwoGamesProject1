#include "Breakable_Barricade.h"

#include "Application.h"
#include "ModuleCollisions.h"
#include "ModuleAudio.h"

#include "ModulePlayer.h"

Breakable_Barricade::Breakable_Barricade(int x, int y) : Breakable(x, y) {
	collider = App->collisions->AddCollider({ 0, 0, 32, 32 }, Collider::Type::BREAKABLE, (Module*)App->breakables);
	animation.PushBack({ 0,0,32,32 });
	currentAnim = &animation;
}

void Breakable_Barricade::Update() {
	Breakable::Update();
}

void Breakable_Barricade::OnCollision(Collider* collider) {

}
