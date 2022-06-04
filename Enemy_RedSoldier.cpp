#include "Enemy_RedSoldier.h"

#include "Application.h"
#include "ModuleCollisions.h"
#include "ModuleAudio.h"

#include "ModulePlayer.h"
#include "ModuleParticles.h"
#include "ModuleEnemies.h" //(Testing)
#include "ModulePowerup.h" //(Testing)

#define REDSOLDIER_SCORE 300;

Enemy_RedSoldier::Enemy_RedSoldier(int x, int y, ushort behaviour) : Enemy(x, y)
{
	this->behaviour = behaviour;

	topAnim.PushBack({ 0,0,32,32 });
	currentAnimTop = &topAnim;

	botAnim.PushBack({ 160,128,32,32 });
	currentAnimBot = &botAnim;

	#pragma region Animations

	topUpCrouch.PushBack({ 256,256,32,32 });
	topUpRightCrouch.PushBack({ 288,256,32,32 });
	topRightCrouch.PushBack({ 320,256,32,32 });
	topDownRightCrouch.PushBack({ 352,256,32,32 });
	topDownCrouch.PushBack({ 384,256,32,32 });
	topDownLeftCrouch.PushBack({ 416,256,32,32 });
	topLeftCrouch.PushBack({ 448,256,32,32 });
	topUpLeftCrouch.PushBack({ 480,256,32,32 });
	currentAnimTop = &topDownCrouch;

	botUpCrouch.PushBack({ 256,288,32,32 });
	botUpRightCrouch.PushBack({ 288,288,32,32 });
	botRightCrouch.PushBack({ 320,288,32,32 });
	botDownRightCrouch.PushBack({ 352,288,32,32 });
	botDownCrouch.PushBack({ 384,288,32,32 });
	botDownLeftCrouch.PushBack({ 416,288,32,32 });
	botLeftCrouch.PushBack({ 448,288,32,32 });
	botUpLeftCrouch.PushBack({ 480,288,32,32 });
	currentAnimBot = &botDownCrouch;


	//Up Shoot
	topUpShoot.PushBack({ 256, 320,32,32 });
	botUpShoot.PushBack({ 256, 352,32,32 });

	//Up Left Shoot
	topUpLeftShoot.PushBack({ 480, 320,32,32 });
	botUpLeftShoot.PushBack({ 480, 352,32,32 });

	//Left Shoot
	topLeftShoot.PushBack({ 448, 320,32,32 });
	botLeftShoot.PushBack({ 448, 352,32,32 });

	//Down Left Shoot
	topDownLeftShoot.PushBack({ 416, 320,32,32 });
	botDownLeftShoot.PushBack({ 416, 352,32,32 });

	//Down Shoot
	topDownShoot.PushBack({ 384, 320,32,32 });
	botDownShoot.PushBack({ 384, 352,32,32 });

	//Down Right Shoot
	topDownRightShoot.PushBack({ 352, 320,32,32 });
	botDownRightShoot.PushBack({ 352, 352,32,32 });

	//Right Shoot
	topRightShoot.PushBack({ 320, 320,32,32 });
	botRightShoot.PushBack({ 320, 352,32,32 });

	//Up Right Shoot
	topUpRightShoot.PushBack({ 288, 320,32,32 });
	botUpRightShoot.PushBack({ 288, 352,32,32 });

#pragma endregion

	path.PushBack({ 0, -1.0f }, 50);
	path.PushBack({ 0, 1.0f }, 50);


	collider = App->collisions->AddCollider({ 0, 0, 32, 64 }, Collider::Type::ENEMY, (Module*)App->enemies);
}

void Enemy_RedSoldier::Update()
{
	#pragma region Update Animation

	if (!burst)
	{
		switch (looking)
		{
		case Directions::UP:
			currentAnimTop = &topUpCrouch;
			currentAnimBot = &botUpCrouch;
			break;

		case Directions::UP_RIGHT:
			currentAnimTop = &topUpRightCrouch;
			currentAnimBot = &botUpRightCrouch;
			break;

		case Directions::UP_LEFT:
			currentAnimTop = &topUpLeftCrouch;
			currentAnimBot = &botUpLeftCrouch;
			break;

		case Directions::RIGHT:
			currentAnimTop = &topRightCrouch;
			currentAnimBot = &botRightCrouch;
			break;

		case Directions::LEFT:
			currentAnimTop = &topLeftCrouch;
			currentAnimBot = &botLeftCrouch;
			break;

		case Directions::DOWN_RIGHT:
			currentAnimTop = &topDownRightCrouch;
			currentAnimBot = &botDownRightCrouch;
			break;
		case Directions::DOWN_LEFT:
			currentAnimTop = &topDownLeftCrouch;
			currentAnimBot = &botDownLeftCrouch;
			break;
		case Directions::DOWN:
			currentAnimTop = &topDownCrouch;
			currentAnimBot = &botDownCrouch;
			break;
		}
	}

#pragma endregion

	//path.Update();
	//position = spawnPos + path.GetRelativePosition();
	Shoot();

	// Call to the base class. It must be called at the end
	// It will update the collider depending on the position
	Enemy::Update();
}

