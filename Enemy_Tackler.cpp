#include "Enemy_Tackler.h"

#include "Application.h"
#include "ModuleCollisions.h"
#include "ModuleAudio.h"
#include "ModulePlayer.h"
#include "ModuleEnemies.h" //(Testing)
#include "ModuleParticles.h"

#define GREENSOLDIER_SCORE 100
Enemy_Tackler::Enemy_Tackler(int x, int y) : Enemy(x, y)
{
	runningTopAnim.PushBack({ 0, 0,32,32 });
	runningTopAnim.PushBack({ 32, 0,32,32 });
	runningTopAnim.PushBack({ 64, 0,32,32 });
	runningTopAnim.speed = 0.2f;
	runningTopAnim.pingpong = true;
	currentAnimTop = &runningTopAnim;

	runningBotAnim.PushBack({ 96, 128,32,32 });
	runningBotAnim.PushBack({ 128,128,32,32 });
	runningBotAnim.PushBack({ 160,128,32,32 });
	runningBotAnim.PushBack({ 192,128,32,32 });
	runningBotAnim.PushBack({ 224,128,32,32 });
	runningBotAnim.speed = 0.2f;
	runningBotAnim.pingpong = true;
	currentAnimBot = &runningBotAnim;


	path.PushBack({ 0, 1 },100);

	collider = App->collisions->AddCollider({ 0, 0, 32, 64 }, Collider::Type::ENEMY, (Module*)App->enemies);
}

void Enemy_Tackler::Update()
{
	path.Update();

	position = spawnPos + path.GetRelativePosition();

	// Call to the base class. It must be called at the end
	// It will update the collider depending on the position


	if (position.y >= App->player->position.y + 300)
	{
		App->particles->AddParticle(App->particles->shot_right, position.x -20, position.y, Collider::Type::PLAYER_SHOT); //Harakiry
	}
	Enemy::Update();
}

void Enemy_Tackler::OnCollision(Collider* collider) {
	if (collider->type == Collider::Type::PLAYER_SHOT || collider->type == Collider::Type::PLAYER) {

		App->audio->PlayFx(enemyDeadFx);
		App->player->score += GREENSOLDIER_SCORE;

		switch (looking)
		{
		case Directions::UP:
			App->particles->greenDeathAnimTop.speed = { 0, 1 };
			App->particles->greenDeathAnimBot.speed = { 0, 1 };
			break;
		case Directions::UP_RIGHT:
			App->particles->greenDeathAnimTop.speed = { -1, 1 };
			App->particles->greenDeathAnimBot.speed = { -1, 1 };
			break;
		case Directions::UP_LEFT:
			App->particles->greenDeathAnimTop.speed = { 1, 1 };
			App->particles->greenDeathAnimBot.speed = { 1, 1 };
			break;
		case Directions::DOWN:
			App->particles->greenDeathAnimTop.speed = { 0, -1 };
			App->particles->greenDeathAnimBot.speed = { 0, -1 };
			break;
		case Directions::DOWN_RIGHT:
			App->particles->greenDeathAnimTop.speed = { -1, -1 };
			App->particles->greenDeathAnimBot.speed = { -1, -1 };
			break;
		case Directions::DOWN_LEFT:
			App->particles->greenDeathAnimTop.speed = { 1, -1 };
			App->particles->greenDeathAnimBot.speed = { 1, -1 };
			break;
		case Directions::RIGHT:
			App->particles->greenDeathAnimTop.speed = { -1, 0 };
			App->particles->greenDeathAnimBot.speed = { -1, 0 };
			break;
		case Directions::LEFT:
			App->particles->greenDeathAnimTop.speed = { 1, 0 };
			App->particles->greenDeathAnimBot.speed = { 1, 0 };
			break;
		}

		App->particles->AddParticle(App->particles->greenDeathAnimTop, position.x, position.y + 1, Collider::Type::NONE);
		App->particles->AddParticle(App->particles->greenDeathAnimBot, position.x, position.y + 32, Collider::Type::NONE);
	}
}

void Enemy_Tackler::Shoot() { return; }

