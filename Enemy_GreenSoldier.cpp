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
	initAnimations();


	//Left Right movement
	//path.PushBack({ -0.5f, 0 }, 200, &botAnimLeft);
	//path.PushBack({ 0.5f, 0 }, 200, &botAnimRight);

	//Testing Waking Movement
	path.PushBack({ -0.5f,	0	 }, 50, &botLeftWalk);
	path.PushBack({ -0.5f,	0.5  }, 50, &botDownLeftWalk);
	path.PushBack({		0,	0.5  }, 50, &botDownWalk);
	path.PushBack({ 0.5f,	0.5	 }, 50, &botDownRightWalk);
	path.PushBack({ 0.5f,	0	 }, 50, &botRightWalk);
	path.PushBack({	0.5f,	-0.5 }, 50, &botUpRightWalk);
	path.PushBack({		0,	-0.5 }, 50, &botUpWalk);
	path.PushBack({ -0.5f,	-0.5 }, 50, &botUpLeftWalk);

	//Testing Crouch Movement
	/*path.PushBack({ -0.5f,	0	 }, 50, &botLeftCrouch);
	path.PushBack({ -0.5f,	0.5  }, 50, &botDownLeftCrouch);
	path.PushBack({		0,	0.5  }, 50, &botDownCrouch);
	path.PushBack({ 0.5f,	0.5	 }, 50, &botDownRightCrouch);
	path.PushBack({ 0.5f,	0	 }, 50, &botRightCrouch);
	path.PushBack({	0.5f,	-0.5 }, 50, &botUpRightCrouch);
	path.PushBack({		0,	-0.5 }, 50, &botUpCrouch);
	path.PushBack({ -0.5f,	-0.5 }, 50, &botUpLeftCrouch);*/

	//collider = App->collisions->AddCollider({ 0, 0, 36, 72 }, Collider::Type::ENEMY, (Module*)App->enemies);
	collider = App->collisions->AddCollider({ 0, 0, 32, 64 }, Collider::Type::ENEMY, (Module*)App->enemies);
	this->behaviour = behaviour;
}

