#include "ModulePlayer.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleParticles.h"
#include "ModuleAudio.h"
#include "ModuleCollisions.h"

#include "SDL/include/SDL_scancode.h"

ModulePlayer::ModulePlayer() {
	// idle animation - just one sprite
	idleAnim.PushBack({ 66, 1, 32, 14 });

	// Insert player animations here
	// move upwards
	upAnim.PushBack({ 100, 1, 32, 14 });
	upAnim.PushBack({ 132, 0, 32, 14 });
	upAnim.loop = false;
	upAnim.speed = 0.1f;

	// Move down
	downAnim.PushBack({ 33, 1, 32, 14 });
	downAnim.PushBack({ 0, 1, 32, 14 });
	downAnim.loop = false;
	downAnim.speed = 0.1f;
}

ModulePlayer::~ModulePlayer() {}

bool ModulePlayer::Start() {
	LOG("Loading player textures");

	bool ret = true;

	texture = App->textures->Load("Assets/ship.png"); // arcade version
	currentAnimation = &idleAnim;

	// initiate player audios here
	laserFx = App->audio->LoadFx("sounds/sfx/128.wav"); // need to confirm which sound it is
	explosionFx = App->audio->LoadFx("sounds/sfx/129.wav");

	// initial position
	position.x = 150;
	position.y = 120;

	// player collider
	collider = App->collisions->AddCollider({ position.x, position.y, 32, 14 }, Collider::Type::PLAYER, this);

	return ret;
}

update_status ModulePlayer::Update() {
	// Moving the player with the camera scroll
	
	if (App->input->keys[SDL_SCANCODE_A] == KEY_STATE::KEY_REPEAT) {
		position.x -= speed;
	}

	if (App->input->keys[SDL_SCANCODE_D] == KEY_STATE::KEY_REPEAT) {
		position.x += speed;
	}

	if (App->input->keys[SDL_SCANCODE_S] == KEY_STATE::KEY_REPEAT) {
		position.y += speed;
		if (currentAnimation != &downAnim) {
			downAnim.Reset();
			currentAnimation = &downAnim;
		}
	}

	if (App->input->keys[SDL_SCANCODE_W] == KEY_STATE::KEY_REPEAT) {
		position.y -= speed;
		if (currentAnimation != &upAnim) {
			upAnim.Reset();
			currentAnimation = &upAnim;
		}
	}

	if (App->input->keys[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_DOWN) {
		App->particles->AddParticle(App->particles->laser, position.x + 20, position.y, Collider::Type::PLAYER_SHOT);
		App->audio->PlayFx(laserFx);
	}

	// If no up/down movement detected, set the current animation back to idle
	if (App->input->keys[SDL_SCANCODE_S] == KEY_STATE::KEY_IDLE
		&& App->input->keys[SDL_SCANCODE_W] == KEY_STATE::KEY_IDLE)
		currentAnimation = &idleAnim;

	// Updates player collider position
	collider->SetPos(position.x, position.y);
	currentAnimation->Update();

	if (dead) {
		destroyedCountdown--;
		if (destroyedCountdown <= 0)
			return update_status::UPDATE_STOP;
	}

	return update_status::UPDATE_CONTINUE;
}

update_status ModulePlayer::PostUpdate() {
	if (!dead) {
		SDL_Rect rect = currentAnimation->GetCurrentFrame();
		App->render->Blit(texture, position.x, position.y, &rect);
	}
	return update_status::UPDATE_CONTINUE;
}

void ModulePlayer::OnCollision(Collider* c1, Collider* c2) {
	if (!this->dead) {
		// Delete player
		this->dead = true;
		// Delete player collider
		c1->pendingToDelete = true;
		App->audio->PlayFx(explosionFx);
		App->particles->AddParticle(App->particles->explosion, position.x, position.y - 10);
	}
}
