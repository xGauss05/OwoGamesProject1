#include "ModuleRender.h"

#include "Application.h"

#include "ModuleWindow.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModulePlayer.h"

#include "SDL/include/SDL_render.h"
#include "SDL/include/SDL_scancode.h"

ModuleRender::ModuleRender(bool startEnabled) : Module(startEnabled) {}

ModuleRender::~ModuleRender() {}

bool ModuleRender::Init() {
	LOG("Creating Renderer context");
	bool ret = true;
	Uint32 flags = 0;

	if (VSYNC == true) {
		flags |= SDL_RENDERER_PRESENTVSYNC;
	}

	renderer = SDL_CreateRenderer(App->window->window, -1, flags);

	if (renderer == nullptr) {
		LOG("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
		ret = false;
	}	
	//camera.x += App->player->position.x;
	//camera.y += App->player->position.y

	return ret;
}

// Called every draw update
update_status ModuleRender::PreUpdate() {
	//Set the color used for drawing operations
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

	//Clear rendering target
	SDL_RenderClear(renderer);

	if (WIN_FULLSCREEN_DESKTOP) {
		SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH * SCREEN_SIZE, SCREEN_HEIGHT * SCREEN_SIZE);
	}

	return update_status::UPDATE_CONTINUE;
}

update_status ModuleRender::Update() {

	if (App->input->keys[SDL_SCANCODE_F5] == KEY_DOWN)
		debugCamera = !debugCamera;

	if (debugCamera) {
		/*Handle positive vertical movement*/
		if (App->input->keys[SDL_SCANCODE_UP] == KEY_REPEAT)
			camera.y -= cameraSpeed;

		//Handle negative vertical movement
		if (App->input->keys[SDL_SCANCODE_DOWN] == KEY_REPEAT)
			camera.y += cameraSpeed;

		if (App->input->keys[SDL_SCANCODE_LEFT] == KEY_REPEAT)
			camera.x -= cameraSpeed;

		if (App->input->keys[SDL_SCANCODE_RIGHT] == KEY_REPEAT)
			camera.x += cameraSpeed;
	}

	if (App->player->IsEnabled() && !debugCamera) {

		//Left
		if (App->player->position.x - camera.x <= SCREEN_WIDTH / 3 - 10)
		{
			camera.x--;
			if (camera.y > -2265 - SCREEN_HEIGHT && camera.y < -1540 && camera.x <= 256) {
				camera.x++;
			}
			if (camera.y > -3320 - SCREEN_HEIGHT && camera.y < -2800 && camera.x <= 488) {
				camera.x++;
			}
		}
			

		//Right
		if (App->player->position.x - camera.x + 32 >= SCREEN_WIDTH / 1.5 + 10)
			camera.x++;
		if (camera.y > -2265 - SCREEN_HEIGHT && camera.y < -1540 && camera.x >= 768 - SCREEN_WIDTH) {
			camera.x--;
		}
		if (camera.y > -3320 - SCREEN_HEIGHT && camera.y < -2800 && camera.x >= 992 - SCREEN_WIDTH) {
			camera.x--;
		}

		//Up
		if (App->player->position.y - camera.y - 20 <= SCREEN_HEIGHT / 1.4f - 60)
			camera.y--;

		//Down
		if (App->player->position.y - camera.y + 40 >= SCREEN_HEIGHT / 1.4f + 60)
			camera.y++;
	}
	

	return update_status::UPDATE_CONTINUE;
}

update_status ModuleRender::PostUpdate() {
	// Update the screen
	SDL_RenderPresent(renderer);

	return update_status::UPDATE_CONTINUE;
}

bool ModuleRender::CleanUp() {
	LOG("Destroying renderer");

	// Destroy the rendering context
	if (renderer != nullptr)
		SDL_DestroyRenderer(renderer);

	return true;
}

// Blit to screen
bool ModuleRender::Blit(SDL_Texture* texture, int x, int y, SDL_Rect* section, float speed, bool useCamera) {
	bool ret = true;
	
	SDL_Rect rect{
		(int)(-camera.x * speed) + x * SCREEN_SIZE,
		(int)(-camera.y * speed) + y * SCREEN_SIZE,
		0, 0 };
	if (useCamera) {
		rect.x -= (camera.x * speed);
		rect.y -= (camera.y * speed);
	}
	if (section != nullptr) {
		rect.w = section->w;
		rect.h = section->h;
	} else {
		// Collect the texture size into rect.w and rect.h variables
		SDL_QueryTexture(texture, nullptr, nullptr, &rect.w, &rect.h);
	}

	rect.w *= SCREEN_SIZE;
	rect.h *= SCREEN_SIZE;

	if (SDL_RenderCopy(renderer, texture, section, &rect) != 0) {
		LOG("Cannot blit to screen. SDL_RenderCopy error: %s", SDL_GetError());
		ret = false;
	}

	return ret;
}

bool ModuleRender::DrawQuad(const SDL_Rect& rect, Uint8 r, Uint8 g, Uint8 b, Uint8 a, float speed, bool useCamera) {
	bool ret = true;

	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
	SDL_SetRenderDrawColor(renderer, r, g, b, a);

	SDL_Rect dstRect{
		(int)(-camera.x * speed) + rect.x * SCREEN_SIZE,
		(int)(-camera.y * speed) + rect.y * SCREEN_SIZE,
		rect.w * SCREEN_SIZE, rect.h * SCREEN_SIZE };
	if (useCamera) {
		dstRect.x -= (camera.x * speed);
		dstRect.y -= (camera.y * speed);
	}
	if (SDL_RenderFillRect(renderer, &dstRect) != 0) {
		LOG("Cannot draw quad to screen. SDL_RenderFillRect error: %s", SDL_GetError());
		ret = false;
	}

	return ret;
}

bool ModuleRender::DrawLine(int x1, int y1, int x2, int y2, Uint8 r, Uint8 g, Uint8 b, Uint8 a, float speed, bool useCamera) {
	bool ret = true;

	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
	SDL_SetRenderDrawColor(renderer, r, g, b, a);

	SDL_RenderDrawLine( renderer,
		(int)(-camera.x * speed * 2) + x1 * SCREEN_SIZE,
		(int)(-camera.y * speed * 2) + y1 * SCREEN_SIZE,
		(int)(-camera.x * speed * 2) + x2 * SCREEN_SIZE,
		(int)(-camera.y * speed * 2) + y2 * SCREEN_SIZE);

	if (useCamera) {
		x1 -= (camera.x * speed);
		x2 -= (camera.y * speed);
	}

	/*if (SDL_RenderDrawLine(renderer,
		(int)(-camera.x * speed * 2) + x1 * SCREEN_SIZE,
		(int)(-camera.y * speed * 2) + y1 * SCREEN_SIZE,
		(int)(-camera.x * speed * 2) + x2 * SCREEN_SIZE,
		(int)(-camera.y * speed * 2) + y2 * SCREEN_SIZE) != 0) {
		LOG("Cannot draw line to screen. SDL_RenderDrawLine error: %s", SDL_GetError());
		ret = false;
	}*/

	return ret;
}
