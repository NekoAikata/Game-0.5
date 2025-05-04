#include "Game_Stat.h"
#include "BObject.h"
#include "Map.h"
#include "Main_o.h"
#include "Timer.h"
#include "ThreatObject.h"
#include "Text.h"
#include "BossThreat.h"
#include "Explosion.h"

BaseObject background;
TTF_Font* font_time = nullptr;
TTF_Font* font_menu = nullptr;
TTF_Font* font_slash = nullptr;
TTF_Font* font_noti = nullptr;
TTF_Font* font_title = nullptr;
TTF_Font* font_combat = nullptr;
Mix_Music* BGM = nullptr;
Mix_Music* FirstBattleBGM = nullptr;
Mix_Music* CaveBattleBGM = nullptr;
Mix_Music* FinalBattleBMG = nullptr;
TTF_Font* Font_noti_2 = nullptr;

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

    int MixFlag = MIX_INIT_MP3;
    if (!(Mix_Init(MixFlag) && MixFlag)) return false;

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
    font_menu = TTF_OpenFont("font//PixelPurl.ttf", 60);
    font_slash = TTF_OpenFont("font//PixelPurl.ttf",25);
    font_noti = TTF_OpenFont("font//PixelPurl.ttf",35);
    font_title = TTF_OpenFont("font//PixelPurl.ttf",100);
    font_combat = TTF_OpenFont("font//PixelPurl.ttf",40);
    Font_noti_2 = TTF_OpenFont("font//PixelPurl.ttf",80);

    if (font_time == NULL || font_menu == NULL || font_slash == NULL)
    {
        return false;
    }
    return true;
}

bool LoadBG(const int& level, SDL_Renderer* screen)
{
    std::string path; bool ret;
    if (level == 1 || level == 2 || level == 3)
    {
        path = "img//grass2.png";
    } else if (level == 4 || level == 5)
    {
        path = "img//ground.png";
    } else if (level == 6)
    {
        path = "img//grass1.png";
    }
    ret = background.LoadImg(path, renderer);
    background.SetRect(0,0);
    background.SetRectWH(SCREEN_WIDTH,SCREEN_HEIGHT);
    background.Render(screen);
    return ret;
}

bool LoadBGM()
{
    BGM = Mix_LoadMUS("Music_Sound//Music.mp3");
    FirstBattleBGM = Mix_LoadMUS("Music_Sound//Music_1.mp3");
    //CaveBattleBGM = Mix_LoadMUS("Music_Sound//Music_2.mp3")
    //FinalBattleBMG = Mix_LoadMUS("Music_Sound//Music_3.mp3")
    return BGM != NULL;
}

void close()
{
    background.Free();
    Mix_FreeMusic(BGM);
    BGM = NULL;

    SDL_DestroyRenderer(renderer);
    renderer = NULL;

    SDL_DestroyWindow(window);
    window = NULL;

    Mix_Quit();
    IMG_Quit();
    SDL_Quit();
}

void close1()
{
    background.Free();

    SDL_DestroyRenderer(renderer);
    renderer = NULL;

    SDL_DestroyWindow(window);
    window = NULL;

    IMG_Quit();
}

int HandleEndGame(int current_time, MainObject Player1, bool& quitG);

std::vector<ThreatObject*> MakeThreatList ();

std::vector<BossThreat*> MakeBossThreatList ();

void SetLevelAndBG(const float& y_pos, int& level, SDL_Renderer* screen, TTF_Font* font);

int Menu(SDL_Renderer* screen, TTF_Font* font_time, bool Start, TTF_Font* font_title);

void Fade(SDL_Renderer* screen, int& level, TTF_Font* font)
{
    SDL_RenderClear(screen);
    Text_object Zone;
    Zone.SetColor(255, 255, 255);
    if (level == 1)
    {
        Zone.SetText("Home");
    } else if (level == 2)
    {
        Zone.SetText("Village");
    } else if (level == 3)
    {
        Zone.SetText("Field");
    } else if (level == 4)
    {
        Zone.SetText("Cave Entrance");
    } else if (level == 5)
    {
        Zone.SetText("Deep Cave");
    } else
    {
        Zone.SetText("???");
    }
    for (int i = 1;i <= 10;++i)
    {
        LoadBG(level,screen);
        SDL_Rect x = {0,0,SCREEN_WIDTH,SCREEN_HEIGHT};
        SDL_SetRenderDrawBlendMode(screen,SDL_BLENDMODE_BLEND);
        SDL_SetRenderDrawColor(screen, 0, 0, 0, 25*i);
        SDL_RenderFillRect(screen, &x);
        Zone.LoadFromRenderText(font,screen);
        Zone.RenderText(screen, SCREEN_WIDTH/2 - Zone.GetWidth()/2, SCREEN_HEIGHT/2 - Zone.GetHeight()/2);
        SDL_RenderPresent(screen);
        SDL_Delay(50);
        SDL_RenderClear(screen);
    }
    SDL_RenderClear(screen);
}

