#include "Main_o.h"
#include "Timer.h"

MainObject::MainObject()
{
    x_val = 0;
    y_val = 0;
    x_pos = 6*TILE_SIZE;
    y_pos = 300*TILE_SIZE;

    width_frame = 0;
    height_frame = 0;
    frame_num = 0;

    status_character = DOWN;
    Store_action.down = 0;
    Store_action.up = 0;
    Store_action.left = 0;
    Store_action.right = 0;

    mapvalue_x = 0;
    mapvalue_y = 0;
    frame_delay = 0;

    xp = 0;
    xp_cap = 100;
    level = 1;

    HP_potion=0;

    maxHP = 100;
    ATK = 20;
    SPEED = 25;
    HP=maxHP;
    have_sword = false;
    battle = false;
    finish_game = false;
    killed_threat = 0;
}

MainObject::~MainObject()
{

}

bool MainObject::LoadImg(std::string path, SDL_Renderer* screen )
{
    bool ret = BaseObject::LoadImg(path, screen);

    if (ret)
    {
        height_frame = rect.h;
        if (BasicAttack.get_status() )
        {
            width_frame = rect.w/4;
        } else
        {
            width_frame = rect.w/6;
        }
    }

}

void MainObject::Clip()
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
    }
}

bool MainObject::Show(SDL_Renderer* des )
{
    UpdateImg(des);
    if (((Store_action.up == 1) && (Store_action.down == 1) &&
         (Store_action.left != 1) && (Store_action.right != 1))
          ||
        ((Store_action.left == 1) && (Store_action.right == 1) &&
         (Store_action.up != 1) && (Store_action.down != 1)))
    {
        frame_num = 0;
    }
    else if (Store_action.left == 1 ||
        Store_action.right == 1 ||
        Store_action.up == 1 ||
        Store_action.down == 1 ||
        BasicAttack.get_status() ||
             battle)
    {
        frame_delay++;
        if (frame_delay >= FRAME_DELAY)
        {
            frame_delay = 0;
            frame_num++;
        }
    }
    else{
        frame_num = 0;
    }

    if (frame_num >= 6 || (frame_num >=4 && BasicAttack.get_status() ))
    {
        frame_num = 0;
    }
    SDL_Rect renderQuad;
    if (!battle){
        rect.x = x_pos - mapvalue_x;
        rect.y = y_pos - mapvalue_y;
        renderQuad = {rect.x, rect.y, 78, 78};
    } else {renderQuad = {rect.x, rect.y, 192, 192};}

    SDL_Rect* current_clip = &frame_clip[frame_num];
    SDL_RenderCopy(des, texture, current_clip, &renderQuad);
}

void MainObject::HandleEvent(SDL_Event event, SDL_Renderer* screen)
{
    if(event.type == SDL_KEYDOWN)
    {
        switch (event.key.keysym.sym)
        {
        case SDLK_w:
            {
                status_character = UP;
                Store_action.up = 1;
                break;
            }
        case SDLK_s:
            {
                status_character = DOWN;
                Store_action.down = 1;
                break;
            }
        case SDLK_d:
            {
                status_character = RIGHT;
                Store_action.right = 1;
                break;
            }
        case SDLK_a:
            {
                status_character = LEFT;
                Store_action.left = 1;
                break;
            }
        case SDLK_j:
            {
                if (have_sword){
                    BasicAttack.set_attack(true);
                }
            }
        }
    } else if(event.type == SDL_KEYUP)
    {
        switch (event.key.keysym.sym)
        {
        case SDLK_w:
            {
                Store_action.up = 0;
                break;
            }
        case SDLK_s:
            {
                Store_action.down = 0;
                break;
            }
        case SDLK_d:
            {
                Store_action.right = 0;
                break;
            }
        case SDLK_a:
            {
                Store_action.left = 0;
                break;
            }
        case SDLK_j:
            {
                BasicAttack.set_attack(false);
            }
        }
    }
}