void Enemy_GreenSoldier::initAnimations()
{
	//Old animations

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

	//New animations

	//Up Walk
	topUpWalk.PushBack({ 0, 128 - 1,32,32 });
	topUpWalk.PushBack({ 32,128 - 1,32,32 });
	topUpWalk.PushBack({ 64,128 - 1,32,32 });
	topUpWalk.speed = 0.2f;
	topUpWalk.pingpong = true;

	botUpWalk.PushBack({ 96, 0,32,32 });
	botUpWalk.PushBack({ 128,0,32,32 });
	botUpWalk.PushBack({ 160,0,32,32 });
	botUpWalk.PushBack({ 192,0,32,32 });
	botUpWalk.PushBack({ 224,0,32,32 });
	botUpWalk.speed = 0.2f;
	botUpWalk.pingpong = true;

	//Up Left Walk
	topUpLeftWalk.PushBack({ 0, 160,32,32 });
	topUpLeftWalk.PushBack({ 32,160,32,32 });
	topUpLeftWalk.PushBack({ 64,160,32,32 });
	topUpLeftWalk.speed = 0.2f;
	topUpLeftWalk.pingpong = true;

	botUpLeftWalk.PushBack({ 96, 224,32,32 });
	botUpLeftWalk.PushBack({ 128,224,32,32 });
	botUpLeftWalk.PushBack({ 160,224,32,32 });
	botUpLeftWalk.PushBack({ 192,224,32,32 });
	botUpLeftWalk.PushBack({ 224,224,32,32 });
	botUpLeftWalk.speed = 0.2f;
	botUpLeftWalk.pingpong = true;

	//Left Walk
	topLeftWalk.PushBack({ 0, 192,32,32 });
	topLeftWalk.PushBack({ 32,192,32,32 });
	topLeftWalk.PushBack({ 64,192,32,32 });
	topLeftWalk.speed = 0.2f;
	topLeftWalk.pingpong = true;

	botLeftWalk.PushBack({ 96, 192,32,32 });
	botLeftWalk.PushBack({ 128,192,32,32 });
	botLeftWalk.PushBack({ 160,192,32,32 });
	botLeftWalk.PushBack({ 192,192,32,32 });
	botLeftWalk.PushBack({ 224,192,32,32 });
	botLeftWalk.speed = 0.2f;
	botLeftWalk.pingpong = true;

	//Down Left Walk
	topDownLeftWalk.PushBack({ 0, 224,32,32 });
	topDownLeftWalk.PushBack({ 32,224,32,32 });
	topDownLeftWalk.PushBack({ 64,224,32,32 });
	topDownLeftWalk.speed = 0.2f;
	topDownLeftWalk.pingpong = true;

	botDownLeftWalk.PushBack({ 96, 160,32,32 });
	botDownLeftWalk.PushBack({ 128,160,32,32 });
	botDownLeftWalk.PushBack({ 160,160,32,32 });
	botDownLeftWalk.PushBack({ 192,160,32,32 });
	botDownLeftWalk.PushBack({ 224,160,32,32 });
	botDownLeftWalk.speed = 0.2f;
	botDownLeftWalk.pingpong = true;

	//Down Walk
	topDownWalk.PushBack({ 0, 0,32,32 });
	topDownWalk.PushBack({ 32,0,32,32 });
	topDownWalk.PushBack({ 64,0,32,32 });
	topDownWalk.speed = 0.2f;
	topDownWalk.pingpong = true;

	botDownWalk.PushBack({ 96, 128,32,32 });
	botDownWalk.PushBack({ 128,128,32,32 });
	botDownWalk.PushBack({ 160,128,32,32 });
	botDownWalk.PushBack({ 192,128,32,32 });
	botDownWalk.PushBack({ 224,128,32,32 });
	botDownWalk.speed = 0.2f;
	botDownWalk.pingpong = true;

	//Down Right Walk
	topDownRightWalk.PushBack({ 0, 32,32,32 });
	topDownRightWalk.PushBack({ 32,32,32,32 });
	topDownRightWalk.PushBack({ 64,32,32,32 });
	topDownRightWalk.speed = 0.2f;
	topDownRightWalk.pingpong = true;

	botDownRightWalk.PushBack({ 96, 96,32,32 });
	botDownRightWalk.PushBack({ 128,96,32,32 });
	botDownRightWalk.PushBack({ 160,96,32,32 });
	botDownRightWalk.PushBack({ 192,96,32,32 });
	botDownRightWalk.PushBack({ 224,96,32,32 });
	botDownRightWalk.speed = 0.2f;
	botDownRightWalk.pingpong = true;

	//Right Walk
	topRightWalk.PushBack({ 0, 64,32,32 });
	topRightWalk.PushBack({ 32,64,32,32 });
	topRightWalk.PushBack({ 64,64,32,32 });
	topRightWalk.speed = 0.2f;
	topRightWalk.pingpong = true;

	botRightWalk.PushBack({ 96, 64,32,32 });
	botRightWalk.PushBack({ 128,64,32,32 });
	botRightWalk.PushBack({ 160,64,32,32 });
	botRightWalk.PushBack({ 192,64,32,32 });
	botRightWalk.PushBack({ 224,64,32,32 });
	botRightWalk.speed = 0.2f;
	botRightWalk.pingpong = true;

	//Up Right Walk
	topUpRightWalk.PushBack({ 0, 96,32,32 });
	topUpRightWalk.PushBack({ 32,96,32,32 });
	topUpRightWalk.PushBack({ 64,96,32,32 });
	topUpRightWalk.speed = 0.2f;
	topUpRightWalk.pingpong = true;

	botUpRightWalk.PushBack({ 96, 32,32,32 });
	botUpRightWalk.PushBack({ 128,32,32,32 });
	botUpRightWalk.PushBack({ 160,32,32,32 });
	botUpRightWalk.PushBack({ 192,32,32,32 });
	botUpRightWalk.PushBack({ 224,32,32,32 });
	botUpRightWalk.speed = 0.2f;
	botUpRightWalk.pingpong = true;

	//Up Idle Crouch
	topUpCrouch.PushBack({ 256, 256,32,32 });
	botUpCrouch.PushBack({ 256, 288,32,32 });

	//Up Left Idle Crouch
	topUpLeftCrouch.PushBack({ 480, 256,32,32 });
	botUpLeftCrouch.PushBack({ 480, 288,32,32 });

	//Left Idle Crouch
	topLeftCrouch.PushBack({ 448, 256,32,32 });
	botLeftCrouch.PushBack({ 448, 288,32,32 });

	//Down Left Idle Crouch
	topDownLeftCrouch.PushBack({ 416, 256,32,32 });
	botDownLeftCrouch.PushBack({ 416, 288,32,32 });

	//Down Idle Crouch
	topDownCrouch.PushBack({ 384, 256,32,32 });
	botDownCrouch.PushBack({ 384, 288,32,32 });

	//Down Right Idle Crouch
	topDownRightCrouch.PushBack({ 352, 256,32,32 });
	botDownRightCrouch.PushBack({ 352, 288,32,32 });

	//Right Idle Crouch
	topRightCrouch.PushBack({ 320, 256,32,32 });
	botRightCrouch.PushBack({ 320, 288,32,32 });

	//Up Right Idle Crouch
	topUpRightCrouch.PushBack({ 288, 256,32,32 });
	botUpRightCrouch.PushBack({ 288, 288,32,32 });
}

void Enemy_GreenSoldier::syncAnimations()
{
	currentAnimBot = path.GetCurrentAnimation();

	if (currentAnimBot == &botUpWalk)
		currentAnimTop = &topUpWalk;

	else if (currentAnimBot == &botUpLeftWalk)
		currentAnimTop = &topUpLeftWalk;

	else if (currentAnimBot == &botLeftWalk)
		currentAnimTop = &topLeftWalk;

	else if (currentAnimBot == &botDownLeftWalk)
		currentAnimTop = &topDownLeftWalk;

	else if (currentAnimBot == &botDownWalk)
		currentAnimTop = &topDownWalk;

	else if (currentAnimBot == &botDownRightWalk)
		currentAnimTop = &topDownRightWalk;

	else if (currentAnimBot == &botRightWalk)
		currentAnimTop = &topRightWalk;

	else if (currentAnimBot == &botUpRightWalk)
		currentAnimTop = &topUpRightWalk;

	else if (currentAnimBot == &botUpCrouch)
		currentAnimTop = &topUpCrouch;

	else if (currentAnimBot == &botUpLeftCrouch)
		currentAnimTop = &topUpLeftCrouch;

	else if (currentAnimBot == &botLeftCrouch)
		currentAnimTop = &topLeftCrouch;

	else if (currentAnimBot == &botDownLeftCrouch)
		currentAnimTop = &topDownLeftCrouch;

	else if (currentAnimBot == &botDownCrouch)
		currentAnimTop = &topDownCrouch;

	else if (currentAnimBot == &botDownRightCrouch)
		currentAnimTop = &topDownRightCrouch;

	else if (currentAnimBot == &botRightCrouch)
		currentAnimTop = &topRightCrouch;

	else if (currentAnimBot == &botUpRightCrouch)
		currentAnimTop = &topUpRightCrouch;

}

void Enemy_GreenSoldier::Update()
{
	path.Update();
	syncAnimations();

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