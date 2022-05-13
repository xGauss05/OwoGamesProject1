#include "BossPhase1.h"

#include "Application.h"
#include "ModuleCollisions.h"
#include "ModuleAudio.h"
#include "ModulePlayer.h"
#include "ModuleParticles.h"
#include "ModuleEnemies.h" //(Testing)

#define BOSSPHASE1_SCORE 100

BossPhase1::BossPhase1(int x, int y) : Enemy(x, y)
{
	/*defaultTopAnim.PushBack({ 0, 0,32,32 });
	defaultTopAnim.PushBack({ 32, 0,32,32 });
	defaultTopAnim.PushBack({ 64, 0,32,32 });
	defaultTopAnim.speed = 0.1f;
	defaultTopAnim.pingpong = true;
	currentAnimTop = &defaultTopAnim;

	botAnimLeft.PushBack({ 96, 192,32,32 });
	botAnimLeft.PushBack({ 128,192,32,32 });
	botAnimLeft.PushBack({ 160,192,32,32 });
	botAnimLeft.PushBack({ 192,192,32,32 });
	botAnimLeft.PushBack({ 224,192,32,32 });
	botAnimLeft.speed = 0.2f;
	botAnimLeft.pingpong = true;

	botAnimRight.PushBack({ 96, 64,32,32 });
	botAnimRight.PushBack({ 128,64,32,32 });
	botAnimRight.PushBack({ 160,64,32,32 });
	botAnimRight.PushBack({ 192,64,32,32 });
	botAnimRight.PushBack({ 224,64,32,32 });
	botAnimRight.speed = 0.2f;
	botAnimRight.pingpong = true;
	currentAnimBot = &botAnimLeft;

	path.PushBack({ -0.5f, 0 }, 100, &botAnimLeft);
	path.PushBack({ 0.5f, 0 }, 100, &botAnimRight);
	*/

	//collider = App->collisions->AddCollider({ 0, 0, 36, 72 }, Collider::Type::ENEMY, (Module*)App->enemies);
	collider = App->collisions->AddCollider({ 0, 0, 32, 64 }, Collider::Type::ENEMY, (Module*)App->enemies);
}

void BossPhase1::Update()
{
	path.Update();
	currentAnimBot = path.GetCurrentAnimation();

	position = spawnPos + path.GetRelativePosition();

	Shoot();

	// Call to the base class. It must be called at the end
	// It will update the collider depending on the position
	Enemy::Update();
}

void BossPhase1::OnCollision(Collider* collider) {
	if (collider->type == Collider::Type::PLAYER_SHOT) {
		App->audio->PlayFx(enemyDeadFx);
		App->player->score += 100;
	}
	//App->particles->AddParticle(App->particles->explosion, position.x, position.y);
	//App->audio->PlayFx(enemyDeadFx);
}

void BossPhase1::Shoot()
{
	if (shootdelay >= 50)
	{
		App->particles->AddParticle(App->particles->grenade, position.x + 16, position.y + 32, Collider::Type::ENEMY_SHOT);
		shootdelay = 0;
	}

	shootdelay++;
}