void MainObject::HandleSlash(SDL_Renderer* screen)
{
    if (( frame_num ==2) && BasicAttack.get_status())
    {
        BasicAttack.LoadImg("img//Slash.PNG", screen);
        if (Store_action.up == 1 || status_character == UP)
        {
            BasicAttack.SetRect(this->rect.x, this->rect.y - 25);
        } else if (Store_action.down == 1 || status_character == DOWN)
        {
            BasicAttack.SetRect(this->rect.x, this->rect.y + height_frame - 30);
        } else if (Store_action.left == 1 || status_character == LEFT)
        {
            BasicAttack.SetRect(this->rect.x - 25, this->rect.y);
        } else
        {
            BasicAttack.SetRect(this->rect.x + width_frame - 30, this->rect.y);
        }
        BasicAttack.Render(screen);
    }
}

void MainObject::UpdateImg(SDL_Renderer* des)
{
    if (Store_action.up == 1)
    {
        if (BasicAttack.get_status() ){
            LoadImg("img//player_slashup.png" ,des);
        }
        else {LoadImg("img//player_up.png" ,des);}
    }

    else if (Store_action.down == 1)
    {
        if (BasicAttack.get_status() ){
            LoadImg("img//player_slashdown.png" ,des);
        }
        else {LoadImg("img//player_down.png" ,des);}
    }

    else if (Store_action.right == 1)
    {
        if (BasicAttack.get_status() ){
            LoadImg("img//player_slashright.png" ,des );
        }
        else {LoadImg("img//player_right.png" ,des);}
    }
    else if (Store_action.left == 1){
        if (BasicAttack.get_status() ){
            LoadImg("img//player_slashleft.png" ,des);
        }
        else {LoadImg("img//player_left.png" ,des);}
    } else
    {
        if (status_character == UP)
        {
            if (BasicAttack.get_status() ){
                LoadImg("img//player_slashup.png" ,des );
            }
            else {LoadImg("img//player_up.png" ,des);}
        }

        else if (status_character == LEFT)
        {
            if (BasicAttack.get_status() ){
                LoadImg("img//player_slashleft.png" ,des);
            }
            else {LoadImg("img//player_left.png" ,des);}
        }

        else if (status_character == RIGHT)
        {
            if (BasicAttack.get_status() ){
                LoadImg("img//player_slashright.png" ,des);
            }
            else {LoadImg("img//player_right.png" ,des);}
        }
        else {
            if (BasicAttack.get_status() ){
                LoadImg("img//player_slashdown.png" ,des);
            }
            else {LoadImg("img//player_down.png" ,des);}
        }
    }
    if (battle)
    {

        LoadImg("img//player_battle.png", des);
    }
}

void MainObject::DoPlayer(Map& map_data)
{
    x_val = 0;
    y_val = 0;
    if (Store_action.left == 1)
    {
        x_val-=PLAYER_SPEED;
    }
    if (Store_action.right == 1)
    {
        x_val+=PLAYER_SPEED;
    }
    if (Store_action.up == 1)
    {
        y_val-=PLAYER_SPEED;
    }
    if (Store_action.down == 1)
    {
        y_val+=PLAYER_SPEED;
    }
    if (xp > 300)
    {
        level++;
    }
    CheckMap(map_data);
    MapMove(map_data);
}