void FadeOut(SDL_Renderer* screen, int& level, TTF_Font* font)
{
    SDL_RenderClear(screen);
    Text_object Zone;
    Zone.SetColor(255, 255, 255);
    if (level == 1)
    {
        Zone.SetText("Home");
    } else if (level == 2)
    {
        Zone.SetText("Village");
    } else if (level == 3)
    {
        Zone.SetText("Field");
    } else if (level == 4)
    {
        Zone.SetText("Cave Entrance");
    } else if (level == 5)
    {
        Zone.SetText("Deep Cave");
    } else
    {
        Zone.SetText("Castle_Outside");
    }
    for (int i = 10;i >= 1; i--)
    {
        LoadBG(level, screen);
        SDL_Rect x = {0,0,SCREEN_WIDTH,SCREEN_HEIGHT};
        SDL_SetRenderDrawColor(screen, 0, 0, 0, 25*i);
        SDL_RenderFillRect(screen, &x);
        Zone.LoadFromRenderText(font,screen);
        Zone.RenderText(screen, SCREEN_WIDTH/2 - Zone.GetWidth()/2, SCREEN_HEIGHT/2 - Zone.GetHeight()/2);
        SDL_RenderPresent(screen);
        SDL_Delay(50);
        SDL_RenderClear(screen);
    }
}

