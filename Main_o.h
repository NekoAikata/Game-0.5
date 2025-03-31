#ifndef MAIN_OBJECT
#define MAIN_OBJECT

#include "BObject.h"
#include "Game_Stat.h"
#include <vector>
#include <algorithm>

#define PLAYER_SPEED 6
class MainObject : public BaseObject
{
public:
    MainObject();
    ~MainObject();

    enum Move_status
    {
        UP = 0,
        DOWN = 1,
        RIGHT = 2,
        LEFT = 3
    };

    bool LoadImg(std::string path, SDL_Renderer* screen);
    bool Show(SDL_Renderer* des);
    void HandleEvent(SDL_Event events, SDL_Renderer* screen);
    void UpdateImg(SDL_Renderer* screen);
    void Clip();

    void DoPlayer(Map& map_data);
    void CheckMap(Map& map_data);
    void SetMapXY(const int x, const int y) {mapvalue_x = x; mapvalue_y = y;}
    void MapMove(Map& map_data);
    void GetValue() {std::cout << y_pos << std::endl;}

private:
    float x_val;
    float y_val;

    float x_pos;
    float y_pos;

    int width_frame;
    int height_frame;

    SDL_Rect frame_clip[6];
    Input_action Store_action;
    int frame_num;
    int status_character;

    int mapvalue_x;
    int mapvalue_y;


};

#endif // MAIN_OBJECT
