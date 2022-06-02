#include "Enemy_GreenSoldier.h"

#include "Application.h"
#include "ModuleCollisions.h"
#include "ModuleAudio.h"
#include "ModulePlayer.h"
#include "ModuleParticles.h"
#include "ModuleEnemies.h" //(Testing)

#include "ModuleFonts.h"
#include <string>
using namespace std;

#define GREENSOLDIER_SCORE 100
Enemy_GreenSoldier::Enemy_GreenSoldier(int x, int y, ushort behaviour) : Enemy(x, y)
{
	//if (behaviour == 0 || behaviour == 1)
	//{
	//
	//}

	defaultTopAnim.PushBack({ 0, 0,32,32 });
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

	path.PushBack({ -0.5f, 0 }, 200, &botAnimLeft);
	path.PushBack({ 0.5f, 0 }, 200, &botAnimRight);


	//collider = App->collisions->AddCollider({ 0, 0, 36, 72 }, Collider::Type::ENEMY, (Module*)App->enemies);
	collider = App->collisions->AddCollider({ 0, 0, 32, 64 }, Collider::Type::ENEMY, (Module*)App->enemies);
	this->behaviour = behaviour;
}

void Enemy_GreenSoldier::Update()
{
	path.Update();
	currentAnimBot = path.GetCurrentAnimation();

	position = spawnPos + path.GetRelativePosition();

	#pragma region Update Direction

	// Down
	if (degrees > 247.5 && degrees < 292.5)
		looking = Directions::UP;

	// Down right
	else if (degrees > 292.5 && degrees < 337.5)
		looking = Directions::UP_RIGHT;

	// Down left
	else if (degrees > 202.5 && degrees < 247.5)
		looking = Directions::UP_LEFT;

	// Right
	else if (degrees > 337.5 || degrees < 22.5)
		looking = Directions::RIGHT;

	// Left
	else if (degrees > 157.5 && degrees < 202.5)
		looking = Directions::LEFT;

	// Up right
	else if (degrees > 22.5 && degrees < 67.5)
		looking = Directions::DOWN_RIGHT;

	// Up left
	else if (degrees > 112.5 && degrees < 157.5)
		looking = Directions::DOWN_LEFT;

	// Up
	else if (degrees > 67.5 && degrees < 112.5)
		looking = Directions::DOWN;

#pragma endregion


	//As every part of the path will have its own animation, you can define certain behaviours for certain parts of the path (animations).
	if (currentAnimBot == &botAnimLeft)
	{
		Shoot();
	}

	// Call to the base class. It must be called at the end
	// It will update the collider depending on the position
	Enemy::Update();
}

void Enemy_GreenSoldier::OnCollision(Collider* collider) {
	if (collider->type == Collider::Type::PLAYER_SHOT) {
		App->audio->PlayFx(enemyDeadFx);
		App->player->score += 100;

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

		App->particles->AddParticle(App->particles->greenDeathAnimTop, position.x, position.y + 5, Collider::Type::NONE);
		App->particles->AddParticle(App->particles->greenDeathAnimBot, position.x, position.y + 32, Collider::Type::NONE);
	}
}

void Enemy_GreenSoldier::Shoot()
{
	switch (behaviour)
	{
	case 0:
		Burst();
		break;

	case 1:
		Grenade();
		break;
	}
}


void Enemy_GreenSoldier::Burst()
{
	if (!burst)
	{
		if (burstDelay >= 100)
		{
			burstDelay = 0;
			burst = true;
		}
		burstDelay++;
	}

	if (burst)
	{
		if (shootdelay >= 10)
		{
			shootdelay = 0;
			burstCount++;

#pragma region Shot
			switch (looking)
			{
			case Directions::UP:
				App->particles->enemy_shot.speed.x = 0;
				App->particles->enemy_shot.speed.y = -2;
				break;
			case Directions::UP_RIGHT:
				App->particles->enemy_shot.speed.x = 2;
				App->particles->enemy_shot.speed.y = -2;
				break;
			case Directions::UP_LEFT:
				App->particles->enemy_shot.speed.x = -2;
				App->particles->enemy_shot.speed.y = -2;
				break;
			case Directions::DOWN:
				App->particles->enemy_shot.speed.x = 0;
				App->particles->enemy_shot.speed.y = 2;
				break;
			case Directions::DOWN_RIGHT:
				App->particles->enemy_shot.speed.x = 2;
				App->particles->enemy_shot.speed.y = 2;
				break;
			case Directions::DOWN_LEFT:
				App->particles->enemy_shot.speed.x = -2;
				App->particles->enemy_shot.speed.y = 2;
				break;
			case Directions::RIGHT:
				App->particles->enemy_shot.speed.x = 2;
				App->particles->enemy_shot.speed.y = 0;
				break;
			case Directions::LEFT:
				App->particles->enemy_shot.speed.x = -2;
				App->particles->enemy_shot.speed.y = 0;
				break;
			}

			App->particles->AddParticle(App->particles->enemy_shot, position.x + 16, position.y + 32, Collider::Type::ENEMY_SHOT);
#pragma endregion
		}
		shootdelay++;

		if (burstCount >= 3)
		{
			burstCount = 0;
			burst = false;
		}
	}
}

void Enemy_GreenSoldier::Grenade()
{
	if (grenadeDelay >= 100)
	{
		switch (looking)
		{
		case Directions::UP:
			App->particles->grenade.speed.x = 0;
			App->particles->grenade.speed.y = -2;
			break;
		case Directions::UP_RIGHT:
			App->particles->grenade.speed.x = 2;
			App->particles->grenade.speed.y = -2;
			break;
		case Directions::UP_LEFT:
			App->particles->grenade.speed.x = -2;
			App->particles->grenade.speed.y = -2;
			break;
		case Directions::DOWN:
			App->particles->grenade.speed.x = 0;
			App->particles->grenade.speed.y = 2;
			break;
		case Directions::DOWN_RIGHT:
			App->particles->grenade.speed.x = 2;
			App->particles->grenade.speed.y = 2;
			break;
		case Directions::DOWN_LEFT:
			App->particles->grenade.speed.x = -2;
			App->particles->grenade.speed.y = 2;
			break;
		case Directions::RIGHT:
			App->particles->grenade.speed.x = 2;
			App->particles->grenade.speed.y = 0;
			break;
		case Directions::LEFT:
			App->particles->grenade.speed.x = -2;
			App->particles->grenade.speed.y = 0;
			break;
		}
		App->particles->AddParticle(App->particles->grenade, position.x + 13, position.y, Collider::Type::NONE);
		grenadeDelay = 0;
	}
	grenadeDelay++;
}