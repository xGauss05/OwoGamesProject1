#include "ModuleDebug.h"

#include "Application.h"
#include "ModuleInput.h"
#include "ModuleRender.h"

#include "ModuleCollisions.h"
#include "ModulePlayer.h"
#include "Enemy.h"
#include "ModuleEnemies.h"

#include "ModuleFonts.h"
#include <string>
using namespace std;

ModuleDebug::ModuleDebug(bool startEnabled) : Module(startEnabled) { debug = false; }
ModuleDebug::~ModuleDebug() {}

update_status ModuleDebug::Update() {
	if (App->input->keys[SDL_SCANCODE_F2] == KEY_DOWN)
		debug = !debug;

	if (debug)
	{
		if (App->input->keys[SDL_SCANCODE_T] == KEY_DOWN)
			text = !text;

		if (App->input->keys[SDL_SCANCODE_C] == KEY_DOWN)
			camLimits = !camLimits;
	}

	return update_status::UPDATE_CONTINUE;
}

update_status ModuleDebug::PostUpdate() {
	if (debug)
		DebugDraw();

	return update_status::UPDATE_CONTINUE;
}

void ModuleDebug::DebugDraw() {

	Uint8 alpha = 80;
	for (uint i = 0; i < MAX_COLLIDERS; ++i) {
		if (App->collisions->colliders[i] == nullptr)
			continue;

		switch (App->collisions->colliders[i]->type) {
		case Collider::Type::NONE: // white
			App->render->DrawQuad(App->collisions->colliders[i]->rect, 255, 255, 255, alpha);
			break;
		case Collider::Type::WALL: // blue
			App->render->DrawQuad(App->collisions->colliders[i]->rect, 0, 0, 255, alpha);
			break;
		case Collider::Type::PLAYER: // green
			App->render->DrawQuad(App->collisions->colliders[i]->rect, 0, 255, 0, alpha);
			break;
		case Collider::Type::HOSTAGE: // green
			App->render->DrawQuad(App->collisions->colliders[i]->rect, 0, 255, 0, alpha);
			break;
		case Collider::Type::ENEMY: // red
			App->render->DrawQuad(App->collisions->colliders[i]->rect, 255, 0, 0, alpha);
			break;
		case Collider::Type::PLAYER_SHOT: // yellow
			App->render->DrawQuad(App->collisions->colliders[i]->rect, 255, 255, 0, alpha);
			break;
		case Collider::Type::ENEMY_SHOT: // magenta
			App->render->DrawQuad(App->collisions->colliders[i]->rect, 0, 255, 255, alpha);
			break;
		case Collider::Type::POWER_UP: // white
			App->render->DrawQuad(App->collisions->colliders[i]->rect, 255, 255, 255, alpha);
			break;
		case Collider::Type::WATER:
			App->render->DrawQuad(App->collisions->colliders[i]->rect, 0, 255, 100, alpha);
			break;
		case Collider::Type::TRENCH:
			App->render->DrawQuad(App->collisions->colliders[i]->rect, 255, 0, 100, alpha);
			break;
		case Collider::Type::BREAKABLE:
			App->render->DrawQuad(App->collisions->colliders[i]->rect, 255, 100, 0, alpha);
			break;
		case Collider::Type::NON_DEST_BAR:
			App->render->DrawQuad(App->collisions->colliders[i]->rect, 100, 255, 0, alpha);
			break;
		default:
			break;
		}

	}


	for (size_t i = 0; i < MAX_ENEMIES; i++)
	{
		if (App->enemies->enemies[i] != nullptr)
		{
			App->render->DrawLine(App->enemies->enemies[i]->position.x + 16,
				App->enemies->enemies[i]->position.y + 32,
				App->enemies->enemies[i]->position.x + 16 + 20 * cos(App->enemies->enemies[i]->degrees * (M_PI / 180)),
				App->enemies->enemies[i]->position.y + 32 + 20 * sin(App->enemies->enemies[i]->degrees * (M_PI / 180)),
				0, 255, 0, 255);
		}
	}

	App->fonts->BlitText(10, 50 , 0, "PRESS T FOR VARIABLES");
	App->fonts->BlitText(10, 60 , 0, "PRESS C FOR CAM LIMITS");

	//Camera limits debug
	if (camLimits)
	{
		//Left offset
		App->render->DrawLine((App->render->camera.x + SCREEN_WIDTH / 2 - 16) - 30, App->render->camera.y, (App->render->camera.x + SCREEN_WIDTH / 2 - 16) - 30, App->render->camera.y + SCREEN_HEIGHT, 50, 50, 255, 255, 1.0, true);
		//Right offset
		App->render->DrawLine((App->render->camera.x + SCREEN_WIDTH / 2 - 16) + 30 + 32, App->render->camera.y, (App->render->camera.x + SCREEN_WIDTH / 2 - 16) + 30 + 32, App->render->camera.y + SCREEN_HEIGHT, 50, 50, 255, 255, 1.0, true);
		//Upper offset
		App->render->DrawLine(App->render->camera.x, (App->render->camera.y + SCREEN_HEIGHT / 1.5f) - 30, App->render->camera.x + SCREEN_WIDTH, (App->render->camera.y + SCREEN_HEIGHT / 1.5f) - 30, 50, 50, 255, 255, 1.0, true);
		//Lower offset
		App->render->DrawLine(App->render->camera.x, (App->render->camera.y + SCREEN_HEIGHT / 1.5f) + 30 + 64, App->render->camera.x + SCREEN_WIDTH, (App->render->camera.y + SCREEN_HEIGHT / 1.5f) + 30 + 64, 50, 50, 255, 255, 1.0, true);
	}

	//Variables debug
	if (text)
	{
		App->fonts->BlitText(10, DEBUG_BOX + -40, 0, "VARIABLES");

		App->fonts->BlitText(10, DEBUG_BOX + -30, 0, "-GOD MODE");
		if (!App->player->godMode)
			App->fonts->BlitText(90, DEBUG_BOX + -30, 0, "OFF");
		else
			App->fonts->BlitText(90, DEBUG_BOX + -30, 0, "ON");
		//	App->fonts->BlitText(90, DEBUG_BOX + -30, 0, "ON");

		App->fonts->BlitText(10, DEBUG_BOX + -20, 0, "-FREE CAM");
		if (!App->render->debugCamera)
			App->fonts->BlitText(90, DEBUG_BOX + -20, 0, "OFF");
		else
			App->fonts->BlitText(90, DEBUG_BOX + -20, 0, "ON");
		//App->fonts->BlitText(90, DEBUG_BOX + -20, 0, "ON");

		//Position debug
		App->fonts->BlitText(10, DEBUG_BOX, 0, "PLAYER");

		App->fonts->BlitText(10, DEBUG_BOX + 10, 0, "X.");
		App->fonts->BlitText(25, DEBUG_BOX + 10, 0, std::to_string(App->player->position.x).c_str());

		App->fonts->BlitText(10, DEBUG_BOX + 20, 0, "Y.");
		App->fonts->BlitText(25, DEBUG_BOX + 20, 0, std::to_string(App->player->position.y).c_str());

		App->fonts->BlitText(10, DEBUG_BOX + 30, 0, "CAMERA X.");
		App->fonts->BlitText(80, DEBUG_BOX + 30, 0, std::to_string(App->render->camera.x).c_str());

		App->fonts->BlitText(10, DEBUG_BOX + 40, 0, "CAMERA Y.");
		App->fonts->BlitText(80, DEBUG_BOX + 40, 0, std::to_string(App->render->camera.y).c_str());

		//Controller debug
		App->fonts->BlitText(10, DEBUG_BOX + 50, 0, "CONTROLLER");

		if (App->input->controllers[0] != nullptr)
		{
			App->fonts->BlitText(10, DEBUG_BOX + 70, 0, "J1.X");
			App->fonts->BlitText(50, DEBUG_BOX + 70, 0, std::to_string(App->input->controllers[0]->j1_x).c_str());

			App->fonts->BlitText(10, DEBUG_BOX + 80, 0, "J1.Y");
			App->fonts->BlitText(50, DEBUG_BOX + 80, 0, std::to_string(App->input->controllers[0]->j1_y).c_str());

			if (App->input->controllers[0]->j1_y < -10000)
				App->fonts->BlitText(185, DEBUG_BOX + 65, 0, "U");

			else if (App->input->controllers[0]->j1_y > 10000)
				App->fonts->BlitText(185, DEBUG_BOX + 85, 0, "D");

			if (App->input->controllers[0]->j1_x < -10000)
				App->fonts->BlitText(175, DEBUG_BOX + 75, 0, "L");

			else if (App->input->controllers[0]->j1_x > 10000)
				App->fonts->BlitText(195, DEBUG_BOX + 75, 0, "R");

			//

			App->fonts->BlitText(10, DEBUG_BOX + 100, 0, "J2.X");
			App->fonts->BlitText(50, DEBUG_BOX + 100, 0, std::to_string(App->input->controllers[0]->j2_x).c_str());

			App->fonts->BlitText(10, DEBUG_BOX + 110, 0, "J2.Y");
			App->fonts->BlitText(50, DEBUG_BOX + 110, 0, std::to_string(App->input->controllers[0]->j2_y).c_str());

			if (App->input->controllers[0]->j2_y < -10000)
				App->fonts->BlitText(185, DEBUG_BOX + 95, 0, "U");

			else if (App->input->controllers[0]->j2_y > 10000)
				App->fonts->BlitText(185, DEBUG_BOX + 115, 0, "D");

			if (App->input->controllers[0]->j2_x < -10000)
				App->fonts->BlitText(175, DEBUG_BOX + 105, 0, "L");

			else if (App->input->controllers[0]->j2_x > 10000)
				App->fonts->BlitText(195, DEBUG_BOX + 105, 0, "R");

			//

			App->fonts->BlitText(10, DEBUG_BOX + 130, 0, "L TRIGGER");
			App->fonts->BlitText(90, DEBUG_BOX + 130, 0, std::to_string(App->input->controllers[0]->LT).c_str());

			App->fonts->BlitText(10, DEBUG_BOX + 140, 0, "R TRIGGER");
			App->fonts->BlitText(90, DEBUG_BOX + 140, 0, std::to_string(App->input->controllers[0]->RT).c_str());

		}
		else
			App->fonts->BlitText(10, DEBUG_BOX + 70, 0, "CONTROLLER NOT FOUND");
	}
}