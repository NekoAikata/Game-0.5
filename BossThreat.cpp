#include "BossThreat.h"

BossThreat::BossThreat()
{
    HP=0;
    ATK=0;
    SPEED=0;
    EF_RES=0;

    maxHP=0;
    count_turn=0;

    attack=false;

    x_pos = 0;
    y_pos = 0;

    width_frame = 0;
    height_frame = 0;
    frame_num = 0;
    mapvalue_x;
    mapvalue_y;

    type = 0;
    battle = false;
    dead = false;
}

BossThreat::~BossThreat ()
{

}

bool BossThreat::LoadImg (std::string path, SDL_Renderer* screen)
{
	bool ret = BaseObject::LoadImg(path, screen);

	height_frame = rect.h;

    if (ret && type == 5)
    {
        width_frame = rect.w/12;
    } else if (ret && (type == 0 || type == 2))
    {
        width_frame = rect.w/4;
    }
    else if (ret && type == 1)
    {
        width_frame = rect.w/7;
    } else if (ret && (type == 2 || type == 3 || type == 4))
    {
        width_frame = rect.w/6;
    }
    return ret;
}

void BossThreat::Clip()
{
    if (width_frame > 0 && height_frame > 0)
    {
        frame_clip[0].x = 0;
        frame_clip[0].y = 0;
        frame_clip[0].h = height_frame;
        frame_clip[0].w = width_frame;

        frame_clip[1].x = width_frame;
        frame_clip[1].y = 0;
        frame_clip[1].h = height_frame;
        frame_clip[1].w = width_frame;

        frame_clip[2].x = 2*width_frame;
        frame_clip[2].y = 0;
        frame_clip[2].h = height_frame;
        frame_clip[2].w = width_frame;

        frame_clip[3].x = 3*width_frame;
        frame_clip[3].y = 0;
        frame_clip[3].h = height_frame;
        frame_clip[3].w = width_frame;

        frame_clip[4].x = 4*width_frame;
        frame_clip[4].y = 0;
        frame_clip[4].h = height_frame;
        frame_clip[4].w = width_frame;

        frame_clip[5].x = 5*width_frame;
        frame_clip[5].y = 0;
        frame_clip[5].h = height_frame;
        frame_clip[5].w = width_frame;

        frame_clip[6].x = 6*width_frame;
        frame_clip[6].y = 0;
        frame_clip[6].h = height_frame;
        frame_clip[6].w = width_frame;

        frame_clip[7].x = 7*width_frame;
        frame_clip[7].y = 0;
        frame_clip[7].h = height_frame;
        frame_clip[7].w = width_frame;

        frame_clip[8].x = 8*width_frame;
        frame_clip[8].y = 0;
        frame_clip[8].h = height_frame;
        frame_clip[8].w = width_frame;

        frame_clip[9].x = 9*width_frame;
        frame_clip[9].y = 0;
        frame_clip[9].h = height_frame;
        frame_clip[9].w = width_frame;

        frame_clip[10].x = 10*width_frame;
        frame_clip[10].y = 0;
        frame_clip[10].h = height_frame;
        frame_clip[10].w = width_frame;

        frame_clip[11].x = 11*width_frame;
        frame_clip[11].y = 0;
        frame_clip[11].h = height_frame;
        frame_clip[11].w = width_frame;
    }
}

