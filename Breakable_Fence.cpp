#include "Breakable_Fence.h"

#include "Application.h"
#include "ModuleCollisions.h"
#include "ModuleAudio.h"

#include "ModulePlayer.h"

Breakable_Fence::Breakable_Fence(int x, int y) : Breakable(x, y) {
	collider = App->collisions->AddCollider({ 0, 0, 23, 23 }, Collider::Type::BREAKABLE, (Module*)App->breakables);


}

void Breakable_Fence::Update() {
	Breakable::Update();
}

void Breakable_Fence::OnCollision(Collider* collider) {

}
