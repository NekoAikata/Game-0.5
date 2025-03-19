#ifndef GAME_MAP
#define GAME_MAP

#include "Game_Stat.h"\
#include "BObject.h"
#include <fstream>

#define MAX_TILE 20

class Tile : public BaseObject
{
public:
    Tile() {;}
    ~Tile() {;}
};

class GameMap
{
public:
    GameMap() {;}
    ~GameMap() {;}
    void LoadMap(char* Name);
    void LoadTiles (SDL_Renderer* screen);
    void DrawMap (SDL_Renderer* screen);
private:
    Map game_map;
    Tile TileMap[MAX_TILE];
};

#endif // GAME_MAP
