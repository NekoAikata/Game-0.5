#include <iostream>
#include "Game_Stat.h"
#include "BObject.h"
#include "Map.h"
#include "Main_o.h"

BaseObject background;

bool InitDataSuccess()
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        return false;
    }
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");

    window = SDL_CreateWindow("Saved the King",
                                          SDL_WINDOWPOS_UNDEFINED,
                                          SDL_WINDOWPOS_UNDEFINED,
                                          SCREEN_WIDTH, SCREEN_HEIGHT,
                                          SDL_WINDOW_SHOWN);
    if (window == NULL) {return false;}

    else {
        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
        if (renderer == NULL) {return false;}
        else {
            SDL_SetRenderDrawColor(renderer, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR);
            int ImgFlag = IMG_INIT_PNG;
            if (!(IMG_Init(ImgFlag) && ImgFlag)) return false;}}

    return true;
}

bool LoadBG()
{
    bool ret = background.LoadImg("Img//grass.png", renderer);
    return ret;
}

void close()
{
    background.Free();

    SDL_DestroyRenderer(renderer);
    renderer = NULL;

    SDL_DestroyWindow(window);
    window = NULL;

    IMG_Quit();
    SDL_Quit();
}

int main(int argc, char* argv[])
{
    if (!InitDataSuccess() || !LoadBG())
    {
        return -1;
    }

    GameMap Game_map;
    Game_map.LoadMap("map/map.dat");
    Game_map.LoadTiles(renderer);

    MainObject Player1;
    Player1.LoadImg("img//", renderer);
    Player1.Clip();

    bool quitG = false;
    while (!quitG)
    {
        while(SDL_PollEvent(&event) != 0)
        {
            if(event.type == SDL_QUIT)
            {
                quitG=true;
            }
            Player1.HandleEvent(event, renderer);
        }
        SDL_SetRenderDrawColor(renderer, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR);
        SDL_RenderClear(renderer);

        background.Render(renderer, NULL);
        Game_map.DrawMap(renderer);

        SDL_RenderPresent(renderer);
        Player1.Show(renderer);
    }
    close();
    return 0;
}
