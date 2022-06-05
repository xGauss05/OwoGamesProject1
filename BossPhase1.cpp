#include "BossPhase1.h"

#include "Application.h"
#include "ModuleCollisions.h"
#include "ModuleAudio.h"
#include "ModulePlayer.h"
#include "ModuleParticles.h"
#include "ModuleEnemies.h" //(Testing)
#include "ModuleFadeToBlack.h"
#include "SceneLevel1.h"

#include "ModuleFonts.h"
#include <string>
#include "SDL/include/SDL.h"

#define BOSSPHASE1_SCORE 100

BossPhase1::BossPhase1(int x, int y) : Enemy(x, y) {
	topAnimIdle.PushBack({ 96,0,32,32 });
	currentAnimTop = &topAnimIdle;
	t1 = SDL_GetTicks();
	topAnimSpawn.PushBack({ 128,0,32,32 });
	topAnimSpawn.PushBack({ 64,0,32,32 });
	topAnimSpawn.PushBack  ({ 160,0,32,32 });
	topAnimSpawn.PushBack({ 0,0,32,32 });

	topAnimSpawn.PushBack({ 32,0,32,32 });

	topAnimSpawn.PushBack({ 0,0,32,32 });
	topAnimSpawn.PushBack({ 160,0,32,32 });
	topAnimSpawn.PushBack({ 64,0,32,32 });
	topAnimSpawn.PushBack({ 128,0,32,32 });
	topAnimSpawn.speed = 0.2f;
	topAnimSpawn.loop = false;
	//topAnimSpawn.pingpong = true;

	botAnimLeft.PushBack({ 0,32,32,32 });
	botAnimLeft.PushBack({ 32,32,32,32 });
	botAnimLeft.PushBack({ 64,32,32,32 });
	botAnimLeft.PushBack({ 96,32,32,32 });
	botAnimLeft.PushBack({ 128,32,32,32 });
	botAnimLeft.speed = 0.2f;
	botAnimLeft.pingpong = true;

	botAnimRight.PushBack({ 0,64,32,32 });
	botAnimRight.PushBack({ 32,64,32,32 });
	botAnimRight.PushBack({ 64,64,32,32 });
	botAnimRight.PushBack({ 96,64,32,32 });
	botAnimRight.PushBack({ 128,64,32,32 });
	botAnimRight.speed = 0.2f;
	botAnimRight.pingpong = true;

	botAnimSpawn.PushBack({ 64,64,32,32 });

	inOutPath.PushBack({ 0, 2.0f }, inOutTime, &botAnimLeft);
	inOutPath.PushBack({ 0, -2.0f }, inOutTime, &botAnimLeft);

	path.PushBack({ -0.5f, 0 }, 200, &botAnimLeft);
	path.PushBack({ 0.5f, 0 }, 200, &botAnimRight);

	collider = App->collisions->AddCollider({ 0, 0, 32, 64 }, Collider::Type::BOSS, (Module*)App->enemies);
}

void BossPhase1::Update() {
	
	if (isHit) {
		int t2 = SDL_GetTicks();
		if (t2 - t1 >= 5) {
			t1 = t2;
			explosionInvincible--;
		}
		if (explosionInvincible <= 0) {
			isHit = false;
			explosionInvincible = 5;
		}
	}
	if (inOut) {
		if (inOutTimer >= inOutTime) {
			inOut = false;
			inOutTimer = 0;
			stayPos = position;
		}

		inOutPath.Update();
		currentAnimBot = inOutPath.GetCurrentAnimation();
		position = spawnPos + inOutPath.GetRelativePosition();

		inOutTimer++;
	}

	if (!spawning && !inOut) {
		path.Update();
		currentAnimBot = path.GetCurrentAnimation();

		position = stayPos + path.GetRelativePosition();

		if (hits < 50)
			Shoot();
	}

	else if (topAnimSpawn.HasFinished()) {
		topAnimSpawn.Reset();
		currentAnimTop = &topAnimIdle;
		currentAnimBot = &botAnimSpawn;
		spawning = false;
	}

	if (hits >= 50) {
		stayPos = position;
		inOut = true;
		if (winWait >= inOutTime) {
			App->fade->FadeToBlack((Module*)App->level1, (Module*)App->win, 0);
		}
		winWait++;
	}
	// Call to the base class. It must be called at the end
	// It will update the collider depending on the position
	Enemy::Update();
}

void BossPhase1::OnCollision(Collider* collider) {
	if (collider->type == Collider::Type::PLAYER_SHOT) {
		hits++;
	}
	if (!isHit) {
		if (collider->type == Collider::Type::EXPLOSION) {
			hits += 2;
			isHit = true;
		}
	}
}

void BossPhase1::Shoot() {
	if (spawnDelay >= 90) {
		currentAnimTop = &topAnimSpawn;

		if (App->level1->bossMinions < MAX_MINIONS)
		{
			App->enemies->AddEnemy(ENEMY_TYPE::GREENSOLDIER, position.x - 50, position.y + 60, 8);
			App->enemies->AddEnemy(ENEMY_TYPE::GREENSOLDIER, position.x + 50, position.y + 60, 8);

			App->level1->bossMinions += 2;
		}

		spawnDelay = 0;
		spawning = true;
	}

	spawnDelay++;
}
