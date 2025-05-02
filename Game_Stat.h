#ifndef GAME_STAT_
#define GAME_STAT_

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <string>
#include <iostream>
#include <vector>

static SDL_Window* window = NULL;
static SDL_Renderer* renderer = NULL;
static SDL_Event event;

const int FRAME_PER_SECOND = 24;
const int SCREEN_WIDTH = 896;
const int SCREEN_HEIGHT = 704;
const int BPP = 32;

const int COLOR_KEY_R = 167;
const int COLOR_KEY_G = 175;
const int COLOR_KEY_B = 180;
const int RENDER_DRAW_COLOR = 0;

#define TILE_SIZE 64
#define MAX_MAP_X 14
#define MAX_MAP_Y 400

#define LEVEL_1 389
#define LEVEL_1_5 375
#define LEVEL_2 300
#define LEVEL_3 200
#define LEVEL_4 100

#define BLANK_MAP 0
#define FLOOR 1
#define DOOR 15
#define DOOR_OPEN 16
#define KEY 17
#define TREASURE 18

namespace Common_Func
{
    bool CheckCollision(const SDL_Rect& object1, const SDL_Rect& object2);
}

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
