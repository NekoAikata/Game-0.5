#include "BossThreat.h"

BossThreat::BossThreat()
{
    HP=500;
    ATK=20;
    SPEED=200;

    x_pos = 0;
    y_pos = 0;

    width_frame = 0;
    height_frame = 0;
    frame_num = 0;
    mapvalue_x;
    mapvalue_y;

    type = 0;
    battle = false;
}

BossThreat::~BossThreat ()
{

}

bool BossThreat::LoadImg (std::string path, SDL_Renderer* screen)
{
	bool ret = BaseObject::LoadImg(path, screen);

    if (ret)
    {
        height_frame = rect.h;
        width_frame = rect.w/12;
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
	frame_num++;
    if (frame_num >= 12)
    {
        frame_num = 0;
    }
    SDL_Rect renderQuad;
    if (!battle){
        rect.x = x_pos - mapvalue_x;
        rect.y = y_pos - mapvalue_y;
        renderQuad = {rect.x, rect.y, 128, 128};
    } else {renderQuad = {rect.x, rect.y, 224, 224};}

    SDL_Rect* current_clip = &frame_clip[frame_num];

    SDL_RenderCopy(des, texture, current_clip, &renderQuad);
}

int BossThreat::BossCombat (MainObject Player, TTF_Font* font_combat, SDL_Renderer* screen, TTF_Font* font_noti)
{
    int PCD = Player.SPEED;
    int BCD = SPEED;
    int defense = 0;
    int result = 0;
    SDL_RenderClear(screen);
    BaseObject background;

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

    Text_object Notifi;
    Text_object PMinus, PHeal, Dmg;
    Notifi.SetColor(But_color[0]);
    PMinus.SetColor(255,0,0);
    PHeal.SetColor(0,0,255);

    Timer threat_delay;

    for (int i = 0; i < BUT_NUM; i++)
    {
        Button[i].SetText(BUTTON[i]);
        Button[i].SetColor(But_color[0]);
        Button[i].LoadFromRenderText(font_noti,renderer);
        if (i==0){
            pos[i].x = 0;
            pos[i].y = SCREEN_HEIGHT - 5*Button[i].GetHeight()/2;
        } else if (i==1)
        {
            pos[i].x = SCREEN_WIDTH/2;
            pos[i].y = SCREEN_HEIGHT - 5*Button[i].GetHeight()/2;
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
        if (PCD > 0 && BCD > 0) {PCD--; BCD--;}

        background.LoadImg("img//grass.png", screen);
        background.SetRect(0,0);
        background.SetRectWH(SCREEN_WIDTH, SCREEN_HEIGHT);
        background.Render(screen);

        for (int i=0; i< BUT_NUM;++i)
        {
            Button[i].LoadFromRenderText(font_combat,screen);
            Button[i].RenderText(screen,pos[i].x,pos[i].y);
        }

        Player.ShowBattleStat(font_combat,screen);

        fps_timer.start();
        Player.Show(screen);

        Show(screen);
        SDL_RenderPresent(screen);
        if (PCD == 0){
            while (SDL_PollEvent(&event))
            {
                if (event.type == SDL_QUIT){
                    for (int i=0;i<BUT_NUM;i++)
                    {
                        Button[i].Free();
                    }
                    running = false;
                    break;
                }
                else if (event.type == SDL_MOUSEBUTTONDOWN){
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
                            PCD = Player.SPEED;
                            defense--;
                            if (i==0)
                            {
                                HP-=Player.ATK;
                                std::string x = "-" + std::to_string(Player.ATK);
                                Dmg.SetText(x);
                                Dmg.LoadFromRenderText(font_noti,screen);
                                Dmg.RenderText(screen, GetRect().x + 180, GetRect().y);
                                SDL_RenderPresent(screen);
                                SDL_Delay(500);
                            }
                            else if (i==1)
                            {
                                defense = 2;
                            }
                            else if (i==2)
                            {
                                Player.HP += Player.maxHP/10;
                                std::string x = "+" + std::to_string(Player.maxHP/10);
                                PHeal.SetText(x);
                                PHeal.LoadFromRenderText(font_noti,screen);
                                PHeal.RenderText(screen,Player.GetRect().x, Player.GetRect().y);
                                if (Player.HP > Player.maxHP)
                                {
                                    Player.HP = Player.maxHP;
                                }
                                SDL_RenderPresent(screen);
                                SDL_Delay(500);
                            }
                            if (i==3)
                            {
                                running = false;
                                break;
                            }
                        }
                    }
                }
                if (event.type == SDL_MOUSEMOTION){
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
        }
        else if (BCD == 0)
        {
            Notifi.SetText("Opponent is thinking");
            Notifi.LoadFromRenderText(font_noti, screen);
            Notifi.RenderText(screen, 2*TILE_SIZE, 50);
            if(!threat_delay.start_check()) threat_delay.start();
            if (threat_delay.get_tick()>2000)
            {
                Player.HP-=ATK;
                std::string x = "-" + std::to_string(ATK);
                PMinus.SetText(x);
                PMinus.LoadFromRenderText(font_noti,screen);
                PMinus.RenderText(screen, Player.GetRect().x, Player.GetRect().y);
                SDL_RenderPresent(screen);
                SDL_Delay(500);
                BCD = SPEED;
            }
        }
        SDL_RenderPresent(screen);
        int real_timer = fps_timer.get_tick();
            int time_per_frame = 1000/50;

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
