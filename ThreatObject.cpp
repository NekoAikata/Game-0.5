#include "ThreatObject.h"

ThreatObject::ThreatObject()
{
    maxHP = 0;
    HP = 0;
    ATK = 0;
    HP_drop = 0;
    XP_drop = 0;

	revive_time = 0;
    x_val = 0;
    y_val = 0;
    x_pos = 0;
    y_pos = 0;
    width_frame = 0;
    height_frame = 0;
    frame_num = 0;
    frame_delay = 0;

    mapvalue_x;
    mapvalue_y;
    x_pos__respawn = 0;
    y_pos_respawn = 0;

    type = 0;

    animation_up = 0;
    animation_down = 0;
    animation_left = 0;
    animation_right = 0;
    Input_type.left = 0;
    Input_type.right = 0;
}

ThreatObject::~ThreatObject ()
{

}

bool ThreatObject::LoadImg (std::string path, SDL_Renderer* screen)
{
	bool ret = BaseObject::LoadImg(path, screen);

	height_frame = rect.h;

    if (ret)
    {
        if (type == 3)
        {width_frame = rect.w/9;}
        if (type == 0 || type == 1 || type == 4 || type == 5 || type == 9 || type == 10) width_frame = rect.w/4;
        if (type == 2 || type == 6 || type == 7 || type == 8) width_frame = rect.w/3;
    }

    return ret;
}

void ThreatObject::Clip()
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

void ThreatObject::Show(SDL_Renderer* des)
{
    frame_delay++;
    if (frame_delay > FRAME_DELAY) {frame_num++; frame_delay =0;}
    if (frame_num >= 4 && (type == 1 || type == 0 || type == 4 || type == 5 || type == 9 || type == 10) ||
        (frame_num >= 9 && (type == 3)) ||
        (frame_num >= 3 && (type == 2 || type == 6 || type == 7 || type == 8)))
    {
        frame_num = 0;
    }

    rect.x = x_pos - mapvalue_x;
    rect.y = y_pos - mapvalue_y;

    SDL_Rect* current_clip = &frame_clip[frame_num];

    SDL_Rect renderQuad = {rect.x, rect.y, 64, 64};
    SDL_RenderCopy(des, texture, current_clip, &renderQuad);
}

void ThreatObject::DoThreat (Map& map_data)
{
    if (revive_time == 0)
    {
        x_val = 0;
        y_val = 0;

        if (frame_delay == 0)
        {
            if (Input_type.left == 1)
            {
                x_val-=THREAT_SPEED;
            } else if (Input_type.right == 1)
            {
                x_val+=THREAT_SPEED;
            } else if (Input_type.up == 1)
            {
                y_val-=THREAT_SPEED;
            } else if  (Input_type.down == 1)
            {
                y_val+=THREAT_SPEED;
            }
            CheckMap (map_data);
        }
    }
    else if (revive_time > 0)
    {
        revive_time--;
        if (revive_time == 0)
        {
            x_val = 0;
            y_val = 0;
            x_pos = x_pos__respawn;
            y_pos = y_pos_respawn;
            HP=maxHP;
        }
    }
}