void MainObject::CheckMap(Map& map_data)
{
    int x1 = 0, x2 = 0;
    int y1 = 0, y2 = 0;
    //Check chieu ngang
    int height_min = height_frame < TILE_SIZE ? height_frame : TILE_SIZE;
    x1 = (x_pos + x_val + 35)/TILE_SIZE;
    x2 = (x_pos + x_val + width_frame - 10)/TILE_SIZE;
    y1 = (y_pos + 30)/TILE_SIZE;
    y2 = (y_pos + height_min - 10)/TILE_SIZE;

    int val1 = map_data.tile[y1][x2];
    int val2 = map_data.tile[y2][x2];
    int val3 = map_data.tile[y1][x1];
    int val4 = map_data.tile[y2][x1];

    if (x1 >=0 && x2 <= MAX_MAP_X && y1 >=0 && y2 <= MAX_MAP_Y)
    {
        if (x_val > 0)
        {
            if (val1 == TREASURE || val2 == TREASURE)
            {
                map_data.tile[y1][x2] = FLOOR;
                map_data.tile[y2][x2] = FLOOR;
                map_data.tile[390][1] = KEY;
                have_sword = true;
            } else if (val1 == KEY || val2 == KEY)
            {
                map_data.tile[y1][x2] = FLOOR;
                map_data.tile[y2][x2] = FLOOR;
                map_data.tile[389][6] = DOOR_OPEN;
            } else if (val1 == CHEST || val2 == CHEST)
            {
                map_data.tile[y1][x2] = BLANK_MAP;
                map_data.tile[y2][x2] = BLANK_MAP;
            }
            else
            {
                if ((val1 !=BLANK_MAP && val1 != FLOOR && val1 !=DOOR_OPEN && val1 !=31) ||
                    (val2 !=BLANK_MAP && val2 != FLOOR && val2 !=DOOR_OPEN && val2 != 31))
                {
                    x_pos = x2*TILE_SIZE - width_frame + 5;
                    x_val=0;
                }
            }
        }
        else if (x_val < 0)
        {
            if (val3 == TREASURE || val4 == TREASURE)
            {
                map_data.tile[y1][x1] = FLOOR;
                map_data.tile[y2][x1] = FLOOR;
                map_data.tile[390][1] = KEY;
                have_sword = true;
            } else if (val3 == KEY || val4 == KEY)
            {
                map_data.tile[y1][x1] = FLOOR;
                map_data.tile[y2][x1] = FLOOR;
                map_data.tile[389][6] = DOOR_OPEN;
            } else if (val3 == CHEST || val4 == CHEST)
            {
                map_data.tile[y1][x1] = BLANK_MAP;
                map_data.tile[y2][x1] = BLANK_MAP;
            }
            else
            {
                if ((val3 !=BLANK_MAP && val3 != FLOOR && val3 !=DOOR_OPEN && val3 != 31) ||
                    (val4 !=BLANK_MAP && val4 != FLOOR && val4 !=DOOR_OPEN && val4 != 31))
                {
                    x_pos = x1*TILE_SIZE+30;
                    x_val = 0;
                }
            }
        }
    }
    //Check chieu doc
    int width_min = width_frame < TILE_SIZE ? width_frame : TILE_SIZE;
    x1 = (x_pos + 40)/TILE_SIZE;
    x2 = (x_pos + width_min - 30)/TILE_SIZE;
    y1 = (y_pos + y_val + 25)/TILE_SIZE;
    y2 = (y_pos + y_val + height_frame - 5)/TILE_SIZE;

    val1 = map_data.tile[y1][x2];
    val2 = map_data.tile[y2][x2];
    val3 = map_data.tile[y1][x1];
    val4 = map_data.tile[y2][x1];

    if (x1 >=0 && x2 <= MAX_MAP_X && y1 >=0 && y2 <= MAX_MAP_Y)
    {
        if (y_val > 0)
        {
            if (val2 == TREASURE || val4 == TREASURE)
            {
                map_data.tile[y2][x2] = FLOOR;
                map_data.tile[y2][x1] = FLOOR;
                map_data.tile[390][1] = KEY;
                have_sword = true;
            } else if (val2 == KEY || val4 == KEY)
            {
                map_data.tile[y2][x2] = FLOOR;
                map_data.tile[y2][x1] = FLOOR;
                map_data.tile[389][6] = DOOR_OPEN;
            } else if (val2 == CHEST || val4 == CHEST)
            {
                map_data.tile[y2][x2] = BLANK_MAP;
                map_data.tile[y2][x1] = BLANK_MAP;
            }
            else
            {
                if ((val2 != BLANK_MAP && val2 !=FLOOR && val2 !=DOOR_OPEN && val2 != 31) ||
                    (val4 != BLANK_MAP && val4 !=FLOOR && val4 !=DOOR_OPEN && val4 != 31))
                {
                    y_pos = y2*TILE_SIZE - height_frame + 5;
                    y_val=0;
                }
            }
        }
        else if (y_val < 0)
        {
            if (val1 == TREASURE || val3 == TREASURE)
            {
                map_data.tile[y1][x1] = FLOOR;
                map_data.tile[y1][x2] = FLOOR;
                map_data.tile[390][1] = KEY;
                have_sword = true;
            }
            else if (val1 ==  KEY|| val3 == KEY)
            {
                map_data.tile[y1][x1] = FLOOR;
                map_data.tile[y1][x2] = FLOOR;
                map_data.tile[389][6] = DOOR_OPEN;
            } else if (val1 ==  CHEST|| val3 == CHEST)
            {
                map_data.tile[y1][x1] = BLANK_MAP;
                map_data.tile[y1][x2] = BLANK_MAP;
            }
            else
            {
                if ((val1 !=BLANK_MAP && val1 !=FLOOR && val1 !=DOOR_OPEN && val1 != 31) ||
                    (val3 !=BLANK_MAP && val3 !=FLOOR && val3 !=DOOR_OPEN && val3 != 31))
                {
                    y_pos = y2*TILE_SIZE - 30;
                    y_val = 0;
                }
            }
        }
    }
    x_pos+=x_val;
    y_pos+=y_val;

    if (x_pos < 0)
    {
        x_pos=0;
    }
    else if (x_pos + width_frame > map_data.max_x)
    {
        x_pos = map_data.max_x - width_frame - 1;
    }
    if (y_pos < 0)
    {
        y_pos=0;
    }
    else if (y_pos + height_frame > map_data.max_y)
    {
        y_pos = map_data.max_y - height_frame - 1;
    }
}

