#include "ModuleDebug.h"

#include "Application.h"
#include "ModuleInput.h"
#include "ModuleRender.h"

#include "ModuleCollisions.h"
#include "ModulePlayer.h"
#include "Enemy.h"
#include "ModuleEnemies.h"
#include "ModulePowerup.h"
#include "ModuleRender.h"
#include "ModuleFonts.h"
#include <string>
using namespace std;

struct {
	int x, y;
	
} mouse;

ModuleDebug::ModuleDebug(bool startEnabled) : Module(startEnabled) {
	debug = false;
}
ModuleDebug::~ModuleDebug() {
}

bool ModuleDebug::Start() {
	if (App->input->controllerCount != 0) {
		debugBox -= 60;
	}
	debug = false;
	return true;
}

update_status ModuleDebug::Update() {
	int state = SDL_GetMouseState(&mouse.x, &mouse.y);
	LOG("Mouse(x,y)=(%d,%d)", mouse.x, mouse.y);
	if (App->input->keys[SDL_SCANCODE_F2] == KEY_DOWN)
		debug = !debug;

	if (debug) {
		if (App->input->keys[SDL_SCANCODE_Z] == KEY_DOWN)
			variables = !variables;

		if (App->input->keys[SDL_SCANCODE_X] == KEY_DOWN &&
			!teleport)
			spawn = !spawn;

		if (App->input->keys[SDL_SCANCODE_C] == KEY_DOWN)
			camLimits = !camLimits;

		if (App->input->keys[SDL_SCANCODE_V] == KEY_DOWN &&
			!spawn)
			teleport = !teleport;
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
		case Collider::Type::HOSTAGE: // white
			App->render->DrawQuad(App->collisions->colliders[i]->rect, 255, 255, 255, alpha);
			break;
		case Collider::Type::ENEMY: // red
			App->render->DrawQuad(App->collisions->colliders[i]->rect, 255, 0, 0, alpha);
			break;
		case Collider::Type::TRUCK: // red
			App->render->DrawQuad(App->collisions->colliders[i]->rect, 255, 0, 0, alpha);
			break;
		case Collider::Type::BOSS: // red
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
		case Collider::Type::BREAKABLE: // orange
			App->render->DrawQuad(App->collisions->colliders[i]->rect, 255, 100, 0, alpha);
			break;
		case Collider::Type::BREAKABLE_BRIDGE: // orange
			App->render->DrawQuad(App->collisions->colliders[i]->rect, 255, 100, 0, alpha);
			break;
		case Collider::Type::NON_DEST_BAR:
			App->render->DrawQuad(App->collisions->colliders[i]->rect, 100, 255, 0, alpha);
			break;
		case Collider::Type::EXPLOSION:
			App->render->DrawQuad(App->collisions->colliders[i]->rect, 255, 255 / 2, 0, alpha);
			break;
		default:
			break;
		}

	}

	for (size_t i = 0; i < MAX_ENEMIES; i++) {
		if (App->enemies->enemies[i] != nullptr) {
			App->render->DrawLine(App->enemies->enemies[i]->position.x + 16,
								  App->enemies->enemies[i]->position.y + 32,
								  App->enemies->enemies[i]->position.x + 16 + 20 * cos(App->enemies->enemies[i]->degrees * (M_PI / 180)),
								  App->enemies->enemies[i]->position.y + 32 + 20 * sin(App->enemies->enemies[i]->degrees * (M_PI / 180)),
								  0, 255, 0, 255);
		}
	}

	App->fonts->BlitText(10, spawnBox, 0, "PRESS Z FOR VARIABLES");
	App->fonts->BlitText(10, spawnBox + 10, 0, "PRESS X FOR SPAWN MENU");
	App->fonts->BlitText(10, spawnBox + 20, 0, "PRESS C FOR CAM LIMITS");
	App->fonts->BlitText(10, spawnBox + 30, 0, "PRESS V FOR TELEPORT MENU");


	//This specific case has to go here in order for the spawn menu to work properly due to code execution order
	if (behaviour)
		if (App->input->keys[SDL_SCANCODE_1] == KEY_DOWN)
		{
			App->enemies->AddEnemy(ENEMY_TYPE::GREENSOLDIER, App->render->camera.x + mouse.x, App->render->camera.y + mouse.y, 1);
			behaviour = false;
		}

	//Spawn Enemies 
	if (spawn) {
		App->fonts->BlitText(10, spawnBox + 40, 0, "SPAWN.");
		App->fonts->BlitText(60, spawnBox + 40, 0, "1.GREENSOLDIER");
		App->fonts->BlitText(60, spawnBox + 50, 0, "2.REDSOLDIER");
		App->fonts->BlitText(60, spawnBox + 60, 0, "3.TACKLER");
		App->fonts->BlitText(60, spawnBox + 70, 0, "4.TRUCK");
		App->fonts->BlitText(60, spawnBox + 80, 0, "5.BOSS");
		App->fonts->BlitText(60, spawnBox + 90, 0, "6.HEAVY RIFLE");
		App->fonts->BlitText(60, spawnBox + 100, 0, "7.FLAMETHROWER");
		App->fonts->BlitText(60, spawnBox + 110, 0, "8.HOSTAGE");

		if (App->input->keys[SDL_SCANCODE_1] == KEY_DOWN && !behaviour)
			behaviour = true;

		if (App->input->keys[SDL_SCANCODE_2] == KEY_DOWN && !behaviour)
			App->enemies->AddEnemy(ENEMY_TYPE::REDSOLDIER, App->render->camera.x + (mouse.x / 2), App->render->camera.y + mouse.y, 0);

		if (App->input->keys[SDL_SCANCODE_3] == KEY_DOWN && !behaviour)
			App->enemies->AddEnemy(ENEMY_TYPE::TACKLER, App->render->camera.x+(mouse.x/2), App->render->camera.y + mouse.y);

		if (App->input->keys[SDL_SCANCODE_4] == KEY_DOWN && !behaviour)
			App->enemies->AddEnemy(ENEMY_TYPE::TRUCK, App->render->camera.x + (mouse.x / 2), App->render->camera.y + (mouse.y / 2), 0);

		if (App->input->keys[SDL_SCANCODE_5] == KEY_DOWN && !behaviour)
			App->enemies->AddEnemy(ENEMY_TYPE::BOSS, App->render->camera.x + (mouse.x / 2), App->render->camera.y + mouse.y, 0);
			
		if (App->input->keys[SDL_SCANCODE_6] == KEY_DOWN && !behaviour)
			App->powerups->AddPowerup(POWERUP_TYPE::HEAVY_RIFLE, App->render->camera.x + (mouse.x / 2), App->render->camera.y + (mouse.y / 2));

		if (App->input->keys[SDL_SCANCODE_7] == KEY_DOWN && !behaviour)
			App->powerups->AddPowerup(POWERUP_TYPE::FLAMETHROWER, App->render->camera.x + (mouse.x / 2), App->render->camera.y + (mouse.y / 2));
			
		if (App->input->keys[SDL_SCANCODE_8] == KEY_DOWN && !behaviour)
			App->powerups->AddPowerup(POWERUP_TYPE::HOSTAGE, App->render->camera.x + (mouse.x / 2), App->render->camera.y + (mouse.y / 2));
	}

	if (behaviour)
	{
		App->fonts->BlitText(60, spawnBox + 120, 0, "CHOOSE BEHAVIOUR 0-7");

		if (App->input->keys[SDL_SCANCODE_0] == KEY_DOWN)
		{
			App->enemies->AddEnemy(ENEMY_TYPE::GREENSOLDIER, App->player->position.x, App->player->position.y - 120, 0);
			behaviour = false;
		}
		
		//Here should go case 1, declared above

		if (App->input->keys[SDL_SCANCODE_2] == KEY_DOWN)
		{
			App->enemies->AddEnemy(ENEMY_TYPE::GREENSOLDIER, App->player->position.x, App->player->position.y - 120, 2);
			behaviour = false;
		}
		if (App->input->keys[SDL_SCANCODE_3] == KEY_DOWN)
		{
			App->enemies->AddEnemy(ENEMY_TYPE::GREENSOLDIER, App->player->position.x, App->player->position.y - 120, 3);
			behaviour = false;
		}
		if (App->input->keys[SDL_SCANCODE_4] == KEY_DOWN)
		{
			App->enemies->AddEnemy(ENEMY_TYPE::GREENSOLDIER, App->player->position.x, App->player->position.y - 120, 4);
			behaviour = false;
		}
		if (App->input->keys[SDL_SCANCODE_5] == KEY_DOWN)
		{
			App->enemies->AddEnemy(ENEMY_TYPE::GREENSOLDIER, App->player->position.x, App->player->position.y - 120, 5);
			behaviour = false;
		}
		if (App->input->keys[SDL_SCANCODE_6] == KEY_DOWN)
		{
			App->enemies->AddEnemy(ENEMY_TYPE::GREENSOLDIER, App->player->position.x, App->player->position.y - 120, 6);
			behaviour = false;
		}
		if (App->input->keys[SDL_SCANCODE_7] == KEY_DOWN)
		{
			App->enemies->AddEnemy(ENEMY_TYPE::GREENSOLDIER, App->player->position.x, App->player->position.y - 120, 7);
			behaviour = false;
		}
	}

	if (teleport) {
		App->fonts->BlitText(10, spawnBox + 40, 0, "TELEPORT.");
		App->fonts->BlitText(75, spawnBox + 40, 0, "1.START");
		App->fonts->BlitText(75, spawnBox + 50, 0, "2.FENCE");
		App->fonts->BlitText(75, spawnBox + 60, 0, "3.BRIDGE");
		App->fonts->BlitText(75, spawnBox + 70, 0, "4.BOSS");

		if (App->input->keys[SDL_SCANCODE_1] == KEY_DOWN) {
			App->player->position.x = 230;
			App->player->position.y = -60;
			App->render->camera.x = App->player->position.x - 100;
			App->render->camera.y = App->player->position.y - 200;
		}
		if (App->input->keys[SDL_SCANCODE_2] == KEY_DOWN) {
			App->player->position.x = 485;
			App->player->position.y = -1375;
			App->render->camera.x = App->player->position.x - 100;
			App->render->camera.y = App->player->position.y - 200;
		}
		if (App->input->keys[SDL_SCANCODE_3] == KEY_DOWN) {
			App->player->position.x = 765;
			App->player->position.y = -2585;
			App->render->camera.x = App->player->position.x - 100;
			App->render->camera.y = App->player->position.y - 200;
		}
		if (App->input->keys[SDL_SCANCODE_4] == KEY_DOWN) {
			App->player->position.x = 750;
			App->player->position.y = -3360;
			App->render->camera.x = App->player->position.x - 100;
			App->render->camera.y = App->player->position.y - 200;
		}

	}

	//Camera limits debug

	if (camLimits) {
		//Left offset
		App->render->DrawLine(App->render->camera.x + SCREEN_WIDTH / 3 - 10,
							  App->render->camera.y,
							  App->render->camera.x + SCREEN_WIDTH / 3 - 10,
							  App->render->camera.y + SCREEN_HEIGHT,
							  255, 255, 50, 255, 0.5 * SCREEN_SIZE, true);

		//Right offset
		App->render->DrawLine(App->render->camera.x + SCREEN_WIDTH / 1.5 + 10,
							  App->render->camera.y,
							  App->render->camera.x + SCREEN_WIDTH / 1.5 + 10,
							  App->render->camera.y + SCREEN_HEIGHT,
							  255, 255, 50, 255, 0.5 * SCREEN_SIZE, true);

		//Upper offset
		App->render->DrawLine(App->render->camera.x,
							  (App->render->camera.y + SCREEN_HEIGHT / 1.4f) - 60,
							  App->render->camera.x + SCREEN_WIDTH,
							  (App->render->camera.y + SCREEN_HEIGHT / 1.4f) - 60,
							  255, 255, 50, 255, 0.5 * SCREEN_SIZE, true);
		//Lower offset
		App->render->DrawLine(App->render->camera.x,
							  (App->render->camera.y + SCREEN_HEIGHT / 1.4f) + 60,
							  App->render->camera.x + SCREEN_WIDTH,
							  (App->render->camera.y + SCREEN_HEIGHT / 1.4f) + 60,
							  255, 255, 50, 255, 0.5 * SCREEN_SIZE, true);
	}

	//Variables debug
	if (variables) {
		App->fonts->BlitText(10, debugBox, 0, "-GOD MODE");
		if (!App->player->godMode)
			App->fonts->BlitText(90, debugBox, 0, "OFF");
		else
			App->fonts->BlitText(90, debugBox, 0, "ON");
		//	App->fonts->BlitText(90, DEBUG_BOX + -30, 0, "ON");

		App->fonts->BlitText(10, debugBox + 10, 0, "-FREE CAM");
		if (!App->render->debugCamera)
			App->fonts->BlitText(90, debugBox + 10, 0, "OFF");
		else
			App->fonts->BlitText(90, debugBox + 10, 0, "ON");

		//Position debug
		App->fonts->BlitText(10, debugBox + 30, 0, "PLAYER");

		App->fonts->BlitText(10, debugBox + 40, 0, "X.");
		App->fonts->BlitText(25, debugBox + 40, 0, std::to_string(App->player->position.x).c_str());

		App->fonts->BlitText(10, debugBox + 50, 0, "Y.");
		App->fonts->BlitText(25, debugBox + 50, 0, std::to_string(App->player->position.y).c_str());

		App->fonts->BlitText(10, debugBox + 60, 0, "CAMERA X.");
		App->fonts->BlitText(80, debugBox + 60, 0, std::to_string(App->render->camera.x).c_str());

		App->fonts->BlitText(10, debugBox + 70, 0, "CAMERA Y.");
		App->fonts->BlitText(80, debugBox + 70, 0, std::to_string(App->render->camera.y).c_str());

		//Controller debug

		if (App->input->controllerCount != 0) {
			App->fonts->BlitText(10, debugBox + 90, 0, "CONTROLLER");

			App->fonts->BlitText(10, debugBox + 100, 0, "J1.X");
			App->fonts->BlitText(50, debugBox + 100, 0, std::to_string(App->input->controllers[0]->j1_x).c_str());

			App->fonts->BlitText(10, debugBox + 110, 0, "J1.Y");
			App->fonts->BlitText(50, debugBox + 110, 0, std::to_string(App->input->controllers[0]->j1_y).c_str());

			if (App->input->controllers[0]->j1_y < -15000)
				App->fonts->BlitText(185, debugBox + 90, 0, "U");

			else if (App->input->controllers[0]->j1_y > 15000)
				App->fonts->BlitText(185, debugBox + 110, 0, "D");

			if (App->input->controllers[0]->j1_x < -15000)
				App->fonts->BlitText(175, debugBox + 100, 0, "L");

			else if (App->input->controllers[0]->j1_x > 15000)
				App->fonts->BlitText(195, debugBox + 100, 0, "R");

			//

			App->fonts->BlitText(10, debugBox + 120, 0, "J2.X");
			App->fonts->BlitText(50, debugBox + 120, 0, std::to_string(App->input->controllers[0]->j2_x).c_str());

			App->fonts->BlitText(10, debugBox + 130, 0, "J2.Y");
			App->fonts->BlitText(50, debugBox + 130, 0, std::to_string(App->input->controllers[0]->j2_y).c_str());

			if (App->input->controllers[0]->j2_y < -15000)
				App->fonts->BlitText(185, debugBox + 120, 0, "U");

			else if (App->input->controllers[0]->j2_y > 15000)
				App->fonts->BlitText(185, debugBox + 140, 0, "D");

			if (App->input->controllers[0]->j2_x < -15000)
				App->fonts->BlitText(175, debugBox + 130, 0, "L");

			else if (App->input->controllers[0]->j2_x > 15000)
				App->fonts->BlitText(195, debugBox + 130, 0, "R");

			//

			App->fonts->BlitText(10, debugBox + 140, 0, "L TRIGGER");
			App->fonts->BlitText(90, debugBox + 140, 0, std::to_string(App->input->controllers[0]->LT).c_str());

			App->fonts->BlitText(10, debugBox + 150, 0, "R TRIGGER");
			App->fonts->BlitText(90, debugBox + 150, 0, std::to_string(App->input->controllers[0]->RT).c_str());

		} else
			App->fonts->BlitText(10, debugBox + 90, 0, "CONTROLLER NOT FOUND");
	}
}