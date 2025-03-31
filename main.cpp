#include <iostream>
#include "Game_Stat.h"
#include "BObject.h"
#include "Map.h"
#include "Main_o.h"
#include "Timer.h"

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
    bool ret = background.LoadImg("img//grass.png", renderer);
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
    Timer game_timer;
    if (!InitDataSuccess() || !LoadBG())
    {
        return -1;
    }

    GameMap Game_map;
    Game_map.LoadMap("map/map.dat");
    Game_map.LoadTiles(renderer);

    MainObject Player1;
    Player1.LoadImg("img//player_down.png", renderer);
    Player1.Clip();

    bool quitG = false;
    while (!quitG)
    {
        game_timer.start();
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
        Map map_data = Game_map.GetMap();

        Player1.SetMapXY(map_data.start_x, map_data.start_y);
        Player1.DoPlayer(map_data);
        Player1.Show(renderer);
        Player1.GetValue();

        Game_map.SetMap(map_data);
        Game_map.DrawMap(renderer);

        SDL_RenderPresent(renderer);
        int real_timer = game_timer.get_tick();
        int time_per_frame = 1000/FRAME_PER_SECOND;

        if (real_timer < time_per_frame)
        {
            int delay_time = time_per_frame - real_timer;
            if (delay_time >= 0)
            {
                SDL_Delay(delay_time);
            }
        }
    }
    close();
    return 0;
}
