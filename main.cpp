#include <iostream>
#include "Game_Stat.h"
#include "BObject.h"

Object background;

using namespace std;

bool InitDataSuccess()
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        return false;
    }
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, 1);

    SDL_Window* window = SDL_CreateWindow("Saved the King",
                                          SDL_WINDOWPOS_CENTERED,
                                          SDL_WINDOWPOS_CENTERED,
                                          SCREEN_WIDTH, SCREEN_HEIGHT,
                                          SDL_WINDOW_SHOWN);
    if (!window) return false;

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) return false;
    SDL_SetRenderDrawColor(renderer, RENDERER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR);

    int ImgFlag = IMG_INIT_PNG;
    if (!(IMG_Init(ImgFlag) && ImgFlag)) return false;

    return true;
}

bool LoadBG()
{
    bool ret = background.LoadImg( ,renderer);
    return ret;
}

int main(int argc, char* argv[])
{
    if (!InitDataSuccess || !LoadBG)
    {
        return -1;
    }
    bool quitG = false;
    while (!quitG)
    {
        while(SDL_PollEvent(&event) != 0)
        {
            if(event->type == SDL_QUIT)
            {
                quitG=true;
            }
        }
        SDL_SetRenderDrawColor(renderer, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR);
        SDL_RenderClear();

        background.Render()
    }
}
