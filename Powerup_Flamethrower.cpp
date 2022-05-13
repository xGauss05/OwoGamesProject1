#include "Powerup_Flamethrower.h"

#include "Application.h"
#include "ModuleCollisions.h"
#include "ModuleAudio.h"

#include "ModulePlayer.h"

Powerup_Flamethrower::Powerup_Flamethrower(int x, int y) : Powerup(x, y) {
	collider = App->collisions->AddCollider({ 0, 0, 23, 23 }, Collider::Type::POWER_UP, (Module*)App->powerups);
	animation.PushBack({ 0, 132, 22, 23 });
	animation.PushBack({ 32, 132, 22, 23 });
	animation.PushBack({ 64, 132, 22, 23 });
	animation.PushBack({ 32, 132, 22, 23 });
	animation.speed = 0.05f;
	animation.loop = true;
	currentAnim = &animation;

}

void Powerup_Flamethrower::Update() {
	Powerup::Update();
}

void Powerup_Flamethrower::OnCollision(Collider* collider) {
	App->audio->PlayFx(pickUpFx);
	App->player->weapon = Weapon::FLAMETHROWER;
}