void Enemy_RedSoldier::OnCollision(Collider* collider) {
	if (collider->type == Collider::Type::PLAYER_SHOT || collider->type == Collider::Type::PLAYER || collider->type == Collider::Type::EXPLOSION) {

		App->audio->PlayFx(enemyDeadFx);
		App->player->score += REDSOLDIER_SCORE;

		if (behaviour == 0)
			App->powerups->AddPowerup(POWERUP_TYPE::HEAVY_RIFLE, position.x, position.y);
		else
			App->powerups->AddPowerup(POWERUP_TYPE::FLAMETHROWER, position.x, position.y);

		switch (looking)
		{
		case Directions::UP:
			App->particles->redDeathAnimTop.speed = { 0, 1 };
			App->particles->redDeathAnimBot.speed = { 0, 1 };
			break;
		case Directions::UP_RIGHT:
			App->particles->redDeathAnimTop.speed = { -1, 1 };
			App->particles->redDeathAnimBot.speed = { -1, 1 };
			break;
		case Directions::UP_LEFT:
			App->particles->greenDeathAnimTop.speed = { 1, 1 };
			App->particles->greenDeathAnimBot.speed = { 1, 1 };
			break;
		case Directions::DOWN:
			App->particles->redDeathAnimTop.speed = { 0, -1 };
			App->particles->redDeathAnimBot.speed = { 0, -1 };
			break;
		case Directions::DOWN_RIGHT:
			App->particles->redDeathAnimTop.speed = { -1, -1 };
			App->particles->redDeathAnimBot.speed = { -1, -1 };
			break;
		case Directions::DOWN_LEFT:
			App->particles->redDeathAnimTop.speed = { 1, -1 };
			App->particles->redDeathAnimBot.speed = { 1, -1 };
			break;
		case Directions::RIGHT:
			App->particles->redDeathAnimTop.speed = { -1, 0 };
			App->particles->redDeathAnimBot.speed = { -1, 0 };
			break;
		case Directions::LEFT:
			App->particles->redDeathAnimTop.speed = { 1, 0 };
			App->particles->redDeathAnimBot.speed = { 1, 0 };
			break;
		}

		App->particles->AddParticle(App->particles->redDeathAnimTop, position.x, position.y + 2, Collider::Type::NONE);
		App->particles->AddParticle(App->particles->redDeathAnimBot, position.x, position.y + 32, Collider::Type::NONE);
	}
}

void Enemy_RedSoldier::Shoot() { Burst(); }

void Enemy_RedSoldier::Burst()
{
	if (!burst)
	{
		if (burstDelay >= 100)
		{
			burstDelay = 0;
			burst = true;
			shotCount++;
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
				App->particles->enemy_shot.speed.y = -SHOT_SPEED_STRAIGHT;
				currentAnimTop = &topUpShoot;
				currentAnimBot = &botUpShoot;
				App->particles->AddParticle(App->particles->enemy_shot, position.x + 21, position.y + 5, Collider::Type::ENEMY_SHOT);
				break;
			case Directions::UP_RIGHT:
				App->particles->enemy_shot.speed.x = SHOT_SPEED_DIAGONAL;
				App->particles->enemy_shot.speed.y = -SHOT_SPEED_DIAGONAL;
				currentAnimTop = &topUpRightShoot;
				currentAnimBot = &botUpRightShoot;
				App->particles->AddParticle(App->particles->enemy_shot, position.x + 28, position.y + 11, Collider::Type::ENEMY_SHOT);
				break;
			case Directions::UP_LEFT:
				App->particles->enemy_shot.speed.x = -SHOT_SPEED_DIAGONAL;
				App->particles->enemy_shot.speed.y = -SHOT_SPEED_DIAGONAL;
				currentAnimTop = &topUpLeftShoot;
				currentAnimBot = &botUpLeftShoot;
				App->particles->AddParticle(App->particles->enemy_shot, position.x + 6, position.y + 8, Collider::Type::ENEMY_SHOT);
				break;
			case Directions::DOWN:
				App->particles->enemy_shot.speed.x = 0;
				App->particles->enemy_shot.speed.y = SHOT_SPEED_STRAIGHT;
				currentAnimTop = &topDownShoot;
				currentAnimBot = &botDownShoot;
				App->particles->AddParticle(App->particles->enemy_shot, position.x + 9, position.y + 46, Collider::Type::ENEMY_SHOT);
				break;
			case Directions::DOWN_RIGHT:
				App->particles->enemy_shot.speed.x = SHOT_SPEED_DIAGONAL;
				App->particles->enemy_shot.speed.y = SHOT_SPEED_DIAGONAL;
				currentAnimTop = &topDownRightShoot;
				currentAnimBot = &botDownRightShoot;
				App->particles->AddParticle(App->particles->enemy_shot, position.x + 27, position.y + 41, Collider::Type::ENEMY_SHOT);
				break;
			case Directions::DOWN_LEFT:
				App->particles->enemy_shot.speed.x = -SHOT_SPEED_DIAGONAL;
				App->particles->enemy_shot.speed.y = SHOT_SPEED_DIAGONAL;
				currentAnimTop = &topDownLeftShoot;
				currentAnimBot = &botDownLeftShoot;
				App->particles->AddParticle(App->particles->enemy_shot, position.x - 1, position.y + 33, Collider::Type::ENEMY_SHOT);
				break;
			case Directions::RIGHT:
				App->particles->enemy_shot.speed.x = SHOT_SPEED_STRAIGHT;
				App->particles->enemy_shot.speed.y = 0;
				currentAnimTop = &topRightShoot;
				currentAnimBot = &botRightShoot;
				App->particles->AddParticle(App->particles->enemy_shot, position.x + 29, position.y + 24, Collider::Type::ENEMY_SHOT);
				break;
			case Directions::LEFT:
				App->particles->enemy_shot.speed.x = -SHOT_SPEED_STRAIGHT;
				App->particles->enemy_shot.speed.y = 0;
				currentAnimTop = &topLeftShoot;
				currentAnimBot = &botLeftShoot;
				App->particles->AddParticle(App->particles->enemy_shot, position.x, position.y + 21, Collider::Type::ENEMY_SHOT);
				break;
			}

			//App->particles->AddParticle(App->particles->enemy_shot, position.x + 16, position.y + 32, Collider::Type::ENEMY_SHOT);
			App->audio->PlayFx(enemyShotFx);
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

