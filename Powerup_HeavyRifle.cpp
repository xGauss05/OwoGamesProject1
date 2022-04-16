#include "Powerup_HeavyRifle.h"

#include "Application.h"
#include "ModuleCollisions.h"
#include "ModuleAudio.h"

#include "ModulePlayer.h"

Powerup_HeavyRifle::Powerup_HeavyRifle(int x, int y) : Powerup(x, y) {

	collider = App->collisions->AddCollider({ 0, 0, 23, 23 }, Collider::Type::POWER_UP, (Module*)App->powerups);
}

void Powerup_HeavyRifle::Update() {
	if (currentAnim != nullptr)
		currentAnim->Update();

	if (collider != nullptr)
		collider->SetPos(position.x, position.y);

	// Call to the base class. It must be called at the end
	// It will update the collider depending on the position
	Powerup::Update();
}

void Powerup_HeavyRifle::OnCollision(Collider* collider) {
	App->audio->PlayFx(pickUpFx);
	App->player->weapon = Weapon::HEAVY_RIFLE;
}
