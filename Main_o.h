#ifndef MAIN_OBJECT
#define MAIN_OBJECT

#include "BObject.h"
#include "Game_Stat.h"
#include "Slash.h"
#include "Text.h"

#define PLAYER_SPEED 6
#define PLAYER_ATTACK 1500
#define FRAME_DELAY 3

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

    void UpdateBattleStatus (const bool& x);

    void DoPlayer(Map& map_data);
    void CheckMap(Map& map_data);
    void SetMapXY(const int x, const int y) {mapvalue_x = x; mapvalue_y = y;}
    void MapMove(Map& map_data);

    void HandleSlash (SDL_Renderer* screen);
    void FreeSlash () {BasicAttack.Free();}
    Slash* GetSlash () {return &BasicAttack;}
    SDL_Rect GetRectP();
    int frame_delay;

    void SetXPos(const float& x) {x_pos = x;}
    void SetYPos(const float& x) {y_pos = x;}
    float GetYPos() {return y_pos;}

    void ShowStat(TTF_Font* font, SDL_Renderer* screen);
    void ShowBattleStat (TTF_Font* font, SDL_Renderer* screen);
    void HandleXP ();
    int HP;
    int maxHP;

    int ATK;
    int SPEED;

    bool have_sword;

    int xp;
    int xp_cap;
    int level;

private:
    bool battle;

    Slash BasicAttack;
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
