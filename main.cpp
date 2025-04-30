#include "Game_Stat.h"
#include "BObject.h"
#include "Map.h"
#include "Main_o.h"
#include "Timer.h"
#include "ThreatObject.h"
#include "Text.h"

BaseObject background;
TTF_Font* font_time;

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
    if (TTF_Init() == -1)
    {
        return false;
    }
    font_time = TTF_OpenFont("font//PixelPurl.ttf", 40);
    if (font_time == NULL)
    {
        return false;
    }
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
            p_threat->SetXYposRes();
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
            p_threat->SetXYposRes();

            list_threats.push_back(p_threat);
        }
    }
    return list_threats;
}

int Menu(SDL_Renderer* screen, TTF_Font* font_time, bool Start)
{
    int x,y;
    const int BUT_NUM = 2;
    const char* BUTTON[BUT_NUM] = {"Continue","Exit"};
    if (Start)
    {
        BUTTON[0] = "Play";
    }
    bool Button_status[BUT_NUM] = {0,0};
    SDL_Color But_color[2] = {{255,255,255},{255,0,0}};
    Text_object Button[BUT_NUM];
    SDL_Point pos[BUT_NUM];
    SDL_RenderClear(screen);
    for (int i = 0; i < BUT_NUM; i++)
    {
        Button[i].SetText(BUTTON[i]);
        Button[i].SetColor(But_color[0]);
        Button[i].LoadFromRenderText(font_time,renderer);
        int height = (Button[i].GetHeight())/2;
        if (i==0){
            height = -height;
        }
        pos[i].x = SCREEN_WIDTH/2 - (Button[i].GetWidth())/2;
        pos[i].y = SCREEN_HEIGHT/2 + height;
        Button[i].RenderText(renderer,pos[i].x, pos[i].y);
    }
    SDL_RenderPresent(screen);
    while (true)
    {
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_QUIT:
                for (int i=0;i<BUT_NUM;i++)
                {
                    Button[i].Free();
                }
                return 1;
            case SDL_MOUSEMOTION:
                SDL_GetMouseState(&x, &y);
                for (int i=0;i<BUT_NUM;++i)
                {
                    if (x>=pos[i].x && x<=pos[i].x + Button[i].GetWidth() &&
                        y>=pos[i].y && y<=pos[i].y + Button[i].GetHeight())
                    {
                        if(!Button_status[i])
                        {
                            Button_status[i] = 1;
                            Button[i].Free();
                            Button[i].SetColor(But_color[1]);
                            Button[i].LoadFromRenderText(font_time,screen);
                            Button[i].RenderText(screen,pos[i].x, pos[i].y);
                            SDL_RenderPresent(screen);
                        }
                    } else
                    {
                        if(Button_status[i])
                        {
                            Button_status[i] = 0;
                            Button[i].Free();
                            Button[i].SetColor(But_color[0]);
                            Button[i].LoadFromRenderText(font_time,screen);
                            Button[i].RenderText(screen,pos[i].x, pos[i].y);
                            SDL_RenderPresent(screen);
                        }
                    }
                }
                break;
            case SDL_MOUSEBUTTONDOWN:
                SDL_GetMouseState(&x, &y);
                for (int i=0;i<BUT_NUM;++i)
                {
                    if (x>=pos[i].x && x<=pos[i].x + Button[i].GetWidth() &&
                        y>=pos[i].y && y<=pos[i].y + Button[i].GetHeight())
                    {
                        for (int j =0;j<BUT_NUM;j++)
                        {
                            Button[j].Free();
                        }
                        return i;
                    }
                }
                break;
            case SDL_KEYDOWN:
                if (event.key.keysym.sym == SDLK_ESCAPE)
                {
                    for (int j =0;j<BUT_NUM;j++)
                    {
                            Button[j].Free();
                    }
                    return 0;
                }
                break;
            }
        }
    }
}

int main(int argc, char* argv[])
{
    Timer fps_timer, Threatt_timer;
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
    Threatt_timer.start();

    Text_object Time_game;
    Time_game.SetColor(255, 255, 255);
    int i = Menu(renderer, font_time, 1);
        if (i==1)
        {
            quitG=true;
        }
    while (!quitG)
    {
        fps_timer.start();
        while(SDL_PollEvent(&event) != 0)
        {
            if(event.type == SDL_QUIT)
            {
                quitG=true;
            }
            if(event.type == SDL_KEYDOWN)
            {
                if (event.key.keysym.sym == SDLK_ESCAPE){
                    int i = Menu(renderer, font_time, 0);
                    if (i==1)
                    {
                        quitG = true;
                    }
                }
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
                if (threat_object->GetRevTime() == 0){
                    threat_object->Show(renderer);
                }
            }
        }
        for (int i=0; i < list_threats.size(); ++i)
        {
            ThreatObject* threat_check = list_threats[i];
            if (threat_check != NULL && threat_check->GetRevTime() == 0)
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
                        list_threats[i]->SetRevTime(100);
                    }
                }
                if (&Player1 != NULL)
                {
                    SDL_Rect PRect = Player1.GetRectP();
                    if (Common_Func::CheckCollision(PRect, TRect))
                    {
                        if (Threatt_timer.get_tick() >= 1500)
                        {
                            Player1.HP-=50;
                            Threatt_timer.start();
                        }
                    }
                }
            }
        }

        Player1.DoPlayer(map_data);
        Player1.Show(renderer);
        Player1.ShowHP(font_time, renderer);
        Game_map.SetMap(map_data);
        Game_map.DrawMap(renderer);

        std::string str_time = "Time: ";
        Uint32 current_time = SDL_GetTicks()/1000;
        std::string str_val = std::to_string(current_time);
        str_time += str_val;

        Time_game.SetText(str_time);
        Time_game.LoadFromRenderText(font_time, renderer);
        Time_game.RenderText(renderer, SCREEN_WIDTH - 128, 15);


        SDL_RenderPresent(renderer);
        int real_timer = fps_timer.get_tick();
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
