#include "Game_Stat.h"
#include "BObject.h"
#include "Map.h"
#include "Main_o.h"
#include "Timer.h"
#include "ThreatObject.h"

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

std::vector<ThreatObject*> MakeThreatList ()
{
    std::vector<ThreatObject*> list_threats;

    ThreatObject* dynamic_threat = new ThreatObject[20];
    for (int i = 0;i<20;i++)
    {
        ThreatObject* p_threat = (dynamic_threat + i);
        if (p_threat != NULL)
        {
            p_threat->LoadImg("img//threat_slime.png",renderer);
            p_threat->Clip();
            p_threat->SetType(1);
            p_threat->SetXpos(128*3);
            p_threat->SetYpos(640*i);
            p_threat->SetBorderX(128*2,128*4);
            p_threat->SetInputL(1);
            list_threats.push_back(p_threat);
        }
    }

    ThreatObject* threats = new ThreatObject[20];

    for (int i =0; i < 20;i++)
    {
        ThreatObject* p_threat = (threats + i);
        if (p_threat != NULL)
        {
            p_threat->LoadImg("img//threat_slime.png",renderer);
            p_threat->Clip();
            p_threat->SetXpos(128*3);
            p_threat->SetInputL(0);
            p_threat->SetType(0);
            p_threat->SetYpos(640*i+256);

            list_threats.push_back(p_threat);
        }
    }
    return list_threats;
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

    std::vector <ThreatObject*> list_threats = MakeThreatList();

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

        Player1.HandleSlash(renderer);
        Player1.SetMapXY(map_data.start_x, map_data.start_y);

        for (int i = 0;i < list_threats.size(); i++)
        {
            ThreatObject* threat_object = list_threats[i];
            if (threat_object != NULL)
            {
                threat_object->SetMapXY(map_data.start_x, map_data.start_y);
                threat_object->Move(renderer);
                threat_object->DoThreat(map_data);
                threat_object->Show(renderer);
            }
        }
        bool checkTCol = false;
        for (int i=0; i < list_threats.size(); ++i)
        {
            ThreatObject* threat_check = list_threats[i];
            if (threat_check != NULL)
            {
                SDL_Rect TRect;
                    TRect.x = threat_check->GetRect().x;
                    TRect.y = threat_check->GetRect().y;
                    TRect.w = threat_check->GetWidthFrame();
                    TRect.h = threat_check->GetHeightFrame();

                Slash* SCheck = Player1.GetSlash();
                if (SCheck != NULL)
                {
                    SDL_Rect SRect = SCheck->GetRect();
                    bool check = Common_Func::CheckCollision(TRect, SRect);

                    if(check)
                    {
                        list_threats[i]->Free();
                        list_threats.erase(list_threats.begin() + i);
                    }
                }
                if (&Player1 != NULL)
                {
                    SDL_Rect PRect = Player1.GetRectP();
                    if (Common_Func::CheckCollision(PRect, TRect))
                    {
                        checkTCol = true;
                    }
                }
            }
        }
        std::cout << Player1.HP << std::endl;
        Player1.DoPlayer(map_data,checkTCol);
        Player1.Show(renderer);
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
