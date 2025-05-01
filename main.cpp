#include "Game_Stat.h"
#include "BObject.h"
#include "Map.h"
#include "Main_o.h"
#include "Timer.h"
#include "ThreatObject.h"
#include "Text.h"
#include "BossThreat.h"

BaseObject background;
TTF_Font* font_time;
TTF_Font* font_menu;
TTF_Font* font_slash;
TTF_Font* font_noti;

bool InitDataSuccess()
{
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
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

    if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
    {
        printf( "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError() );
        return false;
    }

    if (TTF_Init() == -1)
    {
        return false;
    }
    font_time = TTF_OpenFont("font//PixelPurl.ttf", 20);
    font_menu = TTF_OpenFont("font//PixelPurl.ttf", 80);
    font_slash = TTF_OpenFont("font//PixelPurl.ttf",25);
    font_noti = TTF_OpenFont("font//PixelPurl.ttf",35);
    if (font_time == NULL || font_menu == NULL || font_slash == NULL)
    {
        return false;
    }
    return true;
}

bool LoadBG(const int& level, SDL_Renderer* screen)
{
    std::string path; bool ret;
    if (level == 1 || level == 3 || level == 5)
    {
        path = "img//grass.png";
    } else if (level == 2)
    {
        path = "";
    } else if (level == 4)
    {
        path = "";
    }
    ret = background.LoadImg(path, renderer);
    background.SetRect(0,0);
    background.SetRectWH(SCREEN_WIDTH,SCREEN_HEIGHT);
    background.Render(screen);
    return ret;
}

void close()
{
    background.Free();

    SDL_DestroyRenderer(renderer);
    renderer = NULL;

    SDL_DestroyWindow(window);
    window = NULL;

    Mix_Quit();
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

void SetLevelAndBG(const float& y_pos, int& level);
int Menu(SDL_Renderer* screen, TTF_Font* font_time, bool Start);

int main(int argc, char* argv[])
{
    int level = 1;
    Timer fps_timer, Threatt_timer, Slash_cooldown;

    Text_object Noti;
    Text_object PMinus, PHeal, Dmg;
    PMinus.SetColor(255,0,0);
    PHeal.SetColor(0,0,255);


    if (!InitDataSuccess())
    {
        return -1;
    }
    if (!LoadBG(level, renderer))
    {
        return -1;
    }

    GameMap Game_map;
    Game_map.LoadMap("map/map.dat");
    Game_map.LoadTiles(renderer);

    MainObject Player1;
    Player1.LoadImg("img//player_down.png", renderer);
    Player1.Clip();

    BossThreat Boss1;
    Boss1.LoadImg("img//King_Pig.png", renderer);
    Boss1.Clip();
    Boss1.SetXpos(5*TILE_SIZE);
    Boss1.SetYpos(375*TILE_SIZE);

    std::vector <ThreatObject*> list_threats = MakeThreatList();

    bool quitG = false;

    bool intro = true;
    bool MOVE=true; bool attack=true;

    Threatt_timer.start();
    Slash_cooldown.start();

    Text_object Time_game;
    Time_game.SetColor(255, 255, 255);
    int i = Menu(renderer, font_menu, 1);
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
                    int i = Menu(renderer, font_menu, 0);
                    if (i==1)
                    {
                        quitG = true;
                    }
                }
                if ((event.key.keysym.sym == SDLK_w ||
                    event.key.keysym.sym == SDLK_a ||
                    event.key.keysym.sym == SDLK_s ||
                    event.key.keysym.sym == SDLK_d) &&
                    MOVE)
                {
                    MOVE = false;
                }
                if (event.key.keysym.sym == SDLK_j && attack && Player1.have_sword)
                {
                    attack = false;
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
        Boss1.SetMapXY(map_data.start_x, map_data.start_y);


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
            if (&Player1 != NULL)
                {
                    SDL_Rect PRect = Player1.GetRectP();
            ThreatObject* threat_check = list_threats[i];
            if (threat_check != NULL && threat_check->GetRevTime() == 0)
            {
                SDL_Rect TRect;
                    TRect.x = threat_check->GetRect().x; TRect.x +=20;
                    TRect.y = threat_check->GetRect().y; TRect.y +=20;
                    TRect.w = threat_check->GetWidthFrame(); TRect.w -=20;
                    TRect.h = threat_check->GetHeightFrame(); TRect.h -=20;

                Slash* SCheck = Player1.GetSlash();
                if (SCheck != NULL)
                {
                    SDL_Rect SRect = SCheck->GetRect();
                    bool check = Common_Func::CheckCollision(TRect, SRect);

                    if(check)
                    {
                        if (Slash_cooldown.get_tick() >= 750)
                        {
                            (list_threats[i]->HP)-=25;
                            Dmg.SetText("-25");
                            Dmg.LoadFromRenderText(font_slash, renderer);
                            Dmg.RenderText(renderer, TRect.x -40, TRect.y -40);
                            if ((list_threats[i]->HP) == 0)
                            {
                                Player1.HP +=20;
                                PHeal.SetText("+20");
                                PHeal.LoadFromRenderText(font_slash,renderer);
                                PHeal.RenderText(renderer,PRect.x + PRect.w -10,PRect.y);
                                list_threats[i]->SetRevTime(200);
                            }
                            Slash_cooldown.start();
                        }
                        if (Slash_cooldown.get_tick() <= 250)
                        {
                            Dmg.SetText("-25");
                            Dmg.LoadFromRenderText(font_slash, renderer);
                            Dmg.RenderText(renderer, TRect.x -40, TRect.y -40);
                        }
                        if (list_threats[i]->GetRevTime() >= 30)
                        {
                            PHeal.SetText("+20");
                            PHeal.LoadFromRenderText(font_slash,renderer);
                            PHeal.RenderText(renderer,PRect.x + PRect.w -10,PRect.y);
                        }
                    }
                }
                    if (Common_Func::CheckCollision(PRect, TRect))
                    {
                        if (Threatt_timer.get_tick() >= 1500)
                        {
                            Player1.HP-=50;
                            PMinus.SetText("-50");
                            PMinus.LoadFromRenderText(font_slash,renderer);
                            PMinus.RenderText(renderer,PRect.x + PRect.w -10,PRect.y - 20);
                            Threatt_timer.start();
                        }
                        if (Threatt_timer.get_tick() <= 500)
                        {
                            PMinus.SetText("-50");
                            PMinus.LoadFromRenderText(font_slash,renderer);
                            PMinus.RenderText(renderer,PRect.x + PRect.w -10,PRect.y - 20);
                        }
                    }
                }
            }
        }

        Player1.DoPlayer(map_data);

        Game_map.SetMap(map_data);
        Game_map.DrawMap(renderer);

        Player1.FreeSlash();
        Player1.Show(renderer);

        Boss1.Show(renderer);

        //Show Stat_game
        SDL_Rect fill_rect = {SCREEN_WIDTH-160, 0, 160, 64};
        SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 128);
        SDL_RenderFillRect(renderer, &fill_rect);
        if (intro){
            if(MOVE){
                Noti.SetText("Use W,A,S,D to move");
                Noti.LoadFromRenderText(font_noti,renderer);
                Noti.RenderText(renderer,3*TILE_SIZE,30);
            } else if (!Player1.have_sword)
            {
                Noti.SetText("Take sword in this room");
                Noti.LoadFromRenderText(font_noti,renderer);
                Noti.RenderText(renderer,2.5*TILE_SIZE,30);
            } else if (attack)
            {
                Noti.SetText("Use J to attack with sword");
                Noti.LoadFromRenderText(font_noti,renderer);
                Noti.RenderText(renderer,2*TILE_SIZE,30);
            } else if (map_data.tile[390][1] == KEY)
            {
                Noti.SetText("Get key and save our king!");
                Noti.LoadFromRenderText(font_noti,renderer);
                Noti.RenderText(renderer,2*TILE_SIZE,30);
            } else {intro = false;}
        }

        std::string str_time = "Time: ";
        Uint32 current_time = SDL_GetTicks()/1000;
        std::string str_val = std::to_string(current_time);
        str_time += str_val;

        Time_game.SetText(str_time);
        Time_game.LoadFromRenderText(font_time, renderer);
        Time_game.RenderText(renderer, SCREEN_WIDTH - 128, 15);

        Player1.ShowHP(font_time, renderer);
        Player1.GetYPos();

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

int Menu(SDL_Renderer* screen, TTF_Font* font_time, bool Start)
{
    int x,y;
    const int BUT_NUM = 2;
    const char* BUTTON[BUT_NUM] = {"Continue","Exit"};
    if (Start)
    {
        BUTTON[0] = "Play";
        SDL_RenderClear(screen);
    }
    bool Button_status[BUT_NUM] = {0,0};
    SDL_Color But_color[2] = {{255,255,255},{255,0,0}};
    Text_object Button[BUT_NUM];
    SDL_Point pos[BUT_NUM];
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

void SetLevelAndBG(float y_pos, int level)
{

}
