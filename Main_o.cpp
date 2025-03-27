#include "Main_o.h"

MainObject::MainObject()
{
    x_val = 0;
    y_val = 0;
    x_pos = 0;
    y_pos = 0;
    width_frame = 0;
    height_frame = 0;
    frame_num = 0;
    status_character = -1;
}

MainObject::~MainObject()
{

}

bool MainObject::LoadImg(std::string path, SDL_Renderer* screen)
{
    bool ret = BaseObject::LoadImg(path, screen);

    if (ret)
    {
        width_frame = rect.w/6;
        height_frame = rect.h;
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

        /*frame_clip[6].x = 6*width_frame;
        frame_clip[6].y = 0;
        frame_clip[6].h = height_frame;
        frame_clip[6].w = width_frame;

        frame_clip[7].x = 7*width_frame;
        frame_clip[7].y = 0;
        frame_clip[7].h = height_frame;
        frame_clip[7].w = width_frame;*/
    }
}

bool MainObject::Show(SDL_Renderer* des)
{
    if (status_character == UP)
    {
        LoadImg("img//player_up.png" ,des);
    }

    else if (status_character == LEFT)
    {
        LoadImg("img//player_left.png" ,des);
    }

    else if (status_character == RIGHT)
    {
        LoadImg("img//player_right.png" ,des);
    }
    else {
        LoadImg("img//player_down.png" ,des);
    }

    if (Store_action.left == 1 || Store_action.right == 1 || Store_action.up == 1 || Store_action.down == 1)
    {
        frame_num++;
    }
    else{
        frame_num = 0;
    }

    if (frame_num >= 6)
    {
        frame_num = 0;
    }
    rect.x = x_pos;
    rect.y = y_pos;

    SDL_Rect* current_clip = &frame_clip[frame_num];

    SDL_Rect renderQuad = {rect.x, rect.y, width_frame, height_frame};
    SDL_RenderCopy(des, texture, current_clip, &renderQuad);
}

void MainObject::HandleEvent(SDL_Event event, SDL_Renderer* screen)
{
    if(event.type == SDL_KEYDOWN)
    {
        switch (event.key.keysym.sym)
        {
        case SDLK_UP:
            {
                status_character = UP;
                Store_action.up = 1;
                break;
            }
        case SDLK_DOWN:
            {
                status_character = DOWN;
                Store_action.down = 1;
                break;
            }
        case SDLK_RIGHT:
            {
                status_character = RIGHT;
                Store_action.right = 1;
                break;
            }
        case SDLK_LEFT:
            {
                status_character = LEFT;
                Store_action.left = 1;
                break;
            }
        }
    } else if(event.type == SDL_KEYUP)
    {
        switch (event.key.keysym.sym)
        {
        case SDLK_UP:
            {
                Store_action.up = 0;
                break;
            }
        case SDLK_DOWN:
            {
                Store_action.down = 0;
                break;
            }
        case SDLK_RIGHT:
            {
                Store_action.right = 0;
                break;
            }
        case SDLK_LEFT:
            {
                Store_action.left = 0;
                break;
            }
        }
    }
}
