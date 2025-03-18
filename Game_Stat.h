#ifndef GAME_STAT_
#define GAME_STAT_

#include <SDL.h>
#include <SDL_image.h>
#include <string>

static SDL_Window* window = NULL;
static SDL_Renderer* renderer = NULL;
static SDL_Event event = NULL;

const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 640;
const int BPP = 32;

const int COLOR_KEY_R = 167;
const int COLOR_KEY_G = 175;
const int COLOR_KEY_B = 180;
const int RENDER_DRAW_COLOR = 255;

#endif // COMMON_GAME_STAT_