void MainObject::MapMove(Map& map_data)
{
    //chieu x
    map_data.start_x = x_pos - (SCREEN_WIDTH/2);
    if (map_data.start_x < 0)
    {
        map_data.start_x = 0;
    }
    else if (map_data.start_x + SCREEN_WIDTH >= map_data.max_x)
    {
        map_data.start_x = map_data.max_x - SCREEN_WIDTH;
    }
    //Chieu y
    map_data.start_y = y_pos - (SCREEN_HEIGHT/2);

    if (map_data.start_y < 0)
    {
        map_data.start_y = 0;
    }
    else if (y_pos >= LEVEL_1*TILE_SIZE)
    {
        map_data.start_y = map_data.max_y - SCREEN_HEIGHT;
    }
    else if (y_pos >= LEVEL_1_5*TILE_SIZE)
    {
        if (map_data.start_y + SCREEN_HEIGHT > LEVEL_1*TILE_SIZE + TILE_SIZE)
        {
            map_data.start_y = LEVEL_1*TILE_SIZE - SCREEN_HEIGHT + TILE_SIZE;
        } else if (map_data.start_y <= LEVEL_1_5*TILE_SIZE)
        {
            map_data.start_y = LEVEL_1_5*TILE_SIZE;
        }
    }
    else if (y_pos >= LEVEL_2*TILE_SIZE)
    {
        if (map_data.start_y + SCREEN_HEIGHT > LEVEL_1_5*TILE_SIZE + TILE_SIZE)
        {
            map_data.start_y = LEVEL_1_5*TILE_SIZE - SCREEN_HEIGHT + TILE_SIZE;
        } else if (map_data.start_y <= LEVEL_2*TILE_SIZE)
        {
            map_data.start_y = LEVEL_2*TILE_SIZE;
        }
    }
    else if (y_pos >= LEVEL_3*TILE_SIZE)
    {
        if (map_data.start_y + SCREEN_HEIGHT > LEVEL_2*TILE_SIZE + TILE_SIZE)
        {
            map_data.start_y = LEVEL_2*TILE_SIZE - SCREEN_HEIGHT + TILE_SIZE;
        } else if (map_data.start_y <= LEVEL_3*TILE_SIZE)
        {
            map_data.start_y = LEVEL_3*TILE_SIZE;
        }
    }
    else if (y_pos >= LEVEL_4*TILE_SIZE)
    {
        if (map_data.start_y + SCREEN_HEIGHT > LEVEL_3*TILE_SIZE + TILE_SIZE)
        {
            map_data.start_y = LEVEL_3*TILE_SIZE - SCREEN_HEIGHT + TILE_SIZE;
        } else if (map_data.start_y <= LEVEL_4*TILE_SIZE - TILE_SIZE)
        {
            map_data.start_y = LEVEL_4*TILE_SIZE - TILE_SIZE;
        }
    } else
    {
        if (map_data.start_y + SCREEN_HEIGHT > LEVEL_4*TILE_SIZE + TILE_SIZE)
        {
            map_data.start_y = LEVEL_4*TILE_SIZE - SCREEN_HEIGHT + TILE_SIZE;
        }
    }
}

