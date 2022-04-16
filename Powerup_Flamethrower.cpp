#include "Powerup_Flamethrower.h"

#include "Application.h"
#include "ModuleCollisions.h"
#include "ModuleAudio.h"

#include "ModulePlayer.h"

Powerup_Flamethrower::Powerup_Flamethrower(int x, int y) : Powerup(x, y) {
	
	collider = App->collisions->AddCollider({ 0, 0, 23, 23 }, Collider::Type::POWER_UP, (Module*)App->powerups);
}

void Powerup_Flamethrower::Update() {

	position = spawnPos;

	// Call to the base class. It must be called at the end
	// It will update the collider depending on the position
	Powerup::Update();
}

void Powerup_Flamethrower::OnCollision(Collider* collider) {
	App->audio->PlayFx(pickUpFx);
	App->player->weapon = Weapon::HEAVY_RIFLE;
}
