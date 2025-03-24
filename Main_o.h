#ifndef MAIN_OBJECT
#define MAIN_OBJECT

#include "BObject.h"
#include "Game_Stat.h"

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
        LEFT = 3,
    };

    bool LoadImg(std::string path, SDL_Renderer* screen);
    bool Show(SDL_Renderer* design);
    void HandleEvent(SDL_Event events, SDL_Renderer* screen);
    void Clip();

private:
    float x_val;
    float y_val;

    float x_pos;
    float y_pos;

    int width_frame;
    int height_frame;

    SDL_Rect frame_clip[8];
    Input_action Store_action;
    int frame_num;
    int status_character;

};

#endif // MAIN_OBJECT