SDL_Rect MainObject::GetRectP()
{
    SDL_Rect RETURN;
    RETURN.x = rect.x + 20;
    RETURN.y = rect.y + 20;
    RETURN.w = width_frame - 20;
    RETURN.h = height_frame - 20;

    return RETURN;
}

void MainObject::ShowStat(TTF_Font* font, SDL_Renderer* screen)
{
    Text_object HPStat, XP, Level, HPNew;
    std::string HPText = "HP: "; std::string XPText = "XP: "; std::string LEVEL = "Level: ";
    std::string HP_num = std::to_string(HP);
    std::string XP_num = std::to_string(xp);
    std::string LEVEL_num = std::to_string(level);
    HPText += HP_num; XPText += XP_num; LEVEL += LEVEL_num;
    HP_num = std::to_string(maxHP); XP_num = std::to_string(xp_cap);
    HPText += "/"; XPText += "/";
    HPText += HP_num; XPText += XP_num;
    XP.SetText(XPText); Level.SetText(LEVEL);
    HPNew.SetText(HPText);
    HPNew.LoadFromRenderText(font,screen);
    XP.LoadFromRenderText(font, screen);
    Level.LoadFromRenderText(font,screen);
    HPNew.RenderText(screen,SCREEN_WIDTH-128, 40);
    XP.RenderText(screen, SCREEN_WIDTH-128, 65);
    Level.RenderText(screen,SCREEN_WIDTH-128, 90);
}

void MainObject::UpdateBattleStatus (const bool& x)
{
    battle = x;
    Store_action.up = 0;
    Store_action.left = 0;
    Store_action.right = 0;
    Store_action.down = 0;
    BasicAttack.set_attack(false);
}

void MainObject::HandleXP()
{
    if (xp >= xp_cap)
    {
        level++;
        xp=xp - xp_cap;
        xp_cap += level*10;
        maxHP += level*5;
        ATK += level*2/5;
    }
}

void MainObject::ShowBattleStat(TTF_Font* font, SDL_Renderer* screen)
{
    Text_object Speed, Atk, Level, HPNew;
    std::string HPText = "HP: " + std::to_string(HP);
    std::string XPText = "Speed: " ;
    std::string LEVEL = "Player (Level ";
    std::string ATKText ="ATK: " ;
    std::string x = std::to_string(maxHP);
    HPText += "/" + x;
    x=std::to_string(level) + ")";
    LEVEL += x;
    x = std::to_string(SPEED);
    XPText += x;
    x = std::to_string(ATK);
    ATKText += x;

    Speed.SetText(XPText); Level.SetText(LEVEL);
    HPNew.SetText(HPText); Atk.SetText(ATKText);

    Level.LoadFromRenderText(font,screen);
    HPNew.LoadFromRenderText(font,screen);
    Atk.LoadFromRenderText(font, screen);
    Speed.LoadFromRenderText(font, screen);

    Level.RenderText(screen, 30, 45);
    HPNew.RenderText(screen, 30, 75);
    Atk.RenderText(screen, 30, 105);
    Speed.RenderText(screen, 30, 135);
}
