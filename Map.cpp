#include "Map.h"

void GameMap::LoadMap (char* name)
{
    std::ifstream InputFile (name, std::ios::binary | std::ios::in);
    if(!(InputFile.is_open())){
        return;
    }

    game_map.max_x = 13;
    game_map.max_y = 349;
    for (int i = 0; i < MAX_MAP_Y; i++)
    {
        for (int j = 0; j< MAX_MAP_X; j++)
        {
            InputFile >> game_map.tile[i][j];
            int val = game_map.tile[i][j];
        }
    }

    game_map.max_x = (game_map.max_x+1)*TILE_SIZE;
    game_map.max_y = (game_map.max_y+1)*TILE_SIZE;
    game_map.start_x = 0;
    game_map.start_y = 0;
    game_map.File_name = name;
    InputFile.close();
}

void GameMap::LoadTiles (SDL_Renderer* screen)
{
    char file_img[20];
    for (int i =0; i< MAX_TILE; i++)
    {
        sprintf_s (file_img, "map/%d.png", i);

        std::ifstream InputImg (file_img, std::ios::binary | std::ios::in);
        if (!(InputImg.is_open()))
        {
            continue;
        }
        InputImg.close();

        TileMap[i].LoadImg(file_img, screen);
        int w_test = TileMap[i].GetRect().w;
        int h_test = TileMap[i].GetRect().h;
        if (w_test < 64 && h_test < 64 && i!=22)
        {
            TileMap[i].SetRectWH(64,64);
        } else if (i==22)
        {
            TileMap[i].SetRectWH(56,56);
        }
    }
}

void GameMap::DrawMap (SDL_Renderer* screen)
{
    int x1 = 0;
    int x2 = 0;
    int y1 = 0;
    int y2 = 0;

    x1 = (game_map.start_x%TILE_SIZE)*-1;
    x2 = x1+SCREEN_WIDTH + ((x1 == 0) ? 0 : TILE_SIZE);
    y1 = (game_map.start_y%TILE_SIZE)*-1;
    y2 = y1+SCREEN_HEIGHT + ((y1 == 0) ? 0 : TILE_SIZE);
    int map_x = game_map.start_x/TILE_SIZE;
    int map_y = game_map.start_y/TILE_SIZE;

    for (int i = y1; i<y2; i+=TILE_SIZE)
    {
        map_x = game_map.start_x/TILE_SIZE;
        for (int j =x1;j<x2;j+=TILE_SIZE)
        {
            int val=game_map.tile[map_y][map_x];
            if (val >0 && val!=46 && val!=54 && val!=55 && val!=57)
            {
                TileMap[val].SetRect(j, i);
                TileMap[val].Render(screen);
            } else if (val == 46)
            {
                TileMap[val].SetRect(j - 0.5*TILE_SIZE, i - 2*TILE_SIZE);
                TileMap[val].Render(screen);
            } else if (val == 54 || val == 55 || val == 57)
            {
                TileMap[val].SetRect(j, i-TILE_SIZE + 16);
                TileMap[val].Render(screen);
            }
            map_x++;
        }
        map_y++;
    }
}
