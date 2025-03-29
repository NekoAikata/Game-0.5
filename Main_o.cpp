#include "Main_o.h"

MainObject::MainObject()
{
    x_val = 0;
    y_val = 0;
    x_pos = 6*TILE_SIZE;
    y_pos = TILE_SIZE;
    width_frame = 0;
    height_frame = 0;
    frame_num = 0;
    status_character = -1;
    Store_action.down = 0;
    Store_action.up = 0;
    Store_action.left = 0;
    Store_action.right = 0;
    mapvalue_x = 0;
    mapvalue_y = 0;
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
    rect.x = x_pos - mapvalue_x;
    rect.y = y_pos - mapvalue_y;

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

void MainObject::DoPlayer(Map& map_data)
{
    x_val = 0;
    y_val = 0;
    if (Store_action.left == 1)
    {
        x_val-=PLAYER_SPEED;
    }
    else if (Store_action.right == 1)
    {
        x_val+=PLAYER_SPEED;
    }
    else if (Store_action.up == 1)
    {
        y_val-=PLAYER_SPEED;
    }
    else if (Store_action.down == 1)
    {
        y_val+=PLAYER_SPEED;
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
    x1 = (x_pos + x_val)/TILE_SIZE;
    x2 = (x_pos + x_val + width_frame - 1)/TILE_SIZE;
    y1 = (y_pos)/TILE_SIZE;
    y2 = (y_pos + height_min - 1)/TILE_SIZE;

    if (x1 >=0 && x2 <= MAX_MAP_X && y1 >=0 && y2 <= MAX_MAP_Y)
    {
        if (x_val > 0)
        {
            if (map_data.tile[y1][x2] != BLANK_MAP || map_data.tile[y2][x2]!=BLANK_MAP)
            {
                x_pos = x2*TILE_SIZE - width_frame - 1;
                x_val=0;
            }
        }
        else if (x_val < 0)
        {
            if (map_data.tile[y1][x1] !=BLANK_MAP || map_data.tile[y2][x1]!=BLANK_MAP)
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
    if (x1 >=0 && x2 <= MAX_MAP_X && y1 >=0 && y2 <= MAX_MAP_Y)
    {
        if (y_val > 0)
        {
            if (map_data.tile[y2][x2] != BLANK_MAP || map_data.tile[y2][x1]!=BLANK_MAP)
            {
                y_pos = y2*TILE_SIZE - height_frame - 1;
                y_val=0;
            }
        }
        else if (y_val < 0)
        {
            if (map_data.tile[y1][x1]!=BLANK_MAP || map_data.tile[y1][x2]!=BLANK_MAP)
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

void MainObject::MapMove(Map& map_data)
{
    map_data.start_x = x_pos - (SCREEN_WIDTH/2);
    if (map_data.start_x < 0)
    {
        map_data.start_x = 0;
    }
    else if (map_data.start_x + SCREEN_WIDTH >= map_data.max_x)
    {
        map_data.start_x = map_data.max_x - SCREEN_WIDTH;
    }
    map_data.start_y = y_pos - (SCREEN_HEIGHT/2);
    if (map_data.start_y < 0)
    {
        map_data.start_y = 0;
    }
    else if (map_data.start_y + SCREEN_HEIGHT >= map_data.max_y)
    {
        map_data.start_y = map_data.max_y - SCREEN_HEIGHT;
    }
}
