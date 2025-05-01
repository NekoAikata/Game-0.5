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

bool BossThreat::BossCombat (MainObject Player)
{

}
