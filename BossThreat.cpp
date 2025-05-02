#include "BossThreat.h"

BossThreat::BossThreat()
{
    HP=1500;
    ATK=0;
    SPEED=0;

    x_pos = 0;
    y_pos = 0;

    width_frame = 0;
    height_frame = 0;
    frame_num = 0;
    mapvalue_x;
    mapvalue_y;

    type = 0;
    dead = false;
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
    rect.x = x_pos - mapvalue_x;
    rect.y = y_pos - mapvalue_y;

    SDL_Rect* current_clip = &frame_clip[frame_num];

    SDL_Rect renderQuad = {rect.x, rect.y, 128, 128};
    SDL_RenderCopy(des, texture, current_clip, &renderQuad);
}

bool BossThreat::BossCombat (MainObject Player, TTF_Font* font_combat, SDL_Renderer* screen)
{
    Player.SetXPos(x_pos + TILE_SIZE);
    Player.SetYPos(y_pos + 4*TILE_SIZE);
    int x,y;
    const int BUT_NUM = 4;
    const char* BUTTON[BUT_NUM] = {"Attack","Defend","Heal","Back To Map"};
    bool Button_status[BUT_NUM] = {0,0,0,0};
    SDL_Color But_color[2] = {{255,255,255},{0,0,0}};
    Text_object Button[BUT_NUM];
    SDL_Point pos[BUT_NUM];
    for (int i = 0; i < BUT_NUM; i++)
    {
        Button[i].SetText(BUTTON[i]);
        Button[i].SetColor(But_color[0]);
        Button[i].LoadFromRenderText(font_combat,renderer);
        int height = (Button[i].GetHeight())/2;
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
                return false;
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
                        if (i==3)
                        {
                            return false;
                        }
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
