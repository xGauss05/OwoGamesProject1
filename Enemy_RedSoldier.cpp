#include "Enemy_RedSoldier.h"

#include "Application.h"
#include "ModuleCollisions.h"
#include "ModuleAudio.h"

#include "ModulePlayer.h"
#include "ModuleParticles.h"
#include "ModuleEnemies.h" //(Testing)
#include "ModulePowerup.h" //(Testing)

#define REDSOLDIER_SCORE 300;
Enemy_RedSoldier::Enemy_RedSoldier(int x, int y) : Enemy(x, y)
{
	topAnim.PushBack({ 0,0,32,32 });
	currentAnimTop = &topAnim;

	botAnim.PushBack({ 160,128,32,32 });
	currentAnimBot = &botAnim;

	#pragma region Animations

	topUp.PushBack({ 0,128,32,32 });
	topUpRight.PushBack({ 0,96,32,32 });
	topRight.PushBack({ 0,64,32,32 });
	topDownRight.PushBack({ 0,32,32,32 });
	topDown.PushBack({ 0,0,32,32 });
	topDownLeft.PushBack({ 0,224,32,32 });
	topLeft.PushBack({ 0,192,32,32 });
	topUpLeft.PushBack({ 0,160,32,32 });
	currentAnimTop = &topDown;

	botUp.PushBack({ 160,0,32,32 });
	botUpRight.PushBack({ 160,32,32,32 });
	botRight.PushBack({ 160,64,32,32 });
	botDownRight.PushBack({ 160,96,32,32 });
	botDown.PushBack({ 160,0,32,32 });
	botDownLeft.PushBack({ 160,160,32,32 });
	botLeft.PushBack({ 160,192,32,32 });
	botUpLeft.PushBack({ 160,224,32,32 });
	currentAnimBot = &botDown;

#pragma endregion

	path.PushBack({ 0, -1.0f }, 50);
	path.PushBack({ 0, 1.0f }, 50);


	collider = App->collisions->AddCollider({ 0, 0, 32, 64 }, Collider::Type::ENEMY, (Module*)App->enemies);
}

void Enemy_RedSoldier::Update()
{
	#pragma region Update Animation

	switch (looking)
	{
	case Directions::UP:
		currentAnimTop = &topUp;
		currentAnimBot = &botUp;
		break;

	case Directions::UP_RIGHT:
		currentAnimTop = &topUpRight;
		currentAnimBot = &botUpRight;
		break;

	case Directions::UP_LEFT:
		currentAnimTop = &topUpLeft;
		currentAnimBot = &botUpLeft;
		break;

	case Directions::RIGHT:
		currentAnimTop = &topRight;
		currentAnimBot = &botRight;
		break;

	case Directions::LEFT:
		currentAnimTop = &topLeft;
		currentAnimBot = &botLeft;
		break;

	case Directions::DOWN_RIGHT:
		currentAnimTop = &topDownRight;
		currentAnimBot = &botDownRight;
		break;
	case Directions::DOWN_LEFT:
		currentAnimTop = &topDownLeft;
		currentAnimBot = &botDownLeft;
		break;
	case Directions::DOWN:
		currentAnimTop = &topDown;
		currentAnimBot = &botDown;
		break;
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
	if (collider->type == Collider::Type::PLAYER_SHOT) {
		App->audio->PlayFx(enemyDeadFx);
		App->powerups->AddPowerup(POWERUP_TYPE::HEAVY_RIFLE, position.x, position.y);
		App->player->score += 300;
	}
	

	//App->particles->AddParticle(App->particles->explosion, position.x, position.y);
	//App->audio->PlayFx(enemyDeadFx);
}

void Enemy_RedSoldier::Shoot()
{
	if (shootdelay >= 20)
	{
		//App->particles->AddParticle(App->particles->shot_down, position.x + 16, position.y + 32, Collider::Type::ENEMY_SHOT);
		//App->particles->AddParticle(App->particles->shot_down_right, position.x + 16, position.y + 32, Collider::Type::ENEMY_SHOT);

		switch (looking)
		{
		case Directions::UP:
			App->particles->enemy_shot.speed.x = 0;
			App->particles->enemy_shot.speed.y = -SHOT_SPEED_STRAIGHT;
			break;

		case Directions::UP_RIGHT:
			App->particles->enemy_shot.speed.x = SHOT_SPEED_DIAGONAL;
			App->particles->enemy_shot.speed.y = -SHOT_SPEED_DIAGONAL;
			break;

		case Directions::UP_LEFT:
			App->particles->enemy_shot.speed.x = -SHOT_SPEED_DIAGONAL;
			App->particles->enemy_shot.speed.y = -SHOT_SPEED_DIAGONAL;
			break;
			
		case Directions::RIGHT:
			App->particles->enemy_shot.speed.x = SHOT_SPEED_STRAIGHT;
			App->particles->enemy_shot.speed.y = 0;
			break;

		case Directions::LEFT:
			App->particles->enemy_shot.speed.x = -SHOT_SPEED_STRAIGHT;
			App->particles->enemy_shot.speed.y = 0;
			break;

		case Directions::DOWN_RIGHT:
			App->particles->enemy_shot.speed.x = SHOT_SPEED_DIAGONAL;
			App->particles->enemy_shot.speed.y = SHOT_SPEED_DIAGONAL;
			break;
		case Directions::DOWN_LEFT:
			App->particles->enemy_shot.speed.x = -SHOT_SPEED_DIAGONAL;
			App->particles->enemy_shot.speed.y = SHOT_SPEED_DIAGONAL;
			break;
		case Directions::DOWN:
			App->particles->enemy_shot.speed.x = 0;
			App->particles->enemy_shot.speed.y = SHOT_SPEED_STRAIGHT;
			break;
		default:
			break;
		}
		App->particles->AddParticle(App->particles->enemy_shot, position.x + 16, position.y + 32, Collider::Type::ENEMY_SHOT);

		shootdelay = 0;
	}

	shootdelay++;
}