void BossThreat::Show(SDL_Renderer* des)
{
	frame_delay++;
    if (frame_delay >= FRAME_DELAY)
    {
        frame_delay = 0;
        frame_num++;
    }
    if (type == 5)
    {
        frame_num = frame_num >= 12 ? 0 : frame_num;
    } else if (type ==  0 || type == 2)
    {
       frame_num = frame_num >= 4 ? 0 : frame_num;
    }
    else if (type ==  1)
    {
       frame_num = frame_num >= 7 ? 0 : frame_num;
    } else
    {
        frame_num = frame_num >= 6 ? 0 : frame_num;
    }
    SDL_Rect renderQuad;
    if (!battle){
        rect.x = x_pos - mapvalue_x;
        rect.y = y_pos - mapvalue_y;
        if (type == 0) renderQuad = {rect.x, rect.y, 128, 96};
        else if (type == 1) renderQuad = {rect.x - 64, rect.y, 256, 128};
        else if (type == 2) renderQuad = {rect.x - 32, rect.y - 16, 192, 128};
        else if (type == 3) renderQuad = {rect.x, rect.y - 64, 128, 192};
        else renderQuad = {rect.x - 64, rect.y - 64, 256, 256};
    } else
    {
        if (type == 5) renderQuad = {rect.x, rect.y, 224, 224};
        else if (type == 0) renderQuad = {rect.x, rect.y + 64, 256, 160};
        else if (type == 1) renderQuad = {rect.x -64, rect.y+32, 288, 160};
        else if (type == 2) renderQuad = {rect.x , rect.y, 224, 224};
        else if (type == 3) renderQuad = {rect.x - 32 , rect.y, 224, 224};
        else if (type == 4) renderQuad = {rect.x  , rect.y, 224, 224};
    }

    SDL_Rect* current_clip = &frame_clip[frame_num];

    SDL_RenderCopy(des, texture, current_clip, &renderQuad);
}

void BossThreat::ShowHP(TTF_Font* font, SDL_Renderer* screen)
{
    Text_object HPNew;
    std::string HPText;
    if (type == 0) HPText = "LumberJack HP: " + std::to_string(HP);
    else if (type == 1) HPText = "MushMonster HP: " + std::to_string(HP);
    else if (type == 2) HPText = "Golem HP: " + std::to_string(HP);
    else if (type == 3) HPText = "Spider HP: " + std::to_string(HP);
    else if (type == 4) HPText = "Skeleton HP: " + std::to_string(HP);
    else if (type == 5) HPText = "King Pig HP: " + std::to_string(HP);
    std::string x = std::to_string(maxHP);
    HPText += "/" + x;
    HPNew.SetText(HPText);
    HPNew.LoadFromRenderText(font,screen);
    HPNew.RenderText(screen, SCREEN_WIDTH-HPNew.GetWidth(), 100);
}