int main(int argc, char* argv[])
{
    std::random_device rd;
    std::mt19937 gen(std::time(0) ^ reinterpret_cast<uintptr_t>(&gen));

    std::bernoulli_distribution TDL1(0.05);
    std::bernoulli_distribution TDL2(0.1);
    std::bernoulli_distribution TDL3(0.2);
    std::bernoulli_distribution TDL4(0.4);
    std::bernoulli_distribution TDL5(0.6);

    bool running = true;
    while (running){
        int level = 1;
        Timer fps_timer, Threatt_timer, Slash_cooldown, Run_time;

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
        if (!LoadBGM())
        {
            return -1;
        }

        GameMap Game_map;
        Game_map.LoadMap("map/map1.dat");
        Game_map.LoadTiles(renderer);

        MainObject Player1;
        Player1.LoadImg("img//player_down.png", renderer);
        Player1.Clip();

        std::vector <ThreatObject*> list_threats = MakeThreatList();
        std::vector <BossThreat*> list_boss = MakeBossThreatList();

        ExplosionObject exp_threat;
        //bool tRet =

        bool quitG = false;

        bool intro = true;
        bool MOVE=true, attack=true;
        bool threat_hit = false, killed_threat = false, hit_threat = false;

        Threatt_timer.start();
        Slash_cooldown.start();

        Text_object Time_game;
        Time_game.SetColor(255, 255, 255);


        int i = Menu(renderer, font_menu, 1, font_title);
            if (i==1)
            {
                running = false;
                quitG = true;
            }

        if(Mix_PlayingMusic() == 0)
        {
            Mix_PlayMusic(BGM, -1);
        }
        Run_time.start();
        while (!quitG)
        {
            if (Mix_PausedMusic () == 1)
            {
                Mix_ResumeMusic();
            }
            fps_timer.start();
            while(SDL_PollEvent(&event) != 0)
            {
                if(event.type == SDL_QUIT)
                {
                    running=false;
                    quitG=true;
                }
                if(event.type == SDL_KEYDOWN)
                {
                    if (event.key.keysym.sym == SDLK_ESCAPE){

                        Run_time.paused();
                        SDL_Rect fill_rect = {SCREEN_WIDTH/2 - 128,10*TILE_SIZE/2, 256, 128};
                        SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
                        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 128);
                        SDL_RenderFillRect(renderer, &fill_rect);
                        Mix_PauseMusic();

                        int i = Menu(renderer, font_menu, 0, font_title);
                        if (i==1)
                        {
                            Mix_HaltMusic();
                            quitG = true;
                        }
                        if (i==2)
                        {
                            quitG = true;
                            running = false;
                        }
                        Run_time.unpaused();
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
                    if (event.key.keysym.sym == SDLK_k && Player1.HP_potion > 0)
                    {
                        Player1.HP_potion--;
                        if (Player1.HP + Player1.maxHP/10 > Player1.maxHP) Player1.HP = Player1.maxHP;
                        else Player1.HP +=Player1.maxHP/10;
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
            float Player_y = Player1.GetYPos();

            SetLevelAndBG(Player_y, level, renderer, font_title);
            for (int i = 0;i < list_boss.size(); i++)
            {
                BossThreat* boss_object = list_boss[i];
                if(boss_object != NULL)
                {
                    boss_object->SetMapXY(map_data.start_x, map_data.start_y);
                    boss_object->Show(renderer);
                }
            }

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
            if (&Player1 != NULL)
            {
                SDL_Rect PRect = Player1.GetRectP();
                for (int i = 0;i<list_boss.size();++i)
                {
                    BossThreat* Boss_check = list_boss[i];
                    if (Boss_check != NULL)
                    {
                        SDL_Rect BRect;
                            BRect.x = Boss_check->GetRect().x;
                            BRect.y = Boss_check->GetRect().y;
                            BRect.w = 128;
                            BRect.h = 128;
                        if (Common_Func::CheckCollision(PRect,BRect))
                        {
                            SDL_RenderClear(renderer);

                            if (Mix_PlayingMusic() == 1)
                            {
                                Mix_HaltMusic();
                            }
                            if (list_boss[i]->GetType() <=1)
                            {
                                Mix_PlayMusic(FirstBattleBGM, -1);
                            }
                            list_boss[i]->battle = true;
                            int result = list_boss[i]->BossCombat(Player1,font_noti,renderer,font_menu, Font_noti_2);
                            if (result == 1){
                                Player1.UpdateBattleStatus(false);
                                Player1.xp += list_boss[i]->XP_drop;
                                list_boss[i]->Free();
                                list_boss.erase (list_boss.begin() + i);
                                Player1.UpdateImg(renderer);
                                Player1.Clip();
                                if(Mix_PlayingMusic() == 0)
                                {
                                    Mix_PlayMusic(BGM, -1);
                                }
                                continue;
                            } else if (result == 0)
                            {
                                Player1.UpdateBattleStatus(false);
                                Player1.UpdateImg(renderer);
                                Player1.Clip();
                                list_boss[i]->battle = false;
                                list_boss[i]->HP = list_boss[i]->maxHP;
                                list_boss[i]->attack = false;
                                list_boss[i]->count_turn = 0;
                                if(Mix_PlayingMusic() == 0)
                                {
                                    Mix_PlayMusic(BGM, -1);
                                }
                                continue;
                            } else if (result == 2)
                            {
                                quitG = true;
                                running = false;
                            } else if (result == -1)
                            {
                                quitG = true;
                            }
                        }
                    }
                }
                for (int i=0; i < list_threats.size(); ++i)
                {
                    ThreatObject* threat_check = list_threats[i];
                    if (list_threats[i]->GetRevTime() >= 975)
                    {
                        std::string y = std::to_string(list_threats[i]->HP_drop);
                        y = "+" + y;
                        PHeal.SetText(y);
                        PHeal.LoadFromRenderText(font_slash,renderer);
                        PHeal.RenderText(renderer,PRect.x + PRect.w -10,PRect.y);
                    }
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
                                std::string x = std::to_string(Player1.ATK);
                                x = "-" + x;
                                Dmg.SetText(x);
                                if (Slash_cooldown.get_tick() >= 750)
                                {
                                    if (!hit_threat)
                                    {
                                        hit_threat = true;
                                    }
                                    list_threats[i]->HP -=Player1.ATK;
                                    Dmg.LoadFromRenderText(font_slash, renderer);
                                    Dmg.RenderText(renderer, TRect.x -40, TRect.y -40);
                                    if ((list_threats[i]->HP) < 0)
                                    {
                                        if (!killed_threat)
                                        {
                                            killed_threat = true;
                                            Player1.HP_potion++;
                                        }
                                        int x = list_threats[i]->GetType();
                                        if (x==0){if (TDL1(gen)) Player1.HP_potion++;}
                                        if (x==1){if (TDL2(gen)) Player1.HP_potion++;}
                                        if (x==2){if (TDL3(gen)) Player1.HP_potion++;}
                                        if (x==3){if (TDL4(gen)) Player1.HP_potion++;}
                                        if (x==4){if (TDL5(gen)) Player1.HP_potion++;}
                                        Player1.xp+=list_threats[i]->XP_drop;
                                        Player1.killed_threat++;
                                        if (Player1.HP + (list_threats[i]->HP_drop) > Player1.maxHP) Player1.HP = Player1.maxHP;
                                        else Player1.HP +=list_threats[i]->HP_drop;
                                        std::string y = std::to_string(list_threats[i]->HP_drop);
                                        y = "+" + y;
                                        PHeal.SetText(y);
                                        PHeal.LoadFromRenderText(font_slash,renderer);
                                        PHeal.RenderText(renderer,PRect.x + PRect.w -10,PRect.y);
                                        list_threats[i]->SetRevTime(1000);
                                    }
                                    Slash_cooldown.start();
                                }
                                if (Slash_cooldown.get_tick() <= 550)
                                {
                                    Dmg.LoadFromRenderText(font_slash, renderer);
                                    Dmg.RenderText(renderer, TRect.x -40, TRect.y -40);
                                }
                            }
                        }
                        if (Common_Func::CheckCollision(PRect, TRect))
                        {
                            std::string w = std::to_string(list_threats[i]->ATK);
                            w = "-" + w;
                            if (Threatt_timer.get_tick() >= 1500)
                            {
                                if (!threat_hit)
                                {
                                    threat_hit = true;
                                }
                                Player1.HP-=list_threats[i]->ATK;
                                PMinus.SetText(w);
                                PMinus.LoadFromRenderText(font_slash,renderer);
                                PMinus.RenderText(renderer,PRect.x + PRect.w -10,PRect.y - 20);
                                Threatt_timer.start();
                            }
                            if (Threatt_timer.get_tick() <= 850)
                            {
                                PMinus.SetText(w);
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

            Player1.HandleXP();

            //Show Stat_game
            SDL_Rect fill_rect = {SCREEN_WIDTH-160, 0, 160, 135};
            SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 128);
            SDL_RenderFillRect(renderer, &fill_rect);

            Text_object potionShow;
            std::string potion = "Heal_potion: " + std::to_string(Player1.HP_potion);
            potionShow.SetText(potion);
            potionShow.LoadFromRenderText(font_time, renderer);
            potionShow.RenderText(renderer, SCREEN_WIDTH -128, 115);

            std::string str_time = "Time: ";
            int current_time = (Run_time.get_tick() + Run_time.Store_pause)/1000;
            std::string str_val = std::to_string(current_time);
            str_time += str_val;

            Time_game.SetText(str_time);
            Time_game.LoadFromRenderText(font_time, renderer);
            Time_game.RenderText(renderer, SCREEN_WIDTH - 128, 15);

            Player1.ShowStat(font_time, renderer);


            if (intro){
                if(MOVE){
                    Noti.SetText("Use W,A,S,D to move");
                    Noti.LoadFromRenderText(font_noti,renderer);
                    Noti.RenderText(renderer,4*TILE_SIZE,30);
                } else if (!Player1.have_sword)
                {
                    Noti.SetText("Take sword in this room");
                    Noti.LoadFromRenderText(font_noti,renderer);
                    Noti.RenderText(renderer,3.5*TILE_SIZE,30);
                } else if (attack)
                {
                    Noti.SetText("Use J to attack with sword");
                    Noti.LoadFromRenderText(font_noti,renderer);
                    Noti.RenderText(renderer,3*TILE_SIZE,30);
                } else if (map_data.tile[390][1] == KEY)
                {
                    Noti.SetText("Get key and try small threats!");
                    Noti.LoadFromRenderText(font_noti,renderer);
                    Noti.RenderText(renderer,3*TILE_SIZE,30);
                } else if (!killed_threat){
                    if(Player_y <= 389*TILE_SIZE &&
                        Player_y >= 377*TILE_SIZE)
                        if (!threat_hit && !hit_threat)
                        {
                            Noti.SetText("You got hit when threat come close!");
                            Noti.LoadFromRenderText(font_noti,renderer);
                            Noti.RenderText(renderer,2*TILE_SIZE,30);
                        } else if (threat_hit && !hit_threat)
                        {
                            Noti.SetText("Use sword to hit them!");
                            Noti.LoadFromRenderText(font_noti,renderer);
                            Noti.RenderText(renderer,3.5*TILE_SIZE,30);
                        } else if(Player1.killed_threat == 0)
                        {
                            Noti.SetText("Kill them, you gain XP, HP, Potion (Press K to use)");
                            Noti.LoadFromRenderText(font_noti,renderer);
                            Noti.RenderText(renderer,2*TILE_SIZE,30);
                        } else
                        {
                            Noti.SetText("Let's test combat system with Lumberjack");
                            Noti.LoadFromRenderText(font_noti,renderer);
                            Noti.RenderText(renderer,2*TILE_SIZE,30);
                        }
                } else {intro = false;}
            }

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

            //Handle lose outside
            if (Player1.HP <= 0)
            {
                int i = HandleEndGame(current_time, Player1, quitG);
                if (i==1)
                {
                    running = false;
                }
            }
        }
        close1();
    }
    close();
    return 0;
}

int HandleEndGame(int current_time, MainObject Player1, bool& quitG){
    bool space_present = false;int check = 0;
    Timer space_countdown;
    BaseObject Lose;
    Text_object Loser, Space_noti, Stat;
    Stat.SetColor(255,255,255);
    Space_noti.SetText("Press Space_bar to continue");
    Space_noti.SetColor(255,255,255);
    if (!Player1.finish_game){
        Loser.SetText("You Lose!");
        Loser.SetColor(255, 255, 255);
        Lose.LoadImg("img/player_dead.png", renderer);
        SDL_Rect frame_clip[3];
        int check = 0;
        for (int i = 0;i < 3;++i)
        {
            frame_clip[i].x = i*((Lose.GetRect().w)/3);
            frame_clip[i].y = 0;
            frame_clip[i].w = (Lose.GetRect().w)/3;
            frame_clip[i].h = Lose.GetRect().h;
        }
        for (int i = 0;i < 3;++i)
        {
            SDL_RenderClear(renderer);
            SDL_Rect RenderQuad = {Player1.GetRect().x - 32, Player1.GetRect().y - 32, 192, 128};
            SDL_RenderCopy(renderer, Lose.GetTexture(), &frame_clip[i], &RenderQuad);
            SDL_RenderPresent(renderer);
            SDL_Delay(300);
        }
    }
    Loser.LoadFromRenderText(font_title, renderer);
    Loser.RenderText(renderer, SCREEN_WIDTH/2 - Loser.GetWidth()/2, 0);
    SDL_RenderPresent(renderer);
    while (!quitG)
    {
        if (space_countdown.start_check())space_countdown.start();
        if (space_countdown.get_tick() > 2000 && !space_present)
        {
            Space_noti.LoadFromRenderText(font_menu, renderer);
            Space_noti.RenderText(renderer,SCREEN_WIDTH/2 - Space_noti.GetWidth()/2, SCREEN_HEIGHT - Space_noti.GetHeight());
            SDL_RenderPresent(renderer);
            space_present = true;
        }
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_KEYDOWN)
            {
                if (event.key.keysym.sym == SDLK_SPACE)
                {
                    check++;
                    space_countdown.stop();
                    space_present = false;
                    SDL_RenderClear(renderer);
                }
            }
            if (event.type == SDL_QUIT)
            {
                quitG = true;
                return 1;
            }
        }
        if (check == 1)
        {
            Loser.SetText("Game_Statistics");
            SDL_Rect Outline = {SCREEN_WIDTH/2 - 64 - 32, SCREEN_HEIGHT/2 - 32, 192, 128};
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            SDL_RenderDrawRect(renderer, &Outline);
            Loser.LoadFromRenderText(Font_noti_2, renderer);
            Loser.RenderText(renderer, SCREEN_WIDTH/2 - Loser.GetWidth()/2, Outline.y - Loser.GetHeight() -8);
            int y_val = 0;

            //Stat_end_game
            std::string str_time = "Played_time: ";
            int x = ((current_time/60)/60)/24; current_time -= (x*24*60*60);
            str_time += std::to_string(x) + "d";
            x = (current_time/60)/60; current_time -= (x*60*60);
            str_time += std::to_string(x) + "h";
            x = current_time/60; current_time -= (x*60);
            str_time += std::to_string(x) + "m";
            str_time += std::to_string(current_time) + "s";
            Stat.SetText(str_time);
            Stat.LoadFromRenderText(font_time, renderer);
            y_val += Stat.GetHeight() + 10;
            Stat.RenderText(renderer, Outline.x + 16, Outline.y + y_val);
            Stat.Free();
            Stat.SetText("Level: " + std::to_string(Player1.level));
            Stat.LoadFromRenderText(font_time, renderer);
            y_val += Stat.GetHeight() + 10;
            Stat.RenderText(renderer, Outline.x + 16, Outline.y + y_val);
            Stat.Free();
            Stat.SetText("Killed_threats: " + std::to_string(Player1.killed_threat));
            Stat.LoadFromRenderText(font_time, renderer);
            y_val += Stat.GetHeight() + 10;
            Stat.RenderText(renderer, Outline.x + 16, Outline.y + y_val);
            SDL_RenderPresent(renderer);
            check++;
        } else if (check == 2)
        {
            if (space_countdown.start_check())space_countdown.start();
            if (space_countdown.get_tick() > 2000 && !space_present)
            {
                Space_noti.LoadFromRenderText(font_menu, renderer);
                Space_noti.RenderText(renderer,SCREEN_WIDTH/2 - Space_noti.GetWidth()/2, SCREEN_HEIGHT - Space_noti.GetHeight());
                SDL_RenderPresent(renderer);
                space_present = true;
            }
        }
        else if (check == 3)
        {
            Mix_HaltMusic();
            quitG = true;
        }
    }
    return 0;
}

int Menu(SDL_Renderer* screen, TTF_Font* font_time, bool Start, TTF_Font* font_title)
{
    int x,y;
    const int BUT_NUM = 2;
    const char* BUTTON[BUT_NUM] = {"Continue","Exit to Menu"};
    if (Start)
    {

        BUTTON[0] = "New Game";
        BUTTON[1] = "Exit Game";
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
    Text_object Title;
    if (Start)
    {
        Title.SetText("SAVE THE KING!");
        Title.LoadFromRenderText(font_title, screen);
        Title.RenderText(screen,
                         SCREEN_WIDTH/2 - Title.GetWidth()/2, 0);
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
                Title.Free();
                if(!Start)
                {
                    return 2;
                } else
                {
                    return 1;
                }
                break;
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
                        Title.Free();
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

void SetLevelAndBG(const float& y_pos, int& level, SDL_Renderer* screen, TTF_Font* font)
{
    if (y_pos >= LEVEL_1*TILE_SIZE && y_pos <= 400*TILE_SIZE && level != 1)
    {
        level = 1;
        Fade(screen, level, font);
        FadeOut(screen, level, font);
        LoadBG(level, screen);
    } else if (y_pos >= LEVEL_1_5*TILE_SIZE && y_pos < LEVEL_1*TILE_SIZE && level != 2)
    {
        level = 2;
        Fade(screen, level, font);
        FadeOut(screen, level, font);
        LoadBG(level, screen);

    } else if (y_pos >= LEVEL_2*TILE_SIZE && y_pos < LEVEL_1_5*TILE_SIZE && level != 3)
    {
        level = 3;
        Fade(screen, level, font);
        FadeOut(screen, level, font);
        LoadBG(level, screen);

    } else if (y_pos >= LEVEL_3*TILE_SIZE && y_pos < LEVEL_2*TILE_SIZE && level != 4)
    {
        level = 4;
        Fade(screen, level, font);
        FadeOut(screen, level, font);
        LoadBG(level, screen);

    } else if (y_pos >= LEVEL_4*TILE_SIZE && y_pos < LEVEL_3*TILE_SIZE && level != 5)
    {
        level = 5;
        Fade(screen, level, font);
        FadeOut(screen, level, font);
        LoadBG(level, screen);
    } else if (y_pos < LEVEL_4*TILE_SIZE && level != 6)
    {
        level = 6;
        Fade(screen, level, font);
        FadeOut(screen, level, font);
        LoadBG(level, screen);
    }
}

std::vector<ThreatObject*> MakeThreatList ()
{
    std::vector<ThreatObject*> list_threats;
    std::ifstream OpenFile;
    OpenFile.open("map//threat.txt");
    ThreatObject* test_threat = new ThreatObject;
        test_threat->LoadImg("img//threat_slime.png",renderer);
        test_threat->Clip();
        int a,b; float x;
        int type, HP, ATK, HP_drop, XP_drop;
        OpenFile >> type;
        test_threat->SetType(type);
        test_threat->SetInputL(type);
        OpenFile >> x; test_threat->SetXpos(x*TILE_SIZE);
        OpenFile >> x; test_threat->SetYpos(x*TILE_SIZE);
        OpenFile >> a; test_threat->HP = a;
        OpenFile >> a; test_threat->ATK = a;
        OpenFile >> a; test_threat->HP_drop = a;
        OpenFile >> a; test_threat->XP_drop = a;
        test_threat->SetXYposRes();
        list_threats.push_back(test_threat);

    ThreatObject* dynamic_threat = new ThreatObject[20];
    OpenFile >> type;
    OpenFile >> HP;
    OpenFile >> ATK;
    OpenFile >> HP_drop;
    OpenFile >> XP_drop;

    for (int i = 0;i<20;i++)
    {
        ThreatObject* p_threat = (dynamic_threat + i);
        if (p_threat != NULL)
        {
            p_threat->SetType(type);
            p_threat->LoadImg("img//threat_slime.png",renderer);
            p_threat->Clip();
            p_threat->SetInputL(type);
            p_threat->HP = HP;
            p_threat->ATK = ATK;
            p_threat->XP_drop = XP_drop;
            p_threat->HP_drop = HP_drop;
            OpenFile >> x; p_threat->SetXpos(x*TILE_SIZE);
            OpenFile >> x; p_threat->SetYpos(x*TILE_SIZE);
            OpenFile >> a >> b;
            p_threat->SetBorderX(a*TILE_SIZE,b*TILE_SIZE);
            p_threat->SetXYposRes();
            list_threats.push_back(p_threat);
        }
    }

    ThreatObject* threats = new ThreatObject[20];
    OpenFile >> type;
    OpenFile >> HP;
    OpenFile >> ATK;
    OpenFile >> HP_drop;
    OpenFile >> XP_drop;

    for (int i =0; i < 20;i++)
    {
        ThreatObject* p_threat = (threats + i);
        if (p_threat != NULL)
        {
            p_threat->SetType(type);
            p_threat->LoadImg("img//threat_slime.png",renderer);
            p_threat->Clip();
            p_threat->SetInputL(type);
            p_threat->HP = HP;
            p_threat->ATK = ATK;
            p_threat->XP_drop = XP_drop;
            p_threat->HP_drop = HP_drop;
            OpenFile >> x; p_threat->SetXpos(x*TILE_SIZE);
            OpenFile >> x; p_threat->SetYpos(x*TILE_SIZE);
            list_threats.push_back(p_threat);
        }
    }
    OpenFile.close();
    return list_threats;
}

std::vector <BossThreat*> MakeBossThreatList ()
{
    std::vector <BossThreat*> BossList;
    std::ifstream OpenFile;
    OpenFile.open("map//BossThreat.txt");
    float a; int b; double x;
    for (int i = 0;i<6;++i)
    {
        BossThreat* p_boss = new BossThreat;
        OpenFile >> b; p_boss->SetType(b);
        if (i==0) p_boss->LoadImg("img//MiniLumberjack.png", renderer);
        if (i==1) p_boss->LoadImg("img//Mushroom.png", renderer);
        if (i==2) p_boss->LoadImg("img//rat.png", renderer);
        if (i==3) p_boss->LoadImg("img//spider.png", renderer);
        if (i==4) p_boss->LoadImg("img//skeleton.png", renderer);
        if (i==5) p_boss->LoadImg("img//King_Pig.png", renderer);
        p_boss->Clip();
        OpenFile >> a; p_boss->SetXpos(a*TILE_SIZE);
        OpenFile >> a; p_boss->SetYpos(a*TILE_SIZE);
        OpenFile >> b; p_boss->HP = b; p_boss->maxHP = b;
        OpenFile >> b; p_boss->ATK = b;
        OpenFile >> b; p_boss->SPEED = b;
        OpenFile >> b; p_boss->XP_drop = b;
        OpenFile >> x; p_boss->EF_RES = x;
        BossList.push_back(p_boss);
    }
    OpenFile.close();
    return BossList;
}