void ThreatObject::CheckMap (Map& map_data)
{
    int x1 = 0, x2 = 0;
    int y1 = 0, y2 = 0;
    //Check chieu ngang
    int height_min = height_frame < TILE_SIZE ? height_frame : TILE_SIZE;
    x1 = (x_pos + x_val)/TILE_SIZE;
    x2 = (x_pos + x_val + width_frame - 1)/TILE_SIZE;
    y1 = (y_pos)/TILE_SIZE;
    y2 = (y_pos + height_min - 1)/TILE_SIZE;

    int val1 = map_data.tile[y1][x2];
    int val2 = map_data.tile[y2][x2];
    int val3 = map_data.tile[y1][x1];
    int val4 = map_data.tile[y2][x1];

    if (x1 >=0 && x2 <= MAX_MAP_X && y1 >=0 && y2 <= MAX_MAP_Y)
    {
        if (x_val > 0)
        {
                if (val1 != BLANK_MAP || val2 !=BLANK_MAP)
                {
                    x_pos = x2*TILE_SIZE - width_frame - 1;
                    x_val=0;
                }
        }
        else if (x_val < 0)
        {
                if (val3 !=BLANK_MAP || val4 !=BLANK_MAP)
                {
                    x_pos = (x1+1)*TILE_SIZE;
                    x_val = 0;
                }
        }
    }
    //Check chieu doc
    int width_min = width_frame < TILE_SIZE ? width_frame : TILE_SIZE;
    x1 = (x_pos)/TILE_SIZE;
    x2 = (x_pos + width_min - 1)/TILE_SIZE;
    y1 = (y_pos + y_val)/TILE_SIZE;
    y2 = (y_pos + y_val + height_frame - 1)/TILE_SIZE;

    val1 = map_data.tile[y1][x2];
    val2 = map_data.tile[y2][x2];
    val3 = map_data.tile[y1][x1];
    val4 = map_data.tile[y2][x1];

    if (x1 >=0 && x2 <= MAX_MAP_X && y1 >=0 && y2 <= MAX_MAP_Y)
    {
        if (y_val > 0)
        {
                if (val2 != BLANK_MAP || val4 !=BLANK_MAP)
                {
                    y_pos = y2*TILE_SIZE - height_frame - 1;
                    y_val=0;
                }
        }
        else if (y_val < 0)
        {
                if (val1 !=BLANK_MAP || val3 !=BLANK_MAP)
                {
                    y_pos = (y1+1)*TILE_SIZE;
                    y_val = 0;
                }
        }
    }
    x_pos += x_val;
    y_pos +=y_val;
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

void ThreatObject::Move (SDL_Renderer* screen)
{
    if (type == 1 || type == 3 || type == 6 || type == 7 || type == 9)
    {
        if (x_pos >= animation_right)
        {
            Input_type.left = 1;
            Input_type.right = 0;
            if (type == 1) LoadImg("img//threat_slime.png", screen);
            if (type == 3) LoadImg("img//spider_left.png", screen);
            if (type == 6) LoadImg ("img//Mush_2_left.png", screen);
            if (type == 7) LoadImg ("img//Mush_1_left.png", screen);
            if (type == 9) LoadImg ("img//golem_left.png", screen);
        } else if (x_pos <= animation_left)
        {
            Input_type.right = 1;
            Input_type.left = 0;
            if (type == 1) LoadImg ("img//threat_slime.png", screen);
            if (type == 3) LoadImg ("img//spider_right.png", screen);
            if (type == 6) LoadImg ("img//Mush_2_right.png", screen);
            if (type == 7) LoadImg ("img//Mush_1_right.png", screen);
            if (type == 9) LoadImg ("img//golem_right.png", screen);
        }
    }
    else if (type == 2 || type == 8 || type == 10)
    {
        if (y_pos >= animation_down){
            Input_type.down = 0;
            Input_type.up = 1;
            if (type == 2) LoadImg("img//Mush_2_up.png", screen);
            if (type == 8) LoadImg("img//Mush_1_up.png", screen);
            if (type == 10) LoadImg("img//slime_up.png", screen);
        } else if (y_pos <= animation_up)
        {
            Input_type.down = 1;
            Input_type.up = 0;
            if (type == 2) LoadImg("img//Mush_2_down.png", screen);
            if (type == 8) LoadImg("img//Mush_1_down.png", screen);
            if (type == 10) LoadImg("img//threat_slime.png", screen);
        }
    }
    else if (type == 0 || type == 4 || type == 5)
    {
        ;
    }
}

void ThreatObject::InitBullet (BulletObject* p_bullet, SDL_Renderer*screen)
{
    if (p_bullet != NULL)
    {
        bool ret = p_bullet->LoadImgBullet(screen);
        p_bullet->set_is_move(true);
        p_bullet->set_bullet_dir(BulletObject::DIR_LEFT);
        p_bullet->SetRect(rect.x, rect.y);
        p_bullet->set_x_val(15);
        bullet_list.push_back(p_bullet);
    }
}

void ThreatObject::MakeBullet(SDL_Renderer* screen, const int& x_limit, const int& y_limit)
{
    for (int i = 0; i < bullet_list.size(); ++i)
    {
        BulletObject* p_bullet = bullet_list[i];
        if(p_bullet != NULL)
        {
            if (p_bullet->get_is_move())
            {
                    p_bullet->SetRect(p_bullet->GetRect().x, rect.y);
                    p_bullet->HandleMove(x_limit, y_limit);
                    p_bullet->Render(screen);
            } else
            {
                p_bullet->set_is_move(true);
                p_bullet->SetRect(rect.x, rect.y);
            }
            if (type == 4)
            {
                p_bullet->set_bullet_dir(21);
            } else if (type == 5)
            {
                p_bullet->set_bullet_dir(20);
            }
        }
    }
}