int BossThreat::BossCombat (MainObject& Player, TTF_Font* font_combat, SDL_Renderer* screen, TTF_Font* font_noti, TTF_Font* font_title)
{
    std::random_device rd;
    std::mt19937 gen(std::time(0) ^ reinterpret_cast<uintptr_t>(&gen));

    std::uniform_int_distribution<int> dist_rngdmg(1,15);
    std::bernoulli_distribution EF(EF_RES);
    std::bernoulli_distribution EF2(EF_RES*1.5);

    int PCD = Player.SPEED;
    int BCD = SPEED;
    int defense = 0;

    int poison = 0; int para = 0;

    int result = 0;
    SDL_RenderClear(screen);
    BaseObject background;

    BaseObject IconPlayer;
    BaseObject IconBoss;

    BaseObject Para; BaseObject Poison;
    Para.LoadImg("img/para.png", screen);
    Para.SetRect(30, 165); Para.SetRectWH(64, 16);
    Poison.LoadImg("img/poison.png", screen);
    Poison.SetRect(94, 165); Poison.SetRectWH(64, 16);

    IconPlayer.LoadImg("img//PIcon.png", screen);
    if (type==5) IconBoss.LoadImg("img//King_Pig_Icon.png", screen);
    if (type==0) IconBoss.LoadImg("img//MLJ_Icon.png", screen);
    if (type==1) IconBoss.LoadImg("img//Mushroom_Icon.png", screen);
    if (type==2) IconBoss.LoadImg("img//rat_Icon.png", screen);
    if (type==3) IconBoss.LoadImg("img//spider_Icon.png", screen);
    if (type==4) IconBoss.LoadImg("img//skeleton_Icon.png", screen);

    Player.UpdateBattleStatus(true);
    Player.LoadImg("img//player_battle.png",screen);
    Player.Clip();
    Player.SetXPos(x_pos + TILE_SIZE/2);
    Player.SetYPos(y_pos + 2.5*TILE_SIZE);
    Player.SetRect(128,SCREEN_HEIGHT/2 - TILE_SIZE);

    SetRect(SCREEN_WIDTH-320,SCREEN_HEIGHT/2 - 2*TILE_SIZE);

    int x,y;
    const int BUT_NUM = 4;
    const char* BUTTON[BUT_NUM] = {"Attack","Defend","Heal","Back To Map"};
    bool Button_status[BUT_NUM] = {0,0,0,0};
    SDL_Color But_color[2] = {{255,255,255},{0,0,0}};
    Text_object Button[BUT_NUM];
    SDL_Point pos[BUT_NUM];

    SDL_Color StatColor[2] = {{255,0,0},{0,0,255}};

    Text_object Notifi;
    Text_object PMinus, PHeal, Dmg, PoisonDmg;
    Dmg.SetColor(But_color[0]);
    Notifi.SetColor(But_color[0]);
    PMinus.SetColor(StatColor[0]);
    PHeal.SetColor(StatColor[1]);
    PoisonDmg.SetColor(87, 87, 0);
    PoisonDmg.SetText("-" + std::to_string (Player.maxHP*3/100));

    int maxSpeed = Player.SPEED > SPEED ? Player.SPEED : SPEED ;

    Timer threat_delay;

    for (int i = 0; i < BUT_NUM; i++)
    {
        Button[i].SetText(BUTTON[i]);
        Button[i].SetColor(But_color[0]);
        Button[i].LoadFromRenderText(font_noti,renderer);
        if (i==0){
            pos[i].x = 0;
            pos[i].y = SCREEN_HEIGHT - 4*Button[i].GetHeight()/2;
        } else if (i==1)
        {
            pos[i].x = SCREEN_WIDTH/2;
            pos[i].y = SCREEN_HEIGHT - 4*Button[i].GetHeight()/2;
        } else if (i==2)
        {
            pos[i].x = 0;
            pos[i].y = SCREEN_HEIGHT - Button[i].GetHeight();
        } else
        {
            pos[i].x = SCREEN_WIDTH/2;
            pos[i].y = SCREEN_HEIGHT - Button[i].GetHeight();
        }
        Button[i].RenderText(screen,pos[i].x, pos[i].y);
    }
    SDL_RenderPresent(screen);
    Timer fps_timer;
    bool running = true;
    while (running)
    {
        if (PCD > 0 && BCD > 0 && HP > 0 && Player.HP > 0) {PCD--; BCD--;}

        if (type == 0 || type == 1){
            background.LoadImg("img//Battle_1.png", screen);
            background.SetRect(0,0);
            background.SetRectWH(SCREEN_WIDTH, SCREEN_HEIGHT);
            background.Render(screen);
        } else if (type == 2 || type == 3)
        {
            background.LoadImg("img//Battle_2.png", screen);
            background.SetRect(0,0);
            background.SetRectWH(SCREEN_WIDTH, SCREEN_HEIGHT);
            background.Render(screen);
        } else if (type == 4)
        {
            background.LoadImg("img//Battle_3.png", screen);
            background.SetRect(0,0);
            background.SetRectWH(SCREEN_WIDTH, SCREEN_HEIGHT);
            background.Render(screen);
        } else
        {
            background.LoadImg("img//Battle_4.png", screen);
            background.SetRect(0,0);
            background.SetRectWH(SCREEN_WIDTH, SCREEN_HEIGHT);
            background.Render(screen);
        }

        if (HP > 0 && Player.HP > 0)
        {
            for (int i=0; i< BUT_NUM;++i)
            {
                Button[i].LoadFromRenderText(font_combat,screen);
                Button[i].RenderText(screen,pos[i].x,pos[i].y);
            }
            SDL_Rect fillRect = {32, 16, SCREEN_WIDTH-TILE_SIZE, 14};
            SDL_SetRenderDrawColor(screen, 196, 196, 196, 255);
            SDL_RenderFillRect(screen, &fillRect );

            SDL_Rect outlineRect = {32, 16, SCREEN_WIDTH-TILE_SIZE, 14};
            SDL_SetRenderDrawColor(screen, 255, 255, 255, 255);
            SDL_RenderDrawRect(screen, &outlineRect);

            IconPlayer.SetRect(32 + 800*PCD/maxSpeed, 4);
            IconPlayer.SetRectWH(32, 32);
            IconPlayer.Render(screen);

            IconBoss.SetRect(32 + 800*BCD/maxSpeed, 7);
            IconBoss.Render(screen);
        }

        fps_timer.start();

        Player.Show(screen);
        Show(screen);

        ShowHP(font_combat,screen);
        SDL_RenderPresent(screen);
        if (PCD > 0 && HP > 0 && Player.HP > 0)
        {
            while (SDL_PollEvent(&event))
            {
                if (event.type == SDL_QUIT)
                {
                    result = 2;
                    running = false;
                }
            } if (!running) {break;}
        }

        if (HP <=0)
        {
            if (!threat_delay.start_check()) threat_delay.start();
            if (threat_delay.get_tick() > 2500)
            {
                Dmg.SetText("Press Space_bar to continue!");
                Dmg.LoadFromRenderText(font_combat, screen);
                Dmg.RenderText(screen, SCREEN_WIDTH/2 - Dmg.GetWidth()/2, SCREEN_HEIGHT/2 + Notifi.GetHeight()/2 - Dmg.GetHeight()/2);
            }
            Player.ShowBattleStat(font_combat,screen);
            ShowHP(font_combat,screen);
            Notifi.Free();
            Notifi.SetText("You won!");
            Notifi.LoadFromRenderText(font_title, screen);
            Notifi.RenderText(screen, SCREEN_WIDTH/2 - Notifi.GetWidth()/2, SCREEN_HEIGHT/2 - Notifi.GetHeight()/2);
            SDL_RenderPresent(screen);
            while (SDL_PollEvent(&event))
            {
                if (event.type == SDL_QUIT)
                {
                    result = 2;
                    running = false;
                    break;
                } else if (event.type = SDL_KEYDOWN)
                {
                    if (event.key.keysym.sym == SDLK_SPACE)
                    {
                        result = 1;
                        running = false;
                        if(Mix_PlayingMusic() == 1)
                        {
                            Mix_HaltMusic();
                        }
                        break;
                    }
                }
            } if (!running) break;
        } else if (Player.HP <=0)
        {
            if (!threat_delay.start_check()) threat_delay.start();
            if (threat_delay.get_tick() > 2500)
            {
                Dmg.SetText("Press Space_bar to continue!");
                Dmg.LoadFromRenderText(font_combat, screen);
                Dmg.RenderText(screen, SCREEN_WIDTH/2 - Dmg.GetWidth()/2, SCREEN_HEIGHT/2 + Notifi.GetHeight()/2 - Dmg.GetHeight()/2);
            }
            Player.ShowBattleStat(font_combat,screen);
            ShowHP(font_combat,screen);
            Notifi.Free();
            Notifi.SetText("You lose!");
            Notifi.LoadFromRenderText(font_title, screen);
            Notifi.RenderText(screen, SCREEN_WIDTH/2 - Notifi.GetWidth()/2, SCREEN_HEIGHT/2 - Notifi.GetHeight()/2);
            SDL_RenderPresent(screen);
            while (SDL_PollEvent(&event))
            {
                if (event.type == SDL_QUIT)
                {
                    result = 2;
                    running = false;
                    break;
                } else if (event.type = SDL_KEYDOWN)
                {
                    if (event.key.keysym.sym == SDLK_SPACE)
                    {
                        result = -1;
                        running = false;
                        if(Mix_PlayingMusic() == 1)
                        {
                            Mix_HaltMusic();
                        }
                        break;
                    }
                }
            } if (!running) break;
        }

        if (PCD == 0 && HP > 0 && Player.HP > 0)
        {
            Player.ShowBattleStat(font_combat,screen);
            if (para > 0)
            {
                Para.Render(screen);
            }
            if (poison > 0)
            {
                Poison.Render(screen);
            }
            Notifi.SetText("Your turn");
            Notifi.LoadFromRenderText(font_noti,screen);
            while (SDL_PollEvent(&event))
            {
                if (event.type == SDL_QUIT){
                    for (int i=0;i<BUT_NUM;i++)
                    {
                        Button[i].Free();
                    }
                    result = 2;
                    running = false;
                    break;
                }
                else if (event.type == SDL_MOUSEBUTTONDOWN)
                {
                    SDL_GetMouseState(&x, &y);
                    for (int i=0;i<BUT_NUM;++i)
                    {
                        if (x>=pos[i].x && x<=pos[i].x + Button[i].GetWidth() &&
                            y>=pos[i].y && y<=pos[i].y + Button[i].GetHeight())
                        {
                            for (int j =0;j<BUT_NUM;j++)
                            {
                                Button[j].Free();
                                Button[j].SetColor(But_color[0]);
                            }
                            if (i==0)
                            {
                                BaseObject SLASH;
                                SLASH.LoadImg("img/Slash_img.png", screen);
                                SLASH.SetRect(GetRect().x + 0.75*TILE_SIZE,GetRect().y + 1.5*TILE_SIZE);
                                if (type == 1) SLASH.SetRect(GetRect().x +0.15*TILE_SIZE,GetRect().y + 0.95*TILE_SIZE);
                                SLASH.SetRectWH(128,128);
                                SLASH.Render(screen);
                                Notifi.Free();
                                Notifi.SetText("You chose Attack");
                                Notifi.LoadFromRenderText(font_noti, screen);
                                int HPDown = Player.ATK*(84+dist_rngdmg(gen))/100;
                                HP-=HPDown;
                                std::string x = "-" + std::to_string(HPDown);
                                Dmg.SetText(x);
                                Dmg.LoadFromRenderText(font_noti,screen);
                                Dmg.RenderText(screen, GetRect().x + 180, GetRect().y);

                            }
                            else if (i==1)
                            {
                                Notifi.Free();
                                Notifi.SetText("You chose Defense");
                                Notifi.LoadFromRenderText(font_noti, screen);
                                defense = 2;
                            }
                            else if (i==2 && Player.HP_potion >0)
                            {
                                Notifi.Free();
                                Notifi.SetText("You chose Heal");
                                Notifi.LoadFromRenderText(font_noti, screen);
                                Player.HP += Player.maxHP/10;
                                Player.HP_potion--;
                                std::string x = "+" + std::to_string(Player.maxHP/10);
                                PHeal.SetText(x);
                                PHeal.LoadFromRenderText(font_noti,screen);
                                PHeal.RenderText(screen,Player.GetRect().x, Player.GetRect().y);
                                if (Player.HP > Player.maxHP)
                                {
                                    Player.HP = Player.maxHP;
                                }
                            } else if (i==2 && Player.HP_potion <=0)
                            {
                                continue;
                            }
                            if (i==3)
                            {
                                Notifi.Free();
                                Notifi.SetText("You chose Leave");
                                Notifi.LoadFromRenderText(font_noti, screen);
                                Mix_HaltMusic();
                                running = false;
                            }
                            if (para > 0)
                            {
                                PCD = Player.SPEED*1.5;
                            } else PCD = Player.SPEED;
                            if (poison > 0)
                            {
                                Player.HP -= Player.maxHP*3/100;
                                PoisonDmg.LoadFromRenderText(font_noti, screen);
                                PoisonDmg.RenderText(screen,Player.GetRect().x, Player.GetRect().y - 64);
                            }
                            defense--; para--; poison--;
                        }
                    }
                }

                if (event.type == SDL_MOUSEMOTION)
                {
                    SDL_GetMouseState(&x, &y);
                    for (int i=0;i<BUT_NUM;++i)
                    {
                        if (x>=pos[i].x && x<=pos[i].x + Button[i].GetWidth() &&
                            y>=pos[i].y && y<=pos[i].y + Button[i].GetHeight())
                        {
                            if(!Button_status[i])
                            {
                                if (!(i==2 && Player.HP_potion <=0)){
                                    Button_status[i] = 1;
                                    Button[i].Free();
                                    Button[i].SetColor(But_color[1]);
                                }
                                Button[i].LoadFromRenderText(font_combat,screen);
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
                                Button[i].LoadFromRenderText(font_combat,screen);
                                Button[i].RenderText(screen,pos[i].x, pos[i].y);
                                SDL_RenderPresent(screen);
                            }
                        }
                    }
                }
            }
            if (PCD != 0)
            {
                Notifi.RenderText(screen, 5.5*TILE_SIZE, 50);
                SDL_RenderPresent(screen);
                SDL_Delay(500);
            }
            else
            {
                SDL_GetMouseState(&x,&y);
                if (x>=pos[2].x && x<=pos[2].x + Button[2].GetWidth() &&
                    y>=pos[2].y && y<=pos[2].y + Button[2].GetHeight() && Player.HP_potion <=0)
                {
                    Notifi.Free();
                    Notifi.SetText("Not enough potion!");
                    Notifi.LoadFromRenderText(font_noti, screen);
                    Notifi.RenderText(screen, 4.5*TILE_SIZE, 50);
                }else Notifi.RenderText(screen, 7*TILE_SIZE, 50);

                SDL_RenderPresent(screen);
            }
            if (!running) break;
        }
        else if (BCD == 0 && HP>0 && Player.HP > 0)
        {
            if(!threat_delay.start_check()) threat_delay.start();
            if (threat_delay.get_tick()>2000)
            {
                attack=true;
                std::uniform_int_distribution<int> dist_crit(1,50);
                std::uniform_int_distribution<int> dist_skill(1,15);

                count_turn++;
                int damgage; int skill = dist_skill(gen);
                if ((skill ==1 || skill == 18 || skill == 3) && count_turn > 2)
                {
                    Notifi.Free();
                    Notifi.SetText("Opponent chose Ultimate!!!");
                    Notifi.LoadFromRenderText(font_noti, screen);
                    if (EF2(gen))
                    {
                        if (type == 1) poison = 2;
                        else if (type == 2 || type == 5)
                        {
                            para = 2;
                            if (EF(gen)) poison=2;
                        }
                        else if (type == 3) para = 2;
                    }
                    damgage = ATK*2;
                    count_turn=0;
                }
                else if (skill%2 == 1)
                {
                    Notifi.Free();
                    Notifi.SetText("Opponent chose Skill!");
                    Notifi.LoadFromRenderText(font_noti, screen);
                    damgage=1.5*ATK;
                    if (EF(gen))
                    {
                        if (type == 1) poison = 2;
                        else if (type == 2 || type == 5)
                        {
                            para = 2;
                            if (EF(gen)) poison = 1;
                        }
                        else if (type == 3) para = 2;
                    }
                }
                else
                {
                    Notifi.Free();
                    Notifi.SetText("Opponent chose Normal_attack");
                    Notifi.LoadFromRenderText(font_noti, screen);
                    damgage = ATK;
                }
                damgage = damgage*(84+dist_rngdmg(gen))/100;

                if(dist_crit(gen) == 1) damgage*=2;
                if (defense > 0) damgage/=2;

                Player.HP-=damgage;
                std::string dam = std::to_string(damgage);
                std::string x = "-" + dam;
                PMinus.SetText(x);
                PMinus.LoadFromRenderText(font_noti,screen);
                PMinus.RenderText(screen, Player.GetRect().x, Player.GetRect().y);
                SDL_RenderPresent(screen);
                SDL_Delay(500);
                threat_delay.stop();
                BCD = SPEED;
            } else
            {
                Notifi.SetText("Opponent is thinking");
                Notifi.LoadFromRenderText(font_noti, screen);
                Notifi.RenderText(screen, 3*TILE_SIZE, 50);
            }
        }
        SDL_RenderPresent(screen);
        SDL_RenderClear(screen);
        int real_timer = fps_timer.get_tick();
        int time_per_frame = 1000/60;

        if (real_timer < time_per_frame)
        {
            int delay_time = time_per_frame - real_timer;
            if (delay_time >= 0)
            {
                SDL_Delay(delay_time);
            }
        }
    }
    return result;
}
