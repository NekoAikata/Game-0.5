#include "ThreatObject.h"

ThreatObject::ThreatObject()
{
	revive_time = 0;
    x_val = 0;
    y_val = 0;
    x_pos = 0;
    y_pos = 0;
    width_frame = 0;
    height_frame = 0;
    frame_num = 0;
    mapvalue_x;
    mapvalue_y;

    type = 0;
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

    if (ret)
    {
        height_frame = rect.h;
        width_frame = rect.w/4;
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
    }
}

void ThreatObject::Show(SDL_Renderer* des)
{
	frame_num++;
    if (frame_num >= 4)
    {
        frame_num = 0;
    }
    rect.x = x_pos - mapvalue_x;
    rect.y = y_pos - mapvalue_y;

    SDL_Rect* current_clip = &frame_clip[frame_num];

    SDL_Rect renderQuad = {rect.x, rect.y, width_frame, height_frame};
    SDL_RenderCopy(des, texture, current_clip, &renderQuad);
}

void ThreatObject::DoThreat (Map& map_data)
{
    if (revive_time == 0)
    {
        x_val = 0;
        y_val = 0;

        if (Input_type.left == 1)
        {
            x_val-=THREAT_SPEED;
        } else if (Input_type.right == 1)
        {
            x_val+=THREAT_SPEED;
        }
        CheckMap (map_data);
    }
    else if (revive_time > 0)
    {
        revive_time--;
        if (revive_time == 0)
        {
            x_val = 0;
            y_val = 0;
            x_pos = 0;
            y_pos = 0;
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
    if (type == 1)
    {
        if (x_pos > animation_right)
        {
            Input_type.left = 1;
            Input_type.right = 0;
            LoadImg("img//threat_slime.png", screen);
        } else if (x_pos < animation_left)
        {
            Input_type.right = 1;
            Input_type.left = 0;
            LoadImg ("img//threat_slime.png", screen);
        }
    } else if (type == 0)
    {
        ;
    }
}
