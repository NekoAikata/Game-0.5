#ifndef GAME_STAT_
#define GAME_STAT_

#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include <iostream>

static SDL_Window* window = NULL;
static SDL_Renderer* renderer = NULL;
static SDL_Event event;

const int FRAME_PER_SECOND = 50;
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 704;
const int BPP = 32;

const int COLOR_KEY_R = 167;
const int COLOR_KEY_G = 175;
const int COLOR_KEY_B = 180;
const int RENDER_DRAW_COLOR = 0xff;

#define TILE_SIZE 64
#define MAX_MAP_X 13
#define MAX_MAP_Y 400
#define BLANK_MAP 0

struct Map
{
    int start_x;
    int start_y;

    int max_x;
    int max_y;

    int tile[MAX_MAP_Y][MAX_MAP_X];

    char* File_name;
};

struct Input_action
{
    int left;
    int right;
    int up;
    int down;
};

#endif // COMMON_GAME_STAT_
