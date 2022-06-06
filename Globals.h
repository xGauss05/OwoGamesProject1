#ifndef __GLOBALS_H__
#define __GLOBALS_H__

#include <windows.h>

#define LOG(format, ...) log(__FILE__, __LINE__, format, __VA_ARGS__);
void log(const char file[], int line, const char* format, ...);

#define EXIT_FAILURE 1
#define EXIT_SUCCESS 0

enum class update_status {
	UPDATE_CONTINUE = 1,
	UPDATE_STOP,
	UPDATE_ERROR
};

// Useful typedefs ----------------
typedef unsigned int uint;
typedef unsigned short ushort;

// Window Configuration -----------
#define SCREEN_WIDTH 224
#define SCREEN_HEIGHT 384

#define SCREEN_SIZE 2
#define WIN_FULLSCREEN 0
#define WIN_FULLSCREEN_DESKTOP 1
#define WIN_BORDERLESS 0
#define WIN_RESIZABLE 0
#define VSYNC 1

// Gameplay variables
#define DEATH_ANIM_DURATION 185
#define INVINCIBLE_DURATION 500

// Camera Configuration (for debug purposes)
#define CAMERA_SPEED 2

// Scenes
#define SCENE_DURATION 500

// Hostage
#define IDLEFX_COOLDOWN 750

#endif // __GLOBALS_H__
